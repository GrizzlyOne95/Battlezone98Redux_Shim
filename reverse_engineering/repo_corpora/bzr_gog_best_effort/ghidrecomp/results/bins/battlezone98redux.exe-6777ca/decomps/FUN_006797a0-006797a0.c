
void __thiscall FUN_006797a0(int param_1,undefined4 param_2)

{
  char cVar1;
  
  cVar1 = FUN_0067ba10("DeviceLost",param_2);
  if (cVar1 == '\0') {
    cVar1 = FUN_0067ba10("DeviceRestored",param_2);
    if (cVar1 != '\0') {
      *(undefined1 *)(param_1 + 8) = 1;
      FUN_00681dd0(1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 8) = 0;
  }
  return;
}

