/*
 * Entry: 004ee051
 * Name: Spinner_Simulate
 * Namespace: Global
 * Signature: void Spinner_Simulate(_OBJ76 * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Spinner_Simulate(_OBJ76 *param_1)

{
  VECTOR_3D *pVVar1;
  MAT_3D *pMVar2;
  int iVar3;
  MAT_3D *pMVar4;
  float fVar5;
  MAT_3D local_44;
  
  if ((param_1->flags & 0x200) == 0) {
    pVVar1 = param_1->class_ptr;
    fVar5 = TimeStepLocal();
    pMVar2 = Spinner(&local_44,&param_1->transform,*pVVar1,fVar5);
    pMVar4 = &param_1->transform;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar4->right_x = pMVar2->right_x;
      pMVar2 = (MAT_3D *)&pMVar2->right_y;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
    }
  }
  return;
}
