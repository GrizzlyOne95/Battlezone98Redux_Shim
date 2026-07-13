/*
 * Entry: 0045b66b
 * Name: RescueTask::DrawStateA
 * Namespace: RescueTask
 * Signature: void DrawStateA(RescueTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall RescueTask::DrawStateA(RescueTask *this)

{
  int iVar1;
  VECTOR_3D *pVVar2;
  VECTOR_3D *pVVar3;
  long lVar4;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  UnitTask::DrawStateA((UnitTask *)this);
  if (*(int *)&this->field_0xc == 2) {
    iVar1 = *(int *)(*(int *)&this->field_0x1c + 0xe8);
    pVVar2 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    pVVar3 = AddMultVectors(&local_1c,*pVVar2,20.0,*(VECTOR_3D *)(iVar1 + 0x38));
    local_10.x = pVVar3->x;
    local_10.y = pVVar3->y;
    pVVar2 = &local_10;
    local_10.z = pVVar3->z;
    lVar4 = DisplayInterface::colorRed;
    pVVar3 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    WorldLine(pVVar3,pVVar2,lVar4);
  }
  return;
}
