/*
 * Entry: 005720b8
 * Name: Get3DCard
 * Namespace: Global
 * Signature: int Get3DCard(int param_1, char * * param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

int __cdecl Get3DCard(int param_1,char **param_2)

{
  if ((boardSelected < 0) || (param_1 <= boardSelected)) {
    if (param_1 < 2) {
      return 0;
    }
    numCards = param_1;
    cardNames = param_2;
    do_card();
  }
  return boardSelected;
}
