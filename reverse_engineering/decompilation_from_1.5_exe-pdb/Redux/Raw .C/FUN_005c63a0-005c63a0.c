
char __thiscall FUN_005c63a0(int param_1,undefined4 param_2)

{
  undefined1 local_10 [4];
  int local_c;
  char local_5;
  
  local_5 = '\x01';
  local_c = param_1;
  if (DAT_00917b20 < 0x3fa) {
    local_5 = FUN_004cf640(param_2,local_10,4,"ScrapDropoff: recycler",param_1);
  }
  if (local_5 != '\0') {
    local_5 = FUN_005a7c20(param_2);
  }
  *(undefined4 *)(local_c + 0xfc) = 0;
  return local_5;
}

