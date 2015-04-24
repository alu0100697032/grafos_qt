#include "grafo.h"
#include "ui_grafo.h"

Grafo::Grafo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Grafo)
{
    ui->setupUi(this);
}

Grafo::~Grafo()
{
    delete ui;
}
