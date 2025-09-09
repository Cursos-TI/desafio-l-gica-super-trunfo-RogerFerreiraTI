#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Estrutura para representar uma carta de cidade
typedef struct {
    char estado[50];
    char codigo[10];
    char nome_cidade[100];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
    float densidade_populacional;
} Carta;

// Enumeração para os tipos de atributos
typedef enum {
    POPULACAO = 1,
    AREA,
    PIB,
    PONTOS_TURISTICOS,
    DENSIDADE_POPULACIONAL
} TipoAtributo;

// Protótipos das funções
void limpar_buffer();
void exibir_menu_principal();
void exibir_menu_atributos();
Carta criar_carta(int numero_carta);
void exibir_carta(Carta carta, int numero);
void calcular_densidade_populacional(Carta *carta);
int escolher_atributo(const char *mensagem);
int comparar_atributo(Carta carta1, Carta carta2, TipoAtributo atributo);
void realizar_comparacao_simples(Carta carta1, Carta carta2);
void realizar_comparacao_dupla(Carta carta1, Carta carta2);
const char* obter_nome_atributo(TipoAtributo atributo);
float obter_valor_atributo(Carta carta, TipoAtributo atributo);
void exibir_resultado_comparacao(Carta carta1, Carta carta2, TipoAtributo atributo1, TipoAtributo atributo2);

/**
 * Função principal do programa
 * Controla o fluxo principal do jogo Super Trunfo
 */
int main() {
    printf("=== SUPER TRUNFO - CIDADES (NÍVEL MESTRE) ===\n\n");
    
    // Cadastro das duas cartas
    printf("Vamos cadastrar as cartas das cidades!\n\n");
    Carta carta1 = criar_carta(1);
    Carta carta2 = criar_carta(2);
    
    // Exibição das cartas cadastradas
    printf("\n=== CARTAS CADASTRADAS ===\n");
    exibir_carta(carta1, 1);
    printf("\n");
    exibir_carta(carta2, 2);
    
    int opcao;
    do {
        exibir_menu_principal();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        limpar_buffer();
        
        switch(opcao) {
            case 1:
                realizar_comparacao_simples(carta1, carta2);
                break;
            case 2:
                realizar_comparacao_dupla(carta1, carta2);
                break;
            case 3:
                printf("\nObrigado por jogar Super Trunfo - Cidades!\n");
                printf("Desenvolvido pela Equipe MateCheck\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
        
        if (opcao != 3) {
            printf("\nPressione ENTER para continuar...");
            getchar();
        }
        
    } while(opcao != 3);
    
    return 0;
}

/**
 * Limpa o buffer de entrada para evitar problemas com scanf
 */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/**
 * Exibe o menu principal do jogo
 */
void exibir_menu_principal() {
    printf("\n=== MENU PRINCIPAL ===\n");
    printf("1. Comparar um atributo\n");
    printf("2. Comparar dois atributos\n");
    printf("3. Sair\n");
    printf("========================\n");
}

/**
 * Exibe o menu de seleção de atributos
 */
void exibir_menu_atributos() {
    printf("\n=== ATRIBUTOS DISPONÍVEIS ===\n");
    printf("1. População\n");
    printf("2. Área (km²)\n");
    printf("3. PIB (milhões)\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional (hab/km²)\n");
    printf("==============================\n");
}

/**
 * Cria uma nova carta através da entrada do usuário
 * @param numero_carta Número identificador da carta (1 ou 2)
 * @return Estrutura Carta preenchida com os dados inseridos
 */
Carta criar_carta(int numero_carta) {
    Carta nova_carta;
    
    printf("--- CADASTRO DA CARTA %d ---\n", numero_carta);
    
    printf("Estado: ");
    fgets(nova_carta.estado, sizeof(nova_carta.estado), stdin);
    nova_carta.estado[strcspn(nova_carta.estado, "\n")] = 0; // Remove quebra de linha
    
    printf("Código da carta: ");
    fgets(nova_carta.codigo, sizeof(nova_carta.codigo), stdin);
    nova_carta.codigo[strcspn(nova_carta.codigo, "\n")] = 0;
    
    printf("Nome da cidade: ");
    fgets(nova_carta.nome_cidade, sizeof(nova_carta.nome_cidade), stdin);
    nova_carta.nome_cidade[strcspn(nova_carta.nome_cidade, "\n")] = 0;
    
    printf("População: ");
    scanf("%d", &nova_carta.populacao);
    
    printf("Área (km²): ");
    scanf("%f", &nova_carta.area);
    
    printf("PIB (milhões): ");
    scanf("%f", &nova_carta.pib);
    
    printf("Número de pontos turísticos: ");
    scanf("%d", &nova_carta.pontos_turisticos);
    
    limpar_buffer();
    
    // Calcula automaticamente a densidade populacional
    calcular_densidade_populacional(&nova_carta);
    
    printf("Carta %d cadastrada com sucesso!\n", numero_carta);
    
    return nova_carta;
}

/**
 * Exibe as informações de uma carta de forma organizada
 * @param carta Carta a ser exibida
 * @param numero Número identificador da carta
 */
void exibir_carta(Carta carta, int numero) {
    printf("CARTA %d - %s\n", numero, carta.codigo);
    printf("Estado: %s\n", carta.estado);
    printf("Cidade: %s\n", carta.nome_cidade);
    printf("População: %d habitantes\n", carta.populacao);
    printf("Área: %.2f km²\n", carta.area);
    printf("PIB: R$ %.2f milhões\n", carta.pib);
    printf("Pontos Turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade Populacional: %.2f hab/km²\n", carta.densidade_populacional);
}

/**
 * Calcula a densidade populacional de uma carta
 * @param carta Ponteiro para a carta a ter a densidade calculada
 */
void calcular_densidade_populacional(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade_populacional = (float)carta->populacao / carta->area;
    } else {
        carta->densidade_populacional = 0;
    }
}

/**
 * Permite ao usuário escolher um atributo para comparação
 * @param mensagem Mensagem personalizada para a escolha
 * @return Tipo do atributo escolhido
 */
int escolher_atributo(const char *mensagem) {
    int opcao;
    
    do {
        exibir_menu_atributos();
        printf("%s: ", mensagem);
        scanf("%d", &opcao);
        limpar_buffer();
        
        if (opcao < 1 || opcao > 5) {
            printf("Opção inválida! Escolha entre 1 e 5.\n");
        }
    } while (opcao < 1 || opcao > 5);
    
    return opcao;
}

/**
 * Compara um atributo específico entre duas cartas
 * @param carta1 Primeira carta para comparação
 * @param carta2 Segunda carta para comparação
 * @param atributo Tipo do atributo a ser comparado
 * @return 1 se carta1 vencer, 2 se carta2 vencer, 0 se empatar
 */
int comparar_atributo(Carta carta1, Carta carta2, TipoAtributo atributo) {
    float valor1 = obter_valor_atributo(carta1, atributo);
    float valor2 = obter_valor_atributo(carta2, atributo);
    
    // Para densidade populacional, menor valor vence
    if (atributo == DENSIDADE_POPULACIONAL) {
        return (valor1 < valor2) ? 1 : (valor1 > valor2) ? 2 : 0;
    }
    
    // Para outros atributos, maior valor vence
    return (valor1 > valor2) ? 1 : (valor1 < valor2) ? 2 : 0;
}

/**
 * Realiza comparação simples entre duas cartas (um atributo)
 * @param carta1 Primeira carta
 * @param carta2 Segunda carta
 */
void realizar_comparacao_simples(Carta carta1, Carta carta2) {
    printf("\n=== COMPARAÇÃO SIMPLES ===\n");
    
    TipoAtributo atributo = escolher_atributo("Escolha o atributo para comparação");
    
    int resultado = comparar_atributo(carta1, carta2, atributo);
    
    printf("\n--- RESULTADO DA COMPARAÇÃO ---\n");
    printf("Atributo comparado: %s\n", obter_nome_atributo(atributo));
    printf("Carta 1 (%s): %.2f\n", carta1.nome_cidade, obter_valor_atributo(carta1, atributo));
    printf("Carta 2 (%s): %.2f\n", carta2.nome_cidade, obter_valor_atributo(carta2, atributo));
    
    switch(resultado) {
        case 1:
            printf("🏆 VENCEDOR: %s - %s!\n", carta1.codigo, carta1.nome_cidade);
            break;
        case 2:
            printf("🏆 VENCEDOR: %s - %s!\n", carta2.codigo, carta2.nome_cidade);
            break;
        case 0:
            printf("🤝 EMPATE! As duas cidades têm o mesmo valor para este atributo.\n");
            break;
    }
}

/**
 * Realiza comparação dupla entre duas cartas (dois atributos)
 * @param carta1 Primeira carta
 * @param carta2 Segunda carta
 */
void realizar_comparacao_dupla(Carta carta1, Carta carta2) {
    printf("\n=== COMPARAÇÃO DUPLA ===\n");
    
    TipoAtributo atributo1 = escolher_atributo("Escolha o primeiro atributo");
    TipoAtributo atributo2;
    
    do {
        atributo2 = escolher_atributo("Escolha o segundo atributo");
        if (atributo1 == atributo2) {
            printf("Você deve escolher dois atributos diferentes!\n");
        }
    } while (atributo1 == atributo2);
    
    int resultado1 = comparar_atributo(carta1, carta2, atributo1);
    int resultado2 = comparar_atributo(carta1, carta2, atributo2);
    
    exibir_resultado_comparacao(carta1, carta2, atributo1, atributo2);
    
    // Lógica de decisão complexa usando operador ternário
    int pontos_carta1 = (resultado1 == 1 ? 1 : 0) + (resultado2 == 1 ? 1 : 0);
    int pontos_carta2 = (resultado1 == 2 ? 1 : 0) + (resultado2 == 2 ? 1 : 0);
    
    printf("\n--- RESULTADO FINAL ---\n");
    printf("Pontuação da Carta 1 (%s): %d pontos\n", carta1.nome_cidade, pontos_carta1);
    printf("Pontuação da Carta 2 (%s): %d pontos\n", carta2.nome_cidade, pontos_carta2);
    
    // Determinação do vencedor usando if/else para maior clareza e formatação correta
    if (pontos_carta1 > pontos_carta2) {
        printf("🏆 VENCEDOR: %s - %s!\n", carta1.codigo, carta1.nome_cidade);
    } else if (pontos_carta2 > pontos_carta1) {
        printf("🏆 VENCEDOR: %s - %s!\n", carta2.codigo, carta2.nome_cidade);
    } else {
        printf("🤝 EMPATE TÉCNICO!\n");
    }
}

/**
 * Obtém o nome de um atributo baseado no tipo
 * @param atributo Tipo do atributo
 * @return Nome do atributo como string
 */
const char* obter_nome_atributo(TipoAtributo atributo) {
    switch(atributo) {
        case POPULACAO: return "População";
        case AREA: return "Área";
        case PIB: return "PIB";
        case PONTOS_TURISTICOS: return "Pontos Turísticos";
        case DENSIDADE_POPULACIONAL: return "Densidade Populacional";
        default: return "Desconhecido";
    }
}

/**
 * Obtém o valor de um atributo específico de uma carta
 * @param carta Carta da qual extrair o valor
 * @param atributo Tipo do atributo desejado
 * @return Valor do atributo como float
 */
float obter_valor_atributo(Carta carta, TipoAtributo atributo) {
    switch(atributo) {
        case POPULACAO: return (float)carta.populacao;
        case AREA: return carta.area;
        case PIB: return carta.pib;
        case PONTOS_TURISTICOS: return (float)carta.pontos_turisticos;
        case DENSIDADE_POPULACIONAL: return carta.densidade_populacional;
        default: return 0;
    }
}

/**
 * Exibe o resultado detalhado da comparação dupla
 * @param carta1 Primeira carta
 * @param carta2 Segunda carta
 * @param atributo1 Primeiro atributo comparado
 * @param atributo2 Segundo atributo comparado
 */
void exibir_resultado_comparacao(Carta carta1, Carta carta2, TipoAtributo atributo1, TipoAtributo atributo2) {
    printf("\n--- COMPARAÇÃO DETALHADA ---\n");
    
    printf("\n%s:\n", obter_nome_atributo(atributo1));
    printf("  %s (%s): %.2f\n", carta1.codigo, carta1.nome_cidade, obter_valor_atributo(carta1, atributo1));
    printf("  %s (%s): %.2f\n", carta2.codigo, carta2.nome_cidade, obter_valor_atributo(carta2, atributo1));
    
    int resultado1 = comparar_atributo(carta1, carta2, atributo1);
    printf("  Vencedor: %s\n", 
           (resultado1 == 1) ? carta1.codigo : 
           (resultado1 == 2) ? carta2.codigo : "Empate");
    
    printf("\n%s:\n", obter_nome_atributo(atributo2));
    printf("  %s (%s): %.2f\n", carta1.codigo, carta1.nome_cidade, obter_valor_atributo(carta1, atributo2));
    printf("  %s (%s): %.2f\n", carta2.codigo, carta2.nome_cidade, obter_valor_atributo(carta2, atributo2));
    
    int resultado2 = comparar_atributo(carta1, carta2, atributo2);
    printf("  Vencedor: %s\n", 
           (resultado2 == 1) ? carta1.codigo : 
           (resultado2 == 2) ? carta2.codigo : "Empate");
}