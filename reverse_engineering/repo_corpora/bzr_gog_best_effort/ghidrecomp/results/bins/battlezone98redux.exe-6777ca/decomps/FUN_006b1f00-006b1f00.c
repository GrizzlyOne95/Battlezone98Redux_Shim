
void FUN_006b1f00(undefined4 *param_1)

{
  char cVar1;
  undefined1 local_14 [8];
  int local_c;
  int local_8;
  
  cVar1 = FUN_006b1390(param_1);
  if (cVar1 != '\0') {
    local_c = FUN_006b20f0(local_8 + 8,0,0);
    if (local_c != 0) {
      FUN_006b0c30(*param_1,param_1 + 4,1);
    }
  }
  FUN_004fbb60();
  FUN_006ae9c0(*param_1,param_1 + 1,1,local_14);
  *param_1 = 0xffffffff;
  *(undefined1 *)(param_1 + 1) = 0;
  std::shared_ptr<struct_Concurrency::details::_ExceptionHolder>::reset
            ((shared_ptr<struct_Concurrency::details::_ExceptionHolder> *)(param_1 + 2));
  return;
}

