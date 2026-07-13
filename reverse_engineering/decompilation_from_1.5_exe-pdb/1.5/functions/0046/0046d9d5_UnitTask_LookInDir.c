/*
 * Entry: 0046d9d5
 * Name: UnitTask::LookInDir
 * Namespace: UnitTask
 * Signature: void LookInDir(UnitTask * this, VECTOR_3D * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall UnitTask::LookInDir(UnitTask *this,VECTOR_3D *param_1)

{
  VECTOR_3D *pVVar1;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  pVVar1 = Vector_Unrotate(&local_1c,param_1,(MAT_3D *)(this->me->_padding_ + 0x20));
  local_10.x = pVVar1->x;
  local_10.y = pVVar1->y;
  local_10.z = pVVar1->z;
  LookInLocalDir(this,&local_10);
  return;
}
