/*
 * Entry: 0040bf88
 * Name: APCFriend::`scalar_deleting_destructor'
 * Namespace: APCFriend
 * Signature: void * `scalar_deleting_destructor'(APCFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall APCFriend::_scalar_deleting_destructor_(APCFriend *this,uint param_1)

{
  APCProcess::~APCProcess((APCProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
