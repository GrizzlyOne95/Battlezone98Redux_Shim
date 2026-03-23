
void FUN_006bd580(uint *param_1,int param_2)

{
  uint local_14;
  undefined1 local_10 [8];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  for (local_14 = 0; (int)local_14 < 8; local_14 = local_14 + 1) {
    local_10[local_14] = (char)(param_1[(int)local_14 >> 2] >> (sbyte)((local_14 & 3) << 3));
  }
  FUN_006bd400(param_1,&DAT_00895d78,(0x37 - (*param_1 >> 3) & 0x3f) + 1);
  FUN_006bd400(param_1,local_10,8);
  for (local_14 = 0; (int)local_14 < 0x10; local_14 = local_14 + 1) {
    *(char *)(param_2 + local_14) =
         (char)(param_1[((int)local_14 >> 2) + 2] >> (sbyte)((local_14 & 3) << 3));
  }
  FUN_0083e885();
  return;
}

