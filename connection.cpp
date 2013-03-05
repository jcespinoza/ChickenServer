#include "connection.h"

Connection::Connection(QTcpSocket *_socket)
{
    socket = _socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(recv()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnect()));
    this->indice_lista_conexion = -1;
    veces=0;

}

void Connection::recv() {
        message.append(socket->readAll());

        int pos;
        while((pos = message.indexOf("\n\r")) > -1) {
                parseMessage(QString(message.left(pos+2)));
                message = message.mid(pos+2);
        }
}
void Connection::parseMessage(QString msg) {

       if(msg.startsWith("MSG:"))
       {
           msg = "MSGFROM:" + this->nick+ ":" + msg.mid(4);
           emit newMessage(this,msg);
       }

          if(msg.startsWith("CON:")) {
                // Obtener el nick
                QString elresto = msg.mid(4 );
                this->nick = elresto.mid(0,elresto.length()-2) ;
                emit connected(this, nick);
            }
        if(msg.startsWith("MOVE:"))
          {
                QString elresto = msg.mid(5 );
                elresto=elresto.mid(0,elresto.length()-2) ; // Quitarle \n\r
                emit newMove(this, elresto);
        }
        if(msg.startsWith("REMOVE:")){
            QString rest = msg.mid(7);
            rest = rest.mid(0,rest.length()-2);
            emit removePieza(this, rest);
        }


}
void Connection::sendMessage(QString msg) {
    //READ: Si el socket de la conexion es valido entonces enviar el mensaje
    // Pero convertirlo en ASCII
    if (socket->isValid())
        socket->write(msg.toLatin1());

}
void Connection::disconnect() {
       //READ: Emitir una señal al server para desconectarse
        emit disconnected(this, nick);

}

void Connection::sendNicks(QStringList *nicks) {
        //READ: Enviar la lista de nicks separadas por comas
        //si no hay entonces envia una letra X
         if(nicks->size() != 0) {
                sendMessage("NICKLIST:" + nicks->join(",") + "\n\r");
        } else {
                sendMessage("NICKLIST:X\n\r");
        }
}
