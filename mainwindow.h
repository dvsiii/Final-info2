#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include "nivel1.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QLabel>
#include <QMouseEvent>
#include <QGraphicsLineItem>
#include <QGraphicsEllipseItem>
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    QGraphicsView *vista;
    QGraphicsScene *inicio;
    QGraphicsScene *menu;
    QGraphicsScene *juego;
    QGraphicsScene *perdiste;
    QLabel *labelpistas;
    QLabel *labeltiempo;
    QTimer *reloj;
    QTimer *tiempo;
    nivel *actual;
    QPushButton *btnjugar;
    QPushButton *btnsalir;
    QPushButton *btnfacil;
    QPushButton *btnnormal;
    QPushButton *btndificil;
    QGraphicsPixmapItem *spriteSherlock;
    QGraphicsPixmapItem *spriteWatson;
    std::array<QGraphicsEllipseItem*,15> mira;
    QPixmap hojaSherlock;
    QPixmap saltosherlock;
    QPixmap hojaWatson;
    bool mirandoderecha;
    int segundosRestantes;
    int frameactual;
    int contadoranim;
    bool mirandoderechaw;
    int frameactualw;
    int contadoranimw;
    bool derecha;
    bool izquierda;
    bool correr;
    bool interactuo;
    bool lanzado;
    QLabel *texotint;
    std::array<QGraphicsPixmapItem*,6> pistas;
    std::vector<QGraphicsPixmapItem*> plataform;
    QGraphicsPixmapItem* spritepuerta;
    QGraphicsPixmapItem* spriteboton;
    std::vector<QGraphicsPixmapItem*> ganchos;
    std::vector<QGraphicsPixmapItem*> bals;
    enum Estado{Inicio,Menu,dificultad,jugando,Perdiste};
    Estado estado;
    QGraphicsLineItem *cuerda;
    short int opcion;


private slots:
    void actualizarjuego();
    void actualizarbotones();
    void actualizartiempo();
    void iniciarnivel(short int dif);

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;
};
#endif // MAINWINDOW_H