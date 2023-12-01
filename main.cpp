#include <iostream>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <cstring>

#define N 500000

using namespace std;

struct Data
{
    char anzsic06[40];
    char Area[40];
    int year;
    int geo_count;
    int ec_count;
};

struct Arquivo
{
    ifstream f;
    int pos, MAX;
    Data *buffer;
};

int compara(const void *a, const void *b)
{

    if (strcmp(((Data *)a)->Area, ((Data *)b)->Area) == 0)
    {
        return ((Data *)a)->geo_count - ((Data *)b)->geo_count;
    }
    else
    {
        return strcmp(((Data *)a)->Area, ((Data *)b)->Area);
    }

    // return ((Data *)a)->geo_count - ((Data *)b)->geo_count;
}

void preencheBuffer(Arquivo *arq, int K)
{
    if (!arq->f.is_open())
    {
        cerr << "Erro ao abrir arquivo." << endl;
    }
    else
    {
        arq->pos = 0;
        arq->MAX = 0;
        arq->f.read(reinterpret_cast<char *>(arq->buffer), sizeof(Data) * K);
        arq->MAX = arq->f.gcount() / sizeof(Data);
    }
}

void salvaArquivo(const string &nome, Data *V, int tam, int mudaLinhaFinal)
{
    ofstream f(nome, ios::app | ios::binary);
    f.write(reinterpret_cast<char *>(V), sizeof(Data) * tam);
    f.close();
}

int procuraMenor(Arquivo *arq, int numArqs, int K, Data &menor)
{
    int i, idx = -1;
    for (i = 0; i < numArqs; i++)
    {
        if (arq[i].pos < arq[i].MAX)
        {
            if (idx == -1)
                idx = i;
            else
            {
                if (compara(&arq[i].buffer[arq[i].pos], &arq[idx].buffer[arq[idx].pos]) < 0)
                    idx = i;
            }
        }
    }

    if (idx != -1)
    {
        menor = arq[idx].buffer[arq[idx].pos];
        arq[idx].pos++;
        if (arq[idx].pos == arq[idx].MAX)
            preencheBuffer(&arq[idx], K);
        return 1;
    }
    else
    {
        return 0;
    }
}

void merge(const string &nome, int numArqs, int K)
{
    string novo;
    int i;
    Data *buffer = new Data[K];

    Arquivo *arq = new Arquivo[numArqs];

    for (i = 0; i < numArqs; i++)
    {
        novo = "Temp" + to_string(i + 1) + ".bin";
        arq[i].f.open(novo, ios::in | ios::binary);
        arq[i].buffer = new Data[K];
        arq[i].pos = 0;
        arq[i].MAX = 0;
        preencheBuffer(&arq[i], K);
    }

    Data menor;
    int qtdBuffer = 0;
    while (procuraMenor(arq, numArqs, K, menor) == 1)
    {
        buffer[qtdBuffer] = menor;
        qtdBuffer++;
        if (qtdBuffer == K)
        {
            salvaArquivo(nome, buffer, K, 1);
            qtdBuffer = 0;
        }
    }

    if (qtdBuffer != 0)
        salvaArquivo(nome, buffer, qtdBuffer, 1);

    for (i = 0; i < numArqs; i++)
        delete[] arq[i].buffer;

    delete[] arq;
    delete[] buffer;
}

int criarArquivosOrdenados(const string &nome)
{
    Data *V = new Data[N];
    int cont = 0, total = 0;
    string novo;
    ifstream f(nome, ios::binary);

    while (f.read(reinterpret_cast<char *>(V + total), sizeof(Data)))
    {
        total++;
        if (total == N)
        {
            cont++;
            novo = "Temp" + to_string(cont) + ".bin";
            qsort(V, total, sizeof(Data), compara);
            salvaArquivo(novo, V, total, 0);
            total = 0;
        }
    }

    if (total > 0)
    {
        cont++;
        novo = "Temp" + to_string(cont) + ".bin";
        qsort(V, total, sizeof(Data), compara);
        salvaArquivo(novo, V, total, 0);
    }

    f.close();
    delete[] V;
    return cont;
}

void mergeSortExterno(const string &nome)
{
    string novo;
    int numArqs = criarArquivosOrdenados(nome);
    int i, k = N / (numArqs + 1);

    remove(nome.c_str());
    merge(nome, numArqs, k);

    for (i = 0; i < numArqs; i++)
    {
        novo = "Temp" + to_string(i + 1) + ".bin";
        remove(novo.c_str());
    }
}

void mostrar()
{
    string nome = "dados.dat";
    ifstream inputFile(nome, std::ios::binary);
    Data d;
    while (inputFile.read(reinterpret_cast<char *>(&d), sizeof(Data)))
    {
        cout << d.anzsic06 << " " << d.Area << " " << d.year << " " << d.geo_count << " " << d.ec_count << endl;
    }
    inputFile.close();
}

int nPessoasCsv()
{
    int numero = 0;
    string verifica;
    ifstream arquivo;
    arquivo.open("original.csv");

    while (getline(arquivo, verifica))
    {
        numero++;
    }

    arquivo.close();
    return numero;
}

int main()
{
    int tamanho = nPessoasCsv();
    ifstream arquivo;
    char pv;
    arquivo.open("original.csv");
    string primeiraLinha;
    getline(arquivo, primeiraLinha);

    ofstream arqBinario("dados.dat", ios::binary);
    for (int i = 0; i < tamanho; i++)
    {

        Data d;
        if (i != 0)
        {
            arquivo.ignore();
        }
        arquivo.getline(d.anzsic06, 40, ',');
        arquivo.getline(d.Area, 40, ',');
        arquivo >> d.year;
        arquivo >> pv;
        arquivo >> d.geo_count;
        arquivo >> pv;
        arquivo >> d.ec_count;
        arquivo.ignore();

        arqBinario.write(reinterpret_cast<const char *>(&d), sizeof(Data));
    }

    arquivo.close();
    arqBinario.close();
    // criarArquivoTeste("dados.bin");
    mergeSortExterno("dados.dat");
    mostrar();
    return 0;
}