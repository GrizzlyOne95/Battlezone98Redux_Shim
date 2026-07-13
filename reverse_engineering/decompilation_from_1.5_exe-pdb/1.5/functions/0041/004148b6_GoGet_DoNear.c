/*
 * Entry: 004148b6
 * Name: GoGet::DoNear
 * Namespace: GoGet
 * Signature: bool DoNear(GoGet * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall GoGet::DoNear(GoGet *this)

{
  int iVar1;
  float *pfVar2;
  VECTOR_3D *pVVar3;
  float fVar4;
  VECTOR_3D local_40;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  float local_8;
  
  fVar4 = Get_Time();
  if (fVar4 <= *(float *)&this->field_0x158 + 5.0) {
    iVar1 = *(int *)(*(int *)&this->field_0x14 + 0xe8);
    local_10 = (float)*(double *)(iVar1 + 0x48);
    local_c = (float)*(double *)(iVar1 + 0x50);
    local_8 = (float)*(double *)(iVar1 + 0x58);
    pfVar2 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
    local_1c = *pfVar2;
    local_18 = pfVar2[1];
    local_14 = pfVar2[2];
    local_34.x = local_1c - local_10;
    local_34.y = local_18 - local_c;
    local_34.z = local_14 - local_8;
    local_28.x = local_34.x;
    local_28.y = local_34.y;
    local_28.z = local_34.z;
    pVVar3 = Normalize_Vector(&local_28,&local_34);
    local_40.x = pVVar3->x;
    local_40.y = pVVar3->y;
    local_40.z = pVVar3->z;
    UnitTask::LookInDir((UnitTask *)this,&local_40);
    UnitTask::ApplyForce((UnitTask *)this,&local_34);
  }
  else {
    *(undefined4 *)&this->field_0x10 = 0xd;
  }
  return false;
}
