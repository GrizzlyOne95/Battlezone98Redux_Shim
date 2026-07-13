/*
 * Entry: 0045effe
 * Name: GetTransform
 * Namespace: Global
 * Signature: MAT_3D * GetTransform(MAT_3D * __return_storage_ptr__, int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __cdecl GetTransform(MAT_3D *__return_storage_ptr__,int param_1)

{
  GameObject *pGVar1;
  int iVar2;
  MAT_3D *pMVar3;
  MAT_3D *pMVar4;
  
  pGVar1 = GameObjectHandle::GetObj(param_1);
  iVar2 = 0x10;
  if (pGVar1 == (GameObject *)0x0) {
    pMVar3 = &Identity_Matrix;
  }
  else {
    pMVar3 = &pGVar1->obj->transform;
  }
  pMVar4 = __return_storage_ptr__;
  for (; iVar2 != 0; iVar2 = iVar2 + -1) {
    pMVar4->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar4 = (MAT_3D *)&pMVar4->right_y;
  }
  return __return_storage_ptr__;
}
