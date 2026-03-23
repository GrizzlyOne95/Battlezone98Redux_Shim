
void FUN_00573bb0(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 local_2c;
  undefined2 local_1c;
  undefined4 local_1a;
  undefined4 local_16;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = 0x736e;
  local_1a = FUN_004b9a90();
  if (param_1 == 0) {
    local_2c = 0;
  }
  else {
    local_2c = (**(code **)(*(int *)(param_1 + 0x18) + 4))();
  }
  local_16 = local_2c;
  sVar1 = FUN_004b9800();
  if (sVar1 != 0) {
    iVar2 = FUN_007659f0();
    if (iVar2 != 0) {
      FUN_007596b0(sVar1,&local_1c,10,1);
    }
  }
  FUN_0083e885();
  return;
}

