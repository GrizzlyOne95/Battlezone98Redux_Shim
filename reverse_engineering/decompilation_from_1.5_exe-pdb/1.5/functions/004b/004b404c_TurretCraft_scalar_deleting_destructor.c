/*
 * Entry: 004b404c
 * Name: TurretCraft::`scalar_deleting_destructor'
 * Namespace: TurretCraft
 * Signature: void * `scalar_deleting_destructor'(TurretCraft * this, uint param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __thiscall TurretCraft::_scalar_deleting_destructor_(TurretCraft *this,uint param_1)

{
  Craft::~Craft((Craft *)this);
  if ((param_1 & 1) != 0) {
    GameObject::operator_delete(this);
  }
  return this;
}
