
void FUN_005c93e0(void)

{
  undefined4 local_c;
  undefined4 local_8;
  
  for (local_c = 1; local_c < 0x10; local_c = local_c + 1) {
    FUN_005e0bc0(local_c);
    for (local_8 = 1; local_8 < 0x10; local_8 = local_8 + 1) {
      if (local_c == local_8) {
        FUN_005e12b0(local_8);
      }
      else {
        FUN_005e12e0(local_8);
      }
    }
  }
  return;
}

