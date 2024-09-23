#include <opencv2/opencv.hpp>
#include <iostream>
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;

// Função para quebrar o texto em linhas com base na largura da caixa
vector<string> quebraTextoAutomatico(const string& texto, int largura_max, int fontFace, double fontScale, int thickness) {
    vector<string> linhas;
    string linha_atual;
    istringstream iss(texto);
    string palavra;

    while (iss >> palavra) {
        string temp_linha = linha_atual + (linha_atual.empty() ? "" : " ") + palavra;

        // Verifica o tamanho da linha
        int baseline = 0;
        Size tamanho_linha = getTextSize(temp_linha, fontFace, fontScale, thickness, &baseline);

        if (tamanho_linha.width > largura_max) {
            // Se a linha for maior que a largura permitida, adiciona a linha anterior e começa uma nova
            linhas.push_back(linha_atual);
            linha_atual = palavra;
        } else {
            // Caso contrário, continua adicionando à linha atual
            linha_atual = temp_linha;
        }
    }

    // Adiciona a última linha, se existir
    if (!linha_atual.empty()) {
        linhas.push_back(linha_atual);
    }

    return linhas;
}

// Função principal
int main(int argc, char** argv) {
    // Verifica se os parâmetros corretos foram passados
    if (argc != 7) {
        cout << "Uso: " << argv[0] << " <input> <output> <titulo_carta> <atk> <def> <descricao>" << endl;
        return -1;
    }

    // Pega os argumentos da linha de comando
    string caminho_imagem_input = argv[1];  // Imagem de entrada
    string caminho_imagem_output = argv[2];  // Imagem de entrada
    string titulo_carta = argv[3];          // Título da carta
    string atk = argv[4];                   // Valor de ATK
    string def = argv[5];                   // Valor de DEF
    string descricao = argv[6];             // Descrição da carta

    string caminho_template = "template.jpg"; // Template da carta
                                              

    // Carrega a imagem de entrada e o template da carta
    Mat imagem_input = imread(caminho_imagem_input);
    Mat carta_template = imread(caminho_template);

    if (imagem_input.empty() || carta_template.empty()) {
        cout << "Erro ao carregar as imagens." << endl;
        return -1;
    }

    // Definir a região da carta onde a imagem será inserida
    Rect regiao_imagem(96, 212, 598, 598); // x, y, largura, altura

    // Redimensionar a imagem de entrada para caber na área da carta
    Mat imagem_redimensionada;
    resize(imagem_input, imagem_redimensionada, Size(regiao_imagem.width, regiao_imagem.height));

    // Inserir a imagem redimensionada no template da carta
    imagem_redimensionada.copyTo(carta_template(regiao_imagem));

    // Configurações de fonte para o OpenCV
    int fontFace = FONT_HERSHEY_TRIPLEX; // Tipo de fonte padrão
    double fontScaleAtkDefDesc = 1.0;              // Escala da fonte
    double fontScaleTitulo = 2.0;              // Escala da fonte
    int thickness = 2;                   // Espessura da fonte
    int thicknessDescricao = 1;                   // Espessura da fonte
    Scalar cor(0, 0, 0);    // Cor branca para o texto

    // 1. Adicionando o título (nome da carta)
    putText(carta_template, titulo_carta, Point(74, 116), fontFace, fontScaleTitulo, cor, thickness);

    // 2. Adicionando o ATK e DEF
    putText(carta_template, atk, Point(486, 1071), fontFace, fontScaleAtkDefDesc, cor, thickness);
    putText(carta_template, def, Point(648, 1071), fontFace, fontScaleAtkDefDesc, cor, thickness);

    // 3. Adicionando a descrição da carta com quebra automática de linha
    int largura_max_caixa = 636; // Largura máxima da "caixa de texto"
    int linha_inicio = 888;      // Posição inicial da primeira linha de texto
    int incremento_linha = 30;   // Espaço entre as linhas

    // Quebrar o texto em múltiplas linhas com base na largura da caixa
    vector<string> linhas = quebraTextoAutomatico(descricao, largura_max_caixa, fontFace, fontScaleAtkDefDesc, thickness);

    // Renderiza cada linha de texto
    for (size_t i = 0; i < linhas.size(); ++i) {
        putText(carta_template, linhas[i], Point(77, linha_inicio + i * incremento_linha), fontFace, fontScaleAtkDefDesc, cor, thicknessDescricao);
    }

    // Salvar a nova imagem gerada
    imwrite("output/"+caminho_imagem_output+".png", carta_template);

    cout << "Carta gerada com sucesso com quebra automática de linha!" << endl;
    return 0;
}
