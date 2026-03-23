
undefined4 * __thiscall
FUN_006efa60(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  puVar1 = (undefined4 *)FUN_00417780(param_2);
  *param_1 = *puVar1;
  uVar2 = FUN_00417780(param_6);
  uVar3 = FUN_00417780(param_5,uVar2);
  uVar4 = FUN_00417780(param_4,uVar3);
  uVar5 = FUN_00417780(param_3,uVar4);
  FUN_006fca00(uVar5,uVar4,uVar3,uVar2);
  return param_1;
}

