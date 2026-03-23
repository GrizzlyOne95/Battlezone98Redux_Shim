
void FUN_008279c0(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  allocator<char> *this;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined1 *puVar6;
  int *piVar7;
  undefined4 uVar8;
  undefined1 *puVar9;
  undefined *puVar10;
  int *piVar11;
  undefined1 local_52c [8];
  undefined1 local_524 [4];
  undefined1 local_520 [8];
  undefined1 local_518 [4];
  char *local_514;
  undefined1 local_510 [8];
  undefined1 local_508 [8];
  uint local_500;
  undefined1 local_4fc [8];
  undefined4 *local_4f4;
  undefined4 local_4f0;
  undefined4 local_4ec;
  undefined4 local_4e8;
  int local_4e4 [3];
  undefined4 *local_4d8;
  int local_4d4;
  undefined1 local_4d0 [8];
  int local_4c8;
  char *local_4bc;
  undefined4 local_4b8;
  undefined4 *local_4b4;
  undefined4 *local_4b0;
  char *local_4ac;
  int local_4a8;
  char local_4a1;
  uint local_4a0;
  undefined1 local_49c [24];
  undefined1 local_484 [24];
  undefined1 local_46c [24];
  undefined4 local_454;
  undefined4 local_450;
  undefined4 local_44c;
  undefined4 local_448;
  uint local_444;
  undefined4 local_440;
  undefined4 local_43c;
  undefined4 local_438;
  undefined4 local_434;
  undefined4 local_430;
  undefined4 local_42c;
  undefined4 local_428;
  uint local_424;
  undefined4 local_420;
  undefined4 local_41c;
  undefined4 local_418;
  char local_414 [1024];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00865162;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  *param_1 = 0;
  vector<>(local_14);
  local_8 = 0;
  local_500 = FUN_00829680();
  for (local_4a0 = 0; local_4a0 < local_500; local_4a0 = local_4a0 + 1) {
    FUN_004fbb60();
    uVar8 = 0;
    uVar2 = FUN_008296a0(local_4a0);
    FUN_00426a60(uVar2,uVar8);
    local_8._0_1_ = 1;
    FUN_00667590();
    local_8._0_1_ = 2;
    FUN_006675b0(local_46c,local_4fc);
    local_8._0_1_ = 3;
    cVar1 = FUN_004c85a0();
    if (cVar1 != '\0') {
      FUN_006676e0(local_510);
      local_8._0_1_ = 4;
      while (cVar1 = FUN_0066e6d0(local_4d0,local_508), cVar1 != '\0') {
        puVar9 = local_484;
        this = (allocator<char> *)FUN_0066add0(puVar9);
        std::allocator<char>::allocator<char>(this);
        local_4f0 = FUN_008405e0(puVar9);
        local_8 = CONCAT31(local_8._1_3_,5);
        local_4e8 = local_4f0;
        local_4e4[2] = FUN_00417fd0(local_49c);
        local_4bc = (char *)FUN_0041f870();
        local_514 = local_414;
        local_4ac = local_514;
        do {
          local_4a1 = *local_4bc;
          *local_4ac = local_4a1;
          local_4bc = local_4bc + 1;
          local_4ac = local_4ac + 1;
        } while (local_4a1 != '\0');
        ~basic_string<>();
        local_8._0_1_ = 4;
        FUN_004180b0();
        FUN_004fbb60();
        puVar9 = local_520;
        puVar6 = local_52c;
        FUN_0066add0(puVar6,puVar9);
        FUN_006674d0(puVar6,puVar9);
        local_4c8 = get();
        if ((local_4c8 == 2) || (local_4c8 == 4)) {
          local_454 = 0;
          local_450 = 0;
          local_44c = 0;
          local_448 = 0;
          local_440 = 0;
          local_43c = 0;
          local_438 = 0;
          local_444 = local_4a0 & 0xffff;
          FUN_00827640(&local_454,local_414);
          FUN_00829730(&local_454);
          *param_1 = *param_1 + 1;
        }
        FUN_0066ae00();
      }
      local_8._0_1_ = 3;
      FUN_00667660();
    }
    iVar3 = FUN_00667170();
    if (iVar3 != 0) {
      puVar10 = &DAT_008a2458;
      uVar2 = FUN_008296a0(local_4a0);
      iVar3 = FUN_00827620(uVar2,puVar10);
      if (iVar3 != 0) {
        uVar8 = 0;
        uVar2 = FUN_008296a0(local_4a0);
        uVar2 = FUN_008271b0(uVar2,uVar8);
        iVar3 = FUN_008296a0(local_4a0);
        *(undefined4 *)(iVar3 + 0x1000) = uVar2;
        iVar3 = FUN_008296a0(local_4a0);
        if (*(int *)(iVar3 + 0x1000) != 0) {
          piVar11 = local_4e4;
          piVar7 = &local_4d4;
          iVar3 = FUN_008296a0(local_4a0);
          FUN_00827600(*(undefined4 *)(iVar3 + 0x1000),piVar7,piVar11);
          for (local_4a8 = 0; local_4a8 < local_4e4[0]; local_4a8 = local_4a8 + 1) {
            if ((*(uint *)(local_4d4 + 0x20 + local_4a8 * 0x24) & 1) == 0) {
              local_434 = 0;
              local_430 = 0;
              local_42c = 0;
              local_428 = 0;
              local_420 = 0;
              local_41c = 0;
              local_418 = 0;
              local_424 = local_4a0 & 0xffff;
              FUN_00827640(&local_434,local_4a8 * 0x24 + local_4d4);
              FUN_00829730(&local_434);
              *param_1 = *param_1 + 1;
            }
          }
          iVar3 = FUN_008296a0(local_4a0);
          FUN_00827310(*(undefined4 *)(iVar3 + 0x1000));
          iVar3 = FUN_008296a0(local_4a0);
          *(undefined4 *)(iVar3 + 0x1000) = 0;
        }
      }
    }
    local_8._0_1_ = 2;
    FUN_00667660();
    local_8._0_1_ = 1;
    FUN_00667660();
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_004180b0();
  }
  if (*param_1 == 0) {
    local_4e4[1] = 0;
    local_8 = 0xffffffff;
    FUN_004284d0();
  }
  else {
    local_4b0 = (undefined4 *)0x0;
    local_4b4 = calloc(1,*param_1 << 5);
    local_4b0 = local_4b4;
    puVar4 = (undefined4 *)FUN_0042d8c0(local_518);
    local_4b8 = *puVar4;
    puVar4 = (undefined4 *)FID_conflict_begin(local_524);
    local_4ec = *puVar4;
    cVar1 = FUN_00420f10(&local_4ec);
    if (cVar1 != '\0') {
      local_4f4 = (undefined4 *)FUN_00422e80();
      puVar4 = local_4f4;
      puVar5 = local_4b4;
      for (iVar3 = 8; iVar3 != 0; iVar3 = iVar3 + -1) {
        *puVar5 = *puVar4;
        puVar4 = puVar4 + 1;
        puVar5 = puVar5 + 1;
      }
      local_4b4 = local_4b4 + 8;
                    /* WARNING: Subroutine does not return */
      FUN_0042de70();
    }
    local_4d8 = local_4b0;
    local_8 = 0xffffffff;
    FUN_004284d0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

