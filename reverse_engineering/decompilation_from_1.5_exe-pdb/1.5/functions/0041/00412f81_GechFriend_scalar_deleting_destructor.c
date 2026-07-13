/*
 * Entry: 00412f81
 * Name: GechFriend::`scalar_deleting_destructor'
 * Namespace: GechFriend
 * Signature: void * `scalar_deleting_destructor'(GechFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall GechFriend::_scalar_deleting_destructor_(GechFriend *this,uint param_1)

{
  GechProcess::~GechProcess((GechProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
