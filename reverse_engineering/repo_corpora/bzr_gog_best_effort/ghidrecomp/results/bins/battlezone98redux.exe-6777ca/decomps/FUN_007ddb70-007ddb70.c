
void __thiscall FUN_007ddb70(int param_1,int param_2)

{
  undefined1 local_34 [32];
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00863428;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  if (param_2 != param_1) {
    local_14 = param_1;
    FUN_00422170(DAT_008e7000 ^ (uint)&stack0xfffffffc);
    local_8 = 0;
    FUN_007ddf00(local_14);
    FUN_007ddf00(param_2);
    FUN_007ddf00(local_34);
    local_8 = 0xffffffff;
    FUN_007d82e0();
  }
  ExceptionList = local_10;
  return;
}

