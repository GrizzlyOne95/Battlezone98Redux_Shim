
void FUN_0074df20(char param_1)

{
  undefined1 *puVar1;
  undefined1 auStack_2c [8];
  uint uStack_24;
  undefined1 local_20 [20];
  int *local_c;
  undefined1 local_5;
  
  uStack_24 = 0x74df2e;
  local_c = (int *)FUN_0074db30();
  if (local_c != (int *)0x0) {
    local_5 = param_1 == '\0';
    uStack_24 = (uint)(byte)local_5;
    puVar1 = auStack_2c;
    FUN_0073bcf0(local_20);
    FUN_0073a9b0(puVar1);
    (**(code **)(*local_c + 0x3c))();
  }
  return;
}

