
undefined4 FUN_0074e770(void)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  undefined1 auStack_2c [8];
  undefined4 uStack_24;
  int iStack_20;
  undefined1 local_1c [20];
  int *local_8;
  
  iStack_20 = 0x74e77e;
  local_8 = (int *)FUN_0074db30();
  if (local_8 == (int *)0x0) {
    uVar1 = 0;
  }
  else {
    iStack_20 = 0x74e78f;
    iStack_20 = FUN_004170c0();
    iStack_20 = iStack_20 + 1;
    uStack_24 = 0x74e79b;
    uStack_24 = FUN_0041f870();
    puVar2 = auStack_2c;
    FUN_0073bcf0(local_1c);
    FUN_0073a9b0(puVar2);
    uVar1 = (**(code **)(*local_8 + 0x7c))();
  }
  return uVar1;
}

