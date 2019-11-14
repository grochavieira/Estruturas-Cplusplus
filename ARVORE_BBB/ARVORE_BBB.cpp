#include <iostream>
#include <queue>

using namespace std;

template <typename T>
class ABBB;

template <typename T>
class No
{
private:
    T valor;
    No<T> *esquerdo;
    No<T> *direito;
    No<T> *pai;

public:
    friend class ABBB<T>;
};

template <typename T>
class ABBB
{
private:
    No<T> *raiz;
    int inseridos;

    No<T> *Sucessor(No<T> *no)
    {
        if (no->direito)
        {
            no = no->direito;
        }

        while (no->esquerdo)
        {
            no = no->esquerdo;
        }

        return no;
    }

    void ImprimeNoCrescente(No<T> *no)
    {
        if (no->esquerdo)
        {
            ImprimeNoCrescente(no->esquerdo);
        }
        cout << no->valor << " ";
        if (no->direito)
        {
            ImprimeNoCrescente(no->direito);
        }
    }

    void ImprimeNoDecrescente(No<T> *no)
    {
        if (no->direito)
        {
            ImprimeNoDecrescente(no->direito);
        }
        cout << no->valor << " ";
        if (no->esquerdo)
        {
            ImprimeNoDecrescente(no->esquerdo);
        }
    }

    int MAX(int alturaEsquerda, int alturaDireita)
    {
        return (alturaEsquerda > alturaDireita ? alturaEsquerda : alturaDireita);
    }

    int altura(No<T> *no)
    {
        if (!no)
        {
            return -1;
        }
        return MAX(altura(no->esquerdo), altura(no->direito)) + 1;
    }

    int balanceamento(No<T> *no)
    {
        return altura(no->esquerdo) - altura(no->direito);
    }

    void RodaEsquerda(No<T> *no)
    {
        No<T> *novoPai = no->direito;

        if (no->pai)
        {
            if (no->pai->direito && no->pai->direito->valor == no->valor)
            {
                no->pai->direito = novoPai;
            }
            else if (no->pai->esquerdo && no->pai->esquerdo->valor == no->valor)
            {
                no->pai->esquerdo = novoPai;
            }
        }
        else
        {
            raiz = novoPai;
        }

        novoPai->pai = no->pai;
        no->pai = novoPai;
        no->direito = novoPai->esquerdo;
        novoPai->esquerdo = no;
        if (no->direito)
            no->direito->pai = no;
    }

    void RodaDireita(No<T> *no)
    {
        No<T> *novoPai = no->esquerdo;

        if (no->pai)
        {
            if (no->pai->direito && no->pai->direito->valor == no->valor)
            {
                no->pai->direito = novoPai;
            }
            else if (no->pai->esquerdo && no->pai->esquerdo->valor == no->valor)
            {
                no->pai->esquerdo = novoPai;
            }
        }
        else
        {
            raiz = novoPai;
        }

        novoPai->pai = no->pai;
        no->pai = novoPai;
        no->esquerdo = novoPai->direito;
        novoPai->direito = no;
        if (no->esquerdo)
            no->esquerdo->pai = no;
    }

    void balanceiaArvore(No<T> *no)
    {
        while (no)
        {
            int peso = balanceamento(no);
            if (peso == 2)
            {
                if (no->esquerdo && balanceamento(no->esquerdo) < 0)
                {
                    RodaEsquerda(no->esquerdo);
                }
                RodaDireita(no);
            }
            else if (peso == -2)
            {
                if (no->direito && balanceamento(no->direito) > 0)
                {
                    RodaDireita(no->direito);
                }
                RodaEsquerda(no);
            }
            no = no->pai;
        }
    }

    void ImprimeNoPeso(No<T> *no)
    {
        if (no->esquerdo)
        {
            ImprimeNoPeso(no->esquerdo);
        }
        cout << "No ==> " << no->valor << " | Peso --> " << balanceamento(no) << " | Altura ==>--> " << altura(no) << endl;

        if (no->direito)
        {
            ImprimeNoPeso(no->direito);
        }
    }

public:
    ABBB()
    {
        raiz = NULL;
        inseridos = 0;
    }

    ~ABBB()
    {
        Remove(raiz);
    }

    bool Insere(T valor)
    {
        No<T> *novo = new No<T>;
        novo->valor = valor;
        novo->pai = NULL;
        novo->esquerdo = NULL;
        novo->direito = NULL;

        No<T> *atual = raiz;
        No<T> *anterior = NULL;

        while (atual)
        {
            anterior = atual;
            if (atual->valor > valor)
            {
                atual = atual->esquerdo;
            }
            else
            {
                atual = atual->direito;
            }
        }

        if (anterior)
        {
            if (valor < anterior->valor)
            {
                anterior->esquerdo = novo;
            }
            else
            {
                anterior->direito = novo;
            }
            novo->pai = anterior;
        }
        else
        {
            raiz = novo;
        }

        balanceiaArvore(novo);
        inseridos++;
        return true;
    }

    bool Remove(T valor)
    {
        No<T> *atual = Busca(valor);
        No<T> *auxiliar = NULL;
        if (!atual || inseridos == 0)
        {
            return false;
        }

        int filhos = 0;
        if (atual->esquerdo)
            filhos++;
        if (atual->direito)
            filhos++;

        if (filhos == 0)
        {
            if (atual->pai)
            {
                No<T> *pai = atual->pai;
                if (pai->esquerdo->valor == atual->valor)
                {
                    pai->esquerdo = NULL;
                }
                else
                {
                    pai->direito = NULL;
                }
                auxiliar = pai;
            }
            else
            {
                raiz = NULL;
            }
            delete atual;
            inseridos--;
        }
        else if (filhos == 1)
        {
            No<T> *filho = atual->esquerdo;
            No<T> *pai = atual->pai;
            if (!filho)
                filho = atual->direito;

            filho->pai = pai;
            if (pai)
            {
                if (pai->valor > valor)
                {
                    pai->esquerdo = filho;
                }
                else
                {
                    pai->direito = filho;
                }
            }
            else
            {
                raiz = filho;
            }
            auxiliar = pai;
            delete atual;
            inseridos--;
        }
        else
        {
            T valorSucessor = Sucessor(atual)->valor;
            auxiliar = Sucessor(atual)->pai;
            Remove(valorSucessor);
            atual->valor = valorSucessor;
                }
        balanceiaArvore(auxiliar);
        return true;
    }

    bool Remove(No<T> *no)
    {
        return Remove(no->valor);
    }

    No<T> *Busca(T valor)
    {
        No<T> *atual = raiz;

        while (atual && atual->valor != valor)
        {
            if (atual->valor > valor)
            {
                atual = atual->esquerdo;
            }
            else
            {
                atual = atual->direito;
            }
        }

        if (atual)
        {
            return atual;
        }

        return NULL;
    }
    void ImprimeCrescente()
    {
        if (raiz)
        {
            ImprimeNoCrescente(raiz);
            cout << endl;
        }
        else
            cout << endl;
    }

    void ImprimeDecrescente()
    {
        if (raiz)
        {
            ImprimeNoDecrescente(raiz);
            cout << endl;
        }
        else
            cout << endl;
    }

    void Imprime()
    {
        No<T> *atual = raiz;
        No<T> *vertice = NULL;
        queue<No<T> *> lista;
        lista.push(raiz);
        if (raiz)
        {
            while (!lista.empty())
            {
                vertice = lista.front();
                cout << vertice->valor << " ";
                lista.pop();

                if (vertice->esquerdo)
                {
                    lista.push(vertice->esquerdo);
                }

                if (vertice->direito)
                {
                    lista.push(vertice->direito);
                }
            }
        }
        cout << endl;
    }

    void ImprimeTudo()
    {
        No<T> *atual = raiz;
        No<T> *vertice = NULL;
        queue<No<T> *> lista;
        lista.push(raiz);
        if (raiz)
        {
            while (!lista.empty())
            {
                vertice = lista.front();
                cout << "Nó: " << vertice->valor << endl;
                cout << "Pai -> " << (vertice->pai ? vertice->pai->valor : 0)
                     << endl;
                cout << "Filho Esquerdo -> " << (vertice->esquerdo ? vertice->esquerdo->valor : 0)
                     << endl;
                cout << "Filho Direito -> " << (vertice->direito ? vertice->direito->valor : 0)
                     << endl
                     << endl;
                lista.pop();

                if (vertice->esquerdo)
                {
                    lista.push(vertice->esquerdo);
                }

                if (vertice->direito)
                {
                    lista.push(vertice->direito);
                }
            }
        }
        cout << endl;
    }

    void ImprimeBalanceamento()
    {
        ImprimeNoPeso(raiz);
    }
};

int main()
{
    ABBB<int> arvore;
    arvore.Insere(43);
    arvore.Insere(18);
    arvore.Insere(22);
    cout << "Primeiro CASO: ";
    arvore.Imprime();

    arvore.Insere(21);
    arvore.Insere(9);
    arvore.Insere(6);
    cout << "Segundo CASO: ";
    arvore.Imprime();

    arvore.Insere(8);
    cout << "Terceiro CASO: ";
    arvore.Imprime();

    arvore.Insere(20);
    arvore.Insere(63);
    arvore.Insere(50);
    cout << "Quinto CASO: ";
    arvore.Imprime();

    arvore.Insere(62);
    cout << "Sexto CASO: ";
    arvore.Imprime();

    arvore.Insere(51);
    cout << "Sétimo CASO: ";
    arvore.Imprime();

    arvore.ImprimeTudo();

    return 0;
}