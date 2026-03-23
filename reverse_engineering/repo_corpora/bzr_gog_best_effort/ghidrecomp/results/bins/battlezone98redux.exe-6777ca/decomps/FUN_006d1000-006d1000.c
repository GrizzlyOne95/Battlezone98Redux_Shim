
undefined4 FUN_006d1000(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_var;
  undefined4 uVar4;
  undefined1 local_10 [8];
  undefined4 local_8;
  
  FUN_006b2520(*(undefined2 *)(param_2 + 3));
  iVar1 = param_2[4] + 1;
  uVar3 = extraout_var;
  FUN_006b26a0(iVar1);
  iVar2 = param_2[5] + 0x76c;
  FUN_006b25f0(iVar2);
  FUN_006b26e0(iVar2,iVar1,uVar3);
  uVar4 = 0;
  uVar3 = 0;
  FUN_006b28f0(param_2[2],param_2[1],*param_2,0,0);
  FUN_006b29d0(local_10);
  FUN_006b2960(local_8,uVar3,uVar4);
  return param_1;
}

