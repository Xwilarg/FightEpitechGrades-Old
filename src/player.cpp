#include "player.hpp"
#include "projectile.hpp"

Player::Player(unsigned int m_life, unsigned int m_x_size, unsigned int m_y_size, float m_speed, const unsigned int xWin, const unsigned int yWin)
{
  lifeMax = m_life;
  life = lifeMax;
  size.x = m_x_size;
  size.y = m_y_size;
  speed = m_speed;
  pos.x = xWin / 2;
  pos.y = yWin / 2;
  upSpeed = 0;
  horSpeed = 0;
  doesGoLeft = false;
  doesGoRight = false;
  lookDirection = 1;
  canDoubleJump = true;
  lastShot = std::chrono::system_clock::now();
  isInFloor = true;
  beforeNextShot = 2000;
  controller = 1;
  if (!font.loadFromFile("Font/arial.ttf"))
    {
      std::cout << "Error, unable to open arial.ttf. Exitting..." << std::endl;
      exit(1);
    }
  textLife.setFont(font);
  textLife.setColor(sf::Color::Black);
  textLife.setCharacterSize(15);
}

Player::~Player()
{}

void	Player::setImages(int characNameId)
{
  if (characNameId == 0) characName = "Hibiki";
  else if (characNameId == 1) characName = "Akatsuki";
  else if (characNameId == 2) characName = "Inazuma";
  else if (characNameId == 3) characName = "Ikazuchi";
  if (!imageStandLeft.loadFromFile("Images/" + characName + "Stand090.png"))
    {
      std::cout << "Error, character's image not found. Exitting..." << std::endl;
      exit (1);
    }
  imageStandLeft.createMaskFromColor(sf::Color(40, 87, 43), 0);
  if (!imageStandRight.loadFromFile("Images/" + characName + "Stand270.png"))
    {
      std::cout << "Error, character's image not found. Exitting..." << std::endl;
      exit (1);
    }
  imageStandRight.createMaskFromColor(sf::Color(40, 87, 43), 0);
  if (!texture.create(45, 60))
    {
      std::cout << "Error, unable to create texture. Exitting..." << std::endl;
      exit(1);
    }
  texture.update(imageStandLeft);
  sprite.setTexture(texture);
}

void	Player::display(sf::RenderWindow &w)
{
  sf::RectangleShape rect;
  sprite.setPosition(pos);
  w.draw(sprite);
}

void	Player::fall(const unsigned int yWin)
{
  const float gravity = 0.3f;
  if (pos.y + size.y < yWin)
    {
      upSpeed += gravity * 80;
    }
}

void	Player::move(const unsigned int yWin, const unsigned int xWin, bool roof, bool floorDamage)
{
  if (floorDamage)
    {
      if (isInFloor == false && pos.y + size.y == yWin)
	{
	  isInFloor = true;
	  stayFloor = std::chrono::system_clock::now();
	}
      else if (isInFloor == true && pos.y + size.y < yWin)
	isInFloor = false;
      else if (isInFloor == true && std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-stayFloor).count() > 2000)
	{
	  const int	damage  = 50;
	  stayFloor = std::chrono::system_clock::now();
	  if ((int)life - damage < 0)
	    life = 0;
	  else
	    life -= damage;
	}
    }
  if (roof)
    if (pos.y < 0)
      pos.y = 0;

  const float gravity = 0.3f;
  const float friction = 0.2f;
  if (pos.y + size.y < yWin || upSpeed < 0) // jump and gravity
    {
      upSpeed += gravity; // While character is on the air, more gravity are on him, allow that he won't stay in midair
      if (pos.y + upSpeed + size.y > yWin)
	{
	  pos.y = yWin - size.y;
	  upSpeed = 0;
	}
      else
	pos.y += upSpeed;
    }
  if (pos.y + size.y == yWin && canDoubleJump == false)
    canDoubleJump = true;
  if (horSpeed != 0) // horizontal speed
    {
      pos.x += horSpeed;
      if (pos.x < 0)
	{
	  pos.x = 0;
	  horSpeed = 0;
	}
      else if (pos.x + size.x > xWin)
	{
	  pos.x = xWin - size.x;
	  horSpeed = 0;
	}
      if (horSpeed > 0) // if player move, we slower it so he won't feel like he's on ice
	horSpeed -= friction;
      else if (horSpeed < 0)
	horSpeed += friction;
    }
}

void	Player::goLeft()
{
  const float speedLimit = -20.0f;
  horSpeed -= speed;
  if (horSpeed < speedLimit)
    horSpeed = speedLimit;
  lookDirection = 1;
  texture.update(imageStandLeft);
}

void	Player::goRight()
{
  const float speedLimit = 20.0f;
  horSpeed += speed;
  if (horSpeed > speedLimit)
    horSpeed = speedLimit;
  lookDirection = 2;
  texture.update(imageStandRight);
}

void	Player::displayUi(sf::RenderWindow &w, int xPos)
{
  std::string textToDisplay = std::to_string(getLifePurcentage()) + "%";
  textLife.setString(textToDisplay);
  textLife.setPosition(xPos, 20);
  sf::RectangleShape lifeMaxRect;
  sf::RectangleShape lifeValueRect;
  sf::Vector2f sizeLifeMax(100, 10);
  sf::Vector2f sizeLifeValue((life * 100) / lifeMax, 10);
  lifeMaxRect.setPosition(xPos, 50);
  lifeMaxRect.setSize(sizeLifeMax);
  lifeValueRect.setPosition(xPos, 50);
  lifeValueRect.setSize(sizeLifeValue);
  lifeMaxRect.setFillColor(sf::Color::Black);
  lifeValueRect.setFillColor(sf::Color::Green);
  w.draw(lifeMaxRect);
  w.draw(lifeValueRect);
  w.draw(textLife);
}

void	Player::fire(unsigned int type)
{
  if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - lastShot).count() > beforeNextShot)
  {
    lastShot = std::chrono::system_clock::now();
    unsigned int m_size;
    sf::Color m_color;
    float m_lifeTime;
    int m_damage;
    float m_speed;
    unsigned int m_recul;
    float m_angle_movement;
    int decalage_x = (lookDirection == 1) ? (-5 - 1) : (size.x + 5 + 1);
    if (weapon[type - 1] == 0)
      {
	m_size = 5;
	m_color = sf::Color::Red;
	m_lifeTime = 10.0f;
	m_damage = 15;
	m_speed = 40;
	beforeNextShot = 200;
	m_recul = 20;
	m_angle_movement = M_PI * lookDirection;
	Projectile p(m_size, m_color, m_lifeTime, m_damage, pos.x + decalage_x, pos.y + size.y / 10, m_speed, m_angle_movement, m_recul);
	projs.push_back(p);
      }
    else if (weapon[type - 1] == 1)
      {
	m_size = 20;
	m_color = sf::Color::Cyan;
	m_lifeTime = 20.0f;
	m_damage = 30;
	m_speed = 10;
	beforeNextShot = 1000;
	m_recul = 50;
	m_angle_movement = M_PI * lookDirection;
	Projectile p(m_size, m_color, m_lifeTime, m_damage, pos.x + decalage_x, pos.y + size.y / 10, m_speed, m_angle_movement, m_recul);
	projs.push_back(p);
      }
    else if (weapon[type - 1] == 2)
      {
	m_size = 5;
	m_color = sf::Color(255, 215, 0); // Gold
	m_lifeTime = 0.5f;
	m_damage = 5;
	m_speed = 30;
	beforeNextShot = 1000;
	m_recul = 5;
	int direction;
	for (int i = 0 ; i < 10 ; i++)
	  {
	    direction = rand() % 32;
	    if (lookDirection == 1)
	      direction += 32;
	    else
	      direction -= 16;
	    m_angle_movement = M_PI / 48  * direction;
	    Projectile p(m_size, m_color, m_lifeTime, m_damage, pos.x + decalage_x, pos.y + size.y / 10, m_speed, m_angle_movement, m_recul);
	    projs.push_back(p);
	  }
      }
    else
	std::cout << "Error, attack undefined." << std::endl;
  }
}

void	Player::setWeapons(int weaponOne, int weaponTwo)
{
  weapon[0] = weaponOne;
  weapon[1] = weaponTwo;
}

void	Player::displayProjs(sf::RenderWindow &w)
{
  for (unsigned int i = 0 ; i < projs.size() ; i++)
      projs[i].display(w);
}

void	Player::moveProjs(const unsigned int xWin, const unsigned int yWin)
{
    for (unsigned int i = 0 ; i < projs.size() ; i++)
      projs[i].move(xWin, yWin);
}

void	Player::receiveDamages(Player &ennemy)
{
  int a = -1;
  for (unsigned int i = 0 ; i < ennemy.getProjs().size() ; i++)
    {
      if (isTouchByProjectile(ennemy.getProjs()[i]))
	{
	  if ((int)life - ennemy.getProjs()[i].getDamage() < 0)
	    life = 0;
	  else
	    life -= ennemy.getProjs()[i].getDamage();
	  if (cos(ennemy.getProjs()[i].getAngleMovement()) < 0)
	    horSpeed -= ennemy.getProjs()[i].getRecul();
	  else
	    horSpeed += ennemy.getProjs()[i].getRecul();
	  a = i;
	}
    }
  if (a > -1)
    ennemy.getProjs().erase(ennemy.getProjs().begin() + a);
}

void	Player::jump(const unsigned int yWin, const unsigned int xWin)
{
  const float jumpForce = 10.0f;
  const float muralJump = speed * 20;
  if (pos.y + size.y == yWin)
    {
      upSpeed -= jumpForce;
    }
  else if (pos.x == 0)
    { 
      upSpeed -= jumpForce / 1.5;
      horSpeed += muralJump;
    }
  else if (pos.x + size.x == xWin)
    {
      upSpeed -= jumpForce / 1.5;
      horSpeed -= muralJump;
    }
  else if (canDoubleJump)
    {
      upSpeed -= 2 * jumpForce / 3;
      canDoubleJump = false;
    }
}

bool	Player::isTouchByProjectile(Projectile proj)
{
  if ((proj.getPos().x + proj.getSize() < pos.x && proj.getNextMove().x > pos.x + size.x)
      || (proj.getPos().x  > pos.x + size.x && proj.getNextMove().x + proj.getSize() < pos.x))
    { // if projectile is too fast, frame 1 can be before character, and frame 2 after, then we'll need to calculate if the bullet would have touch him or not.
      const int	x_begin = proj.getPos().x;
      const int	y_begin = proj.getPos().y;
      const int	x_end = proj.getNextMove().x;
      const int	y_end = proj.getNextMove().y;
      const int	x_perso = pos.x + size.x / 2;
      const int	y_perso = pos.y + size.y / 2;
      const int	size_p = proj.getSize(); 
      bool		is_upper;
      
      int a = (y_end - y_begin) / (x_end - x_begin);
      int b = y_begin - a * x_begin;
      // ax + b
      
      if (a == 0)
	{
	  if (b > pos.y && b < pos.y + size.y)
	    return (true);
	  else
	    return (false);
	}
      
      if(a * x_perso + b > y_perso)
	is_upper = false;
      else
	is_upper = true;
      // Check if the character is upper or under the ball path
      
      int b2;
      if (is_upper)
	b2 = b - size_p;
      else
	b2 = b + size_p;
      // We will now check with extremity of the ball
      
      if (a * pos.x + b2 > pos.y
	  && a * pos.x + b2 < pos.y + size.y)
	return (true);
      else
	return (false);
    }
  else
    {
      if (proj.getPos().x + proj.getSize() < pos.x)
	return (false);
      else if (proj.getPos().x > pos.x + size.x)
	return (false);
      else if (proj.getPos().y + proj.getSize() < pos.y)
	return (false);
      else if (proj.getPos().y > pos.y + size.y)
	return (false);
      else
	return (true);
    }
}

bool	Player::getDoesGoRight()
{
  return (doesGoRight);
}

bool	Player::getDoesGoLeft()
{
  return (doesGoLeft);
}

void	Player::setDoesGoRight(bool value)
{
  doesGoRight = value;
}

void	Player::setDoesGoLeft(bool value)
{
  doesGoLeft = value;
}

sf::Vector2f	Player::getPosition()
{
  return (pos);
}

sf::Vector2f	Player::getSize()
{
  return (size);
}

std::vector<Projectile>	&Player::getProjs()
{
  return (projs);
}

unsigned int	Player::getLife()
{
  return (life);
}

unsigned int	Player::getLifePurcentage()
{
  return ((life * 100) / lifeMax);
}

int	Player::getLookDirection()
{
  return (lookDirection);
}

bool	Player::getCanDoubleJump()
{
  return (canDoubleJump);
}

void	Player::setController(int value)
{
  controller = value;
}

int	Player::getController()
{
  return (controller);
}

unsigned int	Player::getControllerId()
{
  return (controllerId);
}

void	Player::setControllerId(unsigned int value)
{
  controllerId = value;
}
