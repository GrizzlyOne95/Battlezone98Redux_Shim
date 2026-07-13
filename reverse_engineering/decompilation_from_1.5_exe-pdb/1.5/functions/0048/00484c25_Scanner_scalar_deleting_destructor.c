/*
 * Entry: 00484c25
 * Name: Scanner::`scalar_deleting_destructor'
 * Namespace: Scanner
 * Signature: void * `scalar_deleting_destructor'(Scanner * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Scanner::_scalar_deleting_destructor_(Scanner *this,uint param_1)

{
  ~Scanner(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
