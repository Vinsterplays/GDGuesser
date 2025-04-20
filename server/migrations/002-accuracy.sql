-- Up

ALTER TABLE scores ADD accuracy INT;

-- Down

ALTER TABLE scores DROP COLUMN accuracy;
