/*
 * Entry: 00533a92
 * Name: Ordnance_ControlAll
 * Namespace: Global
 * Signature: void Ordnance_ControlAll(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Ordnance_ControlAll(float param_1)

{
  Ordnance *pOVar1;
  bool bVar2;
  ushort uVar3;
  Ordnance **ppOVar4;
  int iVar5;
  ushort *puVar6;
  uint uVar7;
  ushort uVar8;
  undefined2 *puVar9;
  _Const_iterator<1> local_224;
  uint local_21c;
  _Const_iterator<1> local_218;
  _Const_iterator<1> local_210;
  undefined2 local_208;
  ushort local_206 [49];
  undefined1 local_1a4 [412];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1a4;
  local_208 = 0x6f78;
  puVar6 = local_206;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_210,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_218,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
  bVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                    (&local_210,&local_218);
  while (!bVar2) {
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_210);
    ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                        (&local_224);
    pOVar1 = *ppOVar4;
    if ((pOVar1->obj->flags >> 9 & 1) == 0) {
      (**(code **)(pOVar1->_padding_ + 0xc))(param_1);
    }
    else {
      local_21c = (uint)pOVar1->source;
      uVar3 = Net_GetMyPlayerID();
      if ((((ushort)local_21c != uVar3) && ((pOVar1->obj->flags >> 1 & 1) != 0)) &&
         (pOVar1->ordnanceClass->notifyRemote != false)) {
        *puVar6 = (ushort)local_21c;
        puVar6[1] = pOVar1->ordid;
        puVar6 = puVar6 + 2;
      }
      (**(code **)(pOVar1->_padding_ + 8))();
    }
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_218,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
    bVar2 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                      (&local_210,&local_218);
  }
  iVar5 = Net_IsNetGame();
  if ((iVar5 != 0) && (local_206 < puVar6)) {
    puVar9 = &local_208;
    uVar7 = (int)puVar6 - (int)puVar9;
    iVar5 = 1;
    uVar8 = 0;
    uVar3 = Net_GetMyPlayerID();
    Net::Send(Net::dp,uVar3,uVar8,iVar5,puVar9,uVar7);
  }
  return;
}
