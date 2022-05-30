#include "util.hpp"

void *caesarCipher(void *newData)
{
    data *d = (data *)newData;
    std::string text = (std::string)d->getText();
    state s = (state)d->getState();
    std::string result = "";
    if (s == state::begin)
    {

        for (uint i = 0; i < text.length(); i++)
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

void *reverseCapitalization(void *newData)
{
    data *d = (data *)newData;
    std::string text = (std::string)d->getText();
    state s = (state)d->getState();
    std::string result = "";
    if (s == state::siphered)
    {

        for (uint i = 0; i < text.length(); i++)
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

void *sendResult(void *newData)
{
    data *d = (data *)newData;
    std::string text = (std::string)d->getText();
    int fd = d->getFd();
    state s = (state)d->getState();
    // int check;
    if (s == state::decapitalized)
    {
        send(fd, text.c_str(), text.length(), 0);
    }
    d->setState(state::end);
    return d;
}

void *moveToNext(void *newData, void* object)
{   
    activeObject *ob = (activeObject *)object;
    data *d = (data *)newData;
    state s = (state)d->getState();
    switch (s)
    {
    case state::siphered:
        ob->getQueue()->enQ(d);
        break;
    case state::decapitalized:
        ob->getQueue()->enQ(d);
        break;
    case state::end:
        ob->getQueue()->enQ(d);
        break;
    default:
        break;
    }
    return NULL;
}