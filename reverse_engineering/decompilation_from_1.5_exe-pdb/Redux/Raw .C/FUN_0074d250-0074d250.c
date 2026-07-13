
void __fastcall FUN_0074d250(int param_1)

{
  char cVar1;
  int iVar2;
  
  FUN_005d4930(param_1);
  cVar1 = FUN_0073a900();
  if (cVar1 != '\0') {
    iVar2 = get();
    if (*(int *)(iVar2 + 0xc3c) != 0) {
      param_1 = param_1 + 0x28;
      get(param_1);
      FUN_0075cea0(param_1);
    }
    FUN_00578640(&DAT_0260b1c8,0);
    FUN_006d6f80();
    FUN_00740a90(1);
  }
  FUN_006d6f80();
  FUN_0073ddf0();
  FUN_007476a0();
  return;
}

