
void FUN_00437330(void)

{
  tagRECT local_18;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  GetClientRect(DAT_009183fc,&local_18);
  FUN_0083e885(local_18.right - local_18.left,local_18.bottom - local_18.top);
  return;
}

