/*
 * Entry: 00485425
 * Name: ConstructionRig::GetConstructionMatrix
 * Namespace: ConstructionRig
 * Signature: MAT_3D * GetConstructionMatrix(ConstructionRig * this, MAT_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __thiscall
ConstructionRig::GetConstructionMatrix(ConstructionRig *this,MAT_3D *__return_storage_ptr__)

{
  int iVar1;
  MAT_3D *pMVar2;
  MAT_3D *pMVar3;
  
  pMVar2 = &this->dropMat;
  pMVar3 = __return_storage_ptr__;
  for (iVar1 = 0x10; iVar1 != 0; iVar1 = iVar1 + -1) {
    pMVar3->right_x = pMVar2->right_x;
    pMVar2 = (MAT_3D *)&pMVar2->right_y;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
  }
  return __return_storage_ptr__;
}
