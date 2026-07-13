/*
 * Entry: 005711bd
 * Name: SetNetworkFont2
 * Namespace: Global
 * Signature: void SetNetworkFont2(HDC__ * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetNetworkFont2(HDC__ *param_1)

{
  int iVar1;
  
  iVar1 = IsJapanese();
  if ((iVar1 == 0) && (iVar1 = GetScreenDPI(), iVar1 == 0x60)) {
    return;
  }
  SelectObject((HDC)param_1,netFont);
  return;
}
