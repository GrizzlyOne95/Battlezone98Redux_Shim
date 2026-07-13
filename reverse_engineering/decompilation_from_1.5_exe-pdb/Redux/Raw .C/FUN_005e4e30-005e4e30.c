
void __thiscall FUN_005e4e30(undefined4 param_1,undefined4 param_2)

{
  char cVar1;
  char local_5c;
  undefined1 local_58 [7];
  char local_51;
  undefined1 local_50 [72];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  if (DAT_00917b20 < 0x407) {
    if (DAT_00917b20 < 0x3fb) {
      cVar1 = FUN_004ce910(param_2,local_58,4,param_1);
      if ((((cVar1 == '\0') || (cVar1 = FUN_004ce910(param_2,local_58,4), cVar1 == '\0')) ||
          (cVar1 = FUN_004ce910(param_2,local_58,4), cVar1 == '\0')) ||
         (((cVar1 = FUN_004ce910(param_2,local_58,4), cVar1 == '\0' ||
           (cVar1 = FUN_004ce910(param_2,local_58,4), cVar1 == '\0')) ||
          ((cVar1 = FUN_004ce910(param_2,local_58,4), cVar1 == '\0' ||
           (cVar1 = FUN_004ced10(param_2,local_50,0x48), cVar1 == '\0')))))) {
        local_5c = '\0';
      }
      else {
        local_5c = '\x01';
      }
      local_51 = local_5c;
    }
    else if (DAT_00917b20 < 0x404) {
      local_51 = '\x01';
    }
    else {
      local_51 = FUN_004ce910(param_2,local_58,4,param_1);
    }
    if (local_51 != '\0') {
      local_51 = FUN_004dd370(param_2);
    }
  }
  else {
    FUN_005a7c20(param_2);
  }
  FUN_0083e885();
  return;
}

