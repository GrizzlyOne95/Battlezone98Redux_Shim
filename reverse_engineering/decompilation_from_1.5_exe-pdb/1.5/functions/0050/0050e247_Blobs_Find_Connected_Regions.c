/*
 * Entry: 0050e247
 * Name: Blobs_Find_Connected_Regions
 * Namespace: Global
 * Signature: void Blobs_Find_Connected_Regions(ushort * * param_1, int param_2, int param_3, int param_4)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl Blobs_Find_Connected_Regions(ushort **param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  ushort uVar2;
  int iVar3;
  ushort **local_c;
  int local_8;
  
  uVar2 = 1;
  num_blobs = 0;
  local_8 = 0;
  if (0 < param_3) {
    local_c = param_1;
    do {
      iVar3 = 0;
      if (0 < param_4) {
        do {
          if ((*local_c)[iVar3] == 0x7d1) {
            Blobs_Blank_Region(num_blobs);
            Blobs_Color(param_1,local_8,iVar3,uVar2,param_3,param_4);
            Blobs_Compute_Blob_Data(uVar2 - 1);
            if ((param_2 == 0) || (iVar1 = Blobs_Keep_Blob(uVar2 - 1), iVar1 != 0)) {
              num_blobs = num_blobs + 1;
              uVar2 = uVar2 + 1;
              if (2000 < uVar2) {
                uVar2 = 1;
              }
            }
            else {
              Blobs_Uncolor(param_1,local_8,iVar3,uVar2,param_3,param_4);
            }
          }
          iVar3 = iVar3 + 1;
        } while (iVar3 < param_4);
      }
      local_8 = local_8 + 1;
      local_c = local_c + 1;
    } while (local_8 < param_3);
  }
  return;
}
