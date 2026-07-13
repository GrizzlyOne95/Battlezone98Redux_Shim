
void FUN_00456fc0(undefined4 param_1,undefined4 param_2,undefined4 *param_3)

{
  uint uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined1 local_3c [12];
  undefined4 local_30;
  undefined4 *local_2c;
  undefined4 *local_28;
  undefined4 *local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846e18;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  FUN_00448f10(param_1,param_2,param_3);
  local_8 = 0;
  *local_24 = TrailRender::vftable;
  local_24[0x1f] = 0;
  local_24[0x20] = 0;
  puVar2 = (undefined4 *)FUN_00439de0(local_3c,param_3,uVar1);
  local_20 = *puVar2;
  local_1c = puVar2[1];
  local_18 = puVar2[2];
  local_24[0x21] = local_20;
  local_24[0x22] = local_1c;
  local_24[0x23] = local_18;
  local_2c = (undefined4 *)FUN_00456f00(0x48);
  puVar2 = local_2c;
  for (iVar3 = 0x10; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar2 = *param_3;
    param_3 = param_3 + 1;
    puVar2 = puVar2 + 1;
  }
  local_2c[0x10] = local_24[0x1f];
  local_2c[0x11] = local_24[0x20];
  local_24[0x1e] = 0x100;
  local_28 = local_2c;
  local_30 = FUN_0083d92c(-(uint)((int)((ulonglong)(uint)local_24[0x1e] * 4 >> 0x20) != 0) |
                          (uint)((ulonglong)(uint)local_24[0x1e] * 4));
  local_24[0x1c] = local_30;
  memset((void *)local_24[0x1c],0,local_24[0x1e] << 2);
  *(undefined4 **)local_24[0x1c] = local_28;
  local_24[0x1d] = 1;
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

