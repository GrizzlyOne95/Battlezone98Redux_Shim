/*
 * Entry: 004d88cf
 * Name: Reticle::PostLoad
 * Namespace: Reticle
 * Signature: void PostLoad(Reticle * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Reticle::PostLoad(Reticle *this)

{
  float fVar1;
  float fVar2;
  GameObject *pGVar3;
  MAT_3D *pMVar4;
  int iVar5;
  float *pfVar6;
  MAT_3D *pMVar7;
  double dVar8;
  MAT_3D local_88;
  float local_48 [10];
  double local_20;
  double local_18;
  double local_10;
  GameObject *local_8;
  
  pGVar3 = GameObject::userObject;
  local_8 = GameObject::userObject;
  this->selectObj = (GameObject *)0x0;
  this->groundPos = (VECTOR_3D *)0x0;
  if (pGVar3 == (GameObject *)0x0) {
    pMVar4 = &Identity_Matrix;
    pMVar7 = &this->sightMat;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    pMVar4 = &Identity_Matrix;
    pMVar7 = &this->horizMat;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
  }
  else {
    pMVar4 = obj_rel_parent_matrix(&local_88,*(_OBJ76 **)(pGVar3[1]._padding_ + 0xf4),(_OBJ76 *)0x0)
    ;
    pGVar3 = local_8;
    pfVar6 = local_48;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      *pfVar6 = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pfVar6 = pfVar6 + 1;
    }
    pMVar4 = &pGVar3->obj->transform;
    pMVar7 = &this->sightMat;
    for (iVar5 = 0x10; iVar5 != 0; iVar5 = iVar5 + -1) {
      pMVar7->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    (this->sightMat).posit_x = local_20;
    (this->sightMat).posit_y = local_18;
    (this->sightMat).posit_z = local_10;
    fVar1 = (this->sightMat).front_z;
    fVar2 = (this->sightMat).front_x;
    dVar8 = rsqrt((double)(fVar2 * fVar2 + fVar1 * fVar1));
    (this->horizMat).up_x = 0.0;
    (this->horizMat).up_y = 1.0;
    (this->horizMat).up_z = 0.0;
    fVar1 = (float)dVar8 * (this->sightMat).front_x;
    (this->horizMat).front_x = fVar1;
    (this->horizMat).front_y = 0.0;
    fVar2 = (float)dVar8 * (this->sightMat).front_z;
    (this->horizMat).front_z = fVar2;
    (this->horizMat).right_x = fVar2;
    (this->horizMat).right_y = 0.0;
    (this->horizMat).right_z = -fVar1;
    (this->horizMat).posit_x = (this->sightMat).posit_x;
    (this->horizMat).posit_y = (this->sightMat).posit_y;
    (this->horizMat).posit_z = (this->sightMat).posit_z;
  }
  return;
}
