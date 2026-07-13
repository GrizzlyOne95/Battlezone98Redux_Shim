
void __fastcall FUN_0078c9f0(int param_1)

{
  void *pvVar1;
  undefined4 local_1c;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_008477bc;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (*(int *)(param_1 + 0x164) == 0) {
    FUN_0078cdf0(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    pvVar1 = operator_new(0x144);
    local_8 = 0;
    if (pvVar1 == (void *)0x0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_007d1cc0("movie1",0,0,0x44f00000,0x44870000,0x101,param_1,0);
    }
    local_8 = 0xffffffff;
    *(undefined4 *)(param_1 + 0x164) = local_1c;
    FUN_007d3f20(10);
    FUN_0078c480(1);
    FUN_007d3850("credits.ogv",0);
    FUN_007d3dd0(0);
    FUN_007d2110(*(undefined4 *)(param_1 + 0x164),0);
  }
  ExceptionList = local_10;
  return;
}

