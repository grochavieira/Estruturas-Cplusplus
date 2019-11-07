#include <iostream>

using namespace std;

template <typename T>
class LES;

template <typename T>
ostream &operator<<(ostream &saida, const LES<T> &lesCopia);

template <typename T>
class LES
{
private:
    T *v;
    int tamanho = 0;
    int inseridos = 0;
    T sentinela;

    void copia(const LES &lesCopia)
    {
        tamanho = lesCopia.tamanho;
        v = new T[tamanho];
        for (int i = 0; i < lesCopia.inseridos; i++)
        {
            cout << "Valor de v[" << i << "] : " << lesCopia.v[i] << endl;
            Insere(lesCopia.v[i]);
        }
    }

public:
    LES(int tamanho)
    {
        this->tamanho = tamanho;
        v = new T[tamanho];
    }

    LES(const LES &lesCopia)
    {
        copia(lesCopia);
    }

    bool Insere(T valor)
    {
        // Verifica se tem espaço para inserir
        if (inseridos == tamanho)
        {
            return false;
        }

        int i = 0;
        // Busca o primeiro maior valor para inserir no lugar dele
        for (i = 0; i < inseridos && valor > v[i]; i++)
        {
        }

        // Desloca o vetor para poder inserir o novo valor
        for (int j = inseridos; j > i; j--)
        {
            v[j] = v[j - 1];
        }

        // Insere o novo valor
        v[i] = valor;

        inseridos++;
        return true;
    }

    bool Remove(T valor)
    {
        int index = Busca(valor);

        if (index == -1)
        {
            return false;
        }

        for (int i = index; i < inseridos; i++)
        {
            v[i] = v[i + 1];
        }

        inseridos--;
        return true;
    }

    int Busca(T valor)
    {
        if (inseridos == 0)
        {
            return -1;
        }
        int inicio = 0;
        int fim = inseridos - 1;
        int media = 0;

        while (inicio <= fim)
        {
            media = (fim + inicio) / 2;
            if (valor == v[media])
            {
                return media;
            }
            else if (valor > v[media])
            {
                inicio = media + 1;
            }
            else
            {
                fim = media - 1;
            }
        }

        return -1;
    }

    void Imprime()
    {
        for (int i = 0; i < inseridos; i++)
        {
            cout << v[i] << ((i + 1) != inseridos ? " | " : "\n");
        }
    }

    const T &operator[](int index)
    {
        if (!(index >= 0 && index < inseridos))
        {
            return sentinela;
        }
        else
        {
            return v[index];
        }
    }

    const &operator=(const LES &lesCopia)
    {
        delete[] v;
        inseridos = 0;
        copia(lesCopia);
    }

    friend ostream &operator<<<T>(ostream &saida, const LES &lesCopia);

    ~LES()
    {
        delete[] v;
    }
};
template <typename T>
ostream &operator<<(ostream &saida, const LES<T> &lesCopia)
{
    for (int i = 0; i < lesCopia.inseridos; i++)
    {
        saida << "[" << i << "] ==> " << lesCopia.v[i] << endl;
    }

    return saida;
}

int main()
{
    LES<int> lesInteira(7);

    lesInteira.Insere(4);
    lesInteira.Insere(7);
    lesInteira.Insere(10);
    lesInteira.Insere(14);
    lesInteira.Insere(15);
    lesInteira.Insere(16);
    lesInteira.Imprime();

    lesInteira.Insere(12);
    lesInteira.Imprime();

    LES<string> lesString(5);

    lesString.Insere("b");
    lesString.Insere("c");
    lesString.Insere("a");
    lesString.Insere("g");
    lesString.Insere("e");
    lesString.Insere("z");
    lesString.Imprime();

    cout << lesInteira.Busca(4) << endl;
    cout << lesInteira.Busca(7) << endl;
    cout << lesInteira.Busca(10) << endl;
    cout << lesInteira.Busca(12) << endl;
    cout << lesInteira.Busca(14) << endl;
    cout << lesInteira.Busca(15) << endl;
    cout << lesInteira.Busca(16) << endl;

    cout << lesString.Busca("a") << endl;

    /*
    lesInteira.Remove(4);
    lesInteira.Imprime();
    lesInteira.Remove(7);
    lesInteira.Imprime();
    lesInteira.Remove(10);
    lesInteira.Imprime();
    lesInteira.Remove(12);
    lesInteira.Imprime();
    lesInteira.Remove(14);
    lesInteira.Imprime();
    lesInteira.Remove(15);
    lesInteira.Imprime();
    lesInteira.Remove(16);
    lesInteira.Imprime();
*/
    int l = lesInteira[10];
    int x = lesInteira[2];

    cout << "Valor de l => " << l << endl;
    cout << "Valor de x => " << x << endl;

    LES<int> lesInteira2(10);

    lesInteira2.Insere(23);
    lesInteira2.Insere(73);
    lesInteira2.Insere(103);
    lesInteira2.Insere(143);
    lesInteira2.Insere(153);
    lesInteira2.Insere(163);
    lesInteira2.Imprime();

    lesInteira2 = lesInteira;
    lesInteira2.Imprime();

    LES<int> lesInteira3(lesInteira);
    lesInteira3.Imprime();

    cout << lesInteira3;

    return 0;
}