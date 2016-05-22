#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "bintree.h"

using namespace std;

int main()
{

    char volba; // Volba pre menu
    char YesNo; // Volba pre Ano/Nie
    bintree strom;
    void Export(Uzol_ptr ptr);

    do
    {
        cout << "++++++++++++++++++++++++++++++++++++++++++" << endl;
        cout << "Dnesne menu:" << endl;
        cout << "A - vytvorenie zakladneho stromu" << endl;
        cout << "B - nacitanie stromu zo suboru" << endl;
        cout << "C - spustenie procesu ucenia" << endl;
        cout << "D - export aktualneho stromu do suboru" << endl;
        cout << "X - ukoncenie cinnosti programu" << endl;

        cout << "Zadaj volbu: ";
        cin.clear();
        cin >> volba;

        switch(volba)
        {
            case 'a': // Default
                {

                strom.AddLeft("kon");strom.AddRight("vtak");
                cout << "Zakladny strom bol vytvoreny" << endl;
                break;
                }

            case 'b': // Load
                {
                cout << "Niet casu na panske huncucstva... :-)" << endl;
                break;
                }


            case 'c': // Ucenie
                {
                    strom.GoRoot(); // Chdo na zaciatok stromu
                    cout << "Myslite na nejaky objekt. Odpovedajte na moje otazky. (y/n)"<< endl;


                    int i = 1;
                    while(i == 1)
                    {
                        if(strom.IsLeaf())
                        {
                            cout << "AI: mysleli ste na objekt " << strom.DataRead() << "? y/n" << endl;
                            i = 0;
                            cout << "User: " ;cin >> YesNo;

                            if(YesNo == 'y')
                            {
                                cout << "AI: Som inteligentny" << endl;
                            }
                            else
                            {
                                // A zacina motanica s ucenim
                                string otazka;
                                string objekt;

                                cout << "AI: na aky objekt ste mysleli?" << endl;
                                cout << "User: "; cin >> objekt;
                                cout << "AI: Zadajte otazku, na ktoru odpoviete ano pre vas objekt a nie pre moj objekt" << endl;
                                cout << "User: "; cin >> std::ws;getline(cin, otazka);
                                strom.Store(otazka, objekt);
                                cout << "AI: Ucenie ukoncene" << endl;
                            }
                        break;


                        }
                        else
                        {
                            cout  << "AI: "  << strom.DataRead() << endl;
                            cout << "User: ";cin >> YesNo ;
                            if(YesNo == 'n')
                            {
                                strom.Go('l');
                            }
                            else
                            {
                                strom.Go('r');
                            }

                       }

                }
            break;
            }
            case 'd': // Export suboru
            {

                Uzol_ptr tmp;
                tmp = strom.Koren();

                ofstream subor("vystup.txt", ofstream::out);

                strom.Export(subor, tmp);

                subor.close();

                cout << "Strom bol exportovany" << endl;


                break;
            }
        }
    }
    while (volba !='x');

    return 0;


}


