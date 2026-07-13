/*
 * Entry: 0047eff5
 * Name: Armory::FinishBuild
 * Namespace: Armory
 * Signature: GameObject * FinishBuild(Armory * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Armory::FinishBuild(Armory *this)

{
  ObjectLobber *this_00;
  
  this_00 = (ObjectLobber *)Carrier::GetWeapon((Carrier *)this->_padding_,0);
  ObjectLobber::SetTarget(this_00,&this->launchTarget);
  ObjectLobber::SetObjClass(this_00,(GameObjectClass *)this->_padding_);
  (**(code **)(this_00->_padding_ + 8))();
  this->_padding_ = 0;
  this->_padding_ = 0;
  return (GameObject *)0x0;
}
