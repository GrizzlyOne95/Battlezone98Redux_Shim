/*
 * Entry: 0048f80b
 * Name: DistributedObject::SetLocal
 * Namespace: DistributedObject
 * Signature: void SetLocal(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::SetLocal(DistributedObject *this)

{
  ulong *puVar1;
  ushort uVar2;
  ulong uVar3;
  int iVar4;
  DistributedObject **ppDVar5;
  DistributedObject *unaff_EDI;
  DistributedObject *local_8;
  
  if (this->object_type != '\x01') {
    puVar1 = &this->dwLocalID;
    local_8 = this;
    if (this->object_type == '\x02') {
      std::
      _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
      ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               *)&remoteDistributedObjectMap,puVar1);
      this->object_type = '\x01';
      if (0xffff < *puVar1) {
        uVar3 = GetKeyForObject(unaff_EDI);
        local_8 = (DistributedObject *)(uVar3 | (uint)this->activnet_id << 0x10);
        stdext::
        _Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
        ::erase((_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
                 *)&keyLocalIDMap,(ulong *)&local_8);
        this->activnet_id = global_activnet_id;
      }
      iVar4 = (**(code **)(this->_padding_ + 0x30))();
      if ((iVar4 != 0) && ((*(byte *)(iVar4 + 0x14) & 0x80) != 0)) {
        this->object_type = '\0';
        return;
      }
      BroadCastGrabObject(this);
    }
    else {
      this->object_type = '\x01';
      uVar2 = global_activnet_id;
      this->activnet_id = global_activnet_id;
      *puVar1 = (uint)uVar2 * 0x10000 + dwLocalIDCounter;
      dwLocalIDCounter = dwLocalIDCounter + 1;
    }
    ppDVar5 = std::
              map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
              ::operator[](&localDistributedObjectMap,puVar1);
    *ppDVar5 = this;
    UpdatePermState(this);
  }
  return;
}
