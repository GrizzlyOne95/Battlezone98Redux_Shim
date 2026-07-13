/*
 * Entry: 00533c82
 * Name: Ordnance_SendNew
 * Namespace: Global
 * Signature: void Ordnance_SendNew(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __cdecl Ordnance_SendNew(void)

{
  OrdnanceClass *pOVar1;
  MAT_3D MVar2;
  bool bVar3;
  Ordnance **ppOVar4;
  RMAT *pRVar5;
  void *pvVar6;
  ulong uVar7;
  char cVar8;
  int iVar9;
  char *pcVar10;
  uint uVar11;
  MAT_3D *pMVar12;
  undefined4 unaff_EDI;
  float *pfVar13;
  float fVar14;
  float fStack_278;
  undefined1 in_stack_fffffd8c [48];
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  RMAT local_22c;
  int local_220;
  char *local_21c;
  _Const_iterator<1> local_218;
  _Const_iterator<1> local_210;
  char local_208 [92];
  undefined1 local_1ac [420];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_1ac;
  BOrdnanceLength = '\0';
  fVar14 = Get_Time();
  if (fVar14 < last_send_time) {
    last_send_time = fVar14;
  }
  local_208[0] = 'R';
  local_208[1] = 'O';
  pcVar10 = local_208 + 2;
  std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
            (&local_210,(Ordnance::ordnanceList._Myhead)->_Next,&Ordnance::ordnanceList);
  do {
    uVar15 = 0x533e42;
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::_Const_iterator<1>
              (&local_218,Ordnance::ordnanceList._Myhead,&Ordnance::ordnanceList);
    uVar16 = 0x533e4e;
    bVar3 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator==
                      (&local_210,&local_218);
    if (bVar3) {
LAB_00533e6b:
      uVar11 = (int)pcVar10 - (int)local_208;
      if (2 < uVar11) {
        Net_BroadCastOrdnance(local_208,uVar11);
      }
      return;
    }
    ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                        (&local_210);
    if ((*ppOVar4)->bSend != 0) {
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      local_220 = (*ppOVar4)->bSend;
      local_21c = pcVar10;
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      pOVar1 = (*ppOVar4)->ordnanceClass;
      uVar11 = 0;
      do {
        if ((((uint)pOVar1->cfg & 0x7f7f7f7f) == *(uint *)(sCompactCfg + uVar11)) &&
           ((*(uint *)((int)&pOVar1->cfg + 4) & 0x7f7f7f7f) ==
            *(uint *)((int)sCompactCfg + uVar11 * 8 + 4))) {
          cVar8 = (char)uVar11 + -0x80;
          goto LAB_00533d50;
        }
        uVar11 = uVar11 + 1;
      } while (uVar11 < 0x17);
      cVar8 = '\0';
LAB_00533d50:
      if (cVar8 < '\0') {
        *pcVar10 = cVar8;
        pcVar10 = pcVar10 + 1;
      }
      else {
        *(int *)pcVar10 = (int)pOVar1->cfg;
        *(undefined4 *)(pcVar10 + 4) = *(undefined4 *)((int)&pOVar1->cfg + 4);
        pcVar10 = pcVar10 + 8;
      }
      uVar17 = 0x533d74;
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      pMVar12 = &(*ppOVar4)->initMat;
      pfVar13 = &fStack_278;
      for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar13 = pMVar12->right_x;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
        pfVar13 = pfVar13 + 1;
      }
      MVar2.posit_y._0_4_ = uVar15;
      MVar2.right_x = (float)in_stack_fffffd8c._0_4_;
      MVar2.right_y = (float)in_stack_fffffd8c._4_4_;
      MVar2.right_z = (float)in_stack_fffffd8c._8_4_;
      MVar2.up_x = (float)in_stack_fffffd8c._12_4_;
      MVar2.up_y = (float)in_stack_fffffd8c._16_4_;
      MVar2.up_z = (float)in_stack_fffffd8c._20_4_;
      MVar2.front_x = (float)in_stack_fffffd8c._24_4_;
      MVar2.front_y = (float)in_stack_fffffd8c._28_4_;
      MVar2.front_z = (float)in_stack_fffffd8c._32_4_;
      MVar2._36_4_ = in_stack_fffffd8c._36_4_;
      MVar2.posit_x = (double)in_stack_fffffd8c._40_8_;
      MVar2.posit_y._4_4_ = uVar16;
      MVar2.posit_z._0_4_ = uVar17;
      MVar2.posit_z._4_4_ = unaff_EDI;
      pRVar5 = NetUtil_ReduceMatNoRoll(&local_22c,MVar2);
      *(undefined4 *)pcVar10 = *(undefined4 *)pRVar5->buf;
      *(undefined4 *)(pcVar10 + 4) = *(undefined4 *)(pRVar5->buf + 4);
      *(undefined2 *)(pcVar10 + 8) = *(undefined2 *)(pRVar5->buf + 8);
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      *(ushort *)(pcVar10 + 10) = (*ppOVar4)->ordid;
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      if ((*ppOVar4)->owner == (_OBJ76 *)0x0) {
        pvVar6 = (void *)0x0;
      }
      else {
        pvVar6 = (*ppOVar4)->owner->gameObj;
      }
      if (pvVar6 == (void *)0x0) {
        uVar7 = 0;
      }
      else {
        uVar7 = DistributedObject::GetID((DistributedObject *)((int)pvVar6 + 0x20));
      }
      *(ulong *)(pcVar10 + 0xc) = uVar7;
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      *(float *)(pcVar10 + 0x10) = (*ppOVar4)->initTime;
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      iVar9 = (**(code **)((*ppOVar4)->_padding_ + 0x1c))();
      pcVar10 = pcVar10 + iVar9 + 0x14;
      if (local_208 + Net_MaxOrdnanceSize < pcVar10) {
        ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                            (&local_210);
        (*ppOVar4)->bSend = local_220;
        pcVar10 = local_21c;
        goto LAB_00533e6b;
      }
      ppOVar4 = std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator*
                          (&local_210);
      (*ppOVar4)->bSend = 2;
    }
    std::list<Ordnance_*,std::allocator<Ordnance_*>_>::_Const_iterator<1>::operator++(&local_210);
  } while( true );
}
