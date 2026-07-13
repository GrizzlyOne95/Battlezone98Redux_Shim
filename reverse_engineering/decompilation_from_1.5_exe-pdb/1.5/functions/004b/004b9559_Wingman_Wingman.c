/*
 * Entry: 004b9559
 * Name: Wingman::Wingman
 * Namespace: Wingman
 * Signature: Wingman * Wingman(Wingman * this, _OBJ76 * param_1, WingmanClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Wingman * __thiscall Wingman::Wingman(Wingman *this,_OBJ76 *param_1,WingmanClass *param_2)

{
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  *(undefined ***)this = &_vftable__for__Attachable__;
  *(undefined ***)&this->field_0x20 = &_vftable__for__DistributedObject__;
  return this;
}
