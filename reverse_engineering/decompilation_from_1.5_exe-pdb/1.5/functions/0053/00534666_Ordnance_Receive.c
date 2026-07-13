/*
 * Entry: 00534666
 * Name: Ordnance_Receive
 * Namespace: Global
 * Signature: void Ordnance_Receive(char * param_1, uint param_2, ushort param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Ordnance_Receive(char *param_1,uint param_2,ushort param_3)

{
  byte bVar1;
  undefined2 uVar2;
  _OBJ76 *p_Var3;
  VECTOR_3D VVar4;
  bool bVar5;
  int iVar6;
  MAT_3D *pMVar7;
  GameObject *pGVar8;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> *ppVar9;
  VECTOR_3D *pVVar10;
  Ordnance *pOVar11;
  int iVar12;
  uchar (*pauVar13) [10];
  uchar (*pauVar14) [10];
  MAT_3D *pMVar15;
  float fVar16;
  MAT_3D local_e0;
  MAT_3D local_a0;
  VECTOR_3D local_60;
  pair<std::_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>::iterator,bool>
  local_54;
  float local_48;
  float fStack_44;
  float fStack_40;
  const_iterator local_3c;
  float local_34;
  float local_30;
  float local_2c;
  const_iterator local_28;
  pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*> local_20;
  pair<unsigned_short,unsigned_short> local_18;
  _OBJ76 *local_14;
  char *local_10;
  uchar (*local_c) [10];
  OrdnanceClass *local_8;
  
  local_10 = param_1 + param_2;
  if (param_1 < local_10) {
    do {
      if (local_10 + -1 <= param_1) {
        return;
      }
      bVar1 = *param_1;
      if ((char)bVar1 < '\0') {
        if ((bVar1 < 0x80) || (0x96 < bVar1)) {
          iVar12 = 0;
          iVar6 = 0;
        }
        else {
          iVar12 = (&magnetBuildingClass._padding_)[(uint)bVar1 * 2];
          iVar6 = (&magnetBuildingClass._padding_)[(uint)bVar1 * 2];
        }
        pauVar13 = (uchar (*) [10])(param_1 + 1);
      }
      else {
        iVar12 = *(int *)param_1;
        iVar6 = *(int *)(param_1 + 4);
        pauVar13 = (uchar (*) [10])(param_1 + 8);
      }
      local_8 = OrdnanceClass::Find(CONCAT26((short)((uint)iVar6 >> 0x10),
                                             CONCAT24((short)iVar6,iVar12)));
      if (local_8 == (OrdnanceClass *)0x0) {
        return;
      }
      pauVar14 = pauVar13 + 2;
      local_c = pauVar13;
      if (network_loggit != 0) {
        Get_Time();
        DisplayMessage("Now = %f Ordnance = %f");
      }
      pMVar7 = NetUtil_ExpandMatNoRoll(&local_e0,(RMAT)*pauVar13);
      pMVar15 = &local_a0;
      for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
        pMVar15->right_x = pMVar7->right_x;
        pMVar7 = (MAT_3D *)&pMVar7->right_y;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
      }
      pGVar8 = DistributedObject::GetGameObject(*(ulong *)(pauVar13[1] + 2));
      if (pGVar8 == (GameObject *)0x0) {
        local_14 = (_OBJ76 *)0x0;
      }
      else {
        local_14 = (_OBJ76 *)(**(code **)(pGVar8->_padding_ + 0x30))();
      }
      uVar2 = *(undefined2 *)pauVar13[1];
      std::
      _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
      ::find((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              *)&netOrdnanceMap,(pair<unsigned_short,unsigned_short> *)&local_28);
      std::
      _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
      ::const_iterator::const_iterator
                (&local_3c,(_Node *)netOrdnanceMap._24_4_,
                 (_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                  *)&netOrdnanceMap);
      bVar5 = std::
              _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
              ::const_iterator::operator==(&local_28,&local_3c);
      if (bVar5) {
        pOVar11 = OrdnanceClass::Build(local_8,&local_a0,local_14);
        local_18.first = pOVar11->source;
        local_18.second = pOVar11->ordid;
        std::
        _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
        ::erase((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                 *)&netOrdnanceMap,&local_18);
        pauVar13 = local_c;
        g_next_ordid = g_next_ordid - 1;
        pOVar11->source = param_3;
        pOVar11->ordid = *(ushort *)local_c[1];
        iVar12 = (**(code **)(pOVar11->_padding_ + 0x20))(pauVar14);
        local_20.first.first = param_3;
        local_20.first.second = uVar2;
        local_20.second = pOVar11;
        std::
        _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
        ::insert((_Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                  *)&netOrdnanceMap,&local_54,&local_20);
      }
      else {
        ppVar9 = std::
                 _Tree<std::_Tmap_traits<std::pair<unsigned_short,unsigned_short>,Ordnance_*,std::less<std::pair<unsigned_short,unsigned_short>_>,std::allocator<std::pair<std::pair<unsigned_short,unsigned_short>_const_,Ordnance_*>_>,0>_>
                 ::const_iterator::operator*(&local_28);
        pOVar11 = ppVar9->second;
        pMVar7 = &local_a0;
        pMVar15 = &pOVar11->obj->transform;
        for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
          pMVar15->right_x = pMVar7->right_x;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
          pMVar15 = (MAT_3D *)&pMVar15->right_y;
        }
        p_Var3 = pOVar11->obj;
        local_34 = (p_Var3->transform).front_x;
        local_30 = (p_Var3->transform).front_y;
        local_2c = (p_Var3->transform).front_z;
        VVar4.x = (p_Var3->transform).front_x;
        VVar4.y = (p_Var3->transform).front_y;
        VVar4.z = (p_Var3->transform).front_z;
        pVVar10 = ScaleVector(&local_60,(pOVar11->euler).v_mag,VVar4);
        iVar12 = pOVar11->_padding_;
        local_48 = pVVar10->x;
        fStack_44 = pVVar10->y;
        fStack_40 = pVVar10->z;
        (pOVar11->euler).v.x = local_48;
        (pOVar11->euler).v.y = fStack_44;
        (pOVar11->euler).v.z = fStack_40;
        iVar12 = (**(code **)(iVar12 + 0x20))(pauVar14);
        pauVar13 = local_c;
      }
      param_1 = (char *)(*pauVar14 + iVar12);
      if (0.0 <= *(float *)(pauVar13[1] + 6)) {
        fVar16 = Get_Time();
        local_8 = (OrdnanceClass *)(fVar16 - *(float *)(pauVar13[1] + 6));
        fVar16 = TimeStep();
        fVar16 = (float)local_8 - fVar16;
      }
      else {
        local_8 = (OrdnanceClass *)-*(float *)(pauVar13[1] + 6);
        fVar16 = TimeStep();
        fVar16 = (float)local_8 - fVar16;
      }
      pOVar11->dt = fVar16;
      if (pOVar11->dt < -5.0) {
        if (network_loggit != 0) {
          DisplayMessage("Future ordnance = %f");
        }
        pOVar11->dt = 0.0;
      }
      do {
        if (pOVar11->dt <= 0.05) break;
        pOVar11->dt = pOVar11->dt - 0.05;
        (**(code **)(pOVar11->_padding_ + 0xc))(0xcccd);
        (**(code **)(pOVar11->_padding_ + 0x10))(0x3d4ccccd);
      } while ((pOVar11->obj->flags >> 9 & 1) == 0);
      pOVar11->bSend = 0;
    } while (param_1 < local_10);
  }
  return;
}
