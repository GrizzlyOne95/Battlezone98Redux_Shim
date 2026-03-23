
void FUN_00443a80(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined1 local_94 [64];
  int local_54;
  int local_50;
  int local_4c;
  undefined4 local_48 [16];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  do {
    if (param_1 == 0) {
      FUN_0083e885();
      return;
    }
    puVar1 = (undefined4 *)FUN_0081fe60(local_94,param_1 + 0x20,param_2);
    puVar3 = local_48;
    for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
      *puVar3 = *puVar1;
      puVar1 = puVar1 + 1;
      puVar3 = puVar3 + 1;
    }
    local_4c = FUN_0043fff0(param_1);
    if (local_4c == 0x3000) {
      FUN_00444540(param_1);
    }
    if (local_4c == 0) {
      local_4c = DAT_0260c92c;
    }
    if (((local_4c == 0x1000) || (*(int *)(param_1 + 0x84) == 0x37)) ||
       ((*(uint *)(param_1 + 0x14) & 1) != 0)) {
      FUN_00442820(param_1,0x1000);
    }
    else {
      iVar2 = FUN_004e3620(param_1,0);
      if ((iVar2 == 0) || (*(int *)(param_1 + 100) == 0)) {
        if ((local_4c == 0x4000) || (local_4c == 0x5000)) {
          FUN_00442820(param_1,local_4c);
        }
        else {
          FUN_00442820(param_1,0x1000);
        }
      }
      else {
        local_54 = local_4c;
        if (local_4c == 0x3000) {
          if (2 < *(uint *)(*(int *)(param_1 + 100) + 4)) {
            local_50 = FUN_00444220(param_1,local_48);
            *(int *)(param_1 + 0x9c) = local_50;
            if (local_50 != 0) {
              FUN_00442820(param_1,0x3000);
              goto LAB_00443bfc;
            }
          }
          FUN_00442820(param_1,0x1000);
        }
        else {
          FUN_00442820(param_1,local_4c);
        }
      }
    }
LAB_00443bfc:
    if (*(int *)(param_1 + 0x80) != 0) {
      FUN_00443a80(*(undefined4 *)(param_1 + 0x80),local_48);
    }
    param_1 = *(int *)(param_1 + 0x7c);
  } while( true );
}

