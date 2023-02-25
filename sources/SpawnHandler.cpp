//
// Created by nordi on 1/31/2023.
//

#include <QObject>
#include <QGraphicsScene>
#include "headers/SpawnHandler.h"
#include "headers/enemy.h"

namespace space_pewpew {
  SpawnHandler::SpawnHandler(const int &playerScore, QGraphicsScene *scene,
                             QObject *parent)
    : m_playerScore(playerScore),
      m_scene(scene),
      QObject(parent),
      m_formationSpawnThreshold(50),
      m_miniBossSpawnThreshold(200),
      m_bossSpawnThreshold(300) {
    m_randomSpawnTimer = new QTimer(this);
    m_formationSpawnTimer = new QTimer(this);
    m_miniBossSpawnTimer = new QTimer(this);
    m_bossSpawnTimer = new QTimer(this);
    m_randomSpawnTimer->setInterval(1000);
    m_formationSpawnTimer->setInterval(1000);
    m_miniBossSpawnTimer->setInterval(1000);
    m_bossSpawnTimer->setInterval(1000);

    connect(m_randomSpawnTimer, &QTimer::timeout, [this]() {
      emit spawnRandomEnemySignal();
    });
    connect(m_formationSpawnTimer, &QTimer::timeout, [this]() {
      if (m_playerScore >= m_formationSpawnThreshold) {
        emit spawnFormationSignal();
        m_formationSpawnThreshold += 100;
      }
    });
    connect(m_miniBossSpawnTimer, &QTimer::timeout, [this]() {
      if (m_playerScore >= m_miniBossSpawnThreshold) {
        emit spawnMiniBossSignal();
      }
    });
    connect(m_bossSpawnTimer, &QTimer::timeout, [this]() {
      if (m_playerScore >= m_bossSpawnThreshold) {
        emit spawnBossSignal();
      }
    });
    connect(this, &SpawnHandler::spawnRandomEnemySignal, this,
            &SpawnHandler::spawnRandomHandler);
    connect(this, &SpawnHandler::spawnFormationSignal, this,
            &SpawnHandler::spawnFormationHandler);
    connect(this, &SpawnHandler::spawnMiniBossSignal, this,
            &SpawnHandler::spawnMiniBossHandler);
    connect(this, &SpawnHandler::spawnBossSignal, this,
            &SpawnHandler::spawnBossHandler);
    connect(this, &SpawnHandler::setPlayerScoreSignal, this,
            &SpawnHandler::setPlayerScore);

    m_randomSpawnTimer->start();
    m_formationSpawnTimer->start();
    m_miniBossSpawnTimer->start();
    m_bossSpawnTimer->start();
  }

  SpawnHandler::~SpawnHandler() {
    delete m_formationSpawnTimer;
    delete m_miniBossSpawnTimer;
    delete m_bossSpawnTimer;
    delete m_randomSpawnTimer;
  }

  void SpawnHandler::setPlayerScore(const int &playerScore) {
    m_playerScore = playerScore;
  }

  void
  SpawnHandler::setFormationSpawnThreshold(const int &formationSpawnThreshold) {
    m_formationSpawnThreshold = formationSpawnThreshold;
  }

  void
  SpawnHandler::setMiniBossSpawnThreshold(const int &miniBossSpawnThreshold) {
    m_miniBossSpawnThreshold = miniBossSpawnThreshold;
  }

  void SpawnHandler::setBossSpawnThreshold(const int &bossSpawnThreshold) {
    m_bossSpawnThreshold = bossSpawnThreshold;
  }

  void SpawnHandler::spawnRandomHandler() {
    int randSpawn = rand() % 10;
    if (randSpawn <= 5) {
      return;
    }
    int enemyX = randomPosX();
    int enemyY = -200;

    // random ship type
    settings::ShipTypes shipType = getRandomEnemyShipType(
      settings::ShipClass::Fighter);

    Enemy *enemy = new Enemy(settings::ShipSpeeds::FighterSpeed,
                             settings::UpdateMs::UMs30,
                             settings::Healths::FighterHealth,
                             settings::UpdateMs::UMs100,
                             settings::MoveSteps::Move01,
                             settings::AmmoType::TypeLaser,
                             settings::AmmoDmgLvl::Dmg10,
                             settings::Faction::Enemy,
                             settings::ShipClass::Fighter,
                             shipType,
                             m_scene,
                             parent());
    m_scene->addItem(enemy);
    enemy->setStartPosition(enemyX, enemyY);
    connect(enemy, &Enemy::enemyDiedSignal, this,
            [this](settings::ShipClass enemyClass) {
              emit enemyDiedSignal(enemyClass);
            });
  }

  int SpawnHandler::randomPosX() const {
    int edgeOffset = 100;
    int enemyX =
      edgeOffset + (rand() % (int) (m_scene->width() - edgeOffset * 2));
    return enemyX;
  }

  void SpawnHandler::spawnFormationHandler() {
    if (m_waitSpecialSpawn) {
      return;
    }

    // Choose a random formation from the formation list
    int formationIndex = rand() % settings::formations.size();
    QList<QList<bool>> currentFormation = settings::formations[formationIndex];

    // Calculate the starting position of the formation
    int formationHeight = currentFormation.size();
    int formationWidth = currentFormation[0].size();
    int edgeOffset = 10;
    int rightBound = m_scene->width() - edgeOffset;
    int leftBound = edgeOffset;
    int shipSize = m_scene->width() / formationWidth - (2 * edgeOffset);
    int startX = shipSize / 2 + leftBound;

    int sceneHeightSpawnArea = m_scene->height() * 0.6f;

    int startY = (sceneHeightSpawnArea / formationHeight + shipSize / 2) -
                 m_scene->height();
    // TODO replace this with obove
//    int startY = (sceneHeightSpawnArea / formationHeight + shipSize / 2);

    // Spawn the ships in the formation
    for (int i = 0; i < formationHeight; ++i) {
      bool isRandByRow = settings::randomBool();
      settings::ShipTypes shipType;
      if (isRandByRow) {
        shipType = getRandomEnemyShipType(settings::ShipClass::Fighter);
      }
      for (int j = 0; j < formationWidth; ++j) {
        if (currentFormation[i][j]) {
          // is not randbyrow and j is even
          if (!isRandByRow && (j % 2 == 0)) {
            shipType = getRandomEnemyShipType(settings::ShipClass::Fighter);
          }
//          SpaceCraft *enemy = new SpaceCraft(QPointF(startX + j * shipSize, startY + i * shipSize), SpaceCraft::EnemyFighter);

          Enemy *enemy = new Enemy(settings::ShipSpeeds::FighterSpeed,
                                   settings::UpdateMs::UMs30,
                                   settings::Healths::FighterHealth,
                                   settings::UpdateMs::UMs100,
                                   settings::MoveSteps::Move01,
                                   settings::AmmoType::TypeLaser,
                                   settings::AmmoDmgLvl::Dmg10,
                                   settings::Faction::Enemy,
                                   settings::ShipClass::Fighter,
                                   settings::ShipTypes::Viper,
                                   m_scene,
                                   parent());
          m_scene->addItem(enemy);
//          enemy->setZValue(std::numeric_limits<qreal>::max());

          enemy->setStartPosition(startX + j * shipSize, startY + i * shipSize);
//          enemyList.append(enemy);
          connect(enemy, &Enemy::enemyDiedSignal, this,
                  [this](settings::ShipClass enemyClass) {
                    emit enemyDiedSignal(enemyClass);
                  });
        }
      }
    }
  }

  void SpawnHandler::spawnMiniBossHandler() {
    if (m_waitSpecialSpawn) {
      return;
    }
    m_waitSpecialSpawn = true;

    int enemyX = randomPosX();
    int enemyY = -200;
    Enemy *enemy = new Enemy(settings::ShipSpeeds::BomberSpeed,
                             settings::UpdateMs::UMs40,
                             settings::Healths::BomberHealth,
                             settings::UpdateMs::UMs200,
                             settings::MoveSteps::Move01,
                             settings::AmmoType::TypeMissile,
                             settings::AmmoDmgLvl::Dmg30,
                             settings::Faction::Enemy,
                             settings::ShipClass::Bomber,
                             settings::ShipTypes::Bombardier,
                             m_scene,
                             parent());
    m_scene->addItem(enemy);
    enemy->setStartPosition(enemyX, enemyY);
    connect(enemy, &Enemy::enemyDiedSignal, this,
            [this](settings::ShipClass enemyClass) {
              emit enemyDiedSignal(enemyClass);
              enemyDiedHandler(enemyClass);
            });
    connect(enemy, &Enemy::escaped, [this]() {
      m_waitSpecialSpawn = false;
    });
  }

  void SpawnHandler::spawnBossHandler() {
    if (m_waitSpecialSpawn) {
      return;
    }
    m_waitSpecialSpawn = true;

    int enemyX = randomPosX();
    int enemyY = -200;
    Enemy *enemy = new Enemy(settings::ShipSpeeds::BossSpeed,
                             settings::UpdateMs::UMs50,
                             settings::Healths::BossHealth,
                             settings::UpdateMs::UMs200,
                             settings::MoveSteps::Move01,
                             settings::AmmoType::TypeMissile,
                             settings::AmmoDmgLvl::Dmg50,
                             settings::Faction::Enemy,
                             settings::ShipClass::Boss,
                             settings::ShipTypes::Behemoth,
                             m_scene,
                             parent());
    m_scene->addItem(enemy);
    enemy->setStartPosition(enemyX, enemyY);
    connect(enemy, &Enemy::enemyDiedSignal, this,
            [this](settings::ShipClass enemyClass) {
              emit enemyDiedSignal(enemyClass);
              enemyDiedHandler(enemyClass);
            });
    connect(enemy, &Enemy::escaped, [this]() {
      m_waitSpecialSpawn = false;
    });
  }

  void SpawnHandler::enemyDiedHandler(settings::ShipClass enemyShipClass) {
    switch (enemyShipClass) {
      case settings::ShipClass::Bomber:
        m_waitSpecialSpawn = false;
        m_miniBossSpawnThreshold += 200;
        break;
      case settings::ShipClass::Boss:
        m_waitSpecialSpawn = false;
        m_bossSpawnThreshold += 500;
        break;
      default:
        break;
    }
  }

  settings::ShipTypes
  SpawnHandler::getRandomEnemyShipType(settings::ShipClass shipClass) {
    settings::ShipTypes shipType;
    switch (shipClass) {
      case settings::ShipClass::Fighter:
        shipType = settings::randomBool() ? settings::ShipTypes::Viper
                                          : settings::ShipTypes::Enforcer;
        return shipType;
      case settings::ShipClass::Bomber:
        return settings::ShipTypes::Bombardier;
      case settings::ShipClass::Boss:
        return settings::ShipTypes::Behemoth;
      default:
        return settings::ShipTypes::Viper;
    }
  }

} // space_pewpew