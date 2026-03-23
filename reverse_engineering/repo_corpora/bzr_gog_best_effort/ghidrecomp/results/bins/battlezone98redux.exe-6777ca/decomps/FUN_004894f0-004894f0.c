
uint FUN_004894f0(void)

{
  char cVar1;
  undefined4 uVar2;
  int *piVar3;
  undefined1 local_c [4];
  undefined1 local_8 [4];
  
  FUN_00424640(local_8);
  FID_conflict_begin(local_c);
  do {
    cVar1 = FUN_00420f10(local_c);
    if (cVar1 == '\0') {
      return 1;
    }
    uVar2 = FUN_004237d0(&DAT_0094fef8);
    cVar1 = FUN_00427310(uVar2);
    if (cVar1 == '\0') {
      uVar2 = FUN_004237d0();
      piVar3 = (int *)FUN_0048a3b0(uVar2);
      if (0 < *piVar3) {
LAB_004895ae:
        return (uint)piVar3 & 0xffffff00;
      }
      uVar2 = FUN_004237d0();
      piVar3 = (int *)FUN_0048a3b0(uVar2);
      if (0 < piVar3[1]) goto LAB_004895ae;
    }
    else {
      uVar2 = FUN_004237d0();
      piVar3 = (int *)FUN_0048a3b0(uVar2);
      if (3 < *piVar3) {
LAB_00489577:
        return (uint)piVar3 & 0xffffff00;
      }
      uVar2 = FUN_004237d0();
      piVar3 = (int *)FUN_0048a3b0(uVar2);
      if (3 < piVar3[1]) goto LAB_00489577;
    }
    FUN_00422190();
  } while( true );
}

