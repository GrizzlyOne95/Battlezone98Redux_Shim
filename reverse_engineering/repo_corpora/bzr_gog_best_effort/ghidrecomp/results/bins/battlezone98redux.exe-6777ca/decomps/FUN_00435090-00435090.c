
undefined4 FUN_00435090(LONG *param_1)

{
  undefined4 uVar1;
  BOOL BVar2;
  tagPOINT local_c;
  
  if (param_1 == (LONG *)0x0) {
    uVar1 = 0;
  }
  else {
    local_c.x = *param_1;
    local_c.y = param_1[1];
    BVar2 = GetCursorPos(&local_c);
    if (BVar2 == 0) {
      uVar1 = 0;
    }
    else {
      *param_1 = local_c.x;
      param_1[1] = local_c.y;
      uVar1 = 1;
    }
  }
  return uVar1;
}

