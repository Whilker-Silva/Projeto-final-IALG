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
#include <unistd.h>

using namespace std;

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
string dado(ifstream &arquivo);
void orderna(int a[], int inicio, int fim);

// Criando registro para remédios
struct remedios
{
    float custo, venda;
    long long codigo;
    char fornecedor[80], tarja[50];
};

/*
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
*/

int main()
{

    int selecao = 0;

    while (selecao != 9)
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

        else if (selecao == 9)
        {
            selecao = Imprimir_Trecho_Arq();
        }
    }

    return 0;

} // Fim da main

/*
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
############################################################################################
*/

/*Função para limpar o terminal no windows e linux*/
void terminal_clear()
{
#if defined _WIN32
    system("cls");
#else
    system("clear");
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
        cout << "   | [7] Imprimir O Arquivo Inteiro        |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [8] Imprimir Um Trecho Do Arquivo     |" << endl;
        cout << "   |---------------------------------------|" << endl;
        cout << "   | [9] Sair                              |" << endl;
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
            n != "5" and n != "6" and n != "7" and n != "8" and n != "9")
        {
            cout << "                        OPCAO INVALIDA!";
            sleep(2);

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
    ofstream arqout("BaseDados_binario.dat", ios::binary | ios::ate | ios::app);
    remedios novoremedio[n];

    for (int i = 0; i < n; i++)
    {
        /*
        foi criado uma string auxiliar para cada paramentro;
        Essa string recebe o dado do arquivo CSV;
        o dado já vem tratado da função dado(arquivo);
        Após receber o dado convertido;
        Por fim salvo no vetor de registo.
        */

        string custo = dado(arqin);
        novoremedio[i].custo = stof(custo);

        string venda = dado(arqin);
        novoremedio[i].venda = stof(venda);

        string fornecedor = dado(arqin);
        strcpy(novoremedio[i].fornecedor, fornecedor.c_str());

        string codigo = dado(arqin);
        novoremedio[i].codigo = stoll(codigo);

        string tarja = dado(arqin);
        strcpy(novoremedio[i].tarja, tarja.c_str());
    }

    // reliaza a escrita do vetor de registro no aquivo binario
    arqout.write((const char *)&novoremedio, n * sizeof(remedios));

    arqin.close();
    arqout.close();

    cout << "   ARQUIVO IMPORTADO COM SUCESSO!";
    sleep(3);
    terminal_clear();

    return 0;
}

/*Função para extrair os dados do arquivo CSV,
separando as "céculas"
formatando de acordo que seu tipo
retornando uma string com o dado trado*/
string dado(ifstream &arquivo)
{
    string aux;
    char c;

    // Lê caracter e adiciona na variavel c
    arquivo.read(&c, 1);

    // verificar se exeiste dado no campo atual
    // Se o primeiro carater for ';' retornar caracter 0
    if (c == ';')
    {
        return "0";
    }

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
}

int Cadastrar_Dado()
{
    bool novoCadastro = 0;

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
    cout << "   Fabrincate: ";
    cin.ignore();
    getline(cin, fornecedor);
    strcpy(novoremedio.fornecedor, fornecedor.c_str());
    cout << "   Codigo: ";
    cin >> novoremedio.codigo;
    cout << "   Tarja: ";
    cin.ignore();
    getline(cin, tarja);
    strcpy(novoremedio.tarja, tarja.c_str());
    cout << endl;
    cout << endl;

    // Escreve o novo dado no arquivo binario
    ofstream arqnew("BaseDados_binario.dat", ios::binary | ios::ate | ios::app);
    arqnew.write((const char *)&novoremedio, 1 * sizeof(remedios));
    arqnew.close();

    cout << "   Produto cadastrado! " << endl;
    cout << endl;

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
}

int Ordenar_Dados()
{
    string n;
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
    cout << "   | [4] Codigo de barras                  |" << endl;
    cout << "   |---------------------------------------|" << endl;
    cout << "   | [5] Tarja                             |" << endl;
    cout << "   |---------------------------------------|" << endl;
    cout << "   | [6] Cancelar Ordenacao                |" << endl;
    cout << "   |---------------------------------------|" << endl;
    cout << endl;
    cout << endl;
    cout << "   Informe por qual campo deseja ordenar: ";
    cin >> n;

    // Abre aequivo para leitura
    ifstream arqOrdem("BaseDados_binario.dat", ios::binary | ios::ate);

    // Verifica qantidade de dados
    long int TamByte = arqOrdem.tellg();
    int qtdDados = int(TamByte / sizeof(remedios));
    cout << qtdDados << endl;
    arqOrdem.seekg(0);

    // Passa valores do aquivo binario para  o vetorOrdena
    remedios vetorOrdena[qtdDados];
    arqOrdem.read((char *)&vetorOrdena, qtdDados * sizeof(remedios));

    for (int i = 0; i < qtdDados; i++)
    {
        cout << vetorOrdena[i].custo << " ";
        cout << vetorOrdena[i].venda << " ";
        cout << vetorOrdena[i].fornecedor << " ";
        cout << vetorOrdena[i].codigo << " ";
        cout << vetorOrdena[i].tarja << endl;
    }

    if (n == "1")
    {
    }

    else if (n == "2")
    {
    }

    else if (n == "3")
    {
    }

    else if (n == "4")
    {
    }

    else if (n == "5")
    {
    }

    else
    {
        cout << "                             OPCAO INVALIDA!";
        sleep(2);

        terminal_clear();
        return 5;
    }
}

void LeituraBinario(remedios vetorOrdena[])
{
}

void orderna(int a[], int inicio, int fim)
{
    int meio;
    if (inicio < fim)
    {
        meio = (inicio + fim) / 2;
        orderna(a, inicio, meio);
        orderna(a, meio + 1, fim);
        // intercala(a, inicio, meio, fim);
    }
}

int Buscar_Registro()
{
}

int Imprimir_Arq_Inteiro()
{
}

int Imprimir_Trecho_Arq()
{
}
