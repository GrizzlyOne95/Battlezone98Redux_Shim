/*
 * Entry: 004aaefc
 * Name: Producer::UpdateModeList
 * Namespace: Producer
 * Signature: void UpdateModeList(Producer * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall Producer::UpdateModeList(Producer *this)

{
  int *this_00;
  int iVar1;
  int iVar2;
  bool bVar3;
  char cVar4;
  bool bVar5;
  bool bVar6;
  Producer *pPVar7;
  long lVar8;
  long lVar9;
  long lVar10;
  int iVar11;
  int local_20;
  bool local_1c;
  GameObject *local_10;
  int *local_c;
  int *local_8;
  
  iVar11 = this->_padding_;
  bVar5 = false;
  if (iVar11 == 0) {
    this_00 = &this->_padding_;
    ModeList::SetMode((ModeList *)this_00,0,1,true);
    ModeList::SetMode((ModeList *)this_00,1,2,true);
    ModeList::SetMode((ModeList *)this_00,2,10,true);
    ModeList::SetMode((ModeList *)this_00,3,0xb,true);
    ModeList::SetMode((ModeList *)this_00,4,0,false);
    ModeList::SetMode((ModeList *)this_00,5,0,false);
    ModeList::SetMode((ModeList *)this_00,6,0,false);
    ModeList::SetMode((ModeList *)this_00,7,0,false);
    ModeList::SetMode((ModeList *)this_00,8,0,false);
    ModeList::SetMode((ModeList *)this_00,9,0,false);
    pPVar7 = (Producer *)Team::GetSlot((Team *)this->_padding_,1);
    if (pPVar7 == this) {
      bVar5 = false;
      iVar11 = 0;
      goto LAB_004ab188;
    }
    local_10 = Team::GetSlot((Team *)this->_padding_,1);
    if (local_10 == (GameObject *)0x0) {
LAB_004aafd3:
      iVar11 = Team::FirstFilledSlot((Team *)this->_padding_,0x46,0x4a);
      if (-1 < iVar11) goto LAB_004aafe6;
    }
    else {
      cVar4 = (**(code **)(local_10->_padding_ + 100))();
      if (cVar4 == '\0') {
        local_10 = (GameObject *)0x0;
      }
      if (local_10 == (GameObject *)0x0) goto LAB_004aafd3;
LAB_004aafe6:
      bVar5 = true;
    }
    iVar11 = 8;
    goto LAB_004ab188;
  }
  if (iVar11 == 1) {
    ModeList::SetMode((ModeList *)&this->_padding_,0,0,false);
    iVar2 = this->_padding_;
    iVar11 = 0;
    do {
      local_8 = &this->_padding_;
      iVar1 = iVar11 * 4;
      iVar11 = iVar11 + 1;
      ModeList::SetMode((ModeList *)local_8,iVar11,*(int *)(iVar2 + 0x3d8 + iVar1),false);
    } while (iVar11 < 9);
LAB_004ab182:
    bVar3 = false;
  }
  else {
    if (iVar11 != 2) {
      if (iVar11 != 3) {
        return;
      }
      ModeList::SetMode((ModeList *)&this->_padding_,0,0,false);
      iVar2 = this->_padding_;
      iVar11 = 0;
      do {
        local_8 = &this->_padding_;
        iVar1 = iVar11 * 4;
        iVar11 = iVar11 + 1;
        ModeList::SetMode((ModeList *)local_8,iVar11,*(int *)(iVar2 + 0x3d8 + iVar1),false);
      } while (iVar11 < 9);
      goto LAB_004ab182;
    }
    ModeList::SetMode((ModeList *)&this->_padding_,0,0,false);
    local_c = (int *)(this->_padding_ + 0x3d8);
    local_10 = (GameObject *)0x1;
    local_20 = 9;
    do {
      local_8 = &this->_padding_;
      if ((GameObjectClass *)*local_c == (GameObjectClass *)0x0) {
        ModeList::SetMode((ModeList *)local_8,(int)local_10,0,false);
      }
      else {
        lVar8 = AdjustedScrapCost(this->_padding_,(GameObjectClass *)*local_c);
        lVar9 = AdjustedPilotCost(this->_padding_,(GameObjectClass *)*local_c);
        iVar11 = *(int *)(*local_c + 0x144);
        iVar2 = *(int *)(*local_c + 0x148);
        bVar5 = IsBusy(this);
        if ((((bVar5) || (lVar10 = Team::GetScrap((Team *)this->_padding_), lVar10 < lVar8)) ||
            (lVar8 = Team::GetPilot((Team *)this->_padding_), lVar8 < lVar9)) ||
           (((iVar11 != -1 && (iVar2 != -1)) &&
            (iVar11 = Team::FirstEmptySlot((Team *)this->_padding_,iVar11,iVar2), iVar11 == -1)))) {
          local_1c = false;
        }
        else {
          local_1c = true;
        }
        ModeList::SetMode((ModeList *)local_8,(int)local_10,*local_c,local_1c);
      }
      local_c = local_c + 1;
      local_10 = (GameObject *)((int)local_10 + 1);
      local_20 = local_20 + -1;
    } while (local_20 != 0);
    bVar6 = IsBusy(this);
    bVar5 = true;
    bVar3 = true;
    if (bVar6) {
      iVar11 = 0x17;
      goto LAB_004ab188;
    }
  }
  bVar5 = bVar3;
  iVar11 = 3;
LAB_004ab188:
  ModeList::SetMode((ModeList *)&this->_padding_,10,iVar11,bVar5);
  return;
}
