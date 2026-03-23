
void __fastcall FUN_005d8b10(int param_1)

{
  char cVar1;
  
  cVar1 = FUN_00571c40();
  if (cVar1 != '\0') {
    if (*(int *)(param_1 + 0x238) != 0) {
      FUN_005d89f0(1);
    }
    *(undefined4 *)(param_1 + 0x238) = 0;
  }
  FUN_0047eb00();
  return;
}

