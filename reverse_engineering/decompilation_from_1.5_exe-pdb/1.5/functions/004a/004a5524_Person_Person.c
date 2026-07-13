/*
 * Entry: 004a5524
 * Name: Person::Person
 * Namespace: Person
 * Signature: Person * Person(Person * this, _OBJ76 * param_1, PersonClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Person * __thiscall Person::Person(Person *this,_OBJ76 *param_1,PersonClass *param_2)

{
  VEHICLE *pVVar1;
  
  Craft::Craft((Craft *)this,param_1,(CraftClass *)param_2);
  this->_padding_ = 0;
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  this->_padding_ = (int)param_2;
  this->_padding_ = 2;
  this->curAnim = 2;
  AnimObj_Start((void *)this->_padding_,2,&this->animHandle);
  this->nextScream = 0.0;
  pVVar1 = get_obj_vhcl(param_1);
  this->_padding_ = (int)pVVar1;
  pVVar1->entity = (tagENTITY *)this->_padding_;
  *(Person **)(this->_padding_ + 0x118) = this;
  return this;
}
