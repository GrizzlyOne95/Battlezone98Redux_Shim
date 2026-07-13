/*
 * Entry: 00472f3d
 * Name: CarCarCheck
 * Namespace: Global
 * Signature: int CarCarCheck(tagENTITY * param_1, tagENTITY * param_2, float param_3, CLSN_INFO * param_4, CLSN_INFO * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
CarCarCheck(tagENTITY *param_1,tagENTITY *param_2,float param_3,CLSN_INFO *param_4,
           CLSN_INFO *param_5)

{
  _OBJ76 *p_Var1;
  POINT_VEL *pPVar2;
  BBOX *pBVar3;
  int iVar4;
  MAT_3D *pMVar5;
  CLSN_INFO *unaff_EDI;
  BOX_INFO *pBVar6;
  BBOX *pBVar7;
  MAT_3D *pMVar8;
  float *pfVar9;
  CLSN_INFO *in_stack_fffffef4;
  float local_ec [6];
  float local_d4 [16];
  BOX_INFO local_94;
  BBOX local_1c;
  
  pPVar2 = PositionVelocity((POINT_VEL *)&local_1c,param_1);
  local_94.radius = (param_1->bSphere).radius;
  p_Var1 = param_1->obj76;
  pBVar6 = &local_94;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    (pBVar6->pv).p.x = (pPVar2->p).x;
    pPVar2 = (POINT_VEL *)&(pPVar2->p).y;
    pBVar6 = (BOX_INFO *)&(pBVar6->pv).p.y;
  }
  local_94.obj = p_Var1;
  pBVar3 = GetCarBBox(&local_1c,param_1);
  pBVar7 = &local_94.box;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    (pBVar7->min).x = (pBVar3->min).x;
    pBVar3 = (BBOX *)&(pBVar3->min).y;
    pBVar7 = (BBOX *)&(pBVar7->min).y;
  }
  pMVar5 = &p_Var1->transform;
  pMVar8 = &local_94.mat;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar8->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  pPVar2 = PositionVelocity((POINT_VEL *)&local_1c,param_2);
  p_Var1 = param_2->obj76;
  pfVar9 = (float *)&stack0xfffffef4;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar9 = (pPVar2->p).x;
    pPVar2 = (POINT_VEL *)&(pPVar2->p).y;
    pfVar9 = pfVar9 + 1;
  }
  pBVar3 = GetCarBBox(&local_1c,param_2);
  pfVar9 = local_ec;
  for (iVar4 = 6; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar9 = (pBVar3->min).x;
    pBVar3 = (BBOX *)&(pBVar3->min).y;
    pfVar9 = pfVar9 + 1;
  }
  pMVar5 = &p_Var1->transform;
  pfVar9 = local_d4;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    *pfVar9 = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pfVar9 = pfVar9 + 1;
  }
  iVar4 = BoxBox((BOX_INFO *)&stack0xfffffef4,(BOX_INFO *)param_3,(float)param_4,param_5,unaff_EDI);
  if ((iVar4 == 0) &&
     (iVar4 = BoxBox(&local_94,(BOX_INFO *)param_3,(float)param_5,param_4,in_stack_fffffef4),
     iVar4 == 0)) {
    return 0;
  }
  return 1;
}
