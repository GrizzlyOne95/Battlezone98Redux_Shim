
undefined4 FUN_0041eba0(undefined4 param_1)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_0041fc00(local_8);
  FUN_0041fc60(local_c);
  do {
    cVar1 = FID_conflict_operator__(local_c);
    if (cVar1 == '\0') {
      return 3;
    }
    iVar2 = FUN_00422220();
    cVar1 = FUN_00427310(param_1,iVar2 + 0x2c);
    if (cVar1 == '\0') {
      iVar2 = FUN_00422220();
      cVar1 = FUN_00427310(param_1,iVar2 + 0x48);
      if (cVar1 != '\0') goto LAB_0041ec17;
    }
    else {
LAB_0041ec17:
      uVar3 = FUN_00422220("rightjoy");
      cVar1 = FUN_00427270(uVar3);
      if (cVar1 != '\0') {
        iVar2 = FUN_0041c1d0();
        if (iVar2 == 0) {
          return 0;
        }
        return 1;
      }
      uVar3 = FUN_00422220("leftjoy");
      cVar1 = FUN_00427270(uVar3);
      if (cVar1 != '\0') {
        iVar2 = FUN_0041c1d0();
        if (iVar2 == 0) {
          return 1;
        }
        return 0;
      }
      uVar3 = FUN_00422220(&DAT_008713d4);
      cVar1 = FUN_00427270(uVar3);
      if (cVar1 != '\0') {
        return 2;
      }
    }
    FUN_00422240();
  } while( true );
}

