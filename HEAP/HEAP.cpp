#include <iostream>

using namespace std;

template <typename T, int MAX>
class HEAP;

template <typename T, int MAX>
class HEAP
{
private:
    T heap[MAX];
    int inseridos;
    T sentinela;

    int filhoDireitoIndex(int index)
    {
        return (index * 2) + 2;
    }

    int filhoEsquerdoIndex(int index)
    {
        return (index * 2) + 1;
    }

    int paiIndex(int index)
    {
        if (index == 0)
            return -1;
        return (index - 1) / 2;
    }

    int ultimoPaiIndex()
    {
        return paiIndex(inseridos - 1);
    }

    void ordenaHeapPorCima(int indexAtual)
    {
        if (indexAtual > ultimoPaiIndex())
        {
            return;
        }

        int indexFilhoDireito = filhoDireitoIndex(indexAtual);
        int indexFilhoEsquerdo = filhoEsquerdoIndex(indexAtual);
        cout << "VALOR DO INDEX: " << indexAtual << " HEAP: " << heap[indexAtual]
             << " FILHO ESQUERDO: " << heap[indexFilhoEsquerdo] << " FILHO DIREITO: " << heap[indexFilhoDireito] << endl;
        int menorValorIndex = indexAtual;
        if (indexFilhoEsquerdo < inseridos && indexFilhoEsquerdo != -1 && heap[indexFilhoEsquerdo] < heap[menorValorIndex])
        {
            menorValorIndex = indexFilhoEsquerdo;
        }
        if (indexFilhoDireito < inseridos && indexFilhoEsquerdo != -1 && heap[indexFilhoDireito] < heap[menorValorIndex])
        {
            menorValorIndex = indexFilhoDireito;
        }

        if (menorValorIndex == indexAtual)
        {
            return;
        }

        T temp = heap[indexAtual];
        heap[indexAtual] = heap[menorValorIndex];
        heap[menorValorIndex] = temp;

        ordenaHeapPorCima(menorValorIndex);
    }

    void ordenaHeap()
    {
        for (int i = ultimoPaiIndex(); i >= 0; i--)
        {
            ordenaHeapPorCima(i);
        }
    }

public:
    HEAP()
    {
        inseridos = 0;
    }

    HEAP(T v[], int inseridos)
    {
        this->inseridos = 0;
        if (inseridos >= MAX)
        {
            return;
        }

        for (int i = 0; i < inseridos; i++)
        {
            heap[i] = v[i];
        }

        this->inseridos = inseridos;
        ordenaHeap();
    }

    bool Insere(T valor)
    {
        if (inseridos >= MAX)
        {
            return false;
        }
        heap[inseridos] = valor;
        inseridos++;
        for (int i = ultimoPaiIndex(); i >= 0; i = paiIndex(i))
        {
            ordenaHeapPorCima(i);
        }
        return true;
    }

    T Remove(bool *ok = nullptr)
    {
        if (inseridos == 0)
        {
            if (ok)
                *ok = false;
            return sentinela;
        }

        if (ok)
            *ok = true;
        T temp = heap[0];
        heap[0] = heap[inseridos - 1];
        heap[inseridos - 1] = temp;
        inseridos--;

        for (int i = ultimoPaiIndex(); i >= 0; i--)
        {
            ordenaHeapPorCima(i);
        }
        return temp;
    }

    void Imprime()
    {
        for (int i = 0; i < inseridos; i++)
        {
            cout << heap[i] << " ";
        }
        cout << endl;
    }
};

int main()
{
    HEAP<int, 10> heap;
    heap.Insere(80);
    heap.Insere(70);
    heap.Insere(60);
    heap.Insere(50);
    heap.Insere(40);
    heap.Insere(30);
    heap.Insere(20);
    heap.Insere(10);
    heap.Imprime();

    heap.Insere(7);
    heap.Imprime();

    bool ok;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    else
    {
        cout << "Não deu certo!" << endl;
    }
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    else
    {
        cout << "Não deu certo!" << endl;
    }
    cout << heap.Remove(&ok) << endl;
    if (ok)
        cout << "Deu certo!" << endl;
    else
    {
        cout << "Não deu certo!" << endl;
    }

    int v[5] = {55, 12, 123, 34, 1};
    HEAP<int, 20> heap2(v, 5);

    heap2.Imprime();

    return 0;
}