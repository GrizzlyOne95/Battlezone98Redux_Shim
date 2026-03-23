
uint FUN_004c7700(uint param_1)

{
  int iVar1;
  
  iVar1 = rand();
  if ((int)(param_1 & 0xf000) >> 0xc == (int)(param_1 & 0xf00) >> 8) {
    param_1 = param_1 & 0xffffff8f | (iVar1 >> 0xd & 3U) << 4;
  }
  else {
    param_1 = param_1 & 0xffffffbf;
  }
  return param_1;
}

