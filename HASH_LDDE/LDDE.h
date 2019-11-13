#ifndef LDDE_header
#define LDDE_header

#include <iostream>

using namespace std;

template <typename T>
class LDDE;

template <typename T>
ostream &operator<<(ostream &saida, const LDDE<T> &lddeCopia);

template <typename T>
class No
{
private:
    T valor;
    No<T> *proximo;
    No<T> *anterior;

public:
    friend ostream &operator<<(ostream &saida, const No &noCopia)
    {
        saida << noCopia.valor << " ";
        return saida;
    }

    friend class LDDE<T>;
    friend ostream &operator<<<T>(ostream &saida, const LDDE<T> &lddeCopia);
};

template <typename T>
class LDDE
{
private:
    No<T> *primeiro;
    No<T> *ultimo;
    T sentinela;
    int inseridos;

    void copia(const LDDE &lddeCopia)
    {
        while (RemovePorIndex(0))
        {
        }
        No<T> *atual = lddeCopia.primeiro;

        while (atual)
        {
            Insere(atual->valor);
            atual = atual->proximo;
        }
    }

public:
    LDDE()
    {
        primeiro = NULL;
        ultimo = NULL;
        inseridos = 0;
    }

    LDDE(const LDDE &lddeCopia)
    {
        inseridos = 0;
        primeiro = NULL;
        ultimo = NULL;
        copia(lddeCopia);
    }

    const &operator=(const LDDE &lddeCopia)
    {
        copia(lddeCopia);
    }

    bool Insere(T valor)
    {
        No<T> *atual = primeiro;
        No<T> *anterior = NULL;
        No<T> *novo = new No<T>;

        novo->valor = valor;
        novo->proximo = NULL;
        novo->anterior = NULL;

        while (atual && atual->valor <= valor)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (anterior)
        {
            anterior->proximo = novo;
        }
        else
        {
            primeiro = novo;
        }

        if (atual)
        {
            atual->anterior = novo;
        }
        else
        {
            ultimo = novo;
        }

        novo->anterior = anterior;
        novo->proximo = atual;

        inseridos++;
        return true;
    }

    bool Remove(T valor)
    {
        int index = Busca(valor);
        if (!(index >= 0 && index < inseridos))
        {
            return false;
        }

        No<T> *atual = primeiro;
        int i = 0;
        while (atual && index != i)
        {
            atual = atual->proximo;
            i++;
        }

        if (atual->anterior)
        {
            atual->anterior->proximo = atual->proximo;
        }
        else
        {
            primeiro = atual->proximo;
        }

        if (atual->proximo)
        {
            atual->proximo->anterior = atual->anterior;
        }
        else
        {
            ultimo = atual->anterior;
        }

        delete atual;
        inseridos--;
        return true;
    }

    bool RemovePorIndex(int index)
    {
        if (!(index >= 0 && index < inseridos))
        {
            return false;
        }

        No<T> *atual = primeiro;
        int i = 0;
        while (atual && index != i)
        {
            atual = atual->proximo;
            i++;
        }

        if (atual->anterior)
        {
            atual->anterior->proximo = atual->proximo;
        }
        else
        {
            primeiro = atual->proximo;
        }

        if (atual->proximo)
        {
            atual->proximo->anterior = atual->anterior;
        }
        else
        {
            ultimo = atual->anterior;
        }

        delete atual;
        inseridos--;
        return true;
    }

    int Busca(T valor)
    {
        No<T> *atual = primeiro;
        int index = 0;
        while (atual)
        {
            if (atual->valor == valor)
            {
                return index;
            }
            atual = atual->proximo;
            index++;
        }

        return -1;
    }

    void ImprimeCrescente()
    {
        No<T> *atual = primeiro;
        while (atual)
        {
            cout << *atual << " ";
            atual = atual->proximo;
        }

        cout << endl;
    }

    void ImprimeDescrescente()
    {
        No<T> *atual = ultimo;
        while (atual)
        {
            cout << *atual;
            atual = atual->anterior;
        }

        cout << endl;
    }

    T &operator[](int index)
    {
        if (index < 0 || index >= inseridos)
        {
            return sentinela;
        }

        No<T> *atual = primeiro;
        int i = 0;
        while (atual)
        {
            if (index == i)
            {
                return atual->valor;
            }
            atual = atual->proximo;
            i++;
        }
    }

    ~LDDE()
    {
        while (RemovePorIndex(0))
            ;
    }

    friend ostream &operator<<<T>(ostream &saida, const LDDE<T> &lddeCopia);
};

template <typename T>
ostream &operator<<(ostream &saida, const LDDE<T> &lddeCopia)
{
    No<T> *atual = lddeCopia.primeiro;
    while (atual)
    {
        saida << *atual;
        atual = atual->proximo;
    }
    return saida;
}
#endif // LDDE_header