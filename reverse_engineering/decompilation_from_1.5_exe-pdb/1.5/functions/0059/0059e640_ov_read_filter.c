/*
 * Entry: 0059e640
 * Name: ov_read_filter
 * Namespace: Global
 * Signature: long ov_read_filter(OggVorbis_File * param_1, char * param_2, int param_3, int param_4, int param_5, int param_6, int * param_7, _func___cdecl_void_float_ptr_ptr_long_long_void_ptr * param_8, void * param_9)
 * Symbol source: IMPORTED
 * Export status: ok
 */

long __cdecl
ov_read_filter(OggVorbis_File *param_1,char *param_2,int param_3,int param_4,int param_5,int param_6
              ,int *param_7,_func___cdecl_void_float_ptr_ptr_long_long_void_ptr *param_8,
              void *param_9)

{
  float *pfVar1;
  long64 lVar2;
  vorbis_info *pvVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int local_4c;
  short *local_44;
  char *local_3c;
  int local_30;
  short local_28 [2];
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  float **local_8;
  
  local_18 = host_is_big_endian();
  if (param_1->ready_state < 2) {
    local_20 = -0x83;
  }
  else {
    do {
      if ((param_1->ready_state == 4) &&
         (local_14 = vorbis_synthesis_pcmout(&param_1->vd,&local_8), local_14 != 0)) {
        if (local_14 < 1) {
          return local_14;
        }
        pvVar3 = ov_info(param_1,-1);
        iVar5 = pvVar3->channels;
        local_24 = param_5 * iVar5;
        if (param_3 / local_24 < local_14) {
          local_14 = param_3 / local_24;
        }
        if (local_14 < 1) {
          return -0x83;
        }
        if (param_8 != (_func___cdecl_void_float_ptr_ptr_long_long_void_ptr *)0x0) {
          (*param_8)(local_8,iVar5,local_14,param_9);
        }
        if (param_5 == 1) {
          vorbis_fpu_setround(local_28);
          for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
            for (local_10 = 0; local_10 < iVar5; local_10 = local_10 + 1) {
              local_30 = vorbis_ftoi((double)(local_8[local_10][local_1c] * 128.0));
              if (local_30 < 0x80) {
                if (local_30 < -0x80) {
                  local_30 = -0x80;
                }
              }
              else {
                local_30 = 0x7f;
              }
              *param_2 = (char)local_30 + (-(param_6 != 0) & 0x80U) + 0x80;
              param_2 = param_2 + 1;
            }
          }
          vorbis_fpu_restore(local_28[0]);
        }
        else {
          iVar4 = (-(uint)(param_6 != 0) & 0xffff8000) + 0x8000;
          if (local_18 == param_4) {
            if (param_6 == 0) {
              vorbis_fpu_setround(local_28);
              for (local_10 = 0; local_10 < iVar5; local_10 = local_10 + 1) {
                pfVar1 = local_8[local_10];
                local_44 = (short *)(param_2 + local_10 * 2);
                for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
                  local_30 = vorbis_ftoi((double)(pfVar1[local_1c] * 32768.0));
                  if (local_30 < 0x8000) {
                    if (local_30 < -0x8000) {
                      local_30 = -0x8000;
                    }
                  }
                  else {
                    local_30 = 0x7fff;
                  }
                  *local_44 = (short)local_30 + -0x8000;
                  local_44 = local_44 + iVar5;
                }
              }
              vorbis_fpu_restore(local_28[0]);
            }
            else {
              vorbis_fpu_setround(local_28);
              for (local_10 = 0; local_10 < iVar5; local_10 = local_10 + 1) {
                pfVar1 = local_8[local_10];
                local_3c = param_2 + local_10 * 2;
                for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
                  local_30 = vorbis_ftoi((double)(pfVar1[local_1c] * 32768.0));
                  if (local_30 < 0x8000) {
                    if (local_30 < -0x8000) {
                      local_30 = -0x8000;
                    }
                  }
                  else {
                    local_30 = 0x7fff;
                  }
                  *(undefined2 *)local_3c = (undefined2)local_30;
                  local_3c = local_3c + iVar5 * 2;
                }
              }
              vorbis_fpu_restore(local_28[0]);
            }
          }
          else if (param_4 == 0) {
            vorbis_fpu_setround(local_28);
            for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
              for (local_10 = 0; local_10 < iVar5; local_10 = local_10 + 1) {
                local_4c = vorbis_ftoi((double)(local_8[local_10][local_1c] * 32768.0));
                if (local_4c < 0x8000) {
                  if (local_4c < -0x8000) {
                    local_4c = -0x8000;
                  }
                }
                else {
                  local_4c = 0x7fff;
                }
                local_4c = local_4c + iVar4;
                *param_2 = (char)local_4c;
                param_2[1] = (char)((uint)local_4c >> 8);
                param_2 = param_2 + 2;
              }
            }
            vorbis_fpu_restore(local_28[0]);
          }
          else {
            vorbis_fpu_setround(local_28);
            for (local_1c = 0; local_1c < local_14; local_1c = local_1c + 1) {
              for (local_10 = 0; local_10 < iVar5; local_10 = local_10 + 1) {
                local_30 = vorbis_ftoi((double)(local_8[local_10][local_1c] * 32768.0));
                if (local_30 < 0x8000) {
                  if (local_30 < -0x8000) {
                    local_30 = -0x8000;
                  }
                }
                else {
                  local_30 = 0x7fff;
                }
                local_30 = local_30 + iVar4;
                *param_2 = (char)((uint)local_30 >> 8);
                param_2[1] = (char)local_30;
                param_2 = param_2 + 2;
              }
            }
            vorbis_fpu_restore(local_28[0]);
          }
        }
        vorbis_synthesis_read(&param_1->vd,local_14);
        iVar5 = vorbis_synthesis_halfrate_p(param_1->vi);
        uVar6 = local_14 << ((byte)iVar5 & 0x1f);
        lVar2 = param_1->pcm_offset;
        iVar5 = *(int *)((int)&param_1->pcm_offset + 4);
        *(uint *)&param_1->pcm_offset = uVar6 + (int)param_1->pcm_offset;
        *(uint *)((int)&param_1->pcm_offset + 4) =
             iVar5 + ((int)uVar6 >> 0x1f) + (uint)CARRY4(uVar6,(uint)lVar2);
        if (param_7 != (int *)0x0) {
          *param_7 = param_1->current_link;
        }
        return local_14 * local_24;
      }
      local_20 = _fetch_and_process_packet(param_1,(ogg_packet *)0x0,1,1);
      if (local_20 == -2) {
        return 0;
      }
    } while (0 < local_20);
  }
  return local_20;
}
