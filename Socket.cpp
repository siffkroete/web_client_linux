#include "Socket.h"



Socket::Socket(const string name) : m_sock(0), m_addr(), m_name(name)
{

}

Socket::~Socket()
{
    if (is_valid())
    {
        ::close(m_sock);
    }
}

// Erzeugt TCP Socket
bool Socket::create()
{
    m_sock = ::socket(AF_INET, SOCK_STREAM, 0);
    if (m_sock < 0) {
        throw SocketException(m_name + ": Fehler beim Anlegen des Sockets.");
    }
    int y = 1;
    setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, &y, sizeof(int));
    return true;
}

bool Socket::UDP_create()
{
    m_sock = ::socket(AF_INET, SOCK_DGRAM, 0);
    if(m_sock < 0){
        throw SocketException(m_name + "FEhler beim Anlegen des UDP Sockets");
    }
    return false;
}

// Bindet den socket an eine bestimmte Serveradresse und an einen bestimmten Port
bool Socket::bind(const int port)
{
    if (!is_valid()) return false;
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(port);

    int bind_return = ::bind(m_sock, (sockaddr*)&m_addr, sizeof(m_addr));
    if (bind_return == -1)  throw SocketException(m_name + ": Fehler bei bind()." + Util::get_err_msg());
    return true;
}

bool Socket::listen()
{
    if (!is_valid()) return false;
    int listen_return = ::listen(m_sock, MAXCONNECTIONS);
    if (listen_return == -1) throw SocketException(m_name + ": Fehler bei listen().");

    return true;
}

// Bearbeitet die Verbindungsw�nsche von Clients
// Der Aufruf von accept() blockiert so lange bis ein Client Verbindung aufnimmt.
bool Socket::accept(Socket& new_socket)
{
    int addr_length = sizeof(m_addr);
    new_socket.m_sock = ::accept(m_sock, (sockaddr*)&m_addr, (socklen_t*)&addr_length);
    if (new_socket.m_sock <= 0) throw SocketException(m_name + ": Fehler bei accept().");
    return true;
}

// Baut die Verbindung zum Server auf
bool Socket::connect(const string host, const int port)
{
    if (!is_valid()) return false;
    struct hostent* host_info;
    unsigned long addr;
    memset(&m_addr, 0, sizeof(m_addr));

    // Vom Tutorial und mir
    char host_addr[MAXRECV + 1];
   
    if (inet_pton(AF_INET, host_addr, &m_addr.sin_addr.s_addr) == 1)  // Vom Tutorial
    {
    }
    // End vom Tutorial und mir

    // Vom Buch
    /*
    #pragma warning(disable:4996)
    if ((addr = inet_addr(host.c_str())) != INADDR_NONE)
    {
        memcpy((char*)&m_addr.sin_addr, &addr, sizeof(addr));
    }
    */
    // End vom Buch
    else {
        struct addrinfo hints, * res;
        int err;
        memset(&hints, 0, sizeof(hints));
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_family = AF_INET;

        // F�r den FAll der F�lle: Wandle den Servernamen in eine IP-Adresse um
        /* Vom Buch
        * #pragma warning(disable:4996)
        * host_info = gethostbyname(host._cstr());
        * memcpy( (char*)&m_addr.sin_addr, &addr, sizeof(addr));
        */

        if ((err = getaddrinfo(host.c_str(), NULL, &hints, &res)) != 0) {
            throw SocketException(m_name + ": Unbekannte Adresse: " + host);
        }

        // memcpy((char*)&m_addr.sin_addr, host_info->h_addr, host_info->h_length); // Vom Buch 

        // Im Tutorial wurde das vorgeschlagen statt getaddrinfo() vom Buch
        // addr.S_un = ((struct sockaddr_in*)(res->ai_addr))->sin_addr.S_un; 
        m_addr.sin_addr = ((struct sockaddr_in*)(res->ai_addr))->sin_addr; // Vom Tutorial
    }

    m_addr.sin_family = AF_INET;
    m_addr.sin_port = htons(port);

    int status = ::connect(m_sock, (sockaddr*)&m_addr, sizeof(m_addr));

    if (status == 0)
        return true;
    else
        throw SocketException(m_name + ": Fehler in connect()");

}

// Daten versenden via TCP
bool Socket::send(const string s) const
{
    int status = ::send(m_sock, s.c_str(), s.size(), 0);
    if (status == -1)
        throw SocketException(m_name + ": Fehler in send()");
    else
        return true;
}

// Daten empfangen via TCP
int Socket::recv(string& s) const
{
    char buf[MAXRECV + 1];
    s = "";
    memset(buf, 0, MAXRECV + 1);

    int status = ::recv(m_sock, buf, MAXRECV, 0);
    if (status > 0 || status != -1) {
        s = buf;
        return status;
    }
    else {
        throw SocketException(m_name + "Fehler in Socket::recv()");
    }
    return 0;
}

bool Socket::UDP_send()
{
    return false;
}

bool Socket::UDP_recv()
{
    return false;
}

bool Socket::close() const
{
    ::close(m_sock);
    cleanup();
    return true;
}

void Socket::cleanup() const
{
   
}

const Socket& Socket::operator << (const string& s) const
{
    if (!Socket::send(s)) {
        throw SocketException(m_name + ": Fehler in in Socket::operator << (), Socket::send()");
    }
    return *this;
}
const Socket& Socket::operator >> (string& s) const
{
    if (!Socket::recv(s)) {
        throw SocketException(m_name + ": Fehler in in Socket::operator >> (), Socket::recv()");
    }
    return *this;
}