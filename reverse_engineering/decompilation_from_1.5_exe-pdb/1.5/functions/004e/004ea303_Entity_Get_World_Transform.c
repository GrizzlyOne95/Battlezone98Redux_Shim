/*
 * Entry: 004ea303
 * Name: Entity_Get_World_Transform
 * Namespace: Global
 * Signature: int Entity_Get_World_Transform(tagENTITY * param_1, MAT_3D * param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Entity_Get_World_Transform(tagENTITY *param_1,MAT_3D *param_2,long param_3)

{
  OBJECT_CLASS_T OVar1;
  _OBJ76 *p_Var2;
  MAT_3D *pMVar3;
  int iVar4;
  int iVar5;
  float *pfVar6;
  MAT_3D *pMVar7;
  int local_484 [256];
  MAT_3D local_84;
  MAT_3D local_44;
  
  p_Var2 = param_1->obj76;
  iVar5 = 0;
  while( true ) {
    OVar1 = p_Var2->class_id;
    local_484[iVar5] = (int)p_Var2;
    iVar5 = iVar5 + 1;
    if (OVar1 == param_3) break;
    p_Var2 = p_Var2->child;
    while (p_Var2 == (_OBJ76 *)0x0) {
      if (iVar5 == 0) goto LAB_004ea34b;
      iVar4 = iVar5 + -1;
      iVar5 = iVar5 + -1;
      p_Var2 = *(_OBJ76 **)(local_484[iVar4] + 0xa4);
    }
  }
  if (iVar5 == 0) {
LAB_004ea34b:
    iVar5 = 0;
  }
  else {
    pfVar6 = (float *)(local_484[0] + 0x20);
    pMVar3 = &local_44;
    for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
      pMVar3->right_x = *pfVar6;
      pfVar6 = pfVar6 + 1;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
    }
    param_1 = (tagENTITY *)0x1;
    if (1 < iVar5) {
      do {
        pMVar3 = Matrix_Multiply(&local_84,(MAT_3D *)(local_484[(int)param_1] + 0x20),&local_44);
        param_1 = (tagENTITY *)((int)&param_1->obj76 + 1);
        pMVar7 = &local_44;
        for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
          pMVar7->right_x = pMVar3->right_x;
          pMVar3 = (MAT_3D *)&pMVar3->right_y;
          pMVar7 = (MAT_3D *)&pMVar7->right_y;
        }
      } while ((int)param_1 < iVar5);
    }
    pMVar3 = &local_44;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      param_2->right_x = pMVar3->right_x;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
      param_2 = (MAT_3D *)&param_2->right_y;
    }
    iVar5 = 1;
  }
  return iVar5;
}
