/*
 * Entry: 00474679
 * Name: CheckPair
 * Namespace: Global
 * Signature: int CheckPair(tagENTITY * param_1, tagENTITY * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl CheckPair(tagENTITY *param_1,tagENTITY *param_2)

{
  POINT_VEL PVar1;
  POINT_VEL PVar2;
  tagENTITY *in_EAX;
  POINT_VEL *pPVar3;
  int iVar4;
  CLSN_INFO *unaff_ESI;
  float *pfVar5;
  CLSN_INFO *unaff_EDI;
  float *pfVar6;
  float *pfVar7;
  undefined1 auVar8 [12];
  undefined1 in_stack_fffffe84 [20];
  float fVar9;
  undefined1 in_stack_fffffe9c [16];
  undefined4 in_stack_fffffeac;
  float fVar10;
  tagENTITY *ptVar11;
  float fVar12;
  tagENTITY *ptVar13;
  float fVar14;
  CLSN_INFO *pCVar15;
  VECTOR_3D *pVVar16;
  CLSN_INFO *pCVar17;
  CLSN_INFO local_130;
  CLSN_INFO local_b8;
  POINT_VEL local_40;
  float local_28 [3];
  VECTOR_3D local_1c;
  float local_10;
  int local_c;
  float local_8;
  
  local_c = 0;
  if (((((param_1->bBox).max.x < (in_EAX->bBox).min.x) ||
       ((in_EAX->bBox).max.x < (param_1->bBox).min.x)) ||
      ((param_1->bBox).max.z < (in_EAX->bBox).min.z)) ||
     ((((in_EAX->bBox).max.z < (param_1->bBox).min.z ||
       ((param_1->bBox).max.y < (in_EAX->bBox).min.y)) ||
      ((in_EAX->bBox).max.y < (param_1->bBox).min.y)))) {
    return 0;
  }
  local_8 = TimeStep();
  local_10 = (in_EAX->bSphere).radius + (param_1->bSphere).radius;
  pPVar3 = PositionVelocity(&local_40,in_EAX);
  pfVar6 = local_28;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar6 = (pPVar3->p).x;
    pPVar3 = (POINT_VEL *)&(pPVar3->p).y;
    pfVar6 = pfVar6 + 1;
  }
  fVar10 = 6.545821e-39;
  pPVar3 = PositionVelocity(&local_40,param_1);
  pVVar16 = &local_1c;
  pfVar6 = &local_10;
  fVar9 = 8.40779e-45;
  pfVar5 = (float *)&stack0xfffffe9c;
  fVar12 = local_10;
  fVar14 = local_8;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar5 = (pPVar3->p).x;
    pPVar3 = (POINT_VEL *)&(pPVar3->p).y;
    pfVar5 = pfVar5 + 1;
  }
  pfVar5 = local_28;
  pfVar7 = (float *)&stack0xfffffe84;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar7 = *pfVar5;
    pfVar5 = pfVar5 + 1;
    pfVar7 = pfVar7 + 1;
  }
  PVar1.v.z = fVar9;
  auVar8 = in_stack_fffffe84._0_12_;
  PVar1.p.x = (float)auVar8._0_4_;
  PVar1.p.y = (float)auVar8._4_4_;
  PVar1.p.z = (float)auVar8._8_4_;
  PVar1.v.x = (float)in_stack_fffffe84._12_4_;
  PVar1.v.y = (float)in_stack_fffffe84._16_4_;
  PVar2.v.y = (float)in_stack_fffffeac;
  auVar8 = in_stack_fffffe9c._0_12_;
  PVar2.p.x = (float)auVar8._0_4_;
  PVar2.p.y = (float)auVar8._4_4_;
  PVar2.p.z = (float)auVar8._8_4_;
  PVar2.v.x = (float)in_stack_fffffe9c._12_4_;
  PVar2.v.z = fVar10;
  iVar4 = preclsn(PVar1,PVar2,fVar12,fVar14,pfVar6,pVVar16);
  if (iVar4 == 0) {
    return local_c;
  }
  local_b8.collided = 0;
  local_130.collided = 0;
  local_b8.t = 3.4028235e+38;
  local_130.t = 3.4028235e+38;
  local_c = 1;
  if (in_EAX->cType == CLSN_TYPE_CAR) {
LAB_0047478f:
    pCVar17 = &local_b8;
    pCVar15 = &local_130;
    ptVar11 = in_EAX;
    ptVar13 = param_1;
  }
  else {
    if (param_1->cType != CLSN_TYPE_CAR) {
      if (in_EAX->obj76->class_id == CLASS_ID_VEHICLE) goto LAB_0047478f;
      if (param_1->obj76->class_id != CLASS_ID_VEHICLE) {
        return 1;
      }
    }
    pCVar17 = &local_130;
    pCVar15 = &local_b8;
    ptVar11 = param_1;
    ptVar13 = in_EAX;
  }
  iVar4 = CarEntityCheck(ptVar11,ptVar13,local_8,pCVar15,pCVar17);
  if (iVar4 != 0) {
    local_130.obj = param_1->obj76;
    local_b8.obj = in_EAX->obj76;
    iVar4 = ClassRegisterClsn(local_b8.obj,local_130.obj,&local_130,&local_b8);
    if (iVar4 != 0) {
      ClsnSounds(unaff_EDI,unaff_ESI);
    }
  }
  return local_c;
}
