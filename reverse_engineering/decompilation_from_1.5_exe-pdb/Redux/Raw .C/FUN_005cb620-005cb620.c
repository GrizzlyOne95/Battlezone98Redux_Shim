
void FUN_005cb620(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = FUN_00462630(param_1);
  if ((iVar1 != 0) && (iVar1 = FUN_0045bdf0(), iVar1 != 0)) {
    *(undefined4 *)(iVar1 + 0x18) = param_2;
  }
  return;
}

