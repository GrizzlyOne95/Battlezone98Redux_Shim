
/* WARNING: Removing unreachable block (ram,0x00800fca) */

void __fastcall FUN_00800f90(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007fe0a0(&stack0x00000004);
  cVar1 = FUN_00803a10();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1c18;
  }
  return;
}

