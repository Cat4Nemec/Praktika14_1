//mainwindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDebug>

#define WINDOW_WIDTH "windowWidth"
#define WINDOW_HEIGHT "windowHeight"

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    filePath = "../test141/config.ini";
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    while (!file.atEnd()) {
        configLine = file.readLine();
        int posDelimiter = configLine.indexOf(configDelimiter);
        configKey = configLine.left(posDelimiter);
        configValue = configLine.right(configLine.size() - posDelimiter - 1);
        qDebug() << "Config Line: " << configLine;
        qDebug() << "Pos Delimiter: " << posDelimiter;
        qDebug() << "Key: " << configKey;
        qDebug() << "Value: " << configValue;
        if (!configKey.compare(WINDOW_WIDTH)) {
            windowWidth = configValue.toInt();
        }
    }
    resize(windowWidth, windowHeight);
    setWindowTitle("Test Config Parser v14.1");
}

MainWindow::~MainWindow()
{
    delete ui;
}
//mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QString filePath;
    QString configLine;
    QString configKey;
    QString configValue;
    const QString configDelimiter = "=";
    int windowWidth;
    int windowHeight;
};

#endif // MAINWINDOW_H
