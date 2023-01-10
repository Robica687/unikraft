// Untea Robert-Marius
// 323AC

#include <iostream>
#include <conio.h>
#include <fstream>
#include <iomanip>
#include <chrono>
//#include <time.h>

#define lin_db_1 800
#define nrFiguranti 132
#define nrOfNames 1000
#define cursDolar 4.9
#define priceBus 5680

using namespace std;

// GENERATOR NUMERE RANDOM DE LA 0 LA PARAMETRU
template <typename rndNrRng>
rndNrRng randomNumberInRange(rndNrRng var)
{
    return rand() % var;
}

// CITIRE FISIER PENTRU GENERAREA DE NUME PENTRU FIGURANTI (2 COLOANE A CATE 1000 DE NUME, NE FOLOSIM DE RANDOM NUMBER GENERATOR)
void readNameDb(string v1[nrOfNames][2])
{
    ifstream data_base_2_read;
    data_base_2_read.open("namegendatabase.csv");

    char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
    char delimeter2('\n');
    cout<<">> Deschidere fisier dictionar pentru generarea numelor de figuranti..."<<endl;
    // AM FOLOSIT EXCEPTII LA FIECARE LUCRU CU FISIERE (IFSTREAM/OFSTREAM) LA VERIFICAREA DESCHIDERII ACESTUIA
    try
    {
        if(!data_base_2_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < nrOfNames; i++)
            {
                getline(data_base_2_read, v1[i][0], delimeter1);
                getline(data_base_2_read, v1[i][1], delimeter2);
            }
            cout<<">> Deschis cu succes!"<<endl;
            cout<<endl;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}
// RETURNEAZA STRING RANDOM DIN DICTIONAR
class RandomString
{
    public:
    string mancare[3] =  {"Apt sa manance orice", "Vegetarian", "Flexitarian"};
    string rol[5] =      {"Vampir", "Varcolac", "Sirena", "Clarvazator", "Om"};
    // RETURN RANDOM STRING DIN MANCARE
        string rndMancare(string v1[3])
        {
            return v1[randomNumberInRange(3)];
        }
    // RETURN RANDOM STRING DIN MACHIAJ
        string rndRol(string v1[5])
        {
            return v1[randomNumberInRange(5)];
        }
    // RETURN RANDOM STRING DIN CELE 2X 1000 NUME PT FIGURANTI + CONCATENARE
        string rndFigName(string v1[1000][2])
        {
            return v1[randomNumberInRange(1000)][0] + " " + v1[randomNumberInRange(1000)][1];
        }
};

// PARAMETRII GENERALI
class Database
{
    public:
        string c1[lin_db_1];
        string c2[lin_db_1];
        string figuranti[nrFiguranti];
        unsigned int nrCastInit;
        unsigned int nrActori;
        ~Database();
};
// DESTRUCTOR
Database::~Database(void){}

// CLASA DE CITIRE DIN CSV
class DatabaseReader
{
    public:
        // FUNCTIE DE CITIRE PENTRU 2 COLOANE, FOLOSIT LA CSV-UL INITIAL
        unsigned int nrCol2(string col_1[lin_db_1], string col_2[lin_db_1])
        {
            ifstream data_base_1_read;
            data_base_1_read.open("wednesdayCast.csv");

            char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
            char delimeter2('\n');

            unsigned int indexBuffer = 0;   // INDEX PENTRU DEDUCEREA NUMARULUI DE MEMBRII INITIAL, SE RETURNEAZA LA SFARSITUL FUNCTIEI
            // DIN NOU, EXCEPTIONS, NU MAI COMENTEZ
            try
            {
                if(!data_base_1_read.is_open())
                    throw '1';
                else
                {
                    while (!data_base_1_read.eof( ))   // CITIRE DIN FISIER PANA LA EOF
                    {
                        getline(data_base_1_read, col_1[indexBuffer], delimeter1);
                        getline(data_base_1_read, col_2[indexBuffer], delimeter2);
                        indexBuffer++;
                    }
                    indexBuffer--;      // DECREMENTAM PENTRU A NU LUA IN CONSIDERARE EOF
                }
            }
            catch(char error)
            {
                if(error == '1')
                {
                    cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
                    cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
                    return 0;
                }
            }
            return indexBuffer;
        }
        ~DatabaseReader();
};
DatabaseReader::~DatabaseReader(void){}

// CLASA DE SCRIERE CSV
class DatabaseWriter
{
    public:
        RandomString ranStrGen;
        // SCRIERE CSV PENTRU 4 COLOANE (NUME, FUNCTIE, MANCARE, MACHIAJ/ROL)
        // AM ALES O SCRIERE IN URMATOAREA ORDINE: ACTORI, FIGURANTI, RESTUL CASTULUI PENTRU O UTILITATE MAI BUNA IN CALCULUL COSTURILOR (SI ANUME NUMARATUL FIECAREI DIETE/MACHIAJ)
        unsigned int nrCol4(string col_1[lin_db_1], string col_2[lin_db_1], string col_3[nrFiguranti], unsigned int index)
        {
            string names[nrOfNames][2];
            readNameDb(names);
            ofstream data_base_write;
            // SUPRASCRIE CSV-UL LA RULARE, DECI VOM AVEA LA FIECARE RULARE UN CSV DIFERIT DE FIECARE DATA, INCLUSIV DIETA, MACHIAJ, NUME FIGURANTI. SE PASTREAZA NUMARUL
            data_base_write.open("castdetailed.csv"/*,ios::app*/);

            char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
            char delimeter2('\n');

            unsigned int indexBuffer = 0;   // INDEX
            try
            {
                if(!data_base_write.is_open())
                    throw '1';
                else
                {
                    cout<<">> Scriere in fisier actori..."<<endl;
                    // SCRIERE DOAR ACTORI DIN CSV INITIAL IN NOUL CSV + ROL/DIETA GENERATE RANDOM
                    for(unsigned int i = 0; i < index; i++)
                    {
                        if(col_2[i].find("actor/actress") != string::npos)
                        {
                            data_base_write<<col_1[i];
                            data_base_write<<delimeter1;
                            data_base_write<<"actor";
                            data_base_write<<delimeter1;
                            data_base_write<<ranStrGen.rndMancare(ranStrGen.mancare); //data_base_write<<"CIBO";
                            data_base_write<<delimeter1;
                            data_base_write<<ranStrGen.rndMancare(ranStrGen.rol); //data_base_write<<"RUOLO";
                            data_base_write<<delimeter2;
                            indexBuffer++;
                            //indexBuffer- = -1;
                        }
                    }
                    cout<<">> Scriere in fisier figuranti..."<<endl;
                    // SCRIERE CU GENERARE A FIGURANTILOR IN NOUL CSV + ROL/DIETA GENERATE RANDOM
                    for(unsigned int i = 0; i < nrFiguranti; i++)
                    {
                        
                        data_base_write<<ranStrGen.rndFigName(names);
                        data_base_write<<delimeter1;
                        data_base_write<<"Figurant";
                        data_base_write<<delimeter1;
                        data_base_write<<ranStrGen.rndMancare(ranStrGen.mancare);
                        data_base_write<<delimeter1;

                        data_base_write<<ranStrGen.rndRol(ranStrGen.rol);
                        data_base_write<<delimeter2;
                    }
                    cout<<">> Scriere in fisier restul cast-ului..."<<endl;
                    // SCRIERE DIN VECHIUL CSV IN NOUL CSV RESTUL CASTULUI
                    for(unsigned int i = 0; i < index; i++)
                    {
                        if(col_2[i].find("actor/actress") == string::npos)

                        {
                            data_base_write<<col_1[i];
                            data_base_write<<delimeter1;

                            data_base_write<<col_2[i];
                            data_base_write<<delimeter2;
                        }
                    }
                    data_base_write.close();
                }
            }
            catch(char error)
            {
                if(error == '1')
                {
                    cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
                    cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
                    return 0;
                }
            }
            return indexBuffer;
        }
};

// FUNCTIE MASTER DE CITIRE CCSV INITIAL (NU STIU DE CE AM SPART-O ASA DE CLASA DE MAI SUS AFERENTA)
unsigned int loading_init_CSV(string data1[lin_db_1], string data2[lin_db_1])
{
    cout<<">> Se incarca baza de date..."<<endl;
    DatabaseReader database1;
    unsigned int indexBuffer;
    // APELARE CU SALVARE PARAMETRU RETURNAT
    indexBuffer = database1.nrCol2(data1, data2);
    if(indexBuffer!=0)
    {
        cout<<endl;
        cout<<">> Incarcare reusita!"<<endl
            <<">> Apasati orice tasta pentru continuare."
        <<endl;
        getch();
        system("cls");
        return indexBuffer;
    }
    return 0;
}

// FUNCTIE MASTER DE GENERARE A PRIMULUI CSV (ACEEASI POVESTE CA MAI SUS)
unsigned int generate_CSV_1(string data1[lin_db_1], string data2[lin_db_1], string figuranti[nrFiguranti], unsigned int index)
{
    cout<<">> Se genereaza CSV cu membrii cast-ului ..."<<endl<<endl;
    DatabaseWriter database1;
    unsigned int indexBuffer;
    // APELARE CU SALVARE PARAMETRU RETURNAT
    indexBuffer = database1.nrCol4(data1, data2, figuranti, index);
    if(indexBuffer!=0)
    {
        cout<<endl;
        cout<<">> Incarcare reusita!"<<endl
            <<">> Apasati orice tasta pentru continuare."
        <<endl;
        getch();
        system("cls");
        return indexBuffer;
    }
    return 0;
}

// CITESTE, COMPARA SI CONTORIZEAZA CATE TIPURI DE MACHIAJ SUNT DE FIECARE, FOLOSITA LA CALCUL COST
void readNverifyCSV1_machiaj(unsigned int contor[5], unsigned int castTotal)
{
    ifstream data_base_read;
    data_base_read.open("castdetailed.csv");
    char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
    char delimeter2('\n');
    string s[2];
    try
    {
        if(!data_base_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < castTotal; i++)
            {
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[1], delimeter2);
                if(s[1] == "Vampir")
                    contor[0]++;
                else
                if(s[1] == "Varcolac")
                    contor[1]++;
                else
                if(s[1] == "Sirena")
                    contor[2]++;
                else
                if(s[1] == "Clarvazator")
                    contor[3]++;
                else
                if(s[1] == "Om")
                    contor[4]++;
            }
            data_base_read.close();
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}

// CITESTE, COMPARA SI CONTORIZEAZA CATE TIPURI DE DIETE SUNT DE FIECARE, FOLOSITA LA CALCUL COST
void readNverifyCSV1_tipHrana(unsigned int contor[3], unsigned int castTotal)
{
    ifstream data_base_read;
    data_base_read.open("castdetailed.csv");
    char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
    char delimeter2('\n');
    string s[2];
    try
    {
        if(!data_base_read.is_open())
            throw '1';
        else
        {
            for(unsigned int i = 0; i < castTotal; i++)
            {
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[0], delimeter1);
                getline(data_base_read, s[1], delimeter1);
                getline(data_base_read, s[0], delimeter2);
                if(s[1] == "Apt sa manance orice")
                    contor[0]++;
                else
                if(s[1] == "Vegetarian")
                    contor[1]++;
                else
                if(s[1] == "Flexitarian")
                    contor[2]++;
            }
            data_base_read.close();
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in citirea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}

// SUPRASCRIE CSV-UL DE COST, SCRIE PRIMA LINIE PENTRU STRUCTURARE VIZUALA IN FUNCTIE DE NR DE ZILE PER PERIOADA
void preWriteCSV2()
{
    ofstream data_base_write;
    data_base_write.open("castprices.csv");
    char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
    char delimeter2('\n');
    try
    {
        if(!data_base_write.is_open())
            throw '1';
        else
        {
            data_base_write<<"Zile";    data_base_write<<delimeter1;
            data_base_write<<"30";      data_base_write<<delimeter1;
            data_base_write<<"45";      data_base_write<<delimeter1;
            data_base_write<<"60";      data_base_write<<delimeter1;
            data_base_write<<"100";     data_base_write<<delimeter2;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }
}

// SCRIERE IN CONTINUARE DUPA SUPRASCRIERE A FIECARUI COST (APELAT DE FIECARE DATA)
void writeCSV2(unsigned int price[4], string sInput)
{
    ofstream data_base_write;
    // PENTRU SCRIERE IN CONTINUARE, NU SUPRASCRIERE
    data_base_write.open("castprices.csv",ios::app);
    char delimeter1(';');           // DELIMITATORI PENTRU FISIERUL CSV
    char delimeter2('\n');
    try
    {
        if(!data_base_write.is_open())
            throw '1';
        else
        {
            data_base_write<<sInput;
            data_base_write<<delimeter1;
            for(unsigned int i = 0; i < 3; i++)
            {

                data_base_write<<price[i];
                data_base_write<<delimeter1;
            }
            data_base_write<<price[3];
            data_base_write<<delimeter2;
        }
    }
    catch(char error)
    {
        if(error == '1')
        {
            cout<<">> Whops, a intervenit o eroare in scrierea fisierului CSV."<<endl;
            cout<<">> Va rugam verificati integritatea fisierului si redeschideti aplicatia."<<endl;
        }
    }

}

// FUNCTIE GENERALA DE CALCUL PRETZI * NR ZILE
void calculPretPerioade(unsigned int pretZi, unsigned int pretPerioada[4], unsigned int zilePerioada[4])
{
    pretPerioada[0] = pretZi * zilePerioada[0];
    pretPerioada[1] = pretZi * zilePerioada[1];
    pretPerioada[2] = pretZi * zilePerioada[2];
    pretPerioada[3] = pretZi * zilePerioada[3];
}

// CLASA PARINTE PENTRU COST
class Membrii
{
    protected:
        unsigned int nrCastInit;
        unsigned int nrActori;
    public:
        Membrii();
        Membrii(unsigned int nrCas, unsigned int nrAct)
        {
            nrCastInit = nrCas;
            nrActori = nrAct;
        }
        unsigned int getNrCas()
        {
            return this->nrCastInit;
        }
        unsigned int getNrAct()
        {
            return this->nrActori;
        }
        ~Membrii();
};

// CLASA MOSTENITA PENTRU COST
class Preturi : private Membrii
{
    private:
        unsigned int pretAutocar[4];
        unsigned int pretMachiaj[4];
        unsigned int pretCazare[4];
        unsigned int pretChirie[4];

        unsigned int pretLichide[4];
        unsigned int pretMancare[4];

        unsigned int zilePerioada[4] = {30, 45, 60, 100};
        unsigned int nrZile;

    public:
        Preturi(unsigned int nrCas, unsigned int nrAct) : Membrii(nrCas, nrAct)
        {
            nrCastInit = nrCas;
            nrActori = nrAct;
            cout<<">> Se genereaza CSV cu costurile cast-ului ..."<<endl<<endl;
        }
        Preturi();

        getch();
        // CALCULEAZA PRETUL AUTOCARELOR (ESTE ACELASI INDIFERENT DE PERIOADA)
        void getPretAutocar()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            pretAutocar[0] = castTotal / 50;
            if(castTotal%50 != 0)
                pretAutocar[0]++;
            pretAutocar[0] = pretAutocar[0] * priceBus *2 / cursDolar;

            for(unsigned int i = 1; i < 4; i++)
                pretAutocar[i] = pretAutocar[0];
            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretAutocar, "$ Autocar");
        }
        // CALCULEAZA PRETUL MACHIAJULUI
        void getPretMachiaj()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti - nrActori;
            //pretMachiaj[0] = castTotal;
            unsigned int contor[5] = { 0 };
            unsigned int pretZi;
            // CITIRE SI CONTORIZARE DIN CSV INITIAL
            readNverifyCSV1_machiaj(contor, castTotal);

            pretZi = (contor[0]*230 + contor[1]*555 + contor[2]*345 + contor[3]*157 + contor[4]*55)/cursDolar;

            // CALCUL PRETZI * NRZILE
            calculPretPerioade(pretZi, pretMachiaj, zilePerioada);

            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretMachiaj, "$ Machiaj");
        }
        // CALCULEAZA PRETUL CAZARII
        void getPretCazare()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            unsigned int contor[2] = { 0 };
            unsigned int pretZi;
            contor[0] = nrCastInit / 2;
            if(nrCastInit%2 != 0)
                contor[0]++;
            contor[1] = nrFiguranti / 3;
            if(nrFiguranti%3 != 0)
                contor[1]++;

            pretZi = (contor[0]*350 + contor[1]*420) / cursDolar;

            // CALCUL PRETZI * NRZILE
            calculPretPerioade(pretZi, pretCazare, zilePerioada);

            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretCazare, "$ Cazare");
        }
        // CALCULEAZA PRETUL INCHIRIERII CASTELULUI
        void getPretChirie()
        {
            unsigned int pretZi = 10000;

            calculPretPerioade(pretZi, pretChirie, zilePerioada);
            // DA, APLICA SI REDUCEREA IN FUNCTIE DE NR DE ZILE
            for(unsigned int i = 0; i < 4; i++)
                pretChirie[i] = pretChirie[i]*(1-0.02*(zilePerioada[i] / 10)) / cursDolar;

            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretChirie, "$ Chirie");
        }
        // CALCULEAZA PRETUL LICHIDELOR CONSUMATE
        void getPretLichide()
        {
            unsigned int castTotal = nrCastInit + nrFiguranti;
            unsigned int pretZi;
            unsigned int contor[3] = { 0 };

            // CONSIDER CA PRETURILE SUNT AFERENTE UNOR RECIPIENTE DE DIMENSIUNI FIXE
            // DE EXEMPLU, DACA SE CONSUMA 3L APA SI 2L APA COSTA 6 LEI, TREBUIE SA CUMPAR 2*2L APA
            contor[0] = castTotal *1 / 2;
            if(castTotal%2 != 0)
                contor[0]++;

            contor[1] = castTotal *0.5 / 1;
            if(castTotal%1 != 0)
                contor[1]++;

            contor[2] = castTotal *0.8 / 2;
            if(castTotal%1 != 0)
                contor[2]++;

            pretZi = (contor[0] * 6 + contor[1] * 30 + contor[2] * 8) / cursDolar;

            // CALCUL PRETZI * NRZILE
            calculPretPerioade(pretZi, pretLichide, zilePerioada);

            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretLichide, "$ Lichide");
        }
        // CALCULEAZA PRETUL MANCARII
        void getPretMancare()
        {
            unsigned int castTotal = nrActori + nrFiguranti;
            unsigned int pretZi;
            unsigned int contor[3] = { 0 };
            // CITIRE SI CONTORIZARE DIN CSV INITIAL
            readNverifyCSV1_tipHrana(contor, castTotal);

            pretZi = (contor[0] * 40 + contor[1] * 33 + contor[2] * 46) / cursDolar;
            calculPretPerioade(pretZi, pretMancare, zilePerioada);

            // AICI SCRIE IN CSV 2 REZULTATUL
            writeCSV2(pretMancare, "$ Mancare");

            // MESAJ FINAL
            cout<<">> Incarcare reusita!"<<endl
                <<">> Apasati orice tasta pentru continuare."
                <<endl;
        }
};
Membrii::~Membrii(void){}


// FUNCTIE DE AFISARE, AM FOLOSIT-O PT VERIFICAREA INTEGRITATII CITIRII, RAMANE CA O UNEALTA DE DEBUGGING
void afisareDb_1(unsigned int indexBuffer, string col1[lin_db_1], string col2[lin_db_1])
{
     // AFISARE
    for(unsigned int i = 0; i < indexBuffer; i++)
    {
        //for(unsigned int i = 0; i < nrColoane; i++)
            cout<<right<<setw(3)<<i+1<<") ";
            cout<<right<<setw(36)<<col1[i]<<" - ";
            cout<<left<<setw(9)<<col2[i];
        cout<<endl;
    }
}

int main()
{
    srand(time(NULL));
    Database database1;

    database1.nrCastInit = loading_init_CSV(database1.c1, database1.c2);
    database1.nrActori = generate_CSV_1(database1.c1, database1.c2, database1.figuranti, database1.nrCastInit);

    Membrii membrii(database1.nrCastInit, database1.nrActori);

    Preturi preturi(membrii.getNrCas(), membrii.getNrAct());
    preWriteCSV2();
    preturi.getPretAutocar();
    preturi.getPretMachiaj();
    preturi.getPretCazare();
    preturi.getPretChirie();
    preturi.getPretLichide();
    preturi.getPretMancare();

    //cout<<endl<<endl;
    //afisareDb_1(database1.nrCastInit, database1.c1, database1.c2);
    /*cout<<"DATE:"<<endl
        <<"Actori + Cast extins: "<<database1.nrCastInit<<endl
        <<"Total: "<<database1.nrCastInit+nrFiguranti<<endl
        <<"Actori: "<<database1.nrActori<<endl
        <<"Cast extins: "<<database1.nrCastInit-database1.nrActori<<endl
        <<"Figuranti: "<<nrFiguranti<<endl;*/
    return 0;
}
// Untea Robert-Marius
// 323AC
