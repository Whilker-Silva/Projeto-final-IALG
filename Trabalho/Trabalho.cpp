/*
Alunos:
    Pedro Henrique Pigozzi;
    Victor Hugo Daia Lorenzato
    Whilker Henrique Dos Santos Silva

    Turma 22A

    Professora: Marluce
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <cstring>

/*Biblioteca para uso do sleep no windows ou linux*/
#if defined _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// Criando registro para remédios
struct remedios
{
    float custo, venda;
    long long codigo;
    char fornecedor[80], tarja[50];
    bool status;
};

// Declacaração de funções
void terminal_clear();
int menu(int escolha);
int Importar_dados_CSV();
int Exportar_dados_CSV();
int Cadastrar_Dado();
int Remover_Dado();
int Ordenar_Dados();
int Buscar_Registro();
int Imprimir_Arq_Inteiro();
int Imprimir_Trecho_Arq();
void shell_sort(remedios vet[], int size, string tipo);
void delay(int tempo);
string dado(ifstream &arquivo);

int main()
{

    int selecao = 0;

    while (selecao != 8)
    {
        if (selecao == 0)
        {
            selecao = menu(selecao);
        }

        else if (selecao == 1)
        {
            selecao = Importar_dados_CSV();
        }

        else if (selecao == 2)
        {
            selecao = Exportar_dados_CSV();
        }

        else if (selecao == 3)
        {
            selecao = Cadastrar_Dado();
        }

        else if (selecao == 4)
        {
            selecao = Remover_Dado();
        }

        else if (selecao == 5)
        {
            selecao = Ordenar_Dados();
        }

        else if (selecao == 6)
        {
            selecao = Buscar_Registro();
        }

        else if (selecao == 7)
        {
            selecao = Imprimir_Arq_Inteiro();
        }
    }

    return 0;

} // Fim da main

/*Função para limpar o terminal no windows e linux*/
void terminal_clear()
{
#if defined _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/*Função para daley no windows ou linux*/
void delay(int tempo)
{
#if defined _WIN32
    Sleep(tempo * 1000);
#else
    sleep(tempo);
#endif
}

/*Função menu, mostra as subfunções na qual, o usario
deve informar o que deseja realizar no sistema*/
int menu(int escolha)
{
    if (escolha == 0)
    {

        cout << endl;
        cout << endl;
        cout << endl;
        cout << "   +---------------------------------------+" << endl;
        cout << "   |                MENU                   |" << endl;
        cout << "   +---------------------------------------+" << endl;
        cout << "   | [1] Importar Arquivo CSV              |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [2] Exportar Dados Para CSV           |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [3] Cadastrar Um Novo Elemento        |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [4] Remover Dado Existente            |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [5] Ordenar Dados                     |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [6] Buscar Um Registro                |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [7] Imprimir                          |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [8] Sair                              |" << endl;
        cout << "   +---------------------------------------+" << endl;
        cout << endl;
        cout << endl;
        cout << "   Selecione uma opcao: ";

        // usuario informa opção desejada
        string n;
        cin >> n;

        /*
        Verificando se valor informado é valido
        se for invalido, mostrar mensagem de erro e retornar 0
        se for valido, retornar valor convertido para inteiro
        */
        if (n != "0" and n != "1" and n != "2" and n != "3" and n != "4" and
            n != "5" and n != "6" and n != "7" and n != "8")
        {
            cout << "                        OPCAO INVALIDA!";
            delay(2);

            cout << endl;
            terminal_clear();
            return 0;
        }

        else
        {
            terminal_clear();
            return stoi(n);
        }
    }
}

int Importar_dados_CSV()
{
    string nome_arquvo;
    int n;

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "   Informe o nome do arquivo que deseja importar: ";
    cin >> nome_arquvo;
    cout << "   Informe a quantidade de dados que deseja importar: ";
    cin >> n;

    ifstream arqin(nome_arquvo);

    // verifica se o nome informado é valido
    if (arqin.fail())
    {
        cout << endl;
        cout << "   ARQUIVO NAO ENCONTRADO!" << endl;
        cout << "   VERIFIQUE O NOME DO ARQUIVO QUE DESEJA IMPORTAR!";
        delay(5);
        cout << endl;
        terminal_clear();

        return 0;
    }

    else
    {
        ofstream arqout("BaseDados_binario.dat", ios::binary | ios::ate | ios::app);
        remedios novoremedio[n];

        for (int i = 0; i < n; i++)
        {
            /*
            foi criado uma string auxiliar para cada campo;
            Essa string recebe o dado do arquivo CSV;
            o dado já vem tratado da função dado(arquivo);
            Após receber o dado convertido;
            Por fim salvo no vetor de registo.
            */

            string aux;

            aux = dado(arqin);
            novoremedio[i].custo = stof(aux);

            aux = dado(arqin);
            novoremedio[i].venda = stof(aux);

            aux = dado(arqin);
            strcpy(novoremedio[i].fornecedor, aux.c_str());

            aux = dado(arqin);
            novoremedio[i].codigo = stoll(aux);

            aux = dado(arqin);
            strcpy(novoremedio[i].tarja, aux.c_str());

            novoremedio[i].status = true;
        }

        // reliaza a escrita do vetor de registro no aquivo binario
        arqout.write((const char *)&novoremedio, n * sizeof(remedios));

        arqin.close();
        arqout.close();

        cout << "   ARQUIVO IMPORTADO COM SUCESSO!";
        delay(3);
        cout << endl;
        terminal_clear();

        return 0;
    }
}

/*Função para extrair os dados do arquivo CSV,
1º separa os campos"
1º separa os campos"
2º formata de acordo que seu tipo
3º retorna uma string com o dado já trado*/
string dado(ifstream &arquivo)
{
    string aux;
    char c;

    // Lê caracter e adiciona na variavel c
    arquivo.read(&c, 1);

    // verificar se exeiste dado no campo atual
    // Se o primeiro carater for ';' (valor nulo) retornar caracter 0
    if (c == ';')
    {
        return "0";
    }

    // caso se valor valido
    else
    {
        /*Enquanto c for dirferente de ';' e diferente de quebra de linha
          ler proximo caracter e concatenar na string aux*/
        int tam = 0;
        while (c != ';' and c != '\n')
        {
            aux += c;
            tam++;
            arquivo.read(&c, 1);
        }

        /*verificando se existe virgula
        se houver ',' e substituir por '.'*/
        for (int i = 0; i < tam; i++)
        {
            if (aux[i] == ',')
            {
                aux[i] = '.';
            }
        }

        // retorna a string aux
        return aux;
    }
}

int Exportar_dados_CSV()
{
    // Abre aequivo para leitura
    ifstream arqExport("BaseDados_binario.dat", ios::binary | ios::ate);

    // verifica se o nome informado é valido
    if (arqExport.fail())
    {
        cout << endl;
        cout << "   ARQUIVO BINARIO NAO ENCONTRADO!" << endl;
        cout << "   REALIZAR IMPORTACAO DA BASE DE DADOS!";
        delay(5);
        cout << endl;
        terminal_clear();

        return 0;
    }

    else
    {
        // Verifica qantidade de dados
        long int TamByte = arqExport.tellg();
        int qtdDados = int(TamByte / sizeof(remedios));

        arqExport.seekg(0);

        // copia valores do aquivo binario para  o vetorexport
        remedios vetorExport[qtdDados];
        arqExport.read((char *)&vetorExport, qtdDados * sizeof(remedios));
        arqExport.close();

        // Abre aequivo para escrita
        ofstream arqExpot_csv("Base3_exportada.csv");

        for (int i = 0; i < qtdDados; i++)
        {
            if (vetorExport[i].status == true)
            {
                // excreve no arquino CSV
                arqExpot_csv << vetorExport[i].custo << ";";
                arqExpot_csv << vetorExport[i].venda << ";";
                arqExpot_csv << vetorExport[i].fornecedor << ";";
                arqExpot_csv << vetorExport[i].codigo << ";";
                arqExpot_csv << vetorExport[i].tarja << endl;
            }
        }

        cout << endl;
        cout << endl;
        cout << "   ARQUIVO EXPORTADO COM SUCESSO!";

        delay(3);
        cout << endl;
        terminal_clear();
        return 0;
    }
}

int Cadastrar_Dado()
{
    bool novoCadastro = false;
    bool achoExcluido = false;

    remedios novoremedio;
    string fornecedor, tarja;

    // interação com o usuario afim de guia-lo para realizar o cadastro
    cout << endl;
    cout << endl;
    cout << endl;

    cout << "   Valor de custo: ";
    cin >> novoremedio.custo;

    cout << "   valor de venda: ";
    cin >> novoremedio.venda;

    cout << "   Fornecedor: ";
    cin.ignore();
    getline(cin, fornecedor);
    strcpy(novoremedio.fornecedor, fornecedor.c_str());

    cout << "   Codigo: ";
    cin >> novoremedio.codigo;

    cout << "   Tarja: ";
    cin.ignore();
    getline(cin, tarja);
    strcpy(novoremedio.tarja, tarja.c_str());

    novoremedio.status = true;

    cout << endl;
    cout << endl;
    int pos;

    if (achoExcluido == false)
    {

        fstream arqnew("BaseDados_binario.dat", ios::binary | ios::in | ios::out | ios::ate);
        remedios verificaExcluido;

        long int TamByte = arqnew.tellg();
        int qtdDados = int(TamByte / sizeof(remedios));

        for (int i = 0; i <= qtdDados; i++)
        {
            arqnew.seekg(i * sizeof(remedios));
            arqnew.read((char *)(&verificaExcluido), sizeof(remedios));

            if (verificaExcluido.status == false)
            {
                pos = i * sizeof(remedios);
                achoExcluido = true;
                arqnew.seekp(i * sizeof(remedios));
                arqnew.write((char *)(&novoremedio), sizeof(remedios));
                arqnew.close();
                i = qtdDados + 1;
            }
        }
    }

    if (achoExcluido == false)
    {
        // Escreve o novo dado no final do arquivo binario
        ofstream arqnew("BaseDados_binario.dat", ios::binary | ios::ate | ios::app);
        arqnew.write((const char *)&novoremedio, sizeof(remedios));
        arqnew.close();
    }

    cout << "   Produto cadastrado! " << endl;
    cout << endl;

    // Verifica se usuário deseja realizar mais 1 cadastro
    cout << "   Deseja cadastrar mais algum produto?" << endl;
    cout << "   [0] NAO  [1] SIM" << endl;
    cout << "   ";
    cin >> novoCadastro;

    terminal_clear();
    if (novoCadastro == 1)
    {
        return 3;
    }

    else
    {
        return 0;
    }
}

int Remover_Dado()
{
    fstream arqDeleta("BaseDados_binario.dat", ios::binary | ios::in | ios::out | ios::ate);

    if (arqDeleta.fail())
    {
        cout << endl;
        cout << "   ARQUIVO BINARIO NAO ENCONTRADO!" << endl;
        cout << "   REALIZAR IMPORTACAO DA BASE DE DADOS!";
        delay(5);
        cout << endl;
        terminal_clear();

        return 0;
    }

    else
    {
        long long valorBuscado;
        bool achou = false;
        remedios excluir;

        cout << endl;
        cout << endl;
        cout << endl;
        cout << "   Informe o codigo de barras do remedio que deseja excluir: ";
        cin >> valorBuscado;

        // Verifica qantidade de dados
        long int TamByte = arqDeleta.tellg();
        int qtdDados = (TamByte / sizeof(remedios));

        for (int i = 0; i <= qtdDados; i++)
        {
            arqDeleta.seekg(i * sizeof(remedios));
            arqDeleta.read((char *)(&excluir), sizeof(remedios));

            if (excluir.codigo == valorBuscado and excluir.status != false)
            {

                achou = true;
                excluir.status = false;
                arqDeleta.seekp(i * sizeof(remedios));
                arqDeleta.write((char *)(&excluir), sizeof(remedios));

                i = qtdDados + 1;
            }
        }

        if (achou == true)
        {
            cout << endl;
            cout << "   REGISTRO EXCLUIDO COM SUCESSO!" << endl;
            delay(3);
            cout << endl;
            terminal_clear();
            return 0;
        }

        else
        {
            cout << endl;
            cout << "   REGISTRO NAO ENCONTRADO!" << endl;
            delay(3);
            cout << endl;
            terminal_clear();
            return 0;
        }
    }
}

int Ordenar_Dados()
{
    string n;

    // Abre aequivo para leitura
    ifstream arqOrdem("BaseDados_binario.dat", ios::binary | ios::ate);

    // verifica se o nome informado é valido
    if (arqOrdem.fail())
    {
        cout << endl;
        cout << "   ARQUIVO BINARIO NAO ENCONTRADO!" << endl;
        cout << "   REALIZAR IMPORTACAO DA BASE DE DADOS!";
        delay(5);
        cout << endl;
        terminal_clear();

        return 0;
    }

    else
    {
        // lista de opções de campos para ordenação
        cout << endl;
        cout << endl;
        cout << endl;
        cout << "   +---------------------------------------+" << endl;
        cout << "   |              ORDENACAO                |" << endl;
        cout << "   +---------------------------------------+" << endl;
        cout << "   | [1] Valor de custo                    |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [2] Valor de venda                    |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [3] Fornecedor                        |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [4] Codigo De Barras                  |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [5] Tarja                             |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [6] Cancelar Ordenacao                |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << endl;
        cout << endl;
        cout << "   Informe por qual campo deseja ordenar: ";
        cin >> n;

        // Verifica qantidade de dados
        long int TamByte = arqOrdem.tellg();
        int qtdDados = int(TamByte / sizeof(remedios));

        arqOrdem.seekg(0);

        // Verifica se opção escolhida pelo usuario é valida
        if (n == "1" or n == "2" or n == "3" or n == "4" or n == "5")
        {

            // copia valores do aquivo binario para  o vetorOrdena
            remedios vetorOrdena[qtdDados];
            arqOrdem.read((char *)&vetorOrdena, qtdDados * sizeof(remedios));
            arqOrdem.close();

            // Realizada a ordenação de acordo com campo escolhido
            shell_sort(vetorOrdena, qtdDados, n);

            // escreve vetor ordenado no aquivo binario
            ofstream arqOrdenado("BaseDados_binario.dat", ios::binary);
            arqOrdenado.write((char *)&vetorOrdena, qtdDados * sizeof(remedios));
            arqOrdenado.close();

            cout << "   ARQUIVO ORDENADO COM SUCESSO!";
            delay(3);
            cout << endl;
            terminal_clear();
            return 0;
        }

        else if (n == "6")
        {
            terminal_clear();
            return 0;
        }

        else
        {
            cout << "                             OPCAO INVALIDA!";
            delay(2);
            cout << endl;
            terminal_clear();
            return 5;
        }
    }
}

// Função para realizar a ordenação do vetor utilizando o algoritmo shell sort
void shell_sort(remedios vet[], int size, string tipo)
{
    int gaps[9] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
    int pos_gap = 8;
    while (gaps[pos_gap] > size)
    {
        pos_gap--;
    }

    remedios value[1];

    int j;
    while (pos_gap >= 0)
    {
        int gap = gaps[pos_gap];

        for (int i = gap; i < size; i++)
        {
            value[0] = vet[i];
            j = i;

            // Ordenação pelo campo custo
            if (tipo == "1")
            {
                while ((j >= gap) and (value[0].custo < vet[j - gap].custo))
                {
                    vet[j] = vet[j - gap];
                    j = j - gap;
                }
                vet[j] = value[0];
            }

            // Ordenação pelo campo venda
            else if (tipo == "2")
            {
                while ((j >= gap) and (value[0].venda < vet[j - gap].venda))
                {
                    vet[j] = vet[j - gap];
                    j = j - gap;
                }
                vet[j] = value[0];
            }

            // Ordenação pelo campo fornecedor
            else if (tipo == "3")
            {
                while ((j >= gap) and strcmp(value[0].fornecedor, vet[j - gap].fornecedor) < 0)
                {
                    vet[j] = vet[j - gap];
                    j = j - gap;
                }
                vet[j] = value[0];
            }

            // Ordenação pelo campo codigo de barras
            else if (tipo == "4")
            {
                while ((j >= gap) and (value[0].codigo < vet[j - gap].codigo))
                {
                    vet[j] = vet[j - gap];
                    j = j - gap;
                }
                vet[j] = value[0];
            }

            // Ordenação pelo campo tarja
            else if (tipo == "5")
            {
                while ((j >= gap) and strcmp(value[0].tarja, vet[j - gap].tarja) < 0)
                {
                    vet[j] = vet[j - gap];
                    j = j - gap;
                }
                vet[j] = value[0];
            }
        }

        pos_gap--;
    }
}

int Buscar_Registro()
{
}

int Imprimir_Arq_Inteiro()
{
    // Abre aequivo para leitura
    ifstream arqExport("BaseDados_binario.dat", ios::binary | ios::ate);

    // verifica se o nome informado é valido
    if (arqExport.fail())
    {
        cout << endl;
        cout << "   ARQUIVO BINARIO NAO ENCONTRADO!" << endl;
        cout << "   REALIZAR IMPORTACAO DA BASE DE DADOS!";
        delay(5);
        cout << endl;
        terminal_clear();

        return 0;
    }

    else
    {
        // Verifica qantidade de dados
        long int TamByte = arqExport.tellg();
        int qtdDados = int(TamByte / sizeof(remedios));

        arqExport.seekg(0);

        // copia valores do aquivo binario para  o vetorexport
        remedios vetorExport[qtdDados];
        arqExport.read((char *)&vetorExport, qtdDados * sizeof(remedios));
        arqExport.close();

        for (int i = 0; i < qtdDados; i++)
        {
            // if (vetorExport[i].status == true)
            // {
            // excreve no arquino CSV
            cout << i + 1 << ": ";
            cout << vetorExport[i].custo << ";";
            cout << vetorExport[i].venda << ";";
            cout << vetorExport[i].fornecedor << ";";
            cout << vetorExport[i].codigo << ";";
            cout << vetorExport[i].tarja << " | ";
            cout << vetorExport[i].status << endl;
            // }
        }

        int saifuncao = 0;
        while (saifuncao == 0)
        {
            cin >> saifuncao;
        }
        cout << endl;
        terminal_clear();
        return 0;
    }
}

int Imprimir_Trecho_Arq()
{
}
