#include "server.h"

Server::Server()
{
    //READ: Iinicializar la bandera en false, enlazar o conectar el evento o señal
    // de newConnection que genere una instancia de esta clase y que la reciba y procese
    // esta misma instancia por el SLOT newConnection ..
    // Limpiar la lista de conexiones
    // Hacer que el apuntador al TextEdit(Log) sea nulo
    this->server_started = false;
    connect(this, SIGNAL(newConnection()), this, SLOT(newConnection()));
    this->Lista_Conexiones.clear();
    this->casillas = 0; // llleva un recuento si ya se llenaron las 64 casillas
    this->log = 0;
    for (int i=0; i<8 ; i++)
      for (int j=0; j<8 ; j++)
          this->TABLERO[i][j]=-1;


}
void Server::reset()
{
    for (int i=0; i<8 ; i++)
      for (int j=0; j<8 ; j++)
          this->TABLERO[i][j]=-1;
    this->casillas=0;
     int i=0;
    while (i<this->Lista_Conexiones.count())
   {
        this->Lista_Conexiones.at(i)->veces=0;
        i++;
   }

}

Server::~Server()
{
    //READ: Simplemente llamar al metodo STOP que hace toda la limpieza
    this->stop();
}

void Server::start(int port,int cuantas_conexiones)
{
    //READ: Bueno iniciar el server siempre y cuando NO se haya iniciado previamente
    // para eso se revisa la bandera. Luego ejecutamos el metodo LISTEN para escuchar
    // en el puerto que recibe de parametro, en caso que no pueda escuchar en ese
    // puerto porque por ejemplo puede que ya este ocupado entonces, mostrar un mensaje
    // y dejar en false la bandera.
    // Si logra arranca, entonces colocar la bandera en True, instancia la nickList
    // Limpia la lista de conexiones y muestra un mensaje en el LOG.
    if (this->server_started==false)
    {
        if (listen(QHostAddress::Any, port))
        {
           this->server_started = true;
           this->nickList = new QStringList();
           this->Lista_Conexiones.clear();
           this->log->append(tr("Servidor iniciado en puerto :%1 ").arg(port));
           this->Cantidad_Conexiones = cuantas_conexiones;
        }
        else
        {
            this->server_started = false;
            this->log->append(tr("Servidor no se pudo iniciar :%1 ").arg(this->errorString()));
        }
    }

}
void Server::stop()
{
    if (this->server_started)
    {

      this->server_started = false;
      delete this->nickList;
      // Limpiar la lista de conexiones

       while (!this->Lista_Conexiones.isEmpty())
         {
            // this->Lista_Conexiones.at(0)->disconnect(); //Desconectar la conexion

             Connection *cTemp= this->Lista_Conexiones.takeFirst();  // Libera el apuntador
             cTemp->sendMessage("SERVERSTOP:\n\r");
             cTemp->socket->close();
             delete cTemp;
         }
        //Cerrar el socket del server
        this->close();
        this->Cantidad_Conexiones=0;
        this->casillas=0;
        this->log->append(tr("Servidor detenido!!! "));
    }

}
bool Server::getStatus()
{
    return this->server_started;
}
void Server::newConnection() {
        // Cuando se crea la conexion la enlazo agregandola a lista de conexiones

    if(this->Lista_Conexiones.count()<this->Cantidad_Conexiones)
    {
        Connection *con = new Connection(nextPendingConnection());
         // Agregarla a la lista de conexiones
        this->Lista_Conexiones.push_back(con);
        // Decirle a la conexion en que posicion de la lista la agregaron
        con->indice_lista_conexion = this->Lista_Conexiones.count()-1;

        connect(con, SIGNAL(newMessage(Connection*,QString)), this, SLOT(procesarMensaje(Connection*,QString)));
        connect(con, SIGNAL(newMove(Connection*,QString)), this, SLOT(procesarMovimiento(Connection*,QString)));

        // connect(this, SIGNAL(newMessage(QString)), con, SLOT(sendMessage(QString)));
        connect(con, SIGNAL(connected(Connection*, QString)), this, SLOT(connected(Connection*, QString)));
        connect(con, SIGNAL(disconnected(Connection*, QString)), this , SLOT(disconnected(Connection*, QString)));

        this->log->append("Nueva conexion..." + con->socket->peerAddress().toString());
    }
    else
    {
        this->nextPendingConnection()->close();
        this->log->append("Conexion rechazada, se llego al limite..." );
     }
}
void Server::connected(Connection* con, QString nick) {
        //Enviar los Nicks ya existentes
        //TODO: Se deberia validar un nick repetido
        con->sendNicks(this->nickList);
        this->log->append("Nicks enviados al resto...");
        nickList->push_back(nick);
        con->nick=nick;
        // Enviar un mensaje a todos de este nuevo Nick
        this->sendMessage("NEWNICK:"+nick + "\n\r");
        this->log->append(nick + " [" + con->socket->peerAddress().toString() + "] connected");


}

void Server::disconnected(Connection* con, QString nick) {
        //con->deleteLater();
        int index = nickList->indexOf(nick);
        nickList->removeAt(index);
        // Remover de la lista de conexiones.
        this->log->append(nick + " disconnected");

        this->Lista_Conexiones.at(con->indice_lista_conexion)->socket->close();

        //Avisar al resto que se desconecto
        this->sendMessage("OLDNICK:"+nick + "\n\r");

}
void Server::sendMessage(QString mensaje)
{ // Recorrer la lista de conexiones y enviar
   int i=0;
    while (i<this->Lista_Conexiones.count())
   {
    //TODO: Deberiamos validar el estado de la conexion
        // Para no tratar de enviar en Conexiones cerradas
        // O en el disconnect asegurarse de poner en estado no valida
        // la conexion. Porque sino se pierde el indice.
        if(this->Lista_Conexiones.at(i)->socket->isValid())
           this->Lista_Conexiones.at(i)->sendMessage(mensaje);
    i++;
   }


}
void Server::procesarMensaje(Connection *con, QString mensaje)
{
    int i=0;
    while (i<this->Lista_Conexiones.count())
   {
        // Enviar al resto lo que recibimos de con, inclusive al mismo (ECHO)
        if(this->Lista_Conexiones.at(i)->socket->isValid())
        {
            this->log->append(con->nick+">>Enviando:(" +this->Lista_Conexiones.at(i)->nick+"):" + mensaje);
            this->Lista_Conexiones.at(i)->sendMessage(mensaje);
         }
    i++;
   }

}

void Server::procesarMovimiento(Connection *con, QString mensaje)
{
    // OBtener de mensaje las coordenadas o posiciones donde desea moverse
    // ya sabemos que jugador es atravez de la Connection *con, y asi sabemos
    // su numero
    // El mensaje viene asi :  3:7
    bool band;
     int fila =mensaje.mid(0,1).toInt(&band,10);
     int col = mensaje.mid(2,1).toInt(&band,10);
     if (this->TABLERO[fila][col]==-1) // Esta libre
     {   // Setear el numero de jugador o indice en esa posicion del tablero
         // Enviar el mensaje al resto
         this->TABLERO[fila][col]= con->indice_lista_conexion;
         QString temp;
         temp.setNum(con->indice_lista_conexion,10);
         temp= temp + ":" + mensaje.mid(0,1) + ":" + mensaje.mid(2,1) + "\n\r";
         this->sendMessage("MOVEOK:"+ temp);
         this->log->append(temp);
         con->veces++;  // Aumentar la cantidad de veces que ha puesto fichas exitosamente
         this->casillas++;
         if (casillas == 64)
         {
             this->log->append("Bueno se llenaron las casillas, ya no hay nada mas que hacer");
             // Ver quien gano.
              int i=0;
              QString mens;
              while (i<this->Lista_Conexiones.count())
               {
                  QString temp;
                  temp.setNum(this->Lista_Conexiones.at(i)->veces,10);
                  mens = mens + this->Lista_Conexiones.at(i)->nick + ">" + temp + " ; ";

                i++;
               }
              mens = "INFO:" + mens + "\n\r";
              // Les envio el score final
              this->sendMessage(mens);

         }

     }
}
