#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>
#include "finishGameDevil.h"
#include "finishGameJackpot.h"
#include "finishGameNotMoney.h"

#define JACKPOT 777
#define DEVIL 666
#define PRICE_ROLL_DRUM -500

int const prizeRolls[] = {111,222,333,444,555};

void finish_Devil(){
        finishDevil();
	printf("\n/------------------------------------------------/\n");
        printf("\nDAMN!!! Devil stole all your money!!!!\n");
	printf("\n/------------------------------------------------/\n");
}

void finish_Jackpot(){
        finishJackpot();
	printf("\n/------------------------------------------------/\n");
        printf("\nCongratulations you won JACKPOT!!!!!\n");
	printf("\n/------------------------------------------------/\n");
}

void finish_NotMoney(){
        finishNotMoney();
	printf("\n/------------------------------------------------/\n");
        printf("\nYour Bitcoins are ran out!!!\n");
	printf("\n/------------------------------------------------/\n");
}

int checkMoney(int credits,int* arr){
        if(credits < 500){
                free(arr);
                finish_NotMoney();
                return 0;
        }
	return credits;
}

void rollDrum(int* arr){
srand(time(NULL));
for(int i = 0;i < 3;i++)
	arr[i] = rand() % 8;
}

int drumNumber(int* arr){
	return (arr[0]*100) + (arr[1] * 10) + (arr[2] * 1);
}

int takePrize(int* arr){
	int drumNum = drumNumber(arr);
	if(drumNum == JACKPOT){
		free(arr);
		finish_Jackpot();
		return 0;
	}
	else if(drumNum == DEVIL){
		free(arr);
		finish_Devil();
		return 0;
	}else{
		for(int i = 0;i < (sizeof(prizeRolls) / sizeof(prizeRolls[0]));i++){
			if(drumNum == prizeRolls[i])
				return drumNum + 300;
		}
	}
	return arr[0] == 5 && arr[1] == 5 ? 700:
		arr[0] == 5 ? 400:
		arr[0] == 7 && arr[1] == 7 ? 1200:
		arr[0] == 7 ? 700 : 100;
}

int updateCredits(int credits,int* arr){
	int tmp = takePrize(arr);
	if(tmp == 0)
		return 0;
	else{
		printf("You won, %d credits", tmp);
		printf("\n/------------------------------------------------/\n");
       		credits+= PRICE_ROLL_DRUM + tmp;
		return credits;
	}
}


void printDrum(int* arr){
printf("\n/------------------------------------------------/\n");
for(int i = 0;i < 3;i++)
	printf("[%d]", arr[i]);
	printf("\n");
}


int main(){

int choice = 0;
int CREDITS = 5000;
int* DRUM = (int*)malloc(sizeof(int) * 3);


while(1){
printf("\n1.Show current credits\n");
printf("2.Roll drum\n");
printf("3.Pick up the winnings\n");
printf("What do you want?: \n");
scanf("%d", &choice);
	switch(choice){
		case 1: printf("\n/------------------------------------------------/\n");
			printf("Your current credits, %d", CREDITS);
			printf("\n/------------------------------------------------/\n");
			break;
		case 2: if(checkMoney(CREDITS, DRUM) == 0)
				return 0;
			rollDrum(DRUM);
			printDrum(DRUM);
			CREDITS = updateCredits(CREDITS, DRUM);
			if(CREDITS == 0)
				return 0;
			break;
		case 3:	printf("\n/------------------------------------------------/\n");
			printf("Congratulations your money, %d", CREDITS);
			printf("\n/------------------------------------------------/\n");
			free(DRUM);
			return 0;
		default:printf("\n/------------------------------------------------/\n");
			printf("Your choice wrong!!!, make another choice: ");
			printf("\n/------------------------------------------------/\n");
			break;
	}
}
free(DRUM);
return 0;
}
