#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Command.h"
#include "Parser.h"
#include "Room.h"
#include "Characters.h"
#include "item.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <QTextEdit>
#include <QString>
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void play();
    QString go(QString direction);

private slots:
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_checkBox_stateChanged(int arg1);

    void on_pushButton_10_clicked();

private:
    Parser parser;
    bool encrypted;
    Room *currentRoom;
    Characters *protagonist;
    QTextEdit *textInvent;
    Item *tempItem;
    bool gameEnded;
    Room *a1, *a, *b, *c, *d, *e, *f, *g, *h, *i, *j, *j1;
    void createRooms();
    void printWelcome();
    bool processCommand(Command command);
    void printHelp();
    void goRoom(Command command);
    void teleport();
    void createItems();
    void displayItems();
    void gameOver(bool win);
    void gameOver();
    void map();
    void take(QString itemName);
    void calculateInvent();
    void calculateHealth();
    QFont newFont;
    QFont newFontSecret;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
