
bool FUN_00829400(void)

{
  bool bVar1;
  
  bVar1 = DAT_009468c4 != 0;
  if (bVar1) {
    FUN_00828710();
    free((void *)DAT_009468cc);
    DAT_009468cc = DAT_009468c4;
    DAT_009468c4 = 0;
    FUN_0075f750(&DAT_0260c204);
    FUN_008296f0();
    DAT_009468c0 = DAT_009468c8;
    DAT_009468c8 = 0;
  }
  return bVar1;
}

