#include "data.hpp"


data::data(std::string text, int fd) : text(text), fd(fd), s(state::begin) {}

int data::getFd()
{
    return this->fd;
}

void data::setFd(int newFd)
{
    this->fd =newFd;
}

state &data::getState()
{
    return this->s;
}
void data::setState(state other)
{
    this->s = other;
}
void data::setText(std::string text)
{
    this->text = text;
}

std::string data::getText()
{
    return this->text;
}