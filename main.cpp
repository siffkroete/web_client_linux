#include "include/Socket.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>

using namespace std;


#define PORT 80
// const string dest_server = "localhost";
// const string dest_server = "127.0.0.1";
// const string dest_server = " 0000:0000:0000:0000:0000:0000:0000:0001"; // localhost in ipv6 // Funktioniert noch nicht
// const string dest_server = "www.wenpas.com";
const string dest_server = "php-scripts.ch";






// Client vom Buch C++ von A bis Z und zwar mit selbstgeschriebener Klasse
int client_3(int argc, char** argv)
{
    Util::sleep(20 / 1000);
    cout << endl << "Start Client!" << endl;

    try {
        Socket sock("Client");
        sock.create();

        // Adresse des Servers
        string server_addr = dest_server; 

        // Mit dem Server verbinden
        bool r_conn = sock.connect(server_addr, PORT);

        // Nachricht an den Server
        // string new_line = "\r\n";
        string new_line = "\n"; // Mit diesem String richtige Antwort von wenpas.ch bekommen

        // Nachricht an den Server
        string msg_to_server = "GET /ip/wp-example-project/index.php?mode=dev HTTP/1.1" + new_line;
        msg_to_server += "Host: " + server_addr + new_line; 
        msg_to_server += "User Agent: Internet Explorer" + new_line;

        msg_to_server += "Accept: */*" + new_line;
        msg_to_server += "Accept-Language: de,fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3" + new_line;
        // msg_to_server += "Accept-Encoding: gzip,deflate" + new_line;
        // msg_to_server += "Accept-Charset: utf-8;q=0.7,*;q=0.7" + new_line;

        msg_to_server += "Keep-Alive: 15" + new_line;
        msg_to_server += "Connection: keep-alive" + new_line;
        // msg_to_server += "Content-Type: application/x-www-form-urlencoded" + new_line;
        msg_to_server += "Content-Type: text/html" + new_line;
        msg_to_server += "X-Requested-With: XMLHttpRequest" + new_line;
        msg_to_server += "Referer: Bla Bla etwas <script>alert(document.cookie);</script> und SQL Injection Bla Bla" + new_line;
        msg_to_server += "Cookie: foo=bar; lorem=ipsum;" + new_line;
        
        msg_to_server += (new_line + new_line);

        cout << endl << "Client: msg an Server: " << msg_to_server;
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