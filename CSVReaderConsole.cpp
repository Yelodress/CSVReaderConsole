#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h>
#include <codecvt>

using namespace std;

vector<vector<string>> content;
int textebrut();
int attributiondossards();
bool isUTF8(string filename);

int main()
{
    //Définir la sortie de la console en UTF-8 pour une meilleure compatibilité avec les caractères accentués
    SetConsoleOutputCP(65001);

    string fname;
    cout << "Enter the file name: ";
    cin >> fname;

    if (!isUTF8(fname))
    {
        cout << "The file is not in UTF-8 format. Reformatting..." << endl;
        if (reformatUTF8(fname))
        {
            cout << "File reformatted successfully." << endl;
        }
        else
        {
            cout << "Error reformatting file." << endl;
            return 1;
        }
    }

    string line, word;

    // Ouverture du fichier en mode lecture
    fstream file(fname, ios::in);
    if (file.is_open())
    {
        int i = 0;

        //Tant qu'il y a des lignes à lire dans le fichier
        while (getline(file, line))
        {
            i++;
                if (i == 1)
                {
                    line = line.substr(3);
                }
            // Initialise un vecteur 2D pour stocker le contenu du fichier CSV
            vector<string>* row = new vector<string>;
            row->clear();

            // Initialise un objet stringstream avec la ligne actuelle
             stringstream str(line);

            //Séparer les champs de la ligne en utilisant le caractère ';' comme séparateur
            while (getline(str, word, ';'))
            {
                //Supprimer les "" de chaque mot en utilisant la fonction erase
                word.erase(remove(word.begin(), word.end(), '\"'), word.end());
                row->push_back(word);
            }
            // Ajoute a ligne actuelle au vecteur 2D
            content.push_back(*row);

        }
    }
    else
        cout << "Could not open the file\n";
    //attributiondossards();
    textebrut();
    //[ligne][colonne]
    return 0;
}



int textebrut() //print le contenu du vecteur
{
    for (int i = 0; i < content.size(); i++)
    {
        for (int j = 0; j < content[i].size(); j++)
        {
            cout << content[i][j] << " ";
        }
        cout << "\n \n";
    }
    return 0;
};


int attributiondossards()
{
    int col = -1;
    string test = "Dossard";
    for (int i = 0; i < content[0].size(); i++)
    {
        if (content[0][i].compare(test) == 0)
        {
            col = i;
        }
    }
    cout << "Colonne " << col << endl;
    return col;
}


bool isUTF8(string filename)
{
    // Open the file in binary mode
    ifstream file(filename, ios::binary);
    // Check if the file is open
    if (!file.is_open())
        return false;

    // Read the first byte of the file
    unsigned char buffer;
    file.read((char*)&buffer, 1);
    file.close();

    // Check if the file starts with the UTF-8 BOM (byte order mark)
    if (buffer == 0xEF)
    {
        // Read the next 2 bytes
        unsigned char buffer2[2];
        file.read((char*)buffer2, 2);
        // Check if the next 2 bytes match the UTF-8 BOM
        if (buffer2[0] == 0xBB && buffer2[1] == 0xBF)
            return true;
    }

    // Check if the file is in UTF-8 without BOM
    file.open(filename);
    bool valid = true;
    while (!file.eof())
    {
        char c = 0;
        int nbBytes = 0;
        file.get(c);
        if (file.eof())
            break;
        if ((c & 0x80) == 0)
            nbBytes = 1;
        else if ((c & 0xE0) == 0xC0)
            nbBytes = 2;
        else if ((c & 0xF0) == 0xE0)
            nbBytes = 3;
        else if ((c & 0xF8) == 0xF0)
            nbBytes = 4;
        else
        {
            valid = false;
            break;
        }
        for (int i = 1; i < nbBytes; i++)
        {
            file.get(c);
            if ((c & 0xC0) != 0x80)
            {
                valid = false;
                break;
            }
        }
        if (!valid)
            break;
    }
    file.close();
    return valid;
}

bool reformatUTF8(string filename)
{
    // Open the file in binary mode
    ifstream file(filename, ios::binary);
    // Check if the file is open
    if (!file.is_open())
        return false;

    // Read the content of the file
    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    // Convert the content to UTF-8 with BOM
    wstring_convert<codecvt_utf8<wchar_t>, wchar_t> convert;
    wstring wstr = convert.from_bytes(buffer.str());
    string utf8str = convert.to_bytes(wstr);
    utf8str = "\xEF\xBB\xBF" + utf8str; // Add UTF-8 BOM

    // Rewrite the file in binary mode
    ofstream outfile(filename, ios::binary);
    if (!outfile.is_open())
        return false;

    outfile.write(utf8str.c_str(), utf8str.length());
    outfile.close();

    return true;

}



