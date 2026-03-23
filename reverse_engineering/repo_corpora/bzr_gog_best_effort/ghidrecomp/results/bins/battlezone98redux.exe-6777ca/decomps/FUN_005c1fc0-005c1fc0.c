
void __thiscall FUN_005c1fc0(int param_1,float param_2)

{
  undefined4 *puVar1;
  float10 fVar2;
  undefined1 local_34 [12];
  float local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_24 = param_1;
  if ((*(uint *)(*(int *)(param_1 + 0xf4) + 0x14) & 0x200) == 0) {
    puVar1 = (undefined4 *)FUN_004560b0(local_34,*(int *)(param_1 + 0xf4) + 0x20);
    local_20 = *puVar1;
    local_1c = puVar1[1];
    local_18 = puVar1[2];
    local_14 = local_20;
    local_10 = local_1c;
    local_c = local_18;
    fVar2 = (float10)FUN_004428b0(&local_20,local_24 + 300);
    local_28 = (float)fVar2;
    fVar2 = (float10)FUN_00447ed0((param_2 - local_28) * 0.09,0xbf800000,0x3f800000);
    *(float *)(*(int *)(local_24 + 0x230) + 0xd0) = (float)fVar2;
    *(undefined4 *)(*(int *)(local_24 + 0x230) + 0xcc) = 0;
  }
  FUN_0083e885();
  return;
}

