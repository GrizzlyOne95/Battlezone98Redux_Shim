
void __fastcall FUN_006ad7d0(int param_1)

{
  int iVar1;
  
  while( true ) {
    iVar1 = get();
    if (iVar1 == 0) break;
    FUN_006c8fb0();
    LOCK();
    *(int *)(param_1 + 0x18) = *(int *)(param_1 + 0x18) + -1;
    UNLOCK();
    FUN_006ac970();
  }
  return;
}

