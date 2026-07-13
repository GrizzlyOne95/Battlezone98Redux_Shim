/*
 * Entry: 00466909
 * Name: TugPickup::DoNear
 * Namespace: TugPickup
 * Signature: bool DoNear(TugPickup * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall TugPickup::DoNear(TugPickup *this)

{
  _OBJ76 *p_Var1;
  char cVar2;
  int iVar3;
  MAT_3D *pMVar4;
  VECTOR_3D *pVVar5;
  float *pfVar6;
  MAT_3D *pMVar7;
  bool bVar8;
  MAT_3D local_f0;
  float local_b0 [10];
  double local_88;
  double local_80;
  double local_78;
  MAT_3D local_70;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  _OBJ76 *local_18;
  VECTOR_3D local_14;
  char local_5;
  
  iVar3 = (*(int **)&this->field_0x1c)[0x2a];
  if ((iVar3 == 0) || (iVar3 == *(int *)&this->field_0x14)) {
    local_5 = '\0';
  }
  else {
    local_5 = '\x01';
    if (49.0 < *(float *)&this->field_0x15c) {
      return true;
    }
  }
  iVar3 = (**(code **)(**(int **)&this->field_0x1c + 0x28))();
  if (iVar3 == 0) {
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  else {
    p_Var1 = *(_OBJ76 **)(*(int *)&this->field_0x14 + 0x2d8);
    local_18 = (_OBJ76 *)(**(code **)(**(int **)&this->field_0x1c + 0x28))();
    pMVar4 = obj_rel_parent_matrix(&local_70,p_Var1,(_OBJ76 *)0x0);
    p_Var1 = local_18;
    pfVar6 = local_b0;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      *pfVar6 = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pfVar6 = pfVar6 + 1;
    }
    pMVar4 = obj_rel_parent_matrix(&local_f0,p_Var1,(_OBJ76 *)0x0);
    bVar8 = local_5 == '\0';
    pMVar7 = &local_70;
    for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
      pMVar7->right_x = pMVar4->right_x;
      pMVar4 = (MAT_3D *)&pMVar4->right_y;
      pMVar7 = (MAT_3D *)&pMVar7->right_y;
    }
    local_24.x = (float)((float10)local_70.posit_x - (float10)local_88);
    local_24.y = (float)((float10)local_70.posit_y - (float10)local_80);
    local_24.z = (float)((float10)local_70.posit_z - (float10)local_78);
    local_14.x = local_24.x;
    local_14.y = local_24.y;
    local_14.z = local_24.z;
    if ((bVar8) && (local_24.x * local_24.x + local_24.z * local_24.z < 100.0)) {
      if (*(int **)(*(int *)&this->field_0x1c + 0xa8) == *(int **)&this->field_0x14) {
        *(undefined4 *)&this->field_0x10 = 0xd;
        return false;
      }
      cVar2 = (**(code **)(**(int **)&this->field_0x14 + 0x68))();
      if (cVar2 != '\0') {
        (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
      }
    }
    pVVar5 = Normalize_Vector(&local_14,&local_24);
    local_30.x = pVVar5->x;
    local_30.y = pVVar5->y;
    local_30.z = pVVar5->z;
    if (local_5 != '\0') {
      local_14.x = 0.0;
      local_14.y = 0.0;
      local_14.z = 0.0;
      local_24.x = 0.0;
      local_24.y = 0.0;
      local_24.z = 0.0;
    }
    UnitTask::LookInDir((UnitTask *)this,&local_30);
    UnitTask::ApplyForce((UnitTask *)this,&local_24);
  }
  return false;
}
