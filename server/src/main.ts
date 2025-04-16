import "dotenv/config"

import express from "express"
import { createServer } from "http"
import * as fs from "node:fs"
import * as path from "node:path"

import sqlite3 from "sqlite3"
import { open } from "sqlite"

const router = express()
const httpServer = createServer(router)
router.use(express.json());

// router.use((req, res, next) => {
//     console.log(games)
//     next();
// })

const lvlStats = fs.readFileSync(path.join(__dirname, "..", "resources", "LevelStats.dat")).toString()
const levelIds = lvlStats.split(",").filter((_, index) => index % 2 === 0).map(val => parseInt(val));

async function openDB() {
    return await open({
        filename: process.env.DATABASE_FILE || "./database.db",
        driver: sqlite3.Database
    })
}

(async () => {
    const db = await openDB();
    db.migrate()
})()

type LevelDate = {
    year: number
    month: number
    day: number
}

type Game = {
    accountId: number
    currentLevelId: number
}

const games: {[key: string]: Game} = {}

function stringToLvlDate(str: string): LevelDate {
    const split = str.split("-").map(val => parseInt(val))
    return {
        year: split[0],
        month: split[1],
        day: split[2]
    }
}

// scoring works as indicated in the Doggie video
// if the player is within a week of the correct answer, they get the maximum amount of points (500)
// if they are not, we take off one point for every day off, to a mimimum of 0 points

function calcScore(guess: LevelDate, correct: LevelDate): number {
    const guessDate = new Date(guess.year, guess.month - 1, guess.day)
    const correctDate = new Date(correct.year, correct.month - 1, correct.day)

    const diffDays = Math.ceil(Math.abs(guessDate.getTime() - correctDate.getTime()) / (1000 * 3600 * 24))

    if (diffDays <= 7) {
        return 500
    }

    return Math.max(500 - diffDays, 0)
}

const getRandomLevelId = () => levelIds[Math.floor((Math.random() * levelIds.length) % levelIds.length)]

function getDashAuthUrl() {
    let str = process.env.DASHAUTH_URL
    return str?.endsWith('/') ?
        str.slice(0, -1) :
        str
}

async function checkToken(token: string) {
    const req = await fetch(`${getDashAuthUrl()}/api/v1/verify`, {
        method: "POST",
        body: JSON.stringify({
            token
        }),
        headers: {
            "Content-Type": "application/json"
        }
    })
    return req 
}

router.post("/start-new-game", async (req, res) => {
    const token = req.headers.authorization || "";
    const daResp = await checkToken(token)

    if (daResp.status === 401) {
        res.status(401).send("invalid token")
        return
    }

    const data = (await daResp.json())["data"]
    if (Object.keys(games).includes(data["id"])) {
        res.status(400).send("game already in progress")
        return
    }

    const id = getRandomLevelId()
    games[data["id"]] = {
        accountId: data["id"],
        currentLevelId: id,
    }

    res.json({
        level: id,
        game: games[data["id"]]
    })
})

// `date` is in the format: `year-month-day`, i.e.: "2013-08-13"

router.post("/guess/:date", async (req, res) => {
    const token = req.headers.authorization || ""
    const daResp = await checkToken(token)

    if (daResp.status === 401) {
        res.status(401).send("invalid token")
        return
    }
    const data = (await daResp.json())["data"]
    if (!Object.keys(games).includes(data["id"].toString())) {
        res.status(404).send("game does not exist. did you mean to call /start-new-game?")
        return
    }

    const { date } = req.params
    const levelId = games[data["id"]].currentLevelId

    const correctDate: string = (
    await (
        await fetch(`https://history.geometrydash.eu/api/v1/date/level/${levelId}/`)).json()
    )["approx"]["estimation"]
    .split("T")[0]

    const score = calcScore(stringToLvlDate(date), stringToLvlDate(correctDate))

    const db = await openDB()
    await db.run(`
        INSERT INTO scores (account_id, username, total_score, icon_id)
        VALUES (?, ?, ?, ?)    
        ON CONFLICT (account_id) DO
        UPDATE SET username = ?, total_score = total_score + ?
    `, data["id"], data["username"], score, 1, data["username"], score)

    delete games[data["id"]]

    res.json({
        score
    })
})

router.post("/endGame", async (req, res) => {
    const token = req.headers.authorization || ""
    const daResp = await checkToken(token)

    if (daResp.status === 401) {
        res.status(401).send("invalid token")
        return
    }
    const data = (await daResp.json())["data"]
    if (!Object.keys(games).includes(data["id"].toString())) {
        res.status(404).send("game does not exist")
        return
    }

    delete games[data["id"]]

    res.status(200).send()
})

router.get("/account/:id", async (req, res) => {
    const db = await openDB()

    const response = await db.get(`
        SELECT * FROM scores
        WHERE account_id = ?     
    `, req.params.id)

    if (!response) {
        res.status(404).send("no account found")
        return
    }

    res.json(
        response
    )
})

router.get("/leaderboard", async (req, res) => {
    const db = await openDB()
    const results = await db.all(`
        SELECT * FROM scores
        ORDER BY total_score DESC
        LIMIT 100
    `)
    res.json(results)
})

router.use("/dashauth", async (req, res, next) => {
    const resp = await (await fetch(`${getDashAuthUrl()}${req.path.replace("dashauth", "")}`, {
        body: req.body,
        headers: Object(req.headers),
        method: req.method
    })).json()

    // console.log(resp)

    res.json(resp)
})

const port = process.env.PORT || 8000

console.log(`listening on port ${port}`)
httpServer.listen(port)
