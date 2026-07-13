/*
 * Entry: 005253ba
 * Name: compressData
 * Namespace: Global
 * Signature: void * compressData(void * param_1, int param_2, int * param_3, int * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: _chkstk replaced with injection: alloca_probe */
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void * __cdecl compressData(void *param_1,int param_2,int *param_3,int *param_4)

{
  uint uVar1;
  int iVar2;
  uchar *puVar3;
  uchar *puStack_7003c;
  uint uStack_70038;
  undefined1 *puStack_70034;
  ulong uStack_70030;
  uchar *puStack_7002c;
  uint uStack_70028;
  uchar *puStack_70024;
  uchar *puStack_70020;
  uchar *puStack_7001c;
  undefined1 auStack_70018 [458772];
  
  puStack_7002c = param_1;
  uVar1 = __lzo_align_gap(auStack_70018,0x10);
  puStack_70034 = auStack_70018 + uVar1;
  puStack_7001c = (uchar *)(((int)(param_2 + (param_2 >> 0x1f & 0x3fU)) >> 6) + 0x13 + param_2);
  puStack_70020 = allocBuf((int)puStack_7001c);
  puStack_70024 = allocBuf((int)puStack_7001c);
  puStack_7001c = allocBuf(param_2);
  puStack_7003c = (uchar *)0x0;
  uStack_70030 = param_2;
  if ((LZOIsInitialized != 0) || (iVar2 = initLZO(), iVar2 != 0)) {
    puVar3 = puStack_7002c;
    iVar2 = lzo1x_999_compress(puStack_7002c,param_2,puStack_70020,&uStack_70038,puStack_70034);
    iVar2 = lzoCheck(iVar2,(char *)puVar3);
    if (iVar2 != 0) {
      puVar3 = puStack_7002c;
      iVar2 = lzo1y_999_compress(puStack_7002c,param_2,puStack_70024,&uStack_70028,puStack_70034);
      iVar2 = lzoCheck(iVar2,(char *)puVar3);
      if (iVar2 != 0) {
        if ((uStack_70028 < uStack_70038) || ((uint)param_2 <= uStack_70038)) {
          if (uStack_70028 < (uint)param_2) {
            puVar3 = puStack_70024;
            iVar2 = lzo1y_optimize(puStack_70024,uStack_70028,puStack_7001c,&uStack_70030,
                                   (void *)0x0);
            iVar2 = lzoCheck(iVar2,(char *)puVar3);
            if (iVar2 != 0) {
              freeBuf(puStack_70020);
              freeBuf(puStack_7001c);
              *param_3 = uStack_70028;
              *param_4 = param_2 << 8 | 4;
              return puStack_70024;
            }
          }
          else {
            *param_3 = param_2;
            *param_4 = 0;
            puStack_7003c = puStack_7002c;
          }
        }
        else {
          puVar3 = puStack_70020;
          iVar2 = lzo1x_optimize(puStack_70020,uStack_70038,puStack_7001c,&uStack_70030,(void *)0x0)
          ;
          iVar2 = lzoCheck(iVar2,(char *)puVar3);
          if (iVar2 != 0) {
            freeBuf(puStack_70024);
            freeBuf(puStack_7001c);
            *param_3 = uStack_70038;
            *param_4 = param_2 << 8 | 2;
            return puStack_70020;
          }
        }
      }
    }
  }
  freeBuf(puStack_70020);
  freeBuf(puStack_70024);
  freeBuf(puStack_7001c);
  return puStack_7003c;
}
