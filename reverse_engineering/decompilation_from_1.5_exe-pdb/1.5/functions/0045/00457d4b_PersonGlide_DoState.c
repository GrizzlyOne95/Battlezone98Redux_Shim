/*
 * Entry: 00457d4b
 * Name: PersonGlide::DoState
 * Namespace: PersonGlide
 * Signature: void DoState(PersonGlide * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonGlide::DoState(PersonGlide *this)

{
  int iVar1;
  VECTOR_3D_LONG VVar2;
  float *pfVar3;
  bool bVar4;
  VECTOR_3D *pVVar5;
  undefined4 *puVar6;
  int iVar7;
  float fVar8;
  double dVar9;
  VECTOR_3D local_38;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  float *local_14;
  GameObject *local_10;
  MAT_3D *local_c;
  float local_8;
  
  pVVar5 = (VECTOR_3D *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  bVar4 = OnBlocked(pVVar5);
  if (bVar4) {
    if (*(int *)&this->field_0xc == 0xd) {
      return;
    }
    if (*(int *)&this->field_0x18 != 0) {
      local_10 = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
      if (local_10 == (GameObject *)0x0) {
        UnitTask::CleanGoto((UnitTask *)this);
        *(undefined4 *)&this->field_0xc = 0xd;
        return;
      }
      puVar6 = (undefined4 *)(**(code **)(local_10->_padding_ + 0xc))();
      *(undefined4 *)&this->field_0x2c = *puVar6;
      *(undefined4 *)&this->field_0x30 = puVar6[1];
      *(undefined4 *)&this->field_0x34 = puVar6[2];
      if (local_10->aiProcess != (AiProcess *)0x0) goto LAB_00457d6c;
    }
    iVar7 = *(int *)&this->field_0x14;
    local_10 = (GameObject *)(iVar7 + 0x120);
    local_14 = (float *)(*(int *)(iVar7 + 0x228) + 0xc4);
    local_20.x = *(float *)&this->field_0x2c;
    iVar1 = *(int *)(iVar7 + 0xe8);
    local_20.y = *(float *)&this->field_0x30;
    local_c = (MAT_3D *)(iVar1 + 0x20);
    local_20.z = *(float *)&this->field_0x34;
    if (*(float *)(iVar7 + 0x124) < 0.0) {
      local_8 = 10.0;
      VVar2.z._4_4_ = (int)((ulonglong)*(undefined8 *)(iVar1 + 0x58) >> 0x20);
      VVar2._0_20_ = *(undefined1 (*) [20])(iVar1 + 0x48);
      iVar7 = Terrain_GetIntersection(VVar2,*(VECTOR_3D *)local_10,&local_8,(VECTOR_3D *)0x0);
      if (iVar7 != 0) {
        local_20.x = local_20.x - (float)local_10->_padding_ * local_8;
        local_20.z = local_20.z - (float)local_10->_padding_ * local_8;
      }
    }
    pVVar5 = Vector_Untransform(&local_2c,&local_20,local_c);
    local_20.x = pVVar5->x;
    local_20.y = pVVar5->y;
    local_20.z = pVVar5->z;
    pVVar5 = Vector_Unrotate(&local_38,(VECTOR_3D *)local_10,local_c);
    local_2c.x = pVVar5->x;
    local_2c.y = pVVar5->y;
    local_2c.z = pVVar5->z;
    fVar8 = Clamp(local_20.x * 0.2 - local_2c.x * 0.2,-1.0,1.0);
    pfVar3 = local_14;
    local_14[2] = fVar8;
    fVar8 = Clamp(local_20.z * 0.2 - local_2c.z * 0.2,-1.0,1.0);
    pfVar3[3] = fVar8;
    dVar9 = rsqrt((double)(local_20.x * local_20.x + local_20.z * local_20.z + 0.0001));
    fVar8 = Clamp((float)dVar9 * local_20.x * 5.0 - *(float *)(*(int *)&this->field_0x14 + 0x130),
                  -1.0,1.0);
    *pfVar3 = fVar8;
  }
  else {
LAB_00457d6c:
    UnitTask::CleanGoto((UnitTask *)this);
    *(undefined4 *)&this->field_0xc = 0xd;
  }
  return;
}
