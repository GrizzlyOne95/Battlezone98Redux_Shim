/*
 * Entry: 0048e9e4
 * Name: DistributedObject::Create
 * Namespace: DistributedObject
 * Signature: void Create(ushort param_1, void * param_2, uint param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl DistributedObject::Create(ushort param_1,void *param_2,uint param_3)

{
  byte *pbVar1;
  byte bVar2;
  REDUCED_MAT RVar3;
  _Const_iterator<1> _Var4;
  pair<unsigned_long_const_,DistributedObject_*> *ppVar5;
  GameObjectClass *this;
  MAT_3D *pMVar6;
  GameObject *pGVar7;
  NetProcess *pNVar8;
  AiMission *pAVar9;
  int iVar10;
  MAT_3D *pMVar11;
  bool bVar12;
  iterator iVar13;
  long64 lVar14;
  undefined2 uVar15;
  MAT_3D local_b0;
  MAT_3D local_70;
  const_iterator local_30;
  const_iterator local_28;
  int local_20;
  byte local_19;
  undefined4 local_18;
  undefined4 uStack_14;
  undefined4 uStack_10;
  undefined2 uStack_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  pbVar1 = (byte *)((int)param_2 + 0x14);
  if ((*pbVar1 & 0x80) == 0) {
    bVar12 = *(byte *)param_2 < 0x1c;
  }
  else {
    bVar12 = *(byte *)param_2 < 0x15;
  }
  if (!bVar12) {
    local_20 = *(int *)((int)param_2 + 2);
    local_19 = *(byte *)((int)param_2 + 1);
    local_18 = *(undefined4 *)((int)param_2 + 6);
    uStack_14 = *(undefined4 *)((int)param_2 + 10);
    uStack_10 = *(undefined4 *)((int)param_2 + 0xe);
    uStack_c = *(undefined2 *)((int)param_2 + 0x12);
    iVar13 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                     *)&localDistributedObjectMap,(ulong *)&local_30);
    local_28._padding_ = *iVar13._0_4_;
    local_28._Ptr = (_Node *)iVar13._0_4_[1];
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::const_iterator::const_iterator
              (&local_30,(_Node *)localDistributedObjectMap._24_4_,
               (_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                *)&localDistributedObjectMap);
    bVar12 = std::
             _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
             ::const_iterator::operator==(&local_28,&local_30);
    if ((!bVar12) &&
       (ppVar5 = std::
                 _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
                 ::const_iterator::operator*(&local_28), ppVar5->second != (DistributedObject *)0x0)
       ) {
      return;
    }
    std::
    _Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
    ::find((_Tree<std::_Tmap_traits<unsigned_long,DistributedObject_*,std::less<unsigned_long>,std::allocator<std::pair<unsigned_long_const_,DistributedObject_*>_>,0>_>
            *)&remoteDistributedObjectMap,(ulong *)&local_30);
    stdext::
    _Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
    ::lower_bound((_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
                   *)&delLocalIDMap,(ulong *)&local_28);
    std::
    list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
    ::_Const_iterator<1>::_Const_iterator<1>
              ((_Const_iterator<1> *)&local_30,(_Node *)delLocalIDMap._28_4_,
               (list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
                *)&delLocalIDMap.field_0x8);
    bVar12 = std::
             list<std::pair<unsigned_long_const_,float>,std::allocator<std::pair<unsigned_long_const_,float>_>_>
             ::_Const_iterator<1>::operator==
                       ((_Const_iterator<1> *)&local_28,(_Const_iterator<1> *)&local_30);
    if (!bVar12) {
      _Var4._Ptr._0_2_ = (short)local_28._padding_;
      _Var4._padding_ = (int)&local_30;
      _Var4._Ptr._2_2_ = (short)((uint)local_28._padding_ >> 0x10);
      stdext::
      _Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
      ::erase((_Hash<stdext::_Hmap_traits<unsigned_long,float,stdext::hash_compare<unsigned_long,std::less<unsigned_long>_>,std::allocator<std::pair<unsigned_long_const_,float>_>,0>_>
               *)&delLocalIDMap,_Var4);
    }
    bVar2 = *pbVar1;
    if ((char)bVar2 < '\0') {
      if ((bVar2 < 0x80) || (0xe5 < bVar2)) {
        lVar14 = 0;
      }
      else {
        lVar14 = CONCAT44(*(undefined4 *)(wrkmem + (uint)bVar2 * 8 + 0x6fcd4),
                          *(undefined4 *)(wrkmem + (uint)bVar2 * 8 + 0x6fcd0));
      }
    }
    else {
      lVar14 = StringToPrjID((char *)pbVar1);
    }
    this = GameObjectClass::Find(lVar14);
    if (this != (GameObjectClass *)0x0) {
      RVar3.buf[4] = (undefined1)uStack_14;
      RVar3.buf[5] = uStack_14._1_1_;
      RVar3.buf[6] = uStack_14._2_1_;
      RVar3.buf[7] = uStack_14._3_1_;
      RVar3.buf[0] = (undefined1)local_18;
      RVar3.buf[1] = local_18._1_1_;
      RVar3.buf[2] = local_18._2_1_;
      RVar3.buf[3] = local_18._3_1_;
      RVar3.buf[8] = (undefined1)uStack_10;
      RVar3.buf[9] = uStack_10._1_1_;
      RVar3.buf[10] = uStack_10._2_1_;
      RVar3.buf[0xb] = uStack_10._3_1_;
      RVar3.buf[0xc] = (undefined1)uStack_c;
      RVar3.buf[0xd] = uStack_c._1_1_;
      pMVar6 = NetUtil_ExpandMatrix(&local_b0,RVar3);
      bVar2 = local_19 >> 2;
      pMVar11 = &local_70;
      for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
        pMVar11->right_x = pMVar6->right_x;
        pMVar6 = (MAT_3D *)&pMVar6->right_y;
        pMVar11 = (MAT_3D *)&pMVar11->right_y;
      }
      pGVar7 = GameObjectClass::Build(this,&local_70,bVar2 & 0xf,0,-1,(char *)0x0);
      pNVar8 = operator_new(0x14);
      if (pNVar8 == (NetProcess *)0x0) {
        pNVar8 = (NetProcess *)0x0;
      }
      else {
        pNVar8 = NetProcess::NetProcess(pNVar8);
      }
      iVar10 = *(int *)pNVar8;
      uVar15 = SUB42(pGVar7,0);
      pAVar9 = AiMission::GetCurrent();
      (**(code **)(iVar10 + 0x18))(pAVar9,uVar15);
      *(ushort *)((int)&pGVar7->_padding_ + 2) = param_1;
      pGVar7->_padding_ = local_20;
      SetRemote((DistributedObject *)&pGVar7->_padding_);
    }
  }
  return;
}
