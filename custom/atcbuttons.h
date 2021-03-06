#ifndef ATCBUTTONDIALOG_H
#define ATCBUTTONDIALOG_H

#include <QPushButton>

class ATCButtonDialog : public QPushButton
{
    Q_OBJECT

public:
    explicit ATCButtonDialog(QWidget *parent = 0);
    ~ATCButtonDialog();
};


class ATCButtonMainWindow : public QPushButton
{
    Q_OBJECT

public:
    explicit ATCButtonMainWindow(QWidget *parent = 0);
    ~ATCButtonMainWindow();
};

#endif // ATCBUTTONDIALOG_H
