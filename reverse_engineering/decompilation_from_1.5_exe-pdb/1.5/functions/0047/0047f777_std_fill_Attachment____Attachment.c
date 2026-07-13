/*
 * Entry: 0047f777
 * Name: std::fill<Attachment_*_*,Attachment_*>
 * Namespace: std
 * Signature: void fill<Attachment_*_*,Attachment_*>(Attachment * * param_1, Attachment * * param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
std::fill<Attachment_*_*,Attachment_*>
          (Attachment **param_1,Attachment **param_2,Attachment **param_3)

{
  for (; param_1 != param_2; param_1 = param_1 + 1) {
    *param_1 = *param_3;
  }
  return;
}
