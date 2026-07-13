
undefined4 FUN_005cb0d0(undefined4 param_1,char *param_2,undefined4 param_3)

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
    uVar2 = FUN_00612f10(iVar1,local_8,param_3);
  }
  return uVar2;
}

