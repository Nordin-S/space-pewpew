//
// Created by nordi on 2/7/2023.
//

#ifndef METODIK_INVADERS2_MENUBUTTON_H
#define METODIK_INVADERS2_MENUBUTTON_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsLayoutItem>

namespace space_pewpew {

  /**
   * @brief The MenuButton class
   * A button that can be used in a menu.
   * It has a pixmap and a pixmapHover, which are shown when the mouse is over the button.
   * It emits a signal when clicked.
   */
  class MenuButton
    : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  public:
    /**
     * @brief MenuButton
     * @param pixmap the pixmap to be shown when the mouse is not over the button
     * @param pixmapHover the pixmap to be shown when the mouse is over the button
     * @param parent
     */
   MenuButton(const QPixmap &pixmap, const QPixmap &pixmapHover,
               QGraphicsItem *parent = nullptr)
      : QGraphicsPixmapItem(pixmap, parent) {
      this->pixmapHover = pixmapHover;
      this->pixmapLeave = pixmap;
      setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
      setAcceptHoverEvents(true);
    }

    /**
     * @brief hoverEnterEvent
     * @param event
     * When the mouse enters the button, the pixmapHover is shown.
     */
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override {
      Q_UNUSED(event);
      setPixmap(pixmapHover);
    }

    /**
     * @brief hoverLeaveEvent
     * @param event
     * When the mouse leaves the button, the pixmap is shown.
     */
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override {
      Q_UNUSED(event);
      setPixmap(pixmapLeave);
    }

  signals:

    /**
     * @brief clicked
     * Emitted when the button is clicked.
     */
    void clicked();

  protected:

    /**
     * @brief mousePressEvent
     * @param event
     * When the button is clicked, the clicked signal is emitted.
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override {
      emit clicked();
    }

  private:
    QPixmap pixmapHover;
    QPixmap pixmapLeave;
  };
} // space_pewpew

#endif //METODIK_INVADERS2_MENUBUTTON_H
