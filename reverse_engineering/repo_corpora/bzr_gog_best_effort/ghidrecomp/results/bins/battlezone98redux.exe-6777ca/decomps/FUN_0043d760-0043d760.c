
void __thiscall FUN_0043d760(AudioInterface *param_1,VideoClip *param_2,uint param_3,int param_4)

{
  longlong lVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  HANDLE pvVar5;
  uintptr_t uVar6;
  int iVar7;
  void *pvVar8;
  float fVar9;
  int local_60;
  int local_5c;
  int *local_54;
  AudioInterface *local_50;
  undefined4 local_4c;
  undefined4 local_48;
  int local_44;
  undefined4 local_40;
  undefined2 *local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined2 local_28;
  short local_26;
  int local_24;
  uint local_20;
  short local_1c;
  undefined2 local_1a;
  undefined2 local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00845ef9;
  local_10 = ExceptionList;
  uVar2 = DAT_008e7000 ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_50 = param_1;
  local_14 = uVar2;
  theoraplayer::AudioInterface::AudioInterface(param_1,param_2,param_3,param_4);
  local_8 = 0;
  *(undefined ***)local_50 = DirectSound_AudioInterface::vftable;
  FUN_004379d0(uVar2);
  *(undefined4 *)(local_50 + 0x54) = 0;
  *(undefined4 *)(local_50 + 0x58) = 0;
  iVar3 = theoraplayer::VideoClip::getPrecachedFramesCount(param_2);
  local_5c = iVar3 * 10;
  fVar9 = theoraplayer::VideoClip::getFps(param_2);
  FUN_0043d650(fVar9);
  iVar4 = FUN_0083f040();
  if (iVar4 * 10 + iVar3 * -10 != 0 && local_5c <= iVar4 * 10) {
    local_5c = iVar4 * 10;
  }
  fVar9 = theoraplayer::VideoClip::getFps(param_2);
  *(undefined4 *)(local_50 + 0x60) = 0;
  InitializeCriticalSection((LPCRITICAL_SECTION)(local_50 + 0x10));
  pvVar5 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,0,0,(LPCSTR)0x0);
  *(HANDLE *)(local_50 + 0x28) = pvVar5;
  pvVar5 = CreateEventA((LPSECURITY_ATTRIBUTES)0x0,1,0,(LPCSTR)0x0);
  *(HANDLE *)(local_50 + 0x2c) = pvVar5;
  local_50[0x39] = (AudioInterface)0x0;
  local_50[0x38] = (AudioInterface)0x1;
  local_50[0x3a] = (AudioInterface)0x1;
  uVar6 = _beginthreadex((void *)0x0,0x1000,FUN_0043e4c0,local_50,0,(uint *)(local_50 + 0x30));
  *(uintptr_t *)(local_50 + 0x34) = uVar6;
  SetThreadPriority(*(HANDLE *)(local_50 + 0x34),1);
  local_54 = (int *)0x0;
  local_1c = (short)param_3 << 1;
  iVar3 = param_3 * 2 * (int)((float)param_4 / fVar9);
  iVar4 = (local_5c + 1) * iVar3;
  local_40 = 0;
  local_4c = 0x24;
  local_48 = 0x10188;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 1;
  local_26 = (short)param_3;
  local_24 = param_4;
  local_1a = 0x10;
  local_18 = 0;
  local_20 = (param_3 & 0xffff) * param_4 * 0x10 >> 3;
  local_3c = &local_28;
  local_44 = iVar4;
  if ((DAT_00915594 != 0) &&
     (iVar7 = (**(code **)(**(int **)(DAT_00915594 + 0x18) + 0xc))
                        (*(undefined4 *)(DAT_00915594 + 0x18),&local_4c,local_50 + 0x60,0),
     -1 < iVar7)) {
    iVar7 = (**(code **)**(undefined4 **)(local_50 + 0x60))
                      (*(undefined4 *)(local_50 + 0x60),&DAT_0086e988,&local_54);
    if (iVar7 < 0) {
      local_54 = (int *)0x0;
    }
    else {
      lVar1 = (ulonglong)(local_5c + 1) * 8;
      pvVar8 = (void *)FUN_0083d92c(-(uint)((int)((ulonglong)lVar1 >> 0x20) != 0) | (uint)lVar1);
      if (pvVar8 == (void *)0x0) {
        if (local_54 != (int *)0x0) {
          (**(code **)(*local_54 + 8))(local_54);
        }
        local_54 = (int *)0x0;
      }
      else {
        for (local_60 = 0; local_60 <= local_5c; local_60 = local_60 + 1) {
          *(int *)((int)pvVar8 + local_60 * 8) = iVar3 * local_60 + -1 + iVar3;
          *(undefined4 *)((int)pvVar8 + local_60 * 8 + 4) = *(undefined4 *)(local_50 + 0x28);
        }
        iVar7 = (**(code **)(*local_54 + 0xc))(local_54,local_5c + 1,pvVar8);
        if (iVar7 < 0) {
          operator_delete(local_54);
          local_54 = (int *)0x0;
          operator_delete__(pvVar8);
        }
        else {
          if (local_54 != (int *)0x0) {
            (**(code **)(*local_54 + 8))(local_54);
          }
          local_54 = (int *)0x0;
          operator_delete__(pvVar8);
          (**(code **)(**(int **)(local_50 + 0x60) + 0x34))(*(undefined4 *)(local_50 + 0x60),0);
          *(undefined4 *)(local_50 + 0x3c) = 0;
          *(undefined4 *)(local_50 + 0x40) = 0;
          *(int *)(local_50 + 0x44) = iVar3;
          local_50[0x48] = (AudioInterface)0x0;
          *(int *)(local_50 + 0x4c) = iVar4;
          *(uint *)(local_50 + 0x50) = *(uint *)(local_50 + 0x4c) >> 1;
          (**(code **)(**(int **)(local_50 + 0x60) + 0x44))
                    (*(undefined4 *)(local_50 + 0x60),*(undefined4 *)(local_50 + 0xc));
        }
      }
    }
  }
  local_8 = 0xffffffff;
  ExceptionList = local_10;
  FUN_0083e885();
  return;
}

