/*
 * Entry: 0047bd25
 * Name: AmmoPowerup::`scalar_deleting_destructor'
 * Namespace: AmmoPowerup
 * Signature: void * `scalar_deleting_destructor'(AmmoPowerup * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall AmmoPowerup::_scalar_deleting_destructor_(AmmoPowerup *this,uint param_1)

{
  PowerUp::~PowerUp((PowerUp *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
