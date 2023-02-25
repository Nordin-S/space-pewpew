#include <QTimer>
#include <QGraphicsScene>
#include <QMovie>
#include <QTypeInfo>
#include "headers/GameObject.h"
#include "headers/spacecraft.h"
#include "headers/background.h"
#include "headers/bullet.h"

namespace space_pewpew {
  SpaceCraft::SpaceCraft(int moveStep,
                         int moveUpdate,
                         int health, int fireRate,
                         int bulletMoveStep,
                         settings::AmmoType ammoType,
                         settings::AmmoDmgLvl dmgLevel,
                         settings::Faction faction,
                         settings::ShipClass shipClass,
                         settings::ShipTypes shipType,
                         QObject *parent)
    : GameObject(moveStep, moveUpdate, parent), m_health(health),
      m_fireRate(fireRate),
      m_bulletMoveStep(bulletMoveStep), m_ammoType(ammoType),
      m_dmgLevel(dmgLevel),
      m_faction(faction),
      m_shipClass(shipClass),
      m_shipType(shipType) {

    setShipAnimations(m_shipType);
    m_sfxHandler = new SfxHandler();
    connect(this, &SpaceCraft::fireBulletSignal, m_sfxHandler,
            &SfxHandler::handleBulletFired);
    connect(this, &SpaceCraft::bulletHitSignal, m_sfxHandler,
            &SfxHandler::handleBulletHit);
    connect(this, &SpaceCraft::explodingSignal, m_sfxHandler,
            &SfxHandler::handleExplosion);
  }

  void SpaceCraft::checkCollision() {
    if (m_animState == settings::AnimationStates::Exploding) {
      return;
    }
    if (m_health <= 0) {
      if (getFaction() == settings::Faction::Enemy) {
        emit enemyDiedSignal(getShipClass());
        m_moveStep = m_moveStep / 2;
      } else {
        updateTimer->stop();
      }
      m_shootTimer->stop();
      m_animState = settings::AnimationStates::Exploding;
      emit explodingSignal();
      return;
    }

    QList<QGraphicsItem *> colliding_items = collidingItems();

    for (int i = 0; i < colliding_items.size(); ++i) {
      if (auto *ship = dynamic_cast<SpaceCraft *>(colliding_items[i])) {
        if (getFaction() == ship->getFaction() || ship->getAnimState() ==
                                                  settings::AnimationStates::Exploding) {
          continue;
        }
        m_health = 0;
      } else if (auto *bullet = dynamic_cast<Bullet *>(colliding_items[i])) {
        if (bullet->getOwner() != getFaction()) {
          m_health -= bullet->getDamage();
          emit bulletHitSignal();
          if(bullet && scene()) {
            scene()->removeItem(bullet);
          }
        }
      }
    }
  }

  void SpaceCraft::setShipAnimations(settings::ShipTypes shipType) {
    m_shipType = shipType;
    m_shipCrusingAnims = settings::getShipAnimation(m_shipType,
                                                    settings::AnimationStates::Cruising);
    m_shipAcceleratingAnims = settings::getShipAnimation(m_shipType,
                                                         settings::AnimationStates::Accelerating);
    m_shipDeceleratingAnims = settings::getShipAnimation(m_shipType,
                                                         settings::AnimationStates::Decelerating);
    m_shipExplodingAnims = settings::getShipAnimation(m_shipType,
                                                      settings::AnimationStates::Exploding);
  }

  void SpaceCraft::animateShip() {
    switch (m_animState) {
      case settings::AnimationStates::Cruising:
        if (m_animIndex >= m_shipCrusingAnims.size()) {
          m_animIndex = 0;
        }
        setPixmap(QPixmap(m_shipCrusingAnims[m_animIndex]));
        m_animIndex++;
        break;
      case settings::AnimationStates::Accelerating:
        if (m_animIndex >= m_shipAcceleratingAnims.size()) {
          m_animIndex = 0;
        }
        setPixmap(QPixmap(m_shipAcceleratingAnims[m_animIndex]));
        m_animIndex++;
        break;
      case settings::AnimationStates::Decelerating:
        if (m_animIndex >= m_shipDeceleratingAnims.size()) {
          m_animIndex = 0;
        }
        setPixmap(QPixmap(m_shipDeceleratingAnims[m_animIndex]));
        m_animIndex++;
        break;
      case settings::AnimationStates::Exploding:
        m_animIndex++;
        if (m_animIndex >= m_shipExplodingAnims.size()) {
          animationTimer->stop();
//          scene()->removeItem(this);
          return;
        }
        setPixmap(QPixmap(m_shipExplodingAnims[m_animIndex]));
        break;
    }
  }

  void SpaceCraft::pauseState(bool isPaused) {
    if (isPaused) {
      updateTimer->stop();
      m_shootTimer->stop();
      animationTimer->stop();
    } else {
      updateTimer->start(m_moveUpdate);
      m_shootTimer->start(m_fireRate);
      animationTimer->start(100);
    }
  }

  settings::AnimationStates SpaceCraft::getAnimState() {
    return m_animState;
  }

  SpaceCraft::~SpaceCraft() {
    delete m_sfxHandler;
    delete animationTimer;
    delete m_shootTimer;
    delete updateTimer;
  }

  void SpaceCraft::setTimers() {
    // connect checkCollision() slot to games updatePosition updateTimer
    updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(updatePosition()));
    updateTimer->start(m_moveUpdate);

    m_shootTimer = new QTimer();
    connect(m_shootTimer, SIGNAL(timeout()), this, SLOT(shoot()));
    m_shootTimer->start(m_fireRate);

    animationTimer = new QTimer();
    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animateShip()));
    animationTimer->start(100);
  }

} // namespace space_pewpew
