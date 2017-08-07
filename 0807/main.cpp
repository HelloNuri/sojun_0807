#include <stdio.h>

#define ROUTE 0
#define WALL 1
#define SHORTEST_ROUTE 4
#define START 2
#define GOAL 3

//map의 한 구획당 Node를 만든다. 즉 노드는 100개가 만들어진다.
typedef struct Node{
	int type;//벽인지 통로인지
	int length;//출발지점으로부터의 거리가?
}Node;

int map[100][100];
Node nop[100][100];//배열 주소는 맵 주소와 같다.
int min = 9999;//9999
void FindRoute(int size,int x,int y)//DFS방식으로 찾는다.
{
	if(nop[x][y].length>=min)//찾은 길의 길이가 찾은 최단거리보다 길다면 그 경로를 취소한다.(그리고, 여러 개의 길을 찾지 않는다.)
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
		printf("파일을 열 수 없습니다.\n");
		return 0;
	}

	//map을 만듦, 각각의 칸이 벽인지 스타트 지점인지,
	for(int i = 0; i < 3; ++i)
	{
		int n;
		fscanf(file, "%d", &n);
		for(int y = 0; y < n; ++y)
		{
			for(int x = 0; x < n; ++x)
				fscanf(file, "%d", &map[y][x]);
		}

		//map역할을 할 node배열에 map의 타입을 복사
		for(int i = 0; i < 3; ++i){
			for(int y = 0; y < n; ++y)
			{
				for(int x = 0; x < n; ++x)
					nop[y][x].type = map[y][x];
			}
		
		}
			//최단경로를 찾고 map에 알림
			nop[0][0].type = START;
			nop[0][0].length=0;
			FindRoute(n,0,0);

			//미관상 만든 알림판, 없어도 무방함
			printf("┌ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┐\n");
			printf("ㅣMap %d Shortest Route!!ㅣ\n", i + 1);
			printf("└ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ┘\n");
		

			//미관상 추가한 맵 위와 양쪽을 둘러싸는 벽
			for(int y = 0; y < n; ++y)
			{
				if(y==0){
					for(int a=0;a<n*1.3-2;a++){
						if(a==0)
							printf("        ");
						printf("ㅁ");
					}
					printf("\n");
				}
				printf("        ㅁ");

				//map에 저장되어있는 type에 따라 맵을 출력
				for(int x = 0; x < n; ++x)
				{
					int type = map[y][x];

					switch (type){
					case ROUTE : //통로라면 뚫어놓고
						printf(" ");
						break;
					case SHORTEST_ROUTE : //찾은 최단경로는 @로 표시하고
						printf("@"); 
						break;
					case WALL : //해당 map이 벽이라면 X 표시
						printf("X");
						break;
					case START : //시작지점은 S로 표시
						printf("S");
						break;
					default: printf("E");//도착지점은 E로 표시
					}
				}
				printf("ㅁ\n");

				//미관상 만든, 맵 하단부를 둘러싸는 발판
				if(y==n-1){
					for(int a=0;a<n*1.3-2;a++){
						if(a==0)
							printf("        ");
						printf("ㅁ");
					}
					printf("\n");
				}
			}
		}

		//모든 맵을 출력하고 파일을 종료
		fclose(file);
		return 0;
	}