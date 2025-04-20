-- Up

ALTER TABLE scores ADD color1 INT;
ALTER TABLE scores ADD color2 INT;
ALTER TABLE scores ADD color3 INT;

-- Down

ALTER TABLE scores DROP color1 INT;
ALTER TABLE scores DROP color2 INT;
ALTER TABLE scores DROP color3 INT;
