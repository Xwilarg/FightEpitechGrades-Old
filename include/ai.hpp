/************************************************************\
 **                                                        **
 **                                                        **
 **                   API to make an AI                    **
 **                                                        **
 **      Please do NOT change this file, or it will        **
 **                    no longer work                      **
 **                                                        **
 **                  Instructions bellow...                **
 **                                                        **
\************************************************************/

#ifndef AI_HPP_
# define AI_HPP_

#include "player.hpp"

void	iaPlay(Player *pOne, Player *pTwo, const unsigned int xWin, const unsigned int yWin, unsigned int canFire);
void	iaCustom(Player *enemy, Player *me, const unsigned int xWin, const unsigned int yWin, unsigned int canFire);

class Ai
{
 public:
  // Do NOT use the following 2 lines, or your program won't work.
  Ai(Player *m_me, Player *m_enemy, const unsigned int m_xWin, const unsigned int m_yWin, unsigned int m_canFire);
  ~Ai();
  
  /**
   ** Allow the AI to jump.
   ** If against a wall, will wall-jump.
   ** If already in air, will double-jump.
   **/
  void		jump();

  /**
   ** Allow the AI to fall.
   ** That will make him go lower way faster.
   **/
  void		fall();

  /**
   ** Allow the AI to shoot.
   ** The red ball is faster than the blue one, it reloading time is also smaller.
   ** However, the blue ball deal more damage and is bigger.
   **/
  void		fireRed();
  void		fireBlue();

  /**
   ** Allow the AI to move left or right.
   ** The AI will continue to move in this direction until another action is done.
   **/
  void		moveLeft();
  void		moveRight();

  // Generate a random number from 1 to max.
  int		randomNumber(int max);

  // Is an enemy projectile near the AI ?
  // You must give in parameter the distance you want to check.
  // For the lasts functions, you can choose to give one or two/four distances.
  // For a y axis, upper distance is calculate from the upper corner of the character, lower distance in calculate with lower corner.
  // Same logic with x axis
  bool		isAProjectileUnderMe(unsigned int distance);
  bool		isAProjectileUpperMe(unsigned int distance);
  bool		isAProjectileLeftToMe(unsigned int distance);
  bool		isAProjectileRightToMe(unsigned int distance);
  bool		isAProjectileNearAxisXMe(unsigned int distance);
  bool		isAProjectileNearAxisXMe(unsigned int distanceLeft, unsigned int distanceRight);
  bool		isAProjectileNearAxisYMe(unsigned int distance);
  bool		isAProjectileNearAxisYMe(unsigned int distanceUp, unsigned int distanceDown);
  bool		isAProjectileNearMe(unsigned int distance);
  bool		isAProjectileNearMe(unsigned int distanceUp, unsigned int distanceDown, unsigned int distanceRight, unsigned int distanceLeft);

  // Life is in percentage
  unsigned int	getLifeMe();
  unsigned int	getLifeEnemy();

  // Get the direction where the AI is looking at.
  // -1 if he look on his right, 1 for his left.
  // Very important since a character shoot where he is actually looking.
  int		getLookDirection();

  // return true if the AI can do a second jump, else return false
  bool		canDoubleJump();

  // Size x and y of the characters
  unsigned int	getXSizePerso();
  unsigned int	getYSizePerso();

  // Size x and y of the screen
  // WARNING: x max is at the left of your screen and y max is at the bottom of it
  unsigned int	getXSizeScreen();
  unsigned int	getYSizeScreen();
  
  // x and y position of the characters
  unsigned int	getYPosAiDown();
  unsigned int	getXPosAiLeft();
  unsigned int	getYPosEnemyDown();
  unsigned int	getXPosEnemyLeft();
  unsigned int	getYPosAiUp();
  unsigned int	getXPosAiRight();
  unsigned int	getYPosEnemyUp();
  unsigned int	getXPosEnemyRight();

 private:
  Player	*me;
  Player	*enemy;
  unsigned int	canFire;
  unsigned int	xWin;
  unsigned int	yWin;
};

#endif /* !AI_HPP_ */
