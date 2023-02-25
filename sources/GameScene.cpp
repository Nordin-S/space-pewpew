//
// Created by nordi on 2/9/2023.
//

#include <QObject>
#include "headers/GameScene.h"
#include "headers/GameObject.h"

namespace space_pewpew {
  GameScene::GameScene(QObject *parent) : SceneMaker(parent) {}

  void GameScene::buildScene() {
    m_healthBar = new QGraphicsPixmapItem(
      QPixmap(":/resources/ui/health100.png"));
    m_scoreBar = new QGraphicsPixmapItem(QPixmap(":/resources/ui/score.png"));
    m_scoreText = new QGraphicsTextItem("0");
    int edgeOffsetX = 10;
    int edgeOffsetY = 10;
    int fontPointSize = 32;
    int scoreTextOffsetX = 30;
    int scoreTextOffsetY = m_scoreBar->boundingRect().height() - fontPointSize - 30;

    QFont font("Monospace", fontPointSize, QFont::Bold);
    m_scoreText->setFont(font);
    m_scoreText->setDefaultTextColor(Qt::white);
    // bottom right corner
    m_healthBar->setPos(edgeOffsetX,
                        height() - m_healthBar->boundingRect().height() -
                        edgeOffsetY);
    m_scoreBar->setPos(
      width() - m_scoreBar->boundingRect().width() - edgeOffsetX,
      height() - m_scoreBar->boundingRect().height() - edgeOffsetY);
    m_scoreText->setPos(m_scoreBar->pos().x() + scoreTextOffsetX,
                        m_scoreBar->pos().y() + scoreTextOffsetY);
    addItem(m_healthBar);
    addItem(m_scoreBar);
    addItem(m_scoreText);
  }

  void GameScene::activate() {
    // call base class activate
    SceneMaker::activate();
    // do other stuff if needed
    for (auto &item : items()) {
      auto *pauseable = dynamic_cast<GameObject *>(item);
      if (pauseable) {
        pauseable->pauseState(false);
      }
    }
  }

  void GameScene::deactivate() {
    // call base class deactivate
    SceneMaker::deactivate();
    // do other stuff if needed
    // loop through all items in scene and set pauseState
    for (auto &item : items()) {
      auto *pauseable = dynamic_cast<GameObject *>(item);
      if (pauseable) {
        pauseable->pauseState(true);
      }
    }
  }

  GameScene::~GameScene() {
    delete m_healthBar;
    delete m_scoreBar;
    delete m_scoreText;
    for (auto &item : items()) {
        delete item;
    }
  }

  void GameScene::updateScore(int score) {
    m_scoreText->setPlainText(QString::number(score));
  }

  void GameScene::updateHealth(int health) {
    QString newHealthImg;
    if(health >= 100) {
      newHealthImg = ":/resources/ui/health100.png";
    } else if(health >= 90) {
      newHealthImg = ":/resources/ui/health90.png";
    } else if(health >= 80) {
      newHealthImg = ":/resources/ui/health80.png";
    } else if(health >= 70) {
      newHealthImg = ":/resources/ui/health70.png";
    } else if(health >= 60) {
      newHealthImg = ":/resources/ui/health60.png";
    } else if(health >= 50) {
      newHealthImg = ":/resources/ui/health50.png";
    } else if(health >= 40) {
      newHealthImg = ":/resources/ui/health40.png";
    } else if(health >= 30) {
      newHealthImg = ":/resources/ui/health30.png";
    } else if(health >= 20) {
      newHealthImg = ":/resources/ui/health20.png";
    } else if(health >= 10) {
      newHealthImg = ":/resources/ui/health10.png";
    } else {
      newHealthImg = ":/resources/ui/health0.png";
    }
    m_healthBar->setPixmap(QPixmap(newHealthImg));
  }

} // space_pewpew