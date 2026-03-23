
void FUN_006d83f0(uint param_1)

{
  int iVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint local_14;
  uint local_c;
  
  do {
    iVar1 = param_1 * 2;
    local_c = iVar1 + 1;
    uVar3 = FUN_0046b240();
    if (uVar3 <= local_c) {
      return;
    }
    iVar4 = FUN_0046b240();
    if (iVar1 + 2 == iVar4) {
LAB_006d846a:
      local_14 = local_c;
    }
    else {
      uVar5 = FUN_005111d0(iVar1 + 2);
      uVar6 = FUN_005111d0(local_c);
      cVar2 = FUN_006d7bb0(uVar6,uVar5);
      if (cVar2 != '\0') goto LAB_006d846a;
      local_14 = iVar1 + 2;
    }
    uVar5 = FUN_005111d0(local_14);
    uVar6 = FUN_005111d0(param_1);
    cVar2 = FUN_006d7bb0(uVar6,uVar5);
    if (cVar2 != '\0') {
      return;
    }
    FUN_006d2300(param_1,local_14);
    param_1 = local_14;
  } while( true );
}

