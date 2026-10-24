
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 10
#define NUM_NOTAS 3
#define TAM_NOME 50

float calcularMedia(float n1, float n2, float n3) {
    return (n1 + n2 + n3) / 3.0f;
}

void calcularMediaPonteiro(float n1, float n2, float n3,
                           float *resultado) {
    *resultado = (n1 + n2 + n3) / 3.0f;
}

void calcularMedias(float notas[][NUM_NOTAS],
                    int quantidade, float *medias) {
    int i;

    for (i = 0; i < quantidade; i++) {
        calcularMediaPonteiro(
            notas[i][0],
            notas[i][1],
            notas[i][2],
            &medias[i]
        );
    }
}

const char *verificarSituacao(float media) {
    if (media >= 6.0f) {
        return "Atingiu a meta";
    }

    return "Abaixo da meta";
}

float calcularMediaTurma(float medias[], int quantidade) {
    float soma = 0.0f;
    int i;

    for (i = 0; i < quantidade; i++) {
        soma += medias[i];
    }

    return soma / quantidade;
}

float encontrarMaiorMedia(float medias[], int quantidade) {
    float maior = medias[0];
    int i;

    for (i = 1; i < quantidade; i++) {
        if (medias[i] > maior) {
            maior = medias[i];
        }
    }

    return maior;
}

int main(void) {
    char nomes[MAX_ALUNOS][TAM_NOME];
    float notas[MAX_ALUNOS][NUM_NOTAS];
    float *medias;
    float mediaTurma, maiorMedia;
    int quantidade;
    int i, j;

    printf("=== SISTEMA DE MEDIAS DOS ALUNOS ===\n");

    printf("Quantidade de alunos (1 a 10): ");
    scanf("%d", &quantidade);

    while (quantidade < 1 || quantidade > MAX_ALUNOS) {
        printf("Quantidade invalida! Digite de 1 a 10: ");
        scanf("%d", &quantidade);
    }

    getchar();

    medias = malloc(quantidade * sizeof(float));

    if (medias == NULL) {
        printf("Erro ao alocar memoria!\n");
        return 1;
    }

    for (i = 0; i < quantidade; i++) {
        medias[i] = 0.0f;
    }

    for (i = 0; i < quantidade; i++) {
        printf("\nNome do aluno %d: ", i + 1);
        fgets(nomes[i], TAM_NOME, stdin);

        nomes[i][strcspn(nomes[i], "\n")] = '\0';

        for (j = 0; j < NUM_NOTAS; j++) {
            printf("Digite a nota %d (0 a 10): ", j + 1);
            scanf("%f", &notas[i][j]);

            while (notas[i][j] < 0.0f ||
                   notas[i][j] > 10.0f) {
                printf("Nota invalida! Digite de 0 a 10: ");
                scanf("%f", &notas[i][j]);
            }
        }

        getchar();
    }

    calcularMedias(notas, quantidade, medias);

    printf("\n========== RESULTADOS ==========\n");

    for (i = 0; i < quantidade; i++) {
        printf("\nAluno: %s\n", nomes[i]);

        printf("Notas: %.2f, %.2f, %.2f\n",
               notas[i][0],
               notas[i][1],
               notas[i][2]);

        printf("Media: %.2f\n", medias[i]);
        printf("Situacao: %s\n",
               verificarSituacao(medias[i]));
    }

    mediaTurma = calcularMediaTurma(medias, quantidade);
    maiorMedia = encontrarMaiorMedia(medias, quantidade);

    printf("\nMedia da turma: %.2f\n", mediaTurma);
    printf("Maior media: %.2f\n", maiorMedia);

    printf("\nAluno(s) com a maior media:\n");

    for (i = 0; i < quantidade; i++) {
        if (medias[i] == maiorMedia) {
            printf("- %s (%.2f)\n", nomes[i], medias[i]);
        }
    }

    free(medias);

    printf("\nMemoria liberada com sucesso!\n");

    return 0;
}
