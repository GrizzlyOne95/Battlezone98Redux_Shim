/*
 * Entry: 0047e8c0
 * Name: Armory::Armory
 * Namespace: Armory
 * Signature: Armory * Armory(Armory * this, _OBJ76 * param_1, ArmoryClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Armory * __thiscall Armory::Armory(Armory *this,_OBJ76 *param_1,ArmoryClass *param_2)

{
  GameObjectClass *pGVar1;
  int iVar2;
  
  Producer::Producer((Producer *)this,param_1,(ProducerClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  iVar2 = 0;
  do {
    pGVar1 = param_2->cannonItem[iVar2 + -0x14];
    if (pGVar1 != (GameObjectClass *)0x0) {
      if (pGVar1->sig == 0x414d4d4f) {
        this->reloadItem = pGVar1;
      }
      else if (pGVar1->sig == 0x524b4954) {
        this->repairItem = pGVar1;
      }
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 9);
  iVar2 = this->_padding_;
  this->menu = MENU_NORMAL;
  (this->launchTarget).x = 0.0;
  (this->launchTarget).y = 0.0;
  (this->launchTarget).z = 0.0;
  if (iVar2 != 0) {
    *(undefined4 *)(iVar2 + 4) = 0;
  }
  return this;
}
