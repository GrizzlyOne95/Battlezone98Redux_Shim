/*
 * Entry: 0056e749
 * Name: WarningDlgProc
 * Namespace: Global
 * Signature: int WarningDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl WarningDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  INT_PTR nResult;
  char local_408 [124];
  undefined1 local_38c [132];
  char local_308 [256];
  char local_208 [105];
  undefined1 local_19f [151];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_38c;
  if (param_2 == 0x110) {
    pcVar2 = 
    "The game was not closed properly. Do you wish to run regular Software mode or Hardware accelerated mode?"
    ;
    pcVar3 = local_208;
    for (iVar1 = 0x1a; iVar1 != 0; iVar1 = iVar1 + -1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar3 = pcVar3 + 4;
    }
    *pcVar3 = *pcVar2;
    memset(local_19f,0,0x97);
    read_text_label("hardware","message",local_208);
    SetDlgItemTextA((HWND)param_1,0x427,local_208);
    builtin_strncpy(local_108,"Software",9);
    memset(local_108 + 9,0,0xf7);
    builtin_strncpy(local_408,"Hardware",9);
    memset(local_408 + 9,0,0xf7);
    builtin_strncpy(local_308,"Battlezone Warning",0x13);
    memset(local_308 + 0x13,0,0xed);
    read_text_label("hardware","software",local_108);
    read_text_label("hardware","hardware",local_408);
    read_text_label("hardware","title",local_308);
    SetDlgItemTextA((HWND)param_1,1,local_108);
    SetDlgItemTextA((HWND)param_1,2,local_408);
    SetWindowTextA((HWND)param_1,local_308);
  }
  else if (param_2 == 0x111) {
    if ((param_3 & 0xffff) == 1) {
      nResult = 1;
    }
    else {
      if ((param_3 & 0xffff) != 2) {
        return 0;
      }
      nResult = 0;
    }
    EndDialog((HWND)param_1,nResult);
  }
  return 0;
}
