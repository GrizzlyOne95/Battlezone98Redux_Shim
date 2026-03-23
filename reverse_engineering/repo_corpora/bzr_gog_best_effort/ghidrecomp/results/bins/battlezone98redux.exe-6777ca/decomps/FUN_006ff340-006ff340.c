
undefined4 FUN_006ff340(undefined4 param_1)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 in_stack_00000040;
  undefined4 local_44 [7];
  undefined4 local_28 [7];
  undefined4 local_c;
  undefined1 local_7;
  undefined1 local_6;
  undefined1 local_5;
  
  puVar4 = (undefined4 *)&stack0x00000008;
  puVar5 = local_28;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  do {
    cVar1 = FUN_006f6a30(local_28,&stack0x00000024);
    if (cVar1 == '\0') {
      local_7 = 0;
      make_pair<>(param_1,&stack0x00000024,&local_7);
      return param_1;
    }
    puVar4 = local_28;
    puVar5 = local_44;
    for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
      *puVar5 = *puVar4;
      puVar4 = puVar4 + 1;
      puVar5 = puVar5 + 1;
    }
    local_c = in_stack_00000040;
    while( true ) {
      cVar1 = FID_conflict_operator__(&stack0x00000044);
      if (cVar1 != '\0') {
        local_5 = 1;
        make_pair<>(param_1,local_28,&local_5);
        return param_1;
      }
      cVar1 = FUN_00700d50(local_44,&stack0x00000024);
      if (cVar1 != '\0') break;
      pcVar2 = (char *)FUN_00700d10();
      cVar1 = *pcVar2;
      pcVar2 = (char *)FUN_00421ec0();
      if (cVar1 != *pcVar2) goto LAB_006ff357;
      FUN_00700d30();
      FUN_004f5330();
    }
    cVar1 = FID_conflict_operator__(&stack0x00000040);
    if (cVar1 != '\0') {
      local_6 = 0;
      make_pair<>(param_1,local_28,&local_6);
      return param_1;
    }
LAB_006ff357:
    FUN_00700d30();
  } while( true );
}

