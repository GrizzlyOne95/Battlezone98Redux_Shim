/*
 * Entry: 0054a984
 * Name: GetSaveDesc
 * Namespace: Global
 * Signature: int GetSaveDesc(int param_1, ShellButton * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl GetSaveDesc(int param_1,ShellButton *param_2)

{
  char cVar1;
  FILE *_File;
  int iVar2;
  _iobuf *p_Var3;
  char *pcVar4;
  int local_12c;
  int local_128;
  ShellButton *local_124;
  uint local_120;
  undefined1 local_11a;
  undefined1 local_119;
  char local_118 [4];
  undefined4 uStack_114;
  char acStack_110 [4];
  undefined4 uStack_10c;
  undefined1 local_b0 [152];
  char acStack_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_b0;
  builtin_strncpy(local_118,"NULL",4);
  local_124 = param_2;
  uStack_114 = uStack_114 & 0xffffff00;
  memset((int)&uStack_114 + 1,0,0xfb);
  switch(param_1) {
  case 1:
    pcVar4 = "save\\game1.sav";
    break;
  case 2:
    pcVar4 = "save\\game2.sav";
    break;
  case 3:
    pcVar4 = "save\\game3.sav";
    break;
  case 4:
    pcVar4 = "save\\game4.sav";
    break;
  case 5:
    pcVar4 = "save\\game5.sav";
    break;
  case 6:
    pcVar4 = "save\\game6.sav";
    break;
  case 7:
    pcVar4 = "save\\game7.sav";
    break;
  case 8:
    pcVar4 = "save\\game8.sav";
    break;
  case 9:
    pcVar4 = "save\\game9.sav";
    break;
  case 10:
    builtin_strncpy(local_118,"save",4);
    uStack_114._0_1_ = '\\';
    uStack_114._1_1_ = 'g';
    uStack_114._2_1_ = 'a';
    uStack_114._3_1_ = 'm';
    builtin_strncpy(acStack_110,"e10.",4);
    uStack_10c._0_1_ = 's';
    uStack_10c._1_1_ = 'a';
    uStack_10c._2_1_ = 'v';
    uStack_10c._3_1_ = '\0';
    goto LAB_0054aa34;
  default:
    goto switchD_0054a9d9_default;
  }
  local_118 = *(char (*) [4])pcVar4;
  uStack_114 = *(uint *)(pcVar4 + 4);
  acStack_110 = *(char (*) [4])(pcVar4 + 8);
  uStack_10c._0_3_ = *(undefined3 *)(pcVar4 + 0xc);
LAB_0054aa34:
  _File = fopen(local_118,"rb");
  if (_File != (FILE *)0x0) {
    local_11a = binarySave;
    local_119 = missionSave;
    iVar2 = 0;
    do {
      cVar1 = (&msn_filename)[iVar2];
      acStack_18[iVar2] = cVar1;
      iVar2 = iVar2 + 1;
    } while (cVar1 != '\0');
    binarySave = false;
    missionSave = false;
    fseek(_File,0,2);
    local_120 = ftell(_File);
    fseek(_File,0,0);
    p_Var3 = operator_new__(local_120);
    fread(p_Var3,1,local_120,_File);
    fclose(_File);
    p_Var3 = in_open(p_Var3,local_120);
    in(p_Var3,&version,4);
    if (0x409 < version) {
      in(p_Var3,&binarySave,1);
      in(p_Var3,&msn_filename,0x10);
      in(p_Var3,&local_128,4);
      in(p_Var3,&missionSave,1);
      in(p_Var3,&local_12c,4);
      in(p_Var3,saveGameDesc,0x100);
      ShellButton::SetLabelText(local_124,saveGameDesc);
      binarySave = (bool)local_11a;
      missionSave = (bool)local_119;
      iVar2 = 0;
      do {
        cVar1 = acStack_18[iVar2];
        (&msn_filename)[iVar2] = cVar1;
        iVar2 = iVar2 + 1;
      } while (cVar1 != '\0');
      p_Var3 = in_close(p_Var3);
      operator_delete__(p_Var3);
      return 1;
    }
    ShellButton::SetLabelText(local_124,"Old version save game");
    p_Var3 = in_close(p_Var3);
    operator_delete__(p_Var3);
  }
switchD_0054a9d9_default:
  return 0;
}
