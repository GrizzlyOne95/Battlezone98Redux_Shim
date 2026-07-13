/*
 * Entry: 0053f999
 * Name: WeaponMine::Explode
 * Namespace: WeaponMine
 * Signature: void Explode(WeaponMine * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall WeaponMine::Explode(WeaponMine *this)

{
  uint *puVar1;
  int iVar2;
  
  Carrier::SetSelected((Carrier *)this->_padding_,0);
  iVar2 = this->_padding_;
  *(undefined4 *)(iVar2 + 0x18) = 0;
  puVar1 = (uint *)(iVar2 + 0x2c);
  *puVar1 = *puVar1 & 0xfffffffe;
  Weapon::Remove((Weapon *)this->_padding_);
  this->_padding_ = 0;
  Building::Explode((Building *)this);
  return;
}
