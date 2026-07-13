/*
 * Entry: 00472e85
 * Name: CarSphereCheck
 * Namespace: Global
 * Signature: int CarSphereCheck(tagENTITY * param_1, tagENTITY * param_2, float param_3, CLSN_INFO * param_4, CLSN_INFO * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
CarSphereCheck(tagENTITY *param_1,tagENTITY *param_2,float param_3,CLSN_INFO *param_4,
              CLSN_INFO *param_5)

{
  float fVar1;
  _OBJ76 *p_Var2;
  _OBJ76 *p_Var3;
  VECTOR_3D VVar4;
  POINT_VEL *pPVar5;
  BBOX *pBVar6;
  int iVar7;
  MAT_3D *pMVar8;
  CLSN_INFO *unaff_EDI;
  float *pfVar9;
  float local_d4 [16];
  float local_94 [6];
  float local_7c;
  _OBJ76 *local_78;
  float local_74 [6];
  float local_5c [16];
  BBOX local_1c;
  
  pPVar5 = PositionVelocity((POINT_VEL *)&local_1c,param_1);
  fVar1 = (param_1->bSphere).radius;
  p_Var2 = param_1->obj76;
  pfVar9 = local_94;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar9 = (pPVar5->p).x;
    pPVar5 = (POINT_VEL *)&(pPVar5->p).y;
    pfVar9 = pfVar9 + 1;
  }
  local_7c = fVar1;
  local_78 = p_Var2;
  pBVar6 = GetCarBBox(&local_1c,param_1);
  pfVar9 = local_74;
  for (iVar7 = 6; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar9 = (pBVar6->min).x;
    pBVar6 = (BBOX *)&(pBVar6->min).y;
    pfVar9 = pfVar9 + 1;
  }
  local_1c.max.x = 0.0;
  local_1c.max.y = 0.0;
  local_1c.max.z = 0.0;
  p_Var3 = param_2->obj76;
  pMVar8 = &p_Var2->transform;
  pfVar9 = local_5c;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar9 = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pfVar9 = pfVar9 + 1;
  }
  pMVar8 = &p_Var3->transform;
  pfVar9 = local_d4;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    *pfVar9 = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pfVar9 = pfVar9 + 1;
  }
  VVar4.y = local_1c.max.y;
  VVar4.x = local_1c.max.x;
  VVar4.z = local_1c.max.z;
  WorldVelocity(&local_1c.max,VVar4,p_Var3);
  iVar7 = BoxSphere((BOX_INFO *)p_Var3,(_OBJ76 *)0x3f800000,(float)local_d4,(MAT_3D *)param_3,
                    (float)param_4,param_5,unaff_EDI);
  return (uint)(iVar7 != 0);
}
