
void FUN_00759f50(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  undefined1 local_58 [4];
  undefined1 local_54 [20];
  undefined4 local_40 [7];
  undefined4 local_24 [7];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_00759cd0(local_54,param_2,param_3);
  cVar1 = FUN_004c85a0();
  if (cVar1 == '\0') {
    FUN_00759c40(local_58,param_2,param_3);
    cVar1 = FUN_004c85a0();
    if (cVar1 == '\0') {
      FUN_006b3160();
    }
    else {
      FUN_006b3160();
      local_24[0] = 0;
      _Callable_base<>(local_58);
      FUN_00759f10(local_24);
    }
  }
  else {
    FUN_006b3160();
    local_40[0] = 1;
    FUN_006b2f70(local_54);
    FUN_00759f10(local_40);
  }
  FUN_0083e885();
  return;
}

