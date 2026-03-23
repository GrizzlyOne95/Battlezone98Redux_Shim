
/* WARNING: Type propagation algorithm not settling */

undefined4 FUN_0073bf60(undefined4 param_1,char *param_2)

{
  uint uVar1;
  int iVar2;
  undefined1 auStack_d4 [160];
  undefined *local_34;
  uint local_30 [3];
  undefined *local_24;
  undefined1 *local_20;
  char *local_1c;
  uint local_18;
  undefined1 local_11;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084fe6b;
  local_10 = ExceptionList;
  uVar1 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_30[2] = 0;
  FUN_00574400(3,1);
  local_8 = 0;
  iVar2 = FUN_0081dee0(uVar1);
  if (iVar2 == 7) {
    local_24 = &DAT_00873738;
  }
  else {
    local_24 = &DAT_008733a8;
  }
  local_34 = local_24;
  local_30[1] = 0;
  local_1c = param_2;
  do {
    if (*local_1c == '\0') {
      GetPolicy(param_1);
      local_30[2] = local_30[2] | 1;
      local_8 = 0xffffffff;
      FUN_00417f10();
      ExceptionList = local_10;
      return param_1;
    }
    iVar2 = FUN_0073bd40(local_30 + 1,local_30,(int)*local_1c);
    if (iVar2 == 0) {
      local_11 = 0x3f;
      for (local_18 = 1; local_18 < 0x100; local_18 = local_18 + 1) {
        if (local_30[0] == *(ushort *)(local_34 + local_18 * 2)) {
          local_11 = (undefined1)local_18;
          break;
        }
      }
      if (&stack0x00000000 == (undefined1 *)0xe4) {
        local_20 = (undefined1 *)0x0;
      }
      else {
        local_20 = auStack_d4;
      }
      FUN_006d9650(local_20,local_11);
    }
    local_1c = local_1c + 1;
  } while( true );
}

