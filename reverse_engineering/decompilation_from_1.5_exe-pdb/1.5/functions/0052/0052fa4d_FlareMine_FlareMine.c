/*
 * Entry: 0052fa4d
 * Name: FlareMine::FlareMine
 * Namespace: FlareMine
 * Signature: FlareMine * FlareMine(FlareMine * this, _OBJ76 * param_1, FlareMineClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

FlareMine * __thiscall FlareMine::FlareMine(FlareMine *this,_OBJ76 *param_1,FlareMineClass *param_2)

{
  Mine::Mine((Mine *)this,param_1,(MineClass *)param_2);
  this->owner = (_OBJ76 *)0x0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->shotTimer = -param_2->triggerDelay;
  return this;
}
