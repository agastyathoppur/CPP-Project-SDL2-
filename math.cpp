//#include <bits/stdc++.h>
#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

int gen_addscore(int ammo);
int gen_subscore(int ammo, int flag);

int choose_optype(int num_choices)
{
	srand(time(NULL));
	return rand() % num_choices;
}

int gen_addscore(int ammo)
{
	srand(time(NULL));
	int score1 = 2 + rand() % 4;
	if(ammo==1)
		return score1;
	srand(time(NULL));
	int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
	return max(score1, score2);
}
int gen_subscore(int ammo,int flag)
{
	if(ammo==1 && flag==0)
		return 0;
	if(ammo==1 && flag==1)
		return 1;
	srand(time(NULL));
	int score1 = 1 + rand() % 4;
	int score2;
	srand(time(NULL));
	if(flag==0)
		score2 = (int)(ammo / 4) + rand() % ((int)((ammo*1.2) - (ammo / 4)));
	else
		score2 = (int)(ammo / 8) + rand() % ((int)((ammo*0.5) - (ammo / 8)));

	return max(score1, score2);
}

int gen_addandsubscore(int ammo,int flag)
{
	if(flag==0)
	{
		srand(time(NULL));
		int score1 = 2 + rand() % 4;
		if(ammo==1)
			return score1;
		srand(time(NULL));
		int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
		return max(score1, score2);
	}

	else
	{
		srand(time(NULL));
		int score1 = 1 + rand() % 4;
		int score2;
		srand(time(NULL));
			score2 = (int)(ammo / 3) + rand() % ((int)((ammo*1.5) - (ammo / 3)));
		return max(score1, score2);
	}
}

double gen_addandmulscore(int ammo,int flag)
{
	if(flag==0)
	{
		srand(time(NULL));
		int score1 = 2 + rand() % 4;
		if(ammo==1)
			return score1;
		srand(time(NULL));
		int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
		return (double)max(score1, score2);
	}

	else
	{
		srand(time(NULL));
		int num= 8+ rand()%9;
		double temp=(double)num;
		double score=temp/8;
		return score;
	}
	
}

int gen_subanddivscore(int ammo, int flag)
{
	if(flag==0)
	{
		srand(time(NULL));
		int score1 = 1 + rand() % 4;
		int score2;
		srand(time(NULL));
			score2 = (int)(ammo / 4) + rand() % ((int)((ammo*1.2) - (ammo / 4)));
		return max(score1, score2);
	}

	else
	{
		if(ammo<=2)
			return 1;
		srand(time(NULL));
		int score = 2 + rand() % 9;
		return score;
	}
}
int main(int argc, char* argv[])
{
	/*SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window *window = SDL_CreateWindow("Ammomatics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(10000);*/

	int ammo=10;
	//int op1, op2;
	while (ammo > 0)
	{
		int optype = choose_optype(5);
		if (optype==0)
		{
			int score_add1 = gen_addscore(ammo);
			int score_add2 = gen_addscore(ammo);
			cout << "Choose between +" << score_add1 << " and +" << score_add2 << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				ammo += score_add1;
			if (choice == 2)
				ammo += score_add2;
			//cout << "Ammo= " << ammo;
		}

		if (optype == 1)
		{
			int score_sub1 = gen_subscore(ammo,0);
			int score_sub2 = gen_subscore(ammo,1);
			cout << "Choose between -" << score_sub1 << " and -" << score_sub2 << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				ammo -= score_sub1;
			if (choice == 2)
				ammo -= score_sub2;
			//cout << "Ammo= " << ammo;
		}

		if(optype == 2)
		{
			int score_addandsub1 = gen_addandsubscore(ammo,0);
			int score_addandsub2 = gen_addandsubscore(ammo,1);
			cout << "Choose between +" << score_addandsub1 << " and -" << score_addandsub2 << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				ammo += score_addandsub1;
			if (choice == 2)
				ammo -= score_addandsub2;
		}

		if(optype == 3)
		{
			int score_addandmul1 = (int)gen_addandmulscore(ammo,0);
			double score_addandmul2= gen_addandmulscore(ammo,1);
			cout<< "Choose between +" << score_addandmul1 <<" and *"<<score_addandmul2 << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				ammo += score_addandmul1;
			if (choice == 2)
			{
				double temp=(double)ammo;
				temp*= score_addandmul2;
				ammo=(int)temp;
			}
			
		}

		if(optype==4)
		{
			int score_subanddiv1 = gen_subanddivscore(ammo,0);
			int score_subanddiv2 = gen_subanddivscore(ammo,1);
			cout<< "Choose between -" << score_subanddiv1 <<" and /"<<score_subanddiv2 << endl;
			int choice;
			cin >> choice;
			if (choice == 1)
				ammo -= score_subanddiv1;
			if (choice == 2)
				ammo /= score_subanddiv2;
		}
		cout << "Ammo= " << ammo << endl;
	}
	cout << "Game over";

	return 0;
	
}