/*
 * Entry: 0049db6c
 * Name: HoverCraft::UpdateModeList
 * Namespace: HoverCraft
 * Signature: void UpdateModeList(HoverCraft * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall HoverCraft::UpdateModeList(HoverCraft *this)

{
  int *this_00;
  bool bVar1;
  char cVar2;
  GameObject *pGVar3;
  int iVar4;
  Armory *this_01;
  bool bVar5;
  
  this_00 = &this->_padding_;
  bVar5 = false;
  ModeList::SetMode((ModeList *)this_00,0,1,true);
  ModeList::SetMode((ModeList *)this_00,1,2,true);
  ModeList::SetMode((ModeList *)this_00,2,10,true);
  ModeList::SetMode((ModeList *)this_00,3,0xe,this->_padding_ != 0);
  pGVar3 = Team::GetSlot((Team *)this->_padding_,0);
  if ((this->_padding_ == 0) || (pGVar3 == (GameObject *)0x0)) {
LAB_0049dbdf:
    bVar1 = false;
  }
  else {
    iVar4 = (**(code **)pGVar3->_padding_)();
    if (*(int *)(iVar4 + 0x28) != 4) goto LAB_0049dbdf;
    bVar1 = true;
  }
  ModeList::SetMode((ModeList *)this_00,4,7,bVar1);
  this_01 = (Armory *)Team::GetSlot((Team *)this->_padding_,3);
  if (this_01 != (Armory *)0x0) {
    bVar1 = Armory::CanSendRepair(this_01);
    if (!bVar1) {
      this_01 = (Armory *)0x0;
    }
  }
  if ((float)this->_padding_ <= (float)this->_padding_) {
LAB_0049dc3b:
    bVar1 = false;
  }
  else {
    if (this_01 == (Armory *)0x0) {
      iVar4 = Team::FirstFilledSlot((Team *)this->_padding_,0x3c,0x40);
      if (iVar4 < 0) goto LAB_0049dc3b;
    }
    bVar1 = true;
  }
  ModeList::SetMode((ModeList *)this_00,5,5,bVar1);
  if ((int)(this->_padding_ ^ 0x33333333U) < (int)(this->_padding_ ^ 0x33333333U)) {
    if (this_01 == (Armory *)0x0) {
      iVar4 = Team::FirstFilledSlot((Team *)this->_padding_,0x41,0x45);
      if (iVar4 < 0) goto LAB_0049dc7d;
    }
    bVar1 = true;
  }
  else {
LAB_0049dc7d:
    bVar1 = false;
  }
  ModeList::SetMode((ModeList *)this_00,6,6,bVar1);
  ModeList::SetMode((ModeList *)this_00,7,0,false);
  ModeList::SetMode((ModeList *)this_00,8,0,false);
  ModeList::SetMode((ModeList *)this_00,9,0,false);
  pGVar3 = Team::GetSlot((Team *)this->_padding_,1);
  if (pGVar3 == (GameObject *)0x0) {
LAB_0049dcd1:
    iVar4 = Team::FirstFilledSlot((Team *)this->_padding_,0x46,0x4a);
    if (iVar4 < 0) goto LAB_0049dce7;
  }
  else {
    cVar2 = (**(code **)(pGVar3->_padding_ + 100))();
    if (cVar2 == '\0') {
      pGVar3 = (GameObject *)0x0;
    }
    if (pGVar3 == (GameObject *)0x0) goto LAB_0049dcd1;
  }
  bVar5 = true;
LAB_0049dce7:
  ModeList::SetMode((ModeList *)this_00,10,8,bVar5);
  return;
}
