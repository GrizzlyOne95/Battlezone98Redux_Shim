
undefined4 FUN_0058a8f0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_c [8];
  
  uVar1 = FUN_00417780(param_4);
  uVar2 = FUN_00417780(param_3,uVar1);
  uVar3 = FUN_00417780(param_2,uVar2);
  FUN_0058a9f0(uVar3,uVar2,uVar1);
  puVar4 = (undefined4 *)FUN_0044fd20(local_c);
  uVar1 = FUN_00438b60(*puVar4);
  FUN_0044fdc0(param_1,uVar1);
  return param_1;
}

