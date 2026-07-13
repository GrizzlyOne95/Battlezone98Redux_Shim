/*
 * Entry: 0054e3ba
 * Name: OpenMenu
 * Namespace: Global
 * Signature: int OpenMenu(_menu * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl OpenMenu(_menu *param_1)

{
  char cVar1;
  char *pcVar2;
  _GRAPHIC_BUFFER *p_Var3;
  int iVar4;
  _menu_item *p_Var5;
  _GRAPHIC_BUFFER *p_Var6;
  _GRAPHIC_BUFFER local_3c;
  int local_8;
  
  local_8 = (Device.Viewport.Pane.x1 - Device.Viewport.Pane.x0) + 1;
  if (param_1 == (_menu *)0x0) {
    if (mInfo.exitFunc != (_func___cdecl_void *)0x0) {
      (*mInfo.exitFunc)();
    }
  }
  else {
    CloseMenu(mInfo.curMenu);
    pcVar2 = param_1->backgroundName;
    mInfo.curMenu = param_1;
    iVar4 = 0xc906e4 - (int)pcVar2;
    do {
      cVar1 = *pcVar2;
      pcVar2[iVar4] = cVar1;
      pcVar2 = pcVar2 + 1;
    } while (cVar1 != '\0');
    mInfo.background = UseRDItem(mInfo.backgroundName,0,0);
    if (mInfo.background == (TEXTURE *)0x0) {
      DEBUG_systemWarning("Menu error - can\'t find %s");
    }
    else {
      p_Var3 = Graphic_Buffer_Init_Ex
                         (&local_3c,(int)(mInfo.background)->width,(mInfo.background)->height,
                          (char *)(mInfo.background + 1),BYTES_FORMAT);
      p_Var6 = &mInfo.bgGB;
      for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
        p_Var6->Width = p_Var3->Width;
        p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
        p_Var6 = (_GRAPHIC_BUFFER *)&p_Var6->Height;
      }
      if (mInfo.bgGB.Buffer == (uchar *)0x0) {
        pcVar2 = "Can\'t create graphic buffer for Menu";
      }
      else {
        (param_1->menuRect).top = 0;
        (param_1->menuRect).left = 0;
        (param_1->menuRect).right = (int)(mInfo.background)->width + 3U & 0xfffffffc;
        (param_1->menuRect).bottom = (mInfo.background)->height;
        mInfo.menuLoc.top = (Device.Viewport.Height - (mInfo.background)->height) / 2;
        mInfo.menuLoc.left = (local_8 - (mInfo.background)->width) / 2;
        mInfo.menuLoc.right = (param_1->menuRect).right + mInfo.menuLoc.left;
        mInfo.menuLoc.bottom = (param_1->menuRect).bottom + mInfo.menuLoc.top;
        p_Var3 = CreateTextBitmap(&local_3c,mInfo.dc,(param_1->menuRect).right,
                                  (param_1->menuRect).bottom,&mInfo.hBitmap);
        p_Var6 = &mInfo.textGB;
        for (iVar4 = 0xd; iVar4 != 0; iVar4 = iVar4 + -1) {
          p_Var6->Width = p_Var3->Width;
          p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
          p_Var6 = (_GRAPHIC_BUFFER *)&p_Var6->Height;
        }
        iVar4 = 0;
        if (mInfo.hBitmap != (HBITMAP__ *)0x0) {
          p_Var5 = param_1->items;
          if (0 < param_1->numItems) {
            do {
              if (p_Var5->handlerFunc != (_func___cdecl_long__menu_item_ptr_MENU_CMD *)0x0) {
                (*p_Var5->handlerFunc)(p_Var5,MC_INIT);
              }
              iVar4 = iVar4 + 1;
              p_Var5 = p_Var5 + 1;
            } while (iVar4 < param_1->numItems);
          }
          DrawMenuContents();
          mInfo.buttonPending = 0;
          return 1;
        }
        pcVar2 = "Can\'t create menu bitmap";
      }
      DEBUG_systemWarning(pcVar2);
    }
  }
  return 0;
}
