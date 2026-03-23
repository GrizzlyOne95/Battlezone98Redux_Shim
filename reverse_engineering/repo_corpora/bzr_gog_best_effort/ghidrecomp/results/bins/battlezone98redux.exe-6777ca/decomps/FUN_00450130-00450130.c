
void FUN_00450130(int param_1,int param_2,undefined4 param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008469b0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    construct<>(param_1,param_3);
    param_1 = param_1 + 4;
  }
  FUN_004501c5();
  return;
}

