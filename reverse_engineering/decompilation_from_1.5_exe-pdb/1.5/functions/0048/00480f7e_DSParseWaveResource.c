/*
 * Entry: 00480f7e
 * Name: DSParseWaveResource
 * Namespace: Global
 * Signature: int DSParseWaveResource(void * param_1, tWAVEFORMATEX * * param_2, uchar * * param_3, ulong * param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl
DSParseWaveResource(void *param_1,tWAVEFORMATEX **param_2,uchar **param_3,ulong *param_4)

{
  int *piVar1;
  tWAVEFORMATEX *ptVar2;
  tWAVEFORMATEX *ptVar3;
  int *in_EAX;
  int *piVar4;
  int *piVar5;
  int *unaff_EBX;
  
  if (unaff_EBX != (int *)0x0) {
    *unaff_EBX = 0;
  }
  if (param_1 != (void *)0x0) {
    *(undefined4 *)param_1 = 0;
  }
  if (param_2 != (tWAVEFORMATEX **)0x0) {
    *param_2 = (tWAVEFORMATEX *)0x0;
  }
  piVar5 = in_EAX + 3;
  if ((*in_EAX == 0x46464952) && (in_EAX[2] == 0x45564157)) {
    piVar1 = (int *)(in_EAX[1] + -4 + (int)piVar5);
    while (piVar5 < piVar1) {
      ptVar2 = (tWAVEFORMATEX *)piVar5[1];
      piVar4 = piVar5 + 2;
      if (*piVar5 == 0x20746d66) {
        if ((unaff_EBX != (int *)0x0) && (*unaff_EBX == 0)) {
          if (ptVar2 < (tWAVEFORMATEX *)0xe) {
            return 0;
          }
          *unaff_EBX = (int)piVar4;
          if ((param_1 == (void *)0x0) || (*(int *)param_1 != 0)) {
            if (param_2 == (tWAVEFORMATEX **)0x0) {
              return 1;
            }
            ptVar3 = *param_2;
            goto LAB_0048103c;
          }
        }
      }
      else if ((*piVar5 == 0x61746164) &&
              (((param_1 != (void *)0x0 && (*(int *)param_1 == 0)) ||
               ((param_2 != (tWAVEFORMATEX **)0x0 && (*param_2 == (tWAVEFORMATEX *)0x0)))))) {
        if (param_1 != (void *)0x0) {
          *(int **)param_1 = piVar4;
        }
        if (param_2 != (tWAVEFORMATEX **)0x0) {
          *param_2 = ptVar2;
        }
        if (unaff_EBX == (int *)0x0) {
          return 1;
        }
        ptVar3 = (tWAVEFORMATEX *)*unaff_EBX;
LAB_0048103c:
        if (ptVar3 != (tWAVEFORMATEX *)0x0) {
          return 1;
        }
      }
      piVar5 = (int *)((int)piVar4 + ((uint)((int)&ptVar2->wFormatTag + 1U) & 0xfffffffe));
    }
  }
  return 0;
}
