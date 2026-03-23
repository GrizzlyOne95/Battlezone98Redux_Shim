
undefined4 FUN_00834647(undefined4 param_1)

{
  int iVar1;
  float10 fVar2;
  undefined8 local_c;
  
  local_c = 0.0;
  FUN_0082bbb2(param_1,1,5);
  FUN_0082cd45(param_1);
  iVar1 = FUN_0082cb08(param_1,1);
  while (iVar1 != 0) {
    FUN_0082d226(param_1,0xfffffffe);
    iVar1 = FUN_0082d490(param_1,0xffffffff);
    if (iVar1 == 3) {
      fVar2 = (float10)FUN_0082d3e1(param_1);
      if (local_c < (double)fVar2) {
        local_c = (double)fVar2;
      }
    }
    iVar1 = FUN_0082cb08();
  }
  FUN_0082cd58(param_1,local_c);
  return 1;
}

