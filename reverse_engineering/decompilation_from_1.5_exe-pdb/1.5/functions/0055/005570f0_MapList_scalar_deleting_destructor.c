/*
 * Entry: 005570f0
 * Name: MapList::`scalar_deleting_destructor'
 * Namespace: MapList
 * Signature: void * `scalar_deleting_destructor'(MapList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MapList::_scalar_deleting_destructor_(MapList *this,uint param_1)

{
  StopAnim(this);
  Init(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
