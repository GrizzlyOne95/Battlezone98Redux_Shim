/*
 * Entry: 0047f03d
 * Name: ArmoryClass::ArmoryClass
 * Namespace: ArmoryClass
 * Signature: ArmoryClass * ArmoryClass(ArmoryClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ArmoryClass * __thiscall ArmoryClass::ArmoryClass(ArmoryClass *this)

{
  int iVar1;
  int iVar2;
  GameObjectClass **ppGVar3;
  
  ProducerClass::ProducerClass((ProducerClass *)this);
  this->_padding_ = 3;
  this->_padding_ = 3;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x41524d52;
  this->_padding_ = (int)"armory";
  iVar2 = 9;
  ppGVar3 = this->cannonItem + 2;
  for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppGVar3 = (GameObjectClass *)0x0;
    ppGVar3 = ppGVar3 + 1;
  }
  ppGVar3 = this->rocketItem + 2;
  for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppGVar3 = (GameObjectClass *)0x0;
    ppGVar3 = ppGVar3 + 1;
  }
  ppGVar3 = this->mortarItem + 2;
  for (iVar1 = iVar2; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppGVar3 = (GameObjectClass *)0x0;
    ppGVar3 = ppGVar3 + 1;
  }
  ppGVar3 = this->specialItem + 2;
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    *ppGVar3 = (GameObjectClass *)0x0;
    ppGVar3 = ppGVar3 + 1;
  }
  return this;
}
