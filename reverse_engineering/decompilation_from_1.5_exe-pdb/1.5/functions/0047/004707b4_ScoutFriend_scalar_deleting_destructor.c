/*
 * Entry: 004707b4
 * Name: ScoutFriend::`scalar_deleting_destructor'
 * Namespace: ScoutFriend
 * Signature: void * `scalar_deleting_destructor'(ScoutFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScoutFriend::_scalar_deleting_destructor_(ScoutFriend *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
