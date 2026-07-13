/*
 * Entry: 0059ff40
 * Name: _vorbis_unpack_books
 * Namespace: Global
 * Signature: int _vorbis_unpack_books(vorbis_info * param_1, oggpack_buffer * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _vorbis_unpack_books(vorbis_info *param_1,oggpack_buffer *param_2)

{
  void *pvVar1;
  int iVar2;
  static_codebook *psVar3;
  int iVar4;
  void *pvVar5;
  undefined4 uVar6;
  undefined4 *puVar7;
  oggpack_buffer *unaff_ESI;
  int iVar8;
  int *piVar9;
  
  pvVar1 = param_1->codec_setup;
  if (pvVar1 == (void *)0x0) {
    return -0x81;
  }
  iVar2 = oggpack_read();
  iVar2 = iVar2 + 1;
  *(int *)((int)pvVar1 + 0x18) = iVar2;
  if (0 < iVar2) {
    iVar8 = 0;
    if (0 < iVar2) {
      puVar7 = (undefined4 *)((int)pvVar1 + 0x720);
      do {
        psVar3 = vorbis_staticbook_unpack(unaff_ESI);
        *puVar7 = psVar3;
        if (psVar3 == (static_codebook *)0x0) goto LAB_005a01bf;
        iVar8 = iVar8 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar8 < *(int *)((int)pvVar1 + 0x18));
    }
    iVar2 = oggpack_read();
    iVar2 = iVar2 + 1;
    if (0 < iVar2) {
      iVar8 = 0;
      if (0 < iVar2) {
        do {
          iVar4 = oggpack_read();
          if (iVar4 != 0) goto LAB_005a01bf;
          iVar8 = iVar8 + 1;
        } while (iVar8 < iVar2);
      }
      iVar2 = oggpack_read();
      iVar2 = iVar2 + 1;
      *(int *)((int)pvVar1 + 0x10) = iVar2;
      if (0 < iVar2) {
        iVar8 = 0;
        if (0 < iVar2) {
          piVar9 = (int *)((int)pvVar1 + 0x420);
          do {
            iVar2 = oggpack_read();
            piVar9[-0x40] = iVar2;
            if ((iVar2 < 0) || (1 < iVar2)) goto LAB_005a01bf;
            iVar2 = (**(code **)(*(int *)(&_floor_P + iVar2 * 4) + 4))(param_1);
            *piVar9 = iVar2;
            if (iVar2 == 0) goto LAB_005a01bf;
            iVar8 = iVar8 + 1;
            piVar9 = piVar9 + 1;
          } while (iVar8 < *(int *)((int)pvVar1 + 0x10));
        }
        iVar2 = oggpack_read();
        iVar2 = iVar2 + 1;
        *(int *)((int)pvVar1 + 0x14) = iVar2;
        if (0 < iVar2) {
          iVar8 = 0;
          if (0 < iVar2) {
            piVar9 = (int *)((int)pvVar1 + 0x620);
            do {
              iVar2 = oggpack_read();
              piVar9[-0x40] = iVar2;
              if ((iVar2 < 0) || (2 < iVar2)) goto LAB_005a01bf;
              iVar2 = (**(code **)(*(int *)(&_residue_P + iVar2 * 4) + 4))(param_1);
              *piVar9 = iVar2;
              if (iVar2 == 0) goto LAB_005a01bf;
              iVar8 = iVar8 + 1;
              piVar9 = piVar9 + 1;
            } while (iVar8 < *(int *)((int)pvVar1 + 0x14));
          }
          iVar2 = oggpack_read();
          iVar2 = iVar2 + 1;
          *(int *)((int)pvVar1 + 0xc) = iVar2;
          if (0 < iVar2) {
            iVar8 = 0;
            if (0 < iVar2) {
              piVar9 = (int *)((int)pvVar1 + 0x220);
              do {
                iVar2 = oggpack_read();
                piVar9[-0x40] = iVar2;
                if ((iVar2 < 0) || (0 < iVar2)) goto LAB_005a01bf;
                iVar2 = (**(code **)(*(int *)(&_mapping_P + iVar2 * 4) + 4))(param_1);
                *piVar9 = iVar2;
                if (iVar2 == 0) goto LAB_005a01bf;
                iVar8 = iVar8 + 1;
                piVar9 = piVar9 + 1;
              } while (iVar8 < *(int *)((int)pvVar1 + 0xc));
            }
            iVar2 = oggpack_read();
            iVar2 = iVar2 + 1;
            *(int *)((int)pvVar1 + 8) = iVar2;
            if (0 < iVar2) {
              iVar8 = 0;
              if (0 < iVar2) {
                piVar9 = (int *)((int)pvVar1 + 0x20);
                do {
                  pvVar5 = calloc(1,0x10);
                  *piVar9 = (int)pvVar5;
                  uVar6 = oggpack_read();
                  *(undefined4 *)*piVar9 = uVar6;
                  uVar6 = oggpack_read();
                  *(undefined4 *)(*piVar9 + 4) = uVar6;
                  uVar6 = oggpack_read();
                  *(undefined4 *)(*piVar9 + 8) = uVar6;
                  uVar6 = oggpack_read();
                  *(undefined4 *)(*piVar9 + 0xc) = uVar6;
                  iVar2 = *piVar9;
                  if ((((0 < *(int *)(iVar2 + 4)) || (0 < *(int *)(iVar2 + 8))) ||
                      (*(int *)((int)pvVar1 + 0xc) <= *(int *)(iVar2 + 0xc))) ||
                     (*(int *)(iVar2 + 0xc) < 0)) goto LAB_005a01bf;
                  iVar8 = iVar8 + 1;
                  piVar9 = piVar9 + 1;
                } while (iVar8 < *(int *)((int)pvVar1 + 8));
              }
              iVar2 = oggpack_read();
              if (iVar2 == 1) {
                return 0;
              }
            }
          }
        }
      }
    }
  }
LAB_005a01bf:
  vorbis_info_clear(param_1);
  return -0x85;
}
