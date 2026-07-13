
void __fastcall FUN_006cbaa0(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852a70;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_006d08b0(0x400,"set_fail_handler");
  FUN_006d1110(param_1 + 0x1d0);
  local_8._0_1_ = 1;
  FID_conflict_operator_(&stack0x00000004);
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_006d1140(uVar1);
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

