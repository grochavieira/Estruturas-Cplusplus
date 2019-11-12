#include <iostream>

using namespace std;

template <typename T>
class FILA;

template <typename T>
ostream &operator<<(ostream &saida, const FILA<T> &filaCopia);

template <typename T>
class FILA
{
private:
    T *v;
    int capacidade;
    int inicio;
    int fim;
    T sentinela;

    void copia(const FILA &filaCopia)
    {
        delete[] v;
        capacidade = filaCopia.capacidade;
        inicio = filaCopia.inicio;
        fim = filaCopia.fim;
        v = new T[capacidade];
        for (int i = inicio; i != fim; i = (i + 1) % capacidade)
        {
            v[i] = filaCopia.v[i];
        }
    }

public:
    FILA(int tamanho)
    {
        capacidade = tamanho + 1;
        v = new T[capacidade];
        inicio = 0;
        fim = 0;
    }

    FILA(const FILA &filaCopia)
    {
        copia(filaCopia);
    }

    const &operator=(const FILA &filaCopia)
    {
        copia(filaCopia);
    }

    bool Enfileira(T valor)
    {
        if (inicio == ((fim + 1) % capacidade))
        {
            return false;
        }

        v[fim] = valor;
        fim = (fim + 1) % capacidade;
        return true;
    }

    T Desenfileira()
    {
        if (inicio == fim)
        {
            return sentinela;
        }
        T auxiliar = v[inicio];
        inicio = (inicio + 1) % capacidade;
        return auxiliar;
    }

    T Topo()
    {
        if (inicio == fim)
        {
            return sentinela;
        }

        return v[inicio];
    }

    void Imprime()
    {
        for (int i = inicio; i != fim; i = (i + 1) % capacidade)
        {
            cout << v[i] << " ";
        }
        cout << endl;
    }

    ~FILA()
    {
        delete[] v;
    }

    friend ostream &operator<<<T>(ostream &saida, const FILA &filaCopia);
};

template <typename T>
ostream &operator<<(ostream &saida, const FILA<T> &filaCopia)
{
    for (int i = filaCopia.inicio; i != filaCopia.fim; i = (i + 1) % filaCopia.capacidade)
    {
        saida << filaCopia.v[i] << " ";
    }
    saida << endl;
    return saida;
}

int main()
{
    FILA<int> fila(4);
    fila.Enfileira(1);
    fila.Enfileira(5);
    fila.Enfileira(10);
    fila.Enfileira(99);
    fila.Imprime();
    cout << "Valor Removido : " << fila.Desenfileira() << endl;
    fila.Imprime();
    cout << "Valor Removido : " << fila.Desenfileira() << endl;
    fila.Imprime();
    cout << "Valor Removido : " << fila.Desenfileira() << endl;
    fila.Imprime();
    cout << "Valor Removido : " << fila.Desenfileira() << endl;
    fila.Imprime();
    cout << "Valor Removido : " << fila.Desenfileira() << endl;
    fila.Imprime();

    fila.Enfileira(77);
    fila.Enfileira(102);
    fila.Imprime();

    fila.Enfileira(77);
    fila.Enfileira(102);
    fila.Imprime();

    fila.Desenfileira();
    fila.Imprime();
    cout << "VALOR DO TOPO: " << fila.Topo() << endl;

    fila.Desenfileira();
    fila.Imprime();
    cout << "VALOR DO TOPO: " << fila.Topo() << endl;

    FILA<int> fila2(fila);
    cout << "FILA 2: " << endl;
    fila2.Imprime();
    fila2.Enfileira(9999);
    fila2.Imprime();
    fila.Imprime();
    FILA<int> fila3(5);
    cout << "FILA 3: " << endl;
    fila3 = fila2;
    fila3.Imprime();
    fila3.Enfileira(7777);
    fila3.Imprime();
    fila2.Imprime();

    cout << "COM COUT" << endl;

    cout << fila;
    cout << fila2;
    cout << fila3;
    return 0;
}