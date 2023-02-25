//
// Created by nordi on 1/29/2023.
//

#ifndef METODIK_INVADERS2_GAMEOBJECT_H
#define METODIK_INVADERS2_GAMEOBJECT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "settings.h"

namespace space_pewpew {
  /**
   * @brief The GameObject class is the base class for all game objects.
   * It contains the basic functionality for all game objects.
   */
  class GameObject : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  public:
    /**
     * @brief GameObject constructor
     * @param moveStep the step size for the move function
     * @param moveUpdate the update interval for the move function
     * @param parent the parent object
     */
    explicit GameObject(int moveStep = 0, int moveUpdate = 0, QObject *parent = nullptr);

    ~GameObject() = default;

    /**
     * @brief setStartPosition sets the start position of the object
     * @param xPos the x position
     * @param yPos the y position
     */
    virtual void setStartPosition(qreal xPos, qreal yPos);

  protected:
    int m_moveStep;
    int m_moveUpdate;
    QTimer *updateTimer;
    QTimer *animationTimer;

  public slots:

    /**
     * @brief move moves the object
     */
    virtual void move() = 0;

    /**
     * @brief updatePosition updates the position of the object
     */
    virtual void updatePosition() = 0;

    /**
     * @brief updateAnimation updates the animation of the object
     */
    virtual void pauseState(bool isPaused) = 0;

  };


} // space_pewpew

#endif //METODIK_INVADERS2_GAMEOBJECT_H
