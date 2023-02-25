#include "headers/game.h"
#include "headers/background.h"
#include "headers/backgroundmusic.h"
#include "headers/player.h"
#include "headers/MenuScene.h"
#include "headers/GameScene.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QApplication>

namespace space_pewpew {
  Game::Game()
    : m_state(settings::GameState::MAIN_MENU),
      m_score(0),
      m_lives(3),
      m_health(settings::PlayerHealth),
      m_waveCount(0),
      view(new QGraphicsView()),
      m_inputHandler(new InputHandler()),
      startMenuScene(new MenuScene(this)),
      pauseMenuScene(new MenuScene(this)),
      gameOverMenuScene(new MenuScene(this)),
      m_bgMusic(new BackgroundMusic(this)),
      m_sfxHandler(new SfxHandler()) {

    setupView();

    setupMainMenuScene();
    setupPauseMenuScene();
    setupGameOverMenuScene();
    setupGameScene();

    gameOverMenuScene->deactivate();
    pauseMenuScene->deactivate();
    gameScene->deactivate();

    showStartMenuScene();
  }

  void Game::setupView() {
    // performance of view
    view->setCacheMode(QGraphicsView::CacheBackground);
    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    view->setOptimizationFlags(QGraphicsView::DontSavePainterState);
//    view->setOptimizationFlags(QGraphicsView::DontAdjustForAntialiasing);

    // quality of view
    view->setRenderHint(QPainter::Antialiasing);
    view->setRenderHint(QPainter::SmoothPixmapTransform);
    view->setRenderHint(QPainter::TextAntialiasing);

    // size of view
    view->setFixedSize(QApplication::primaryScreen()->size());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Show the view
    view->setFocus();
    view->activateWindow();
    view->showFullScreen();

    // send events to inputHandler
    view->installEventFilter(m_inputHandler);
  }

  void Game::setupGameBackground() {
    // Create a new background and add it to the gameScene
    auto *bgUniverse = new Background(1, 100,
                                      {":/resources/bg/nebulaAquaPink.png"});
    auto *galaxies = new Background(1, 90,
                                    {":/resources/bg/galaxies01.png",
                                     ":/resources/bg/galaxies02.png"});
    auto *bgStars1 = new Background(1, 80,
                                    {":/resources/bg/starsSmall1.png"});
    auto *bgStars2 = new Background(1, 60,
                                    {":/resources/bg/starsSmall2.png"});

    QList<QString> planetSlides = {":/resources/bg/planets01.png",
                                   ":/resources/bg/planets02.png",
                                   ":/resources/bg/planets03.png",
                                   ":/resources/bg/planets04.png"
    };
    auto *bgPlanets = new Background(2, 20, planetSlides);

    auto *bgStarWarp = new Background(6, 8,
                                      {":/resources/bg/starfieldWarp.png"});

    gameScene->addBackground(bgUniverse);
    gameScene->addBackground(galaxies);
    gameScene->addBackground(bgStars1);
    gameScene->addBackground(bgStars2);
    gameScene->addBackground(bgPlanets);
    gameScene->addBackground(bgStarWarp);
  }

  void Game::setupMainMenuScene() {
    startMenuScene->setSceneRect(0, 0, view->width(), view->height());
    // Create backgrounds and add it to this scene
    auto *bgUniverse = new Background(1, 100,
                                      {":/resources/bg/nebulaRed.png"});
    auto *bgStars1 = new Background(1, 80,
                                    {":/resources/bg/starsSmall1.png"});
    auto *bgStars2 = new Background(1, 60,
                                    {":/resources/bg/starsSmall2.png"});

    startMenuScene->addBackground(bgUniverse);
    startMenuScene->addBackground(bgStars1);
    startMenuScene->addBackground(bgStars2);

    startMenuScene->setTitleImg(":/resources/ui/spaceInvasion.png");

    // Create the quit button
    auto *startBtn = new MenuButton(
      QPixmap(":/resources/ui/startGame.png"),
      QPixmap(":/resources/ui/startGame_active.png"));
    startMenuScene->addButton(startBtn);
    connect(startBtn, &MenuButton::clicked, this, &Game::showGameScene);

    // Create the quit button
    auto *quitBtn = new MenuButton(
      QPixmap(":/resources/ui/quitGame.png"),
      QPixmap(":/resources/ui/quitGame_active.png"));
    startMenuScene->addButton(quitBtn);
    connect(quitBtn, &MenuButton::clicked, this,
            []() { QApplication::quit(); });

    startMenuScene->buildScene();
  }

  void Game::setupPauseMenuScene() {
    pauseMenuScene->setSceneRect(0, 0, view->width(), view->height());
    // Create backgrounds and add it to this scene
    auto *bgUniverse = new Background(1, 100,
                                      {":/resources/bg/nebulaBlue.png"});
    auto *bgStars1 = new Background(1, 80,
                                    {":/resources/bg/starsSmall1.png"});
    auto *bgStars2 = new Background(1, 60,
                                    {":/resources/bg/starsSmall2.png"});

    pauseMenuScene->addBackground(bgUniverse);
    pauseMenuScene->addBackground(bgStars1);
    pauseMenuScene->addBackground(bgStars2);

    //TODO: add a pause menu image
    pauseMenuScene->setTitleImg(":/resources/ui/spaceInvasion.png");

    // Create resume button
    auto *resumeBtn = new MenuButton(
      QPixmap(":/resources/ui/resume.png"),
      QPixmap(":/resources/ui/resume_active.png"));
    pauseMenuScene->addButton(resumeBtn);
    connect(resumeBtn, &MenuButton::clicked, this, &Game::showGameScene);

    // Create the quit button
    auto *quitBtn = new MenuButton(
      QPixmap(":/resources/ui/quitGame.png"),
      QPixmap(":/resources/ui/quitGame_active.png"));
    pauseMenuScene->addButton(quitBtn);
    connect(quitBtn, &MenuButton::clicked, this,
            []() { QApplication::quit(); });

    pauseMenuScene->buildScene();
  }

  void Game::setupGameOverMenuScene() {
    gameOverMenuScene->setSceneRect(0, 0, view->width(), view->height());
    // Create backgrounds and add it to this scene
    auto *bgUniverse = new Background(1, 100,
                                      {":/resources/bg/nebulaRed.png"});
    auto *bgStars1 = new Background(1, 80,
                                    {":/resources/bg/starsSmall1.png"});
    auto *bgStars2 = new Background(1, 60,
                                    {":/resources/bg/starsSmall2.png"});

    gameOverMenuScene->addBackground(bgUniverse);
    gameOverMenuScene->addBackground(bgStars1);
    gameOverMenuScene->addBackground(bgStars2);

    //TODO: add a gameOver menu image
    gameOverMenuScene->setTitleImg(":/resources/ui/gameOver.png");

    // Create resume button
    auto *retryBtn = new MenuButton(
      QPixmap(":/resources/ui/retry.png"),
      QPixmap(":/resources/ui/retry_active.png"));
    gameOverMenuScene->addButton(retryBtn);
    connect(retryBtn, &MenuButton::clicked, this, &Game::retryGame);

    // Create the quit button
    auto *quitBtn = new MenuButton(
      QPixmap(":/resources/ui/quitGame.png"),
      QPixmap(":/resources/ui/quitGame_active.png"));
    gameOverMenuScene->addButton(quitBtn);
    connect(quitBtn, &MenuButton::clicked, this,
            []() { QApplication::quit(); });

    gameOverMenuScene->buildScene();
  }

  void Game::setupGameScene() {
    gameScene = new GameScene(this);
    gameScene->setSceneRect(0, 0, view->width(), view->height());
    setupGameBackground();

    m_score = 0;
    m_health = settings::Healths::PlayerHealth;
    m_lives = 0;

    // Create a new player and add it to the gameScene
    player = new Player(settings::ShipSpeeds::PlayerSpeed,
                        settings::UpdateMs::UMs20,
                        settings::Healths::PlayerHealth,
                        settings::UpdateMs::UMs200,
                        settings::MoveSteps::Move01,
                        settings::AmmoType::TypeLaser,
                        settings::AmmoDmgLvl::Dmg10,
                        settings::Faction::Player,
                        settings::ShipClass::Fighter,
                        settings::ShipTypes::Striker,
                        this);
    gameScene->addItem(player);
    player->setStartPosition(gameScene->width() / 2,
                             gameScene->height() - 200);
    player->setZValue(std::numeric_limits<qreal>::max());

    spawnHandler = new SpawnHandler(m_score, gameScene, this);

    gameScene->buildScene();

    // connections for the gameScene, player and spawnHandler, etc.
    makeConnections();
  }

  void Game::showStartMenuScene() {
    m_state = settings::GameState::MAIN_MENU;
    m_bgMusic->setMusicPath("qrc:/resources/music/menu01.mp3");
    m_bgMusic->play();
    view->setScene(startMenuScene);
    startMenuScene->activate();
  }

  void Game::showGameScene() {
    m_state = settings::GameState::RUNNING;
    pauseMenuScene->deactivate();
    gameOverMenuScene->deactivate();
    m_bgMusic->setMusicPath("qrc:/resources/music/playTime01.mp3");
    m_bgMusic->play();
    view->setScene(gameScene);
    gameScene->activate();
  }

  void Game::showPauseScene() {
    m_state = settings::GameState::PAUSED;
    gameScene->deactivate();
    gameOverMenuScene->deactivate();
    m_bgMusic->setMusicPath("qrc:/resources/music/menu01.mp3");
    m_bgMusic->play();
    view->setScene(pauseMenuScene);
    pauseMenuScene->activate();
  }

  void Game::showGameOverScene() {
    m_sfxHandler->playSound("qrc:/resources/sfx/sfx_gameOver.mp3");
    m_sfxHandler->playSound("qrc:/resources/sfx/sfx_explosion05.mp3");
    m_state = settings::GameState::GAME_OVER;
    gameScene->deactivate();
    delete player;
    delete spawnHandler;
    delete gameScene;
    gameOverMenuScene->activate();
    m_bgMusic->setMusicPath("qrc:/resources/music/gameOver01.mp3");
    m_bgMusic->play();
    view->setScene(gameOverMenuScene);
  }

  void Game::retryGame() {
    setupGameScene();
    showGameScene();
  }

  void Game::makeConnections() {

    connect(m_inputHandler, &InputHandler::pausePressed, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        showPauseScene();
      } else if (m_state == settings::GameState::PAUSED) {
        showGameScene();
      }
    });
    connect(m_inputHandler, &InputHandler::shootDown, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setShooting(true);
      }
    });
    connect(m_inputHandler, &InputHandler::shootUp, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setShooting(false);
      }
    });
    connect(m_inputHandler, &InputHandler::moveLeftDown, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionX(-1);
      }
    });
    connect(m_inputHandler, &InputHandler::moveLeftUp, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionX(0);
      }
    });
    connect(m_inputHandler, &InputHandler::moveRightDown, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionX(1);
      }
    });
    connect(m_inputHandler, &InputHandler::moveRightUp, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionX(0);
      }
    });
    connect(m_inputHandler, &InputHandler::moveUpDown, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionY(-1);
      }
    });
    connect(m_inputHandler, &InputHandler::moveUpUp, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionY(0);
      }
    });
    connect(m_inputHandler, &InputHandler::moveDownDown, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionY(1);
      }
    });
    connect(m_inputHandler, &InputHandler::moveDownUp, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        player->setDirectionY(0);
      }
    });
    connect(player, &Player::bulletHitSignal, this, [this]() {
      m_health = player->getHealth();
      gameScene->updateHealth(m_health);
      if (m_health <= 0 && m_state == settings::GameState::RUNNING) {
        showGameOverScene();
      }
    });
    connect(player, &Player::explodingSignal, this, [this]() {
      if (m_state == settings::GameState::RUNNING) {
        m_health = 0;
        gameScene->updateHealth(m_health);
        showGameOverScene();
      }
    });
    connect(spawnHandler, &SpawnHandler::enemyDiedSignal, this,
            [this](settings::ShipClass enemyClass) {
              switch (enemyClass) {
                case settings::ShipClass::Fighter:
                  m_score += settings::ClassKilledScore::FighterScore;
                  break;
                case settings::ShipClass::Bomber:
                  m_score += settings::ClassKilledScore::BomberScore;
                  break;
                case settings::ShipClass::Boss:
                  m_score += settings::ClassKilledScore::BossScore;
                  break;
                default:
                  m_score += settings::ClassKilledScore::FighterScore;
                  break;
              }
              spawnHandler->setPlayerScore(m_score);
              gameScene->updateScore(m_score);
            });
  }
  Game::~Game() {
    delete player;
    delete m_bgMusic;
    delete spawnHandler;
    delete gameScene;
    delete pauseMenuScene;
    delete gameOverMenuScene;
    delete startMenuScene;
    delete m_inputHandler;
    delete view;
  }
} // namespace space_pewpew