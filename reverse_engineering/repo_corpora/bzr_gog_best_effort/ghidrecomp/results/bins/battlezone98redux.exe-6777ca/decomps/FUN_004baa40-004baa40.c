
undefined4 FUN_004baa40(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  cVar1 = FUN_00575890(param_1,param_2,0,0);
  if (cVar1 == '\0') {
    FUN_00584530(0);
    uVar3 = 0;
  }
  else {
    DAT_009175b4 = 0;
    FUN_00584530(1);
    uVar2 = FUN_00822e60();
    if ((uVar2 < DAT_009180dc) || (1000 < uVar2 - DAT_009180dc)) {
      DAT_009180dc = uVar2;
      DAT_009180d0 = FUN_00573100();
    }
    uVar3 = 1;
  }
  return uVar3;
}

