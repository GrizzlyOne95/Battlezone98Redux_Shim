
/* WARNING: Function: __alloca_probe_16 replaced with injection: alloca_probe */
/* WARNING: Unable to track spacebase fully for stack */

void FUN_004afff0(undefined4 param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int aiStack_30 [3];
  int *piStack_24;
  undefined1 *local_20;
  int local_1c;
  undefined1 *local_18;
  int local_14;
  char *local_10;
  char *local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  piStack_24 = param_2;
  aiStack_30[2] = param_1;
  aiStack_30[1] = 0x4b000d;
  param_2 = (int *)FUN_004aff40();
  piStack_24 = &local_1c;
  aiStack_30[2] = param_1;
  aiStack_30[1] = 0x4b0020;
  local_14 = FUN_00829130();
  if (local_14 != 0) {
    piStack_24 = (int *)0x4b003b;
    iVar1 = -(local_1c + 1);
    local_20 = (undefined1 *)((int)&local_20 + iVar1);
    local_18 = (undefined1 *)((int)&local_20 + iVar1);
    *(int *)((int)&piStack_24 + iVar1) = local_1c;
    *(int *)((int)aiStack_30 + iVar1 + 8) = local_14;
    *(undefined1 **)((int)aiStack_30 + iVar1 + 4) = local_18;
    *(undefined4 *)((int)aiStack_30 + iVar1) = 0x4b0056;
    strncpy(*(char **)((int)aiStack_30 + iVar1 + 4),*(char **)((int)aiStack_30 + iVar1 + 8),
            *(size_t *)((int)&piStack_24 + iVar1));
    *(int *)((int)&piStack_24 + iVar1) = local_14;
    *(undefined4 *)((int)aiStack_30 + iVar1 + 8) = 0x4b0062;
    FUN_0062f240();
    local_18[local_1c] = 0;
    *(char **)((int)&piStack_24 + iVar1) = ", \t\r\n";
    *(undefined1 **)((int)aiStack_30 + iVar1 + 8) = local_18;
    *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b007d;
    local_c = strtok(*(char **)((int)aiStack_30 + iVar1 + 8),*(char **)((int)&piStack_24 + iVar1));
    while (local_c != (char *)0x0) {
      *(int **)((int)&piStack_24 + iVar1) = param_2;
      *(char **)((int)aiStack_30 + iVar1 + 8) = local_c;
      *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b00af;
      param_2 = (int *)FUN_004aff40();
      *(undefined4 *)((int)&piStack_24 + iVar1) = 0x2e;
      *(char **)((int)aiStack_30 + iVar1 + 8) = local_c;
      *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b00c1;
      local_10 = strrchr(*(char **)((int)aiStack_30 + iVar1 + 8),*(int *)((int)&piStack_24 + iVar1))
      ;
      if (local_10 != (char *)0x0) {
        *(undefined4 **)((int)&piStack_24 + iVar1) = &DAT_00878418;
        *(char **)((int)aiStack_30 + iVar1 + 8) = local_10;
        *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b00e0;
        iVar2 = _stricmp(*(char **)((int)aiStack_30 + iVar1 + 8),
                         *(char **)((int)&piStack_24 + iVar1));
        if (iVar2 == 0) {
          builtin_strncpy(local_10,".vdf",5);
          *(char **)((int)&piStack_24 + iVar1) = local_c;
          *(undefined4 *)((int)aiStack_30 + iVar1 + 8) = 0x4b0104;
          iVar2 = FUN_00829390();
          if (iVar2 != 0) {
            *(int **)((int)&piStack_24 + iVar1) = param_2;
            *(char **)((int)aiStack_30 + iVar1 + 8) = local_c;
            *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b0118;
            param_2 = (int *)FUN_004aff40();
          }
          builtin_strncpy(local_10,".sdf",5);
          *(char **)((int)&piStack_24 + iVar1) = local_c;
          *(undefined4 *)((int)aiStack_30 + iVar1 + 8) = 0x4b013b;
          iVar2 = FUN_00829390();
          if (iVar2 != 0) {
            *(int **)((int)&piStack_24 + iVar1) = param_2;
            *(char **)((int)aiStack_30 + iVar1 + 8) = local_c;
            *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b014f;
            param_2 = (int *)FUN_004aff40();
          }
        }
      }
      *(char **)((int)&piStack_24 + iVar1) = ", \t\r\n";
      *(undefined4 *)((int)aiStack_30 + iVar1 + 8) = 0;
      *(undefined4 *)((int)aiStack_30 + iVar1 + 4) = 0x4b0092;
      local_c = strtok(*(char **)((int)aiStack_30 + iVar1 + 8),*(char **)((int)&piStack_24 + iVar1))
      ;
    }
  }
  piStack_24 = (int *)0x4b016a;
  FUN_0083e885();
  return;
}

