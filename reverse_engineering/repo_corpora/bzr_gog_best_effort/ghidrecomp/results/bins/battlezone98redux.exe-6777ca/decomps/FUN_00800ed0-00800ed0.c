
/* WARNING: Removing unreachable block (ram,0x00800f0a) */

void __fastcall FUN_00800ed0(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007fe040(&stack0x00000004);
  cVar1 = FUN_00803950();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1be4;
  }
  return;
}

