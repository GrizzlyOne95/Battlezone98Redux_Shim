
/* WARNING: Removing unreachable block (ram,0x00800f6a) */

void __fastcall FUN_00800f30(undefined4 *param_1)

{
  char cVar1;
  
  FUN_007fe080(&stack0x00000004);
  cVar1 = FUN_008039d0();
  if (cVar1 == '\0') {
    *param_1 = 0;
  }
  else {
    *param_1 = &DAT_008a1c5c;
  }
  return;
}

