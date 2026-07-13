/*
 * Entry: 005110f1
 * Name: IParse_Variable_Match
 * Namespace: Global
 * Signature: int IParse_Variable_Match(_domain * param_1, char * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl IParse_Variable_Match(_domain *param_1,char *param_2)

{
  _struct_list_element *p_Var1;
  _variable_struct *p_Var2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  char *pcVar6;
  bool bVar7;
  
  iVar3 = 4;
  bVar7 = true;
  pcVar6 = param_2;
  pcVar5 = "int";
  do {
    if (iVar3 == 0) break;
    iVar3 = iVar3 + -1;
    bVar7 = *pcVar6 == *pcVar5;
    pcVar6 = pcVar6 + 1;
    pcVar5 = pcVar5 + 1;
  } while (bVar7);
  if (bVar7) {
    iVar3 = 1;
  }
  else {
    iVar3 = 6;
    bVar7 = true;
    pcVar6 = param_2;
    pcVar5 = "float";
    do {
      if (iVar3 == 0) break;
      iVar3 = iVar3 + -1;
      bVar7 = *pcVar6 == *pcVar5;
      pcVar6 = pcVar6 + 1;
      pcVar5 = pcVar5 + 1;
    } while (bVar7);
    if (bVar7) {
      iVar3 = 2;
    }
    else {
      iVar3 = 7;
      pcVar6 = "Adouble";
      bVar7 = true;
      iVar4 = iVar3;
      pcVar5 = param_2;
      do {
        pcVar6 = pcVar6 + 1;
        if (iVar4 == 0) break;
        iVar4 = iVar4 + -1;
        bVar7 = *pcVar5 == *pcVar6;
        pcVar5 = pcVar5 + 1;
      } while (bVar7);
      if (bVar7) {
        iVar3 = 3;
      }
      else {
        iVar4 = 5;
        bVar7 = true;
        pcVar6 = param_2;
        pcVar5 = "char";
        do {
          if (iVar4 == 0) break;
          iVar4 = iVar4 + -1;
          bVar7 = *pcVar6 == *pcVar5;
          pcVar6 = pcVar6 + 1;
          pcVar5 = pcVar5 + 1;
        } while (bVar7);
        if (bVar7) {
          iVar3 = 4;
        }
        else {
          bVar7 = true;
          iVar4 = iVar3;
          pcVar6 = param_2;
          pcVar5 = "struct";
          do {
            if (iVar4 == 0) break;
            iVar4 = iVar4 + -1;
            bVar7 = *pcVar6 == *pcVar5;
            pcVar6 = pcVar6 + 1;
            pcVar5 = pcVar5 + 1;
          } while (bVar7);
          if (bVar7) {
            iVar3 = 5;
          }
          else {
            iVar4 = 8;
            bVar7 = true;
            pcVar6 = param_2;
            pcVar5 = "#define";
            do {
              if (iVar4 == 0) break;
              iVar4 = iVar4 + -1;
              bVar7 = *pcVar6 == *pcVar5;
              pcVar6 = pcVar6 + 1;
              pcVar5 = pcVar5 + 1;
            } while (bVar7);
            if (!bVar7) {
              iVar3 = 9;
              bVar7 = true;
              pcVar6 = param_2;
              pcVar5 = "#include";
              do {
                if (iVar3 == 0) break;
                iVar3 = iVar3 + -1;
                bVar7 = *pcVar6 == *pcVar5;
                pcVar6 = pcVar6 + 1;
                pcVar5 = pcVar5 + 1;
              } while (bVar7);
              if (bVar7) {
                iVar3 = 0x10;
              }
              else {
                iVar3 = 3;
                bVar7 = true;
                pcVar6 = param_2;
                pcVar5 = "if";
                do {
                  if (iVar3 == 0) break;
                  iVar3 = iVar3 + -1;
                  bVar7 = *pcVar6 == *pcVar5;
                  pcVar6 = pcVar6 + 1;
                  pcVar5 = pcVar5 + 1;
                } while (bVar7);
                if (bVar7) {
                  iVar3 = 0xb;
                }
                else {
                  iVar3 = 5;
                  bVar7 = true;
                  pcVar6 = param_2;
                  pcVar5 = "else";
                  do {
                    if (iVar3 == 0) break;
                    iVar3 = iVar3 + -1;
                    bVar7 = *pcVar6 == *pcVar5;
                    pcVar6 = pcVar6 + 1;
                    pcVar5 = pcVar5 + 1;
                  } while (bVar7);
                  if (bVar7) {
                    iVar3 = 0xe;
                  }
                  else {
                    iVar3 = 4;
                    bVar7 = true;
                    pcVar6 = param_2;
                    pcVar5 = "for";
                    do {
                      if (iVar3 == 0) break;
                      iVar3 = iVar3 + -1;
                      bVar7 = *pcVar6 == *pcVar5;
                      pcVar6 = pcVar6 + 1;
                      pcVar5 = pcVar5 + 1;
                    } while (bVar7);
                    if (bVar7) {
                      iVar3 = 0xc;
                    }
                    else {
                      iVar3 = 2;
                      bVar7 = true;
                      pcVar6 = param_2;
                      pcVar5 = "{";
                      do {
                        if (iVar3 == 0) break;
                        iVar3 = iVar3 + -1;
                        bVar7 = *pcVar6 == *pcVar5;
                        pcVar6 = pcVar6 + 1;
                        pcVar5 = pcVar5 + 1;
                      } while (bVar7);
                      if (bVar7) {
                        iVar3 = 0xd;
                      }
                      else {
                        p_Var1 = IParse_Which_Struct(param_1,param_2);
                        if (p_Var1 == (_struct_list_element *)0x0) {
                          p_Var2 = IParse_Which_Variable(param_1,param_2);
                          iVar3 = (-(uint)(p_Var2 != (_variable_struct *)0x0) & 0xc) - 3;
                        }
                        else {
                          iVar3 = 8;
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
  return iVar3;
}
