/*
 * Entry: 0054e644
 * Name: InitMenu
 * Namespace: Global
 * Signature: int InitMenu(_menu * param_1, _func___cdecl_void * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl InitMenu(_menu *param_1,_func___cdecl_void *param_2)

{
  int iVar1;
  HDC hdc;
  _GRAPHIC_BUFFER *p_Var2;
  _GRAPHIC_BUFFER *p_Var3;
  char *pcVar4;
  _GRAPHIC_BUFFER local_38;
  
  UnlockMouse();
  if (MenuInited == 0) {
    FixRects(menuItemLocs6[0],0x66);
    FixRects(menuItemLocs3[0],0x66);
    MenuInited = 1;
  }
  if (levelNum != levelChosen) {
    iVar1 = rand();
    levelNum = levelChosen;
    mInfo.checkNumBase = iVar1 % 0x3e0 + (levelChosen + 900) * 1000;
  }
  hdc = (*Device.VideoMode.GetVideoDC)(&Device);
  mInfo.dc = (HDC__ *)CreateCompatibleDC(hdc);
  if ((((((mInfo.dc == (HDC__ *)0x0) &&
         ((*Device.VideoMode.writePaletteEntries)(&Device,0,0x100,Device.Palette,(char *)0x0),
         mInfo.dc == (HDC__ *)0x0)) ||
        (mInfo.titleFont = OpenRDFont(&titleFont), mInfo.titleFont == (HFONT__ *)0x0)) ||
       ((mInfo.yesNoFont = OpenRDFont(&yesNoFont), mInfo.yesNoFont == (HFONT__ *)0x0 ||
        (mInfo.itemFont = OpenRDFont(&itemFont), mInfo.itemFont == (HFONT__ *)0x0)))) ||
      ((mInfo.itemFontSmall = OpenRDFont(&itemFontSmall), mInfo.itemFontSmall == (HFONT__ *)0x0 ||
       ((mInfo.checkboxFont = OpenRDFont(&checkboxFont), mInfo.checkboxFont == (HFONT__ *)0x0 ||
        (mInfo.sliderFont = OpenRDFont(&sliderFont), mInfo.sliderFont == (HFONT__ *)0x0)))))) ||
     ((mInfo.checkNumFont = OpenRDFont(&checkNumFont), mInfo.checkNumFont == (HFONT__ *)0x0 ||
      (mInfo.checkmark = UseRDItem("x1.map",0,0), mInfo.checkmark == (TEXTURE *)0x0)))) {
    pcVar4 = "Menu error - can\'t open a font or create the dc";
  }
  else {
    p_Var2 = Graphic_Buffer_Init_Ex
                       (&local_38,(int)(mInfo.checkmark)->width,(mInfo.checkmark)->height,
                        (char *)(mInfo.checkmark + 1),BYTES_FORMAT);
    p_Var3 = &mInfo.cmGB;
    for (iVar1 = 0xd; iVar1 != 0; iVar1 = iVar1 + -1) {
      p_Var3->Width = p_Var2->Width;
      p_Var2 = (_GRAPHIC_BUFFER *)&p_Var2->Height;
      p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
    }
    if (mInfo.cmGB.Buffer == (uchar *)0x0) {
      pcVar4 = "Can\'t create graphic buffer for Menu checkbox";
    }
    else {
      menuItemLocs = menuItemLocs3;
      if ((UserProfilePtr->graphicDetail).resolution < 6) {
        menuItemLocs = menuItemLocs6;
      }
      iVar1 = OpenMenu(param_1);
      if (iVar1 != 0) {
        DisableForceFeedback();
        mInfo.exitFunc = param_2;
        return 1;
      }
      pcVar4 = "Can\'t open Menu";
    }
  }
  DEBUG_systemWarning(pcVar4);
  ClearMenu();
  return 0;
}
