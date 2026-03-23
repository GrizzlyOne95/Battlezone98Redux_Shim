
void __fastcall FUN_004510d0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_20 [4];
  undefined4 local_1c;
  int local_18;
  int local_14;
  int local_10;
  undefined4 local_c;
  undefined4 *local_8;
  
  *param_1 = ParticleSimulateClass::vftable;
  local_8 = param_1;
  iVar1 = FUN_004170c0();
  if (0 < iVar1) {
    FUN_0044e950(local_8 + 1);
  }
  FUN_00423890();
  while (iVar1 = FUN_004170c0(), iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_00447e20(local_20);
    local_c = *puVar2;
    local_10 = FUN_00447e70();
    FUN_0044e950(local_10);
    local_18 = local_10;
    local_14 = local_10;
    if (local_10 == 0) {
      local_1c = 0;
    }
    else {
      local_1c = FUN_00451190(1);
    }
  }
  FUN_0044e9d0();
  return;
}

