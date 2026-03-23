
void FUN_0081f920(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 *puVar1;
  int iVar2;
  undefined1 local_78 [12];
  undefined1 local_6c [12];
  undefined1 local_60 [12];
  undefined1 local_54 [12];
  undefined4 local_48 [4];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_20 = 0;
  local_18 = 0;
  local_10 = 0;
  puVar1 = (undefined4 *)FUN_004621a0(local_6c,param_2);
  local_48[3] = *puVar1;
  local_38 = puVar1[1];
  local_34 = puVar1[2];
  puVar1 = (undefined4 *)FUN_004440d0(local_78,local_48 + 3,param_3);
  local_48[0] = *puVar1;
  local_48[1] = puVar1[1];
  local_48[2] = puVar1[2];
  puVar1 = (undefined4 *)FUN_004621a0(local_54,local_48);
  local_48[0] = *puVar1;
  local_48[1] = puVar1[1];
  local_48[2] = puVar1[2];
  puVar1 = (undefined4 *)FUN_004440d0(local_60,local_48,local_48 + 3);
  local_30 = *puVar1;
  local_2c = puVar1[1];
  local_28 = puVar1[2];
  puVar1 = local_48;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *param_1 = *puVar1;
    puVar1 = puVar1 + 1;
    param_1 = param_1 + 1;
  }
  FUN_0083e885();
  return;
}

