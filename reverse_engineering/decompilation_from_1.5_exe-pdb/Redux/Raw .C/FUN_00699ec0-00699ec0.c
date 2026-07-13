
undefined4 __thiscall
FUN_00699ec0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_006996c0(param_2,param_3,param_4,param_6,param_1);
  if (iVar1 == -1) {
    uVar2 = 0xffffffff;
  }
  else {
    uVar2 = FUN_00699980(param_5,param_6);
  }
  return uVar2;
}

