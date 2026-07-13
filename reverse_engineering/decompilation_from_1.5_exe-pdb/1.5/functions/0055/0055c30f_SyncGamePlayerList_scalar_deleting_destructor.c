/*
 * Entry: 0055c30f
 * Name: SyncGamePlayerList::`scalar_deleting_destructor'
 * Namespace: SyncGamePlayerList
 * Signature: void * `scalar_deleting_destructor'(SyncGamePlayerList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
SyncGamePlayerList::_scalar_deleting_destructor_(SyncGamePlayerList *this,uint param_1)

{
  PlayerList::~PlayerList((PlayerList *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
