#ifndef METODIK_INVADERS2_BACKGROUNDMUSIC_H
#define METODIK_INVADERS2_BACKGROUNDMUSIC_H

#include <QMediaPlayer>

namespace space_pewpew {
  /**
   * @brief The BackgroundMusic class
   * @details This class is responsible for playing the background music.
   * It is a QObject because it needs to be able to connect to a QTimer.
   */
  class BackgroundMusic : public QObject {
  Q_OBJECT
  public:
    /**
     * @brief BackgroundMusic
     * @details Creates a new BackgroundMusic object.
     * @param parent
     */
    explicit BackgroundMusic(QObject *parent = nullptr);

    ~BackgroundMusic();

  public slots:

    /**
     * @brief BackgroundMusic::play
     * Plays the background music.
     */
    void play();

    /**
     * @brief BackgroundMusic::stop
     * Stops the background music.
     */
    void stop();

    /**
     * @brief BackgroundMusic::setVolume
     * @param volume
     * Sets the volume of the background music.
     */
    void setVolume(int volume);

    /**
     * @brief BackgroundMusic::setMusicPath
     * @param songPath
     * Sets the path to the music file.
     */
    void setMusicPath(QString songPath);

  private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    QString m_songPath;
  };

} // namespace space_pewpew
#endif //METODIK_INVADERS2_BACKGROUNDMUSIC_H