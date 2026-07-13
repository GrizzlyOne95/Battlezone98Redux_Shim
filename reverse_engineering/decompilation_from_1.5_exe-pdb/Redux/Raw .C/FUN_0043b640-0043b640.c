
void FUN_0043b640(undefined4 *param_1)

{
  undefined4 uVar1;
  
  uVar1 = *param_1;
  memset(param_1,0,0x88);
  *param_1 = uVar1;
  FUN_0043a990(param_1 + 1);
  FUN_0043a9e0(param_1 + 0xc);
  *(undefined1 *)(param_1 + 0x1b) = 0xff;
  param_1[0x17] = 0;
  param_1[0x19] = 0xffffffff;
  return;
}

