
undefined4 FUN_005cc020(undefined4 param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  undefined8 local_10;
  int local_8;
  
  local_8 = FUN_00460fc0(param_1);
  if (local_8 == 0) {
    uVar1 = 0;
  }
  else {
    local_10 = FUN_0045c460(*param_2,param_2[1],param_2[2]);
    uVar1 = FUN_005cbf30(local_8,&local_10);
  }
  return uVar1;
}

