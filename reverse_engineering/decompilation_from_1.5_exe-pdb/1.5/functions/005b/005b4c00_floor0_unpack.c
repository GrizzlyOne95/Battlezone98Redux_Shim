/*
 * Entry: 005b4c00
 * Name: floor0_unpack
 * Namespace: Global
 * Signature: void * floor0_unpack(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl floor0_unpack(vorbis_info *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  int *piVar2;
  int *_Memory;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  pvVar1 = param_1->codec_setup;
  _Memory = malloc(0x60);
  iVar3 = oggpack_read(param_2,8);
  *_Memory = iVar3;
  iVar3 = oggpack_read(param_2,0x10);
  _Memory[1] = iVar3;
  iVar3 = oggpack_read(param_2,0x10);
  _Memory[2] = iVar3;
  iVar3 = oggpack_read(param_2,6);
  _Memory[3] = iVar3;
  iVar3 = oggpack_read(param_2,8);
  _Memory[4] = iVar3;
  iVar3 = oggpack_read(param_2,4);
  iVar3 = iVar3 + 1;
  _Memory[5] = iVar3;
  if ((((0 < *_Memory) && (0 < _Memory[1])) && (0 < _Memory[2])) && (0 < iVar3)) {
    iVar5 = 0;
    if (0 < iVar3) {
      piVar4 = _Memory + 6;
      do {
        iVar3 = oggpack_read(param_2,8);
        *piVar4 = iVar3;
        if (((iVar3 < 0) || (*(int *)((int)pvVar1 + 0x18) <= iVar3)) ||
           ((piVar2 = *(int **)((int)pvVar1 + iVar3 * 4 + 0x720), piVar2[3] == 0 || (*piVar2 < 1))))
        goto LAB_005b4cbe;
        iVar5 = iVar5 + 1;
        piVar4 = piVar4 + 1;
      } while (iVar5 < _Memory[5]);
    }
    return _Memory;
  }
LAB_005b4cbe:
  memset(_Memory,0,0x60);
  free(_Memory);
  return (void *)0x0;
}
