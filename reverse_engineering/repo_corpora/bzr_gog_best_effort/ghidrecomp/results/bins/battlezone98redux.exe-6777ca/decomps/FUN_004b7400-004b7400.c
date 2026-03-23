
undefined4 * FUN_004b7400(undefined4 *param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined1 local_c [4];
  undefined4 local_8;
  
  local_8 = param_2;
  FUN_0042da80();
  while( true ) {
    cVar1 = FUN_00420f10(&stack0x0000000c);
    if (cVar1 == '\0') break;
    puVar2 = (undefined4 *)FUN_0042de50();
    cVar1 = FUN_004b6400(*puVar2);
    if (cVar1 == '\0') {
      uVar3 = FUN_0042de50();
      puVar2 = (undefined4 *)FUN_00417780(uVar3);
      FUN_00438c10(local_c,0);
      puVar4 = (undefined4 *)FUN_0042de50();
      *puVar4 = *puVar2;
    }
    FUN_0042da80();
  }
  *param_1 = local_8;
  return param_1;
}

