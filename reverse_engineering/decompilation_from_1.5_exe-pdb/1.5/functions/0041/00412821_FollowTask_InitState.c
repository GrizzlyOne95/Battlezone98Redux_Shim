/*
 * Entry: 00412821
 * Name: FollowTask::InitState
 * Namespace: FollowTask
 * Signature: void InitState(FollowTask * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall FollowTask::InitState(FollowTask *this)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = *(int *)&this->field_0xc;
  if (iVar1 == 1) {
    *(undefined4 *)&this->field_0x10 = 4;
  }
  else {
    if (iVar1 == 2) {
      UnitTask::InitGoto((UnitTask *)this);
      return;
    }
    if (iVar1 == 3) {
      UnitTask::InitStuck((UnitTask *)this);
      return;
    }
    if ((iVar1 == 4) && (*(FollowGroup **)&this->field_0x120 != (FollowGroup *)0x0)) {
      bVar2 = FollowGroup::NeedsReset
                        (*(FollowGroup **)&this->field_0x120,*(GameObject **)&this->field_0x14);
      if (bVar2) {
        ResetOffset(this);
        FollowGroup::DidReset(*(FollowGroup **)&this->field_0x120,*(GameObject **)&this->field_0x14)
        ;
        return;
      }
    }
  }
  return;
}
