#include <iostream>

using namespace std;

template <typename T>
class LDE;

template <typename T>
ostream &operator<<(ostream &saida, const LDE<T> &ldeCopia);
template <typename T>
class No
{
private:
    T valor;
    No<T> *proximo;

public:
    friend ostream &operator<<(ostream &saida, const No &noCopia)
    {
        saida << noCopia.valor << " ";
        return saida;
    }

    friend class LDE<T>;
    friend ostream &operator<<<T>(ostream &saida, const LDE<T> &ldeCopia);
};

template <typename T>
class LDE
{
private:
    No<T> *primeiro = NULL;
    int inseridos = 0;
    T sentinela;

    void copia(const LDE &ldeCopia)
    {
        while (Remove(0))
        {
        }

        inseridos = 0;
        primeiro = NULL;
        No<T> *copia = ldeCopia.primeiro;

        while (copia)
        {
            Insere(copia->valor);
            copia = copia->proximo;
        }
    }

public:
    LDE()
    {
        primeiro = NULL;
        inseridos = 0;
    }

    LDE(const LDE &ldeCopia)
    {
        copia(ldeCopia);
    }

    bool Insere(T valor)
    {
        No<T> *atual = primeiro;
        No<T> *anterior = NULL;
        No<T> *novo = new No<T>;
        novo->valor = valor;
        novo->proximo = NULL;

        while (atual && atual->valor <= valor)
        {
            anterior = atual;
            atual = atual->proximo;
        }

        if (!anterior)
        {
            primeiro = novo;
        }
        else
        {
            anterior->proximo = novo;
        }

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
        No<T> *anterior = NULL;
        int i = 0;
        while (atual && index != i)
        {
            i++;
            cout << "Valor do atual: " << atual->valor << endl;
            anterior = atual;
            atual = atual->proximo;
        }

        if (!anterior && atual->proximo)
        {
            primeiro = primeiro->proximo;
        }
        else if (anterior && !(atual->proximo))
        {
            anterior->proximo = NULL;
        }
        else if (anterior && atual)
        {
            anterior->proximo = atual->proximo;
        }

        delete atual;
        if (!anterior && !atual->proximo)
        {
            primeiro = NULL;
        }
        inseridos--;
        return true;
    }

    int Busca(T valor)
    {
        No<T> *atual = primeiro;
        int index = 0;
        while (atual && atual->valor != valor)
        {
            atual = atual->proximo;
            index++;
        }

        if (atual)
            return index;

        return -1;
    }

    void Imprime()
    {
        No<T> *atual = primeiro;
        while (atual)
        {
            cout << *atual << endl;
            atual = atual->proximo;
        }
        cout << endl;
    }

    ~LDE()
    {
        while (Remove(0))
        {
        }
    }

    const T &operator[](int index)
    {
        if (!(index >= 0 && index < inseridos))
        {
            return sentinela;
        }

        No<T> *atual = primeiro;
        int i = 0;
        while (atual && index != i)
        {
            atual = atual->proximo;
        }

        return atual->valor;
    }

    const &operator=(const LDE &ldeCopia)
    {
        copia(ldeCopia);
    }

    friend ostream &operator<<<T>(ostream &saida, const LDE &ldeCopia);
};

template <typename T>
ostream &operator<<(ostream &saida, const LDE<T> &ldeCopia)
{
    No<T> *atual = ldeCopia.primeiro;
    while (atual)
    {
        saida << *atual;
        atual = atual->proximo;
    }
    saida << endl;
    return saida;
}

int main()
{
    LDE<int> lde;
    lde.Insere(4);
    lde.Insere(8);
    lde.Insere(12);
    lde.Insere(99);
    lde.Insere(14);
    lde.Insere(104);
    lde.Imprime();

    lde.Insere(1);
    lde.Insere(55);
    lde.Insere(106);

    lde.Imprime();

    cout << endl;
    cout << lde.Busca(1) << endl;
    cout << lde.Busca(99) << endl;
    cout << lde.Busca(106) << endl;
    cout << lde.Busca(1092) << endl
         << endl;

    lde.Remove(0);
    lde.Remove(0);
    lde.Imprime();
    lde.Remove(6);
    lde.Imprime();
    lde.Remove(3);
    lde.Imprime();
    lde.Remove(0);
    lde.Imprime();
    lde.Remove(0);
    lde.Imprime();
    lde.Remove(0);
    lde.Imprime();
    lde.Remove(0);
    lde.Imprime();
    lde.Remove(0);
    lde.Insere(345);
    cout << lde[0] << endl;
    cout << lde[1] << endl;
    lde.Imprime();

    LDE<int> lde2(lde);

    cout << "LDE 2: " << endl;
    lde2.Imprime();
    lde2.Insere(567);
    lde.Imprime();
    lde2.Imprime();

    cout << "COUT DA LDE2: " << endl;
    cout << lde2;
    cout << lde;

    cout << "COUT ANTES DO IGUAL: " << endl;
    cout << lde2;

    cout << "COUT DEPOIS DO IGUAL: " << endl;
    lde2 = lde;
    cout << lde2;

    return 0;
}