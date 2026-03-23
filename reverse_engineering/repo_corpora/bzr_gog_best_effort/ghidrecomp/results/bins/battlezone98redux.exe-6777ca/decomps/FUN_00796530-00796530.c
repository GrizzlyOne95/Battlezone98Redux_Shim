
void FUN_00796530(void)

{
  undefined4 uVar1;
  bool bVar2;
  undefined1 *puVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_134 [16];
  undefined1 local_124 [16];
  undefined1 local_114 [52];
  uint local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  undefined4 local_cc;
  byte *local_c8;
  uint local_c4;
  byte *local_c0;
  byte *local_bc;
  byte local_b6;
  byte local_b5;
  int local_b4;
  undefined1 local_b0 [24];
  undefined1 local_98 [24];
  undefined1 local_80 [24];
  undefined1 local_68 [24];
  undefined1 local_50 [48];
  char local_20 [12];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0085f2c1;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  puVar4 = local_50;
  FUN_00764780(puVar4,local_14);
  FUN_007664f0(puVar4);
  local_8 = 0;
  FUN_00764780();
  local_d0 = FUN_00766680();
  FUN_00426b10(0,0,0);
  local_8._0_1_ = 1;
  sprintf(local_20,"%d",local_d0);
  FUN_00426a60(&DAT_02cf2000,0);
  local_8._0_1_ = 2;
  FUN_00426af0("multi.ini");
  local_dc = FUN_00417fd0(local_b0);
  local_8._0_1_ = 3;
  local_d8 = local_dc;
  uVar1 = FUN_0041f870();
  FUN_00426c30(uVar1);
  local_8._0_1_ = 2;
  ~basic_string<>();
  uVar6 = 0;
  uVar5 = 0;
  uVar1 = FUN_0041f870(0,0);
  FUN_00421f90("multi","vehicle",uVar1,uVar5,uVar6);
  FUN_00421f90("multi","faction",local_20,0,0);
  local_d4 = FUN_00417fd0(local_98);
  local_8._0_1_ = 4;
  uVar5 = 1;
  local_cc = local_d4;
  uVar1 = FUN_0041f870(1);
  FUN_00426c90(uVar1,uVar5);
  local_8._0_1_ = 2;
  ~basic_string<>();
  basic_string<>("vehicle");
  local_8._0_1_ = 5;
  uVar1 = (**(code **)(**(int **)(local_b4 + 0x1bc) + 0x38))(local_124,local_80);
  uVar5 = FUN_0073bcf0(local_114);
  local_c8 = (byte *)(**(code **)(**(int **)(local_b4 + 0x1bc) + 0x28))(uVar5,uVar1);
  local_8 = CONCAT31(local_8._1_3_,2);
  ~basic_string<>();
  if (local_c8 != (byte *)0x0) {
    local_c0 = (byte *)FUN_0041f870();
    local_bc = local_c8;
    do {
      local_b6 = *local_bc;
      bVar2 = local_b6 < *local_c0;
      if (local_b6 != *local_c0) {
LAB_007967ba:
        local_c4 = -(uint)bVar2 | 1;
        goto LAB_007967c5;
      }
      if (local_b6 == 0) break;
      local_b5 = local_bc[1];
      bVar2 = local_b5 < local_c0[1];
      if (local_b5 != local_c0[1]) goto LAB_007967ba;
      local_bc = local_bc + 2;
      local_c0 = local_c0 + 2;
    } while (local_b5 != 0);
    local_c4 = 0;
LAB_007967c5:
    local_e0 = local_c4;
    if (local_c4 == 0) goto LAB_00796837;
  }
  basic_string<>("vehicle");
  local_8._0_1_ = 6;
  puVar4 = local_50;
  puVar3 = local_68;
  uVar1 = FUN_0073bcf0(local_134);
  (**(code **)(**(int **)(local_b4 + 0x1bc) + 0x1c))(uVar1,puVar3,puVar4);
  local_8 = CONCAT31(local_8._1_3_,2);
  ~basic_string<>();
LAB_00796837:
  local_8._0_1_ = 1;
  FUN_004180b0();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00426bc0();
  local_8 = 0xffffffff;
  ~basic_string<>();
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

