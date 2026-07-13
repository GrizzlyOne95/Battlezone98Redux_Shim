/*
 * Entry: 0049f9cf
 * Name: Minelayer::Minelayer
 * Namespace: Minelayer
 * Signature: Minelayer * Minelayer(Minelayer * this, _OBJ76 * param_1, MinelayerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Minelayer * __thiscall Minelayer::Minelayer(Minelayer *this,_OBJ76 *param_1,MinelayerClass *param_2)

{
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->mineRad = param_2->mineDist;
  this->mineStep = *(float *)&param_2->field_0x3c4;
  this->mineDist = (float)param_2[1]._padding_;
  return this;
}
