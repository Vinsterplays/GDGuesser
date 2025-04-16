-- Up

CREATE TABLE scores (
    account_id INT NOT NULL PRIMARY KEY,
    username TEXT NOT NULL,
    total_score INT NOT NULL,
    icon_id INT NOT NULL
);

-- Down

DROP TABLE scores;
