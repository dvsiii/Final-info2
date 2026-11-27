#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    derecha=false;
    izquierda=false;
    correr=false;
    lanzado=false;
    arriba=false;
    abajo=false;
    actual=nullptr;
    notaAbierta=nullptr;
    muebles.fill(nullptr);
    nota.fill(nullptr);
    mirandoderecha=false;
    frameactual=0;
    contadoranim=0;
    mirandoderechaw=false;
    frameactualw=0;
    contadoranimw=0;
    spriteSherlock=nullptr;
    spriteWatson=nullptr;
    pistas.fill(nullptr);
    mira.fill(nullptr);
    spritepuerta=nullptr;
    spriteboton=nullptr;
    cuerda=nullptr;
    estado=Inicio;
    opcion=0;
    inicio=new QGraphicsScene(this);
    menu=new QGraphicsScene(this);
    juego=new QGraphicsScene(this);
    perdiste=new QGraphicsScene(this);
    Ganaste=new QGraphicsScene(this);
    Controlesn1=new QGraphicsScene(this);
    Controlesn2=new QGraphicsScene(this);
    reloj=new QTimer(this);
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
    perdiste->setSceneRect(0,0,800,600);
    vista=new QGraphicsView(inicio,this);
    vista->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    vista->setFocusPolicy(Qt::NoFocus);
    setCentralWidget(vista);
    vista->viewport()->installEventFilter(this);
    vista->viewport()->setMouseTracking(true);
    tiempo=new QTimer(this);
    connect(tiempo,&QTimer::timeout,this,&MainWindow::actualizarjuego);
    tiempo->start(16);
    inicio->addPixmap(QPixmap(":/assets/inicio.png").scaled(800,600));
    menu->addPixmap(QPixmap(":/assets/Menu.png").scaled(800,600));
    perdiste->addPixmap(QPixmap(":/assets/gameover.png").scaled(800,600));
    Ganaste->addPixmap(QPixmap(":/assets/ganaste.png").scaled(800,600));
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
    connect(reloj, &QTimer::timeout, this, &MainWindow::actualizartiempo);
    interactuo=false;
    texotint=new QLabel(this);
    texotint->setGeometry(180,20,440,40);
    texotint->setAlignment(Qt::AlignCenter);
    texotint->setStyleSheet("background-color: rgba(0, 0, 0, 180); color: white; font-size: 14px;");
    texotint->setVisible(false);
    labelpistas=new QLabel(this);
    labeltiempo=new QLabel(this);
    labelpistas->setGeometry(20,20,140,40);
    labelpistas->setAlignment(Qt::AlignCenter);
    labelpistas->setStyleSheet("background-color: rgba(0, 0, 0, 180); color: white; font-size: 14px;");
    labelpistas->setVisible(false);
    labeltiempo->setGeometry(640,20,140,40);
    labeltiempo->setAlignment(Qt::AlignCenter);
    labeltiempo->setStyleSheet("background-color: rgba(0, 0, 0, 180); color: white; font-size: 14px;");
    labeltiempo->setVisible(false);
    hojaSherlock.load(":/assets/Sherlock_walking.png");
    saltosherlock.load(":/assets/Sherlock_salta.png");
    hojaWatson.load(":/assets/watson.png");
    vista->scale(1.8,1.8);
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
    for(int i=0;i<15;i++){
        mira[i]=juego->addEllipse(0,0,4,4,QPen(Qt::NoPen),QBrush(Qt::white));
        mira[i]->setVisible(false);
        mira[i]->setZValue(10);
    }
    cuerda=juego->addLine(0,0,0,0,QPen(Qt::black,2));
    cuerda->setVisible(false);
    fondo->setPos(0,0);
    juego->setSceneRect(0,0,2400,1800);
    estado=jugando;
    vista->setScene(juego);
    vista->centerOn(1200,1718);
    actual=new nivel1(dif);
    segundosRestantes=180;
    reloj->start(1000);
    labelpistas->setText("Pistas: 0/6");
    labeltiempo->setText("03:00");
    labelpistas->setVisible(true);
    labeltiempo->setVisible(true);
    int ancho=hojaSherlock.width()/3;
    int alto=hojaSherlock.height()/2;
    int anchow=hojaWatson.width()/3;
    int altow=hojaWatson.height();
    spriteSherlock = juego->addPixmap(hojaSherlock.copy(0,0,ancho,alto).scaled(32,32));
    spriteSherlock->setPos(1200,1718);
    spriteWatson=juego->addPixmap(hojaWatson.copy(0,0,anchow,altow).scaled(32,32));
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
void MainWindow::iniciarnivel2(){
    delete actual;
    juego->clear();
    plataform.clear();
    bals.clear();
    ganchos.clear();
    juego->setSceneRect(0,0,800,600);
    actual=new nivel2();
    vista->centerOn(400,300);
    derecha=false;
    izquierda=false;
    arriba=false;
    abajo=false;
    correr=false;
    interactuo=false;
    labelpistas->setVisible(false);
    texotint->setVisible(false);
    reloj->stop();
    labeltiempo->setVisible(false);
    QGraphicsPixmapItem *fondo=juego->addPixmap(QPixmap(":/assets/nivel2.png").scaled(800,600));
    fondo->setPos(0,0);
    nivel2 *n2=dynamic_cast<nivel2*>(actual);
    verticalwatson.load(":/assets/watsonn2.png");
    int ancho=verticalwatson.width()/3;
    int alto=verticalwatson.height()/2;
    dirwatson=1;
    spriteWatson=juego->addPixmap(verticalwatson.copy(0,0,ancho,alto).scaled(32,45));
    spriteWatson->setPos(400,300);
    if(n2!=nullptr){
        muebles[0]=juego->addPixmap(QPixmap(":/assets/escritorio.png").scaled(50,50));
        muebles[0]->setPos(230,300);
        muebles[1]=juego->addPixmap(QPixmap(":/assets/tablero.png").scaled(50,50));
        muebles[1]->setPos(630,300);
    }
    notaAbierta=juego->addPixmap(QPixmap());
    notaAbierta->setPos(250,100);
    notaAbierta->setZValue(10);
    notaAbierta->setVisible(false);
    for(int i=0;i<6;i++){
        nota[i]=juego->addPixmap(QPixmap());
        nota[i]->setPos(115+(i%3)*210,90+(i/3)*230);
        nota[i]->setZValue(10);
        nota[i]->setVisible(false);
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
        else{
            nivel2 *n2=dynamic_cast<nivel2*>(actual);
            if(n2!=nullptr){
                if(event->key()==Qt::Key_Left||event->key()==Qt::Key_A){
                    izquierda=true;
                }
                else if(event->key()==Qt::Key_Right||event->key()==Qt::Key_D){
                    derecha=true;
                }
                else if(event->key()==Qt::Key_Up||event->key()==Qt::Key_W){
                    arriba=true;
                }
                else if(event->key()==Qt::Key_Shift){
                    correr=true;
                }
                else if(event->key()==Qt::Key_Down||event->key()==Qt::Key_S){
                    abajo=true;
                }
                if(n2->cercamueble(n2->getmuebles()[0].getposicionx(),n2->getmuebles()[0].getposiciony())==true){
                    if(event->key()==Qt::Key_E){
                        izquierda=false;
                        derecha=false;
                        correr=false;
                        arriba=false;
                        abajo=false;
                        estado=escritorio;
                        texotint->setText("1-6: Leer nota | Esc: Salir");
                        texotint->setVisible(true);
                        notaAbierta->setPixmap(QPixmap(":/assets/nota1.png").scaled(300, 400, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                        notaAbierta->setVisible(true);
                    }
                }
                else if(n2->cercamueble(n2->getmuebles()[1].getposicionx(),n2->getmuebles()[1].getposiciony())==true){
                    if(event->key()==Qt::Key_E){
                        izquierda=false;
                        derecha=false;
                        correr=false;
                        arriba=false;
                        abajo=false;
                        estado=tablero;
                        texotint->setText("1-6: Intercambiar | Esc: Salir");
                        texotint->setVisible(true);
                        for (int i=0;i<6;i++) {
                            int id=n2->getnotas()[i].getid();
                            nota[i]->setPixmap(QPixmap(QString(":/assets/nota%1.png").arg(id)).scaled(150,200,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                            nota[i]->setVisible(true);
                        }
                    }
                }
            }
        }
    }
    else if(estado==Perdiste){
        if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter){
            estado=Menu;
            vista->setScene(menu);
            opcion=0;
            btnfacil->setVisible(false);
            btnnormal->setVisible(false);
            btndificil->setVisible(false);
            actualizarbotones();
        }
    }
    else if(estado==ganaste){
        if(event->key()==Qt::Key_Return||event->key()==Qt::Key_Enter){
            estado=Menu;
            vista->setScene(menu);
            opcion=0;
            btnfacil->setVisible(false);
            btnnormal->setVisible(false);
            btndificil->setVisible(false);
            actualizarbotones();
        }
    }
    else if(estado==escritorio){
        if(event->key()>=Qt::Key_1&& event->key()<=Qt::Key_6){
            int num=event->key()-Qt::Key_0;
            notaAbierta->setPixmap(QPixmap(QString(":/assets/nota%1.png").arg(num)).scaled(300, 400));
            notaAbierta->setVisible(true);
        }
        else if (event->key()==Qt::Key_Escape){
            notaAbierta->setVisible(false);
            texotint->setVisible(false);
            estado=jugando;
        }
    }
    else if(estado==tablero){
        nivel2 *n2=dynamic_cast<nivel2*>(actual);
        if(n2!=nullptr){
            if(event->key()>=Qt::Key_1&&event->key()<=Qt::Key_6){
                int idx=event->key()-Qt::Key_1;
                n2->seleccionar(idx);
                for(int i=0;i<6;i++){
                    int id=n2->getnotas()[i].getid();
                    nota[i]->setPixmap(QPixmap(QString(":/assets/nota%1.png").arg(id)).scaled(150,200,Qt::KeepAspectRatio,Qt::SmoothTransformation));
                }
                if (n2->getcompletado()==true){
                    texotint->setVisible(false);
                    estado=ganaste;
                    vista->setScene(Ganaste);
                }
            }
            else if(event->key()==Qt::Key_Escape){
                for(int i=0;i<6;i++){
                    nota[i]->setVisible(false);
                }
                texotint->setVisible(false);
                estado=jugando;
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
        else if(event->key()==Qt::Key_Up||event->key()==Qt::Key_W){
            arriba=false;
        }
        else if(event->key()==Qt::Key_Down||event->key()==Qt::Key_S){
            abajo=false;
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
                for(int i=0;i<15;i++){
                    mira[i]->setVisible(false);
                }
            }
        }
    }
    else if(obj==vista->viewport()&&event->type()==QEvent::MouseMove){
        if(estado==jugando&&actual!=nullptr){
            nivel1 *n1=dynamic_cast<nivel1*>(actual);
            if (n1!=nullptr&& n1->getagente().getcontrol()==true){
                QMouseEvent *mouseEvent=static_cast<QMouseEvent*>(event);
                QPointF posMapa=vista->mapToScene(mouseEvent->pos());
                float px=n1->getagente().getposicionx();
                float py=n1->getagente().getposiciony();
                float angulo=qAtan2(posMapa.y()-py,posMapa.x()-px);
                float vx=15.0f*qCos(angulo);
                float vy=15.0f*qSin(angulo);
                for (int i=0;i<15;i++) {
                    px+=vx;
                    py+=vy;
                    vy+=0.5f;
                    mira[i]->setPos(px,py);
                    mira[i]->setVisible(true);
                }
            }
        }
    }
    return QMainWindow::eventFilter(obj, event);
}
void MainWindow::actualizartiempo(){
    segundosRestantes--;
    int min=segundosRestantes/60;
    int seg=segundosRestantes%60;
    labeltiempo->setText(QString("%1:%2").arg(min,2,10,QChar('0')).arg(seg,2,10,QChar('0')));
    if(segundosRestantes<=0){
        reloj->stop();
        estado=Perdiste;
        derecha=izquierda=correr=interactuo=false;
        labelpistas->setVisible(false);
        labeltiempo->setVisible(false);
        texotint->setVisible(false);
        vista->setScene(perdiste);
    }
}
void MainWindow::actualizarjuego(){
    if(estado==jugando&&actual!=nullptr){
        actual->actualizar();
        nivel1 *n1 = dynamic_cast<nivel1*>(actual);
        if(n1!=nullptr){
            sherlock* jugador=&n1->getjugador();
            watson* agente=&n1->getagente();
            int recolectadas=0;
            std::array<pista,6>& pistasas=n1->getpistas();
            spriteSherlock->setPos(jugador->getposicionx(),jugador->getposiciony());
            spriteWatson->setPos(agente->getposicionx(),agente->getposiciony());
            vista->centerOn(jugador->getposicionx(),jugador->getposiciony());
            for(int i=5;i>=0;i--){
                if(pistasas[i].getrecolectado()==true){
                    pistas[i]->setVisible(false);
                    recolectadas++;
                }
                pistas[i]->setPos(pistasas[i].getposicionx(),pistasas[i].getposiciony());
            }
            labelpistas->setText("Pistas: "+QString::number(recolectadas)+"/6");
            if(recolectadas==6){
                iniciarnivel2();
                return;
            }
            std::vector<plataforma>& plataformas=n1->getplataformas();
            for(int i=plataformas.size()-1;i>=0;i--){
                plataform[i]->setVisible(plataformas[i].getactivo());
                plataform[i]->setPos(plataformas[i].getposicionx(),plataformas[i].getposiciony());
            }
            if(jugador->getgancho()==true){
                cuerda->setVisible(true);
                cuerda->setLine(jugador->getposicionx()+16, jugador->getposiciony()+16,jugador->getpivotex(),jugador->getpivotey());
            }
            else{
                cuerda->setVisible(false);
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
                jugador->setv(0,jugador->getvy());
            }
            else if(lanzado==false){
                jugador->setv(0,jugador->getvy());
            }
            int ancho=hojaSherlock.width()/3;
            int alto=hojaSherlock.height()/2;
            if(derecha==true){
                mirandoderecha=true;
            }
            else if(izquierda==true){
                mirandoderecha=false;
            }
            if(jugador->getp()==false&&jugador->getgancho()==false){
                int anchos=saltosherlock.width()/3;
                int altos=saltosherlock.height();
                int col=(jugador->getvy()<0)?2:1;
                QPixmap frame=saltosherlock.copy(col*anchos,0,anchos,altos).scaled(32,32);
                if(mirandoderecha==false){
                    frame=frame.transformed(QTransform().scale(-1, 1));
                }
                spriteSherlock->setPixmap(frame);
            }
            else{
                if((derecha==true||izquierda==true)&&jugador->getp()==true){
                    contadoranim++;
                    if (contadoranim>=6){
                        contadoranim=0;
                        frameactual=(frameactual+1)%3;
                    }
                }
                else{
                    contadoranim=0;
                    frameactual=mirandoderecha?0:2;
                }
                int fila=mirandoderecha?1:0;
                spriteSherlock->setPixmap(hojaSherlock.copy(frameactual*ancho,fila*alto,ancho,alto).scaled(32,32));
            }
            if(agente->getvx()>0){
                mirandoderechaw=true;
            }
            else if(agente->getvx()<0){
                mirandoderechaw=false;
            }
            int anchow=hojaWatson.width()/3;
            int altow=hojaWatson.height();
            if(agente->getvx()!=0&&agente->getp()==true){
                contadoranimw++;
                if(contadoranimw>=6){
                    contadoranimw=0;
                    frameactualw=(frameactualw+1)%3;
                }
            }
            else{
                contadoranimw=0;
                frameactualw=0;
            }
            QPixmap framew=hojaWatson.copy(frameactualw*anchow,0,anchow,altow).scaled(32,32);
            if(mirandoderechaw==false){
                framew=framew.transformed(QTransform().scale(-1,1));
            }
            spriteWatson->setPixmap(framew);
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
        nivel2 *n2=dynamic_cast<nivel2*>(actual);
        if(n2!=nullptr){
            watson* jugador=&n2->getjugador();
            spriteWatson->setPos(jugador->getposicionx(),jugador->getposiciony());
            if(derecha==true){
                jugador->moverse(true,correr);
            }
            else if(izquierda==true){
                jugador->moverse(false,correr);
            }
            else{
                jugador->setv(0,jugador->getvy());
            }
            if(arriba==true){
                jugador->moversevertical(true,correr);
            }
            else if(abajo==true){
                jugador->moversevertical(false,correr);
            }
            else{
                jugador->setv(jugador->getvx(),0);
            }
            if(arriba==true){
                dirwatson=0;
            }
            else if(abajo==true){
                dirwatson=1;
            }
            else if(derecha==true){
                dirwatson=2;
            }
            else if(izquierda==true){
                dirwatson=3;
            }

            if(arriba || abajo || derecha || izquierda){
                contadoranimw++;
                if (contadoranimw>=6){
                    contadoranimw=0;
                    frameactualw=(frameactualw+1)%3;
                }
            }
            else{
                contadoranimw=0;
                frameactualw=0;
            }
            if(dirwatson==0||dirwatson==1){
                int anchov=verticalwatson.width()/3;
                int altov=verticalwatson.height()/2;
                spriteWatson->setPixmap(verticalwatson.copy(frameactualw*anchov,dirwatson*altov,anchov,altov).scaled(32,45));
            }
            else{
                int anchow=hojaWatson.width()/3;
                int altow=hojaWatson.height();
                QPixmap framew=hojaWatson.copy(frameactualw*anchow,0,anchow,altow).scaled(32,45);
                if(dirwatson == 3){
                    framew=framew.transformed(QTransform().scale(-1,1));
                }
                spriteWatson->setPixmap(framew);
            }
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
    delete actual;
}
