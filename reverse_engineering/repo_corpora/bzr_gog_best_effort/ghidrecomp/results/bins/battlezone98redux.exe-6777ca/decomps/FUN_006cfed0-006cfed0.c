
void __fastcall FUN_006cfed0(int param_1)

{
  uint uVar1;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  puStack_c = &LAB_00852f2f;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_8 = 5;
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_1 + 0x50));
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_1 + 0x58));
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_1 + 0x60));
  if (((*(int *)(param_1 + 0x78) != 0) && (*(char *)(param_1 + 0x4c) == '\0')) &&
     (*(int *)(param_1 + 0x48) != 0)) {
    FUN_006cd0e0(1);
  }
  local_8._0_1_ = 4;
  FUN_006ca8c0(uVar1);
  local_8._0_1_ = 3;
  FUN_006ca8c0();
  local_8._0_1_ = 2;
  FUN_006ca8c0();
  local_8._0_1_ = 1;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x30));
  local_8 = (uint)local_8._1_3_ << 8;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)(param_1 + 0x18));
  local_8 = 0xffffffff;
  FUN_006d1210();
  ExceptionList = local_10;
  return;
}

