/*
 * Entry: 0055c1b3
 * Name: PlayerList::`scalar_deleting_destructor'
 * Namespace: PlayerList
 * Signature: void * `scalar_deleting_destructor'(PlayerList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PlayerList::_scalar_deleting_destructor_(PlayerList *this,uint param_1)

{
  ~PlayerList(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
