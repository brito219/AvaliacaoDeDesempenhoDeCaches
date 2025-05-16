//-----------------------------------------------------------------------------
// Simulador de cache básica: UM ÚNICO NÍVEL DE CACHE, UNIFICADA PARA INSTRUÇÕES E DADOS
//
// Para compilar: gcc cache.c simbasica.c -o simbasica -Wall
// Para executar: simbasica arquivoConfiguracao arquivoAcessos
//-----------------------------------------------------------------------------
// Bibliotecas

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cache.h" // Módulo que implementa cache genérica

//-----------------------------------------------------------------------------
// Variaveis

// Medidas de desempenho
int nAcessosI, // Número total de acessos a instruções
	nAcessosD, // Número total de acessos a dados
	nFalhasI,  // Número de falhas na cache L1
	nFalhasD;

tCache cacheI; // Cache I
tCache cacheD; // Cache D

FILE *arqAcessos; // Arquivo de trace com acessos a memória

//-----------------------------------------------------------------------------
// Prototipos de funcoes

void inicializa(int, char **);
void finaliza(void);

//-----------------------------------------------------------------------------
// Programa principal

int main(int argc, char **argv)
{
	char tipoAcesso; // 'I' (leitura de instrução), 'L' (LOAD = leitura de dado) ou 'S' (STORE = escrita de dado)
	int result,
		resultAcesso,
		endereco; // Endereço de memória acessado

	inicializa(argc, argv);

	// Enquanto não termina arquivo de acessos
	while (!feof(arqAcessos))
	{
		// Lê um endereço do arquivo de acessos
		result = fscanf(arqAcessos, "%c %d\n", &tipoAcesso, &endereco);

		if ((result != 0) && (result != EOF))
		{
			if (tipoAcesso == 'I')
			{

				// Acesso é leitura de uma instrução
				nAcessosI++;
				resultAcesso = buscaInsereCache(&cacheI, endereco);

				if ((resultAcesso == 1) || (resultAcesso == 2)) // Se houve falha na cache
					nFalhasI++;
			}

			else // Acesso é leitura de dado ('L') ou escrita de dado ('S')
			{
				nAcessosD++;
				resultAcesso = buscaInsereCache(&cacheD, endereco);

				if ((resultAcesso == 1) || (resultAcesso == 2)) // Se houve falha na cache
					nFalhasD++;
			}
			// Procura bloco na cache e, se não encontra, insere bloco na cache
			// Valor de retorno = 0 (acerto), 1 (falha sem substituição) ou 2 (falha com substituição)
		}
	}

	finaliza();

	return 0;
}

void inicializa(int argc, char **argv)
{
	char nomeArqConfig[100],
		nomeArqAcessos[100];

	unsigned int nBlocosI, // Número total de blocos da cache L1
		associatividadeI,  // Número de blocos por conjunto da cache L1
		nPalavrasBlocoI,   // Número de palavras do bloco da cache L1
		nBlocosD,
		associatividadeD,
		nPalavrasBlocoD;

	FILE *arqConfig; // Arquivo com configuração da cache

	if (argc != 3)
	{
		printf("\nUso: simbasica arquivoConfiguracao arquivoAcessos\n");
		exit(0);
	}

	// Lê arquivo de configuracao e obtem nBlocos, associatividade e nPalavrasBloco da cache L1
	strcpy(nomeArqConfig, argv[1]);
	arqConfig = fopen(nomeArqConfig, "rt");
	if (arqConfig == NULL)
	{
		printf("\nArquivo de configuração não encontrado\n");
		exit(0);
	}
	fscanf(arqConfig, "%d %d %d", &nBlocosI, &associatividadeI, &nPalavrasBlocoI);
	fscanf(arqConfig, "%d %d %d", &nBlocosD, &associatividadeD, &nPalavrasBlocoD);
	fclose(arqConfig);

	// Abre arquivo de acessos
	strcpy(nomeArqAcessos, argv[2]);
	arqAcessos = fopen(nomeArqAcessos, "rt");
	if (arqAcessos == NULL)
	{
		printf("\nArquivo de acessos não encontrado\n");
		exit(0);
	}

	// Inicializa medidas de desempenho
	nAcessosI = 0;
	nAcessosD = 0;
	nFalhasI = 0;
	nFalhasD = 0;

	// Aloca e inicializa estrutura de dados da cache I
	alocaCache(&cacheI, nBlocosI, associatividadeI, nPalavrasBlocoI);

	// Aloca e inicializa estrutura de dados da cache D
	alocaCache(&cacheD, nBlocosD, associatividadeD, nPalavrasBlocoD);
}

//-----------------------------------------------------------------------------
void finaliza(void)
{
	// Fecha arquivo de acessos
	fclose(arqAcessos);

	// Imprime medidas de desempenho
	printf("nAcessosI: %d\n", nAcessosI);
	printf("nAcessosD: %d\n", nAcessosD);
	printf("nFalhasI: %d\n", nFalhasI);
	printf("nFalhasD: %d\n", nFalhasD);

	// Libera estrutura de dados da cache
	liberaCache(&cacheI);
	liberaCache(&cacheD);
}

//-----------------------------------------------------------------------------
