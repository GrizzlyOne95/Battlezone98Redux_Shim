
undefined4 FUN_008390ce(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  char *pcVar3;
  
  if (param_2 < 0x101) {
    iVar1 = iscntrl(param_2);
    if (iVar1 == 0) {
      pcVar3 = "%c";
    }
    else {
      pcVar3 = "char(%d)";
    }
    uVar2 = FUN_0082e8cd(*(undefined4 *)(param_1 + 0x34),pcVar3,param_2);
  }
  else {
    uVar2 = *(undefined4 *)("unable to get ModuleFileName" + param_2 * 4 + 0x18);
  }
  return uVar2;
}

