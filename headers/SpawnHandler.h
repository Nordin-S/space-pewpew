//
// Created by nordi on 1/31/2023.
//

#ifndef METODIK_INVADERS2_SPAWNHANDLER_H
#define METODIK_INVADERS2_SPAWNHANDLER_H

#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "enemy.h"

namespace space_pewpew {

  /**
   * @brief The SpawnHandler class
   * This class is responsible for spawning enemies and handling the spawn timers.
   * It also handles the score and the thresholds for special enemy spawns.
   */
  class SpawnHandler : public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  public:

    /**
     * @brief SpawnHandler
     * @param playerScore
     * @param scene
     * @param parent
     */
    explicit SpawnHandler(const int &playerScore = 0, QGraphicsScene* scene = nullptr, QObject* parent = nullptr);
    ~SpawnHandler() override;

    /**
     * @brief setFormationSpawnThreshold
     * @param formationSpawnThreshold - the score threshold for spawning a formation
     */
    void setFormationSpawnThreshold(const int &formationSpawnThreshold);

    /**
     * @brief setMiniBossSpawnThreshold
     * @param miniBossSpawnThreshold - the score threshold for spawning a mini boss
     */
    void setMiniBossSpawnThreshold(const int &miniBossSpawnThreshold);

    /**
     * @brief setBossSpawnThreshold
     * @param bossSpawnThreshold - the score threshold for spawning a boss
     */
    void setBossSpawnThreshold(const int &bossSpawnThreshold);

    /**
     * @brief getRandomEnemyShipType
     * @param shipClass - the ship class of the enemy
     */
    settings::ShipTypes getRandomEnemyShipType(settings::ShipClass shipClass);
  signals:

    /**
     * @brief spawnRandomEnemySignal
     * This signal is emitted when a random enemy should be spawned.
     */
    void spawnRandomEnemySignal();

    /**
     * @brief spawnFormationSignal
     * This signal is emitted when a formation should be spawned.
     */
    void spawnFormationSignal();

    /**
     * @brief spawnMiniBossSignal
     * This signal is emitted when a mini boss should be spawned.
     */
    void spawnMiniBossSignal();

    /**
     * @brief spawnBossSignal
     * This signal is emitted when a boss should be spawned.
     */
    void spawnBossSignal();

    /**
     * @brief setPlayerScoreSignal
     * This signal is emitted when the player score should be updated.
     * @param playerScore - the new player score
     */
    void setPlayerScoreSignal(const int &playerScore);

//    void togglePauseSignal();

/**
 * @brief enemyDiedSignal - This signal is emitted when an enemy dies.
 * It is used to update the score based on the enemy that died.
 * @param enemyShipClass - the ship class of the enemy that died
 */
    void enemyDiedSignal(settings::ShipClass enemyShipClass);


  public slots:

    /**
     * @brief setPlayerScore
     * @param playerScore - the new player score
     */
    void setPlayerScore(const int &playerScore);

    /**
     * @brief spawnRandomHandler
     * This slot is called when a random enemy should be spawned.
     */
    void spawnRandomHandler();

    /**
     * @brief spawnFormationHandler
     * This slot is called when a formation should be spawned.
     */
    void spawnFormationHandler();

    /**
     * @brief spawnMiniBossHandler
     * This slot is called when a mini boss should be spawned.
     */
    void spawnMiniBossHandler();

    /**
     * @brief spawnBossHandler
     * This slot is called when a boss should be spawned.
     */
    void spawnBossHandler();

    /**
     * @brief enemyDiedHandler
     * This slot is called when an enemy dies.
     * It is used to update the score based on the enemy that died.
     * @param enemyShipClass - the ship class of the enemy that died
     */
    void enemyDiedHandler(settings::ShipClass enemyShipClass);

  private:
    int m_playerScore;
    QList<Enemy*> m_enemies;
    int m_formationSpawnThreshold;
    int m_miniBossSpawnThreshold;
    int m_bossSpawnThreshold;
    bool m_waitSpecialSpawn = false;

    QTimer *m_randomSpawnTimer;
    QTimer *m_formationSpawnTimer;
    QTimer *m_miniBossSpawnTimer;
    QTimer *m_bossSpawnTimer;
    QGraphicsScene *m_scene;

    /**
     * @brief randomPosX
     * @details This function returns a random x position for spawning an enemy
     * within the x bounds of the scene.
     * @return a random x position for spawning an enemy
     */
    int randomPosX() const;
  };
} // space_pewpew

#endif //METODIK_INVADERS2_SPAWNHANDLER_H
