#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct cadastro
{
    char nome[10];
    char zona[10];
    int cpf;
    struct cadastro *proximo;
};
typedef struct cadastro cadastro;
//CRIA A LISTA ENCADEADA
void *criar(cadastro *l)
{
    return NULL;
}
//CONTA O TOTAL DE CASOS DE CADA ZONA
int infectados_zona(cadastro *l, char zona[10])
{
    cadastro *ponteiro = l;
    int cont = 0;
    //LAÇO PARA FAZER A CONTAGEM
    while(ponteiro != NULL)
    {
        if(strcmp(zona, ponteiro->zona) == 0)
        {
            cont++;
        }
        ponteiro = ponteiro->proximo;
    }return cont;
}
//DÁ A PREVISÃO DA MELHOR E PIOR HIPÓTESE
void PREVISAO(int casos, int vet[2])
{   
    float taxa = 1.2; //TAXA DE TRANSMISSÃO APROXIMADA
    vet[0] = casos*(pow(taxa, 6));
    vet[1] = casos*(pow(taxa, 14));
}
//INSERE NA LISTA EM ORDEM ALFABÉTICA
cadastro *inserir(cadastro *l, char nome[10], char zona[10], int cpf)
{
    cadastro *novo; 
    novo = (cadastro *) malloc(sizeof(cadastro));
    strcpy(novo->nome, nome);
    strcpy(novo->zona, zona);
    novo->cpf = cpf;
    //VERIFICA SE A LISTA ESTÁ VAZIA
    if (l == NULL)
    {
        novo->proximo = NULL;
        return novo;
    }
    int comp = strcmp(nome, l->nome);//CONDIÇÃO PARA ADICIONAR O ELEMENTO NO INICIO DA LISTA
    if (comp <= 0)
    {
        novo->proximo = l;
        return novo;
    }else //CONDIÇÃO PARA ADICIONAR NO MEIO DA LISTA OU NO FIM
    {   
        
        cadastro *ponteiro = l, *aux;
        while(ponteiro->proximo != NULL && comp > 0)
        {   
            aux = ponteiro;
            ponteiro = ponteiro->proximo;
            comp = strcmp(nome, ponteiro->nome);
        }if(comp <= 0)//MEIO DA LISTA 
            {
                aux->proximo = novo;
                novo->proximo = ponteiro;
            }else //FINAL DA LISTA
            {
                novo->proximo = ponteiro->proximo;
                ponteiro->proximo = novo;
            }return l; 
    }
}
//MOSTRA TODOS OS ELEMENTOS DA LISTA
void listar(cadastro *l)
{
    cadastro *pont = l;
    printf("LISTA:\n");
    while(pont != NULL)
    {   
        printf("\n---------------------------\n");
        printf("Nome: %s\n", pont->nome);
        printf("Zona: %s\n", pont->zona);
        printf("Cpf: %d\n", pont->cpf);
        printf("\n---------------------------\n");
        pont = pont->proximo;
    }
}
//SALVA TODOS OS ELEMENTOS EM UM ARQUIVO .TXT
void salvar_arquivo(cadastro *l, FILE *file)
{
    cadastro *ponteiro = l;
    file  = fopen("Arquivo_covid.txt", "a");
    if(l != NULL)
    {
        while(ponteiro != NULL)
        {   
            fprintf(file, "%s %s %d", ponteiro->nome, ponteiro->zona, ponteiro->cpf );
            ponteiro = ponteiro->proximo;
        }
        printf("\n---------------------------\n");
        printf("Salvo com sucesso!!");
        printf("\n---------------------------\n");
        fclose(file);
    }else
    {   printf("\n----------------------\n");
        printf("Erro ao salvar, a lista está vazia!!");
        printf("\n---------------------------\n");
    }

}
//PESQUISA UM NÓ NA LISTA
void pesquisar(cadastro *l, char nome[10])
{
    cadastro *ponteiro = l;
    int comp = strcmp(ponteiro->nome, nome);
    while(ponteiro != NULL && comp != 0)
    {   
        ponteiro = ponteiro->proximo;
        if(ponteiro != NULL)
        {
            comp = strcmp(ponteiro->nome, nome);
        }
    }
    if(ponteiro == NULL)
    {   
        printf("\n---------------------------\n");
        printf("Pessoa não encontrada!\n");
        printf("\n---------------------------\n");
    }
    else
    {   
        printf("\n---------------------------\n");
        printf("Pessoa encontrada!!\nDados:\n");
        printf("Nome: %s\n", ponteiro->nome); printf("Zona: %s\n", ponteiro->zona);
        printf("Cpf: %d\n", ponteiro->cpf);
        printf("\n---------------------------\n");
    }
}
//REMOVE UM NÓ DA LISTA
cadastro *remover(cadastro *l, char n[10])
{
    if(l !=NULL)
    { 
        cadastro *ponteiro = l, *aux = l;
        int comp = strcmp(ponteiro->nome, n);
        int i = 0;
    
        while(ponteiro->proximo != NULL && comp != 0)
        {   
            if(i>0){aux = aux->proximo;}
            ponteiro = ponteiro->proximo;
            comp = strcmp(ponteiro->nome, n);
            i++;
        }if(i == 0 && comp == 0)
        {   
            l = aux->proximo ;
            free(aux);
            printf("\n---------------------------\n");
            printf("%s removido com sucesso!\n", n);
            printf("\n---------------------------\n");
            return l;
        }
        if(ponteiro->proximo == NULL && comp == 0)
        {
            aux->proximo = NULL;
            free(ponteiro);
            printf("\n---------------------------\n");
            printf("%s removido com sucesso!\n", n);
            printf("\n---------------------------\n");
            return l;
        }
        if(comp == 0)
        {   
            aux->proximo = ponteiro->proximo;
            free(ponteiro);
            printf("\n---------------------------\n");
            printf("%s removido com sucesso!\n", n);
            printf("\n---------------------------\n");
            return l;
        }
        printf("\n---------------------------\n");
        printf("%s não estava na lista!!\n", n);
        printf("\n---------------------------\n");
        return l;
    }else{
        printf("\n---------------------------\n");
        printf("Lista vazia!!");
        printf("\n---------------------------\n");
        return l;
    }
}

int main(void)
{   
    int resposta, cpf;
    char z[4][10] = {"sul", "norte", "oeste", "leste"};
    FILE *file;

    cadastro *lista;
    lista = criar(lista);
    while (resposta != -1)
    {   
        printf("\n--------------------------\n");
        printf("\n ~~~~~~COVID MANAGER~~~~~~");
        printf("\n         BEM VINDO\n");
        printf("--------------------------\n");
        printf("Defina o tipo de usuário\n");
        printf(" 1 - GESTOR\n");
        printf(" 2 - AGENTE DE SAÚDE\n");
        printf("-1 - sair\n");
        scanf("%d", &resposta);
        printf("\n--------------------------\n");
        if(resposta == 1)
        {
            while(resposta != 0)
            {   printf("\n--------------------------\n");
                printf("Bem Vindo, Gestor\n");
                printf("O que deseja saber ?\n");
                printf("1 - PREVISÃO\n");
                printf("2 - LISTAR INFECTADOS\n");
                printf("3 - SALVAR EM UM ARQUIVO\n");
                printf("0 - VOLTAR\n");
                scanf("%d", &resposta);
                printf("\n--------------------------\n");
                switch (resposta)
                {
                case 1:
                    printf("\n--------------------------\n");
                    printf("INFORME A ZONA\n");
                    printf("0 - ZONA SUL\n1 - ZONA NORTE\n2 - ZONA OESTE\n3 - ZONA LESTE\n");
                    scanf("%d", &resposta);
                    printf("\n--------------------------\n");
                    if(resposta > 0 && resposta <5)
                    {
                        int casos = infectados_zona(lista, z[resposta]);
                        int previsao[2];
                        PREVISAO(casos, previsao);
                        printf("\n--------------------------\n");
                        printf("O numero de casos previstos é:\n %d infectados na melhor hipotese\n ", previsao[0]);
                        printf("%d infectados na pior hipotese \n", previsao[1]);
                        printf("\n--------------------------\n");
                    }else
                    {
                        printf("\n----------------------\n");
                        printf("Opção inválida!!!\n");
                        printf("\n----------------------\n");
                    }
                    break;
                case 2:
                    listar(lista);
                    break;
                case 3:
                    salvar_arquivo(lista, file);
                    break;
                case 0:
                    printf("\n----------------------\n");
                    printf("Voltando...\n");
                    printf("\n----------------------\n");
                    break;
                
                default:
                    printf("\n----------------------\n");
                    printf("ENTRADA INVÁLIDA, TENTE NOVAMENTE!\n");
                    printf("\n----------------------\n");
                    break;
                }
            }
        }else if (resposta == 2)
        {   
            char zona[10], nome[10], remove, r = 's';
            int cpf;
            while(resposta!=0)
            {   printf("\n----------------------\n");
                printf("Bem Vindo! \n O que deseja fazer?\n");
                printf("1 - CADASTRAR \n2 - REMOVER PESSOA\n3 - PESQUISAR  \n4 - LISTAR\n0 - VOLTAR\n");
                setbuf(stdin, NULL);
                scanf("%d", &resposta);
                printf("\n----------------------\n");
                switch (resposta)
                {
                case 1:
                    while(r == 's') 

                    {   printf("  ~~NOVO CADASTRO~~"); 
                        printf("\n----------------------\n");
                        printf("Nome: "); scanf("%s", nome);
                        printf("Zona: "); scanf("%s", zona);
                        setbuf(stdin, NULL);
                        printf("cpf: "); scanf("%d", &cpf);
                        lista = inserir(lista, nome, zona, cpf);
                        setbuf(stdin, NULL);
                        printf("Deseja continuar [s|n]?");
                        scanf("%c", &r);
                        printf("\n----------------------\n");
                    }

                    break;
                case 2:
                    printf("\n----------------------\n");
                    printf("Quem você deseja remover: "); scanf("%s", &nome);
                    lista = remover(lista, nome);
                    printf("\n----------------------\n");
                    break;
                case 3:
                    printf("\n----------------------\n");
                    printf("Quem você deseja pesquisar: "); scanf("%s", nome);
                    printf("\n----------------------\n");
                    pesquisar(lista, nome);
                    break;
                case 4:
                    listar(lista);
                    break;
                case 0:
                    printf("\n----------------------\n");
                    printf("Voltando...");
                    printf("\n----------------------\n");
                    break;
                default:
                    printf("\n----------------------\n");
                    printf("Opção invalida!! Tente novamente!!");
                    printf("\n----------------------\n");
                    break;
                }
            }
        }else if(resposta == -1)
        {
        printf("\n----------------------\n");
        printf("Programa encerrado...");
        printf("\n----------------------\n");
        }
        else
        {   printf("\n----------------------\n");
            printf("Opção inválida");
            printf("\n----------------------\n");
        }
    }return 0;
}