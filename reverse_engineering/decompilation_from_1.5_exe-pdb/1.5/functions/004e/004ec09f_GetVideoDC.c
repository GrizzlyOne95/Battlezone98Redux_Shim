/*
 * Entry: 004ec09f
 * Name: GetVideoDC
 * Namespace: Global
 * Signature: HDC__ * GetVideoDC(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

HDC__ * __cdecl GetVideoDC(void)

{
  HDC__ *pHVar1;
  
  pHVar1 = (*Device.VideoMode.GetVideoDC)(&Device);
  return pHVar1;
}
