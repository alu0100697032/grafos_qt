#ifndef GRAFO_H
#define GRAFO_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <QCoreApplication>
#include <QVector>
#include <QMap>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <QFile>

namespace Ui {
class Grafo;
}

// definicion de un elemento de la lista de adyacencia

typedef struct {
    unsigned nodo; // nodo
    int coste; // atributo para expresar el peso, la longitud, el coste, la inversin, etc...
} ElementoLista;


//definicion del tipo de una lista de adyacencia de un nodo

typedef QVector<ElementoLista> LA_nodo;

//clase grafo

class Grafo : public QMainWindow
{
    Q_OBJECT

public:
    explicit Grafo(QWidget *parent = 0);
    ~Grafo();

    QString cargarGrafo(QString nombrefichero);
    unsigned Es_dirigido(); //devuelve 0 si el grafo es no dirigido y 1 si es dirigido
    void Info_Grafo();
    void Mostrar_Lista_Sucesores();
    void Mostrar_Lista_Predecesores();
    void ListaPredecesores();
    void dfs(unsigned i, QVector<bool> &visitado);
    void ComponentesConexas();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::Grafo *ui;

    unsigned numero_nodos;         // numero de NODOS //
    unsigned numero_arcos;         // numero de ARCOS //
    unsigned dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
    QVector<LA_nodo> LSucesores; // Lista de adyacencia de los sucesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
    QVector<LA_nodo> LPredecesores; // Lista de adyacencia de los predecesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
    QMap<unsigned, unsigned> pendientes;
};

#endif // GRAFO_H
