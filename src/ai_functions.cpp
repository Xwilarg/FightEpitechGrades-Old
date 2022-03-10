#include "player.hpp"
#include "ai.hpp"

Ai::Ai(Player *m_me, Player *m_enemy, const unsigned int m_xWin, const unsigned int m_yWin, unsigned m_canFire)
{
  me = m_me;
  enemy = m_enemy;
  canFire = m_canFire;
  xWin = m_xWin;
  yWin = m_yWin;
}

Ai::~Ai()
{}

int	Ai::randomNumber(int max)
{
  int	randomNb = rand() % max;
  randomNb++;
  return (randomNb);
}

void	Ai::moveRight()
{
  me->setDoesGoLeft(false);
  me->setDoesGoRight(true);
}

void	Ai::moveLeft()
{
  me->setDoesGoLeft(true);
  me->setDoesGoRight(false);
}

void	Ai::jump()
{
  me->jump(yWin, xWin);
  me->setDoesGoLeft(false);
  me->setDoesGoRight(false);
}

void	Ai::fall()
{
  me->fall(yWin);
  me->setDoesGoLeft(false);
  me->setDoesGoRight(false);
}

void	Ai::fireRed()
{
  me->fire(1);
  me->setDoesGoLeft(false);
  me->setDoesGoRight(false);
}

void	Ai::fireBlue()
{
  me->fire(2);
  me->setDoesGoLeft(false);
  me->setDoesGoRight(false);
}

bool	Ai::isAProjectileUpperMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) > 0
	  && getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) < distance)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileUnderMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (enemy->getProjs()[i].getPos().y - getYPosAiDown() > 0
	  && enemy->getProjs()[i].getPos().y - getYPosAiDown() < distance)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileNearAxisYMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) > 0
	  && getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) < distance)
	return (true);
      if (enemy->getProjs()[i].getPos().y - getYPosAiDown() > 0
	  && enemy->getProjs()[i].getPos().y - getYPosAiDown() < distance)
	return (true);
    }
  return (false);
}
bool	Ai::isAProjectileNearAxisYMe(unsigned int distanceUp, unsigned int distanceDown)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) > 0
	  && getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) < distanceUp)
	return (true);
      if (enemy->getProjs()[i].getPos().y - getYPosAiDown() > 0
	  && enemy->getProjs()[i].getPos().y - getYPosAiDown() < distanceDown)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileLeftToMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (enemy->getProjs()[i].getPos().x - getXPosAiLeft() > 0
	  && enemy->getProjs()[i].getPos().x - getXPosAiLeft() < distance)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileRightToMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) > 0
	  && getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) < distance)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileNearAxisXMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (enemy->getProjs()[i].getPos().x - getXPosAiLeft() > 0
	  && enemy->getProjs()[i].getPos().x - getXPosAiLeft() < distance)
	return (true);
      if (getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) > 0
	  && getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) < distance)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileNearAxisXMe(unsigned int distanceRight, unsigned int distanceLeft)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (enemy->getProjs()[i].getPos().x - getXPosAiLeft() > 0
	  && enemy->getProjs()[i].getPos().x - getXPosAiLeft() < distanceLeft)
	return (true);
      if (getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) > 0
	  && getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) < distanceRight)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileNearMe(unsigned int distanceUp, unsigned int distanceDown, unsigned int distanceRight, unsigned int distanceLeft)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) > 0
	  && getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) < distanceUp)
	return (true);
      if (enemy->getProjs()[i].getPos().y - getYPosAiDown() > 0
	  && enemy->getProjs()[i].getPos().y - getYPosAiDown() < distanceDown)
	return (true);
      if (enemy->getProjs()[i].getPos().x - getXPosAiLeft() > 0
	  && enemy->getProjs()[i].getPos().x - getXPosAiLeft() < distanceLeft)
	return (true);
      if (getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) > 0
	  && getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) < distanceRight)
	return (true);
    }
  return (false);
}

bool	Ai::isAProjectileNearMe(unsigned int distance)
{
  for (unsigned int i = 0 ; i < enemy->getProjs().size() ; i++)
    {
      if (getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) > 0
	  && getYPosAiUp() - (enemy->getProjs()[i].getPos().y + enemy->getProjs()[i].getSize()) < distance)
	return (true);
      if (enemy->getProjs()[i].getPos().y - getYPosAiDown() > 0
	  && enemy->getProjs()[i].getPos().y - getYPosAiDown() < distance)
	return (true);
      if (enemy->getProjs()[i].getPos().x - getXPosAiLeft() > 0
	  && enemy->getProjs()[i].getPos().x - getXPosAiLeft() < distance)
	return (true);
      if (getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) > 0
	  && getXPosAiRight() - (enemy->getProjs()[i].getPos().x + enemy->getProjs()[i].getSize()) < distance)
	return (true);
    }
  return (false);
}

unsigned int	Ai::getLifeMe()
{
  return (me->getLifePurcentage());
}
unsigned int	Ai::getLifeEnemy()
{
  return (enemy->getLifePurcentage());
}

bool		Ai::canDoubleJump()
{
  return (me->getCanDoubleJump());
}

int		Ai::getLookDirection()
{
  if (me->getLookDirection() == 1)
    return (-1);
  else
    return (1);
}

unsigned int	Ai::getXSizePerso()
{
  return (me->getSize().x);
}

unsigned int	Ai::getYSizePerso()
{
  return (me->getSize().x);
}

unsigned int	Ai::getXPosAiLeft()
{
  return (me->getPosition().x);
}

unsigned int	Ai::getYPosAiDown()
{
  return (me->getPosition().y + getYSizePerso());
}

unsigned int	Ai::getXPosEnemyLeft()
{
  return (enemy->getPosition().x);
}

unsigned int	Ai::getYPosEnemyDown()
{
  return (enemy->getPosition().y + getYSizePerso());
}

unsigned int	Ai::getXPosAiRight()
{
  return (me->getPosition().x + getXSizePerso());
}

unsigned int	Ai::getYPosAiUp()
{
  return (me->getPosition().y);
}

unsigned int	Ai::getXPosEnemyRight()
{
  return (enemy->getPosition().x + getXSizePerso());
}

unsigned int	Ai::getYPosEnemyUp()
{
  return (enemy->getPosition().y);
}

unsigned int	Ai::getXSizeScreen()
{
  return (xWin);
}

unsigned int	Ai::getYSizeScreen()
{
  return (yWin);
}
