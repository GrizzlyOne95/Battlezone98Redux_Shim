/*
 * Entry: 00485835
 * Name: ConstructionRig::UpdateModeList
 * Namespace: ConstructionRig
 * Signature: void UpdateModeList(ConstructionRig * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ConstructionRig::UpdateModeList(ConstructionRig *this)

{
  int *this_00;
  int iVar1;
  bool bVar2;
  char cVar3;
  int *piVar4;
  long lVar5;
  long lVar6;
  long lVar7;
  int iVar8;
  GameObject *pGVar9;
  int local_18;
  bool local_14;
  int *local_c;
  int local_8;
  
  this_00 = &this->_padding_;
  if (this->_padding_ != 0) {
    ModeList::SetMode((ModeList *)this_00,0,0,false);
    ModeList::SetMode((ModeList *)this_00,1,0,false);
    ModeList::SetMode((ModeList *)this_00,2,0,false);
    local_c = (int *)(this->_padding_ + 0x3d8);
    local_8 = 3;
    do {
      ModeList::SetMode((ModeList *)this_00,local_8,*local_c,false);
      local_8 = local_8 + 1;
      local_c = local_c + 1;
    } while (local_8 < 10);
    bVar2 = Producer::IsBusy((Producer *)this);
    if (bVar2) {
      bVar2 = true;
      iVar8 = 0x17;
    }
    else {
      bVar2 = this->_padding_ == 2;
      iVar8 = 3;
    }
    goto LAB_00485a10;
  }
  ModeList::SetMode((ModeList *)this_00,0,1,true);
  ModeList::SetMode((ModeList *)this_00,1,2,true);
  ModeList::SetMode((ModeList *)this_00,2,10,true);
  piVar4 = (int *)(this->_padding_ + 0x3d8);
  local_8 = 3;
  local_18 = 7;
  do {
    if ((GameObjectClass *)*piVar4 == (GameObjectClass *)0x0) {
      ModeList::SetMode((ModeList *)this_00,local_8,0,false);
    }
    else {
      lVar5 = AdjustedScrapCost(this->_padding_,(GameObjectClass *)*piVar4);
      lVar6 = AdjustedPilotCost(this->_padding_,(GameObjectClass *)*piVar4);
      iVar8 = *(int *)(*piVar4 + 0x144);
      iVar1 = *(int *)(*piVar4 + 0x148);
      bVar2 = Producer::IsBusy((Producer *)this);
      if (bVar2) {
LAB_00485923:
        local_14 = false;
      }
      else {
        lVar7 = Team::GetScrap((Team *)this->_padding_);
        if (lVar7 < lVar5) goto LAB_00485923;
        lVar5 = Team::GetPilot((Team *)this->_padding_);
        if (lVar5 < lVar6) goto LAB_00485923;
        if ((iVar8 != -1) && (iVar1 != -1)) {
          iVar8 = Team::FirstEmptySlot((Team *)this->_padding_,iVar8,iVar1);
          if (iVar8 == -1) goto LAB_00485923;
        }
        local_14 = true;
      }
      ModeList::SetMode((ModeList *)this_00,local_8,*piVar4,local_14);
    }
    piVar4 = piVar4 + 1;
    local_8 = local_8 + 1;
    local_18 = local_18 + -1;
  } while (local_18 != 0);
  pGVar9 = Team::GetSlot((Team *)this->_padding_,1);
  if (pGVar9 == (GameObject *)0x0) {
LAB_0048597b:
    iVar8 = Team::FirstFilledSlot((Team *)this->_padding_,0x46,0x4a);
    if (-1 < iVar8) goto LAB_00485992;
    bVar2 = false;
  }
  else {
    cVar3 = (**(code **)(pGVar9->_padding_ + 100))();
    if (cVar3 == '\0') {
      pGVar9 = (GameObject *)0x0;
    }
    if (pGVar9 == (GameObject *)0x0) goto LAB_0048597b;
LAB_00485992:
    bVar2 = true;
  }
  iVar8 = 8;
LAB_00485a10:
  ModeList::SetMode((ModeList *)this_00,10,iVar8,bVar2);
  return;
}
