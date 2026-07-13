
int FUN_005c3140(void)

{
  int iVar1;
  int local_c;
  int local_8;
  
  FUN_00462590();
  local_8 = FUN_005e0f70(1);
  if (((local_8 == 0) && (local_8 = FUN_005e0f70(2), local_8 == 0)) &&
     (local_8 = FUN_005e0f70(3), local_8 == 0)) {
    for (local_c = 0xf; local_c < 0x19; local_c = local_c + 1) {
      iVar1 = FUN_005e0f70(local_c);
      if (iVar1 != 0) {
        return iVar1;
      }
      local_8 = 0;
    }
    local_c = 5;
    while ((local_c < 0xf && (local_8 = FUN_005e0f70(local_c), local_8 == 0))) {
      local_c = local_c + 1;
    }
  }
  return local_8;
}

