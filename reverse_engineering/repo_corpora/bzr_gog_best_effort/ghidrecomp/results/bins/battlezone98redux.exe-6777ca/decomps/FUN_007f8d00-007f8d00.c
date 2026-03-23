
undefined4 FUN_007f8d00(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 local_14 [15];
  undefined1 local_5;
  
  local_5 = 0;
  uVar1 = FUN_007f7eb0(local_14,param_2,param_3,param_4);
  uVar1 = FUN_00417780(uVar1);
  uVar2 = max_size(param_2,param_3,param_4);
  uVar2 = FUN_00417780(uVar2,uVar1);
  FUN_007f9170(param_1,uVar2,uVar1);
  return param_1;
}

