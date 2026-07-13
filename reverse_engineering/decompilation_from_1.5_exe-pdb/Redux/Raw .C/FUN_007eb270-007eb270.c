
undefined4 FUN_007eb270(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 local_a4 [36];
  undefined1 local_80 [32];
  undefined1 local_60 [60];
  undefined1 local_24 [31];
  undefined1 local_5;
  
  uVar2 = param_3;
  uVar3 = param_4;
  uVar1 = FUN_007e3090(param_2,param_3,param_4);
  uVar2 = FUN_007ebc90(local_80,uVar1,uVar2,uVar3);
  uVar3 = FUN_007ebcc0(local_a4,uVar2);
  uVar2 = param_4;
  uVar3 = FUN_007e3040(param_2,param_3,param_4,uVar3);
  uVar2 = FUN_007e3330(local_24,uVar3,param_3,uVar2);
  FUN_007ebce0(local_60,uVar2);
  local_5 = 0;
  FUN_007ebd00(param_1,local_60,param_4);
  return param_1;
}

