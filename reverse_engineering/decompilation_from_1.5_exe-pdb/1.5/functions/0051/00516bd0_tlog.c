/*
 * Entry: 00516bd0
 * Name: tlog
 * Namespace: Global
 * Signature: void tlog(int param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl tlog(int param_1,char *param_2)

{
  char *pcVar1;
  char *pcVar2;
  
  if ((param_1 & log_mode) == 0) {
    _tlog_filename = (char *)0x0;
    return;
  }
  vsprintf(msg,param_2,&stack0x0000000c);
  pcVar2 = (char *)0xc3f58f;
  do {
    pcVar1 = pcVar2 + 1;
    pcVar2 = pcVar2 + 1;
  } while (*pcVar1 != '\0');
  *(char (*) [2])pcVar2 = (char  [2])0xa;
  return;
}
