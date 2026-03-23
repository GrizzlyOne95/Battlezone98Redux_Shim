
void FUN_007d6080(void)

{
  int iVar1;
  FILE *pFVar2;
  FILE *pFVar3;
  char *pcVar4;
  size_t sVar5;
  SMALL_RECT local_14;
  FILE *local_c;
  COORD local_8;
  
  local_14.Left = 0;
  local_14.Top = 0;
  local_14.Right = 0x4f;
  local_14.Bottom = 0x18;
  local_8.X = 0x50;
  local_8.Y = 1000;
  FUN_007d61b0();
  DAT_008f1694 = GetStdHandle(0xfffffff5);
  FUN_007d6020(DAT_008f1694,"Battlezone Console");
  SetConsoleWindowInfo(DAT_008f1694,1,&local_14);
  SetConsoleScreenBufferSize(DAT_008f1694,local_8);
  pcVar4 = "w";
  iVar1 = _open_osfhandle((intptr_t)DAT_008f1694,0x4000);
  pFVar2 = _fdopen(iVar1,pcVar4);
  local_c = pFVar2;
  pFVar3 = __iob_func();
  pFVar3 = pFVar3 + 1;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pFVar3->_ptr = pFVar2->_ptr;
    pFVar2 = (FILE *)&pFVar2->_cnt;
    pFVar3 = (FILE *)&pFVar3->_cnt;
  }
  sVar5 = 0;
  iVar1 = 4;
  pcVar4 = (char *)0x0;
  pFVar2 = __iob_func();
  setvbuf(pFVar2 + 1,pcVar4,iVar1,sVar5);
  pFVar2 = local_c;
  pFVar3 = __iob_func();
  pFVar3 = pFVar3 + 2;
  for (iVar1 = 8; iVar1 != 0; iVar1 = iVar1 + -1) {
    pFVar3->_ptr = pFVar2->_ptr;
    pFVar2 = (FILE *)&pFVar2->_cnt;
    pFVar3 = (FILE *)&pFVar3->_cnt;
  }
  sVar5 = 0;
  iVar1 = 4;
  pcVar4 = (char *)0x0;
  pFVar2 = __iob_func();
  setvbuf(pFVar2 + 2,pcVar4,iVar1,sVar5);
  return;
}

