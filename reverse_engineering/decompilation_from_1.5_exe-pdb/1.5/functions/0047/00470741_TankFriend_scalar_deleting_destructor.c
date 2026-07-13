/*
 * Entry: 00470741
 * Name: TankFriend::`scalar_deleting_destructor'
 * Namespace: TankFriend
 * Signature: void * `scalar_deleting_destructor'(TankFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TankFriend::_scalar_deleting_destructor_(TankFriend *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
