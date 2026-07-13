/*
 * Entry: 0049aee6
 * Name: Geizer::Geizer
 * Namespace: Geizer
 * Signature: Geizer * Geizer(Geizer * this, _OBJ76 * param_1, GeizerClass * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

Geizer * __thiscall Geizer::Geizer(Geizer *this,_OBJ76 *param_1,GeizerClass *param_2)

{
  uint *puVar1;
  
  Building::Building((Building *)this,param_1,(BuildingClass *)param_2);
  this->_padding_ = (int)&_vftable__for__Attachable__;
  this->_padding_ = (int)&_vftable__for__DistributedObject__;
  DeleteCollisionEntity((tagENTITY *)this->_padding_);
  *(undefined4 *)(this->_padding_ + 0x14) = 0x41200000;
  puVar1 = (uint *)(this->_padding_ + 0x14);
  *puVar1 = *puVar1 & 0xfffffbfe;
  this->isSteamOn = true;
  this->isLocked = false;
  param_2 = (GeizerClass *)this;
  std::vector<Geizer_*,std::allocator<Geizer_*>_>::push_back(&geizerList,(Geizer **)&param_2);
  this->smokeTimer = 0.0;
  this->smokeEmitter = smokeEffect.steamEmitter;
  return this;
}
