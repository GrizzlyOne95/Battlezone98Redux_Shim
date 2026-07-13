/*
 * Entry: 0054f3ea
 * Name: ToggleMap
 * Namespace: Global
 * Signature: void ToggleMap(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl ToggleMap(void)

{
  _gas_object *p_Var1;
  _GRAPHIC_BUFFER *p_Var2;
  int iVar3;
  _GRAPHIC_BUFFER *p_Var4;
  char *pcVar5;
  _GRAPHIC_BUFFER local_34;
  
  if (ScreenMode == SCREENMODE_MAP) {
    p_Var1 = FindGASObject("cmap2.wav",(_OBJ76 *)0x0);
    StopGASEvent(p_Var1);
    p_Var1 = FindGASObject("gdsgc26.wav",(_OBJ76 *)0x0);
    StopGASEvent(p_Var1);
    FreeMap();
    UnPauseGAS();
    SetScreenMode(SCREENMODE_SIM);
    EnableForceFeedback();
    return;
  }
  if (mapName[0] == '\0') {
    DEBUG_systemWarning("No map specified for this mission");
  }
  else {
    mapTexture = UseRDItem(mapName,1,4);
    if (mapTexture != (TEXTURE *)0x0) {
      p_Var2 = Graphic_Buffer_Init_Ex
                         (&local_34,(int)mapTexture->width,mapTexture->height,
                          (char *)(mapTexture + 1),BYTES_FORMAT);
      p_Var4 = &mapTextureGB;
      for (iVar3 = 0xd; iVar3 != 0; iVar3 = iVar3 + -1) {
        p_Var4->Width = p_Var2->Width;
        p_Var2 = (_GRAPHIC_BUFFER *)&p_Var2->Height;
        p_Var4 = (_GRAPHIC_BUFFER *)&p_Var4->Height;
      }
      if (mapTextureGB.Buffer == (uchar *)0x0) {
        pcVar5 = "Can\'t create graphic buffer for Map!";
      }
      else {
        iVar3 = RDBlit(&mapTextureGB);
        if (iVar3 != 0) {
          DisableForceFeedback();
          PauseGAS();
          StartGASEvent("cmap2.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
          StartGASEvent("gdsgc26.wav",(_OBJ76 *)0x0,(GAS_CTRL *)0x0,(GAS_PREP_INFO *)0x0);
          SetScreenMode(SCREENMODE_MAP);
          return;
        }
        pcVar5 = "Can\'t lock the buffer to draw Map";
      }
      DEBUG_systemWarning(pcVar5);
      FreeMap();
      return;
    }
  }
  return;
}
