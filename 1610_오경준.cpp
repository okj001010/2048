#include <stdio.h> // ���� ���°� 
#include <stdlib.h> // �����Լ� ���� ���ؼ� 
#include <string.h> //strcpy ���� ���ؼ� 
#include <time.h> // time ���� ���ؼ� 
#include <conio.h> //getch ���� ���ؼ� 
#include <windows.h>

int arr[4][4]={}, arr2[4][4]={}; // ����� �迭�̴�. 
int checkarr[4][4]={}; // ���߿� ���� �迭�� ���ؼ� �����Ұ��� �� �Ұ��� �����ϰ� ���ִ� �迭�̴�. 
char spell; // ���� �������� �����ִ� ������. 
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

int checkpossible(void) // �� �Լ��� 1�ܰ� �ڵ��̴�. �� �̻� ������ �� ��� ������ ��Ȳ�� �� game over�� ����ϱ� ���ؼ� �� �Լ��� �ٽ� �����Դ�. 
{ // 1�ܰ� �ڵ忡 �ּ�ó���� �Ǿ� �����Ƿ� �ڼ��� ������ �����Ѵ�. 
	int i, j, yes=0;
	for(i=0;i<4;i++) // 0�� ������ yes�� ������Ų��. 
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
	
	for(i=0;i<4;i++) // �¿�� ������ �� ������ yes�� ������Ų��. 
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
	
	for(j=0;j<4;j++) // ���Ϸ� ������ �� ������ yes�� ������Ų��. 
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
	if(yes>0) return 1; // ���࿡ yes�� 0���� ũ�ٸ� ������ �� �ִٴ� ���� �ǹ��Ѵ�. �̶��� 1�� ��ȯ�Ѵ�. 
	else return 0; // ���࿡ yes�� 0���� ũ�� �ʴٸ�(yes�� 0�̶��) 0�� ��ȯ�Ѵ�. 
}

int check(void) // �� �Լ��� �б� ���� �� ���� ���� ���ϴ� �Լ��̴�. 
{
	int i, j, cnt=0; // cnt�� ������ ���� �����̴�. 
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			if(checkarr[i][j]==arr[i][j]) cnt++; // �ؿ��� �б� ���� checkarr�� arr�� ������ ���̴�. �� �Ŀ� arr���� checkarr���� ���� ĭ�� ������ ����. 
	}
	if(cnt==16) return 0; // ���� ĭ�� ������ 16�� ��, ��� ���ٸ� ������ ���ٴ� ���̴�. �̶��� 0�� ��ȯ�Ѵ�. 
	else return 1; // ���Ѱ� �ϳ��� ������ 1�� ��ȯ�Ѵ�. 
}

void firstrandom(void) //ó���� �������� 2�� �ΰ� �����ϴ� �Լ��̴�. 
{
	int i, j, num1, num2, num3 = 4, num4 = 4; // num1�� 2�� ����� x��ǥ, num2�� 2�� ����� y��ǥ, num3�� �ٸ� 2�� ����� x��ǥ, num4�� �ٸ� 2�� ����� y��ǥ�̴�. 
	for(i=0;i<4;i++) // ���� arr�� ��� 0���� �ʱ�ȭ��Ų��. 
	{
		for(j=0;j<4;j++)
			arr[i][j] = 0;
	}
	srand((int)time(NULL)); // �ð��� ��� �ٲ�Ƿ� time�� �Ἥ �������� �̴´�. 
	num1 = rand()%4; // �������� x��ǥ�� 0���� 3 ���̿� �̰� 
	num2 = rand()%4; // ���� ������� y��ǥ�� �̴´�. 
	arr[num1][num2]=2; // �׷��� ������ ��ǥ�� 2�� �����Ѵ�. 
	while(1) // num3, num4�� ���� ������� ������ �� �� ������ ���� ��ҿ� ���� Ȯ���� �ֱ� ������ �ٸ� ������� �ؾ� �Ѵ�. 
	{
		num3 = rand()%4; // �ϴ� �̰� ����. 
		num4 = rand()%4;
		if(!(num3==num1&&num4==num2)) // �� �� �ٸ��� �ִٸ� while���� �������´�. �� �� ���ٸ� �ٸ� ������ while���� ��� ���ƾ� �Ѵ�. 
			break;
	}
	arr[num3][num4]=2; // �׷��� ���� ��ǥ�� 2�� �����Ѵ�. 
} // �̷��� �Ǹ� �������� 2���� ��ҿ� 2�� ����� �� �ִ�. 

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

void removezero(void) // �� �Լ��� 3�ܰ� �ڵ忡�� �ִ� �Լ��̹Ƿ� �ڼ��� ������ �����Ѵ�. 
{
	int i, j, k;
	for(j=0;j<4;j++)
	{
		for(i=0;i<4;i++)
		{
			if(arr[i][j]==0) // 0�� ������ 
			{
				for(k=i;k<3;k++)
				{
					arr[k][j]=arr[k+1][j]; // ���� ���� �Ʒ��� ���� �ְ� 
					arr[k+1][j]=0; // �Ʒ��� ���� 0�� �����Ѵ�. �׷��� ���߿� �ٽ� 0�� �� �߰��ؼ� �Ʒ� �ִ� ��� ���� �� ����ø� �� �ִ�. 
				}
			}
		}
	}
}

void plus(void) // �� �Լ��� 3�ܰ� �ڵ忡 �ִµ� �ٲ� ���̶�� removezero�� ���ٴ� ���̴�. �������� ��� �����Ƿ� �ڼ��� ������ �����Ѵ�. 
{
	int i, j; 
	for(j=0;j<4;j++)
	{
		for(i=0;i<3;i++)
		{
			if(arr[i][j]==arr[i+1][j]||arr[i+1][j]==0) //�� �Ʒ��� ���� ���ų� �Ʒ��� ���� 0�̸� �����Ѵ�. 
			{
				arr[i][j]+=arr[i+1][j]; // ���� ���� �Ʒ��� ���� ���� ���� �����ϰ� 
				score+=(2*arr[i+1][j]);
				arr[i+1][j]=0; // �Ʒ� ���� 0���� �ʱ�ȭ��Ų��. �̷��� if���� �ٽ� ����ǹǷ� �Ʒ��� ���� ��� ����ø� �� �ִ�. 
			}
		}
	}
}

void push(void) // ���������� �̴� �Լ��̴�. 
{
	removezero(); // ���⼭ �Ʊ� removezero �Լ��� �������� �ذ��Ѵ�. 
	removezero(); // �׳� �ι� ����. 
	plus(); // 0�� �� ���� �Ŀ� ���ϰ� 
	removezero(); // (2, 2, 2, 2) ���� ���� ���ϸ� (4, 0, 4, 0)�� �ǹǷ� �ٽ� 0�� �� �����ش�. 
}

void rotate(void) // ���� �ΰ��� �Լ��� ��� ���� �̴� �����̾���. �׷��� �� �Ʒ� ���� ������ ��� �Ǿ� �ϹǷ� ȸ����Ų ���� ���ϰ� �ٽ� ȸ����Ű�� ������� �ߴ�. 
{
	int i, j, tmp;
	for(i=0;i<2;i++) // ��� �� �ڵ�� �������� 1�ܰ� �ڵ� ������ �÷����� ������ �����ߴ�. 
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

void push_all(void) // ��� �������� �̴� �Լ��̴�. 
{
	int i, j;
	for(i=0;i<4;i++) // ���� ����� check �Լ����� �б� ���� checkarr�� arr�� �����Ѵٰ� �ߴµ� �� �����̴�. 
	{
		for(j=0;j<4;j++)
		{
			checkarr[i][j]=arr[i][j];
		}
	}
	checkscore = score;
	switch(spell) // spell���� ���� �󸶳� ȸ����ų�� �ٸ��Ƿ� ��츦 ������. 
	{
		case 'W':
		case 'w':  //���� �����̸� �׳� �״�� 
			push();
			break;
		case 'A':
		case 'a':  //�������� �����̸� �ð�������� �ѹ� ȸ���ϰ� ���� �Ŀ� 3�� ȸ���Ѵ�. 
			rotate();
			push();
			rotate();
			rotate();
			rotate();
			break;
		case 'S':
		case 's':  // �ι� ȸ���ϰ� ���� �Ŀ� �ι� ȸ���Ѵ�. 
			rotate();
			rotate();
			push();
			rotate();
			rotate();
			break;
		case 'D':
		case 'd':  // 3�� ȸ���ϰ� ���� �Ŀ� �ι� ȸ���Ѵ�. 
			rotate();
			rotate();
			rotate();
			push();
			rotate();
			break;
	}
}

void print(void) // �ܼ��� ����ϴ� �Լ��̴�. 
{
	int i, j;
	system("cls"); // �Ʒ��� ��� ��µ��� �ʰ� �� �ڸ����� ��� �ٲ��� �ϹǷ� �� ���ֹ����� �۾��̴�. 
	printf("ID? %s\n", str);
	printf("Score:%d Stage:%d Biggest Score:%d\n", score, stage, bigscore);
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
			printf("%-4d ", arr[i][j]); // ���ʿ� �����Ѵ�.
		printf("\n"); // ����� ���̱� ���ؼ� ���ʹ� �ι� ����. 
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
	firstrandom(); // �ϴ� �������� 2���� ��ҿ� 2�� �����ϰ� 
	print(); // ����Ѵ�. 
	while(1) // ������ �� �ִ� ��Ȳ�̶�� 
	{
		if(unlockscan)
			spell = getch(); // ����Ű�� �Է¹ް� 
		if((spell=='W')||(spell=='w')||(spell=='A')||(spell=='a')||(spell=='D')||(spell=='d')||(spell=='S')||(spell=='s'))
		{
			undo_cnt=0;
			push_all(); // �� �������� �ѹ� �� ������ 
			if(check()) // �б� ���� ������ Ȯ���Ѵ�. ���� ���� �ʴٸ� 
			{
				random(); // 0 �ڸ��� �������� 2 �Ǵ� 4�� �ְ� 
				stage++;
				print(); // ����Ѵ�. 
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
			firstrandom(); // N�� �Է��ϸ� �ʱ�ȭ ���Ѿ� �ϹǷ� firstrandom���� �������� �ڸ��� ���� 
			print(); // ����Ѵ�.  
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
