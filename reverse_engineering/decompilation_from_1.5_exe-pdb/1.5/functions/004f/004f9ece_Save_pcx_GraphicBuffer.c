/*
 * Entry: 004f9ece
 * Name: Save_pcx_GraphicBuffer
 * Namespace: Global
 * Signature: int Save_pcx_GraphicBuffer(char * param_1, _GRAPHIC_BUFFER * param_2, RGB * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl Save_pcx_GraphicBuffer(char *param_1,_GRAPHIC_BUFFER *param_2,RGB *param_3)

{
  int iVar1;
  int iVar2;
  long unaff_EDI;
  uchar *puVar3;
  undefined1 local_3a4 [768];
  RGB *local_a4;
  uchar *local_a0;
  int local_9c;
  int local_98;
  uchar local_94;
  undefined3 uStack_93;
  FILE *local_90;
  uchar local_89;
  undefined1 local_88;
  undefined1 local_87;
  undefined1 local_86;
  undefined1 local_85;
  undefined2 local_84;
  undefined2 local_82;
  short local_80;
  short local_7e;
  undefined2 local_7c;
  undefined2 local_7a;
  undefined1 local_78;
  undefined1 local_77 [7];
  undefined1 local_70 [40];
  undefined1 local_48;
  undefined1 local_47;
  short local_46;
  undefined2 local_44;
  undefined1 local_42;
  undefined1 local_41 [57];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)local_70;
  local_a4 = param_3;
  local_84 = 0;
  local_82 = 0;
  local_7c = 0x140;
  local_7a = 200;
  iVar2 = 0;
  local_88 = 10;
  local_87 = 5;
  local_86 = 1;
  local_85 = 8;
  local_78 = 0;
  memset(local_77,0,0x2f);
  local_44 = 1;
  local_48 = 0;
  local_47 = 1;
  local_42 = 0;
  memset(local_41,0,0x39);
  local_a0 = param_2->Buffer;
  local_46 = (short)param_2->Width;
  local_80 = local_46 + -1;
  local_7e = (short)param_2->Height + -1;
  local_90 = fopen(param_1,"wb");
  if (local_90 == (FILE *)0x0) {
    iVar2 = 0;
  }
  else {
    fwrite(&local_88,1,0x80,local_90);
    local_98 = 0;
    if (0 < param_2->Height) {
      do {
        puVar3 = local_a0 + iVar2;
        iVar1 = 1;
        _local_94 = CONCAT31(uStack_93,*puVar3);
        if (param_2->Width < 2) {
LAB_004fa000:
          Encode_Data((_iobuf *)local_90,(char)_local_94,unaff_EDI);
        }
        else {
          local_9c = param_2->Width + -1;
          do {
            puVar3 = puVar3 + 1;
            local_89 = *puVar3;
            if (local_89 == local_94) {
              iVar1 = iVar1 + 1;
              if (iVar1 == 0x3f) {
                Encode_Data((_iobuf *)local_90,local_94,unaff_EDI);
                iVar1 = 0;
              }
            }
            else {
              if (iVar1 != 0) {
                Encode_Data((_iobuf *)local_90,local_94,unaff_EDI);
              }
              _local_94 = CONCAT31(uStack_93,local_89);
              iVar1 = 1;
            }
            local_9c = local_9c + -1;
          } while (local_9c != 0);
          local_9c = 0;
          if (iVar1 != 0) goto LAB_004fa000;
        }
        local_98 = local_98 + 1;
        iVar2 = iVar2 + param_2->Width;
      } while (local_98 < param_2->Height);
    }
    memmove(local_3a4,local_a4,0x300);
    fputc(0xc,local_90);
    fwrite(local_3a4,3,0x100,local_90);
    fclose(local_90);
    iVar2 = 1;
  }
  return iVar2;
}
