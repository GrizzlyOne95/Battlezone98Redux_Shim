
void FUN_00823d30(void)

{
  int *piVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int local_18;
  undefined4 *local_14;
  char *local_10;
  char local_5;
  
  local_14 = DAT_02cc1b40;
  do {
    fVar4 = DAT_00920ef4;
    if (local_14 == (undefined4 *)0x0) {
      return;
    }
    piVar1 = (int *)local_14[2];
    if ((piVar1[0x48] & 1U) != 0) {
      fVar2 = (float)((uint)(((DAT_02cecef0 - DAT_02cecee8) + 1) * *piVar1) / 0x280) + 0.0;
      fVar3 = (float)((uint)(((DAT_02cecef4 - DAT_02ceceec) + 1) * piVar1[1]) / 0x1e0) + 0.0;
      DAT_00920ef4 = DAT_00920ef4 + 0.01;
      FUN_0068afb0(&DAT_02cecee0,(int)fVar2,(int)fVar3,
                   (int)(((float)((double)piVar1[2] + (double)(&DAT_008a2fd0)[-(piVar1[2] >> 0x1f)])
                         + fVar2) - 1.0),
                   (int)(((float)((double)piVar1[3] + (double)(&DAT_008a2fd0)[-(piVar1[3] >> 0x1f)])
                         + fVar3) - 1.0),0,2);
      DAT_00920ef4 = fVar4;
      std::_Init_atomic_counter(DAT_0091552c,piVar1[0x47]);
      FUN_00689960(DAT_0091552c,0xffffffff);
      local_18 = 0;
      local_5 = '\0';
      for (local_10 = (char *)((int)piVar1 + piVar1[0x45] + 0x10); *local_10 != '\0';
          local_10 = local_10 + 1) {
        FUN_00689a20(DAT_0091552c,(short)*local_10);
        iVar5 = FUN_0083f040();
        if ((uint)piVar1[2] < (uint)(local_18 + iVar5)) {
          local_5 = *local_10;
          *local_10 = '\0';
          break;
        }
        local_18 = local_18 + iVar5;
      }
      FUN_00689d10(DAT_0091552c,&DAT_02cecee0,
                   (int)((float)((double)piVar1[0x46] +
                                (double)(&DAT_008a2fd0)[-(piVar1[0x46] >> 0x1f)]) + fVar2),
                   (int)fVar3,(int)piVar1 + piVar1[0x45] + 0x10);
      *local_10 = local_5;
      if ((piVar1[0x48] & 0x100U) != 0) {
        FUN_00824050(piVar1);
      }
      piVar1[0x48] = piVar1[0x48] & 0xfffffdff;
    }
    local_14 = (undefined4 *)*local_14;
  } while( true );
}

