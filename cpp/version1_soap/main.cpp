#include <iostream>
#include <string>
#include <regex>
#include <cstdio>
#include <sstream>
#include <fstream>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#define popen _popen
#define pclose _pclose
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define closesocket close
#endif

using namespace std;

string runCmd(const string& cmd) {
    char buffer[256];
    string result;

    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";

    while (fgets(buffer, sizeof(buffer), pipe)) {
        result += buffer;
    }

    pclose(pipe);
    return result;
}

string numberToWords(string n) {
    string body =
        "<soapenv:Envelope xmlns:soapenv=\"http://schemas.xmlsoap.org/soap/envelope/\" "
        "xmlns:web=\"http://www.dataaccess.com/webservicesserver/\">"
        "<soapenv:Header/>"
        "<soapenv:Body>"
        "<web:NumberToWords>"
        "<web:ubiNum>" + n + "</web:ubiNum>"
        "</web:NumberToWords>"
        "</soapenv:Body>"
        "</soapenv:Envelope>";

    ofstream file("soap_request.xml", ios::binary);
    file << body;
    file.close();

    string cmd =
        "curl.exe -s -X POST \"https://www.dataaccess.com/webservicesserver/NumberConversion.wso\" "
        "-H \"Content-Type: text/xml; charset=utf-8\" "
        "-H \"SOAPAction: http://www.dataaccess.com/webservicesserver/NumberToWords\" "
        "--data-binary \"@soap_request.xml\"";

    string xml = runCmd(cmd);

    regex re("<m:NumberToWordsResult>(.*?)</m:NumberToWordsResult>|<NumberToWordsResult>(.*?)</NumberToWordsResult>");
    smatch m;

    if (regex_search(xml, m, re)) {
        return m[1].matched ? m[1].str() : m[2].str();
    }

    return xml;
}

int main() {
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2, 2), &wsa);
#endif

    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(3000);

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 5);

    cout << "Servidor en http://localhost:3000/?n=10" << endl;

    while (true) {
        int c = accept(server_fd, nullptr, nullptr);

        char buf[2048] = {0};
        recv(c, buf, 2047, 0);

        string req(buf);
        smatch m;
        string n = "10";

        if (regex_search(req, m, regex("\\?n=([0-9]+)"))) {
            n = m[1];
        }

        string out = numberToWords(n);

        string resp =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/plain; charset=utf-8\r\n"
            "\r\n" + out;

        send(c, resp.c_str(), resp.size(), 0);
        closesocket(c);
    }

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}