
int __thiscall FUN_0077cb40(int param_1,undefined4 param_2,undefined4 param_3)

{
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00846933;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  allocator<>(param_2);
  FUN_0077cbe0(param_3);
  local_8 = 0;
  FUN_00423c20(param_3);
  FUN_0044f100(&local_11);
  local_8 = CONCAT31(local_8._1_3_,1);
  *(undefined4 *)(param_1 + 0x1c) = 0x3f800000;
  FUN_0044f090(8);
  ExceptionList = local_10;
  return param_1;
}

