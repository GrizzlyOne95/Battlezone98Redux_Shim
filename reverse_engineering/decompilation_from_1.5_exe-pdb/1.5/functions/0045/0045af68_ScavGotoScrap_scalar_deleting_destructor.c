/*
 * Entry: 0045af68
 * Name: ScavGotoScrap::`scalar_deleting_destructor'
 * Namespace: ScavGotoScrap
 * Signature: void * `scalar_deleting_destructor'(ScavGotoScrap * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall ScavGotoScrap::_scalar_deleting_destructor_(ScavGotoScrap *this,uint param_1)

{
  ~ScavGotoScrap(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
