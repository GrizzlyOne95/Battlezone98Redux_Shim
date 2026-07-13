
undefined1 FUN_0058fd10(undefined4 param_1,undefined4 param_2,char param_3)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  
  cVar1 = FUN_0048fca0(param_1,param_2);
  if ((cVar1 == '\0') || (cVar1 != param_3)) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_0048fbe0(param_1,param_2);
    iVar3 = FUN_00591670(uVar2);
    uVar2 = (&DAT_008e8e10)[iVar3];
  }
  return uVar2;
}

