//
// Created by nordi on 2/9/2023.
//

#ifndef METODIK_INVADERS2_SCENEMAKER_H
#define METODIK_INVADERS2_SCENEMAKER_H

#include <QGraphicsScene>
#include "background.h"

namespace space_pewpew {

  /**
   * @brief The SceneMaker class
   * This class is the base class for all scenes in the game.
   * It contains a list of Backgrounds, which are the background
   * images that are displayed in the scene.
   * It also contains the buildScene() method, which is called
   * when the scene is activated.
   */
  class SceneMaker : public QGraphicsScene {
      Q_OBJECT
  public:
    /**
     * @brief SceneMaker
     * @param parent
     */
    explicit SceneMaker(QObject *parent = nullptr) : QGraphicsScene(parent) {}

    /**
     * @brief addBackground
     * @param background
     * Adds a background to the scene.
     */
    virtual void addBackground(Background *background) {
      m_backgrounds.append(background);
      for (auto &instance : background->getInstances()) {
        addItem(instance);
      }
    }

    /**
     * @brief buildScene
     * This method is called when the scene is activated.
     * It should be overridden by subclasses.
     */
    virtual void buildScene() = 0;

    /**
     * @brief activate
     * This method is called when the scene is activated.
     * It starts the timers of all the backgrounds.
     */
    virtual void activate() {
      for (auto &background : m_backgrounds) {
        background->startTimer();
      }
    }

    /**
     * @brief deactivate
     * This method is called when the scene is deactivated.
     * It stops the timers of all the backgrounds.
     */
    virtual void deactivate() {
      for (auto &background : m_backgrounds) {
        background->stopTimer();
      }
    }

    /**
     * @brief ~SceneMaker
     * Deletes all the backgrounds.
     */
    virtual ~SceneMaker() {
      for (auto &background : m_backgrounds) {
        delete background;
      }
    }

  protected:
    QList<Background *> m_backgrounds;
  };

} // space_pewpew

#endif //METODIK_INVADERS2_SCENEMAKER_H
