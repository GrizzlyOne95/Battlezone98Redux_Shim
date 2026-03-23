
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_00617b20(void)

{
  uint uVar1;
  int iVar2;
  float10 fVar3;
  float fVar4;
  uint local_8;
  
  uVar1 = FUN_00822e60();
  DAT_009183e0 = 1;
  DAT_02a13e84 = DAT_02a13e84 + 1;
  if (DAT_02a13df0 + 1000 < uVar1) {
    fVar4 = ((float)DAT_02a13e84 * 1000.0) /
            (float)((double)(int)(uVar1 - DAT_02a13df0) +
                   (double)(&DAT_008a2fd0)[-((int)(uVar1 - DAT_02a13df0) >> 0x1f)]);
    iVar2 = DAT_02ceef80 / DAT_02a13e84;
    DAT_02ceffe0 = (int)(1000.0 / fVar4);
    DAT_02a13e84 = 0;
    DAT_02ceef80 = 0;
    if (DAT_02a13e28 < fVar4) {
      DAT_02a13e28 = fVar4;
    }
    if (fVar4 < DAT_02a13e2c) {
      DAT_02a13e2c = fVar4;
    }
    if (DAT_02a13e7c < fVar4) {
      DAT_02a13e7c = fVar4;
    }
    if (fVar4 < DAT_02a13df4) {
      DAT_02a13df4 = fVar4;
    }
    DAT_02a13df0 = uVar1;
    if (DAT_009183c0 != 0) {
      sprintf(&DAT_02a13e38,"%4.1f-(%d)",SUB84((double)fVar4,0),
              (int)((ulonglong)(double)fVar4 >> 0x20),iVar2);
      fVar3 = (float10)FUN_00689cb0(DAT_0091552c,&DAT_02a13e38);
      _DAT_02a13e78 = (int)((float)fVar3 + 4.0);
    }
    if (DAT_02a13dfc + 60000 < uVar1) {
      FUN_0081e0c0("Frame rates over last minute: Max FPS %f, Min FPS %f\n",(double)DAT_02a13e7c,
                   (double)DAT_02a13df4);
      DAT_02a13df4 = 100000.0;
      DAT_02a13e7c = 0.0;
      DAT_02a13dfc = uVar1;
    }
    if ((fVar4 < DAT_008eaabc) || (DAT_02a13e00 != 0 || DAT_02a13e04 != 0)) {
      for (local_8 = 0; local_8 < 5; local_8 = local_8 + 1) {
        if ((fVar4 < (&DAT_008eaabc)[local_8]) &&
           ((&DAT_02a13e00)[local_8 * 2] == 0 && (&DAT_02a13e04)[local_8 * 2] == 0)) {
          (&DAT_02a13e00)[local_8 * 2] = uVar1;
          (&DAT_02a13e04)[local_8 * 2] = 0;
          FUN_0081e0c0("Frame Rate Dropped Lower Than %.0f\n",(double)(&DAT_008eaabc)[local_8]);
        }
      }
      for (local_8 = 4; -1 < (int)local_8; local_8 = local_8 + -1) {
        if (((&DAT_008eaabc)[local_8] <= fVar4) &&
           ((&DAT_02a13e00)[local_8 * 2] != 0 || (&DAT_02a13e04)[local_8 * 2] != 0)) {
          FUN_0081e0c0("Frame Rate Back Above %.0f, spent %ld ms under limit\n",
                       (double)(&DAT_008eaabc)[local_8],uVar1 - (&DAT_02a13e00)[local_8 * 2]);
          (&DAT_02a13e00)[local_8 * 2] = 0;
          (&DAT_02a13e04)[local_8 * 2] = 0;
        }
      }
    }
  }
  return;
}

