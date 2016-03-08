#include <iostream>
#include <fstream>
#include <cstdlib>
/*#include "stack.cpp"

/* Trieda na pracu s volbou New */
class ChoseNew{
		 
	public:
		
		std::ofstream file;
		
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

	private:
		
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
			file.open("game.txt");			
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

			std::ifstream file;
			
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

    New.SetNewData();
    CS.clear_screen();
    Hrac.NacitajParametre();
    
    return 0;
}





