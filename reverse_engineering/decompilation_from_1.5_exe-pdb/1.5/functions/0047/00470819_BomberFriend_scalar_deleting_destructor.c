/*
 * Entry: 00470819
 * Name: BomberFriend::`scalar_deleting_destructor'
 * Namespace: BomberFriend
 * Signature: void * `scalar_deleting_destructor'(BomberFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall BomberFriend::_scalar_deleting_destructor_(BomberFriend *this,uint param_1)

{
  WingmanProcess::~WingmanProcess((WingmanProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
