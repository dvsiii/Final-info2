#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    derecha=false;
    izquierda=false;
    correr=false;
    lanzado=false;
    actual=nullptr;
    spriteSherlock=nullptr;
    spriteWatson=nullptr;
    pistas.fill(nullptr);
    spritepuerta=nullptr;
    spriteboton=nullptr;
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
    vista->viewport()->installEventFilter(this);
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
        actualizarbotones();
    });
    interactuo=false;
    texotint=new QLabel(this);
    texotint->setGeometry(180,20,440,40);
    texotint->setAlignment(Qt::AlignCenter);
    texotint->setStyleSheet("background-color: rgba(0, 0, 0, 180); color: white; font-size: 14px;");
    texotint->setVisible(false);
}
void MainWindow::actualizarbotones(){
    if(estado==Menu){
        if(opcion==0){
            btnjugar->setIcon(QIcon(":/assets/Boton jugar seleccionado.png"));
            btnsalir->setIcon(QIcon(":/assets/Boton salir no seleccionado.png"));
        }
        else{
            btnjugar->setIcon(QIcon(":/assets/Boton jugar no seleccionado.png"));
            btnsalir->setIcon(QIcon(":/assets/Boton salir seleccionado.png"));
        }
    }
    else if(estado==dificultad){
        if(opcion==0){
            btnfacil->setIcon(QIcon(":/assets/facils.png"));
            btnnormal->setIcon(QIcon(":/assets/normalns.png"));
            btndificil->setIcon(QIcon(":/assets/dificilns.png"));
        }
        else if(opcion==1){
            btnfacil->setIcon(QIcon(":/assets/facilns.png"));
            btnnormal->setIcon(QIcon(":/assets/normals.png"));
            btndificil->setIcon(QIcon(":/assets/dificilns.png"));
        }
        else if(opcion==2){
            btnfacil->setIcon(QIcon(":/assets/facilns.png"));
            btnnormal->setIcon(QIcon(":/assets/normalns.png"));
            btndificil->setIcon(QIcon(":/assets/dificils.png"));
        }
    }
    if(estado==jugando){
        nivel1 *n1 = dynamic_cast<nivel1*>(actual);
        if(n1!=nullptr){
            if(n1->getpuerta().getactivo()==false){
                spriteboton->setPixmap(QPixmap(":/assets/botonpurtap.png").scaled(n1->getpuerta().getbl(),n1->getpuerta().getba()));
            }
            else{
                spriteboton->setPixmap(QPixmap(":/assets/botonpurtanp.png").scaled(n1->getpuerta().getbl(),n1->getpuerta().getba()));
            }
        }
    }
}
void MainWindow::iniciarnivel(short int dif){
    delete actual;
    juego->clear();
    plataform.clear();
    bals.clear();
    ganchos.clear();
    QGraphicsPixmapItem *fondo=juego->addPixmap(QPixmap(":/assets/bocetomapa.png").scaled(2400,1800));
    fondo->setPos(0,0);
    juego->setSceneRect(0,0,2400,1800);
    estado=jugando;
    vista->setScene(juego);
    vista->centerOn(1200,1718);
    actual=new nivel1(dif);
    spriteSherlock=juego->addPixmap(QPixmap(":/assets/Sherlock_walking.png").scaled(32,32));
    spriteSherlock->setPos(1200,1718);
    spriteWatson=juego->addRect(0,0,32,32);
    spriteWatson->setPos(1150,1718);
    nivel1 *n1 = dynamic_cast<nivel1*>(actual);
    if(n1!=nullptr){
        std::array<pista,6>& pistasas=n1->getpistas();
        for(int i=5;i>=0;i--){
            pistas[i]=juego->addPixmap(QPixmap(":/assets/pistas.png").scaled(24, 24));
            pistas[i]->setPos(pistasas[i].getposicionx(),pistasas[i].getposiciony());
        }
        std::vector<plataforma>& plataformas=n1->getplataformas();
        for(int i=0;i<plataformas.size();i++){
            QGraphicsPixmapItem* sprite=juego->addPixmap(QPixmap(":/assets/plataforma.png").scaled(plataformas[i].gethitboxb(),plataformas[i].gethitboxa()));
            sprite->setPos(plataformas[i].getposicionx(),plataformas[i].getposiciony());
            plataform.push_back(sprite);
        }
        spritepuerta=juego->addPixmap(QPixmap(":/assets/puerta.png").scaled(n1->getpuerta().gethitboxb(),n1->getpuerta().gethitboxa()));
        spritepuerta->setPos(n1->getpuerta().getposicionx(),n1->getpuerta().getposiciony());
        spriteboton=juego->addPixmap(QPixmap(":/assets/botonpurtanp.png").scaled(n1->getpuerta().getbl(),n1->getpuerta().getba()));
        spriteboton->setPos(n1->getpuerta().getpbx(),n1->getpuerta().getpby());
        std::vector<gancho>& ganchs=n1->getganchos();
        for(int i=0;i<ganchs.size();i++){
            float r=ganchs[i].gethitboxb();
            QGraphicsPixmapItem* sprite=juego->addPixmap(QPixmap(":/assets/gancho.png").scaled(2*ganchs[i].gethitboxb(),2*ganchs[i].gethitboxb()));
            sprite->setPos(ganchs[i].getposicionx()-r,ganchs[i].getposiciony()-r);
            ganchos.push_back(sprite);
        }
    }
}
void MainWindow::keyPressEvent(QKeyEvent *event){
    if(estado==Inicio){
        if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter){
            estado=Menu;
            vista->setScene(menu);
            opcion=0;
            actualizarbotones();
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
                actualizarbotones();
            }
            else{
                opcion=0;
                actualizarbotones();
            }
        }
        else if(event->key()==Qt::Key_Down){
            if(opcion==0){
                opcion=1;
                actualizarbotones();
            }
            else{
                opcion=0;
                actualizarbotones();
            }
        }
        else if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
            if(opcion==0){
                estado=dificultad;
                opcion=0;
                btnfacil->setVisible(true);
                btnnormal->setVisible(true);
                btndificil->setVisible(true);
                actualizarbotones();
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
            actualizarbotones();
        }
        else if(event->key()==Qt::Key_Up){
            if(opcion==0){
                opcion=2;
                actualizarbotones();
            }
            else{
                opcion--;
                actualizarbotones();
            }
        }
        else if(event->key()==Qt::Key_Down){
            if(opcion==2){
                opcion=0;
                actualizarbotones();
            }
            else{
                opcion++;
                actualizarbotones();
            }
        }
        else if(event->key()==Qt::Key_Enter||event->key()==Qt::Key_Return){
            iniciarnivel(opcion);
        }
    }
    else if(estado==jugando){
        nivel1 *n1 = dynamic_cast<nivel1*>(actual);
        if(n1!=nullptr){
            sherlock& jugador=n1->getjugador();
            watson& agente=n1->getagente();
            if(interactuo==false&&agente.getcontrol()==false){
                if(event->key()==Qt::Key_Left||event->key()==Qt::Key_A){
                    izquierda=true;
                }
                else if(event->key()==Qt::Key_Right||event->key()==Qt::Key_D){
                    derecha=true;
                }
                else if(event->key()==Qt::Key_Up||event->key()==Qt::Key_W){
                    if(jugador.getgancho()==false){
                        jugador.saltar();
                        lanzado=false;
                    }
                    else{
                        jugador.soltarse();
                        lanzado=true;
                    }
                }
                else if(event->key()==Qt::Key_Shift){
                    correr=true;
                }
                else if(event->key()==Qt::Key_E){
                    interactuo=true;
                    izquierda=false;
                    derecha=false;
                    correr=false;
                    texotint->setText("1: Pista | 2: Disparar");
                    texotint->setVisible(true);
                }
            }
            else if(interactuo==true){
                if(event->key()==Qt::Key_1){
                    texotint->setText(QString::fromStdString(agente.pistacerca()));
                    interactuo=false;
                }
                else if(event->key()==Qt::Key_2){
                    agente.setcontrol(true);
                    agente.setv(0,agente.getvy());
                    texotint->setText("Haz clic para disparar");
                    interactuo = false;
                }
            }
        }
    }
}
void MainWindow::keyReleaseEvent(QKeyEvent *event){
    if(event->isAutoRepeat()) return;
    if(estado==jugando){
        if(event->key()==Qt::Key_Left||event->key()==Qt::Key_A){
            izquierda=false;
        }
        else if(event->key()==Qt::Key_Right||event->key()==Qt::Key_D){
            derecha=false;
        }
        else if(event->key()==Qt::Key_Shift){
            correr=false;
        }
    }
}
bool MainWindow::eventFilter(QObject *obj,QEvent *event){
    if(obj==vista->viewport()&&event->type()==QEvent::MouseButtonPress){
        if(estado==jugando&&actual!=nullptr){
            nivel1 *n1=dynamic_cast<nivel1*>(actual);
            if(n1!=nullptr&&n1->getagente().getcontrol()==true){
                QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
                QPointF posMapa=vista->mapToScene(mouseEvent->pos());
                bala* nueva=n1->getagente().disparar(posMapa.x(),posMapa.y());
                n1->agregarbala(nueva);
                QGraphicsPixmapItem* sprite = juego->addPixmap(QPixmap(":/assets/bala.png").scaled(8,8));
                sprite->setPos(nueva->getposicionx(),nueva->getposiciony());
                bals.push_back(sprite);
                n1->getagente().setcontrol(false);
                texotint->setVisible(false);
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::actualizarjuego(){
    if(estado==jugando&&actual!=nullptr){
        actual->actualizar();
        nivel1 *n1 = dynamic_cast<nivel1*>(actual);
        if(n1!=nullptr){
            sherlock* jugador=&n1->getjugador();
            watson* agente=&n1->getagente();
            std::array<pista,6>& pistasas=n1->getpistas();
            spriteSherlock->setPos(jugador->getposicionx(),jugador->getposiciony());
            spriteWatson->setPos(agente->getposicionx(),agente->getposiciony());
            vista->centerOn(jugador->getposicionx(),jugador->getposiciony());
            for(int i=5;i>=0;i--){
                if(pistasas[i].getrecolectado()==true){
                    pistas[i]->setVisible(false);
                }
                pistas[i]->setPos(pistasas[i].getposicionx(),pistasas[i].getposiciony());
            }
            std::vector<plataforma>& plataformas=n1->getplataformas();
            for(int i=plataformas.size()-1;i>=0;i--){
                plataform[i]->setVisible(plataformas[i].getactivo());
                plataform[i]->setPos(plataformas[i].getposicionx(),plataformas[i].getposiciony());
            }
            if(derecha==true){
                if(jugador->getgancho()==false){
                    jugador->moverse(true,correr);
                }
                else{
                    jugador->setfa(jugador->getfa()+0.35f);
                }
            }
            else if(izquierda==true){
                if(jugador->getgancho()==false){
                    jugador->moverse(false,correr);
                }
                else{
                    jugador->setfa(jugador->getfa()-0.35f);
                }
            }
            else if(jugador->getp()==true){
                lanzado=false;
                jugador->setv(0, jugador->getvy());
            }
            else if(lanzado==false){
                jugador->setv(0, jugador->getvy());
            }
            spritepuerta->setVisible(n1->getpuerta().getactivo());
            actualizarbotones();
            std::vector<bala*>& balas=n1->getbalas();
            for(int i=bals.size()-1;i>=0;i--){
                if(balas[i]->getacti()==true){
                    bals[i]->setPos(balas[i]->getposicionx(),balas[i]->getposiciony());
                }
                else{
                    delete balas[i];
                    balas.erase(balas.begin()+i);
                    juego->removeItem(bals[i]);
                    delete bals[i];
                    bals.erase(bals.begin()+i);
                }
            }
            std::vector<gancho>& ganchs=n1->getganchos();
            for(int i=ganchs.size()-1;i>=0;i--){
                float r=ganchs[i].gethitboxb();
                ganchos[i]->setVisible(ganchs[i].getactivo());
                ganchos[i]->setPos(ganchs[i].getposicionx()-r,ganchs[i].getposiciony()-r);
            }
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete actual;
}
