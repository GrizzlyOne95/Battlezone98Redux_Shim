
void FUN_005738a0(void)

{
  int iVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined1 local_c;
  undefined1 local_b;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = DAT_00917f44;
  local_18 = DAT_00917f54;
  local_14 = DAT_00917f70;
  local_10 = DAT_00917fa4;
  local_c = DAT_009175bf;
  local_b = DAT_008e8c0d;
  iVar1 = FUN_005771b0(DAT_009180d4);
  if (iVar1 == 0) {
    DAT_00917f4c = 1;
  }
  else {
    FUN_00575570(0xc,&local_1c,0x14);
  }
  FUN_0083e885();
  return;
}

