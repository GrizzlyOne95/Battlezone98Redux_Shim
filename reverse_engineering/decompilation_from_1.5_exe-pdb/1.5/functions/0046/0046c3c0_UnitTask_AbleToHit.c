/*
 * Entry: 0046c3c0
 * Name: UnitTask::AbleToHit
 * Namespace: UnitTask
 * Signature: bool AbleToHit(UnitTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall UnitTask::AbleToHit(UnitTask *this)

{
  float fVar1;
  GameObject *pGVar2;
  Craft *pCVar3;
  Weapon *pWVar4;
  VECTOR_3D_LONG VVar5;
  VECTOR_3D VVar6;
  VECTOR_3D VVar7;
  float *pfVar8;
  MAT_3D *pMVar9;
  VECTOR_3D *pVVar10;
  int iVar11;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar12;
  double dVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  MAT_3D local_110;
  MAT_3D local_d0;
  MAT_3D local_90;
  VECTOR_3D local_50;
  VECTOR_3D local_44;
  double local_38;
  double local_30;
  double local_28;
  float local_20;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  pGVar2 = this->him;
  if (pGVar2 != (GameObject *)0x0) {
    if (this->weapon == (Weapon *)0x0) {
      pfVar8 = (float *)(**(code **)(pGVar2->_padding_ + 0xc))();
      local_44.x = *pfVar8;
      local_44.y = pfVar8[1];
      local_44.z = pfVar8[2];
      pMVar9 = obj_rel_parent_matrix(&local_d0,this->me->vhcl->eyepoint,(_OBJ76 *)0x0);
      pCVar3 = this->me;
      pMVar12 = &local_110;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        pMVar12->right_x = pMVar9->right_x;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
      }
      local_38 = local_110.posit_x;
      local_30 = local_110.posit_y;
      local_28 = local_110.posit_z;
      pMVar9 = Build_Pitch_Matrix(&local_d0,(pCVar3->vhcl->control).pitch * -0.5);
      pMVar12 = &local_90;
      for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
        pMVar12->right_x = pMVar9->right_x;
        pMVar9 = (MAT_3D *)&pMVar9->right_y;
        pMVar12 = (MAT_3D *)&pMVar12->right_y;
      }
      pMVar9 = Matrix_Multiply(&local_d0,&local_90,&local_110);
    }
    else {
      pfVar8 = (float *)(**(code **)(this->weapon->_padding_ + 0x2c))(&local_10,pGVar2);
      pWVar4 = this->weapon;
      local_44.x = *pfVar8;
      local_44.y = pfVar8[1];
      local_44.z = pfVar8[2];
      local_38 = (pWVar4->M).posit_x;
      local_30 = (pWVar4->M).posit_y;
      local_28 = (pWVar4->M).posit_z;
      pMVar9 = Matrix_Multiply(&local_d0,&pWVar4->obj->transform,&pWVar4->M);
    }
    pMVar12 = &local_90;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar12->right_x = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pMVar12 = (MAT_3D *)&pMVar12->right_y;
    }
    pMVar9 = Matrix_Inverse(&local_d0,unaff_EDI);
    pMVar12 = &local_90;
    for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
      pMVar12->right_x = pMVar9->right_x;
      pMVar9 = (MAT_3D *)&pMVar9->right_y;
      pMVar12 = (MAT_3D *)&pMVar12->right_y;
    }
    pVVar10 = &this->targetDiff;
    Vector_Transform(pVVar10,&local_44,1,&local_90);
    fVar1 = pVVar10->x * pVVar10->x +
            (this->targetDiff).y * (this->targetDiff).y +
            (this->targetDiff).z * (this->targetDiff).z;
    this->targetDistSq = fVar1;
    if (fVar1 <= 0.0) {
      pVVar10 = &local_1c;
      local_1c.x = 0.0;
      local_1c.y = 0.0;
      local_1c.z = 1.0;
    }
    else {
      fVar14 = pVVar10->x;
      fVar15 = (this->targetDiff).y;
      fVar16 = (this->targetDiff).z;
      dVar13 = rsqrt((double)fVar1);
      VVar7.y = fVar15;
      VVar7.x = fVar14;
      VVar7.z = fVar16;
      pVVar10 = ScaleVector(&local_50,(float)dVar13,VVar7);
      local_10.x = pVVar10->x;
      local_10.y = pVVar10->y;
      local_10.z = pVVar10->z;
      pVVar10 = &local_10;
    }
    pGVar2 = this->him;
    (this->targetDir).x = pVVar10->x;
    (this->targetDir).y = pVVar10->y;
    (this->targetDir).z = pVVar10->z;
    pCVar3 = this->me;
    local_50.x = (float)pCVar3->_padding_;
    local_50.y = (float)pCVar3->_padding_;
    local_50.z = (float)pCVar3->_padding_;
    local_1c.x = (pGVar2->euler).v.x;
    local_1c.y = (pGVar2->euler).v.y;
    local_1c.z = (pGVar2->euler).v.z;
    local_10.x = local_1c.x - local_50.x;
    local_10.y = local_1c.y - local_50.y;
    local_10.z = local_1c.z - local_50.z;
    (this->targetVel).x = local_10.x;
    (this->targetVel).y = local_10.y;
    (this->targetVel).z = local_10.z;
    pVVar10 = Vector_Rotate(&local_10,&this->targetVel,&local_90);
    fVar1 = this->rangeSq;
    fVar14 = this->targetDistSq;
    (this->targetVel).x = pVVar10->x;
    (this->targetVel).y = pVVar10->y;
    (this->targetVel).z = pVVar10->z;
    if (fVar14 <= fVar1) {
      local_10.x = local_44.x - (float)local_38;
      local_10.y = local_44.y - (float)local_30;
      local_10.z = local_44.z - (float)local_28;
      local_20 = 1.0;
      VVar5.y = local_30;
      VVar5.x = local_38;
      VVar5.z._0_4_ = SUB84(local_28,0);
      VVar5.z._4_4_ = (int)((ulonglong)local_28 >> 0x20);
      VVar6.y = local_10.y;
      VVar6.x = local_10.x;
      VVar6.z = local_10.z;
      iVar11 = Terrain_GetIntersection(VVar5,VVar6,&local_20,(VECTOR_3D *)0x0);
      return (bool)('\x01' - (iVar11 != 0));
    }
  }
  return false;
}
