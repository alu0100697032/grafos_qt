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

    int cargarGrafo(QString nombrefichero);
    int actualizar(QString nombrefichero);
    unsigned Es_dirigido(); //devuelve 0 si el grafo es no dirigido y 1 si es dirigido
    void Info_Grafo();
    void Mostrar_Lista_Sucesores();
    void Mostrar_Lista_Predecesores();
    void ListaPredecesores();
    void dfs(unsigned i, QVector<bool> &visitado);
    void ComponentesConexas();

private slots:

    void on_actionGrafo1_gr_triggered();

    void on_actionGrafo2_gr_triggered();

    void on_actionGrafo3_gr_triggered();

    void on_actionGrafo4_gr_triggered();

    void on_actionGrafo5_gr_triggered();

    void on_actionGrafo6_gr_triggered();

    void on_actionGrafo7_gr_triggered();

    void on_actionGrafo8_gr_triggered();

    void on_actionGrafo9_gr_2_triggered();

    void on_actionInformaci_n_del_grafo_triggered();

private:
    Ui::Grafo *ui;

    bool cargado = false;
    unsigned numero_nodos;         // numero de NODOS //
    unsigned numero_arcos;         // numero de ARCOS //
    unsigned dirigido;  //0 si el grafo es no dirigido y 1 si es dirigido
    QVector<LA_nodo> LSucesores; // Lista de adyacencia de los sucesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
    QVector<LA_nodo> LPredecesores; // Lista de adyacencia de los predecesores: es una matriz donde cada fila posiblemente es posiblemente de distinto tamaño//
    QMap<unsigned, unsigned> pendientes;
};

#endif // GRAFO_H
