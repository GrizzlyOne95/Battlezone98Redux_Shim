/*
 * Entry: 00584808
 * Name: swd_insertdict
 * Namespace: Global
 * Signature: void swd_insertdict(lzo1y_999_swd_t * param_1, ulong param_2, ulong param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl swd_insertdict(lzo1y_999_swd_t *param_1,ulong param_2,ulong param_3)

{
  byte *pbVar1;
  short *psVar2;
  ushort uVar3;
  int *in_EAX;
  uint uVar4;
  ushort *puVar5;
  short *psVar6;
  short sVar7;
  
  in_EAX[0x59] = *in_EAX - param_2;
  in_EAX[0x5a] = (int)param_1;
  if (param_2 != 0) {
    puVar5 = (ushort *)((int)(in_EAX + 0x5b) + (int)param_1);
    psVar6 = (short *)((int)in_EAX + (int)param_1 * 2 + 0x2e16a);
    do {
      pbVar1 = (byte *)((((int)in_EAX + 0x16e) - (int)(in_EAX + 0x5b)) + (int)puVar5);
      uVar4 = (((uint)pbVar1[(int)in_EAX + (0x16d - ((int)in_EAX + 0x16e))] ^
               (uint)(byte)*puVar5 << 5) << 5 ^ (uint)*pbVar1) * 0x9f5f >> 5 & 0x3fff;
      psVar2 = (short *)((int)in_EAX + uVar4 * 2 + 0x47168);
      sVar7 = -1;
      if (*psVar2 != 0) {
        sVar7 = *(short *)((int)in_EAX + uVar4 * 2 + 0xd16c);
      }
      psVar6[-0xc7ff] = sVar7;
      *(undefined2 *)((int)in_EAX + uVar4 * 2 + 0xd16c) = param_1._0_2_;
      *psVar6 = (short)in_EAX[1] + 1;
      *psVar2 = *psVar2 + 1;
      uVar3 = *puVar5;
      psVar6 = psVar6 + 1;
      puVar5 = (ushort *)((int)puVar5 + 1);
      param_2 = param_2 - 1;
      *(undefined2 *)((int)in_EAX + (uint)uVar3 * 2 + 0x4f168) = param_1._0_2_;
      param_1 = (lzo1y_999_swd_t *)((int)&param_1->swd_n + 1);
    } while (param_2 != 0);
  }
  return;
}
