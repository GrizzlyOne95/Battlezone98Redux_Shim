
undefined4 FUN_00505ea0(int *param_1,uint param_2,undefined4 param_3,int param_4)

{
  int iVar1;
  undefined4 uVar2;
  int local_8;
  
  if (param_4 < 0) {
    iVar1 = FUN_0082c8f6(param_3);
    param_4 = param_4 + 1 + iVar1;
  }
  if (*param_1 + 1U < param_2) {
    local_8 = FUN_0082d490(param_3,param_4);
    if (local_8 == -1) {
      local_8 = 0;
    }
    *(char *)*param_1 = (char)(local_8 << 5);
    *param_1 = *param_1 + 1;
    switch(local_8) {
    case 0:
      uVar2 = operator==<>(param_1,param_2,param_3,param_4);
      break;
    case 1:
      uVar2 = FUN_005053a0(param_1,param_2,param_3,param_4);
      break;
    case 2:
      uVar2 = FUN_00505410(param_1,param_2,param_3,param_4);
      break;
    case 3:
      uVar2 = FUN_00505630(param_1,param_2,param_3,param_4);
      break;
    case 4:
      uVar2 = FUN_005058d0(param_1,param_2,param_3,param_4);
      break;
    case 5:
      uVar2 = FUN_00505a10(param_1,param_2,param_3,param_4);
      break;
    default:
      uVar2 = 1;
      break;
    case 7:
      uVar2 = FUN_00505bf0(param_1,param_2,param_3,param_4);
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

