/*
 * Entry: 00475a6e
 * Name: CollectObjFloor
 * Namespace: Global
 * Signature: void CollectObjFloor(_OBJ76 * param_1, tagENTITY * param_2, MAT_3D * param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl CollectObjFloor(_OBJ76 *param_1,tagENTITY *param_2,MAT_3D *param_3,int param_4)

{
  MAT_3D *pMVar1;
  int iVar2;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar3;
  MAT_3D local_84;
  MAT_3D local_44;
  
  for (; param_1 != (_OBJ76 *)0x0; param_1 = param_1->sibling) {
    pMVar1 = Matrix_Multiply(&local_84,&param_1->transform,param_3);
    pMVar3 = &local_44;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      pMVar3->right_x = pMVar1->right_x;
      pMVar1 = (MAT_3D *)&pMVar1->right_y;
      pMVar3 = (MAT_3D *)&pMVar3->right_y;
    }
    if ((param_1->clsnInfo != (CLSN_GEOM *)0x0) &&
       ((param_4 == 0 || (param_1->class_id == CLASS_ID_FLOOR)))) {
      CollectFloorFaces(param_1->clsnInfo,(_OBJ76 *)param_2,(tagENTITY *)&local_44,unaff_EDI);
    }
    if (param_1->child != (_OBJ76 *)0x0) {
      CollectObjFloor(param_1->child,param_2,&local_44,param_4);
    }
  }
  return;
}
