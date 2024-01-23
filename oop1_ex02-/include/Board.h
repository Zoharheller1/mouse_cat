#pragma once
#include<vector>
#include<string>
#include"Location.h"

class Controller;

class Board
{
public:

	Board(const std::string& levelname);

	std::vector<std::string>	getBoard()const ;

    Location getPlacePlayer(std::vector<Location> &enemys);
	
	unsigned int getCounterChesee() const ;

	unsigned int getCounterKeys() const;

	
	
	void readLevel(const std::string& levelname);

	bool isValidCell(const Location& new_potential_player_place,
		char& current_place,
		bool& kill_enemy);

	bool isValideEnemeyPlace(const Location& new_potential_player_place);


	bool isValidLevel(std::ifstream& current_level, const std::string& levelname);

private:

	std::vector<std::string> mBoard;

	unsigned int mCounterCheese;

	unsigned int mCounterKeys;
};