
/* WARNING: Removing unreachable block (ram,0x00800eaa) */

void __fastcall FUN_00800e70(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007fe060(&stack0x00000004);
  cVar1 = FUN_00803990();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1c04;
  }
  return;
}

