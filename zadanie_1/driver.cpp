#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <stack.cpp>

/* Trieda na pracu s volbou New */
class ChoseNew{

	public:
        std::fstream file;

		int SetNewData()
		{
			int PZ,PP,dINT,hINT;

			// Otvorim subor a vymazem stare data
			file.open("game.txt",std::fstream::out | std::fstream::trunc);

			std::cout << "Zadajte pocet zivotov hracov: ";
			std::cin >> PZ ;
			WritePara(PZ);WriteSemi();

			std::cout << "Zadajte pocet prvkov hracov: " ;
			std::cin >> PP ;
			WritePara(PP);WriteSemi();

			std::cout << "Zadajte zaciatok uzavreteho intervalu prvkov: " ;
			std::cin >> dINT;
			WritePara(dINT);WriteSemi();

			std::cout << "Zadajte koniec uzavreteho intervalu prvkov: " ;
			std::cin >> hINT;
			WritePara(hINT);


			file.close();
			return 0;
		}

        int KontrolaVolby(std::string Volba)
        {
            /* Kontrola ci je volba spravne zadana */
            int result = 0;

            if
            (Volba == "New"){result = 1;}
            else if
            (Volba == "Load"){result = 1;}
            else if
            (Volba == "Exit"){result = 1;}

            return result;
        }

        int KontrolaIntervalu(std::string interval)
        {
            int result = 0;
            int dINT, hINT, INT;
            using namespace std;
            string value;
			ifstream file;

            /* Nacitanie intervalov zo suboru */
			file.open("game.txt");

			getline(file,value,';');
			getline(file,value,';');


			getline(file,value,';');
			dINT = stoi(value);

			getline(file,value,'\n');
			hINT = stoi(value);

			file.close();

            INT = stoi(interval);

            /* Kontrola ci je cislo v intervale */
			if( INT >= dINT && INT <= hINT )
			{
                result = 1;
			}
			else
			{
                cout << "Cislo je mimo intervalu, zadaj znova" << endl;
                result = 0;
			}

            return result;
        }

		void SetNewPlayer()
		{
			std::string Meno ,value;
			int i, PP, PZ, control;
            control = 0;

			// Nacitanie kolko prvkov sa bude hadat
			PP = PocetPrvkov();
            PZ = PocetZivotov();
            // Otvrorenie suboru na pridanie riadku
            std::fstream file;
            file.open("game.txt", std::fstream::out | std::fstream::app);

            std::cout << "Zadaj svoje meno: ";
			std::cin >> Meno;
			file << "\n" << Meno << ";";

            /* Zadanie zivotov */
            file << PZ << ";";

            /* Zadavanie prvkov do suboru a kontrola intervalu */
			for(i = 0; i < PP; i++)
			{

                do
                {
                    std::cout << "Zadaj prvok c." << i+1 << ":";
                    std::cin >> value;
                    control = KontrolaIntervalu(value);
                }
                while(control == 0);

                /* Ak je v poriadku zapis ho */
                 file << value ;

                if(i < PP - 1) file << ";";
			}

            file.close();


		}

	private:
		int PocetPrvkov()
		{
			// Zisti pocet prvkov v hre zo suboru
			std::string i;
			int PP;

			file.open("game.txt", std::fstream::in); // Otvorim len na citanie;

            std::getline (file, i, ';');// Vynecham lebo je to pocet zivotov
			std::getline (file, i, ';');// Toto je pocet prvkov

			PP = std::stoi(i);

			CloseFile();

			return PP;

		}

		int PocetZivotov()
        {
            using namespace std;

			string value;
			ifstream file;

			int result;

			file.open("game.txt");
            getline(file,value,';');
            result = stoi(value);
            file.close();

            return result;

        }

		void WritePara(int para)
		{
			file << para;
		}

		void WriteSemi()
		{
			file << ";" ;
		}

		void CloseFile()
		{
			file.close();
		}

};

class Hrac
{
	public:
		void NacitajParametre()
		{
            // Nacitaj zakladne parametre zo suboru a zobraz na obrazovke

            using namespace std;

			string value;

			ifstream file;

			file.open("game.txt");

			getline(file,value,';');
			cout << "Parametre hry: PZ=" <<  value;

			getline(file,value,';');
			cout << ",PP=" <<  value;

			getline(file,value,';');
			cout << ",<"<<  value;

			getline(file,value,'\n');
			cout << "," <<  value << ">" << endl;

			file.close();

		}

        int NaplnStack(int hrac, IntStack* PP)
        {
            using namespace std;
            /* Naplnenie stackov zo suboru. Hrac ocakava int ako poradie hrac */
            ifstream file;
            string value;
            int i,c,prvok;
            file.open("game.txt");

            getline(file,value); /* Preskoc prvy riadok s parametrami*/

            if(hrac == 2){getline(file,value);} /* Preskoc druhy riadok s prvym hracom */

            getline(file,value,';'); /* Preskoc meno hraca */
            getline(file,value,';'); /* Preskoc zivot hraca */

            i = KolkoStackov();

            for(c = 0; c < i; c++)
            {
                getline(file,value,';');
                prvok = stoi(value);
                PP->Push(prvok);
            }

            file.close();

            return i;

        }

        int KolkoPP()
        {
            int pp;
            pp = KolkoStackov();
            return pp;
        }

        int KolkoPZ()
        {
            /* kolko zivotov */
            int pz;
            pz = KolkoZivota();

            return pz;
        }

        void NaplnZivoty(int pz, IntStack* PZ)
        {
            int i;

            for( i = 1 ; i < pz + 1 ; i++)
            {
                PZ->Push(i);
            }
        }

        std::string MenoHraca(int hrac)
        {
            using namespace std;
            ifstream file;
            string value;
            file.open("game.txt");

            getline(file,value); /* Preskoc prvy riadok s parametrami*/

            if(hrac == 2){getline(file,value);}
            getline(file,value,';'); // Meno hraca

            file.close();
            return value;

            file.close();

        }

    private:
        int KolkoZivota()
        {
            using namespace std;

			string value;
			ifstream file;

			int result;

			file.open("game.txt");
            getline(file,value,';');
            result = stoi(value);
            file.close();

            return result;

        }

        int KolkoStackov()
        {
            using namespace std;

			string value;
			ifstream file;

			int result;

			file.open("game.txt");
            getline(file,value,';');
            getline(file,value,';');
            result = stoi(value);
            file.close();

            return result;
        }

};

/* Trieda na pracu s volbou Load */
class ChoseLoad{
	public:

	private:
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

int main()
{

    using namespace std;

    string Volba, meno;
    int ControlChoice;

    ChoseNew New;
   	ClearScreen CS;
    Hrac Hrac;

   	IntStack PZ1; // Pocet zivotov hraca cislo 1
   	IntStack PP1; // Stack hraca cislo 1
   	IntStack PZ2;
   	IntStack PP2;

    IntStack *ptr_PZ1;
    ptr_PZ1 = &PZ1;
    IntStack *ptr_PZ2;
    ptr_PZ2 = &PZ2;
    IntStack *ptr_PP1;
    ptr_PP1 = &PP1;
    IntStack *ptr_PP2;
    ptr_PP2 = &PP2;

    do
    {
        cout << "Zadaj tvoju volbu (New, Load, Exit): ";
        cin >> Volba;
        ControlChoice = New.KontrolaVolby(Volba);
    }
    while(ControlChoice == 0);

    CS.clear_screen();


    if (Volba == "New")
    {

        // Zadavanie novych parametrov hry

      /*  New.SetNewData();
        CS.clear_screen();

        cout << "Zadanie udajov hraca c.1" << endl;
        Hrac.NacitajParametre();
        New.SetNewPlayer();

        CS.clear_screen();

        cout << "Zadanie udajov hraca c.2" << endl;
        Hrac.NacitajParametre();
        New.SetNewPlayer();
*/



        /* Naplnenie udajov do stackov zo suboru - zivoty*/
        int pz; /* Pocet zivotov */
        pz = Hrac.KolkoPZ();

        /* Napln zivot Hrac 1 */
        Hrac.NaplnZivoty(pz, ptr_PZ1);
        /* Napln zivot Hrac 2 */
        Hrac.NaplnZivoty(pz, ptr_PZ2);

        /* Naplnenie udajov do stackov zo suboru  - prvky*/

        /* Napln stack Hrac 1 */
        Hrac.NaplnStack(1, ptr_PP1);

        /* Napln stack Hrac 2*/
        Hrac.NaplnStack(2, ptr_PP2);



        /* Napln stack Hrac 2*/
       // Hrac.NaplnStack(2, ptr_PP2);
        //cout << " Hrac 2: " << PP2.Top() << endl;

    }


    else if (Volba  == "Load")
    {

        int koniec, hrac, count_p1, count_p2, data, pz;
        string pokus;

        pz = Hrac.KolkoPZ();

        /* Napln zivot Hrac 1 */
        Hrac.NaplnZivoty(pz, ptr_PZ1);
        /* Napln zivot Hrac 2 */
        Hrac.NaplnZivoty(6, ptr_PZ2); // Tu je to zle ak maju rozdielne zivoty

        /* Napln a zrataj stack Hrac 1 */
        count_p1 = Hrac.NaplnStack(1, ptr_PP1);

        /* Napln a zrataj stack Hrac 2*/
        count_p2 = Hrac.NaplnStack(2, ptr_PP2);

        // Hra



        koniec = 0; hrac = 1;
        while(koniec == 0)
        {

            meno = Hrac.MenoHraca(hrac);
            cout << "Hada hrac c." << hrac << " - " << meno << endl;
            cout << "PZ_ME=";if(hrac == 1){cout << PZ1.Top();} else if (cout << PZ2.Top());
            cout << " PZ_OPP="; if(hrac == 1){ cout << PZ2.Top();}else if (cout << PZ1.Top()); cout << endl;
            cout << "PP_ME=";if(hrac == 1){cout << count_p1;} else if (cout << count_p2);
            cout << " PP_OPP=";if(hrac == 2){cout << count_p2;} else if (cout << count_p1); cout << endl;

            // Hadanie
            pz = 0;
            do
            {
                cout << "Hadajte prvok na vrchu protivnikovho zasobnika: ";
                cin >> pokus;
                // Kontrola intervalu
                pz = New.KontrolaIntervalu(pokus);
            }
            while(pz == 0);

            data = stoi(pokus);



            koniec = 1;

        }



    }
/*
    else if (Volba  == "Exit")
    {
        cout << "Vybral si si Exit" << endl;
    }
*/




    //New.SetNewPlayer();

    return 0;
}





