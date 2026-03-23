
undefined4 * FUN_0083120f(undefined4 param_1,int param_2,int *param_3)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_8;
  
  puVar1 = (undefined4 *)FUN_00831196(param_2,param_3);
  if ((puVar1[2] != 0) || (puVar1 == (undefined4 *)&DAT_0086eef0)) {
    local_8 = *(undefined4 **)(param_2 + 0x14);
    do {
      if (local_8 <= *(undefined4 **)(param_2 + 0x10)) {
        *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -0x20;
        local_8 = (undefined4 *)0x0;
        break;
      }
      *(int *)(param_2 + 0x14) = *(int *)(param_2 + 0x14) + -0x20;
      local_8 = *(undefined4 **)(param_2 + 0x14);
    } while (local_8[6] != 0);
    if (local_8 == (undefined4 *)0x0) {
      FUN_008312f6(param_1,param_2,param_3);
      puVar1 = (undefined4 *)FUN_008310b4(param_1,param_2,param_3);
      return puVar1;
    }
    puVar2 = (undefined4 *)FUN_00831196(param_2,puVar1 + 4);
    if (puVar2 == puVar1) {
      local_8[7] = puVar1[7];
      puVar1[7] = local_8;
      puVar1 = local_8;
    }
    else {
      for (; (undefined4 *)puVar2[7] != puVar1; puVar2 = (undefined4 *)puVar2[7]) {
      }
      puVar2[7] = local_8;
      puVar2 = puVar1;
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *local_8 = *puVar2;
        puVar2 = puVar2 + 1;
        local_8 = local_8 + 1;
      }
      puVar1[7] = 0;
      puVar1[2] = 0;
    }
  }
  puVar1[4] = *param_3;
  puVar1[5] = param_3[1];
  puVar1[6] = param_3[2];
  if (((3 < param_3[2]) && ((*(byte *)(*param_3 + 5) & 3) != 0)) &&
     ((*(byte *)(param_2 + 5) & 4) != 0)) {
    FUN_00830000(param_1,param_2);
  }
  return puVar1;
}

