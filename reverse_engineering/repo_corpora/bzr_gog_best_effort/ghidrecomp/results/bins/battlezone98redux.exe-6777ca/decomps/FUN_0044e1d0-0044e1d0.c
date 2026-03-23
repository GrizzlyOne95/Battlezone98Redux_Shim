
void __fastcall FUN_0044e1d0(undefined4 *param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined1 local_1c [4];
  undefined4 local_18;
  undefined4 *local_14;
  undefined4 local_10;
  undefined4 *local_c;
  undefined4 *local_8;
  
  *param_1 = ParticleRenderClass::vftable;
  local_8 = param_1;
  FUN_00423890();
  while (iVar1 = FUN_004170c0(), iVar1 != 0) {
    puVar2 = (undefined4 *)FUN_00447e20(local_1c);
    local_10 = *puVar2;
    local_14 = (undefined4 *)FUN_00447e70();
    local_c = local_14;
    if (local_14 == (undefined4 *)0x0) {
      local_18 = 0;
    }
    else {
      local_18 = (**(code **)*local_14)(1);
    }
  }
  FUN_0044e9d0();
  return;
}

