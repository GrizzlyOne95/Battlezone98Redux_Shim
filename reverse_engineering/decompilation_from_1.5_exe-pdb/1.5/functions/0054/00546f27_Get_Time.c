/*
 * Entry: 00546f27
 * Name: Get_Time
 * Namespace: Global
 * Signature: float Get_Time(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

float __cdecl Get_Time(void)

{
  float fVar1;
  DWORD DVar2;
  
  DVar2 = Get_TimeNow();
  fVar1 = (float)(int)DVar2;
  if ((int)DVar2 < 0) {
    fVar1 = fVar1 + 4.2949673e+09;
  }
  return fVar1 * 0.001;
}
