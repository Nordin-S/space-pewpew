//
// Created by nordi on 1/30/2023.
//

#ifndef METODIK_INVADERS2_ENEMY_H
#define METODIK_INVADERS2_ENEMY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "settings.h"
#include "spacecraft.h"

namespace space_pewpew {
  /**
   * @brief The Enemy class
   * @details This class is used to create enemy ships.
   */
  class Enemy : public SpaceCraft {
  Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  private:
    QGraphicsScene *m_scene;
  public:
    /**
     * @brief Enemy
     * @details This constructor is used to create an enemy ship.
     * @param speed The speed of the enemy ship.
     * @param health The health of the enemy ship.
     * @param fireRate The fire rate of the enemy ship.
     * @param bulletMoveStep The bullet move step of the enemy ship.
     * @param ammoType The ammo type of the enemy ship.
     * @param dmgLevel The damage level of the bullet.
     * @param shipType The ship type of the enemy ship.
     * @param shipClass The enemy ship class of the enemy ship.
     * @param scene The scene of the enemy ship.
     * @param parent The parent of the enemy ship.
     */
    explicit Enemy(int speed = settings::ShipSpeeds::FighterSpeed,
                   int moveUpdate = settings::UpdateMs::UMs300,
                   int health = settings::Healths::FighterHealth,
                   int fireRate = settings::UpdateMs::UMs01,
                   int bulletMoveStep = settings::MoveSteps::Move01,
                   settings::AmmoType ammoType = settings::AmmoType::TypeLaser,
                   settings::AmmoDmgLvl dmgLevel = settings::AmmoDmgLvl::Dmg10,
                   settings::Faction faction = settings::Faction::Enemy,
                   settings::ShipClass shipClass = settings::ShipClass::Fighter,
                   settings::ShipTypes shipType = settings::ShipTypes::Viper,
                   QGraphicsScene *scene = nullptr,
                   QObject *parent = nullptr);

    ~Enemy() = default;

    /**
     * @brief getFaction
     * @details This method is used to get the faction of the enemy ship.
     * @return The faction of the enemy ship.
     */
    settings::Faction getFaction() override;

    /**
     * @brief getShipClass
     * @details This method is used to get the ship class of the enemy ship.
     * @return The ship class of the enemy ship.
     */
    settings::ShipClass getShipClass() override;

    /**
     * @brief getShipType
     * @details This method is used to get the ship type of the enemy ship.
     * @return The ship type of the enemy ship.
     */
    settings::ShipTypes getShipType() override;

  public slots:

    /**
     * @brief updatePosition
     * @details This method is used to update the position of the enemy ship.
     */
    void updatePosition() override;

    /**
     * @brief move
     * @details This method is used to move the enemy ship.
     */
    void move() override;

    /**
     * @brief shoot
     * @details This method is used to shoot a bullet from the enemy ship.
     */
    void shoot() override;

  signals:

    /**
     * @brief escaped
     * @details This signal is emitted when the enemy ship has escaped.
     */
    void escaped();
  };

} // namespace space_pewpew
#endif //METODIK_INVADERS2_ENEMY_H