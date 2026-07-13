/*
 * Entry: 0049f5d9
 * Name: Howitzer::Howitzer
 * Namespace: Howitzer
 * Signature: Howitzer * Howitzer(Howitzer * this, _OBJ76 * param_1, HowitzerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Howitzer * __thiscall Howitzer::Howitzer(Howitzer *this,_OBJ76 *param_1,HowitzerClass *param_2)

{
  TurretTank::TurretTank((TurretTank *)this,param_1,(TurretTankClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
