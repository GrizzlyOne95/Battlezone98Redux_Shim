/*
 * Entry: 0059b140
 * Name: _open_seekable2
 * Namespace: Global
 * Signature: int _open_seekable2(OggVorbis_File * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl _open_seekable2(OggVorbis_File *param_1)

{
  long64 *plVar1;
  uint *puVar2;
  uint uVar3;
  long64 *plVar4;
  long lVar5;
  int iVar6;
  long64 lVar7;
  long in_stack_ffffffc8;
  long local_30;
  undefined8 local_2c;
  uint local_24;
  uint local_20;
  undefined8 local_1c;
  undefined4 local_14;
  undefined4 local_10;
  long local_8;
  
  local_24 = *(uint *)param_1->dataoffsets;
  local_20 = *(uint *)((int)param_1->dataoffsets + 4);
  local_14 = 0xffffffff;
  local_10 = 0xffffffff;
  local_30 = (param_1->os).serialno;
  local_8 = (param_1->os).serialno;
  local_2c = _initial_pcmoffset(param_1,param_1->vi);
  if (((param_1->callbacks).seek_func == (_func___cdecl_int_void_ptr_long64_int *)0x0) ||
     ((param_1->callbacks).tell_func == (_func___cdecl_long_void_ptr *)0x0)) {
    *(undefined4 *)&param_1->end = 0xffffffff;
    *(undefined4 *)((int)&param_1->end + 4) = 0xffffffff;
    *(undefined4 *)&param_1->offset = 0xffffffff;
    *(undefined4 *)((int)&param_1->offset + 4) = 0xffffffff;
  }
  else {
    (*(param_1->callbacks).seek_func)(param_1->datasource,0x200000000,in_stack_ffffffc8);
    lVar5 = (*(param_1->callbacks).tell_func)(param_1->datasource);
    *(long *)&param_1->end = lVar5;
    *(long *)((int)&param_1->end + 4) = lVar5 >> 0x1f;
    *(int *)&param_1->offset = (int)param_1->end;
    *(undefined4 *)((int)&param_1->offset + 4) = *(undefined4 *)((int)&param_1->end + 4);
  }
  if (((uint)param_1->end & *(uint *)((int)&param_1->end + 4)) == 0xffffffff) {
    local_1c._0_4_ = -0x83;
  }
  else {
    lVar7 = _get_prev_page_serial
                      (param_1,param_1->serialnos + 2,param_1->serialnos[1],&local_30,
                       (long64 *)&local_14);
    local_1c._4_4_ = (int)((ulonglong)lVar7 >> 0x20);
    if ((local_1c._4_4_ < 1) && (lVar7 < 0)) {
      local_1c._0_4_ = (int)lVar7;
    }
    else {
      local_1c = lVar7;
      iVar6 = _bisect_forward_serialno
                        (param_1,(ulonglong)local_24 << 0x20,CONCAT44((int)param_1->offset,local_20)
                         ,CONCAT44(local_14,*(undefined4 *)((int)&param_1->offset + 4)),
                         CONCAT44(local_30,local_10),(int)(param_1->serialnos + 2),
                         (long *)param_1->serialnos[1],0,in_stack_ffffffc8);
      if (iVar6 < 0) {
        local_1c._0_4_ = -0x80;
      }
      else {
        plVar1 = param_1->offsets;
        *(undefined4 *)plVar1 = 0;
        *(undefined4 *)((int)plVar1 + 4) = 0;
        *param_1->serialnos = local_8;
        puVar2 = (uint *)param_1->dataoffsets;
        *puVar2 = local_24;
        puVar2[1] = local_20;
        puVar2 = (uint *)param_1->pcmlengths;
        *puVar2 = (uint)local_2c;
        puVar2[1] = local_2c._4_4_;
        uVar3 = *(uint *)(param_1->pcmlengths + 1);
        iVar6 = *(int *)((int)param_1->pcmlengths + 0xc);
        plVar1 = param_1->pcmlengths;
        *(uint *)(plVar1 + 1) = uVar3 - (uint)local_2c;
        *(uint *)((int)plVar1 + 0xc) = (iVar6 - local_2c._4_4_) - (uint)(uVar3 < (uint)local_2c);
        plVar1 = param_1->pcmlengths;
        iVar6 = *(int *)((int)plVar1 + 0xc);
        if ((iVar6 < 1) && (iVar6 < 0)) {
          plVar4 = param_1->pcmlengths;
          *(undefined4 *)(plVar4 + 1) = 0;
          *(undefined4 *)((int)plVar4 + 0xc) = 0;
        }
        local_1c._0_4_ = ov_raw_seek(param_1,CONCAT44(plVar1,local_20));
      }
    }
  }
  return (int)local_1c;
}
