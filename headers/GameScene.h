//
// Created by nordi on 2/9/2023.
//

#ifndef METODIK_INVADERS2_GAMESCENE_H
#define METODIK_INVADERS2_GAMESCENE_H

#include <QObject>
#include "SceneMaker.h"

namespace space_pewpew {

  /**
   * @brief The GameScene class
   * This class is responsible for building the game scene.
   * It is a child of the SceneMaker class.
   */
  class GameScene : public SceneMaker {
    Q_OBJECT
  public:

    /**
     * @brief GameScene
     * @param parent
     */
    explicit GameScene(QObject *parent = nullptr);

    /**
     * @brief buildScene
     * This method builds the game scene.
     */
    void buildScene() override;

    /**
     * @brief activate
     * This method activates the game scene.
     */
    void activate() override;

    /**
     * @brief deactivate
     * This method deactivates the game scene.
     */
    void deactivate() override;

    ~GameScene() override;

  public slots:

    /**
     * @brief updateScore
     * This method updates the score.
     * @param score
     */
    void updateScore(int score);

    /**
     * @brief updateHealth
     * This method updates the health.
     * @param health
     */
    void updateHealth(int health);
  private:
//    QGraphicsPixmapItem *m_livesBar{}; // TODO: implement lives later
    QGraphicsPixmapItem *m_healthBar;
    QGraphicsPixmapItem *m_scoreBar;
    QGraphicsTextItem *m_scoreText;
  };
} // space_pewpew

#endif //METODIK_INVADERS2_GAMESCENE_H
