
/* WARNING: Removing unreachable block (ram,0x00765b38) */

void FUN_00765ae0(char *param_1)

{
  undefined1 local_4d4 [176];
  undefined4 local_424;
  undefined1 local_420 [24];
  char local_408 [1023];
  undefined1 uStack_9;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_408[0] = 'S';
  local_408[1] = '\0';
  strncat(local_408,param_1,0x3fe);
  local_424 = 0x3ff;
  uStack_9 = 0;
  basic_string<>(local_408);
  FUN_004203f0(local_420,3,1);
  ~basic_string<>();
  FUN_0073ba90(local_4d4,&DAT_0260b460);
  FUN_00417f10();
  FUN_0083e885();
  return;
}

