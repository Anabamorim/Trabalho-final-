#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Veiculo {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
    struct Veiculo *prox;
} Veiculo;

// criar um novo veículo
Veiculo* criarVeiculo(char proprietario[], char combustivel[], char modelo[], char cor[], char chassi[], int ano, char placa[]) {
    Veiculo *novoVeiculo = (Veiculo*)malloc(sizeof(Veiculo));
    if (novoVeiculo != NULL) {
        strcpy(novoVeiculo->proprietario, proprietario);
        strcpy(novoVeiculo->combustivel, combustivel);
        strcpy(novoVeiculo->modelo, modelo);
        strcpy(novoVeiculo->cor, cor);
        strcpy(novoVeiculo->chassi, chassi);
        novoVeiculo->ano = ano;
        strcpy(novoVeiculo->placa, placa);
        novoVeiculo->prox = NULL;
    }
    return novoVeiculo;
}

// carros do ano de 2010 ou posterior movidos a diesel
void listarProprietariosDiesel2010OuPosterior(Veiculo *inicio) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        if (atual->ano >= 2010 && strcmp(atual->combustivel, "diesel") == 0) {
            printf("Proprietário: %s\n", atual->proprietario);
        }
        atual = atual->prox;
    }
}

//  placas que comecem com a letra J e terminem com 0, 2, 4 ou 7 
void listarPlacasJFinal0247(Veiculo *inicio) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        if (atual->placa[0] == 'J' && (atual->placa[6] == '0' || atual->placa[6] == '2' || atual->placa[6] == '4' || atual->placa[6] == '7')) {
            printf("Placa: %s | Proprietário: %s\n", atual->placa, atual->proprietario);
        }
        atual = atual->prox;
    }
}

// modelo e cor dos veículos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par
void listarModeloCorPlacasSegundaVogalSomaPar(Veiculo *inicio) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        if ((atual->placa[1] == 'A' || atual->placa[1] == 'E' || atual->placa[1] == 'I' || atual->placa[1] == 'O' || atual->placa[1] == 'U')
            && ((atual->placa[2] - '0') + (atual->placa[3] - '0') + (atual->placa[4] - '0') + (atual->placa[5] - '0')) % 2 == 0) {
            printf("Modelo: %s | Cor: %s\n", atual->modelo, atual->cor);
        }
        atual = atual->prox;
    }
}

// trocar proprietário com base no número do chassi para carros com placas sem nenhum dígito igual a zero
void trocarProprietarioSemDigitoZero(Veiculo *inicio, char chassi[], char novoProprietario[]) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        int temZero = 0;
        for (int i = 0; i < strlen(atual->placa); i++) {
            if (atual->placa[i] == '0') {
                temZero = 1;
                break;
            }
        }
        if (!temZero && strcmp(atual->chassi, chassi) == 0) {
            strcpy(atual->proprietario, novoProprietario);
            printf("Proprietário alterado com sucesso.\n");
            return;
        }
        atual = atual->prox;
    }
    printf("Não foi possível encontrar um veículo com essas características.\n");
}


void liberarLista(Veiculo *inicio) {
    Veiculo *atual = inicio;
    while (atual != NULL) {
        Veiculo *temp = atual;
        atual = atual->prox;
        free(temp);
    }
}

int main() {
   
    Veiculo *listaVeiculos = NULL;

    // veículos à lista 
    listaVeiculos = criarVeiculo("Joao", "diesel", "Gol", "Preto", "123456789", 2010, "JAB1234");
    listaVeiculos->prox = criarVeiculo("Maria", "gasolina", "Civic", "Branco", "987654321", 2015, "JZC5678");
    listaVeiculos->prox->prox = criarVeiculo("Pedro", "diesel", "Onix", "Vermelho", "246810121", 2020, "JOD2468");

    printf("Proprietários de carros do ano de 2010 ou posterior movidos a diesel:\n");
    listarProprietariosDiesel2010OuPosterior(listaVeiculos);

    printf("\nPlacas que começam com J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários:\n");
    listarPlacasJFinal0247(listaVeiculos);

    printf("\nModelo e cor dos veículos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par:\n");
    listarModeloCorPlacasSegundaVogalSomaPar(listaVeiculos);

    printf("\nTroca de proprietário com base no número do chassi para carros com placas sem nenhum dígito igual a zero:\n");
    trocarProprietarioSemDigitoZero(listaVeiculos, "123456789", "Novo Proprietario");

    liberarLista(listaVeiculos); 

    return 0;
}
