
undefined4 * __thiscall FUN_005bce80(undefined4 *param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084c648;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  FUN_004802c0(param_2,param_3);
  local_8 = 0;
  *param_1 = Rocket::vftable;
  if ((((*(int *)(param_3 + 0xa8) < 1) || (*(int *)(param_3 + 0xac) < 1)) ||
      (*(float *)(param_3 + 0xb0) <= 0.0)) || (*(float *)(param_3 + 0xa0) <= 0.0)) {
    param_1[0x3b] = 0;
  }
  else {
    uVar1 = FUN_00491000(*(undefined4 *)(param_3 + 0xa8),*(undefined4 *)(param_3 + 0xac),
                         *(undefined4 *)(param_3 + 0xb0),*(undefined4 *)(param_3 + 0xa0),0x3f800000)
    ;
    param_1[0x3b] = uVar1;
  }
  ExceptionList = local_10;
  return param_1;
}

