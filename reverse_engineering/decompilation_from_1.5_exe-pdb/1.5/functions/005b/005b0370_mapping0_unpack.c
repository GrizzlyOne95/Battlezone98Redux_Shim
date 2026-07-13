/*
 * Entry: 005b0370
 * Name: mapping0_unpack
 * Namespace: Global
 * Signature: void * mapping0_unpack(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl mapping0_unpack(vorbis_info *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  int *_Memory;
  int iVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int local_8;
  
  _Memory = calloc(1,0xc88);
  pvVar1 = param_1->codec_setup;
  memset(_Memory,0,0xc88);
  iVar2 = oggpack_read(param_2,1);
  if (-1 < iVar2) {
    if (iVar2 == 0) {
      *_Memory = 1;
    }
    else {
      iVar2 = oggpack_read(param_2,4);
      *_Memory = iVar2 + 1;
      if (iVar2 + 1 < 1) goto LAB_005b03c6;
    }
    iVar2 = oggpack_read(param_2,1);
    if (-1 < iVar2) {
      if (iVar2 != 0) {
        iVar2 = oggpack_read(param_2,8);
        _Memory[0x121] = iVar2 + 1;
        if (iVar2 + 1 < 1) goto LAB_005b03c6;
        local_8 = 0;
        piVar5 = _Memory + 0x222;
        do {
          iVar2 = 0;
          if (param_1->channels != 0) {
            for (uVar4 = param_1->channels - 1; uVar4 != 0; uVar4 = uVar4 >> 1) {
              iVar2 = iVar2 + 1;
            }
          }
          iVar3 = oggpack_read(param_2,iVar2);
          piVar5[-0x100] = iVar3;
          iVar2 = 0;
          if (param_1->channels != 0) {
            for (uVar4 = param_1->channels - 1; uVar4 != 0; uVar4 = uVar4 >> 1) {
              iVar2 = iVar2 + 1;
            }
          }
          iVar2 = oggpack_read(param_2,iVar2);
          *piVar5 = iVar2;
          if ((((iVar3 < 0) || (iVar2 < 0)) || (iVar3 == iVar2)) ||
             ((param_1->channels <= iVar3 || (param_1->channels <= iVar2)))) goto LAB_005b03c6;
          local_8 = local_8 + 1;
          piVar5 = piVar5 + 1;
        } while (local_8 < _Memory[0x121]);
      }
      iVar2 = oggpack_read(param_2,2);
      if (iVar2 == 0) {
        if ((1 < *_Memory) && (iVar2 = 0, piVar5 = _Memory, 0 < param_1->channels)) {
          do {
            iVar3 = oggpack_read(param_2,4);
            piVar5[1] = iVar3;
            if ((*_Memory <= iVar3) || (iVar3 < 0)) goto LAB_005b03c6;
            iVar2 = iVar2 + 1;
            piVar5 = piVar5 + 1;
          } while (iVar2 < param_1->channels);
        }
        iVar2 = 0;
        if (0 < *_Memory) {
          piVar5 = _Memory + 0x111;
          do {
            oggpack_read(param_2,8);
            iVar3 = oggpack_read(param_2,8);
            piVar5[-0x10] = iVar3;
            if ((*(int *)((int)pvVar1 + 0x10) <= iVar3) || (iVar3 < 0)) goto LAB_005b03c6;
            iVar3 = oggpack_read(param_2,8);
            *piVar5 = iVar3;
            if ((*(int *)((int)pvVar1 + 0x14) <= iVar3) || (iVar3 < 0)) goto LAB_005b03c6;
            iVar2 = iVar2 + 1;
            piVar5 = piVar5 + 1;
          } while (iVar2 < *_Memory);
        }
        return _Memory;
      }
    }
  }
LAB_005b03c6:
  if (_Memory != (int *)0x0) {
    memset(_Memory,0,0xc88);
    free(_Memory);
  }
  return (void *)0x0;
}
