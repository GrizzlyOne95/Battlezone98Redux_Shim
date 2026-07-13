/*
 * Entry: 0049f753
 * Name: Howitzer::UpdateModeList
 * Namespace: Howitzer
 * Signature: void UpdateModeList(Howitzer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Howitzer::UpdateModeList(Howitzer *this)

{
  undefined1 *this_00;
  bool bVar1;
  char cVar2;
  GameObject *pGVar3;
  int iVar4;
  Armory *this_01;
  bool bVar5;
  
  this_00 = &this->field_0x19c;
  bVar5 = false;
  ModeList::SetMode((ModeList *)this_00,0,1,true);
  ModeList::SetMode((ModeList *)this_00,1,2,true);
  ModeList::SetMode((ModeList *)this_00,2,10,true);
  ModeList::SetMode((ModeList *)this_00,3,0xe,*(int *)&this->field_0x198 != 0);
  pGVar3 = Team::GetSlot(*(Team **)&this->field_0x170,0);
  if ((*(int *)&this->field_0xe0 == 0) || (pGVar3 == (GameObject *)0x0)) {
LAB_0049f7c8:
    bVar1 = false;
  }
  else {
    iVar4 = (**(code **)pGVar3->_padding_)();
    if (*(int *)(iVar4 + 0x28) != 4) goto LAB_0049f7c8;
    bVar1 = true;
  }
  ModeList::SetMode((ModeList *)this_00,4,7,bVar1);
  this_01 = (Armory *)Team::GetSlot(*(Team **)&this->field_0x170,3);
  if (this_01 != (Armory *)0x0) {
    bVar1 = Armory::CanSendRepair(this_01);
    if (!bVar1) {
      this_01 = (Armory *)0x0;
    }
  }
  if (*(float *)&this->field_0x200 <= *(float *)&this->field_0x1fc) {
LAB_0049f82c:
    bVar1 = false;
  }
  else {
    if (this_01 == (Armory *)0x0) {
      if (*(int *)&this->field_0x220 == 0) {
        iVar4 = Team::FirstFilledSlot(*(Team **)&this->field_0x170,0x3c,0x40);
        if (-1 < iVar4) goto LAB_0049f828;
      }
      goto LAB_0049f82c;
    }
LAB_0049f828:
    bVar1 = true;
  }
  ModeList::SetMode((ModeList *)this_00,5,5,bVar1);
  if ((int)(*(uint *)&this->field_0x208 ^ 0x33333333) <
      (int)(*(uint *)&this->field_0x20c ^ 0x33333333)) {
    if (this_01 == (Armory *)0x0) {
      if (*(int *)&this->field_0x220 == 0) {
        iVar4 = Team::FirstFilledSlot(*(Team **)&this->field_0x170,0x41,0x45);
        if (-1 < iVar4) goto LAB_0049f872;
      }
      goto LAB_0049f876;
    }
LAB_0049f872:
    bVar1 = true;
  }
  else {
LAB_0049f876:
    bVar1 = false;
  }
  ModeList::SetMode((ModeList *)this_00,6,6,bVar1);
  ModeList::SetMode((ModeList *)this_00,7,4,*(int *)&this->field_0x220 == 0);
  ModeList::SetMode((ModeList *)this_00,8,0,false);
  ModeList::SetMode((ModeList *)this_00,9,0,false);
  pGVar3 = Team::GetSlot(*(Team **)&this->field_0x170,1);
  if (pGVar3 == (GameObject *)0x0) {
LAB_0049f8d7:
    iVar4 = Team::FirstFilledSlot(*(Team **)&this->field_0x170,0x46,0x4a);
    if (iVar4 < 0) goto LAB_0049f8ed;
  }
  else {
    cVar2 = (**(code **)(pGVar3->_padding_ + 100))();
    if (cVar2 == '\0') {
      pGVar3 = (GameObject *)0x0;
    }
    if (pGVar3 == (GameObject *)0x0) goto LAB_0049f8d7;
  }
  bVar5 = true;
LAB_0049f8ed:
  ModeList::SetMode((ModeList *)this_00,10,8,bVar5);
  return;
}
