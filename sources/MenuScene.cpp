//
// Created by nordi on 2/6/2023.
//

#include "headers/MenuScene.h"
#include "headers/game.h"
#include "headers/background.h"

namespace space_pewpew {

  MenuScene::MenuScene(QObject *parent) : SceneMaker(parent) {}

  void MenuScene::buildScene() {
    addItem(m_title);
    // loop through backgrounds list and add them to the scene
    for (auto &background: m_backgrounds) {
      addItem(background);
    }
    // loop through buttons list and add them to the scene
    for (auto &button: m_buttons) {
      addItem(button);
    }

    // Determine the scene rect
    QRect sceneRect = this->sceneRect().toRect();

    // Calculate the center of the screen
    qreal centerX = sceneRect.width() / 2;
    qreal centerY = sceneRect.height() / 2;

    // Set the position for each item TODO: make this constant
    int margin = 20;

    int y = centerY - m_title->boundingRect().height();
    m_title->setPos(centerX - m_title->boundingRect().width() / 2, y);

    y += m_title->boundingRect().height();

    // loop through buttons list and set their position
    for (auto &button: m_buttons) {
      button->setPos(centerX - button->boundingRect().width() / 2, y + margin);
      y += button->boundingRect().height();
    }
  }

  void MenuScene::setTitleImg(QString title) {
    m_title = new QGraphicsPixmapItem(QPixmap(title));
  }

  void MenuScene::activate() {
    // call base class activate
    SceneMaker::activate();
    // do other stuff if needed
  }

  void MenuScene::deactivate() {
    // call base class deactivate
    SceneMaker::deactivate();
    // do other stuff if needed
  }

  void MenuScene::addButton(MenuButton *button) {
    m_buttons.append(button);
  }

  MenuScene::~MenuScene() {
    delete m_title;
  }

} // space_pewpew