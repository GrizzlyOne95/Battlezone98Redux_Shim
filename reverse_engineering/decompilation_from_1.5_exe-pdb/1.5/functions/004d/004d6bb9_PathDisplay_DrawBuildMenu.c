/*
 * Entry: 004d6bb9
 * Name: PathDisplay::DrawBuildMenu
 * Namespace: PathDisplay
 * Signature: void DrawBuildMenu(PathDisplay * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDisplay::DrawBuildMenu(PathDisplay *this)

{
  MenuMode MVar1;
  float fVar2;
  int iVar3;
  BuildItem *pBVar4;
  GameObject *this_00;
  AiMission *pAVar5;
  char *pcVar6;
  int iVar7;
  long lVar8;
  MAT_3D *pMVar9;
  MAT_3D *pMVar10;
  MAT_3D local_68;
  long local_28 [3];
  float local_1c;
  float local_18;
  float local_14;
  int local_10;
  long local_c;
  int local_8;
  
  MVar1 = this->menuMode;
  lVar8 = DisplayInterface::colorWhite;
  if ((MVar1 != MENU_BUILD) && (lVar8 = DisplayInterface::colorGreen, MVar1 != MENU_NONE)) {
    lVar8 = DisplayInterface::colorGrey;
  }
  pcVar6 = this->buildItem->name;
  if (this->buildItem->parent == (BuildItem *)0x0) {
    pcVar6 = "Build";
  }
  if (MVar1 == MENU_NONE) {
    iVar3 = this[1]._padding_ + 5;
  }
  else {
    iVar3 = 0;
  }
  DrawKeyItem(this,0x154,10,iVar3,pcVar6,lVar8,DisplayInterface::colorBlack);
  local_c = 0x1a;
  if (this->menuMode == MENU_BUILD) {
    local_28[0] = DisplayInterface::colorWhite;
    local_28[1] = DisplayInterface::colorGreen;
    local_28[2] = DisplayInterface::colorRed;
    if (this->buildItem->menu != (BuildItem *)0x0) {
      local_10 = 0;
      local_8 = 0;
      do {
        if (this->buildItem->menu->name[local_8] != '\0') {
          iVar7 = (local_10 + 1) % 10;
          pBVar4 = this->buildItem->menu;
          iVar3 = *(int *)(pBVar4->name + local_8 + 0x10);
          if (iVar3 < 0) {
            iVar3 = 0;
          }
          else if (3 < iVar3) {
            iVar3 = 3;
          }
          DrawKeyItem(this,0x154,local_c,this[1]._padding_ + iVar7,pBVar4->name + local_8,
                      local_28[iVar3],DisplayInterface::colorBlack);
          if (command_controls.mode_select[iVar7] != '\0') {
            pBVar4 = (BuildItem *)(this->buildItem->menu->name + local_8 + -4);
            if ((GameObjectClass *)pBVar4->menu == (GameObjectClass *)0x0) {
              if (pBVar4->item != (GameObjectClass *)0x0) {
                (**(code **)(this->_padding_ + 0x24))
                          (DisplayInterface::mousePos.x,DisplayInterface::mousePos.y,&local_1c,
                           &local_14);
                local_18 = Terrain_FindFloor((double)local_1c,(double)local_14);
                fVar2 = local_1c;
                iVar3 = this->buildTeam;
                pMVar9 = &Identity_Matrix;
                pMVar10 = &local_68;
                for (iVar7 = 0x10; iVar7 != 0; iVar7 = iVar7 + -1) {
                  pMVar10->right_x = pMVar9->right_x;
                  pMVar9 = (MAT_3D *)&pMVar9->right_y;
                  pMVar10 = (MAT_3D *)&pMVar10->right_y;
                }
                local_68.posit_x = (double)fVar2;
                local_68.posit_y = (double)local_18;
                local_68.posit_z = (double)local_14;
                if (iVar3 < 0) {
                  iVar3 = *(int *)(this->buildItem->menu->name + local_8 + 0x10);
                }
                this_00 = GameObjectClass::Build
                                    (*(GameObjectClass **)
                                      (this->buildItem->menu->name + local_8 + 0x18),&local_68,iVar3
                                     ,0,-1,(char *)0x0);
                if (this_00 != (GameObject *)0x0) {
                  pAVar5 = AiMission::GetCurrent();
                  (**(code **)(pAVar5->_padding_ + 0x18))();
                  iVar3 = Net_IsNetGame();
                  if (iVar3 != 0) {
                    DistributedObject::SetLocal((DistributedObject *)&this_00->_padding_);
                  }
                  iVar3 = GameObject::GetHandle(this_00);
                  this->taskWhoHandle = iVar3;
                }
              }
            }
            else {
              this->buildItem = pBVar4;
            }
          }
          local_c = local_c + 0xb;
        }
        local_8 = local_8 + 0x24;
        local_10 = local_10 + 1;
      } while (local_8 < 0x168);
      local_c = local_c + 5;
      if (this->buildItem->parent == (BuildItem *)0x0) {
        DrawKeyItem(this,0x154,local_c,this[1]._padding_,"Cancel",DisplayInterface::colorWhite,
                    DisplayInterface::colorBlack);
        if (command_controls.menu_back != '\0') {
          this->menuMode = MENU_NONE;
        }
      }
      else {
        DrawKeyItem(this,0x154,local_c,this[1]._padding_,"Back",DisplayInterface::colorWhite,
                    DisplayInterface::colorBlack);
        if (command_controls.menu_back != '\0') {
          this->buildItem = this->buildItem->parent;
        }
      }
    }
  }
  return;
}
