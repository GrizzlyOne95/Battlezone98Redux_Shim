/*
 * Entry: 004b6b60
 * Name: Walker::Walker
 * Namespace: Walker
 * Signature: Walker * Walker(Walker * this, _OBJ76 * param_1, WalkerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Walker * __thiscall Walker::Walker(Walker *this,_OBJ76 *param_1,WalkerClass *param_2)

{
  Craft::Craft((Craft *)this,param_1,(CraftClass *)param_2);
  this->_padding_ = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->curAnim = 2;
  AnimObj_Start(param_1,2,&this->animHandle);
  this->_padding_ = 1;
  return this;
}
