#ifndef METODIK_INVADERS2_GAME_H
#define METODIK_INVADERS2_GAME_H

#include <QObject>
#include "spacecraft.h"
#include "enemy.h"
#include "backgroundmusic.h"
#include "SpawnHandler.h"
#include "player.h"
#include "InputHandler.h"
#include "MenuScene.h"
#include "GameScene.h"

namespace space_pewpew {

  /**
   * @brief The Game class
   * This class is the main class of the game. It is responsible for the game state and the game loop.
   */
  class Game : public QObject {
  Q_OBJECT

  public:
    /**
     * @brief Game
     */
    Game();

    /**
     * @brief startGame
     * This method starts the game loop.
     */
    void setState(settings::GameState state);

    /**
     * @brief getState
     * @return the current game state
     */
    settings::GameState getState() const;

    ~Game();

//    bool eventFilter(QObject *obj, QEvent *event) override;

//    QSet<int> pressedKeys;

  public slots:

    /**
     * @brief showGameScene
     * This method shows the game scene.
     */
    void showGameScene();

    /**
     * @brief showPauseScene
     * This method shows the start menu scene.
     */
    void showPauseScene();

    /**
     * @brief retryGame
     * This method shows the game over scene.
     */
    void retryGame();

    /**
     * @brief showGameOverScene
     * This method quits the game.
     */
    void showGameOverScene();

    /**
     * @brief showStartMenuScene
     * This method shows the start menu scene.
     */
    void showStartMenuScene();

  private:
    settings::GameState m_state;
    QTimer *gameSceneTimer;
    int m_score;
    int m_lives;
    int m_health;
    int m_waveCount;
    QGraphicsView *view;
    InputHandler *m_inputHandler;
    MenuScene *startMenuScene;
    MenuScene *pauseMenuScene;
    MenuScene *gameOverMenuScene;
    BackgroundMusic *m_bgMusic;
    SfxHandler *m_sfxHandler;
    GameScene *gameScene;
    Player *player;
    SpawnHandler *spawnHandler;

    /**
     * @brief setupView
     * This method sets up the view.
     */
    void setupView();

    /**
     * @brief setupStartMenuScene
     * This method sets up the start menu scene.
     */
    void setupMainMenuScene();

    /**
     * @brief setupPauseMenuScene
     * This method sets up the pause menu scene.
     */
    void setupPauseMenuScene();

    /**
     * @brief setupGameOverMenuScene
     * This method sets up the game over menu scene.
     */
    void setupGameOverMenuScene();

    /**
     * @brief setupGameScene
     * This method sets up the game scene.
     */
    void setupGameScene();

    /**
     * @brief setupGameBackground
     * This method sets up the game background.
     */
    void setupGameBackground();

    /**
     * @brief makeConnections
     * This method sets up the game scene timer.
     */
    void makeConnections();

  };
} // namespace space_pewpew
#endif // METODIK_INVADERS2_GAME_H
