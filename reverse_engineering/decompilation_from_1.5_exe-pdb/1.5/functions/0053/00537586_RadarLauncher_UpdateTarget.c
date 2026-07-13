/*
 * Entry: 00537586
 * Name: RadarLauncher::UpdateTarget
 * Namespace: RadarLauncher
 * Signature: GameObject * UpdateTarget(RadarLauncher * this, float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

GameObject * __thiscall RadarLauncher::UpdateTarget(RadarLauncher *this,float param_1)

{
  float fVar1;
  float fVar2;
  MAT_3D *pMVar3;
  float *pfVar4;
  SPHERE *pSVar5;
  int iVar6;
  int iVar7;
  MAT_3D *unaff_EDI;
  MAT_3D *pMVar8;
  MAT_3D local_d8;
  MAT_3D local_98;
  float local_58 [16];
  float local_18;
  GameObject *local_14;
  VECTOR_3D local_10;
  
  pMVar3 = Matrix_Multiply(&local_d8,(MAT_3D *)(*(int *)&this->field_0x10 + 0x20),
                           (MAT_3D *)&this->field_0x20);
  pfVar4 = local_58;
  for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
    *pfVar4 = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pfVar4 = pfVar4 + 1;
  }
  pMVar3 = Matrix_Inverse(&local_d8,unaff_EDI);
  iVar6 = *(int *)&this->field_0x8;
  pMVar8 = &local_98;
  for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
    pMVar8->right_x = pMVar3->right_x;
    pMVar3 = (MAT_3D *)&pMVar3->right_y;
    pMVar8 = (MAT_3D *)&pMVar8->right_y;
  }
  local_18 = *(float *)(iVar6 + 0x7c);
  local_14 = GameObject::GetObj(*(int *)(*(int *)&this->field_0xc0 + 0x214));
  if (local_14 != (GameObject *)0x0) {
    pfVar4 = (float *)(**(code **)(local_14->_padding_ + 0xc))();
    local_10.x = *pfVar4;
    local_10.y = pfVar4[1];
    local_10.z = pfVar4[2];
    Vector_Transform(&local_10,&local_10,1,&local_98);
    if ((0.0 <= local_10.z) && (local_10.z <= local_18)) {
      pSVar5 = GameObject::GetSphere(local_14);
      fVar1 = pSVar5->radius * 0.75;
      fVar2 = local_10.x * local_10.x + local_10.y * local_10.y;
      if (fVar2 <= fVar1 * fVar1) {
        return local_14;
      }
      if (fVar2 <= (local_10.z * local_10.z + fVar2) * *(float *)&this->field_0xb4) {
        return local_14;
      }
    }
  }
  return (GameObject *)0x0;
}
