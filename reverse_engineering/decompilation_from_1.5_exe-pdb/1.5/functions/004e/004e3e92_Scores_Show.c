/*
 * Entry: 004e3e92
 * Name: Scores_Show
 * Namespace: Global
 * Signature: void Scores_Show(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Scores_Show(int param_1)

{
  int iVar1;
  
  if ((Device.Viewport.Width < 0x280) && (param_1 != 0)) {
    iVar1 = 0;
  }
  else {
    iVar1 = 1;
  }
  Chat_Show(iVar1);
  score_show = param_1;
  return;
}
