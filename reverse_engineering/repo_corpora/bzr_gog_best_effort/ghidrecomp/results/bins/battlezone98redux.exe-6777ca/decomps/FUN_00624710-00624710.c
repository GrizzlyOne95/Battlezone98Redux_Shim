
void FUN_00624710(char *param_1)

{
  undefined2 uVar1;
  char local_408 [1024];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  _vsnprintf(local_408,0x400,param_1,&stack0x00000008);
  uVar1 = FUN_00572d90(local_408,0);
  FUN_00624550(uVar1);
  FUN_0083e885();
  return;
}

