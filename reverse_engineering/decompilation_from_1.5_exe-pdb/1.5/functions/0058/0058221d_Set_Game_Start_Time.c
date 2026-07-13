/*
 * Entry: 0058221d
 * Name: Set_Game_Start_Time
 * Namespace: Global
 * Signature: void Set_Game_Start_Time(float param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Set_Game_Start_Time(float param_1)

{
  ulong extraout_EAX;
  
  _ftol2();
  StartTimer(extraout_EAX);
  return;
}
