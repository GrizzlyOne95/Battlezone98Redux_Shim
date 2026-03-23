
undefined4 FUN_006d7470(void)

{
  undefined8 uVar1;
  undefined1 local_20 [16];
  int *local_10;
  undefined1 local_c;
  
  FUN_006d1a70(local_20);
  uVar1 = FUN_006c94e0();
  if ((*local_10 == (int)uVar1) && (local_10[1] == (int)((ulonglong)uVar1 >> 0x20))) {
    local_c = 1;
  }
  else {
    local_c = 0;
  }
  return CONCAT31((int3)((uint)*local_10 >> 8),local_c);
}

