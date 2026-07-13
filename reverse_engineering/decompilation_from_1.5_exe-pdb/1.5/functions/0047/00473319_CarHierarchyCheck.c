/*
 * Entry: 00473319
 * Name: CarHierarchyCheck
 * Namespace: Global
 * Signature: int CarHierarchyCheck(tagENTITY * param_1, tagENTITY * param_2, float param_3, CLSN_INFO * param_4, CLSN_INFO * param_5)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
CarHierarchyCheck(tagENTITY *param_1,tagENTITY *param_2,float param_3,CLSN_INFO *param_4,
                 CLSN_INFO *param_5)

{
  float fVar1;
  _OBJ76 *p_Var2;
  POINT_VEL *pPVar3;
  BBOX *pBVar4;
  int iVar5;
  MAT_3D *pMVar6;
  BOX_INFO *pBVar7;
  BBOX *pBVar8;
  MAT_3D *pMVar9;
  BOX_INFO local_94;
  BBOX local_1c;
  
  pPVar3 = PositionVelocity((POINT_VEL *)&local_1c,param_1);
  fVar1 = (param_1->bSphere).radius;
  p_Var2 = param_1->obj76;
  pBVar7 = &local_94;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    (pBVar7->pv).p.x = (pPVar3->p).x;
    pPVar3 = (POINT_VEL *)&(pPVar3->p).y;
    pBVar7 = (BOX_INFO *)&(pBVar7->pv).p.y;
  }
  local_94.radius = fVar1;
  local_94.obj = p_Var2;
  pBVar4 = GetCarBBox(&local_1c,param_1);
  pBVar8 = &local_94.box;
  for (iVar5 = 6; iVar5 != 0; iVar5 = iVar5 + -1) {
    (pBVar8->min).x = (pBVar4->min).x;
    pBVar4 = (BBOX *)&(pBVar4->min).y;
    pBVar8 = (BBOX *)&(pBVar8->min).y;
  }
  pMVar6 = &p_Var2->transform;
  pMVar9 = &local_94.mat;
  for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
    pMVar9->right_x = pMVar6->right_x;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
    pMVar9 = (MAT_3D *)&pMVar9->right_y;
  }
  iVar5 = CarRecurse(&local_94,param_2->obj76,&Identity_Matrix,param_3,param_4,param_5);
  return iVar5;
}
