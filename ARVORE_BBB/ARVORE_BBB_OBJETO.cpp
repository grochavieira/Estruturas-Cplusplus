#include <iostream>

using namespace std;

template <class T, bool (*C)(const T &, const T &)>
class ABBB;

class Pessoa
{
private:
    string nome;
    int idade;

public:
    Pessoa()
    {
        nome = "";
        idade = 0;
    }

    Pessoa(string nome, int idade)
    {
        this->nome = nome;
        this->idade = idade;
    }

    void Imprime()
    {
        cout << "Nome : " << nome << " Idade: " << idade << endl;
    }

    bool Compara(const Pessoa &pessoa)
    {
        if (pessoa.nome == nome && pessoa.idade == idade)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    friend bool maiorNome(const Pessoa &pessoa1, const Pessoa &pessoa2);
    friend bool maiorIdade(const Pessoa &pessoa1, const Pessoa &pessoa2);
};

bool maiorNome(const Pessoa &pessoa1, const Pessoa &pessoa2)
{
    return (pessoa1.nome > pessoa2.nome);
}

bool maiorIdade(const Pessoa &pessoa1, const Pessoa &pessoa2)
{
    return (pessoa1.idade > pessoa2.idade);
}

template <class T, bool (*C)(const T &, const T &)>
class No
{
private:
    No<T, C> *pai;
    No<T, C> *esquerdo;
    No<T, C> *direito;
    T objeto;

public:
    friend class ABBB<T, C>;
};

template <class T, bool (*C)(const T &, const T &)>
class ABBB
{
private:
    No<T, C> *raiz;
    int inseridos;

    No<T, C> *Sucessor(No<T, C> *no)
    {
        if (no->direito)
            no = no->direito;

        while (no && no->esquerdo)
        {
            no = no->esquerdo;
        }

        return no;
    }

    void ImprimeCrescente(No<T, C> *no)
    {
        if (no->esquerdo)
        {
            ImprimeCrescente(no->esquerdo);
        }
        no->objeto.Imprime();
        if (no->direito)
        {
            ImprimeCrescente(no->direito);
        }
    }

public:
    ABBB()
    {
        raiz = NULL;
        inseridos = 0;
    }

    bool Insere(T objeto)
    {
        No<T, C> *novo = new No<T, C>;
        novo->objeto = objeto;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->pai = NULL;

        No<T, C> *atual = raiz;
        No<T, C> *anterior = NULL;

        while (atual)
        {
            anterior = atual;
            if (C(atual->objeto, objeto))
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
            if (C(anterior->objeto, objeto))
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
        inseridos++;
        return true;
    }

    bool Remove(T objeto)
    {
        No<T, C> *atual = Busca(objeto);

        if (!atual || inseridos == 0)
            return false;

        int filhos = (atual->esquerdo != NULL) + (atual->direito != NULL);

        if (filhos == 0)
        {
            No<T, C> *pai = atual->pai;
            if (pai)
            {
                if (pai->esquerdo && pai->esquerdo->objeto.Compara(objeto))
                {
                    pai->esquerdo = NULL;
                }
                else
                {
                    pai->direito = NULL;
                }
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
            No<T, C> *pai = atual->pai;
            No<T, C> *filho = atual->esquerdo;
            if (!filho)
                filho = atual->direito;

            filho->pai = pai;
            if (pai)
            {
                if (C(pai->objeto, objeto))
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

            delete atual;
            inseridos--;
        }
        else
        {
            T sucessor = Sucessor(atual)->objeto;
            Remove(sucessor);
            atual->objeto = sucessor;
        }

        return true;
    }

    No<T, C> *Busca(T objeto)
    {
        No<T, C> *atual = raiz;

        while (atual && !(atual->objeto.Compara(objeto)))
        {
            if (atual->esquerdo && C(atual->objeto, objeto))
            {
                atual = atual->esquerdo;
            }
            else
            {
                atual = atual->direito;
            }
        }
        if (atual)
            return atual;
        else
            return NULL;
    }

    void Imprime()
    {
        if (raiz)
            ImprimeCrescente(raiz);
        else
            cout << endl;
    }
};

int main()
{
    ABBB<Pessoa, maiorIdade> arvore;
    Pessoa p1("h", 19);
    Pessoa p2("a", 23);
    Pessoa p3("z", 11);
    Pessoa p4("A", 25);
    Pessoa p5("C", 1);
    Pessoa p6("y", 99);
    Pessoa p7("B", 3);
    Pessoa p8("x", 2);

    arvore.Insere(p1);
    arvore.Insere(p2);
    arvore.Insere(p3);
    arvore.Insere(p4);
    arvore.Insere(p5);
    arvore.Insere(p6);
    arvore.Insere(p7);
    arvore.Insere(p8);
    arvore.Imprime();
    cout << endl;
    arvore.Remove(p1);

    arvore.Imprime();
    return 0;
}