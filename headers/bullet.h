#ifndef METODIK_INVADERS2_BULLET_H
#define METODIK_INVADERS2_BULLET_H


#include <QGraphicsPixmapItem>
#include <QObject>
#include "settings.h"

namespace space_pewpew {
  /**
   * @brief The Bullet class
   * @details This class is used to create bullets that are fired by the player and the enemies.
   * The bullets are created by the player and the enemies and are added to the scene.
   *
   */
  class Bullet : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  public:
    /**
     * @brief Bullet
     * @details This constructor creates a bullet with the given parameters.
     * @param ownerType The owner of the bullet. This is used to determine if the bullet is fired by the player or an enemy.
     * @param bMoveStep The speed of the bullet. This is used to determine how many pixels the bullet moves each time it is moved.
     * @param ammoType The type of ammo. This is used to determine the type of bullet that is fired.
     * @param dmgLevel The damage level of the bullet. This is used to determine the damage that the bullet does.
     * @param parent The parent of the bullet.
     */
    Bullet(settings::Faction ownerType = settings::Faction::Player,
           int bMoveStep = static_cast<int>(settings::MoveSteps::Move01),
           settings::AmmoType ammoType = settings::AmmoType::TypeLaser,
           settings::AmmoDmgLvl dmgLevel = settings::AmmoDmgLvl::Dmg10,
           QObject *parent = nullptr);

    ~Bullet() = default;

    /**
     * @brief getOwner
     * @details This function returns the owner of the bullet.
     * @return The owner of the bullet.
     */
    settings::Faction getOwner();

  private:
    settings::Faction myOwnersType;
    settings::AmmoType m_ammoType;
    settings::AmmoDmgLvl m_dmgLevel;
    QTimer *updateTimer;
    int m_bMoveStep;

  private slots:

    /**
     * @brief move
     * @details This function moves the bullet.
     */
    void move();

  public slots:
    /**
     * @brief getDamage
     * @details This function returns the damage that the bullet does.
     * @return The damage that the bullet does.
     */
    int getDamage();

  };

} // namespace space_pewpew
#endif //METODIK_INVADERS2_BULLET_H