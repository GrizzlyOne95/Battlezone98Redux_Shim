
undefined4 FUN_006db740(undefined4 param_1,undefined4 param_2,undefined4 param_3,byte param_4)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 extraout_var;
  
  uVar1 = (uint)param_4;
  FUN_006e1cb0(&param_3);
  uVar2 = FUN_006e1c80(extraout_var,uVar1);
  puVar3 = (undefined4 *)FUN_00447eb0(param_2);
  FUN_006e1c50(*puVar3,uVar2);
  return param_1;
}

