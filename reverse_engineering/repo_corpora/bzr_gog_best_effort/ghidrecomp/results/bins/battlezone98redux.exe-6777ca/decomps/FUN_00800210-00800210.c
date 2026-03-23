
undefined4 FUN_00800210(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined1 local_5c [32];
  undefined1 local_3c [28];
  undefined1 local_20 [28];
  
  uVar1 = FUN_007e1640(param_2,param_3,param_4);
  FUN_007fe670(uVar1);
  puVar3 = local_20;
  uVar1 = param_4;
  uVar2 = FUN_007e3090(param_2,puVar3,param_4);
  FUN_00800500(local_3c,uVar2,puVar3,uVar1);
  puVar3 = local_3c;
  uVar1 = FUN_007e3040(param_2,puVar3,param_4);
  FUN_00800530(local_5c,uVar1,puVar3,param_4);
  FUN_007fe2e0(local_5c);
  return param_1;
}

