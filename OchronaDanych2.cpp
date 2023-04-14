#include <iostream>
#include <fstream>
#include <string>

int option;

std::string toUpperCase(std::string& str)
{
    for (int i = 0; i < str.length(); i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] = toupper(str[i]);
        }

    }
    return str;
}


void shift(std::string &txt)
{
    char temp;
    temp = txt[txt.size() - 1];
    txt[txt.size() - 1] = txt[0];
    for (int i = 0; i < txt.size()-1; i++)
    {
        if ((i + 1) == (txt.size() - 1))
            txt[i] = temp;
        else
            txt[i] = txt[i+1];
    }
}

void shiftRight(std::string& txt)
{
    char temp;
    temp = txt[0];
    txt[0] = txt[txt.size() - 1];
    for (int i = txt.size() - 1; i > 0; i--)
    {
        txt[i] = txt[i - 1];
    }
    txt[1] = temp;
}

char findLET(char let, char pass)
{
    std::string alfabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    std::string tab[27];
    int x, y;
    if(option == 1)
    {
        for (int i = 0; i < 27; i++)
        {
            tab[i] = alfabet;
            shift(alfabet);
        }
    }
    else
    {
        for (int i = 0; i < 27; i++)
        {
            tab[i] = alfabet;
            shiftRight(alfabet);
        }
    }
    
    /*std::cout << "-----------------------" << std::endl;
    for (int i = 0; i < 27; i++)
    {
        std::cout << tab[i] << std::endl;
    }
    std::cout << "-----------------------" << std::endl;*/

    for (int i = 0; i < alfabet.size(); i++)
    {
        if (alfabet[i] == let)
            x = i;
    }
    for (int i = 0; i < alfabet.size(); i++)
    {
        if (alfabet[i] == pass)
            y = i;
    }
    std::string result = tab[y];
    std::cout << tab[y] << " TO TA LITERA " << result[x] << " " << x << " " << y << " " << let << " " << pass<< std::endl;
    return result[x];
}

void szyfr(std::string &txt, std::string pass)
{
    std::string op = "";
    std::string result = "";
    for (int i = 0; i < txt.size(); i++)
    {
        op += pass[i % pass.size()];
    }
    std::cout << op << std::endl;
    for (int i = 0; i < txt.size(); i++)
    {
        if ((txt[i] >= 'A' && txt[i] <= 'Z') || txt[i] == ' ')
            result += findLET(txt[i], op[i]);
        else
            result += txt[i];
    }
    txt = result;
}



int main()
{
    std::string pass;
    std::string content = "";

    std::cout << "1-szyfruj 2-deszyfruj: ";
    std::cin >> option;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Podaj haslo: ";
    std::getline(std::cin, pass);
    toUpperCase(pass);
    std::cout << pass << std::endl;

    std::ifstream file("in.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            content += line + '\n';
        }
        //std::getline(std::cin, content);
        switch (option)
        {
        case 1:
            toUpperCase(content);
            szyfr(content, pass);
            file.close();
            break;
        case 2:
            szyfr(content, pass);
            file.close();
            break;

        }
        std::ofstream file2("out.txt");
        file2 << content;
        std::cout << content;
        file2.close();
    }
    else
        std::cout << "FILE PROBLEM";


}
