/*
 * Entry: 00457f3e
 * Name: PersonStraight::DoState
 * Namespace: PersonStraight
 * Signature: void DoState(PersonStraight * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PersonStraight::DoState(PersonStraight *this)

{
  GameObject *pGVar1;
  undefined4 *puVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  double dVar5;
  VECTOR_3D local_24;
  VECTOR_3D local_18;
  GameObject *local_c;
  float local_8;
  
  if (*(int *)&this->field_0xc == 0xd) {
    return;
  }
  if (*(int *)&this->field_0x18 != 0) {
    local_c = GameObjectHandle::GetObj(*(int *)&this->field_0x18);
    if (local_c == (GameObject *)0x0) {
      UnitTask::CleanGoto((UnitTask *)this);
      *(undefined4 *)&this->field_0xc = 0xd;
      return;
    }
    puVar2 = (undefined4 *)(**(code **)(local_c->_padding_ + 0xc))();
    *(undefined4 *)&this->field_0x2c = *puVar2;
    *(undefined4 *)&this->field_0x30 = puVar2[1];
    *(undefined4 *)&this->field_0x34 = puVar2[2];
    *(undefined4 *)
     (*(int *)(*(int *)&this->field_0x44 + 8) + -8 + *(int *)(*(int *)&this->field_0x44 + 4) * 8) =
         *(undefined4 *)&this->field_0x2c;
    *(undefined4 *)
     (*(int *)(*(int *)&this->field_0x44 + 8) + -4 + *(int *)(*(int *)&this->field_0x44 + 4) * 8) =
         *(undefined4 *)&this->field_0x34;
    if (local_c->aiProcess != (AiProcess *)0x0) {
      UnitTask::CleanGoto((UnitTask *)this);
      *(undefined4 *)&this->field_0xc = 0xd;
      return;
    }
  }
  pVVar3 = UnitTask::GotoForce((UnitTask *)this,&local_18,true);
  *(float *)&this->field_0x50 = pVVar3->x;
  *(float *)&this->field_0x54 = pVVar3->y;
  *(float *)&this->field_0x58 = pVVar3->z;
  local_c = (GameObject *)(*(int *)(*(int *)&this->field_0x14 + 0x228) + 0xc4);
  pVVar3 = Vector_Unrotate(&local_24,(VECTOR_3D *)&this->field_0x50,
                           (MAT_3D *)(*(int *)(*(int *)&this->field_0x14 + 0xe8) + 0x20));
  local_18.x = pVVar3->x;
  local_18.y = pVVar3->y;
  local_18.z = pVVar3->z;
  dVar5 = rsqrt((double)(local_18.x * local_18.x + local_18.z * local_18.z + 0.0001));
  fVar4 = Clamp((float)dVar5 * local_18.x * -5.0 - *(float *)(*(int *)&this->field_0x14 + 0x130),
                -1.0,1.0);
  pGVar1 = local_c;
  *(float *)local_c = fVar4;
  local_8 = 1.0;
  if (ABS(fVar4) == 1.0) {
    local_8 = 0.25;
  }
  else if (0.7 < ABS(fVar4)) {
    local_8 = 0.5;
  }
  local_c = (GameObject *)-local_8;
  fVar4 = Clamp(*(float *)&this->field_0x68 * local_18.z,(float)local_c,local_8);
  *(float *)((int)pGVar1 + 0xc) = fVar4;
  fVar4 = Clamp(*(float *)&this->field_0x6c * local_18.x,(float)local_c,local_8);
  *(float *)((int)pGVar1 + 8) = fVar4;
  return;
}
