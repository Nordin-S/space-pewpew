//
// Created by nordi on 1/30/2023.
//

#include "headers/player.h"
#include "headers/bullet.h"

namespace space_pewpew {
  Player::Player(int moveStep, int moveUpdate, int health, int fireRate,
                 int bulletMoveStep,
                 settings::AmmoType ammoType,
                 settings::AmmoDmgLvl dmgLevel,
                 settings::Faction faction,
                 settings::ShipClass shipClass,
                 settings::ShipTypes shipType,
                 QObject *parent)
    : SpaceCraft(moveStep, moveUpdate, health, fireRate, bulletMoveStep,
                 ammoType, dmgLevel, faction,
                 shipClass, shipType, parent) {
    setTimers();
  }

  settings::Faction Player::getFaction() {
    return m_faction;
  }

  void Player::move() {
    if (xDirection < 0) {
      if (pos().x() > pixmap().width() / 2)
        setPos(pos().x() - m_moveStep, y());
    }
    if (xDirection > 0) {
      if (pos().x() + pixmap().width() <
          scene()->sceneRect().width() - pixmap().width() / 2)
        setPos(pos().x() + m_moveStep, y());
    }
    if (yDirection < 0) {
      m_animState = settings::AnimationStates::Accelerating;
      if (pos().y() > 0)
        setPos(pos().x(), y() - m_moveStep);
    }
    if (yDirection > 0) {
      m_animState = settings::AnimationStates::Decelerating;
      if (pos().y() + pixmap().height() <
          scene()->sceneRect().height() - pixmap().height() / 2)
        setPos(pos().x(), y() + m_moveStep);
    }
  }

  void Player::setDirectionX(int xDirection) {
    this->xDirection = xDirection;
  }

  void Player::setDirectionY(int yDirection) {
    this->yDirection = yDirection;
  }

  void Player::updatePosition() {
    if (xDirection != 0 || yDirection != 0) {
      move();
    }
    m_animState = settings::AnimationStates::Cruising;
    checkCollision();
  }

  void Player::setShooting(bool shooting) {
    m_isShooting = shooting;
  }

  void Player::shoot() {
    if (m_health <= 0 || !m_isShooting)
      return;
    // create bullets and add to gameScene
    Bullet *bullet = new Bullet(settings::Faction::Player,
                                m_bulletMoveStep,
                                m_ammoType,
                                m_dmgLevel,
                                this);

    int shipsCenterX = x() + pixmap().width() / 2;

    //TODO: Resize functionality for bullets?
//    bullet->setPixmap(bullet->pixmap().scaled(bullet->pixmap().size().width() * 0.25,
//                            bullet->pixmap().size().height() * 0.25));
    int bulletsCenterX = bullet->boundingRect().width() / 2;

    bullet->setPos(shipsCenterX - bulletsCenterX, y());
    scene()->addItem(bullet);
    emit fireBulletSignal();
  }

  int Player::getHealth() {
    return m_health;
  }

  void Player::setHealth(int health) {
    m_health = health;
  }

  settings::ShipTypes Player::getShipType() {
    return m_shipType;
  }

  settings::ShipClass Player::getShipClass() {
    return m_shipClass;
  }
} // space_pewpew