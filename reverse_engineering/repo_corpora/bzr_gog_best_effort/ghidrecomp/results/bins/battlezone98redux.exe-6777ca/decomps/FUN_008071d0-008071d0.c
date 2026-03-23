
undefined4 FUN_008071d0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_1c [8];
  undefined1 local_14 [9];
  undefined1 local_b [4];
  undefined1 local_7 [2];
  undefined1 local_5;
  
  uVar2 = param_3;
  uVar3 = param_4;
  uVar1 = FUN_007e3090(param_2,param_3,param_4);
  uVar2 = FUN_00807a10(local_b,uVar1,uVar2,uVar3);
  uVar3 = FUN_00807a40(local_14,uVar2);
  uVar2 = param_4;
  uVar3 = FUN_007e3040(param_2,param_3,param_4,uVar3);
  uVar2 = FUN_00805fa0(local_7,uVar3,param_3,uVar2);
  FUN_00807a60(local_1c,uVar2);
  local_5 = 0;
  FUN_00807a80(param_1,local_1c,param_4);
  return param_1;
}

