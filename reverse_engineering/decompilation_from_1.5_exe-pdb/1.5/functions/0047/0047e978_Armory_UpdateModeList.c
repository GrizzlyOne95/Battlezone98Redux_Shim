/*
 * Entry: 0047e978
 * Name: Armory::UpdateModeList
 * Namespace: Armory
 * Signature: void UpdateModeList(Armory * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Armory::UpdateModeList(Armory *this)

{
  int *piVar1;
  MENU_MODE MVar2;
  int iVar3;
  char cVar4;
  bool bVar5;
  int iVar6;
  long lVar7;
  long lVar8;
  long lVar9;
  int *local_24;
  int local_1c;
  GameObject *local_10;
  int *local_c;
  
  bVar5 = false;
  if (this->_padding_ != 0) {
    piVar1 = &this->_padding_;
    ModeList::SetMode((ModeList *)piVar1,0,0,false);
    MVar2 = this->menu;
    if (MVar2 == MENU_NORMAL) {
      local_24 = (int *)(this->_padding_ + 0x3d8);
      local_c = (int *)0x5;
      ModeList::SetMode((ModeList *)piVar1,6,0x12,this->_padding_ == 2);
      ModeList::SetMode((ModeList *)piVar1,7,0x13,this->_padding_ == 2);
      ModeList::SetMode((ModeList *)piVar1,8,0x14,this->_padding_ == 2);
      ModeList::SetMode((ModeList *)piVar1,9,0x15,this->_padding_ == 2);
    }
    else {
      if (MVar2 == MENU_CANNONS) {
        local_24 = (int *)(this->_padding_ + 0x430);
      }
      else if (MVar2 == MENU_ROCKETS) {
        local_24 = (int *)(this->_padding_ + 0x454);
      }
      else if (MVar2 == MENU_MORTARS) {
        local_24 = (int *)(this->_padding_ + 0x478);
      }
      else {
        if (MVar2 != MENU_SPECIALS) goto LAB_0047eb40;
        local_24 = (int *)(this->_padding_ + 0x49c);
      }
      local_c = (int *)0x9;
    }
LAB_0047eb40:
    if (0 < (int)local_c) {
      local_10 = (GameObject *)0x1;
      local_1c = (int)local_c;
      local_c = local_24;
      do {
        if ((GameObjectClass *)*local_c == (GameObjectClass *)0x0) {
          bVar5 = false;
          iVar6 = 0;
        }
        else {
          lVar7 = AdjustedScrapCost(this->_padding_,(GameObjectClass *)*local_c);
          lVar8 = AdjustedPilotCost(this->_padding_,(GameObjectClass *)*local_c);
          iVar6 = *(int *)(*local_c + 0x144);
          iVar3 = *(int *)(*local_c + 0x148);
          if ((((this->_padding_ != 2) || (bVar5 = Producer::IsBusy((Producer *)this), bVar5)) ||
              (lVar9 = Team::GetScrap((Team *)this->_padding_), lVar9 < lVar7)) ||
             ((lVar7 = Team::GetPilot((Team *)this->_padding_), lVar7 < lVar8 ||
              (((iVar6 != -1 && (iVar3 != -1)) &&
               (iVar6 = Team::FirstEmptySlot((Team *)this->_padding_,iVar6,iVar3), iVar6 == -1))))))
          {
            bVar5 = false;
          }
          else {
            bVar5 = true;
          }
          iVar6 = *local_c;
        }
        ModeList::SetMode((ModeList *)piVar1,(int)local_10,iVar6,bVar5);
        local_c = local_c + 1;
        local_10 = (GameObject *)((int)local_10 + 1);
        local_1c = local_1c + -1;
      } while (local_1c != 0);
    }
    bVar5 = Producer::IsBusy((Producer *)this);
    if (bVar5) {
      bVar5 = true;
      iVar6 = 0x17;
    }
    else {
      bVar5 = this->_padding_ == 2;
      iVar6 = 3;
    }
    goto LAB_0047ec43;
  }
  piVar1 = &this->_padding_;
  ModeList::SetMode((ModeList *)piVar1,0,1,true);
  ModeList::SetMode((ModeList *)piVar1,1,2,true);
  ModeList::SetMode((ModeList *)piVar1,2,10,true);
  ModeList::SetMode((ModeList *)piVar1,3,0xb,true);
  ModeList::SetMode((ModeList *)piVar1,4,0,false);
  ModeList::SetMode((ModeList *)piVar1,5,0,false);
  ModeList::SetMode((ModeList *)piVar1,6,0,false);
  ModeList::SetMode((ModeList *)piVar1,7,0,false);
  ModeList::SetMode((ModeList *)piVar1,8,0,false);
  ModeList::SetMode((ModeList *)piVar1,9,0,false);
  local_10 = Team::GetSlot((Team *)this->_padding_,1);
  if (local_10 == (GameObject *)0x0) {
LAB_0047ea33:
    iVar6 = Team::FirstFilledSlot((Team *)this->_padding_,0x46,0x4a);
    if (-1 < iVar6) goto LAB_0047ea46;
  }
  else {
    cVar4 = (**(code **)(local_10->_padding_ + 100))();
    if (cVar4 == '\0') {
      local_10 = (GameObject *)0x0;
    }
    if (local_10 == (GameObject *)0x0) goto LAB_0047ea33;
LAB_0047ea46:
    bVar5 = true;
  }
  iVar6 = 8;
LAB_0047ec43:
  ModeList::SetMode((ModeList *)&this->_padding_,10,iVar6,bVar5);
  return;
}
