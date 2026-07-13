/*
 * Entry: 004cf8b0
 * Name: InfoDisplay::FindSightObject
 * Namespace: InfoDisplay
 * Signature: GameObject * FindSightObject(InfoDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall InfoDisplay::FindSightObject(InfoDisplay *this)

{
  float fVar1;
  float fVar2;
  float fVar3;
  GameObject *pGVar4;
  bool bVar5;
  MAT_3D *pMVar6;
  GameObject *this_00;
  float *pfVar7;
  SPHERE *pSVar8;
  int iVar9;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar10;
  MAT_3D local_cc;
  MAT_3D local_8c;
  Range_Search_Results local_4c;
  GameObject *local_20;
  float local_1c;
  GameObject *local_18;
  int *local_14;
  VECTOR_3D local_10;
  
  local_20 = GameObject::userObject;
  local_18 = (GameObject *)0x0;
  if (GameObject::userObject != (GameObject *)0x0) {
    pMVar6 = Matrix_Inverse(&local_cc,unaff_EDI);
    local_1c = 0.0;
    local_18 = (GameObject *)0x0;
    pMVar10 = &local_8c;
    for (iVar9 = 0x10; iVar9 != 0; iVar9 = iVar9 + -1) {
      pMVar10->right_x = pMVar6->right_x;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
      pMVar10 = (MAT_3D *)&pMVar10->right_y;
    }
    Range::Search(GameObject::objectRange,
                  (double)(reticle.sightMat.front_x * 50.0 + (float)reticle.sightMat.posit_x),
                  (double)(reticle.sightMat.front_z * 50.0 + (float)reticle.sightMat.posit_z),50.0,
                  &local_4c);
    bVar5 = Range_Search_Results::Get_Next_Object(&local_4c,&local_14);
    if (bVar5) {
      do {
        this_00 = GameObject::GetObj(*local_14);
        fVar1 = local_1c;
        pGVar4 = local_18;
        if (((this_00 != (GameObject *)0x0) && (this_00 != local_20)) &&
           ((this_00->obj->flags & 0x600) == 0)) {
          pfVar7 = (float *)(**(code **)(this_00->_padding_ + 0xc))();
          local_10.x = *pfVar7;
          local_10.y = pfVar7[1];
          local_10.z = pfVar7[2];
          Vector_Transform(&local_10,&local_10,1,&local_8c);
          fVar1 = local_1c;
          pGVar4 = local_18;
          if ((0.0 <= local_10.z) && (local_10.z <= 100.0)) {
            pSVar8 = GameObject::GetSphere(this_00);
            fVar1 = pSVar8->radius * 0.75;
            fVar3 = local_10.x * local_10.x + local_10.y * local_10.y;
            fVar2 = local_10.z * local_10.z + fVar3;
            if (((fVar1 * fVar1 < fVar3) && (fVar2 * 0.01 < fVar3)) ||
               (fVar1 = 1.0 - fVar3 / fVar2, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1,
               fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, pGVar4 = this_00
               , fVar1 <= local_1c)) {
              fVar1 = local_1c;
              pGVar4 = local_18;
            }
          }
        }
        local_18 = pGVar4;
        local_1c = fVar1;
        bVar5 = Range_Search_Results::Get_Next_Object(&local_4c,&local_14);
      } while (bVar5);
    }
  }
  return local_18;
}
