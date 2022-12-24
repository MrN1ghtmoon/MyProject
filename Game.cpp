#include "Game.h" // Подключаем файл Game.h, используем кавычки, чтобы сказать, что мы ищем файл среди файлов нашего проекта.
//Приватная функция
namespace MyProject
{
	void Game::initVariables() //Обращение к функции
	{
		m_window = nullptr;//Отдельный тип данных, с которым комплилятор не может спутать(указатель на нулевое значение)

		//Логика игры.
		m_endGame = false;
		m_points = 0;
		m_figureSpawnTimerMax = 20;
		m_figureSpawnTimer = m_figureSpawnTimerMax;
		m_maxfigures = 5;
		m_mouseHeld = false;
	}

	void Game::initWindow()
	{
		m_videoMode.height = 600;//высота(y)
		m_videoMode.width = 800;//ширина(x)
		m_window = new sf::RenderWindow(m_videoMode, "My Project"); // Создаём графическое окно
	}//указатель на переменую, которая создает окно для двумерного пространства.

	// Конструктор / деструктор
	Game::Game()
	{
		initVariables();
		initWindow();
	}

	const bool Game::running() // Чтобы не изменялось значение пишем - const
	{
		return m_window->isOpen();
	}

	const bool Game::getEndGame()// Чтобы не изменялось значение пишем - const
	{
		return m_endGame;
	}

	//Функции
	void Game::spawnFigure()
	{
		/*
		  Создавайте врагов и устанавливайте их типы и цвета. Порождает их в случайных позициях.
		 -Задает случайный тип.
		 -Устанавливает случайную позицию.
		 -Устанавливает случайный цвет.
		 - Добавляет врага.
		*/

		m_figure.setPosition(
			float(rand() % int(m_window->getSize().x - m_figure.getRadius())), 0); // Рандомизирует позицию фигур по Х
		// Рандомизировать тип фигур
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
		//Добать элемент(фигуру) в конец массива
		m_figures.push_back(m_figure);
	}

	void Game::pollEvents()
	{
		//События
		while (m_window->pollEvent(m_event))
		{
			switch (m_event.type) // проверка типа события
			{
			case sf::Event::Closed://Если закрыл окно
				m_window->close();// закрывает
				break;
			case sf::Event::KeyPressed://нажатие клавиши
				if (m_event.key.code == sf::Keyboard::Escape) // Код Кнопки ESC	
					m_window->close();// закрыть (C помощью стрелки осуществляется доступ к методу close)
				break;
			}
		}
	}
	void Game::updateMousePositions()// Позиция мыши.
	{
		/*
			Обновляет положения мыши:
			- Положение мыши относительно окна
		*/

		m_mousePosWindow = sf::Mouse::getPosition(*m_window);//нахоим коорд курсора
		m_mousePosView = m_window->mapPixelToCoords(m_mousePosWindow);//переводим пикселей в координаты
	}
	void Game::updateFigures()
	{
		/**

			Обновляет таймер появления фигуры и создает фигуры
			Когда общее количество фигур меньше максимального.
			Перемещает фигуры вниз.
			Удаляет фигуры на краю экрана.
		*/

		//Обновление таймера для появления фигуры
		if (m_figures.size() < m_maxfigures) //size - найти длину массива класса вектор
		{
			if (m_figureSpawnTimer == m_figureSpawnTimerMax)
			{
				//Появление фигуры и сбрасывание таймера
				spawnFigure();
				m_figureSpawnTimer = 0;
			}
			else
				m_figureSpawnTimer += 1;
		}

		//Перемещение и обновление фигур
		for (int i = 0; i < m_figures.size(); i++)
		{
			bool deleted = false;

			m_figures[i].move(0, 5); // Шаг по х = 0, шаг по у = 5

			if (m_figures[i].getPosition().y > m_window->getSize().y)
			{
				m_figures.erase(m_figures.begin() + i); //Стереть элемент массива(фигуру) begin - возвращает указатель на начало массива
			}
		}

		//Проверка нажатия на левую кнопки мыши.
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (m_mouseHeld == false)
			{
				m_mouseHeld = true;
				bool deleted = false;
				for (int i = 0; i < m_figures.size() && deleted == false; i++)
				{
					if (m_figures[i].getGlobalBounds().contains(m_mousePosView)) //Границы к круга, если точка находится в координатах границы круга,то выполняются условия ниже.
					{
						//Очки за фигуру
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

						//Удалять фигуры при нажатии
						deleted = true;
						m_figures.erase(m_figures.begin() + i);//begin дал доступ нашему итератору к самому первому элементу вектора
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

		if (m_endGame == false)// Если игра не закончена.
		{
			updateMousePositions(); // Обновляем позицию мышки
			updateFigures(); // Обновляем фигуры
		}

		//Условие окончания игры
		if (m_points > 100)
			m_endGame = true;
	}

	void Game::renderFigures(sf::RenderTarget& target)//
	{
		//Визуализация всех фигур
		for (auto e : m_figures)//auto помогает компилятору на этапе компиляции определить тип переменной на основе типа инициализируемого выражения.
			//Перебор по значениям
		{
			target.draw(e);//Рисует фигуры
		}
	}
	void Game::render()
	{
		m_window->clear(sf::Color::Color(255, 182, 193)); // Очищает экран цветом(каждый фрейм)

		//Рисуем игровые объекты
		renderFigures(*m_window);

		m_window->display();//Визуализирует игровые объекты.
	}
}