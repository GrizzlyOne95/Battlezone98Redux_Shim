
void __fastcall FUN_004b7ab0(int param_1)

{
  if (*(char *)(param_1 + 0x68) == '\x02') {
    if (*(uint *)(param_1 + 100) < 0x10000) {
      FUN_004b7bd0();
    }
  }
  else if (*(char *)(param_1 + 0x68) == '\x01') {
    FUN_004b7bd0();
  }
  return;
}

