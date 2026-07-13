/*
 * Entry: 0040d25d
 * Name: SLFFriend::`scalar_deleting_destructor'
 * Namespace: SLFFriend
 * Signature: void * `scalar_deleting_destructor'(SLFFriend * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SLFFriend::_scalar_deleting_destructor_(SLFFriend *this,uint param_1)

{
  ArmoryProcess::~ArmoryProcess((ArmoryProcess *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
