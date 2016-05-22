#ifndef BINTREE_H
#define BINTREE_H
#include <string>
#include <iostream>

using namespace std;

    struct Uzol;
    typedef  Uzol* Uzol_ptr;


    struct Uzol
    {
        string text;
        Uzol_ptr left;
        Uzol_ptr right;

    };


class bintree
{


    public:




        /** Default constructor */
        bintree();
        // Zmeni uzol na otazku a povodny presunie do lava a novy da do prava
        void Store(string otazka, string odpoved);
        void AddNode(string text, Uzol_ptr left, Uzol_ptr right);

        // Ide na koren stromu
        void GoRoot();
        // Chod do  l lava/( r prava)
        void Go(char ch);
        // Vrati text laveho listu
        string ReadLeft();
        // Vrati text praveho listu
        string ReadRight();
        // Skontroluje ci to je list
        bool IsLeaf();
        // Precita uzol
        string DataRead();

        void Export(ofstream &outFile, Uzol_ptr ptr);

        bool Visit(Uzol_ptr ptr);

        Uzol_ptr LChild(Uzol_ptr ptr);
        Uzol_ptr RChild(Uzol_ptr ptr);
        Uzol_ptr Koren();

        // Prida lavy list
        void AddLeft(string text);
        // Prida pravy list
        void AddRight(string text);

        Uzol_ptr koren;
        Uzol_ptr visit;

        /** Default destructor */
        virtual ~bintree();
    protected:
    private:




};

#endif // BINTREE_H
