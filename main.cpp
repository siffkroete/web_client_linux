#include "include/Socket.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;


#define PORT 1500
const std::string dest_server = "localhost";






// Client vom Buch C++ von A bis Z und zwar mit selbstgeschriebener Klasse
int client_3(int argc, char** argv)
{
    Util::sleep(20 / 1000);
    cout << endl << "Start Client!" << endl;

    try {
        Socket sock("Client");
        sock.create();

        // Adresse des Servers
        string server_addr = dest_server; //  94.126.18.110

        // Mit dem Server verbinden
        bool r_conn = sock.connect(server_addr, PORT);

        // Nachricht an den Server
        string msg_to_server = "GET / index.php HTTP / 1.1\r\n""Host: " + server_addr + "\r\n""\r\n";
        string msg_from_server = "";

        sock << msg_to_server; // Client sendet
        sock >> msg_from_server; // Cleint bekommt Antwort vom Server
        cout << endl << "Client: Antwort bekommen: " << msg_from_server;
        return 0;
    }
    catch (SocketException& e) {
        cout << endl << "Client: " << e.what();
    }
    catch (exception& e) {
        cout << endl << "Clien: " << e.what();
    }
    catch (...) {
        cout << endl << "Clien: Unbekannter Fehler!";
    }

    return 1;
}



int main(int argc, char** argv)
{
    cout << endl << "Hi Welt!" << endl;
    return client_3(argc, argv);
    // return 0;
}