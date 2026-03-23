
undefined4 FUN_0062b6b0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float10 fVar4;
  undefined4 uVar5;
  int local_c;
  int local_8;
  
  uVar5 = 0;
  local_c = 0;
  local_8 = 0;
  while ((local_8 < 0x200 && (local_c < DAT_00920c58))) {
    if ((*(int *)(&DAT_02a17498 + local_8 * 0x20) != 0) &&
       (local_c = local_c + 1, *(int *)(&DAT_02a17498 + local_8 * 0x20) == 1)) {
      iVar1 = *(int *)(&DAT_02a1749c + local_8 * 0x20);
      iVar2 = *(int *)(iVar1 + 0x38);
      if ((*(int *)(iVar1 + 0x3c) == 0) ||
         ((iVar2 == 0 || (iVar3 = FUN_0062c890(iVar2,uVar5), iVar3 != *(int *)(iVar1 + 0x3c))))) {
        *(undefined4 *)(&DAT_02a174b0 + local_8 * 0x20) = 0;
        *(undefined4 *)(&DAT_02a17498 + local_8 * 0x20) = 3;
      }
      else if (*(int *)(&DAT_02a174b0 + local_8 * 0x20) < 1) {
        *(undefined4 *)(&DAT_02a174b0 + local_8 * 0x20) = 0;
        *(undefined4 *)(&DAT_02a17498 + local_8 * 0x20) = 2;
      }
      else {
        fVar4 = (float10)FUN_0062b4c0(&DAT_02a17498 + local_8 * 0x20);
        FUN_0062b3c0(iVar2,uVar5,&DAT_02a17498 + local_8 * 0x20,(float)fVar4);
      }
    }
    local_8 = local_8 + 1;
  }
  return 0;
}

