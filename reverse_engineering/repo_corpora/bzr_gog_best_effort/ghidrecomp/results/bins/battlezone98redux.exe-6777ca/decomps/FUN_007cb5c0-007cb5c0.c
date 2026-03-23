
void __fastcall FUN_007cb5c0(int param_1)

{
  int iVar1;
  int local_c;
  
  FUN_007cb780();
  local_c = 0;
  while( true ) {
    iVar1 = size();
    if (iVar1 <= local_c) break;
    FUN_007cabf0(&DAT_008a1ad8,local_c,0);
    local_c = local_c + 1;
  }
  *(undefined4 *)(param_1 + 0x150) = 0;
  FUN_007cafa0(0xffffffff);
  FUN_007cb400();
  return;
}

