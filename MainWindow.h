#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Task.h"
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  public slots:
    void addTask();
    void removeTask(Task *task);

  private:
    Ui::MainWindow *ui;
    QVector<Task *> _tasks;
};
#endif // MAINWINDOW_H
