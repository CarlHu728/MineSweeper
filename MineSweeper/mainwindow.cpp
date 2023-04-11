#include "mainwindow.h"
#include "game.h"
#include "./ui_mainwindow.h"

#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    StartLocalGame();
    fame.load(":/img/source.png");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::StartLocalGame() {
    firstClick = true;
    time = 0;
    timer = new QTimer;
    myGame.Start(level, customRow, customColumn, customMineNum);
    SetWindow();
}

void MainWindow::StartOnlineGame() {
    if (isHost) {
        myGame.newRoom();
    } else {
        myGame.joinRoom(roomCode);
    }
}

void MainWindow::SetWindow() {
    W = 50 + myGame.GetRow() * 20;
    H = 100 + myGame.GetColumn() * 20;
    ui->RestartButton->setGeometry(W / 2 - 15, 10, 30, 30);
    ui->RemainMineLabel->setGeometry(W / 4 - 30, 10, 60, 30);
    ui->TimeCountLabel->setGeometry(W / 4 * 3 - 30, 10, 60, 30);
    setFixedSize(W, H);
    update();
}

void MainWindow::TimeOut() {
    if (myGame.GetState() == STATE::INGAME) { ++this->time; }
    update();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    ui->actionEasy->setChecked(level == LEVEL::EASY);
    ui->actionMedium->setChecked(level == LEVEL::MEDIUM);
    ui->actionHard->setChecked(level == LEVEL::HARD);
    ui->actionCustom->setChecked(level == LEVEL::CUSTOM);
    ui->TimeCountLabel->setText(QString::number(this->time));
    ui->RemainMineLabel->setText(QString::number(qMax(myGame.GetRemainMine(), 0)));
    QPainter painter(this);

    if (myGame.GetState() == STATE::WIN) { ui->RestartButton->setText(":D"); }
    if (myGame.GetState() == STATE::LOSE) { ui->RestartButton->setText(":("); }

    painter.drawPixmap(100, 100, fame, 0, 0, 70, 40);

    for (int i = 0; i < myGame.GetRow(); i++) {
        for (int j = 0; j < myGame.GetColumn(); j++) {
            painter.drawPixmap(i * 20 + 25, j * 20 + 75, fame, int(myGame.GetType(i, j)) * 20, 0, 20, 20);
        }
    }
}

void MainWindow::Draw() {
    myGame.Check();
    if (myGame.GetState() != STATE::INGAME) {
        timer->stop();
        myGame.End();
    }
    update();
}

void MainWindow::on_RestartButton_clicked()
{
    StartLocalGame();
}

void MainWindow::on_actionEasy_triggered()
{
    level = LEVEL::EASY;
    StartLocalGame();
}

void MainWindow::on_actionMedium_triggered()
{
    level = LEVEL::MEDIUM;
    StartLocalGame();
}

void MainWindow::on_actionHard_triggered()
{
    level = LEVEL::HARD;
    StartLocalGame();
}

void MainWindow::on_actionCustom_triggered()
{
    Dialog *dialog = new Dialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        dialog->GetValue(customRow, customColumn, customMineNum);
        level = LEVEL::CUSTOM;
        StartLocalGame();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (myGame.GetState() != STATE::INGAME) { return; }
    int x = (event->pos().x() - 25) / 20, y = (event->pos().y() - 70) / 20;
    if (event->button() == Qt::LeftButton){
        if (myGame.Click(x, y) && firstClick) {
            this->timer->start(1000);
            firstClick = false;
            connect(timer, &QTimer::timeout, this, &MainWindow::TimeOut);
        }
    } else if (event->button() == Qt::RightButton){
        if (myGame.RightClick(x, y) && firstClick) {
            this->timer->start(1000);
            firstClick = false;
            connect(timer, &QTimer::timeout, this, &MainWindow::TimeOut);
        }
    }
    Draw();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (myGame.GetState() != STATE::INGAME) { return; }
    ui->RestartButton->setText(":)");
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    int x = (event->pos().x() - 25) / 20, y = (event->pos().y() - 70) / 20;
    if (event->button() == Qt::LeftButton) {
        myGame.DoubleClick(x, y);
    }
    Draw();
}

void MainWindow::on_actionAbout_triggered()
{

}

void MainWindow::on_actionExit_room_triggered()
{
    if (!myGame.exitRoom()) {

    }

}

