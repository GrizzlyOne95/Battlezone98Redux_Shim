
void __thiscall FUN_00734be0(int param_1,undefined4 *param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_20;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085a1e1;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar2 = FUN_006ca480(*param_2,DAT_008e7000 ^ (uint)&stack0xfffffffc);
  if (iVar2 == 0) {
    FUN_00417780(param_3);
    uVar3 = FUN_00717ce0(200,param_3);
    local_8 = 1;
    iVar2 = forward<>(200,uVar3);
    local_8._0_1_ = 2;
    if (iVar2 == 0) {
      local_20 = 0;
    }
    else {
      local_20 = FUN_00735960(param_3);
    }
    local_8._0_1_ = 1;
    cVar1 = FUN_006b44f0(param_2,local_20);
    if (cVar1 != '\0') {
      FUN_006ca4c0(*param_2);
      local_8._0_1_ = 4;
      uVar3 = FUN_004fbb60(0);
      FUN_007359d0(*(undefined4 *)(param_1 + 0x14),local_20,uVar3);
      local_8._0_1_ = 3;
      FUN_006b4030();
      local_8 = CONCAT31(local_8._1_3_,1);
      FUN_006ca540();
    }
    local_8 = 0xffffffff;
    FUN_00735af0();
  }
  else {
    FUN_006ace00(0);
    local_8 = 0;
    FUN_007362e0(param_3,param_3);
    local_8 = 0xffffffff;
    FUN_006ace20();
  }
  ExceptionList = local_10;
  return;
}

