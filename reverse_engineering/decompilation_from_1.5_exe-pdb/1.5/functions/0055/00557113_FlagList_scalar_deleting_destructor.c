/*
 * Entry: 00557113
 * Name: FlagList::`scalar_deleting_destructor'
 * Namespace: FlagList
 * Signature: void * `scalar_deleting_destructor'(FlagList * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall FlagList::_scalar_deleting_destructor_(FlagList *this,uint param_1)

{
  ~FlagList(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
