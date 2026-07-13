/*
 * Entry: 0054b85d
 * Name: SetupRemapTable
 * Namespace: Global
 * Signature: ushort * SetupRemapTable(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

ushort * __cdecl SetupRemapTable(void)

{
  uint uVar1;
  ushort uVar2;
  
  if (done == 0) {
    uVar2 = 0xc0;
    uVar1 = 0x81;
    do {
      if (((((uVar1 != 0x85) && (uVar1 != 0x86)) && (uVar1 != 0xeb)) &&
          ((uVar1 != 0xec && (((uVar1 & 0xf0) < 0x91 || (0xdf < (uVar1 & 0xf0))))))) &&
         (((int)uVar1 < 0xef || (0xf9 < (int)uVar1)))) {
        RemapTable[uVar1] = uVar2;
        uVar2 = uVar2 + 0xc0;
      }
      uVar1 = uVar1 + 1;
    } while ((int)uVar1 < 0xfd);
    done = 1;
  }
  return RemapTable;
}
