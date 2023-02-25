//
// Created by nordi on 1/30/2023.
//
#ifndef METODIK_INVADERS2_SFXHANDLER_H
#define METODIK_INVADERS2_SFXHANDLER_H

#include <QList>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>
#include <QObject>

namespace space_pewpew {

  /**
   * @brief The SfxHandler class
   * Handles all sound effects in the game
   */
  class SfxHandler : public QObject {
  Q_OBJECT

  public:

    /**
     * @brief SfxHandler
     * @param parent
     */
    SfxHandler();

    ~SfxHandler();

    /**
     * @brief playSound
     * @param soundFilePath
     */
    void playSound(const QString &soundFilePath);

  private:
//    QAudioOutput *audioOutput;
    QList<QMediaPlayer *> m_sounds;

  signals:

    /**
     * @brief bulletFired
     */
    void bulletFired();

    /**
     * @brief bulletHit
     */
    void bulletHit();

    /**
     * @brief explosion
     */
    void explosion();

    /**
     * @brief miscSFX
     */
    void miscSFX();

  public slots:

    /**
     * @brief handleBulletFired
     */
    void handleBulletFired() {//TODO: needs to retrieve sound path from ammotype
      playSound("qrc:/resources/sfx/sfx_laser1.wav");
    }

    /**
     * @brief handleBulletHit
     */
    void handleBulletHit() {
      QString random = QString::number(rand() % 3 + 1);
      QString path = "qrc:/resources/sfx/sfx_hit0" + random + ".wav";
      playSound(path);
    }

    /**
     * @brief handleExplosion
     */
    void handleExplosion() {
      QString random = QString::number(rand() % 4 + 1);
      QString path = "qrc:/resources/sfx/sfx_explosion0" + random + ".mp3";
      playSound(path);
    }

    //TODO: add more sfx
//    void handleMiscSFX() { playSound("qrc:/resources/sfx/sfx_laser1.wav"); }
  };

} // space_pewpew

#endif //METODIK_INVADERS2_SFXHANDLER_H
