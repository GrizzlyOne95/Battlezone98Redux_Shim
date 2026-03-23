
undefined1 __thiscall FUN_0049e0f0(int param_1,undefined4 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined8 local_24;
  undefined1 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  uint local_10;
  int local_c;
  char local_5;
  
  local_5 = 1;
  local_24 = 0;
  local_c = param_1;
  cVar1 = FUN_004ce910(param_2,param_1 + 0x14c,4);
  local_5 = cVar1 != '\0';
  local_10 = (uint)(byte)local_5;
  if (((bool)local_5) && (cVar1 = FUN_004cf210(param_2,&local_24,8), cVar1 != '\0')) {
    local_14 = 1;
  }
  else {
    local_14 = 0;
  }
  local_5 = (char)local_14;
  if (((char)local_14 == '\0') || (cVar1 = FUN_004ceb10(param_2,local_c + 0x154,4), cVar1 == '\0'))
  {
    local_18 = 0;
  }
  else {
    local_18 = 1;
  }
  local_5 = (char)local_18;
  if ((int)local_24 == 0 && local_24._4_4_ == 0) {
    *(undefined4 *)(local_c + 0x150) = 0;
  }
  else {
    uVar2 = FUN_004e0f70((int)local_24,local_24._4_4_);
    *(undefined4 *)(local_c + 0x150) = uVar2;
  }
  if ((local_5 == '\0') || (cVar1 = FUN_004e5b10(param_2), cVar1 == '\0')) {
    local_1c = 0;
  }
  else {
    local_1c = 1;
  }
  return local_1c;
}

