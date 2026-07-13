/*
 * Entry: 0045ad0c
 * Name: ScavGotoScrap::DoNear
 * Namespace: ScavGotoScrap
 * Signature: bool DoNear(ScavGotoScrap * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavGotoScrap::DoNear(ScavGotoScrap *this)

{
  DistributedObject *this_00;
  Scavenger *this_01;
  VECTOR_3D VVar1;
  bool bVar2;
  int iVar3;
  float *pfVar4;
  VECTOR_3D *pVVar5;
  float fVar6;
  VECTOR_3D local_34;
  VECTOR_3D local_28;
  VECTOR_3D local_1c;
  VECTOR_3D local_10;
  
  fVar6 = Get_TimeLocal();
  if (*(float *)&this->field_0x158 + 5.0 < fVar6) {
    this_01 = *(Scavenger **)&this->field_0x14;
    this_00 = (DistributedObject *)(*(int *)&this->field_0x1c + 0x20);
    iVar3 = (**(code **)this_00->_padding_)();
    Scavenger::LoadScrap(this_01,*(int *)(iVar3 + 0x54));
    iVar3 = Net_IsNetGame();
    if ((iVar3 == 0) ||
       (bVar2 = DistributedObject::IsLocal((DistributedObject *)&this_01->_padding_), bVar2)) {
      iVar3 = Net_IsNetGame();
      if ((iVar3 == 0) || (bVar2 = DistributedObject::IsLocal(this_00), bVar2)) {
        (**(code **)(this_00->_padding_ + 0x10))();
      }
      else {
        iVar3 = Net_IsNetGame();
        if ((iVar3 != 0) && (bVar2 = DistributedObject::IsRemote(this_00), bVar2)) {
          DistributedObject::RemoteDelete(this_00);
        }
      }
    }
    *(undefined4 *)&this->field_0x10 = 0xd;
    return false;
  }
  GameObject::SetTarget(*(GameObject **)&this->field_0x14,*(GameObject **)&this->field_0x1c);
  if ((*(int **)&this->field_0x14)[0x88] == 0) {
    (**(code **)(**(int **)&this->field_0x14 + 0x5c))();
  }
  iVar3 = *(int *)(*(int *)&this->field_0x14 + 0xe8);
  local_10.x = (float)*(double *)(iVar3 + 0x48);
  local_10.y = (float)*(double *)(iVar3 + 0x50);
  local_10.z = (float)*(double *)(iVar3 + 0x58);
  pfVar4 = (float *)(**(code **)(*(int *)(*(int *)&this->field_0x1c + 0x20) + 0xc))();
  local_28.x = *pfVar4 - local_10.x;
  local_28.y = pfVar4[1] - local_10.y;
  local_28.z = pfVar4[2] - local_10.z;
  local_1c.x = local_28.x;
  local_1c.y = local_28.y;
  local_1c.z = local_28.z;
  pVVar5 = Normalize_Vector(&local_10,&local_28);
  local_34.x = pVVar5->x;
  local_34.y = pVVar5->y;
  local_34.z = pVVar5->z;
  UnitTask::LookInDir((UnitTask *)this,&local_34);
  VVar1.y = local_1c.y;
  VVar1.x = local_1c.x;
  VVar1.z = local_1c.z;
  pVVar5 = ScaleVector(&local_1c,5.0,VVar1);
  local_28.x = pVVar5->x;
  local_28.y = pVVar5->y;
  local_28.z = pVVar5->z;
  UnitTask::ApplyForce((UnitTask *)this,&local_28);
  return false;
}
