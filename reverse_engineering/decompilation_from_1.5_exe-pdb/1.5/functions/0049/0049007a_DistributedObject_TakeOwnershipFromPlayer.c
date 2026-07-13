/*
 * Entry: 0049007a
 * Name: DistributedObject::TakeOwnershipFromPlayer
 * Namespace: DistributedObject
 * Signature: void TakeOwnershipFromPlayer(ushort param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DistributedObject::TakeOwnershipFromPlayer(ushort param_1)

{
  bool bVar1;
  _Node *p_Var2;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar3;
  DistributedObject **ppDVar4;
  uint uVar5;
  undefined2 in_stack_00000006;
  map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
  *pmVar6;
  vector<DistributedObject_*,std::allocator<DistributedObject_*>_> local_34;
  const_iterator local_1c;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_14;
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_> local_c;
  
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  vector<DistributedObject_*,std::allocator<DistributedObject_*>_>(&local_34);
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::reserve
            (&local_34,remoteDistributedObjectMap._28_4_);
  uVar5 = _param_1 & 0xffff;
  _param_1 = uVar5 << 0x10;
  pmVar6 = &remoteDistributedObjectMap;
  p_Var2 = std::
           _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           ::_Lbound((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                      *)&remoteDistributedObjectMap,(ulong *)&param_1);
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::const_iterator::const_iterator
            ((const_iterator *)&local_14,p_Var2,
             (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              *)pmVar6);
  pmVar6 = &remoteDistributedObjectMap;
  _param_1 = uVar5 * 0x10000 + 0xffff;
  p_Var2 = std::
           _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           ::_Ubound((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                      *)&remoteDistributedObjectMap,(ulong *)&param_1);
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_1c,p_Var2,
             (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              *)pmVar6);
  local_c._padding_ = local_14._padding_;
  local_c._Myptr = local_14._Myptr;
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::const_iterator::operator==((const_iterator *)&local_c,&local_1c);
  while (bVar1 == false) {
    ppVar3 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::const_iterator::operator*((const_iterator *)&local_c);
    if (ppVar3->second != (DistributedObject *)0x0) {
      ppVar3 = std::
               _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               ::const_iterator::operator*((const_iterator *)&local_c);
      std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::push_back
                (&local_34,&ppVar3->second);
    }
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::const_iterator::_Inc((const_iterator *)&local_c);
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::const_iterator::operator==((const_iterator *)&local_c,&local_1c);
  }
  std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
  _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
            (&local_c,local_34._Myfirst,(_Container_base_aux *)&local_34);
  while( true ) {
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    _Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              (&local_14,local_34._Mylast,(_Container_base_aux *)&local_34);
    bVar1 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
            operator==(&local_c,&local_14);
    if (bVar1) break;
    ppDVar4 = std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>
              ::operator*(&local_c);
    SetLocal(*ppDVar4);
    std::_Vector_const_iterator<DistributedObject_*,std::allocator<DistributedObject_*>_>::
    operator++(&local_c);
  }
  std::vector<DistributedObject_*,std::allocator<DistributedObject_*>_>::_Tidy(&local_34);
  operator_delete((void *)local_34._padding_);
  return;
}
