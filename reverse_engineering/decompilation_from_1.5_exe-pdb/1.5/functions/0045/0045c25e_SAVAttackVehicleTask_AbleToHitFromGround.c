/*
 * Entry: 0045c25e
 * Name: SAVAttackVehicleTask::AbleToHitFromGround
 * Namespace: SAVAttackVehicleTask
 * Signature: bool AbleToHitFromGround(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall SAVAttackVehicleTask::AbleToHitFromGround(SAVAttackVehicleTask *this)

{
  float fVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  float fVar5;
  
  iVar2 = *(int *)(*(int *)&this->field_0x14 + 0xe8);
  iVar4 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x14 + 0x20))();
  fVar1 = *(float *)(iVar4 + 0x324);
  fVar5 = Terrain_FindFloor(*(double *)(iVar2 + 0x48),*(double *)(iVar2 + 0x58));
  fVar1 = (fVar5 + fVar1) - (float)*(double *)(iVar2 + 0x50);
  *(double *)(iVar2 + 0x50) = (double)((float)*(double *)(iVar2 + 0x50) + fVar1);
  if (*(int *)&this->field_0xb8 != 0) {
    *(double *)(*(int *)&this->field_0xb8 + 0x50) =
         (double)(fVar1 + (float)*(double *)(*(int *)&this->field_0xb8 + 0x50));
  }
  bVar3 = UnitTask::AbleToHit((UnitTask *)this);
  *(double *)(iVar2 + 0x50) = *(double *)(iVar2 + 0x50) - (double)fVar1;
  if (*(int *)&this->field_0xb8 != 0) {
    *(double *)(*(int *)&this->field_0xb8 + 0x50) =
         *(double *)(*(int *)&this->field_0xb8 + 0x50) - (double)fVar1;
  }
  return bVar3;
}
