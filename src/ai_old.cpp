#include "player.hpp"
#include "ai.hpp"

void	iaPlay(Player *pOne, Player *pTwo, const unsigned int xWin, const unsigned int yWin, unsigned int canFire)
{
  for (unsigned int i = 0 ; i < pOne->getProjs().size() ; i++)
    {
      if (pTwo->getPosition().y < 200 - pOne->getProjs()[i].getPos().y
	  && abs(pOne->getProjs()[i].getPos().x - pTwo->getPosition().x) < 150
	  && pTwo->getPosition().y + pTwo->getSize().y < yWin - 150)
	{
	  pTwo->setDoesGoLeft(false);
	  pTwo->setDoesGoRight(false);
	  pTwo->fall(yWin);
	  return ;
	}
      else if (abs(pOne->getProjs()[i].getPos().x - pTwo->getPosition().x) < 100
	       && pOne->getProjs()[i].getPos().y - pTwo->getPosition().y < 120
	       && (pTwo->getPosition().y + pTwo->getSize().y == yWin
		   || (pTwo->getPosition().y + pTwo->getSize().y > yWin - 150 && pTwo->getCanDoubleJump())))
	{
	  bool dontJump = false;
	  for (unsigned int y = 0 ; y < pOne->getProjs().size() ; y++)
	    {
	      if (pOne->getProjs()[i].getPos().y - pTwo->getPosition().y < 0 && pOne->getProjs()[i].getPos().y - pTwo->getPosition().y > -200)
		{
		  dontJump = true;
		  break;
		}
	    }
	  if (dontJump) break;
	  pTwo->setDoesGoLeft(false);
	  pTwo->setDoesGoRight(false);
	  pTwo->jump(yWin, xWin);
	  return ;
	}
	       }
  if ((pTwo->getPosition().x == 0 || pTwo->getPosition().x + pTwo->getSize().x == xWin || (pTwo->getPosition().y + pTwo->getSize().y == yWin && pOne->getPosition().y > yWin / 2)))
    {
      pTwo->jump(yWin, xWin);
      pTwo->setDoesGoLeft(false);
      pTwo->setDoesGoRight(false);
    }
  else if (abs(pOne->getPosition().x - pTwo->getPosition().x) < 50 &&
	   abs(pOne->getPosition().y - pTwo->getPosition().y) < 50)
    {
      int nbRandom = rand() % 2;
      if (nbRandom == 1)
	{
	  pTwo->setDoesGoLeft(true);
	  pTwo->setDoesGoRight(false);
	}
      else
	{
	  pTwo->setDoesGoLeft(false);
	  pTwo->setDoesGoRight(true);
	}
    }
  else if (pTwo->getPosition().x < 100 && pTwo->getPosition().x + pTwo->getSize().x > yWin - 100)
    {
      pTwo->setDoesGoLeft(true);
      pTwo->setDoesGoRight(false);
    }
  else if (pTwo->getPosition().x > xWin - 200 && pTwo->getPosition().x + pTwo->getSize().x < yWin - 100)
    {
      pTwo->setDoesGoLeft(false);
      pTwo->setDoesGoRight(true);
    }
  else if (abs(pTwo->getPosition().y - pOne->getPosition().y) < 100 && canFire == 0)
    {
      if (pTwo->getPosition().x > pOne->getPosition().x && pTwo->getLookDirection() == 2)
	{
	  pTwo->setDoesGoLeft(true);
	  pTwo->setDoesGoRight(false);
	}
      else if (pTwo->getPosition().x < pOne->getPosition().x && pTwo->getLookDirection() == 1)
	{
	  pTwo->setDoesGoLeft(false);
	  pTwo->setDoesGoRight(true);
	}
      else
	{
	  int nbRandom = rand() % 2;
	  if (abs(pTwo->getPosition().x - pOne->getPosition().x) < 50 || (nbRandom == 1 && pTwo->getPosition().y + pTwo->getSize().y > yWin - 200 && abs(pTwo->getPosition().x - pOne->getPosition().x) > 400))
	    pTwo->fire(2);
	  else
	    pTwo->fire(1);
	  pTwo->setDoesGoLeft(false);
	  pTwo->setDoesGoRight(false);
	}
    }
  else if (pOne->getPosition().y + pOne->getSize().y < yWin && pTwo->getPosition().x < xWin / 2)
    {
      pTwo->setDoesGoLeft(true);
      pTwo->setDoesGoRight(false);
    }
  else if (pOne->getPosition().y + pOne->getSize().y < yWin)
    {
      pTwo->setDoesGoLeft(false);
      pTwo->setDoesGoRight(true);
    }
  else if (pTwo->getPosition().x < pOne->getPosition().x)
    {
      pTwo->setDoesGoLeft(true);
      pTwo->setDoesGoRight(false);
    }
  else
    {
      pTwo->setDoesGoLeft(false);
      pTwo->setDoesGoRight(true);
    }
}
