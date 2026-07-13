
int __thiscall FUN_00462630(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_004da060(param_2,param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    uVar2 = FUN_0045c4b0();
    if ((uVar2 & 0x200) != 0) {
      iVar1 = 0;
    }
  }
  return iVar1;
}

