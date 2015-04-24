#ifndef GRAFO_H
#define GRAFO_H

#include <QMainWindow>

namespace Ui {
class Grafo;
}

class Grafo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Grafo(QWidget *parent = 0);
    ~Grafo();

private:
    Ui::Grafo *ui;
};

#endif // GRAFO_H
