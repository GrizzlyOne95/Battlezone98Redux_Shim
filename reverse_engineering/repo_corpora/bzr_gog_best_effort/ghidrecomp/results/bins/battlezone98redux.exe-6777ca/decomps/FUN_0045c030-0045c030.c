
void FUN_0045c030(void)

{
  undefined4 *puVar1;
  
  if (DAT_0260d10c == (undefined4 *)0x0) {
    puVar1 = (undefined4 *)FUN_0045ca50();
    if ((puVar1 != (undefined4 *)0x0) && (puVar1 != (undefined4 *)0x0)) {
      (**(code **)*puVar1)(1);
    }
  }
  else {
    if (DAT_0260d10c != (undefined4 *)0x0) {
      (**(code **)*DAT_0260d10c)(1);
    }
    DAT_0260d10c = (undefined4 *)0x0;
  }
  FUN_004610c0();
  return;
}

