
void FUN_007761d0(int param_1,float *param_2,float param_3,int param_4)

{
  int local_48c;
  undefined1 local_488 [12];
  undefined4 auStack_47c [2];
  undefined1 auStack_474 [748];
  float afStack_188 [4];
  float fStack_178;
  float fStack_174;
  float fStack_170;
  float fStack_16c;
  float fStack_168;
  float fStack_164;
  float fStack_160;
  float fStack_15c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  afStack_188[0] = -param_3 + *param_2;
  afStack_188[1] = param_2[1];
  afStack_188[2] = -param_3 + param_2[2];
  afStack_188[3] = param_3 + *param_2;
  fStack_178 = param_2[1];
  fStack_174 = -param_3 + param_2[2];
  fStack_170 = param_3 + *param_2;
  fStack_16c = param_2[1];
  fStack_168 = param_3 + param_2[2];
  fStack_164 = -param_3 + *param_2;
  fStack_160 = param_2[1];
  fStack_15c = param_3 + param_2[2];
  for (local_48c = 0; local_48c < 4; local_48c = local_48c + 1) {
    auStack_47c[local_48c * 6] = *(undefined4 *)(&DAT_008f0510 + local_48c * 8 + param_4 * 0x20);
    auStack_47c[local_48c * 6 + 1] = *(undefined4 *)(&DAT_008f0514 + param_4 * 0x20 + local_48c * 8)
    ;
    auStack_474[local_48c * 0x18 + 1] = 0xff;
    auStack_474[local_48c * 0x18] = 0xff;
    FUN_00820180(local_488 + local_48c * 0x18,afStack_188 + local_48c * 3,1,param_1 + 0x40);
  }
  FUN_00685a40(param_1,local_488,4);
  FUN_0083e885();
  return;
}

