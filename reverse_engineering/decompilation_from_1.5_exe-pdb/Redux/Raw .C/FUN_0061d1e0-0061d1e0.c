
bool FUN_0061d1e0(short param_1)

{
  int iVar1;
  bool bVar2;
  
  bVar2 = ((int)param_1 & 0xff00U) == 0x300;
  if (bVar2) {
    memmove(&DAT_02cebcc0,&DAT_02cebcc1,0xe);
    iVar1 = tolower((int)param_1 & 0xff);
    DAT_02cebcce = (undefined1)iVar1;
  }
  return bVar2;
}

