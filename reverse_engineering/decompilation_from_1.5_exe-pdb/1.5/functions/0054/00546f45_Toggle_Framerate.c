/*
 * Entry: 00546f45
 * Name: Toggle_Framerate
 * Namespace: Global
 * Signature: void Toggle_Framerate(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Toggle_Framerate(void)

{
  HighestFrame = 0.0;
  JustToggledOn = 1;
  LowestFrame = 100.0;
  FrameAmount = 0.0;
  TotalFrameRate = 0.0;
  Frame_Rate_On = (uint)(Frame_Rate_On == 0);
  return;
}
