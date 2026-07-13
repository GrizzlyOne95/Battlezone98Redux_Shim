/*
 * Entry: 004599a9
 * Name: RecyclerFriend::`scalar_deleting_destructor'
 * Namespace: RecyclerFriend
 * Signature: void * `scalar_deleting_destructor'(RecyclerFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall RecyclerFriend::_scalar_deleting_destructor_(RecyclerFriend *this,uint param_1)

{
  RecyclerProcess::~RecyclerProcess((RecyclerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
