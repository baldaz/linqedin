#include "gui_newmessage.h"

Gui_NewMessage::Gui_NewMessage(QWidget *parent) : QWidget(parent) {
  QGridLayout *grid = new QGridLayout(this);
  grid->setSpacing(20);

  QLabel *title = new QLabel("To:", this);
  grid->addWidget(title, 0, 0, 1, 1);

  QLineEdit *edt1 = new QLineEdit(this);
  grid->addWidget(edt1, 0, 1, 1, 1);

  QLabel *author = new QLabel("Subject:", this);
  grid->addWidget(author, 1, 0, 1, 1);

  QLineEdit *edt2 = new QLineEdit(this);
  grid->addWidget(edt2, 1, 1, 1, 1);

  QLabel *review = new QLabel("Body:", this);
  grid->addWidget(review, 2, 0, 1, 1);

  QTextEdit *te = new QTextEdit(this);
  te->setStyleSheet("background: #1a1a1a; border-radius: 5px; color: #e6e6e6; font-weight: 400;");
  grid->addWidget(te, 2, 1, 3, 1);

  setLayout(grid);
}