#include <stdio.h>
#include <iostream>

using namespace std;

#define MAX 105
struct INFO{
	char dia[4];
	int hora1, hora2, carrasco, carrasco_optimus;
	bool escolhido;
}INFO;


main()
{
	char nomearquivo[20];
	int total, i, j, aux, k, idx;
	bool invalido = true, ok;
	FILE *arquivo;
	

	printf("Digite o nome do arquivo\n"); 
	while(strcmp(nomearquivo, "0") != 0){
		gets(nomearquivo); 
		arquivo = fopen(nomearquivo, "rb"); 
		if(arquivo == NULL)
				printf("Erro, nao foi possivel abrir o arquivo\n");
		else{
			fscanf(arquivo, "%d", &total);
			struct INFO *info = new struct INFO[total];
			aux = 1;
			struct INFO *saida = new struct INFO[total];
			for(i=0; i < total; i++){
				fscanf(arquivo,"%s %d %d %d\n", info[i].dia, &info[i].hora1, &info[i].hora2, &info[i].carrasco);
				info[i].carrasco_optimus = info[i].carrasco/(info[i].hora2-info[i].hora1);
				info[i].escolhido = false;
			}
			saida[0] = info[0];
			aux = 1;
			for(i=1; i < total; i++){
				for(j = 0; j < aux; j++){
					if(strcmp(info[i].dia, saida[j].dia) != 0)
						invalido = false;
					else if(info[i].hora2 <= saida[j].hora1 || info[i].hora1 >= saida[j].hora2)
						invalido = false;
					else if(info[i].carrasco_optimus > saida[j].carrasco_optimus){
						invalido = true;
						saida[j] = info[i];
						info[i].escolhido = true;
						break;
					}
					else{
						invalido = true;
						break;					
					}
				}
				if(!invalido){
					saida[aux] = info[i];
					aux++;
					invalido = true;
					info[i].escolhido= true;
				}		
								
			}
			for(j = 0; j < aux; j++){
				for(i = j+1; i < aux; i++){
					if(strcmp(saida[i].dia, saida[j].dia) == 0 && (saida[j].hora1 == saida[i].hora1 && saida[j].hora2 == saida[i].hora2)){
						if(saida[j].carrasco_optimus <= saida[i].carrasco_optimus)
							saida[j].carrasco = 0;
					}
				}
			}


			k = 0;		
			j = 0;
			for(j = 0; j < aux; j++)
					k += saida[j].carrasco;		
			cout<<k<<endl;	
		}
		fclose(arquivo);
		printf("Digite o nome do arquivo\n"); 
	}
	system("pause");
}
