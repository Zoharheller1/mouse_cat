#pragma once

#include <fstream>
#include "Player.h"
#include "Board.h"
#include "enemy.h"
#include  "Location.h"
#include "BfsCellData.h"

class Controller
{
public:

	Controller();

	void run();
    int handleSpecialKey(std::vector<Location> enemey);
	int handleSpecialKy(std::vector<Location> enemey);
	bool is_Coliision();
	
	bool isEnemeyMovement(const int move);
	void print() const;
	void noEnptySpace(char , bool ,std::vector<Location> );

private:

	void resetLevel(Location start_place_of_player, std::vector<Location>enemys);
	void BFS();
	void initCellData();

	Player m_player;

	std::vector<std::vector<BfsCellData>> m_bfsCellData; // might need rename to m_bfs_cell_data

	Board mBoardC;

	std::vector<Enemy> m_enemies; //rename to m_enemies and PLEASE NOT 'enemys'
};
