
void FUN_0062cba0(void)

{
  int iVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  int local_8;
  
  uVar5 = 0xffffffff;
  uVar4 = 0xffffffff;
  cVar2 = FUN_0062c170(0xffffffff,0xffffffff);
  if (cVar2 == '\0') {
    uVar5 = uVar5 ^ 0x14;
  }
  cVar2 = FUN_0062c180(uVar4,uVar5);
  if (cVar2 == '\0') {
    uVar4 = uVar4 ^ 0x14;
  }
  for (local_8 = 0; local_8 < DAT_00920c7c; local_8 = local_8 + 1) {
    iVar1 = *(int *)(&DAT_02a1f570 + local_8 * 0xe4);
    if (iVar1 != 0) {
      iVar3 = FUN_0062e000(iVar1,uVar4);
      if (iVar3 == 1) {
        FUN_0062cb60(iVar1,uVar5);
      }
      else {
        FUN_0062cb60(iVar1,uVar4);
      }
    }
  }
  return;
}

