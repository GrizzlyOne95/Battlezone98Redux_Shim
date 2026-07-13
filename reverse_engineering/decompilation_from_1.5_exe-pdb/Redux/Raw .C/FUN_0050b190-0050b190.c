
bool __thiscall FUN_0050b190(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  char *local_10;
  bool local_5;
  
  local_5 = false;
  if (*(int *)(param_1 + 0x58) == 0) {
    local_5 = false;
  }
  else {
    FUN_0082c82c(*(undefined4 *)(param_1 + 0x58),0xffffd8ee,"Command");
    iVar1 = FUN_0082d490(*(undefined4 *)(param_1 + 0x58),0xffffffff);
    if (iVar1 == 6) {
      iVar1 = FUN_0082c8f6(*(undefined4 *)(param_1 + 0x58));
      local_10 = strchr(param_2,0x20);
      if (local_10 == (char *)0x0) {
        FUN_0082cd77(*(undefined4 *)(param_1 + 0x58),param_2);
      }
      else {
        FUN_0082cd08(*(undefined4 *)(param_1 + 0x58),param_2,(int)local_10 - (int)param_2);
        for (; *local_10 != '\0'; local_10 = local_10 + 1) {
          if (*local_10 != ' ') {
            FUN_0082cd77(*(undefined4 *)(param_1 + 0x58),local_10);
            break;
          }
        }
      }
      iVar2 = FUN_0082c8f6(*(undefined4 *)(param_1 + 0x58));
      uVar3 = FUN_0082cb8c(*(undefined4 *)(param_1 + 0x58),iVar2 - iVar1,1,0,
                           *(undefined4 *)(param_1 + 0x58),"Lua script Command error:\n%s");
      FUN_004ff600(uVar3);
      iVar1 = FUN_0082d2e8(*(undefined4 *)(param_1 + 0x58),0xffffffff);
      local_5 = iVar1 != 0;
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
    else {
      FUN_0082d226(*(undefined4 *)(param_1 + 0x58),0xfffffffe);
    }
  }
  return local_5;
}

