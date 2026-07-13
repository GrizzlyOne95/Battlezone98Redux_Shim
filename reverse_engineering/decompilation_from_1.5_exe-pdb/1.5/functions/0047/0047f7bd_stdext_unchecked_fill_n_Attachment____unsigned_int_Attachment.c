/*
 * Entry: 0047f7bd
 * Name: stdext::unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>
 * Namespace: stdext
 * Signature: void unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>(Attachment * * param_1, uint param_2, Attachment * * param_3)
 * Symbol source: IMPORTED
 * Export status: ok
 */

void __cdecl
stdext::unchecked_fill_n<Attachment_*_*,unsigned_int,Attachment_*>
          (Attachment **param_1,uint param_2,Attachment **param_3)

{
  std::_Fill_n<Attachment_*_*,unsigned_int,Attachment_*>
            (param_1,param_2,param_3,(random_access_iterator_tag)0x0,
             (_Range_checked_iterator_tag)0x0);
  return;
}
