
void FUN_0082a2d0(int param_1,int param_2)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_00865290;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  for (; param_2 != 0; param_2 = param_2 + -1) {
    destroy<>(param_1);
    param_1 = param_1 + 0x1004;
  }
  FUN_0082a367();
  return;
}

