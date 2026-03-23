
void __thiscall
FUN_004b7030(undefined4 param_1,undefined4 param_2,float param_3,float param_4,float param_5)

{
  char local_48 [64];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  sprintf(local_48,"%s: (%f,%f,%f)",param_2,(double)param_3,(double)param_4,(double)param_5,param_1)
  ;
  FUN_00689d10();
  DAT_0091758c = DAT_0091758c + 1;
  FUN_0083e885();
  return;
}

