#include "Controller.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Location.h"
#include "io.h"
#include <conio.h>
#include <queue>
#include <cstdlib>
#include <vector>


Controller::Controller() :  m_player(0, 0) ,mBoardC("level1.txt") {
    initCellData();
}


/*
    initCellData ()

    reset()

*/
void Controller::run()
{
    int level = 1;
 
    while (true)
    {
        std::vector<Location> enemys; // enemies starting positions.

        m_player = mBoardC.getPlacePlayer(enemys);

        Location start_place_of_player = m_player.getPosition();

        for (int row = 0; row < enemys.size(); row++) m_enemies.push_back(enemys[row]);

        int move = 0;
        while (((mBoardC.getCounterChesee()) != 0))

        {
            print();

            std::cout << "points:" << m_player.getPoint() <<
                " life:" << m_player.getLife() <<
                " keys:" << mBoardC.getCounterKeys() << '\n';


            handleSpecialKey(enemys);

            if (is_Coliision())
            {
                resetLevel(start_place_of_player, enemys);
            }

            std::system("cls");
             
            if (!isEnemeyMovement(move))
            {
                resetLevel(start_place_of_player, enemys);
            }

            move++;

            if (m_player.isDead())
            {
                exit(0); // handle death 
            }
        }
        enemys.clear();
        level ++;
        auto levelname = "level" + std::to_string(level) + ".txt";

        mBoardC.readLevel(levelname);
        initCellData();

    }

    exit(0);
   

}
void  Controller::resetLevel(Location start_place_of_player, std::vector<Location>enemys)
{
    m_player.setPosition(start_place_of_player);
    m_enemies.clear();
    
    for (int row = 0; row < enemys.size(); row++) m_enemies.push_back(enemys[row]);
    m_player.decriseLife();
}

void Controller::BFS()
{
    std::queue<BfsCellData> q;
    std::vector<std::vector<bool>> visited(m_bfsCellData.size(), std::vector<bool>(m_bfsCellData[0].size(), false));
    Location player_pos = m_player.getPosition();

    q.push(m_bfsCellData[player_pos.row][player_pos.col]);
    visited[player_pos.row][player_pos.col] = true;

    while (!q.empty()) 
    {
        auto current = q.front();
        q.pop();

        for (auto n : current._neighbors)
        {
            // if neighbor is not disabled and not visited
            if (!n->_disabled && !visited[n->_index.row][n->_index.col])
            {
                q.push(*n);
                visited[n->_index.row][n->_index.col] = true;
                n->_distance = current._distance + 1; // increase distance
                n->_parent = std::make_shared<BfsCellData>(current); // create pointer to parent
            }
        }
    }
}

void Controller::initCellData() {

    auto board = mBoardC.getBoard();
    m_bfsCellData.clear(); // reset current;

    // init from board data
    for (size_t row = 0; row < board.size(); row++)
    {
        std::vector<BfsCellData> curr_row;
        for (size_t col = 0; col < board[row].size(); col++)
        {
            BfsCellData current;
            current._disabled = board[row][col] == '#' || board[row][col] == 'D';
            current._distance = 0;
            current._index = Location(row, col);
            curr_row.push_back(current);
        }
        m_bfsCellData.push_back(curr_row);
        curr_row.clear();
    }

    for (size_t row = 0; row < board.size(); row++)
    {
        for (size_t col = 0; col < board[row].size(); col++)
        {
            if (row > 0)
            { // if not first row
                m_bfsCellData[row][col]._neighbors.push_back(std::make_shared<BfsCellData>(m_bfsCellData[row - 1][col]));
            }
            if (row + 1 < board.size())
            { // if not last row
                m_bfsCellData[row][col]._neighbors.push_back(std::make_shared<BfsCellData>(m_bfsCellData[row + 1][col]));
            }
            if (col > 0) { // if not first column
                m_bfsCellData[row][col]._neighbors.push_back(std::make_shared<BfsCellData>(m_bfsCellData[row][col - 1]));
            }
            if (col + 1 < board[row].size())
            { // if not last column
                m_bfsCellData[row][col]._neighbors.push_back(std::make_shared<BfsCellData>(m_bfsCellData[row][col + 1]));
            }

        }
    }

}

//void setCellsData() {
    // move accross the board and for each cell we create BfsCellData
    // // disabled == is wall or door
    // 
    // for example
    // obj = { _disabled = false , Location(row,col) , distance = 0 , _parent = null, _neigthboors = all near cells ( row+1,row-1,col-1+col+1 )

    //Bfs
// thePlayerIsKilled() -> checkCollision()

bool Controller::is_Coliision()
{
    for (int enemey = 0; enemey < m_enemies.size(); enemey++)
    {
        Location new_potential_enemy_place = m_enemies[enemey].getPosition();

      if(m_player.isCollision(new_potential_enemy_place)) 
      {
            return true;
      }

    }
    return false;
    
}

// remove move
bool Controller::isEnemeyMovement(const int move)
{
    for (int enemy = 0; enemy < m_enemies.size(); enemy++)
    {
        Location poisition = m_enemies[enemy].getPosition();
        std::shared_ptr<BfsCellData> parent = m_bfsCellData[poisition.row][poisition.col]._parent;
        Location nextCell = parent ? parent->_index : poisition;
        m_enemies[enemy].setPosition(nextCell);
    }
    return true;
}
// handleKey
int Controller::handleSpecialKey(std::vector<Location> enemey)
{
    const auto c = _getch();
   
    switch (c) 
        {
        
        case 0:
        case Keys::SPECIAL_KEY:
            handleSpecialKy(enemey);
            return 1;
       
        default:
            return -1;  
        }
    
}

// handleSpecialKey
int Controller::handleSpecialKy(std::vector<Location> enemey)
{
    const auto c = _getch();

    Location new_potential_place = m_player.getPosition();

    char currect_place= ' ';
    bool kill_enemey = false;

    
    switch (c)
    {
    case SpecialKeys::UP:
        new_potential_place.row--;

        if (mBoardC.isValidCell(new_potential_place, currect_place, kill_enemey))
        {
            noEnptySpace(currect_place, kill_enemey, enemey);
            m_player.move(UP);
            
        }
        break;

    case SpecialKeys::DOWN:

        new_potential_place.row++;

        if (mBoardC.isValidCell(new_potential_place, currect_place, kill_enemey))
        {
            noEnptySpace(currect_place, kill_enemey,enemey);
            m_player.move(DOWN);
        }
        break;
    case SpecialKeys::LEFT:


        new_potential_place.col--;

        if (mBoardC.isValidCell(new_potential_place, currect_place, kill_enemey))
        {
            noEnptySpace(currect_place, kill_enemey, enemey);
            m_player.move(LEFT);
        }

        break;
    case SpecialKeys::RIGHT:


        new_potential_place.col++;

        if (mBoardC.isValidCell(new_potential_place, currect_place, kill_enemey))
        {
            noEnptySpace(currect_place, kill_enemey, enemey);
            m_player.move(RIGHT);
        }
        break;
    };

    BFS();
    return 1; // remove return values
    
}

void Controller::print() const
{
    Location points = m_player.getPosition();

    std::vector<std::string> current_board =  mBoardC.getBoard();

    for (int row = 0; row < m_enemies.size(); row++)
    {
        current_board[m_enemies[row].getPosition().row]
            [m_enemies[row].getPosition().col] = '^';
    }

    current_board[points.row][points.col] = '%';
    
    
    for (const std::string& line : current_board)
    {
        std::cout << line << '\n';
    }
       
}



void Controller::noEnptySpace(char currect_place, bool kill_enemy,
                                         std::vector<Location> enemey)
{
    if (currect_place != ' ')
    {
        if (kill_enemy)
        {
            m_enemies.pop_back();
            enemey.pop_back();
        }
        m_player.updatePoints(currect_place);
    }
    
}

