
void FUN_0062e650(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_88 [64];
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar1 = (undefined4 *)FUN_008203f0(local_88,param_1 + 0x20);
  puVar3 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  *param_2 = 0x4b189680;
  param_2[1] = 0x4b189680;
  param_2[2] = 0x4b189680;
  *param_3 = 0xcb189680;
  param_3[1] = 0xcb189680;
  param_3[2] = 0xcb189680;
  FUN_0062e3f0(param_1,local_48,param_2,param_3);
  FUN_0083e885();
  return;
}

