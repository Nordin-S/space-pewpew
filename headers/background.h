#ifndef METODIK_INVADERS2_BACKGROUND_H
#define METODIK_INVADERS2_BACKGROUND_H

#include <QGraphicsRectItem>
#include "BackgroundPixmapItem.h"

namespace space_pewpew {
  /**
   * @brief The Background class
   * @details This class is responsible for the background of the game.
   * It is a QObject because it needs to be able to connect to a QTimer.
   * It is a QGraphicsPixmapItem because it needs to be able to be added to a
   * QGraphicsScene.
   */
  class Background : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  public:
    /**
     * @brief Background
     * @details Creates a new Background object.
     * @param speed
     * @param updateSpeed
     * @param imgPaths
     * @param parent
     */
    Background(int speed, int updateSpeed, QList<QString> imgPaths,
               QObject *parent = nullptr);

    /**
     * @brief startTimer
     * Starts the timer that moves the background.
     */
    void startTimer();
    /**
     * @brief stopTimer
     * Stops the timer that moves the background.
     */
    void stopTimer();

    /**
     * @brief getInstances
     * @return A list of the background instances of the this background
     * that are part of the continuous background loop.
     *
     */
    QList<BackgroundPixmapItem *> getInstances() const;
    virtual ~Background() override = default;


  public slots:

    /**
     * @brief Background::move
     * Moves the background down by m_speed.
     * If the background has moved off the screen, it is moved back to the top.
     */
    void move();

  private:
    QTimer *m_backgroundTimer;
    int m_speed;
    int m_updateSpeed;
    QPixmap m_image;
    QList<QString> m_images;
    QList<BackgroundPixmapItem *> m_instances;

  };
} // namespace space_pewpew
#endif //METODIK_INVADERS2_BACKGROUND_H
