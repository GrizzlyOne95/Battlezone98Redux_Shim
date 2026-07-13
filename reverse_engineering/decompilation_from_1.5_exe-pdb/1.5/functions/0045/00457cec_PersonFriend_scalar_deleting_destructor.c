/*
 * Entry: 00457cec
 * Name: PersonFriend::`scalar_deleting_destructor'
 * Namespace: PersonFriend
 * Signature: void * `scalar_deleting_destructor'(PersonFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall PersonFriend::_scalar_deleting_destructor_(PersonFriend *this,uint param_1)

{
  PersonProcess::~PersonProcess((PersonProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
