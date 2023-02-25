#include "headers/enemy.h"
#include "headers/bullet.h"

namespace space_pewpew {
  Enemy::Enemy(int moveStep, int moveUpdate,
               int health, int fireRate, int bulletMoveStep,
               settings::AmmoType ammoType,
               settings::AmmoDmgLvl dmgLevel,
               settings::Faction faction,
               settings::ShipClass shipClass,
               settings::ShipTypes shipType,
               QGraphicsScene *scene,
               QObject *parent)
    : SpaceCraft(moveStep, moveUpdate, health, fireRate, bulletMoveStep,
                 ammoType, dmgLevel,
                 faction, shipClass, shipType, parent),
      m_scene(scene) {
    setTimers();
  }

  void Enemy::updatePosition() {
    move();
    checkCollision();
  }

  void Enemy::move() {
    // choose m_moveStep based on ship type
    setPos(x(), y() + m_moveStep);
    if (pos().y() > m_scene->height()) {
      emit escaped();
      m_scene->removeItem(this);
//      delete this;
      deleteLater();
    }
  }

  void Enemy::shoot() {
    int randomNum = rand() % 200 + 1;
    if (randomNum <= 5 && m_scene) {
      // create bullets and add to gameScene
      Bullet *bullet = new Bullet(settings::Faction::Enemy,
                                  m_bulletMoveStep,
                                  m_ammoType,
                                  m_dmgLevel,
                                  this);
      int shipsCenterX = x() + pixmap().width() / 2;
      int bulletsCenterX = bullet->pixmap().width() / 2;

      bullet->setPos(shipsCenterX - bulletsCenterX, y());
      scene()->addItem(bullet);
      emit fireBulletSignal();
    }
  }

  settings::Faction Enemy::getFaction() {
    return m_faction;
  }

  settings::ShipTypes Enemy::getShipType() {
    return m_shipType;
  }

  settings::ShipClass Enemy::getShipClass() {
    return m_shipClass;
  }

} // namespace space_pewpew