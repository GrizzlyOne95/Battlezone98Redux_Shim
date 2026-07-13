
void __thiscall
FUN_00806190(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            undefined4 param_5,undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  uVar1 = FUN_00806e80(param_5,param_6,param_1);
  puVar2 = (undefined4 *)FUN_00417780(uVar1);
  uVar1 = *puVar2;
  uVar3 = FUN_00806e60(param_4,param_6,uVar1);
  puVar2 = (undefined4 *)FUN_00417780(uVar3);
  uVar3 = *puVar2;
  uVar4 = FUN_00806e40(param_3,param_6,uVar3);
  puVar2 = (undefined4 *)FUN_00417780(uVar4);
  uVar4 = *puVar2;
  FUN_00806e20(param_2,param_6,uVar4);
  FUN_00806230(uVar4,uVar3,uVar1);
  return;
}

