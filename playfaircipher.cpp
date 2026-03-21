#include <iostream>
#include <string>
#include <cctype>
using namespace std;

string clean(string s)
{
    string t = "";
    for(char ch : s)
    {
        if(isalpha((unsigned char)ch))
        {
            ch = toupper(ch);
            if(ch == 'J') ch = 'I';
            t += ch;
        }
    }
    return t;
}

void buildMatrix(string key, char m[5][5])
{
    bool used[26] = {0};
    used['J' - 'A'] = true;

    key = clean(key);
    string k = "";

    for(char ch : key)
    {
        if(!used[ch - 'A'])
        {
            used[ch - 'A'] = true;
            k += ch;
        }
    }

    for(char ch = 'A'; ch <= 'Z'; ch++)
    {
        if(!used[ch - 'A'])
        {
            used[ch - 'A'] = true;
            k += ch;
        }
    }

    int p = 0;
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            m[i][j] = k[p++];
}

void findPos(char m[5][5], char ch, int &r, int &c)
{
    for(int i = 0; i < 5; i++)
        for(int j = 0; j < 5; j++)
            if(m[i][j] == ch)
            {
                r = i;
                c = j;
                return;
            }
}

string makePairs(string p)
{
    p = clean(p);
    string d = "";

    for(int i = 0; i < (int)p.size(); )
    {
        char a = p[i];
        char b = (i + 1 < (int)p.size()) ? p[i + 1] : 'X';

        if(a == b)
        {
            d += a;
            d += 'X';
            i++;
        }
        else
        {
            d += a;
            d += b;
            i += 2;
        }
    }

    if(d.size() % 2 == 1)
        d += 'X';

    return d;
}

string playfair(string text, string key, bool enc)
{
    char m[5][5];
    buildMatrix(key, m);

    if(enc)
        text = makePairs(text);
    else
        text = clean(text);

    string out = "";

    for(int i = 0; i < (int)text.size(); i += 2)
    {
        char a = text[i];
        char b = text[i + 1];

        int r1, c1, r2, c2;
        findPos(m, a, r1, c1);
        findPos(m, b, r2, c2);

        if(r1 == r2)
        {
            out += m[r1][(c1 + (enc ? 1 : 4)) % 5];
            out += m[r2][(c2 + (enc ? 1 : 4)) % 5];
        }
        else if(c1 == c2)
        {
            out += m[(r1 + (enc ? 1 : 4)) % 5][c1];
            out += m[(r2 + (enc ? 1 : 4)) % 5][c2];
        }
        else
        {
            out += m[r1][c2];
            out += m[r2][c1];
        }
    }

    return out;
}

int main()
{
    string key, text;
    int choice;
    
    cout<<"\t\t ****Sandeep Shrestha****"<<endl;
    cout<<"\t\t ****Playfair-cipher****"<<endl;
	cout<<endl;
    cout << "1. Encrypt\n2. Decrypt\nChoose: ";
    cin >> choice;
    cin.ignore();

    cout << "Enter key: ";
    getline(cin, key);

    cout << "Enter text: ";
    getline(cin, text);

    if(choice == 1)
        cout << "Ciphertext: " << playfair(text, key, true) << endl;
    else
        cout << "Plaintext (raw): " << playfair(text, key, false) << endl;

    return 0;
}