/*
 * Entry: 0047a511
 * Name: InitialFrames
 * Namespace: Global
 * Signature: void InitialFrames(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl InitialFrames(void)

{
  ulong uVar1;
  
  DoFrame();
  uVar1 = Get_Frame_Count();
  if (10 < uVar1) {
    DoNextFrame = NormalFrames;
  }
  return;
}
