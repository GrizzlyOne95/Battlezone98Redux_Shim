
undefined4
FUN_007f00d0(undefined4 param_1,undefined4 param_2,undefined1 *param_3,undefined4 param_4,
            undefined4 param_5)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined1 local_24 [31];
  undefined1 local_5;
  
  iVar2 = FUN_007df2f0();
  if (iVar2 != 0) {
    uVar3 = FUN_00417780(param_4);
    FUN_00423b10(uVar3);
    FUN_007f0cc0(&local_5,param_5,param_2);
    cVar1 = FUN_007df230(param_1,local_24,param_3);
    if (cVar1 != '\0') {
      operator==<>(param_1,*param_3);
      return 1;
    }
  }
  return 0;
}

