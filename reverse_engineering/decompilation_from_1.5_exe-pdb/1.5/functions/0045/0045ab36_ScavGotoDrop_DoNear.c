/*
 * Entry: 0045ab36
 * Name: ScavGotoDrop::DoNear
 * Namespace: ScavGotoDrop
 * Signature: bool DoNear(ScavGotoDrop * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __thiscall ScavGotoDrop::DoNear(ScavGotoDrop *this)

{
  Team *this_00;
  char cVar1;
  int iVar2;
  long lVar3;
  long lVar4;
  int iVar5;
  
  iVar2 = (*(code *)**(undefined4 **)(*(int *)&this->field_0x1c + 0x20))();
  if ((*(int *)(iVar2 + 0x20) != 0x52435943) ||
     (cVar1 = (**(code **)(**(int **)&this->field_0x1c + 100))(), cVar1 != '\0')) {
    this_00 = *(Team **)(*(int *)&this->field_0x1c + 0x170);
    lVar3 = Team::GetScrap(this_00);
    lVar4 = Team::GetMaxScrap(this_00);
    if (lVar3 < lVar4) {
      iVar2 = (*(Scavenger **)&this->field_0x14)->scrapHeld;
      Scavenger::UnloadScrap(*(Scavenger **)&this->field_0x14,iVar2);
      iVar5 = Net_IsNetGame();
      if (iVar5 != 0) {
        iVar2 = iVar2 * 2;
      }
      Team::AddScrap(this_00,iVar2);
    }
  }
  *(undefined4 *)&this->field_0x10 = 0xd;
  return false;
}
