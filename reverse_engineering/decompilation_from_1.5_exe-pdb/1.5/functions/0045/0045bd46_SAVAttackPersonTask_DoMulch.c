/*
 * Entry: 0045bd46
 * Name: SAVAttackPersonTask::DoMulch
 * Namespace: SAVAttackPersonTask
 * Signature: void DoMulch(SAVAttackPersonTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall SAVAttackPersonTask::DoMulch(SAVAttackPersonTask *this)

{
  int iVar1;
  bool bVar2;
  ushort uVar3;
  short sVar4;
  float *pfVar5;
  VECTOR_3D *pVVar6;
  float fVar7;
  VECTOR_3D local_2c;
  VECTOR_3D local_20;
  VECTOR_3D local_14;
  int local_8;
  
  local_8 = *(int *)(*(int *)&this->field_0x14 + 0x228);
  pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0xc))();
  local_20.x = *pfVar5;
  local_20.y = pfVar5[1];
  local_20.z = pfVar5[2];
  pfVar5 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
  local_2c.x = *pfVar5 - local_20.x;
  local_2c.y = pfVar5[1] - local_20.y;
  local_2c.z = pfVar5[2] - local_20.z;
  local_14.x = local_2c.x;
  local_14.y = local_2c.y;
  local_14.z = local_2c.z;
  pVVar6 = Vector_Unrotate(&local_2c,&local_14,
                           (MAT_3D *)(*(int *)(*(int *)&this->field_0x14 + 0xe8) + 0x20));
  local_14.x = pVVar6->x;
  local_14.y = pVVar6->y;
  local_14.z = pVVar6->z;
  pVVar6 = Normalize_Vector(&local_20,&local_14);
  iVar1 = local_8;
  local_2c.x = pVVar6->x;
  local_2c.y = pVVar6->y;
  local_2c.z = pVVar6->z;
  *(undefined4 *)(local_8 + 0xd4) = 0;
  *(undefined4 *)(local_8 + 0xcc) = 0;
  fVar7 = Clamp((local_14.z + 1.0) * 0.001,-0.25,0.25);
  *(float *)(iVar1 + 0xd0) = fVar7;
  fVar7 = Clamp(local_2c.x * -5.0 - *(float *)(*(int *)&this->field_0x14 + 0x130),-1.0,1.0);
  *(float *)(iVar1 + 0xc4) = fVar7;
  fVar7 = Clamp(*(float *)&this->field_0xb4 + local_2c.y,-1.0,1.0);
  *(float *)&this->field_0xb4 = fVar7;
  *(float *)(iVar1 + 200) = fVar7;
  if ((0.0 < local_14.z) && (local_14.z < 5.0)) {
    mulchDamage.damager =
         (_OBJ76 *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0x30))();
    mulchDamage.dmg_source =
         (_OBJ76 *)(**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 0x30))();
    uVar3 = mulchDamage._8_2_ & 0xfff4 | 4;
    mulchDamage._8_2_ =
         uVar3 ^ ((ushort)((*(byte *)(*(int *)(*(int *)&this->field_0x14 + 0xe8) + 0x14) & 0x30) !=
                          0) << 4 ^ uVar3) & 0x10;
    bVar2 = DistributedObject::IsRemote((DistributedObject *)(*(int *)&this->field_0x14 + 0x20));
    mulchDamage._8_2_ = (ushort)bVar2 << 5 | mulchDamage._8_2_ & 0xffdf;
    sVar4 = (**(code **)(*(int *)(*(int *)&this->field_0x14 + 0x20) + 4))();
    mulchDamage.dmg_value = 75.0;
    mulchDamage._8_2_ = mulchDamage._8_2_ ^ (sVar4 << 6 ^ mulchDamage._8_2_) & 0x3c0U;
    mulchNormal.x = 0.0;
    mulchNormal.y = 1.0;
    mulchNormal.z = 0.0;
    (**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0x38))(&mulchDamage,&mulchNormal);
  }
  return;
}
