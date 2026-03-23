
void FUN_0046cd10(int param_1)

{
  char local_30 [16];
  undefined4 local_20;
  undefined1 local_1c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_0260d5ec == 0) {
    DAT_00917398 = param_1;
    if (param_1 == 0) {
      builtin_strncpy(local_30,"Unally with team",0x10);
      local_20._0_1_ = ' ';
      local_20._1_1_ = '#';
      local_20._2_1_ = ':';
      local_20._3_1_ = ' ';
      local_1c = 0;
    }
    else {
      builtin_strncpy(local_30,"Ally with team #",0x10);
      local_20._0_3_ = 0x203a;
    }
    FUN_00823470(DAT_0260d184,local_30);
    FUN_00823600(DAT_0260d184,&DAT_008a1ad8);
    FUN_00823330(DAT_0260d184,1);
    FUN_00434f20();
    FUN_00823390(DAT_0260d184,1);
  }
  FUN_0083e885();
  return;
}

