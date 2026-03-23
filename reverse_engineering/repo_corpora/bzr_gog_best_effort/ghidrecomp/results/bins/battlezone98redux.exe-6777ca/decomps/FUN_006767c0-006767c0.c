
void FUN_006767c0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = FUN_00669260(param_2,param_1);
  if (cVar1 != '\0') {
    iter_swap<>(param_2,param_1);
  }
  cVar1 = FUN_00669260(param_3,param_2);
  if (cVar1 != '\0') {
    iter_swap<>(param_3,param_2);
    cVar1 = FUN_00669260(param_2,param_1);
    if (cVar1 != '\0') {
      iter_swap<>(param_2,param_1);
    }
  }
  return;
}

