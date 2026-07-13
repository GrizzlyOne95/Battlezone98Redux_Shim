
undefined4 FUN_00805200(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_1c [8];
  undefined1 local_14 [10];
  undefined1 local_a [4];
  undefined1 local_6;
  undefined1 local_5;
  
  uVar2 = param_3;
  uVar3 = param_4;
  uVar1 = FUN_007e31c0(param_2,param_3,param_4);
  uVar2 = FUN_00801340(&local_6,uVar1,uVar2,uVar3);
  uVar3 = FUN_007e7390(local_a,uVar2);
  uVar2 = param_4;
  uVar3 = FUN_007e3040(param_2,param_3,param_4,uVar3);
  uVar2 = FUN_007e2fc0(local_14,uVar3,param_3,uVar2);
  FUN_007e7960(local_1c,uVar2);
  local_5 = 0;
  FUN_00806030(param_1,local_1c,param_4);
  return param_1;
}

