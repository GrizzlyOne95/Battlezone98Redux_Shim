/*
 * Entry: 00555e08
 * Name: Player::~Player
 * Namespace: Player
 * Signature: void ~Player(Player * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Player::~Player(Player *this)

{
  PlayerInfo *this_00;
  
  this_00 = this->pinfo;
  if (this_00 != (PlayerInfo *)0x0) {
    PlayerInfo::~PlayerInfo(this_00);
    operator_delete(this_00);
  }
  return;
}
