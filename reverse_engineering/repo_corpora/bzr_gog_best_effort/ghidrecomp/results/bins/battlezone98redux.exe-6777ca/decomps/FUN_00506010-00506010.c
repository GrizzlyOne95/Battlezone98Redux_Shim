
void FUN_00506010(int *param_1,undefined4 param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)*param_1;
  *param_1 = *param_1 + 1;
  switch((int)(uint)bVar1 >> 5) {
  case 0:
    FUN_00505380(param_1,param_2);
    break;
  case 1:
    FUN_005053d0(param_1,param_2);
    break;
  case 2:
    FUN_00505490(param_1,param_2);
    break;
  case 3:
    FUN_00505820(param_1,param_2);
    break;
  case 4:
    FUN_005059b0(param_1,param_2);
    break;
  case 5:
    FUN_00505b50(param_1,param_2);
    break;
  case 7:
    FUN_00505db0(param_1,param_2);
  }
  return;
}

