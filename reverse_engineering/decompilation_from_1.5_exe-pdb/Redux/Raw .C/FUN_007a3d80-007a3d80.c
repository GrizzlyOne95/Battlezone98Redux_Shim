
void __thiscall FUN_007a3d80(undefined4 param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  uint uVar6;
  uint uVar7;
  uint local_30;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084b778;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar6 = 0;
  local_14 = uVar2;
  if (param_2 != 0) {
    basic_string<>(param_2);
    local_8 = 0;
    uVar7 = uVar6;
    for (local_30 = 0; uVar3 = FUN_004170c0(), uVar6 = uVar7, local_30 < uVar3;
        local_30 = local_30 + 1) {
      puVar5 = local_2c;
      uVar4 = FUN_00752d30(local_30);
      cVar1 = FUN_00427310(uVar4,puVar5);
      uVar6 = local_30;
      if (cVar1 != '\0') break;
    }
    local_8 = 0xffffffff;
    ~basic_string<>(uVar2,uVar6);
  }
  FUN_007cafa0(uVar6);
  FUN_007a41c0(uVar2,uVar6,param_1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

