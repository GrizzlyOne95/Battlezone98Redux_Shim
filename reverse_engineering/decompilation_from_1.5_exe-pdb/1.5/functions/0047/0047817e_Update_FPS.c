/*
 * Entry: 0047817e
 * Name: Update_FPS
 * Namespace: Global
 * Signature: void Update_FPS(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Update_FPS(void)

{
  float fVar1;
  DWORD DVar2;
  uint extraout_EAX;
  long lVar3;
  int iVar4;
  float10 extraout_ST0;
  
  fVar1 = spriteZ;
  DVar2 = timeGetTime();
  frameFPS = frameFPS + 1;
  if (timeFPS + 1000 < DVar2) {
    _ftol2();
    frameFPS = 0;
    TriCounter = 0;
    if (trackFPS == 0) {
      timeFPS = DVar2;
      frameFPS = 0;
      TriCounter = 0;
      avgFrameTime = extraout_EAX;
      return;
    }
    timeFPS = DVar2;
    avgFrameTime = extraout_EAX;
    if (useD3D == 0) {
      sprintf(strFPS,"%4.1f",(double)extraout_ST0);
    }
    else {
      sprintf(strFPS,"%4.1f-%c%c%c%c%c%c%d(%d)",(double)extraout_ST0,
              ~(D3IniFlags << 4) & 0x20U | 0x41,~((uint)D3IniFlags >> 9) & 0x20 | 0x4d,
              ~(D3IniFlags << 5) & 0x20U | 0x5a,~((uint)D3IniFlags >> 3) & 0x20 | 0x54,
              ~D3IniFlags & 0x20U | 0x48,(-(uint)(D3RadarType != 1) & 0x20) + 0x46,
              (uint)((D3IniFlags & 8U) != 0) * 8 + 8);
    }
    lVar3 = Font_Get_String_Length(Default_Font,strFPS);
    lenFPS = lVar3 + 4;
  }
  if (trackFPS != 0) {
    iVar4 = ((View_Record.MainCam.Buffer)->Pane).x1 - lenFPS;
    Font_Set_Foreground(Default_Font,fgFPS);
    spriteZ = fVar1 + 0.1;
    Clipped_Rect_Filled(View_Record.MainCam.Buffer,iVar4,0,
                        ((View_Record.MainCam.Buffer)->Pane).x1 + -1,dyFPS + 4,bgFPS,SOLID_PIXELS);
    spriteZ = fVar1;
    Font_Print_String(Default_Font,View_Record.MainCam.Buffer,iVar4 + 2,2,strFPS);
  }
  return;
}
