/*
 * Entry: 004f47f9
 * Name: Graphic_Buffer_Init_Ex
 * Namespace: Global
 * Signature: _GRAPHIC_BUFFER * Graphic_Buffer_Init_Ex(_GRAPHIC_BUFFER * __return_storage_ptr__, long param_1, long param_2, char * param_3, GRAPHIC_BUF_BITDEPTH param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

_GRAPHIC_BUFFER * __cdecl
Graphic_Buffer_Init_Ex
          (_GRAPHIC_BUFFER *__return_storage_ptr__,long param_1,long param_2,char *param_3,
          GRAPHIC_BUF_BITDEPTH param_4)

{
  uchar *puVar1;
  uint uVar2;
  
  memset(__return_storage_ptr__,0,0x34);
  uVar2 = param_1 * param_2;
  if (param_4 == WORD_FORMAT) {
    uVar2 = uVar2 * 2;
  }
  if (0 < (int)uVar2) {
    if (param_3 == (char *)0x0) {
      puVar1 = malloc(uVar2 + 0x20);
      __return_storage_ptr__->OrBuffer = puVar1;
      if (puVar1 == (uchar *)0x0) {
        return __return_storage_ptr__;
      }
      __return_storage_ptr__->Buffer = (uchar *)((uint)(puVar1 + 0x1f) & 0xffffffe0);
    }
    else {
      __return_storage_ptr__->OrBuffer = (uchar *)0x0;
      __return_storage_ptr__->Buffer = (uchar *)param_3;
      __return_storage_ptr__->Allocated = 1;
    }
    __return_storage_ptr__->Width = param_1;
    __return_storage_ptr__->SizeByteAmount = uVar2 & 0x1f;
    __return_storage_ptr__->Height = param_2;
    __return_storage_ptr__->SizeWordAmount = (int)uVar2 >> 2;
    __return_storage_ptr__->Bit_Depth = param_4;
    (__return_storage_ptr__->Pane).x1 = param_1 + -1;
    (__return_storage_ptr__->Pane).y1 = param_2 + -1;
    __return_storage_ptr__->Status = 1;
  }
  return __return_storage_ptr__;
}
