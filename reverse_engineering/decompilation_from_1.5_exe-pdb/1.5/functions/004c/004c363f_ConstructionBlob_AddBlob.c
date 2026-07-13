/*
 * Entry: 004c363f
 * Name: ConstructionBlob::AddBlob
 * Namespace: ConstructionBlob
 * Signature: void AddBlob(ConstructionBlob * this, SPHERE * param_1, float param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionBlob::AddBlob(ConstructionBlob *this,SPHERE *param_1,float param_2)

{
  Blob **ppBVar1;
  Blob *pBVar2;
  
  if ((((WeAreActive != 0) && (0 < this->blobTexture)) && (View_Record.Current_View != TWO_D_VIEW))
     && ((View_Record.Current_View != EDIT_VIEW && (0 < ResolutionMode)))) {
    ppBVar1 = &this->blobPtr;
    pBVar2 = *ppBVar1;
    if (pBVar2 < ppBVar1) {
      (pBVar2->sphere).origin.x = (param_1->origin).x;
      (pBVar2->sphere).origin.y = (param_1->origin).y;
      (pBVar2->sphere).origin.z = (param_1->origin).z;
      (pBVar2->sphere).radius = param_1->radius;
      (*ppBVar1)->scale = param_2;
      *ppBVar1 = *ppBVar1 + 1;
    }
  }
  return;
}
