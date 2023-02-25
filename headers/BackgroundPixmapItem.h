//
// Created by nordi on 2/1/2023.
//

#ifndef METODIK_INVADERS2_BACKGROUNDPIXMAPITEM_H
#define METODIK_INVADERS2_BACKGROUNDPIXMAPITEM_H

#include <QGraphicsPixmapItem>
#include <QObject>

namespace space_pewpew {

  /**
   * @brief The BackgroundPixmapItem class
   * This class is a QGraphicsPixmapItem that overrides the shape() method to
   * prevent collision detection.
   */
  class BackgroundPixmapItem : public QObject, public QGraphicsPixmapItem {
  Q_OBJECT
  public:
    /**
     * @brief BackgroundPixmapItem constructor
     */
    BackgroundPixmapItem() = default;

    /**
     * @brief ~BackgroundPixmapItem destructor
     */
    ~BackgroundPixmapItem() override = default;
  protected:
    /**
     * @brief shape
     * This method overrides the shape() method of QGraphicsPixmapItem to
     * prevent collision detection.
     * @return
     */
    QPainterPath shape() const override {
      return *new QPainterPath();
    }
  };

} // space_pewpew

#endif //METODIK_INVADERS2_BACKGROUNDPIXMAPITEM_H
