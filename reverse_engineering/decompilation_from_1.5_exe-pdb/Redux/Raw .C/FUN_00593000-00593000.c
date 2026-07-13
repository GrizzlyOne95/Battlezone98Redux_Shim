
void FUN_00593000(int param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0084bff0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    destroy<>(param_1);
    param_1 = param_1 + 0x10;
  }
  FUN_00593091();
  return;
}

