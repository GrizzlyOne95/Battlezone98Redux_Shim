
undefined1 FUN_004ce400(undefined4 param_1,int param_2,uint param_3)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  int iVar4;
  uint local_c;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,0,param_3);
    FUN_004ce0b0();
    iVar4 = sscanf(DAT_0260db08,"%*s =");
    uVar1 = iVar4 == 0;
    FUN_004ce120();
    FUN_004ce180();
    if ((bool)uVar1) {
      for (local_c = 0; local_c < param_3; local_c = local_c + 1) {
        uVar2 = FUN_004ce180();
        uVar3 = FUN_004ce180();
        uVar2 = FUN_004ce390(uVar2,uVar3);
        *(undefined1 *)(param_2 + local_c) = uVar2;
      }
      FUN_004ce100();
    }
  }
  else {
    uVar1 = FUN_004cdda0(0,param_3,param_2);
  }
  return uVar1;
}

