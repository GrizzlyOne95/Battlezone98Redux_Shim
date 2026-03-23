
undefined4 __fastcall FUN_006accf0(int param_1)

{
  undefined4 uVar1;
  
  LOCK();
  uVar1 = *(undefined4 *)(param_1 + 0x1c);
  *(undefined4 *)(param_1 + 0x1c) = 0;
  UNLOCK();
  return uVar1;
}

