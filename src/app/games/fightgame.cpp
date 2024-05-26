#include "app/games/fightgame.hpp"
#include "os/portableos.hpp"

FightGame::FightGame(){
     items.push_back({10, 200, FOOD});
//    items.push_back({150, 200, INVISIBILITY_POTION});
//    items.push_back({200, 200, INVISIBILITY_POTION});
//    items.push_back({250, 200, INVISIBILITY_POTION});
    items.push_back({300, 200, AMO_PACK});
    items.push_back({350, 200, INVISIBILITY_POTION});
     items.push_back({300, 100, POTATO});
     items.push_back({150, 150, NO_ATTACK_POTION});
     items.push_back({170, 100, BLACK_HOLE});

   obstacleVec.push_back({200, 100, 30, 45});

   obstacleVec.push_back({50, 200, 35, 20});
   obstacleVec.push_back({250, 45, 50, 35});
//    obstacleVec.push_back({310, 70, 60, 30});
    // obstacleVec.push_back({25, 35, 40, 20});

//    obstacleVec.push_back({100, 200, 21});
     obstacleVec.push_back({220, 220, 15});
    // obstacleVec.push_back({350, 300, 12});

    enemies.push_back({350, 250, 5});
    enemies.push_back({210, 30, 5});
    // enemies.push_back({150, 300, 5});
    // enemies.push_back({380, 20, 5});

}

void FightGame::start(int w, int h) {
    appScreenW = w;
    appScreenH = h;
    player.setCharacterMoveRanges(2, 2, appScreenW - 2, appScreenH - 2);
    for (auto& element: enemies) {
        element.setCharacterMoveRanges(2, 2, appScreenW - 2, appScreenH - 2);
    }
    speedCounter = 0;
}

void FightGame::input(InputType input) {
    if(input == BUTTON_A && gameState == GAME_INIT) {
        updateOverlayText();
        //appTextOnOverlayActive = PortableOS::activateAppTextMode(overlayText, 0x1070AD);
        changeGameState(GAME_RUNNING);
    }

    if(input == BUTTON_D  && gameState == GAME_RUNNING)
    {
        shot();
    }
}

void FightGame::udpDataReceived(int messageID, std::vector<uint8_t> data) {

}

void FightGame::longPressInput(InputType input)
{

}

void FightGame::longPressRelease(InputType input)
{

}

void FightGame::analogInput(int x, int y) {
    y = y * -1;
    playerMoveInput.set(x * 1.3f, y * 1.3f);
    //Serial.println("Received x: " + String(x) + ", y: " + String(y) + ", length: " + String(playerMoveInput.getLength()));
    needsRepaint = true;
    isPlayerMovePending = true;
}

void FightGame::touchInput(int x, int y) {

}

void FightGame::update() { 
    if(gameState == GAME_RUNNING) {
        if(!itemActionsFlags[INVISIBILITY_POTION] && !itemActionsFlags[NO_ATTACK_POTION]) {
            calculateEnemyPosition();
        }

        // Update shots
        calculateShotsCollisions();

        calculatePlayerPosition();

        // Check player collisions
        calculateCollisions();

        calculateItemCollisions();
        updateActionTimers();
        updateOverlayText();
        spawnNewEnemy();
        spawnItem();
        checkIfGameOver();
    #ifdef EMULATOR
    #else
        lastUpdateMS = millis();
    #endif
        if(scoreCalculationCounter == 30) {
            scoreCalculationCounter = 0;
            score++;
        }
        scoreCalculationCounter++;
    }
}
void FightGame::render(DisplayProvider& display) {

    if (needsCleanScreen) {
        display.fillScreen(getBackgroundColor());
        needsCleanScreen = false;
    }

    if (needsRepaint) {
        switch (gameState) {
            case GAME_INIT:
                printGameStartScreen(display);
                needsRepaint = false;
            break;
            case GAME_RUNNING:
                for (auto& gameItem: items) {
                    gameItem.draw(display);
                }

                display.fillCircle(player.getLastX(), player.getLastY(), player.getSize(), getBackgroundColor());
                //delay(3);
                if(!itemActionsFlags[INVISIBILITY_POTION]) {
                    display.fillCircle(player.getX(), player.getY(), player.getSize(), 0x144377);//TFT_CYAN);
                }
                // Keep last rendered X and Y for player


                player.setLastXandY(player.getX(), player.getY());
                for (auto& enemy: enemies) {
                    enemy.draw(display);
                }

                // Draw obstacles
                for (auto& element: obstacleVec) {
                    element.draw(display);
                }

                // draw shots
                for(auto& shot : shots)
                {
                    shot.draw(display);
                }


                /*** REMOVE RENDERED GONE OBJECTS ***/
                {
                        shots.erase(std::remove_if(shots.begin(),
                                          shots.end(),
                                          [](GunShot& element) { return element.destroyed(); }),
                           shots.end());


                        items.erase(std::remove_if(items.begin(),
                                                           items.end(),
                                                           [](Item2D& element) { return element.getRemoveFlag(); }),
                                            items.end());

                        enemies.erase(std::remove_if(enemies.begin(),
                                                           enemies.end(),
                                                           [](Character2D& element) { return element.isKilled(); }),
                                            enemies.end());
                }

            break;
            case GAME_OVER:
                 printGameOverScreen(display);
            break;
        }




    }
    //needsRepaint = false;
}


void FightGame::forceRender(DisplayProvider &display)
{

}

void FightGame::end() {

}

String FightGame::getAppNameString() {
    return "Fight Game";
}

uint16_t FightGame::getBackgroundColor() {
    return TFT_BLACK;
}

void FightGame::calculateEnemyPosition() {
    for (auto& enemy: enemies) {
        enemy.update();
        Vector2D forceToChasePlayer{0, 0};
        forceToChasePlayer = !itemActionsFlags[POTATO] ?
             (player.getPosition() - enemy.getPosition()) : (enemy.getPosition() - player.getPosition());
        float chaseDistance = forceToChasePlayer.getLength();
        forceToChasePlayer = Vector2D::getNormalizedVector(forceToChasePlayer);

        bool anyCollision = false;
        // Go through obstacles on the map
        for(auto& obstacle: obstacleVec)
        {
            Vector2D forceToAvoidCollision{0,0};
            // Get obstacle to enemy vector
            forceToAvoidCollision = enemy.getPosition() - obstacle.getPosition();
            float forceLength = forceToAvoidCollision.getLength();
            // Check if obstacle is close enough
            if(forceLength < obstacle.getForceRange())
            {
                forceToAvoidCollision = Vector2D::getNormalizedVector(forceToAvoidCollision);
                enemy.applyMovementForce(forceToAvoidCollision, forceLength*0.1/0.03);

                anyCollision = true;
            }
        }
        // Only if there is no obstacle collision - try to chase the player
        if(!anyCollision)
        {
            enemy.applyMovementForce(forceToChasePlayer, chaseDistance*0.01/0.5);
        }

        for(auto& otherEnemy: enemies)
        {
            // Check if this is other enemy
            if(otherEnemy.getId() != enemy.getId())
            {
                // Check how far is other enemy
                Vector2D enemyToOtherDistance = enemy.getPosition() - otherEnemy.getPosition();
                // If we are close to each other
                if(enemyToOtherDistance.getLength() < enemy.getSize() + 3)
                {
                    // Move in opposite direction
                    enemyToOtherDistance = Vector2D::getNormalizedVector(enemyToOtherDistance);
                    enemy.applyMovementForce(enemyToOtherDistance, 5.f);
                }
            }
        }

    }



////            enemy.setVelocity(newVelocity);
////            enemy.moveBy(enemy.getVelocity().getX(), enemy.getVelocity().getY());

}

void FightGame::calculatePlayerPosition() {
    if(isPlayerMovePending) {
        Vector2D playerMoveDir = Vector2D::getNormalizedVector(playerMoveInput);
        //Apply shot direction
        shotDirection = playerMoveDir;

        // Adjust player 'speed'
        if(!itemActionsFlags[FOOD]) {
            playerMoveDir.rescale(1.1f);
        }
        else {
            playerMoveDir.rescale(1.7f);
        }

        // Move player to new position
        player.moveBy(playerMoveDir.getX(), playerMoveDir.getY());
        // Clear moveInput vector
        playerMoveInput.set(0, 0);

        // Clean player move pending flag
        isPlayerMovePending = false;
    }
}

void FightGame::calculateCollisions() {
    //player collisions
    for (auto& obstacle: obstacleVec) {
        if(obstacle.isInCollision(player.getX(), player.getY(), player.getSize())) {
            player.move(player.getLastX(), player.getLastY());
            break;
        }
    }
}

void FightGame::calculateItemCollisions()
{
    for (auto& gameItem: items) {
        if (gameItem.isInCollision(player)) {
            switch (gameItem.getType()) {
                case FOOD:
                    foodItemReaction();
                break;
                case INVISIBILITY_POTION:
                    invisibilityPotionItemReaction();
                break;
                case POTATO:
                    potatoReaction();
                break;
                case NO_ATTACK_POTION:
                    ghostPotionReaction();
                break;
                case BLACK_HOLE:
                    holeReaction();
                break;
                case AMO_PACK:
                    collectAmo();
                break;
                default:
                break;
            }
            collectedItems++;
        }
    }
}

void FightGame::foodItemReaction()
{
    itemActionsFlags[FOOD] = true;
    itemActionsTimers[FOOD] = 10000;
}

void FightGame::invisibilityPotionItemReaction()
{
    itemActionsFlags[INVISIBILITY_POTION] = true;
    itemActionsTimers[INVISIBILITY_POTION] = 5000;
}

void FightGame::potatoReaction()
{
    itemActionsFlags[POTATO] = true;
    itemActionsTimers[POTATO] = 10000;
}

void FightGame::ghostPotionReaction()
{
    itemActionsFlags[NO_ATTACK_POTION] = true;
    itemActionsTimers[NO_ATTACK_POTION] = 5000;
}

void FightGame::holeReaction()
{
    gameOver();
}

void FightGame::collectAmo()
{
    amo += 5;
}

void FightGame::updateActionTimers() {
#ifdef EMULATOR
    uint8_t timeSinceLastUpdate = 25;
#else
    //calculate time since last update
    uint8_t timeSinceLastUpdate = millis() - lastUpdateMS;
#endif

    //go through all events timers
    for (uint8_t i = FOOD; i <= BLACK_HOLE; i++)
    {
        //check if event is active
        if(itemActionsFlags[i]) {
            //subtract time from timer
            itemActionsTimers[i] -= timeSinceLastUpdate;
            //check if timer expired
            if(itemActionsTimers[i] <= 0) {
                //disable flag
                itemActionsFlags[i] = false;
            }
        }
    }
}

void FightGame::changeGameState(GameState newState)
{
    gameState = newState;
    needsRepaint = true;
    needsCleanScreen = true;
}

void FightGame::printGameStartScreen(DisplayProvider &display)
{
    if (!startScreenDisplayed) {
        display.setTextSize(2);
        display.setTextFont(2);
        display.drawString("Zasady gry", 175, 3);
        display.setTextSize(1);
        display.drawString("Uciekaj przed goniacymi przeciwnikami aby zdobyc jak najwiecej punktow.", 10, 40);
        display.drawString("Po drodze zbieraj dodatkowe przedmioty ktore pomoga Ci w ucieczce", 20, 60);
        display.setTextSize(1);
        display.drawString("- batonik przyspieszenia", 40, 85);
        display.drawString("- mikstura niewidzialnosci", 40, 115);
        display.drawString("- przedmiot odpychania", 40, 145);
        display.drawString("- mikstura przenikania", 40, 175);
        display.drawString("- czarna dziura (KONIEC GRY)", 40, 205);

        display.drawString("- PRZECIWNIK", 340, 140);
        display.drawString("- PRZESZKODA", 340, 200);

        display.setTextSize(2);
        display.drawString("Nacisnij A, aby rozpoczac ...", 110, 250);


        Item2D temporary1(25, 90, FOOD);
        temporary1.draw(display);

        Item2D temporary2(25, 120, INVISIBILITY_POTION);
        temporary2.draw(display);

        Item2D temporary3(25, 150, POTATO);
        temporary3.draw(display);

        Item2D temporary4(25, 180, NO_ATTACK_POTION);
        temporary4.draw(display);

        Item2D temporary5(25, 210, BLACK_HOLE);
        temporary5.draw(display);

        Character2D enemyPlaceholder(310, 150, 20);

        Obstacle obstaclePlaceholder(300, 180, 30, 50);
        display.fillCircle(enemyPlaceholder.getX(), enemyPlaceholder.getY(), enemyPlaceholder.getSize(), TFT_RED);
        obstaclePlaceholder.draw(display);

        startScreenDisplayed = true;
    }
}

void FightGame::printGameOverScreen(DisplayProvider &display)
{
    if(!gameOverScreenDisplayed) {
        display.fillScreen(getBackgroundColor());
        display.setTextColor(TFT_RED, TFT_BLACK);
        display.drawString("GAME OVER!", 165, 40);

        String scoreString = "Score : ";
        String killsString = "Kills : ";
        String itemsString = "Items collected : ";

#ifdef EMULATOR
        scoreString += QString::number(score);
        killsString += QString::number(kills);
        itemsString += QString::number(collectedItems);
#else
        scoreString += String(score);
        killsString += String(kills);
        itemsString += String(collectedItems);
#endif

        display.setTextColor(0x22879B, TFT_BLACK);
        display.drawString(scoreString, 60, 100);
        display.drawString(killsString, 60, 150);
        display.drawString(itemsString, 60, 200);

        needsRepaint = false;
        gameOverScreenDisplayed = true;
    }
}

void FightGame::shot()
{
    if(amo > 0)
    {
        Vector2D shotPosVector = player.getPosition();
        shots.push_back({shotPosVector, shotDirection});
        amo --;
    }
}

void FightGame::updateOverlayText()
{
    if(gameState == GAME_RUNNING) {

#ifdef EMULATOR
        overlayText = "Score: ";
        if(score < 1000)
        {
            overlayText += "0";
        }
        if(score < 100)
        {
            overlayText += "0";
        }
        if(score < 10)
        {
            overlayText += "0";
        }
        overlayText += String(QString::number(score)) + " ";
        overlayText += "| Amo: ";
        if(amo < 10){
            overlayText += "0";
        }
        overlayText += String(QString::number(amo));
#else
        overlayText = "Score: ";
        if(score < 1000)
        {
            overlayText += "0";
        }
        if(score < 100)
        {
            overlayText += "0";
        }
        if(score < 10)
        {
            overlayText += "0";
        }
        overlayText += String(score) + " ";
        overlayText += "| Amo: ";
        if(amo < 10){
            overlayText += "0";
        }
        overlayText += String(amo);
#endif

        appTextOnOverlayActive = PortableOS::activateAppTextMode(overlayText, 0x1070AD);
    }

}

void FightGame::calculateShotsCollisions()
{
    Vector2D shotPos;
    for(auto& shot : shots)
    {
        shot.update();

        shotPos = shot.getPos();

        for(auto& enemy : enemies)
        {
            Vector2D enemyPos = enemy.getPosition();
            Vector2D shotToEnemyVector = {enemyPos.getX() - shotPos.getX(),
                                         enemyPos.getY() - shotPos.getY()};
            if(shotToEnemyVector.getLength() < (enemy.getSize() /* shot size skipped*/))
            {
                enemy.kill();
                shot.destroy();
                score += 10;
                kills ++;
            }
        }
    }
}

void FightGame::spawnNewEnemy()
{
    if(enemySpawnCounter == 0)
    {
#ifdef EMULATOR
        enemySpawnCounter = rand()%200;
        enemies.push_back({(float)(rand()%475), (float)(rand()%300), 5});
#else
        enemySpawnCounter = random(200);
        enemies.push_back({(float)(random(475)), (float)(random(300)), 5});
#endif
    }else
    {
        enemySpawnCounter --;
    }
}

void FightGame::checkIfGameOver()
{
    Vector2D enemyPos;
    Vector2D playerPos = player.getPosition();
    Vector2D enemyToPlayerVec;
    for (auto& enemy: enemies) {

        enemyPos = enemy.getPosition();
        enemyToPlayerVec = {enemyPos.getX() - playerPos.getX(), enemyPos.getY() - playerPos.getY()};

        if(enemyToPlayerVec.getLength() < player.getSize() + enemy.getSize()) {
            gameOver();
        }
    }
}

void FightGame::gameOver()
{
    gameState = GAME_OVER;
    PortableOS::deactivateAppTextMode();
}

void FightGame::spawnItem()
{
    if(itemSpawnCounter == 0)
    {
        GameItemType itemType;
        float itemX, itemY;
        #ifdef EMULATOR
        itemSpawnCounter = rand()%220;
        itemType = (GameItemType)(rand()%6);
        itemX = (float)(rand()%475);
        itemY = (float)(rand()%300);
        #else
        itemSpawnCounter = random(220);
        itemType = (GameItemType)(random(6));
        itemX = (float)(random(475));
        itemY = (float)(random(300));
        #endif

        Vector2D itemPos{itemX, itemY};
        for(auto& obstacle: obstacleVec) {

            Vector2D itemToObstacleVec{itemPos.getX() - obstacle.getPosition().getX(),
                        itemPos.getY() - obstacle.getPosition().getY()};
            while(obstacle.isInCollision(itemPos.getX(), itemPos.getY(), 7)) {
                itemPos.setX(itemPos.getX() + itemToObstacleVec.getX());
                itemPos.setY(itemPos.getY() + itemToObstacleVec.getY());

            }

        }

        items.push_back({itemPos.getX(), itemPos.getY(), itemType});

    }else
    {
        itemSpawnCounter --;
    }

}
