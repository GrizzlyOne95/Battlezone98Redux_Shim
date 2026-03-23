
void __thiscall FUN_004b6fa0(undefined4 param_1,undefined4 param_2,float param_3)

{
  char local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_48,"%s: %f",param_2,(double)param_3,param_1);
  FUN_00689d10(DAT_0091552c,DAT_0260d798,100,DAT_0091758c * DAT_00917568 + 0x8c,local_48);
  DAT_0091758c = DAT_0091758c + 1;
  FUN_0083e885();
  return;
}

