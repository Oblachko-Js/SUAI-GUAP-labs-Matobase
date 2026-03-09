#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QPropertyAnimation>
#include <QMediaRecorder>
#include <QVideoWidget>
#include <QGraphicsVideoItem>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int currentFrame READ currentFrame WRITE setCurrentFrame NOTIFY currentFrameChanged)

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int currentFrame() const;
    void setCurrentFrame(int frame);

signals:
    void currentFrameChanged(int frame);

private slots:
    void on_btnPlay_clicked();
    void on_btnRender_clicked();
    void on_btnAddKeyframe_clicked();
    void updateAnimation();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QGraphicsRectItem *rectangle;
    QGraphicsEllipseItem *circle;
    QPropertyAnimation *animation;
    QList<QPointF> keyframes;
    QList<qreal> scales;
    int m_currentFrame = 0;
    void setupScene();
};
#endif
