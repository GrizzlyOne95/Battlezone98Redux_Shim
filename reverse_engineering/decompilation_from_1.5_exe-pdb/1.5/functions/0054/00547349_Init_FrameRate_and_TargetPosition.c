/*
 * Entry: 00547349
 * Name: Init_FrameRate_and_TargetPosition
 * Namespace: Global
 * Signature: void Init_FrameRate_and_TargetPosition(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_FrameRate_and_TargetPosition(void)

{
  Mono_Handle = Mono_Register(Clear_Mono_Target_Position);
  Time0 = Get_Time();
  Frames = 0.0;
  sprintf(Speed,"FPS 0.0");
  sprintf(lp_Poly,"Polygons 0.0");
  sprintf(lp_Sub_Poly,"");
  Font_Set_Foreground(Default_Font,2);
  return;
}
