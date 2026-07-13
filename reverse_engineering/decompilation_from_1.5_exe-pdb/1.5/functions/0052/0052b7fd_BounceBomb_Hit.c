/*
 * Entry: 0052b7fd
 * Name: BounceBomb::Hit
 * Namespace: BounceBomb
 * Signature: void Hit(BounceBomb * this, GameObject * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall BounceBomb::Hit(BounceBomb *this,GameObject *param_1,VECTOR_3D *param_2)

{
  uint *puVar1;
  float fVar2;
  MAT_3D MVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  VECTOR_3D VVar8;
  VECTOR_3D VVar9;
  unkbyte10 Var10;
  VECTOR_3D VVar11;
  ushort uVar12;
  VECTOR_3D *pVVar13;
  int iVar14;
  RMAT *pRVar15;
  MAT_3D *pMVar16;
  VECTOR_3D *pVVar17;
  _OBJ76 *p_Var18;
  float *pfVar19;
  undefined4 *puVar20;
  undefined4 unaff_EDI;
  float *pfVar21;
  undefined4 *puVar22;
  float fVar23;
  float fVar24;
  undefined4 uStack_f0;
  undefined1 in_stack_ffffff14 [20];
  undefined4 uVar25;
  undefined4 uVar26;
  undefined4 uVar27;
  undefined4 uVar28;
  char *pcVar29;
  float fVar30;
  undefined2 uVar31;
  undefined2 uVar32;
  MAT_3D local_a4;
  float local_64 [16];
  VECTOR_3D local_24;
  undefined4 *local_18;
  undefined1 local_14 [8];
  float local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_1 == (GameObject *)0x0) {
    fVar24 = *(float *)(*(int *)&this->field_0x10 + 0xb0);
    uVar26 = *(undefined4 *)&this->field_0x34;
    uVar27 = *(undefined4 *)&this->field_0x38;
    pVVar17 = &local_24;
    uVar28 = *(undefined4 *)&this->field_0x3c;
    VVar9.x = *(float *)&this->field_0x34;
    VVar9.y = *(float *)&this->field_0x38;
    VVar9.z = *(float *)&this->field_0x3c;
    uVar25 = 0x52b86e;
    VVar4.z._2_2_ = (short)((uint)param_2->z >> 0x10);
    VVar4._0_10_ = *(unkbyte10 *)param_2;
    pVVar13 = CombineVectors(pVVar17,fVar24,VVar9,
                             (*(float *)&this->field_0x34 * param_2->x +
                             param_2->y * *(float *)&this->field_0x38 +
                             param_2->z * *(float *)&this->field_0x3c) * fVar24 * -2.0,VVar4);
    p_Var18 = (_OBJ76 *)pVVar13->x;
    fVar30 = pVVar13->y;
    local_c = pVVar13->z;
    Var10 = *(unkbyte10 *)pVVar13;
    *(_OBJ76 **)&this->field_0x34 = p_Var18;
    *(float *)&this->field_0x38 = fVar30;
    *(float *)&this->field_0x3c = local_c;
    pcVar29 = (char *)0x52b88f;
    VVar5.z._2_2_ = (short)((uint)local_c >> 0x10);
    VVar5._0_10_ = Var10;
    local_14._0_4_ = p_Var18;
    local_14._4_4_ = fVar30;
    fVar23 = VecLen(VVar5);
    *(float *)&this->field_0x24 = fVar23;
    if (fVar23 <= 0.0) {
      fVar2 = 1e+30;
    }
    else {
      fVar2 = 1.0 / fVar23;
    }
    *(float *)&this->field_0x28 = fVar2;
    if (5.0 <= fVar23) {
LAB_0052b8c0:
      fVar30 = 0.0;
      p_Var18 = *(_OBJ76 **)&this->field_0x18;
      pcVar29 = (char *)(*(int *)&this->field_0x10 + 0xb4);
      uVar28 = 0x52b8d5;
      StartGASEvent(pcVar29,p_Var18,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
      goto LAB_0052b8d8;
    }
  }
  else {
    p_Var18 = (_OBJ76 *)(**(code **)(param_1->_padding_ + 0x30))();
    iVar14 = IsBuilding(p_Var18);
    if (iVar14 == 0) {
      Grenade::Hit((Grenade *)this,param_1,param_2);
      return;
    }
    uVar26 = *(undefined4 *)&this->field_0x34;
    uVar27 = *(undefined4 *)&this->field_0x38;
    pVVar17 = &local_24;
    uVar28 = *(undefined4 *)&this->field_0x3c;
    VVar11.x = *(float *)&this->field_0x34;
    VVar11.y = *(float *)&this->field_0x38;
    VVar11.z = *(float *)&this->field_0x3c;
    fVar24 = 0.5;
    uVar25 = 0x52ba05;
    VVar7.z._2_2_ = (short)((uint)param_2->z >> 0x10);
    VVar7._0_10_ = *(unkbyte10 *)param_2;
    pVVar13 = CombineVectors(pVVar17,0.5,VVar11,
                             -(*(float *)&this->field_0x34 * param_2->x +
                              param_2->y * *(float *)&this->field_0x38 +
                              param_2->z * *(float *)&this->field_0x3c),VVar7);
    p_Var18 = (_OBJ76 *)pVVar13->x;
    fVar30 = pVVar13->y;
    local_c = pVVar13->z;
    Var10 = *(unkbyte10 *)pVVar13;
    *(_OBJ76 **)&this->field_0x34 = p_Var18;
    *(float *)&this->field_0x38 = fVar30;
    *(float *)&this->field_0x3c = local_c;
    pcVar29 = (char *)0x52ba26;
    VVar8.z._2_2_ = (short)((uint)local_c >> 0x10);
    VVar8._0_10_ = Var10;
    local_14._0_4_ = p_Var18;
    local_14._4_4_ = fVar30;
    fVar23 = VecLen(VVar8);
    *(float *)&this->field_0x24 = fVar23;
    if (fVar23 <= 0.0) {
      fVar2 = 1e+30;
    }
    else {
      fVar2 = 1.0 / fVar23;
    }
    *(float *)&this->field_0x28 = fVar2;
    if (1.0 <= fVar23) goto LAB_0052b8c0;
  }
  puVar1 = (uint *)(*(int *)&this->field_0x18 + 0x14);
  *puVar1 = *puVar1 & 0xfffffff7;
LAB_0052b8d8:
  iVar14 = Net_IsNetGame();
  if ((iVar14 != 0) && (uVar12 = Net_GetMyPlayerID(), *(ushort *)&this->field_0x7c == uVar12)) {
    uVar31 = 0xb8fb;
    uVar32 = 0x52;
    Ordnance::OrientToVelocity((Ordnance *)this);
    puVar20 = (undefined4 *)(*(int *)&this->field_0x18 + 0x20);
    puVar22 = &uStack_f0;
    for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
      *puVar22 = *puVar20;
      puVar20 = puVar20 + 1;
      puVar22 = puVar22 + 1;
    }
    MVar3.up_z = (float)uVar25;
    MVar3.right_x = (float)in_stack_ffffff14._0_4_;
    MVar3.right_y = (float)in_stack_ffffff14._4_4_;
    MVar3.right_z = (float)in_stack_ffffff14._8_4_;
    MVar3.up_x = (float)in_stack_ffffff14._12_4_;
    MVar3.up_y = (float)in_stack_ffffff14._16_4_;
    MVar3.front_x = (float)pVVar17;
    MVar3.front_y = fVar24;
    MVar3.front_z = (float)uVar26;
    MVar3._36_4_ = uVar27;
    MVar3.posit_x._0_4_ = uVar28;
    MVar3.posit_x._4_4_ = pcVar29;
    MVar3.posit_y._0_4_ = p_Var18;
    MVar3.posit_y._4_4_ = fVar30;
    MVar3.posit_z._0_2_ = uVar31;
    MVar3.posit_z._2_2_ = uVar32;
    MVar3.posit_z._4_4_ = unaff_EDI;
    pRVar15 = NetUtil_ReduceMatNoRoll((RMAT *)local_14,MVar3);
    pMVar16 = NetUtil_ExpandMatNoRoll(&local_a4,(RMAT)*&pRVar15->buf);
    pfVar19 = local_64;
    for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
      *pfVar19 = pMVar16->right_x;
      pMVar16 = (MAT_3D *)&pMVar16->right_y;
      pfVar19 = pfVar19 + 1;
    }
    pfVar19 = local_64;
    pfVar21 = (float *)(*(int *)&this->field_0x18 + 0x20);
    for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
      *pfVar21 = *pfVar19;
      pfVar19 = pfVar19 + 1;
      pfVar21 = pfVar21 + 1;
    }
    iVar14 = *(int *)&this->field_0x18;
    local_18 = (undefined4 *)(iVar14 + 0x20);
    local_14._0_4_ = *(undefined4 *)(iVar14 + 0x38);
    local_14._4_4_ = *(undefined4 *)(iVar14 + 0x3c);
    local_c = *(float *)(iVar14 + 0x40);
    VVar6.z._2_2_ = (short)((uint)local_c >> 0x10);
    VVar6._0_10_ = *(unkbyte10 *)(iVar14 + 0x38);
    pVVar17 = ScaleVector(&local_24,*(float *)&this->field_0x24,VVar6);
    *(float *)&this->field_0x34 = pVVar17->x;
    *(float *)&this->field_0x38 = pVVar17->y;
    *(float *)&this->field_0x3c = pVVar17->z;
    puVar20 = local_18;
    puVar22 = (undefined4 *)&this->field_0x88;
    for (iVar14 = 0x10; iVar14 != 0; iVar14 = iVar14 + -1) {
      *puVar22 = *puVar20;
      puVar20 = puVar20 + 1;
      puVar22 = puVar22 + 1;
    }
    fVar24 = Get_Time();
    *(undefined4 *)&this->field_0x80 = 1;
    *(float *)&this->field_0xc8 = fVar24;
  }
  return;
}
