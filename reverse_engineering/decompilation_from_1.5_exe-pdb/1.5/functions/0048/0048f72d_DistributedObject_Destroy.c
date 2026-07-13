/*
 * Entry: 0048f72d
 * Name: DistributedObject::Destroy
 * Namespace: DistributedObject
 * Signature: void Destroy(DistributedObject * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DistributedObject::Destroy(DistributedObject *this)

{
  byte bVar1;
  DistributedObject *pDVar2;
  int iVar3;
  ulong uVar4;
  float *pfVar5;
  undefined4 extraout_EDX;
  byte bVar6;
  float fVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  DistributedObject *local_c;
  uint uStack_8;
  
  bVar6 = 0;
  if (dp != (dp_s *)0x0) {
    local_c = (DistributedObject *)0x0;
    uStack_8 = (uint)this & 0xffff0000;
    std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::push_back
              (&queuedState,(BASE_STRUCT *)&local_c);
    pDVar2 = (DistributedObject *)
             std::deque<BASE_STRUCT,std::allocator<BASE_STRUCT>_>::back(&queuedState);
    iVar3 = (**(code **)(this->_padding_ + 0x30))();
    if ((iVar3 != 0) && ((*(uint *)(iVar3 + 0x14) & 0x1000000) != 0)) {
      bVar6 = 1;
    }
    *(undefined1 *)&pDVar2->_padding_ = 6;
    if (GameObject::userObject == (GameObject *)0x0) {
      local_c = (DistributedObject *)0x0;
    }
    else {
      local_c = (DistributedObject *)&GameObject::userObject->_padding_;
    }
    bVar1 = (**(code **)(this->_padding_ + 0x20))();
    *(byte *)((int)&pDVar2->_padding_ + 1) =
         ((bVar1 & 1 | (this == local_c) * '\x02') << 4 | bVar6) << 2 | 1;
    *(ulong *)((int)&pDVar2->_padding_ + 2) = this->dwLocalID;
    if (dp != (dp_s *)0x0) {
      uVar9 = 0;
      uVar8 = 6;
      uVar4 = GetKeyForObject(pDVar2);
      iVar3 = dpSetPlayerData(extraout_EDX,global_activnet_id,uVar4,pDVar2,uVar8,uVar9);
      if (iVar3 == 0) {
        fVar7 = Get_TimeLocal();
        this->last_send_time = fVar7;
      }
    }
    pfVar5 = stdext::
             hash_map<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
             ::operator[](&delLocalIDMap,&this->dwLocalID);
    fVar7 = Get_TimeLocal();
    *pfVar5 = fVar7;
  }
  return;
}
