#ifndef NBASEMOVEABLEWIDGET_H
#define NBASEMOVEABLEWIDGET_H

/**
 * 作者: daodaoliang
 * 时间: 2016年8月10日
 * 邮箱: daodaoliang@yeah.net
 */

#include <QObject>
#include <QWidget>
#include <QPoint>
#include <QCursor>
#include <QRect>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <windows.h>
#include <windowsx.h>
#include "nbaseuikit_global.h"
#include "nbasetoolbutton.h"

/*接受边框处理的宽度*/
#define PADDING 2

/**
 * @brief The Direction enum
 * 鼠标方向
 */
enum Direction{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT,
    LEFTTOP,
    LEFTBOTTOM,
    RIGHTBOTTOM,
    RIGHTTOP,
    NONE
};

/**
 * @brief The MOVEPLAN enum
 * 窗体移动方案
 */
enum MOVEPLAN{
    PLANA,
    PLANB
};

/**
 * @brief The NBaseMoveableWidget class
 * 可拖动大小,可移动窗体
 */

class NBASEUIKITSHARED_EXPORT NBaseMoveableWidget : public NBaseToolButton
{
    Q_OBJECT
public:
    /**
     * @brief NBaseMoveableWidget 构造函数
     * @param parent 父指针
     */
    explicit NBaseMoveableWidget(QWidget *parent = 0);

    /**
     * @brief move_plan 窗体移动方案
     * @return 方案
     */
    MOVEPLAN move_plan() const;

    /**
     * @brief isDragAble 获取是否可拖拽
     * @return 是否可拖拽
     */
    bool isDragAble() const;

    /**
     * @brief setIsDragAble 设置是否可拖拽
     * @param isDragAble 是否可拖拽
     */
    void setIsDragAble(bool isDragAble);

protected:
    /**
     * @brief mousePressEvent 鼠标按压事件处理
     * @param event
     */
    void mousePressEvent(QMouseEvent *event);

    /**
     * @brief mouseMoveEvent 鼠标移动事件处理
     * @param event
     */
    void mouseMoveEvent(QMouseEvent *event);

    /**
     * @brief mouseReleaseEvent 鼠标释放时间处理
     * @param event
     */
    void mouseReleaseEvent(QMouseEvent *event);

    /**
     * @brief paintEvent 绘制事件
     * @param event
     */
    void paintEvent(QPaintEvent *event);

    /**
     * @brief winEvent windows窗体事件
     * @param message
     * @param result
     * @return
     */
    bool winEvent(MSG *message, long *result);

private:
    /**
     * @brief region 鼠标指针修改
     * @param cursorGlobalPoint
     */
    void region(const QPoint &cursorGlobalPoint);

    /**
     * @brief setMove_plan 设置窗体移动方案
     * @param move_plan
     */
    void setMove_plan(const MOVEPLAN &move_plan);

private:
    /**
     * @brief isLeftPressDown_ 左键是否按压
     */
    bool isLeftPressDown_;

    /**
     * @brief isDragAble_ 窗体是否可拖拽大小
     */
    bool isDragAble_;

    /**
     * @brief dragPosition_ 窗体拖拽的位置
     */
    QPoint dragPosition_;

    /**
     * @brief dir_ 鼠标方向
     */
    Direction dir_;

    /**
     * @brief move_plan_ 窗体移动方案
     */
    MOVEPLAN move_plan_;
};

#endif // NBASEMOVEABLEWIDGET_H
