/*
 * Entry: 004d42f5
 * Name: ObjDlgProc
 * Namespace: Global
 * Signature: int ObjDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl ObjDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  UINT UVar1;
  
  if (param_2 == 0x110) {
    SetDlgItemTextA((HWND)param_1,0x3f2,objLabel);
    SetDlgItemInt((HWND)param_1,0x3f7,independence,0);
  }
  else {
    if (param_2 != 0x111) {
      return 0;
    }
    if ((param_3 & 0xffff) == 1) {
      GetDlgItemTextA((HWND)param_1,0x3f2,objLabel,0x2e);
      UVar1 = GetDlgItemInt((HWND)param_1,0x3f7,(BOOL *)&param_2,0);
      if (param_2 != 0) {
        independence = UVar1;
      }
      EndDialog((HWND)param_1,1);
      cancelled = false;
    }
    else {
      if ((param_3 & 0xffff) != 2) {
        return 0;
      }
      EndDialog((HWND)param_1,0);
    }
  }
  return 1;
}
