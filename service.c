#include "fraction.h"

void simplex_met(int *bazis, struct fractions **mas2, struct fractions *Q, struct fractions *Z) {
	int k, l, i, j;
	struct fractions del, zir;
	zir.nu = 0;
	zir.den = 1;
	
	struct fractions **mas, Z2[m];
	mas = (struct fractions **)malloc(sizeof(struct fractions *) * n);
    i = 0;
    while(i < n) {
        mas[i] = (struct fractions *)malloc(sizeof(struct fractions) * m);
        i++;
    }

	while(!opt(Z)) {
		copy(mas, mas2);
		k = max_mod_Z(Z);
		i = 0;
		while(i < n) {
			if(fractMore(mas[i][k], zir)) Q[i] = fractDiv(mas[i][m - 1], mas[i][k]);
			i++;
		}
		
		l = min_Q(Q);
		print_simplex_table(bazis, mas2, Q, Z, 1);
		printf("A[%d][%d] - main\n\n", l + 1, k + 1);
		
		bazis[l] = k;
		i = 0;
		while(i < n) {
			Q[i].nu = -10;
			Q[i].den = 1;
			i++;
		}
		del = mas[l][k];
		printf("Recalculate: \n");
		i = 0;
		while(i < m) {
			mas2[l][i] = fractDiv(mas2[l][i], del);
			i++;
		}
		copy(mas, mas2);
		i = 0;
		while(i < m){
			Z2[i] = fractSub(fractMul(mas[l][k], Z[i]), fractMul(mas[l][i], Z[k]));
			i++;
		}
		
		copy_one(Z, Z2, m);
		i = 0;
		while(i < n) {
		    j = 0;
			while(j < m) {
				if(i != l) {
					mas2[i][j] = fractSub(fractMul(mas[l][k], mas[i][j]), fractMul(mas[i][k], mas[l][j]));
				}
				j++;
			}
			i++;
		}
		copy(mas, mas2);
		print_simplex_table(bazis, mas2, Q, Z, 1);			
	}
	free(mas);
}

int max_mod_Z(struct fractions *Z){
	struct fractions maxZ = Z[0];
	int maxI = 0, i = 0;
	while(i < m - 1) {
		if(fractMore(fractMulInt(Z[i], -1), maxZ)) {
			maxZ = fractMulInt(Z[i], -1);
			maxI = i;
		}
		i++;
	}
	return maxI;	
}

int min_Q(struct fractions *Q){
	struct fractions minn;
	minn.nu = 10000;
	minn.den = 1;
	struct fractions minQ = minn;
	struct fractions consten;
	consten.nu = -10;
	consten.den = 1;
	int minI = 0, i = 0;
	while(i < n) {
		if(fractLess(Q[i], minQ) && fractNotEq(Q[i], consten)) {
			minQ = Q[i];
			minI = i;
		}
		i++;
	}
	return minI;	
}
int opt(struct fractions *Z){
	struct fractions zir;
	zir.nu = 0;
	zir.den = 1;
	int i = 0;
	while(i < m - 1) {
		if(fractLess(Z[i], zir)) return 0;
		i++;
	}
	return 1;
}

void print_simplex_table(int *bazis, struct fractions **mas, struct fractions *Q, struct fractions *Z, int flag) {
	int i, j;
	struct fractions zir;
	zir.nu = 0;
	zir.den = 1;
	
	printf("bp | ");
	i = 0;
	while(i < m - 1) {
		printf("X%d   ", i + 1);
		i++;
	}
	printf("| B   | ");
	if (flag == 1) printf(" CO \n");
	else printf("\n");
	
	i = 0;
	while(i < m + 3) {
		printf("----");
		i++;
	}
	printf("\n");
	
	i = 0;
    while(i < n) {
    	printf("X%d | ", bazis[i] + 1);
    	j = 0;
    	while(j < m - 1) {
    		 printf("%d/%d ", mas[i][j].nu, mas[i][j].den);
    		 j++;
		}
		printf(" | %d/%d | ", mas[i][m - 1].nu, mas[i][m - 1].den);
		if(flag == 1) {
			if(fractMore(Q[i], zir) || fractEq(Q[i], zir)) 
				printf("%d/%d", Q[i].nu, Q[i].den);
			else printf("-");
		}

		printf("\n");
		i++;
	}
	
	i = 0;
	while(i < m + 3) {
		printf("----");
		i++;
	}
	printf("\n");
	
	printf("Z | ");
	i = 0;

	while(i < m - 1) {
		if(fractEq(Z[i], zir)) printf("%d/%d ", Z[i].nu, Z[i].den);	
		else printf("%d/%d ", Z[i].nu, Z[i].den);
		i++;
	}
	printf(" | %d/%d |   \n", Z[i].nu, Z[i].den);
	if(flag == 2) {
	    i = 0;
		while(i < m + 3) {
			printf("----");
			i++;
		}
		printf("\n");
		printf("Q | ");
		i = 0;
		while(i < n) {
			if(fractMore(Q[i], zir) || fractEq(Q[i], zir)) printf("%d/%d ", Q[i].nu, Q[i].den);
			else printf(" -   ");
			i++;
		}
		printf(" | \n");		
	}
	printf("\n");
}

int rect(struct fractions **mas2, int *C) {
	int i, j = 0, q, f;
	struct fractions zir, one, del;
	zir.nu = 0;
	zir.den = 1;
	one.nu = 1;
	one.den = 1;
	
	struct fractions **mas, **sys;
	mas = (struct fractions **)malloc(sizeof(struct fractions *) * n);
	sys = (struct fractions **)malloc(sizeof(struct fractions *) * n);
    i = 0;
    while(i < n) {
        mas[i] = (struct fractions *)malloc(sizeof(struct fractions) * m);
        sys[i] = (struct fractions *)malloc(sizeof(struct fractions) * m);
    	i++;
    }
    int flag_bazis[n];
    memset(flag_bazis, 0, n * sizeof(int));

	copy(sys, mas2);
	copy(mas, mas2);

	i = 0;
	while(i < n) {
		j = 0;
		while(j < n) {
			if ((fractNotEq(mas[j][C[i]], zir)) && (flag_bazis[j] == 0)){
				if(fractNotEq(mas[j][C[i]], one)) {
					del = mas[j][C[i]];
					q = 0;
					while(q < m) {
						mas[j][q] = fractDiv(mas[j][q], del);
						sys[j][q] = mas[j][q];
						q++;
					}		
				}
				q = 0;
				while(q < n) {
					f = 0;
					while(f < m) {
						if(q != j) {
							sys[q][f] = fractSub(fractMul(mas[j][C[i]], mas[q][f]), fractMul(mas[q][C[i]], mas[j][f]));			
						}
						f++;
					}
					q++;
				}	
				copy(mas, sys);
				flag_bazis[j] = 1;
				break;	
			}
			j++;
		}
		i++;
	}
	copy(mas2, mas);
	free(mas);
	free(sys);
	return 1;
}

void newZ(int *bazis, struct fractions **mas, struct fractions *Z){
	struct fractions Z2[m];	
	int *fre = (int *)malloc(sizeof(int)), size = 1;
	struct fractions zir;
	zir.nu = 0;
	zir.den = 1;
	int k, i = 0, j;
	while(i < m - 1) {
		Z2[i].nu = 0;
		Z2[i].den = 1;
		if(!in_bazis(bazis, i)) {
			fre[size - 1] = i;
			fre = (int *)realloc(fre, sizeof(int) + size);
			size++;
		}
		i++;
	}	
	size--;
	Z2[m - 1].nu = 0;
	Z2[m - 1].den = 1;
	
	i = 0;
	while(i < m - 1) {
		if(fractNotEq(Z[i], zir) && in_bazis(bazis,i)) {
			k = bazis_line(bazis, i);
			j = 0;
			while(j < size) {
				Z2[fre[j]] = fractSub(Z2[fre[j]], fractMul(Z[i], mas[k][fre[j]]));
				j++;
			}
			Z2[m - 1] = fractAdd(Z2[m - 1], fractMul(Z[i], fractMulInt(mas[k][m - 1], (-1))));
		}
		else if(fractNotEq(Z[i], zir)) {
			Z2[i] = fractAdd(Z2[i], Z[i]);
		}
		i++;		
	}
	printf("\n");	
	copy_one(Z, Z2, m);
	free(fre);
}

int bazis_line(int *bazis, int j) {
	int i = 0;
	while(i < n){
		if(j == bazis[i]) return i;
		i++;
	}
}

int in_bazis(int *bazis, int j) {
	int i = 0;
	while(i < n) {
		if(j == bazis[i]) return 1;
		i++;
	}
	return 0;
}

void print(struct fractions **mas) {
    int i = 0, j;
    while(i < n) {
    	j = 0;
    	while(j < m) {
    		printf("%d/%d ", mas[i][j].nu, mas[i][j].den);
    		if(j == m - 2) printf("|");
    		j++;
		}
		printf("\n");
		i++;
	}
	printf("\n");
}

void copy(struct fractions **mas1, struct fractions **mas2) {
	int i = 0, j;
    while(i < n) {
    	j = 0;
    	while(j < m) {
    		mas1[i][j] = mas2[i][j];
    		j++;
		}
		i++;
	}
}

void copy_one(struct fractions *mas1, struct fractions *mas2, int size) {
	int i = 0;
	while(i < size) {
		mas1[i] = mas2[i];
		i++;
	}
}
