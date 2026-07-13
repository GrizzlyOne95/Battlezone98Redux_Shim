/*
 * Entry: 0048ffb7
 * Name: DistributedObject::RemoteDelete
 * Namespace: DistributedObject
 * Signature: void RemoteDelete(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::RemoteDelete(DistributedObject *this)

{
  _OBJ76 *p_Var1;
  DistributedObject *pDVar2;
  int iVar3;
  
  if (this->object_type != '\x01') {
    p_Var1 = (_OBJ76 *)(**(code **)(this->_padding_ + 0x30))();
    if (p_Var1 != (_OBJ76 *)0x0) {
      obj_set_flag(p_Var1,0x280);
    }
    this->object_type = '\0';
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             *)&remoteDistributedObjectMap,&this->dwLocalID);
    packet_buffer[0] = 'P';
    packet_buffer[1] = 'O';
    packet_buffer._2_4_ = Get_Time();
    packet_buffer[6] = '\x06';
    if (GameObject::userObject == (GameObject *)0x0) {
      pDVar2 = (DistributedObject *)0x0;
    }
    else {
      pDVar2 = (DistributedObject *)&GameObject::userObject->_padding_;
    }
    packet_buffer[7] = (this == pDVar2) << 7 | 3;
    packet_buffer._8_4_ = this->dwLocalID;
    if (dp != (dp_s *)0x0) {
      Net::Send(dp,global_activnet_id,0,1,packet_buffer,0xc);
    }
    Destroy(this);
    iVar3 = (**(code **)this->_padding_)();
    if ((iVar3 != 0) && (*(int *)(iVar3 + 0x20) == 0x53435250)) {
                    /* WARNING: Could not recover jumptable at 0x00490075. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(this->_padding_ + 0x10))();
      return;
    }
  }
  return;
}
