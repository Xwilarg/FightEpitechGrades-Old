#include "projectile.hpp"

Projectile::Projectile(unsigned int m_size, sf::Color m_color, float m_lifeTime, int m_damage, unsigned int m_x, unsigned m_y, float m_speed, float m_angleMovement, unsigned int m_recul)
{
  size = m_size;
  color = m_color;
  pos.x = m_x;
  pos.y = m_y;
  speed = m_speed;
  angleMovement = m_angleMovement;
  lifeTime = m_lifeTime;
  damage = m_damage;
  recul = m_recul;
}

Projectile::~Projectile()
{}

void	Projectile::display(sf::RenderWindow &w)
{
  sf::CircleShape proj;
  proj.setPosition(pos);
  proj.setRadius(size);
  proj.setFillColor(color);
  w.draw(proj);
}

void	Projectile::move(const unsigned int xWin, const unsigned int yWin)
{
  pos.x += cos(angleMovement) * speed;
  pos.y += sin(angleMovement) * speed;
}

sf::Vector2f	Projectile::getNextMove()
{
  sf::Vector2f nextPos(0, 0);
  nextPos.x = pos.x + cos(angleMovement) * speed;
  nextPos.y = pos.y + sin(angleMovement) * speed;
  return (nextPos);
}

unsigned int	Projectile::getSize()
{
  return (size);
}

sf::Vector2f	Projectile::getPos()
{
  return (pos);
}

float	Projectile::getAngleMovement()
{
  return (angleMovement);
}

unsigned int	Projectile::getRecul()
{
  return (recul);
}

int	Projectile::getDamage()
{
  return (damage);
}
