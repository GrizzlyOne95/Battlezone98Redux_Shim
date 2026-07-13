/*
 * Entry: 004dbe3d
 * Name: Targeting::FindTarget
 * Namespace: Targeting
 * Signature: GameObject * FindTarget(Targeting * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall Targeting::FindTarget(Targeting *this)

{
  int *piVar1;
  float fVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  GameObject *this_00;
  GameObject *pGVar5;
  bool bVar6;
  float *pfVar7;
  int iVar8;
  SPHERE *pSVar9;
  GameObject *this_01;
  Range_Search_Results local_6c;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  GameObject *local_18;
  int *local_14;
  float local_10;
  GameObject *local_c;
  float local_8;
  
  this_00 = GameObject::userObject;
  pfVar7 = (float *)(**(code **)(GameObject::userObject->_padding_ + 0xc))();
  fVar2 = this_00->scanner->range;
  local_1c = fVar2 * fVar2;
  local_18 = (GameObject *)0x0;
  local_34 = *pfVar7;
  local_10 = 0.0;
  local_30 = pfVar7[1];
  local_2c = pfVar7[2];
  Range::Search(GameObject::objectRange,
                (double)(reticle.sightMat.front_x * fVar2 * 0.5 + (float)reticle.sightMat.posit_x),
                (double)(reticle.sightMat.front_z * fVar2 * 0.5 + (float)reticle.sightMat.posit_z),
                (double)(fVar2 * 0.5),&local_6c);
  pGVar5 = local_18;
  fVar2 = local_10;
LAB_004dc07c:
  do {
    do {
      local_10 = fVar2;
      local_18 = pGVar5;
      bVar6 = Range_Search_Results::Get_Next_Object(&local_6c,&local_14);
      if (!bVar6) {
        return local_18;
      }
      local_c = GameObject::GetObj(*local_14);
      pGVar5 = local_18;
      fVar2 = local_10;
    } while (((local_c == (GameObject *)0x0) || (local_c == this_00)) ||
            ((local_c->obj->flags & 0x201) != 0));
    piVar1 = &local_c->_padding_;
    iVar8 = (**(code **)*piVar1)();
  } while (((*(int *)(iVar8 + 0x28) != 2) &&
           (iVar8 = (**(code **)*piVar1)(), *(int *)(iVar8 + 0x28) != 1)) &&
          (iVar8 = (**(code **)*piVar1)(), pGVar5 = local_18, fVar2 = local_10,
          *(int *)(iVar8 + 0x28) != 6));
  pfVar7 = (float *)(**(code **)(*piVar1 + 0xc))();
  this_01 = local_c;
  local_40 = *pfVar7;
  local_3c = pfVar7[1];
  local_38 = pfVar7[2];
  local_28 = local_40 - local_34;
  local_24 = local_3c - local_30;
  local_20 = local_38 - local_2c;
  bVar6 = GameObject::EnemyP(this_00,local_c);
  if (((bVar6) && (this_01->jammer != (Jammer *)0x0)) &&
     (bVar6 = Jammer::IsJamming(this_01->jammer), bVar6)) goto code_r0x004dbf6a;
  goto LAB_004dbfab;
code_r0x004dbf6a:
  local_8 = 1.0;
  VVar3.y._0_4_ = SUB84((double)local_30,0);
  VVar3.x = (double)local_34;
  VVar3.y._4_4_ = (int)((ulonglong)(double)local_30 >> 0x20);
  VVar3.z = (double)local_2c;
  VVar4.y = local_24;
  VVar4.x = local_28;
  VVar4.z = local_20;
  iVar8 = Terrain_GetIntersection(VVar3,VVar4,&local_8,(VECTOR_3D *)0x0);
  this_01 = local_c;
  pGVar5 = local_18;
  fVar2 = local_10;
  if (iVar8 == 0) {
LAB_004dbfab:
    fVar2 = local_28 * reticle.sightMat.front_x +
            local_20 * reticle.sightMat.front_z + local_24 * reticle.sightMat.front_y;
    if (((0.0001 <= fVar2) &&
        (local_8 = local_28 * local_28 + local_24 * local_24 + local_20 * local_20,
        0.0001 <= local_8)) && (local_8 <= local_1c)) {
      local_c = (GameObject *)(fVar2 * fVar2);
      pSVar9 = GameObject::GetSphere(this_01);
      fVar2 = pSVar9->radius * 0.75;
      if (((fVar2 * fVar2 < local_8 - (float)local_c) &&
          (pGVar5 = local_18, fVar2 = local_10, (float)local_c < local_8 * 0.5)) ||
         (fVar2 = ((float)local_c / local_8) * ((float)local_c / local_8), fVar2 = fVar2 * fVar2,
         fVar2 = fVar2 * fVar2, fVar2 = fVar2 * fVar2, fVar2 = fVar2 * fVar2, pGVar5 = this_01,
         local_10 < fVar2)) goto LAB_004dc07c;
    }
    pGVar5 = local_18;
    fVar2 = local_10;
  }
  goto LAB_004dc07c;
}
