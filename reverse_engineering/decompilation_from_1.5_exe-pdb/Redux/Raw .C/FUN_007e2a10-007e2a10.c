
/* WARNING: Removing unreachable block (ram,0x007e2a4a) */

void __fastcall FUN_007e2a10(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007dd750(&stack0x00000004);
  cVar1 = FUN_007e6be0();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1ae4;
  }
  return;
}

