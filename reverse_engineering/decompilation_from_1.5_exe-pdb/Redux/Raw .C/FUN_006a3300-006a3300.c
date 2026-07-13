
void FUN_006a3300(int param_1)

{
  int iVar1;
  char cVar2;
  int local_d8;
  int local_d4;
  char local_d0 [200];
  uint local_8;
  
  local_8 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  cVar2 = FUN_006a07b0(0x4000);
  if (cVar2 != '\0') {
    for (local_d4 = 0; local_d4 < *(int *)(param_1 + 0x78); local_d4 = local_d4 + 1) {
      for (local_d8 = 0; local_d8 < *(int *)(param_1 + 0x7c); local_d8 = local_d8 + 1) {
        iVar1 = *(int *)(*(int *)(*(int *)(param_1 + 0x80) + local_d4 * 4) + local_d8 * 4);
        if (*(int *)(iVar1 + 4) != 0) {
          sprintf(local_d0,"%d %d %c %f min %d max %d",local_d8,local_d4,
                  (int)s__DASEMP_008fe75c[*(int *)(iVar1 + 4)],(double)*(float *)(iVar1 + 0x1c),
                  *(undefined4 *)(iVar1 + 0x10),*(undefined4 *)(iVar1 + 0xc));
          FUN_006a60f0(local_d0);
        }
      }
    }
    if (DAT_009310b8 != 0) {
      sprintf(local_d0,"user at: %d %d",
              (int)(*(int *)(DAT_009310b8 + 0x14) + (*(int *)(DAT_009310b8 + 0x14) >> 0x1f & 0xfU))
              >> 4,(int)(*(int *)(DAT_009310b8 + 0x18) +
                        (*(int *)(DAT_009310b8 + 0x18) >> 0x1f & 0xfU)) >> 4);
      FUN_006a60f0(local_d0);
    }
  }
  FUN_0083e885();
  return;
}

