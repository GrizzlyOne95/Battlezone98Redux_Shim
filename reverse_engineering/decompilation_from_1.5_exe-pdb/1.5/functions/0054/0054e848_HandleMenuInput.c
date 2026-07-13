/*
 * Entry: 0054e848
 * Name: HandleMenuInput
 * Namespace: Global
 * Signature: void HandleMenuInput(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl HandleMenuInput(void)

{
  _menu_item *p_Var1;
  short sVar2;
  _menu *p_Var3;
  long lVar4;
  _menu_item *p_Var5;
  MENU_CMD MVar6;
  _func___cdecl_long__menu_item_ptr_MENU_CMD *local_8;
  int local_4;
  
  p_Var3 = mInfo.curMenu;
  sVar2 = user_controls.key;
  local_8 = (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0;
  local_4 = 0;
  if (mInfo.buttonPending != 0) {
    return;
  }
  if (user_controls.key == 0) {
    return;
  }
  if ((((user_controls.key != 9) && (user_controls.key != 0xd)) && (user_controls.key != 0x1b)) &&
     (user_controls.key != 0x20)) {
    if (user_controls.key < 0xc6) {
      return;
    }
    if ((0xc9 < user_controls.key) && (user_controls.key != 0x209)) {
      return;
    }
  }
  if (user_controls.key == 0) {
    return;
  }
  user_controls.key = 0;
  menu_controls.item_reset = '\x01';
  menu_controls.value_reset = '\x01';
  MVar6 = MC_INC_ITEM;
  if (sVar2 < 199) {
    if (sVar2 == 0xc6) {
LAB_0054e951:
      MVar6 = MC_DEC_ITEM;
    }
    else if (sVar2 != 9) {
      if (sVar2 == 0xd) {
        MVar6 = MC_ENTER;
      }
      else {
        MVar6 = MC_REJECT;
        if (sVar2 != 0x1b) {
          if (sVar2 != 0x20) goto LAB_0054e94c;
          goto LAB_0054e8e7;
        }
      }
    }
  }
  else if (sVar2 != 199) {
    if (sVar2 == 200) {
LAB_0054e8e7:
      MVar6 = MC_INC_VALUE;
    }
    else if (sVar2 == 0xc9) {
      MVar6 = MC_DEC_VALUE;
    }
    else {
      if (sVar2 == 0x209) goto LAB_0054e951;
LAB_0054e94c:
      MVar6 = MC_NONE;
    }
  }
  p_Var1 = (mInfo.curMenu)->items;
  p_Var5 = p_Var1 + (mInfo.curMenu)->curItem;
  if ((int)MVar6 < 0) {
    user_controls.key = 0;
    menu_controls.item_reset = '\x01';
    menu_controls.value_reset = '\x01';
    return;
  }
  if ((int)MVar6 < 2) {
    do {
      lVar4 = ChangeMenuItem(p_Var3->curItem,p_Var3->numItems,MVar6,p_Var5->flags & 0xffffefff);
      p_Var3->curItem = lVar4;
    } while (p_Var1[lVar4].handlerFunc == (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0);
  }
  else {
    if (3 < (int)MVar6) {
      if (MVar6 == MC_ENTER) {
        if (((p_Var5->flags & 0x200U) == 0) && ((p_Var5->flags & 4U) == 0)) {
          local_8 = mh_Yes;
        }
        else {
          local_8 = p_Var5->handlerFunc;
        }
      }
      else {
        if (MVar6 != MC_REJECT) {
          user_controls.key = 0;
          menu_controls.item_reset = '\x01';
          menu_controls.value_reset = '\x01';
          return;
        }
        local_8 = mh_No;
      }
      goto LAB_0054e9d8;
    }
    local_8 = p_Var5->handlerFunc;
    if ((p_Var5->flags & 0x800U) == 0) {
      lVar4 = ChangeMenuItem(p_Var5->curChoice,p_Var5->numChoices,MVar6,p_Var5->flags);
      p_Var5->curChoice = lVar4;
    }
    else {
      (*local_8)(p_Var5,MVar6);
    }
    MVar6 = MC_UPDATE;
  }
  local_4 = 1;
LAB_0054e9d8:
  if (local_8 != (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0) {
    local_4 = (*local_8)(p_Var5,MVar6);
  }
  if (local_4 == 0) {
    return;
  }
  DrawMenuContents();
  return;
}
