/*
 * Entry: 0055af09
 * Name: ServerList::`scalar_deleting_destructor'
 * Namespace: ServerList
 * Signature: void * `scalar_deleting_destructor'(ServerList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ServerList::_scalar_deleting_destructor_(ServerList *this,uint param_1)

{
  ~ServerList(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
