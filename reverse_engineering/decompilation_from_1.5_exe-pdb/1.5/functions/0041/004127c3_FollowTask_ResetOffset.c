/*
 * Entry: 004127c3
 * Name: FollowTask::ResetOffset
 * Namespace: FollowTask
 * Signature: void ResetOffset(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowTask::ResetOffset(FollowTask *this)

{
  undefined4 *puVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = FollowGroup::GetFollowCount(*(FollowGroup **)&this->field_0x120);
  iVar4 = FollowGroup::GetSlot
                    (*(FollowGroup **)&this->field_0x120,*(GameObject **)&this->field_0x14);
  if (uVar3 < 5) {
    puVar1 = (undefined4 *)((int)(&offsets4[3].z)[uVar3] + iVar4 * 8);
    *(undefined4 *)&this->field_0x114 = *puVar1;
    fVar2 = (float)puVar1[1];
  }
  else {
    *(undefined4 *)&this->field_0x114 = 0;
    fVar2 = (float)(iVar4 + 1) * -20.0;
  }
  *(float *)&this->field_0x118 = fVar2;
  return;
}
