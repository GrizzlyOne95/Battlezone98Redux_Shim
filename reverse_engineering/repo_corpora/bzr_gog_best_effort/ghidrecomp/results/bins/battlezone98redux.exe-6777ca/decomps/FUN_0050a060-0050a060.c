
void __thiscall FUN_0050a060(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_2c;
  undefined2 *local_28;
  uint local_24;
  uint local_20;
  uint local_1c;
  uint local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (DAT_009173b7 == '\0') {
    local_1c = (uint)(0x413 < DAT_00917b20);
    local_20 = local_1c;
  }
  else {
    local_18 = (uint)(DAT_00917b20 == 0x414);
    local_20 = local_18;
  }
  local_8 = param_1;
  if (local_20 == 0) {
    local_24 = (uint)(DAT_009173b7 == '\0');
    *(bool *)(param_1 + 0x5c) = DAT_009173b7 == '\0';
  }
  else {
    FUN_004ce5e0(param_2,param_1 + 0x5c,1);
  }
  if ((*(int *)(local_8 + 0x58) != 0) && (DAT_009173b7 == '\0')) {
    FUN_0082c82c(*(undefined4 *)(local_8 + 0x58),0xffffd8ee,&DAT_0087d1e8);
    iVar1 = FUN_0082d490(*(undefined4 *)(local_8 + 0x58),0xffffffff);
    if (iVar1 == 6) {
      local_10 = 0;
      FUN_004ce910(param_2,&local_10,4);
      for (local_c = 0; local_c < local_10; local_c = local_c + 1) {
        FUN_007d6a70("-- Load %d\n",local_c + 1);
        FUN_00509be0(param_2,*(undefined4 *)(local_8 + 0x58),1,0);
        if (local_c < local_10 + -1) {
          local_28 = (undefined2 *)&DAT_0087d158;
        }
        else {
          local_28 = &DAT_0087a44c;
        }
        FUN_007d6a70(local_28);
      }
      uVar2 = FUN_0082cb8c(*(undefined4 *)(local_8 + 0x58),local_10,0,0,
                           *(undefined4 *)(local_8 + 0x58),"Lua script Load error:\n%s");
      FUN_004ff600(uVar2);
    }
    else {
      local_2c = 0;
      FUN_004ce910(param_2,&local_2c,4);
      for (local_14 = 0; local_14 < local_2c; local_14 = local_14 + 1) {
        FUN_00509be0(param_2,*(undefined4 *)(local_8 + 0x58),0,0);
      }
      FUN_0082d226(*(undefined4 *)(local_8 + 0x58),0xfffffffe);
    }
  }
  FUN_0045d570(param_2);
  return;
}

