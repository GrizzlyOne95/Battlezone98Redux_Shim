
undefined4 FUN_005ce520(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar3 = 0;
  }
  else {
    iVar2 = FUN_00462630(param_2);
    if (iVar2 == 0) {
      uVar3 = 0;
    }
    else {
      FUN_004d3130(iVar2);
      uVar3 = FUN_004d3540(iVar1);
    }
  }
  return uVar3;
}

