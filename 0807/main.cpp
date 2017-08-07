#include <stdio.h>

#define ROUTE 0
#define WALL 1
#define SHORTEST_ROUTE 4
#define START 2
#define GOAL 3

//map�� �� ��ȹ�� Node�� �����. �� ���� 100���� ���������.
typedef struct Node{
	int type;//������ �������
	int length;//����������κ����� �Ÿ���?
}Node;

int map[100][100];
Node nop[100][100];//�迭 �ּҴ� �� �ּҿ� ����.
int min = 9999;//9999
void FindRoute(int size,int x,int y)//DFS������� ã�´�.
{
	if(nop[x][y].length>=min)//ã�� ���� ���̰� ã�� �ִܰŸ����� ��ٸ� �� ��θ� ����Ѵ�.(�׸���, ���� ���� ���� ã�� �ʴ´�.)
		return ;

	if(nop[	x+1][y].type!=WALL){
		nop[x+1][y].length=nop[x][y].length+1;
		FindRoute(size,x,y);
	}
}

int main()
{
	FILE *file = fopen("map.txt", "rt");
	if(file == NULL) {
		printf("������ �� �� �����ϴ�.\n");
		return 0;
	}

	//map�� ����, ������ ĭ�� ������ ��ŸƮ ��������,
	for(int i = 0; i < 3; ++i)
	{
		int n;
		fscanf(file, "%d", &n);
		for(int y = 0; y < n; ++y)
		{
			for(int x = 0; x < n; ++x)
				fscanf(file, "%d", &map[y][x]);
		}

		//map������ �� node�迭�� map�� Ÿ���� ����
		for(int i = 0; i < 3; ++i){
			for(int y = 0; y < n; ++y)
			{
				for(int x = 0; x < n; ++x)
					nop[y][x].type = map[y][x];
			}
		
		}
			//�ִܰ�θ� ã�� map�� �˸�
			nop[0][0].type = START;
			nop[0][0].length=0;
			FindRoute(n,0,0);

			//�̰��� ���� �˸���, ��� ������
			printf("���ѤѤѤѤѤѤѤѤѤѤѦ�\n");
			printf("��Map %d Shortest Route!!��\n", i + 1);
			printf("���ѤѤѤѤѤѤѤѤѤѤѦ�\n");
		

			//�̰��� �߰��� �� ���� ������ �ѷ��δ� ��
			for(int y = 0; y < n; ++y)
			{
				if(y==0){
					for(int a=0;a<n*1.3-2;a++){
						if(a==0)
							printf("        ");
						printf("��");
					}
					printf("\n");
				}
				printf("        ��");

				//map�� ����Ǿ��ִ� type�� ���� ���� ���
				for(int x = 0; x < n; ++x)
				{
					int type = map[y][x];

					switch (type){
					case ROUTE : //��ζ�� �վ����
						printf(" ");
						break;
					case SHORTEST_ROUTE : //ã�� �ִܰ�δ� @�� ǥ���ϰ�
						printf("@"); 
						break;
					case WALL : //�ش� map�� ���̶�� X ǥ��
						printf("X");
						break;
					case START : //���������� S�� ǥ��
						printf("S");
						break;
					default: printf("E");//���������� E�� ǥ��
					}
				}
				printf("��\n");

				//�̰��� ����, �� �ϴܺθ� �ѷ��δ� ����
				if(y==n-1){
					for(int a=0;a<n*1.3-2;a++){
						if(a==0)
							printf("        ");
						printf("��");
					}
					printf("\n");
				}
			}
		}

		//��� ���� ����ϰ� ������ ����
		fclose(file);
		return 0;
	}