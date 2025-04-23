-- Up

ALTER TABLE scores ADD COLUMN max_score INT;
ALTER TABLE scores ADD COLUMN total_normal_guesses INT;
ALTER TABLE scores ADD COLUMN total_hardcore_guesses INT;

-- Down

ALTER TABLE scores DROP COLUMN max_score;
ALTER TABLE scores DROP COLUMN total_normal_guesses;
ALTER TABLE scores DROP COLUMN total_hardcore_guesses;
