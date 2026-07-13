/*
 * Entry: 004d40ea
 * Name: PathDlgProc
 * Namespace: Global
 * Signature: int PathDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl PathDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  UINT UVar1;
  CHAR local_30 [40];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  if (param_2 == 0x110) {
    SetDlgItemTextA((HWND)param_1,1000,pathName);
    CheckRadioButton((HWND)param_1,0x3e9,0x3ea,(isArea != false) + 0x3e9);
    CheckRadioButton((HWND)param_1,0x3eb,0x3ec,(isInteresting == false) + 0x3eb);
    CheckRadioButton((HWND)param_1,0x3ee,0x3ef,(isInside == false) + 0x3ee);
    CheckRadioButton((HWND)param_1,0x3f4,0x3f5,(defendArea == false) + 0x3f4);
    sprintf(local_30,"%d",areaValue);
    SetDlgItemTextA((HWND)param_1,0x3f0,local_30);
    sprintf(local_30,"%d",areaForce);
    SetDlgItemTextA((HWND)param_1,0x3f1,local_30);
  }
  else {
    if (param_2 != 0x111) {
      return 0;
    }
    if ((param_3 & 0xffff) == 1) {
      GetDlgItemTextA((HWND)param_1,1000,pathName,0x28);
      UVar1 = IsDlgButtonChecked((HWND)param_1,0x3ea);
      isArea = (bool)('\x01' - (UVar1 != 1));
      UVar1 = IsDlgButtonChecked((HWND)param_1,0x3eb);
      isInteresting = (bool)('\x01' - (UVar1 != 1));
      UVar1 = IsDlgButtonChecked((HWND)param_1,0x3ee);
      isInside = (bool)('\x01' - (UVar1 != 1));
      UVar1 = IsDlgButtonChecked((HWND)param_1,0x3f4);
      defendArea = (bool)('\x01' - (UVar1 != 1));
      GetDlgItemTextA((HWND)param_1,0x3f0,local_30,0x28);
      sscanf(local_30,"%d",&areaValue);
      GetDlgItemTextA((HWND)param_1,0x3f1,local_30,0x28);
      sscanf(local_30,"%d",&areaForce);
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
