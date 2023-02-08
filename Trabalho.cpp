#include <iostream>
#include <fstream>
using namespace std;

void terminal_clear(){
    #if defined _WIN32
        system("cls");
    #elif defined (LINUX)  defined(gnu_linux)  defined(linux)
        system("clear");
    #elif defined (APPLE)
        system("clear");
    #endif
}

void Cadastro(){

}

void Remover_Dado(){

}

void Ordenar_Dados(){

}                 
void Importar_dados_CSV(){

}

void Exportar_dados_CSV(){

}

void Buscar_Registro(){

}

void Imprimir_Arq_Inteiro(){

}

void Imprimir_Trecho_Arq(){

}

string menu(string escolha){
    while ((escolha != "1") && (escolha != "2") && (escolha != "3") && (escolha != "4") && (escolha != "5") && (escolha != "6") && (escolha != "7") && (escolha != "8") && (escolha != "9")){
        cout <<"" << endl << endl << endl;
        cout << "+---------------------------------------+" << endl;
        cout << "|          Menuzinho de cria            |" << endl ;
        cout << "+---------------------------------------+" << endl;
        cout << "| [1] Cadastrar Um Novo Elemento        |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [2] Remover Dado Existente            |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [3] Ordenar Os Dados                  |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [4] Importar dados Para O Formato CSV |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [5] Exportar dados para o formato CSV |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [6] Buscar Um Registro                |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [7] Imprimir O Arquivo Inteiro        |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [8] Imprimir Um Trecho Do Arquivo     |" << endl;
        cout << "|---------------------------------------|" << endl;
        cout << "| [9] Sair                              |" << endl;
        cout << "+---------------------------------------+" << endl;
        cin >> escolha;
        terminal_clear();
        }

return escolha;
}

int main(){
    string escolha;
    while(escolha != "9"){
        escolha = " ";
        escolha = menu(escolha);
        
        if(escolha == "1"){
            Cadastro();
        }

        else if(escolha == "2"){
            Remover_Dado();
        }

        else if(escolha == "3"){
            Ordenar_Dados();
        }

        else if(escolha == "4"){
            Importar_dados_CSV();
        }

        else if(escolha == "5"){
            Exportar_dados_CSV();
        }

        else if(escolha == "6"){
            Buscar_Registro();
        }

        else if(escolha == "7"){
            Imprimir_Arq_Inteiro();
        }

        else if(escolha == "8"){
            Imprimir_Trecho_Arq();
        }

    }
    cout << "Vc saiu! :( ";
    return 0;
}
