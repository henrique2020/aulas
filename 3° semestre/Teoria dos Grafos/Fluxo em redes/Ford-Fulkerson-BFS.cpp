#include <stdio.h>
 #include <conio.h>

#define N 13
#define INF 1000000000

#define max(a,b) (a)>(b)?(a):(b)
#define min(a,b) (a)<(b)?(a):(b)

#define cont(i,j) F[j][i]
#define dir(i,j) (C[i][j]-F[i][j])

int visit[N]={0};
            //S PE SM SB POAE POAS CAXE CAXS FLO CUR SP RJ T
int C[N][N]={{0,15,18,12,0   ,0    ,0   ,0   ,0  ,0  ,0 ,0,0}, // S
             {0,0,  0, 0,15   ,0    ,5   ,0   ,0  ,0  ,0 ,0,0}, // PE
             {0,0,  0, 0,10   ,0    ,5   ,0   ,0  ,0  ,0 ,0,0},// SM
             {0,0,  0, 0,10   ,0    ,3   ,0   ,0  ,0  ,0 ,0,0},// SB
             {0,0,  0, 0,0   ,30    ,10   ,0   ,0  ,0  ,0 ,0,0},// POAE
             {0,0,  0, 0,0   ,0    ,0   ,0   ,3  ,5  ,10 ,10,0},// POAS
             {0,0,  0, 0,0   ,0    ,0   ,20   ,0  ,0  ,0 ,0,0},// CAXE
             {0,0,  0, 0,0   ,0    ,0   ,0   ,3  ,8  ,7 ,7,0},// CAXS
             {0,0,  0, 0,0   ,0    ,0   ,0   ,0  ,0  ,0 ,0,4},// FLO
             {0,0,0,0,0,0,0,0,0,0,0,0,7},// CUR
             {0,0,0,0,0,0,0,0,0,0,0,0,19},// SP
             {0,0,0,0,0,0,0,0,0,0,0,0,15},// RJ
             {0,0,0,0,0,0,0,0,0,0,0,0,0}};// T
             
            //S PE SM SB POAE POAS CAXE CAXS FLO CUR SP RJ T
int F[N][N]={{0,0, 0, 0, 0   ,0    ,0   ,0   ,0  ,0  ,0 ,0,0},
             //{0,15,18, 12  ,0    ,0   ,0   ,0  ,0  ,0 ,0,0}, // matriz de fluxos
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},

             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0},
             {0,0,0,0,0,0,0,0,0,0,0,0,0}};

int pai[N];
int fila[N];
int menor[N];

int bfs(int s,int t,int numvert)
{
	int TD=0,PA=1,i;
	visit[s]=1;
	fila[0]=s;
	menor[s]=INF;
	while (visit[t]==0 && TD!=PA)
		{
		int v=fila[TD++];
		for (i=0;i<numvert;i++)
			if (visit[i]==0 && (dir(v,i) || cont(v,i)))
				{
				visit[i]=1;
				pai[i]=v;
				menor[i]=min (menor[v], max(dir(v,i),cont(v,i)));
				fila[PA++]=i;
				}
		}
	if (visit[t]==0) return 0;
	int minval=menor[t];
	int aux=t;
	while (aux!=s)
		{
		int v=pai[aux];
		if (dir(v,aux)>=minval)
			F[v][aux]+=minval;
		else 
		   	F[aux][v]-=minval;
		aux=v;	
		}
	return 1;      
}

int main()	
{
while (1)
   {
   int ftot=0,i;
   for (i=0;i<N;i++){
        ftot+=F[0][i];
        visit[i] = 0;
   }
   	
   printf("\nFluxo atual é %d\n",ftot);
   for (i=0;i<13;i++)
      {
      int j;
	  for (j=0;j<13;j++)
          printf("%2d ",F[i][j]);
       printf("\n");
	  }
   if (!bfs(0,12,13)) 
      {
      printf("Nao ha caminho aumentante\n");
      break;
      }
   }
}
	   
