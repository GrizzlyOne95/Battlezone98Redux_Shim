/*
 * Entry: 00466f97
 * Name: TugFriend::`scalar_deleting_destructor'
 * Namespace: TugFriend
 * Signature: void * `scalar_deleting_destructor'(TugFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TugFriend::_scalar_deleting_destructor_(TugFriend *this,uint param_1)

{
  TugProcess::~TugProcess((TugProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
