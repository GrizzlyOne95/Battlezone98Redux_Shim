/*
 * Entry: 004780cd
 * Name: Init_FPS
 * Namespace: Global
 * Signature: void Init_FPS(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Init_FPS(void)

{
  bgFPS = Get_Closest_RGB_Entry(0.0,0.0,0.0);
  fgFPS = Get_Closest_RGB_Entry(1.0,1.0,1.0);
  dyFPS = Default_Font->char_height;
  frameFPS = 0;
  lenFPS = 0;
  TriCounter = 0;
  timeFPS = timeGetTime();
  trackFPS = GetPrivateProfileIntA("Debug","TrackFPS",trackFPS,&cfgFileName);
  avgFrameTime = 1000;
  return;
}
