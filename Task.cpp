#include "Task.h"
#include "ui_Task.h"

#include <QInputDialog>

Task::Task(const QString &name, QWidget *parent)
    : QWidget(parent), ui(new Ui::Task) {
  ui->setupUi(this);
  setName(name);

  connect(ui->editButton, &QPushButton::clicked, this, &Task::rename);
  connect(ui->removeButton, &QPushButton::clicked,
          [this] { emit removed(this); });
}

Task::~Task()
{
    delete ui;
}

void Task::setName(const QString &name) { ui->checkBox->setText(name); }

QString Task::name() const { return ui->checkBox->text(); }

bool Task::isCompleted() const { return ui->checkBox->isChecked(); }

void Task::rename() {
  bool ok;
  QString newName =
      QInputDialog::getText(this, tr("Edit task"), tr("Task name"),
                            QLineEdit::Normal, this->name(), &ok);
  if (ok && !newName.isEmpty()) {
    setName(newName);
  }
}
