#include "headers/backgroundmusic.h"

#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

namespace space_pewpew {
  BackgroundMusic::BackgroundMusic(QObject *parent)
    : QObject(parent) {
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput;
    player->setAudioOutput(audioOutput);
    player->audioOutput()->setVolume(0.25f);
    //TODO: background music douse not seem to loop
    player->setLoops(QMediaPlayer::Infinite);
    // loop the music
    connect(player, &QMediaPlayer::mediaStatusChanged, [this](QMediaPlayer::MediaStatus status) {
      // play again if the music has ended
      if (status == QMediaPlayer::EndOfMedia) {
        player->play();
      }
    });
    player->play();
  }

  void BackgroundMusic::play() {
    player->play();
  }

  void BackgroundMusic::stop() {
    player->stop();
  }

  void BackgroundMusic::setVolume(int volume) {
    player->audioOutput()->setVolume(volume);
  }

  BackgroundMusic::~BackgroundMusic() {
    delete audioOutput;
    delete player;
  }

  void BackgroundMusic::setMusicPath(QString songPath) {
    player->setSource(QUrl(songPath));
  }
} // namespace space_pewpew
