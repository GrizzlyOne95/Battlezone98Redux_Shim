
void FUN_0074e630(void)

{
  undefined1 auStack_18 [8];
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e63e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 != (int *)0x0) {
    uStack_10 = 0x74e64f;
    uStack_10 = FUN_0041f870();
    FUN_0073a9b0(auStack_18);
    (**(code **)(*local_8 + 0x5c))();
  }
  return;
}

