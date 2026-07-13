/*
 * Entry: 005a9350
 * Name: dradfg
 * Namespace: Global
 * Signature: void dradfg(int param_1, int param_2, int param_3, int param_4, float * param_5, float * param_6, float * param_7, float * param_8, float * param_9, float * param_10)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
dradfg(int param_1,int param_2,int param_3,int param_4,float *param_5,float *param_6,float *param_7,
      float *param_8,float *param_9,float *param_10)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  float fVar5;
  float fVar6;
  int in_EAX;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 *puVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  float *pfVar18;
  undefined4 *puVar19;
  float *pfVar20;
  float *in_ECX;
  int iVar21;
  float *pfVar22;
  int iVar23;
  int iVar24;
  float *pfVar25;
  int iVar26;
  int unaff_EBX;
  int iVar27;
  int iVar28;
  float10 fVar29;
  float10 fVar30;
  float *pfStack_60;
  int iStack_5c;
  int iStack_54;
  float *pfStack_44;
  float *pfStack_40;
  float *pfStack_3c;
  float *pfStack_38;
  float *pfStack_34;
  float *pfStack_30;
  float *pfStack_2c;
  float *pfStack_28;
  float *pfStack_24;
  float *local_20;
  float fStack_1c;
  float fStack_18;
  int iStack_14;
  int iStack_10;
  int iStack_c;
  int iStack_8;
  int iStack_4;
  
  iVar27 = param_3;
  fVar29 = (float10)__CIcos();
  fVar30 = (float10)__CIsin();
  iStack_8 = param_1 + 1 >> 1;
  iVar7 = unaff_EBX + -1 >> 1;
  iVar8 = unaff_EBX * param_2;
  iVar9 = unaff_EBX * param_1;
  if (unaff_EBX != 1) {
    iVar23 = 0;
    if (3 < param_3) {
      pfStack_24 = (float *)((param_3 - 4U >> 2) + 1);
      iVar23 = (int)pfStack_24 * 4;
      pfVar18 = param_6 + 1;
      pfVar25 = param_5 + 3;
      do {
        pfVar18[-1] = pfVar25[-3];
        pfStack_24 = (float *)((int)pfStack_24 + -1);
        *pfVar18 = *(float *)((int)param_5 + (-0x10 - (int)param_6) + (int)(pfVar18 + 4));
        pfVar18[1] = pfVar25[-1];
        pfVar18[2] = *pfVar25;
        pfVar18 = pfVar18 + 4;
        pfVar25 = pfVar25 + 4;
      } while (pfStack_24 != (float *)0x0);
    }
    if (iVar23 < param_3) {
      iVar21 = param_3 - iVar23;
      pfVar18 = param_6 + iVar23;
      do {
        iVar21 = iVar21 + -1;
        *pfVar18 = *(float *)((int)pfVar18 + ((int)param_5 - (int)param_6));
        pfVar18 = pfVar18 + 1;
      } while (iVar21 != 0);
    }
    iVar23 = 0;
    if (1 < param_1) {
      pfStack_24 = (float *)(param_1 + -1);
      do {
        iVar23 = iVar23 + iVar8;
        pfStack_60 = (float *)0x0;
        iVar21 = iVar23;
        if (3 < param_2) {
          iVar24 = (param_2 - 4U >> 2) + 1;
          pfStack_60 = (float *)(iVar24 * 4);
          do {
            *(float *)(in_EAX + iVar21 * 4) = in_ECX[iVar21];
            iVar21 = iVar21 + unaff_EBX;
            *(float *)(in_EAX + iVar21 * 4) = in_ECX[iVar21];
            iVar21 = iVar21 + unaff_EBX;
            *(float *)(in_EAX + iVar21 * 4) = in_ECX[iVar21];
            iVar21 = iVar21 + unaff_EBX;
            *(float *)(in_EAX + iVar21 * 4) = in_ECX[iVar21];
            iVar21 = iVar21 + unaff_EBX;
            iVar24 = iVar24 + -1;
          } while (iVar24 != 0);
        }
        if ((int)pfStack_60 < param_2) {
          iVar24 = param_2 - (int)pfStack_60;
          puVar10 = (undefined4 *)(in_EAX + iVar21 * 4);
          do {
            *puVar10 = *(undefined4 *)(((int)in_ECX - in_EAX) + (int)puVar10);
            puVar10 = puVar10 + unaff_EBX;
            iVar24 = iVar24 + -1;
          } while (iVar24 != 0);
        }
        pfStack_24 = (float *)((int)pfStack_24 + -1);
      } while (pfStack_24 != (float *)0x0);
    }
    iVar23 = -unaff_EBX;
    iVar21 = 0;
    if (param_2 < iVar7) {
      if (1 < param_1) {
        pfStack_28 = param_7 + (-1 - unaff_EBX);
        pfVar25 = (float *)(in_EAX + unaff_EBX * -4);
        pfVar18 = in_ECX + (-1 - unaff_EBX);
        pfStack_3c = (float *)(param_1 + -1);
        do {
          pfVar25 = pfVar25 + iVar8;
          pfVar18 = pfVar18 + iVar8;
          pfStack_28 = pfStack_28 + unaff_EBX;
          if (0 < param_2) {
            pfStack_38 = (float *)param_2;
            pfVar20 = pfVar18;
            pfVar13 = pfVar25;
            do {
              pfVar13 = pfVar13 + unaff_EBX;
              pfVar20 = pfVar20 + unaff_EBX;
              if (2 < unaff_EBX) {
                pfStack_34 = (float *)((unaff_EBX - 3U >> 1) + 1);
                pfVar11 = pfVar20;
                pfVar22 = pfStack_28;
                pfStack_2c = pfVar13;
                do {
                  pfStack_2c = pfStack_2c + 2;
                  pfVar12 = pfVar11 + 2;
                  pfStack_34 = (float *)((int)pfStack_34 + -1);
                  *(float *)((in_EAX - (int)in_ECX) + (int)pfVar12) =
                       pfVar22[1] * *pfVar12 + pfVar11[3] * pfVar22[2];
                  *pfStack_2c = pfVar11[3] * pfVar22[1] - pfVar22[2] * *pfVar12;
                  pfVar11 = pfVar12;
                  pfVar22 = pfVar22 + 2;
                } while (pfStack_34 != (float *)0x0);
              }
              pfStack_38 = (float *)((int)pfStack_38 + -1);
            } while (pfStack_38 != (float *)0x0);
          }
          pfStack_3c = (float *)((int)pfStack_3c + -1);
        } while (pfStack_3c != (float *)0x0);
      }
    }
    else if (1 < param_1) {
      pfStack_28 = (float *)(iVar23 + -1);
      pfStack_2c = param_7 + (-1 - unaff_EBX);
      pfStack_40 = (float *)(param_1 + -1);
      iVar24 = iVar23;
      do {
        iVar21 = iVar21 + iVar8;
        pfStack_28 = (float *)((int)pfStack_28 + unaff_EBX);
        iVar24 = iVar24 + unaff_EBX;
        pfStack_2c = pfStack_2c + unaff_EBX;
        if (2 < unaff_EBX) {
          pfStack_34 = (float *)(((int)pfStack_28 - iVar24) + 1 + iVar21);
          pfStack_3c = (float *)((unaff_EBX - 3U >> 1) + 1);
          pfVar18 = pfStack_2c;
          do {
            pfStack_34 = (float *)((int)pfStack_34 + 2);
            pfVar25 = pfVar18 + 2;
            pfStack_60 = (float *)0x0;
            iVar14 = (int)pfStack_34;
            if (3 < param_2) {
              iVar26 = (param_2 - 4U >> 2) + 1;
              pfStack_60 = (float *)(iVar26 * 4);
              do {
                *(float *)(in_EAX + -4 + iVar14 * 4) =
                     in_ECX[iVar14] * *pfVar25 + pfVar18[1] * in_ECX[iVar14 + -1];
                *(float *)(in_EAX + iVar14 * 4) =
                     pfVar18[1] * in_ECX[iVar14] - in_ECX[iVar14 + -1] * *pfVar25;
                iVar14 = iVar14 + unaff_EBX;
                *(float *)(in_EAX + -4 + iVar14 * 4) =
                     in_ECX[iVar14] * *pfVar25 + pfVar18[1] * in_ECX[iVar14 + -1];
                *(float *)(in_EAX + iVar14 * 4) =
                     pfVar18[1] * in_ECX[iVar14] - in_ECX[iVar14 + -1] * *pfVar25;
                iVar14 = iVar14 + unaff_EBX;
                *(float *)(in_EAX + -4 + iVar14 * 4) =
                     in_ECX[iVar14] * *pfVar25 + pfVar18[1] * in_ECX[iVar14 + -1];
                *(float *)(in_EAX + iVar14 * 4) =
                     pfVar18[1] * in_ECX[iVar14] - in_ECX[iVar14 + -1] * *pfVar25;
                iVar14 = iVar14 + unaff_EBX;
                *(float *)(in_EAX + -4 + iVar14 * 4) =
                     in_ECX[iVar14] * *pfVar25 + pfVar18[1] * in_ECX[iVar14 + -1];
                *(float *)(in_EAX + iVar14 * 4) =
                     pfVar18[1] * in_ECX[iVar14] - in_ECX[iVar14 + -1] * *pfVar25;
                iVar14 = iVar14 + unaff_EBX;
                iVar26 = iVar26 + -1;
              } while (iVar26 != 0);
            }
            if ((int)pfStack_60 < param_2) {
              pfStack_38 = (float *)(param_2 - (int)pfStack_60);
              pfVar20 = (float *)(in_EAX + iVar14 * 4);
              pfVar13 = in_ECX + iVar14 + -1;
              do {
                *(float *)((in_EAX - (int)in_ECX) + (int)pfVar13) =
                     pfVar13[1] * *pfVar25 + pfVar18[1] * *pfVar13;
                pfVar11 = pfVar13 + 1;
                fVar1 = *pfVar13;
                pfVar13 = pfVar13 + unaff_EBX;
                *pfVar20 = pfVar18[1] * *pfVar11 - *pfVar25 * fVar1;
                pfVar20 = pfVar20 + unaff_EBX;
                pfStack_38 = (float *)((int)pfStack_38 + -1);
              } while (pfStack_38 != (float *)0x0);
            }
            pfStack_3c = (float *)((int)pfStack_3c + -1);
            pfVar18 = pfVar25;
          } while (pfStack_3c != (float *)0x0);
        }
        pfStack_40 = (float *)((int)pfStack_40 + -1);
      } while (pfStack_40 != (float *)0x0);
    }
    iVar21 = iVar8 * param_1;
    iStack_5c = 0;
    if (iVar7 < param_2) {
      if (1 < iStack_8) {
        pfStack_3c = (float *)(iStack_8 + -1);
        pfStack_28 = (float *)iVar23;
        do {
          iStack_5c = iStack_5c + iVar8;
          pfStack_28 = (float *)((int)pfStack_28 + iVar8);
          iVar21 = iVar21 - iVar8;
          if (2 < unaff_EBX) {
            pfStack_38 = (float *)((unaff_EBX - 3U >> 1) + 1);
            iVar23 = (int)pfStack_28;
            do {
              iVar23 = iVar23 + 2;
              iVar24 = iVar23 + (iVar21 - iStack_5c);
              pfStack_60 = (float *)0x0;
              iVar14 = iVar23;
              if (3 < param_2) {
                iVar26 = (param_2 - 4U >> 2) + 1;
                pfStack_60 = (float *)(iVar26 * 4);
                do {
                  iVar24 = iVar24 + unaff_EBX;
                  iVar14 = iVar14 + unaff_EBX;
                  in_ECX[iVar14 + -1] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) + *(float *)(in_EAX + -4 + iVar14 * 4);
                  in_ECX[iVar24 + -1] =
                       *(float *)(in_EAX + iVar14 * 4) - *(float *)(in_EAX + iVar24 * 4);
                  in_ECX[iVar14] = *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar24 * 4)
                  ;
                  iVar15 = iVar14 + unaff_EBX;
                  in_ECX[iVar24] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) - *(float *)(in_EAX + -4 + iVar14 * 4);
                  iVar24 = iVar24 + unaff_EBX;
                  in_ECX[iVar15 + -1] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) + *(float *)(in_EAX + -4 + iVar15 * 4);
                  in_ECX[iVar24 + -1] =
                       *(float *)(in_EAX + iVar15 * 4) - *(float *)(in_EAX + iVar24 * 4);
                  in_ECX[iVar15] = *(float *)(in_EAX + iVar15 * 4) + *(float *)(in_EAX + iVar24 * 4)
                  ;
                  iVar16 = iVar15 + unaff_EBX;
                  in_ECX[iVar24] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) - *(float *)(in_EAX + -4 + iVar15 * 4);
                  iVar24 = iVar24 + unaff_EBX;
                  in_ECX[iVar16 + -1] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) + *(float *)(in_EAX + -4 + iVar16 * 4);
                  in_ECX[iVar24 + -1] =
                       *(float *)(in_EAX + iVar16 * 4) - *(float *)(in_EAX + iVar24 * 4);
                  in_ECX[iVar16] = *(float *)(in_EAX + iVar16 * 4) + *(float *)(in_EAX + iVar24 * 4)
                  ;
                  iVar14 = iVar16 + unaff_EBX;
                  in_ECX[iVar24] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) - *(float *)(in_EAX + -4 + iVar16 * 4);
                  iVar24 = iVar24 + unaff_EBX;
                  iVar26 = iVar26 + -1;
                  in_ECX[iVar14 + -1] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) + *(float *)(in_EAX + -4 + iVar14 * 4);
                  in_ECX[iVar24 + -1] =
                       *(float *)(in_EAX + iVar14 * 4) - *(float *)(in_EAX + iVar24 * 4);
                  in_ECX[iVar14] = *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar24 * 4)
                  ;
                  in_ECX[iVar24] =
                       *(float *)(in_EAX + -4 + iVar24 * 4) - *(float *)(in_EAX + -4 + iVar14 * 4);
                } while (iVar26 != 0);
              }
              if ((int)pfStack_60 < param_2) {
                pfStack_30 = in_ECX + iVar24;
                pfStack_2c = in_ECX + iVar14;
                pfStack_24 = (float *)(param_2 - (int)pfStack_60);
                pfVar18 = (float *)(in_EAX + -4 + iVar14 * 4);
                pfVar25 = (float *)(in_EAX + -4 + iVar24 * 4);
                do {
                  pfVar20 = pfVar18 + unaff_EBX;
                  pfVar13 = pfVar25 + unaff_EBX;
                  pfStack_2c = pfStack_2c + unaff_EBX;
                  pfStack_30 = pfStack_30 + unaff_EBX;
                  pfVar18 = pfVar18 + unaff_EBX;
                  pfVar25 = pfVar25 + unaff_EBX;
                  *(float *)((int)pfVar18 + ((int)in_ECX - in_EAX)) = *pfVar20 + *pfVar13;
                  pfStack_24 = (float *)((int)pfStack_24 + -1);
                  *(float *)((int)pfVar25 + ((int)in_ECX - in_EAX)) = pfVar18[1] - pfVar25[1];
                  *pfStack_2c = pfVar25[1] + pfVar18[1];
                  *pfStack_30 = *pfVar25 - *pfVar18;
                } while (pfStack_24 != (float *)0x0);
              }
              pfStack_38 = (float *)((int)pfStack_38 + -1);
            } while (pfStack_38 != (float *)0x0);
          }
          pfStack_3c = (float *)((int)pfStack_3c + -1);
        } while (pfStack_3c != (float *)0x0);
      }
    }
    else if (1 < iStack_8) {
      pfStack_2c = in_ECX + iVar21;
      pfStack_30 = (float *)(in_EAX + -4 + iVar21 * 4);
      pfStack_28 = (float *)(in_EAX + -4);
      iStack_5c = iStack_8 + -1;
      pfVar18 = in_ECX;
      do {
        pfStack_28 = pfStack_28 + iVar8;
        pfStack_2c = pfStack_2c + -iVar8;
        pfStack_30 = pfStack_30 + -iVar8;
        pfVar18 = pfVar18 + iVar8;
        if (0 < param_2) {
          iStack_54 = param_2;
          pfVar25 = pfStack_30;
          pfStack_44 = pfStack_2c;
          pfStack_40 = pfStack_28;
          pfStack_3c = pfVar18;
          do {
            if (2 < unaff_EBX) {
              pfStack_38 = pfStack_44;
              pfStack_34 = pfStack_3c;
              iVar23 = (unaff_EBX - 3U >> 1) + 1;
              pfVar20 = pfStack_40;
              pfVar13 = pfVar25;
              do {
                pfStack_34 = pfStack_34 + 2;
                pfStack_38 = pfStack_38 + 2;
                pfVar22 = pfVar13 + 2;
                pfVar11 = pfVar20 + 2;
                iVar23 = iVar23 + -1;
                *(float *)((int)pfVar11 + ((int)in_ECX - in_EAX)) = pfVar13[2] + pfVar20[2];
                *(float *)((int)pfVar22 + ((int)in_ECX - in_EAX)) = pfVar20[3] - pfVar13[3];
                *pfStack_34 = pfVar13[3] + pfVar20[3];
                *pfStack_38 = *pfVar22 - *pfVar11;
                pfVar20 = pfVar11;
                pfVar13 = pfVar22;
              } while (iVar23 != 0);
            }
            pfStack_3c = pfStack_3c + unaff_EBX;
            pfStack_40 = pfStack_40 + unaff_EBX;
            pfStack_44 = pfStack_44 + unaff_EBX;
            pfVar25 = pfVar25 + unaff_EBX;
            iStack_54 = iStack_54 + -1;
          } while (iStack_54 != 0);
        }
        iStack_5c = iStack_5c + -1;
      } while (iStack_5c != 0);
    }
  }
  iVar23 = 0;
  if (3 < param_3) {
    pfStack_24 = (float *)((param_3 - 4U >> 2) + 1);
    iVar23 = (int)pfStack_24 * 4;
    pfVar18 = param_5 + 1;
    pfVar25 = param_6 + 3;
    do {
      pfVar18[-1] = pfVar25[-3];
      pfStack_24 = (float *)((int)pfStack_24 + -1);
      *pfVar18 = *(float *)((int)param_6 + (-0x10 - (int)param_5) + (int)(pfVar18 + 4));
      pfVar18[1] = pfVar25[-1];
      pfVar18[2] = *pfVar25;
      pfVar18 = pfVar18 + 4;
      pfVar25 = pfVar25 + 4;
    } while (pfStack_24 != (float *)0x0);
  }
  if (iVar23 < param_3) {
    iVar21 = param_3 - iVar23;
    pfVar18 = param_5 + iVar23;
    do {
      iVar21 = iVar21 + -1;
      *pfVar18 = *(float *)(((int)param_6 - (int)param_5) + (int)pfVar18);
      pfVar18 = pfVar18 + 1;
    } while (iVar21 != 0);
  }
  iVar23 = param_1 * param_3;
  if (1 < iStack_8) {
    iVar24 = iVar23 - unaff_EBX;
    iVar21 = -unaff_EBX;
    pfStack_28 = (float *)(iStack_8 + -1);
    do {
      iVar21 = iVar21 + iVar8;
      iVar24 = iVar24 - iVar8;
      pfStack_60 = (float *)0x0;
      iVar14 = iVar21;
      iVar26 = iVar24;
      if (3 < param_2) {
        iVar15 = (param_2 - 4U >> 2) + 1;
        pfStack_60 = (float *)(iVar15 * 4);
        do {
          iVar14 = iVar14 + unaff_EBX;
          iVar26 = iVar26 + unaff_EBX;
          in_ECX[iVar14] = *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar26 * 4);
          iVar16 = iVar14 + unaff_EBX;
          in_ECX[iVar26] = *(float *)(in_EAX + iVar26 * 4) - *(float *)(in_EAX + iVar14 * 4);
          iVar26 = iVar26 + unaff_EBX;
          in_ECX[iVar16] = *(float *)(in_EAX + iVar16 * 4) + *(float *)(in_EAX + iVar26 * 4);
          iVar17 = iVar16 + unaff_EBX;
          in_ECX[iVar26] = *(float *)(in_EAX + iVar26 * 4) - *(float *)(in_EAX + iVar16 * 4);
          iVar26 = iVar26 + unaff_EBX;
          in_ECX[iVar17] = *(float *)(in_EAX + iVar17 * 4) + *(float *)(in_EAX + iVar26 * 4);
          iVar14 = iVar17 + unaff_EBX;
          in_ECX[iVar26] = *(float *)(in_EAX + iVar26 * 4) - *(float *)(in_EAX + iVar17 * 4);
          iVar26 = iVar26 + unaff_EBX;
          iVar15 = iVar15 + -1;
          in_ECX[iVar14] = *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar26 * 4);
          in_ECX[iVar26] = *(float *)(in_EAX + iVar26 * 4) - *(float *)(in_EAX + iVar14 * 4);
        } while (iVar15 != 0);
      }
      if ((int)pfStack_60 < param_2) {
        pfStack_24 = (float *)(param_2 - (int)pfStack_60);
        pfVar18 = (float *)(in_EAX + iVar14 * 4);
        pfVar25 = (float *)(in_EAX + iVar26 * 4);
        do {
          pfVar20 = pfVar25 + unaff_EBX;
          pfVar25 = pfVar25 + unaff_EBX;
          pfVar13 = pfVar18 + unaff_EBX;
          pfVar18 = pfVar18 + unaff_EBX;
          pfStack_24 = (float *)((int)pfStack_24 + -1);
          *(float *)(((int)in_ECX - in_EAX) + (int)pfVar18) = *pfVar20 + *pfVar13;
          *(float *)(((int)in_ECX - in_EAX) + (int)pfVar25) = *pfVar25 - *pfVar18;
        } while (pfStack_24 != (float *)0x0);
      }
      pfStack_28 = (float *)((int)pfStack_28 + -1);
    } while (pfStack_28 != (float *)0x0);
  }
  fStack_1c = 1.0;
  iVar21 = (param_1 + -1) * param_3;
  iStack_5c = 0;
  if (1 < iStack_8) {
    pfStack_2c = param_6 + 2;
    fVar1 = 0.0;
    pfStack_30 = param_6 + iVar23 + 2;
    iStack_4 = iStack_8 + -1;
    do {
      pfStack_2c = pfStack_2c + param_3;
      pfStack_30 = pfStack_30 + -param_3;
      iVar23 = iVar23 - param_3;
      iStack_5c = iStack_5c + param_3;
      fVar5 = fStack_1c * (float)fVar29 - fVar1 * (float)fVar30;
      iVar24 = 0;
      pfStack_44 = (float *)param_3;
      fVar1 = fStack_1c * (float)fVar30 + (float)fVar29 * fVar1;
      iVar14 = iVar23;
      iVar26 = iStack_5c;
      pfStack_28 = (float *)iVar21;
      if (3 < param_3) {
        pfStack_40 = param_5 + param_3 + 2;
        iVar15 = (param_3 - 4U >> 2) + 1;
        iVar24 = iVar15 * 4;
        iVar26 = iStack_5c + iVar24;
        iVar14 = iVar23 + iVar24;
        pfStack_28 = (float *)(iVar21 + iVar24);
        pfStack_44 = (float *)(iVar24 + param_3);
        pfVar18 = pfStack_2c;
        pfStack_60 = param_5 + iVar21 + 2;
        pfStack_3c = param_5 + 2;
        pfStack_34 = pfStack_30;
        do {
          pfVar18[-2] = pfStack_40[-2] * fVar5 + pfStack_3c[-2];
          pfStack_34[-2] = pfStack_60[-2] * fVar1;
          pfVar18[-1] = pfStack_40[-1] * fVar5 + pfStack_3c[-1];
          pfStack_34[-1] = pfStack_60[-1] * fVar1;
          *pfVar18 = *pfStack_40 * fVar5 + *pfStack_3c;
          *pfStack_34 = *pfStack_60 * fVar1;
          pfVar25 = pfStack_40 + 1;
          pfStack_40 = pfStack_40 + 4;
          pfVar18[1] = *pfVar25 * fVar5 + pfStack_3c[1];
          iVar15 = iVar15 + -1;
          pfStack_34[1] = pfStack_60[1] * fVar1;
          pfVar18 = pfVar18 + 4;
          pfStack_60 = pfStack_60 + 4;
          pfStack_3c = pfStack_3c + 4;
          pfStack_34 = pfStack_34 + 4;
        } while (iVar15 != 0);
      }
      if (iVar24 < param_3) {
        pfStack_44 = param_5 + (int)pfStack_44;
        pfVar18 = param_6 + iVar26;
        pfStack_34 = param_6 + iVar14;
        pfStack_28 = param_5 + (int)pfStack_28;
        do {
          fVar2 = *pfStack_44;
          iVar14 = iVar24 + 1;
          pfStack_44 = pfStack_44 + 1;
          *pfVar18 = fVar2 * fVar5 + param_5[iVar24];
          *pfStack_34 = fVar1 * *pfStack_28;
          pfVar18 = pfVar18 + 1;
          iVar24 = iVar14;
          pfStack_34 = pfStack_34 + 1;
          pfStack_28 = pfStack_28 + 1;
        } while (iVar14 < param_3);
      }
      if (2 < iStack_8) {
        pfStack_60 = param_5 + param_3 + 2;
        pfStack_34 = param_5 + iVar21 + 2;
        iStack_c = iStack_8 + -2;
        iVar24 = iVar21;
        iVar14 = param_3;
        fVar2 = fVar1;
        fStack_18 = fVar5;
        do {
          iVar24 = iVar24 - param_3;
          pfStack_60 = pfStack_60 + param_3;
          pfStack_34 = pfStack_34 + -param_3;
          iVar14 = iVar14 + param_3;
          fVar6 = fStack_18 * fVar5 - fVar2 * fVar1;
          iVar26 = 0;
          fVar2 = fStack_18 * fVar1 + fVar5 * fVar2;
          iVar15 = iStack_5c;
          iVar16 = iVar23;
          iStack_14 = iVar24;
          iStack_10 = iVar14;
          if (3 < param_3) {
            iVar17 = (param_3 - 4U >> 2) + 1;
            iVar26 = iVar17 * 4;
            iVar15 = iStack_5c + iVar26;
            iVar16 = iVar23 + iVar26;
            iStack_10 = iVar14 + iVar26;
            iStack_14 = iVar24 + iVar26;
            pfVar18 = pfStack_2c;
            pfVar25 = pfStack_30;
            pfStack_40 = pfStack_34;
            pfStack_3c = pfStack_60;
            do {
              pfVar18[-2] = pfStack_3c[-2] * fVar6 + pfVar18[-2];
              pfVar25[-2] = pfStack_40[-2] * fVar2 + pfVar25[-2];
              pfVar18[-1] = pfStack_3c[-1] * fVar6 + pfVar18[-1];
              pfVar25[-1] = pfStack_40[-1] * fVar2 + pfVar25[-1];
              *pfVar18 = *pfStack_3c * fVar6 + *pfVar18;
              *pfVar25 = *pfStack_40 * fVar2 + *pfVar25;
              iVar17 = iVar17 + -1;
              pfVar18[1] = pfStack_3c[1] * fVar6 + pfVar18[1];
              pfVar25[1] = pfStack_40[1] * fVar2 + pfVar25[1];
              pfVar18 = pfVar18 + 4;
              pfVar25 = pfVar25 + 4;
              pfStack_40 = pfStack_40 + 4;
              pfStack_3c = pfStack_3c + 4;
            } while (iVar17 != 0);
          }
          if (iVar26 < param_3) {
            pfStack_28 = param_5 + iStack_10;
            iVar26 = param_3 - iVar26;
            pfVar18 = param_6 + iVar15;
            pfVar25 = param_6 + iVar16;
            pfStack_3c = param_5 + iStack_14;
            do {
              fVar3 = *pfStack_28;
              pfStack_28 = pfStack_28 + 1;
              iVar26 = iVar26 + -1;
              *pfVar18 = fVar6 * fVar3 + *pfVar18;
              *pfVar25 = fVar2 * *pfStack_3c + *pfVar25;
              pfVar18 = pfVar18 + 1;
              pfVar25 = pfVar25 + 1;
              pfStack_3c = pfStack_3c + 1;
            } while (iVar26 != 0);
          }
          iStack_c = iStack_c + -1;
          fStack_18 = fVar6;
        } while (iStack_c != 0);
      }
      iStack_4 = iStack_4 + -1;
      fStack_1c = fVar5;
    } while (iStack_4 != 0);
  }
  iVar23 = 0;
  if (1 < iStack_8) {
    param_3 = (int)(param_5 + 2);
    iStack_4 = iStack_8 + -1;
    do {
      param_3 = param_3 + iVar27 * 4;
      iVar23 = iVar23 + iVar27;
      iVar21 = 0;
      iVar24 = iVar23;
      if (3 < iVar27) {
        iVar14 = (iVar27 - 4U >> 2) + 1;
        iVar21 = iVar14 * 4;
        iVar24 = iVar23 + iVar21;
        pfVar18 = param_6 + 2;
        pfVar25 = (float *)param_3;
        do {
          iVar14 = iVar14 + -1;
          pfVar18[-2] = pfVar25[-2] + pfVar18[-2];
          pfVar18[-1] = pfVar25[-1] + pfVar18[-1];
          *pfVar18 = *pfVar18 + *pfVar25;
          pfVar18[1] = pfVar25[1] + pfVar18[1];
          pfVar18 = pfVar18 + 4;
          pfVar25 = pfVar25 + 4;
        } while (iVar14 != 0);
      }
      if (iVar21 < iVar27) {
        pfVar18 = param_5 + iVar24;
        do {
          iVar24 = iVar21 + 1;
          fVar1 = *pfVar18;
          pfVar18 = pfVar18 + 1;
          param_6[iVar21] = param_6[iVar21] + fVar1;
          iVar21 = iVar24;
        } while (iVar24 < iVar27);
      }
      iStack_4 = iStack_4 + -1;
    } while (iStack_4 != 0);
  }
  if (unaff_EBX < param_2) {
    pfStack_28 = (float *)0x0;
    if (0 < unaff_EBX) {
      do {
        pfStack_60 = (float *)0x0;
        pfVar18 = pfStack_28;
        pfVar25 = pfStack_28;
        if (3 < param_2) {
          iVar27 = (param_2 - 4U >> 2) + 1;
          pfStack_60 = (float *)(iVar27 * 4);
          do {
            *(undefined4 *)(param_4 + (int)pfVar25 * 4) = *(undefined4 *)(in_EAX + (int)pfVar18 * 4)
            ;
            iVar23 = (int)pfVar18 + unaff_EBX + unaff_EBX;
            *(undefined4 *)(param_4 + ((int)pfVar25 + iVar9) * 4) =
                 *(undefined4 *)(in_EAX + ((int)pfVar18 + unaff_EBX) * 4);
            iVar24 = (int)pfVar25 + iVar9 + iVar9;
            iVar21 = iVar23 + unaff_EBX;
            *(undefined4 *)(param_4 + iVar24 * 4) = *(undefined4 *)(in_EAX + iVar23 * 4);
            iVar24 = iVar24 + iVar9;
            pfVar18 = (float *)(iVar21 + unaff_EBX);
            *(undefined4 *)(param_4 + iVar24 * 4) = *(undefined4 *)(in_EAX + iVar21 * 4);
            pfVar25 = (float *)(iVar24 + iVar9);
            iVar27 = iVar27 + -1;
          } while (iVar27 != 0);
        }
        if ((int)pfStack_60 < param_2) {
          param_3 = param_4 + (int)pfVar25 * 4;
          puVar10 = (undefined4 *)(in_EAX + (int)pfVar18 * 4);
          iVar27 = param_2 - (int)pfStack_60;
          do {
            *(undefined4 *)param_3 = *puVar10;
            puVar10 = puVar10 + unaff_EBX;
            param_3 = param_3 + iVar9 * 4;
            iVar27 = iVar27 + -1;
          } while (iVar27 != 0);
        }
        pfStack_28 = (float *)((int)pfStack_28 + 1);
      } while ((int)pfStack_28 < unaff_EBX);
    }
  }
  else {
    iStack_5c = 0;
    iStack_54 = 0;
    if (0 < param_2) {
      pfStack_24 = (float *)(in_EAX + 8);
      pfStack_2c = (float *)(param_4 + 8);
      iStack_4 = param_2;
      do {
        iVar27 = 0;
        iVar23 = iStack_5c;
        iVar21 = iStack_54;
        if (3 < unaff_EBX) {
          iVar24 = (unaff_EBX - 4U >> 2) + 1;
          iVar27 = iVar24 * 4;
          iVar23 = iStack_5c + iVar27;
          iVar21 = iVar27 + iStack_54;
          pfVar18 = pfStack_24;
          pfVar25 = pfStack_2c;
          do {
            pfVar25[-2] = pfVar18[-2];
            iVar24 = iVar24 + -1;
            pfVar25[-1] = pfVar18[-1];
            *pfVar25 = *pfVar18;
            pfVar25[1] = pfVar18[1];
            pfVar18 = pfVar18 + 4;
            pfVar25 = pfVar25 + 4;
          } while (iVar24 != 0);
        }
        if (iVar27 < unaff_EBX) {
          puVar10 = (undefined4 *)(param_4 + iVar21 * 4);
          puVar19 = (undefined4 *)(in_EAX + iVar23 * 4);
          iVar27 = unaff_EBX - iVar27;
          do {
            uVar4 = *puVar19;
            puVar19 = puVar19 + 1;
            *puVar10 = uVar4;
            puVar10 = puVar10 + 1;
            iVar27 = iVar27 + -1;
          } while (iVar27 != 0);
        }
        iStack_5c = iStack_5c + unaff_EBX;
        pfStack_24 = pfStack_24 + unaff_EBX;
        iStack_54 = iStack_54 + iVar9;
        pfStack_2c = pfStack_2c + iVar9;
        iStack_4 = iStack_4 + -1;
      } while (iStack_4 != 0);
    }
  }
  iVar27 = iVar8 * param_1;
  iVar23 = 0;
  iVar21 = 0;
  if (1 < iStack_8) {
    iStack_4 = iStack_8 + -1;
    iVar24 = iVar27;
    do {
      iVar21 = iVar21 + iVar8;
      iVar24 = iVar24 - iVar8;
      iVar23 = iVar23 + unaff_EBX * 2;
      pfStack_60 = (float *)0x0;
      iVar14 = iVar23;
      iVar26 = iVar21;
      iVar15 = iVar24;
      if (3 < param_2) {
        param_1 = (param_2 - 4U >> 2) + 1;
        pfStack_60 = (float *)(param_1 * 4);
        do {
          *(undefined4 *)(param_4 + -4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar26 * 4);
          *(undefined4 *)(param_4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar15 * 4);
          iVar14 = iVar14 + iVar9;
          iVar16 = iVar26 + unaff_EBX + unaff_EBX;
          *(undefined4 *)(param_4 + -4 + iVar14 * 4) =
               *(undefined4 *)(in_EAX + (iVar26 + unaff_EBX) * 4);
          iVar26 = iVar15 + unaff_EBX + unaff_EBX;
          *(undefined4 *)(param_4 + iVar14 * 4) = *(undefined4 *)(in_EAX + (iVar15 + unaff_EBX) * 4)
          ;
          iVar14 = iVar14 + iVar9;
          iVar15 = iVar16 + unaff_EBX;
          *(undefined4 *)(param_4 + -4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar16 * 4);
          iVar16 = iVar26 + unaff_EBX;
          *(undefined4 *)(param_4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar26 * 4);
          iVar14 = iVar14 + iVar9;
          iVar26 = iVar15 + unaff_EBX;
          *(undefined4 *)(param_4 + -4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar15 * 4);
          iVar15 = iVar16 + unaff_EBX;
          *(undefined4 *)(param_4 + iVar14 * 4) = *(undefined4 *)(in_EAX + iVar16 * 4);
          iVar14 = iVar14 + iVar9;
          param_1 = param_1 + -1;
        } while (param_1 != 0);
      }
      if ((int)pfStack_60 < param_2) {
        param_1 = in_EAX + iVar15 * 4;
        puVar10 = (undefined4 *)(in_EAX + iVar26 * 4);
        iVar26 = param_2 - (int)pfStack_60;
        puVar19 = (undefined4 *)(param_4 + iVar14 * 4);
        do {
          puVar19[-1] = *puVar10;
          *puVar19 = *(undefined4 *)param_1;
          puVar19 = puVar19 + iVar9;
          param_1 = param_1 + unaff_EBX * 4;
          puVar10 = puVar10 + unaff_EBX;
          iVar26 = iVar26 + -1;
        } while (iVar26 != 0);
      }
      iStack_4 = iStack_4 + -1;
    } while (iStack_4 != 0);
  }
  if (unaff_EBX != 1) {
    if (iVar7 < param_2) {
      iVar23 = 0;
      iVar7 = 0;
      if (1 < iStack_8) {
        iStack_14 = iStack_8 + -1;
        iVar21 = -2;
        do {
          iVar21 = iVar21 + unaff_EBX * 2;
          iVar23 = iVar23 + unaff_EBX * 2;
          iVar7 = iVar7 + iVar8;
          iVar27 = iVar27 - iVar8;
          if (2 < unaff_EBX) {
            iStack_10 = (unaff_EBX - 3U >> 1) + 1;
            param_1 = iVar21;
            iVar24 = iVar7;
            do {
              iVar24 = iVar24 + 2;
              pfStack_44 = (float *)((iVar23 - iVar7) + iVar24);
              iVar15 = (iVar27 - iVar7) + iVar24;
              pfStack_60 = (float *)0x0;
              iVar14 = iVar24;
              iVar26 = param_1;
              if (3 < param_2) {
                iStack_4 = (param_2 - 4U >> 2) + 1;
                pfStack_60 = (float *)(iStack_4 * 4);
                do {
                  *(float *)(param_4 + -4 + (int)pfStack_44 * 4) =
                       *(float *)(in_EAX + -4 + iVar15 * 4) + *(float *)(in_EAX + -4 + iVar14 * 4);
                  *(float *)(param_4 + -4 + iVar26 * 4) =
                       *(float *)(in_EAX + -4 + iVar14 * 4) - *(float *)(in_EAX + -4 + iVar15 * 4);
                  *(float *)(param_4 + (int)pfStack_44 * 4) =
                       *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar15 * 4);
                  iVar17 = iVar15 + unaff_EBX;
                  iVar16 = iVar14 + unaff_EBX;
                  *(float *)(param_4 + iVar26 * 4) =
                       *(float *)(in_EAX + iVar15 * 4) - *(float *)(in_EAX + iVar14 * 4);
                  iVar26 = iVar26 + iVar9;
                  iVar28 = (int)pfStack_44 + iVar9;
                  *(float *)(param_4 + -4 + iVar28 * 4) =
                       *(float *)(in_EAX + -4 + iVar17 * 4) + *(float *)(in_EAX + -4 + iVar16 * 4);
                  *(float *)(param_4 + -4 + iVar26 * 4) =
                       *(float *)(in_EAX + -4 + iVar16 * 4) - *(float *)(in_EAX + -4 + iVar17 * 4);
                  *(float *)(param_4 + iVar28 * 4) =
                       *(float *)(in_EAX + iVar16 * 4) + *(float *)(in_EAX + iVar17 * 4);
                  iVar15 = iVar17 + unaff_EBX;
                  iVar14 = iVar16 + unaff_EBX;
                  *(float *)(param_4 + iVar26 * 4) =
                       *(float *)(in_EAX + iVar17 * 4) - *(float *)(in_EAX + iVar16 * 4);
                  iVar26 = iVar26 + iVar9;
                  iVar28 = iVar28 + iVar9;
                  *(float *)(param_4 + -4 + iVar28 * 4) =
                       *(float *)(in_EAX + -4 + iVar15 * 4) + *(float *)(in_EAX + -4 + iVar14 * 4);
                  *(float *)(param_4 + -4 + iVar26 * 4) =
                       *(float *)(in_EAX + -4 + iVar14 * 4) - *(float *)(in_EAX + -4 + iVar15 * 4);
                  *(float *)(param_4 + iVar28 * 4) =
                       *(float *)(in_EAX + iVar14 * 4) + *(float *)(in_EAX + iVar15 * 4);
                  iVar17 = iVar15 + unaff_EBX;
                  iVar16 = iVar14 + unaff_EBX;
                  *(float *)(param_4 + iVar26 * 4) =
                       *(float *)(in_EAX + iVar15 * 4) - *(float *)(in_EAX + iVar14 * 4);
                  iVar26 = iVar26 + iVar9;
                  iVar28 = iVar28 + iVar9;
                  *(float *)(param_4 + -4 + iVar28 * 4) =
                       *(float *)(in_EAX + -4 + iVar17 * 4) + *(float *)(in_EAX + -4 + iVar16 * 4);
                  *(float *)(param_4 + -4 + iVar26 * 4) =
                       *(float *)(in_EAX + -4 + iVar16 * 4) - *(float *)(in_EAX + -4 + iVar17 * 4);
                  *(float *)(param_4 + iVar28 * 4) =
                       *(float *)(in_EAX + iVar16 * 4) + *(float *)(in_EAX + iVar17 * 4);
                  iVar15 = iVar17 + unaff_EBX;
                  iVar14 = iVar16 + unaff_EBX;
                  *(float *)(param_4 + iVar26 * 4) =
                       *(float *)(in_EAX + iVar17 * 4) - *(float *)(in_EAX + iVar16 * 4);
                  iVar26 = iVar26 + iVar9;
                  pfStack_44 = (float *)(iVar28 + iVar9);
                  iStack_4 = iStack_4 + -1;
                } while (iStack_4 != 0);
              }
              if ((int)pfStack_60 < param_2) {
                pfVar18 = (float *)(param_4 + (int)pfStack_44 * 4);
                pfVar25 = (float *)(param_4 + iVar26 * 4);
                iVar26 = param_2 - (int)pfStack_60;
                pfVar20 = (float *)(in_EAX + iVar14 * 4);
                pfVar13 = (float *)(in_EAX + iVar15 * 4);
                do {
                  pfVar18[-1] = pfVar13[-1] + pfVar20[-1];
                  pfVar25[-1] = pfVar20[-1] - pfVar13[-1];
                  *pfVar18 = *pfVar20 + *pfVar13;
                  pfVar18 = pfVar18 + iVar9;
                  *pfVar25 = *pfVar13 - *pfVar20;
                  pfVar25 = pfVar25 + iVar9;
                  pfVar20 = pfVar20 + unaff_EBX;
                  pfVar13 = pfVar13 + unaff_EBX;
                  iVar26 = iVar26 + -1;
                } while (iVar26 != 0);
              }
              param_1 = param_1 + -2;
              iStack_10 = iStack_10 + -1;
            } while (iStack_10 != 0);
          }
          iStack_14 = iStack_14 + -1;
        } while (iStack_14 != 0);
        return;
      }
    }
    else if (1 < iStack_8) {
      pfStack_24 = (float *)(in_EAX + 8 + iVar27 * 4);
      local_20 = (float *)(param_4 + 8);
      param_3 = param_4 + -8;
      param_1 = in_EAX + 8;
      iStack_8 = iStack_8 + -1;
      do {
        param_3 = param_3 + unaff_EBX * 8;
        local_20 = local_20 + unaff_EBX * 2;
        param_1 = param_1 + iVar8 * 4;
        pfStack_24 = pfStack_24 + -iVar8;
        if (0 < param_2) {
          iStack_4 = param_2;
          pfVar18 = local_20;
          pfStack_30 = pfStack_24;
          pfStack_2c = (float *)param_1;
          pfStack_28 = (float *)param_3;
          do {
            if (2 < unaff_EBX) {
              iVar27 = (unaff_EBX - 3U >> 1) + 1;
              pfVar25 = pfStack_30;
              pfVar20 = pfStack_2c;
              pfVar13 = pfStack_28;
              pfVar11 = pfVar18;
              do {
                iVar27 = iVar27 + -1;
                pfVar11[-1] = pfVar25[-1] + pfVar20[-1];
                pfVar13[-1] = pfVar20[-1] - pfVar25[-1];
                *pfVar11 = *pfVar25 + *pfVar20;
                *pfVar13 = *pfVar25 - *pfVar20;
                pfVar25 = pfVar25 + 2;
                pfVar20 = pfVar20 + 2;
                pfVar13 = pfVar13 + -2;
                pfVar11 = pfVar11 + 2;
              } while (iVar27 != 0);
            }
            pfStack_28 = pfStack_28 + iVar9;
            pfVar18 = pfVar18 + iVar9;
            pfStack_2c = pfStack_2c + unaff_EBX;
            pfStack_30 = pfStack_30 + unaff_EBX;
            iStack_4 = iStack_4 + -1;
          } while (iStack_4 != 0);
        }
        iStack_8 = iStack_8 + -1;
      } while (iStack_8 != 0);
    }
  }
  return;
}
