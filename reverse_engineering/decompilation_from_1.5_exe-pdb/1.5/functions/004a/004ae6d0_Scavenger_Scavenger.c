/*
 * Entry: 004ae6d0
 * Name: Scavenger::Scavenger
 * Namespace: Scavenger
 * Signature: Scavenger * Scavenger(Scavenger * this, _OBJ76 * param_1, ScavengerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Scavenger * __thiscall Scavenger::Scavenger(Scavenger *this,_OBJ76 *param_1,ScavengerClass *param_2)

{
  int iVar1;
  
  HoverCraft::HoverCraft((HoverCraft *)this,param_1,(HoverCraftClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  iVar1 = *(int *)(param_2->soundPickup + 4);
  this->delayTimer = 0.0;
  this->scrapHeld = 0;
  this->_padding_ = 0;
  this->animHandle = -1;
  this->maxScrap = iVar1;
  return this;
}
