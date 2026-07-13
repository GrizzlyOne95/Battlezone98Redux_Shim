
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined2 * FUN_006a12b0(int param_1,undefined2 *param_2)

{
  char cVar1;
  int *piVar2;
  uint uVar3;
  void *pvVar4;
  uint local_28;
  int local_24;
  char *local_1c;
  char *local_18;
  char *local_14;
  char *local_10;
  
  piVar2 = (int *)FUN_004200d0(DAT_02c00ec0);
  if (*piVar2 == 0) {
    if (param_2 == (undefined2 *)0x0) {
      uVar3 = size();
      if (DAT_02c00ec0 < uVar3) {
        piVar2 = (int *)FUN_004200d0(DAT_02c00ec0);
        param_2 = *(undefined2 **)(*piVar2 + 4);
      }
      else {
        param_2 = (undefined2 *)&DAT_00931028;
      }
    }
    else {
      pvVar4 = operator_new(8);
      if (pvVar4 == (void *)0x0) {
        local_24 = 0;
      }
      else {
        local_24 = FUN_006a1570();
      }
      piVar2 = (int *)FUN_004200d0(DAT_02c00ec0);
      *piVar2 = local_24;
      *(undefined2 **)(local_24 + 4) = param_2;
      memset(param_2,0,0x80);
      local_18 = (char *)(param_1 + 0x30);
      local_10 = (char *)(param_2 + 0x20);
      do {
        cVar1 = *local_18;
        *local_10 = cVar1;
        local_18 = local_18 + 1;
        local_10 = local_10 + 1;
      } while (cVar1 != '\0');
      *(undefined1 *)(param_2 + 0x24) = 0;
      local_1c = (char *)(param_2 + 0x20);
      local_14 = (char *)(param_2 + 0x30);
      do {
        cVar1 = *local_1c;
        *local_14 = cVar1;
        local_1c = local_1c + 1;
        local_14 = local_14 + 1;
      } while (cVar1 != '\0');
      *(undefined4 *)(param_2 + 0x10) = *(undefined4 *)(param_1 + 0x48);
      if (DAT_00931014 == 0) {
        _DAT_02c00a98 = _DAT_02c00a98 + 1;
        *param_2 = DAT_02c00a98;
      }
      else {
        *param_2 = DAT_02c00a90;
      }
      param_2[0xb] = 0;
      param_2[0xc] = 0;
      param_2[7] = 0;
      param_2[8] = 0;
      param_2[6] = 0;
      *(uint *)(param_2 + 0x12) = *(uint *)(param_2 + 0x12) & 0xfffffffe;
      cVar1 = FUN_006a07e0(*(undefined4 *)(param_1 + 0x14),param_2 + 0x30,param_2 + 0x20);
      local_28 = (uint)(cVar1 != '\0');
      *(uint *)(param_2 + 0x12) = *(uint *)(param_2 + 0x12) & 0xfffffffd | local_28 << 1;
      *(undefined4 *)(param_2 + 2) = 0;
      *(undefined4 *)(param_2 + 4) = 0;
      *(undefined4 *)(param_2 + 0x16) = 0;
      *(undefined4 *)(param_2 + 0x18) = 0;
      *(uint *)(param_2 + 0x12) = *(uint *)(param_2 + 0x12) & 0xfc3fffff | 0x2000000;
      *(uint *)(param_2 + 0x12) = *(uint *)(param_2 + 0x12) & 0xffc3ffff | 0x200000;
    }
  }
  else {
    param_2 = *(undefined2 **)(*piVar2 + 4);
  }
  return param_2;
}

