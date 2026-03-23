
void FUN_007657b0(void)

{
  if (DAT_00945470 != (int *)0x0) {
    (**(code **)(*DAT_00945470 + 0x10))();
  }
  if (DAT_00945474 != (undefined4 *)0x0) {
    (**(code **)*DAT_00945474)(1);
  }
  DAT_00945474 = (undefined4 *)0x0;
  if (DAT_00945488 != (undefined4 *)0x0) {
    (**(code **)*DAT_00945488)(1);
  }
  DAT_00945488 = (undefined4 *)0x0;
  if (DAT_00945470 != (int *)0x0) {
    (**(code **)*DAT_00945470)(1);
  }
  DAT_00945470 = (int *)0x0;
  if (DAT_0094547c != (undefined4 *)0x0) {
    (**(code **)*DAT_0094547c)(1);
  }
  DAT_0094547c = (undefined4 *)0x0;
  if (DAT_00945478 != (undefined4 *)0x0) {
    (**(code **)*DAT_00945478)(1);
  }
  DAT_00945478 = (undefined4 *)0x0;
  SteamAPI_Shutdown();
  if (DAT_00945490 != (undefined4 *)0x0) {
    if (DAT_00945490 != (undefined4 *)0x0) {
      (**(code **)*DAT_00945490)(1);
    }
    DAT_00945490 = (undefined4 *)0x0;
    FUN_0073b680();
  }
  if (DAT_00945484 != 0) {
    if (DAT_00945484 != 0) {
      FUN_00765980(1);
    }
    DAT_00945484 = 0;
  }
  return;
}

