
undefined4 FUN_00805170(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_24 [12];
  undefined1 local_18 [8];
  undefined1 local_10 [9];
  undefined1 local_7 [2];
  undefined1 local_5;
  
  uVar2 = param_3;
  uVar3 = param_4;
  uVar1 = FUN_007e31c0(param_2,param_3,param_4);
  uVar2 = FUN_00805fd0(local_10,uVar1,uVar2,uVar3);
  uVar3 = FUN_007e2ff0(local_18,uVar2);
  uVar2 = param_4;
  uVar3 = FUN_007e3040(param_2,param_3,param_4,uVar3);
  uVar2 = FUN_00805fa0(local_7,uVar3,param_3,uVar2);
  FUN_00801320(local_24,uVar2);
  local_5 = 0;
  FUN_00806000(param_1,local_24,param_4);
  return param_1;
}

