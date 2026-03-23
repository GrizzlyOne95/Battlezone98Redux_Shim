
void FUN_0062e070(undefined4 *param_1,int param_2,int param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_88 [64];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_2 == param_3) {
    puVar1 = &DAT_008fe1e0;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = *puVar1;
      puVar1 = puVar1 + 1;
      param_1 = param_1 + 1;
    }
  }
  else {
    puVar1 = (undefined4 *)(param_2 + 0x20);
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    for (param_2 = *(int *)(param_2 + 0x78); (param_2 != 0 && (param_2 != param_3));
        param_2 = *(int *)(param_2 + 0x78)) {
      puVar1 = (undefined4 *)FUN_0081fe60(local_88,local_48,param_2 + 0x20);
      puVar3 = local_48;
      for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
        *puVar3 = *puVar1;
        puVar1 = puVar1 + 1;
        puVar3 = puVar3 + 1;
      }
    }
    puVar1 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *param_1 = *puVar1;
      puVar1 = puVar1 + 1;
      param_1 = param_1 + 1;
    }
  }
  FUN_0083e885();
  return;
}

