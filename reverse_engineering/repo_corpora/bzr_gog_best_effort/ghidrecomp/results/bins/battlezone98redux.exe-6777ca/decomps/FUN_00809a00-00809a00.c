
void FUN_00809a00(void)

{
  uint uVar1;
  undefined4 uVar2;
  char *extraout_var;
  char *pcVar3;
  uint uVar4;
  undefined1 local_2c [24];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845608;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  uVar4 = 0;
  local_14 = uVar1;
  basic_string<>("literal-char");
  local_8 = 0;
  pcVar3 = extraout_var;
  uVar2 = FUN_00417780((int)*extraout_var,uVar1);
  FUN_007faed0(local_2c,uVar2);
  local_8 = 0xffffffff;
  ~basic_string<>(uVar1,pcVar3,uVar4 | 1);
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

