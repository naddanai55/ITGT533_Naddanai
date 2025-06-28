#include "GameEngine.hpp"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

namespace NP 
{
    GameEngine::GameEngine() : 
        gameTitle_("Math Game"),
        welcomeMessage_("Welcome!"),
        levelSelectInstructions_("Controls: ..."),
        quitMessage_("Goodbye!"),
        currentLevelIndex(-1),
        currentCalculation(0.0),
        chosenOperator(' '),
        isGameActive(false),
        needsFirstNumber(true),
        needsOperator(false),
        needsSecondNumber(false),
        levelWon(false),
        levelLostAttempt(false),
        awaitingRetryConfirmation(false),
        gameShouldClose(false),
        inLevelSelectionMode(true),
        playerMapInput(' '),
        playerInputChoice(-1)
    {}

    bool GameEngine::init(const std::string& gameSettingsFile, const std::string& enemyLevelDataFile, const std::string& mapLayoutFile) 
    {
        ifstream ifs_settings(gameSettingsFile);
        json settings_data_json;
        ifs_settings >> settings_data_json;

        ifstream ifs_levels(enemyLevelDataFile);
        json levels_data_json;
        ifs_levels >> levels_data_json;

        ifstream ifs_map(mapLayoutFile);
        json map_data_json;
        ifs_map >> map_data_json;

        gameTitle_ = settings_data_json.value("game_title", "Math Quest");
        welcomeMessage_ = settings_data_json.value("welcome_message", "Welcome!");
        levelSelectInstructions_ = settings_data_json.value("level_select_instructions", "W,A,S,D to move, E to select, Q to quit.");
        quitMessage_ = settings_data_json.value("quit_message", "Thanks for playing!");
        ifs_settings.close();
        allEnemies.clear();
        allLevelNumbers.clear();
        enemyArts.clear();
        levelsCompleted_.clear();

        if (levels_data_json.contains("enemy_arts") && levels_data_json["enemy_arts"].is_object()) 
        {
            for (json::iterator it = levels_data_json["enemy_arts"].begin(); it != levels_data_json["enemy_arts"].end(); ++it) 
            {
                if (it.value().is_string()) enemyArts[it.key()] = it.value().get<string>();
            }
        }

        if (levels_data_json.contains("levels") && levels_data_json["levels"].is_array()) 
        {
            for (const auto& level_item_json : levels_data_json["levels"]) 
            {
                string art_key_idle = level_item_json.value("art_key_idle", "");
                string art_key_died = level_item_json.value("art_key_died", "");

                std::string idle_art_str = enemyArts.count(art_key_idle) ? enemyArts[art_key_idle] : "IDLE_ART_MISSING";
                std::string died_art_str = enemyArts.count(art_key_died) ? enemyArts[art_key_died] : "DIED_ART_MISSING";

                allEnemies.emplace_back(level_item_json.value("target", 0), idle_art_str, died_art_str);
                allLevelNumbers.push_back(level_item_json.value("numbers", vector<int>{1, 1, 1}));
            }
        }
        levelsCompleted_.assign(allEnemies.size(), false);
        levelSelectionMap.loadMap(map_data_json);

        ifs_map.close();

        inLevelSelectionMode = true;
        isGameActive = false;

        cout << "--- " << gameTitle_ << " ---" << endl;
        cout << welcomeMessage_ << endl;
        cout << "Initialization Complete. " << allEnemies.size() << " levels available." << endl;
        return true;
    }

    void GameEngine::run() 
    {
        if (gameShouldClose) 
        {
            if (!allEnemies.empty() || levelSelectionMap.getTitle() != "Default Map")
            {
                release();
                return;
            }
        }
        while (!gameShouldClose) 
        {
            render();
            handleInput();
            update();
        }
        if (!allEnemies.empty() || levelSelectionMap.getTitle() != "Default Map") 
        {
            release();
        }
    }

    void GameEngine::render() const 
    {
        clearScreen();
        if (inLevelSelectionMode) 
        {
            renderLevelSelection();
        }
        else if (isGameActive) 
        {
            currentEnemy.showArt(false, cout);
            currentEnemy.showPower(cout);
            cout << "------------------------------------" << endl;
            cout << "To defeat the enemy, you need to have equal power! " << endl;
            cout << "Current Calculation: " << fixed << setprecision(2) << currentCalculation << endl;

            if (needsFirstNumber || needsSecondNumber)
            {
                displayAvailableNumbers();
            }

            if (needsOperator) 
            {
                displayAvailableOperators();
            } 
            cout << "------------------------------------" << endl;

        }
        else if (levelWon && !awaitingRetryConfirmation && !gameShouldClose) 
        {
            cout << "Level " << currentLevelIndex + 1 << " CLEARED! Target " << currentEnemy.getTargetPower() << " reached." << endl;
            cout << "--- Enemy Defeated! ---" << endl;
            if (static_cast<size_t>(currentLevelIndex) < allEnemies.size()) {
                currentEnemy.showArt(true, cout);
            }
            cout << "Press 'Y' to return to map, or 'Q' to quit game: ";

        }
        else if (awaitingRetryConfirmation) {
            cout << "--- Level " << currentLevelIndex + 1 << " Attempt Failed ---" << endl;
            if (static_cast<size_t>(currentLevelIndex) < allEnemies.size()) currentEnemy.showPower(cout);
            cout << "Your final calculation: " << fixed << setprecision(2) << currentCalculation << endl;
            cout << "------------------------------------" << endl;
        }
        else if (gameShouldClose) 
        {
            bool allDone = true;
            for (bool c : levelsCompleted_) if (!c) allDone = false;
            if (allDone && !allEnemies.empty() && static_cast<size_t>(currentLevelIndex) >= allEnemies.size() - 1 && levelsCompleted_.back()) {
                cout << "CONGRATULATIONS! All levels cleared in " << gameTitle_ << "!" << endl;
            }
        }
    }

    void GameEngine::renderLevelSelection() const 
    {
        cout << "--- " << levelSelectionMap.getTitle() << " ---" << endl;
        cout << endl;
        cout << welcomeMessage_ << endl;
        cout << endl;
        cout << levelSelectInstructions_ << endl;
        cout << "-----------------------" << endl;
        levelSelectionMap.render();
        cout << "-----------------------" << endl;
    }

    void GameEngine::handleInput() 
    {
        playerInputChoice = -1;
        playerMapInput = ' ';

        if (inLevelSelectionMode) {
            playerMapInput = getCharInput("");
        }
        else if (isGameActive) {
            if (awaitingRetryConfirmation) {
                char c = getCharInput("Try this level again? (y/n): ");
                playerInputChoice = (tolower(c) == 'y') ? 1 : 0;
            }
            else if (needsFirstNumber) {
                if (currentAvailableNumbers.empty()) { levelLostAttempt = true; return; }
                playerInputChoice = getValidIntInput(0, currentAvailableNumbers.size(), "FIRST#(0=R): ");
            }
            else if (needsOperator) {
                playerInputChoice = getValidIntInput(0, OPERATORS.size(), "OP#(0=R): ");
            }
            else if (needsSecondNumber) {
                if (currentAvailableNumbers.empty()) { levelLostAttempt = true; return; }
                playerInputChoice = getValidIntInput(0, currentAvailableNumbers.size(), "SECOND#(0=R): ");
            }
        }
        else if (levelWon && !gameShouldClose && !awaitingRetryConfirmation) {
            char confirmChoice = getCharInput("");
            if (tolower(confirmChoice) == 'y') playerInputChoice = 1;
            else if (tolower(confirmChoice) == 'q') playerInputChoice = 0;
            else playerInputChoice = -1;
        }
    }

    void GameEngine::update() 
    {
        if (gameShouldClose) return;

        if (inLevelSelectionMode) {
            char inputLower = tolower(playerMapInput);
            if (inputLower == 'e') {
                char tile = levelSelectionMap.getTileAtPlayerPos();
                int levelNum = tile - '0';
                if (levelNum >= 1 && static_cast<size_t>(levelNum) <= allEnemies.size()) {
                    int selectedIdx = levelNum - 1;
                    if (static_cast<size_t>(selectedIdx) < levelsCompleted_.size() && levelsCompleted_[selectedIdx]) {
                        cout << "Level " << levelNum << " has already been completed!" << endl;
                    }
                    else {
                        currentLevelIndex = selectedIdx;
                        startNewLevel();
                    }
                }
                else { cout << "Not a valid level spot. Move 'P' to a number." << endl; }
            }
            else if (inputLower == 'q') {
                cout << "Quitting game..." << endl; gameShouldClose = true;
            }
            else if (string("wasd").find(inputLower) != string::npos) {
                levelSelectionMap.movePlayer(inputLower);
            }
        }
        else if (isGameActive) {
            if (awaitingRetryConfirmation) {
                if (playerInputChoice == 1) {
                    startNewLevel();
                }
                else {
                    cout << "You chose not to retry." << endl;
                    isGameActive = false;
                    inLevelSelectionMode = true;
                }
                awaitingRetryConfirmation = false;
                playerInputChoice = -1;
                return;
            }

            if (levelLostAttempt) {
                awaitingRetryConfirmation = true;
                levelLostAttempt = false;
                return;
            }

            if (playerInputChoice == 0) { resetCurrentLevelAttempt(); playerInputChoice = -1; return; }

            bool calculationDoneThisTurn = false;
            if (playerInputChoice > 0) {
                if (needsFirstNumber) {
                    if (static_cast<size_t>(playerInputChoice - 1) < currentAvailableNumbers.size()) {
                        currentCalculation = currentAvailableNumbers[playerInputChoice - 1];
                        currentAvailableNumbers.erase(currentAvailableNumbers.begin() + (playerInputChoice - 1));
                        needsFirstNumber = false; needsOperator = true;
                    }
                }
                else if (needsOperator) {
                    if (static_cast<size_t>(playerInputChoice - 1) < OPERATORS.size()) {
                        chosenOperator = OPERATORS[playerInputChoice - 1];
                        needsOperator = false; needsSecondNumber = true;
                        if (currentAvailableNumbers.empty()) { levelLostAttempt = true; }
                    }
                }
                else if (needsSecondNumber) {
                    if (levelLostAttempt) { playerInputChoice = -1; return; }
                    if (static_cast<size_t>(playerInputChoice - 1) < currentAvailableNumbers.size()) {
                        int secondNum = currentAvailableNumbers[playerInputChoice - 1];
                        currentAvailableNumbers.erase(currentAvailableNumbers.begin() + (playerInputChoice - 1));
                        switch (chosenOperator) {
                        case '+': currentCalculation += secondNum; break;
                        case '-': currentCalculation -= secondNum; break;
                        case '*': currentCalculation *= secondNum; break;
                        case '/':
                            if (secondNum == 0) { cout << "Div by zero!" << endl; levelLostAttempt = true; }
                            else currentCalculation /= secondNum;
                            break;
                        }
                        needsSecondNumber = false;
                        calculationDoneThisTurn = true;
                    }
                }
            }
            // Consume input only if it was processed by the math logic stages
            if (playerInputChoice > 0 && (needsFirstNumber == false || needsOperator == false || needsSecondNumber == false)) {
                playerInputChoice = -1;
            }


            if (calculationDoneThisTurn || levelLostAttempt) { // Re-evaluate win/loss
                if (!levelLostAttempt) {
                    if (static_cast<int>(round(currentCalculation)) == currentEnemy.getTargetPower()) {
                        levelWon = true;
                        isGameActive = false;
                    }
                    else if (currentAvailableNumbers.empty()) {
                        levelLostAttempt = true;
                    }
                    else {
                        needsOperator = true;
                    }
                }
            }

            if (levelLostAttempt && !awaitingRetryConfirmation && !levelWon) {
                awaitingRetryConfirmation = true;
            }

        }
        else if (levelWon && !gameShouldClose && !awaitingRetryConfirmation) {
            if (playerInputChoice == 1) { // Pressed 'Y'
                if (static_cast<size_t>(currentLevelIndex) < levelsCompleted_.size()) {
                    levelsCompleted_[currentLevelIndex] = true;
                    char levelChar = static_cast<char>((currentLevelIndex + 1) + '0');
                    levelSelectionMap.markCompleted(levelChar, '.');
                }
                bool allDone = true;
                for (bool c : levelsCompleted_) if (!c) allDone = false;
                if (allDone) {
                    cout << "CONGRATULATIONS! All levels cleared!" << endl;
                    gameShouldClose = true;
                }
                else {
                    inLevelSelectionMode = true;
                }
                levelWon = false;
            }
            else if (playerInputChoice == 0) 
            {
                gameShouldClose = true;
                cout << "Quitting after level win." << endl;
            }
          
            if (playerInputChoice == 1 || playerInputChoice == 0) playerInputChoice = -1;
        }
    }

    void GameEngine::startNewLevel() {
        if (currentLevelIndex < 0 || static_cast<size_t>(currentLevelIndex) >= allEnemies.size()) {
            if (static_cast<size_t>(currentLevelIndex) >= allEnemies.size() && !allEnemies.empty()) {
            }
            else {
                cerr << "Error: Invalid level index " << currentLevelIndex << " for startNewLevel." << endl;
            }
            gameShouldClose = true; isGameActive = false; inLevelSelectionMode = false;
            return;
        }
        currentEnemy = allEnemies[currentLevelIndex];
        cout << "Starting Level " << currentLevelIndex + 1 << endl;
        resetCurrentLevelAttempt();
        isGameActive = true;
        inLevelSelectionMode = false;
        levelWon = false;
        levelLostAttempt = false;
        awaitingRetryConfirmation = false;
    }

    void GameEngine::resetCurrentLevelAttempt() {
        if (currentLevelIndex < 0 || static_cast<size_t>(currentLevelIndex) >= allLevelNumbers.size()) {
            gameShouldClose = true; isGameActive = false; inLevelSelectionMode = true;
            return;
        }
        currentAvailableNumbers = allLevelNumbers[currentLevelIndex];
        currentCalculation = 0.0;
        chosenOperator = ' ';
        needsFirstNumber = true;
        needsOperator = false;
        needsSecondNumber = false;
        levelWon = false;
        levelLostAttempt = false;
    }

    void GameEngine::release() {
        allEnemies.clear();
        allLevelNumbers.clear();
        currentAvailableNumbers.clear();
        enemyArts.clear();
        levelsCompleted_.clear();
        cout << endl;
        cout  << quitMessage_ << endl;
    }

    void GameEngine::displayAvailableNumbers() const {
        if (currentAvailableNumbers.empty()) { cout << "No numbers left!" << endl; return; }
        cout << "You and your comrades: "; for (size_t i = 0; i < currentAvailableNumbers.size(); ++i) cout << "[" << i + 1 << "]:" << currentAvailableNumbers[i] << " "; cout << endl;
    }
    void GameEngine::displayAvailableOperators() const {
        cout << "Ops: "; for (size_t i = 0; i < OPERATORS.size(); ++i) cout << "[" << i + 1 << "]:" << OPERATORS[i] << " "; cout << endl;
    }
    void GameEngine::clearScreen() const {
#if defined(_WIN32) || defined(_WIN64)
        system("cls");
#else
        system("clear");
#endif
    }
    int GameEngine::getValidIntInput(int minVal, int maxVal, const std::string& promptText) const {
        int val;
        while (true) {
            cout << promptText;
            cin >> val;
            if (cin.good() && val >= minVal && val <= maxVal) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return val;
            }
            else {
                cout << "Invalid (" << minVal << "-" << maxVal << ")." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
    char GameEngine::getCharInput(const std::string& promptText) const {
        char c;
        if (!promptText.empty()) cout << promptText;
        cin >> c;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return c;
    }
}