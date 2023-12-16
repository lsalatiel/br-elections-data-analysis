# br-elections-data-analysis
## Sobre
Trabalho da disciplina de Programação Orientada a Objetos, com o intuito de processar informações sobre a eleição legislativa do ano de 2022 para Deputados Federais e Deputados Estaduais.

## Como usar
1. Clone o repositório
```sh
git clone https://github.com/lsalatiel/br-elections-data-analysis.git
```
2. Compile
```sh
make
```
3. Execute o binario
```sh
./deputados <opção_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>
```
- opção_de_cargo - o cargo dos candidatos a serem analisados (--federal ou --estadual)

- caminho_arquivo_candidatos - o caminho para o arquivo de cadidatos

- caminho_arquivo_votacao - o caminho para o arquivo de votação 

- data - a data a ser analisada (DD/MM/YYYY)

---

4. Outras alternativas de executar
```sh
make runfederal
```
para rodar com "--federal candidatos.csv votacao.csv 02/10/2022"
```
make runestadual
```
para rodar com "--estadual candidatos.csv votacao.csv 02/10/2022"
