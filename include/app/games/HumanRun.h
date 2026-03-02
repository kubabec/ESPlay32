#ifndef HUMAN_RUN_H
#define HUMAN_RUN_H

#include "app/runtimeApplication.hpp"
enum CustomCharacter {
  STANDING_HUMAN,
  RUNNING_HUMAN,
  JUMPING_HUMAN,
  TOP_PART,
  BOTTOM_PART,
  OBSTACLE1,
  OBSTACLE2
};

enum PlayerState {
  RUNNING1,
  RUNNING2,
  JUMP_START,
  JUMP,
  JUMP_DOWN
};
enum ProgramState {
  SELECTION,
  GAME
};
struct RunObstacle {
  bool isActive = false;
  CustomCharacter type = OBSTACLE1;
  int x = 15;
  int oldX = 15;
};

struct Player {
  PlayerState state = RUNNING1;
  int posX = 2;
  int score = 0;
};

struct Game {
  unsigned long mainTaskTimer = 0;
  int mainTaskDelay = 700;
  bool isGameOver = false;
  int ticksToGenerateNewObst = 4;
  RunObstacle obstacles[5];
  bool stateCompleted = false;
  int ticksToSpeedUp = 5;
  Player player;
  int boardBeginX = 0;
  int boardEndX = 15;
  int buttonPin = 10;
};
enum Mode {
  SINGLE,
  DUEL
};
class HumanRun : public RuntimeApplication
{
public:
    HumanRun();
    ~HumanRun();
    void start(int w, int h);
    void input(InputType input);
    void longPressInput(InputType input);
    void longPressRelease(InputType input);
    void analogInput(int x, int y);
    void touchInput(int x, int y);
    void update();
    void render(DisplayProvider &display);
    void forceRender(DisplayProvider &display);
    void end();
    void udpDataReceived(int messageID, std::vector<uint8_t> data);
    String getAppNameString();
    uint16_t getBackgroundColor();
private:
    Game gameArray[2];
    int gamesOverCount = 0;
    ProgramState programState = SELECTION;
    Mode gameMode = SINGLE;
    int appHeight = 0;
    int appWidth = 0;
    const int obstacleWidth = 30;

    bool isObstOnPlayerX(Game& game) ;
    bool isCollision(Game& game);
    void resetGameOver(Game& game);
    void processObstacleMove(Game& game);
    void processHumanMove(Game& game);
    void initializeGame(Game& game, int begin, int end, int btnPin);
    void processButton(Game& game);
    void processScore(Game& game);
    void generateObstacle(Game& game);
    void processGame(Game& game);
};

#endif // PONG_H
