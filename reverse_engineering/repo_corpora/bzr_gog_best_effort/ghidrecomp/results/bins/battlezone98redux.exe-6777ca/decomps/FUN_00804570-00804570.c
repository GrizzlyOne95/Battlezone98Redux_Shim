
undefined4 FUN_00804570(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_50 [36];
  undefined1 local_2c [39];
  undefined1 local_5;
  
  FUN_007e0b60(&local_5,param_2,param_3,param_4);
  puVar3 = &local_5;
  uVar2 = param_4;
  uVar1 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_008045f0(local_2c,uVar1,puVar3,uVar2);
  puVar3 = local_2c;
  uVar2 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00804620(local_50,uVar2,puVar3,param_4);
  FUN_007fe5d0(local_50);
  return param_1;
}

