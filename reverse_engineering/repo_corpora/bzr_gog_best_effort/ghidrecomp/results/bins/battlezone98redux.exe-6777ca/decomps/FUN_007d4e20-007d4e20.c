
void __thiscall FUN_007d4e20(undefined4 param_1,undefined4 param_2)

{
  uint local_244;
  uint local_240;
  uint local_23c;
  undefined4 local_238 [132];
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_18 = 0;
  local_14 = 0;
  local_10 = 0;
  local_c = 0;
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  if (DAT_009456d8 != (code *)0x0) {
    memset(local_238,0,0x210);
    for (local_23c = 0; local_23c < 6; local_23c = local_23c + 1) {
      for (local_240 = 0; local_240 < 0x16; local_240 = local_240 + 1) {
        local_238[local_23c * 0x16 + local_240] = param_2;
      }
    }
    (*DAT_009456d8)(2,local_238,&local_18);
    (*DAT_009456d8)(0,0,&local_28);
    for (local_244 = 0; local_244 < 3; local_244 = local_244 + 1) {
      (*DAT_009456fc)(local_18,local_14,local_10,local_c);
      Sleep(200);
      (*DAT_009456fc)(local_28,local_24,local_20,local_1c);
      Sleep(200);
    }
    (*DAT_009456f0)(local_18,local_14,local_10,local_c);
    (*DAT_009456f0)(local_28,local_24,local_20,local_1c);
  }
  FUN_0083e885(param_1);
  return;
}

