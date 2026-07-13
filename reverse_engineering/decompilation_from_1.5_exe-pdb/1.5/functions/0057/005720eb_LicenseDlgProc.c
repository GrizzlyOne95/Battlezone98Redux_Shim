/*
 * Entry: 005720eb
 * Name: LicenseDlgProc
 * Namespace: Global
 * Signature: int LicenseDlgProc(HWND__ * param_1, uint param_2, uint param_3, long param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl LicenseDlgProc(HWND__ *param_1,uint param_2,uint param_3,long param_4)

{
  FILE *_File;
  HWND pHVar1;
  char *pcVar2;
  char *pcVar3;
  BOOL bEnable;
  int iVar4;
  char local_308 [29];
  undefined1 local_2eb [95];
  undefined1 local_28c [132];
  char local_208 [256];
  char local_108 [256];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_28c;
  if (param_2 == 0x110) {
    _File = fopen("license.txt","rb");
    if (_File == (FILE *)0x0) {
      bEnable = 0;
      pHVar1 = GetDlgItem((HWND)param_1,1);
      EnableWindow(pHVar1,bEnable);
      pcVar2 = "License Text Not Found";
      pcVar3 = strbuf;
      for (iVar4 = 5; iVar4 != 0; iVar4 = iVar4 + -1) {
        *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
        pcVar2 = pcVar2 + 4;
        pcVar3 = pcVar3 + 4;
      }
      *(undefined2 *)pcVar3 = *(undefined2 *)pcVar2;
      pcVar3[2] = pcVar2[2];
    }
    else {
      fread(strbuf,1,0x1f400,_File);
      fclose(_File);
    }
    SetDlgItemTextA((HWND)param_1,0x427,strbuf);
    builtin_strncpy(local_108,"Accept",7);
    memset(local_108 + 7,0,0xf9);
    builtin_strncpy(local_208,"Do Not Accept",0xe);
    memset(local_208 + 0xe,0,0xf2);
    pcVar2 = "Map Editor License Agreement";
    pcVar3 = local_308;
    for (iVar4 = 7; iVar4 != 0; iVar4 = iVar4 + -1) {
      *(undefined4 *)pcVar3 = *(undefined4 *)pcVar2;
      pcVar2 = pcVar2 + 4;
      pcVar3 = pcVar3 + 4;
    }
    *pcVar3 = *pcVar2;
    memset(local_2eb,0,0xe3);
    read_text_label("license","accept",local_108);
    read_text_label("license","not_accept",local_208);
    read_text_label("license","title",local_308);
    pHVar1 = GetDlgItem((HWND)param_1,1);
    SetNetworkFont((HWND__ *)pHVar1);
    pHVar1 = GetDlgItem((HWND)param_1,2);
    SetNetworkFont((HWND__ *)pHVar1);
    pHVar1 = GetDlgItem((HWND)param_1,0x427);
    SetNetworkFont((HWND__ *)pHVar1);
    SetDlgItemTextA((HWND)param_1,1,local_108);
    SetDlgItemTextA((HWND)param_1,2,local_208);
    SetWindowTextA((HWND)param_1,local_308);
  }
  else if (param_2 == 0x111) {
    if ((param_3 & 0xffff) == 1) {
      iVar4 = 1;
    }
    else {
      if ((param_3 & 0xffff) != 2) {
        return 0;
      }
      iVar4 = 0;
    }
    Shell_EndDialog(param_1,iVar4);
  }
  return 0;
}
