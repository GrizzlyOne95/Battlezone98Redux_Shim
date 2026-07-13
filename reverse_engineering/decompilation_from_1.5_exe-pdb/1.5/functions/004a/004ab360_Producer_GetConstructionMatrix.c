/*
 * Entry: 004ab360
 * Name: Producer::GetConstructionMatrix
 * Namespace: Producer
 * Signature: MAT_3D * GetConstructionMatrix(Producer * this, MAT_3D * __return_storage_ptr__)
 * Symbol source: IMPORTED
 * Export status: ok
 */

MAT_3D * __thiscall Producer::GetConstructionMatrix(Producer *this,MAT_3D *__return_storage_ptr__)

{
  MAT_3D *pMVar1;
  SPHERE *pSVar2;
  VECTOR_3D *pVVar3;
  int iVar4;
  MAT_3D *pMVar5;
  MAT_3D *pMVar6;
  _OBJ76 *p_Var7;
  MAT_3D local_9c;
  VECTOR_3D local_5c;
  MAT_3D local_50;
  float local_10;
  float local_c;
  float local_8;
  
  if (this->buildClass->class_id == CLASS_ID_POWERUP) {
    p_Var7 = this->ejectPowerup;
  }
  else {
    p_Var7 = this->ejectVehicle;
  }
  pMVar1 = obj_rel_parent_matrix(&local_9c,p_Var7,(_OBJ76 *)0x0);
  pMVar5 = &local_50;
  pMVar6 = pMVar5;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar6->right_x = pMVar1->right_x;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
    pMVar6 = (MAT_3D *)&pMVar6->right_y;
  }
  pSVar2 = GameObjectClass::GetBoundingSphere(this->buildClass);
  pVVar3 = Vector_Rotate(&local_5c,&pSVar2->origin,pMVar5);
  local_10 = pVVar3->x;
  local_c = pVVar3->y;
  local_8 = pVVar3->z;
  local_50.posit_x = (double)((float)local_50.posit_x - pVVar3->x);
  local_50.posit_y = (double)((float)local_50.posit_y - pVVar3->y);
  local_50.posit_z = (double)((float)local_50.posit_z - pVVar3->z);
  pMVar5 = &local_50;
  pMVar1 = __return_storage_ptr__;
  for (iVar4 = 0x10; iVar4 != 0; iVar4 = iVar4 + -1) {
    pMVar1->right_x = pMVar5->right_x;
    pMVar5 = (MAT_3D *)&pMVar5->right_y;
    pMVar1 = (MAT_3D *)&pMVar1->right_y;
  }
  return __return_storage_ptr__;
}
