/*
 * Entry: 004ec143
 * Name: InitNotepad
 * Namespace: Global
 * Signature: int InitNotepad(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl InitNotepad(void)

{
  HDC hdc;
  _GRAPHIC_BUFFER *p_Var1;
  int iVar2;
  _GRAPHIC_BUFFER *p_Var3;
  NOTEPAD_DATA *pNVar4;
  char *pcVar5;
  _GRAPHIC_BUFFER local_38;
  
  if (od.NumObjs < 1) {
    DEBUG_systemWarning("No objectives found at load time.");
  }
  memset(&np,0,0xa4);
  builtin_strncpy(np.TextureName,"zhpd.map",9);
  hdc = (*Device.VideoMode.GetVideoDC)(&Device);
  np.DC = (HDC__ *)CreateCompatibleDC(hdc);
  if (np.DC == (HDC__ *)0x0) {
    pcVar5 = "Can\'t create Notepad device context";
  }
  else {
    np.Font = OpenRDFont(&npFont);
    if (np.Font == (HFONT__ *)0x0) {
      pcVar5 = "Can\'t create Notepad font";
    }
    else {
      np.TextBox.top = 0;
      np.TextBox.left = 0;
      if ((UserProfilePtr->graphicDetail).resolution < 6) {
        np.TextBox.right = 0x1c0;
        np.TextBox.bottom = 0x13d;
      }
      else {
        np.TextBox.right = 0xe4;
        np.TextBox.bottom = 199;
      }
      p_Var1 = CreateTextBitmap(&local_38,np.DC,np.TextBox.right,np.TextBox.bottom,&np.TextBitmap);
      p_Var3 = &np.TextGB;
      for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
        p_Var3->Width = p_Var1->Width;
        p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
        p_Var3 = (_GRAPHIC_BUFFER *)&p_Var3->Height;
      }
      if (np.TextBitmap == (HBITMAP__ *)0x0) {
        pcVar5 = "Can\'t create bitmap for Notepad text";
      }
      else {
        np.Texture = UseRDItem(np.TextureName,0,4);
        if (np.Texture == (TEXTURE *)0x0) {
          DEBUG_systemWarning("Can\'t find Notepad texture map %s");
          goto LAB_004ec1a8;
        }
        p_Var1 = Graphic_Buffer_Init_Ex
                           (&local_38,(int)(np.Texture)->width,(np.Texture)->height,
                            (char *)(np.Texture + 1),BYTES_FORMAT);
        pNVar4 = &np;
        for (iVar2 = 0xd; pNVar4 = (NOTEPAD_DATA *)&pNVar4->TextureGB, iVar2 != 0;
            iVar2 = iVar2 + -1) {
          ((_GRAPHIC_BUFFER *)pNVar4)->Width = p_Var1->Width;
          p_Var1 = (_GRAPHIC_BUFFER *)&p_Var1->Height;
        }
        if (np.TextureGB.Buffer == (uchar *)0x0) {
          pcVar5 = "Can\'t create graphic buffer for Notepad";
        }
        else {
          if ((UserProfilePtr->graphicDetail).resolution < 6) {
            np.Top = 0x66;
            np.Left = 0x52;
          }
          else {
            np.Top = 0x29;
            np.Left = 0x28;
          }
          DrawNotepadContents();
          Graphic_Copy_Bitmap(&np.TextureGB,&np.TextGB,np.Left,np.Top,TRANSPARENT_PIXELS);
          iVar2 = RDBlit(&np.TextureGB);
          if (iVar2 != 0) {
            return 1;
          }
          pcVar5 = "Can\'t lock the buffer to draw Notepad";
        }
      }
    }
  }
  DEBUG_systemWarning(pcVar5);
LAB_004ec1a8:
  DeleteNotepad();
  return 0;
}
