
void FUN_005bc640(int *param_1)

{
  char cVar1;
  bool bVar2;
  undefined4 *puVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined1 local_114 [44];
  undefined4 *local_e8;
  undefined4 local_e4;
  _Order_node_base<enum_Concurrency::agent_status> *local_e0;
  float local_dc;
  float local_d8;
  _Order_node_base<enum_Concurrency::agent_status> *local_d4;
  float local_d0;
  int local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  _Order_node_base<enum_Concurrency::agent_status> *local_b8;
  int local_b4;
  _Order_node_base<enum_Concurrency::agent_status> *local_b0;
  _Order_node_base<enum_Concurrency::agent_status> *local_ac;
  float local_a8;
  float local_a4;
  undefined4 local_a0 [16];
  undefined4 local_60 [16];
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  float local_c;
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_b8 = (_Order_node_base<enum_Concurrency::agent_status> *)FUN_00417c70();
  if (local_b8 != (_Order_node_base<enum_Concurrency::agent_status> *)0x0) {
    puVar3 = (undefined4 *)FUN_008203f0();
    puVar7 = local_a0;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    puVar3 = local_a0;
    puVar7 = local_60;
    for (iVar6 = 0x10; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar7 = *puVar3;
      puVar3 = puVar3 + 1;
      puVar7 = puVar7 + 1;
    }
    local_d4 = (_Order_node_base<enum_Concurrency::agent_status> *)0x0;
    local_bc = 0.0;
    FUN_005b28e0((double)(*(float *)(local_b4 + 0x40) * 200.0 * 0.5) + *(double *)(local_b4 + 0x50),
                 (double)(*(float *)(local_b4 + 0x48) * 200.0 * 0.5) + *(double *)(local_b4 + 0x60),
                 0x4059000000000000,local_114);
LAB_005bc75a:
    cVar1 = FUN_00462710(&local_e8);
    if (cVar1 != '\0') {
      local_ac = (_Order_node_base<enum_Concurrency::agent_status> *)FUN_004da060(*local_e8);
      if ((((local_ac != (_Order_node_base<enum_Concurrency::agent_status> *)0x0) &&
           (local_ac != local_b8)) &&
          ((param_1 == (int *)0x0 || (iVar6 = (**(code **)(*param_1 + 0x34))(local_ac), iVar6 != 0))
          )) && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')) {
        iVar6 = (**(code **)(*(int *)(local_b8 + 0x18) + 4))();
        iVar4 = (**(code **)(*(int *)(local_ac + 0x18) + 4))();
        if (iVar6 != iVar4) {
          local_e4 = (**(code **)(*(int *)(local_ac + 0x18) + 0x30))();
          iVar6 = FUN_00417e20(local_e4);
          if (iVar6 != 0) {
            local_e0 = local_ac;
            bVar2 = Concurrency::_Order_node_base<enum_Concurrency::agent_status>::has_value
                              (local_ac);
            if (bVar2) goto LAB_005bc75a;
          }
        }
        pfVar5 = (float *)(**(code **)(*(int *)(local_ac + 0x18) + 0xc))();
        local_14 = *pfVar5;
        local_10 = pfVar5[1];
        local_c = pfVar5[2];
        FUN_00820180();
        if ((0.0001 <= local_c) && (local_c <= 200.0)) {
          iVar6 = FUN_00462400();
          local_c4 = *(float *)(iVar6 + 0xc) * 0.75;
          local_c4 = local_c4 * local_c4;
          local_d0 = local_14 * local_14 + local_10 * local_10;
          local_dc = local_c * local_c + local_d0;
          if (((local_d0 <= local_c4) || (local_d0 <= local_dc * 0.01)) &&
             (local_a4 = 1.0 - local_d0 / local_dc, local_a4 = local_a4 * local_a4,
             local_a4 = local_a4 * local_a4, local_a4 = local_a4 * local_a4,
             local_a4 = local_a4 * local_a4, local_a4 = local_a4 * local_a4, local_bc < local_a4)) {
            local_d4 = local_ac;
            local_bc = local_a4;
          }
        }
      }
      goto LAB_005bc75a;
    }
    for (local_cc = 0; local_cc < DAT_00917af8; local_cc = local_cc + 1) {
      local_b0 = *(_Order_node_base<enum_Concurrency::agent_status> **)
                  (&DAT_00917a78 + local_cc * 4);
      if ((local_b0 != local_b8) &&
         (((param_1 == (int *)0x0 || (iVar6 = (**(code **)(*param_1 + 0x34))(local_b0), iVar6 != 0))
          && (cVar1 = FUN_0045bbc0(), cVar1 == '\0')))) {
        pfVar5 = (float *)(**(code **)(*(int *)(local_b0 + 0x18) + 0xc))();
        local_20 = *pfVar5;
        local_1c = pfVar5[1];
        local_18 = pfVar5[2];
        FUN_00820180();
        if (0.0001 <= local_18) {
          iVar6 = FUN_00462400();
          local_c8 = *(float *)(iVar6 + 0xc) * 0.75;
          local_c8 = local_c8 * local_c8;
          local_c0 = local_20 * local_20 + local_1c * local_1c;
          local_d8 = local_18 * local_18 + local_c0;
          if (((local_c0 <= local_c8) || (local_c0 <= local_d8 * 0.01)) &&
             (local_a8 = 1.0 - local_c0 / local_d8, local_a8 = local_a8 * local_a8,
             local_a8 = local_a8 * local_a8, local_a8 = local_a8 * local_a8,
             local_a8 = local_a8 * local_a8, local_a8 = local_a8 * local_a8, local_bc < local_a8)) {
            local_d4 = local_b0;
            local_bc = local_a8;
          }
        }
      }
    }
  }
  FUN_0083e885();
  return;
}

