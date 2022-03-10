/**
 ** Game made by Christian CHAUX aka Zirk
 ** Graphisms made by RaythalosM
 **/

//#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>
#include <string>
#include <iostream>
#include "player.hpp"
#include "ai.hpp"

void	click_menu(unsigned int xMouse, unsigned int yMouse, int &nbPlayers, int &inGame, int &choiceCharacP1, int &choiceCharacP2, Player &pOne, Player &pTwo, bool &lowFps, sf::RenderWindow &w, sf::Texture controller_t[2], sf::Image controller_i[3], int ammoPOne[2], int ammoPTwo[2], bool &roof, bool &floorDamage, bool isUserReady[2], sf::Texture controllerV_t[2], sf::Image controllerV_i[4])
{
  const int	differentWeapons = 3;
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 25 && yMouse <= 65)
    {
      nbPlayers = 0;
      isUserReady[0] = true;
      isUserReady[1] = true;
      controllerV_t[0].update(controllerV_i[0]);
      controllerV_t[1].update(controllerV_i[0]);
    }
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 120 && yMouse <= 160)
    {
      nbPlayers = 1;
      isUserReady[0] = false;
      isUserReady[1] = true;
      controllerV_t[0].update(controllerV_i[pOne.getController() + 1]);
      controllerV_t[1].update(controllerV_i[0]);
    }
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 215 && yMouse <= 255)
    {
      nbPlayers = 2;
      isUserReady[0] = false;
      isUserReady[1] = false;
      controllerV_t[0].update(controllerV_i[pOne.getController() + 1]);
      controllerV_t[1].update(controllerV_i[pTwo.getController() + 1]);
    }
  if (xMouse >= 800 && xMouse <= 840 && yMouse >= 455 && yMouse <= 495 && isUserReady[0] && isUserReady[1])
    {
      pOne.setImages(choiceCharacP1);
      pTwo.setImages(choiceCharacP2);
      inGame = 1;
      pOne.setWeapons(ammoPOne[0], ammoPOne[1]);
      pTwo.setWeapons(ammoPTwo[0], ammoPTwo[1]);
    }
  if (xMouse >= 510 && xMouse <= 555 && yMouse >= 100 && yMouse <= 160)
    {
      choiceCharacP1++;
      if (choiceCharacP1 > 3)
	choiceCharacP1 = 0;
    }
  if (xMouse >= 760 && xMouse <= 805 && yMouse >= 100 && yMouse <= 160)
    {
      choiceCharacP2++;
      if (choiceCharacP2 > 3)
	choiceCharacP2 = 0;
    }
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 520 && yMouse <= 560)
    {
      lowFps = !lowFps;
      if (lowFps) w.setFramerateLimit(5);
      else w.setFramerateLimit(60);
    }
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 470 && yMouse <= 510)
    floorDamage = !floorDamage;
  if (xMouse >= 30 && xMouse <= 70 && yMouse >= 420 && yMouse <= 460)
    roof = !roof;
  if (xMouse >= 490 && xMouse <= 608 && yMouse >= 350 && yMouse <= 386 && nbPlayers > 0)
    {
      if (pOne.getController() >= 2)
	pOne.setController(0);
      else
	pOne.setController(pOne.getController() + 1);
      controller_t[0].update(controller_i[pOne.getController()]);
      if (nbPlayers > 0)
	{
	  controllerV_t[0].update(controllerV_i[pOne.getController() + 1]);
	  isUserReady[0] = false;
	}
    }
  if (xMouse >= 740 && xMouse <= 858 && yMouse >= 350 && yMouse <= 386 && nbPlayers > 1) 
    {
      if (pTwo.getController() >= 2)
	pTwo.setController(0);
      else
	pTwo.setController(pTwo.getController() + 1);
      controller_t[1].update(controller_i[pTwo.getController()]);
      if (nbPlayers != 0)
	{
	  controllerV_t[1].update(controllerV_i[pTwo.getController() + 1]);
	  isUserReady[1] = false;
	}
    }
  if (xMouse >= 480 && xMouse <= 580 && yMouse >= 205 && yMouse <= 305)
    {
      ammoPOne[0]++;
      if (ammoPOne[0] >= differentWeapons)
	ammoPOne[0] = 0;
    }
  if (xMouse >= 580 && xMouse <= 680 && yMouse >= 205 && yMouse <= 305)
    {
      ammoPOne[1]++;
      if (ammoPOne[1] >= differentWeapons)
	ammoPOne[1] = 0;
    }
  if (xMouse >= 730 && xMouse <= 830 && yMouse >= 205 && yMouse <= 305)
    {
      ammoPTwo[0]++;
      if (ammoPTwo[0] >= differentWeapons)
	ammoPTwo[0] = 0;
    }
  if (xMouse >= 830 && xMouse <= 930 && yMouse >= 205 && yMouse <= 305)
    {
      ammoPTwo[1]++;
      if (ammoPTwo[1] >= differentWeapons)
	ammoPTwo[1] = 0;
    }
}

void	display_menu(sf::RenderWindow &w, int nbPlayers, bool lowFps, int ammoPOne[2], int ammoPTwo[2], bool roof, bool floorDamage, bool isUserReady[2])
{
  sf::RectangleShape pZero;
  sf::RectangleShape pOne;
  sf::RectangleShape pTwo;
  sf::RectangleShape lowerFps;
  sf::RectangleShape roofButton;
  sf::RectangleShape floorDamageButton;
  sf::RectangleShape pOneCharacLeft;
  sf::RectangleShape pOneCharacRight;
  sf::RectangleShape pTwoCharacLeft;
  sf::RectangleShape pTwoCharacRight;
  sf::RectangleShape oneVOne;
  sf::RectangleShape campaign;
  sf::CircleShape    ammoOnePOne;
  sf::CircleShape    ammoOnePTwo;
  sf::CircleShape    ammoTwoPOne;
  sf::CircleShape    ammoTwoPTwo;
  unsigned int	     sizeAmmo[3] = {5, 20, 5};
  sf::Color	     colorAmmo[3] = {sf::Color::Red, sf::Color::Cyan, sf::Color(255, 215, 0)};

  pZero.setPosition(30, 25);
  pOne.setPosition(30, 120);
  pTwo.setPosition(30, 215);
  oneVOne.setPosition(800, 455);
  campaign.setPosition(800, 525);
  lowerFps.setPosition(30, 520);
  floorDamageButton.setPosition(30, 470);
  roofButton.setPosition(30, 420);
  ammoOnePOne.setPosition(480 + 50 - sizeAmmo[ammoPOne[0]], 205 + 50 - sizeAmmo[ammoPOne[0]]);
  ammoOnePTwo.setPosition(580 + 50 - sizeAmmo[ammoPOne[1]], 205 + 50 - sizeAmmo[ammoPOne[1]]);
  ammoTwoPOne.setPosition(730 + 50 - sizeAmmo[ammoPTwo[0]], 205 + 50 - sizeAmmo[ammoPTwo[0]]);
  ammoTwoPTwo.setPosition(830 + 50 - sizeAmmo[ammoPTwo[1]], 205 + 50 - sizeAmmo[ammoPTwo[1]]);

  pZero.setSize(sf::Vector2f(40, 40));
  pOne.setSize(sf::Vector2f(40, 40));
  pTwo.setSize(sf::Vector2f(40, 40));
  oneVOne.setSize(sf::Vector2f(40, 40));
  campaign.setSize(sf::Vector2f(40, 40));
  lowerFps.setSize(sf::Vector2f(40, 40));
  roofButton.setSize(sf::Vector2f(40, 40));
  floorDamageButton.setSize(sf::Vector2f(40, 40));
  ammoOnePOne.setRadius(sizeAmmo[ammoPOne[0]]);
  ammoOnePTwo.setRadius(sizeAmmo[ammoPOne[1]]);
  ammoTwoPOne.setRadius(sizeAmmo[ammoPTwo[0]]);
  ammoTwoPTwo.setRadius(sizeAmmo[ammoPTwo[1]]);

  pZero.setFillColor((nbPlayers == 0) ? sf::Color::Green : sf::Color::Red);
  pOne.setFillColor((nbPlayers == 1) ? sf::Color::Green : sf::Color::Red);
  pTwo.setFillColor((nbPlayers == 2) ? sf::Color::Green : sf::Color::Red);
  oneVOne.setFillColor((isUserReady[0] && isUserReady[1]) ? sf::Color::Green : sf::Color::Red);
  campaign.setFillColor(sf::Color::Red);
  lowerFps.setFillColor((lowFps) ? sf::Color::Green : sf::Color::Red);
  roofButton.setFillColor((roof) ? sf::Color::Green : sf::Color::Red);
  floorDamageButton.setFillColor((floorDamage) ? sf::Color::Red : sf::Color::Green);
  ammoOnePOne.setFillColor(colorAmmo[ammoPOne[0]]);
  ammoOnePTwo.setFillColor(colorAmmo[ammoPOne[1]]);
  ammoTwoPOne.setFillColor(colorAmmo[ammoPTwo[0]]);
  ammoTwoPTwo.setFillColor(colorAmmo[ammoPTwo[1]]);

  w.draw(pZero);
  w.draw(pOne);
  w.draw(pTwo);
  w.draw(oneVOne);
  w.draw(campaign);
  w.draw(lowerFps);
  w.draw(ammoOnePOne);
  w.draw(ammoOnePTwo);
  w.draw(ammoTwoPOne);
  w.draw(ammoTwoPTwo);
  w.draw(roofButton);
  w.draw(floorDamageButton);
}

void	iniImages(sf::Image image[4][7], std::string path[4][7])
{
  for (int y = 0 ; y < 4 ; y++)
    {
      for (int i = 0 ; i < 7 ; i++)
	{
	  if (!image[y][i].loadFromFile("Images/" + path[y][i]))
	    {
	      std::cout << "Error, Images/" + path[y][i] + " not found. Exitting..." << std::endl;
	      exit(1);
	    }
	  image[y][i].createMaskFromColor(sf::Color(40, 87, 43), 0);
	}
    }
}

void	loadImageFromFile(sf::Image &image, std::string path, sf::Color maskColor)
{
  if (!image.loadFromFile(path))
    {
    std::cout << "Error, image not found. Exitting..." << std::endl;
    exit(1);
    }
  image.createMaskFromColor(maskColor, 0);
}

int	main()
{
  srand(time(NULL));
  int nbPlayers = 1;
  bool lowFps = false;
  bool roof = false;
  bool floorDamage = true;
  bool isUserReady[2] = {false, true}; // TODO: verify entry
  const unsigned int xWin = 1000;
  const unsigned int yWin = 600;
  int	inGame = 0; // 0: menu, 1: inGame, 2: end of game, 3: pause
  int	choiceCharacP1 = 0;
  int	choiceCharacP2 = 1;
  Player player(300, 45, 60, 1.0f, xWin, yWin);
  Player player2(300, 45, 60, 1.0f, xWin, yWin);
  Player *charac[2];
  charac[0] = &player;
  charac[1] = &player2;
  int	ammoPOne[2] = {0, 1};
  int	ammoPTwo[2] = {0, 1};
  unsigned int	beginGame = 60;
  sf::RenderWindow window(sf::VideoMode(xWin, yWin), "Fight Epitech Grades DEBUG VERSION");
  std::chrono::time_point<std::chrono::system_clock>	beforeChronoAnim = std::chrono::system_clock::now();
  int	beforeNextAnim = 100;
  sf::Image controllerType[3];
  sf::Texture controller_t[2];
  sf::Sprite controller_s[2];
  loadImageFromFile(controllerType[0], "Images/keyboard.png", sf::Color::White);
  loadImageFromFile(controllerType[1], "Images/xbox.png", sf::Color::White);
  loadImageFromFile(controllerType[2], "Images/ps4.png", sf::Color::White);
  controller_s[0].setPosition(490, 350);
  controller_s[1].setPosition(740, 350);
  for (int i = 0 ; i < 2 ; i++)
    {
      if (!controller_t[i].create(118, 36))
	{
	  std::cout << "Error, unable to create texture. Exitting..." << std:: endl;
	  exit(1);
	}
       controller_t[i].update(controllerType[i + 1]);
       controller_s[i].setTexture(controller_t[i]);
       charac[i]->setController(i + 1);
    }
  sf::Image controllerValidation[4];
  sf::Texture controllerV_t[2];
  sf::Sprite controllerV_s[2];
  loadImageFromFile(controllerValidation[0], "Images/ready.png", sf::Color::White);
  loadImageFromFile(controllerValidation[1], "Images/pressEnter.png", sf::Color::White);
  loadImageFromFile(controllerValidation[2], "Images/pressA.png", sf::Color::White);
  loadImageFromFile(controllerValidation[3], "Images/pressX.png", sf::Color::White);
  controllerV_s[0].setPosition(580, 10);
  controllerV_s[1].setPosition(820, 10);
  for (int i = 0 ; i < 2 ; i++)
    {
      if (!controllerV_t[i].create(118, 36))
	{
	  std::cout << "Error, unable to create texture. Exitting..." << std:: endl;
	  exit(1);
	}
       controllerV_s[i].setTexture(controllerV_t[i]);
    }
  controllerV_t[0].update(controllerValidation[2]);
  controllerV_t[1].update(controllerValidation[0]);
  std::string hibikiNameImage[4][7] = {{"HibikiStand000.png", "HibikiStand045.png", "HibikiStand135.png", "HibikiStand180.png", "HibikiStand225.png", "HibikiStand270.png", "HibikiStand315.png"}, {"AkatsukiStand000.png", "AkatsukiStand045.png", "AkatsukiStand135.png", "AkatsukiStand180.png", "AkatsukiStand225.png", "AkatsukiStand270.png", "AkatsukiStand315.png"}, {"InazumaStand000.png", "InazumaStand045.png", "InazumaStand135.png", "InazumaStand180.png", "InazumaStand225.png", "InazumaStand270.png", "InazumaStand315.png"}, {"IkazuchiStand000.png", "IkazuchiStand045.png", "IkazuchiStand135.png", "IkazuchiStand180.png", "IkazuchiStand225.png", "IkazuchiStand270.png", "IkazuchiStand315.png"}};
  sf::Image hibikiImage[4][7];
  iniImages(hibikiImage, hibikiNameImage);
  sf::Texture hibiki_t[2];
  sf::Sprite hibiki_s[2];
  int animationCharacMenu = 0;
  hibiki_s[0].setPosition(510, 100);
  hibiki_s[1].setPosition(760, 100);
  sf::Texture menu_t;
  sf::Sprite menu;
  for (int i = 0 ; i < 2 ; i++)
    {
      if (!hibiki_t[i].create(45, 60))
	{
	  std::cout << "Error, unable to create texture. Exitting..." << std:: endl;
	  exit(1);
	}
       hibiki_t[i].update(hibikiImage[i][0]);
       hibiki_s[i].setTexture(hibiki_t[i]);
    }
  if (!menu_t.loadFromFile("Images/MainMenu.png"))
    {
      std::cout << "Error, main menu's image not found. Exiting..." << std::endl;
      return (1);
    }
  menu.setTexture(menu_t);
  //glEnable(GL_TEXTURE_2D);
  //glClearColor(255, 255, 255, 0);
  window.setFramerateLimit(60);
  
  while (inGame > -1)
    {
      if (beginGame > 0) beginGame--;
      sf::Event event;
      while (window.pollEvent(event))
	{
	  if (event.type == sf::Event::Closed)
	    inGame = -1;
	  if (event.type == sf::Event::MouseButtonPressed && inGame == 0)
	    click_menu(event.mouseButton.x, event.mouseButton.y, nbPlayers, inGame, choiceCharacP1, choiceCharacP2, player, player2, lowFps, window, controller_t, controllerType, ammoPOne, ammoPTwo, roof, floorDamage, isUserReady, controllerV_t, controllerValidation);
	  if (event.type == sf::Event::KeyPressed && inGame == 0)
	    {
	      for (int i = 0 ; i < 2 ; i++)
		{
		  if (charac[i]->getController() == 0 && event.key.code == sf::Keyboard::Return)
		    {
		      if (!isUserReady[i])
			{
			  controllerV_t[i].update(controllerValidation[0]);
			  isUserReady[i] = true;
			  break;
			}
		      else if ((i == 0 && nbPlayers > 0) || (i == 1 && nbPlayers != 0))
			{
			  controllerV_t[i].update(controllerValidation[1]);
			  isUserReady[i] = false;
			  break;
			}
		    }
		}
	    }
	  if (event.type == sf::Event::JoystickButtonPressed && inGame == 0)
	    {
	      for (int i = 0 ; i < 2 ; i++)
		{
		  if (event.joystickButton.button == 0 && charac[i]->getController() == 1)
		    {
		      if (!isUserReady[i])
			{
			  controllerV_t[i].update(controllerValidation[0]);
			  isUserReady[i] = true;
			  charac[i]->setControllerId(event.joystickButton.joystickId);
			  break;
			}
		      else if (event.joystickButton.joystickId == charac[i]->getControllerId()
			       && ((i == 0 && nbPlayers > 0) || (i == 1 && nbPlayers != 0)))
			{
			  controllerV_t[i].update(controllerValidation[2]);
			  isUserReady[i] = false;
			  break;
			}
		    }
		   if (event.joystickButton.button == 1 && charac[i]->getController() == 2)
		    {
		      if (!isUserReady[i])
			{
			  controllerV_t[i].update(controllerValidation[0]);
			  isUserReady[i] = true;
			  charac[i]->setControllerId(event.joystickButton.joystickId);
			  break;
			}
		      else if (event.joystickButton.joystickId == charac[i]->getControllerId()
			       && ((i == 0 && nbPlayers > 0) || (i == 1 && nbPlayers != 0)))
			{
			  controllerV_t[i].update(controllerValidation[3]);
			  isUserReady[i] = false;
			  break;
			}
		    }
		}
	    }
	  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape && (inGame == 1 || inGame == 3))
	    {
	      if (inGame != 3) inGame = 3;
	      else inGame = 1;
	    }
	  if (event.type == sf::Event::JoystickMoved && inGame == 1 && event.joystickButton.joystickId == player.getControllerId() && player.getController() > 0)
	    {
	      if (event.joystickMove.axis == sf::Joystick::X && nbPlayers > 0)
		{
		  if (event.joystickMove.position < -75)
		      player.setDoesGoLeft(true);
		  else if (event.joystickMove.position > 75)
		      player.setDoesGoRight(true);
		  else
		    {
		      player.setDoesGoLeft(false);
		      player.setDoesGoRight(false);
		    }
		}
	    }
	  if (event.type == sf::Event::JoystickMoved && inGame == 1 && event.joystickButton.joystickId == player2.getControllerId() && player2.getController() > 0)
	    {
	      if (event.joystickMove.axis == sf::Joystick::X && nbPlayers > 0)
		{
		  if (event.joystickMove.position < -75)
		      player2.setDoesGoLeft(true);
		  else if (event.joystickMove.position > 75)
		      player2.setDoesGoRight(true);
		  else
		    {
		      player2.setDoesGoLeft(false);
		      player2.setDoesGoRight(false);
		    }
		}
	    }
	  if (event.type == sf::Event::JoystickButtonPressed && inGame == 1 && event.joystickButton.joystickId == player.getControllerId() && player.getController() != 0)
	    {
	      if (((event.joystickButton.button == 0 && player.getController() == 1)
		   || (event.joystickButton.button == 1 && player.getController() == 2))
		  && nbPlayers > 0)
		player.jump(yWin, xWin);
	      if (((event.joystickButton.button == 1 && player.getController() == 1)
		   || (event.joystickButton.button == 2 && player.getController() == 2))
		  && nbPlayers > 0)
		player.fall(yWin);
	      if (event.joystickButton.button == 5 && nbPlayers > 0)
		player.fire(1);
	      if (event.joystickButton.button == 4 && nbPlayers > 0)
		player.fire(2);
	    }
	   if (event.type == sf::Event::JoystickButtonPressed && inGame == 1 && event.joystickButton.joystickId == player2.getControllerId() && player2.getController() != 0)
	    {
	      if (((event.joystickButton.button == 0 && player2.getController() == 1)
		   || (event.joystickButton.button == 1 && player2.getController() == 2))
		  && nbPlayers > 0)
		player2.jump(yWin, xWin);
	      if (((event.joystickButton.button == 1 && player2.getController() == 1)
		   || (event.joystickButton.button == 2 && player2.getController() == 2))
		  && nbPlayers > 0)
		player2.fall(yWin);
	      if (event.joystickButton.button == 5 && nbPlayers > 0)
		player2.fire(1);
	      if (event.joystickButton.button == 4 && nbPlayers > 0)
		player2.fire(2);
	    }
	  if (event.type == sf::Event::KeyPressed && inGame == 1)
	    {
	      if (player.getController() == 0)
		{
		  if (event.key.code == sf::Keyboard::Z && nbPlayers > 0)
		    player.jump(yWin, xWin);
		  if (event.key.code == sf::Keyboard::Q && nbPlayers > 0)
		    player.setDoesGoLeft(true);
		  if (event.key.code == sf::Keyboard::D && nbPlayers > 0)
		    player.setDoesGoRight(true);
		  if (event.key.code == sf::Keyboard::S && nbPlayers > 0)
		    player.fall(yWin);
		  if (event.key.code == sf::Keyboard::L && nbPlayers > 0 && beginGame == 0)
		    player.fire(1);
		  if (event.key.code == sf::Keyboard::M && nbPlayers > 0 && beginGame == 0)
		    player.fire(2);
		}
	      else if (player2.getController() == 0)
		{
		  if (event.key.code == sf::Keyboard::Z && nbPlayers == 2)
		    player2.jump(yWin, xWin);
		  if (event.key.code == sf::Keyboard::Q && nbPlayers == 2)
		    player2.setDoesGoLeft(true);
		  if (event.key.code == sf::Keyboard::D && nbPlayers == 2)
		    player2.setDoesGoRight(true);
		  if (event.key.code == sf::Keyboard::S && nbPlayers == 2)
		    player2.fall(yWin);
		  if (event.key.code == sf::Keyboard::L && nbPlayers == 2 && beginGame == 0)
		    player2.fire(1);
		  if (event.key.code == sf::Keyboard::M && nbPlayers == 2 && beginGame == 0)
		    player2.fire(2);
		}
	    }
	  if (event.type == sf::Event::KeyReleased && inGame == 1)
	    {
	      if (player.getController() == 0)
		{
		  if (event.key.code == sf::Keyboard::Q && nbPlayers > 0)
		    player.setDoesGoLeft(false);
		  if (event.key.code == sf::Keyboard::D && nbPlayers > 0)
		    player.setDoesGoRight(false);
		}
	      else if (player2.getController() == 0)
		{
		  if (event.key.code == sf::Keyboard::Q && nbPlayers == 2)
		    player2.setDoesGoLeft(false);
		  if (event.key.code == sf::Keyboard::D && nbPlayers == 2)
		    player2.setDoesGoRight(false);
		}
	    }
	}
      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      window.clear(sf::Color::White);
      //window.pushGLStates();
      //window.resetGLStates();
      if (inGame == 1 || inGame == 2 || inGame == 3)
	{
	  if (inGame != 3)
	    {
	      if (inGame != 2)
		{
		  // iaPlay, iaCustom
		  if (nbPlayers < 2)
		    iaPlay(charac[0], charac[1], xWin, yWin, beginGame);
		  if (nbPlayers == 0)
		    iaPlay(charac[1], charac[0], xWin, yWin, beginGame);
		}
	      charac[0]->receiveDamages(*charac[1]);
	      charac[1]->receiveDamages(*charac[0]);
	    }
	  for (int i = 0 ; i < 2 ; i++)
	    {
	      if (inGame == 1)
		{
		  if (charac[i]->getDoesGoLeft())
		    charac[i]->goLeft();
		  if (charac[i]->getDoesGoRight())
		    charac[i]->goRight();
		  charac[i]->move(yWin, xWin, roof, floorDamage);
		  charac[i]->moveProjs(xWin, yWin);
		}
	      charac[i]->display(window);
	      charac[i]->displayUi(window, 8 * xWin / 10 * i + 50);
	      charac[i]->displayProjs(window);
	      if (charac[i]->getLife() == 0)
		inGame = 2;
	    }
	}
      else if (inGame == 0)
	{
	  window.draw(menu);
	  window.draw(hibiki_s[0]);
	  window.draw(hibiki_s[1]);
	  window.draw(controller_s[0]);
	  window.draw(controller_s[1]);
	  window.draw(controllerV_s[0]);
	  window.draw(controllerV_s[1]);
	  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - beforeChronoAnim).count() > beforeNextAnim)
	    {
	      beforeChronoAnim = std::chrono::system_clock::now();
	      animationCharacMenu++;
	      if (animationCharacMenu > 6)
		animationCharacMenu = 0;
	      hibiki_t[0].update(hibikiImage[choiceCharacP1][animationCharacMenu]);
	      hibiki_t[1].update(hibikiImage[choiceCharacP2][animationCharacMenu]);
	    }
	  display_menu(window, nbPlayers, lowFps, ammoPOne, ammoPTwo, roof, floorDamage, isUserReady);
	}
      //window.popGLStates();
      window.display();
    }
  return (0);
}
