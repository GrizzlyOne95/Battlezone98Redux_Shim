
void FUN_00787de0(int param_1,undefined4 param_2)

{
  uint uVar1;
  void *pvVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  undefined4 local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084d0bc;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  if (param_1 != 0) {
    local_14 = 0x220;
    if (DAT_009454e2 != '\0') {
      local_14 = 800;
    }
    DAT_009454e0 = 0;
    pvVar2 = operator_new(0x15c);
    local_8 = 0;
    if (pvVar2 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007c1ef0("GameAlert",0,0,0x44160000,0x43610000,local_14,param_1);
    }
    local_8 = 0xffffffff;
    DAT_009454d8 = local_1c;
    FUN_005df1f0(param_2);
    uVar3 = FUN_0081cb40("multi_popup","ok_button",uVar1);
    FUN_007c2430(uVar3);
    uVar3 = FUN_0041f870();
    FUN_007c2400(uVar3);
    FUN_007c23c0(FUN_00787cc0);
    if (DAT_009454e2 != '\0') {
      uVar3 = FUN_0081cb40("multi_popup","cancel_button");
      FUN_007c2450(uVar3);
      FUN_007c23e0(FUN_00787d50);
    }
    FUN_007d2110(DAT_009454d8,0);
  }
  ExceptionList = local_10;
  return;
}

