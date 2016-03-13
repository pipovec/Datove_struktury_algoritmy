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
			int i = 0;

			OpenFileW();

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

			CloseFile();
			return 0;
		}

		void SetNewPlayer()
		{
			std::string Meno;
			int i,PP,value;


			// Nacitanie kolko prvkov sa bude hadat
			PP = PocetPrvkov();

            // Otvrorenie suboru na pridanie riadku
            std::fstream file;
            file.open("game.txt", std::fstream::out | std::fstream::app);

            std::cout << "Zadaj svoje meno: ";
			std::cin >> Meno;
			file << "\n" << Meno << ";";


			for(i = 0; i < PP; i++)
			{
                std::cout << "Zadaj prvok c." << i+1 << ":";
                std::cin >> value;
                file << value ; // Osetrit tak aby som nevysiel z definovaneho intervalu.
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

			std::fstream file;

			file.open("game.txt", std::fstream::in); // Otvorim len na citanie;

			std::getline (file, i, ';');// Vynecham lebo je to pocet zivotov
			std::getline (file, i, ';');// Toto je pocet prvkov

			file.close();

			PP = std::stoi(i);

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

		void OpenFileW()
		{
			file.open("game.txt",std::fstream::out | std::fstream::trunc);
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

			int PZ,PP,dINT,hINT;
			std::string value;

			std::fstream file;

			file.open("game.txt");


			getline(file,value,';');
			std::cout << "Parametre hry: PZ=" <<  value;

			getline(file,value,';');
			std::cout << ",PP=" <<  value;

			getline(file,value,';');
			std::cout << ",<"<<  value;

			getline(file,value,';');
			std::cout << "," <<  value << ">" << std::endl;

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
   	ChoseNew New;
   	ClearScreen CS;
   	Hrac Hrac;
   	IntStack Hrac1;
   	IntStack Hrac2;

    New.SetNewData();

    New.SetNewPlayer();

    return 0;
}





