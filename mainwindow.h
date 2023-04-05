#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "dialog.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    Game myGame;


    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void StartGame();
    void paintEvent(QPaintEvent *);
    void Draw();
    void TimeOut();
    bool firstClick;

private slots:
    void on_RestartButton_clicked();

    void on_actionEasy_triggered();

    void on_actionHard_triggered();

    void on_actionMedium_triggered();

    void on_actionCustom_triggered();

    void mousePressEvent(QMouseEvent *event);

    void mouseDoubleClickEvent(QMouseEvent *event);

    void mouseReleaseEvent(QMouseEvent *event);



private:
    Ui::MainWindow *ui;
    int W = 300, H = 350;
    LEVEL level = LEVEL::EASY;
    int customRow = 10, customColumn = 10;
    int customMineNum = 10;
    QPixmap fame;
    QTimer* timer;
    int time = 0;
};
#endif // MAINWINDOW_H
