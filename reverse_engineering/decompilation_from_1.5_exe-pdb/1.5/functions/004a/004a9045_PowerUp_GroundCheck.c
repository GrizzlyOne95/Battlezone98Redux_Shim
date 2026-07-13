/*
 * Entry: 004a9045
 * Name: PowerUp::GroundCheck
 * Namespace: PowerUp
 * Signature: bool GroundCheck(PowerUp * this, CLSN_INFO * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall PowerUp::GroundCheck(PowerUp *this,CLSN_INFO *param_1,float param_2)

{
  _OBJ76 *p_Var1;
  VECTOR_3D_LONG VVar2;
  VECTOR_3D VVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  CLSN_INFO *pCVar6;
  VECTOR_3D_LONG *pVVar7;
  VECTOR_3D *pVVar8;
  VECTOR_3D *pVVar9;
  int iVar10;
  MAT_3D *unaff_ESI;
  undefined4 *puVar11;
  VECTOR_3D *unaff_EDI;
  undefined4 *puVar12;
  undefined1 in_stack_ffffff14 [20];
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float *pfVar17;
  VECTOR_3D_LONG local_b0;
  undefined4 local_98 [6];
  VECTOR_3D local_80;
  VECTOR_3D local_74;
  float local_68;
  float fStack_64;
  float fStack_60;
  float local_5c;
  float fStack_58;
  float fStack_54;
  float local_50;
  _OBJ76 *local_4c;
  float local_48;
  float local_44;
  _OBJ76 *local_40;
  float local_3c;
  float local_38;
  _OBJ76 *local_34;
  float local_30;
  float local_2c;
  _OBJ76 *local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  PowerUp *local_8;
  
  pCVar6 = param_1;
  if (param_1->collided == 0) {
    param_1->t = param_2;
  }
  iVar10 = this->_padding_;
  param_2 = 8.40779e-45;
  local_50 = (*(float *)(iVar10 + 0xd8) + *(float *)(iVar10 + 0xe4)) * 0.5;
  local_4c = (_OBJ76 *)((*(float *)(iVar10 + 0xdc) + *(float *)(iVar10 + 0xe8)) * 0.5);
  local_3c = (*(float *)(iVar10 + 0xe0) + *(float *)(iVar10 + 0xec)) * 0.5;
  local_48 = *(float *)(iVar10 + 0xec);
  local_44 = *(float *)(iVar10 + 0xd8);
  local_38 = *(float *)(iVar10 + 0xe4);
  local_24 = *(float *)(iVar10 + 0xe0);
  local_1c = *(float *)(iVar10 + 0xdc);
  local_10 = *(float *)(iVar10 + 0xe8);
  param_1 = (CLSN_INFO *)&local_50;
  local_40 = local_4c;
  local_34 = local_4c;
  local_30 = local_3c;
  local_2c = local_50;
  local_28 = local_4c;
  local_20 = local_50;
  local_18 = local_3c;
  local_14 = local_50;
  local_c = local_3c;
  local_8 = this;
  do {
    pVVar7 = Long_Vector_Transform(&local_b0,unaff_EDI,unaff_ESI);
    p_Var1 = (_OBJ76 *)local_8->_padding_;
    puVar11 = local_98;
    for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
      *puVar11 = *(undefined4 *)&pVVar7->x;
      pVVar7 = (VECTOR_3D_LONG *)((int)&pVVar7->x + 4);
      puVar11 = puVar11 + 1;
    }
    VVar5.x = (float)param_1->collided;
    VVar5.y = (float)param_1->obj;
    VVar5.z = (param_1->euler).mass;
    uVar13 = 0x4a9150;
    pVVar8 = WorldVelocity(&local_74,VVar5,p_Var1);
    local_5c = pVVar8->x;
    fStack_58 = pVVar8->y;
    pVVar9 = &pCVar6->normal;
    fStack_54 = pVVar8->z;
    pfVar17 = &pCVar6->t;
    fVar14 = pVVar8->x;
    fVar15 = pVVar8->y;
    fVar16 = pVVar8->z;
    puVar11 = local_98;
    puVar12 = (undefined4 *)&stack0xffffff14;
    for (iVar10 = 6; iVar10 != 0; iVar10 = iVar10 + -1) {
      *puVar12 = *puVar11;
      puVar11 = puVar11 + 1;
      puVar12 = puVar12 + 1;
    }
    VVar2.z._4_4_ = uVar13;
    VVar2._0_20_ = in_stack_ffffff14;
    VVar3.y = fVar15;
    VVar3.x = fVar14;
    VVar3.z = fVar16;
    iVar10 = Terrain_GetIntersection(VVar2,VVar3,pfVar17,pVVar9);
    if (iVar10 != 0) {
      pCVar6->obj = (_OBJ76 *)0x0;
      pCVar6->collided = 1;
      InitEuler(&pCVar6->euler);
      VVar4.y = fStack_58;
      VVar4.x = local_5c;
      VVar4.z = fStack_54;
      pVVar9 = NegVector(&local_80,VVar4);
      local_68 = pVVar9->x;
      fStack_64 = pVVar9->y;
      fStack_60 = pVVar9->z;
      (pCVar6->vel).x = local_68;
      (pCVar6->vel).y = fStack_64;
      (pCVar6->vel).z = fStack_60;
      (pCVar6->point).x = (float)param_1->collided;
      (pCVar6->point).y = (float)param_1->obj;
      (pCVar6->point).z = (param_1->euler).mass;
    }
    param_1 = (CLSN_INFO *)&(param_1->euler).mass_inv;
    param_2 = (float)((int)param_2 + -1);
  } while (param_2 != 0.0);
  return 0 < pCVar6->collided;
}
