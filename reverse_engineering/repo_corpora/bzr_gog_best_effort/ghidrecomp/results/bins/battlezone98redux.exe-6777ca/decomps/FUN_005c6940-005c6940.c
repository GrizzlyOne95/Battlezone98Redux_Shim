
void __fastcall FUN_005c6940(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_004b9830();
  if (cVar1 == '\0') {
    FUN_005c65a0(param_1 + 0x108,*(undefined4 *)(*(int *)(param_1 + 0xf8) + 0x4c));
    (**(code **)(*(int *)(param_1 + 0x18) + 0x10))();
  }
  return;
}

