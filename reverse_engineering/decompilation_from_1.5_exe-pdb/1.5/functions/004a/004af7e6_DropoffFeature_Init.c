/*
 * Entry: 004af7e6
 * Name: DropoffFeature::Init
 * Namespace: DropoffFeature
 * Signature: void Init(DropoffFeature * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __thiscall DropoffFeature::Init(DropoffFeature *this)

{
  uint uVar1;
  
  uVar1 = 0;
  do {
    *(undefined4 *)((int)&dropoffList[0].dropObj + uVar1) = 0;
    *(undefined4 *)((int)&dropoffList[0].refCount + uVar1) = 0;
    uVar1 = uVar1 + 8;
  } while (uVar1 < 0xa0);
  return;
}
