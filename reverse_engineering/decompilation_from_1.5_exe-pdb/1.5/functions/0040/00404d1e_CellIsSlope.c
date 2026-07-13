/*
 * Entry: 00404d1e
 * Name: CellIsSlope
 * Namespace: Global
 * Signature: bool CellIsSlope(int param_1, int param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

bool __cdecl CellIsSlope(int param_1,int param_2)

{
  int in_EAX;
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int in_ECX;
  uint uVar6;
  
  iVar3 = in_ECX + 1;
  iVar1 = GetTerY(iVar3,in_EAX);
  iVar2 = GetTerY(in_ECX,in_EAX);
  uVar6 = iVar2 - iVar1 >> 0x1f;
  if ((int)((iVar2 - iVar1 ^ uVar6) - uVar6) < 0x33) {
    iVar1 = in_EAX + 1;
    iVar2 = GetTerY(iVar3,in_EAX);
    iVar3 = GetTerY(iVar3,iVar1);
    uVar6 = iVar2 - iVar3 >> 0x1f;
    if ((int)((iVar2 - iVar3 ^ uVar6) - uVar6) < 0x33) {
      iVar3 = GetTerY(in_ECX,iVar1);
      iVar2 = GetTerY(in_ECX + 1,iVar1);
      uVar6 = iVar2 - iVar3 >> 0x1f;
      if ((int)((iVar2 - iVar3 ^ uVar6) - uVar6) < 0x33) {
        iVar3 = GetTerY(in_ECX,iVar1);
        iVar2 = GetTerY(in_ECX,in_EAX);
        uVar6 = iVar3 - iVar2 >> 0x1f;
        if ((int)((iVar3 - iVar2 ^ uVar6) - uVar6) < 0x33) {
          iVar3 = in_EAX + -1;
          iVar2 = GetTerY(in_ECX + -1,iVar3);
          iVar4 = GetTerY(in_ECX,in_EAX);
          if (iVar2 - iVar4 < 0xc9) {
            iVar2 = GetTerY(in_ECX + -1,in_EAX);
            iVar4 = GetTerY(in_ECX,in_EAX);
            if (iVar2 - iVar4 < 0xc9) {
              iVar2 = GetTerY(in_ECX,iVar1);
              iVar4 = GetTerY(in_ECX + -1,iVar1);
              if (iVar4 - iVar2 < 0xc9) {
                iVar2 = in_EAX + 2;
                iVar4 = GetTerY(in_ECX,iVar1);
                iVar5 = GetTerY(in_ECX + -1,iVar2);
                if (iVar5 - iVar4 < 0xc9) {
                  iVar4 = GetTerY(in_ECX + 1,in_EAX);
                  iVar5 = GetTerY(in_ECX + 2,iVar3);
                  if (iVar5 - iVar4 < 0xc9) {
                    iVar4 = GetTerY(in_ECX + 2,in_EAX);
                    iVar5 = GetTerY(in_ECX + 1,in_EAX);
                    if (iVar4 - iVar5 < 0xc9) {
                      iVar4 = GetTerY(in_ECX + 2,iVar1);
                      iVar5 = GetTerY(in_ECX + 1,iVar1);
                      if (iVar4 - iVar5 < 0xc9) {
                        iVar4 = GetTerY(in_ECX + 2,iVar2);
                        iVar5 = GetTerY(in_ECX + 1,iVar1);
                        if (iVar4 - iVar5 < 0xc9) {
                          iVar4 = GetTerY(in_ECX + -1,iVar3);
                          iVar5 = GetTerY(in_ECX,in_EAX);
                          if (iVar4 - iVar5 < 0xc9) {
                            iVar4 = GetTerY(in_ECX,iVar3);
                            iVar5 = GetTerY(in_ECX,in_EAX);
                            if (iVar4 - iVar5 < 0xc9) {
                              iVar4 = GetTerY(in_ECX + 1,in_EAX);
                              iVar5 = GetTerY(in_ECX + 1,iVar3);
                              if (iVar5 - iVar4 < 0xc9) {
                                iVar4 = in_ECX + 1;
                                iVar5 = GetTerY(iVar4,in_EAX);
                                iVar3 = GetTerY(in_ECX + 2,iVar3);
                                if (iVar3 - iVar5 < 0xc9) {
                                  iVar3 = GetTerY(in_ECX,iVar1);
                                  iVar5 = GetTerY(in_ECX + -1,iVar2);
                                  if (iVar5 - iVar3 < 0xc9) {
                                    iVar3 = GetTerY(in_ECX,iVar2);
                                    iVar5 = GetTerY(in_ECX,iVar1);
                                    if (iVar3 - iVar5 < 0xc9) {
                                      iVar3 = GetTerY(iVar4,iVar2);
                                      iVar5 = GetTerY(iVar4,iVar1);
                                      if (iVar3 - iVar5 < 0xc9) {
                                        iVar3 = GetTerY(in_ECX + 2,iVar2);
                                        iVar1 = GetTerY(iVar4,iVar1);
                                        if (iVar3 - iVar1 < 0xc9) {
                                          return false;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return true;
}
