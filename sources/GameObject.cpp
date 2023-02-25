#include "headers/GameObject.h"

namespace space_pewpew {
  GameObject::GameObject(int moveStep, int moveUpdate, QObject *parent)
    : QObject(parent),
      m_moveStep(moveStep), m_moveUpdate(moveUpdate) {}


  void GameObject::setStartPosition(qreal xPos, qreal yPos) {
    // position based on center of pixmap
    this->setPos(xPos - pixmap().width() / 2,
                 yPos - pixmap().height() - pixmap().height() / 2);
  }
} // space_pewpew
