
char __thiscall FUN_005d3e30(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  char local_5;
  
  local_5 = '\x01';
  if (DAT_00917b20 < 0x3fd) {
    if (*(int *)(param_1 + 0x238) < 0) {
      *(undefined4 *)(param_1 + 0x23c) = 0;
    }
    else {
      uVar1 = FUN_005c5fd0(*(undefined4 *)(param_1 + 0x238));
      *(undefined4 *)(param_1 + 0x23c) = uVar1;
    }
  }
  else {
    if (-1 < *(int *)(param_1 + 0x238)) {
      FUN_005c6230(*(undefined4 *)(param_1 + 0x238));
      *(undefined4 *)(param_1 + 0x238) = 0xffffffff;
    }
    local_5 = FUN_004cf640(param_2,param_1 + 0x23c,4,"ScrapSilo::dropObj",param_1);
  }
  if (local_5 != '\0') {
    local_5 = FUN_0047eb20(param_2);
  }
  return local_5;
}

