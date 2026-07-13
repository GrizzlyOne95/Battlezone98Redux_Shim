
bool FUN_005902d0(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  char local_c;
  
  uVar1 = FUN_0046acc0(param_1,param_2);
  if ((uVar1 & 8) == 0) {
    local_c = FUN_0046adb0(param_1,param_2);
  }
  else {
    local_c = '\0';
  }
  return local_c == DAT_02a13c78;
}

