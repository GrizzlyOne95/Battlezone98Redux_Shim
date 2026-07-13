
void FUN_004f86a0(void)

{
  undefined4 uVar1;
  undefined8 uVar2;
  float local_e8;
  undefined8 local_e4;
  undefined4 local_dc;
  undefined8 local_d8;
  uint local_d0;
  undefined8 local_cc;
  float local_c4;
  int local_c0;
  int local_bc;
  int local_b8;
  int local_b4;
  int local_b0;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  undefined1 local_98 [44];
  undefined1 local_6c [44];
  undefined1 local_40 [28];
  undefined1 local_24 [28];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_c0 = FUN_00417c70();
  if (local_c0 != 0) {
    local_b4 = FUN_00417ca0();
    if (local_b4 != 0) {
      local_d0 = FUN_00417f90();
      for (local_a0 = 0; local_a0 < 5; local_a0 = local_a0 + 1) {
        if ((1 << ((byte)local_a0 & 0x1f) & local_d0) != 0) {
          local_bc = FUN_00417f60(local_a0);
          local_a8 = *(int *)(local_bc + 8);
          if ((((*(int *)(local_a8 + 0xc) == 0x4c4e4348) || (*(int *)(local_a8 + 0xc) == 0x54484d4c)
               ) || (*(int *)(local_a8 + 0xc) == 0x494d474c)) ||
             (*(int *)(local_a8 + 0xc) == 0x5244524c)) {
            local_a4 = local_bc;
            local_9c = local_a8;
            if (*(int *)(local_b8 + 8 + local_a0 * 4) < *(int *)(local_bc + 0xd0)) {
              if (*(int *)(local_bc + 0xd0) == *(int *)(local_a8 + 0xb8) + -1) {
                if (*(char *)(local_a8 + 0xa8) != '\0') {
                  FUN_0043a990(local_6c);
                  FUN_0043a9e0(local_40);
                  FUN_0043aa30(local_9c + 0xa8,0,local_6c,local_40);
                }
              }
              else if (*(char *)(local_a8 + 0x94) != '\0') {
                FUN_0043a990(local_98);
                FUN_0043a9e0(local_24);
                FUN_0043aa30(local_9c + 0x94,0,local_98,local_24);
              }
            }
            *(undefined4 *)(local_b8 + 8 + local_a0 * 4) = *(undefined4 *)(local_a4 + 0xd0);
            local_b0 = FUN_004da060(*(undefined4 *)(local_a4 + 0xdc));
            local_ac = FUN_004da060(*(undefined4 *)(local_a4 + 0xe4));
            if (local_ac != 0) {
              uVar1 = (**(code **)(*(int *)(local_ac + 0x18) + 0xc))(DAT_00917594,&local_c4);
              uVar2 = FUN_00497780(uVar1);
              local_dc = *(undefined4 *)(local_9c + 0xa4);
              local_e4 = uVar2;
              local_d8 = uVar2;
              if (0.0 < local_c4) {
                FUN_0068c560(DAT_00917580,local_dc,uVar2,0x250004,0);
              }
            }
            if ((local_b0 != 0) && (local_b0 != local_ac)) {
              uVar1 = (**(code **)(*(int *)(local_b0 + 0x18) + 0xc))(DAT_00917594,&local_e8);
              uVar2 = FUN_00497780(uVar1);
              local_cc = uVar2;
              if (0.0 < local_e8) {
                FUN_0068c560(DAT_00917580,*(undefined4 *)(local_9c + 0x90),uVar2,0x250004,0);
              }
            }
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

