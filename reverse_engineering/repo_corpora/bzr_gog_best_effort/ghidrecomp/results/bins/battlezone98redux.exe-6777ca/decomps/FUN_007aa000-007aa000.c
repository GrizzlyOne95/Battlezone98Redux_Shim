
void FUN_007aa000(void)

{
  int iVar1;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_008608b0;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_8 = 0;
  iVar1 = FUN_00684ca0(0);
  if (iVar1 != 0) {
    FUN_0067cb70(0,0,0);
    FUN_0067ccf0(0,0x3f800000,0x41100000,0,0,0);
    if (DAT_0094554a == '\0') {
      if (DAT_00945588 != 0) {
        if (DAT_0094554b == '\0') {
          FUN_006618b0(0);
        }
        else {
          DAT_00945590 = DAT_00945590 + DAT_00920e90;
          switch(DAT_0094558c) {
          case 0:
            DAT_00945594 = 0.0;
            if (10.0 <= DAT_00945590) {
              DAT_00945590 = 0.0;
              DAT_0094558c = 1;
            }
            break;
          case 1:
            DAT_00945594 = 1.0 - (4.0 - DAT_00945590) / 4.0;
            if (1.0 < DAT_00945594) {
              DAT_00945594 = 1.0;
            }
            if (DAT_00945594 < 0.0) {
              DAT_00945594 = 0.0;
            }
            if (4.0 <= DAT_00945590) {
              DAT_00945590 = 0.0;
              DAT_0094558c = 2;
            }
            break;
          case 2:
            DAT_00945594 = 1.0;
            if (2.0 <= DAT_00945590) {
              DAT_00945590 = 0.0;
              DAT_0094558c = 3;
            }
            break;
          case 3:
            DAT_00945594 = (4.0 - DAT_00945590) / 4.0;
            if (1.0 < DAT_00945594) {
              DAT_00945594 = 1.0;
            }
            if (DAT_00945594 < 0.0) {
              DAT_00945594 = 0.0;
            }
            if (4.0 <= DAT_00945590) {
              DAT_00945590 = 0.0;
              DAT_0094558c = 0;
            }
          }
          FUN_006618b0(DAT_00945594);
        }
      }
      FUN_0067ce80();
    }
  }
  FUN_007aa321();
  return;
}

