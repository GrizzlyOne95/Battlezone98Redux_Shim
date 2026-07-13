/*
 * Entry: 0052bd75
 * Name: IntersectGameObject
 * Namespace: Global
 * Signature: bool IntersectGameObject(VECTOR_3D * param_1, VECTOR_3D * param_2, float * param_3, VECTOR_3D * param_4, GameObject * param_5, float param_6)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl
IntersectGameObject(VECTOR_3D *param_1,VECTOR_3D *param_2,float *param_3,VECTOR_3D *param_4,
                   GameObject *param_5,float param_6)

{
  int *piVar1;
  float fVar2;
  POINT_VEL PVar3;
  VECTOR_3D VVar4;
  VECTOR_3D VVar5;
  float *pfVar6;
  BBOX *pBVar7;
  VECTOR_3D *pVVar8;
  int iVar9;
  VECTOR_3D *unaff_EDI;
  BBOX *pBVar10;
  float *pfVar11;
  undefined8 in_stack_ffffff74;
  undefined4 in_stack_ffffff7c;
  undefined4 in_stack_ffffff80;
  undefined4 in_stack_ffffff84;
  float in_stack_ffffff88;
  GameObject *pGVar12;
  float fVar13;
  _OBJ76 **pp_Var14;
  float *pfVar15;
  float fVar16;
  int iVar17;
  float local_4c [3];
  VECTOR_3D local_40;
  BBOX local_34;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  pGVar12 = param_5;
  piVar1 = &param_5->_padding_;
  param_5 = (GameObject *)(**(code **)(*piVar1 + 0x2c))();
  pfVar6 = (float *)(**(code **)(*piVar1 + 0xc))();
  local_40.x = param_1->x - *pfVar6;
  local_34.max.x = (pGVar12->euler).v.x;
  local_40.y = param_1->y - pfVar6[1];
  local_34.max.y = (pGVar12->euler).v.y;
  local_40.z = param_1->z - pfVar6[2];
  local_34.max.z = (pGVar12->euler).v.z;
  local_1c = param_2->x;
  local_18 = param_2->y;
  local_14 = param_2->z;
  local_10 = local_1c - local_34.max.x;
  local_c = local_18 - local_34.max.y;
  local_8 = local_14 - local_34.max.z;
  if (param_5->_padding_ == 3) {
    pBVar7 = GetOrdBBox((BBOX *)param_1,(VECTOR_3D *)*param_3,(float)param_2,unaff_EDI);
    pBVar10 = &local_34;
    for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
      (pBVar10->min).x = (pBVar7->min).x;
      pBVar7 = (BBOX *)&(pBVar7->min).y;
      pBVar10 = (BBOX *)&(pBVar10->min).y;
    }
    iVar9 = CheckBoxes(&local_34,(tagENTITY *)param_5);
    if (iVar9 != 0) {
      iVar17 = 0;
      fVar13 = *param_3;
      local_4c[0] = param_1->x;
      local_4c[1] = param_1->y;
      local_4c[2] = param_1->z;
      pp_Var14 = (_OBJ76 **)&param_1;
      local_40.x = local_10;
      local_40.y = local_c;
      local_40.z = local_8;
      pfVar6 = local_4c;
      pfVar11 = (float *)&stack0xffffff74;
      pGVar12 = param_5;
      pfVar15 = param_3;
      pVVar8 = param_4;
      fVar16 = param_6;
      for (iVar9 = 6; iVar9 != 0; iVar9 = iVar9 + -1) {
        *pfVar11 = *pfVar6;
        pfVar6 = pfVar6 + 1;
        pfVar11 = pfVar11 + 1;
      }
      PVar3.p.z = (float)in_stack_ffffff7c;
      PVar3.p.x = (float)(int)in_stack_ffffff74;
      PVar3.p.y = (float)(int)((ulonglong)in_stack_ffffff74 >> 0x20);
      PVar3.v.x = (float)in_stack_ffffff80;
      PVar3.v.y = (float)in_stack_ffffff84;
      PVar3.v.z = in_stack_ffffff88;
      iVar9 = PointEntityCheck(PVar3,(tagENTITY *)pGVar12,fVar13,pp_Var14,pfVar15,pVVar8,fVar16,
                               iVar17);
      if (iVar9 != 0) {
        return true;
      }
    }
  }
  else {
    fVar13 = local_10 * local_40.x + local_c * local_40.y + local_8 * local_40.z;
    if (NAN(fVar13) || 0.0 < fVar13 == (fVar13 == 0.0)) {
      fVar2 = local_8 * local_8 + local_c * local_c + local_10 * local_10;
      fVar16 = (float)param_5->_padding_ * 0.75 + param_6;
      fVar16 = fVar13 * fVar13 -
               ((local_40.z * local_40.z + local_40.y * local_40.y + local_40.x * local_40.x) -
               fVar16 * fVar16) * fVar2;
      if ((0.0 <= fVar16) &&
         (fVar13 = -(SQRT(fVar16) + fVar13),
         *param_3 * fVar2 < fVar13 == (*param_3 * fVar2 == fVar13))) {
        *param_3 = fVar13 / fVar2;
        VVar4.y = local_40.y;
        VVar4.x = local_40.x;
        VVar4.z = local_40.z;
        VVar5.y = local_c;
        VVar5.x = local_10;
        VVar5.z = local_8;
        pVVar8 = AddMultVectors(&local_40,VVar4,fVar13 / fVar2,VVar5);
        param_4->x = pVVar8->x;
        param_4->y = pVVar8->y;
        param_4->z = pVVar8->z;
        pVVar8 = Normalize_Vector(&local_40,param_4);
        param_4->x = pVVar8->x;
        param_4->y = pVVar8->y;
        param_4->z = pVVar8->z;
        return true;
      }
    }
  }
  return false;
}
