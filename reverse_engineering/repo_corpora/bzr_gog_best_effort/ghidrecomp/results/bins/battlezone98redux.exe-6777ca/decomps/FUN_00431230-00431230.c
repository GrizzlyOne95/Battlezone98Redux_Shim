
void __thiscall FUN_00431230(int param_1,undefined1 param_2)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined1 local_124 [4];
  undefined1 local_120 [4];
  undefined1 local_11c [4];
  undefined1 local_118 [4];
  undefined4 local_114;
  undefined4 local_110;
  undefined4 local_10c;
  undefined4 local_108;
  undefined1 local_104 [11];
  undefined1 local_f9;
  uint local_f8;
  uint local_f4;
  undefined1 local_ed;
  int local_ec [2];
  undefined1 local_e4 [208];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845901;
  local_10 = ExceptionList;
  local_14 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_ec[0] = param_1;
  if (1 < *(uint *)(param_1 + 4)) {
    uVar2 = Getal(&local_f9);
    allocator<>(uVar2);
    FUN_004324f0(&local_ed);
    local_8 = 0;
    FUN_0083ead2(local_e4,8,0x1a,vector<>,FUN_004284d0);
    local_8 = CONCAT31(local_8._1_3_,1);
    local_f4 = 0;
    while (cVar1 = FUN_0042d8f0(), cVar1 == '\0') {
      FUN_0042d8c0(local_120);
      puVar3 = (undefined4 *)FUN_0042da80();
      local_110 = *puVar3;
      puVar3 = (undefined4 *)FUN_0042d8c0(local_118);
      local_114 = *puVar3;
      puVar3 = (undefined4 *)FUN_0042d8c0(local_124);
      local_108 = *puVar3;
      FUN_00432670(local_108,local_ec[0],local_114,local_110,1);
      local_ec[1] = 0;
      while (((uint)local_ec[1] < local_f4 && (cVar1 = FUN_0042d8f0(), cVar1 == '\0'))) {
        FUN_00432e40(local_104,param_2);
        FUN_00432540(local_104);
        local_ec[1] = local_ec[1] + 1;
      }
      if (local_ec[1] == 0x19) {
        FUN_00432e40(local_104,param_2);
      }
      else {
        FUN_00432540(local_104);
        if (local_ec[1] == local_f4) {
          local_f4 = local_f4 + 1;
        }
      }
    }
    for (local_f8 = 1; local_f8 < local_f4; local_f8 = local_f8 + 1) {
      FUN_00432e40(local_ec + local_f8 * 2,param_2);
    }
    puVar3 = (undefined4 *)FUN_0042d8c0(local_11c);
    local_10c = *puVar3;
    FUN_00432600(local_10c,local_ec + local_f4 * 2);
    local_8 = local_8 & 0xffffff00;
    _eh_vector_destructor_iterator_(local_e4,8,0x1a,FUN_004284d0);
    local_8 = 0xffffffff;
    FUN_004284d0();
  }
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

