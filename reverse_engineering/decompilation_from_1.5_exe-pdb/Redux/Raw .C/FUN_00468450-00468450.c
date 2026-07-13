
undefined4 FUN_00468450(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = FUN_0077d640(param_1,param_2);
  iVar2 = FUN_0077d640(param_1 + 1,param_2);
  uVar3 = iVar1 - iVar2 >> 0x1f;
  if ((int)((iVar1 - iVar2 ^ uVar3) - uVar3) < 0x19) {
    iVar1 = FUN_0077d640(param_1 + 1,param_2);
    iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
    uVar3 = iVar1 - iVar2 >> 0x1f;
    if ((int)((iVar1 - iVar2 ^ uVar3) - uVar3) < 0x19) {
      iVar1 = FUN_0077d640(param_1 + 1,param_2 + 1);
      iVar2 = FUN_0077d640(param_1,param_2 + 1);
      uVar3 = iVar1 - iVar2 >> 0x1f;
      if ((int)((iVar1 - iVar2 ^ uVar3) - uVar3) < 0x19) {
        iVar1 = FUN_0077d640(param_1,param_2 + 1);
        iVar2 = FUN_0077d640(param_1,param_2);
        uVar3 = iVar1 - iVar2 >> 0x1f;
        if ((int)((iVar1 - iVar2 ^ uVar3) - uVar3) < 0x19) {
          iVar1 = FUN_0077d640(param_1 + -1,param_2 + -1);
          iVar2 = FUN_0077d640(param_1,param_2);
          if (iVar1 - iVar2 < 100) {
            iVar1 = FUN_0077d640(param_1 + -1,param_2);
            iVar2 = FUN_0077d640(param_1,param_2);
            if (iVar1 - iVar2 < 100) {
              iVar1 = FUN_0077d640(param_1 + -1,param_2 + 1);
              iVar2 = FUN_0077d640(param_1,param_2 + 1);
              if (iVar1 - iVar2 < 100) {
                iVar1 = FUN_0077d640(param_1 + -1,param_2 + 2);
                iVar2 = FUN_0077d640(param_1,param_2 + 1);
                if (iVar1 - iVar2 < 100) {
                  iVar1 = FUN_0077d640(param_1 + 2,param_2 + -1);
                  iVar2 = FUN_0077d640(param_1 + 1,param_2);
                  if (iVar1 - iVar2 < 100) {
                    iVar1 = FUN_0077d640(param_1 + 2,param_2);
                    iVar2 = FUN_0077d640(param_1 + 1,param_2);
                    if (iVar1 - iVar2 < 100) {
                      iVar1 = FUN_0077d640(param_1 + 2,param_2 + 1);
                      iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
                      if (iVar1 - iVar2 < 100) {
                        iVar1 = FUN_0077d640(param_1 + 2,param_2 + 2);
                        iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
                        if (iVar1 - iVar2 < 100) {
                          iVar1 = FUN_0077d640(param_1 + -1,param_2 + -1);
                          iVar2 = FUN_0077d640(param_1,param_2);
                          if (iVar1 - iVar2 < 100) {
                            iVar1 = FUN_0077d640(param_1,param_2 + -1);
                            iVar2 = FUN_0077d640(param_1,param_2);
                            if (iVar1 - iVar2 < 100) {
                              iVar1 = FUN_0077d640(param_1 + 1,param_2 + -1);
                              iVar2 = FUN_0077d640(param_1 + 1,param_2);
                              if (iVar1 - iVar2 < 100) {
                                iVar1 = FUN_0077d640(param_1 + 2,param_2 + -1);
                                iVar2 = FUN_0077d640(param_1 + 1,param_2);
                                if (iVar1 - iVar2 < 100) {
                                  iVar1 = FUN_0077d640(param_1 + -1,param_2 + 2);
                                  iVar2 = FUN_0077d640(param_1,param_2 + 1);
                                  if (iVar1 - iVar2 < 100) {
                                    iVar1 = FUN_0077d640(param_1,param_2 + 2);
                                    iVar2 = FUN_0077d640(param_1,param_2 + 1);
                                    if (iVar1 - iVar2 < 100) {
                                      iVar1 = FUN_0077d640(param_1 + 1,param_2 + 2);
                                      iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
                                      if (iVar1 - iVar2 < 100) {
                                        iVar1 = FUN_0077d640(param_1 + 2,param_2 + 2);
                                        iVar2 = FUN_0077d640(param_1 + 1,param_2 + 1);
                                        if (iVar1 - iVar2 < 100) {
                                          return 0;
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
  return 1;
}

