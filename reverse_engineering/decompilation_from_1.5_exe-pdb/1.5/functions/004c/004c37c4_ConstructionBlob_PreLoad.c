/*
 * Entry: 004c37c4
 * Name: ConstructionBlob::PreLoad
 * Namespace: ConstructionBlob
 * Signature: void PreLoad(ConstructionBlob * this)
 * Symbol source: IMPORTED
 * Export status: ok
 */

/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */

void __thiscall ConstructionBlob::PreLoad(ConstructionBlob *this)

{
  int iVar1;
  ParameterDB local_1c;
  char local_18 [16];
  uint local_8;
  
  local_8 = __security_cookie ^ (uint)&stack0xfffffffc;
  ParameterDB::ParameterDB(&local_1c,"cnstblob.odf");
  ParameterDB::Get(&local_1c,0x8b188e5f,0x5df29add,local_18,0x10,"bpuff.0");
  iVar1 = GetSpriteIndex(local_18);
  this->blobTexture = iVar1;
  ParameterDB::Get(&local_1c,0x8b188e5f,0xdeb6a738,&this->blobFrames,0xe);
  ParameterDB::Get(&local_1c,0x8b188e5f,0x8df5df5d,&this->blobVariance,3);
  this->blobIndex = 0;
  this->blobPtr = this->blobList;
  ParameterDB::~ParameterDB(&local_1c);
  return;
}
