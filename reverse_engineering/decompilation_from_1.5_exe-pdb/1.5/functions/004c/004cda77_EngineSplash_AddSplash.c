/*
 * Entry: 004cda77
 * Name: EngineSplash::AddSplash
 * Namespace: EngineSplash
 * Signature: void AddSplash(EngineSplash * this, MAT_3D * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EngineSplash::AddSplash(EngineSplash *this,MAT_3D *param_1,float param_2)

{
  Splash **ppSVar1;
  int iVar2;
  Splash *pSVar3;
  
  if ((((WeAreActive != 0) && (View_Record.Current_View != TWO_D_VIEW)) &&
      (View_Record.Current_View != EDIT_VIEW)) && (0 < ResolutionMode)) {
    ppSVar1 = &this->splashPtr;
    if (*ppSVar1 < ppSVar1) {
      pSVar3 = *ppSVar1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        (pSVar3->transform).right_x = param_1->right_x;
        param_1 = (MAT_3D *)&param_1->right_y;
        pSVar3 = (Splash *)&(pSVar3->transform).right_y;
      }
      (*ppSVar1)->scale = param_2;
      *ppSVar1 = *ppSVar1 + 1;
    }
  }
  return;
}
