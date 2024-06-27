#include "funcoes_operacoes.h"

//função que verifica se a string é igual a "NULO"
int VerificaNulo(char **Campo, char *string) {
    int tamanho;
    if (strcmp(string, "NULO") == 0) {
        tamanho = 0;
        *Campo = (char *)malloc(sizeof(char));
        (*Campo)[0] = '\0';
    } else {
        tamanho = strlen(string);
        *Campo = (char *)malloc((tamanho + 1) * sizeof(char));
        strncpy(*Campo, string, tamanho);
        (*Campo)[tamanho] = '\0';
    }
    return tamanho;
}

//função que verifica se o token esta vazio, e caso negativo aloca o tamanho necessario para armazenar o valor
int AlocaCamposVariados(char **Campo, char *token){
    int tamanho;
    if(token == NULL || *token == '\0'){
        tamanho = 0;
    }else{

        tamanho = strlen(token);

        *Campo = (char *)malloc((tamanho + 1) * sizeof(char));

        if (*Campo == NULL) {
            return -1;
        }

        strncpy(*Campo, token, tamanho);
    }
    return tamanho;
}



void binarioNaTela(char *nomeArquivoBinario) {

	/* Use essa função para comparação no run.codes. Lembre-se de ter fechado (fclose) o arquivo anteriormente.
	*  Ela vai abrir de novo para leitura e depois fechar (você não vai perder pontos por isso se usar ela). */

	unsigned long i, cs;
	unsigned char *mb;
	size_t fl;
	FILE *fs;
	if(nomeArquivoBinario == NULL || !(fs = fopen(nomeArquivoBinario, "rb"))) {
		fprintf(stderr, "ERRO AO ESCREVER O BINARIO NA TELA (função binarioNaTela): não foi possível abrir o arquivo que me passou para leitura. Ele existe e você tá passando o nome certo? Você lembrou de fechar ele com fclose depois de usar?\n");
		return;
	}
	fseek(fs, 0, SEEK_END);
	fl = ftell(fs);
	fseek(fs, 0, SEEK_SET);
	mb = (unsigned char *) malloc(fl);
	fread(mb, 1, fl, fs);

	cs = 0;
	for(i = 0; i < fl; i++) {
		cs += (unsigned long) mb[i];
	}
	printf("%lf\n", (cs / (double) 100));
	free(mb);
	fclose(fs);
}

//função que verifica se o token esta vazio, e caso negativo armazena a ele no registro como int
void processarCampoInt(Registro *registro, char *token, int *campo) {
    if (token != NULL && *token != '\0') {
        *campo = atoi(token);
    } else {
        *campo = -1;
    }
}

//função que verifica se o token esta vazio e atribui tamanho 0 caso positivo
void processarCampoString(Registro *registro, char *token, int *tamanhoCampo, char **campo) {
    if (token != NULL && *token != '\0' && strlen(token) > 1) {
        *tamanhoCampo = AlocaCamposVariados(campo, token);
    } else {
        *tamanhoCampo = 0;
    }
}

void scan_quote_string(char *str) {

	/*
	*	Use essa função para ler um campo string delimitado entre aspas (").
	*	Chame ela na hora que for ler tal campo. Por exemplo:
	*
	*	A entrada está da seguinte forma:
	*		nomeDoCampo "MARIA DA SILVA"
	*
	*	Para ler isso para as strings já alocadas str1 e str2 do seu programa, você faz:
	*		scanf("%s", str1); // Vai salvar nomeDoCampo em str1
	*		scan_quote_string(str2); // Vai salvar MARIA DA SILVA em str2 (sem as aspas)
	*
	*/

	char R;

	while((R = getchar()) != EOF && isspace(R)); // ignorar espaços, \r, \n...

	if(R == 'N' || R == 'n') { // campo NULO
		getchar(); getchar(); getchar(); // ignorar o "ULO" de NULO.
		strcpy(str, ""); // copia string vazia
	} else if(R == '\"') {
		if(scanf("%[^\"]", str) != 1) { // ler até o fechamento das aspas
			strcpy(str, "");
		}
		getchar(); // ignorar aspas fechando
	} else if(R != EOF){ // vc tá tentando ler uma string que não tá entre aspas! Fazer leitura normal %s então, pois deve ser algum inteiro ou algo assim...
		str[0] = R;
		scanf("%s", &str[1]);
	} else { // EOF
		strcpy(str, "");
	}
}

//função que reseta o registro padrão para novas buscas
void zera_registro(Registro *registro) {
    registro->id = -1;
    registro->idade = -1;
    registro->tamNomeJog = 0;
    registro->tamNacionalidade = 0;
    registro->tamNomeClube = 0;
    
    if (registro->nomeJogador != NULL) {
        free(registro->nomeJogador);
        registro->nomeJogador = NULL;
    }
    if (registro->nacionalidade != NULL) {
        free(registro->nacionalidade);
        registro->nacionalidade = NULL;
    }
    if (registro->nomeClube != NULL) {
        free(registro->nomeClube);
        registro->nomeClube = NULL;
    }
}

//multiplex que verifica qual o campo de pesquisa e altera o valor do campo, futuramente esses valores serão comparados
//para efetuar a busca
int determina_campo(char *campo, Registro *registro) {
    char string[20]; 

    if (strcmp(campo, "id") == 0) {
        scanf("%d", &registro->id);
    } else if (strcmp(campo, "idade") == 0) {
        scanf("%d", &registro->idade);
    } else if (strcmp(campo, "nomeJogador") == 0) {
        scan_quote_string(string);
        AlocaCamposVariados(&registro->nomeJogador, string);
        registro->tamNomeJog = strlen(registro->nomeJogador);
    } else if (strcmp(campo, "nomeClube") == 0) {
        scan_quote_string(string);
        AlocaCamposVariados(&registro->nomeClube, string);
        registro->tamNomeClube = strlen(registro->nomeClube);
    } else if (strcmp(campo, "nacionalidade") == 0) {
        scan_quote_string(string);
        AlocaCamposVariados(&registro->nacionalidade, string);
        registro->tamNacionalidade = strlen(registro->nacionalidade);
    } else {
        return -1;
    }
}

//função que compara os registro, registro padrão e registro atual, a ideia consiste em comparar apenas os campos diferentes do
//registro padrão editados na funçao "determina campo"
int compararRegistros(Registro *registro1, Registro *registro2) {
    if (registro1->id != -1 && registro1->id != registro2->id) {
        return 0;
    }

    if (registro1->idade != -1 && registro1->idade != registro2->idade) {
        return 0;
    }

    if (registro1->tamNomeJog != 0 && strcmp(registro1->nomeJogador, registro2->nomeJogador) != 0) {
        return 0;
    }

    if (registro1->tamNacionalidade != 0 && strcmp(registro1->nacionalidade, registro2->nacionalidade) != 0) {
        return 0;
    }

    if (registro1->tamNomeClube != 0 && strcmp(registro1->nomeClube, registro2->nomeClube) != 0) {
        return 0;
    }

    return 1;
}