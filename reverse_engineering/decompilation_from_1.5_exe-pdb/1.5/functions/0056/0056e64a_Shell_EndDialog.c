/*
 * Entry: 0056e64a
 * Name: Shell_EndDialog
 * Namespace: Global
 * Signature: int Shell_EndDialog(HWND__ * param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Shell_EndDialog(HWND__ *param_1,int param_2)

{
  BOOL BVar1;
  
  BVar1 = DestroyWindow((HWND)param_1);
  if (hDialog == param_1) {
    hDialog = (HWND__ *)0x0;
  }
  nDialogResult = param_2;
  return BVar1;
}
