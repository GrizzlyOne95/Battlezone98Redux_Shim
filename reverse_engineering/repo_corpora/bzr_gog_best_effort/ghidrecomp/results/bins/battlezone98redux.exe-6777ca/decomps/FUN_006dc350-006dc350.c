
undefined4
FUN_006dc350(undefined4 param_1,undefined4 param_2,undefined4 param_3,byte param_4,byte param_5)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  
  uVar1 = (uint)param_5;
  uVar4 = (uint)param_4;
  uVar5 = uVar4;
  FUN_006e1cb0(&param_3);
  uVar2 = FUN_006e2780(uVar4,uVar5,uVar1);
  puVar3 = (undefined4 *)FUN_00447eb0(param_2);
  FUN_006e1c50(*puVar3,uVar2);
  return param_1;
}

