
undefined4 * __thiscall FUN_10018a00(void *this,undefined4 *param_1)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  void *pvVar6;
  void *_Dst;
  uint uVar7;
  uint uVar8;
  
  *(undefined4 *)this = 0;
  *(undefined4 *)((int)this + 4) = 0;
  *(undefined4 *)((int)this + 8) = 0;
  *(undefined4 *)((int)this + 0xc) = 0;
  *(undefined4 *)((int)this + 0x10) = 0;
  *(undefined4 *)((int)this + 0x14) = 0;
  uVar2 = param_1[4];
  if (0xf < (uint)param_1[5]) {
    param_1 = (undefined4 *)*param_1;
  }
  if (0x7fffffff < uVar2) {
                    /* WARNING: Subroutine does not return */
    FUN_10003680();
  }
  if (uVar2 < 0x10) {
    *(uint *)((int)this + 0x10) = uVar2;
    *(undefined4 *)((int)this + 0x14) = 0xf;
    uVar3 = param_1[1];
    uVar4 = param_1[2];
    uVar5 = param_1[3];
    *(undefined4 *)this = *param_1;
    *(undefined4 *)((int)this + 4) = uVar3;
    *(undefined4 *)((int)this + 8) = uVar4;
    *(undefined4 *)((int)this + 0xc) = uVar5;
    return this;
  }
  uVar8 = uVar2 | 0xf;
  if (uVar8 < 0x80000000) {
    if (uVar8 < 0x16) {
      uVar8 = 0x16;
    }
    uVar1 = uVar8 + 1;
    _Dst = (void *)0x0;
    if (uVar1 == 0) goto LAB_10018ac1;
    if (uVar1 < 0x1000) {
      _Dst = operator_new(uVar1);
      goto LAB_10018ac1;
    }
    uVar7 = uVar8 + 0x24;
    if (uVar7 <= uVar1) {
                    /* WARNING: Subroutine does not return */
      FUN_10001f20();
    }
  }
  else {
    uVar8 = 0x7fffffff;
    uVar7 = 0x80000023;
  }
  pvVar6 = operator_new(uVar7);
  if (pvVar6 == (void *)0x0) {
                    /* WARNING: Subroutine does not return */
    _invalid_parameter_noinfo_noreturn();
  }
  _Dst = (void *)((int)pvVar6 + 0x23U & 0xffffffe0);
  *(void **)((int)_Dst - 4) = pvVar6;
LAB_10018ac1:
  *(void **)this = _Dst;
  *(uint *)((int)this + 0x10) = uVar2;
  *(uint *)((int)this + 0x14) = uVar8;
  memcpy(_Dst,param_1,uVar2 + 1);
  return this;
}

