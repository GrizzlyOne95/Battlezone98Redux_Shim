
undefined4 FUN_005cb050(undefined4 param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_8;
  
  iVar1 = FUN_00462630(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if ((param_2 == (char *)0x0) || (*param_2 == '\0')) {
      local_8 = 0;
    }
    else {
      local_8 = FUN_00588c10(param_2);
    }
    if (local_8 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = FUN_006131e0(iVar1,local_8);
    }
  }
  return uVar2;
}

