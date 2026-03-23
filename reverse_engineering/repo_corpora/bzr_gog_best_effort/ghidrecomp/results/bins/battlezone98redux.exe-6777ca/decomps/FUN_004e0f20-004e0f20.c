
void __fastcall FUN_004e0f20(undefined4 *param_1)

{
  *param_1 = GameObjectClass::vftable;
  if (param_1[0x52] != 0) {
    operator_delete__((void *)param_1[0x52]);
  }
  FUN_00477440();
  return;
}

