// copyrigth: Nordin Suleimani 14/2/2023

#ifndef METODIK_INVADERS2_MENUSCENE_H
#define METODIK_INVADERS2_MENUSCENE_H

#include <QGraphicsScene>
#include "MenuButton.h"
#include "background.h"
#include "SceneMaker.h"

namespace space_pewpew {

  /**
   * @Author: Nordin Suleimani 14/2/2023
   * @file MenuScene.h
   * @class MenuScene
   * @brief The MenuScene class
   * @details This class is responsible for creating the main menu scene.
   * It is a subclass of SceneMaker.
   */
  class MenuScene : public SceneMaker {
  Q_OBJECT
  public:
    /**
     * @brief MenuScene
     * @param parent
     */
    explicit MenuScene(QObject *parent = nullptr);

    /**
     * @brief setTitleImg
     * @param title
     */
    void setTitleImg(QString title);

    /**
     * @brief addButton
     * @param button
     */
    void addButton(MenuButton *button);

    /**
     * @brief buildScene builds the scene and adds all the items to it
     */
    void buildScene() override;

    /**
     * @brief activate the scene and makes all the items move
     */
    void activate() override;

    /**
     * @brief deactivate the scene and stops all the items from moving
     */
    void deactivate() override;

    ~MenuScene() override;

  private:
    QGraphicsPixmapItem *m_title{};
    QList<MenuButton *> m_buttons;
  };
} // space_pewpew
#endif //METODIK_INVADERS2_MENUSCENE_H
