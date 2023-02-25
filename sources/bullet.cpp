#include <QTimer>
#include <QGraphicsScene>
#include "headers/bullet.h"
#include "headers/spacecraft.h"

namespace space_pewpew {
  Bullet::Bullet(settings::Faction ownerType, int bMoveStep,
                 settings::AmmoType ammoType,
                 settings::AmmoDmgLvl dmgLevel,
                 QObject *parent)
    : myOwnersType(ownerType), m_bMoveStep(bMoveStep), m_ammoType(ammoType),
      m_dmgLevel(dmgLevel), QObject{parent} {

    if (m_ammoType == settings::AmmoType::TypeLaser)
      setPixmap(
        QPixmap(settings::ammoLasers[rand() % settings::ammoLasers.size()]));
    if (m_ammoType == settings::AmmoType::TypeMissile)//TODO: add missile
      setPixmap(QPixmap(
        settings::ammoMissiles[rand() % settings::ammoMissiles.size()]));

    QTimer *updateTimer = new QTimer();
    connect(updateTimer, SIGNAL(timeout()), this, SLOT(move()));
    updateTimer->start(bMoveStep * 30 );//TODO: maybe multiply by owners fire rate
  }

  settings::Faction Bullet::getOwner() {
    return myOwnersType;
  }

  void Bullet::move() {
    // player bullet
    if (myOwnersType == settings::Faction::Player)
      setPos(x(), y() - m_bMoveStep * pixmap().height());

    // enemy bullet
    if (myOwnersType == settings::Faction::Enemy)
      setPos(x(), y() + m_bMoveStep * pixmap().height());

//    if(pos().y() + pixmap().height() < parentObject()->boundingRect().top() || pos().y() > parentObject()->boundingRect().height()){
////        gameScene()->removeItem(this);
//        qDebug() << "test";
//        this->deleteLater();
//    }

//    if (y() < 0 || y() > 1000) {
////        gameScene()->removeItem(this);
//        this->deleteLater();
//    }
  }

  int Bullet::getDamage() {
    return m_dmgLevel;
  }

} // space_pewpew