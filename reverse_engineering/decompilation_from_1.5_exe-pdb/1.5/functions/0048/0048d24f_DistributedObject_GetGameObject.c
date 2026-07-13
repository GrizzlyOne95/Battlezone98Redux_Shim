/*
 * Entry: 0048d24f
 * Name: DistributedObject::GetGameObject
 * Namespace: DistributedObject
 * Signature: GameObject * GetGameObject(ulong param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __cdecl DistributedObject::GetGameObject(ulong param_1)

{
  bool bVar1;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar2;
  iterator iVar3;
  const_iterator local_14;
  const_iterator local_c;
  
  iVar3 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                  *)&localDistributedObjectMap,(ulong *)&local_14);
  local_c._padding_ = *iVar3._0_4_;
  local_c._Ptr = (_Node *)iVar3._0_4_[1];
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_14,(_Node *)localDistributedObjectMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              *)&localDistributedObjectMap);
  bVar1 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::const_iterator::operator==(&local_c,&local_14);
  if ((bVar1) ||
     (ppVar2 = std::
               _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               ::const_iterator::operator*(&local_c), ppVar2->second == (DistributedObject *)0x0)) {
    iVar3 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                    *)&remoteDistributedObjectMap,(ulong *)&local_14);
    local_c._padding_ = *iVar3._0_4_;
    local_c._Ptr = (_Node *)iVar3._0_4_[1];
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_14,(_Node *)remoteDistributedObjectMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                *)&remoteDistributedObjectMap);
    bVar1 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::const_iterator::operator==(&local_c,&local_14);
    if (bVar1) {
      return (GameObject *)0x0;
    }
    ppVar2 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::const_iterator::operator*(&local_c);
    if (ppVar2->second == (DistributedObject *)0x0) {
      return (GameObject *)0x0;
    }
  }
  ppVar2 = std::
           _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
           ::const_iterator::operator*(&local_c);
  if (ppVar2->second == (DistributedObject *)0x0) {
    return (GameObject *)0x0;
  }
  return (GameObject *)&ppVar2->second[-1].net_user;
}
