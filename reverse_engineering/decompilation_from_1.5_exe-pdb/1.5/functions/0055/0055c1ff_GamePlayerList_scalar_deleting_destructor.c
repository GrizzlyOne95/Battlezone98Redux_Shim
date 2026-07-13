/*
 * Entry: 0055c1ff
 * Name: GamePlayerList::`scalar_deleting_destructor'
 * Namespace: GamePlayerList
 * Signature: void * `scalar_deleting_destructor'(GamePlayerList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GamePlayerList::_scalar_deleting_destructor_(GamePlayerList *this,uint param_1)

{
  PlayerList::~PlayerList((PlayerList *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
