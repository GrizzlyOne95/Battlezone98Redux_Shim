
undefined4 *
FUN_0081d370(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  uVar1 = FUN_00417780(param_4);
  uVar2 = FUN_00417780(param_3,uVar1);
  FUN_0081d4a0(uVar2,uVar1);
  puVar3 = (undefined4 *)FUN_0044fd20(local_c);
  uVar1 = FUN_00438b60(*puVar3);
  puVar3 = (undefined4 *)FUN_0081d4f0(local_14,uVar1);
  *param_1 = *puVar3;
  return param_1;
}

