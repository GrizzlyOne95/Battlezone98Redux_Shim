/*
 * Entry: 00477fb2
 * Name: Render_Pause_Message
 * Namespace: Global
 * Signature: void Render_Pause_Message(CAMERA * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Render_Pause_Message(CAMERA *param_1)

{
  float fVar1;
  int iVar2;
  DWORD DVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = GetSpriteIndex("<<< PAUSED >>>");
  iVar5 = (Device.Viewport.Pane.x0 + Device.Viewport.Pane.x1) / 2;
  iVar6 = (Device.Viewport.Pane.y0 + Device.Viewport.Pane.y1) / 2;
  DVar3 = timeGetTime();
  fVar1 = spriteZ;
  uVar4 = DVar3 & 0x7ff;
  if (useD3D == 0) {
    (*Device.VideoMode.LockBuffer)(&Device);
  }
  else {
    Begin_D3D_Scene(param_1);
  }
  spriteZ = fVar1 + 0.1;
  Clipped_Rect_Filled(&Device.Viewport,iVar5 + -100,iVar6 + -8,iVar5 + 100,iVar6 + 8,0,SOLID_PIXELS)
  ;
  if (uVar4 < 0x500) {
    if (uVar4 < 0x280) {
      Foreground_Color = (uVar4 >> 5) + 1;
    }
    else {
      Foreground_Color = (0x500 - uVar4 >> 5) + 1;
    }
  }
  else {
    Foreground_Color = 0;
  }
  spriteZ = fVar1;
  DrawSprite(&Device.Viewport,iVar2,iVar5,iVar6,0x50005);
  if (useD3D == 0) {
    (*Device.VideoMode.UnlockBuffer)(&Device);
  }
  else {
    End_D3D_Scene();
  }
  (*Device.Refresh.Blit)(&Device);
  return;
}
