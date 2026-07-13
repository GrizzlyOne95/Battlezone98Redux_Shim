
void __fastcall FUN_005a9900(int param_1)

{
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  undefined8 local_20;
  undefined8 local_18;
  undefined8 local_10;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if ((*(uint *)(*(int *)(param_1 + 0x228) + 0x114) & 1) != 0) {
    local_48 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x20);
    local_44 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x24);
    local_40 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x28);
    local_3c = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x38);
    local_38 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x3c);
    local_34 = *(undefined4 *)(*(int *)(param_1 + 0xf4) + 0x40);
    local_30 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x2c) ^ 0x80000000;
    local_2c = *(uint *)(*(int *)(param_1 + 0xf4) + 0x30) ^ 0x80000000;
    local_28 = *(uint *)(*(int *)(param_1 + 0xf4) + 0x34) ^ 0x80000000;
    local_20 = *(undefined8 *)(*(int *)(param_1 + 0xf4) + 0x48);
    local_18 = *(undefined8 *)(*(int *)(param_1 + 0xf4) + 0x50);
    local_10 = *(undefined8 *)(*(int *)(param_1 + 0xf4) + 0x58);
    FUN_004c8800(&local_48,0x3e4ccccd);
  }
  FUN_0083e885();
  return;
}

