/*
 * Entry: 004bd422
 * Name: StoreGameKey
 * Namespace: Global
 * Signature: void StoreGameKey(uint param_1, long param_2)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl StoreGameKey(uint param_1,long param_2)

{
  ushort uVar1;
  ushort uVar2;
  
  if (((param_2 & 0x40000000U) == 0) && (uVar2 = virtualKeyToGI[param_1], uVar2 != 0)) {
    uVar1 = GetKeyState(0x11);
    if ((uVar1 & 0x1000) != 0) {
      uVar2 = uVar2 | 0x100;
    }
    uVar1 = GetKeyState(0x12);
    if ((uVar1 & 0x1000) != 0) {
      uVar2 = uVar2 | 0x400;
    }
    uVar1 = GetKeyState(0x10);
    if ((uVar1 & 0x1000) != 0) {
      uVar2 = uVar2 | 0x200;
    }
    keyboardBuffer[bufferIn] = uVar2;
    bufferIn = bufferIn + 1;
    if (bufferIn == 0x40) {
      bufferIn = 0;
      return;
    }
    if ((bufferIn == bufferOut) && (bufferOut = bufferOut + 1, bufferOut == 0x40)) {
      bufferOut = 0;
    }
  }
  return;
}
