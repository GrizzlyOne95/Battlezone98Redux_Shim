
void FUN_006a0350(ushort param_1,int *param_2)

{
  ushort *local_8;
  
  for (local_8 = *(ushort **)(DAT_02ceb7e8 + 0xc + (uint)param_1 * 0x9c); *local_8 != 0;
      local_8 = local_8 + 1) {
    if (*local_8 != param_1) {
      FUN_006a0350(*local_8,param_2);
    }
  }
  *(ushort *)*param_2 = param_1;
  *param_2 = *param_2 + 2;
  return;
}

