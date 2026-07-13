/*
 * Entry: 00558a43
 * Name: GameSessionList::`scalar_deleting_destructor'
 * Namespace: GameSessionList
 * Signature: void * `scalar_deleting_destructor'(GameSessionList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GameSessionList::_scalar_deleting_destructor_(GameSessionList *this,uint param_1)

{
  SessionList::~SessionList((SessionList *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
