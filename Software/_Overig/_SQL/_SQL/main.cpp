#include <iostream>
#include "_SQLite/sqlite3.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
	int i;
	for (i = 0; i<argc; i++) {
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int main( int argc, char* argv[]) {


	int _ENDING;
	int rc;
	int connection;
	std::cout << "Checking CMD" << std::endl;

	sqlite3 *database;
	char *_ERROR_MESSAGE = 0;

	connection = sqlite3_open("database.db", &database);

	if (connection) {
		std::cout << "Can't open the given database" << std::endl;
		return 0;
	}

	else {
		std::cout << "Congratulations, you opened the given database!" << std::endl;
	}

	char *sql = "DROP TABLE IF EXISTS `NPC`;"\
		"CREATE TABLE IF NOT EXISTS `NPC` ("\
		"`id` INT NOT NULL,"\
		"`naam` VARCHAR(45) NOT NULL,"\
		"`level` INT NOT NULL,"\
		"`class` VARCHAR(45) NULL,"\
		"PRIMARY KEY(`id`))"\
		";"\
		"DROP TABLE IF EXISTS `NPC_properties`;"\
		"CREATE TABLE IF NOT EXISTS `NPC_properties` ("\
		"`id` INT NOT NULL,"\
		"`naam` VARCHAR(45) NOT NULL,"\
		"`health` INT NOT NULL DEFAULT 1,"\
		"`armor` INT NOT NULL DEFAULT 1,"\
		"PRIMARY KEY(`id`))"\
		";"\
		"DROP TABLE IF EXISTS `quest`;"\
		"CREATE TABLE IF NOT EXISTS `quest` ("\
		"`id` INT NOT NULL,"\
		"`triggered` INT NOT NULL DEFAULT 0,"\
		"`active` INT NOT NULL DEFAULT 0,"\
		"`parts` INT NOT NULL,"\
		"PRIMARY KEY(`id`))"\
		";"\
		"DROP TABLE IF EXISTS `maps`;"\
		"CREATE TABLE IF NOT EXISTS `maps` ("\
		"`id` INT NOT NULL,"\
		"`naam` VARCHAR(45) NOT NULL,"\
		"PRIMARY KEY(`id`))"\
		";"\
		"DROP TABLE IF EXISTS `stories`;"\
		"CREATE TABLE IF NOT EXISTS `stories` ("\
		"`quest_id` INT NOT NULL,"\
		"`part` INT NOT NULL,"\
		"`spreaker` INT NOT NULL,"\
		"`text` VARCHAR(300) NOT NULL,"\
		"PRIMARY KEY(`quest_id`, `part`),"\
		"CONSTRAINT `id`"\
		"FOREIGN KEY(`quest_id`)"\
		"REFERENCES `quest` (`id`)"\
		");"
		;

	rc = sqlite3_exec(database, sql, callback , 0, &_ERROR_MESSAGE);

	if (rc != SQLITE_OK) {
		std::cout << "ERROR: " << _ERROR_MESSAGE;
		sqlite3_free(_ERROR_MESSAGE);
	}
	else {
		std::cout << "Records created successfully" << std::endl;
	}

	sqlite3_close(database);

	std::cin >> _ENDING; // This will prefend the program from closing directly after executing.
}
