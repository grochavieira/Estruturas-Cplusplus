#include <iostream>

using namespace std;

template <typename T, bool (*C)(const T &, const T &)>
class LDDE;

template <typename T, bool (*C)(const T &, const T &)>
ostream &operator<<(ostream &saida, const LDDE<T, C> &lddeCopia);

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
        cout << "Nome: " << nome << " Idade: " << idade << endl;
    }

    string getNome()
    {
        return nome;
    }

    int getIdade()
    {
        return idade;
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

    friend ostream &operator<<(ostream &saida, const Pessoa &pessoa);
    friend bool maiorNome(const Pessoa &pessoa1, const Pessoa &pessoa2);
    friend bool maiorIdade(const Pessoa &pessoa1, const Pessoa &pessoa2);
};

ostream &operator<<(ostream &saida, const Pessoa &pessoa)
{
    saida << "Nome==> " << pessoa.nome << " Idade--> " << pessoa.idade;
    return saida;
}

bool maiorNome(const Pessoa &pessoa1, const Pessoa &pessoa2)
{
    return pessoa1.nome > pessoa2.nome;
}

bool maiorIdade(const Pessoa &pessoa1, const Pessoa &pessoa2)
{
    return pessoa1.idade > pessoa2.idade;
}

template <typename T, bool (*C)(const T &, const T &)>
class No
{
private:
    T objeto;
    No<T, C> *proximo;
    No<T, C> *anterior;

public:
    friend ostream &operator<<(ostream &saida, const No &noCopia)
    {
        saida << noCopia.objeto << endl;
        return saida;
    }

    friend ostream &operator<<<T, C>(ostream &saida, const LDDE<T, C> &lddeCopia);
    friend class LDDE<T, C>;
};

template <typename T, bool (*C)(const T &, const T &)>
class LDDE
{
private:
    No<T, C> *primeiro;
    No<T, C> *ultimo;
    T sentinela;
    int inseridos;

    void copia(const LDDE &lddeCopia)
    {
        while (Remove(0))
        {
        }

        No<T, C> *atual = lddeCopia.primeiro;
        while (atual)
        {
            Insere(atual->objeto);
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

    const &operator=(const LDDE &lddeCopia)
    {
        copia(lddeCopia);
    }

    LDDE(const LDDE &lddeCopia)
    {
        primeiro = NULL;
        ultimo = NULL;
        inseridos = 0;
        copia(lddeCopia);
    }

    ~LDDE()
    {
        while (Remove(0))
        {
        }
    }

    bool Insere(T objeto)
    {
        No<T, C> *novo = new No<T, C>;
        novo->objeto = objeto;
        novo->proximo = NULL;
        novo->anterior = NULL;

        No<T, C> *atual = primeiro;
        No<T, C> *anterior = NULL;

        while (atual && C(objeto, atual->objeto))
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

        if (!atual)
        {
            ultimo = novo;
        }
        else
        {
            atual->anterior = novo;
        }
        novo->proximo = atual;
        novo->anterior = anterior;
        inseridos++;
        return true;
    }

    No<T, C> *Busca(T objeto)
    {
        No<T, C> *atual = primeiro;

        while (atual && !atual->objeto.Compara(objeto))
        {
            atual = atual->proximo;
        }

        if (atual)
            return atual;
        else
            return NULL;
    }

    bool Remove(T objeto)
    {
        No<T, C> *atual = Busca(objeto);
        if (!atual && inseridos == 0)
        {
            return false;
        }

        if (!atual->anterior)
        {
            primeiro = atual->proximo;
        }
        else
        {
            atual->anterior->proximo = atual->proximo;
        }

        if (!atual->proximo)
        {
            ultimo = atual->anterior;
        }
        else
        {
            atual->proximo->anterior = atual->anterior;
        }

        delete atual;
        inseridos--;
        return true;
    }

    bool Remove(int index)
    {
        if (index < 0 || index >= inseridos)
        {
            return false;
        }

        No<T, C> *atual = primeiro;
        int i = 0;

        while (atual && index != i)
        {
            atual = atual->proximo;
            i++;
        }

        if (!atual->anterior)
        {
            primeiro = atual->proximo;
        }
        else
        {
            atual->anterior->proximo = atual->proximo;
        }

        if (!atual->proximo)
        {
            ultimo = atual->anterior;
        }
        else
        {
            atual->proximo->anterior = atual->anterior;
        }

        delete atual;
        inseridos--;
        return true;
    }

    void Imprime()
    {
        No<T, C> *atual = primeiro;
        while (atual)
        {
            atual->objeto.Imprime();
            atual = atual->proximo;
        }
        cout << endl;
    }

    friend ostream &operator<<<T, C>(ostream &saida, const LDDE<T, C> &lddeCopia);
};

template <typename T, bool (*C)(const T &, const T &)>
ostream &operator<<(ostream &saida, const LDDE<T, C> &lddeCopia)
{
    No<T, C> *atual = lddeCopia.primeiro;

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
    LDDE<Pessoa, maiorIdade> ldde;
    Pessoa p1("z", 99);
    Pessoa p2("c", 50);
    Pessoa p3("d", 40);
    Pessoa p4("a", 22);
    Pessoa p5("k", 1);

    ldde.Insere(p1);
    ldde.Insere(p2);
    ldde.Insere(p3);
    ldde.Insere(p4);
    ldde.Insere(p5);
    ldde.Imprime();

    ldde.Remove(p5);
    ldde.Imprime();

    ldde.Remove(0);
    ldde.Imprime();

    LDDE<Pessoa, maiorIdade> ldde2(ldde);

    cout << "LDDE 2: " << endl;
    ldde2.Imprime();
    ldde2.Insere(p1);
    ldde2.Insere(p2);
    ldde2.Imprime();

    LDDE<Pessoa, maiorIdade> ldde3;

    ldde3 = ldde2;

    cout << "LDDE 3: " << endl;
    ldde3.Imprime();

    cout << "COUTS: " << endl;
    cout << ldde;
    return 0;
}