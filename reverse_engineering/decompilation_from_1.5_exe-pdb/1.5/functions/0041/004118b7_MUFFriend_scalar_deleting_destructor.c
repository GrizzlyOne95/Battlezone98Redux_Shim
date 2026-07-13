/*
 * Entry: 004118b7
 * Name: MUFFriend::`scalar_deleting_destructor'
 * Namespace: MUFFriend
 * Signature: void * `scalar_deleting_destructor'(MUFFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall MUFFriend::_scalar_deleting_destructor_(MUFFriend *this,uint param_1)

{
  RecyclerProcess::~RecyclerProcess((RecyclerProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
