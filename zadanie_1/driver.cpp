#include <iostream>
#include <fstream>

/* Trieda na pracu s volbou New */
class ChoseNew{
	
	
	public:
		std::ofstream file;

		int SetNewData()
		{
			OpenFile();
			
			CloseFile();
			return 0;
		}

	private:
		
		void OpenFile()
		{
			file.open("game.txt", std::ofstream::trunc);
			std::cout << "Som tu." << std::endl;
		}	

		void CloseFile()
		{
			file.close();
		}

};

/* Trieda na pracu s volbou Load */
class ChoseLoad{
	public:

	private:	
};

int main()
{
    
    using namespace std;
   	ChoseNew New;

    New.SetNewData();


    
    return 0;
}





