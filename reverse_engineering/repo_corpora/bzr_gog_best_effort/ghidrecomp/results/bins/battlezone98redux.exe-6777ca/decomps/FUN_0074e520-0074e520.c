
void FUN_0074e520(void)

{
  undefined1 auStack_1c [8];
  undefined4 uStack_14;
  undefined4 uStack_10;
  int *local_8;
  
  uStack_10 = 0x74e52e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 != (int *)0x0) {
    uStack_10 = 0x74e53f;
    uStack_10 = FUN_0041f870();
    uStack_14 = 0x74e548;
    uStack_14 = FUN_0041f870();
    FUN_0073a9b0(auStack_1c);
    (**(code **)(*local_8 + 0x68))();
  }
  return;
}

