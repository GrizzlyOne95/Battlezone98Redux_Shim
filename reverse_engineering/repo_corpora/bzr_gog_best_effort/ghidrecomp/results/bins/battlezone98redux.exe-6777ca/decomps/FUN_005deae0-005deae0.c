
void __fastcall FUN_005deae0(undefined4 param_1)

{
  int iVar1;
  int local_20;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  iVar1 = FUN_00417c70(param_1);
  FUN_00462370();
  if (iVar1 != 0) {
    local_8 = FUN_00462610();
    if (DAT_009198cf == '\0') {
      if (DAT_009198d0 == '\0') {
        if (local_8 != 0) {
          local_8 = FUN_005df0e0(local_8);
        }
      }
      else {
        if (local_8 == 0) {
          local_10 = 0;
        }
        else {
          local_10 = FUN_0045bba0();
          if ((local_10 < 0x23) || (0x2c < local_10)) {
            local_10 = 0;
          }
        }
        local_8 = 0;
        local_c = local_10;
        if (local_10 == 0) {
          local_14 = 0x23;
          while ((local_14 < 0x2d && (local_8 = FUN_005e0f70(local_14), local_8 == 0))) {
            local_14 = local_14 + 1;
          }
        }
        else {
          do {
            local_c = local_c + 1;
            if (0x2c < local_c) break;
            local_8 = FUN_005e0f70(local_c);
          } while (local_8 == 0);
          if (local_8 == 0) {
            local_c = 0x23;
            while ((local_c <= local_10 && (local_8 = FUN_005e0f70(local_c), local_8 == 0))) {
              local_c = local_c + 1;
            }
          }
        }
      }
    }
    else if (local_8 == 0) {
      local_8 = FUN_005dec80();
    }
    else {
      local_8 = 0;
    }
    FUN_0049f450(local_8);
    local_20 = FUN_0045bbe0(local_8);
    if (local_20 == 1) {
      local_20 = 0;
    }
    FUN_004a72a0(local_20,local_8);
  }
  return;
}

