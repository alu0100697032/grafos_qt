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

int Grafo::cargarGrafo(QString nombrefichero){
    ElementoLista dummy;
    QFile textfile(nombrefichero);
    if(!textfile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", textfile.errorString());
        return 0;
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
    return 1;
}

int Grafo::actualizar(QString nombrefichero){
    LPredecesores.clear();
    LSucesores.clear();
    pendientes.clear();
    ElementoLista dummy;
    QFile textfile(nombrefichero);
    if(!textfile.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", textfile.errorString());
        return 0;
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
    return 1;
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
void Grafo::on_actionGrafo1_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo1.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo2_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo2.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo3_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo3.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo4_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo4.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo5_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo5.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo6_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo6.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo7_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo7.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo8_gr_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo1.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionGrafo9_gr_2_triggered()
{
    QString path = QCoreApplication::applicationDirPath();
    path.append("/grafo9.gr");
    if(cargado){
        if(actualizar(path) == 1)//si carga bien..
            ui->statusBar->showMessage(tr("Grafo cargado"));
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }else{
        if(cargarGrafo(path) == 1)//si carga bien..
        {
            ui->statusBar->showMessage(tr("Grafo cargado"));
            cargado = true;
        }
        else//si no...
            ui->statusBar->showMessage(tr("Error en la apertura del grafo"));
    }
}

void Grafo::on_actionInformaci_n_del_grafo_triggered()
{
    Info_Grafo();
}
