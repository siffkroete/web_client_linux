#ifndef __UTIL_H__
#define __UTIL_H__


#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <errno.h>

   


#define DEFAULT_BUFLEN 512
// "27015"
#define DEFAULT_PORT "55054" 




using namespace std;

class Util
{
public:
    // #include "web_client_2.cpp"
    static bool char_to_wchar(const char* c, wchar_t* buf, size_t max_length = 255)
    {
        return false;
    }

    static bool wchar_to_char(const wchar_t* wc, char* buf, int max_length = 255)
    {
        
        return false;
    }


    static string get_err_msg(int err = 0)
    {
        return strerror(errno);
        /*
        char* msgbuf = nullptr;
        try {
            char* msgbuf = new char[512];
            msgbuf[0] = '\0';    // Microsoft doesn't guarantee this on man page.

            wchar_t wmsgbuf[512];

            Util::char_to_wchar(msgbuf, wmsgbuf, 512);

            FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,   // flags
                NULL,                                           // lpsource
                err,                                            // message id
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),      // languageid
                wmsgbuf,                                        // output buffer
                sizeof(wmsgbuf),                                // size of msgbuf, bytes
                NULL                                            // va_list of arguments
            );

            Util::wchar_to_char(wmsgbuf, msgbuf);
            string return_string(msgbuf);
            if (msgbuf != nullptr) delete[] msgbuf;
            return return_string;
        }
        catch (exception& e) {
            cout << endl << "Fehler in get_err_msg()! e.what(): " << e.what();
        }
        catch (...) {
            cout << endl << "Unbekannter Fehler in get_err_msg()!";
        }
        if (msgbuf != nullptr) delete[] msgbuf;
         */
        return string("");
    }

    static void sleep(int miliseconds) {
        std::this_thread::sleep_for(std::chrono::milliseconds(miliseconds));
    }

};


#endif