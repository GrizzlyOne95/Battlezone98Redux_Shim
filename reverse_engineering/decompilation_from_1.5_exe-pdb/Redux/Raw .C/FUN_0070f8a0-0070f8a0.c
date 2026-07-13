
undefined4 FUN_0070f8a0(undefined4 param_1)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  int extraout_var;
  int iVar4;
  
  while( true ) {
    cVar1 = FID_conflict_operator__(&stack0x00000008);
    if (cVar1 == '\0') {
      return 1;
    }
    iVar4 = extraout_var;
    puVar2 = (undefined1 *)FUN_00421ec0();
    iVar3 = FUN_006bb930(iVar4,iVar4 + 4,*puVar2);
    if (iVar3 == 1) break;
    FUN_004f5330(iVar3,iVar4,param_1);
  }
  return 0;
}

