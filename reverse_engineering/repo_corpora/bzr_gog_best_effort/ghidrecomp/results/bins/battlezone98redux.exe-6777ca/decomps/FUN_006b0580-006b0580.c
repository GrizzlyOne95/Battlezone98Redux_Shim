
void FUN_006b0580(void)

{
  undefined1 local_428 [8];
  undefined1 local_420 [8];
  uint local_418;
  undefined4 *local_414;
  int local_410;
  undefined1 local_409;
  undefined1 local_408 [1024];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  FUN_006af000(local_420,local_408,0x400);
  FUN_004fbb60();
  local_410 = FUN_006af020(*local_414,local_420,1,0,local_428);
  local_409 = 0 < local_410;
  local_418 = (uint)(byte)local_409;
  while (local_410 == 0x400) {
    local_410 = FUN_006af020(*local_414,local_420,1,0,local_428);
  }
  FUN_0083e885();
  return;
}

