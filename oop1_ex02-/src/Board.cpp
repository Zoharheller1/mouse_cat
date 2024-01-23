#include "Board.h"
#include "io.h"
#include "Location.h"
#include "Player.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <string>
#include <vector>
#include <windows.h>

Board::Board( const std::string& levelname)
{
    readLevel(levelname);
}
void Board::readLevel(const std::string& levelname)
{
    mBoard.clear();
    mCounterCheese = 0;
    mCounterKeys = 0;

    std::ifstream current_level;

    if (isValidLevel(current_level, levelname))
    {
        for (auto line = std::string(); std::getline(current_level, line);) mBoard.push_back(line);
    }
    else exit(0);
          
   
}

bool Board:: isValidLevel(std::ifstream &current_level,const std::string& levelname)
{
    if (current_level = std::ifstream(levelname))
    {
        return true;
    }
    std::system("cls");
    std::cout << "Outstanding, you beat the cats \n you won";
    Sleep(5000);

    return false;
}


std::vector<std::string> Board::getBoard() const
{
  return mBoard  ;
}

Location Board::getPlacePlayer(std::vector<Location> &enemys)
{
    Location place_player,
              place_enemy;

    
    place_player.col = 0;
    place_player.row = 0;

    auto mouse = '%',
        chesee = '*',
        enemy = '^';
    
    

    int row = 0;
   
        for (const std::string& line : mBoard)
      {

        for ( int place_in_line = 0;
            place_in_line < mBoard[row].size();
            place_in_line++)
        {

            if (mouse == mBoard[row][place_in_line])
            {
                place_player.col = place_in_line;
                place_player.row = row;
                mBoard[row][place_in_line] = ' ';
              

            }
            if (chesee == mBoard[row][place_in_line])
            {
                mCounterCheese++;
            }

            if (enemy == mBoard[row][place_in_line])
            {
                mBoard[row][place_in_line] = ' ';
                place_enemy.row = row;
                place_enemy.col = place_in_line;
                enemys.push_back(place_enemy);
                
            }
        }
        
        row++;
    }

        return place_player;
}

unsigned int Board::  getCounterChesee() const
{
    return mCounterCheese;
}

unsigned int Board:: getCounterKeys() const
{
    return mCounterKeys;
}

bool Board::isValideEnemeyPlace(const Location& new_potential_player_place)
{
    return (mBoard[new_potential_player_place.row][new_potential_player_place.col] != '#');
  
}
bool Board::isValidCell(const Location& new_potential_player_place,char& current_place,
                                   bool&  kill_enemy)
{
    
    switch (mBoard[new_potential_player_place.row][new_potential_player_place.col])
    {
    case'#':

        return false;

    case'*':
        mBoard[new_potential_player_place.row][new_potential_player_place.col] = ' ';
        current_place = '*';
        mCounterCheese--;
        return true;

    case'F':
        mBoard[new_potential_player_place.row][new_potential_player_place.col] = ' ';
        current_place = 'F';
        mCounterKeys++;
        return true;

    case'D':

        if (mCounterKeys > 0)
        {
            mBoard[new_potential_player_place.row][new_potential_player_place.col] = ' ';
            current_place = 'D';
            mCounterKeys--;
            return true;
        }
        return false;

    case'$':
        mBoard[new_potential_player_place.row][new_potential_player_place.col] = ' ';
        current_place = '$';
        kill_enemy = true;
        return true;

    default:
        return true;
    };
}





















