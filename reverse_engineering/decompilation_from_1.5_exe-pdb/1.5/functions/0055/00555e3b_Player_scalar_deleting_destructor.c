/*
 * Entry: 00555e3b
 * Name: Player::`scalar_deleting_destructor'
 * Namespace: Player
 * Signature: void * `scalar_deleting_destructor'(Player * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Player::_scalar_deleting_destructor_(Player *this,uint param_1)

{
  ~Player(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
