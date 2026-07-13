/*
 * Entry: 0054e13c
 * Name: ProcessMouseInMenu
 * Namespace: Global
 * Signature: void ProcessMouseInMenu(uint param_1, uint param_2, long param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ProcessMouseInMenu(uint param_1,uint param_2,long param_3)

{
  uint uVar1;
  _menu *p_Var2;
  int extraout_EAX;
  int extraout_EAX_00;
  int iVar3;
  int iVar4;
  long lVar5;
  uint uVar6;
  int iVar7;
  _menu_item *p_Var8;
  MENU_CMD MVar9;
  tagRECT local_24;
  long local_14;
  int local_10;
  int local_c;
  int local_8;
  
  p_Var2 = mInfo.curMenu;
  local_8 = 0;
  _ftol2_sse();
  local_c = extraout_EAX;
  _ftol2_sse();
  iVar3 = IsWithinRect(&mInfo.menuLoc,local_c,extraout_EAX_00);
  if (iVar3 != 0) {
    local_c = local_c - mInfo.menuLoc.left;
    local_14 = extraout_EAX_00 - mInfo.menuLoc.top;
    local_10 = 0;
    p_Var8 = p_Var2->items;
    if (0 < p_Var2->numItems) {
      do {
        param_3 = -1;
        if (p_Var8->handlerFunc != (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0) {
          iVar3 = IsWithinRect(&p_Var8->itemRect,local_c,local_14);
          if ((iVar3 != 0) ||
             (iVar3 = IsWithinRect(&p_Var8->choiceRect,local_c,local_14), iVar3 != 0)) {
            local_8 = 1;
            break;
          }
          if ((p_Var8->flags & 0x80) != 0) {
            iVar3 = (p_Var8->itemRect).left;
            local_24.top = (p_Var8->itemRect).top;
            if ((UserProfilePtr->graphicDetail).resolution < 6) {
              iVar7 = 0x11;
              iVar3 = iVar3 + 5;
              local_24.top = local_24.top + 0x1c;
            }
            else {
              iVar7 = 7;
              iVar3 = iVar3 + 1;
              local_24.top = local_24.top + 10;
            }
            param_3 = 0;
            local_24.right = iVar7 + iVar3;
            local_24.bottom = iVar7 + local_24.top;
            local_24.left = iVar3;
            if (0 < p_Var8->numChoices) {
              do {
                local_24.left = iVar3;
                iVar4 = IsWithinRect(&local_24,local_c,local_14);
                if (iVar4 != 0) {
                  local_8 = 1;
                  break;
                }
                param_3 = param_3 + 1;
                local_24.right = local_24.right + iVar7;
                iVar3 = iVar3 + iVar7;
                local_24.left = iVar3;
              } while (param_3 < p_Var8->numChoices);
            }
            if (local_8 != 0) goto LAB_0054e2c6;
          }
        }
        local_10 = local_10 + 1;
        p_Var8 = p_Var8 + 1;
      } while (local_10 < (mInfo.curMenu)->numItems);
      if (local_8 != 0) {
LAB_0054e2c6:
        if (param_1 == 0x201) {
          (mInfo.curMenu)->curItem = local_10;
          if (((p_Var8->flags & 0x80) != 0) && (param_3 != -1)) {
            p_Var8->curChoice = param_3 + 1;
          }
          DrawMenuContents();
          mInfo.buttonPending = 1;
          return;
        }
        if (param_1 != 0x202) {
          return;
        }
        if ((mInfo.buttonPending != 0) && (local_10 == (mInfo.curMenu)->curItem)) {
          uVar1 = p_Var8->flags;
          if (((uVar1 & 0x80) != 0) && ((param_3 != -1 && (param_3 + 1 != p_Var8->curChoice)))) {
            local_8 = 0;
          }
          if (local_8 != 0) {
            if (((uVar1 & 0x200) == 0) && ((uVar1 & 6) == 0)) {
              if ((uVar1 & 0x800) == 0) {
                if (((uVar1 & 0x80) == 0) || (param_3 == -1)) {
                  if (p_Var8->numChoices == 1) {
                    uVar6 = 0;
                  }
                  else {
                    uVar6 = p_Var8->curChoice + 1;
                    if ((p_Var8->numChoices <= (int)uVar6) &&
                       (uVar6 = p_Var8->curChoice, (uVar1 & 0x180) == 0)) {
                      uVar6 = uVar1 >> 0xc & 1;
                    }
                  }
                  p_Var8->curChoice = uVar6;
                }
              }
              else {
                (*p_Var8->handlerFunc)(p_Var8,MC_INC_VALUE);
              }
              MVar9 = MC_UPDATE;
            }
            else {
              MVar9 = MC_ENTER;
            }
            lVar5 = (*p_Var8->handlerFunc)(p_Var8,MVar9);
            if (lVar5 != 0) {
              DrawMenuContents();
            }
          }
        }
        mInfo.buttonPending = 0;
        return;
      }
    }
    mInfo.buttonPending = 0;
  }
  return;
}
