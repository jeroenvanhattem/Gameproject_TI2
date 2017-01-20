BEGIN TRANSACTION;
CREATE TABLE `standard_dialogue` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`faction_id`	INTEGER NOT NULL,
	`text`	TEXT NOT NULL
);
CREATE TABLE "sprites" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`path`	TEXT NOT NULL,
	`name`	TEXT NOT NULL,
	`size`	INTEGER NOT NULL DEFAULT 64
);
CREATE TABLE "quest_stories" (
	`quest_id`	INT NOT NULL,
	`part`	INT NOT NULL,
	`speaker`	INT NOT NULL,
	`text`	TEXT NOT NULL DEFAULT 'Test',
	PRIMARY KEY(`quest_id`,`part`),
	FOREIGN KEY(`quest_id`) REFERENCES `quest`(`id`),
	FOREIGN KEY(`part`) REFERENCES `quest`(`part`)
);
CREATE TABLE "quest" (
	`id`	INT NOT NULL,
	`status`	INT NOT NULL DEFAULT 0,
	`parts`	INT NOT NULL,
	`reward`	INTEGER NOT NULL DEFAULT 0,
	PRIMARY KEY(`id`)
);
CREATE TABLE "player" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`map`	INTEGER NOT NULL,
	`level`	INTEGER NOT NULL,
	`position_x`	INTEGER NOT NULL,
	`position_y`	INTEGER NOT NULL,
	`faction_id`	INTEGER NOT NULL DEFAULT 0,
	FOREIGN KEY(`faction_id`) REFERENCES `faction`(`id`)
);
CREATE TABLE "objects" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL,
	`default_object_id`	INTEGER NOT NULL,
	`position_x`	INTEGER NOT NULL,
	`position_y`	INTEGER NOT NULL,
	`map`	INTEGER NOT NULL,
	FOREIGN KEY(`default_object_id`) REFERENCES `default_objects`(`id`)
);
CREATE TABLE `music` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`path_to_file`	INTEGER NOT NULL
);
CREATE TABLE "maps" (
	`id`	INTEGER NOT NULL,
	`name`	TEXT NOT NULL,
	`music_id`	INTEGER NOT NULL DEFAULT 0,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`music_id`) REFERENCES `music`(`id`)
);
CREATE TABLE "item" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`name`	TEXT NOT NULL,
	`heal_point`	INTEGER NOT NULL DEFAULT 0,
	`armor`	INTEGER NOT NULL DEFAULT 0,
	`strength`	INTEGER NOT NULL DEFAULT 0,
	`max_health`	INTEGER NOT NULL DEFAULT 0
);
CREATE TABLE "inventory" (
	`item_id`	INTEGER NOT NULL,
	`amount`	INTEGER NOT NULL,
	`owner_id`	INTEGER NOT NULL DEFAULT 0,
	`active`	INTEGER NOT NULL DEFAULT 0,
	PRIMARY KEY(`item_id`,`owner_id`),
	FOREIGN KEY(`item_id`) REFERENCES `item`(`id`),
	FOREIGN KEY(`owner_id`) REFERENCES `NPC`(`id`)
);
CREATE TABLE "factions" (
	`id`	INTEGER NOT NULL,
	`name`	VARCHAR(45) NOT NULL,
	`health`	INT NOT NULL DEFAULT 1,
	`armor`	INT NOT NULL DEFAULT 1,
	`strength`	INTEGER NOT NULL DEFAULT 1,
	PRIMARY KEY(`id`)
);
CREATE TABLE `default_objects` (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`sprite_id`	INTEGER NOT NULL,
	`name`	TEXT NOT NULL,
	`size`	INTEGER NOT NULL DEFAULT 32,
	`walkable`	INTEGER NOT NULL,
	FOREIGN KEY(`sprite_id`) REFERENCES `sprites`(`id`)
);
CREATE TABLE `background` (
	`id`	INTEGER NOT NULL,
	`name`	TEXT NOT NULL,
	`sprite_id`	INTEGER NOT NULL,
	`position_x`	INTEGER NOT NULL,
	`position_y`	INTEGER NOT NULL,
	`size`	INTEGER NOT NULL DEFAULT 32,
	`map_id`	INTEGER NOT NULL,
	PRIMARY KEY(`id`),
	FOREIGN KEY(`map_id`) REFERENCES `maps`(`id`)
);
CREATE TABLE "NPC" (
	`id`	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,
	`naam`	VARCHAR(45) NOT NULL,
	`level`	INT NOT NULL,
	`class_id`	INTEGER NOT NULL,
	`sprite_id`	INTEGER NOT NULL,
	`position_x`	INTEGER NOT NULL,
	`position_y`	INTEGER NOT NULL,
	`quest_id`	INTEGER NOT NULL DEFAULT 0,
	FOREIGN KEY(`class_id`) REFERENCES `factions`(`id`),
	FOREIGN KEY(`sprite_id`) REFERENCES `sprites`(`id`)
);
COMMIT;
