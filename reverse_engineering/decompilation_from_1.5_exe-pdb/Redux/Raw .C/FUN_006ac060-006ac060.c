
void FUN_006ac060(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined1 local_10 [8];
  int local_8;
  
  piVar2 = (int *)(param_1 + 4);
  LOCK();
  local_8 = *piVar2;
  *piVar2 = *piVar2;
  UNLOCK();
  if (local_8 != 0) {
    uVar1 = FUN_006abbb0();
    FUN_00416430(local_8,uVar1);
    FUN_006aba00(local_10,"winsock");
  }
  return;
}

