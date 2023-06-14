#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <Windows.h> //Pour le setconsoleoutput
#include <codecvt> //Conversion
#include <random> //Génération aléatoire
//#include <mysql_driver.h>
//#include <mysql_connection.h>

//using namespace sql;
using namespace std;

vector<vector<string>> content;
vector<streampos> linePosition;
int texteBrut();
void rechercheColonnes();
bool isUTF8BOM(string filename);
bool reformatUTF8(string filename);
bool reformatUTF16(string filename);
bool isUTF16(string filename);
bool cle;
int numColonneDosssard;
int numColonneCourse;
int numColonneClub;
int numColonneSupprime;
int numColonneTags;
string courseTransmedievale = "La Transmédiévale"; //Définit la chaine de caractère de la course a rechercher
string courseReleve = "La Relève";
string courseCanailles = "Les Canailles";
string courseLutins = "Les Lutins";
string coursePitchoune = "La Pitchoune";
string courseBoreale = "La Boréale";
string clubCG = "LBDLV";
string coureurSupprime = "SUPPRIMÉ";
bool isUtf16Before;
string stockageDossards = "Dossards; TAGs;\n";
void generationTags();
string tag;



int main()
{
    //Définir la sortie de la console en UTF-8 pour une meilleure compatibilité avec les caractères accentués
    SetConsoleOutputCP(65001);

    string fname;
    do {
        cout << "Entrez le nom du fichier: ";
        cin >> fname;
        cle = true;
        if (!isUTF8BOM(fname) && isUTF16(fname))
        {
            cout << "Le fichier est en UTF-16. Formatage en UTF-8..." << endl;
            if (reformatUTF16(fname))
            {
                cout << "Fichier formaté avec succès." << endl;
                cle = true;
            }
            else
            {
                cout << "Erreur de formatage." << endl;
                cle = false;
            }
        }
        else if (!isUTF8BOM(fname) && !isUTF16(fname)){
                cout << "le fichier n'est pas en UTF-8 BOM. Formatage ..." << endl;
                if (reformatUTF8(fname))
                {
                    cout << "Fichier formaté avec succès" << endl;
                    cle = true;

                }
                else
                {
                    cout << "Erreur de formatage." << endl;
                    cle = false;
                }
            
        }
    } while (cle == false);
    string line, word;

    // Ouverture du fichier en mode lecture
    fstream file(fname, ios::in | ios::out);
    if (file.is_open())
    {
        int i = 0;
        streampos pos = file.tellg();

        //Tant qu'il y a des lignes à lire dans le fichier
        while (getline(file, line))
        {
            i++;
                if (i == 1)
                {
                    line = line.substr(3);
                }
                linePosition.push_back(pos);
                pos = file.tellg();
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
        file.clear(); //Efface l'indicateur d'état "eofbit"
    }
    else
        cout << "Erreur dans l'ouverture du fichier\n";

    rechercheColonnes();

     if (numColonneDosssard != -1) {
        // Créez un fichier temporaire
        string tempFilename = "temp.csv";
        ofstream tempFile(tempFilename, ios::out);

        if (tempFile.is_open()) {
            int a = 0, b = 0, c = 0, d = 0, e = 0, f = 0, g = 0;
            for (size_t i = 0; i < content.size(); ++i) {//taille totale
                stringstream newLine;
                for (size_t j = 0; j < content[i].size(); ++j) {//ligne
                    if (j == numColonneDosssard) {
                        if (i == 0) {
                            newLine << content[i][j];
                        }
                        else {
                            //ecris des valeurs incrémentées dans la colonne dossard
                            if (content[i][numColonneCourse].compare(courseTransmedievale) == 0 && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                a++;
                                string num = to_string(a);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                            else if (content[i][numColonneCourse].compare(coursePitchoune) == 0 && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                b++;
                                string num = to_string(1000 + b);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                            else if (content[i][numColonneCourse].compare(courseBoreale) == 0 && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0 )
                            {
                                c++;
                                string num = to_string(2000 + c);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                            else if (content[i][numColonneCourse].compare(courseCanailles) == 0 && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                d++;
                                string num = to_string(3000 + d);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                            else if (content[i][numColonneCourse].compare(courseLutins) == 0 && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                e++;
                                string num = to_string(4000 + e);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                            else if (content[i][numColonneCourse].compare(courseReleve) == 0  && content[i][numColonneClub].compare(clubCG) != 0 && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                f++;
                                string num = to_string(5000 + f);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                           else if (content[i][numColonneClub].compare(clubCG) == 0  && content[i][numColonneSupprime].compare(coureurSupprime) != 0)
                            {
                                g++;
                                string num = to_string(10000 + g);
                                newLine << num;
                                generationTags();
                                stockageDossards = stockageDossards + num + ";" + tag + ";\n";
                            }
                        } 
                    }
                    else {
                        newLine << content[i][j];
                    }
                    if (j < content[i].size() - 1) {
                        newLine << ';'; //séparation entre chaque colonne
                    }
                }
                tempFile << newLine.str() << "\n";
            }
            tempFile.close();
        }
        else {
            cout << "Erreur d'ouverture du fichier temporaire\n";
        }

        // Fermez le fichier original
        file.close();

        // Supprimez le fichier original et renommez le fichier temporaire
        remove(fname.c_str());
        rename(tempFilename.c_str(), fname.c_str());
    }

    //texteBrut();
    //[ligne][colonne]

    string nomFichier = "tagsDossards.csv";
    ofstream fichier(nomFichier);
    if (fichier.is_open())
    {
        //cout << stockageDossards;
        content.clear();
        fichier << stockageDossards;

        //rechercheColonnes();
        fichier.close();
    }
    else
    {
        cout << "erreur";
    }

    return 0;
}



int texteBrut() //print le contenu du vecteur
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

void generationTags() {
    // Tous les chiffres et lettres que vous voulez utiliser
    string characters = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.size() - 1);
    tag = "0";

    for (int i = 0; i < 7; i++) {
        // Générer un index aléatoire dans characters
        int randomIndex = distribution(generator);
        // Ajouter le caractère à tag
        tag += characters[randomIndex];
    }
    tag = "05800" + tag;
}

void rechercheColonnes()
{
    numColonneDosssard = -1;
    numColonneCourse = -1;
    numColonneClub = -1;
    numColonneSupprime = -1;
    string nomColonneDossard = "Dossard"; //définit la chaine de caractère à rechercher
    string nomColonneCourse = "Course";
    string nomColonneClub = "Club";
    string nomColonneSupprime = "Supprimé";


    for (int i = 0; i < content[0].size(); i++)// boucle "tant que la ligne n'est pas finie"
    {
        if (content[0][i].compare(nomColonneDossard) == 0)//boucle pour comparer "Si le contenu de la case correspond à la valeur stockée dans la variable nomColonneDossard"
        {
            numColonneDosssard = i;
        }

        if (content[0][i].compare(nomColonneCourse) == 0)
        {
            numColonneCourse = i;
        }

       if (content[0][i].compare(nomColonneClub) == 0)
        {
            numColonneClub = i;
        }

       if (content[0][i].compare(nomColonneSupprime) == 0)
       {
           numColonneSupprime = i;
       }

    }

    if (numColonneDosssard == -1)
    {
        cout << "Colonne des dossards non trouvée. L'orthographe recherchée est: \"" << nomColonneDossard << "\"" << endl;
    }

    if (numColonneCourse == -1)
    {
        cout << "Colonne des courses non trouvée. L'orthographe recherchée est: \"" << nomColonneCourse << "\"" << endl;
    }

    if (numColonneClub == -1)
    {
        cout << "Colonne des clubs non trouvée. L'orthographe recherchée est: \"" << nomColonneClub << "\"" << endl;
    }

    if (numColonneSupprime)
    {
        cout << "Colonne des supprimés non trouvée. L'orthographe recherchée est: \"" << nomColonneSupprime << "\"" << endl;
    }

    cout << "Colonne dossard: " << numColonneDosssard+1 << "\nColonne Course: " << numColonneCourse + 1 << "\nColonne Club: " << numColonneClub+1 << "\nColonne Supprime: " << numColonneSupprime+1 << endl; //Sortie pour l'utilisateur
}


bool isUTF8BOM(string filename)
{
    // Open the file in binary mode
    ifstream file(filename, ios::binary);
    // Check if the file is open
    if (!file.is_open())
        return false;

    // Read the first 3 bytes of the file
    unsigned char buffer[3];
    file.read((char*)buffer, 3);
    file.close();

    // Check if the file starts with the UTF-8 BOM (byte order mark)
    return buffer[0] == 0xEF && buffer[1] == 0xBB && buffer[2] == 0xBF;
}

bool isUTF16(string filename)
{
    ifstream file(filename, ios::binary);//Ouvrir le fichier en binaire
    if (!file.is_open())//Check si le fichier est ouvert
        return false;

    unsigned char buffer[6];
    file.read((char*)buffer, 6);
    file.close();

    //Check si le fichier a un bit sur 2 est égal à 0
    return buffer[0] != 0x00 && buffer[1] == 0x00 && buffer[3] == 0x00 && buffer[5] == 0x00;
};


bool reformatUTF8(string filename) {
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
    wstring wstr;
        wstr = convert.from_bytes(buffer.str());
    
    
    string utf8str = convert.to_bytes(wstr);
    if (!isUTF8BOM(filename)) {
        utf8str = "\xEF\xBB\xBF" + utf8str; // Add UTF-8 BOM
    }

    // Rewrite the file in binary mode
    ofstream outfile(filename, ios::binary);
    if (!outfile.is_open())
        return false;

    outfile.write(utf8str.c_str(), utf8str.length());
    outfile.close();

    isUtf16Before = false;

    return true;
}

bool reformatUTF16(string filename) {
    // Open the file in binary mode
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // Read the content of the file
    std::stringstream buffer;
    buffer << file.rdbuf();
    file.close();
    std::string inputStr = buffer.str();

    // Convert the content to UTF-16
    std::wstring_convert<std::codecvt_utf16<wchar_t, 0x10ffff, std::little_endian>, wchar_t> convert16;
    std::wstring utf16str = convert16.from_bytes(inputStr);

    // Convert the content to UTF-8 with BOM
    std::wstring_convert<std::codecvt_utf8<wchar_t>> convert8;
    std::string utf8str = convert8.to_bytes(utf16str);
    utf8str = "\xEF\xBB\xBF" + utf8str; // Add UTF-8 BOM

    // Rewrite the file in binary mode
    std::ofstream outfile(filename, std::ios::binary);
    if (!outfile.is_open()) {
        return false;
    }

    outfile.write(utf8str.c_str(), utf8str.length());
    outfile.close();

    isUtf16Before = true;

    return true;
}
