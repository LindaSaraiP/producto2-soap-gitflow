#include <iostream>
#include <string>
#include <regex>
#include <cstdio>
#include <map>
#include <fstream>
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
string runCmd(const string& cmd){char buffer[256];string result;FILE* pipe=popen(cmd.c_str(),"r");if(!pipe)return"";while(fgets(buffer,sizeof(buffer),pipe))result+=buffer;pclose(pipe);return result;}
string numberToWords(string n){string body="<?xml version=\"1.0\" encoding=\"utf-8\"?><soap:Envelope xmlns:soap=\"http://schemas.xmlsoap.org/soap/envelope/\"><soap:Body><NumberToWords xmlns=\"http://www.dataaccess.com/webservicesserver/\"><ubiNum>"+n+"</ubiNum></NumberToWords></soap:Body></soap:Envelope>";ofstream file("soap_request.xml");file<<body;file.close();string cmd="curl -s -X POST https://www.dataaccess.com/webservicesserver/NumberConversion.wso -H \"Content-Type: text/xml; charset=utf-8\" -H \"SOAPAction: http://www.dataaccess.com/webservicesserver/NumberToWords\" --data-binary @soap_request.xml";string xml=runCmd(cmd);regex re("<m:NumberToWordsResult>(.*?)</m:NumberToWordsResult>|<NumberToWordsResult>(.*?)</NumberToWordsResult>");smatch m;if(regex_search(xml,m,re))return m[1].matched?m[1].str():m[2].str();return xml;}
string repl(string s,string a,string b){size_t pos=0;while((pos=s.find(a,pos))!=string::npos){s.replace(pos,a.size(),b);pos+=b.size();}return s;}
string translate(string s){map<string,string>d={{"zero","cero"},{"one","uno"},{"two","dos"},{"three","tres"},{"four","cuatro"},{"five","cinco"},{"six","seis"},{"seven","siete"},{"eight","ocho"},{"nine","nueve"},{"ten","diez"},{"eleven","once"},{"twelve","doce"},{"thirteen","trece"},{"fourteen","catorce"},{"fifteen","quince"},{"sixteen","dieciseis"},{"seventeen","diecisiete"},{"eighteen","dieciocho"},{"nineteen","diecinueve"},{"twenty","veinte"},{"thirty","treinta"},{"forty","cuarenta"},{"fifty","cincuenta"},{"sixty","sesenta"},{"seventy","setenta"},{"eighty","ochenta"},{"ninety","noventa"},{"hundred","cien"},{"thousand","mil"},{"million","millon"},{"millions","millones"},{"and","y"}};for(auto&p:d)s=repl(s,p.first,p.second);return s;}
int main(){
#ifdef _WIN32
    WSADATA wsa;
    WSAStartup(MAKEWORD(2,2), &wsa);
#endif
    int server_fd=socket(AF_INET,SOCK_STREAM,0);sockaddr_in addr{};addr.sin_family=AF_INET;addr.sin_addr.s_addr=INADDR_ANY;addr.sin_port=htons(3000);bind(server_fd,(sockaddr*)&addr,sizeof(addr));listen(server_fd,5);cout<<"Servidor en http://localhost:3000/?n=10\n";while(true){int c=accept(server_fd,nullptr,nullptr);char buf[2048]={0};recv(c,buf,2047,0);string req(buf);smatch m;string n="10";if(regex_search(req,m,regex("\\?n=([0-9]+)")))n=m[1];string out=translate(numberToWords(n));string resp="HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=utf-8\r\n\r\n"+out;send(c,resp.c_str(),resp.size(),0);closesocket(c);} }
