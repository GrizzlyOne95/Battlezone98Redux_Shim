
void __fastcall FUN_007d7170(undefined4 param_1)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00862d5b;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  FUN_007d7220(DAT_008e7000 ^ (uint)&stack0xfffffffc,param_1);
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  return;
}

