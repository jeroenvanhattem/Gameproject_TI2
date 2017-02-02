BEGIN TRANSACTION;
CREATE TABLE `music` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`path_to_file`	INTEGER NOT NULL
);
INSERT INTO `music` VALUES (1,'../../bin/music/x_gon_give_it_to_ya.wav');
COMMIT;
