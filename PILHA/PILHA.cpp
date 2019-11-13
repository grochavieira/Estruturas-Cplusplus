#include <iostream>

using namespace std;

template <typename T>
class PILHA;

template <typename T>
ostream &operator<<(ostream &saida, const PILHA<T> &pilhaCopia);

template <typename T>
class PILHA
{
private:
    T *v;
    int inseridos;
    int capacidade;
    T sentinela;

    void copia(const PILHA &pilhaCopia)
    {
        bool ok = true;
        while (ok)
        {
            Desempilha(&ok);
        }

        inseridos = pilhaCopia.inseridos;
        capacidade = pilhaCopia.capacidade;
        v = new T[capacidade];

        for (int i = 0; i < capacidade; i++)
        {
            v[i] = pilhaCopia.v[i];
        }
    }

public:
    PILHA(int tamanho)
    {
        capacidade = tamanho;
        inseridos = 0;
        v = new T[capacidade];
    }

    PILHA(const PILHA &pilhaCopia)
    {
        copia(pilhaCopia);
    }

    const &operator=(const PILHA &pilhaCopia)
    {
        copia(pilhaCopia);
    }

    bool Empilha(T valor)
    {
        if (inseridos == capacidade)
        {
            return false;
        }
        v[inseridos] = valor;
        inseridos++;
        return true;
    }

    T Desempilha(bool *ok = NULL)
    {
        if (inseridos == 0)
        {
            if (ok)
                *ok = false;
            return sentinela;
        }

        if (ok)
            *ok = true;
        T temp = v[inseridos - 1];
        inseridos--;
        return temp;
    }

    void Imprime()
    {
        for (int i = 0; i < inseridos; i++)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    friend ostream &operator<<<T>(ostream &saida, const PILHA &pilhaCopia);
};

template <typename T>
ostream &operator<<(ostream &saida, const PILHA<T> &pilhaCopia)
{
    for (int i = 0; i < pilhaCopia.inseridos; i++)
    {
        saida << pilhaCopia.v[i] << " ";
    }
    saida << endl;
    return saida;
}

int main()
{
    PILHA<int> pilha(7);
    pilha.Empilha(5);
    pilha.Empilha(77);
    pilha.Empilha(88);
    pilha.Empilha(99);
    pilha.Empilha(234);

    PILHA<int> pilha2(10);
    PILHA<int> pilha3(10);

    pilha2 = pilha;

    pilha2.Empilha(999);
    pilha3 = pilha2;

    cout << "COUT" << endl;
    cout << pilha << endl;

    pilha.Imprime();

    bool ok;
    cout << pilha.Desempilha(&ok) << endl;
    if (ok)
        cout << "Deu Certo" << endl;
    cout << pilha.Desempilha(&ok) << endl;
    if (ok)
        cout << "Deu Certo" << endl;
    cout << pilha.Desempilha(&ok) << endl;
    if (ok)
        cout << "Deu Certo" << endl;
    cout << pilha.Desempilha(&ok) << endl;
    if (ok)
        cout << "Deu Certo" << endl;
    else
    {
        cout << "DEU ERRADO" << endl;
    }

    pilha.Imprime();

    cout << "PILHA 2: " << pilha2;

    pilha3.Empilha(777);
    cout << "PILHA 3: " << pilha3;

    return 0;
}