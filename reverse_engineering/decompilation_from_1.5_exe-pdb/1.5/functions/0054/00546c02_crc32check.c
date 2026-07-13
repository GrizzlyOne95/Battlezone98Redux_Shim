/*
 * Entry: 00546c02
 * Name: crc32check
 * Namespace: Global
 * Signature: ulong crc32check(char * param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Unable to track spacebase fully for stack */

ulong __cdecl crc32check(char *param_1,long param_2)

{
  int iVar1;
  void *pvVar2;
  char *pcVar3;
  char *pcVar4;
  int iVar5;
  undefined4 uStackY_38;
  undefined4 auStackY_34 [2];
  int local_c;
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  param_2 = crc32zix(param_1,param_2);
  auStackY_34[1] = 0x546c2f;
  pvVar2 = zixReadFile(param_1,&local_c);
  if (pvVar2 != (void *)0x0) {
    iVar1 = -(local_c + 1);
    *(int *)(&stack0xffffffe0 + iVar1) = local_c;
    *(void **)(&stack0xffffffdc + iVar1) = pvVar2;
    *(undefined1 **)(&stack0xffffffd8 + iVar1) = &stack0xffffffe4 + iVar1;
    *(undefined4 *)(&stack0xffffffd4 + iVar1) = 0x546c52;
    strncpy(*(char **)(&stack0xffffffd8 + iVar1),*(char **)(&stack0xffffffdc + iVar1),
            *(size_t *)(&stack0xffffffe0 + iVar1));
    *(void **)(&stack0xffffffd4 + iVar1) = pvVar2;
    *(undefined4 *)((int)auStackY_34 + iVar1 + 4) = 0x546c58;
    zixFree(*(void **)(&stack0xffffffd4 + iVar1));
    *(char **)((int)auStackY_34 + iVar1 + 4) = ", \t\r\n";
    *(undefined1 **)((int)auStackY_34 + iVar1) = &stack0xffffffe4 + iVar1;
    (&stack0xffffffe4)[local_c + iVar1] = 0;
    *(undefined4 *)((int)&uStackY_38 + iVar1) = 0x546c6b;
    pcVar3 = strtok(*(char **)((int)auStackY_34 + iVar1),*(char **)((int)auStackY_34 + iVar1 + 4));
    while (pcVar3 != (char *)0x0) {
      *(long *)(&stack0xffffffe0 + iVar1) = param_2;
      *(char **)(&stack0xffffffdc + iVar1) = pcVar3;
      *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x546c7c;
      param_2 = crc32zix(*(char **)(&stack0xffffffdc + iVar1),*(ulong *)(&stack0xffffffe0 + iVar1));
      *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x2e;
      *(char **)(&stack0xffffffd4 + iVar1) = pcVar3;
      *(undefined4 *)((int)auStackY_34 + iVar1 + 4) = 0x546c88;
      pcVar4 = strrchr(*(char **)(&stack0xffffffd4 + iVar1),*(int *)(&stack0xffffffd8 + iVar1));
      if (pcVar4 != (char *)0x0) {
        *(undefined **)(&stack0xffffffe0 + iVar1) = &s__odf;
        *(char **)(&stack0xffffffdc + iVar1) = pcVar4;
        *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x546ca0;
        iVar5 = _stricmp(*(char **)(&stack0xffffffdc + iVar1),*(char **)(&stack0xffffffe0 + iVar1));
        if (iVar5 == 0) {
          builtin_strncpy(pcVar4,".vdf",4);
          *(char **)(&stack0xffffffe0 + iVar1) = pcVar3;
          pcVar4[4] = '\0';
          *(undefined4 *)(&stack0xffffffdc + iVar1) = 0x546cb3;
          iVar5 = zixIsFileInIndex(*(char **)(&stack0xffffffe0 + iVar1));
          if (iVar5 != 0) {
            *(long *)(&stack0xffffffe0 + iVar1) = param_2;
            *(char **)(&stack0xffffffdc + iVar1) = pcVar3;
            *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x546cc1;
            param_2 = crc32zix(*(char **)(&stack0xffffffdc + iVar1),
                               *(ulong *)(&stack0xffffffe0 + iVar1));
          }
          builtin_strncpy(pcVar4,".sdf",4);
          *(char **)(&stack0xffffffe0 + iVar1) = pcVar3;
          pcVar4[4] = '\0';
          *(undefined4 *)(&stack0xffffffdc + iVar1) = 0x546cd6;
          iVar5 = zixIsFileInIndex(*(char **)(&stack0xffffffe0 + iVar1));
          if (iVar5 != 0) {
            *(long *)(&stack0xffffffe0 + iVar1) = param_2;
            *(char **)(&stack0xffffffdc + iVar1) = pcVar3;
            *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x546ce4;
            param_2 = crc32zix(*(char **)(&stack0xffffffdc + iVar1),
                               *(ulong *)(&stack0xffffffe0 + iVar1));
          }
        }
      }
      *(char **)(&stack0xffffffe0 + iVar1) = ", \t\r\n";
      *(undefined4 *)(&stack0xffffffdc + iVar1) = 0;
      *(undefined4 *)(&stack0xffffffd8 + iVar1) = 0x546cf6;
      pcVar3 = strtok(*(char **)(&stack0xffffffdc + iVar1),*(char **)(&stack0xffffffe0 + iVar1));
    }
  }
  return param_2;
}
