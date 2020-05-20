#include "fraction.h"

int main() {
    FILE *f = fopen("file.txt", "r");

    int k, i, j;
    fscanf(f, "%d", &n);
    fscanf(f, "%d", &m);
    m++;
    
    int bazis[n];
    struct fractions **mas, Z[m], Q[n];
    mas = (struct fractions **)malloc(sizeof(struct fractions *) * n);
    i = 0;
    while(i < n) {
        mas[i] = (struct fractions *)malloc(sizeof(struct fractions) * m);
        i++;
    }
    
    i = 0;
    while(i < n) {
    	fscanf(f, "%d", &k);
		bazis[i] = k-1;
		Q[i].nu = -10;
		Q[i].den = 1;
		i++;
	}
	
	printf("Z = ");
	i = 0;
	while(i < m - 1) {
    	fscanf(f, "%d", &k);
		Z[i].nu = k * (-1);
		Z[i].den = 1;

		printf("(%d)*X%d +", k, i + 1);
		i++;

	}
	printf("\b \n");

	Z[m - 1].nu = 0;
	Z[m - 1].den = 1;
	
	i = 0;
    while(i < n) {
    	j = 0;
    	while(j < m) {
    		fscanf(f, "%d", &k);
    		mas[i][j].nu = k; 
    		mas[i][j].den = 1;
    		j++;
		}
		i++;
	}
	printf("\n");
	
	printf("Source mas:\n");
	print(mas);
	rect(mas, bazis);
	newZ(bazis, mas, Z);
	printf("With basis ");
	
	i = 0;
	while(i < n) {
		printf("x%d", bazis[i] + 1);
		i++;
	}
	printf(":\n");
	print(mas);
	printf("New Z = ");
	
	i = 0;
	while(i < m - 1) {
		printf("(%d/%d)*x%d +", Z[i].nu, Z[i].den, i + 1);
		i++;
	}
	printf("\b \n\n");

	printf("Simplex method:\n");
	print_simplex_table(bazis, mas, Q, Z, 1);
	simplex_met(bazis, mas, Q, Z);
	
	printf("Z = %d/%d\n", Z[m - 1].nu * (-1), Z[m - 1].den);
	fclose(f);
	free(mas);
}
