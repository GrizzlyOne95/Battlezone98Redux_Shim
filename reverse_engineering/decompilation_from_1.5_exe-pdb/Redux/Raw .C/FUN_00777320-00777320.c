
void FUN_00777320(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5,
                 undefined4 param_6)

{
  float fVar1;
  float10 fVar2;
  int local_48c;
  undefined1 local_488 [12];
  undefined4 auStack_47c [189];
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
  if ((param_5 * 0.2 < param_3) || (param_5 * 0.2 < param_4)) {
    fVar2 = (float10)FUN_00820570((double)(param_5 * param_5 + param_3 * param_3 + param_4 * param_4
                                          ));
    fVar1 = (float)fVar2;
    param_5 = param_5 * fVar1;
    param_3 = param_3 * fVar1;
    param_4 = param_4 * fVar1;
  }
  afStack_188[0] = -param_3;
  afStack_188[2] = param_5;
  afStack_188[1] = -param_4;
  afStack_188[3] = param_3;
  fStack_174 = param_5;
  fStack_178 = -param_4;
  fStack_170 = param_3;
  fStack_168 = param_5;
  fStack_16c = param_4;
  fStack_164 = -param_3;
  fStack_15c = param_5;
  fStack_160 = param_4;
  for (local_48c = 0; local_48c < 4; local_48c = local_48c + 1) {
    auStack_47c[local_48c * 6] = *(undefined4 *)(&DAT_008f0510 + local_48c * 8);
    auStack_47c[local_48c * 6 + 1] = *(undefined4 *)(&DAT_008f0514 + local_48c * 8);
    auStack_47c[local_48c * 6 + 2] = 0x3f800000;
    FUN_00820180(local_488 + local_48c * 0x18,afStack_188 + local_48c * 3);
  }
  FUN_006860d0(local_488,4,param_6);
  FUN_0083e885();
  return;
}

