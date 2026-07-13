/*
 * Entry: 0046d979
 * Name: UnitTask::LookAtPos
 * Namespace: UnitTask
 * Signature: void LookAtPos(UnitTask * this, VECTOR_3D * param_1, VECTOR_3D * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::LookAtPos(UnitTask *this,VECTOR_3D *param_1,VECTOR_3D *param_2)

{
  VECTOR_3D *pVVar1;
  MAT_3D *pMVar2;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  UnitTask *local_8;
  
  pMVar2 = (MAT_3D *)(this->me->_padding_ + 0x20);
  local_8 = this;
  pVVar1 = Vector_Untransform(&local_14,param_1,pMVar2);
  local_20.x = pVVar1->x;
  local_20.y = pVVar1->y;
  local_20.z = pVVar1->z;
  pVVar1 = Vector_Unrotate(&local_2c,param_2,pMVar2);
  local_14.x = pVVar1->x;
  local_14.y = pVVar1->y;
  local_14.z = pVVar1->z;
  LookAtLocalPos(local_8,&local_20,&local_14);
  return;
}
