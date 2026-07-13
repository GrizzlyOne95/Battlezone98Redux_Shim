/*
 * Entry: 0048e988
 * Name: DistributedObject::SetRemote
 * Namespace: DistributedObject
 * Signature: void SetRemote(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::SetRemote(DistributedObject *this)

{
  undefined4 *puVar1;
  int iVar2;
  DistributedObject **ppDVar3;
  
  if (this->object_type != '\x02') {
    if (this->object_type == '\x01') {
      iVar2 = (**(code **)(this->_padding_ + 0x30))();
      if ((iVar2 != 0) && (iVar2 = *(int *)(iVar2 + 0xb4), iVar2 != 0)) {
        AiMission::GetCurrent();
        puVar1 = *(undefined4 **)(iVar2 + 0xf0);
        if (puVar1 != (undefined4 *)0x0) {
          (**(code **)*puVar1)(1);
        }
      }
      std::
      _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
      ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               *)&localDistributedObjectMap,&this->dwLocalID);
    }
    this->object_type = '\x02';
    ppDVar3 = std::
              map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
              ::operator[](&remoteDistributedObjectMap,&this->dwLocalID);
    *ppDVar3 = this;
  }
  return;
}
