
/* WARNING: Removing unreachable block (ram,0x00844603) */
/* WARNING: Removing unreachable block (ram,0x00844829) */
/* WARNING: Removing unreachable block (ram,0x00844608) */
/* WARNING: Removing unreachable block (ram,0x00844616) */
/* WARNING: Removing unreachable block (ram,0x00844620) */
/* WARNING: Removing unreachable block (ram,0x0084462a) */
/* WARNING: Removing unreachable block (ram,0x0084463c) */
/* WARNING: Removing unreachable block (ram,0x0084464f) */
/* WARNING: Removing unreachable block (ram,0x0084465d) */
/* WARNING: Removing unreachable block (ram,0x00844667) */
/* WARNING: Removing unreachable block (ram,0x00844677) */

ulonglong FUN_008447bf(void)

{
  int iVar1;
  int extraout_ECX;
  double in_XMM0_Qa;
  ulonglong in_XMM0_Qb;
  double dVar2;
  ulonglong uVar3;
  undefined1 auVar4 [16];
  undefined1 auVar5 [16];
  double dVar6;
  longlong lVar7;
  ulonglong uVar8;
  undefined1 auVar9 [16];
  
  iVar1 = 5;
  dVar2 = 9.223372036854776e+18;
  if (((uint)((ulonglong)in_XMM0_Qa >> 0x20) & 0x7fffffff) < 0x7ff00000) {
    auVar4._0_8_ = ABS(in_XMM0_Qa);
    auVar4._8_8_ = in_XMM0_Qb & 0x7fffffffffffffff;
    if (3.4028235677973366e+38 < auVar4._0_8_) {
      FUN_0084475d();
      FUN_0084475d();
      iVar1 = extraout_ECX;
    }
    if (1.1754943157898259e-38 <= auVar4._0_8_) {
      dVar6 = in_XMM0_Qa;
      if ((iVar1 == 4) && (9.223372036854776e+18 <= in_XMM0_Qa)) {
        dVar6 = in_XMM0_Qa - 9.223372036854776e+18;
      }
      if ((int)((ulonglong)((longlong)dVar6 << 0x23) >> 0x20) != 0) {
        FUN_0084475d();
      }
      if ((dVar2 <= in_XMM0_Qa) || (in_XMM0_Qa < -9.223372036854776e+18)) goto LAB_0084474b;
    }
    else if (auVar4._0_8_ != 0.0) {
      FUN_0084475d();
      FUN_0084475d();
    }
    uVar3 = 0;
    dVar2 = auVar4._0_8_;
    if (dVar2 != 0.0) {
      auVar5 = auVar4 & ZEXT816(0xfffffffffffff) | ZEXT816(0x10000000000000);
      lVar7 = SUB168(ZEXT416(0x433),0) - ((ulonglong)dVar2 >> 0x34);
      uVar8 = auVar5._0_8_ >> lVar7;
      iVar1 = -(uint)(0x433 < auVar4._4_4_ >> 0x14);
      uVar3 = CONCAT44(iVar1,iVar1);
      uVar3 = ~uVar3 & uVar8 |
              auVar5._0_8_ << ((ulonglong)dVar2 >> 0x34) - SUB168(ZEXT416(0x433),0) & uVar3;
      uVar3 = ~-(ulonglong)(in_XMM0_Qa == dVar2) & -uVar3 |
              uVar3 & -(ulonglong)(in_XMM0_Qa == dVar2);
      if ((0 < (int)lVar7) &&
         (auVar9._0_8_ = uVar8 << lVar7,
         auVar9._8_8_ = (auVar5._8_8_ >> lVar7) << -(auVar4._8_8_ >> 0x34),
         SUB164(auVar5 ^ auVar9,0) != 0 || SUB164(auVar5 ^ auVar9,4) != 0)) {
        FUN_0084475d();
      }
    }
    return uVar3;
  }
LAB_0084474b:
  FUN_0084475d();
  return 0x8000000000000000;
}

