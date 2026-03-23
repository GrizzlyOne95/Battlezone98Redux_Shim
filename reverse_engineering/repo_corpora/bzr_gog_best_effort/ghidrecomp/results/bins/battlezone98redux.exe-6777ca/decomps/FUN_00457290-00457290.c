
undefined4 * __thiscall FUN_00457290(undefined4 *param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  float local_24;
  float local_20;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846e50;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  FUN_00448f90(param_2,param_3);
  local_8 = 0;
  *param_1 = TrailRenderClass::vftable;
  if (param_2 == 0) {
    param_1[0x5d] = 0;
    param_1[0x5f] = 0x7f7fffff;
    param_1[0x60] = 0;
    param_1[0x62] = 0;
  }
  else {
    uVar2 = FUN_00446460(param_1 + 0x15,0x811c9dc5,uVar1);
    FUN_00589430(param_1 + 0x25);
    local_8._0_1_ = 1;
    FUN_00589800(uVar2,0x5632f5da,param_1 + 0x5f,*(undefined4 *)(param_2 + 0x17c));
    FUN_00589800(uVar2,0x5ee6293f,param_1 + 0x5d,*(undefined4 *)(param_2 + 0x174));
    FUN_00589800(uVar2,0xa133566,param_1 + 0x60,*(undefined4 *)(param_2 + 0x180));
    FUN_00589800(uVar2,0x5a45d6ff,param_1 + 0x61,*(undefined4 *)(param_2 + 0x184));
    if ((float)param_1[0x5d] <= 0.0) {
      local_20 = 0.0;
    }
    else {
      local_20 = 1.0 / (float)param_1[0x5d];
    }
    param_1[0x5e] = local_20;
    if ((float)param_1[0x5f] <= 0.0) {
      local_24 = 0.0;
    }
    else {
      local_24 = 1.0 / (float)param_1[0x5f];
    }
    param_1[0x62] = local_24;
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00589530();
  }
  ExceptionList = local_10;
  return param_1;
}

