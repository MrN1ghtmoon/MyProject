#pragma once // ����� 1 ���
#include <chrono>
#include <thread>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

namespace MyProject
{
	class Game //�����, ������� ��������� ��� ������� ������.
	{
	private:
		//Window
		sf::RenderWindow* m_window; // ���������� ����
		sf::VideoMode m_videoMode;// ����� ���������� ��������
		sf::Event m_event;//�������

		//Mouse positions
		sf::Vector2i m_mousePosWindow; // ��������� ���� ������������ ����
		sf::Vector2f m_mousePosView;// ��������� ���� ������������ ���� ���������

		//������� ������
		bool m_endGame;
		unsigned m_points;
		int m_health;
		float m_figureSpawnTimer;
		float m_figureSpawnTimerMax;
		int m_maxfigures;
		bool m_mouseHeld;

		//������� �������
		std::vector<sf::CircleShape> m_figures;
		sf::CircleShape m_figure;

		//Private functions
		void initVariables();
		void initWindow();

	public:
		//����������� / ����������
		Game();
		~Game();
		const bool running();
		const bool getEndGame();

		//�������
		void spawnFigure();
		void pollEvents();
		void updateMousePositions();
		void updateFigures();
		void update();
		void renderFigures(sf::RenderTarget& target);
		void render();

	};
}