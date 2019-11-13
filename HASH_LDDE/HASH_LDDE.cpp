#include <iostream>
#include "LDDE.h"
using namespace std;

template <typename T, unsigned int (*F)(T valor, int tamanho)>
class HASH;

template <typename T, unsigned int (*F)(T valor, int tamanho)>
ostream &operator<<(ostream &saida, const HASH<T, F> &hashCopia);

template <typename T>
unsigned int metodoDivisao(T valor, int tamanho)
{
    return valor % tamanho;
}

template <typename T, unsigned int (*F)(T valor, int tamanho)>
class HASH
{
private:
    LDDE<T> *tabelaHash;
    int tamanho;
    int inseridos;

    unsigned int funcaoHash(T valor)
    {
        return F(valor, tamanho);
    }

public:
    HASH(int tamanho)
    {
        this->tamanho = tamanho;
        tabelaHash = new LDDE<T>[tamanho];
        inseridos = 0;
    }

    ~HASH()
    {
        delete[] tabelaHash;
    }

    bool Contem(T valor)
    {
        return tabelaHash[funcaoHash(valor)].Busca(valor) != -1;
    }

    bool Insere(T valor)
    {
        if (Contem(valor) || inseridos >= tamanho)
        {
            return false;
        }
        inseridos++;
        return tabelaHash[funcaoHash(valor)].Insere(valor);
    }

    bool Remove(T valor)
    {
        if (!(Contem(valor)) || inseridos == 0)
        {
            return false;
        }

        inseridos--;
        return tabelaHash[funcaoHash(valor)].Remove(valor);
    }

    void Imprime()
    {
        cout << "Tabela HASH: " << endl;
        for (int i = 0; i < tamanho; i++)
        {
            cout << "[" << i << "] ==> ";
            tabelaHash[i].ImprimeCrescente();
        }
        cout << endl;
    }

    friend ostream &operator<<<T, F>(ostream &saida, const HASH &hashCopia);
};

template <typename T, unsigned int (*F)(T valor, int tamanho)>
ostream &operator<<(ostream &saida, const HASH<T, F> &hashCopia)
{
    saida << "TABELA HASH: " << endl;
    for (int i = 0; i < hashCopia.tamanho; i++)
    {
        saida << "(" << i << ") --> ";
        hashCopia.tabelaHash[i].ImprimeCrescente();
    }
    saida << endl;
    return saida;
}

int main()
{
    HASH<int, metodoDivisao> hash(5);

    hash.Insere(10);
    hash.Insere(12);
    hash.Insere(13);
    hash.Insere(9);
    hash.Insere(99);
    hash.Insere(109);
    hash.Imprime();

    hash.Remove(99);
    hash.Remove(10);
    hash.Imprime();

    cout << hash << endl;
}