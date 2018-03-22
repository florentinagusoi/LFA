#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
int stareinitiala, starifin[10], v[100], pozitieact, nrmuchii, nrfin;
char cuvant[100];
ifstream f("date.in");

struct tranzitie
{
    char litera;
    int nodcurent;
    int nodurmator;
} tranz[100];

/**
*
*@param stareact reprezinta nodul in care se afla cu recursivitatea
*@param cuvant reprezinta un sir de caractere care se modifica la fiecare pas,
*stergand prima litera
*@param nrmuchii este numarul de muchii, pe fiecare muchie avand o singura litera
*@param nrfin este numarul total de stari finale ale automatului
*/

void automat(int starecurenta, char cuvant[100])
{
    int i,OK = 0;
    char copie[100];
    if(cuvant[0] == NULL)
    {
        for(i = 0; i < nrfin; i ++)
            if(starecurenta == starifin[i])
            {
                v[pozitieact] = 1;
                pozitieact ++;
                OK = 1;
            }
        if(OK == 0)
        {
            v[pozitieact] = 0;
            pozitieact ++;
        }
    }
    for(i = 0; i < nrmuchii; i ++)
        if(tranz[i].nodcurent == starecurenta && cuvant[0] == tranz[i].litera)
        {
            strcpy(copie, cuvant+1);
            automat(tranz[i].nodurmator, copie);
        }

}

/**
*
*@param cuvant este un string care reprezinta cuvantul introduc de la tastatura
*in cadrul functiei verificareautomat se va determina daca stringul "cuvant" apartine
*sau nu automatului din "date.in"
*valoarea returnata este de tip bool, true daca apartine si false in caz contrar
*/

bool verificareautomat(char cuvant[100])
{
    int i;
    automat(stareinitiala, cuvant);
    for(i = 0; i < pozitieact; i ++)
        if(v[i] == 1)
            return true;
        return false;
}

int main()
{
    cout << "Introduceti numarul nodului care contine starea initiala: ";
    cin >> stareinitiala;
    cout << "Introduceti numarul starilor finale: ";
    cin>>nrfin;
    cout << "Introduceti starile finale: ";
    int OK = 0;
    for(int i = 0; i < nrfin; i ++)
        cin >> starifin[i];
    f >> nrmuchii;
    for(int i = 0; i < nrmuchii; i ++)
    {
        f >> tranz[i].nodcurent;
        f >> tranz[i].litera;
        f >> tranz[i].nodurmator;
    }
    cout << "Introduceti cuvantul:" << endl;
    cin >> cuvant;
    cout << endl;
    if(verificareautomat(cuvant))
        cout << "acceptat";
    else cout << "neacceptat";
    return 0;
}
