#include <iostream>
#include <string>
#include <map>
#include <regex>
#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define closesocket close
#endif
using namespace std;
string u(int n){string a[]={"cero","uno","dos","tres","cuatro","cinco","seis","siete","ocho","nueve"};return a[n];}
string c(int n){map<int,string>e={{10,"diez"},{11,"once"},{12,"doce"},{13,"trece"},{14,"catorce"},{15,"quince"},{16,"dieciseis"},{17,"diecisiete"},{18,"dieciocho"},{19,"diecinueve"},{20,"veinte"},{21,"veintiuno"},{22,"veintidos"},{23,"veintitres"},{24,"veinticuatro"},{25,"veinticinco"},{26,"veintiseis"},{27,"veintisiete"},{28,"veintiocho"},{29,"veintinueve"}};map<int,string>d={{30,"treinta"},{40,"cuarenta"},{50,"cincuenta"},{60,"sesenta"},{70,"setenta"},{80,"ochenta"},{90,"noventa"}};map<int,string>ci={{100,"cien"},{200,"doscientos"},{300,"trescientos"},{400,"cuatrocientos"},{500,"quinientos"},{600,"seiscientos"},{700,"setecientos"},{800,"ochocientos"},{900,"novecientos"}};if(n<10)return u(n);if(e.count(n))return e[n];if(n<100){int de=n/10*10,un=n%10;return un?d[de]+" y "+u(un):d[de];}if(ci.count(n))return ci[n];int ce=n/100*100,r=n%100;return (ce==100?"ciento":ci[ce])+" "+c(r);}
string num(int n){if(n==0)return"cero";if(n<0)return"menos "+num(-n);if(n<1000)return c(n);if(n<1000000){int m=n/1000,r=n%1000;string p=m==1?"mil":num(m)+" mil";return r?p+" "+c(r):p;}int m=n/1000000,r=n%1000000;string p=m==1?"un millon":num(m)+" millones";return r?p+" "+num(r):p;}
int main(){
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    int server_fd=socket(AF_INET,SOCK_STREAM,0);sockaddr_in addr{};addr.sin_family=AF_INET;addr.sin_addr.s_addr=INADDR_ANY;addr.sin_port=htons(3000);bind(server_fd,(sockaddr*)&addr,sizeof(addr));listen(server_fd,5);cout<<"Servidor en http://localhost:3000/?n=10\n";while(true){int cl=accept(server_fd,nullptr,nullptr);char buf[2048]={0};recv(cl,buf,2047,0);string req(buf);smatch m;int n=10;if(regex_search(req,m,regex("\\?n=([0-9]+)")))n=stoi(m[1]);string out=num(n);string resp="HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n"+out;send(cl,resp.c_str(),resp.size(),0);closesocket(cl);} }
