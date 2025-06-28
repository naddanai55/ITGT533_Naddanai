#pragma once
#include <iostream>
#include "nlohmann/json.hpp"

using namespace std;

namespace NP 
{
    class Map 
    {
    public:
        Map();
        bool loadMap(const nlohmann::json& mapJson);
        void render(ostream& os = cout) const;
        bool movePlayer(char direction);
        char getTileAtPlayerPos() const;
        char getTileAt(int x, int y) const;
        string getTitle() const;
        void markCompleted(char level, char completed = '.');

    private:
        string title;
        vector<string> layout;
        int playerX;
        int playerY;

        void determinePlayerStartPosition(const nlohmann::json& mapJson);
        bool isValidPosition(int x, int y) const;
    };
}