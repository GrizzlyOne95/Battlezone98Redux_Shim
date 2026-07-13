/*
 * Entry: 0048ff56
 * Name: DistributedObject::Explode
 * Namespace: DistributedObject
 * Signature: void Explode(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::Explode(DistributedObject *this)

{
  bool *pbVar1;
  _OBJ76 *p_Var2;
  int iVar3;
  
  if (this == (DistributedObject *)0x0) {
    pbVar1 = (bool *)0x0;
  }
  else {
    pbVar1 = &this[-1].net_user;
  }
  *(undefined4 *)(pbVar1 + 0xe0) = 0;
  p_Var2 = (_OBJ76 *)(**(code **)(this->_padding_ + 0x30))();
  if (p_Var2 != (_OBJ76 *)0x0) {
    obj_set_flag(p_Var2,0x280);
  }
  this->object_type = '\0';
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           *)&remoteDistributedObjectMap,&this->dwLocalID);
  Destroy(this);
  iVar3 = (**(code **)this->_padding_)();
  if ((iVar3 != 0) && (*(int *)(iVar3 + 0x20) == 0x53435250)) {
                    /* WARNING: Could not recover jumptable at 0x0048ffb2. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(this->_padding_ + 0x10))();
    return;
  }
  return;
}
