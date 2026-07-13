/*
 * Entry: 0053176c
 * Name: MagnetMine::MagnetMine
 * Namespace: MagnetMine
 * Signature: MagnetMine * MagnetMine(MagnetMine * this, _OBJ76 * param_1, MagnetMineClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MagnetMine * __thiscall
MagnetMine::MagnetMine(MagnetMine *this,_OBJ76 *param_1,MagnetMineClass *param_2)

{
  Mine::Mine((Mine *)this,param_1,(MineClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
