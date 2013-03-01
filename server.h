#ifndef SERVER_H
#define SERVER_H

//READ: De las librerias ocupamos el TcpServer, la lista QList y por supuesto
//la libreria connection.h que es la que nosotros implementamos para administrar
// cada conexion
#include <QTcpServer>
#include <QStringList>
#include <QList>
#include <QTextEdit>
#include "connection.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    //READ: Constructor, destructor, metodos Start y Stop
    Server();
     ~Server();
    void start(int port,int cuantas_conexiones);
    void stop();
    //READ: Mantener una variable de Status
    bool getStatus();
    int Cuantas_Conexiones () { return this->Cantidad_Conexiones; }
    //READ: Este metodo envia mensajes a TODAS las conexiones abiertas y validaas
    // Recorre la lista de conexiones
    void sendMessage(QString mensaje);
    //READ: Tengamos una lista de conexiones, la hare publica para no hacer get ni set
    QList<Connection *> Lista_Conexiones;
     // Matriz de enteros que representa el tablero
    int TABLERO[8][8];
    int casillas;
    //READ: Un apuntador al textedit donde iremos colocando los mensajes
    QTextEdit *log;
    void reset();

 //READ: Los public slots son los metodos que se llaman cuando se generan ciertos eventos
 // en QT estos eventos se declaran como SIGNALS.
public slots:
        //READ: Slot que se ejecuta cuando se detecta la se�al o evento de una nueva conexion
        void newConnection();
        //READ: Slot que se ejecuta cuando el cliente ha confirmado la conexion enviando
        // su NICK
        void connected(Connection* con, QString nick);
        //READ: Slot que se ejecuta cuando un cliente se desconecta
        void disconnected(Connection *con, QString nick);
        //READ: Slot que se ejecuta cuando un cliente esta enviando mensajes al server
        // y estos mensajes deben enviarse al resto
        void procesarMensaje(Connection *con, QString mensaje);
        void procesarMovimiento(Connection *con, QString mensaje);

private:
        //READ: Tenemos una lista de nicks por separado aunque podriamos haber usado
        // la lista de conexiones
        QStringList *nickList;
        //READ: Tenemos una variable booleana que nos indica si el server ha iniciado o no
        bool server_started;
        int Cantidad_Conexiones;


};

#endif // SERVER_H
