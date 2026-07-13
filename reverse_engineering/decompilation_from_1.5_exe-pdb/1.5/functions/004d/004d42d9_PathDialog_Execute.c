/*
 * Entry: 004d42d9
 * Name: PathDialog::Execute
 * Namespace: PathDialog
 * Signature: void Execute(PathDialog * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall PathDialog::Execute(PathDialog *this)

{
  DialogBoxParamA((HINSTANCE)Device.hInstance,(LPCSTR)0x65,(HWND)Device.hwndApp,PathDlgProc,0);
  return;
}
