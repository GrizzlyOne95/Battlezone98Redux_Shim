
/* WARNING: Function: __SEH_prolog4 replaced with injection: SEH_prolog4 */
/* WARNING: Function: __SEH_epilog4 replaced with injection: EH_epilog3 */

int entry(void)

{
  byte bVar1;
  bool bVar2;
  void *pvVar3;
  WORD WVar4;
  void *pvVar5;
  BOOL BVar6;
  int iVar7;
  byte *pbVar8;
  
  ___security_init_cookie();
  WVar4 = __crtGetShowWindowMode();
  bVar2 = false;
  do {
    pvVar5 = (void *)0x0;
    LOCK();
    pvVar3 = StackBase;
    if (DAT_02cc3b74 != (void *)0x0) {
      pvVar5 = DAT_02cc3b74;
      pvVar3 = DAT_02cc3b74;
    }
    DAT_02cc3b74 = pvVar3;
    UNLOCK();
    if (pvVar5 == (void *)0x0) goto LAB_0083eeb2;
  } while (pvVar5 != StackBase);
  bVar2 = true;
LAB_0083eeb2:
  if (DAT_02cc3b78 == 1) {
    _amsg_exit(0x1f);
  }
  else if (DAT_02cc3b78 == 0) {
    DAT_02cc3b78 = 1;
    iVar7 = initterm_e(&DAT_0086e768,&DAT_0086e77c);
    if (iVar7 != 0) {
      return 0xff;
    }
  }
  else {
    DAT_00915048 = 1;
  }
  if (DAT_02cc3b78 == 1) {
    initterm(&DAT_0086a134,&DAT_0086e764);
    DAT_02cc3b78 = 2;
  }
  if (!bVar2) {
    LOCK();
    DAT_02cc3b74 = (void *)0x0;
    UNLOCK();
  }
  if ((DAT_02cc3b7c != (code *)0x0) &&
     (BVar6 = __IsNonwritableInCurrentImage((PBYTE)&DAT_02cc3b7c), BVar6 != 0)) {
    (*DAT_02cc3b7c)(0,2,0);
  }
  pbVar8 = *(byte **)_acmdln_exref;
  bVar2 = false;
  while ((bVar1 = *pbVar8, 0x20 < bVar1 || ((bVar1 != 0 && (bVar2))))) {
    if (bVar1 == 0x22) {
      bVar2 = !bVar2;
    }
    iVar7 = _ismbblead((uint)bVar1);
    if (iVar7 != 0) {
      pbVar8 = pbVar8 + 1;
    }
    pbVar8 = pbVar8 + 1;
  }
  for (; (*pbVar8 != 0 && (*pbVar8 < 0x21)); pbVar8 = pbVar8 + 1) {
  }
  DAT_0091504c = FUN_00618b10(0x400000,0,pbVar8,WVar4);
  if (DAT_00915050 != 0) {
    if (DAT_00915048 == 0) {
      _cexit();
    }
    return DAT_0091504c;
  }
                    /* WARNING: Subroutine does not return */
  exit(DAT_0091504c);
}

