#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "stack.cpp"

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
			int i,PP, control;
            control = 0;

			// Nacitanie kolko prvkov sa bude hadat
			PP = PocetPrvkov();

            // Otvrorenie suboru na pridanie riadku
            std::fstream file;
            file.open("game.txt", std::fstream::out | std::fstream::app);

            std::cout << "Zadaj svoje meno: ";
			std::cin >> Meno;
			file << "\n" << Meno << ";";

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

                if(i < PP) file << ";";
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

    string Volba;
    int ControlChoice;

    ChoseNew New;
   	ClearScreen CS;
    Hrac Hrac;
   	//IntStack Hrac1;
   	//IntStack Hrac2;

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

        New.SetNewData(); // Zadavanie novych parametrov hry
        CS.clear_screen();

        cout << "Zadanie udajov hraca c.1" << endl;
        Hrac.NacitajParametre();
        New.SetNewPlayer();

        CS.clear_screen();

        cout << "Zadanie udajov hraca c.2" << endl;
        Hrac.NacitajParametre();
        New.SetNewPlayer();


    }
    else if (Volba  == "Load")
    {
        cout << "Vybral si si Load" << endl;
    }
    else if (Volba  == "Exit")
    {
        cout << "Vybral si si Exit" << endl;
    }





    //New.SetNewPlayer();

    return 0;
}





