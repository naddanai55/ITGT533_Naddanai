#pragma once

#include <iostream>
#include "Enemy.hpp" 
#include "Map.hpp"   
#include "nlohmann/json.hpp" 

using namespace std;

namespace NP
{
    class GameEngine 
    {
    public:
        GameEngine();
        bool init(const string& gameSettingsFile, const string& enemyLevelDataFile, const string& mapLayoutFile);
        void run();
        void release();

    private:
        void handleInput();
        void update();
        void render() const;

        void startNewLevel();
        void resetCurrentLevelAttempt();
        void renderLevelSelection() const;
        void displayAvailableNumbers() const;
        void displayAvailableOperators() const;
        void clearScreen() const;
        int getValidIntInput(int minVal, int maxVal, const string& prompt) const;
        char getCharInput(const string& prompt) const;

        // Game Settings
        string gameTitle_;
        string welcomeMessage_;
        string levelSelectInstructions_;
        string quitMessage_;

        // Game Data
        vector<Enemy> allEnemies;
        vector<vector<int>> allLevelNumbers;
        map<string, string> enemyArts;
        vector<bool> levelsCompleted_;

        const vector<char> OPERATORS = { '+', '-', '*', '/' };

        // Map
        Map levelSelectionMap;
        char playerMapInput;

        // Current Gameplay State
        int currentLevelIndex;
        Enemy currentEnemy;
        vector<int> currentAvailableNumbers;
        double currentCalculation;
        char chosenOperator;

        // Boolean Flags
        bool isGameActive;
        bool needsFirstNumber;
        bool needsOperator;
        bool needsSecondNumber;
        bool levelWon;
        bool levelLostAttempt;
        bool awaitingRetryConfirmation;

        bool gameShouldClose;
        bool inLevelSelectionMode;
        int playerInputChoice;
    };
}