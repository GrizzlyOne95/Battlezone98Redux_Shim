/*
 * Entry: 00530343
 * Name: ImageLauncher::UpdateTarget
 * Namespace: ImageLauncher
 * Signature: GameObject * UpdateTarget(ImageLauncher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall ImageLauncher::UpdateTarget(ImageLauncher *this,float param_1)

{
  double dVar1;
  float fVar2;
  VECTOR_3D_LONG VVar3;
  VECTOR_3D VVar4;
  double dVar5;
  GameObject *pGVar6;
  bool bVar7;
  MAT_3D *pMVar8;
  float *pfVar9;
  SPHERE *pSVar10;
  int iVar11;
  int iVar12;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar13;
  MAT_3D local_124;
  MAT_3D local_e4;
  Range_Search_Results local_a4;
  float local_78 [6];
  float local_60;
  float local_5c;
  float local_58;
  double local_50;
  undefined8 local_48;
  double local_40;
  double local_38;
  double local_28;
  GameObject *local_20;
  GameObject *local_1c;
  int *local_18;
  VECTOR_3D local_14;
  float local_8;
  
  pMVar8 = Matrix_Multiply(&local_124,(MAT_3D *)(*(int *)&this->field_0x10 + 0x20),
                           (MAT_3D *)&this->field_0x20);
  iVar12 = *(int *)&this->field_0x8;
  pfVar9 = local_78;
  for (iVar11 = 0x10; iVar11 != 0; iVar11 = iVar11 + -1) {
    *pfVar9 = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pfVar9 = pfVar9 + 1;
  }
  local_38 = local_50;
  local_28 = local_40;
  local_14.x = local_60;
  local_14.y = local_5c;
  local_14.z = local_58;
  local_8 = *(float *)(iVar12 + 0x7c);
  VVar3.y._0_4_ = (int)local_48;
  VVar3.x = local_50;
  VVar3.y._4_4_ = (int)((ulonglong)local_48 >> 0x20);
  VVar3.z._0_4_ = SUB84(local_40,0);
  VVar3.z._4_4_ = (int)((ulonglong)local_40 >> 0x20);
  VVar4.y = local_5c;
  VVar4.x = local_60;
  VVar4.z = local_58;
  Terrain_GetIntersection(VVar3,VVar4,&local_8,(VECTOR_3D *)0x0);
  local_1c = (GameObject *)0x0;
  pMVar8 = Matrix_Inverse(&local_124,unaff_EDI);
  dVar5 = local_28;
  dVar1 = (double)local_8;
  pMVar13 = &local_e4;
  for (iVar12 = 0x10; iVar12 != 0; iVar12 = iVar12 + -1) {
    pMVar13->right_x = pMVar8->right_x;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
    pMVar13 = (MAT_3D *)&pMVar13->right_y;
  }
  Range::Search(GameObject::objectRange,local_38,dVar5,dVar1,&local_a4);
  while( true ) {
    bVar7 = Range_Search_Results::Get_Next_Object(&local_a4,&local_18);
    if (!bVar7) break;
    local_20 = GameObject::GetObj(*local_18);
    if (((local_20 != (GameObject *)0x0) && (local_20 != *(GameObject **)&this->field_0xc0)) &&
       ((local_20->obj->flags & 0x400) == 0)) {
      pfVar9 = (float *)(**(code **)(local_20->_padding_ + 0xc))();
      local_14.x = *pfVar9;
      local_14.y = pfVar9[1];
      local_14.z = pfVar9[2];
      Vector_Transform(&local_14,&local_14,1,&local_e4);
      pGVar6 = local_20;
      if ((0.0 <= local_14.z) && (local_14.z <= local_8)) {
        pSVar10 = GameObject::GetSphere(local_20);
        fVar2 = pSVar10->radius * 0.75;
        if (local_14.x * local_14.x + local_14.y * local_14.y <= fVar2 * fVar2) {
          local_1c = pGVar6;
          local_8 = local_14.z;
        }
      }
    }
  }
  return local_1c;
}
