
void FUN_007d6020(HANDLE param_1,LPCSTR param_2)

{
  if (DAT_008f1690 < 1) {
    FUN_007d6000();
  }
  DAT_008f1690 = DAT_008f1690 + 1;
  (&DAT_02c41af8)[DAT_008f1690] = param_1;
  SetConsoleActiveScreenBuffer(param_1);
  (&DAT_02c41ae8)[DAT_008f1690] = param_2;
  SetConsoleTitleA(param_2);
  return;
}

