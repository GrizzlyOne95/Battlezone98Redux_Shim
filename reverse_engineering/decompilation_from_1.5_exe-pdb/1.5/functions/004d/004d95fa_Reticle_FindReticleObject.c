/*
 * Entry: 004d95fa
 * Name: Reticle::FindReticleObject
 * Namespace: Reticle
 * Signature: GameObject * FindReticleObject(Reticle * this, GameObject * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Reticle::FindReticleObject(Reticle *this,GameObject *param_1)

{
  float fVar1;
  GameObject *pGVar2;
  float fVar3;
  float fVar4;
  bool bVar5;
  MAT_3D *pMVar6;
  GameObject *pGVar7;
  float *pfVar8;
  SPHERE *pSVar9;
  int iVar10;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar11;
  MAT_3D local_cc;
  MAT_3D local_8c;
  Range_Search_Results local_4c;
  GameObject *local_20;
  GameObject *local_1c;
  float local_18;
  int *local_14;
  VECTOR_3D local_10;
  
  local_20 = GameObject::userObject;
  local_1c = (GameObject *)0x0;
  if (GameObject::userObject != (GameObject *)0x0) {
    pMVar6 = Matrix_Inverse(&local_cc,unaff_EDI);
    local_18 = 0.0;
    local_1c = (GameObject *)0x0;
    fVar1 = (this->sightMat).front_z;
    pMVar11 = &local_8c;
    for (iVar10 = 0x10; iVar10 != 0; iVar10 = iVar10 + -1) {
      pMVar11->right_x = pMVar6->right_x;
      pMVar6 = (MAT_3D *)&pMVar6->right_y;
      pMVar11 = (MAT_3D *)&pMVar11->right_y;
    }
    Range::Search(GameObject::objectRange,
                  (double)((this->sightMat).front_x * 100.0 + (float)(this->sightMat).posit_x),
                  (double)(fVar1 * 100.0 + (float)(this->sightMat).posit_z),100.0,&local_4c);
    pGVar2 = local_1c;
    fVar1 = local_18;
    while (local_18 = fVar1, local_1c = pGVar2,
          bVar5 = Range_Search_Results::Get_Next_Object(&local_4c,&local_14), bVar5) {
      pGVar7 = GameObject::GetObj(*local_14);
      pGVar2 = local_1c;
      fVar1 = local_18;
      if ((((pGVar7 != (GameObject *)0x0) && (pGVar7 != local_20)) &&
          ((param_1 == (GameObject *)0x0 ||
           (iVar10 = (**(code **)(param_1->_padding_ + 0x34))(pGVar7), pGVar2 = local_1c,
           fVar1 = local_18, iVar10 != 0)))) &&
         (pGVar2 = local_1c, fVar1 = local_18, pGVar7->isCargo == false)) {
        pfVar8 = (float *)(**(code **)(pGVar7->_padding_ + 0xc))();
        local_10.x = *pfVar8;
        local_10.y = pfVar8[1];
        local_10.z = pfVar8[2];
        Vector_Transform(&local_10,&local_10,1,&local_8c);
        pGVar2 = local_1c;
        fVar1 = local_18;
        if ((0.0001 <= local_10.z) && (local_10.z <= 200.0)) {
          pSVar9 = GameObject::GetSphere(pGVar7);
          fVar1 = pSVar9->radius * 0.75;
          fVar4 = local_10.x * local_10.x + local_10.y * local_10.y;
          fVar3 = local_10.z * local_10.z + fVar4;
          if (((fVar1 * fVar1 < fVar4) && (fVar3 * 0.01 < fVar4)) ||
             (fVar1 = 1.0 - fVar4 / fVar3, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1,
             fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, pGVar2 = pGVar7,
             fVar1 <= local_18)) {
            pGVar2 = local_1c;
            fVar1 = local_18;
          }
        }
      }
    }
    local_14 = (int *)0x0;
    if (0 < GameObject::objectiveCount) {
      do {
        pGVar2 = GameObject::objectiveList[(int)local_14];
        pGVar7 = local_1c;
        fVar1 = local_18;
        if ((pGVar2 != local_20) &&
           (((param_1 == (GameObject *)0x0 ||
             (iVar10 = (**(code **)(param_1->_padding_ + 0x34))(pGVar2), pGVar7 = local_1c,
             fVar1 = local_18, iVar10 != 0)) &&
            (pGVar7 = local_1c, fVar1 = local_18, pGVar2->isCargo == false)))) {
          pfVar8 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
          local_10.x = *pfVar8;
          local_10.y = pfVar8[1];
          local_10.z = pfVar8[2];
          Vector_Transform(&local_10,&local_10,1,&local_8c);
          pGVar7 = local_1c;
          fVar1 = local_18;
          if (0.0001 <= local_10.z) {
            pSVar9 = GameObject::GetSphere(pGVar2);
            fVar1 = pSVar9->radius * 0.75;
            fVar4 = local_10.x * local_10.x + local_10.y * local_10.y;
            fVar3 = local_10.z * local_10.z + fVar4;
            if (((fVar1 * fVar1 < fVar4) && (fVar3 * 0.01 < fVar4)) ||
               (fVar1 = 1.0 - fVar4 / fVar3, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1,
               fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, fVar1 = fVar1 * fVar1, pGVar7 = pGVar2,
               fVar1 <= local_18)) {
              pGVar7 = local_1c;
              fVar1 = local_18;
            }
          }
        }
        local_18 = fVar1;
        local_1c = pGVar7;
        local_14 = (int *)((int)local_14 + 1);
      } while ((int)local_14 < GameObject::objectiveCount);
    }
  }
  return local_1c;
}
