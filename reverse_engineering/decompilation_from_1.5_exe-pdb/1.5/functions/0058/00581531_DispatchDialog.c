/*
 * Entry: 00581531
 * Name: DispatchDialog
 * Namespace: Global
 * Signature: void DispatchDialog(int param_1, HWND__ * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl DispatchDialog(int param_1,HWND__ *param_2)

{
  int iVar1;
  char *pcVar2;
  code *pcVar3;
  
  nShellMode = param_1;
  switch(param_1) {
  case 1:
    pcVar3 = ShellDlgProc;
    pcVar2 = (char *)0x68;
    goto LAB_00581565;
  case 2:
    do_single();
    break;
  default:
    nShellMode = 0;
    break;
  case 7:
    do_usamissions();
    break;
  case 8:
    do_ussrmissions();
    break;
  case 9:
    do_trnmissions();
    break;
  case 0xb:
    iVar1 = Net_IsNetGame();
    if (iVar1 != 0) {
      do_netescape();
      lastShellMode = param_1;
      return;
    }
    pcVar3 = EscapeDlgProc;
    pcVar2 = (char *)0x75;
    goto LAB_00581565;
  case 0xc:
    do_old(nPlayerSide);
    break;
  case 0xd:
    do_stransport();
    break;
  case 0xe:
    do_shell();
    break;
  case 0xf:
  case 0x10:
  case 0x11:
  case 0x14:
    break;
  case 0x12:
    do_loadgame(lastShellMode);
    break;
  case 0x13:
    pcVar3 = FailMissionDlgProc;
    pcVar2 = (char *)0x81;
LAB_00581565:
    Shell_DialogBoxParam(shell_hInstance,pcVar2,shell_hwnd,pcVar3,0);
  }
  lastShellMode = param_1;
  return;
}
