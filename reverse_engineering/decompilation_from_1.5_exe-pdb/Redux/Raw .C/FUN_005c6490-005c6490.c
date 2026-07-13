
undefined4 __thiscall FUN_005c6490(int *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int local_8;
  
  uVar3 = param_2;
  cVar1 = (**(code **)(*param_1 + 0x60))(param_2);
  if (cVar1 == '\0') {
    uVar3 = 0;
  }
  else {
    local_8 = FUN_005b50e0(uVar3,param_2);
    FUN_005b50a0(local_8);
    iVar2 = FUN_00572a70();
    if (iVar2 != 0) {
      local_8 = local_8 << 1;
    }
    FUN_005e1010(local_8);
    uVar3 = 1;
  }
  return uVar3;
}

