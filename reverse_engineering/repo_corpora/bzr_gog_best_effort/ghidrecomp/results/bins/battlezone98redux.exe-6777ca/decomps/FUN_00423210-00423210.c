
int __fastcall FUN_00423210(int param_1)

{
  char cVar1;
  int iVar2;
  int local_c;
  
  if (*(int *)(param_1 + 0x50) == 0) {
    local_c = 0;
  }
  else {
    cVar1 = FUN_00423330();
    local_c = param_1;
    if (cVar1 == '\0') {
      local_c = 0;
    }
    iVar2 = fclose(*(FILE **)(param_1 + 0x50));
    if (iVar2 != 0) {
      local_c = 0;
    }
  }
  FUN_00423280(0,2);
  return local_c;
}

