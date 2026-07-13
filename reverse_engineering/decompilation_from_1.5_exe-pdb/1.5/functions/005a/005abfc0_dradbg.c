/*
 * Entry: 005abfc0
 * Name: dradbg
 * Namespace: Global
 * Signature: void dradbg(int param_1, int param_2, int param_3, int param_4, float * param_5, float * param_6, float * param_7, float * param_8, float * param_9, float * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Variable defined which should be unmapped: param_2 */
/* WARNING: Variable defined which should be unmapped: param_4 */

void __cdecl
dradbg(int param_1,int param_2,int param_3,int param_4,float *param_5,float *param_6,float *param_7,
      float *param_8,float *param_9,float *param_10)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  float *in_EAX;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  float *pfVar15;
  float *pfVar16;
  undefined4 *puVar17;
  float *pfVar18;
  float *pfVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  float *pfVar23;
  float *pfVar24;
  float *pfVar25;
  int iVar26;
  int unaff_EBX;
  int unaff_ESI;
  int iVar27;
  float10 fVar28;
  float10 fVar29;
  int iStack_68;
  int iStack_64;
  int iStack_60;
  float *pfStack_5c;
  float *pfStack_58;
  float *local_50;
  int iStack_48;
  float *pfStack_44;
  float *pfStack_40;
  float *pfStack_3c;
  float *pfStack_38;
  float *pfStack_34;
  float *pfStack_30;
  float *pfStack_2c;
  float fStack_24;
  float fStack_20;
  float *pfStack_1c;
  int iStack_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  
  iVar27 = param_4;
  iVar7 = param_1;
  iVar8 = param_1 * param_2;
  iVar9 = param_1 * param_3;
  fVar28 = (float10)__CIcos();
  fVar29 = (float10)__CIsin();
  iVar10 = param_1 + -1 >> 1;
  iVar11 = param_2 + 1 >> 1;
  if (param_1 < param_3) {
    param_1 = 0;
    if (0 < iVar7) {
      do {
        pfStack_5c = (float *)0x0;
        iVar12 = param_1;
        pfStack_44 = (float *)param_1;
        if (3 < param_3) {
          pfStack_2c = (float *)((param_3 - 4U >> 2) + 1);
          pfStack_5c = (float *)((int)pfStack_2c * 4);
          do {
            *(float *)(unaff_ESI + iVar12 * 4) = in_EAX[(int)pfStack_44];
            *(float *)(unaff_ESI + (iVar12 + iVar7) * 4) = in_EAX[(int)pfStack_44 + iVar8];
            iVar20 = (int)pfStack_44 + iVar8 + iVar8;
            iVar12 = iVar12 + iVar7 + iVar7;
            *(float *)(unaff_ESI + iVar12 * 4) = in_EAX[iVar20];
            iVar20 = iVar20 + iVar8;
            iVar12 = iVar12 + iVar7;
            *(float *)(unaff_ESI + iVar12 * 4) = in_EAX[iVar20];
            iVar12 = iVar12 + iVar7;
            pfStack_44 = (float *)(iVar20 + iVar8);
            pfStack_2c = (float *)((int)pfStack_2c + -1);
          } while (pfStack_2c != (float *)0x0);
        }
        if ((int)pfStack_5c < param_3) {
          iVar20 = param_3 - (int)pfStack_5c;
          pfVar16 = (float *)(unaff_ESI + iVar12 * 4);
          pfStack_44 = in_EAX + (int)pfStack_44;
          do {
            *pfVar16 = *pfStack_44;
            pfVar16 = pfVar16 + iVar7;
            pfStack_44 = pfStack_44 + iVar8;
            iVar20 = iVar20 + -1;
          } while (iVar20 != 0);
        }
        param_1 = param_1 + 1;
      } while (param_1 < iVar7);
    }
  }
  else {
    param_1 = 0;
    iStack_68 = 0;
    if (0 < param_3) {
      pfStack_30 = in_EAX + 2;
      pfStack_2c = (float *)(unaff_ESI + 8);
      pfStack_34 = (float *)param_3;
      do {
        iVar12 = 0;
        iVar20 = iStack_68;
        iVar14 = param_1;
        if (3 < iVar7) {
          iVar21 = (iVar7 - 4U >> 2) + 1;
          iVar12 = iVar21 * 4;
          iVar14 = param_1 + iVar12;
          iVar20 = iStack_68 + iVar12;
          pfVar16 = pfStack_2c;
          pfVar15 = pfStack_30;
          do {
            pfVar16[-2] = pfVar15[-2];
            iVar21 = iVar21 + -1;
            pfVar16[-1] = pfVar15[-1];
            *pfVar16 = *pfVar15;
            pfVar16[1] = pfVar15[1];
            pfVar16 = pfVar16 + 4;
            pfVar15 = pfVar15 + 4;
          } while (iVar21 != 0);
        }
        if (iVar12 < iVar7) {
          pfVar16 = in_EAX + iVar20;
          iVar12 = iVar7 - iVar12;
          pfVar15 = (float *)(unaff_ESI + iVar14 * 4);
          do {
            *pfVar15 = *pfVar16;
            pfVar16 = pfVar16 + 1;
            iVar12 = iVar12 + -1;
            pfVar15 = pfVar15 + 1;
          } while (iVar12 != 0);
        }
        param_1 = param_1 + iVar7;
        pfStack_2c = pfStack_2c + iVar7;
        iStack_68 = iStack_68 + iVar8;
        pfStack_30 = pfStack_30 + iVar8;
        pfStack_34 = (float *)((int)pfStack_34 + -1);
      } while (pfStack_34 != (float *)0x0);
    }
  }
  iVar12 = iVar9 * param_2;
  param_1 = 0;
  if (1 < iVar11) {
    pfStack_38 = (float *)(iVar11 + -1);
    iVar20 = iVar7 * 2;
    iStack_68 = iVar12;
    do {
      param_1 = param_1 + iVar9;
      iStack_68 = iStack_68 - iVar9;
      pfStack_5c = (float *)0x0;
      iVar14 = iVar20;
      iVar21 = param_1;
      pfStack_58 = (float *)iStack_68;
      if (3 < param_3) {
        pfStack_2c = (float *)((param_3 - 4U >> 2) + 1);
        pfStack_5c = (float *)((int)pfStack_2c * 4);
        do {
          *(float *)(unaff_ESI + iVar21 * 4) = in_EAX[iVar14 + -1] + in_EAX[iVar14 + -1];
          iVar13 = iVar14 + iVar8;
          *(float *)(unaff_ESI + (int)pfStack_58 * 4) = in_EAX[iVar14] + in_EAX[iVar14];
          *(float *)(unaff_ESI + (iVar21 + iVar7) * 4) = in_EAX[iVar13 + -1] + in_EAX[iVar13 + -1];
          iVar21 = iVar21 + iVar7 + iVar7;
          iVar14 = iVar13 + iVar8;
          *(float *)(unaff_ESI + ((int)pfStack_58 + iVar7) * 4) = in_EAX[iVar13] + in_EAX[iVar13];
          iVar26 = (int)pfStack_58 + iVar7 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) = in_EAX[iVar14 + -1] + in_EAX[iVar14 + -1];
          iVar21 = iVar21 + iVar7;
          iVar13 = iVar14 + iVar8;
          *(float *)(unaff_ESI + iVar26 * 4) = in_EAX[iVar14] + in_EAX[iVar14];
          iVar26 = iVar26 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) = in_EAX[iVar13 + -1] + in_EAX[iVar13 + -1];
          iVar21 = iVar21 + iVar7;
          iVar14 = iVar13 + iVar8;
          *(float *)(unaff_ESI + iVar26 * 4) = in_EAX[iVar13] + in_EAX[iVar13];
          pfStack_58 = (float *)(iVar26 + iVar7);
          pfStack_2c = (float *)((int)pfStack_2c + -1);
        } while (pfStack_2c != (float *)0x0);
      }
      if ((int)pfStack_5c < param_3) {
        pfStack_2c = (float *)(unaff_ESI + (int)pfStack_58 * 4);
        pfVar16 = (float *)(unaff_ESI + iVar21 * 4);
        iVar21 = param_3 - (int)pfStack_5c;
        pfVar15 = in_EAX + iVar14;
        do {
          *pfVar16 = pfVar15[-1] + pfVar15[-1];
          *pfStack_2c = *pfVar15 + *pfVar15;
          pfStack_2c = pfStack_2c + iVar7;
          pfVar16 = pfVar16 + iVar7;
          pfVar15 = pfVar15 + iVar8;
          iVar21 = iVar21 + -1;
        } while (iVar21 != 0);
      }
      iVar20 = iVar20 + iVar7 * 2;
      pfStack_38 = (float *)((int)pfStack_38 + -1);
    } while (pfStack_38 != (float *)0x0);
  }
  if (iVar7 != 1) {
    if (iVar10 < param_3) {
      iVar20 = 0;
      param_1 = 0;
      if (1 < iVar11) {
        fStack_24 = (float)(iVar11 + -1);
        iStack_68 = iVar12;
        do {
          param_1 = param_1 + iVar9;
          iStack_68 = iStack_68 - iVar9;
          iVar20 = iVar20 + iVar7 * 2;
          if (2 < iVar7) {
            pfStack_58 = (float *)((iVar7 - 3U >> 1) + 1);
            iVar14 = iVar20;
            pfStack_2c = (float *)iVar20;
            do {
              pfStack_2c = (float *)((int)pfStack_2c + -2);
              iVar14 = iVar14 + 2;
              iStack_60 = (param_1 - iVar20) + iVar14;
              iStack_64 = (iStack_68 - iVar20) + iVar14;
              pfStack_5c = (float *)0x0;
              iVar21 = iVar14;
              pfStack_38 = pfStack_2c;
              if (3 < param_3) {
                pfStack_30 = (float *)((param_3 - 4U >> 2) + 1);
                pfStack_5c = (float *)((int)pfStack_30 * 4);
                do {
                  *(float *)(unaff_ESI + -4 + iStack_60 * 4) =
                       in_EAX[(int)pfStack_38 + -1] + in_EAX[iVar21 + -1];
                  *(float *)(unaff_ESI + -4 + iStack_64 * 4) =
                       in_EAX[iVar21 + -1] - in_EAX[(int)pfStack_38 + -1];
                  iVar13 = iStack_60 + iVar7;
                  *(float *)(unaff_ESI + iStack_60 * 4) = in_EAX[iVar21] - in_EAX[(int)pfStack_38];
                  iVar26 = iStack_64 + iVar7;
                  *(float *)(unaff_ESI + iStack_64 * 4) = in_EAX[iVar21] + in_EAX[(int)pfStack_38];
                  iVar22 = (int)pfStack_38 + iVar8;
                  iVar21 = iVar21 + iVar8;
                  *(float *)(unaff_ESI + -4 + iVar13 * 4) =
                       in_EAX[iVar22 + -1] + in_EAX[iVar21 + -1];
                  *(float *)(unaff_ESI + -4 + iVar26 * 4) =
                       in_EAX[iVar21 + -1] - in_EAX[iVar22 + -1];
                  iVar1 = iVar13 + iVar7;
                  *(float *)(unaff_ESI + iVar13 * 4) = in_EAX[iVar21] - in_EAX[iVar22];
                  iVar13 = iVar26 + iVar7;
                  *(float *)(unaff_ESI + iVar26 * 4) = in_EAX[iVar21] + in_EAX[iVar22];
                  iVar22 = iVar22 + iVar8;
                  iVar21 = iVar21 + iVar8;
                  *(float *)(unaff_ESI + -4 + iVar1 * 4) = in_EAX[iVar22 + -1] + in_EAX[iVar21 + -1]
                  ;
                  *(float *)(unaff_ESI + -4 + iVar13 * 4) =
                       in_EAX[iVar21 + -1] - in_EAX[iVar22 + -1];
                  iVar26 = iVar1 + iVar7;
                  *(float *)(unaff_ESI + iVar1 * 4) = in_EAX[iVar21] - in_EAX[iVar22];
                  iVar1 = iVar13 + iVar7;
                  *(float *)(unaff_ESI + iVar13 * 4) = in_EAX[iVar21] + in_EAX[iVar22];
                  iVar22 = iVar22 + iVar8;
                  iVar21 = iVar21 + iVar8;
                  *(float *)(unaff_ESI + -4 + iVar26 * 4) =
                       in_EAX[iVar22 + -1] + in_EAX[iVar21 + -1];
                  *(float *)(unaff_ESI + -4 + iVar1 * 4) = in_EAX[iVar21 + -1] - in_EAX[iVar22 + -1]
                  ;
                  iStack_60 = iVar26 + iVar7;
                  *(float *)(unaff_ESI + iVar26 * 4) = in_EAX[iVar21] - in_EAX[iVar22];
                  iStack_64 = iVar1 + iVar7;
                  *(float *)(unaff_ESI + iVar1 * 4) = in_EAX[iVar21] + in_EAX[iVar22];
                  iVar21 = iVar21 + iVar8;
                  pfStack_38 = (float *)(iVar22 + iVar8);
                  pfStack_30 = (float *)((int)pfStack_30 + -1);
                } while (pfStack_30 != (float *)0x0);
              }
              if ((int)pfStack_5c < param_3) {
                pfStack_3c = (float *)(unaff_ESI + iStack_64 * 4);
                pfStack_30 = (float *)(unaff_ESI + iStack_60 * 4);
                pfStack_44 = (float *)(param_3 - (int)pfStack_5c);
                pfStack_38 = in_EAX + (int)pfStack_38;
                pfVar16 = in_EAX + iVar21;
                do {
                  pfStack_30[-1] = pfVar16[-1] + pfStack_38[-1];
                  pfStack_3c[-1] = pfVar16[-1] - pfStack_38[-1];
                  *pfStack_30 = *pfVar16 - *pfStack_38;
                  *pfStack_3c = *pfVar16 + *pfStack_38;
                  pfStack_3c = pfStack_3c + iVar7;
                  pfStack_30 = pfStack_30 + iVar7;
                  pfStack_38 = pfStack_38 + iVar8;
                  pfVar16 = pfVar16 + iVar8;
                  pfStack_44 = (float *)((int)pfStack_44 + -1);
                } while (pfStack_44 != (float *)0x0);
              }
              pfStack_58 = (float *)((int)pfStack_58 + -1);
            } while (pfStack_58 != (float *)0x0);
          }
          fStack_24 = (float)((int)fStack_24 + -1);
        } while (fStack_24 != 0.0);
      }
    }
    else if (1 < iVar11) {
      pfStack_40 = (float *)(iVar11 + -1);
      pfVar16 = (float *)(unaff_ESI + iVar12 * 4);
      iVar20 = unaff_ESI;
      do {
        iVar20 = iVar20 + iVar9 * 4;
        pfVar16 = pfVar16 + -iVar9;
        in_EAX = in_EAX + iVar7 * 2;
        if (0 < param_3) {
          pfStack_3c = (float *)param_3;
          pfVar15 = in_EAX;
          pfStack_30 = (float *)iVar20;
          pfStack_2c = pfVar16;
          do {
            if (2 < iVar7) {
              pfStack_38 = pfStack_2c;
              param_1 = (int)pfStack_30;
              iVar14 = (iVar7 - 3U >> 1) + 1;
              pfVar18 = pfVar15;
              pfVar24 = pfVar15;
              do {
                pfVar23 = pfVar24 + -2;
                *(float *)(param_1 + 4) = pfVar24[-3] + pfVar18[1];
                pfVar19 = pfVar18 + 1;
                pfVar18 = pfVar18 + 2;
                iVar14 = iVar14 + -1;
                pfStack_38[1] = *pfVar19 - pfVar24[-3];
                *(float *)(param_1 + 8) = *pfVar18 - *pfVar23;
                pfStack_38[2] = *pfVar23 + *pfVar18;
                pfVar24 = pfVar23;
                param_1 = param_1 + 8;
                pfStack_38 = pfStack_38 + 2;
              } while (iVar14 != 0);
            }
            pfStack_2c = pfStack_2c + iVar7;
            pfStack_30 = (float *)((int)pfStack_30 + iVar7 * 4);
            pfVar15 = pfVar15 + iVar8;
            pfStack_3c = (float *)((int)pfStack_3c + -1);
          } while (pfStack_3c != (float *)0x0);
        }
        pfStack_40 = (float *)((int)pfStack_40 + -1);
      } while (pfStack_40 != (float *)0x0);
    }
  }
  fStack_24 = 1.0;
  iStack_68 = param_2 * param_4;
  iVar8 = (param_2 + -1) * param_4;
  param_1 = 0;
  if (1 < iVar11) {
    iVar20 = iStack_68 - param_4;
    fVar2 = 0.0;
    pfStack_2c = param_5 + 2;
    pfStack_30 = param_5 + iStack_68 + 2;
    iStack_c = iVar11 + -1;
    do {
      param_1 = param_1 + param_4;
      iStack_68 = iStack_68 - param_4;
      pfStack_2c = pfStack_2c + param_4;
      pfStack_30 = pfStack_30 + -param_4;
      fVar5 = fStack_24 * (float)fVar28 - fVar2 * (float)fVar29;
      iStack_48 = param_4;
      local_50 = (float *)0x0;
      fVar2 = fStack_24 * (float)fVar29 + (float)fVar28 * fVar2;
      iVar14 = iStack_68;
      pfStack_58 = (float *)param_1;
      fStack_20 = (float)iVar8;
      if (3 < param_4) {
        pfStack_5c = param_6 + param_4 + 2;
        iVar21 = (param_4 - 4U >> 2) + 1;
        local_50 = (float *)(iVar21 * 4);
        pfStack_58 = (float *)(param_1 + (int)local_50);
        iStack_48 = (int)local_50 + param_4;
        iVar14 = iStack_68 + (int)local_50;
        fStack_20 = (float)(iVar8 + (int)local_50);
        pfVar16 = pfStack_2c;
        pfStack_40 = param_6 + 2;
        pfStack_3c = param_6 + iVar8 + 2;
        pfStack_38 = pfStack_30;
        do {
          pfVar16[-2] = pfStack_5c[-2] * fVar5 + pfStack_40[-2];
          pfStack_38[-2] = pfStack_3c[-2] * fVar2;
          pfVar16[-1] = pfStack_5c[-1] * fVar5 + pfStack_40[-1];
          pfStack_38[-1] = pfStack_3c[-1] * fVar2;
          *pfVar16 = *pfStack_5c * fVar5 + *pfStack_40;
          *pfStack_38 = *pfStack_3c * fVar2;
          pfVar15 = pfStack_5c + 1;
          pfStack_5c = pfStack_5c + 4;
          pfVar16[1] = *pfVar15 * fVar5 + pfStack_40[1];
          iVar21 = iVar21 + -1;
          pfStack_38[1] = pfStack_3c[1] * fVar2;
          pfVar16 = pfVar16 + 4;
          pfStack_40 = pfStack_40 + 4;
          pfStack_3c = pfStack_3c + 4;
          pfStack_38 = pfStack_38 + 4;
        } while (iVar21 != 0);
      }
      if ((int)local_50 < param_4) {
        pfStack_5c = param_6 + (int)fStack_20;
        pfStack_38 = param_5 + (int)pfStack_58;
        pfStack_40 = param_6 + iStack_48;
        iVar21 = param_4 - (int)local_50;
        pfStack_58 = param_6 + (int)local_50;
        pfStack_3c = param_5 + iVar14;
        do {
          fVar3 = *pfStack_40;
          pfStack_40 = pfStack_40 + 1;
          *pfStack_38 = fVar5 * fVar3 + *pfStack_58;
          fVar3 = *pfStack_5c;
          pfStack_5c = pfStack_5c + 1;
          iVar21 = iVar21 + -1;
          *pfStack_3c = fVar3 * fVar2;
          pfStack_58 = pfStack_58 + 1;
          pfStack_3c = pfStack_3c + 1;
          pfStack_38 = pfStack_38 + 1;
        } while (iVar21 != 0);
      }
      iStack_64 = param_4;
      if (2 < iVar11) {
        pfStack_5c = param_6 + param_4 + 2;
        pfStack_40 = param_6 + iVar20 + 2;
        iStack_14 = iVar11 + -2;
        fVar3 = fVar2;
        iStack_48 = iVar20;
        fStack_20 = fVar5;
        do {
          iStack_64 = iStack_64 + param_4;
          iStack_48 = iStack_48 - param_4;
          pfStack_5c = pfStack_5c + param_4;
          pfStack_40 = pfStack_40 + -param_4;
          fVar6 = fStack_20 * fVar5 - fVar3 * fVar2;
          local_50 = (float *)0x0;
          fVar3 = fStack_20 * fVar2 + fVar5 * fVar3;
          iVar14 = iStack_68;
          pfStack_58 = (float *)param_1;
          pfStack_38 = (float *)iStack_48;
          iStack_18 = iStack_64;
          if (3 < param_4) {
            pfStack_1c = (float *)((param_4 - 4U >> 2) + 1);
            local_50 = (float *)((int)pfStack_1c * 4);
            pfStack_58 = (float *)(param_1 + (int)local_50);
            iVar14 = iStack_68 + (int)local_50;
            iStack_18 = iStack_64 + (int)local_50;
            pfStack_38 = (float *)(iStack_48 + (int)local_50);
            pfVar16 = pfStack_2c;
            pfVar15 = pfStack_30;
            pfVar18 = pfStack_40;
            pfVar24 = pfStack_5c;
            do {
              pfStack_1c = (float *)((int)pfStack_1c + -1);
              pfVar16[-2] = pfVar24[-2] * fVar6 + pfVar16[-2];
              pfVar15[-2] = pfVar18[-2] * fVar3 + pfVar15[-2];
              pfVar16[-1] = pfVar24[-1] * fVar6 + pfVar16[-1];
              pfVar15[-1] = pfVar18[-1] * fVar3 + pfVar15[-1];
              *pfVar16 = *pfVar24 * fVar6 + *pfVar16;
              *pfVar15 = *pfVar18 * fVar3 + *pfVar15;
              pfVar16[1] = pfVar24[1] * fVar6 + pfVar16[1];
              pfVar15[1] = pfVar18[1] * fVar3 + pfVar15[1];
              pfVar16 = pfVar16 + 4;
              pfVar15 = pfVar15 + 4;
              pfVar18 = pfVar18 + 4;
              pfVar24 = pfVar24 + 4;
            } while (pfStack_1c != (float *)0x0);
          }
          if ((int)local_50 < param_4) {
            pfStack_3c = param_6 + (int)pfStack_38;
            pfStack_38 = param_6 + iStack_18;
            iVar21 = param_4 - (int)local_50;
            pfVar16 = param_5 + (int)pfStack_58;
            pfStack_1c = param_5 + iVar14;
            do {
              fVar4 = *pfStack_38;
              pfStack_38 = pfStack_38 + 1;
              *pfVar16 = fVar4 * fVar6 + *pfVar16;
              iVar21 = iVar21 + -1;
              *pfStack_1c = *pfStack_3c * fVar3 + *pfStack_1c;
              pfVar16 = pfVar16 + 1;
              pfStack_3c = pfStack_3c + 1;
              pfStack_1c = pfStack_1c + 1;
            } while (iVar21 != 0);
          }
          iStack_14 = iStack_14 + -1;
          fStack_20 = fVar6;
        } while (iStack_14 != 0);
      }
      iStack_c = iStack_c + -1;
      fStack_24 = fVar5;
    } while (iStack_c != 0);
  }
  param_1 = 0;
  if (1 < iVar11) {
    pfStack_2c = param_6 + 2;
    iStack_10 = iVar11 + -1;
    do {
      param_1 = param_1 + param_4;
      pfStack_2c = pfStack_2c + param_4;
      iVar8 = 0;
      iStack_68 = param_1;
      if (3 < param_4) {
        iStack_c = (param_4 - 4U >> 2) + 1;
        iVar8 = iStack_c * 4;
        iStack_68 = param_1 + iVar8;
        pfVar16 = param_6 + 2;
        pfVar15 = pfStack_2c;
        do {
          iStack_c = iStack_c + -1;
          pfVar16[-2] = pfVar15[-2] + pfVar16[-2];
          pfVar16[-1] = pfVar15[-1] + pfVar16[-1];
          *pfVar16 = *pfVar15 + *pfVar16;
          pfVar16[1] = pfVar15[1] + pfVar16[1];
          pfVar16 = pfVar16 + 4;
          pfVar15 = pfVar15 + 4;
        } while (iStack_c != 0);
      }
      if (iVar8 < param_4) {
        pfVar16 = param_6 + iStack_68;
        do {
          fVar2 = *pfVar16;
          iVar20 = iVar8 + 1;
          pfVar16 = pfVar16 + 1;
          param_6[iVar8] = fVar2 + param_6[iVar8];
          iVar8 = iVar20;
        } while (iVar20 < param_4);
      }
      iStack_10 = iStack_10 + -1;
    } while (iStack_10 != 0);
  }
  iVar8 = 0;
  if (1 < iVar11) {
    iStack_10 = iVar11 + -1;
    iVar20 = iVar12;
    do {
      iVar8 = iVar8 + iVar9;
      iVar20 = iVar20 - iVar9;
      pfStack_5c = (float *)0x0;
      iVar14 = iVar8;
      iVar21 = iVar20;
      if (3 < param_3) {
        iVar13 = (param_3 - 4U >> 2) + 1;
        pfStack_5c = (float *)(iVar13 * 4);
        do {
          *(float *)(unaff_ESI + iVar14 * 4) =
               *(float *)(unaff_EBX + iVar14 * 4) - *(float *)(unaff_EBX + iVar21 * 4);
          iVar26 = iVar14 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) =
               *(float *)(unaff_EBX + iVar21 * 4) + *(float *)(unaff_EBX + iVar14 * 4);
          iVar21 = iVar21 + iVar7;
          *(float *)(unaff_ESI + iVar26 * 4) =
               *(float *)(unaff_EBX + iVar26 * 4) - *(float *)(unaff_EBX + iVar21 * 4);
          iVar14 = iVar26 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) =
               *(float *)(unaff_EBX + iVar21 * 4) + *(float *)(unaff_EBX + iVar26 * 4);
          iVar21 = iVar21 + iVar7;
          *(float *)(unaff_ESI + iVar14 * 4) =
               *(float *)(unaff_EBX + iVar14 * 4) - *(float *)(unaff_EBX + iVar21 * 4);
          iVar26 = iVar14 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) =
               *(float *)(unaff_EBX + iVar21 * 4) + *(float *)(unaff_EBX + iVar14 * 4);
          iVar21 = iVar21 + iVar7;
          *(float *)(unaff_ESI + iVar26 * 4) =
               *(float *)(unaff_EBX + iVar26 * 4) - *(float *)(unaff_EBX + iVar21 * 4);
          iVar14 = iVar26 + iVar7;
          *(float *)(unaff_ESI + iVar21 * 4) =
               *(float *)(unaff_EBX + iVar21 * 4) + *(float *)(unaff_EBX + iVar26 * 4);
          iVar21 = iVar21 + iVar7;
          iVar13 = iVar13 + -1;
        } while (iVar13 != 0);
      }
      if ((int)pfStack_5c < param_3) {
        iStack_c = param_3 - (int)pfStack_5c;
        pfVar16 = (float *)(unaff_EBX + iVar14 * 4);
        pfVar15 = (float *)(unaff_EBX + iVar21 * 4);
        do {
          *(float *)((unaff_ESI - unaff_EBX) + (int)pfVar16) = *pfVar16 - *pfVar15;
          *(float *)((unaff_ESI - unaff_EBX) + (int)pfVar15) = *pfVar16 + *pfVar15;
          pfVar16 = pfVar16 + iVar7;
          pfVar15 = pfVar15 + iVar7;
          iStack_c = iStack_c + -1;
        } while (iStack_c != 0);
      }
      iStack_10 = iStack_10 + -1;
    } while (iStack_10 != 0);
  }
  if (iVar7 != 1) {
    if (iVar10 < param_3) {
      iVar8 = 0;
      if (1 < iVar11) {
        iStack_14 = iVar11 + -1;
        iStack_68 = iVar12;
        do {
          iVar8 = iVar8 + iVar9;
          iStack_68 = iStack_68 - iVar9;
          if (2 < iVar7) {
            iStack_10 = (iVar7 - 3U >> 1) + 1;
            iVar11 = iVar8;
            do {
              iVar11 = iVar11 + 2;
              iVar20 = (iStack_68 - iVar8) + iVar11;
              pfStack_5c = (float *)0x0;
              iVar12 = iVar11;
              if (3 < param_3) {
                iVar14 = (param_3 - 4U >> 2) + 1;
                pfStack_5c = (float *)(iVar14 * 4);
                do {
                  *(float *)(unaff_ESI + -4 + iVar12 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar12 * 4) - *(float *)(unaff_EBX + iVar20 * 4);
                  *(float *)(unaff_ESI + -4 + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar20 * 4) + *(float *)(unaff_EBX + -4 + iVar12 * 4);
                  *(float *)(unaff_ESI + iVar12 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar20 * 4) + *(float *)(unaff_EBX + iVar12 * 4);
                  iVar21 = iVar12 + iVar7;
                  *(float *)(unaff_ESI + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar12 * 4) - *(float *)(unaff_EBX + -4 + iVar20 * 4);
                  iVar20 = iVar20 + iVar7;
                  *(float *)(unaff_ESI + -4 + iVar21 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar21 * 4) - *(float *)(unaff_EBX + iVar20 * 4);
                  *(float *)(unaff_ESI + -4 + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar20 * 4) + *(float *)(unaff_EBX + -4 + iVar21 * 4);
                  *(float *)(unaff_ESI + iVar21 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar20 * 4) + *(float *)(unaff_EBX + iVar21 * 4);
                  iVar12 = iVar21 + iVar7;
                  *(float *)(unaff_ESI + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar21 * 4) - *(float *)(unaff_EBX + -4 + iVar20 * 4);
                  iVar20 = iVar20 + iVar7;
                  *(float *)(unaff_ESI + -4 + iVar12 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar12 * 4) - *(float *)(unaff_EBX + iVar20 * 4);
                  *(float *)(unaff_ESI + -4 + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar20 * 4) + *(float *)(unaff_EBX + -4 + iVar12 * 4);
                  *(float *)(unaff_ESI + iVar12 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar20 * 4) + *(float *)(unaff_EBX + iVar12 * 4);
                  iVar21 = iVar12 + iVar7;
                  *(float *)(unaff_ESI + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar12 * 4) - *(float *)(unaff_EBX + -4 + iVar20 * 4);
                  iVar20 = iVar20 + iVar7;
                  *(float *)(unaff_ESI + -4 + iVar21 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar21 * 4) - *(float *)(unaff_EBX + iVar20 * 4);
                  *(float *)(unaff_ESI + -4 + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar20 * 4) + *(float *)(unaff_EBX + -4 + iVar21 * 4);
                  *(float *)(unaff_ESI + iVar21 * 4) =
                       *(float *)(unaff_EBX + -4 + iVar20 * 4) + *(float *)(unaff_EBX + iVar21 * 4);
                  iVar12 = iVar21 + iVar7;
                  *(float *)(unaff_ESI + iVar20 * 4) =
                       *(float *)(unaff_EBX + iVar21 * 4) - *(float *)(unaff_EBX + -4 + iVar20 * 4);
                  iVar20 = iVar20 + iVar7;
                  iVar14 = iVar14 + -1;
                } while (iVar14 != 0);
              }
              if ((int)pfStack_5c < param_3) {
                iStack_c = param_3 - (int)pfStack_5c;
                pfVar16 = (float *)(unaff_EBX + -4 + iVar20 * 4);
                pfVar15 = (float *)(unaff_EBX + -4 + iVar12 * 4);
                pfStack_30 = (float *)(unaff_ESI + iVar20 * 4);
                pfStack_2c = (float *)(unaff_ESI + iVar12 * 4);
                do {
                  *(float *)((unaff_ESI - unaff_EBX) + (int)pfVar15) = *pfVar15 - pfVar16[1];
                  *(float *)((unaff_ESI - unaff_EBX) + (int)pfVar16) = *pfVar15 + pfVar16[1];
                  *pfStack_2c = *pfVar16 + pfVar15[1];
                  pfVar18 = pfVar15 + 1;
                  fVar2 = *pfVar16;
                  pfVar15 = pfVar15 + iVar7;
                  pfVar16 = pfVar16 + iVar7;
                  iStack_c = iStack_c + -1;
                  *pfStack_30 = *pfVar18 - fVar2;
                  pfStack_30 = pfStack_30 + iVar7;
                  pfStack_2c = pfStack_2c + iVar7;
                } while (iStack_c != 0);
              }
              iStack_10 = iStack_10 + -1;
            } while (iStack_10 != 0);
          }
          iStack_14 = iStack_14 + -1;
        } while (iStack_14 != 0);
      }
    }
    else if (1 < iVar11) {
      pfStack_2c = (float *)(unaff_ESI + iVar12 * 4);
      pfStack_30 = (float *)(unaff_EBX + -4 + iVar12 * 4);
      param_1 = unaff_EBX + -4;
      iStack_14 = iVar11 + -1;
      param_4 = unaff_ESI;
      do {
        param_4 = param_4 + iVar9 * 4;
        param_1 = param_1 + iVar9 * 4;
        pfStack_2c = pfStack_2c + -iVar9;
        pfStack_30 = pfStack_30 + -iVar9;
        if (0 < param_3) {
          iStack_10 = param_3;
          local_50 = pfStack_30;
          pfStack_44 = pfStack_2c;
          pfStack_40 = (float *)param_1;
          pfStack_3c = (float *)param_4;
          do {
            if (2 < iVar7) {
              iStack_c = (iVar7 - 3U >> 1) + 1;
              pfStack_34 = pfStack_3c;
              pfStack_38 = pfStack_44;
              pfVar16 = pfStack_40;
              pfVar15 = local_50;
              do {
                pfStack_34 = pfStack_34 + 2;
                pfStack_38 = pfStack_38 + 2;
                pfVar18 = pfVar16 + 2;
                pfVar24 = pfVar15 + 2;
                *(float *)((int)pfVar18 + (unaff_ESI - unaff_EBX)) = pfVar16[2] - pfVar15[3];
                iStack_c = iStack_c + -1;
                *(float *)((int)pfVar24 + (unaff_ESI - unaff_EBX)) = pfVar15[3] + *pfVar18;
                *pfStack_34 = *pfVar24 + pfVar16[3];
                *pfStack_38 = pfVar16[3] - *pfVar24;
                pfVar16 = pfVar18;
                pfVar15 = pfVar24;
              } while (iStack_c != 0);
            }
            pfStack_3c = pfStack_3c + iVar7;
            pfStack_40 = pfStack_40 + iVar7;
            pfStack_44 = pfStack_44 + iVar7;
            local_50 = local_50 + iVar7;
            iStack_10 = iStack_10 + -1;
          } while (iStack_10 != 0);
        }
        iStack_14 = iStack_14 + -1;
      } while (iStack_14 != 0);
    }
    iVar8 = 0;
    if (3 < iVar27) {
      param_1 = (iVar27 - 4U >> 2) + 1;
      iVar8 = param_1 * 4;
      pfVar16 = param_5 + 1;
      param_4 = (int)(param_6 + 3);
      do {
        pfVar16[-1] = *(float *)(param_4 + -0xc);
        *pfVar16 = *(float *)((int)pfVar16 + ((int)param_6 - (int)param_5));
        param_1 = param_1 + -1;
        pfVar16[1] = *(float *)(param_4 + -4);
        pfVar16[2] = *(float *)param_4;
        pfVar16 = pfVar16 + 4;
        param_4 = param_4 + 0x10;
      } while (param_1 != 0);
    }
    if (iVar8 < iVar27) {
      iVar27 = iVar27 - iVar8;
      pfVar16 = param_5 + iVar8;
      do {
        iVar27 = iVar27 + -1;
        *pfVar16 = *(float *)((int)pfVar16 + ((int)param_6 - (int)param_5));
        pfVar16 = pfVar16 + 1;
      } while (iVar27 != 0);
    }
    iVar27 = 0;
    if (1 < param_2) {
      param_4 = param_2 + -1;
      do {
        iVar27 = iVar27 + iVar9;
        iVar8 = 0;
        iVar11 = iVar27;
        if (3 < param_3) {
          iVar12 = (param_3 - 4U >> 2) + 1;
          iVar8 = iVar12 * 4;
          do {
            *(undefined4 *)(unaff_EBX + iVar11 * 4) = *(undefined4 *)(unaff_ESI + iVar11 * 4);
            iVar11 = iVar11 + iVar7;
            *(undefined4 *)(unaff_EBX + iVar11 * 4) = *(undefined4 *)(unaff_ESI + iVar11 * 4);
            iVar11 = iVar11 + iVar7;
            *(undefined4 *)(unaff_EBX + iVar11 * 4) = *(undefined4 *)(unaff_ESI + iVar11 * 4);
            iVar11 = iVar11 + iVar7;
            *(undefined4 *)(unaff_EBX + iVar11 * 4) = *(undefined4 *)(unaff_ESI + iVar11 * 4);
            iVar11 = iVar11 + iVar7;
            iVar12 = iVar12 + -1;
          } while (iVar12 != 0);
        }
        if (iVar8 < param_3) {
          puVar17 = (undefined4 *)(unaff_EBX + iVar11 * 4);
          iVar8 = param_3 - iVar8;
          do {
            *puVar17 = *(undefined4 *)((unaff_ESI - unaff_EBX) + (int)puVar17);
            puVar17 = puVar17 + iVar7;
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
        param_4 = param_4 + -1;
      } while (param_4 != 0);
    }
    if (param_3 < iVar10) {
      if (1 < param_2) {
        pfVar16 = param_7 + (-1 - iVar7);
        param_4 = unaff_ESI + -4;
        iStack_14 = param_2 + -1;
        param_2 = unaff_EBX;
        do {
          param_2 = param_2 + iVar9 * 4;
          param_4 = param_4 + iVar9 * 4;
          pfVar16 = pfVar16 + iVar7;
          if (0 < param_3) {
            iStack_10 = param_3;
            pfVar15 = (float *)param_2;
            param_1 = param_4;
            do {
              if (2 < iVar7) {
                iVar27 = (iVar7 - 3U >> 1) + 1;
                pfVar18 = (float *)param_1;
                pfVar24 = pfVar16;
                pfVar19 = pfVar15;
                do {
                  pfVar25 = pfVar24 + 2;
                  pfVar23 = pfVar18 + 2;
                  pfVar19 = pfVar19 + 2;
                  iVar27 = iVar27 + -1;
                  *(float *)((unaff_EBX - unaff_ESI) + (int)pfVar23) =
                       pfVar24[1] * pfVar18[2] - *pfVar25 * pfVar18[3];
                  *pfVar19 = pfVar18[3] * pfVar24[1] + *pfVar25 * *pfVar23;
                  pfVar18 = pfVar23;
                  pfVar24 = pfVar25;
                } while (iVar27 != 0);
              }
              param_1 = param_1 + iVar7 * 4;
              pfVar15 = pfVar15 + iVar7;
              iStack_10 = iStack_10 + -1;
            } while (iStack_10 != 0);
          }
          iStack_14 = iStack_14 + -1;
        } while (iStack_14 != 0);
        return;
      }
    }
    else {
      iVar27 = 0;
      if (1 < param_2) {
        iStack_c = param_2 + -1;
        pfVar16 = param_7 + (-1 - iVar7);
        do {
          iVar27 = iVar27 + iVar9;
          pfVar16 = pfVar16 + iVar7;
          if (2 < iVar7) {
            param_4 = (iVar7 - 3U >> 1) + 1;
            iVar8 = iVar27;
            pfVar15 = pfVar16;
            do {
              iVar8 = iVar8 + 2;
              pfVar18 = pfVar15 + 2;
              pfStack_5c = (float *)0x0;
              iVar10 = iVar8;
              if (3 < param_3) {
                iVar11 = (param_3 - 4U >> 2) + 1;
                pfStack_5c = (float *)(iVar11 * 4);
                do {
                  *(float *)(unaff_EBX + -4 + iVar10 * 4) =
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * pfVar15[1] -
                       *(float *)(unaff_ESI + iVar10 * 4) * *pfVar18;
                  *(float *)(unaff_EBX + iVar10 * 4) =
                       *(float *)(unaff_ESI + iVar10 * 4) * pfVar15[1] +
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * *pfVar18;
                  iVar10 = iVar10 + iVar7;
                  *(float *)(unaff_EBX + -4 + iVar10 * 4) =
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * pfVar15[1] -
                       *(float *)(unaff_ESI + iVar10 * 4) * *pfVar18;
                  *(float *)(unaff_EBX + iVar10 * 4) =
                       *(float *)(unaff_ESI + iVar10 * 4) * pfVar15[1] +
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * *pfVar18;
                  iVar10 = iVar10 + iVar7;
                  *(float *)(unaff_EBX + -4 + iVar10 * 4) =
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * pfVar15[1] -
                       *(float *)(unaff_ESI + iVar10 * 4) * *pfVar18;
                  *(float *)(unaff_EBX + iVar10 * 4) =
                       *(float *)(unaff_ESI + iVar10 * 4) * pfVar15[1] +
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * *pfVar18;
                  iVar10 = iVar10 + iVar7;
                  *(float *)(unaff_EBX + -4 + iVar10 * 4) =
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * pfVar15[1] -
                       *(float *)(unaff_ESI + iVar10 * 4) * *pfVar18;
                  *(float *)(unaff_EBX + iVar10 * 4) =
                       *(float *)(unaff_ESI + iVar10 * 4) * pfVar15[1] +
                       *(float *)(unaff_ESI + -4 + iVar10 * 4) * *pfVar18;
                  iVar10 = iVar10 + iVar7;
                  iVar11 = iVar11 + -1;
                } while (iVar11 != 0);
              }
              if ((int)pfStack_5c < param_3) {
                param_2 = param_3 - (int)pfStack_5c;
                pfVar24 = (float *)(unaff_EBX + iVar10 * 4);
                pfVar19 = (float *)(unaff_ESI + -4 + iVar10 * 4);
                do {
                  *(float *)((unaff_EBX - unaff_ESI) + (int)pfVar19) =
                       pfVar15[1] * *pfVar19 - pfVar19[1] * *pfVar18;
                  pfVar23 = pfVar19 + 1;
                  fVar2 = *pfVar19;
                  pfVar19 = pfVar19 + iVar7;
                  *pfVar24 = *pfVar18 * fVar2 + *pfVar23 * pfVar15[1];
                  pfVar24 = pfVar24 + iVar7;
                  param_2 = param_2 + -1;
                } while (param_2 != 0);
              }
              param_4 = param_4 + -1;
              pfVar15 = pfVar18;
            } while (param_4 != 0);
          }
          iStack_c = iStack_c + -1;
        } while (iStack_c != 0);
      }
    }
  }
  return;
}
