
void FUN_007be670(int param_1,int param_2,int param_3)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00861b70;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_1 != param_2; param_1 = param_1 + 8) {
    construct<>(param_3,param_1);
    param_3 = param_3 + 8;
  }
  FUN_007be707();
  return;
}

