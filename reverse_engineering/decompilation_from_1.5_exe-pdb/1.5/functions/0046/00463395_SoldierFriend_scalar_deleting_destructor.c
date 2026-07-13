/*
 * Entry: 00463395
 * Name: SoldierFriend::`scalar_deleting_destructor'
 * Namespace: SoldierFriend
 * Signature: void * `scalar_deleting_destructor'(SoldierFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SoldierFriend::_scalar_deleting_destructor_(SoldierFriend *this,uint param_1)

{
  SoldierProcess::~SoldierProcess((SoldierProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
