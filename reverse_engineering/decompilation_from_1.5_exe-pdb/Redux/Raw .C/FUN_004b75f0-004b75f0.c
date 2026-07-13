
int FUN_004b75f0(void)

{
  uint uVar1;
  int local_c;
  
  uVar1 = FUN_004b9a90();
  if (uVar1 < 0x10000) {
    local_c = FUN_004b9a90();
    local_c = local_c + 0x200;
  }
  else {
    local_c = FUN_004b75c0();
    local_c = local_c + 0x1200;
  }
  return local_c;
}

