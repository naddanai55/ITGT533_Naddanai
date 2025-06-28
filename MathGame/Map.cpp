#include "Map.hpp"

using namespace std;

namespace NP 
{
    Map::Map() : playerX(1), playerY(1), title("Default Map") {} 

    bool Map::loadMap(const nlohmann::json& mapJson) 
    {

        title = mapJson.value("map_title", "Level Selection Map");
        if (mapJson.contains("layout") && mapJson["layout"].is_array()) 
        {
            layout = mapJson["layout"].get<vector<string>>();
        }

        determinePlayerStartPosition(mapJson);
        return true;
    }

    bool Map::isValidPosition(int x, int y) const 
    {
        if (y < 0 || static_cast<size_t>(y) >= layout.size())
        {
            return false;
        }
        if (x < 0 || static_cast<size_t>(x) >= layout[y].size())
        {
            return false;
        }

        return layout[y][x] != '#';
    }

    void Map::determinePlayerStartPosition(const nlohmann::json& mapJson) 
    {
        bool positionSet = false;

        if (mapJson.contains("start_player_x") && mapJson["start_player_x"].is_number() && mapJson.contains("start_player_y") && mapJson["start_player_y"].is_number()) 
        {
            int startX = mapJson["start_player_x"].get<int>();
            int startY = mapJson["start_player_y"].get<int>();
            if (isValidPosition(startX, startY)) 
            {
                playerX = startX;
                playerY = startY;
                positionSet = true;
            }
        }
    }

    void Map::render(std::ostream& os) const 
    {
        for (size_t y = 0; y < layout.size(); y++) 
        {
            for (size_t x = 0; x < layout[y].size(); x++) 
            {
                if (static_cast<int>(y) == playerY && static_cast<int>(x) == playerX) 
                {
                    os << 'P';
                }
                else 
                {
                    os << layout[y][x];
                }
            }
            os << endl;
        }
    }

    bool Map::movePlayer(char direction) 
    {
        int newX = playerX;
        int newY = playerY;
        switch (tolower(direction)) 
        {
            case 'w': 
                newY--; 
                break;
            case 's': 
                newY++; 
                break;
            case 'a': 
                newX--; 
                break;
            case 'd': 
                newX++; 
                break;
            default: return false;
        }
        if (isValidPosition(newX, newY)) 
        {
            playerX = newX;
            playerY = newY;
            return true;
        }
        return false;
    }

    char Map::getTileAtPlayerPos() const 
    {
        if (playerY >= 0 && static_cast<size_t>(playerY) < layout.size() && playerX >= 0 && static_cast<size_t>(playerX) < layout[playerY].size()) 
        {
            return layout[playerY][playerX];
        }
        return '#';
    }

    char Map::getTileAt(int x, int y) const 
    {
        if (y >= 0 && static_cast<size_t>(y) < layout.size() && x >= 0 && static_cast<size_t>(x) < layout[y].size()) 
        {
            return layout[y][x];
        }
        return '#';
    }

    string Map::getTitle() const 
    {
        return title;
    }

    void Map::markCompleted(char level, char completed) 
    {
        for (size_t y = 0; y < layout.size(); y++) 
        {
            for (size_t x = 0; x < layout[y].size(); x++) 
            {
                if (layout[y][x] == level) 
                {
                    layout[y][x] = completed;
                }
            }
        }
    }
}