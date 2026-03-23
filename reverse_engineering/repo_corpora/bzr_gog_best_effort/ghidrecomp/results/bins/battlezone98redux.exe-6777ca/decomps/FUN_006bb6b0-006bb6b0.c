
void FUN_006bb6b0(void)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851308;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  uVar1 = FUN_006ab750(DAT_008e7000 ^ (uint)&stack0xfffffffc);
  FUN_006cadd0(uVar1);
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

