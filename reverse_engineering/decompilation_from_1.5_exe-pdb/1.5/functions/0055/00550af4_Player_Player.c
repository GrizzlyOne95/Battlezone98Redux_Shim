/*
 * Entry: 00550af4
 * Name: Player::Player
 * Namespace: Player
 * Signature: Player * Player(Player * this, char * param_1, ushort param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Player * __thiscall Player::Player(Player *this,char *param_1,ushort param_2)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)this - (int)param_1;
  do {
    cVar1 = *param_1;
    param_1[iVar2] = cVar1;
    param_1 = param_1 + 1;
  } while (cVar1 != '\0');
  this->dwLastPingSendTime = 0;
  this->launched = false;
  this->hostlaunched = false;
  this->InGame = false;
  this->sendresult = '\0';
  this->avg_ms = 0;
  this->loss_pct = 0;
  this->mute = false;
  this->pinfo = (PlayerInfo *)0x0;
  this->id = param_2;
  this->mark = 1;
  return this;
}
