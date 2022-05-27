#include "util.hpp"


void* (*caesarCipher)(void* data)
{
    data* d = (data*)data;
    std::string text = (std::string)d->getText();
    state state = (state)d->getState();
    std::string result = "";
    if (state == state::begin) {
        
        for (int i = 0; i < text.length(); i++)
        {
            if (text.at(i) == ' ')
            {
                result += ' ';
            }
            else if (isalpha(text.at(i)))
            {
                if (isupper(text.at(i)))
                {
                    result += (char)(((int)text.at(i) + 3 - 65) % 26 + 65);
                }
                else
                {
                    result += (char)(((int)text.at(i) + 3 - 97) % 26 + 97);
                }
            }
            else
            {
                result += text.at(i);
            }
        }

    }
    d->setState(state::siphered);
    d->setText(result);
    return d; 
}


void* (*reverseCapitalization)(void* data)
{
    data* d = (data*)data;
    std::string text = (std::string)d->getText();
    state state = (state)d->getState();
    std::string result = "";
    if (state == state::siphered) {
        
        for (int i = 0; i < text.length(); i++)
        {
            if (text.at(i) == ' ')
            {
                result += ' ';
            }
            else if (isalpha(text.at(i)))
            {
                if (isupper(text.at(i)))
                {
                    result += tolower(text.at(i));
                }
                else
                {
                    result += toupper(text.at(i));
                }
            }
            else
            {
                result += text.at(i);
            }
        }

    }
    d->setState(state::decapitalized);
    d->setText(result);
    return d;
}


void* (*sendResult)(void* data)
{
    data* d = (data*)data;
    std::string text = (std::string)d->getText();
    int fd = d->getFd();
    state state = (state)d->getState();
    int check;
    if (state == state::decapitalized) {
        check = send(fd, text.c_str(), text.length(), 0);
    }
    d->setState(state::end);
    return d;
}


void (*moveToNext)(void* data)
{
    data* d = (data*)data;
    state state = (state)d->getState();
    switch (state) {
        case state::siphered:
            queue1.enQ(data);
            break;
        case state::decapitalized:
            queue2.enQ(data);
            break;
        case state::end:
            queue3.enQ(data);
            break;
        default:
            break;
    }
    
}