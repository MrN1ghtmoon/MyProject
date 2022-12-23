#include <iostream>
#include "Game.h" // Подключаем файл Game.h


int main()
{
	//Инициализация игрового движка
	MyProject::Game game;

	//Игровой цикл
	while (game.running() && !game.getEndGame())
	{
		//Обновление
		game.update();
		game.render();
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
	}

	return 0;
}