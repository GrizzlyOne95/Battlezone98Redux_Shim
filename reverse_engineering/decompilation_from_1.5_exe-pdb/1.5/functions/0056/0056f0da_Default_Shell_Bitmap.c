/*
 * Entry: 0056f0da
 * Name: Default_Shell_Bitmap
 * Namespace: Global
 * Signature: int Default_Shell_Bitmap(tagRGBQUAD * param_1, tagBITMAPINFO * * param_2, void * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Default_Shell_Bitmap(tagRGBQUAD *param_1,tagBITMAPINFO **param_2,void **param_3)

{
  undefined4 *puVar1;
  tagRGBQUAD tVar2;
  undefined2 *puVar3;
  int iVar4;
  size_t _Size;
  int *unaff_EDI;
  
  puVar1 = malloc(0x42c);
  *unaff_EDI = (int)puVar1;
  if (puVar1 == (undefined4 *)0x0) {
    return 0;
  }
  puVar1[1] = 0x10;
  puVar1[2] = 0x10;
  *(undefined2 *)(puVar1 + 3) = 1;
  *(undefined2 *)((int)puVar1 + 0xe) = 0x18;
  *puVar1 = 0x28;
  puVar1[6] = 0xb12;
  puVar1[7] = 0xb12;
  puVar1[4] = 0;
  puVar1[5] = 0;
  puVar1[8] = 0;
  puVar1[9] = 0;
  puVar3 = (undefined2 *)(*unaff_EDI + 0x28);
  iVar4 = 0;
  do {
    *puVar3 = (short)iVar4;
    puVar3 = puVar3 + 1;
    iVar4 = iVar4 + 1;
  } while (iVar4 < 0x100);
  _Size = puVar1[2] * puVar1[1] * 3;
  tVar2 = (tagRGBQUAD)malloc(_Size);
  *param_1 = tVar2;
  if (tVar2 != (tagRGBQUAD)0x0) {
    memset(tVar2,0,_Size);
  }
  else {
    free((void *)*unaff_EDI);
    *unaff_EDI = 0;
  }
  return (uint)(tVar2 != (tagRGBQUAD)0x0);
}
