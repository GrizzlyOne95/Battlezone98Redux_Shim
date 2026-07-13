/*
 * Entry: 00585d02
 * Name: _lzo_config_check
 * Namespace: Global
 * Signature: int _lzo_config_check(void)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

int __cdecl _lzo_config_check(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint uVar5;
  uint extraout_EDX;
  uint uVar6;
  ulong unaff_ESI;
  uint uVar7;
  void *unaff_EDI;
  int iVar8;
  
  u2p(unaff_EDI,unaff_ESI);
  piVar4 = u2p(unaff_EDI,unaff_ESI);
  iVar8 = 0;
  uVar6 = extraout_EDX & (short)*piVar4 == 0 & (uint)((short)*piVar4 == 0) &
          (uint)((short)*piVar4 == 0x80) & (uint)((short)*piVar4 == -0x7e80) &
          (uint)((short)*piVar4 == -0x7e80) & (uint)(*piVar4 == 0) & (uint)(*piVar4 == 0) &
          (uint)(*piVar4 == 0x80) & (uint)(*piVar4 == -0x7c7d7e80) & (uint)(*piVar4 == -0x7c7d7e80);
  uVar7 = 1;
  uVar5 = uVar7;
  do {
    if (uVar6 != 1) break;
    uVar6 = 0x1f;
    if (uVar5 != 0) {
      for (; uVar5 >> uVar6 == 0; uVar6 = uVar6 - 1) {
      }
    }
    uVar3 = 0x1f;
    if (uVar5 != 0) {
      for (; uVar5 >> uVar3 == 0; uVar3 = uVar3 - 1) {
      }
    }
    uVar6 = (uint)((uVar3 ^ 0x1f) == 0x1fU - iVar8 && (uVar6 ^ 0x1f) == 0x1fU - iVar8);
    uVar5 = uVar5 * 2;
    iVar8 = iVar8 + 1;
  } while (uVar5 != 0);
  iVar8 = 0;
  do {
    if (uVar6 != 1) break;
    iVar1 = 0;
    if (uVar7 != 0) {
      for (; (uVar7 >> iVar1 & 1) == 0; iVar1 = iVar1 + 1) {
      }
    }
    iVar2 = 0;
    if (uVar7 != 0) {
      for (; (uVar7 >> iVar2 & 1) == 0; iVar2 = iVar2 + 1) {
      }
    }
    uVar7 = uVar7 * 2;
    uVar6 = (uint)(iVar2 == iVar8 && iVar1 == iVar8);
    iVar8 = iVar8 + 1;
  } while (uVar7 != 0);
  return -(uint)(uVar6 != 1);
}
