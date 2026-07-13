/*
 * Entry: 004c415a
 * Name: ControlPanel::PostLoad
 * Namespace: ControlPanel
 * Signature: void PostLoad(ControlPanel * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall ControlPanel::PostLoad(ControlPanel *this)

{
  int iVar1;
  long *plVar2;
  int iVar3;
  Team *this_00;
  GameObject *pGVar4;
  int *piVar5;
  int (*paiVar6) [90];
  undefined4 unaff_EDI;
  BuildItem *pBVar7;
  BuildItem *pBVar8;
  undefined4 uVar9;
  int local_c;
  int (*local_8) [90];
  int local_4;
  
  iVar3 = D3IniFlags;
  if (TerrainEdit != 0) {
    D3IniFlags = D3IniFlags & 0xffff7fff;
    iVar1 = ItemExists("build.odf");
    if (iVar1 == 0) {
      uVar9 = 10;
      buildMenu.menu = calloc(10,0x24);
      pBVar8 = buildMenu.menu;
      InitBuildItem(buildMenu.menu,CONCAT44(uVar9,0x74626d63));
      pBVar7 = buildMenu.menu + 1;
      InitBuildItem(pBVar7,CONCAT44(pBVar8,0x646f7270));
      pBVar8 = buildMenu.menu + 2;
      InitBuildItem(pBVar8,CONCAT44(pBVar7,0x67646c62));
      pBVar7 = buildMenu.menu + 3;
      InitBuildItem(pBVar7,CONCAT44(pBVar8,0x6e676973));
      InitBuildItem(buildMenu.menu + 4,CONCAT44(pBVar7,0x74626d63));
      pBVar8 = buildMenu.menu + 5;
      InitBuildItem(pBVar8,CONCAT44(unaff_EDI,0x646f7270));
      pBVar7 = buildMenu.menu + 6;
      InitBuildItem(pBVar7,CONCAT44(pBVar8,0x67646c62));
      pBVar8 = buildMenu.menu + 7;
      InitBuildItem(pBVar8,CONCAT44(pBVar7,0x6e676973));
      InitBuildItem(buildMenu.menu + 8,CONCAT44(pBVar8,0x67646c62));
    }
    else {
      InitBuildItem(&buildMenu,CONCAT44(unaff_EDI,100));
    }
  }
  iVar1 = 10;
  plVar2 = &this->modeButton[0].color;
  D3IniFlags = iVar3;
  do {
    (((ModeButton *)(plVar2 + -1))->field0_0x0).type = 0;
    plVar2[1] = 0x3f800000;
    *plVar2 = 0;
    iVar1 = iVar1 + -1;
    plVar2[2] = -0xeb60d36;
    plVar2[3] = 0;
    plVar2[4] = -0xeb60d36;
    plVar2 = plVar2 + 6;
  } while (iVar1 != 0);
  this->menuItem = -1;
  this->currentItem = -1;
  (this->cmdButton).command = NUM_CMD;
  (this->altButton).command = NUM_CMD;
  local_8 = this->groupList;
  (this->cmdButton).object = (GameObject *)0x0;
  (this->cmdButton).pos = (VECTOR_3D *)0x0;
  (this->cmdButton).color = 0;
  (this->altButton).object = (GameObject *)0x0;
  (this->altButton).pos = (VECTOR_3D *)0x0;
  (this->altButton).color = 0;
  this->satelliteEnabled = 0;
  this->menuPos = 0;
  this->menuState = 0;
  this->buildItem = &buildMenu;
  this->editMode = 0;
  this->itemEnabled = 0;
  this->itemSelected = 0;
  this->itemAttacked = 0;
  this->itemDisplayed = 0xf;
  plVar2 = this->groupNum;
  local_4 = 10;
  do {
    local_c = 0;
    paiVar6 = local_8;
    if (0 < *plVar2) {
      do {
        iVar3 = ConvertHandle((*paiVar6)[0]);
        local_c = local_c + 1;
        (*paiVar6)[0] = iVar3;
        paiVar6 = (int (*) [90])(*paiVar6 + 1);
      } while (local_c < *plVar2);
    }
    local_8 = local_8 + 1;
    plVar2 = plVar2 + 1;
    local_4 = local_4 + -1;
  } while (local_4 != 0);
  this->currentMode = 0;
  this->menuMode = MENU_TYPE_PANEL;
  this_00 = GameObject::userTeamList;
  if (GameObject::userTeamList == (Team *)0x0) {
    this_00 = Team::GetTeam(1);
  }
  pGVar4 = Team::GetSlot(this_00,1);
  if (pGVar4 != (GameObject *)0x0) {
    this->itemDisplayed = this->itemDisplayed | 0x10;
    iVar3 = (**(code **)pGVar4->_padding_)();
    piVar5 = (int *)(iVar3 + 0x3d8);
    iVar3 = 9;
    do {
      if (*piVar5 != 0) {
        iVar1 = *(int *)(*piVar5 + 0x20);
        if (iVar1 == 0x41524d52) {
          this->itemDisplayed = this->itemDisplayed | 0x40;
        }
        else if (iVar1 == 0x434e5354) {
          this->itemDisplayed = this->itemDisplayed | 0x180;
        }
        else if (iVar1 == 0x46414354) {
          this->itemDisplayed = this->itemDisplayed | 0x20;
        }
      }
      piVar5 = piVar5 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  pGVar4 = Team::GetSlot(this_00,2);
  if (pGVar4 != (GameObject *)0x0) {
    this->itemDisplayed = this->itemDisplayed | 0x20;
  }
  pGVar4 = Team::GetSlot(this_00,3);
  if (pGVar4 != (GameObject *)0x0) {
    this->itemDisplayed = this->itemDisplayed | 0x40;
  }
  pGVar4 = Team::GetSlot(this_00,4);
  if (pGVar4 != (GameObject *)0x0) {
    this->itemDisplayed = this->itemDisplayed | 0x180;
  }
  return;
}
