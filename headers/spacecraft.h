#ifndef METODIK_INVADERS2_SPACECRAFT_H
#define METODIK_INVADERS2_SPACECRAFT_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QPropertyAnimation>
#include <QGraphicsScene>
#include "settings.h"
#include "GameObject.h"
#include "SfxHandler.h"
#include "bullet.h"

namespace space_pewpew {
  class SpaceCraft : public GameObject {
  Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  public:
    explicit SpaceCraft(int moveStep = settings::ShipSpeeds::PlayerSpeed,
                        int moveUpdate = settings::UpdateMs::UMs300,
                        int health = settings::Healths::PlayerHealth,
                        int fireRate = settings::UpdateMs::UMs01,
                        int bulletMoveStep = settings::MoveSteps::Move01,
                        settings::AmmoType ammoType = settings::AmmoType::TypeLaser,
                        settings::AmmoDmgLvl dmgLevel = settings::AmmoDmgLvl::Dmg10,
                        settings::Faction faction = settings::Faction::Player,
                        settings::ShipClass shipClass = settings::ShipClass::Fighter,
                        settings::ShipTypes shipType = settings::ShipTypes::Striker,
                        QObject *parent = nullptr);

    virtual ~SpaceCraft();

    /**
     * @brief move
     * @details This method is to set connect timers for updateposition and shoot
     * and set the ship animations.
     */
    void setTimers();

    /**
     * @brief setShipAnimations
     * @details This method is used to set the ship animations.
     * @param shipType The ship type of the ship.
     */
    void setShipAnimations(settings::ShipTypes shipType);

    /**
     * @brief getFaction
     * @details This method is used to get the faction of the ship.
     * @return The faction of the ship.
     */
    virtual settings::Faction getFaction() = 0;

    /**
     * @brief getShipType
     * @details This method is used to get the ship type of the ship.
     * @return The ship type.
     */
    virtual settings::ShipTypes getShipType() = 0;

    /**
     * @brief getShipClass
     * @details This method is used to get the ship class of the ship.
     * @return The ship class.
     */
    virtual settings::ShipClass getShipClass() = 0;

    /**
     * @brief getAnimState
     * @details This method is used to get the animation state of the ship.
     * @return The animation state.
     */
    settings::AnimationStates getAnimState();

    /**
     * @brief checkCollision
     * @details This method is used to check if the ship is colliding with another object.
     */
    virtual void checkCollision();

  protected:
    int m_health;
    int m_fireRate;
    int m_bulletMoveStep;
    settings::Faction m_faction;
    settings::ShipClass m_shipClass;
    settings::ShipTypes m_shipType;
    settings::AmmoType m_ammoType;
    settings::AmmoDmgLvl m_dmgLevel;
    settings::AnimationStates m_animState = settings::AnimationStates::Cruising;
    QList<QString> m_shipCrusingAnims;
    QList<QString> m_shipAcceleratingAnims;
    QList<QString> m_shipDeceleratingAnims;
    QList<QString> m_shipExplodingAnims;
    QTimer *m_shootTimer;
    SfxHandler *m_sfxHandler;
    bool m_isShooting = false;
    int m_animIndex = 0;

  signals:

    /**
     * @brief fireBulletSignal
     * @details This signal is used to fire a bullet.
     */
    void fireBulletSignal();

    /**
     * @brief bulletHitSignal
     * @details This signal is used to notify that a bullet has hit a ship.
     */
    void bulletHitSignal();

    /**
     * @brief explodingSignal
     * @details This signal is used to notify that the ship is exploding.
     */
    void explodingSignal();

    /**
     * @brief playerDiedSignal
     * @details This signal is used to notify that the player has died.
     */
    void playerDiedSignal();

    /**
     * @brief enemyDiedSignal
     * @details This signal is used to notify that an enemy has died.
     * @param enemyClass The class of the enemy that died.
     */
    void enemyDiedSignal(settings::ShipClass enemyClass);

  public slots:

    /**
     * @brief updatePosition
     * @details This method is used to update the position of the ship.
     */
    virtual void updatePosition() = 0;

    /**
     * @brief move
     * @details This method is used to move the ship.
     */
    virtual void move() = 0;

    /**
     * @brief shoot
     * @details This method is used to create a bullet and add it to the scene.
     */
    virtual void shoot() = 0;

    /**
     * @brief animateShip
     * @details This method is used to animate the ship.
     */
    void animateShip();

//    virtual void handlePlayerDied();
//    virtual void handleEnemyDied();

    /**
     * @brief pauseState
     * @details This method is used to pause the ship actions.
     * @param isPaused
     */
    void pauseState(bool isPaused) override;

  };

} // namespace space_pewpew
#endif //METODIK_INVADERS2_SPACECRAFT_H
