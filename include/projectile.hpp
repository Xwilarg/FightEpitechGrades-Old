#ifndef PROJECTILE_HPP_
# define PROJECTILE_HPP_

# include <SFML/Graphics.hpp>
# include <SFML/System.hpp>
# include <cmath>

class Projectile
{
public:
  Projectile(unsigned int m_size, sf::Color m_color, float m_lifeTime, int m_damage, unsigned int m_x, unsigned int m_y, float m_speed, float m_angleMovement, unsigned int m_recul);
  ~Projectile();
  void	display(sf::RenderWindow &w);
  void	move(const unsigned int xWin, const unsigned int yWin);
  unsigned int getSize();
  sf::Vector2f getPos();
  sf::Vector2f getNextMove();
  float	getAngleMovement();
  unsigned int	getRecul();
  int	getDamage();

private:
  unsigned int	size;
  sf::Color	color;
  float		lifeTime;
  int		damage;
  sf::Vector2f	pos;
  float		angleMovement;
  float		speed;
  unsigned int	recul;
};

#endif /* !PROJECTILE_HPP_ */
