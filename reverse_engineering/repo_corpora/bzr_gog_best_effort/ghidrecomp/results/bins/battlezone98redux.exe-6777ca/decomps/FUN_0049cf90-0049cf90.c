
void FUN_0049cf90(undefined4 *param_1,undefined4 *param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  float10 fVar4;
  undefined1 local_d4 [64];
  undefined1 local_94 [24];
  int local_7c;
  undefined4 local_78 [16];
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_2c = *param_1;
  puVar1 = (undefined4 *)FUN_0049c4f0(local_94,*param_1,param_1[1],param_1[2]);
  local_20 = *puVar1;
  local_1c = puVar1[1];
  local_18 = puVar1[2];
  local_14 = puVar1[3];
  local_10 = puVar1[4];
  local_c = puVar1[5];
  fVar4 = (float10)FUN_0049c8f0(local_20,local_1c,local_18,local_14,local_10,local_c);
  local_28 = (float)fVar4;
  local_24 = param_1[2];
  local_38 = *param_2;
  local_34 = 0;
  local_30 = param_2[2];
  puVar1 = (undefined4 *)FUN_0081fa10(local_d4,&local_2c,&local_38);
  puVar3 = local_78;
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar1 = local_78;
  puVar3 = (undefined4 *)(local_7c + 0x378);
  for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar3 = *puVar1;
    puVar1 = puVar1 + 1;
    puVar3 = puVar3 + 1;
  }
  FUN_0083e885();
  return;
}

