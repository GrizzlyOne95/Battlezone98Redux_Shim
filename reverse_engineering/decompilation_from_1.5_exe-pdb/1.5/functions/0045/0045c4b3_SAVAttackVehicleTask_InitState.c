/*
 * Entry: 0045c4b3
 * Name: SAVAttackVehicleTask::InitState
 * Namespace: SAVAttackVehicleTask
 * Signature: void InitState(SAVAttackVehicleTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackVehicleTask::InitState(SAVAttackVehicleTask *this)

{
  int iVar1;
  VECTOR_3D VVar2;
  VECTOR_3D VVar3;
  bool bVar4;
  char cVar5;
  GameObject *pGVar6;
  VECTOR_3D *pVVar7;
  float fVar8;
  VECTOR_3D local_30;
  VECTOR_3D local_24;
  float local_18;
  float local_14;
  float local_10;
  SINCOS local_c;
  
  iVar1 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  *(undefined4 *)(iVar1 + 0xd0) = 0;
  *(undefined4 *)(iVar1 + 0xd4) = 0;
  *(undefined4 *)(iVar1 + 0xc4) = 0;
  *(undefined4 *)(iVar1 + 200) = 0;
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    pGVar6 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar6;
    if ((pGVar6 != (GameObject *)0x0) && (*(int *)(*(int *)&this->field_0x14 + 0x198) != 0)) {
      bVar4 = AbleToHitFromGround(this);
      this->field_0xc8 = bVar4;
      if ((bVar4) && (cVar5 = (**(code **)(**(int **)&this->field_0x14 + 0x68))(), cVar5 != '\0')) {
        *(undefined4 *)&this->field_0x10 = 5;
        return;
      }
      *(undefined4 *)&this->field_0x10 = 0xf;
      return;
    }
  }
  else {
    if (iVar1 != 2) {
      if (iVar1 == 5) {
        fVar8 = Get_Time();
        *(float *)&this->field_0x124 = fVar8 + 15.0;
        fVar8 = Get_Time();
        *(float *)&this->field_0x10c = fVar8 + 3.0;
        return;
      }
      if (iVar1 == 0xe) {
        (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
        fVar8 = Get_Time();
        *(float *)&this->field_0x124 = fVar8 + 5.0;
        return;
      }
      if (iVar1 != 0xf) {
        return;
      }
    }
    pGVar6 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    *(GameObject **)&this->field_0x1c = pGVar6;
    if (pGVar6 != (GameObject *)0x0) {
      pVVar7 = EstimatePosition(&local_24,pGVar6,2.0);
      local_18 = pVVar7->x;
      local_14 = pVVar7->y;
      local_10 = pVVar7->z;
      *(float *)&this->field_0x2c = local_18;
      *(float *)&this->field_0x30 = local_14;
      *(float *)&this->field_0x34 = local_10;
      if (*(int *)&this->field_0xc == 0xf) {
        local_c.Cos = (float)AttackGroup::GetSlot
                                       (*(AttackGroup **)&this->field_0x108,
                                        *(GameObject **)&this->field_0x14);
        local_c = SinCos((float)(int)local_c.Cos * 0.3926991);
        local_10 = local_c.Cos;
        local_18 = local_c.Sin;
        local_14 = 0.0;
        VVar3.x = *(float *)&this->field_0x2c;
        VVar3.y = *(float *)&this->field_0x30;
        VVar3.z = *(float *)&this->field_0x34;
        VVar2.z = local_10;
        VVar2.x = (float)(int)((ulonglong)local_c & 0xffffffff);
        VVar2.y = (float)(int)(((ulonglong)local_c & 0xffffffff) >> 0x20);
        pVVar7 = AddMultVectors(&local_30,VVar3,*(float *)&this->field_0xf4,VVar2);
        *(float *)&this->field_0x2c = pVVar7->x;
        *(float *)&this->field_0x30 = pVVar7->y;
        *(float *)&this->field_0x34 = pVVar7->z;
      }
      (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
  }
  *(undefined4 *)&this->field_0x10 = 0xd;
  return;
}
