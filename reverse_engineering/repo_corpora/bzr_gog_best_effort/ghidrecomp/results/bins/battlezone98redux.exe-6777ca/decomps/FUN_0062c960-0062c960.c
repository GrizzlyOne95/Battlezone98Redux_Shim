
void FUN_0062c960(undefined4 *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_a8 [64];
  undefined1 local_68 [12];
  int *local_5c;
  undefined4 local_58 [16];
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  int local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_5c = (int *)FUN_0062c890(param_2);
  if (local_5c == (int *)0x0) {
    local_c = 0;
    puVar1 = (undefined4 *)FUN_00440000(local_68,0,0,0);
    local_18 = *puVar1;
    local_14 = puVar1[1];
    local_10 = puVar1[2];
    *param_1 = local_18;
    param_1[1] = local_14;
    param_1[2] = local_10;
    param_1[3] = local_c;
  }
  else {
    local_c = local_5c[5];
    if ((*(uint *)(*local_5c + 0x14) & 0x100) == 0) {
      puVar1 = (undefined4 *)(*local_5c + 0x20);
      puVar3 = local_58;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    else {
      puVar1 = (undefined4 *)FUN_0062e070(local_a8,param_2,0);
      puVar3 = local_58;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    FUN_00820180(&local_18,local_5c + 2,1,local_58);
    *param_1 = local_18;
    param_1[1] = local_14;
    param_1[2] = local_10;
    param_1[3] = local_c;
  }
  FUN_0083e885();
  return;
}

