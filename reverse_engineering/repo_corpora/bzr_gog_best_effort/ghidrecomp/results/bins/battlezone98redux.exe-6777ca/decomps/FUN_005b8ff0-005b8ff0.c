
void __thiscall FUN_005b8ff0(int param_1,float param_2)

{
  char cVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined1 local_12c [64];
  uint local_ec;
  undefined4 local_e8;
  uint local_e4;
  uint local_e0;
  uint local_dc;
  char local_d5;
  int local_d4;
  undefined4 local_d0 [16];
  undefined4 local_90 [16];
  undefined1 local_50 [16];
  undefined4 local_40;
  undefined1 local_24 [4];
  undefined4 local_20;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  *(float *)(param_1 + 0xc0) = *(float *)(param_1 + 0xc0) + param_2;
  local_e4 = 0;
  local_d4 = param_1;
  for (local_e0 = 0; local_e0 < 4; local_e0 = local_e0 + 1) {
    if (*(int *)(local_d4 + 0xe0 + local_e0 * 4) != 0) {
      cVar1 = FUN_00583dc0();
      if (cVar1 == '\0') {
        local_e4 = local_e4 + 1;
      }
      else {
        *(undefined4 *)(local_d4 + 0xe0 + local_e0 * 4) = 0;
      }
    }
  }
  if (((*(uint *)(*(int *)(local_d4 + 0x18) + 0x14) & 0x10) == 0) || (DAT_00919875 == '\0')) {
    local_e8 = 0;
  }
  else {
    local_e8 = 1;
  }
  local_d5 = (char)local_e8;
  if ((*(char *)(local_d4 + 0xf0) == '\0') || ((char)local_e8 != '\0')) {
    *(undefined4 *)(local_d4 + 0xa8) = *(undefined4 *)(*(int *)(local_d4 + 8) + 0x68);
    if (*(char *)(local_d4 + 0xd8) == '\0') {
      if (local_e4 != 0) {
        *(undefined1 *)(local_d4 + 0xf0) = 1;
      }
    }
    else {
      if ((char)local_e8 == '\0') {
        local_ec = 1;
      }
      else {
        local_ec = 4;
      }
      if ((((local_e4 < local_ec) &&
           (iVar2 = FUN_00417c80(), *(int *)(*(int *)(local_d4 + 0xc) + 0x4c) <= iVar2)) &&
          (0.0 < *(float *)(local_d4 + 0xc0))) && (cVar1 = FUN_00611840(), cVar1 != '\0')) {
        for (local_dc = 0; local_dc < 4; local_dc = local_dc + 1) {
          if (*(int *)(local_d4 + 0xe0 + local_dc * 4) == 0) {
            if (*(char *)(*(int *)(local_d4 + 8) + 0x58) != '\0') {
              FUN_0043a990(local_50);
              local_40 = 0x1000;
              FUN_0043a9e0(local_24);
              if ((*(uint *)(*(int *)(local_d4 + 0x18) + 0x14) & 0x10) != 0) {
                local_20 = 0x41;
              }
              FUN_0043aa30(*(int *)(local_d4 + 8) + 0x58,*(undefined4 *)(local_d4 + 0x10),local_50,
                           local_24);
            }
            (**(code **)(**(int **)(local_d4 + 0xd4) + 0x18))
                      (-*(int *)(*(int *)(local_d4 + 0xc) + 0x4c));
            puVar3 = (undefined4 *)
                     FUN_0081fe60(local_12c,*(int *)(local_d4 + 0x10) + 0x20,local_d4 + 0x28);
            puVar5 = local_90;
            for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar5 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar5 = puVar5 + 1;
            }
            puVar3 = local_90;
            puVar5 = local_d0;
            for (iVar2 = 0x10; iVar2 != 0; iVar2 = iVar2 + -1) {
              *puVar5 = *puVar3;
              puVar3 = puVar3 + 1;
              puVar5 = puVar5 + 1;
            }
            uVar4 = FUN_00586ff0(local_d0,*(undefined4 *)(local_d4 + 0x18));
            *(undefined4 *)(local_d4 + 0xe0 + local_dc * 4) = uVar4;
            *(float *)(*(int *)(local_d4 + 0xe0 + local_dc * 4) + 0x10) =
                 *(float *)(local_d4 + 0xc0) - param_2;
            *(float *)(local_d4 + 0xc0) =
                 *(float *)(local_d4 + 0xc0) - *(float *)(*(int *)(local_d4 + 8) + 0x80);
            break;
          }
        }
      }
    }
  }
  else {
    *(undefined4 *)(local_d4 + 0xa8) = *(undefined4 *)(*(int *)(local_d4 + 8) + 0x98);
    if (*(char *)(local_d4 + 0xd8) == '\0') {
      if (local_e4 == 0) {
        *(undefined1 *)(local_d4 + 0xf0) = 0;
      }
    }
    else {
      FUN_005b8e30();
    }
  }
  if (0.0 < *(float *)(local_d4 + 0xc0)) {
    *(undefined4 *)(local_d4 + 0xc0) = 0;
  }
  *(undefined1 *)(local_d4 + 0xd8) = 0;
  FUN_0083e885();
  return;
}

