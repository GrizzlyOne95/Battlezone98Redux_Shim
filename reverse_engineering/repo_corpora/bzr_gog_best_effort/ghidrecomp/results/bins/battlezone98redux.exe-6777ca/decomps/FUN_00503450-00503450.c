
undefined4 FUN_00503450(undefined4 param_1)

{
  undefined4 uVar1;
  int iVar2;
  int local_c;
  
  uVar1 = FUN_004ff750(param_1,1);
  iVar2 = FUN_0082d490(param_1,2,uVar1);
  if (iVar2 < 1) {
    local_c = 1;
  }
  else {
    local_c = FUN_0082d2e8(param_1,2);
  }
  FUN_005caff0(uVar1,local_c != 0);
  return 0;
}

