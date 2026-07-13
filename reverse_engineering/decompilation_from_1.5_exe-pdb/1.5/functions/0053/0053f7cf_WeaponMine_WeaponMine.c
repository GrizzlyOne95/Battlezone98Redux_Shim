/*
 * Entry: 0053f7cf
 * Name: WeaponMine::WeaponMine
 * Namespace: WeaponMine
 * Signature: WeaponMine * WeaponMine(WeaponMine * this, _OBJ76 * param_1, WeaponMineClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

WeaponMine * __thiscall
WeaponMine::WeaponMine(WeaponMine *this,_OBJ76 *param_1,WeaponMineClass *param_2)

{
  Mine::Mine((Mine *)this,param_1,(MineClass *)param_2);
  this->weapon = (Weapon *)0x0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  return this;
}
