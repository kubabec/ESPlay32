#ifndef FIGHTGAME_H
#define FIGHTGAME_H

// #define DEVELOPMENT_CODE

#include <app/runtimeApplication.hpp>
#include <app/tools/character2d.hpp>
#include <app/tools/line2d.h>
#include <app/tools/item2d.h>
#include <app/tools/gunshot.h>
#include <vector>

typedef enum {
    GAME_INIT,
    GAME_RUNNING,
    GAME_OVER
}GameState;

class FightGame :public RuntimeApplication {
    bool needsUpdate = true;
    public:

    FightGame();
    virtual void start(int w, int h) override;
    virtual void input(InputType input) override;
    virtual void longPressInput(InputType input) override;
    virtual void longPressRelease(InputType input) override;
    virtual void analogInput(int x, int y) override;
    virtual void touchInput(int x, int y) override;
    virtual void update() override;
    virtual void render(DisplayProvider& display) override;
    virtual void end() override;

    String getAppNameString() override;

    uint16_t getBackgroundColor();
    void udpDataReceived(std::vector<uint8_t> data);

    private:
    Character2D player{150, 100, 7};
    std::vector<Character2D> enemies;
    std::vector<Item2D> items;
    std::vector<GunShot> shots;
    uint8_t speedCounter = 0;
    uint16_t appScreenW;
    uint16_t appScreenH;
    bool needsRepaint = true;
    bool needsCleanScreen = false;
    bool isPlayerMovePending = false;
    Vector2D playerMoveInput{0, 0};
    Vector2D shotDirection{0,0};
    std::vector<Obstacle> obstacleVec;
    int16_t itemActionsTimers[5] = {0};
    bool itemActionsFlags[5] = {0};
    int16_t enemyLastX = 0;
    int16_t enemyLastY = 0;
    uint32_t lastUpdateMS = 0;
    GameState gameState = GAME_INIT;
    bool startScreenDisplayed = false;
    bool gameOverScreenDisplayed = false;
    bool appTextOnOverlayActive = false;

    uint16_t enemySpawnCounter = 300;
    uint16_t itemSpawnCounter = 600;
    int score = 0;
    uint8_t scoreCalculationCounter = 0;
    uint16_t collectedItems = 0;
    uint16_t kills = 0;
    int amo = 30;
    String overlayText = "";

#ifdef DEVELOPMENT_CODE
    //DEVELOPMENT CODE
    bool test_gameFreezeFlag = false;
    Vector2D test_enemyToPlayer;
    //DEVELOPMENT CODE
#endif

    void calculateEnemyPosition();
    void calculatePlayerPosition();
    void calculateCollisions();
    void calculateItemCollisions();
    void foodItemReaction();
    void invisibilityPotionItemReaction();
    void potatoReaction();
    void ghostPotionReaction();
    void holeReaction();
    void collectAmo();
    void updateActionTimers();
    void changeGameState(GameState newState);
    void printGameStartScreen(DisplayProvider& display);
    void printGameOverScreen(DisplayProvider& display);
    void shot();
    void updateOverlayText();
    void calculateShotsCollisions();
    void spawnNewEnemy();
    void checkIfGameOver();
    void gameOver();
    void spawnItem();
};

#endif
