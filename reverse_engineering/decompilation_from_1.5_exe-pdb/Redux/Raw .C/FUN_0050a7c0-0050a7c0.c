
void __thiscall FUN_0050a7c0(int param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 local_1c;
  undefined2 *local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = param_1;
  if (DAT_009173b7 == '\0') {
    FUN_004ccf20(param_2,param_1 + 0x5c,1,"started");
  }
  if ((*(int *)(local_8 + 0x58) != 0) && (DAT_009173b7 == '\0')) {
    FUN_0082c82c(*(undefined4 *)(local_8 + 0x58),0xffffd8ee,&DAT_0087d2a8);
    iVar2 = FUN_0082d490(*(undefined4 *)(local_8 + 0x58),0xffffffff);
    if (iVar2 == 6) {
      local_14 = FUN_0082c8f6(*(undefined4 *)(local_8 + 0x58));
      uVar3 = FUN_0082cb8c(*(undefined4 *)(local_8 + 0x58),0,0xffffffff,0,
                           *(undefined4 *)(local_8 + 0x58),"Lua script Save error:\n%s");
      cVar1 = FUN_004ff600(uVar3);
      if (cVar1 != '\0') {
        iVar2 = FUN_0082c8f6(*(undefined4 *)(local_8 + 0x58));
        local_10 = (iVar2 - local_14) + 1;
        FUN_004cd1b0(param_2,&local_10,4,"count");
        for (local_c = 0; local_c < local_10; local_c = local_c + 1) {
          FUN_007d6a70("-- Save %d\n",local_c + 1);
          FUN_0050a270(param_2,*(undefined4 *)(local_8 + 0x58),local_c + local_14,0);
          if (local_c < local_10 + -1) {
            local_18 = (undefined2 *)&DAT_0087d158;
          }
          else {
            local_18 = &DAT_0087a44c;
          }
          FUN_007d6a70(local_18);
        }
      }
    }
    else {
      local_1c = 0;
      FUN_004cd1b0(param_2,&local_1c,4,"count");
      FUN_0082d226(*(undefined4 *)(local_8 + 0x58),0xfffffffe);
    }
  }
  FUN_0045d830(param_2);
  return;
}

