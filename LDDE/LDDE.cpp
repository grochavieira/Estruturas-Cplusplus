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
        while (Remove(0))
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

    bool Remove(int index)
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
        while (Remove(0))
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

int main()
{
    LDDE<int> ldde;

    ldde.Insere(5);
    ldde.Insere(8);
    ldde.Insere(10);
    ldde.Insere(12);
    ldde.Insere(99);
    ldde.Insere(55);
    ldde.ImprimeCrescente();

    ldde.Remove(3);
    ldde.ImprimeCrescente();

    ldde.Remove(0);
    ldde.ImprimeCrescente();

    ldde.Remove(3);
    ldde.ImprimeCrescente();

    cout << ldde.Busca(55) << endl;
    cout << ldde.Busca(10) << endl;
    cout << ldde.Busca(8) << endl;

    cout << ldde[2] << endl;
    cout << ldde[0] << endl;
    cout << ldde[4] << endl;

    LDDE<int> ldde2(ldde);
    cout << "LDDE2: " << endl;
    ldde2.ImprimeCrescente();
    ldde2.Insere(56);
    ldde2.Insere(77);
    cout << "LDDE2: " << endl;
    ldde2.ImprimeCrescente();
    cout << "LDDE: " << endl;
    ldde.ImprimeCrescente();

    LDDE<int> ldde3;

    ldde3 = ldde2;
    cout << "LDDE3: " << endl;
    ldde3.ImprimeCrescente();
    ldde3.Insere(11);
    ldde3.Insere(999);
    cout << "LDDE3: " << endl;
    ldde3.ImprimeCrescente();
    cout << "LDDE2: " << endl;
    ldde2.ImprimeCrescente();

    cout << "USANDO COUT" << endl;

    cout << ldde << endl;
    cout << ldde2 << endl;
    cout << ldde3 << endl;

    return 0;
}