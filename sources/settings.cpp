#include <QMap>
#include <QDirIterator>
#include "headers/settings.h"

namespace space_pewpew {
  const QList<QString> settings::ammoLasers = {
    ":/resources/lasers/laserSmall01.png",
    ":/resources/lasers/laserSmall02.png",
    ":/resources/lasers/laserSmall03.png",
    ":/resources/lasers/laserSmall04.png",
    ":/resources/lasers/laserSmall05.png",
    ":/resources/lasers/laserSmall06.png",
    ":/resources/lasers/laserSmall07.png",
    ":/resources/lasers/laserSmall08.png",
    ":/resources/lasers/laserSmall09.png",
    ":/resources/lasers/laserSmall10.png"
  };

  const QList<QString> settings::ammoMissiles = {
    ":/resources/lasers/laserMedium21.png"
    ":/resources/lasers/laserMedium22.png",
    ":/resources/lasers/laserMedium23.png",
    ":/resources/lasers/laserMedium24.png",
    ":/resources/lasers/laserMedium25.png",
    ":/resources/lasers/laserMedium26.png",
    ":/resources/lasers/laserMedium27.png",
    ":/resources/lasers/laserMedium28.png",
    ":/resources/lasers/laserMedium29.png"
  };

  QList<QString> settings::getShipAnimation(settings::ShipTypes shipType,
                                            settings::AnimationStates animState) {

    QString shipTypeStr = settings::shipTypes.find(shipType)->second;
    QString animStateStr = settings::animationStates.find(animState)->second;
    QString path = ":/resources/ships/" + shipTypeStr +
                   "/" + animStateStr + "/";

    // TODO: refactor this to retrieve images for any path request
    QList<QString> animList;
    try {
      QDirIterator it(path, QDirIterator::Subdirectories);

      while (it.hasNext()) {
        it.next();
        if (it.fileInfo().isFile())
          animList.append(it.filePath());
      }
    } catch (std::exception &e) {
      qDebug() << "Error: " << e.what();
    } catch (...) {
      qDebug() << "Unknown error";
    }
    std::sort(animList.begin(), animList.end());
    return animList;
  }

  bool settings::randomBool() {
    return rand() > (RAND_MAX / 2);
  }
}