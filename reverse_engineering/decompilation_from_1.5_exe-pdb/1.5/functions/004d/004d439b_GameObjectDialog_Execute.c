/*
 * Entry: 004d439b
 * Name: GameObjectDialog::Execute
 * Namespace: GameObjectDialog
 * Signature: void Execute(GameObjectDialog * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall GameObjectDialog::Execute(GameObjectDialog *this)

{
  DialogBoxParamA((HINSTANCE)Device.hInstance,(LPCSTR)0x66,(HWND)Device.hwndApp,ObjDlgProc,0);
  return;
}
