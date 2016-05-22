#include "bintree.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stddef.h>

using namespace std;


// Vytvorenie zakladneho stromu s otazkou
bintree::bintree()
{
    this->koren = this->visit = NULL;

    Uzol_ptr tmp;

    tmp = new Uzol;
    tmp->text = "Ma to dve nohy?";
    tmp->left = NULL;
    tmp->right = NULL;

    this->koren = this->visit = tmp;

}

void bintree::AddNode(string text, Uzol_ptr left, Uzol_ptr right)
{
    Uzol_ptr tmp;

    tmp = new Uzol;
    tmp->text = text;
    tmp->left = left;
    tmp->right = right;

}

void bintree::AddLeft(string text)
{
    Uzol_ptr tmp;

    tmp = new Uzol;
    tmp->text = text;
    tmp->left = NULL;
    tmp->right = NULL;

    this->visit->left = tmp;

}

void bintree::AddRight(string text)
{
    Uzol_ptr tmp;

    tmp = new Uzol;
    tmp->text = text;
    tmp->left = NULL;
    tmp->right = NULL;

    this->visit->right = tmp;

}

// Precitanie laveho uzla
string bintree::ReadLeft()
{
    Uzol_ptr tmp;
    tmp = this->visit->left;

    return tmp->text;
}

// Precitanie praveho uzla
string bintree::ReadRight()
{
    Uzol_ptr tmp;
    tmp = this->visit->right;

    return tmp->text;
}

string bintree::DataRead()
{
    return  this->visit->text ;
}

void bintree::Store(string otazka, string odpoved)
{
    //Najprv si presuniem povodnu odpoved na lavo ako odpoved na nie
    this->AddLeft(this->visit->text);

    // Potom si zadam otazku do povodneho uzla
    this->visit->text = otazka;

    // A potom si pridam do praveho uzla odpoved na ano
    this->AddRight(odpoved);

}

// Chod na zaciatok stromu
void bintree::GoRoot()
{
    visit = koren;
}


// Presun po strome do prava(r) alebo lava(l)
void bintree::Go(char c)
{
    Uzol_ptr tmp;

    // Najprv skontroluj ci exituju listy
    if(IsLeaf())
    {
        cout << "Tento uzol je list, neda sa ist nikam" << endl;
    }
    else
    {
        if(c == 'l')
        {
            tmp = this->visit->left;
        }
        if(c == 'r')
        {
            tmp = this->visit->right;
        }

        this->visit = tmp;

    }

}

// Skontroluj ci ma listy
bool bintree::IsLeaf()
{
    return (visit->left == NULL && visit->right == NULL);
}

bool bintree::Visit(Uzol_ptr koren)
{
    cout << koren->text << endl;
}

Uzol_ptr bintree::LChild(Uzol_ptr ptr)
{
    return (ptr == NULL) ? NULL : ptr->left;
}

Uzol_ptr bintree::RChild(Uzol_ptr ptr)
{
    return (ptr == NULL) ? NULL : ptr->right;
}

Uzol_ptr bintree::Koren()
{
    return koren;
}
// Vhodne na export do suboru
void bintree::Export(ofstream &outFile, Uzol_ptr ptr) {

       string text;

       if (ptr != NULL)
       {
            outFile << ptr->text ;
             if(ptr->left == NULL or ptr->right == NULL)
             {
                outFile << ptr->left << ptr->right;
             }


            this->Export(outFile, LChild(ptr));
            this->Export(outFile, RChild(ptr));

       }



}

bintree::~bintree()
{
    //dtor
};
