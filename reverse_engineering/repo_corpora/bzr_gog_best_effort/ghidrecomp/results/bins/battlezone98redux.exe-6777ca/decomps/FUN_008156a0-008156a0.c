
undefined4 FUN_008156a0(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 extraout_ECX;
  undefined1 *puVar3;
  undefined1 local_1c [8];
  undefined1 local_14 [4];
  char local_10;
  undefined1 local_5;
  
  local_5 = 0;
  puVar3 = local_1c;
  uVar1 = FUN_00422f60(param_3);
  uVar2 = extraout_ECX;
  FUN_007d6f20(&param_2);
  FUN_00815720(local_14,uVar2,uVar1,puVar3);
  if (local_10 == '\0') {
    FUN_006cc240(local_14);
  }
  else {
    puVar3 = local_1c;
    uVar2 = FUN_00417780(param_3,puVar3);
    FUN_00815a90(param_1,uVar2,puVar3);
  }
  return param_1;
}

