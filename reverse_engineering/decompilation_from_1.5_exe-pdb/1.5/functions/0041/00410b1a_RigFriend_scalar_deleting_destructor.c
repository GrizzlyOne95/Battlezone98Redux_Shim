/*
 * Entry: 00410b1a
 * Name: RigFriend::`scalar_deleting_destructor'
 * Namespace: RigFriend
 * Signature: void * `scalar_deleting_destructor'(RigFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RigFriend::_scalar_deleting_destructor_(RigFriend *this,uint param_1)

{
  RigProcess::~RigProcess((RigProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
