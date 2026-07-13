
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00572ad0(void)

{
  char cVar1;
  float10 fVar2;
  float local_8;
  
  cVar1 = FUN_00571c50();
  if ((cVar1 == '\0') && (DAT_009183f8 != 1)) {
    DAT_008e8d04 = DAT_008e8d04 + -1;
    FUN_006260f0();
  }
  if (DAT_008e8d04 < 1) {
    local_8 = 5.0;
  }
  else {
    local_8 = 2.0;
  }
  fVar2 = (float10)FUN_00822da0();
  _DAT_009183f0 = (float)fVar2 + local_8;
  DAT_009183f8 = 1;
  return;
}

