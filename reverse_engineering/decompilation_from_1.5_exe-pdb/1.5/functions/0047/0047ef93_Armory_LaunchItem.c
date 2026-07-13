/*
 * Entry: 0047ef93
 * Name: Armory::LaunchItem
 * Namespace: Armory
 * Signature: bool LaunchItem(Armory * this, GameObjectClass * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall Armory::LaunchItem(Armory *this,GameObjectClass *param_1,VECTOR_3D *param_2)

{
  bool bVar1;
  
  if (((param_2 == (VECTOR_3D *)0x0) || (this->_padding_ == 0)) ||
     (*(int *)(this->_padding_ + 0x34) == 0)) {
    bVar1 = false;
  }
  else {
    AnimObj_Start((void *)this->_padding_,4,&this->_padding_);
    (this->launchTarget).x = param_2->x;
    (this->launchTarget).y = param_2->y;
    (this->launchTarget).z = param_2->z;
    bVar1 = Producer::StartBuild((Producer *)this,param_1);
    if (bVar1) {
      this->_padding_ = 0x3eb33333;
    }
  }
  return bVar1;
}
