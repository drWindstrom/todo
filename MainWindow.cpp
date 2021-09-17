#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _tasks() {
  ui->setupUi(this);
  connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addTask() {
  bool ok;
  QString name =
      QInputDialog::getText(this, tr("Add task"), tr("Task name"),
                            QLineEdit::Normal, tr("Untitled task"), &ok);

  if (ok && !name.isEmpty()) {
    qDebug() << "Adding a task";
    Task *task = new Task(name);
    _tasks.append(task);
    ui->tasksLayout->addWidget(task);
    connect(task, &Task::removed, this, &MainWindow::removeTask);
  }
}

void MainWindow::removeTask(Task *task) {
  _tasks.removeOne(task);
  ui->tasksLayout->removeWidget(task);
  delete task;
}
