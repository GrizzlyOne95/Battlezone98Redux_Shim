/*
 * Entry: 00470dfd
 * Name: WingmanBlastAttack::`scalar_deleting_destructor'
 * Namespace: WingmanBlastAttack
 * Signature: void * `scalar_deleting_destructor'(WingmanBlastAttack * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall
WingmanBlastAttack::_scalar_deleting_destructor_(WingmanBlastAttack *this,uint param_1)

{
  ~WingmanBlastAttack(this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
