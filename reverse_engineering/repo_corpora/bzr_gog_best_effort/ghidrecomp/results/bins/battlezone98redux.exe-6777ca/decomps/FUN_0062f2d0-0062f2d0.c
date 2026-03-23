
void FUN_0062f2d0(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 local_50 [9];
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  puVar2 = *(undefined4 **)(param_2 + 0x88);
  FUN_00444970(local_50);
  local_2c = *puVar2;
  local_28 = puVar2[1];
  local_24 = puVar2[2];
  puVar2 = local_50;
  for (iVar1 = 0x12; iVar1 != 0; iVar1 = iVar1 + -1) {
    *param_1 = *puVar2;
    puVar2 = puVar2 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

