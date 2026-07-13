
/* WARNING: Removing unreachable block (ram,0x00844608) */
/* WARNING: Removing unreachable block (ram,0x00844616) */

ulonglong FUN_008445de(void)

{
  double dVar1;
  ushort in_FPUControlWord;
  float in_XMM0_Da;
  ulonglong in_XMM0_Qb;
  int iVar2;
  ulonglong uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  longlong lVar6;
  ulonglong uVar7;
  undefined1 auVar8 [16];
  
  if (((0x7f7fffff < (uint)ABS(in_XMM0_Da)) ||
      (dVar1 = (double)in_XMM0_Da, 9.223372036854776e+18 <= dVar1)) ||
     (dVar1 < -9.223372036854776e+18)) {
    FUN_0084475d();
    return 0x8000000000000000;
  }
  auVar4._0_8_ = ABS(dVar1);
  auVar4._8_8_ = in_XMM0_Qb & 0x7fffffffffffffff;
  if (((auVar4._0_8_ <= 1.1754943157898259e-38) && (auVar4._0_8_ != 0.0)) &&
     ((in_FPUControlWord & 0x10) == 0)) {
    FUN_0084475d();
    return 0x8000000000000000;
  }
  uVar3 = 0;
  if (auVar4._0_8_ != 0.0) {
    auVar5 = auVar4 & ZEXT816(0xfffffffffffff) | ZEXT816(0x10000000000000);
    lVar6 = SUB168(ZEXT416(0x433),0) - ((ulonglong)auVar4._0_8_ >> 0x34);
    uVar7 = auVar5._0_8_ >> lVar6;
    iVar2 = -(uint)(0x433 < (uint)((ulonglong)((longlong)dVar1 << 1) >> 0x35));
    uVar3 = CONCAT44(iVar2,iVar2);
    uVar3 = ~uVar3 & uVar7 |
            auVar5._0_8_ << ((ulonglong)auVar4._0_8_ >> 0x34) - SUB168(ZEXT416(0x433),0) & uVar3;
    uVar3 = ~-(ulonglong)(dVar1 == auVar4._0_8_) & -uVar3 |
            uVar3 & -(ulonglong)(dVar1 == auVar4._0_8_);
    if ((0 < (int)lVar6) &&
       (auVar8._0_8_ = uVar7 << lVar6,
       auVar8._8_8_ = (auVar5._8_8_ >> lVar6) << -(auVar4._8_8_ >> 0x34),
       SUB164(auVar5 ^ auVar8,0) != 0 || SUB164(auVar5 ^ auVar8,4) != 0)) {
      FUN_0084475d();
    }
  }
  return uVar3;
}

