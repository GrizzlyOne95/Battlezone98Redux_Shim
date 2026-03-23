
undefined4 FUN_00629dd0(int param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  void *_Dst;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  
  iVar1 = *(int *)(param_1 + 0x18) * 0x94;
  iVar6 = *(int *)(param_1 + 0x1c) * 0x84;
  iVar5 = *(int *)(param_1 + 0x20) * 0x14;
  iVar2 = *(int *)(param_1 + 0x24) * 0x10;
  iVar7 = *(int *)(param_1 + 0x28) * 0x10;
  iVar3 = iVar1 + 0x40 + iVar6 + iVar5 + iVar2 + iVar7;
  if (((*(int *)(param_1 + 0x18) * *(int *)(param_1 + 0x1c) < *(int *)(param_1 + 0x28)) ||
      (*(int *)(param_1 + 0x20) != 0)) || (*(int *)(param_1 + 0x24) != 0)) {
    if (DAT_00920c5c < 0x1000) {
      if ((param_3 < (uint)(param_1 + *(int *)(param_1 + 4))) ||
         (*(int *)(param_1 + 4) != iVar3 + 8)) {
        FUN_007d6c70("AnimObj_Add() chunk size and header info mismatch",param_2);
        uVar4 = 0xffffffff;
      }
      else {
        puVar8 = param_2;
        _Dst = malloc(iVar1 + 0x40 + iVar6 + iVar5 + iVar2 + iVar7);
        if (_Dst == (void *)0x0) {
          FUN_007d6c70("AnimObj_Add() anim list malloc failed",puVar8);
          uVar4 = 0xffffffff;
        }
        else {
          memcpy(_Dst,(void *)(param_1 + 8),0x40);
          memcpy((void *)((int)_Dst + 0x40),(void *)(param_1 + 0x48),iVar3 - 0x40);
          *(void **)(&DAT_02a1b498 + DAT_00920c5c * 4) = _Dst;
          DAT_00920c5c = DAT_00920c5c + 1;
          *(int *)((int)_Dst + 0x24) = (int)_Dst + 0x40;
          *(int *)((int)_Dst + 0x28) = (int)_Dst + iVar1 + 0x40;
          *(int *)((int)_Dst + 0x2c) = (int)_Dst + iVar6 + iVar1 + 0x40;
          *(int *)((int)_Dst + 0x30) = (int)_Dst + iVar5 + iVar6 + iVar1 + 0x40;
          *(int *)((int)_Dst + 0x34) = (int)_Dst + iVar2 + iVar5 + iVar6 + iVar1 + 0x40;
          *(undefined4 *)((int)_Dst + 0x38) = *param_2;
          *(undefined4 *)((int)_Dst + 0x3c) = 0;
          uVar4 = 0;
        }
      }
    }
    else {
      FUN_007d6c70("AnimObj_Add() anim list overflow",param_2);
      uVar4 = 0xffffffff;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

