
undefined4 __fastcall FUN_0043d3e0(undefined4 param_1)

{
  int iVar1;
  
  if (DAT_00915640 != 0) {
    do {
      do {
        if (DAT_00915640 == 0) {
          return 0;
        }
        DAT_00915640 = FUN_0043d540(DAT_00915640,param_1);
      } while ((DAT_00915640 == 0) ||
              (iVar1 = FUN_0043d170(*(undefined4 *)(DAT_00915640 + 0x10)), iVar1 != 0));
      iVar1 = FUN_0043d460(DAT_00915640);
      *(int *)(DAT_00915640 + 0x14) = iVar1;
      param_1 = 0;
    } while (iVar1 == 0);
  }
  return 0;
}

