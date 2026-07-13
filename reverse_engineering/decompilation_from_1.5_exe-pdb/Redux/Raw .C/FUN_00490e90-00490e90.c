
void __fastcall FUN_00490e90(undefined4 *param_1)

{
  *param_1 = ChargeGunClass::vftable;
  if (param_1[0x2b] != 0) {
    operator_delete__((void *)param_1[0x2b]);
  }
  FUN_0048faa0();
  return;
}

