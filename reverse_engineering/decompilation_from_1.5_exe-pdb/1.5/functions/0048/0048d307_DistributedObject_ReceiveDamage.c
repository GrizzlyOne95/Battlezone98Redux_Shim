/*
 * Entry: 0048d307
 * Name: DistributedObject::ReceiveDamage
 * Namespace: DistributedObject
 * Signature: void ReceiveDamage(ushort param_1, void * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject::ReceiveDamage(ushort param_1,void *param_2,uint param_3)

{
  bool bVar1;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar2;
  DistributedObject *pDVar3;
  void *pvVar4;
  undefined4 local_20;
  const_iterator local_1c;
  undefined4 local_14;
  undefined4 local_10;
  const_iterator local_c;
  
  pvVar4 = param_2;
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          *)&localDistributedObjectMap,(ulong *)&local_c);
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_1c,(_Node *)localDistributedObjectMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              *)&localDistributedObjectMap);
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::const_iterator::operator==(&local_c,&local_1c);
  if (bVar1) {
    pDVar3 = (DistributedObject *)0x0;
  }
  else {
    ppVar2 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::const_iterator::operator*(&local_c);
    pDVar3 = ppVar2->second;
  }
  if (pDVar3 != (DistributedObject *)0x0) {
    local_14 = 0;
    local_10 = 0;
    local_c._padding_ =
         (int)(ushort)(*(ushort *)((int)param_2 + 4) >> 4 & 0xf |
                      (*(ushort *)((int)param_2 + 4) & 0xf) << 6);
    local_c._Ptr = (_Node *)(float)*(ushort *)((int)param_2 + 6);
    local_20 = 0;
    local_1c._padding_ = 0;
    local_1c._Ptr = (_Node *)0x0;
    (**(code **)(pDVar3->_padding_ + 0x38))(&local_14,&local_20,pvVar4);
  }
  return;
}
