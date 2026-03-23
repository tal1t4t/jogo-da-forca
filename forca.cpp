#include <cstdlib>
#include <ctime>   // pra setar a semente de números aleatórios
#include <fstream> //para mexer com arquivos
#include <iostream>
#include <map> // para criar dicionários
#include <ostream>
#include <string>
#include <vector> // para criar vetores dinâmicos do código

using namespace std;

string palavra_secreta;

int numero_categoria;

map<char, bool> chutou;
/*
é assim que se cria um DICIONÁRIO em C++. primeiro, definimos o tipo da
CHAVE(termo que usamos para fazer a consulta). depois, definimos o tipo do
RETORNO. é a lógica de uma função: a gente dá um x e recebe um y aqui o mapa
inicia vazio. durante o primeiro for, ele vai buscando a chave(letra)
selecionada. primeiro, ele verifica se a chave existe no dicionário. caso não,
define o retorno como FALSE. é assim que a palavra secreta fica registrada no
dicionário.

depois que o usuário começa os chutes, as letras da palavra mudam o valor de
retorno para TRUE caso o chute seja certo.
*/

vector<char> chutes_errados;
/*criando um vetor dinâmico*/

void limpa_tela() { system("clear"); }

bool letra_existe(char chute) {
    // for (int i = 0; i < palavra_secreta.size(); i++) { // a função .size()
    // retorna o tamanho da string
    for (char letra : palavra_secreta) { // outra forma de percorrer uma string
                                         // caractere por caractere
        if (chute == letra) {
            return true;
        }
    }
    return false; // o programa só chega aqui se passar pela palavra toda e não
                  // achar a letra
}

bool nao_acertou() {
    for (char letra : palavra_secreta) {
        if (!chutou[letra]) {
            return true;
        }
    }
    return false;
}

bool nao_enforcou() {
    return chutes_errados.size() < 5; // verifica se 5 letras já foram chutadas
}

void mostra_cabecalho() {
    limpa_tela();

    cout << "*********************" << endl;
    cout << "*   JOGO DA FORCA   *" << endl;
    cout << "*********************" << endl << endl;
}

void imprime_erros() {
    cout << "Chutes errados: ";
    for (char letra : chutes_errados) {
        cout << letra << " ";
    }
    cout << endl;
}

void imprime_palavra() {
    for (char letra : palavra_secreta) {
        if (chutou[letra]) {
            cout << letra << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl << endl;
}

void chuta() {
    cout << "Digite seu chute: ";
    char chute;
    cin >> chute;
    chutou[chute] = true;

    limpa_tela();

    if (letra_existe(chute)) {
        cout << "Acertou o chute!" << endl;
    } else {
        cout << "Errou!" << endl;
        chutes_errados.push_back(
            chute); // acrescenta a letra errada no final do vetor
    }
    cout << endl;
}

vector<string> le_arquivo() {
    ifstream arquivo; // é necessário criar uma variável desse tipo para
                      // ler arquivos

    switch (numero_categoria) {
    case 1:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/frutas.txt");
        break;
    case 2:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/nomes.txt");
        break;
    case 3:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/paises.txt");
        break;
    case 4:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/pdc.txt");
        break;
    case 5:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/animais.txt");
        break;
    }

    if (arquivo.is_open()) {

        int quant_palavras;
        arquivo >> quant_palavras;
        // pega a primeira linha do arquivo, que contém um número inteiro. é
        // tipo um cin

        vector<string> palavras_do_arquivo;

        for (int i = 0; i < quant_palavras; i++) {
            string palavra_lida;
            arquivo >> palavra_lida;
            palavras_do_arquivo.push_back(palavra_lida);
        }

        arquivo.close(); // fecha o arquivo aberto atualmente(no caso, o
                         // palavras.txt)

        return palavras_do_arquivo;
    } else {
        cout << "Não foi possível acessar o banco de palavras.";
        exit(0); // para a execução na hora se der erro pra abrir arquivo
    }
}

void salva_arquivo(vector<string> nova_lista) {
    ofstream arquivo; // esse tipo de variável é capaz de escrever em arquivos
    switch (numero_categoria) {
    case 1:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/frutas.txt");
        break;
    case 2:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/nomes.txt");
        break;
    case 3:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/paises.txt");
        break;
    case 4:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/pdc.txt");
        break;
    case 5:
        arquivo.open("/home/talita/UERJ/3 PERIODO/ED2/jogo_forca/animais.txt");
        break;
    }

    if (arquivo.is_open()) { // retorna true se o arquivo for aberto com sucesso
        arquivo << nova_lista.size() << endl;
        // sobrescreve o tamanho novo na primeira linha do arquivo. mesma lógica
        // do cout

        for (string palavra : nova_lista) {
            arquivo << palavra << endl; // escrevendo a nova lista
        }

        arquivo.close();
    } else {
        cout << "Não foi possível acessar o banco de palavras.";
        exit(0); // para a execução na hora se der erro pra abrir arquivo
    }
}

void adiciona_palavra() {
    cout << "Digite a nova palavra, usando letras MAIÚSCULAS: ";
    string nova_palavra;
    cin >> nova_palavra;

    vector<string> lista_palavras = le_arquivo();
    lista_palavras.push_back(nova_palavra);

    salva_arquivo(lista_palavras);
}

void fim_de_jogo() {
    cout << "Fim de jogo!" << endl;
    cout << "A palavra secreta era " << palavra_secreta << endl;
    if (nao_acertou()) {
        cout << "Você perdeu! Tente Novamente." << endl << endl;
    } else {
        cout << "Parabéns! Você acertou a palavra secreta." << endl << endl;
        cout << "Deseja adicionar uma nova palavra ao banco? (S/N): ";
        char resposta;
        bool resp_valida;

        do {
            cin >> resposta;
            if (resposta == 'S') {
                resp_valida = true;
                adiciona_palavra();
            } else if (resposta == 'N') {
                resp_valida = true;
            } else {
                resp_valida = false;
                cout << "Resposta inválida." << endl;
                cout << "Deseja adicionar uma nova palavra ao banco? (S/N): ";
            }
        } while (!resp_valida);
    }

    cout << "Obrigada por jogar!" << endl << endl;
}

void sorteia_palavra() {
    vector<string> palavras = le_arquivo();

    srand(time(NULL));

    int indice_sorteado = rand() % palavras.size();

    palavra_secreta = palavras[indice_sorteado];
}

void escolhe_categoria() {
    cout << "Escolha uma categoria de palavras: " << endl
         << endl
         << "[1] Frutas" << endl
         << "[2] Nomes próprios" << endl
         << "[3] Países" << endl
         << "[4] Partes do corpo humano" << endl
         << "[5] Animais" << endl
         << endl
         << "Sua escolha: ";

    bool numero_valido;
    do {
        cin >> numero_categoria;
        switch (numero_categoria) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            numero_valido = true;
            break;
        default:
            numero_valido = false;
            cout << "Insira um número válido: ";
            break;
        }
    } while (!numero_valido);
}

void imprime_categoria() {
    cout << "Categoria: ";
    switch (numero_categoria) {
    case 1:
        cout << "Frutas";
        break;
    case 2:
        cout << "Nomes próprios";
        break;
    case 3:
        cout << "Países";
        break;
    case 4:
        cout << "Partes do corpo humano";
        break;
    case 5:
        cout << "Animais";
    }
    cout << endl;
}

int main() {
    mostra_cabecalho();
    escolhe_categoria();
    le_arquivo();
    sorteia_palavra();

    while (nao_acertou() && nao_enforcou()) {

        imprime_erros();

        imprime_palavra();

        imprime_categoria();

        chuta();
    }
    fim_de_jogo();
}