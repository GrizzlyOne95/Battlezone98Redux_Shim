/*
 * Entry: 00410bfe
 * Name: DefendTask::InitState
 * Namespace: DefendTask
 * Signature: void InitState(DefendTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DefendTask::InitState(DefendTask *this)

{
  int iVar1;
  VECTOR_3D VVar2;
  GameObject *pGVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  float fVar6;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  SINCOS local_c;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0x10 = 6;
  }
  else if (iVar1 == 2) {
    UnitTask::InitGoto((UnitTask *)this);
  }
  else if (iVar1 == 3) {
    UnitTask::InitStuck((UnitTask *)this);
  }
  else if (iVar1 == 6) {
    fVar6 = Get_Time();
    *(float *)&this->field_0x124 = fVar6 + 10.0;
    pGVar3 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar3;
    if (pGVar3 == (GameObject *)0x0) {
      pfVar4 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
    }
    else {
      local_10 = *(float *)(*(int *)&this->field_0x14 + 0x158) + pGVar3->collisionRadius + 10.0;
      local_c.Cos = (float)rand();
      local_c = SinCos((float)(int)local_c.Cos * 0.00019175345);
      local_14 = local_c.Cos;
      local_1c = local_c.Sin;
      local_18 = 0.0;
      pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
      VVar2.y = local_18;
      VVar2.x = local_1c;
      VVar2.z = local_14;
      pVVar5 = AddMultVectors(&local_28,*pVVar5,local_10,VVar2);
      local_1c = pVVar5->x;
      local_18 = pVVar5->y;
      local_14 = pVVar5->z;
      pfVar4 = &local_1c;
    }
    *(float *)&this->field_0x2c = *pfVar4;
    *(float *)&this->field_0x30 = pfVar4[1];
    *(float *)&this->field_0x34 = pfVar4[2];
  }
  return;
}
