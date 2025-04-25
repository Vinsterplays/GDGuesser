#pragma once

enum class DateFormat {
    Normal,
    American,
    Backwards
};

enum class GameMode {
    Normal,
    Hardcore,
    Extreme
};

enum class TaskStatus {
    None,
    Authenticate,
    Start,
    GetLevel,
    GetScore,
    GetLeaderboard,
    SubmitGuess,
    EndGame
};