/*
 * Entry: 0053abbf
 * Name: SprayBomb::Hit
 * Namespace: SprayBomb
 * Signature: void Hit(SprayBomb * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall SprayBomb::Hit(SprayBomb *this,GameObject *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  GameObjectClass *this_00;
  float fVar2;
  MAT_3D MVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  undefined6 uVar9;
  VECTOR_3D VVar10;
  VECTOR_3D VVar11;
  unkbyte10 Var12;
  ushort uVar13;
  VECTOR_3D *pVVar14;
  MAT_3D *pMVar15;
  GameObject *pGVar16;
  char *pcVar17;
  int iVar18;
  RMAT *pRVar19;
  VECTOR_3D *pVVar20;
  _OBJ76 *p_Var21;
  byte bVar22;
  int iVar23;
  VECTOR_3D *unaff_ESI;
  undefined4 *puVar24;
  VECTOR_3D *unaff_EDI;
  undefined4 *puVar25;
  MAT_3D *pMVar26;
  float *pfVar27;
  float fVar28;
  float fVar29;
  undefined4 uStack_104;
  undefined1 in_stack_ffffff00 [20];
  undefined4 in_stack_ffffff14;
  VECTOR_3D *__return_storage_ptr__;
  float fVar30;
  undefined4 uVar31;
  undefined4 uVar32;
  undefined4 uVar33;
  undefined2 uVar34;
  undefined2 uVar35;
  MAT_3D local_b4;
  MAT_3D local_74;
  undefined4 local_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  VECTOR_3D local_28;
  GameObject *local_1c;
  VECTOR_3D *local_18;
  undefined1 local_14 [4];
  undefined4 local_10;
  float local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&local_74;
  local_1c = param_1;
  local_18 = param_2;
  if (param_1 == (GameObject *)0x0) {
    fVar30 = *(float *)(*(int *)&this->field_0x10 + 0xb4);
    uVar31 = *(undefined4 *)&this->field_0x34;
    pVVar20 = &local_28;
    VVar10.x = *(float *)&this->field_0x34;
    VVar10.y = *(float *)&this->field_0x38;
    VVar10.z = *(float *)&this->field_0x3c;
    __return_storage_ptr__ = (VECTOR_3D *)0x53ac38;
    VVar7.y._2_2_ = (short)((uint)param_2->y >> 0x10);
    VVar7._0_6_ = *(undefined6 *)param_2;
    VVar7.z = param_2->z;
    pVVar14 = CombineVectors(pVVar20,fVar30,VVar10,
                             (*(float *)&this->field_0x34 * param_2->x +
                             param_2->y * *(float *)&this->field_0x38 +
                             param_2->z * *(float *)&this->field_0x3c) * fVar30 * -2.0,VVar7);
    local_14 = (undefined1  [4])pVVar14->x;
    local_10 = pVVar14->y;
    uVar9 = *(undefined6 *)pVVar14;
    fVar29 = pVVar14->z;
    *(undefined1 (*) [4])&this->field_0x34 = local_14;
    *(float *)&this->field_0x38 = local_10;
    *(float *)&this->field_0x3c = fVar29;
    VVar8.y._2_2_ = (short)((uint)local_10 >> 0x10);
    VVar8._0_6_ = uVar9;
    VVar8.z = fVar29;
    local_c = fVar29;
    fVar28 = VecLen(VVar8);
    *(float *)&this->field_0x24 = fVar28;
    if (fVar28 <= 0.0) {
      fVar2 = 1e+30;
    }
    else {
      fVar2 = 1.0 / fVar28;
    }
    *(float *)&this->field_0x28 = fVar2;
    if (fVar28 < 5.0) {
      iVar18 = *(int *)&this->field_0x18;
      local_34 = *(undefined4 *)(iVar18 + 0x38);
      uStack_30 = *(undefined4 *)(iVar18 + 0x3c);
      uStack_2c = *(undefined4 *)(iVar18 + 0x40);
      local_14[0] = '\0';
      local_14[1] = '\0';
      local_14[2] = '\0';
      local_14[3] = '\0';
      local_c = 0.0;
      local_10._0_1_ = '\0';
      local_10._1_1_ = '\0';
      local_10._2_1_ = 0x80;
      local_10._3_1_ = '?';
      local_28.x = 0.0;
      local_28.y = 1.0;
      local_28.z = 0.0;
      pMVar15 = Build_Orthogonal_Matrix(&local_b4,unaff_EDI,unaff_ESI);
      iVar18 = *(int *)&this->field_0x18;
      pMVar26 = &local_74;
      for (iVar23 = 0x10; iVar23 != 0; iVar23 = iVar23 + -1) {
        pMVar26->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar26 = (MAT_3D *)&pMVar26->right_y;
      }
      local_74.posit_x = *(double *)(iVar18 + 0x48);
      local_74.posit_y = *(double *)(iVar18 + 0x50);
      local_74.posit_z = *(double *)(iVar18 + 0x58);
      this_00 = *(GameObjectClass **)(*(int *)&this->field_0x10 + 0xb0);
      pGVar16 = GameObjectClass::Build
                          (this_00,&local_74,*(ushort *)(iVar18 + 0x16) & 0xf,0,-1,(char *)0x0);
      if (this_00->sig == 0x53424d42) {
        bVar22 = (byte)*(undefined2 *)&this->field_0x6c;
        *(byte *)&pGVar16[1]._padding_ = bVar22 >> 4 & 1;
        *(byte *)((int)&pGVar16[1]._padding_ + 1) = bVar22 >> 5 & 1;
      }
      puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
      *puVar1 = *puVar1 | 0x200;
      return;
    }
LAB_0053ad4d:
    p_Var21 = *(_OBJ76 **)&this->field_0x18;
    pcVar17 = (char *)(*(int *)&this->field_0x10 + 0xb8);
    uVar32 = 0x53ad62;
    StartGASEvent(pcVar17,p_Var21,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
    iVar18 = Net_IsNetGame();
    if ((iVar18 != 0) && (uVar13 = Net_GetMyPlayerID(), *(ushort *)&this->field_0x7c == uVar13)) {
      uVar34 = 0;
      uVar35 = 0;
      uVar33 = 0x53ad8e;
      (**(code **)(*(int *)this + 0x10))();
      puVar24 = (undefined4 *)(*(int *)&this->field_0x18 + 0x20);
      puVar25 = &uStack_104;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        *puVar25 = *puVar24;
        puVar24 = puVar24 + 1;
        puVar25 = puVar25 + 1;
      }
      MVar3.up_z = (float)in_stack_ffffff14;
      MVar3.right_x = (float)in_stack_ffffff00._0_4_;
      MVar3.right_y = (float)in_stack_ffffff00._4_4_;
      MVar3.right_z = (float)in_stack_ffffff00._8_4_;
      MVar3.up_x = (float)in_stack_ffffff00._12_4_;
      MVar3.up_y = (float)in_stack_ffffff00._16_4_;
      MVar3.front_x = (float)__return_storage_ptr__;
      MVar3.front_y = (float)pVVar20;
      MVar3.front_z = fVar30;
      MVar3._36_4_ = uVar31;
      MVar3.posit_x._0_4_ = uVar32;
      MVar3.posit_x._4_4_ = pcVar17;
      MVar3.posit_y._0_4_ = p_Var21;
      MVar3.posit_y._4_4_ = uVar33;
      MVar3.posit_z._0_2_ = uVar34;
      MVar3.posit_z._2_2_ = uVar35;
      MVar3.posit_z._4_4_ = fVar29;
      pRVar19 = NetUtil_ReduceMatNoRoll((RMAT *)local_14,MVar3);
      pMVar15 = NetUtil_ExpandMatNoRoll(&local_b4,(RMAT)*&pRVar19->buf);
      pMVar26 = &local_74;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        pMVar26->right_x = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pMVar26 = (MAT_3D *)&pMVar26->right_y;
      }
      pMVar15 = &local_74;
      pfVar27 = (float *)(*(int *)&this->field_0x18 + 0x20);
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        *pfVar27 = pMVar15->right_x;
        pMVar15 = (MAT_3D *)&pMVar15->right_y;
        pfVar27 = pfVar27 + 1;
      }
      iVar18 = *(int *)&this->field_0x18;
      local_18 = (VECTOR_3D *)(iVar18 + 0x20);
      local_14 = *(undefined1 (*) [4])(iVar18 + 0x38);
      local_10 = *(float *)(iVar18 + 0x3c);
      local_c = *(float *)(iVar18 + 0x40);
      VVar4.z._2_2_ = (short)((uint)local_c >> 0x10);
      VVar4._0_10_ = *(unkbyte10 *)(iVar18 + 0x38);
      pVVar20 = ScaleVector(&local_28,*(float *)&this->field_0x24,VVar4);
      *(float *)&this->field_0x34 = pVVar20->x;
      *(float *)&this->field_0x38 = pVVar20->y;
      *(float *)&this->field_0x3c = pVVar20->z;
      pVVar20 = local_18;
      puVar24 = (undefined4 *)&this->field_0x88;
      for (iVar18 = 0x10; iVar18 != 0; iVar18 = iVar18 + -1) {
        *puVar24 = pVVar20->x;
        pVVar20 = (VECTOR_3D *)((int)pVVar20 + 4);
        puVar24 = puVar24 + 1;
      }
      fVar29 = Get_Time();
      *(undefined4 *)&this->field_0x80 = 1;
      *(float *)&this->field_0xc8 = fVar29;
    }
  }
  else {
    fVar29 = 7.684861e-39;
    p_Var21 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
    iVar18 = IsBuilding(p_Var21);
    if (iVar18 != 0) {
      fVar30 = *(float *)&this->field_0x34;
      uVar31 = *(undefined4 *)&this->field_0x38;
      __return_storage_ptr__ = &local_28;
      VVar11.x = *(float *)&this->field_0x34;
      VVar11.y = *(float *)&this->field_0x38;
      VVar11.z = *(float *)&this->field_0x3c;
      pVVar20 = (VECTOR_3D *)0x3f000000;
      in_stack_ffffff14 = 0x53ae95;
      VVar5.z._2_2_ = (short)((uint)param_2->z >> 0x10);
      VVar5._0_10_ = *(unkbyte10 *)param_2;
      pVVar14 = CombineVectors(__return_storage_ptr__,0.5,VVar11,
                               -(param_2->x * *(float *)&this->field_0x34 +
                                param_2->y * *(float *)&this->field_0x38 +
                                param_2->z * *(float *)&this->field_0x3c),VVar5);
      local_14 = (undefined1  [4])pVVar14->x;
      local_10 = pVVar14->y;
      local_c = pVVar14->z;
      Var12 = *(unkbyte10 *)pVVar14;
      *(undefined1 (*) [4])&this->field_0x34 = local_14;
      *(float *)&this->field_0x38 = local_10;
      *(float *)&this->field_0x3c = local_c;
      VVar6.z._2_2_ = (short)((uint)local_c >> 0x10);
      VVar6._0_10_ = Var12;
      fVar28 = VecLen(VVar6);
      *(float *)&this->field_0x24 = fVar28;
      if (fVar28 <= 0.0) {
        fVar2 = 1e+30;
      }
      else {
        fVar2 = 1.0 / fVar28;
      }
      *(float *)&this->field_0x28 = fVar2;
      param_1 = local_1c;
      param_2 = local_18;
      if (1.0 <= fVar28) goto LAB_0053ad4d;
    }
    Grenade::Hit((Grenade *)this,param_1,param_2);
  }
  return;
}
