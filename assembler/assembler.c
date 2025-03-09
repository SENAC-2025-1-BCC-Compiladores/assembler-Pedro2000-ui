#include "assembler.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 256

// Função que converte um arquivo de texto com instruções assembly em um arquivo binário
int converter_binario(FILE *input, FILE *output)
{
    // Buffer para armazenar o programa e os dados (256 posições, tamanho da memória Neander)
    uint16_t buffer[BUFFER_SIZE];

    // Cabeçalho do arquivo binário (identificação do formato Neander)
    uint8_t header[] = {0x03, 0x4e, 0x44, 0x52}; // "NDR" em hexadecimal
    fwrite(&header, sizeof(header), 1, output);  // Escreve o cabeçalho no arquivo de saída

    // Inicializa o buffer com zeros
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        buffer[i] = 0x00;
    }

    // Definição dos códigos das instruções
    uint16_t nop = 0x00; // Instrução NOP (No Operation)
    uint16_t sta = 0x10; // Instrução STA (Store Accumulator)
    uint16_t lda = 0x20; // Instrução LDA (Load Accumulator)
    uint16_t add = 0x30; // Instrução ADD (Add to Accumulator)
    uint16_t or = 0x40;  // Instrução OR (Logical OR)
    uint16_t and = 0x50; // Instrução AND (Logical AND)
    uint16_t not = 0x60; // Instrução NOT (Logical NOT)
    uint16_t jmp = 0x80; // Instrução JMP (Jump)
    uint16_t jn = 0x90;  // Instrução JN (Jump if Negative)
    uint16_t jz = 0xa0;  // Instrução JZ (Jump if Zero)
    uint16_t hlt = 0xf0; // Instrução HLT (Halt)

    // Variáveis para leitura do arquivo de entrada
    char linha[256];
    int idx = 0; // Índice para o buffer de instruções

    // Loop para ler o arquivo de entrada linha por linha
    while (fgets(linha, sizeof(linha), input))
    {
        // Remove o caractere de nova linha (\n) do final da linha
        linha[strcspn(linha, "\n")] = '\0';

        // Ignora linhas vazias ou comentários (começam com ';')
        if (linha[0] == '\0' || linha[0] == ';')
        {
            continue;
        }

        // Separa a instrução e o operando (se houver)
        char *instrucao = strtok(linha, " ");
        char *operando1 = strtok(NULL, " ");

        // Processa as instruções do programa
        if (strcmp(instrucao, "DADO") == 0)
        {
            buffer[idx++] = (uint16_t)atoi(operando1);
        }
        else if (strcmp(instrucao, "NOP") == 0)
        {
            buffer[idx++] = nop;
        }
        else if (strcmp(instrucao, "STA") == 0)
        {
            buffer[idx++] = sta;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "LDA") == 0)
        {
            buffer[idx++] = lda;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "ADD") == 0)
        {
            buffer[idx++] = add;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "OR") == 0)
        {
            buffer[idx++] = or ;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "AND") == 0)
        {
            buffer[idx++] = and;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "NOT") == 0)
        {
            buffer[idx++] = not;
        }
        else if (strcmp(instrucao, "JMP") == 0)
        {
            buffer[idx++] = jmp;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "JN") == 0)
        {
            buffer[idx++] = jn;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "JZ") == 0)
        {
            buffer[idx++] = jz;
            buffer[idx++] = (uint16_t)atoi(operando1); // Converte o operando para número
        }
        else if (strcmp(instrucao, "HLT") == 0)
        {
            buffer[idx++] = hlt;
        }
        else
        {
            printf("Instrução desconhecida: %s\n", instrucao);
            return -1; // Retorna erro se a instrução for desconhecida
        }
    }

    // Escreve o buffer no arquivo de saída
    fwrite(&buffer, sizeof(uint16_t), BUFFER_SIZE, output);

    // Fecha os arquivos
    fclose(input);
    fclose(output);

    return 0; // Retorna 0 indicando sucesso
}