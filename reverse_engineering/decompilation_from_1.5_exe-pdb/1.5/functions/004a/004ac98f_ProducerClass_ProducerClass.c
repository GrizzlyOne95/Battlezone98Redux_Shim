/*
 * Entry: 004ac98f
 * Name: ProducerClass::ProducerClass
 * Namespace: ProducerClass
 * Signature: ProducerClass * ProducerClass(ProducerClass * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ProducerClass * __thiscall ProducerClass::ProducerClass(ProducerClass *this)

{
  int iVar1;
  GameObjectClass **ppGVar2;
  
  HoverCraftClass::HoverCraftClass((HoverCraftClass *)this);
  this->_padding_ = 0x40400000;
  this->timeRepair = 5.0;
  this->healthRepair = 5.0;
  this->scrapHold = 0x3f800000;
  this->_padding_ = (int)&_vftable_;
  this->_padding_ = 0x50524f44;
  this->pilotHold = 0x42c80000;
  this->_padding_ = (int)"producer";
  this->_padding_ = 6;
  this->_padding_ = 0;
  this->buildItem[0] = (GameObjectClass *)0xa;
  this->buildItem[1] = (GameObjectClass *)0x0;
  ppGVar2 = this->buildItem + 2;
  for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
    *ppGVar2 = (GameObjectClass *)0x0;
    ppGVar2 = ppGVar2 + 1;
  }
  this->soundBuild[8] = '\0';
  this->soundFinish[8] = '\0';
  this->blockedGeyserMsg[8] = '\0';
  return this;
}
