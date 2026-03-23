
/* WARNING: Removing unreachable block (ram,0x00785ce0) */
/* WARNING: Removing unreachable block (ram,0x00785cc3) */
/* WARNING: Removing unreachable block (ram,0x00785cfe) */

void FUN_00785c80(int param_1,int param_2,void *param_3)

{
  int iVar1;
  void *_Dst;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int local_20;
  int local_18;
  int local_14;
  int local_10;
  uint local_c;
  uint local_8;
  
  iVar1 = param_1 * 0x100;
  param_2 = param_2 * 0x100;
  if ((param_3 != (void *)0x0) && (_Dst = malloc(param_1 * 0x200 * param_2), _Dst != (void *)0x0)) {
    memcpy(_Dst,param_3,param_1 * 0x200 * param_2);
    for (local_c = 0; (int)local_c < param_2; local_c = local_c + 1) {
      for (local_8 = 0; (int)local_8 < iVar1; local_8 = local_8 + 1) {
        iVar4 = local_8 - (local_8 & 0xff);
        iVar5 = local_c - (local_c & 0xff);
        local_18 = 0;
        local_20 = 0;
        for (local_14 = -1; local_14 < 2; local_14 = local_14 + 1) {
          for (local_10 = -1; local_10 < 2; local_10 = local_10 + 1) {
            if ((((-1 < (int)(local_8 + local_10)) && ((int)(local_8 + local_10) < iVar1)) &&
                (-1 < (int)(local_c + local_14))) && ((int)(local_c + local_14) < param_2)) {
              iVar2 = (local_8 + local_10) - (local_8 + local_10 & 0xff);
              iVar3 = (local_c + local_14) - (local_c + local_14 & 0xff);
              local_18 = (uint)*(ushort *)
                                ((int)_Dst +
                                ((local_8 + local_10 & 0xff) + (local_c + local_14 & 0xff) * 0x100 +
                                (((int)(iVar2 + (iVar2 >> 0x1f & 0xffU)) >> 8) +
                                ((uint)(((int)(iVar3 + (iVar3 >> 0x1f & 0xffU)) >> 8) * iVar1) >> 8)
                                ) * 0x10000) * 2) + local_18;
              local_20 = local_20 + 1;
            }
          }
        }
        local_18._0_2_ = (undefined2)((uint)(local_20 + local_18 * 2) / (uint)(local_20 << 1));
        *(undefined2 *)
         ((int)param_3 +
         ((local_8 & 0xff) + (local_c & 0xff) * 0x100 +
         (((int)(iVar4 + (iVar4 >> 0x1f & 0xffU)) >> 8) +
         ((uint)(((int)(iVar5 + (iVar5 >> 0x1f & 0xffU)) >> 8) * iVar1) >> 8)) * 0x10000) * 2) =
             (undefined2)local_18;
      }
    }
    free(_Dst);
  }
  return;
}

