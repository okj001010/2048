#include <stdio.h> // 원래 쓰는거 
#include <stdlib.h> // 랜덤함수 쓰기 위해서 
#include <string.h> //strcpy 쓰기 위해서 
#include <time.h> // time 쓰기 위해서 
#include <conio.h> //getch 쓰기 위해서 
#include <windows.h>

int arr[4][4]={}, arr2[4][4]={}; // 출력할 배열이다. 
int checkarr[4][4]={}; // 나중에 위의 배열과 비교해서 실행할건지 안 할건지 결정하게 해주는 배열이다. 
char spell; // 어디로 움직일지 정해주는 변수다. 
int score=0, stage=1, bigscore=0, c_num=0;
char str[20];
int scores[5]={}, stages[5]={};
int undoarr1[4][4]={}, undoarr2[4][4]={}, undoarr3[4][4]={};
int redoarr1[4][4]={}, redoarr2[4][4]={}, redoarr3[4][4]={};
int score0=0, checkscore=0, score1=0, score2=0, score3=0;
char strs[5][20];
int undo_cnt=0, undo_num=0;
int unlockscan=1;
int AIarr[4][4]={};

int checkpossible(void) // 이 함수는 1단계 코드이다. 더 이상 움직일 수 없어서 끝나는 상황일 때 game over를 출력하기 위해서 이 함수를 다시 가져왔다. 
{ // 1단계 코드에 주석처리가 되어 있으므로 자세한 설명은 생략한다. 
	int i, j, yes=0;
	for(i=0;i<4;i++) // 0이 있으면 yes를 증가시킨다. 
	{
		for(j=0;j<4;j++) 
		{
			if(arr[i][j]==0) 
			{
				yes++;
				break; 
			}
		}
		if(arr[i][j]==0) break; 
	}
	
	for(i=0;i<4;i++) // 좌우로 움직일 수 있으면 yes를 증가시킨다. 
	{
		for(j=0;j<3;j++)
		{
			if(arr[i][j]==arr[i][j+1])
			{
				yes++;
				break;
			}
		}
		if(arr[i][j]==arr[i][j+1]) break;
	}
	
	for(j=0;j<4;j++) // 상하로 움직일 수 있으면 yes를 증가시킨다. 
	{
		for(i=0;i<3;i++)
		{
			if(arr[i][j]==arr[i+1][j])
			{
				yes++;
				break;
			}
		}
		if(arr[i][j]==arr[i+1][j]) break;
	}
	if(yes>0) return 1; // 만약에 yes가 0보다 크다면 움직일 수 있다는 것을 의미한다. 이때는 1을 반환한다. 
	else return 0; // 만약에 yes가 0보다 크지 않다면(yes가 0이라면) 0을 반환한다. 
}

int check(void) // 이 함수는 밀기 전과 민 후의 값을 비교하는 함수이다. 
{
	int i, j, cnt=0; // cnt는 개수를 세는 변수이다. 
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			if(checkarr[i][j]==arr[i][j]) cnt++; // 밑에서 밀기 전에 checkarr에 arr를 대입할 것이다. 민 후에 arr값과 checkarr값이 같은 칸의 개수를 센다. 
	}
	if(cnt==16) return 0; // 같은 칸의 개수가 16개 즉, 모두 같다면 변동이 없다는 뜻이다. 이때는 0을 반환한다. 
	else return 1; // 변한게 하나라도 있으면 1을 반환한다. 
}

void firstrandom(void) //처음에 랜덤으로 2를 두개 생성하는 함수이다. 
{
	int i, j, num1, num2, num3 = 4, num4 = 4; // num1은 2가 생기는 x좌표, num2는 2가 생기는 y좌표, num3은 다른 2가 생기는 x좌표, num4는 다른 2가 생기는 y좌표이다. 
	for(i=0;i<4;i++) // 먼저 arr를 모두 0으로 초기화시킨다. 
	{
		for(j=0;j<4;j++)
			arr[i][j] = 0;
	}
	srand((int)time(NULL)); // 시간은 계속 바뀌므로 time을 써서 무작위로 뽑는다. 
	num1 = rand()%4; // 랜덤으로 x좌표를 0에서 3 사이에 뽑고 
	num2 = rand()%4; // 같은 방법으로 y좌표도 뽑는다. 
	arr[num1][num2]=2; // 그래서 정해진 좌표에 2를 대입한다. 
	while(1) // num3, num4도 같은 방법으로 뽑으면 될 것 같지만 같은 장소에 생길 확률이 있기 때문에 다른 방법으로 해야 한다. 
	{
		num3 = rand()%4; // 일단 뽑고 본다. 
		num4 = rand()%4;
		if(!(num3==num1&&num4==num2)) // 둘 중 다른게 있다면 while문을 빠져나온다. 둘 다 같다면 다를 때까지 while문을 계속 돌아야 한다. 
			break;
	}
	arr[num3][num4]=2; // 그렇게 나온 좌표에 2를 대입한다. 
} // 이렇게 되면 랜덤으로 2개의 장소에 2를 출력할 수 있다. 

void random(void)
{
	int i, j, k, num1, num2, l=0, a[16]={};
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			if(arr[i][j]==0)
			{
				a[l] = 10*i+j;
				l++;
			}
		}
	}
	srand((int)time(NULL));
	num1 = a[rand()%l]/10;
	num2 = a[rand()%l]%10;
	k = rand()%5;
	if(k<4) arr[num1][num2] = 2;
	else arr[num1][num2] =4;
}

void removezero(void) // 이 함수는 3단계 코드에도 있는 함수이므로 자세한 설명은 생략한다. 
{
	int i, j, k;
	for(j=0;j<4;j++)
	{
		for(i=0;i<4;i++)
		{
			if(arr[i][j]==0) // 0이 있으면 
			{
				for(k=i;k<3;k++)
				{
					arr[k][j]=arr[k+1][j]; // 위의 값에 아래의 값을 넣고 
					arr[k+1][j]=0; // 아래의 값에 0을 대입한다. 그러면 나중에 다시 0을 또 발견해서 아래 있는 모든 수를 다 끌어올릴 수 있다. 
				}
			}
		}
	}
}

void plus(void) // 이 함수도 3단계 코드에 있는데 바뀐 점이라면 removezero를 뺐다는 점이다. 나머지는 모두 같으므로 자세한 설명은 생략한다. 
{
	int i, j; 
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			if(arr[i][j]==arr[i+1][j]||arr[i+1][j]==0) //위 아래의 값이 같거나 아래의 값이 0이면 실행한다. 
			{
				arr[i][j]+=arr[i+1][j]; // 위의 값에 아래의 값과 더한 값을 대입하고 
				score+=(2*arr[i+1][j]);
				arr[i+1][j]=0; // 아래 값을 0으로 초기화시킨다. 이러면 if문이 다시 실행되므로 아래의 수를 모두 끌어올릴 수 있다. 
			}
		}
	}
}

void push(void) // 최종적으로 미는 함수이다. 
{
	removezero(); // 여기서 아까 removezero 함수의 문제점을 해결한다. 
	removezero(); // 그냥 두번 쓴다. 
	plus(); // 0을 다 없앤 후에 더하고 
	removezero(); // (2, 2, 2, 2) 같은 경우는 더하면 (4, 0, 4, 0)이 되므로 다시 0을 다 없애준다. 
}

void rotate(void) // 위의 두개의 함수는 모두 위로 미는 내용이었다. 그런데 위 아래 왼쪽 오른쪽 모두 되야 하므로 회전시킨 다음 더하고 다시 회전시키는 방법으로 했다. 
{
	int i, j, tmp;
	for(i=0;i<2;i++) // 사실 이 코드는 선생님이 1단계 코드 답지로 올려놓은 내용을 참고했다. 
	{
		for(j=i;j<3-i;j++)
		{
			tmp = arr[i][j];
			arr[i][j] = arr[3-j][i];
			arr[3-j][i] = arr[3-i][3-j];
			arr[3-i][3-j] = arr[j][3-i];
			arr[j][3-i] = tmp;
		}
	}
}

void push_all(void) // 모든 방향으로 미는 함수이다. 
{
	int i, j;
	for(i=0;i<4;i++) // 전에 언급한 check 함수에서 밀기 전에 checkarr에 arr를 대입한다고 했는데 그 과정이다. 
	{
		for(j=0;j<4;j++)
		{
			checkarr[i][j]=arr[i][j];
		}
	}
	checkscore = score;
	switch(spell) // spell값에 따라서 얼마나 회전시킬지 다르므로 경우를 나눈다. 
	{
		case 'W':
		case 'w':  //위로 움직이면 그냥 그대로 
			push();
			break;
		case 'A':
		case 'a':  //왼쪽으로 움직이면 시계방향으로 한번 회전하고 더한 후에 3번 회전한다. 
			rotate();
			push();
			rotate();
			rotate();
			rotate();
			break;
		case 'S':
		case 's':  // 두번 회전하고 더한 후에 두번 회전한다. 
			rotate();
			rotate();
			push();
			rotate();
			rotate();
			break;
		case 'D':
		case 'd':  // 3번 회전하고 더한 후에 두번 회전한다. 
			rotate();
			rotate();
			rotate();
			push();
			rotate();
			break;
	}
}

void print(void) // 단순히 출력하는 함수이다. 
{
	int i, j;
	system("cls"); // 아래에 계속 출력되지 않고 그 자리에서 계속 바뀌어야 하므로 다 없애버리는 작업이다. 
	printf("ID? %s\n", str);
	printf("Score:%d Stage:%d Biggest Score:%d\n", score, stage, bigscore);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			printf("%-4d ", arr[i][j]); // 왼쪽에 정렬한다.
		printf("\n"); // 깔끔해 보이기 위해서 엔터는 두번 쓴다. 
		printf("\n");
	}
}

void snailchance(void)
{
	int i, j;
	for(i=0;i<4;i++)
		arr2[0][i] = arr[0][i];
	arr2[1][3] = arr[1][0];
	arr2[2][3] = arr[1][1];
	arr2[3][3] = arr[1][2];
	arr2[3][2] = arr[1][3];
	arr2[3][1] = arr[2][0];
	arr2[3][0] = arr[2][1];
	arr2[2][0] = arr[2][2];
	arr2[1][0] = arr[2][3];
	arr2[1][1] = arr[3][0];
	arr2[1][2] = arr[3][1];
	arr2[2][2] = arr[3][2];
	arr2[2][1] = arr[3][3];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		{
			arr[i][j] = arr2[i][j];
		}
	}
	c_num++;
}

void sortmine(void)
{
	int i=4, j;
	while(i!=-1)
	{
		if(score>scores[i]) i--;
		else break;
	}
	if(i!=4)
	{
		for(j=4;j>i+1;j--)
		{
			scores[j] = scores[j-1];
			stages[j] = stages[j-1];
			strcpy(strs[j], strs[j-1]);
		}
		scores[i+1] = score;
		stages[i+1] = stage;
		strcpy(strs[i+1], str);
	}
	bigscore = scores[0];
}

void printall(void)
{
	int i;
	for(i=0;i<5;i++)
		printf("%d %s %d %d\n", i+1, strs[i], scores[i], stages[i]);
	printf("0 %s %d %d", str, score, stage);
}

void readyundo(void)
{
	int i, j;
	score0 = score;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			undoarr3[i][j] = undoarr2[i][j];
	}
	score3 = score2;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			undoarr2[i][j] = undoarr1[i][j];
	}
	score2 = score1;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			undoarr1[i][j] = checkarr[i][j];
	}
	score1 = checkscore;
}

void undo(void)
{
	int i, j;
	switch(undo_cnt)
	{
		case 1:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					redoarr1[i][j] = arr[i][j];
					arr[i][j] = undoarr1[i][j];
				}
			}
			score = score1;
			break;
		case 2:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					redoarr2[i][j] = arr[i][j];
					arr[i][j] = undoarr2[i][j];
				}
			}
			score = score2;
			break;
		case 3:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
				{
					redoarr3[i][j] = arr[i][j];
					arr[i][j] = undoarr3[i][j];
				}
			}
			score = score3;
			break;
	}
	undo_num++;
	if(undo_cnt<4) stage--;
}

void redo(void)
{
	int i, j;
	switch(undo_cnt)
	{
		case 1:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
					arr[i][j] = redoarr1[i][j];
			}
			score = score0;
			stage++;
			break;
		case 2:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
					arr[i][j] = redoarr2[i][j];
			}
			undo_cnt--;
			score = score1;
			stage++;
			break;
		case 3:
			for(i=0;i<4;i++)
			{
				for(j=0;j<4;j++)
					arr[i][j] = redoarr3[i][j];
			}
			undo_cnt--;
			score = score2;
			stage++;
			break;
		}
}

int predict(char gspell1, char gspell2)
{
	int i, j, AIscore, tempscore;
	spell=gspell1;
	tempscore = score;
	push_all();
	spell=gspell2;
	push_all();
	AIscore = score;
	score = tempscore;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			arr[i][j] = AIarr[i][j];
	}
	return AIscore-tempscore;
}

void AI(void)
{
	int i, j, max=0;
	int spells[16];
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			AIarr[i][j] = arr[i][j];
	}
	spells[0] = predict('W','W');
	spells[1] = predict('W','A');
	spells[2] = predict('W','D');
	spells[3] = predict('W','S');
	spells[4] = predict('A','W');
	spells[5] = predict('A','A');
	spells[6] = predict('A','D');
	spells[7] = predict('A','S');
	spells[8] = predict('D','W');
	spells[9] = predict('D','A');
	spells[10] = predict('D','D');
	spells[11] = predict('D','S');
	spells[12] = predict('S','W');
	spells[13] = predict('S','A');
	spells[14] = predict('S','D');
	spells[15] = predict('S','S');
	for(i=0;i<16;i++)
	{
		if(max < spells[i])
			max = spells[i];
	}
	if((max==spells[4])||(max==spells[5])||(max==spells[6])||(max==spells[7]))
		spell = 'A';
	else if((max==spells[12])||(max==spells[13])||(max==spells[14])||(max==spells[15]))
		spell = 'S';
	else if((max==spells[8])||(max==spells[9])||(max==spells[10])||(max==spells[11]))
		spell = 'D';
	else
		spell = 'W';
	push_all();
	random();
	stage++;
	print();
	printf("%c", spell);
}

int main()
{
	printf("ID? ");
	scanf("%s", str);
	firstrandom(); // 일단 랜덤으로 2개의 장소에 2를 대입하고 
	print(); // 출력한다. 
	while(1) // 움직일 수 있는 상황이라면 
	{
		if(unlockscan)
			spell = getch(); // 방향키를 입력받고 
		if((spell=='W')||(spell=='w')||(spell=='A')||(spell=='a')||(spell=='D')||(spell=='d')||(spell=='S')||(spell=='s'))
		{
			undo_cnt=0;
			push_all(); // 그 방향으로 한번 민 다음에 
			if(check()) // 밀기 전과 같은지 확인한다. 만약 같지 않다면 
			{
				random(); // 0 자리에 랜덤으로 2 또는 4를 넣고 
				stage++;
				print(); // 출력한다. 
				readyundo();
			}
		}
		else if((spell=='N')||(spell=='n')) 
		{
			undo_num=0;
			undo_cnt=0;
			c_num = 0;
			sortmine();
			system("cls");
			printf("ID? ");
			scanf("%s", str);
			score = 0, stage = 1;
			firstrandom(); // N을 입력하면 초기화 시켜야 하므로 firstrandom에서 랜덤으로 자리를 고르고 
			print(); // 출력한다.  
		}
		else if((spell=='C')||(spell=='c'))
		{
			undo_cnt=0;
			if(c_num!=3)
			{
				snailchance();
				system("cls");
				print();
				readyundo();
			}
		}
		else if((spell=='U')||(spell=='u'))
		{
			if(undo_num<4)
			{
				undo_cnt++;
				undo();
				system("cls");
				print();
			}
		}
		else if((spell=='R')||(spell=='r'))
		{
			redo();
			system("cls");
			print();
		}
		else if((spell=='P')||(spell=='p'))
		{
			unlockscan=0;
			AI();
			Sleep(50);
			spell = 'P';
			if(!checkpossible())
				spell='O';
		}
		else if(spell='O')
		{
			unlockscan=1;
			printf("\n");
			scanf("%c", &spell);
		}
		else if((spell=='X')||(spell=='x'))
		{
			sortmine();
			break;
		}
	}
	printall();
}
