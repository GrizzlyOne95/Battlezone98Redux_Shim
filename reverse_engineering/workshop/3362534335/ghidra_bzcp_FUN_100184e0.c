
undefined4 * __thiscall
FUN_100184e0(void *this,uint param_1,undefined4 param_2,void *param_3,size_t param_4)

{
  size_t _Size;
  uint uVar1;
  void *_Src;
  uint uVar2;
  void *pvVar3;
  uint uVar4;
  uint uVar5;
  void *_Dst;
  
  _Size = *(size_t *)((int)this + 0x10);
  if (0x7fffffff - _Size < param_1) {
                    /* WARNING: Subroutine does not return */
    FUN_10003680();
  }
  uVar1 = *(uint *)((int)this + 0x14);
  uVar5 = _Size + param_1 | 0xf;
  if ((uVar5 < 0x80000000) && (uVar1 <= 0x7fffffff - (uVar1 >> 1))) {
    uVar4 = (uVar1 >> 1) + uVar1;
    if (uVar5 < uVar4) {
      uVar5 = uVar4;
    }
    uVar4 = uVar5 + 1;
    if (uVar4 == 0) {
      _Dst = (void *)0x0;
    }
    else {
      if (0xfff < uVar4) {
        uVar2 = uVar5 + 0x24;
        if (uVar2 <= uVar4) {
                    /* WARNING: Subroutine does not return */
          FUN_10001f20();
        }
        goto LAB_1001852a;
      }
      _Dst = operator_new(uVar4);
    }
  }
  else {
    uVar5 = 0x7fffffff;
    uVar2 = 0x80000023;
LAB_1001852a:
    pvVar3 = operator_new(uVar2);
    if (pvVar3 == (void *)0x0) goto LAB_100185ff;
    _Dst = (void *)((int)pvVar3 + 0x23U & 0xffffffe0);
    *(void **)((int)_Dst - 4) = pvVar3;
  }
  *(size_t *)((int)this + 0x10) = _Size + param_1;
  *(uint *)((int)this + 0x14) = uVar5;
  pvVar3 = (void *)(_Size + (int)_Dst);
  if (uVar1 < 0x10) {
    memcpy(_Dst,this,_Size);
    memcpy(pvVar3,param_3,param_4);
    *(undefined1 *)(param_4 + (int)pvVar3) = 0;
    *(void **)this = _Dst;
    return this;
  }
  _Src = *(void **)this;
  memcpy(_Dst,_Src,_Size);
  memcpy(pvVar3,param_3,param_4);
  *(undefined1 *)(param_4 + (int)pvVar3) = 0;
  pvVar3 = _Src;
  if ((uVar1 + 1 < 0x1000) ||
     (pvVar3 = *(void **)((int)_Src + -4), (uint)((int)_Src + (-4 - (int)pvVar3)) < 0x20)) {
    FUN_1001f9a8(pvVar3);
    *(void **)this = _Dst;
    return this;
  }
LAB_100185ff:
                    /* WARNING: Subroutine does not return */
  _invalid_parameter_noinfo_noreturn();
}

