#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "stack.cpp"

/* Trieda na pracu s volbou New */
class ChoseNew{

	public:
        std::fstream file;

		/* Nastav parametre hry */
		void SetNewData(/* pocet zivotov*/ int *pz, /* prvky*/ int *pp, /* interval */ int* dInt, int *hInt)
		{
            using namespace std;
            string temp;

            cout << "Zadajte pocet zivotov hracov: " ;
            cin >> temp;
            *pz = stoi(temp);


            cout << "Zadajte pocet prvkov hracov: " ;
            cin >> temp;
            *pp = stoi(temp);


            cout << "Zadajte zaciatok uzavreteho intervalu prvkov: " ;
            cin >> temp;
            *dInt = stoi(temp);


            cout << "Zadajte koniec uzavreteho intervalu prvkov: " ;
            cin >> temp;
            *hInt = stoi(temp);



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

        int KontrolaIntervalu(std::string interval) // Cita zo suboru
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

        void SetNewPlayer(/* pocet zivotov*/ int *pz, /* prvky*/ int *pp, /* interval */ int* dInt, int *hInt, IntStack *PZ, IntStack *PP, std::string *name,  int hrac)
		{
			using namespace std;

			cout << "Nacitavanie udajov hraca c." << hrac << endl;
			cout << "Parametre hry: PZ=" << *pz << ",PP=" << *pp << ",<" << *dInt << "," << *hInt << ">" << endl;

			cout << "Zadajte svoje meno: "; cin >> *name;
            NaplnPrvky(pp, PP, dInt, hInt);


			NaplnZivoty(pz, PZ); // Bez vystupu, iba naplni stack so zivotmi


		}

        int SkontrolujInterval(std::string value, int* dInt, int *hInt) // Z klavesnice, pre vlastnu blbost to tu musim mat dvakrat
        {
            int i, result;
            i = std::stoi(value);

             /* Kontrola ci je cislo v intervale */
			if( i >= *dInt && i <= *hInt )
			{
                result = 1;
			}
			else
			{
                std::cout << "Cislo je mimo intervalu, zadaj znova" << std::endl;
                result = 0;
			}

			return result;

        }

        std::string MenoHraca(int hrac, std::string *ptr_meno1,std::string *ptr_meno2)
        {
            switch(hrac)
            {
                case 1: return *ptr_meno1; break;
                case 2: return *ptr_meno2; break;
            }
            return 0;
        }


	private:
        void NaplnZivoty(int *pz, IntStack *PZ)
        {
            int i;

            for(i = 0;  i < *pz + 1; i++)
            {
                PZ->Push(i);
            }

        }

        void NaplnPrvky(int *pp, IntStack *PP, int* dInt, int *hInt )
        {

            using namespace std;
            int i,c;
            string temp;
            c = 0;


            for(i = 1; i < *pp + 1; i++ )
            {
                do
                {
                    cout << "Zadajte prvok č." << i << ": ";
                    cin >> temp;
                    // Kontrola intervalu
                    c = SkontrolujInterval(temp, dInt, hInt);

                }
                while(c == 0);

                PP->Push(stoi(temp));

            }
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



        }

        void VyhodnotTah(int data, int hra, int *ptr_count, IntStack *ptr_PP, IntStack *ptr_PZ)
        {
            using namespace std;
            int pz;

            if(data != ptr_PP->Top())
            {
                // Neuhadol
                pz = ptr_PZ->Top();

                // Skontroluj pocet zivotov
                if(pz == 1){cout << "Koniec hry dosli ti zivoty" << endl; _Exit(0);}

                cout <<  "Neuhadli ste" << endl; ptr_PZ->Pop();

            }
            else
            {
                int pz; // aktualny pocet zivotov

                if(hra == 1) // Ak je prva hra pridaj zivot navyse
                {
                    pz = ptr_PZ->Top(); // zisti aktualny pocet zivotov
                    ptr_PZ->Push(pz + 1);
                }

                // Ak uhadol pridaj zivot
                pz = ptr_PZ->Top(); // zisti aktualny pocet zivotov
                ptr_PZ->Push(pz + 1);

                // Odober pritohracovi prvok
                ptr_PP->Pop();

                // Odrataj mu prvky
                if(*ptr_count == 1){cout << "Vyhral si, uhadol si vsetky prvky, koniec hry" << endl; _Exit(0);}
                *ptr_count = *ptr_count - 1;
                cout << "Lucky hit!" << endl;
            }

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

// Funkcia na stlacenie ENTER // 2 hodiny zabite s picovinou
void WaitForEnter()
{
    std::cin.get();
    std::cin.ignore();
}



int main()
{

    using namespace std;

    string Volba, meno;
    int ControlChoice;

    ChoseNew New;
   	ClearScreen CS;
    Hrac Hrac;

   	IntStack PZ1; // Pocet zivotov hraca cislo 1
   	IntStack *ptr_PZ1;

   	IntStack PP1; // Prvky hraca 1
   	IntStack *ptr_PP1;

   	IntStack PZ2; // Pocet zivotov hraca cislo 2
    IntStack *ptr_PZ2;

   	IntStack PP2; // Prvky hraca 2
    IntStack *ptr_PP2;


    ptr_PP1 = &PP1;
    ptr_PP2 = &PP2;
    ptr_PZ1 = &PZ1;
    ptr_PZ2 = &PZ2;

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

        int koniec, hra, hrac, count_p1, count_p2, data, pz, pp, dInt, hInt;
        string pokus, name1, name2, tmp_name;


        int *ptr_pz; int *ptr_dInt;int *ptr_hInt; int *ptr_pp;
        ptr_pz = &pz; ptr_pp = &pp;
        ptr_dInt = &dInt; ptr_hInt = &hInt;

        string *ptr_name1; string *ptr_name2;
        ptr_name1 = &name1; ptr_name2 = &name2;



        hra = 1; // Indikuje prve kolo
        int *ptr_count_p1; // pocet prvkov hrac1
        int *ptr_count_p2; // pocet prvkov hrac 2

        ptr_count_p1 = &count_p1;
        ptr_count_p2 = &count_p2;

        New.SetNewData(ptr_pz, ptr_pp, ptr_dInt,ptr_hInt);
        count_p1 = *ptr_pp;count_p2 = *ptr_pp; // Nastav pocet prvkov hracom


        CS.clear_screen();

        New.SetNewPlayer(ptr_pz, ptr_pp, ptr_dInt,ptr_hInt, ptr_PZ1,ptr_PP1, ptr_name1, 1);

        CS.clear_screen();

        New.SetNewPlayer(ptr_pz, ptr_pp, ptr_dInt,ptr_hInt, ptr_PZ2,ptr_PP2, ptr_name2, 2);



        CS.clear_screen();


        koniec = 0; hrac = 1;
        while(koniec == 0)
        {

            tmp_name = New.MenoHraca(hrac, ptr_name1, ptr_name2);
            cout << "Hada hrac c." << hrac << " - " << tmp_name << endl;
            cout << "PZ_ME=";if(hrac == 1){cout << PZ1.Top();} else if (cout << PZ2.Top());
            cout << " PZ_OPP="; if(hrac == 1){ cout << PZ2.Top();}else if (cout << PZ1.Top()); cout << endl;
            cout << "PP_ME=";if(hrac == 1){cout << count_p1;} else if (cout << count_p2);
            cout << " PP_OPP=";if(hrac == 1){cout << count_p2;} else if (cout << count_p1); cout << endl;

            // Hadanie
            pz = 0;
            do
            {
                cout << "Hadajte prvok na vrchu protivnikovho zasobnika: ";
                cin >> pokus;
                // Kontrola intervalu
                pz = New.SkontrolujInterval(pokus, ptr_dInt, ptr_hInt);
            }
            while(pz == 0);

            data = stoi(pokus);

            // Vyhodnotenie tipu
            if(hrac == 1)
                {
                   Hrac.VyhodnotTah(data,hra,ptr_count_p2,ptr_PP2,ptr_PZ1);
                }

            if(hrac == 2)
                {
                    Hrac.VyhodnotTah(data,hra,ptr_count_p1,ptr_PP1,ptr_PZ2);
                    if(hra = 1){hra = 0;} // Ukonci prve kolo
                }

            // Zobrazenie stavu po hadani
            cout << "PZ_ME=";if(hrac == 1){cout << PZ1.Top();} else if (cout << PZ2.Top());
            cout << " PZ_OPP="; if(hrac == 1){ cout << PZ2.Top();}else if (cout << PZ1.Top()); cout << endl;
            cout << "PP_ME=";if(hrac == 1){cout << count_p1;} else if (cout << count_p2);
            cout << " PP_OPP=";if(hrac == 1){cout << count_p2;} else if (cout << count_p1); cout << endl;

            // Cakaj na ENTER
            cout << "Stlacte enter a prenechajte hru hracovi c.: " ;
            if(hrac == 1){cout << "2";} else{cout << "1";}

            WaitForEnter();

            // Vymaz obrazovku
            CS.clear_screen();


            // Prehod hracov
            switch(hrac)
            {
                case 2: hrac = 1; break;
                case 1: hrac = 2; break;
            }


        }

    }


    else if (Volba  == "Load")
    {

        int koniec, hrac, count_p1, count_p2, data, pz, hra;
        string pokus;
        hra = 1; // Indikuje prve kolo
        int *ptr_count_p1;
        int *ptr_count_p2;

        ptr_count_p1 = &count_p1;
        ptr_count_p2 = &count_p2;

        pz = Hrac.KolkoPZ();

        /* Napln zivot Hrac 1 */
        Hrac.NaplnZivoty(pz, ptr_PZ1);

        /* Napln zivot Hrac 2 */
        Hrac.NaplnZivoty(pz, ptr_PZ2); // Tu je to zle ak maju rozdielne zivoty

        /* Napln a zrataj stack Hrac 1 */
        *ptr_count_p1 = Hrac.NaplnStack(1, ptr_PP1);

        /* Napln a zrataj stack Hrac 2*/
        *ptr_count_p2 = Hrac.NaplnStack(2, ptr_PP2);

        // Hra

        koniec = 0; hrac = 1;
        while(koniec == 0)
        {

            meno = Hrac.MenoHraca(hrac);
            cout << "Hada hrac c." << hrac << " - " << meno << endl;
            cout << "PZ_ME=";if(hrac == 1){cout << PZ1.Top();} else if (cout << PZ2.Top());
            cout << " PZ_OPP="; if(hrac == 1){ cout << PZ2.Top();}else if (cout << PZ1.Top()); cout << endl;
            cout << "PP_ME=";if(hrac == 1){cout << count_p1;} else if (cout << count_p2);
            cout << " PP_OPP=";if(hrac == 1){cout << count_p2;} else if (cout << count_p1); cout << endl;

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

            // Vyhodnotenie tipu
            if(hrac == 1)
                {
                   Hrac.VyhodnotTah(data,hra,ptr_count_p2,ptr_PP2,ptr_PZ1);
                }

            if(hrac == 2)
                {
                    Hrac.VyhodnotTah(data,hra,ptr_count_p1,ptr_PP1,ptr_PZ2);
                    if(hra = 1){hra = 0;} // Ukonci prve kolo
                }

            // Zobrazenie stavu po hadani
            cout << "PZ_ME=";if(hrac == 1){cout << PZ1.Top();} else if (cout << PZ2.Top());
            cout << " PZ_OPP="; if(hrac == 1){ cout << PZ2.Top();}else if (cout << PZ1.Top()); cout << endl;
            cout << "PP_ME=";if(hrac == 1){cout << count_p1;} else if (cout << count_p2);
            cout << " PP_OPP=";if(hrac == 1){cout << count_p2;} else if (cout << count_p1); cout << endl;

            // Cakaj na ENTER
            cout << "Stlacte enter a prenechajte hru hracovi c.: " ;
            if(hrac == 1){cout << "2";} else{cout << "1";}

            WaitForEnter();

            // Vymaz obrazovku
            CS.clear_screen();


            // Prehod hracov
            switch(hrac)
            {
                case 2: hrac = 1; break;
                case 1: hrac = 2; break;
            }


        }

    }

    else if (Volba  == "Exit")
    {
        cout << "Vybral si si Exit" << endl;
        return 0;
    }

    return 0;
}





