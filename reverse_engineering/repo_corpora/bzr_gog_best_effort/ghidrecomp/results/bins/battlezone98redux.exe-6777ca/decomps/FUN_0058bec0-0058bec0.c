
float10 FUN_0058bec0(uint param_1)

{
  float local_c;
  
  local_c = (float)(&DAT_00918174)[param_1 & 0xff];
  if (((ushort)(param_1 >> 0x10) & DAT_00918158) != 0) {
    local_c = local_c + 2.0;
  }
  return (float10)local_c;
}

