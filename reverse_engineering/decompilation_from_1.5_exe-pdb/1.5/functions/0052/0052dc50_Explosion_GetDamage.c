/*
 * Entry: 0052dc50
 * Name: Explosion::GetDamage
 * Namespace: Explosion
 * Signature: DAMAGE * GetDamage(Explosion * this, DAMAGE * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

DAMAGE * __thiscall Explosion::GetDamage(Explosion *this,DAMAGE *__return_storage_ptr__)

{
  __return_storage_ptr__->damager = (this->damage).damager;
  __return_storage_ptr__->dmg_source = (this->damage).dmg_source;
  *(undefined4 *)&__return_storage_ptr__->field_0x8 = *(undefined4 *)&(this->damage).field_0x8;
  __return_storage_ptr__->dmg_value = (this->damage).dmg_value;
  return __return_storage_ptr__;
}
