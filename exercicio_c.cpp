#include <stdio.h>
#include <iostream>

using namespace std;

struct COMIDA{
	float valor, volume, custoBeni;
};

void qsort(struct COMIDA *vet, int inicio, int fim);

main(){
	int qtdAlunos, i, j, qtdComida;
	FILE *arquivo;

	

	arquivo = fopen("coffee", "rb");
	if(arquivo == NULL)
			printf("Erro, nao foi possivel abrir o arquivo\n");
	else{
		while(!feof(arquivo)){
			fscanf(arquivo, "%d %d", &qtdComida, &qtdAlunos);
			struct COMIDA *comida = new struct COMIDA[qtdComida];
			float *vEstomago = new float[qtdAlunos];
			double *valorTotal = new double[qtdAlunos];
			for(i = 0; i < qtdComida; i++){
				fscanf(arquivo, "%f ", &comida[i].valor);
			}
			for(i = 0; i < qtdComida; i++){
				fscanf(arquivo, "%f ", &comida[i].volume);
				
				comida[i].custoBeni = comida[i].valor / comida[i].volume;
			}
			for(i = 0; i < qtdAlunos; i++){
				fscanf(arquivo, "%f\n", &vEstomago[i]);

				valorTotal[i] = 0;
			}
			qsort(comida, 0, qtdComida-1);
			for(j=0; j<qtdAlunos; j++){
				for(i = qtdComida-1; i >= 0; i--){					
					if(comida[i].volume <= vEstomago[j]){
						valorTotal[j] += comida[i].valor;
						vEstomago[j] -= comida[i].volume;
					}
					else{
						valorTotal[j] += vEstomago[j] * comida[i].custoBeni;
						break;
					}						
				}
				printf("%.4f\n", valorTotal[j]);
			}
				
			delete vEstomago, valorTotal, comida;
		}
	}
	fclose(arquivo);
	system("pause");
}

//quicksort
void qsort(struct COMIDA *vet, int inicio, int fim){
  
	int i = inicio;
	int j = fim;
	struct COMIDA tmp;
	
	if (i >= j)
   {
	    return;
	}
	
	struct COMIDA pivo = vet[(int)(inicio+fim)/2];
	
	while (i < j) 
   {
        
	    while (i<j && vet[i].custoBeni < pivo.custoBeni) { i++; }
		
	    while (i<j && vet[j].custoBeni > pivo.custoBeni) { j--; }
     
	    if (i < j)                           
       {
		    tmp= vet[i];
		    vet[i] = vet[j];
		    vet[j] = tmp;
		    i++;
		    j--;
	    }
	}
	
	if (j < i)
   {
	    tmp.custoBeni = j;
	    j = i;
	    i = tmp.custoBeni;
	}
	
	qsort(vet, inicio, i);
	
	if(i == inicio)
	{
      qsort(vet,i+1,fim);
   }
   else
   {
   
     qsort(vet,i,fim);
   }
}

