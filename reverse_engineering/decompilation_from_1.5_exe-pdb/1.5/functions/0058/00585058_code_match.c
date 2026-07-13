/*
 * Entry: 00585058
 * Name: code_match
 * Namespace: Global
 * Signature: uchar * code_match(lzo1y_999_t * param_1, uchar * param_2, ulong param_3, ulong param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

uchar * __cdecl code_match(lzo1y_999_t *param_1,uchar *param_2,ulong param_3,ulong param_4)

{
  lzo1y_999_t *plVar1;
  byte *in_EAX;
  uchar *puVar2;
  byte bVar3;
  char cVar4;
  undefined1 *puVar5;
  byte *pbVar6;
  int unaff_EDI;
  
  plVar1 = param_1;
  *(int *)(unaff_EDI + 0x40) = (int)&param_1->init + *(int *)(unaff_EDI + 0x40);
  if (param_1 == (lzo1y_999_t *)0x2) {
    *in_EAX = ((byte)(param_2 + -1) & 3) << 2;
    in_EAX[1] = (byte)((uint)(param_2 + -1) >> 2);
    pbVar6 = in_EAX + 2;
    *(int *)(unaff_EDI + 0x54) = *(int *)(unaff_EDI + 0x54) + 1;
  }
  else {
    cVar4 = (char)param_1;
    if ((param_1 < (lzo1y_999_t *)0xf) && (param_2 < (uchar *)0x401)) {
      *in_EAX = ((byte)(param_2 + -1) & 3) << 2 | (cVar4 + '\x01') * '\x10';
      in_EAX[1] = (byte)((uint)(param_2 + -1) >> 2);
      pbVar6 = in_EAX + 2;
      *(int *)(unaff_EDI + 0x5c) = *(int *)(unaff_EDI + 0x5c) + 1;
    }
    else if ((param_1 == (lzo1y_999_t *)0x3) &&
            ((param_2 < (uchar *)0x801 && (3 < *(uint *)(unaff_EDI + 0x4c))))) {
      *in_EAX = ((byte)(param_2 + -0x401) & 3) << 2;
      in_EAX[1] = (byte)((uint)(param_2 + -0x401) >> 2);
      pbVar6 = in_EAX + 2;
      *(int *)(unaff_EDI + 0x58) = *(int *)(unaff_EDI + 0x58) + 1;
    }
    else if (param_2 < (uchar *)0x4001) {
      if (param_1 < (lzo1y_999_t *)0x22) {
        puVar5 = (undefined1 *)(uint)(byte)(cVar4 - 2U | 0x20);
      }
      else {
        puVar5 = (undefined1 *)((int)&param_1[-1].r1_m_len + 3);
        *in_EAX = 0x20;
        in_EAX = in_EAX + 1;
        if ((undefined1 *)0xff < puVar5) {
          param_1 = (lzo1y_999_t *)((uint)((int)&param_1[-3].printcount + 3U) / 0xff + 1);
          memset(in_EAX,0,param_1);
          in_EAX = in_EAX + (int)param_1;
          do {
            puVar5 = puVar5 + -0xff;
            param_1 = (lzo1y_999_t *)((int)&param_1[-1].lit3_r + 3);
          } while (param_1 != (lzo1y_999_t *)0x0);
        }
      }
      *in_EAX = (byte)puVar5;
      in_EAX[1] = (char)(param_2 + -1) << 2;
      in_EAX[2] = (byte)((uint)(param_2 + -1) >> 6);
      pbVar6 = in_EAX + 3;
      *(int *)(unaff_EDI + 0x60) = *(int *)(unaff_EDI + 0x60) + 1;
    }
    else {
      puVar2 = param_2 + -0x4000;
      bVar3 = (byte)((uint)puVar2 >> 0xb) & 8;
      if (param_1 < (lzo1y_999_t *)0xa) {
        puVar5 = (undefined1 *)(uint)(byte)(cVar4 - 2U | bVar3 | 0x10);
      }
      else {
        puVar5 = (undefined1 *)((int)&param_1[-1].lit1_r + 3);
        *in_EAX = bVar3 | 0x10;
        in_EAX = in_EAX + 1;
        if ((undefined1 *)0xff < puVar5) {
          param_1 = (lzo1y_999_t *)((uint)((int)&param_1[-3].r1_m_len + 3U) / 0xff + 1);
          memset(in_EAX,0,param_1);
          in_EAX = in_EAX + (int)param_1;
          do {
            puVar5 = puVar5 + -0xff;
            param_1 = (lzo1y_999_t *)((int)&param_1[-1].lit3_r + 3);
          } while (param_1 != (lzo1y_999_t *)0x0);
        }
      }
      *in_EAX = (byte)puVar5;
      in_EAX[1] = (char)puVar2 << 2;
      in_EAX[2] = (byte)((uint)puVar2 >> 6);
      pbVar6 = in_EAX + 3;
      *(int *)(unaff_EDI + 100) = *(int *)(unaff_EDI + 100) + 1;
    }
  }
  *(lzo1y_999_t **)(unaff_EDI + 0x10) = plVar1;
  *(uchar **)(unaff_EDI + 0x14) = param_2;
  return pbVar6;
}
