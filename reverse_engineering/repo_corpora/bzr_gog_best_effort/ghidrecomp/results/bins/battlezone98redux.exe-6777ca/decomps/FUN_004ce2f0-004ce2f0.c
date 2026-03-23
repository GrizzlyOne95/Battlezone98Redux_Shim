
undefined4 FUN_004ce2f0(undefined4 param_1,undefined1 *param_2,undefined4 param_3)

{
  undefined4 uVar1;
  int iVar2;
  
  if (DAT_009173b6 == '\0') {
    FUN_004cc410(0,0,2,param_3);
    FUN_004ce0b0();
    iVar2 = sscanf(DAT_0260db08,"%*s = %[^\n]s",param_2);
    if (iVar2 != 1) {
      *param_2 = 0;
    }
    FUN_004ce100();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004cdda0(2,param_3,param_2);
  }
  return uVar1;
}

