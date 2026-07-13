/*
 * Entry: 0053c8e1
 * Name: Torpedo::`scalar_deleting_destructor'
 * Namespace: Torpedo
 * Signature: void * `scalar_deleting_destructor'(Torpedo * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall Torpedo::_scalar_deleting_destructor_(Torpedo *this,uint param_1)

{
  PowerUp::~PowerUp((PowerUp *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
