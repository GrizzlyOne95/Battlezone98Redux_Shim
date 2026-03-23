
undefined4 FUN_00836a0a(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  float10 fVar3;
  undefined8 local_c;
  
  iVar1 = FUN_0082c8f6();
  fVar3 = (float10)FUN_0082ba89(param_1);
  local_c = (double)fVar3;
  iVar2 = 2;
  if (1 < iVar1) {
    do {
      fVar3 = (float10)FUN_0082ba89(param_1,iVar2);
      if (local_c < (double)fVar3) {
        local_c = (double)fVar3;
      }
      iVar2 = iVar2 + 1;
    } while (iVar2 <= iVar1);
  }
  FUN_0082cd58(param_1,local_c);
  return 1;
}

