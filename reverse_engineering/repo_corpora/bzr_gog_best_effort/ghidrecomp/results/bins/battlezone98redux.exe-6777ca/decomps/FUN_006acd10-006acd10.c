
void __fastcall FUN_006acd10(int param_1)

{
  LOCK();
  *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + 1;
  UNLOCK();
  return;
}

