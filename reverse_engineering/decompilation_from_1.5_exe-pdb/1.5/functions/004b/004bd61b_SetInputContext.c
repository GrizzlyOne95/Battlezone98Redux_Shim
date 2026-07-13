/*
 * Entry: 004bd61b
 * Name: SetInputContext
 * Namespace: Global
 * Signature: void SetInputContext(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl SetInputContext(int param_1)

{
  if (param_1 == 1) {
    OldIMEContext = (HIMC__ *)_ImmAssociateContext_8((HWND)Device.hwndApp,(HIMC)0x0);
    return;
  }
  if (OldIMEContext != (HIMC__ *)0x0) {
    _ImmAssociateContext_8((HWND)Device.hwndApp,(HIMC)OldIMEContext);
    OldIMEContext = (HIMC__ *)0x0;
  }
  return;
}
