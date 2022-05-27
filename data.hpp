#ifndef DATA_HPP
#define DATA_HPP

#include <iostream>
#include <stdexcept>
#include <string>

enum class state
{
    begin,
    siphered,
    decapitalized,
    end
};

class data
{
private:
    std::string text;
    int fd;
    state state;
public:
    data(std::string text, int fd) : text(text), fd(fd), state(state::begin) {}
    ~data();
    std::string getText();
    void setText(std::string text);
    int getFd();
    void setFd(int fd);
    state getState();
    void setState(state state);
    
};
   

#endif
