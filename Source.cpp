#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <iostream>
#include <stdio.h>

using namespace std;

class Rect
{
public:
	Rect(SDL_Window* window, SDL_Renderer* renderer, int w, int h, int x, int y, int r, int g, int b, int a, SDL_Texture* Message);
	void draw();
	void move();
	double getx();
private:
	int w, h, x, y, r, g, b, a;

	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* Message;


};

int ammo = 10;

class Math
{
public:
	int choose_optype(int num_choices);
	int gen_addscore(int ammo);
	int gen_subscore(int ammo, int flag);
	int gen_addandsubscore(int ammo, int flag);
	double gen_addandmulscore(int ammo, int flag);
	int gen_subanddivscore(int ammo, int flag);
};	


Rect::Rect(SDL_Window* window,	SDL_Renderer *renderer, int w, int h, int x, int y, int r, int g, int b, int a, SDL_Texture* Message)
{
	this->window = window;
	this->renderer = renderer;
	this->w = w;
	this->h = h;
	this->x = x;
	this->y = y;
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
	this->Message = Message;
}

void Rect::draw()
{
	SDL_Rect rect;

	rect.w = w;
	rect.h = h;
	rect.x = x;
	rect.y = y;

	SDL_SetRenderDrawColor(renderer, r, g, b, a);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_RenderFillRect(renderer, &rect);

	

	SDL_RenderCopy(renderer, Message, NULL, &rect);
	SDL_RenderPresent(renderer);



}

void Rect::move()
{
	this->x -= 1;
}

double Rect::getx()
{
	return x;
}

int Math::choose_optype(int num_choices)
{
	srand(time(NULL));
	return rand() % num_choices;
}

int Math::gen_addscore(int ammo)
{
	srand(time(NULL));
	int score1 = 2 + rand() % 4;
	if (ammo == 1)
		return score1;
	srand(time(NULL));
	int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
	return max(score1, score2);
}
int Math::gen_subscore(int ammo, int flag)
{
	if (ammo == 1 && flag == 0)
		return 0;
	if (ammo == 1 && flag == 1)
		return 1;
	srand(time(NULL));
	int score1 = 1 + rand() % 4;
	int score2;
	srand(time(NULL));
	if (flag == 0)
		score2 = (int)(ammo / 4) + rand() % ((int)((ammo * 1.2) - (ammo / 4)));
	else
		score2 = (int)(ammo / 8) + rand() % ((int)((ammo * 0.5) - (ammo / 8)));

	return max(score1, score2);
}

int Math::gen_addandsubscore(int ammo, int flag)
{
	if (flag == 0)
	{
		srand(time(NULL));
		int score1 = 2 + rand() % 4;
		if (ammo == 1)
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
		score2 = (int)(ammo / 3) + rand() % ((int)((ammo * 1.5) - (ammo / 3)));
		return max(score1, score2);
	}
}

double Math::gen_addandmulscore(int ammo, int flag)
{
	if (flag == 0)
	{
		srand(time(NULL));
		int score1 = 2 + rand() % 4;
		if (ammo == 1)
			return score1;
		srand(time(NULL));
		int score2 = (int)(ammo / 8) + rand() % ((int)((ammo / 2) - (ammo / 8)));
		return (double)max(score1, score2);
	}

	else
	{
		srand(time(NULL));
		int num = 8 + rand() % 9;
		double temp = (double)num;
		double score = temp / 8;
		return score;
	}

}

int Math::gen_subanddivscore(int ammo, int flag)
{
	if (flag == 0)
	{
		srand(time(NULL));
		int score1 = 1 + rand() % 4;
		int score2;
		srand(time(NULL));
		score2 = (int)(ammo / 4) + rand() % ((int)((ammo * 1.2) - (ammo / 4)));
		return max(score1, score2);
	}

	else
	{
		if (ammo <= 2)
			return 1;
		srand(time(NULL));
		int score = 2 + rand() % 9;
		return score;
	}
}

void spawnRects(SDL_Window *window, SDL_Renderer *renderer )
{
	TTF_Font* Sans = TTF_OpenFont("Font.ttf", 24);

	Math* math = new Math();

	/*int op1, op2;
	int operand1, operand2;
	double doperand2;*/
	string s1, s2;

	int optype = math->choose_optype(5);

	if (optype == 0)
	{
		int score_add1 = math->gen_addscore(ammo);
		int score_add2 = math->gen_addscore(ammo);
		s1 = "+" + to_string(score_add1);
		s2 = "+" + to_string(score_add2);
		
	}

	if (optype == 1)
	{
		int score_sub1 = math->gen_subscore(ammo, 0);
		int score_sub2 = math->gen_subscore(ammo, 1);

		s1 = "-" + to_string(score_sub1);
		s2 = "-" + to_string(score_sub2);
		
	}

	if (optype == 2)
	{
		int score_addandsub1 = math->gen_addandsubscore(ammo, 0);
		int score_addandsub2 = math->gen_addandsubscore(ammo, 1);

		s1 = "+" + to_string(score_addandsub1);
		s2 = "-" + to_string(score_addandsub2);
		
	}

	if (optype == 3)
	{
		int score_addandmul1 = (int)math->gen_addandmulscore(ammo, 0);
		double score_addandmul2 = math->gen_addandmulscore(ammo, 1);

		double temp = (int)(score_addandmul2 * 100 + 0.5);
		score_addandmul2 /= 100;
		cout << score_addandmul2 << endl;
		s1 = "+" + to_string(score_addandmul1);
		s2 = "*" + to_string(score_addandmul2);
		s2 = s2.substr(0, 5);
		
		

	}

	if (optype == 4)
	{
		int score_subanddiv1 = math->gen_subanddivscore(ammo, 0);
		int score_subanddiv2 = math->gen_subanddivscore(ammo, 1);

		s1 = "-" + to_string(score_subanddiv1);
		s2 = "/" + to_string(score_subanddiv2);
	}
		


	SDL_Color White = { 255,255,255 };

	SDL_Surface* surfaceMessage =
		TTF_RenderText_Solid(Sans, s1.c_str(), White);


	SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);

	SDL_Surface* surfaceMessage2 =
		TTF_RenderText_Solid(Sans, s2.c_str(), White);


	SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);



	Rect* rect = new Rect(window, renderer, 100, 300, 800, 0, 0, 255, 0, 150, Message);
	Rect* rect2 = new Rect(window, renderer, 100, 300, 800, 300, 0, 0, 255, 150, Message2);

	/*Rect* rect = new Rect(window, renderer, 100, 300, 800, 0, 0, 255, 0, 150);
	Rect* rect2 = new Rect(window, renderer, 100, 300, 800, 300, 0, 0, 255, 150);*/





	while (true)
	{
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

		SDL_RenderClear(renderer);
		SDL_RenderPresent(renderer);

		rect->move();
		rect->draw();

		rect2->move();
		rect2->draw();

		SDL_Delay(5);

		if (rect->getx() <= -100)
		{
			free(rect);
			free(rect2);
			break;
		}



		//cout << 1;

	}

}

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);

	TTF_Init();

	SDL_Window* window = SDL_CreateWindow("Ammomatics", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);

	while (true)
	{

		int call = rand() % 2000;
		//cout << call << endl;
		if (call == 1999)
			spawnRects(window, renderer);
	}


}

