/*
 * Entry: 00539cf3
 * Name: SniperShell::`scalar_deleting_destructor'
 * Namespace: SniperShell
 * Signature: void * `scalar_deleting_destructor'(SniperShell * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall SniperShell::_scalar_deleting_destructor_(SniperShell *this,uint param_1)

{
  *(undefined ***)this = &_vftable_;
  Bullet::~Bullet((Bullet *)this);
  if ((param_1 & 1) != 0) {
    operator_delete(this);
  }
  return this;
}
