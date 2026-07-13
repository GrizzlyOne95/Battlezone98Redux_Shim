/*
 * Entry: 005b1690
 * Name: res0_unpack
 * Namespace: Global
 * Signature: void * res0_unpack(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void * __cdecl res0_unpack(vorbis_info *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  undefined4 *_Memory;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  int local_8;
  
  iVar7 = 0;
  local_8 = 0;
  _Memory = calloc(1,0xb18);
  pvVar1 = param_1->codec_setup;
  uVar2 = oggpack_read(param_2,0x18);
  *_Memory = uVar2;
  uVar2 = oggpack_read(param_2,0x18);
  _Memory[1] = uVar2;
  iVar3 = oggpack_read(param_2,0x18);
  _Memory[2] = iVar3 + 1;
  iVar3 = oggpack_read(param_2,6);
  _Memory[3] = iVar3 + 1;
  iVar3 = oggpack_read(param_2,8);
  _Memory[5] = iVar3;
  if (-1 < iVar3) {
    if (0 < (int)_Memory[3]) {
      param_1 = (vorbis_info *)(_Memory + 6);
      do {
        uVar4 = oggpack_read(param_2,3);
        iVar3 = oggpack_read(param_2,1);
        if (iVar3 < 0) goto LAB_005b181b;
        if (iVar3 != 0) {
          iVar3 = oggpack_read(param_2,5);
          if (iVar3 < 0) goto LAB_005b181b;
          uVar4 = uVar4 | iVar3 * 8;
        }
        iVar3 = 0;
        param_1->version = uVar4;
        for (; uVar4 != 0; uVar4 = uVar4 >> 1) {
          iVar3 = iVar3 + (uVar4 & 1);
        }
        local_8 = local_8 + iVar3;
        param_1 = (vorbis_info *)&param_1->channels;
        iVar7 = iVar7 + 1;
      } while (iVar7 < (int)_Memory[3]);
    }
    iVar3 = 0;
    if (0 < local_8) {
      piVar6 = _Memory + 0x46;
      do {
        iVar7 = oggpack_read(param_2,8);
        if (iVar7 < 0) goto LAB_005b181b;
        *piVar6 = iVar7;
        iVar3 = iVar3 + 1;
        piVar6 = piVar6 + 1;
      } while (iVar3 < local_8);
    }
    if ((int)_Memory[5] < *(int *)((int)pvVar1 + 0x18)) {
      iVar3 = 0;
      if (0 < local_8) {
        piVar6 = _Memory + 0x46;
        do {
          if ((*(int *)((int)pvVar1 + 0x18) <= *piVar6) ||
             (*(int *)(*(int *)((int)pvVar1 + *piVar6 * 4 + 0x720) + 0xc) == 0)) goto LAB_005b181b;
          iVar3 = iVar3 + 1;
          piVar6 = piVar6 + 1;
        } while (iVar3 < local_8);
      }
      piVar6 = *(int **)((int)pvVar1 + _Memory[5] * 4 + 0x720);
      iVar3 = piVar6[1];
      iVar7 = *piVar6;
      iVar5 = 1;
      if (0 < iVar7) {
        if (0 < iVar7) {
          do {
            iVar5 = iVar5 * _Memory[3];
            if (iVar5 - iVar3 != 0 && iVar3 <= iVar5) goto LAB_005b181b;
            iVar7 = iVar7 + -1;
          } while (0 < iVar7);
        }
        _Memory[4] = iVar5;
        return _Memory;
      }
    }
  }
LAB_005b181b:
  memset(_Memory,0,0xb18);
  free(_Memory);
  return (void *)0x0;
}
