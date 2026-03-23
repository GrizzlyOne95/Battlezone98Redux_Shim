
void FUN_004351e0(LONG *param_1)

{
  RECT local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (param_1 == (LONG *)0x0) {
    ClipCursor((RECT *)0x0);
  }
  else {
    local_18.bottom = param_1[3];
    local_18.left = *param_1;
    local_18.right = param_1[2];
    local_18.top = param_1[1];
    ClipCursor(&local_18);
  }
  FUN_0083e885();
  return;
}

