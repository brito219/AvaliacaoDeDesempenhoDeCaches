# Simuladores de Cache para Arquitetura de Computadores 2

Este projeto contém simuladores de cache desenvolvidos como parte do Trabalho 1 da disciplina de Arquitetura de Computadores 2. Os simuladores permitem avaliar o desempenho de diferentes configurações de cache utilizando um arquivo de trace de acessos à memória.

## Visão Geral do Projeto

O objetivo principal é implementar e analisar o comportamento de caches com diferentes organizações:

- **Cache Única Unificada:** Um único nível de cache que armazena tanto instruções quanto dados.
- **Cache Única Dividida (Split):** Um único nível de cache, mas com caches separadas para instruções e dados.
- **Cache de Múltiplos Níveis:** Uma hierarquia com cache L1 dividida (instruções e dados) e uma cache L2 unificada.

Os simuladores são implementados em C e utilizam um arquivo de trace (`traceDijkstra.txt`) para simular os acessos à memória.

## Arquivos do Projeto

- `cache.c`: Contém a implementação das funcionalidades básicas da cache (lógica de busca, inserção, políticas de substituição, etc.), utilizada por todos os simuladores.
- `cache.h`: Arquivo de cabeçalho para `cache.c`, definindo as estruturas de dados e protótipos das funções da cache.
- `simbasica.c`: Implementação do simulador de cache única unificada.
- `simsplit.c`: Implementação do simulador de cache única dividida (uma para instruções, outra para dados).
- `simniveis.c`: Implementação do simulador de cache com dois níveis (L1 dividida e L2 unificada).
- `traceDijkstra.txt`: Arquivo de trace contendo os endereços de memória acessados, utilizado como entrada para as simulações. (Nota: Este arquivo é grande e pode não estar incluído diretamente no repositório. Consulte as instruções de obtenção se necessário).
- `relatorio_final.pdf` (ou similar): Documento contendo a análise detalhada dos experimentos realizados com os simuladores.
- `README.md`: Este arquivo.

## Compilação dos Simuladores

Os simuladores podem ser compilados utilizando um compilador C (como o GCC) e a biblioteca matemática (`-lm`). Execute os seguintes comandos no terminal, no diretório do projeto:

- **Para o simulador básico (cache unificada):**

  ```bash
  gcc -o simbasica simbasica.c cache.c -lm
  ```

- **Para o simulador com cache dividida:**

  ```bash
  gcc -o simsplit simsplit.c cache.c -lm
  ```

- **Para o simulador com múltiplos níveis de cache:**
  ```bash
  gcc -o simniveis simniveis.c cache.c -lm
  ```

## Execução dos Simuladores

Após a compilação, os simuladores podem ser executados a partir do terminal. Eles geralmente requerem um arquivo de configuração da cache e o arquivo de trace como argumentos.

### Formato do Arquivo de Configuração

Os arquivos de configuração especificam os parâmetros da(s) cache(s). O formato exato pode variar ligeiramente entre os simuladores:

- **`simbasica` (Cache L1 Unificada):**

  ```
  <NBlocos_L1>
  <Associatividade_L1>
  <NPalavrasBloco_L1>
  ```

  Exemplo de arquivo `config_l1.txt`:

  ```
  64
  1
  2
  ```

- **`simsplit` (Cache L1 Dividida - I1 para Instruções, D1 para Dados):**

  ```
  <NBlocos_I1>
  <Associatividade_I1>
  <NPalavrasBloco_I1>
  <NBlocos_D1>
  <Associatividade_D1>
  <NPalavrasBloco_D1>
  ```

  Exemplo de arquivo `config_split.txt`:

  ```
  32
  1
  1
  32
  1
  1
  ```

- **`simniveis` (Cache L1 Dividida e L2 Unificada):**
  ```
  <NBlocos_I1>
  <Associatividade_I1>
  <NPalavrasBloco_I1>
  <NBlocos_D1>
  <Associatividade_D1>
  <NPalavrasBloco_D1>
  <NBlocos_L2>
  <Associatividade_L2>
  <NPalavrasBloco_L2>
  ```
  Exemplo de arquivo `config_niveis.txt`:
  ```
  32
  1
  2
  32
  1
  2
  64
  2
  8
  ```

### Comandos de Execução

- **`simbasica`:**

  ```bash
  ./simbasica <arquivo_config_l1.txt> <arquivo_trace.txt>
  ```

  Exemplo:

  ```bash
  ./simbasica config_l1.txt traceDijkstra.txt
  ```

- **`simsplit`:**

  ```bash
  ./simsplit <arquivo_config_split.txt> <arquivo_trace.txt>
  ```

  Exemplo:

  ```bash
  ./simsplit config_split.txt traceDijkstra.txt
  ```

- **`simniveis`:**
  ```bash
  ./simniveis <arquivo_config_niveis.txt> <arquivo_trace.txt>
  ```
  Exemplo:
  ```bash
  ./simniveis config_niveis.txt traceDijkstra.txt
  ```

A saída dos simuladores geralmente inclui estatísticas como número de acessos, número de falhas (misses) e taxas de falha para cada nível de cache.

## Experimentos e Análise

Foram realizados diversos experimentos para avaliar o impacto de diferentes parâmetros da cache (tamanho, associatividade, tamanho do bloco) e organizações (unificada vs. dividida, um nível vs. dois níveis) no desempenho geral. As análises detalhadas, incluindo os resultados das simulações e as respostas às questões propostas, podem ser encontradas no arquivo `relatorio_final.pdf` (ou nome similar) que acompanha este projeto.

## Contribuições e Autoria

Este trabalho foi desenvolvido por [Seu Nome/Nomes do Grupo Aqui] como parte dos requisitos da disciplina de Arquitetura de Computadores 2.

---

Sinta-se à vontade para adaptar a seção de "Contribuições e Autoria" e verificar se os nomes dos arquivos de configuração e relatório correspondem exatamente aos que você está usando.
