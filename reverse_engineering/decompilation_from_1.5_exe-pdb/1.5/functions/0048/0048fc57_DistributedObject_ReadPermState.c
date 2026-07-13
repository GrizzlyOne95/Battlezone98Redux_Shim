/*
 * Entry: 0048fc57
 * Name: DistributedObject::ReadPermState
 * Namespace: DistributedObject
 * Signature: void ReadPermState(ushort param_1, uint param_2, ushort param_3, void * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
DistributedObject::ReadPermState(ushort param_1,uint param_2,ushort param_3,void *param_4)

{
  _Node *p_Var1;
  bool bVar2;
  ushort uVar3;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar4;
  _OBJ76 *p_Var5;
  int iVar6;
  DistributedObject **ppDVar7;
  DistributedObject *pDVar8;
  iterator iVar9;
  ulong uVar10;
  _Node **pp_Var11;
  const_iterator local_24;
  const_iterator local_1c;
  const_iterator local_14;
  _Node *local_c;
  byte local_5;
  
  local_5 = *(byte *)((int)param_4 + 1);
  p_Var1 = *(_Node **)((int)param_4 + 2);
  local_c = p_Var1;
  iVar9 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                  *)&localDistributedObjectMap,(ulong *)&local_24);
  local_1c._padding_ = *iVar9._0_4_;
  local_1c._Ptr = (_Node *)iVar9._0_4_[1];
  std::
  _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
  ::const_iterator::const_iterator
            (&local_14,(_Node *)localDistributedObjectMap._24_4_,
             (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              *)&localDistributedObjectMap);
  bVar2 = std::
          _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
          ::const_iterator::operator==(&local_1c,&local_14);
  if (bVar2) {
    pDVar8 = (DistributedObject *)0x0;
  }
  else {
    ppVar4 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::const_iterator::operator*(&local_1c);
    pDVar8 = ppVar4->second;
  }
  if (pDVar8 == (DistributedObject *)0x0) {
    local_14._Ptr = (_Node *)CONCAT22(param_1,param_3);
    local_14._Ptr =
         (_Node *)stdext::
                  hash_map<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>_>
                  ::operator[](&keyLocalIDMap,(ulong *)&local_14._Ptr);
    if ((local_14._Ptr)->_Left == (_Node *)0x0) {
      (local_14._Ptr)->_Left = p_Var1;
    }
    else if ((local_14._Ptr)->_Left != p_Var1) {
      iVar9 = std::
              _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                      *)&remoteDistributedObjectMap,(ulong *)&local_24);
      local_1c._padding_ = *iVar9._0_4_;
      local_1c._Ptr = (_Node *)iVar9._0_4_[1];
      std::
      _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_24,(_Node *)remoteDistributedObjectMap._24_4_,
                 (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                  *)&remoteDistributedObjectMap);
      bVar2 = std::
              _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
              ::const_iterator::operator==(&local_1c,&local_24);
      if (bVar2) {
        pDVar8 = (DistributedObject *)0x0;
      }
      else {
        ppVar4 = std::
                 _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                 ::const_iterator::operator*(&local_1c);
        pDVar8 = ppVar4->second;
      }
      if (pDVar8 != (DistributedObject *)0x0) {
        *(undefined4 *)&pDVar8[1].true_transform.posit_y = 0;
        pDVar8->object_type = '\0';
        std::
        _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
        ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                 *)&remoteDistributedObjectMap,&pDVar8->dwLocalID);
        (**(code **)(pDVar8->_padding_ + 0x10))();
      }
      (local_14._Ptr)->_Left = local_c;
    }
    pp_Var11 = &local_c;
    iVar9 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                    *)&remoteDistributedObjectMap,(ulong *)&local_24);
    local_1c._padding_ = *iVar9._0_4_;
    local_1c._Ptr = (_Node *)iVar9._0_4_[1];
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_24,(_Node *)remoteDistributedObjectMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                *)&remoteDistributedObjectMap);
    bVar2 = std::
            _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            ::const_iterator::operator==(&local_1c,&local_24);
    if (bVar2) {
      pDVar8 = (DistributedObject *)0x0;
    }
    else {
      ppVar4 = std::
               _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               ::const_iterator::operator*(&local_1c);
      pDVar8 = ppVar4->second;
    }
    if ((pDVar8 != (DistributedObject *)0x0) && ((local_5 & 3) == 1)) {
      *(undefined4 *)&pDVar8[1].true_transform.posit_y = 0;
      p_Var5 = (_OBJ76 *)(**(code **)(pDVar8->_padding_ + 0x30))(pp_Var11);
      if ((local_5 & 0x40) == 0) {
        if (p_Var5 != (_OBJ76 *)0x0) {
          if ((local_5 & 0x3c) == 0) {
            uVar10 = 0x280;
          }
          else {
            uVar10 = 0x1000280;
          }
          obj_set_flag(p_Var5,uVar10);
        }
      }
      else {
        (**(code **)(pDVar8->_padding_ + 0x24))();
      }
      pDVar8->object_type = '\0';
      std::
      _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
      ::erase((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
               *)&remoteDistributedObjectMap,&pDVar8->dwLocalID);
      Destroy(pDVar8);
      iVar6 = (**(code **)pDVar8->_padding_)();
      if ((iVar6 != 0) && (*(int *)(iVar6 + 0x20) == 0x53435250)) {
        (**(code **)(pDVar8->_padding_ + 0x10))();
      }
    }
    if ((local_5 & 3) == 0) {
      uVar3 = Net_GetMyPlayerID();
      if (param_1 != uVar3) {
        if (pDVar8 == (DistributedObject *)0x0) {
          Create(param_1,param_4,param_2);
          ppDVar7 = std::
                    map<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>_>
                    ::operator[](&remoteDistributedObjectMap,(ulong *)&local_c);
          pDVar8 = *ppDVar7;
          if (pDVar8 == (DistributedObject *)0x0) {
            return;
          }
        }
        PermStateRead(pDVar8,param_1,param_3,param_4,param_2);
      }
    }
    else {
      param_4 = (_Node *)CONCAT22(param_1,param_3);
      stdext::
      _Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
      ::erase((_Hash<stdext::_Hmap_traits<unsigned_long,unsigned_long,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,unsigned_long>_>,0>_>
               *)&keyLocalIDMap,(ulong *)&param_4);
    }
  }
  return;
}
