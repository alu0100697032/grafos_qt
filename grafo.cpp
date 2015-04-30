#include "grafo.h"
#include "ui_grafo.h"

Grafo::Grafo(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Grafo)
{
    ui->setupUi(this);
    ui->actionInfoGrafo->setEnabled(false);
    ui->actionPintarGrafo->setEnabled(false);
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
    ui->actionInfoGrafo->setEnabled(true);
    ui->actionPintarGrafo->setEnabled(true);
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

/****************************************************************************************
 ************************************** PINTAR ******************************************
 ****************************************************************************************/

void Grafo::pintarGrafo(){
    int nodosPorFila = qSqrt(numero_nodos);
    int radioNodo = 40;
    int centroNodo = radioNodo/2;
    int separacionEntreNodos = 50;
    int posicionX = 0;
    int posicionY = 0;
    int distancia = radioNodo+separacionEntreNodos;
    int nodosAgregadosFila = 0;
    QVector<int> coordenadasXNodo;
    QVector<int> coordenadasYNodo;

    escena = new QGraphicsScene(this);
    ui->graphicsView->setScene(escena);

    //pintar nodos
    for(int i = 0; i < numero_nodos; i++){
        if(nodosPorFila > nodosAgregadosFila){
            nodosAgregadosFila++;
            escena->addEllipse(posicionX,posicionY,radioNodo,radioNodo);
            coordenadasXNodo.push_back(posicionX);
            coordenadasYNodo.push_back(posicionY);
            posicionX+= distancia;
        }else{
            nodosAgregadosFila = 1;
            posicionX = 0;
            posicionY+=distancia;
            escena->addEllipse(posicionX,posicionY,radioNodo,radioNodo);
            coordenadasXNodo.push_back(posicionX);
            coordenadasYNodo.push_back(posicionY);
            posicionX+=distancia;
        }
    }
    //pintar arcos
    for(int i = 0; i < LSucesores.size(); i++){
        for(int j = 0; j < LSucesores[i].size(); j++){
            escena->addLine(coordenadasXNodo[i]+(radioNodo/2), coordenadasYNodo[i]+(radioNodo/2),
                        coordenadasXNodo[LSucesores[i][j].nodo]+(radioNodo/2),
                        coordenadasYNodo[LSucesores[i][j].nodo]+(radioNodo/2));
        }
    }
}

/****************************************************************************************
 ************************************** EVENTOS******************************************
 ****************************************************************************************/

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

void Grafo::on_actionInfoGrafo_triggered()
{
    Info_Grafo();
}

void Grafo::on_actionPintarGrafo_triggered()
{
    pintarGrafo();
}
