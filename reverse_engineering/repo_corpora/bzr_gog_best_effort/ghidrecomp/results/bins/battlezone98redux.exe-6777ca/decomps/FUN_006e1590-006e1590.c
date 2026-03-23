
void FUN_006e1590(void)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00851238;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FID_conflict_operator_(&stack0x00000004);
  local_8 = 0xffffffff;
  std::function<void___cdecl(void)>::~function<void___cdecl(void)>
            ((function<void___cdecl(void)> *)&stack0x00000004);
  ExceptionList = local_10;
  return;
}

