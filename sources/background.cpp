#include <QTimer>
#include <QGraphicsScene>
#include "headers/background.h"
#include "headers/BackgroundPixmapItem.h"

namespace space_pewpew {
  Background::Background(int speed, int updateSpeed, QList<QString> imgPaths,
                         QObject *parent)
    : QObject(parent), m_speed(speed), m_updateSpeed(updateSpeed),
      m_images(imgPaths) {
    const int NUM_IMAGES = 3; // TODO: two should be enough!?

    // Load the image
    if (m_images.size() > 1){
      // Load a random image if there are more than one
      m_image.load(m_images[rand() % m_images.size()]);
    } else {
      m_image.load(imgPaths[0]);
    }

    // Create the instances of the background, and set them up to be moved
    for (int i = 0; i < NUM_IMAGES; i++) {
      auto *instance = new BackgroundPixmapItem();
      instance->setPixmap(m_image);
      instance->setPos(0, -(i * m_image.height()));
      m_instances.append(instance);
      // Turn off collision detection for the pixmap item
      instance->setData(0, false);
    }

    m_backgroundTimer = new QTimer();
    connect(m_backgroundTimer, SIGNAL(timeout()), this, SLOT(move()));
  }

  void Background::move() {
    /* Move the background down and reset it if it goes out of the screen */
    for (int i = 0; i < m_instances.size(); i++) {
      m_instances[i]->setPos(0, m_instances[i]->y() + m_speed);
      if (m_instances[i]->y() > m_image.height()) {
        if (m_images.size() > 1) {
          m_image.load(m_images[rand() % m_images.size()]);
          m_instances[i]->setPixmap(m_image);
        }
        m_instances[i]->setPos(m_instances[i]->x(), -m_image.height());
      }
    }
  }

  void Background::startTimer() {
    m_backgroundTimer->start(m_updateSpeed);
  }

  void Background::stopTimer() {
    m_backgroundTimer->stop();
  }

  QList<BackgroundPixmapItem *> Background::getInstances() const {
    return m_instances;
  }
}