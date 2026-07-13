/*
 * Entry: 00454630
 * Name: LinkContainer
 * Namespace: Global
 * Signature: void LinkContainer(Strip * param_1)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl LinkContainer(Strip *param_1)

{
  Strip *unaff_ESI;
  
  unaff_ESI->neighbor = -1;
  LinkLeft(unaff_ESI);
  LinkTop(unaff_ESI);
  LinkRight(unaff_ESI);
  LinkBottom(unaff_ESI);
  return;
}
