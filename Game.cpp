#include "Game.h" // ���������� ���� Game.h, ���������� �������, ����� �������, ��� �� ���� ���� ����� ������ ������ �������.
//��������� �������
namespace MyProject
{
	void Game::initVariables() //��������� � �������
	{
		m_window = nullptr;//��������� ��� ������, � ������� ����������� �� ����� �������(��������� �� ������� ��������)

		//������ ����.
		m_endGame = false;
		m_points = 0;
		m_figureSpawnTimerMax = 20;
		m_figureSpawnTimer = m_figureSpawnTimerMax;
		m_maxfigures = 5;
		m_mouseHeld = false;
	}

	void Game::initWindow()
	{
		m_videoMode.height = 600;//������(y)
		m_videoMode.width = 800;//������(x)
		m_window = new sf::RenderWindow(m_videoMode, "My Project"); // ������ ����������� ����
	}//��������� �� ���������, ������� ������� ���� ��� ���������� ������������.

	// ����������� / ����������
	Game::Game()
	{
		initVariables();
		initWindow();
	}

	const bool Game::running() // ����� �� ���������� �������� ����� - const
	{
		return m_window->isOpen();
	}

	const bool Game::getEndGame()// ����� �� ���������� �������� ����� - const
	{
		return m_endGame;
	}

	//�������
	void Game::spawnFigure()
	{
		/*
		  ���������� ������ � �������������� �� ���� � �����. ��������� �� � ��������� ��������.
		 -������ ��������� ���.
		 -������������� ��������� �������.
		 -������������� ��������� ����.
		 - ��������� �����.
		*/

		m_figure.setPosition(
			float(rand() % int(m_window->getSize().x - m_figure.getRadius())), 0); // ������������� ������� ����� �� �
		// ��������������� ��� �����
		int type = rand() % 5;
		switch (type)
		{
		case 0:
			m_figure.setRadius(35);
			m_figure.setFillColor(sf::Color::Color(75, 0, 130));
			break;
		case 1:
			m_figure.setRadius(45);
			m_figure.setFillColor(sf::Color::Color(128, 0, 0));
			break;
		case 2:
			m_figure.setRadius(55);
			m_figure.setFillColor(sf::Color::Color(192, 192, 192));
			break;
		case 3:
			m_figure.setRadius(65);
			m_figure.setFillColor(sf::Color::Color(128, 128, 0));
			break;
		case 4:
			m_figure.setRadius(80);
			m_figure.setFillColor(sf::Color::Color(0, 128, 128));
			break;
		}
		//������ �������(������) � ����� �������
		m_figures.push_back(m_figure);
	}

	void Game::pollEvents()
	{
		//�������
		while (m_window->pollEvent(m_event))
		{
			switch (m_event.type) // �������� ���� �������
			{
			case sf::Event::Closed://���� ������ ����
				m_window->close();// ���������
				break;
			case sf::Event::KeyPressed://������� �������
				if (m_event.key.code == sf::Keyboard::Escape) // ��� ������ ESC	
					m_window->close();// ������� (C ������� ������� �������������� ������ � ������ close)
				break;
			}
		}
	}
	void Game::updateMousePositions()// ������� ����.
	{
		/*
			��������� ��������� ����:
			- ��������� ���� ������������ ����
		*/

		m_mousePosWindow = sf::Mouse::getPosition(*m_window);//������ ����� �������
		m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);//��������� �������� � ����������
	}
	void Game::updateFigures()
	{
		/**

			��������� ������ ��������� ������ � ������� ������
			����� ����� ���������� ����� ������ �������������.
			���������� ������ ����.
			������� ������ �� ���� ������.
		*/

		//���������� ������� ��� ��������� ������
		if (m_figures.size() < m_maxfigures) //size - ����� ����� ������� ������ ������
		{
			if (m_figureSpawnTimer == m_figureSpawnTimerMax)
			{
				//��������� ������ � ����������� �������
				spawnFigure();
				m_figureSpawnTimer = 0;
			}
			else
				m_figureSpawnTimer += 1;
		}

		//����������� � ���������� �����
		for (int i = 0; i < m_figures.size(); i++)
		{
			bool deleted = false;

			m_figures[i].move(0, 5); // ��� �� � = 0, ��� �� � = 5

			if (m_figures[i].getPosition().y > m_window->getSize().y)
			{
				m_figures.erase(m_figures.begin() + i); //������� ������� �������(������) begin - ���������� ��������� �� ������ �������
			}
		}

		//�������� ������� �� ����� ������ ����.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_mouseHeld == false)
			{
				m_mouseHeld = true;
				bool deleted = false;
				for (int i = 0; i < m_figures.size() && deleted == false; i++)
				{
					if (m_figures[i].getGlobalBounds().contains(m_mousePosView)) //������� � �����, ���� ����� ��������� � ����������� ������� �����,�� ����������� ������� ����.
					{
						//���� �� ������
						if (m_figures[i].getFillColor() == sf::Color::Color(75, 0, 130))
							m_points += 1;
						else if (m_figures[i].getFillColor() == sf::Color::Color(128, 0, 0))
							m_points += 2;
						else if (m_figures[i].getFillColor() == sf::Color::Color(192, 192, 192))
							m_points += 3;
						else if (m_figures[i].getFillColor() == sf::Color::Color(128, 128, 0))
							m_points += 4;
						else if (m_figures[i].getFillColor() == sf::Color::Color(0, 128, 128))
							m_points += 5;

						std::cout << "Points: " << m_points << "\n";

						//������� ������ ��� �������
						deleted = true;
						m_figures.erase(m_figures.begin() + i);//begin ��� ������ ������ ��������� � ������ ������� �������� �������
					}
				}
			}
		}
		else
		{
			m_mouseHeld = false;
		}
	}

	void Game::update()
	{
		pollEvents();

		if (m_endGame == false)// ���� ���� �� ���������.
		{
			updateMousePositions(); // ��������� ������� �����
			updateFigures(); // ��������� ������
		}

		//������� ��������� ����
		if (m_points > 100)
			m_endGame = true;
	}

	void Game::renderFigures(sf::RenderTarget& target)//
	{
		//������������ ���� �����
		for (auto e : m_figures)//auto �������� ����������� �� ����� ���������� ���������� ��� ���������� �� ������ ���� ����������������� ���������.
			//������� �� ���������
		{
			target.draw(e);//������ ������
		}
	}
	void Game::render()
	{
		m_window->clear(sf::Color::Color(255, 182, 193)); // ������� ����� ������(������ �����)

		//������ ������� �������
		renderFigures(*m_window);

		m_window->display();//������������� ������� �������.
	}
}