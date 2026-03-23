
undefined4 __thiscall
FUN_00805290(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_10 [5];
  undefined1 local_b [3];
  undefined1 local_8 [2];
  undefined1 local_6;
  undefined1 local_5;
  
  uVar2 = param_4;
  uVar3 = param_5;
  uVar1 = FUN_007e3090(param_3,param_4,param_5,param_1);
  uVar2 = FUN_007e7820(&local_6,uVar1,uVar2,uVar3);
  uVar3 = FUN_007e6f80(local_b,uVar2);
  uVar2 = param_5;
  uVar3 = FUN_007e3040(param_3,param_4,param_5,uVar3);
  uVar2 = FUN_00805fa0(local_8,uVar3,param_4,uVar2);
  FUN_00806060(local_10,uVar2);
  local_5 = 0;
  FUN_00806080(param_2,local_10,param_5);
  return param_2;
}

