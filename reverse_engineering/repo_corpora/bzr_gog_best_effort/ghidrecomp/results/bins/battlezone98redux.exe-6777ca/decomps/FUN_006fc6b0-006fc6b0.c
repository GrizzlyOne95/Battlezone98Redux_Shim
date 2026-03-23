
undefined4 __thiscall
FUN_006fc6b0(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int local_c;
  
  do {
    cVar1 = FID_conflict_operator__(&param_4);
    if (cVar1 == '\0') {
      FUN_006ff2c0(param_4,param_4);
      return param_2;
    }
    cVar1 = FUN_0070c630(param_1);
    if (cVar1 != '\0') {
      FUN_006ff2c0(param_4,param_4);
      return param_2;
    }
    uVar4 = param_3;
    for (local_c = get(param_3,param_3);
        (cVar1 = FID_conflict_operator__(&param_4), cVar1 != '\0' &&
        (iVar2 = FUN_00416410(), local_c != iVar2)); local_c = local_c + 1) {
      iVar2 = local_c;
      uVar3 = FUN_00421ec0(local_c);
      cVar1 = FUN_00708c90(uVar3,iVar2);
      if (cVar1 == '\0') break;
      FUN_004f5330();
    }
    iVar2 = FUN_00416410();
    if (local_c == iVar2) {
      FUN_006ff2c0(param_3,uVar4);
      return param_2;
    }
    FUN_004f5330();
  } while( true );
}

