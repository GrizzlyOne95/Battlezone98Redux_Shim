
/* WARNING: Removing unreachable block (ram,0x00800c9a) */

void __fastcall FUN_00800c60(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007fe000(&stack0x00000004);
  cVar1 = FUN_008037a0();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1c34;
  }
  return;
}

