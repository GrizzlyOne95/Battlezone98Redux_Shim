/*
 * Entry: 004cd696
 * Name: EngineFlame::AddFlame
 * Namespace: EngineFlame
 * Signature: void AddFlame(EngineFlame * this, MAT_3D * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall EngineFlame::AddFlame(EngineFlame *this,MAT_3D *param_1,float param_2)

{
  Flame **ppFVar1;
  int iVar2;
  Flame *pFVar3;
  
  if ((((WeAreActive != 0) && (View_Record.Current_View != TWO_D_VIEW)) &&
      (View_Record.Current_View != EDIT_VIEW)) && (0 < ResolutionMode)) {
    ppFVar1 = &this->flamePtr;
    if (*ppFVar1 < ppFVar1) {
      pFVar3 = *ppFVar1;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        (pFVar3->transform).right_x = param_1->right_x;
        param_1 = (MAT_3D *)&param_1->right_y;
        pFVar3 = (Flame *)&(pFVar3->transform).right_y;
      }
      (*ppFVar1)->scale = param_2;
      *ppFVar1 = *ppFVar1 + 1;
    }
  }
  return;
}
