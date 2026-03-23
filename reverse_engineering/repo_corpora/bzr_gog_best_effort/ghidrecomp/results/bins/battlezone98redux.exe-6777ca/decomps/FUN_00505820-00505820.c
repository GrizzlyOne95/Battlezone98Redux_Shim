
void FUN_00505820(int *param_1,undefined4 param_2)

{
  switch(*(byte *)(*param_1 + -1) & 0x1f) {
  case 0:
    FUN_00505710(param_1,param_2);
    break;
  case 1:
    FUN_00505740(param_1,param_2);
    break;
  case 2:
    FUN_00505770(param_1,param_2);
    break;
  case 4:
    FUN_005057b0(param_1,param_2);
    break;
  case 8:
    FUN_005057e0(param_1,param_2);
  }
  return;
}

