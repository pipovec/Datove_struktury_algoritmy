#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "stack.h"

using namespace std;

float bilancia = 0.00;


class Bilancia
{
    public:
    void Bilancuj(string operacia, int pocet, float ck)
    {
        if(operacia == "p")
        {
            bilancia  = bilancia + (pocet * ck);
        }
        else
        {
            bilancia  = bilancia - (pocet * ck);
        }

    }

};

class WorkQueue
{

    public:
    void ListQueue(Queue mat)
    {
        mat.ListQueue();
    }


    // Nakup materialu
    void Nakup(Queue *ptr_mat, int pocet, float ck)
    {
       ptr_mat->Enqueue(pocet, ck);
    }

    void Predaj(Queue *ptr_mat, int pocet, float ck)
    {
        int tmp_pocet, all_pocet;
        Bilancia bil;

        //Spocitaj vsetky polozky vo fronte
        all_pocet  = ptr_mat->CountPocet();
        if(all_pocet < pocet)
        {
            cout << "Chces predat viac kusov ako mas k dispozicii" << endl;
        }
        else
        {
            // Ak je pocet mensi ako je v prvom Node
            if(ptr_mat->FrontPocet() > pocet)
            {
                ptr_mat->Odpocitaj(pocet);;
            }

            // Ak je pocet vacsi ako je v prvom Node
            if(ptr_mat->FrontPocet() < pocet)
            {

                bil.Bilancuj("p", pocet, ck);

                tmp_pocet = ptr_mat->FrontPocet();
                // Zrus nod
                ptr_mat->Dequeue();

                // A od dalsieho odrataj zvysok
                pocet = pocet - tmp_pocet;
                ptr_mat->Odpocitaj(pocet);

            }

            // Ak je pocet rovny ako pocet v prvom Node
            if(ptr_mat->FrontPocet() == pocet)
            {
                ptr_mat->Dequeue();
                bil.Bilancuj("p", pocet, ck);
            }

        }


    }

};

class File
{

    public:
    string filename = "inventar.txt";

    // Precita subor na zaciatku a narve to do front a urobi bilanciu
    void readFile(Queue *ptr1,Queue *ptr2,Queue *ptr3)
    {
        ifstream file;

        /* Spocitaj riadky */
        file.open(filename);

        int numLines = 0; string odpad;
        while(getline(file, odpad))
                  {++numLines;}

        file.close();

        /* Citaj riadky*/
        file.open(filename);
        int i = 0;
        string  operacia, material,pocet,cena;


        while(i < numLines)
        {
            file >> operacia >> material >> pocet >> cena ;
            //Spocitaj bilnaciu
            Bilancia bil;
            bil.Bilancuj(operacia, stoi(pocet), stof(cena));

            // Narvy to do stackov
            if(material == "1")
            {
                ptr1->Enqueue(stoi(pocet), stof(cena));
            }

            if(material == "2")
            {
                ptr2->Enqueue(stoi(pocet), stof(cena));
            }

            if(material == "3")
            {
                ptr3->Enqueue(stoi(pocet), stof(cena));
            }

            ++i;
        }
        cout  << "Nacitanie je ukoncene" << endl;
        file.close();
    }

};

class ClearScreen
{
	public:
		void clear_screen()
		{
			#ifdef WINDOWS
    		std::system("cls");
			#else
    		// Assume POSIX
    		std::system ("clear");
			#endif
		}

};

class Commands
{
    public:
        void ShowCommands()
        {
            cout << "Prehlad prikazov a syntaxe(dodrzuj medzery)" << endl;
            cout << "r - nacitaj (musi byt spustene ako prve)" << endl;
            cout << "i M vypis polozky materialu M" << endl;
            cout << "n M P CK - nakup " << endl;
            cout << "p M P CK - predaj " << endl << endl;

        }

        void VyhodnotComm(string volba,Queue mat1,Queue mat2,Queue mat3,Queue *ptr1,Queue *ptr2,Queue *ptr3, int *ptr_exit)
        {
            string tmp;
            tmp = volba[0];

            // Nacitanie materialu pri starte programu
            if(tmp == "r")
            {
                File file;
                file.readFile(ptr1,ptr2,ptr3);
            }

            // Citanie zoznamu materialu
            if(tmp == "i")
            {
                string material;
                WorkQueue WQ;
                material = volba[2];

                switch(stoi(material))
                {
                    case 1: cout << "Material 1" << endl;WQ.ListQueue(mat1);break;

                    case 2: cout << "Material 2" << endl;WQ.ListQueue(mat2);break;

                    case 3: cout << "Material 3" << endl;WQ.ListQueue(mat3);break;
                }

            }

            // Nakup
            if(tmp == "n")
            {
                string operacia; int fronta; int pocet; float ck;

                stringstream s(volba);
                s >> operacia >> fronta >> pocet >> ck;

                WorkQueue wq;
                Bilancia bil;

                switch(fronta)
                {
                    case 1: wq.Nakup(ptr1, pocet, ck); bil.Bilancuj(operacia,pocet,ck); break;

                    case 2: wq.Nakup(ptr2, pocet, ck); bil.Bilancuj(operacia,pocet,ck); break;

                    case 3: wq.Nakup(ptr3, pocet, ck); bil.Bilancuj(operacia,pocet,ck); break;
                }



            }

            // Predaj
            if(tmp == "p")
            {
                WorkQueue wq;

                string operacia; int fronta; int pocet; float ck;
                stringstream s(volba);
                s >> operacia >> fronta >> pocet >> ck;

                switch(fronta)
                {
                    case 1: wq.Predaj(ptr1, pocet, ck);  break;

                    case 2: wq.Predaj(ptr2, pocet, ck);  break;

                    case 3: wq.Predaj(ptr2, pocet, ck);  break;
                }



            }

            // Koniec programu
            if(tmp == "x")
            {
                *ptr_exit = 0;
            }

        }


};



//////////////////////// Hlavny program //////////////////

int main()
{
    string volba;
    int exit = 1; int *ptr_exit; ptr_exit = &exit;

    Commands comm;
    ClearScreen cs;

    Queue mat1; Queue *ptr_mat1; ptr_mat1 = &mat1;
    Queue mat2; Queue *ptr_mat2; ptr_mat2 = &mat2;
    Queue mat3; Queue *ptr_mat3; ptr_mat3 = &mat3;



    while(exit == 1)
    {

        cout << "Bilancia je: " << bilancia << endl;
        comm.ShowCommands();
        getline(cin, volba);

        comm.VyhodnotComm(volba,mat1,mat2,mat3,ptr_mat1,ptr_mat2,ptr_mat3, ptr_exit);
        if(*ptr_exit  == 0){return 0;}
        cout << endl << "=======================" << endl << endl;

        cout << "stlac hocico" << endl;
        cin.get();

        cs.clear_screen();

    }




    return 0;
}
