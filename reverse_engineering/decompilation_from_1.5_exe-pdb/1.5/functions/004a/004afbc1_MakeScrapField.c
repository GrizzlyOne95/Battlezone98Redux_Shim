/*
 * Entry: 004afbc1
 * Name: MakeScrapField
 * Namespace: Global
 * Signature: void MakeScrapField(VECTOR_3D * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl MakeScrapField(VECTOR_3D *param_1,int param_2)

{
  float fVar1;
  VECTOR_3D_LONG VVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  MAT_3D *pMVar6;
  GameObject *pGVar7;
  VECTOR_3D *unaff_ESI;
  VECTOR_3D *unaff_EDI;
  MAT_3D *pMVar8;
  SINCOS SVar9;
  float fVar10;
  MAT_3D local_cc;
  MAT_3D local_8c;
  VECTOR_3D local_4c;
  float local_40;
  undefined4 local_3c;
  float local_38;
  double local_34;
  double local_2c;
  double local_24;
  float local_1c;
  SINCOS local_18;
  float local_10;
  int local_c;
  int local_8;
  
  iVar4 = (0x200 - ((int)GameObject::objectList->_Mylast - (int)GameObject::objectList->_Myfirst >>
                   2)) * 3;
  iVar4 = (int)(iVar4 + (iVar4 >> 0x1f & 3U)) >> 2;
  if (iVar4 < param_2) {
    param_2 = iVar4;
  }
  local_8 = 0;
  local_c = param_2;
  local_10 = SQRT((float)param_2) * 10.0;
  if (0 < param_2) {
    do {
      uVar5 = Rand_Counter + 1U & 0xff;
      Rand_Counter = uVar5 + 1 & 0xff;
      fVar10 = Pseudo_Rand_Number[uVar5] * local_10 + param_1->x;
      local_34 = (double)fVar10;
      local_2c = (double)param_1->y;
      fVar1 = Pseudo_Rand_Number[Rand_Counter] * local_10 + param_1->z;
      local_24 = (double)fVar1;
      bVar3 = GoodScrapPosition(fVar10,fVar1);
      if (bVar3) {
        VVar2.y._0_4_ = SUB84(local_2c,0);
        VVar2.x = local_34;
        VVar2.y._4_4_ = (int)((ulonglong)local_2c >> 0x20);
        VVar2.z._0_4_ = SUB84(local_24,0);
        VVar2.z._4_4_ = (int)((ulonglong)local_24 >> 0x20);
        Floor_GetFloor(VVar2,&local_1c,&local_4c);
        fVar10 = rand<float>(6.2831855);
        SVar9 = SinCos(fVar10);
        local_40 = SVar9.Cos;
        local_38 = SVar9.Sin;
        local_3c = 0;
        local_18 = SVar9;
        pMVar6 = Build_Orthogonal_Matrix(&local_cc,unaff_EDI,unaff_ESI);
        local_8c.posit_x = local_34;
        pMVar8 = &local_8c;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          pMVar8->right_x = pMVar6->right_x;
          pMVar6 = (MAT_3D *)&pMVar6->right_y;
          pMVar8 = (MAT_3D *)&pMVar8->right_y;
        }
        local_8c.posit_y = (double)local_1c;
        local_8c.posit_z = local_24;
        iVar4 = rand();
        pGVar7 = GameObjectClass::Build
                           (scrapFieldFeature.objClass[(uint)(iVar4 >> 8) % 3],&local_8c,0,0,-1,
                            (char *)0x0);
        iVar4 = Net_IsNetGame();
        if (iVar4 != 0) {
          DistributedObject::SetLocal((DistributedObject *)&pGVar7->_padding_);
        }
      }
      else if (0 < local_c) {
        local_c = local_c + -1;
        local_8 = local_8 + -1;
      }
      local_8 = local_8 + 1;
    } while (local_8 < param_2);
  }
  return;
}
