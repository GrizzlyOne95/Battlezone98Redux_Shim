/*
 * Entry: 004bbfd7
 * Name: set_joystick_map
 * Namespace: Global
 * Signature: int set_joystick_map(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl set_joystick_map(int param_1)

{
  char cVar1;
  undefined4 *puVar2;
  char *pcVar3;
  int iVar4;
  FILE *_File;
  char *pcVar5;
  undefined4 *puVar6;
  undefined4 local_108;
  undefined2 auStack_104 [2];
  char acStack_100 [120];
  undefined1 local_88 [128];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_88;
  local_108 = 0x64646967;
  auStack_104[0] = 0x69;
  pcVar5 = &stack0xfffffef7;
  do {
    pcVar3 = pcVar5 + 1;
    pcVar5 = pcVar5 + 1;
  } while (*pcVar3 != '\0');
  *(char (*) [2])pcVar5 = (char  [2])0x5c;
  pcVar5 = &stack0xfffffef7;
  do {
    pcVar3 = pcVar5;
    pcVar5 = pcVar3 + 1;
  } while (pcVar3[1] != '\0');
  builtin_strncpy(pcVar3 + 1,"joystick",9);
  pcVar5 = (char *)&local_108;
  do {
    pcVar3 = pcVar5;
    pcVar5 = pcVar3 + 1;
  } while (*pcVar3 != '\0');
  iVar4 = isdigit((int)pcVar3[-1]);
  while (iVar4 != 0) {
    pcVar5 = (char *)&local_108;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    pcVar5[(int)(acStack_100 + (-9 - ((int)&local_108 + 1)))] = '\0';
    pcVar5 = (char *)&local_108;
    do {
      cVar1 = *pcVar5;
      pcVar5 = pcVar5 + 1;
    } while (cVar1 != '\0');
    iVar4 = isdigit((int)pcVar5[(int)(acStack_100 + (-9 - ((int)&local_108 + 1)))]);
  }
  puVar2 = (undefined4 *)&stack0xfffffef7;
  do {
    puVar6 = puVar2;
    puVar2 = (undefined4 *)((int)puVar6 + 1);
  } while (*(char *)((int)puVar6 + 1) != '\0');
  *(undefined4 *)((int)puVar6 + 1) = 0x6474732e;
  *(undefined1 *)((int)puVar6 + 5) = 0;
  _File = fopen((char *)&local_108,"r");
  if (_File != (FILE *)0x0) {
    inmap_lineno = 0;
    inmap_filename = (char *)&local_108;
    read_one_mapping_file((_iobuf *)_File);
    fclose(_File);
  }
  return 1;
}
