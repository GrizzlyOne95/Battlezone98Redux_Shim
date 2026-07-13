/*
 * Entry: 00478ba0
 * Name: GetMissionID
 * Namespace: Global
 * Signature: void GetMissionID(char * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl GetMissionID(char *param_1)

{
  char *pcVar1;
  char *pcVar2;
  
  param_1[0] = '\0';
  param_1[1] = '\0';
  param_1[2] = '\0';
  param_1[3] = '\0';
  param_1[4] = '\0';
  param_1[5] = '\0';
  param_1[6] = '\0';
  param_1[7] = '\0';
  pcVar2 = strchr(&msn_filename,0x2e);
  if (pcVar2 == (char *)0x0) {
    pcVar1 = &msn_filename;
    do {
      pcVar2 = pcVar1;
      pcVar1 = pcVar2 + 1;
    } while (*pcVar2 != '\0');
  }
  if ((int)(pcVar2 + -0xd42330) < 0x11) {
    memcpy(param_1,&msn_filename,pcVar2 + -0xd42330);
  }
  return;
}
