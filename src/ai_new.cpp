#include "player.hpp"
#include "ai.hpp"

void	iaCustom(Player *enemy, Player *me, const unsigned int xWin, const unsigned int yWin, unsigned int canFire)
{
  // The following line is mandatory, do NOT delete it or your AI won't work.
  Ai ai(me, enemy, xWin, yWin, canFire);

  if (ai.getXPosAiLeft() == 0)
    ai.jump();
  else if (ai.getXPosAiRight() == ai.getXSizeScreen())
    ai.jump();
  else if (abs(ai.getYPosAiUp() - ai.getYPosEnemyUp()) < 100)
    {
      if ((ai.getXPosAiLeft() < ai.getXPosEnemyLeft() && ai.getLookDirection() == 1) || (ai.getXPosAiLeft() > ai.getXPosEnemyLeft() && ai.getLookDirection() == -1))
	{
	  if (abs(ai.getXPosAiLeft() - ai.getXPosEnemyLeft()) < 200)
	    ai.fireBlue();
	  else
	    ai.fireRed();
	}
      else if (ai.getXPosAiLeft() < ai.getXPosEnemyLeft())
	ai.moveRight();
      else
	ai.moveLeft();
    }
  else if (ai.getYPosEnemyDown() > ai.getYSizeScreen() / 2)
    {
      if (ai.getXPosAiLeft() < ai.getXPosEnemyLeft())
	ai.moveLeft();
      else
	ai.moveRight();
    }
  else
    ai.jump();
}
