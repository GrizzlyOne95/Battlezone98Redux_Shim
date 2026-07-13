
void __thiscall FUN_004feb30(int param_1,uint param_2)

{
  uint uVar1;
  int iVar2;
  uint uStack_44;
  uint local_20;
  undefined1 local_15;
  undefined1 *local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0084aa40;
  local_10 = ExceptionList;
  uStack_44 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  local_14 = (undefined1 *)&uStack_44;
  ExceptionList = &local_10;
  local_20 = param_2 | 7;
  uVar1 = FID_conflict_max_size();
  if (uVar1 < local_20) {
    local_20 = param_2;
  }
  else if (local_20 / 3 < *(uint *)(param_1 + 0x14) >> 1) {
    uVar1 = *(uint *)(param_1 + 0x14);
    iVar2 = FID_conflict_max_size();
    if (iVar2 - (uVar1 >> 1) < *(uint *)(param_1 + 0x14)) {
      local_20 = FID_conflict_max_size();
    }
    else {
      local_20 = (*(uint *)(param_1 + 0x14) >> 1) + *(int *)(param_1 + 0x14);
    }
  }
  local_8 = 0;
  Getal(&local_15);
  allocate(local_20 + 1);
  FUN_004fec66();
  return;
}

