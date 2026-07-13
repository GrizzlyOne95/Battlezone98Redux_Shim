
void FUN_007cf350(int param_1,int param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00862830;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    construct<>(param_1,param_3);
    param_1 = param_1 + 0x18;
  }
  FUN_007cf3e5();
  return;
}

