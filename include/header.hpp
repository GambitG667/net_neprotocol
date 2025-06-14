#include <cstddef>
#include <string>



class Message{
public:

int id;
std::string from;
std::string to;
std::string text;


    Message():id{0}, from{"Dow"}, to{"Dow"}, text{"text"}{}
    Message(int id, std::string from, std::string to, std::string text): id{id}, from{from}, to{to}, text{text} {}
    Message(std::string message){
        std::size_t a = 0;
        std::size_t b = 0;
        while(message.at(a+b) != ';'){
            b++;
        }
        id = std::stoi(message.substr(a,b));
        a = a+b+1;
        b = 0;
        while(message.at(a+b) != ';'){
            b++;
        }
        from = message.substr(a,b);
        
        a = a+b+1;
        b = 0;
        while(message.at(a+b) != ';'){
            b++;
        }
        to = message.substr(a, b);
        
        a = a+b + 1;
        b = message.length() - a;
        text = message.substr(a,b);
    }
    std::string to_string(){
        return std::to_string(id)+";"+from+";"+to+";"+text;
    }
};