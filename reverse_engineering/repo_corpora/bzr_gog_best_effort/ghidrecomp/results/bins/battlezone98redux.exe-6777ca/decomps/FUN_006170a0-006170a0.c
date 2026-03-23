
bool FUN_006170a0(void)

{
  int iVar1;
  
  DAT_009467b4 = 0;
  DAT_025cfa1c = *(undefined4 *)(DAT_0094672c + 0x40);
  iVar1 = FUN_004fc490(&DAT_00945708,0);
  if (iVar1 != 0) {
    *(undefined4 *)(DAT_0094672c + 0x40) = DAT_025cfa1c;
  }
  else {
    FUN_0081e0c0("Quiting Game because failed to load game files\n");
    FUN_00434170(2);
    FUN_00437620(1);
  }
  return iVar1 != 0;
}

