#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QTimer>
#include <QKeyEvent>
#include <QPushButton>
#include "nivel1.h"
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
    QWidget *pausa;
    QTimer *tiempo;
    nivel *actual;
    QPushButton *btnjugar;
    QPushButton *btnsalir;
    QPushButton *btnfacil;
    QPushButton *btnnormal;
    QPushButton *btndificil;
    enum Estado{Inicio,Menu,dificultad,jugando,Pausa};
    Estado estado;
    short int opcion;


private slots:
    void actualizarjuego();
    void actualizarbotones();
    void iniciarnivel(short int dif);

protected:
    void keyPressEvent(QKeyEvent *event) override;
};
#endif // MAINWINDOW_H
