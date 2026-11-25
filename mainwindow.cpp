#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    actual=nullptr;
    estado=Inicio;
    opcion=0;
    inicio=new QGraphicsScene(this);
    menu=new QGraphicsScene(this);
    juego=new QGraphicsScene(this);
    btnjugar=new QPushButton;
    btnsalir=new QPushButton;
    btnfacil=new QPushButton;
    btnnormal=new QPushButton;
    btndificil=new QPushButton;
    btnjugar->setGeometry(251,328,206,60);
    btnsalir->setGeometry(251,457,206,60);
    btnfacil->setGeometry(562,304,194,34);
    btnnormal->setGeometry(562,386,194,34);
    btndificil->setGeometry(562,465,194,34);
    btnjugar->setIcon(QIcon(":/assets/Boton jugar no seleccionado.png"));
    btnjugar->setIconSize(QSize(206,60));
    btnjugar->setStyleSheet("border: none; background: transparent;");
    btnjugar->setFocusPolicy(Qt::NoFocus);
    btnsalir->setIcon(QIcon(":/assets/Boton salir no seleccionado.png"));
    btnsalir->setIconSize(QSize(206,60));
    btnsalir->setStyleSheet("border: none; background: transparent;");
    btnsalir->setFocusPolicy(Qt::NoFocus);
    btnfacil->setIcon(QIcon(":/assets/facilns.png"));
    btnfacil->setIconSize(QSize(194,34));
    btnfacil->setStyleSheet("border: none; background: transparent;");
    btnfacil->setVisible(false);
    btnfacil->setFocusPolicy(Qt::NoFocus);
    btnnormal->setIcon(QIcon(":/assets/normalns.png"));
    btnnormal->setIconSize(QSize(194,34));
    btnnormal->setStyleSheet("border: none; background: transparent;");
    btnnormal->setVisible(false);
    btnnormal->setFocusPolicy(Qt::NoFocus);
    btndificil->setIcon(QIcon(":/assets/dificilns.png"));
    btndificil->setIconSize(QSize(194,34));
    btndificil->setStyleSheet("border: none; background: transparent;");
    btndificil->setVisible(false);
    btndificil->setFocusPolicy(Qt::NoFocus);
    inicio->setSceneRect(0,0,800,600);
    menu->setSceneRect(0,0,800,600);
    vista=new QGraphicsView(inicio,this);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFocusPolicy(Qt::NoFocus);
    setCentralWidget(vista);
    tiempo=new QTimer(this);
    connect(tiempo,&QTimer::timeout,this,&MainWindow::actualizarjuego);
    tiempo->start(16);
    inicio->addPixmap(QPixmap(":/assets/inicio.png").scaled(800,600));
    menu->addPixmap(QPixmap(":/assets/Menu.png").scaled(800,600));
    menu->addWidget(btnjugar);
    menu->addWidget(btnsalir);
    menu->addWidget(btnfacil);
    menu->addWidget(btnnormal);
    menu->addWidget(btndificil);
    connect(btnsalir,&QPushButton::clicked,this,&MainWindow::close);
    connect(btnfacil,&QPushButton::clicked,this,[this](){
        iniciarnivel(0);
    });
    connect(btnnormal,&QPushButton::clicked,this,[this](){
        iniciarnivel(1);
    });
    connect(btndificil, &QPushButton::clicked, this,[this](){
        iniciarnivel(2);
    });
    connect(btnjugar,&QPushButton::clicked,this,[this](){
        estado=dificultad;
        opcion=0;
        btnfacil->setVisible(true);
        btnnormal->setVisible(true);
        btndificil->setVisible(true);
    });
}
void MainWindow::actualizarbotones(){}
void MainWindow::iniciarnivel(short int dif){}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(estado==Inicio){
        if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter){
            estado=Menu;
            vista->setScene(menu);
            opcion=0;
        }
    }
    else if(estado==Menu){
        if(event->key()==Qt::Key_Escape){
            estado=Inicio;
            vista->setScene(inicio);
            opcion=0;
        }
        else if(event->key()==Qt::Key_Up){
            if(opcion==0){
                opcion=1;
            }
            else{
                opcion=0;
            }
        }
        else if(event->key()==Qt::Key_Down){
            if(opcion==0){
                opcion=1;
            }
            else{
                opcion=0;
            }
        }
        else if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
            if(opcion==0){
                estado=dificultad;
                opcion=0;
                btnfacil->setVisible(true);
                btnnormal->setVisible(true);
                btndificil->setVisible(true);
            }
            else{
                close();
            }
        }
    }
    else if(estado==dificultad){
        if(event->key()==Qt::Key_Escape){
            estado=Menu;
            opcion=0;
            btnfacil->setVisible(false);
            btnnormal->setVisible(false);
            btndificil->setVisible(false);
        }
        else if(event->key()==Qt::Key_Up){
            if(opcion==0){
                opcion=2;
            }
            else{
                opcion--;
            }
        }
        else if(event->key()==Qt::Key_Down){
            if(opcion==2){
                opcion=0;
            }
            else{
                opcion++;
            }
        }
        else if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
            iniciarnivel(opcion);
        }
    }
}
void MainWindow::actualizarjuego(){}
MainWindow::~MainWindow()
{
    delete ui;
    delete actual;
}
