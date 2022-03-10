#ifndef PLAYER_HPP_
# define PLAYER_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <vector>
# include <cmath>
# include <string>
# include <iostream>
# include <chrono>
# include <projectile.hpp>

class Player
{
public:
  Player(unsigned int life, unsigned int m_x_size, unsigned int m_y_size, float speed, const unsigned int xWin, const unsigned int yWin);
  ~Player();
  void	setImages(int characNameId);
  void	display(sf::RenderWindow &w); // display character
  void	move(const unsigned int yWin, const unsigned int xWin, bool move, bool floorDamage); // move character
  void	jump(const unsigned int yWin, const unsigned int xWin); // jump, double jump and wall jump
  void	goLeft();
  void	goRight();
  bool	getCanDoubleJump();
  bool  getDoesGoRight();
  bool	getDoesGoLeft();
  int	getLookDirection();
  void	setDoesGoRight(bool value);
  void	setDoesGoLeft(bool value);
  void	setWeapons(int weaponOne, int weapon2);
  void	displayUi(sf::RenderWindow &w, int xPos); // display health bar
  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  void	fire(unsigned int type); // shoot bullet
  void	displayProjs(sf::RenderWindow &w); // display bullets
  void	moveProjs(const unsigned int xWin, const unsigned int yWin);
  void	receiveDamages(Player &ennemy); // check if in collision with a bullet
  std::vector<Projectile> &getProjs();
  unsigned int	getLife();
  unsigned int	getLifePurcentage();
  void	fall(const unsigned int yWin); // S or Down arrow
  void	setController(int value);
  int	getController();
  void	setControllerId(unsigned int value);
  unsigned int	getControllerId();

private:
  bool	isTouchByProjectile(Projectile proj);
  unsigned int	life; // current life
  unsigned int	lifeMax; // life max
  sf::Vector2f	size; // size of character
  float		speed; // speed
  float		upSpeed; // allow to manage jump and gravity
  float		horSpeed; // Horizontal speed
  sf::Vector2f	pos; // position on the window
  bool		doesGoLeft;
  bool		doesGoRight; // if true, go right, else does not
  int		lookDirection; // where the character look at, 1: left ; 2 : right
  std::vector<Projectile> projs; // bullets fired by the character
  bool		canDoubleJump; // false when double jump, go back to true when charac touch the floor
  sf::Texture	texture;
  sf::Sprite	sprite;
  std::string	characName;
  sf::Image	imageStandLeft;
  sf::Image	imageStandRight;
  std::chrono::time_point<std::chrono::system_clock>	lastShot;
  std::chrono::time_point<std::chrono::system_clock>	stayFloor;
  bool	isInFloor;
  unsigned int	beforeNextShot;
  unsigned int	controller; // 0: keyboard, 1: xbox controller, 2: ps4 controller
  int	weapon[2];
  unsigned int	controllerId;
  sf::Font font;
  sf::Text textLife;
};

#endif /* !PLAYER_HPP_ */
