
undefined4 FUN_00481a80(undefined4 *param_1,char *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *local_8;
  
  if (param_1 == (undefined4 *)0x0) {
    local_8 = &DAT_0091739c;
  }
  else {
    local_8 = param_1;
  }
  if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
    uVar1 = 0;
  }
  else {
    iVar2 = FUN_004817a0(local_8,param_2);
    if (iVar2 == 0) {
      uVar1 = FUN_00829150(param_2);
    }
    else {
      uVar1 = *(undefined4 *)(iVar2 + 0x10);
    }
  }
  return uVar1;
}

