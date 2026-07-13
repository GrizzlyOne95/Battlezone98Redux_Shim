
char __fastcall FUN_007d3ee0(int param_1)

{
  char cVar1;
  
  if (*(int *)(param_1 + 0x13c) == 0) {
    cVar1 = *(char *)(param_1 + 0xe8);
  }
  else {
    cVar1 = FUN_007d3ee0();
    cVar1 = cVar1 + *(char *)(param_1 + 0xe8);
  }
  return cVar1;
}

