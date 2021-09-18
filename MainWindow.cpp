#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QDebug>
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), _tasks() {
  ui->setupUi(this);
  connect(ui->addTaskButton, &QPushButton::clicked, this, &MainWindow::addTask);
  updateStatus();
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::updateStatus() {
  int completedTasks = 0;
  for (const auto task : _tasks) {
    if (task->isCompleted()) {
      completedTasks++;
    }
  }
  int todoCount = _tasks.size() - completedTasks;

  ui->statusLabel->setText(QString("Status: %1 todo / %2 completed")
                               .arg(todoCount)
                               .arg(completedTasks));
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
    connect(task, &Task::statusChanged, this, &MainWindow::taskStatusChanged);
    updateStatus();
  }
}

void MainWindow::removeTask(Task *task) {
  _tasks.removeOne(task);
  ui->tasksLayout->removeWidget(task);
  delete task;
  updateStatus();
}

void MainWindow::taskStatusChanged(Task *task) { updateStatus(); }
