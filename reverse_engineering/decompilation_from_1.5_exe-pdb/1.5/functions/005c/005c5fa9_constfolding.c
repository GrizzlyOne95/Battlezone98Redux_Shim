/*
 * Entry: 005c5fa9
 * Name: constfolding
 * Namespace: Global
 * Signature: int constfolding(OpCode param_1, expdesc * param_2, expdesc * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl constfolding(OpCode param_1,expdesc *param_2,expdesc *param_3)

{
  double dVar1;
  int iVar2;
  int extraout_ECX;
  int unaff_ESI;
  float10 fVar3;
  float10 fVar4;
  expdesc *in_stack_ffffffec;
  double dVar5;
  
  iVar2 = isnumeral(in_stack_ffffffec);
  if (iVar2 == 0) {
    return 0;
  }
  iVar2 = isnumeral(in_stack_ffffffec);
  if (iVar2 != 0) {
    dVar5 = *(double *)(unaff_ESI + 8);
    fVar3 = (float10)dVar5;
    dVar1 = *(double *)(extraout_ECX + 8);
    fVar4 = (float10)dVar1;
    switch(param_1) {
    case OP_ADD:
      fVar3 = fVar4 + fVar3;
      break;
    case OP_SUB:
      fVar3 = fVar3 - fVar4;
      break;
    case OP_MUL:
      fVar3 = fVar4 * fVar3;
      break;
    case OP_DIV:
      if ((float10)0 == fVar4) {
        return 0;
      }
      fVar3 = fVar3 / fVar4;
      break;
    case OP_MOD:
      if ((float10)0 == fVar4) {
        return 0;
      }
      fVar3 = (float10)floor((double)(fVar3 / fVar4));
      fVar3 = (float10)dVar5 - fVar3 * (float10)dVar1;
      break;
    case OP_POW:
      fVar3 = (float10)__CIpow();
      break;
    case OP_UNM:
      fVar3 = -fVar3;
      break;
    default:
      fVar3 = (float10)0;
      break;
    case OP_LEN:
      return 0;
    }
    *(double *)(unaff_ESI + 8) = (double)fVar3;
    return 1;
  }
  return 0;
}
