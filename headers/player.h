//
// Created by nordi on 1/30/2023.
//

#ifndef METODIK_INVADERS2_PLAYER_H
#define METODIK_INVADERS2_PLAYER_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include "settings.h"
#include "spacecraft.h"

namespace space_pewpew {
  /**
   * @brief The Player class
   * @details This class is used to create the player ship.
   */
  class Player : public SpaceCraft {
  Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)
  private:
    int xDirection = 0;
    int yDirection = 0;
  public:
    /**
     * @brief Player
     * @details This constructor is used to create the player ship.
     * @param moveStep The moveStep of the player ship.
     * @param health The health of the player ship.
     * @param fireRate The fire rate of the player ship.
     * @param bulletMoveStep The bullet move step of the player ship.
     * @param ammoType The ammo type of the player ship.
     * @param dmgLevel The damage level of the bullet.
     * @param shipType The ship type of the player ship.
     * @param parent The parent of the player ship.
     */
    explicit Player(int moveStep = settings::ShipSpeeds::FighterSpeed,
                    int moveUpdate = settings::UpdateMs::UMs300,
                    int health = settings::Healths::FighterHealth,
                    int fireRate = settings::UpdateMs::UMs01,
                    int bulletMoveStep = settings::MoveSteps::Move01,
                    settings::AmmoType ammoType = settings::AmmoType::TypeLaser,
                    settings::AmmoDmgLvl dmgLevel = settings::AmmoDmgLvl::Dmg10,
                    settings::Faction faction = settings::Faction::Player,
                    settings::ShipClass shipClass = settings::ShipClass::Fighter,
                    settings::ShipTypes shipType = settings::ShipTypes::Striker,
                    QObject *parent = nullptr);

    ~Player() = default;

    /**
     * @brief setDirectionX
     * @details This method is used to set the x direction of the ship.
     * @param xDirection The x direction of the player ship.
     */
    void setDirectionX(int xDirection);

    /**
     * @brief setDirectionY
     * @details This method is used to set the y direction of the ship.
     * @param yDirection The y direction of the player ship.
     */
    void setDirectionY(int yDirection);

    /**
     * @brief setShooting
     * @details This method is used to set the shooting state of the ship.
     * @param shooting The shooting state of the player ship.
     */
    void setShooting(bool shooting);

    /**
     * @brief getFaction This method is used to get the faction of the ship.
     * @return The faction of the player ship.
     */
    settings::Faction getFaction() override;

    /**
     * @brief getShipType This method is used to get the ship type of the ship.
     * @return The ship type of the player ship.
     */
    settings::ShipTypes getShipType() override;

    /**
     * @brief getShipClass This method is used to get the ship class of the ship.
     * @return
     */
    settings::ShipClass getShipClass() override;

    /**
     * @brief getHealth This method is used to get the health of the ship.
     * @return The health of the player ship.
     */
    int getHealth();

    /**
     * @brief setHealth This method is used to set the health of the ship.
     * @param health The health of the player ship.
     */
    void setHealth(int health);

  public slots:

    /**
     * @brief updatePosition This method is used to update the position of the ship.
     */
    void updatePosition() override;

    /**
     * @brief move This method is used to move the ship.
     */
    void move() override;

    /**
     * @brief shoot This method is used to shoot from the ship.
     * @note should be refactored to shoot based on pickup ammo type.
     */
    void shoot() override;

  };

} // namespace space_pewpew
#endif //METODIK_INVADERS2_PLAYER_H
