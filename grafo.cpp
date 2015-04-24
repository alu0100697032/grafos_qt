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

QString Grafo::cargarGrafo(QString nombrefichero){
    ElementoLista dummy;
    QFile textfile(nombrefichero);
    if(!textfile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", textfile.errorString());
        return "Error en la apertura del fichero";
    }
    QTextStream infile(&textfile);

    //QString line = infile.readLine();
    unsigned i, j, k;
    // leemos por conversion implicita el numero de nodos, arcos y el atributo dirigido
    infile >> (unsigned &) numero_nodos >> (unsigned &) numero_arcos
            >> (unsigned &) dirigido;
    // los nodos internamente se numeran desde 0 a n-1
    // creamos las n listas de sucesores
    LSucesores.resize(numero_nodos);
    // leemos los m arcos y cramos las listas de sucesores LS
    for (k = 0; k < numero_arcos; k++) {
        infile >> i;
        infile >> j;
        dummy.nodo = j - 1;
        LSucesores[i - 1].push_back(dummy);
    }
    textfile.close();
    if (Es_dirigido() == 1) { //Si es dirigido creamos la lista de predecesores
        ListaPredecesores();
    } else { // si no, recorremos la lista de sucesores para unir bien los nodos
        QVector<LA_nodo> aux = LSucesores;
        for (i = 0; i < aux.size(); i++) {
            for (j = 0; j < aux[i].size(); j++) {
                dummy.nodo = i;
                LSucesores[LSucesores[i][j].nodo].push_back(dummy);
            }
        }
    }
    return "Grafo leido correctamente";
}

/*
 * CONSTRUYE LA LISTA DE PREDECESORES
 */
void Grafo::ListaPredecesores() {
    unsigned j, k;
    ElementoLista dummy;
    LPredecesores.resize(numero_nodos);
    for (j = 0; j < LPredecesores.size(); j++) {
        for (k = 0; k < LSucesores[j].size(); k++) {
            dummy.nodo = j;
            LPredecesores[LSucesores[j][k].nodo].push_back(dummy);
        }
    }
}

unsigned Grafo::Es_dirigido() {
    return dirigido;
}

/*
 * MUESTRA LA INFORMACION DEL GRAFO
 */
void Grafo::Info_Grafo() {
    QString arcos = QString::number(numero_arcos);
    QString nodos = QString::number(numero_nodos);
    QString tipo;
    if(Es_dirigido())
        tipo = "Grafo dirigido";
    else
        tipo = "Grafo no dirigido";

    ui->label_2->setText("Información del grafo:\n\nNúmero de nodos: \t" +
                         nodos + "\nNúmero de arcos: \t" + arcos + "\n" + tipo);
}

/*
 * EVENTOS
 */
//carga el grafo 1
void Grafo::on_pushButton_clicked()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo1.gr");
    ui->label->setText(cargarGrafo(path));
}
//muestra la información del grafo
void Grafo::on_pushButton_5_clicked()
{
    Info_Grafo();
}
