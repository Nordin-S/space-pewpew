//
// Created by nordi on 2/6/2023.
//

#ifndef METODIK_INVADERS2_INPUTHANDLER_H
#define METODIK_INVADERS2_INPUTHANDLER_H

#include <QObject>
#include <QKeyEvent>

namespace space_pewpew {

  /**
   * @brief The InputHandler class
   * This class is responsible for handling all the input events
   * from the user.
   */
  class InputHandler : public QObject {
  Q_OBJECT
  public:
    /**
     * @brief InputHandler
     * @param parent
     */
    explicit InputHandler(QObject *parent = nullptr);
    ~InputHandler() = default;

    /**
     * @brief eventFilter
     * @param obj
     * @param event
     * @return true if the event was handled, false otherwise
     */
    bool eventFilter(QObject *obj, QEvent *event) override;

    /**
     * @brief keyPressEvent
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief keyReleaseEvent
     * @param event
     */
    void keyReleaseEvent(QKeyEvent *event);

    signals:

    /**
     * @brief moveLeftDown
     * This signal is emitted when the user presses the left arrow key.
     */
    void moveLeftDown();

    /**
     * @brief moveLeftUp
     * This signal is emitted when the user releases the left arrow key.
     */
    void moveLeftUp();

    /**
     * @brief moveRightDown
     * This signal is emitted when the user presses the right arrow key.
     */
    void moveRightDown();

    /**
     * @brief moveRightUp
     * This signal is emitted when the user releases the right arrow key.
     */
    void moveRightUp();

    /**
     * @brief moveUpDown
     * This signal is emitted when the user presses the up arrow key.
     */
    void moveUpDown();

    /**
     * @brief moveUpUp
     * This signal is emitted when the user releases the up arrow key.
     */
    void moveUpUp();

    /**
     * @brief moveDownDown
     * This signal is emitted when the user presses the down arrow key.
     */
    void moveDownDown();

    /**
     * @brief moveDownUp
     * This signal is emitted when the user releases the down arrow key.
     */
    void moveDownUp();

    /**
     * @brief shootDown
     * This signal is emitted when the user presses the space bar.
     */
    void shootDown();

    /**
     * @brief shootUp
     * This signal is emitted when the user releases the space bar.
     */
    void shootUp();

    /**
     * @brief pausePressed
     * This signal is emitted when the user presses the escape key.
     */
    void pausePressed();
  };

} // space_pewpew

#endif //METODIK_INVADERS2_INPUTHANDLER_H
