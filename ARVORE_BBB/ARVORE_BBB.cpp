#include <iostream>

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
    friend ostream &operator<<(ostream &saida, const No &noCopia)
    {
        saida << noCopia.valor << endl;
        return saida;
    }

    friend class ABB<T>;
};

template <typename T>
class ABB
{
private:
    No<T> *raiz;
    int inseridos;
};

int main()
{
    return 0;
}