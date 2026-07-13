/*
 * Entry: 005c46ac
 * Name: getbinopr
 * Namespace: Global
 * Signature: BinOpr getbinopr(int param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

BinOpr __cdecl getbinopr(int param_1)

{
  int in_EAX;
  
  if (in_EAX < 0x5f) {
    if (in_EAX == 0x5e) {
      return OPR_POW;
    }
    if (in_EAX == 0x25) {
      return OPR_MOD;
    }
    if (in_EAX == 0x2a) {
      return OPR_MUL;
    }
    if (in_EAX == 0x2b) {
      return OPR_ADD;
    }
    if (in_EAX == 0x2d) {
      return OPR_SUB;
    }
    if (in_EAX == 0x2f) {
      return OPR_DIV;
    }
    if (in_EAX == 0x3c) {
      return OPR_LT;
    }
    if (in_EAX == 0x3e) {
      return OPR_GT;
    }
  }
  else {
    if (in_EAX == 0x101) {
      return OPR_AND;
    }
    if (in_EAX == 0x10f) {
      return OPR_OR;
    }
    if (in_EAX == 0x116) {
      return OPR_CONCAT;
    }
    if (in_EAX == 0x118) {
      return OPR_EQ;
    }
    if (in_EAX == 0x119) {
      return OPR_GE;
    }
    if (in_EAX == 0x11a) {
      return OPR_LE;
    }
    if (in_EAX == 0x11b) {
      return OPR_NE;
    }
  }
  return OPR_NOBINOPR;
}
