#pragma once // Вызов 1 раз
#include <chrono>
#include <thread>
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

namespace MyProject
{
	class Game //Класс, который действует как игровой движок.
	{
	private:
		//Window
		sf::RenderWindow* m_window; // объявление окна
		sf::VideoMode m_videoMode;
		sf::Event m_event;

		//Mouse positions
		sf::Vector2i m_mousePosWindow; // Положение мыши относительно окна
		sf::Vector2f m_mousePosView;// 


		//Игровая логика
		bool m_endGame;
		unsigned m_points;
		int m_health;
		float m_figureSpawnTimer;
		float m_figureSpawnTimerMax;
		int m_maxfigures;
		bool m_mouseHeld;

		//Игровые объекты
		std::vector<sf::CircleShape> m_figures;
		sf::CircleShape m_figure;

		//Private functions
		void initVariables();
		void initWindow();

	public:
		//Конструктор / Деструктор
		Game();
		~Game();

		const bool running();
		const bool getEndGame();

		//Функции
		void spawnFigure();
		void pollEvents();
		void updateMousePositions();
		void updateFigures();
		void update();
		void renderFigures(sf::RenderTarget& target);
		void render();

	};
}