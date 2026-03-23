
void __fastcall FUN_0060b650(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int local_48;
  undefined4 local_38;
  undefined4 local_34;
  int local_30;
  int local_2c;
  undefined1 local_25;
  int local_24;
  int local_20;
  int local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_1c = param_1;
  if (*(int *)(param_1 + 0xc) == 0) {
    local_48 = 0;
  }
  else {
    local_48 = FUN_00417ca0();
  }
  local_30 = local_48;
  for (local_20 = 0; local_20 < 5; local_20 = local_20 + 1) {
    *(undefined4 *)(local_1c + 0x24 + local_20 * 4) = 0;
    *(undefined4 *)(local_1c + 0x4c + local_20 * 4) = 0;
    *(undefined4 *)(local_1c + 0x38 + local_20 * 4) = 0;
    *(undefined4 *)(local_1c + 0x60 + local_20 * 4) = 0;
  }
  if (local_48 != 0) {
    uVar1 = FUN_00608a80();
    for (local_20 = 0; local_20 < 5; local_20 = local_20 + 1) {
      if ((1 << ((byte)local_20 & 0x1f) & uVar1) != 0) {
        iVar2 = FUN_00417f60(local_20);
        *(uint *)(local_1c + 0x24 + local_20 * 4) =
             1 << ((byte)local_20 & 0x1f) | *(uint *)(local_1c + 0x24 + local_20 * 4);
        *(uint *)(local_1c + 0x38 + local_20 * 4) =
             1 << ((byte)local_20 & 0x1f) | *(uint *)(local_1c + 0x38 + local_20 * 4);
        local_24 = local_20;
        while (local_24 = local_24 + 1, local_24 < 5) {
          if ((1 << ((byte)local_24 & 0x1f) & uVar1) != 0) {
            iVar3 = FUN_00417f60(local_24);
            if (*(int *)(iVar2 + 8) == *(int *)(iVar3 + 8)) {
              *(uint *)(local_1c + 0x24 + local_20 * 4) =
                   1 << ((byte)local_24 & 0x1f) | *(uint *)(local_1c + 0x24 + local_20 * 4);
              *(uint *)(local_1c + 0x24 + local_24 * 4) =
                   1 << ((byte)local_20 & 0x1f) | *(uint *)(local_1c + 0x24 + local_24 * 4);
            }
            if (*(int *)(*(int *)(iVar2 + 0x14) + 0x84) == *(int *)(*(int *)(iVar3 + 0x14) + 0x84))
            {
              *(uint *)(local_1c + 0x38 + local_20 * 4) =
                   1 << ((byte)local_24 & 0x1f) | *(uint *)(local_1c + 0x38 + local_20 * 4);
              *(uint *)(local_1c + 0x38 + local_24 * 4) =
                   1 << ((byte)local_20 & 0x1f) | *(uint *)(local_1c + 0x38 + local_24 * 4);
            }
          }
        }
      }
    }
  }
  local_20 = 0;
  do {
    if (4 < local_20) {
      if (local_30 != 0) {
        if (*(int *)(local_1c + 0x24 + *(int *)(local_1c + 0x20) * 0x14 +
                    *(int *)(local_1c + 0x1c) * 4) == 0) {
          *(undefined4 *)(local_1c + 0x1c) =
               *(undefined4 *)
                (local_1c + 0x4c + *(int *)(local_1c + 0x20) * 0x14 + *(int *)(local_1c + 0x1c) * 4)
          ;
        }
        FUN_004d9880(0);
        FUN_004d9880(*(undefined4 *)
                      (local_1c + 0x24 + *(int *)(local_1c + 0x20) * 0x14 +
                      *(int *)(local_1c + 0x1c) * 4));
      }
      if (local_30 != 0) {
        FUN_0060a240();
      }
      local_38 = 0x6163702a;
      local_34 = 0x726d;
      iVar2 = (*(code *)**(undefined4 **)(*(int *)(local_1c + 0xc) + 0x18))();
      local_38 = CONCAT31(local_38._1_3_,*(undefined1 *)(iVar2 + 0xcc));
      sprintf(local_18,"%.8s.odf",&local_38);
      iVar2 = FUN_00481f10(local_18);
      if (iVar2 == 0) {
        iVar2 = (*(code *)**(undefined4 **)(*(int *)(local_1c + 0xc) + 0x18))();
        if (*(char *)(iVar2 + 0xcc) == 'c') {
          local_25 = 0x73;
        }
        else {
          local_25 = 0x61;
        }
        local_38 = CONCAT31(local_38._1_3_,local_25);
      }
      uVar4 = FUN_004e0f70(local_38,local_34);
      *(undefined4 *)(local_1c + 0x18) = uVar4;
      FUN_0083e885();
      return;
    }
    local_2c = local_20;
    local_24 = local_20;
    do {
      local_24 = local_24 + 1;
      if (4 < local_24) goto LAB_0060b98f;
    } while ((*(int *)(local_1c + 0x24 + local_24 * 4) == *(int *)(local_1c + 0x24 + local_20 * 4))
            || (*(int *)(local_1c + 0x24 + local_24 * 4) == 0));
    local_2c = local_24;
LAB_0060b98f:
    if (local_2c == local_20) {
      for (local_24 = 0; local_24 < local_20; local_24 = local_24 + 1) {
        if ((*(int *)(local_1c + 0x24 + local_24 * 4) != *(int *)(local_1c + 0x24 + local_20 * 4))
           && (*(int *)(local_1c + 0x24 + local_24 * 4) != 0)) {
          local_2c = local_24;
          break;
        }
      }
    }
    *(int *)(local_1c + 0x4c + local_20 * 4) = local_2c;
    local_2c = local_20;
    local_24 = local_20;
    do {
      local_24 = local_24 + 1;
      if (4 < local_24) goto LAB_0060ba85;
    } while ((*(int *)(local_1c + 0x38 + local_24 * 4) == *(int *)(local_1c + 0x38 + local_20 * 4))
            || (*(int *)(local_1c + 0x38 + local_24 * 4) == 0));
    local_2c = local_24;
LAB_0060ba85:
    if (local_2c == local_20) {
      for (local_24 = 0; local_24 < local_20; local_24 = local_24 + 1) {
        if ((*(int *)(local_1c + 0x38 + local_24 * 4) != *(int *)(local_1c + 0x38 + local_20 * 4))
           && (*(int *)(local_1c + 0x38 + local_24 * 4) != 0)) {
          local_2c = local_24;
          break;
        }
      }
    }
    *(int *)(local_1c + 0x60 + local_20 * 4) = local_2c;
    local_20 = local_20 + 1;
  } while( true );
}

