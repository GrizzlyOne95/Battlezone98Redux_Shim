
void FUN_00505db0(int *param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_94 [64];
  undefined4 *local_54;
  undefined4 *local_50;
  uint local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_4c = (int)*(char *)(*param_1 + -1) & 0x1f;
  if (local_4c == 1) {
    local_54 = (undefined4 *)FUN_004ff7e0(param_2);
    puVar1 = (undefined4 *)*param_1;
    *local_54 = *puVar1;
    local_54[1] = puVar1[1];
    local_54[2] = puVar1[2];
    *param_1 = *param_1 + 0xc;
  }
  else if (local_4c == 2) {
    local_50 = (undefined4 *)FUN_004ff840(param_2);
    puVar1 = (undefined4 *)*param_1;
    puVar1 = (undefined4 *)
             FUN_006253c0(local_94,*puVar1,puVar1[1],puVar1[2],*(undefined2 *)(puVar1 + 3));
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    puVar1 = local_48;
    puVar3 = local_50;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    *param_1 = *param_1 + 0xe;
  }
  FUN_0083e885();
  return;
}

