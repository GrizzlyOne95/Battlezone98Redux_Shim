; Entry: 005862e9
; Name: DXGetErrorStringA
; Signature: char * DXGetErrorStringA(T_HRESULT param_1)
; Stop: 0x00597a7d
; Reason: Exception while decompiling 005862e9: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x005862e9 --stop-address=0x00597a7d C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  5862e9:      	movl	%edi, %edi
  5862eb:      	pushl	%ebp
  5862ec:      	movl	%esp, %ebp
  5862ee:      	movl	0x8(%ebp), %eax
  5862f1:      	movl	$0x8009200d, %ecx       # imm = 0x8009200D
  5862f6:      	cmpl	%ecx, %eax
  5862f8:      	jg	0x589b2d <.text+0x188b2d>
  5862fe:      	je	0x589b23 <.text+0x188b23>
  586304:      	movl	$0x8007065a, %ecx       # imm = 0x8007065A
  586309:      	cmpl	%ecx, %eax
  58630b:      	jg	0x588bb2 <.text+0x187bb2>
  586311:      	je	0x58de88 <.text+0x18ce88>
  586317:      	movl	$0x80044023, %ecx       # imm = 0x80044023
  58631c:      	cmpl	%ecx, %eax
  58631e:      	jg	0x588457 <.text+0x187457>
  586324:      	je	0x58844d <.text+0x18744d>
  58632a:      	movl	$0x800401f3, %ecx       # imm = 0x800401F3
  58632f:      	cmpl	%ecx, %eax
  586331:      	jg	0x587584 <.text+0x186584>
  586337:      	je	0x58757a <.text+0x18657a>
  58633d:      	movl	$0x800288c6, %ecx       # imm = 0x800288C6
  586342:      	cmpl	%ecx, %eax
  586344:      	jg	0x586c81 <.text+0x185c81>
  58634a:      	je	0x586c77 <.text+0x185c77>
  586350:      	movl	$0x80010110, %ecx       # imm = 0x80010110
  586355:      	cmpl	%ecx, %eax
  586357:      	jg	0x58685f <.text+0x18585f>
  58635d:      	je	0x586855 <.text+0x185855>
  586363:      	movl	$0x80004029, %ecx       # imm = 0x80004029
  586368:      	cmpl	%ecx, %eax
  58636a:      	jg	0x5865b8 <.text+0x1855b8>
  586370:      	je	0x5865ae <.text+0x1855ae>
  586376:      	addl	$-0x15, %ecx
  586379:      	cmpl	%ecx, %eax
  58637b:      	jg	0x5864d1 <.text+0x1854d1>
  586381:      	je	0x5864c7 <.text+0x1854c7>
  586387:      	movl	$0x8000400a, %ecx       # imm = 0x8000400A
  58638c:      	cmpl	%ecx, %eax
  58638e:      	jg	0x586458 <.text+0x185458>
  586394:      	je	0x58644e <.text+0x18544e>
  58639a:      	addl	$-0x5, %ecx
  58639d:      	cmpl	%ecx, %eax
  58639f:      	jg	0x586406 <.text+0x185406>
  5863a1:      	je	0x5863fc <.text+0x1853fc>
  5863a3:      	cmpl	$0x8000000a, %eax       # imm = 0x8000000A
  5863a8:      	je	0x5863f2 <.text+0x1853f2>
  5863aa:      	cmpl	$0x80004001, %eax       # imm = 0x80004001
  5863af:      	je	0x5863e8 <.text+0x1853e8>
  5863b1:      	cmpl	$0x80004002, %eax       # imm = 0x80004002
  5863b6:      	je	0x5863de <.text+0x1853de>
  5863b8:      	cmpl	$0x80004003, %eax       # imm = 0x80004003
  5863bd:      	je	0x5863d4 <.text+0x1853d4>
  5863bf:      	cmpl	$0x80004004, %eax       # imm = 0x80004004
  5863c4:      	jne	0x591a16 <.text+0x190a16>
  5863ca:      	movl	$0x609ca4, %eax         # imm = 0x609CA4
  5863cf:      	jmp	0x591a45 <.text+0x190a45>
  5863d4:      	movl	$0x609c98, %eax         # imm = 0x609C98
  5863d9:      	jmp	0x591a45 <.text+0x190a45>
  5863de:      	movl	$0x609c88, %eax         # imm = 0x609C88
  5863e3:      	jmp	0x591a45 <.text+0x190a45>
  5863e8:      	movl	$0x609c7c, %eax         # imm = 0x609C7C
  5863ed:      	jmp	0x591a45 <.text+0x190a45>
  5863f2:      	movl	$0x609c70, %eax         # imm = 0x609C70
  5863f7:      	jmp	0x591a45 <.text+0x190a45>
  5863fc:      	movl	$0x609c68, %eax         # imm = 0x609C68
  586401:      	jmp	0x591a45 <.text+0x190a45>
  586406:      	cmpl	$0x80004006, %eax       # imm = 0x80004006
  58640b:      	je	0x586444 <.text+0x185444>
  58640d:      	cmpl	$0x80004007, %eax       # imm = 0x80004007
  586412:      	je	0x58643a <.text+0x18543a>
  586414:      	cmpl	$0x80004008, %eax       # imm = 0x80004008
  586419:      	je	0x586430 <.text+0x185430>
  58641b:      	cmpl	$0x80004009, %eax       # imm = 0x80004009
  586420:      	jne	0x591a16 <.text+0x190a16>
  586426:      	movl	$0x609c50, %eax         # imm = 0x609C50
  58642b:      	jmp	0x591a45 <.text+0x190a45>
  586430:      	movl	$0x609c34, %eax         # imm = 0x609C34
  586435:      	jmp	0x591a45 <.text+0x190a45>
  58643a:      	movl	$0x609c18, %eax         # imm = 0x609C18
  58643f:      	jmp	0x591a45 <.text+0x190a45>
  586444:      	movl	$0x609c08, %eax         # imm = 0x609C08
  586449:      	jmp	0x591a45 <.text+0x190a45>
  58644e:      	movl	$0x609bf0, %eax         # imm = 0x609BF0
  586453:      	jmp	0x591a45 <.text+0x190a45>
  586458:      	addl	$0x7fffbff5, %eax       # imm = 0x7FFFBFF5
  58645d:      	cmpl	$0x8, %eax
  586460:      	ja	0x591a16 <.text+0x190a16>
  586466:      	jmpl	*0x591a49(,%eax,4)
  58646d:      	movl	$0x609bcc, %eax         # imm = 0x609BCC
  586472:      	jmp	0x591a45 <.text+0x190a45>
  586477:      	movl	$0x609bac, %eax         # imm = 0x609BAC
  58647c:      	jmp	0x591a45 <.text+0x190a45>
  586481:      	movl	$0x609b88, %eax         # imm = 0x609B88
  586486:      	jmp	0x591a45 <.text+0x190a45>
  58648b:      	movl	$0x609b6c, %eax         # imm = 0x609B6C
  586490:      	jmp	0x591a45 <.text+0x190a45>
  586495:      	movl	$0x609b48, %eax         # imm = 0x609B48
  58649a:      	jmp	0x591a45 <.text+0x190a45>
  58649f:      	movl	$0x609b28, %eax         # imm = 0x609B28
  5864a4:      	jmp	0x591a45 <.text+0x190a45>
  5864a9:      	movl	$0x609b0c, %eax         # imm = 0x609B0C
  5864ae:      	jmp	0x591a45 <.text+0x190a45>
  5864b3:      	movl	$0x609aec, %eax         # imm = 0x609AEC
  5864b8:      	jmp	0x591a45 <.text+0x190a45>
  5864bd:      	movl	$0x609ad8, %eax         # imm = 0x609AD8
  5864c2:      	jmp	0x591a45 <.text+0x190a45>
  5864c7:      	movl	$0x609ac0, %eax         # imm = 0x609AC0
  5864cc:      	jmp	0x591a45 <.text+0x190a45>
  5864d1:      	addl	$0x7fffbfeb, %eax       # imm = 0x7FFFBFEB
  5864d6:      	cmpl	$0x13, %eax
  5864d9:      	ja	0x591a16 <.text+0x190a16>
  5864df:      	jmpl	*0x591a6d(,%eax,4)
  5864e6:      	movl	$0x609aa4, %eax         # imm = 0x609AA4
  5864eb:      	jmp	0x591a45 <.text+0x190a45>
  5864f0:      	movl	$0x609a8c, %eax         # imm = 0x609A8C
  5864f5:      	jmp	0x591a45 <.text+0x190a45>
  5864fa:      	movl	$0x609a78, %eax         # imm = 0x609A78
  5864ff:      	jmp	0x591a45 <.text+0x190a45>
  586504:      	movl	$0x609a5c, %eax         # imm = 0x609A5C
  586509:      	jmp	0x591a45 <.text+0x190a45>
  58650e:      	movl	$0x609a38, %eax         # imm = 0x609A38
  586513:      	jmp	0x591a45 <.text+0x190a45>
  586518:      	movl	$0x609a1c, %eax         # imm = 0x609A1C
  58651d:      	jmp	0x591a45 <.text+0x190a45>
  586522:      	movl	$0x6099fc, %eax         # imm = 0x6099FC
  586527:      	jmp	0x591a45 <.text+0x190a45>
  58652c:      	movl	$0x6099e0, %eax         # imm = 0x6099E0
  586531:      	jmp	0x591a45 <.text+0x190a45>
  586536:      	movl	$0x6099bc, %eax         # imm = 0x6099BC
  58653b:      	jmp	0x591a45 <.text+0x190a45>
  586540:      	movl	$0x6099a0, %eax         # imm = 0x6099A0
  586545:      	jmp	0x591a45 <.text+0x190a45>
  58654a:      	movl	$0x609984, %eax         # imm = 0x609984
  58654f:      	jmp	0x591a45 <.text+0x190a45>
  586554:      	movl	$0x609968, %eax         # imm = 0x609968
  586559:      	jmp	0x591a45 <.text+0x190a45>
  58655e:      	movl	$0x609954, %eax         # imm = 0x609954
  586563:      	jmp	0x591a45 <.text+0x190a45>
  586568:      	movl	$0x609944, %eax         # imm = 0x609944
  58656d:      	jmp	0x591a45 <.text+0x190a45>
  586572:      	movl	$0x609934, %eax         # imm = 0x609934
  586577:      	jmp	0x591a45 <.text+0x190a45>
  58657c:      	movl	$0x609904, %eax         # imm = 0x609904
  586581:      	jmp	0x591a45 <.text+0x190a45>
  586586:      	movl	$0x6098f0, %eax         # imm = 0x6098F0
  58658b:      	jmp	0x591a45 <.text+0x190a45>
  586590:      	movl	$0x6098d8, %eax         # imm = 0x6098D8
  586595:      	jmp	0x591a45 <.text+0x190a45>
  58659a:      	movl	$0x6098c4, %eax         # imm = 0x6098C4
  58659f:      	jmp	0x591a45 <.text+0x190a45>
  5865a4:      	movl	$0x6098ac, %eax         # imm = 0x6098AC
  5865a9:      	jmp	0x591a45 <.text+0x190a45>
  5865ae:      	movl	$0x609890, %eax         # imm = 0x609890
  5865b3:      	jmp	0x591a45 <.text+0x190a45>
  5865b8:      	movl	$0x8001000e, %ecx       # imm = 0x8001000E
  5865bd:      	cmpl	%ecx, %eax
  5865bf:      	jg	0x586715 <.text+0x185715>
  5865c5:      	je	0x58670b <.text+0x18570b>
  5865cb:      	addl	$-0xa, %ecx
  5865ce:      	cmpl	%ecx, %eax
  5865d0:      	jg	0x58669c <.text+0x18569c>
  5865d6:      	je	0x586692 <.text+0x185692>
  5865dc:      	movl	$0x80004033, %ecx       # imm = 0x80004033
  5865e1:      	cmpl	%ecx, %eax
  5865e3:      	jg	0x58664a <.text+0x18564a>
  5865e5:      	je	0x586640 <.text+0x185640>
  5865e7:      	cmpl	$0x8000402a, %eax       # imm = 0x8000402A
  5865ec:      	je	0x586636 <.text+0x185636>
  5865ee:      	cmpl	$0x8000402b, %eax       # imm = 0x8000402B
  5865f3:      	je	0x58662c <.text+0x18562c>
  5865f5:      	cmpl	$0x80004030, %eax       # imm = 0x80004030
  5865fa:      	je	0x586622 <.text+0x185622>
  5865fc:      	cmpl	$0x80004031, %eax       # imm = 0x80004031
  586601:      	je	0x586618 <.text+0x185618>
  586603:      	cmpl	$0x80004032, %eax       # imm = 0x80004032
  586608:      	jne	0x591a16 <.text+0x190a16>
  58660e:      	movl	$0x609880, %eax         # imm = 0x609880
  586613:      	jmp	0x591a45 <.text+0x190a45>
  586618:      	movl	$0x609868, %eax         # imm = 0x609868
  58661d:      	jmp	0x591a45 <.text+0x190a45>
  586622:      	movl	$0x609854, %eax         # imm = 0x609854
  586627:      	jmp	0x591a45 <.text+0x190a45>
  58662c:      	movl	$0x609838, %eax         # imm = 0x609838
  586631:      	jmp	0x591a45 <.text+0x190a45>
  586636:      	movl	$0x60981c, %eax         # imm = 0x60981C
  58663b:      	jmp	0x591a45 <.text+0x190a45>
  586640:      	movl	$0x609808, %eax         # imm = 0x609808
  586645:      	jmp	0x591a45 <.text+0x190a45>
  58664a:      	cmpl	$0x8000ffff, %eax       # imm = 0x8000FFFF
  58664f:      	je	0x586688 <.text+0x185688>
  586651:      	cmpl	$0x80010001, %eax       # imm = 0x80010001
  586656:      	je	0x58667e <.text+0x18567e>
  586658:      	cmpl	$0x80010002, %eax       # imm = 0x80010002
  58665d:      	je	0x586674 <.text+0x185674>
  58665f:      	cmpl	$0x80010003, %eax       # imm = 0x80010003
  586664:      	jne	0x591a16 <.text+0x190a16>
  58666a:      	movl	$0x6097ec, %eax         # imm = 0x6097EC
  58666f:      	jmp	0x591a45 <.text+0x190a45>
  586674:      	movl	$0x6097d8, %eax         # imm = 0x6097D8
  586679:      	jmp	0x591a45 <.text+0x190a45>
  58667e:      	movl	$0x6097c4, %eax         # imm = 0x6097C4
  586683:      	jmp	0x591a45 <.text+0x190a45>
  586688:      	movl	$0x6097b4, %eax         # imm = 0x6097B4
  58668d:      	jmp	0x591a45 <.text+0x190a45>
  586692:      	movl	$0x609794, %eax         # imm = 0x609794
  586697:      	jmp	0x591a45 <.text+0x190a45>
  58669c:      	addl	$0x7ffefffb, %eax       # imm = 0x7FFEFFFB
  5866a1:      	cmpl	$0x8, %eax
  5866a4:      	ja	0x591a16 <.text+0x190a16>
  5866aa:      	jmpl	*0x591abd(,%eax,4)
  5866b1:      	movl	$0x609770, %eax         # imm = 0x609770
  5866b6:      	jmp	0x591a45 <.text+0x190a45>
  5866bb:      	movl	$0x609754, %eax         # imm = 0x609754
  5866c0:      	jmp	0x591a45 <.text+0x190a45>
  5866c5:      	movl	$0x609740, %eax         # imm = 0x609740
  5866ca:      	jmp	0x591a45 <.text+0x190a45>
  5866cf:      	movl	$0x60972c, %eax         # imm = 0x60972C
  5866d4:      	jmp	0x591a45 <.text+0x190a45>
  5866d9:      	movl	$0x609710, %eax         # imm = 0x609710
  5866de:      	jmp	0x591a45 <.text+0x190a45>
  5866e3:      	movl	$0x6096f8, %eax         # imm = 0x6096F8
  5866e8:      	jmp	0x591a45 <.text+0x190a45>
  5866ed:      	movl	$0x6096d8, %eax         # imm = 0x6096D8
  5866f2:      	jmp	0x591a45 <.text+0x190a45>
  5866f7:      	movl	$0x6096b8, %eax         # imm = 0x6096B8
  5866fc:      	jmp	0x591a45 <.text+0x190a45>
  586701:      	movl	$0x609698, %eax         # imm = 0x609698
  586706:      	jmp	0x591a45 <.text+0x190a45>
  58670b:      	movl	$0x609678, %eax         # imm = 0x609678
  586710:      	jmp	0x591a45 <.text+0x190a45>
  586715:      	movl	$0x80010106, %ecx       # imm = 0x80010106
  58671a:      	cmpl	%ecx, %eax
  58671c:      	jg	0x5867e6 <.text+0x1857e6>
  586722:      	je	0x5867dc <.text+0x1857dc>
  586728:      	addl	$-0x5, %ecx
  58672b:      	cmpl	%ecx, %eax
  58672d:      	jg	0x586794 <.text+0x185794>
  58672f:      	je	0x58678a <.text+0x18578a>
  586731:      	cmpl	$0x8001000f, %eax       # imm = 0x8001000F
  586736:      	je	0x586780 <.text+0x185780>
  586738:      	cmpl	$0x80010010, %eax       # imm = 0x80010010
  58673d:      	je	0x586776 <.text+0x185776>
  58673f:      	cmpl	$0x80010011, %eax       # imm = 0x80010011
  586744:      	je	0x58676c <.text+0x18576c>
  586746:      	cmpl	$0x80010012, %eax       # imm = 0x80010012
  58674b:      	je	0x586762 <.text+0x185762>
  58674d:      	cmpl	$0x80010100, %eax       # imm = 0x80010100
  586752:      	jne	0x591a16 <.text+0x190a16>
  586758:      	movl	$0x609660, %eax         # imm = 0x609660
  58675d:      	jmp	0x591a45 <.text+0x190a45>
  586762:      	movl	$0x609648, %eax         # imm = 0x609648
  586767:      	jmp	0x591a45 <.text+0x190a45>
  58676c:      	movl	$0x609630, %eax         # imm = 0x609630
  586771:      	jmp	0x591a45 <.text+0x190a45>
  586776:      	movl	$0x609618, %eax         # imm = 0x609618
  58677b:      	jmp	0x591a45 <.text+0x190a45>
  586780:      	movl	$0x609604, %eax         # imm = 0x609604
  586785:      	jmp	0x591a45 <.text+0x190a45>
  58678a:      	movl	$0x6095ec, %eax         # imm = 0x6095EC
  58678f:      	jmp	0x591a45 <.text+0x190a45>
  586794:      	cmpl	$0x80010102, %eax       # imm = 0x80010102
  586799:      	je	0x5867d2 <.text+0x1857d2>
  58679b:      	cmpl	$0x80010103, %eax       # imm = 0x80010103
  5867a0:      	je	0x5867c8 <.text+0x1857c8>
  5867a2:      	cmpl	$0x80010104, %eax       # imm = 0x80010104
  5867a7:      	je	0x5867be <.text+0x1857be>
  5867a9:      	cmpl	$0x80010105, %eax       # imm = 0x80010105
  5867ae:      	jne	0x591a16 <.text+0x190a16>
  5867b4:      	movl	$0x6095d8, %eax         # imm = 0x6095D8
  5867b9:      	jmp	0x591a45 <.text+0x190a45>
  5867be:      	movl	$0x6095cc, %eax         # imm = 0x6095CC
  5867c3:      	jmp	0x591a45 <.text+0x190a45>
  5867c8:      	movl	$0x6095b4, %eax         # imm = 0x6095B4
  5867cd:      	jmp	0x591a45 <.text+0x190a45>
  5867d2:      	movl	$0x609598, %eax         # imm = 0x609598
  5867d7:      	jmp	0x591a45 <.text+0x190a45>
  5867dc:      	movl	$0x609584, %eax         # imm = 0x609584
  5867e1:      	jmp	0x591a45 <.text+0x190a45>
  5867e6:      	addl	$0x7ffefef9, %eax       # imm = 0x7FFEFEF9
  5867eb:      	cmpl	$0x8, %eax
  5867ee:      	ja	0x591a16 <.text+0x190a16>
  5867f4:      	jmpl	*0x591ae1(,%eax,4)
  5867fb:      	movl	$0x609570, %eax         # imm = 0x609570
  586800:      	jmp	0x591a45 <.text+0x190a45>
  586805:      	movl	$0x60955c, %eax         # imm = 0x60955C
  58680a:      	jmp	0x591a45 <.text+0x190a45>
  58680f:      	movl	$0x609550, %eax         # imm = 0x609550
  586814:      	jmp	0x591a45 <.text+0x190a45>
  586819:      	movl	$0x609534, %eax         # imm = 0x609534
  58681e:      	jmp	0x591a45 <.text+0x190a45>
  586823:      	movl	$0x609518, %eax         # imm = 0x609518
  586828:      	jmp	0x591a45 <.text+0x190a45>
  58682d:      	movl	$0x609500, %eax         # imm = 0x609500
  586832:      	jmp	0x591a45 <.text+0x190a45>
  586837:      	movl	$0x6094dc, %eax         # imm = 0x6094DC
  58683c:      	jmp	0x591a45 <.text+0x190a45>
  586841:      	movl	$0x6094c8, %eax         # imm = 0x6094C8
  586846:      	jmp	0x591a45 <.text+0x190a45>
  58684b:      	movl	$0x6094b0, %eax         # imm = 0x6094B0
  586850:      	jmp	0x591a45 <.text+0x190a45>
  586855:      	movl	$0x609498, %eax         # imm = 0x609498
  58685a:      	jmp	0x591a45 <.text+0x190a45>
  58685f:      	movl	$0x8001ffff, %ecx       # imm = 0x8001FFFF
  586864:      	cmpl	%ecx, %eax
  586866:      	jg	0x586a67 <.text+0x185a67>
  58686c:      	je	0x586a5d <.text+0x185a5d>
  586872:      	addl	$0x7ffefeef, %eax       # imm = 0x7FFEFEEF
  586877:      	cmpl	$0x2f, %eax
  58687a:      	ja	0x591a16 <.text+0x190a16>
  586880:      	jmpl	*0x591b05(,%eax,4)
  586887:      	movl	$0x609480, %eax         # imm = 0x609480
  58688c:      	jmp	0x591a45 <.text+0x190a45>
  586891:      	movl	$0x609468, %eax         # imm = 0x609468
  586896:      	jmp	0x591a45 <.text+0x190a45>
  58689b:      	movl	$0x609454, %eax         # imm = 0x609454
  5868a0:      	jmp	0x591a45 <.text+0x190a45>
  5868a5:      	movl	$0x60943c, %eax         # imm = 0x60943C
  5868aa:      	jmp	0x591a45 <.text+0x190a45>
  5868af:      	movl	$0x609428, %eax         # imm = 0x609428
  5868b4:      	jmp	0x591a45 <.text+0x190a45>
  5868b9:      	movl	$0x609414, %eax         # imm = 0x609414
  5868be:      	jmp	0x591a45 <.text+0x190a45>
  5868c3:      	movl	$0x609400, %eax         # imm = 0x609400
  5868c8:      	jmp	0x591a45 <.text+0x190a45>
  5868cd:      	movl	$0x6093ec, %eax         # imm = 0x6093EC
  5868d2:      	jmp	0x591a45 <.text+0x190a45>
  5868d7:      	movl	$0x6093dc, %eax         # imm = 0x6093DC
  5868dc:      	jmp	0x591a45 <.text+0x190a45>
  5868e1:      	movl	$0x6093bc, %eax         # imm = 0x6093BC
  5868e6:      	jmp	0x591a45 <.text+0x190a45>
  5868eb:      	movl	$0x6093a8, %eax         # imm = 0x6093A8
  5868f0:      	jmp	0x591a45 <.text+0x190a45>
  5868f5:      	movl	$0x609390, %eax         # imm = 0x609390
  5868fa:      	jmp	0x591a45 <.text+0x190a45>
  5868ff:      	movl	$0x609378, %eax         # imm = 0x609378
  586904:      	jmp	0x591a45 <.text+0x190a45>
  586909:      	movl	$0x609364, %eax         # imm = 0x609364
  58690e:      	jmp	0x591a45 <.text+0x190a45>
  586913:      	movl	$0x609354, %eax         # imm = 0x609354
  586918:      	jmp	0x591a45 <.text+0x190a45>
  58691d:      	movl	$0x609344, %eax         # imm = 0x609344
  586922:      	jmp	0x591a45 <.text+0x190a45>
  586927:      	movl	$0x60932c, %eax         # imm = 0x60932C
  58692c:      	jmp	0x591a45 <.text+0x190a45>
  586931:      	movl	$0x609314, %eax         # imm = 0x609314
  586936:      	jmp	0x591a45 <.text+0x190a45>
  58693b:      	movl	$0x6092f8, %eax         # imm = 0x6092F8
  586940:      	jmp	0x591a45 <.text+0x190a45>
  586945:      	movl	$0x6092e0, %eax         # imm = 0x6092E0
  58694a:      	jmp	0x591a45 <.text+0x190a45>
  58694f:      	movl	$0x6092c0, %eax         # imm = 0x6092C0
  586954:      	jmp	0x591a45 <.text+0x190a45>
  586959:      	movl	$0x6092a4, %eax         # imm = 0x6092A4
  58695e:      	jmp	0x591a45 <.text+0x190a45>
  586963:      	movl	$0x609284, %eax         # imm = 0x609284
  586968:      	jmp	0x591a45 <.text+0x190a45>
  58696d:      	movl	$0x609264, %eax         # imm = 0x609264
  586972:      	jmp	0x591a45 <.text+0x190a45>
  586977:      	movl	$0x60924c, %eax         # imm = 0x60924C
  58697c:      	jmp	0x591a45 <.text+0x190a45>
  586981:      	movl	$0x609234, %eax         # imm = 0x609234
  586986:      	jmp	0x591a45 <.text+0x190a45>
  58698b:      	movl	$0x60921c, %eax         # imm = 0x60921C
  586990:      	jmp	0x591a45 <.text+0x190a45>
  586995:      	movl	$0x609200, %eax         # imm = 0x609200
  58699a:      	jmp	0x591a45 <.text+0x190a45>
  58699f:      	movl	$0x6091f0, %eax         # imm = 0x6091F0
  5869a4:      	jmp	0x591a45 <.text+0x190a45>
  5869a9:      	movl	$0x6091d8, %eax         # imm = 0x6091D8
  5869ae:      	jmp	0x591a45 <.text+0x190a45>
  5869b3:      	movl	$0x6091c0, %eax         # imm = 0x6091C0
  5869b8:      	jmp	0x591a45 <.text+0x190a45>
  5869bd:      	movl	$0x6091a8, %eax         # imm = 0x6091A8
  5869c2:      	jmp	0x591a45 <.text+0x190a45>
  5869c7:      	movl	$0x60918c, %eax         # imm = 0x60918C
  5869cc:      	jmp	0x591a45 <.text+0x190a45>
  5869d1:      	movl	$0x609170, %eax         # imm = 0x609170
  5869d6:      	jmp	0x591a45 <.text+0x190a45>
  5869db:      	movl	$0x609158, %eax         # imm = 0x609158
  5869e0:      	jmp	0x591a45 <.text+0x190a45>
  5869e5:      	movl	$0x609140, %eax         # imm = 0x609140
  5869ea:      	jmp	0x591a45 <.text+0x190a45>
  5869ef:      	movl	$0x60912c, %eax         # imm = 0x60912C
  5869f4:      	jmp	0x591a45 <.text+0x190a45>
  5869f9:      	movl	$0x609114, %eax         # imm = 0x609114
  5869fe:      	jmp	0x591a45 <.text+0x190a45>
  586a03:      	movl	$0x6090fc, %eax         # imm = 0x6090FC
  586a08:      	jmp	0x591a45 <.text+0x190a45>
  586a0d:      	movl	$0x6090e0, %eax         # imm = 0x6090E0
  586a12:      	jmp	0x591a45 <.text+0x190a45>
  586a17:      	movl	$0x6090c8, %eax         # imm = 0x6090C8
  586a1c:      	jmp	0x591a45 <.text+0x190a45>
  586a21:      	movl	$0x6090b0, %eax         # imm = 0x6090B0
  586a26:      	jmp	0x591a45 <.text+0x190a45>
  586a2b:      	movl	$0x609090, %eax         # imm = 0x609090
  586a30:      	jmp	0x591a45 <.text+0x190a45>
  586a35:      	movl	$0x609070, %eax         # imm = 0x609070
  586a3a:      	jmp	0x591a45 <.text+0x190a45>
  586a3f:      	movl	$0x60905c, %eax         # imm = 0x60905C
  586a44:      	jmp	0x591a45 <.text+0x190a45>
  586a49:      	movl	$0x609044, %eax         # imm = 0x609044
  586a4e:      	jmp	0x591a45 <.text+0x190a45>
  586a53:      	movl	$0x60902c, %eax         # imm = 0x60902C
  586a58:      	jmp	0x591a45 <.text+0x190a45>
  586a5d:      	movl	$0x609018, %eax         # imm = 0x609018
  586a62:      	jmp	0x591a45 <.text+0x190a45>
  586a67:      	movl	$0x80028016, %ecx       # imm = 0x80028016
  586a6c:      	cmpl	%ecx, %eax
  586a6e:      	jg	0x586b4d <.text+0x185b4d>
  586a74:      	je	0x586b43 <.text+0x185b43>
  586a7a:      	addl	$0x7ffdffff, %eax       # imm = 0x7FFDFFFF
  586a7f:      	cmpl	$0x12, %eax
  586a82:      	ja	0x591a16 <.text+0x190a16>
  586a88:      	jmpl	*0x591bc5(,%eax,4)
  586a8f:      	movl	$0x609000, %eax         # imm = 0x609000
  586a94:      	jmp	0x591a45 <.text+0x190a45>
  586a99:      	movl	$0x608fe8, %eax         # imm = 0x608FE8
  586a9e:      	jmp	0x591a45 <.text+0x190a45>
  586aa3:      	movl	$0x608fd0, %eax         # imm = 0x608FD0
  586aa8:      	jmp	0x591a45 <.text+0x190a45>
  586aad:      	movl	$0x608fbc, %eax         # imm = 0x608FBC
  586ab2:      	jmp	0x591a45 <.text+0x190a45>
  586ab7:      	movl	$0x608fa8, %eax         # imm = 0x608FA8
  586abc:      	jmp	0x591a45 <.text+0x190a45>
  586ac1:      	movl	$0x608f94, %eax         # imm = 0x608F94
  586ac6:      	jmp	0x591a45 <.text+0x190a45>
  586acb:      	movl	$0x608f80, %eax         # imm = 0x608F80
  586ad0:      	jmp	0x591a45 <.text+0x190a45>
  586ad5:      	movl	$0x608f6c, %eax         # imm = 0x608F6C
  586ada:      	jmp	0x591a45 <.text+0x190a45>
  586adf:      	movl	$0x608f5c, %eax         # imm = 0x608F5C
  586ae4:      	jmp	0x591a45 <.text+0x190a45>
  586ae9:      	movl	$0x608f4c, %eax         # imm = 0x608F4C
  586aee:      	jmp	0x591a45 <.text+0x190a45>
  586af3:      	movl	$0x608f38, %eax         # imm = 0x608F38
  586af8:      	jmp	0x591a45 <.text+0x190a45>
  586afd:      	movl	$0x608f20, %eax         # imm = 0x608F20
  586b02:      	jmp	0x591a45 <.text+0x190a45>
  586b07:      	movl	$0x608f08, %eax         # imm = 0x608F08
  586b0c:      	jmp	0x591a45 <.text+0x190a45>
  586b11:      	movl	$0x608ef0, %eax         # imm = 0x608EF0
  586b16:      	jmp	0x591a45 <.text+0x190a45>
  586b1b:      	movl	$0x608edc, %eax         # imm = 0x608EDC
  586b20:      	jmp	0x591a45 <.text+0x190a45>
  586b25:      	movl	$0x608ec4, %eax         # imm = 0x608EC4
  586b2a:      	jmp	0x591a45 <.text+0x190a45>
  586b2f:      	movl	$0x608eb0, %eax         # imm = 0x608EB0
  586b34:      	jmp	0x591a45 <.text+0x190a45>
  586b39:      	movl	$0x608e98, %eax         # imm = 0x608E98
  586b3e:      	jmp	0x591a45 <.text+0x190a45>
  586b43:      	movl	$0x608e80, %eax         # imm = 0x608E80
  586b48:      	jmp	0x591a45 <.text+0x190a45>
  586b4d:      	movl	$0x8002802a, %ecx       # imm = 0x8002802A
  586b52:      	cmpl	%ecx, %eax
  586b54:      	jg	0x586bfc <.text+0x185bfc>
  586b5a:      	je	0x586bf2 <.text+0x185bf2>
  586b60:      	addl	$-0xd, %ecx
  586b63:      	cmpl	%ecx, %eax
  586b65:      	jg	0x586bbb <.text+0x185bbb>
  586b67:      	je	0x586bb1 <.text+0x185bb1>
  586b69:      	cmpl	$0x80028017, %eax       # imm = 0x80028017
  586b6e:      	je	0x586ba7 <.text+0x185ba7>
  586b70:      	cmpl	$0x80028018, %eax       # imm = 0x80028018
  586b75:      	je	0x586b9d <.text+0x185b9d>
  586b77:      	cmpl	$0x80028019, %eax       # imm = 0x80028019
  586b7c:      	je	0x586b93 <.text+0x185b93>
  586b7e:      	cmpl	$0x8002801c, %eax       # imm = 0x8002801C
  586b83:      	jne	0x591a16 <.text+0x190a16>
  586b89:      	movl	$0x608e68, %eax         # imm = 0x608E68
  586b8e:      	jmp	0x591a45 <.text+0x190a45>
  586b93:      	movl	$0x608e54, %eax         # imm = 0x608E54
  586b98:      	jmp	0x591a45 <.text+0x190a45>
  586b9d:      	movl	$0x608e40, %eax         # imm = 0x608E40
  586ba2:      	jmp	0x591a45 <.text+0x190a45>
  586ba7:      	movl	$0x608e28, %eax         # imm = 0x608E28
  586bac:      	jmp	0x591a45 <.text+0x190a45>
  586bb1:      	movl	$0x608e10, %eax         # imm = 0x608E10
  586bb6:      	jmp	0x591a45 <.text+0x190a45>
  586bbb:      	cmpl	$0x80028027, %eax       # imm = 0x80028027
  586bc0:      	je	0x586be8 <.text+0x185be8>
  586bc2:      	cmpl	$0x80028028, %eax       # imm = 0x80028028
  586bc7:      	je	0x586bde <.text+0x185bde>
  586bc9:      	cmpl	$0x80028029, %eax       # imm = 0x80028029
  586bce:      	jne	0x591a16 <.text+0x190a16>
  586bd4:      	movl	$0x608dfc, %eax         # imm = 0x608DFC
  586bd9:      	jmp	0x591a45 <.text+0x190a45>
  586bde:      	movl	$0x608ddc, %eax         # imm = 0x608DDC
  586be3:      	jmp	0x591a45 <.text+0x190a45>
  586be8:      	movl	$0x608dc4, %eax         # imm = 0x608DC4
  586bed:      	jmp	0x591a45 <.text+0x190a45>
  586bf2:      	movl	$0x608dac, %eax         # imm = 0x608DAC
  586bf7:      	jmp	0x591a45 <.text+0x190a45>
  586bfc:      	cmpl	$0x8002802b, %eax       # imm = 0x8002802B
  586c01:      	je	0x586c6d <.text+0x185c6d>
  586c03:      	cmpl	$0x8002802c, %eax       # imm = 0x8002802C
  586c08:      	je	0x586c63 <.text+0x185c63>
  586c0a:      	cmpl	$0x8002802d, %eax       # imm = 0x8002802D
  586c0f:      	je	0x586c59 <.text+0x185c59>
  586c11:      	cmpl	$0x8002802e, %eax       # imm = 0x8002802E
  586c16:      	je	0x586c4f <.text+0x185c4f>
  586c18:      	cmpl	$0x8002802f, %eax       # imm = 0x8002802F
  586c1d:      	je	0x586c45 <.text+0x185c45>
  586c1f:      	cmpl	$0x800288bd, %eax       # imm = 0x800288BD
  586c24:      	je	0x586c3b <.text+0x185c3b>
  586c26:      	cmpl	$0x800288c5, %eax       # imm = 0x800288C5
  586c2b:      	jne	0x591a16 <.text+0x190a16>
  586c31:      	movl	$0x608d98, %eax         # imm = 0x608D98
  586c36:      	jmp	0x591a45 <.text+0x190a45>
  586c3b:      	movl	$0x608d80, %eax         # imm = 0x608D80
  586c40:      	jmp	0x591a45 <.text+0x190a45>
  586c45:      	movl	$0x608d64, %eax         # imm = 0x608D64
  586c4a:      	jmp	0x591a45 <.text+0x190a45>
  586c4f:      	movl	$0x608d50, %eax         # imm = 0x608D50
  586c54:      	jmp	0x591a45 <.text+0x190a45>
  586c59:      	movl	$0x608d3c, %eax         # imm = 0x608D3C
  586c5e:      	jmp	0x591a45 <.text+0x190a45>
  586c63:      	movl	$0x608d24, %eax         # imm = 0x608D24
  586c68:      	jmp	0x591a45 <.text+0x190a45>
  586c6d:      	movl	$0x608d0c, %eax         # imm = 0x608D0C
  586c72:      	jmp	0x591a45 <.text+0x190a45>
  586c77:      	movl	$0x608cf8, %eax         # imm = 0x608CF8
  586c7c:      	jmp	0x591a45 <.text+0x190a45>
  586c81:      	movl	$0x8004006d, %ecx       # imm = 0x8004006D
  586c86:      	cmpl	%ecx, %eax
  586c88:      	jg	0x587228 <.text+0x186228>
  586c8e:      	je	0x58721e <.text+0x18621e>
  586c94:      	movl	$0x80030108, %ecx       # imm = 0x80030108
  586c99:      	cmpl	%ecx, %eax
  586c9b:      	jg	0x586f84 <.text+0x185f84>
  586ca1:      	je	0x586f7a <.text+0x185f7a>
  586ca7:      	movl	$0x8003001e, %ecx       # imm = 0x8003001E
  586cac:      	cmpl	%ecx, %eax
  586cae:      	jg	0x586e3a <.text+0x185e3a>
  586cb4:      	je	0x586e30 <.text+0x185e30>
  586cba:      	addl	$-0x1b, %ecx
  586cbd:      	cmpl	%ecx, %eax
  586cbf:      	jg	0x586d8b <.text+0x185d8b>
  586cc5:      	je	0x586d81 <.text+0x185d81>
  586ccb:      	movl	$0x80029c4a, %ecx       # imm = 0x80029C4A
  586cd0:      	cmpl	%ecx, %eax
  586cd2:      	jg	0x586d39 <.text+0x185d39>
  586cd4:      	je	0x586d2f <.text+0x185d2f>
  586cd6:      	cmpl	$0x800288cf, %eax       # imm = 0x800288CF
  586cdb:      	je	0x586d25 <.text+0x185d25>
  586cdd:      	cmpl	$0x80028ca0, %eax       # imm = 0x80028CA0
  586ce2:      	je	0x586d1b <.text+0x185d1b>
  586ce4:      	cmpl	$0x80028ca1, %eax       # imm = 0x80028CA1
  586ce9:      	je	0x586d11 <.text+0x185d11>
  586ceb:      	cmpl	$0x80028ca2, %eax       # imm = 0x80028CA2
  586cf0:      	je	0x586d07 <.text+0x185d07>
  586cf2:      	cmpl	$0x80028ca3, %eax       # imm = 0x80028CA3
  586cf7:      	jne	0x591a16 <.text+0x190a16>
  586cfd:      	movl	$0x608cdc, %eax         # imm = 0x608CDC
  586d02:      	jmp	0x591a45 <.text+0x190a45>
  586d07:      	movl	$0x608ccc, %eax         # imm = 0x608CCC
  586d0c:      	jmp	0x591a45 <.text+0x190a45>
  586d11:      	movl	$0x608cb8, %eax         # imm = 0x608CB8
  586d16:      	jmp	0x591a45 <.text+0x190a45>
  586d1b:      	movl	$0x608ca4, %eax         # imm = 0x608CA4
  586d20:      	jmp	0x591a45 <.text+0x190a45>
  586d25:      	movl	$0x608c90, %eax         # imm = 0x608C90
  586d2a:      	jmp	0x591a45 <.text+0x190a45>
  586d2f:      	movl	$0x608c78, %eax         # imm = 0x608C78
  586d34:      	jmp	0x591a45 <.text+0x190a45>
  586d39:      	cmpl	$0x80029c83, %eax       # imm = 0x80029C83
  586d3e:      	je	0x586d77 <.text+0x185d77>
  586d40:      	cmpl	$0x80029c84, %eax       # imm = 0x80029C84
  586d45:      	je	0x586d6d <.text+0x185d6d>
  586d47:      	cmpl	$0x80030001, %eax       # imm = 0x80030001
  586d4c:      	je	0x586d63 <.text+0x185d63>
  586d4e:      	cmpl	$0x80030002, %eax       # imm = 0x80030002
  586d53:      	jne	0x591a16 <.text+0x190a16>
  586d59:      	movl	$0x608c64, %eax         # imm = 0x608C64
  586d5e:      	jmp	0x591a45 <.text+0x190a45>
  586d63:      	movl	$0x608c4c, %eax         # imm = 0x608C4C
  586d68:      	jmp	0x591a45 <.text+0x190a45>
  586d6d:      	movl	$0x608c38, %eax         # imm = 0x608C38
  586d72:      	jmp	0x591a45 <.text+0x190a45>
  586d77:      	movl	$0x608c18, %eax         # imm = 0x608C18
  586d7c:      	jmp	0x591a45 <.text+0x190a45>
  586d81:      	movl	$0x608c04, %eax         # imm = 0x608C04
  586d86:      	jmp	0x591a45 <.text+0x190a45>
  586d8b:      	movl	$0x80030009, %ecx       # imm = 0x80030009
  586d90:      	cmpl	%ecx, %eax
  586d92:      	jg	0x586de8 <.text+0x185de8>
  586d94:      	je	0x586dde <.text+0x185dde>
  586d96:      	cmpl	$0x80030004, %eax       # imm = 0x80030004
  586d9b:      	je	0x586dd4 <.text+0x185dd4>
  586d9d:      	cmpl	$0x80030005, %eax       # imm = 0x80030005
  586da2:      	je	0x586dca <.text+0x185dca>
  586da4:      	cmpl	$0x80030006, %eax       # imm = 0x80030006
  586da9:      	je	0x586dc0 <.text+0x185dc0>
  586dab:      	cmpl	$0x80030008, %eax       # imm = 0x80030008
  586db0:      	jne	0x591a16 <.text+0x190a16>
  586db6:      	movl	$0x608be8, %eax         # imm = 0x608BE8
  586dbb:      	jmp	0x591a45 <.text+0x190a45>
  586dc0:      	movl	$0x608bd4, %eax         # imm = 0x608BD4
  586dc5:      	jmp	0x591a45 <.text+0x190a45>
  586dca:      	movl	$0x608bc0, %eax         # imm = 0x608BC0
  586dcf:      	jmp	0x591a45 <.text+0x190a45>
  586dd4:      	movl	$0x608ba8, %eax         # imm = 0x608BA8
  586dd9:      	jmp	0x591a45 <.text+0x190a45>
  586dde:      	movl	$0x608b90, %eax         # imm = 0x608B90
  586de3:      	jmp	0x591a45 <.text+0x190a45>
  586de8:      	cmpl	$0x80030012, %eax       # imm = 0x80030012
  586ded:      	je	0x586e26 <.text+0x185e26>
  586def:      	cmpl	$0x80030013, %eax       # imm = 0x80030013
  586df4:      	je	0x586e1c <.text+0x185e1c>
  586df6:      	cmpl	$0x80030019, %eax       # imm = 0x80030019
  586dfb:      	je	0x586e12 <.text+0x185e12>
  586dfd:      	cmpl	$0x8003001d, %eax       # imm = 0x8003001D
  586e02:      	jne	0x591a16 <.text+0x190a16>
  586e08:      	movl	$0x608b7c, %eax         # imm = 0x608B7C
  586e0d:      	jmp	0x591a45 <.text+0x190a45>
  586e12:      	movl	$0x608b6c, %eax         # imm = 0x608B6C
  586e17:      	jmp	0x591a45 <.text+0x190a45>
  586e1c:      	movl	$0x608b50, %eax         # imm = 0x608B50
  586e21:      	jmp	0x591a45 <.text+0x190a45>
  586e26:      	movl	$0x608b3c, %eax         # imm = 0x608B3C
  586e2b:      	jmp	0x591a45 <.text+0x190a45>
  586e30:      	movl	$0x608b2c, %eax         # imm = 0x608B2C
  586e35:      	jmp	0x591a45 <.text+0x190a45>
  586e3a:      	movl	$0x800300fe, %ecx       # imm = 0x800300FE
  586e3f:      	cmpl	%ecx, %eax
  586e41:      	jg	0x586f0b <.text+0x185f0b>
  586e47:      	je	0x586f01 <.text+0x185f01>
  586e4d:      	addl	$-0xe, %ecx
  586e50:      	cmpl	%ecx, %eax
  586e52:      	jg	0x586eb9 <.text+0x185eb9>
  586e54:      	je	0x586eaf <.text+0x185eaf>
  586e56:      	cmpl	$0x80030020, %eax       # imm = 0x80030020
  586e5b:      	je	0x586ea5 <.text+0x185ea5>
  586e5d:      	cmpl	$0x80030021, %eax       # imm = 0x80030021
  586e62:      	je	0x586e9b <.text+0x185e9b>
  586e64:      	cmpl	$0x80030050, %eax       # imm = 0x80030050
  586e69:      	je	0x586e91 <.text+0x185e91>
  586e6b:      	cmpl	$0x80030057, %eax       # imm = 0x80030057
  586e70:      	je	0x586e87 <.text+0x185e87>
  586e72:      	cmpl	$0x80030070, %eax       # imm = 0x80030070
  586e77:      	jne	0x591a16 <.text+0x190a16>
  586e7d:      	movl	$0x608b18, %eax         # imm = 0x608B18
  586e82:      	jmp	0x591a45 <.text+0x190a45>
  586e87:      	movl	$0x608b00, %eax         # imm = 0x608B00
  586e8c:      	jmp	0x591a45 <.text+0x190a45>
  586e91:      	movl	$0x608ae8, %eax         # imm = 0x608AE8
  586e96:      	jmp	0x591a45 <.text+0x190a45>
  586e9b:      	movl	$0x608ad4, %eax         # imm = 0x608AD4
  586ea0:      	jmp	0x591a45 <.text+0x190a45>
  586ea5:      	movl	$0x608abc, %eax         # imm = 0x608ABC
  586eaa:      	jmp	0x591a45 <.text+0x190a45>
  586eaf:      	movl	$0x608aa4, %eax         # imm = 0x608AA4
  586eb4:      	jmp	0x591a45 <.text+0x190a45>
  586eb9:      	cmpl	$0x800300fa, %eax       # imm = 0x800300FA
  586ebe:      	je	0x586ef7 <.text+0x185ef7>
  586ec0:      	cmpl	$0x800300fb, %eax       # imm = 0x800300FB
  586ec5:      	je	0x586eed <.text+0x185eed>
  586ec7:      	cmpl	$0x800300fc, %eax       # imm = 0x800300FC
  586ecc:      	je	0x586ee3 <.text+0x185ee3>
  586ece:      	cmpl	$0x800300fd, %eax       # imm = 0x800300FD
  586ed3:      	jne	0x591a16 <.text+0x190a16>
  586ed9:      	movl	$0x608a94, %eax         # imm = 0x608A94
  586ede:      	jmp	0x591a45 <.text+0x190a45>
  586ee3:      	movl	$0x608a80, %eax         # imm = 0x608A80
  586ee8:      	jmp	0x591a45 <.text+0x190a45>
  586eed:      	movl	$0x608a6c, %eax         # imm = 0x608A6C
  586ef2:      	jmp	0x591a45 <.text+0x190a45>
  586ef7:      	movl	$0x608a54, %eax         # imm = 0x608A54
  586efc:      	jmp	0x591a45 <.text+0x190a45>
  586f01:      	movl	$0x608a38, %eax         # imm = 0x608A38
  586f06:      	jmp	0x591a45 <.text+0x190a45>
  586f0b:      	addl	$0x7ffcff01, %eax       # imm = 0x7FFCFF01
  586f10:      	cmpl	$0x8, %eax
  586f13:      	ja	0x591a16 <.text+0x190a16>
  586f19:      	jmpl	*0x591c11(,%eax,4)
  586f20:      	movl	$0x608a24, %eax         # imm = 0x608A24
  586f25:      	jmp	0x591a45 <.text+0x190a45>
  586f2a:      	movl	$0x608a18, %eax         # imm = 0x608A18
  586f2f:      	jmp	0x591a45 <.text+0x190a45>
  586f34:      	movl	$0x608a04, %eax         # imm = 0x608A04
  586f39:      	jmp	0x591a45 <.text+0x190a45>
  586f3e:      	movl	$0x6089f4, %eax         # imm = 0x6089F4
  586f43:      	jmp	0x591a45 <.text+0x190a45>
  586f48:      	movl	$0x6089e4, %eax         # imm = 0x6089E4
  586f4d:      	jmp	0x591a45 <.text+0x190a45>
  586f52:      	movl	$0x6089d4, %eax         # imm = 0x6089D4
  586f57:      	jmp	0x591a45 <.text+0x190a45>
  586f5c:      	movl	$0x6089c4, %eax         # imm = 0x6089C4
  586f61:      	jmp	0x591a45 <.text+0x190a45>
  586f66:      	movl	$0x6089b0, %eax         # imm = 0x6089B0
  586f6b:      	jmp	0x591a45 <.text+0x190a45>
  586f70:      	movl	$0x608994, %eax         # imm = 0x608994
  586f75:      	jmp	0x591a45 <.text+0x190a45>
  586f7a:      	movl	$0x608978, %eax         # imm = 0x608978
  586f7f:      	jmp	0x591a45 <.text+0x190a45>
  586f84:      	movl	$0x80040007, %ecx       # imm = 0x80040007
  586f89:      	cmpl	%ecx, %eax
  586f8b:      	jg	0x587119 <.text+0x186119>
  586f91:      	je	0x58710f <.text+0x18610f>
  586f97:      	movl	$0x80030309, %ecx       # imm = 0x80030309
  586f9c:      	cmpl	%ecx, %eax
  586f9e:      	jg	0x58706a <.text+0x18606a>
  586fa4:      	je	0x587060 <.text+0x186060>
  586faa:      	movl	$0x80030202, %ecx       # imm = 0x80030202
  586faf:      	cmpl	%ecx, %eax
  586fb1:      	jg	0x587018 <.text+0x186018>
  586fb3:      	je	0x58700e <.text+0x18600e>
  586fb5:      	cmpl	$0x80030109, %eax       # imm = 0x80030109
  586fba:      	je	0x587004 <.text+0x186004>
  586fbc:      	cmpl	$0x80030110, %eax       # imm = 0x80030110
  586fc1:      	je	0x586ffa <.text+0x185ffa>
  586fc3:      	cmpl	$0x80030111, %eax       # imm = 0x80030111
  586fc8:      	je	0x586ff0 <.text+0x185ff0>
  586fca:      	cmpl	$0x80030112, %eax       # imm = 0x80030112
  586fcf:      	je	0x586fe6 <.text+0x185fe6>
  586fd1:      	cmpl	$0x80030201, %eax       # imm = 0x80030201
  586fd6:      	jne	0x591a16 <.text+0x190a16>
  586fdc:      	movl	$0x608964, %eax         # imm = 0x608964
  586fe1:      	jmp	0x591a45 <.text+0x190a45>
  586fe6:      	movl	$0x60894c, %eax         # imm = 0x60894C
  586feb:      	jmp	0x591a45 <.text+0x190a45>
  586ff0:      	movl	$0x608934, %eax         # imm = 0x608934
  586ff5:      	jmp	0x591a45 <.text+0x190a45>
  586ffa:      	movl	$0x60891c, %eax         # imm = 0x60891C
  586fff:      	jmp	0x591a45 <.text+0x190a45>
  587004:      	movl	$0x608904, %eax         # imm = 0x608904
  587009:      	jmp	0x591a45 <.text+0x190a45>
  58700e:      	movl	$0x6088f0, %eax         # imm = 0x6088F0
  587013:      	jmp	0x591a45 <.text+0x190a45>
  587018:      	cmpl	$0x80030305, %eax       # imm = 0x80030305
  58701d:      	je	0x587056 <.text+0x186056>
  58701f:      	cmpl	$0x80030306, %eax       # imm = 0x80030306
  587024:      	je	0x58704c <.text+0x18604c>
  587026:      	cmpl	$0x80030307, %eax       # imm = 0x80030307
  58702b:      	je	0x587042 <.text+0x186042>
  58702d:      	cmpl	$0x80030308, %eax       # imm = 0x80030308
  587032:      	jne	0x591a16 <.text+0x190a16>
  587038:      	movl	$0x6088d0, %eax         # imm = 0x6088D0
  58703d:      	jmp	0x591a45 <.text+0x190a45>
  587042:      	movl	$0x6088b4, %eax         # imm = 0x6088B4
  587047:      	jmp	0x591a45 <.text+0x190a45>
  58704c:      	movl	$0x608890, %eax         # imm = 0x608890
  587051:      	jmp	0x591a45 <.text+0x190a45>
  587056:      	movl	$0x608868, %eax         # imm = 0x608868
  58705b:      	jmp	0x591a45 <.text+0x190a45>
  587060:      	movl	$0x60884c, %eax         # imm = 0x60884C
  587065:      	jmp	0x591a45 <.text+0x190a45>
  58706a:      	movl	$0x80040002, %ecx       # imm = 0x80040002
  58706f:      	cmpl	%ecx, %eax
  587071:      	jg	0x5870c7 <.text+0x1860c7>
  587073:      	je	0x5870bd <.text+0x1860bd>
  587075:      	cmpl	$0x8003030a, %eax       # imm = 0x8003030A
  58707a:      	je	0x5870b3 <.text+0x1860b3>
  58707c:      	cmpl	$0x8003030b, %eax       # imm = 0x8003030B
  587081:      	je	0x5870a9 <.text+0x1860a9>
  587083:      	cmpl	$0x80040000, %eax       # imm = 0x80040000
  587088:      	je	0x58709f <.text+0x18609f>
  58708a:      	cmpl	$0x80040001, %eax       # imm = 0x80040001
  58708f:      	jne	0x591a16 <.text+0x190a16>
  587095:      	movl	$0x608840, %eax         # imm = 0x608840
  58709a:      	jmp	0x591a45 <.text+0x190a45>
  58709f:      	movl	$0x608834, %eax         # imm = 0x608834
  5870a4:      	jmp	0x591a45 <.text+0x190a45>
  5870a9:      	movl	$0x60881c, %eax         # imm = 0x60881C
  5870ae:      	jmp	0x591a45 <.text+0x190a45>
  5870b3:      	movl	$0x608800, %eax         # imm = 0x608800
  5870b8:      	jmp	0x591a45 <.text+0x190a45>
  5870bd:      	movl	$0x6087ec, %eax         # imm = 0x6087EC
  5870c2:      	jmp	0x591a45 <.text+0x190a45>
  5870c7:      	cmpl	$0x80040003, %eax       # imm = 0x80040003
  5870cc:      	je	0x587105 <.text+0x186105>
  5870ce:      	cmpl	$0x80040004, %eax       # imm = 0x80040004
  5870d3:      	je	0x5870fb <.text+0x1860fb>
  5870d5:      	cmpl	$0x80040005, %eax       # imm = 0x80040005
  5870da:      	je	0x5870f1 <.text+0x1860f1>
  5870dc:      	cmpl	$0x80040006, %eax       # imm = 0x80040006
  5870e1:      	jne	0x591a16 <.text+0x190a16>
  5870e7:      	movl	$0x6087dc, %eax         # imm = 0x6087DC
  5870ec:      	jmp	0x591a45 <.text+0x190a45>
  5870f1:      	movl	$0x6087c8, %eax         # imm = 0x6087C8
  5870f6:      	jmp	0x591a45 <.text+0x190a45>
  5870fb:      	movl	$0x6087b4, %eax         # imm = 0x6087B4
  587100:      	jmp	0x591a45 <.text+0x190a45>
  587105:      	movl	$0x608798, %eax         # imm = 0x608798
  58710a:      	jmp	0x591a45 <.text+0x190a45>
  58710f:      	movl	$0x60878c, %eax         # imm = 0x60878C
  587114:      	jmp	0x591a45 <.text+0x190a45>
  587119:      	movl	$0x80040064, %ecx       # imm = 0x80040064
  58711e:      	cmpl	%ecx, %eax
  587120:      	jg	0x5871b9 <.text+0x1861b9>
  587126:      	je	0x5871af <.text+0x1861af>
  58712c:      	addl	$0x7ffbfff8, %eax       # imm = 0x7FFBFFF8
  587131:      	cmpl	$0xa, %eax
  587134:      	ja	0x591a16 <.text+0x190a16>
  58713a:      	jmpl	*0x591c35(,%eax,4)
  587141:      	movl	$0x60877c, %eax         # imm = 0x60877C
  587146:      	jmp	0x591a45 <.text+0x190a45>
  58714b:      	movl	$0x608764, %eax         # imm = 0x608764
  587150:      	jmp	0x591a45 <.text+0x190a45>
  587155:      	movl	$0x60874c, %eax         # imm = 0x60874C
  58715a:      	jmp	0x591a45 <.text+0x190a45>
  58715f:      	movl	$0x60873c, %eax         # imm = 0x60873C
  587164:      	jmp	0x591a45 <.text+0x190a45>
  587169:      	movl	$0x608720, %eax         # imm = 0x608720
  58716e:      	jmp	0x591a45 <.text+0x190a45>
  587173:      	movl	$0x60870c, %eax         # imm = 0x60870C
  587178:      	jmp	0x591a45 <.text+0x190a45>
  58717d:      	movl	$0x6086f8, %eax         # imm = 0x6086F8
  587182:      	jmp	0x591a45 <.text+0x190a45>
  587187:      	movl	$0x6086e4, %eax         # imm = 0x6086E4
  58718c:      	jmp	0x591a45 <.text+0x190a45>
  587191:      	movl	$0x6086cc, %eax         # imm = 0x6086CC
  587196:      	jmp	0x591a45 <.text+0x190a45>
  58719b:      	movl	$0x6086b8, %eax         # imm = 0x6086B8
  5871a0:      	jmp	0x591a45 <.text+0x190a45>
  5871a5:      	movl	$0x6086a8, %eax         # imm = 0x6086A8
  5871aa:      	jmp	0x591a45 <.text+0x190a45>
  5871af:      	movl	$0x608698, %eax         # imm = 0x608698
  5871b4:      	jmp	0x591a45 <.text+0x190a45>
  5871b9:      	addl	$0x7ffbff9b, %eax       # imm = 0x7FFBFF9B
  5871be:      	cmpl	$0x7, %eax
  5871c1:      	ja	0x591a16 <.text+0x190a16>
  5871c7:      	jmpl	*0x591c61(,%eax,4)
  5871ce:      	movl	$0x608684, %eax         # imm = 0x608684
  5871d3:      	jmp	0x591a45 <.text+0x190a45>
  5871d8:      	movl	$0x608674, %eax         # imm = 0x608674
  5871dd:      	jmp	0x591a45 <.text+0x190a45>
  5871e2:      	movl	$0x608664, %eax         # imm = 0x608664
  5871e7:      	jmp	0x591a45 <.text+0x190a45>
  5871ec:      	movl	$0x608658, %eax         # imm = 0x608658
  5871f1:      	jmp	0x591a45 <.text+0x190a45>
  5871f6:      	movl	$0x60864c, %eax         # imm = 0x60864C
  5871fb:      	jmp	0x591a45 <.text+0x190a45>
  587200:      	movl	$0x60863c, %eax         # imm = 0x60863C
  587205:      	jmp	0x591a45 <.text+0x190a45>
  58720a:      	movl	$0x60862c, %eax         # imm = 0x60862C
  58720f:      	jmp	0x591a45 <.text+0x190a45>
  587214:      	movl	$0x608610, %eax         # imm = 0x608610
  587219:      	jmp	0x591a45 <.text+0x190a45>
  58721e:      	movl	$0x6085fc, %eax         # imm = 0x6085FC
  587223:      	jmp	0x591a45 <.text+0x190a45>
  587228:      	addl	$0x7ffbff01, %eax       # imm = 0x7FFBFF01
  58722d:      	cmpl	$0xf3, %eax
  587232:      	ja	0x591a16 <.text+0x190a16>
  587238:      	movzbl	0x591dcd(%eax), %eax
  58723f:      	jmpl	*0x591c81(,%eax,4)
  587246:      	movl	$0x6085f0, %eax         # imm = 0x6085F0
  58724b:      	jmp	0x591a45 <.text+0x190a45>
  587250:      	movl	$0x6085dc, %eax         # imm = 0x6085DC
  587255:      	jmp	0x591a45 <.text+0x190a45>
  58725a:      	movl	$0x6085cc, %eax         # imm = 0x6085CC
  58725f:      	jmp	0x591a45 <.text+0x190a45>
  587264:      	movl	$0x6085ac, %eax         # imm = 0x6085AC
  587269:      	jmp	0x591a45 <.text+0x190a45>
  58726e:      	movl	$0x608594, %eax         # imm = 0x608594
  587273:      	jmp	0x591a45 <.text+0x190a45>
  587278:      	movl	$0x60857c, %eax         # imm = 0x60857C
  58727d:      	jmp	0x591a45 <.text+0x190a45>
  587282:      	movl	$0x608568, %eax         # imm = 0x608568
  587287:      	jmp	0x591a45 <.text+0x190a45>
  58728c:      	movl	$0x60854c, %eax         # imm = 0x60854C
  587291:      	jmp	0x591a45 <.text+0x190a45>
  587296:      	movl	$0x608538, %eax         # imm = 0x608538
  58729b:      	jmp	0x591a45 <.text+0x190a45>
  5872a0:      	movl	$0x608528, %eax         # imm = 0x608528
  5872a5:      	jmp	0x591a45 <.text+0x190a45>
  5872aa:      	movl	$0x608518, %eax         # imm = 0x608518
  5872af:      	jmp	0x591a45 <.text+0x190a45>
  5872b4:      	movl	$0x608508, %eax         # imm = 0x608508
  5872b9:      	jmp	0x591a45 <.text+0x190a45>
  5872be:      	movl	$0x6084fc, %eax         # imm = 0x6084FC
  5872c3:      	jmp	0x591a45 <.text+0x190a45>
  5872c8:      	movl	$0x6084ec, %eax         # imm = 0x6084EC
  5872cd:      	jmp	0x591a45 <.text+0x190a45>
  5872d2:      	movl	$0x6084e0, %eax         # imm = 0x6084E0
  5872d7:      	jmp	0x591a45 <.text+0x190a45>
  5872dc:      	movl	$0x6084d0, %eax         # imm = 0x6084D0
  5872e1:      	jmp	0x591a45 <.text+0x190a45>
  5872e6:      	movl	$0x6084c0, %eax         # imm = 0x6084C0
  5872eb:      	jmp	0x591a45 <.text+0x190a45>
  5872f0:      	movl	$0x6084ac, %eax         # imm = 0x6084AC
  5872f5:      	jmp	0x591a45 <.text+0x190a45>
  5872fa:      	movl	$0x608498, %eax         # imm = 0x608498
  5872ff:      	jmp	0x591a45 <.text+0x190a45>
  587304:      	movl	$0x608480, %eax         # imm = 0x608480
  587309:      	jmp	0x591a45 <.text+0x190a45>
  58730e:      	movl	$0x60846c, %eax         # imm = 0x60846C
  587313:      	jmp	0x591a45 <.text+0x190a45>
  587318:      	movl	$0x608458, %eax         # imm = 0x608458
  58731d:      	jmp	0x591a45 <.text+0x190a45>
  587322:      	movl	$0x60844c, %eax         # imm = 0x60844C
  587327:      	jmp	0x591a45 <.text+0x190a45>
  58732c:      	movl	$0x608440, %eax         # imm = 0x608440
  587331:      	jmp	0x591a45 <.text+0x190a45>
  587336:      	movl	$0x608434, %eax         # imm = 0x608434
  58733b:      	jmp	0x591a45 <.text+0x190a45>
  587340:      	movl	$0x608428, %eax         # imm = 0x608428
  587345:      	jmp	0x591a45 <.text+0x190a45>
  58734a:      	movl	$0x608414, %eax         # imm = 0x608414
  58734f:      	jmp	0x591a45 <.text+0x190a45>
  587354:      	movl	$0x608400, %eax         # imm = 0x608400
  587359:      	jmp	0x591a45 <.text+0x190a45>
  58735e:      	movl	$0x6083e8, %eax         # imm = 0x6083E8
  587363:      	jmp	0x591a45 <.text+0x190a45>
  587368:      	movl	$0x6083d4, %eax         # imm = 0x6083D4
  58736d:      	jmp	0x591a45 <.text+0x190a45>
  587372:      	movl	$0x6083bc, %eax         # imm = 0x6083BC
  587377:      	jmp	0x591a45 <.text+0x190a45>
  58737c:      	movl	$0x6083a0, %eax         # imm = 0x6083A0
  587381:      	jmp	0x591a45 <.text+0x190a45>
  587386:      	movl	$0x60838c, %eax         # imm = 0x60838C
  58738b:      	jmp	0x591a45 <.text+0x190a45>
  587390:      	movl	$0x608378, %eax         # imm = 0x608378
  587395:      	jmp	0x591a45 <.text+0x190a45>
  58739a:      	movl	$0x60835c, %eax         # imm = 0x60835C
  58739f:      	jmp	0x591a45 <.text+0x190a45>
  5873a4:      	movl	$0x608344, %eax         # imm = 0x608344
  5873a9:      	jmp	0x591a45 <.text+0x190a45>
  5873ae:      	movl	$0x608334, %eax         # imm = 0x608334
  5873b3:      	jmp	0x591a45 <.text+0x190a45>
  5873b8:      	movl	$0x608324, %eax         # imm = 0x608324
  5873bd:      	jmp	0x591a45 <.text+0x190a45>
  5873c2:      	movl	$0x608314, %eax         # imm = 0x608314
  5873c7:      	jmp	0x591a45 <.text+0x190a45>
  5873cc:      	movl	$0x608304, %eax         # imm = 0x608304
  5873d1:      	jmp	0x591a45 <.text+0x190a45>
  5873d6:      	movl	$0x6082ec, %eax         # imm = 0x6082EC
  5873db:      	jmp	0x591a45 <.text+0x190a45>
  5873e0:      	movl	$0x6082d8, %eax         # imm = 0x6082D8
  5873e5:      	jmp	0x591a45 <.text+0x190a45>
  5873ea:      	movl	$0x6082c4, %eax         # imm = 0x6082C4
  5873ef:      	jmp	0x591a45 <.text+0x190a45>
  5873f4:      	movl	$0x6082ac, %eax         # imm = 0x6082AC
  5873f9:      	jmp	0x591a45 <.text+0x190a45>
  5873fe:      	movl	$0x608294, %eax         # imm = 0x608294
  587403:      	jmp	0x591a45 <.text+0x190a45>
  587408:      	movl	$0x608284, %eax         # imm = 0x608284
  58740d:      	jmp	0x591a45 <.text+0x190a45>
  587412:      	movl	$0x608274, %eax         # imm = 0x608274
  587417:      	jmp	0x591a45 <.text+0x190a45>
  58741c:      	movl	$0x608268, %eax         # imm = 0x608268
  587421:      	jmp	0x591a45 <.text+0x190a45>
  587426:      	movl	$0x608254, %eax         # imm = 0x608254
  58742b:      	jmp	0x591a45 <.text+0x190a45>
  587430:      	movl	$0x608240, %eax         # imm = 0x608240
  587435:      	jmp	0x591a45 <.text+0x190a45>
  58743a:      	movl	$0x608224, %eax         # imm = 0x608224
  58743f:      	jmp	0x591a45 <.text+0x190a45>
  587444:      	movl	$0x608208, %eax         # imm = 0x608208
  587449:      	jmp	0x591a45 <.text+0x190a45>
  58744e:      	movl	$0x6081e4, %eax         # imm = 0x6081E4
  587453:      	jmp	0x591a45 <.text+0x190a45>
  587458:      	movl	$0x6081d0, %eax         # imm = 0x6081D0
  58745d:      	jmp	0x591a45 <.text+0x190a45>
  587462:      	movl	$0x6081b0, %eax         # imm = 0x6081B0
  587467:      	jmp	0x591a45 <.text+0x190a45>
  58746c:      	movl	$0x608190, %eax         # imm = 0x608190
  587471:      	jmp	0x591a45 <.text+0x190a45>
  587476:      	movl	$0x608180, %eax         # imm = 0x608180
  58747b:      	jmp	0x591a45 <.text+0x190a45>
  587480:      	movl	$0x608170, %eax         # imm = 0x608170
  587485:      	jmp	0x591a45 <.text+0x190a45>
  58748a:      	movl	$0x608158, %eax         # imm = 0x608158
  58748f:      	jmp	0x591a45 <.text+0x190a45>
  587494:      	movl	$0x608144, %eax         # imm = 0x608144
  587499:      	jmp	0x591a45 <.text+0x190a45>
  58749e:      	movl	$0x608130, %eax         # imm = 0x608130
  5874a3:      	jmp	0x591a45 <.text+0x190a45>
  5874a8:      	movl	$0x608118, %eax         # imm = 0x608118
  5874ad:      	jmp	0x591a45 <.text+0x190a45>
  5874b2:      	movl	$0x60810c, %eax         # imm = 0x60810C
  5874b7:      	jmp	0x591a45 <.text+0x190a45>
  5874bc:      	movl	$0x608100, %eax         # imm = 0x608100
  5874c1:      	jmp	0x591a45 <.text+0x190a45>
  5874c6:      	movl	$0x6080e8, %eax         # imm = 0x6080E8
  5874cb:      	jmp	0x591a45 <.text+0x190a45>
  5874d0:      	movl	$0x6080d4, %eax         # imm = 0x6080D4
  5874d5:      	jmp	0x591a45 <.text+0x190a45>
  5874da:      	movl	$0x6080c0, %eax         # imm = 0x6080C0
  5874df:      	jmp	0x591a45 <.text+0x190a45>
  5874e4:      	movl	$0x6080b4, %eax         # imm = 0x6080B4
  5874e9:      	jmp	0x591a45 <.text+0x190a45>
  5874ee:      	movl	$0x6080a4, %eax         # imm = 0x6080A4
  5874f3:      	jmp	0x591a45 <.text+0x190a45>
  5874f8:      	movl	$0x60808c, %eax         # imm = 0x60808C
  5874fd:      	jmp	0x591a45 <.text+0x190a45>
  587502:      	movl	$0x608064, %eax         # imm = 0x608064
  587507:      	jmp	0x591a45 <.text+0x190a45>
  58750c:      	movl	$0x608050, %eax         # imm = 0x608050
  587511:      	jmp	0x591a45 <.text+0x190a45>
  587516:      	movl	$0x608040, %eax         # imm = 0x608040
  58751b:      	jmp	0x591a45 <.text+0x190a45>
  587520:      	movl	$0x60802c, %eax         # imm = 0x60802C
  587525:      	jmp	0x591a45 <.text+0x190a45>
  58752a:      	movl	$0x608018, %eax         # imm = 0x608018
  58752f:      	jmp	0x591a45 <.text+0x190a45>
  587534:      	movl	$0x608008, %eax         # imm = 0x608008
  587539:      	jmp	0x591a45 <.text+0x190a45>
  58753e:      	movl	$0x607ff8, %eax         # imm = 0x607FF8
  587543:      	jmp	0x591a45 <.text+0x190a45>
  587548:      	movl	$0x607fe8, %eax         # imm = 0x607FE8
  58754d:      	jmp	0x591a45 <.text+0x190a45>
  587552:      	movl	$0x607fd4, %eax         # imm = 0x607FD4
  587557:      	jmp	0x591a45 <.text+0x190a45>
  58755c:      	movl	$0x607fbc, %eax         # imm = 0x607FBC
  587561:      	jmp	0x591a45 <.text+0x190a45>
  587566:      	movl	$0x607fa4, %eax         # imm = 0x607FA4
  58756b:      	jmp	0x591a45 <.text+0x190a45>
  587570:      	movl	$0x607f88, %eax         # imm = 0x607F88
  587575:      	jmp	0x591a45 <.text+0x190a45>
  58757a:      	movl	$0x607f74, %eax         # imm = 0x607F74
  58757f:      	jmp	0x591a45 <.text+0x190a45>
  587584:      	movl	$0x80040317, %ecx       # imm = 0x80040317
  587589:      	cmpl	%ecx, %eax
  58758b:      	jg	0x587afb <.text+0x186afb>
  587591:      	je	0x587af1 <.text+0x186af1>
  587597:      	addl	$0x7ffbfe0c, %eax       # imm = 0x7FFBFE0C
  58759c:      	cmpl	$0x111, %eax            # imm = 0x111
  5875a1:      	ja	0x591a16 <.text+0x190a16>
  5875a7:      	movzbl	0x5920dd(%eax), %eax
  5875ae:      	jmpl	*0x591ec1(,%eax,4)
  5875b5:      	movl	$0x607f64, %eax         # imm = 0x607F64
  5875ba:      	jmp	0x591a45 <.text+0x190a45>
  5875bf:      	movl	$0x607f50, %eax         # imm = 0x607F50
  5875c4:      	jmp	0x591a45 <.text+0x190a45>
  5875c9:      	movl	$0x607f3c, %eax         # imm = 0x607F3C
  5875ce:      	jmp	0x591a45 <.text+0x190a45>
  5875d3:      	movl	$0x607f2c, %eax         # imm = 0x607F2C
  5875d8:      	jmp	0x591a45 <.text+0x190a45>
  5875dd:      	movl	$0x607f18, %eax         # imm = 0x607F18
  5875e2:      	jmp	0x591a45 <.text+0x190a45>
  5875e7:      	movl	$0x607f08, %eax         # imm = 0x607F08
  5875ec:      	jmp	0x591a45 <.text+0x190a45>
  5875f1:      	movl	$0x607ef4, %eax         # imm = 0x607EF4
  5875f6:      	jmp	0x591a45 <.text+0x190a45>
  5875fb:      	movl	$0x607ee4, %eax         # imm = 0x607EE4
  587600:      	jmp	0x591a45 <.text+0x190a45>
  587605:      	movl	$0x607ed4, %eax         # imm = 0x607ED4
  58760a:      	jmp	0x591a45 <.text+0x190a45>
  58760f:      	movl	$0x607ebc, %eax         # imm = 0x607EBC
  587614:      	jmp	0x591a45 <.text+0x190a45>
  587619:      	movl	$0x607ea8, %eax         # imm = 0x607EA8
  58761e:      	jmp	0x591a45 <.text+0x190a45>
  587623:      	movl	$0x607e98, %eax         # imm = 0x607E98
  587628:      	jmp	0x591a45 <.text+0x190a45>
  58762d:      	movl	$0x607e64, %eax         # imm = 0x607E64
  587632:      	jmp	0x591a45 <.text+0x190a45>
  587637:      	movl	$0x607e20, %eax         # imm = 0x607E20
  58763c:      	jmp	0x591a45 <.text+0x190a45>
  587641:      	movl	$0x607de4, %eax         # imm = 0x607DE4
  587646:      	jmp	0x591a45 <.text+0x190a45>
  58764b:      	movl	$0x607da0, %eax         # imm = 0x607DA0
  587650:      	jmp	0x591a45 <.text+0x190a45>
  587655:      	movl	$0x607d60, %eax         # imm = 0x607D60
  58765a:      	jmp	0x591a45 <.text+0x190a45>
  58765f:      	movl	$0x607d10, %eax         # imm = 0x607D10
  587664:      	jmp	0x591a45 <.text+0x190a45>
  587669:      	movl	$0x607cd0, %eax         # imm = 0x607CD0
  58766e:      	jmp	0x591a45 <.text+0x190a45>
  587673:      	movl	$0x607ca0, %eax         # imm = 0x607CA0
  587678:      	jmp	0x591a45 <.text+0x190a45>
  58767d:      	movl	$0x607c70, %eax         # imm = 0x607C70
  587682:      	jmp	0x591a45 <.text+0x190a45>
  587687:      	movl	$0x607c48, %eax         # imm = 0x607C48
  58768c:      	jmp	0x591a45 <.text+0x190a45>
  587691:      	movl	$0x607c20, %eax         # imm = 0x607C20
  587696:      	jmp	0x591a45 <.text+0x190a45>
  58769b:      	movl	$0x607bf8, %eax         # imm = 0x607BF8
  5876a0:      	jmp	0x591a45 <.text+0x190a45>
  5876a5:      	movl	$0x607be4, %eax         # imm = 0x607BE4
  5876aa:      	jmp	0x591a45 <.text+0x190a45>
  5876af:      	movl	$0x607bd0, %eax         # imm = 0x607BD0
  5876b4:      	jmp	0x591a45 <.text+0x190a45>
  5876b9:      	movl	$0x607bbc, %eax         # imm = 0x607BBC
  5876be:      	jmp	0x591a45 <.text+0x190a45>
  5876c3:      	movl	$0x607ba8, %eax         # imm = 0x607BA8
  5876c8:      	jmp	0x591a45 <.text+0x190a45>
  5876cd:      	movl	$0x607b94, %eax         # imm = 0x607B94
  5876d2:      	jmp	0x591a45 <.text+0x190a45>
  5876d7:      	movl	$0x607b80, %eax         # imm = 0x607B80
  5876dc:      	jmp	0x591a45 <.text+0x190a45>
  5876e1:      	movl	$0x607b6c, %eax         # imm = 0x607B6C
  5876e6:      	jmp	0x591a45 <.text+0x190a45>
  5876eb:      	movl	$0x607b54, %eax         # imm = 0x607B54
  5876f0:      	jmp	0x591a45 <.text+0x190a45>
  5876f5:      	movl	$0x607b44, %eax         # imm = 0x607B44
  5876fa:      	jmp	0x591a45 <.text+0x190a45>
  5876ff:      	movl	$0x607b2c, %eax         # imm = 0x607B2C
  587704:      	jmp	0x591a45 <.text+0x190a45>
  587709:      	movl	$0x607b10, %eax         # imm = 0x607B10
  58770e:      	jmp	0x591a45 <.text+0x190a45>
  587713:      	movl	$0x607afc, %eax         # imm = 0x607AFC
  587718:      	jmp	0x591a45 <.text+0x190a45>
  58771d:      	movl	$0x607ae8, %eax         # imm = 0x607AE8
  587722:      	jmp	0x591a45 <.text+0x190a45>
  587727:      	movl	$0x607ad8, %eax         # imm = 0x607AD8
  58772c:      	jmp	0x591a45 <.text+0x190a45>
  587731:      	movl	$0x607ac8, %eax         # imm = 0x607AC8
  587736:      	jmp	0x591a45 <.text+0x190a45>
  58773b:      	movl	$0x607ab4, %eax         # imm = 0x607AB4
  587740:      	jmp	0x591a45 <.text+0x190a45>
  587745:      	movl	$0x607aa4, %eax         # imm = 0x607AA4
  58774a:      	jmp	0x591a45 <.text+0x190a45>
  58774f:      	movl	$0x607a8c, %eax         # imm = 0x607A8C
  587754:      	jmp	0x591a45 <.text+0x190a45>
  587759:      	movl	$0x607a78, %eax         # imm = 0x607A78
  58775e:      	jmp	0x591a45 <.text+0x190a45>
  587763:      	movl	$0x607a60, %eax         # imm = 0x607A60
  587768:      	jmp	0x591a45 <.text+0x190a45>
  58776d:      	movl	$0x607a48, %eax         # imm = 0x607A48
  587772:      	jmp	0x591a45 <.text+0x190a45>
  587777:      	movl	$0x607a28, %eax         # imm = 0x607A28
  58777c:      	jmp	0x591a45 <.text+0x190a45>
  587781:      	movl	$0x607a0c, %eax         # imm = 0x607A0C
  587786:      	jmp	0x591a45 <.text+0x190a45>
  58778b:      	movl	$0x6079f8, %eax         # imm = 0x6079F8
  587790:      	jmp	0x591a45 <.text+0x190a45>
  587795:      	movl	$0x6079e4, %eax         # imm = 0x6079E4
  58779a:      	jmp	0x591a45 <.text+0x190a45>
  58779f:      	movl	$0x6079c8, %eax         # imm = 0x6079C8
  5877a4:      	jmp	0x591a45 <.text+0x190a45>
  5877a9:      	movl	$0x6079ac, %eax         # imm = 0x6079AC
  5877ae:      	jmp	0x591a45 <.text+0x190a45>
  5877b3:      	movl	$0x607990, %eax         # imm = 0x607990
  5877b8:      	jmp	0x591a45 <.text+0x190a45>
  5877bd:      	movl	$0x607978, %eax         # imm = 0x607978
  5877c2:      	jmp	0x591a45 <.text+0x190a45>
  5877c7:      	movl	$0x607964, %eax         # imm = 0x607964
  5877cc:      	jmp	0x591a45 <.text+0x190a45>
  5877d1:      	movl	$0x607950, %eax         # imm = 0x607950
  5877d6:      	jmp	0x591a45 <.text+0x190a45>
  5877db:      	movl	$0x60793c, %eax         # imm = 0x60793C
  5877e0:      	jmp	0x591a45 <.text+0x190a45>
  5877e5:      	movl	$0x607928, %eax         # imm = 0x607928
  5877ea:      	jmp	0x591a45 <.text+0x190a45>
  5877ef:      	movl	$0x607914, %eax         # imm = 0x607914
  5877f4:      	jmp	0x591a45 <.text+0x190a45>
  5877f9:      	movl	$0x6078f8, %eax         # imm = 0x6078F8
  5877fe:      	jmp	0x591a45 <.text+0x190a45>
  587803:      	movl	$0x6078e4, %eax         # imm = 0x6078E4
  587808:      	jmp	0x591a45 <.text+0x190a45>
  58780d:      	movl	$0x6078cc, %eax         # imm = 0x6078CC
  587812:      	jmp	0x591a45 <.text+0x190a45>
  587817:      	movl	$0x6078b4, %eax         # imm = 0x6078B4
  58781c:      	jmp	0x591a45 <.text+0x190a45>
  587821:      	movl	$0x607898, %eax         # imm = 0x607898
  587826:      	jmp	0x591a45 <.text+0x190a45>
  58782b:      	movl	$0x607880, %eax         # imm = 0x607880
  587830:      	jmp	0x591a45 <.text+0x190a45>
  587835:      	movl	$0x607870, %eax         # imm = 0x607870
  58783a:      	jmp	0x591a45 <.text+0x190a45>
  58783f:      	movl	$0x607854, %eax         # imm = 0x607854
  587844:      	jmp	0x591a45 <.text+0x190a45>
  587849:      	movl	$0x60783c, %eax         # imm = 0x60783C
  58784e:      	jmp	0x591a45 <.text+0x190a45>
  587853:      	movl	$0x607824, %eax         # imm = 0x607824
  587858:      	jmp	0x591a45 <.text+0x190a45>
  58785d:      	movl	$0x607808, %eax         # imm = 0x607808
  587862:      	jmp	0x591a45 <.text+0x190a45>
  587867:      	movl	$0x6077ec, %eax         # imm = 0x6077EC
  58786c:      	jmp	0x591a45 <.text+0x190a45>
  587871:      	movl	$0x6077d4, %eax         # imm = 0x6077D4
  587876:      	jmp	0x591a45 <.text+0x190a45>
  58787b:      	movl	$0x6077b8, %eax         # imm = 0x6077B8
  587880:      	jmp	0x591a45 <.text+0x190a45>
  587885:      	movl	$0x60779c, %eax         # imm = 0x60779C
  58788a:      	jmp	0x591a45 <.text+0x190a45>
  58788f:      	movl	$0x607780, %eax         # imm = 0x607780
  587894:      	jmp	0x591a45 <.text+0x190a45>
  587899:      	movl	$0x60776c, %eax         # imm = 0x60776C
  58789e:      	jmp	0x591a45 <.text+0x190a45>
  5878a3:      	movl	$0x607758, %eax         # imm = 0x607758
  5878a8:      	jmp	0x591a45 <.text+0x190a45>
  5878ad:      	movl	$0x60773c, %eax         # imm = 0x60773C
  5878b2:      	jmp	0x591a45 <.text+0x190a45>
  5878b7:      	movl	$0x607724, %eax         # imm = 0x607724
  5878bc:      	jmp	0x591a45 <.text+0x190a45>
  5878c1:      	movl	$0x607704, %eax         # imm = 0x607704
  5878c6:      	jmp	0x591a45 <.text+0x190a45>
  5878cb:      	movl	$0x6076ec, %eax         # imm = 0x6076EC
  5878d0:      	jmp	0x591a45 <.text+0x190a45>
  5878d5:      	movl	$0x6076d0, %eax         # imm = 0x6076D0
  5878da:      	jmp	0x591a45 <.text+0x190a45>
  5878df:      	movl	$0x6076bc, %eax         # imm = 0x6076BC
  5878e4:      	jmp	0x591a45 <.text+0x190a45>
  5878e9:      	movl	$0x6076a0, %eax         # imm = 0x6076A0
  5878ee:      	jmp	0x591a45 <.text+0x190a45>
  5878f3:      	movl	$0x607684, %eax         # imm = 0x607684
  5878f8:      	jmp	0x591a45 <.text+0x190a45>
  5878fd:      	movl	$0x607668, %eax         # imm = 0x607668
  587902:      	jmp	0x591a45 <.text+0x190a45>
  587907:      	movl	$0x60764c, %eax         # imm = 0x60764C
  58790c:      	jmp	0x591a45 <.text+0x190a45>
  587911:      	movl	$0x607638, %eax         # imm = 0x607638
  587916:      	jmp	0x591a45 <.text+0x190a45>
  58791b:      	movl	$0x607620, %eax         # imm = 0x607620
  587920:      	jmp	0x591a45 <.text+0x190a45>
  587925:      	movl	$0x607608, %eax         # imm = 0x607608
  58792a:      	jmp	0x591a45 <.text+0x190a45>
  58792f:      	movl	$0x6075fc, %eax         # imm = 0x6075FC
  587934:      	jmp	0x591a45 <.text+0x190a45>
  587939:      	movl	$0x6075dc, %eax         # imm = 0x6075DC
  58793e:      	jmp	0x591a45 <.text+0x190a45>
  587943:      	movl	$0x6075c4, %eax         # imm = 0x6075C4
  587948:      	jmp	0x591a45 <.text+0x190a45>
  58794d:      	movl	$0x6075ac, %eax         # imm = 0x6075AC
  587952:      	jmp	0x591a45 <.text+0x190a45>
  587957:      	movl	$0x607590, %eax         # imm = 0x607590
  58795c:      	jmp	0x591a45 <.text+0x190a45>
  587961:      	movl	$0x60757c, %eax         # imm = 0x60757C
  587966:      	jmp	0x591a45 <.text+0x190a45>
  58796b:      	movl	$0x607564, %eax         # imm = 0x607564
  587970:      	jmp	0x591a45 <.text+0x190a45>
  587975:      	movl	$0x607554, %eax         # imm = 0x607554
  58797a:      	jmp	0x591a45 <.text+0x190a45>
  58797f:      	movl	$0x60753c, %eax         # imm = 0x60753C
  587984:      	jmp	0x591a45 <.text+0x190a45>
  587989:      	movl	$0x607520, %eax         # imm = 0x607520
  58798e:      	jmp	0x591a45 <.text+0x190a45>
  587993:      	movl	$0x60750c, %eax         # imm = 0x60750C
  587998:      	jmp	0x591a45 <.text+0x190a45>
  58799d:      	movl	$0x6074f8, %eax         # imm = 0x6074F8
  5879a2:      	jmp	0x591a45 <.text+0x190a45>
  5879a7:      	movl	$0x6074dc, %eax         # imm = 0x6074DC
  5879ac:      	jmp	0x591a45 <.text+0x190a45>
  5879b1:      	movl	$0x6074c0, %eax         # imm = 0x6074C0
  5879b6:      	jmp	0x591a45 <.text+0x190a45>
  5879bb:      	movl	$0x6074a0, %eax         # imm = 0x6074A0
  5879c0:      	jmp	0x591a45 <.text+0x190a45>
  5879c5:      	movl	$0x607488, %eax         # imm = 0x607488
  5879ca:      	jmp	0x591a45 <.text+0x190a45>
  5879cf:      	movl	$0x60746c, %eax         # imm = 0x60746C
  5879d4:      	jmp	0x591a45 <.text+0x190a45>
  5879d9:      	movl	$0x60744c, %eax         # imm = 0x60744C
  5879de:      	jmp	0x591a45 <.text+0x190a45>
  5879e3:      	movl	$0x607434, %eax         # imm = 0x607434
  5879e8:      	jmp	0x591a45 <.text+0x190a45>
  5879ed:      	movl	$0x607420, %eax         # imm = 0x607420
  5879f2:      	jmp	0x591a45 <.text+0x190a45>
  5879f7:      	movl	$0x607408, %eax         # imm = 0x607408
  5879fc:      	jmp	0x591a45 <.text+0x190a45>
  587a01:      	movl	$0x6073f0, %eax         # imm = 0x6073F0
  587a06:      	jmp	0x591a45 <.text+0x190a45>
  587a0b:      	movl	$0x6073d8, %eax         # imm = 0x6073D8
  587a10:      	jmp	0x591a45 <.text+0x190a45>
  587a15:      	movl	$0x6073b4, %eax         # imm = 0x6073B4
  587a1a:      	jmp	0x591a45 <.text+0x190a45>
  587a1f:      	movl	$0x60739c, %eax         # imm = 0x60739C
  587a24:      	jmp	0x591a45 <.text+0x190a45>
  587a29:      	movl	$0x607388, %eax         # imm = 0x607388
  587a2e:      	jmp	0x591a45 <.text+0x190a45>
  587a33:      	movl	$0x607370, %eax         # imm = 0x607370
  587a38:      	jmp	0x591a45 <.text+0x190a45>
  587a3d:      	movl	$0x607350, %eax         # imm = 0x607350
  587a42:      	jmp	0x591a45 <.text+0x190a45>
  587a47:      	movl	$0x607338, %eax         # imm = 0x607338
  587a4c:      	jmp	0x591a45 <.text+0x190a45>
  587a51:      	movl	$0x607318, %eax         # imm = 0x607318
  587a56:      	jmp	0x591a45 <.text+0x190a45>
  587a5b:      	movl	$0x607300, %eax         # imm = 0x607300
  587a60:      	jmp	0x591a45 <.text+0x190a45>
  587a65:      	movl	$0x6072e4, %eax         # imm = 0x6072E4
  587a6a:      	jmp	0x591a45 <.text+0x190a45>
  587a6f:      	movl	$0x6072c4, %eax         # imm = 0x6072C4
  587a74:      	jmp	0x591a45 <.text+0x190a45>
  587a79:      	movl	$0x6072ac, %eax         # imm = 0x6072AC
  587a7e:      	jmp	0x591a45 <.text+0x190a45>
  587a83:      	movl	$0x607294, %eax         # imm = 0x607294
  587a88:      	jmp	0x591a45 <.text+0x190a45>
  587a8d:      	movl	$0x607274, %eax         # imm = 0x607274
  587a92:      	jmp	0x591a45 <.text+0x190a45>
  587a97:      	movl	$0x607254, %eax         # imm = 0x607254
  587a9c:      	jmp	0x591a45 <.text+0x190a45>
  587aa1:      	movl	$0x607234, %eax         # imm = 0x607234
  587aa6:      	jmp	0x591a45 <.text+0x190a45>
  587aab:      	movl	$0x607218, %eax         # imm = 0x607218
  587ab0:      	jmp	0x591a45 <.text+0x190a45>
  587ab5:      	movl	$0x607200, %eax         # imm = 0x607200
  587aba:      	jmp	0x591a45 <.text+0x190a45>
  587abf:      	movl	$0x6071e8, %eax         # imm = 0x6071E8
  587ac4:      	jmp	0x591a45 <.text+0x190a45>
  587ac9:      	movl	$0x6071c8, %eax         # imm = 0x6071C8
  587ace:      	jmp	0x591a45 <.text+0x190a45>
  587ad3:      	movl	$0x60719c, %eax         # imm = 0x60719C
  587ad8:      	jmp	0x591a45 <.text+0x190a45>
  587add:      	movl	$0x607180, %eax         # imm = 0x607180
  587ae2:      	jmp	0x591a45 <.text+0x190a45>
  587ae7:      	movl	$0x607164, %eax         # imm = 0x607164
  587aec:      	jmp	0x591a45 <.text+0x190a45>
  587af1:      	movl	$0x607150, %eax         # imm = 0x607150
  587af6:      	jmp	0x591a45 <.text+0x190a45>
  587afb:      	movl	$0x80041053, %ecx       # imm = 0x80041053
  587b00:      	cmpl	%ecx, %eax
  587b02:      	jg	0x587f97 <.text+0x186f97>
  587b08:      	je	0x587f8d <.text+0x186f8d>
  587b0e:      	addl	$-0x38, %ecx
  587b11:      	cmpl	%ecx, %eax
  587b13:      	jg	0x587d8e <.text+0x186d8e>
  587b19:      	je	0x587d84 <.text+0x186d84>
  587b1f:      	movl	$0x80041002, %ecx       # imm = 0x80041002
  587b24:      	cmpl	%ecx, %eax
  587b26:      	jg	0x587c7f <.text+0x186c7f>
  587b2c:      	je	0x587c75 <.text+0x186c75>
  587b32:      	movl	$0x8004040a, %ecx       # imm = 0x8004040A
  587b37:      	cmpl	%ecx, %eax
  587b39:      	jg	0x587be3 <.text+0x186be3>
  587b3f:      	je	0x587bd9 <.text+0x186bd9>
  587b45:      	addl	$0x7ffbfc0e, %eax       # imm = 0x7FFBFC0E
  587b4a:      	cmpl	$0x17, %eax
  587b4d:      	ja	0x591a16 <.text+0x190a16>
  587b53:      	movzbl	0x592225(%eax), %eax
  587b5a:      	jmpl	*0x5921f1(,%eax,4)
  587b61:      	movl	$0x60713c, %eax         # imm = 0x60713C
  587b66:      	jmp	0x591a45 <.text+0x190a45>
  587b6b:      	movl	$0x607120, %eax         # imm = 0x607120
  587b70:      	jmp	0x591a45 <.text+0x190a45>
  587b75:      	movl	$0x6070fc, %eax         # imm = 0x6070FC
  587b7a:      	jmp	0x591a45 <.text+0x190a45>
  587b7f:      	movl	$0x6070ec, %eax         # imm = 0x6070EC
  587b84:      	jmp	0x591a45 <.text+0x190a45>
  587b89:      	movl	$0x6070dc, %eax         # imm = 0x6070DC
  587b8e:      	jmp	0x591a45 <.text+0x190a45>
  587b93:      	movl	$0x6070cc, %eax         # imm = 0x6070CC
  587b98:      	jmp	0x591a45 <.text+0x190a45>
  587b9d:      	movl	$0x6070bc, %eax         # imm = 0x6070BC
  587ba2:      	jmp	0x591a45 <.text+0x190a45>
  587ba7:      	movl	$0x6070a8, %eax         # imm = 0x6070A8
  587bac:      	jmp	0x591a45 <.text+0x190a45>
  587bb1:      	movl	$0x60709c, %eax         # imm = 0x60709C
  587bb6:      	jmp	0x591a45 <.text+0x190a45>
  587bbb:      	movl	$0x60708c, %eax         # imm = 0x60708C
  587bc0:      	jmp	0x591a45 <.text+0x190a45>
  587bc5:      	movl	$0x607070, %eax         # imm = 0x607070
  587bca:      	jmp	0x591a45 <.text+0x190a45>
  587bcf:      	movl	$0x607058, %eax         # imm = 0x607058
  587bd4:      	jmp	0x591a45 <.text+0x190a45>
  587bd9:      	movl	$0x607048, %eax         # imm = 0x607048
  587bde:      	jmp	0x591a45 <.text+0x190a45>
  587be3:      	movl	$0x80041001, %ecx       # imm = 0x80041001
  587be8:      	cmpl	%ecx, %eax
  587bea:      	jg	0x591a16 <.text+0x190a16>
  587bf0:      	je	0x587c6b <.text+0x186c6b>
  587bf2:      	addl	$0x7ffbf6ff, %eax       # imm = 0x7FFBF6FF
  587bf7:      	cmpl	$0x9, %eax
  587bfa:      	ja	0x591a16 <.text+0x190a16>
  587c00:      	jmpl	*0x59223d(,%eax,4)
  587c07:      	movl	$0x607034, %eax         # imm = 0x607034
  587c0c:      	jmp	0x591a45 <.text+0x190a45>
  587c11:      	movl	$0x607018, %eax         # imm = 0x607018
  587c16:      	jmp	0x591a45 <.text+0x190a45>
  587c1b:      	movl	$0x607000, %eax         # imm = 0x607000
  587c20:      	jmp	0x591a45 <.text+0x190a45>
  587c25:      	movl	$0x606fe8, %eax         # imm = 0x606FE8
  587c2a:      	jmp	0x591a45 <.text+0x190a45>
  587c2f:      	movl	$0x606fd0, %eax         # imm = 0x606FD0
  587c34:      	jmp	0x591a45 <.text+0x190a45>
  587c39:      	movl	$0x606fb8, %eax         # imm = 0x606FB8
  587c3e:      	jmp	0x591a45 <.text+0x190a45>
  587c43:      	movl	$0x606f98, %eax         # imm = 0x606F98
  587c48:      	jmp	0x591a45 <.text+0x190a45>
  587c4d:      	movl	$0x606f78, %eax         # imm = 0x606F78
  587c52:      	jmp	0x591a45 <.text+0x190a45>
  587c57:      	movl	$0x606f5c, %eax         # imm = 0x606F5C
  587c5c:      	jmp	0x591a45 <.text+0x190a45>
  587c61:      	movl	$0x606f44, %eax         # imm = 0x606F44
  587c66:      	jmp	0x591a45 <.text+0x190a45>
  587c6b:      	movl	$0x606f34, %eax         # imm = 0x606F34
  587c70:      	jmp	0x591a45 <.text+0x190a45>
  587c75:      	movl	$0x606f20, %eax         # imm = 0x606F20
  587c7a:      	jmp	0x591a45 <.text+0x190a45>
  587c7f:      	addl	$0x7ffbeffd, %eax       # imm = 0x7FFBEFFD
  587c84:      	cmpl	$0x17, %eax
  587c87:      	ja	0x591a16 <.text+0x190a16>
  587c8d:      	jmpl	*0x592265(,%eax,4)
  587c94:      	movl	$0x606f08, %eax         # imm = 0x606F08
  587c99:      	jmp	0x591a45 <.text+0x190a45>
  587c9e:      	movl	$0x606ef0, %eax         # imm = 0x606EF0
  587ca3:      	jmp	0x591a45 <.text+0x190a45>
  587ca8:      	movl	$0x606ed8, %eax         # imm = 0x606ED8
  587cad:      	jmp	0x591a45 <.text+0x190a45>
  587cb2:      	movl	$0x606ec0, %eax         # imm = 0x606EC0
  587cb7:      	jmp	0x591a45 <.text+0x190a45>
  587cbc:      	movl	$0x606ea8, %eax         # imm = 0x606EA8
  587cc1:      	jmp	0x591a45 <.text+0x190a45>
  587cc6:      	movl	$0x606e8c, %eax         # imm = 0x606E8C
  587ccb:      	jmp	0x591a45 <.text+0x190a45>
  587cd0:      	movl	$0x606e74, %eax         # imm = 0x606E74
  587cd5:      	jmp	0x591a45 <.text+0x190a45>
  587cda:      	movl	$0x606e5c, %eax         # imm = 0x606E5C
  587cdf:      	jmp	0x591a45 <.text+0x190a45>
  587ce4:      	movl	$0x606e44, %eax         # imm = 0x606E44
  587ce9:      	jmp	0x591a45 <.text+0x190a45>
  587cee:      	movl	$0x606e2c, %eax         # imm = 0x606E2C
  587cf3:      	jmp	0x591a45 <.text+0x190a45>
  587cf8:      	movl	$0x606e10, %eax         # imm = 0x606E10
  587cfd:      	jmp	0x591a45 <.text+0x190a45>
  587d02:      	movl	$0x606df4, %eax         # imm = 0x606DF4
  587d07:      	jmp	0x591a45 <.text+0x190a45>
  587d0c:      	movl	$0x606ddc, %eax         # imm = 0x606DDC
  587d11:      	jmp	0x591a45 <.text+0x190a45>
  587d16:      	movl	$0x606dc4, %eax         # imm = 0x606DC4
  587d1b:      	jmp	0x591a45 <.text+0x190a45>
  587d20:      	movl	$0x606da8, %eax         # imm = 0x606DA8
  587d25:      	jmp	0x591a45 <.text+0x190a45>
  587d2a:      	movl	$0x606d80, %eax         # imm = 0x606D80
  587d2f:      	jmp	0x591a45 <.text+0x190a45>
  587d34:      	movl	$0x606d60, %eax         # imm = 0x606D60
  587d39:      	jmp	0x591a45 <.text+0x190a45>
  587d3e:      	movl	$0x606d40, %eax         # imm = 0x606D40
  587d43:      	jmp	0x591a45 <.text+0x190a45>
  587d48:      	movl	$0x606d24, %eax         # imm = 0x606D24
  587d4d:      	jmp	0x591a45 <.text+0x190a45>
  587d52:      	movl	$0x606d08, %eax         # imm = 0x606D08
  587d57:      	jmp	0x591a45 <.text+0x190a45>
  587d5c:      	movl	$0x606cf0, %eax         # imm = 0x606CF0
  587d61:      	jmp	0x591a45 <.text+0x190a45>
  587d66:      	movl	$0x606cd4, %eax         # imm = 0x606CD4
  587d6b:      	jmp	0x591a45 <.text+0x190a45>
  587d70:      	movl	$0x606cbc, %eax         # imm = 0x606CBC
  587d75:      	jmp	0x591a45 <.text+0x190a45>
  587d7a:      	movl	$0x606ca0, %eax         # imm = 0x606CA0
  587d7f:      	jmp	0x591a45 <.text+0x190a45>
  587d84:      	movl	$0x606c84, %eax         # imm = 0x606C84
  587d89:      	jmp	0x591a45 <.text+0x190a45>
  587d8e:      	addl	$0x7ffbefe4, %eax       # imm = 0x7FFBEFE4
  587d93:      	cmpl	$0x36, %eax
  587d96:      	ja	0x591a16 <.text+0x190a16>
  587d9c:      	jmpl	*0x5922c5(,%eax,4)
  587da3:      	movl	$0x606c68, %eax         # imm = 0x606C68
  587da8:      	jmp	0x591a45 <.text+0x190a45>
  587dad:      	movl	$0x606c54, %eax         # imm = 0x606C54
  587db2:      	jmp	0x591a45 <.text+0x190a45>
  587db7:      	movl	$0x606c38, %eax         # imm = 0x606C38
  587dbc:      	jmp	0x591a45 <.text+0x190a45>
  587dc1:      	movl	$0x606c20, %eax         # imm = 0x606C20
  587dc6:      	jmp	0x591a45 <.text+0x190a45>
  587dcb:      	movl	$0x606c08, %eax         # imm = 0x606C08
  587dd0:      	jmp	0x591a45 <.text+0x190a45>
  587dd5:      	movl	$0x606bf0, %eax         # imm = 0x606BF0
  587dda:      	jmp	0x591a45 <.text+0x190a45>
  587ddf:      	movl	$0x606bd4, %eax         # imm = 0x606BD4
  587de4:      	jmp	0x591a45 <.text+0x190a45>
  587de9:      	movl	$0x606bc0, %eax         # imm = 0x606BC0
  587dee:      	jmp	0x591a45 <.text+0x190a45>
  587df3:      	movl	$0x606ba4, %eax         # imm = 0x606BA4
  587df8:      	jmp	0x591a45 <.text+0x190a45>
  587dfd:      	movl	$0x606b88, %eax         # imm = 0x606B88
  587e02:      	jmp	0x591a45 <.text+0x190a45>
  587e07:      	movl	$0x606b6c, %eax         # imm = 0x606B6C
  587e0c:      	jmp	0x591a45 <.text+0x190a45>
  587e11:      	movl	$0x606b4c, %eax         # imm = 0x606B4C
  587e16:      	jmp	0x591a45 <.text+0x190a45>
  587e1b:      	movl	$0x606b38, %eax         # imm = 0x606B38
  587e20:      	jmp	0x591a45 <.text+0x190a45>
  587e25:      	movl	$0x606b18, %eax         # imm = 0x606B18
  587e2a:      	jmp	0x591a45 <.text+0x190a45>
  587e2f:      	movl	$0x606af8, %eax         # imm = 0x606AF8
  587e34:      	jmp	0x591a45 <.text+0x190a45>
  587e39:      	movl	$0x606adc, %eax         # imm = 0x606ADC
  587e3e:      	jmp	0x591a45 <.text+0x190a45>
  587e43:      	movl	$0x606ac0, %eax         # imm = 0x606AC0
  587e48:      	jmp	0x591a45 <.text+0x190a45>
  587e4d:      	movl	$0x606aa8, %eax         # imm = 0x606AA8
  587e52:      	jmp	0x591a45 <.text+0x190a45>
  587e57:      	movl	$0x606a90, %eax         # imm = 0x606A90
  587e5c:      	jmp	0x591a45 <.text+0x190a45>
  587e61:      	movl	$0x606a6c, %eax         # imm = 0x606A6C
  587e66:      	jmp	0x591a45 <.text+0x190a45>
  587e6b:      	movl	$0x606a54, %eax         # imm = 0x606A54
  587e70:      	jmp	0x591a45 <.text+0x190a45>
  587e75:      	movl	$0x606a3c, %eax         # imm = 0x606A3C
  587e7a:      	jmp	0x591a45 <.text+0x190a45>
  587e7f:      	movl	$0x606a24, %eax         # imm = 0x606A24
  587e84:      	jmp	0x591a45 <.text+0x190a45>
  587e89:      	movl	$0x606a0c, %eax         # imm = 0x606A0C
  587e8e:      	jmp	0x591a45 <.text+0x190a45>
  587e93:      	movl	$0x6069f0, %eax         # imm = 0x6069F0
  587e98:      	jmp	0x591a45 <.text+0x190a45>
  587e9d:      	movl	$0x6069d0, %eax         # imm = 0x6069D0
  587ea2:      	jmp	0x591a45 <.text+0x190a45>
  587ea7:      	movl	$0x6069b4, %eax         # imm = 0x6069B4
  587eac:      	jmp	0x591a45 <.text+0x190a45>
  587eb1:      	movl	$0x606998, %eax         # imm = 0x606998
  587eb6:      	jmp	0x591a45 <.text+0x190a45>
  587ebb:      	movl	$0x606974, %eax         # imm = 0x606974
  587ec0:      	jmp	0x591a45 <.text+0x190a45>
  587ec5:      	movl	$0x606954, %eax         # imm = 0x606954
  587eca:      	jmp	0x591a45 <.text+0x190a45>
  587ecf:      	movl	$0x606938, %eax         # imm = 0x606938
  587ed4:      	jmp	0x591a45 <.text+0x190a45>
  587ed9:      	movl	$0x60691c, %eax         # imm = 0x60691C
  587ede:      	jmp	0x591a45 <.text+0x190a45>
  587ee3:      	movl	$0x606904, %eax         # imm = 0x606904
  587ee8:      	jmp	0x591a45 <.text+0x190a45>
  587eed:      	movl	$0x6068e0, %eax         # imm = 0x6068E0
  587ef2:      	jmp	0x591a45 <.text+0x190a45>
  587ef7:      	movl	$0x6068c4, %eax         # imm = 0x6068C4
  587efc:      	jmp	0x591a45 <.text+0x190a45>
  587f01:      	movl	$0x6068a8, %eax         # imm = 0x6068A8
  587f06:      	jmp	0x591a45 <.text+0x190a45>
  587f0b:      	movl	$0x606888, %eax         # imm = 0x606888
  587f10:      	jmp	0x591a45 <.text+0x190a45>
  587f15:      	movl	$0x606864, %eax         # imm = 0x606864
  587f1a:      	jmp	0x591a45 <.text+0x190a45>
  587f1f:      	movl	$0x606848, %eax         # imm = 0x606848
  587f24:      	jmp	0x591a45 <.text+0x190a45>
  587f29:      	movl	$0x606824, %eax         # imm = 0x606824
  587f2e:      	jmp	0x591a45 <.text+0x190a45>
  587f33:      	movl	$0x60680c, %eax         # imm = 0x60680C
  587f38:      	jmp	0x591a45 <.text+0x190a45>
  587f3d:      	movl	$0x6067f4, %eax         # imm = 0x6067F4
  587f42:      	jmp	0x591a45 <.text+0x190a45>
  587f47:      	movl	$0x6067dc, %eax         # imm = 0x6067DC
  587f4c:      	jmp	0x591a45 <.text+0x190a45>
  587f51:      	movl	$0x6067c0, %eax         # imm = 0x6067C0
  587f56:      	jmp	0x591a45 <.text+0x190a45>
  587f5b:      	movl	$0x6067a0, %eax         # imm = 0x6067A0
  587f60:      	jmp	0x591a45 <.text+0x190a45>
  587f65:      	movl	$0x606778, %eax         # imm = 0x606778
  587f6a:      	jmp	0x591a45 <.text+0x190a45>
  587f6f:      	movl	$0x606750, %eax         # imm = 0x606750
  587f74:      	jmp	0x591a45 <.text+0x190a45>
  587f79:      	movl	$0x606734, %eax         # imm = 0x606734
  587f7e:      	jmp	0x591a45 <.text+0x190a45>
  587f83:      	movl	$0x606718, %eax         # imm = 0x606718
  587f88:      	jmp	0x591a45 <.text+0x190a45>
  587f8d:      	movl	$0x6066f4, %eax         # imm = 0x6066F4
  587f92:      	jmp	0x591a45 <.text+0x190a45>
  587f97:      	movl	$0x80041309, %ecx       # imm = 0x80041309
  587f9c:      	cmpl	%ecx, %eax
  587f9e:      	jg	0x5881b3 <.text+0x1871b3>
  587fa4:      	je	0x5881a9 <.text+0x1871a9>
  587faa:      	addl	$0x7ffbefac, %eax       # imm = 0x7FFBEFAC
  587faf:      	cmpl	$0x36, %eax
  587fb2:      	ja	0x591a16 <.text+0x190a16>
  587fb8:      	jmpl	*0x5923a1(,%eax,4)
  587fbf:      	movl	$0x6066d4, %eax         # imm = 0x6066D4
  587fc4:      	jmp	0x591a45 <.text+0x190a45>
  587fc9:      	movl	$0x6066b4, %eax         # imm = 0x6066B4
  587fce:      	jmp	0x591a45 <.text+0x190a45>
  587fd3:      	movl	$0x60669c, %eax         # imm = 0x60669C
  587fd8:      	jmp	0x591a45 <.text+0x190a45>
  587fdd:      	movl	$0x606684, %eax         # imm = 0x606684
  587fe2:      	jmp	0x591a45 <.text+0x190a45>
  587fe7:      	movl	$0x60666c, %eax         # imm = 0x60666C
  587fec:      	jmp	0x591a45 <.text+0x190a45>
  587ff1:      	movl	$0x606654, %eax         # imm = 0x606654
  587ff6:      	jmp	0x591a45 <.text+0x190a45>
  587ffb:      	movl	$0x606638, %eax         # imm = 0x606638
  588000:      	jmp	0x591a45 <.text+0x190a45>
  588005:      	movl	$0x606618, %eax         # imm = 0x606618
  58800a:      	jmp	0x591a45 <.text+0x190a45>
  58800f:      	movl	$0x6065f8, %eax         # imm = 0x6065F8
  588014:      	jmp	0x591a45 <.text+0x190a45>
  588019:      	movl	$0x6065d8, %eax         # imm = 0x6065D8
  58801e:      	jmp	0x591a45 <.text+0x190a45>
  588023:      	movl	$0x6065b0, %eax         # imm = 0x6065B0
  588028:      	jmp	0x591a45 <.text+0x190a45>
  58802d:      	movl	$0x606588, %eax         # imm = 0x606588
  588032:      	jmp	0x591a45 <.text+0x190a45>
  588037:      	movl	$0x606570, %eax         # imm = 0x606570
  58803c:      	jmp	0x591a45 <.text+0x190a45>
  588041:      	movl	$0x606554, %eax         # imm = 0x606554
  588046:      	jmp	0x591a45 <.text+0x190a45>
  58804b:      	movl	$0x60653c, %eax         # imm = 0x60653C
  588050:      	jmp	0x591a45 <.text+0x190a45>
  588055:      	movl	$0x606520, %eax         # imm = 0x606520
  58805a:      	jmp	0x591a45 <.text+0x190a45>
  58805f:      	movl	$0x606504, %eax         # imm = 0x606504
  588064:      	jmp	0x591a45 <.text+0x190a45>
  588069:      	movl	$0x6064ec, %eax         # imm = 0x6064EC
  58806e:      	jmp	0x591a45 <.text+0x190a45>
  588073:      	movl	$0x6064d4, %eax         # imm = 0x6064D4
  588078:      	jmp	0x591a45 <.text+0x190a45>
  58807d:      	movl	$0x6064b4, %eax         # imm = 0x6064B4
  588082:      	jmp	0x591a45 <.text+0x190a45>
  588087:      	movl	$0x6064a0, %eax         # imm = 0x6064A0
  58808c:      	jmp	0x591a45 <.text+0x190a45>
  588091:      	movl	$0x606484, %eax         # imm = 0x606484
  588096:      	jmp	0x591a45 <.text+0x190a45>
  58809b:      	movl	$0x606468, %eax         # imm = 0x606468
  5880a0:      	jmp	0x591a45 <.text+0x190a45>
  5880a5:      	movl	$0x606450, %eax         # imm = 0x606450
  5880aa:      	jmp	0x591a45 <.text+0x190a45>
  5880af:      	movl	$0x60643c, %eax         # imm = 0x60643C
  5880b4:      	jmp	0x591a45 <.text+0x190a45>
  5880b9:      	movl	$0x606428, %eax         # imm = 0x606428
  5880be:      	jmp	0x591a45 <.text+0x190a45>
  5880c3:      	movl	$0x60640c, %eax         # imm = 0x60640C
  5880c8:      	jmp	0x591a45 <.text+0x190a45>
  5880cd:      	movl	$0x6063f0, %eax         # imm = 0x6063F0
  5880d2:      	jmp	0x591a45 <.text+0x190a45>
  5880d7:      	movl	$0x6063d4, %eax         # imm = 0x6063D4
  5880dc:      	jmp	0x591a45 <.text+0x190a45>
  5880e1:      	movl	$0x6063b4, %eax         # imm = 0x6063B4
  5880e6:      	jmp	0x591a45 <.text+0x190a45>
  5880eb:      	movl	$0x606394, %eax         # imm = 0x606394
  5880f0:      	jmp	0x591a45 <.text+0x190a45>
  5880f5:      	movl	$0x606378, %eax         # imm = 0x606378
  5880fa:      	jmp	0x591a45 <.text+0x190a45>
  5880ff:      	movl	$0x60635c, %eax         # imm = 0x60635C
  588104:      	jmp	0x591a45 <.text+0x190a45>
  588109:      	movl	$0x60633c, %eax         # imm = 0x60633C
  58810e:      	jmp	0x591a45 <.text+0x190a45>
  588113:      	movl	$0x606324, %eax         # imm = 0x606324
  588118:      	jmp	0x591a45 <.text+0x190a45>
  58811d:      	movl	$0x606304, %eax         # imm = 0x606304
  588122:      	jmp	0x591a45 <.text+0x190a45>
  588127:      	movl	$0x6062f0, %eax         # imm = 0x6062F0
  58812c:      	jmp	0x591a45 <.text+0x190a45>
  588131:      	movl	$0x6062e0, %eax         # imm = 0x6062E0
  588136:      	jmp	0x591a45 <.text+0x190a45>
  58813b:      	movl	$0x6062c8, %eax         # imm = 0x6062C8
  588140:      	jmp	0x591a45 <.text+0x190a45>
  588145:      	movl	$0x6062ac, %eax         # imm = 0x6062AC
  58814a:      	jmp	0x591a45 <.text+0x190a45>
  58814f:      	movl	$0x60628c, %eax         # imm = 0x60628C
  588154:      	jmp	0x591a45 <.text+0x190a45>
  588159:      	movl	$0x606278, %eax         # imm = 0x606278
  58815e:      	jmp	0x591a45 <.text+0x190a45>
  588163:      	movl	$0x606254, %eax         # imm = 0x606254
  588168:      	jmp	0x591a45 <.text+0x190a45>
  58816d:      	movl	$0x606234, %eax         # imm = 0x606234
  588172:      	jmp	0x591a45 <.text+0x190a45>
  588177:      	movl	$0x606214, %eax         # imm = 0x606214
  58817c:      	jmp	0x591a45 <.text+0x190a45>
  588181:      	movl	$0x6061ec, %eax         # imm = 0x6061EC
  588186:      	jmp	0x591a45 <.text+0x190a45>
  58818b:      	movl	$0x6061d0, %eax         # imm = 0x6061D0
  588190:      	jmp	0x591a45 <.text+0x190a45>
  588195:      	movl	$0x6061c0, %eax         # imm = 0x6061C0
  58819a:      	jmp	0x591a45 <.text+0x190a45>
  58819f:      	movl	$0x6061a4, %eax         # imm = 0x6061A4
  5881a4:      	jmp	0x591a45 <.text+0x190a45>
  5881a9:      	movl	$0x606188, %eax         # imm = 0x606188
  5881ae:      	jmp	0x591a45 <.text+0x190a45>
  5881b3:      	movl	$0x80042001, %ecx       # imm = 0x80042001
  5881b8:      	cmpl	%ecx, %eax
  5881ba:      	jg	0x58825d <.text+0x18725d>
  5881c0:      	je	0x588253 <.text+0x187253>
  5881c6:      	addl	$0x7ffbecf6, %eax       # imm = 0x7FFBECF6
  5881cb:      	cmpl	$0xb, %eax
  5881ce:      	ja	0x591a16 <.text+0x190a16>
  5881d4:      	jmpl	*0x59247d(,%eax,4)
  5881db:      	movl	$0x606170, %eax         # imm = 0x606170
  5881e0:      	jmp	0x591a45 <.text+0x190a45>
  5881e5:      	movl	$0x606154, %eax         # imm = 0x606154
  5881ea:      	jmp	0x591a45 <.text+0x190a45>
  5881ef:      	movl	$0x606134, %eax         # imm = 0x606134
  5881f4:      	jmp	0x591a45 <.text+0x190a45>
  5881f9:      	movl	$0x606118, %eax         # imm = 0x606118
  5881fe:      	jmp	0x591a45 <.text+0x190a45>
  588203:      	movl	$0x606100, %eax         # imm = 0x606100
  588208:      	jmp	0x591a45 <.text+0x190a45>
  58820d:      	movl	$0x6060dc, %eax         # imm = 0x6060DC
  588212:      	jmp	0x591a45 <.text+0x190a45>
  588217:      	movl	$0x6060bc, %eax         # imm = 0x6060BC
  58821c:      	jmp	0x591a45 <.text+0x190a45>
  588221:      	movl	$0x60609c, %eax         # imm = 0x60609C
  588226:      	jmp	0x591a45 <.text+0x190a45>
  58822b:      	movl	$0x60607c, %eax         # imm = 0x60607C
  588230:      	jmp	0x591a45 <.text+0x190a45>
  588235:      	movl	$0x60605c, %eax         # imm = 0x60605C
  58823a:      	jmp	0x591a45 <.text+0x190a45>
  58823f:      	movl	$0x606038, %eax         # imm = 0x606038
  588244:      	jmp	0x591a45 <.text+0x190a45>
  588249:      	movl	$0x60601c, %eax         # imm = 0x60601C
  58824e:      	jmp	0x591a45 <.text+0x190a45>
  588253:      	movl	$0x605ff8, %eax         # imm = 0x605FF8
  588258:      	jmp	0x591a45 <.text+0x190a45>
  58825d:      	movl	$0x80044011, %ecx       # imm = 0x80044011
  588262:      	cmpl	%ecx, %eax
  588264:      	jg	0x58838e <.text+0x18738e>
  58826a:      	je	0x588384 <.text+0x187384>
  588270:      	addl	$-0x9, %ecx
  588273:      	cmpl	%ecx, %eax
  588275:      	jg	0x58831f <.text+0x18731f>
  58827b:      	je	0x588315 <.text+0x187315>
  588281:      	movl	$0x80044004, %ecx       # imm = 0x80044004
  588286:      	cmpl	%ecx, %eax
  588288:      	jg	0x5882de <.text+0x1872de>
  58828a:      	je	0x5882d4 <.text+0x1872d4>
  58828c:      	cmpl	$0x80042002, %eax       # imm = 0x80042002
  588291:      	je	0x5882ca <.text+0x1872ca>
  588293:      	cmpl	$0x80044001, %eax       # imm = 0x80044001
  588298:      	je	0x5882c0 <.text+0x1872c0>
  58829a:      	cmpl	$0x80044002, %eax       # imm = 0x80044002
  58829f:      	je	0x5882b6 <.text+0x1872b6>
  5882a1:      	cmpl	$0x80044003, %eax       # imm = 0x80044003
  5882a6:      	jne	0x591a16 <.text+0x190a16>
  5882ac:      	movl	$0x605fd8, %eax         # imm = 0x605FD8
  5882b1:      	jmp	0x591a45 <.text+0x190a45>
  5882b6:      	movl	$0x605fc0, %eax         # imm = 0x605FC0
  5882bb:      	jmp	0x591a45 <.text+0x190a45>
  5882c0:      	movl	$0x605f9c, %eax         # imm = 0x605F9C
  5882c5:      	jmp	0x591a45 <.text+0x190a45>
  5882ca:      	movl	$0x605f78, %eax         # imm = 0x605F78
  5882cf:      	jmp	0x591a45 <.text+0x190a45>
  5882d4:      	movl	$0x605f58, %eax         # imm = 0x605F58
  5882d9:      	jmp	0x591a45 <.text+0x190a45>
  5882de:      	cmpl	$0x80044005, %eax       # imm = 0x80044005
  5882e3:      	je	0x58830b <.text+0x18730b>
  5882e5:      	cmpl	$0x80044006, %eax       # imm = 0x80044006
  5882ea:      	je	0x588301 <.text+0x187301>
  5882ec:      	cmpl	$0x80044007, %eax       # imm = 0x80044007
  5882f1:      	jne	0x591a16 <.text+0x190a16>
  5882f7:      	movl	$0x605f34, %eax         # imm = 0x605F34
  5882fc:      	jmp	0x591a45 <.text+0x190a45>
  588301:      	movl	$0x605f14, %eax         # imm = 0x605F14
  588306:      	jmp	0x591a45 <.text+0x190a45>
  58830b:      	movl	$0x605ef0, %eax         # imm = 0x605EF0
  588310:      	jmp	0x591a45 <.text+0x190a45>
  588315:      	movl	$0x605ecc, %eax         # imm = 0x605ECC
  58831a:      	jmp	0x591a45 <.text+0x190a45>
  58831f:      	addl	$0x7ffbbff7, %eax       # imm = 0x7FFBBFF7
  588324:      	cmpl	$0x7, %eax
  588327:      	ja	0x591a16 <.text+0x190a16>
  58832d:      	jmpl	*0x5924ad(,%eax,4)
  588334:      	movl	$0x605eac, %eax         # imm = 0x605EAC
  588339:      	jmp	0x591a45 <.text+0x190a45>
  58833e:      	movl	$0x605e8c, %eax         # imm = 0x605E8C
  588343:      	jmp	0x591a45 <.text+0x190a45>
  588348:      	movl	$0x605e70, %eax         # imm = 0x605E70
  58834d:      	jmp	0x591a45 <.text+0x190a45>
  588352:      	movl	$0x605e4c, %eax         # imm = 0x605E4C
  588357:      	jmp	0x591a45 <.text+0x190a45>
  58835c:      	movl	$0x605e2c, %eax         # imm = 0x605E2C
  588361:      	jmp	0x591a45 <.text+0x190a45>
  588366:      	movl	$0x605e10, %eax         # imm = 0x605E10
  58836b:      	jmp	0x591a45 <.text+0x190a45>
  588370:      	movl	$0x605df0, %eax         # imm = 0x605DF0
  588375:      	jmp	0x591a45 <.text+0x190a45>
  58837a:      	movl	$0x605dcc, %eax         # imm = 0x605DCC
  58837f:      	jmp	0x591a45 <.text+0x190a45>
  588384:      	movl	$0x605da4, %eax         # imm = 0x605DA4
  588389:      	jmp	0x591a45 <.text+0x190a45>
  58838e:      	addl	$0x7ffbbfee, %eax       # imm = 0x7FFBBFEE
  588393:      	cmpl	$0x10, %eax
  588396:      	ja	0x591a16 <.text+0x190a16>
  58839c:      	jmpl	*0x5924cd(,%eax,4)
  5883a3:      	movl	$0x605d88, %eax         # imm = 0x605D88
  5883a8:      	jmp	0x591a45 <.text+0x190a45>
  5883ad:      	movl	$0x605d64, %eax         # imm = 0x605D64
  5883b2:      	jmp	0x591a45 <.text+0x190a45>
  5883b7:      	movl	$0x605d44, %eax         # imm = 0x605D44
  5883bc:      	jmp	0x591a45 <.text+0x190a45>
  5883c1:      	movl	$0x605d2c, %eax         # imm = 0x605D2C
  5883c6:      	jmp	0x591a45 <.text+0x190a45>
  5883cb:      	movl	$0x605d0c, %eax         # imm = 0x605D0C
  5883d0:      	jmp	0x591a45 <.text+0x190a45>
  5883d5:      	movl	$0x605ce8, %eax         # imm = 0x605CE8
  5883da:      	jmp	0x591a45 <.text+0x190a45>
  5883df:      	movl	$0x605cc0, %eax         # imm = 0x605CC0
  5883e4:      	jmp	0x591a45 <.text+0x190a45>
  5883e9:      	movl	$0x605ca4, %eax         # imm = 0x605CA4
  5883ee:      	jmp	0x591a45 <.text+0x190a45>
  5883f3:      	movl	$0x605c88, %eax         # imm = 0x605C88
  5883f8:      	jmp	0x591a45 <.text+0x190a45>
  5883fd:      	movl	$0x605c68, %eax         # imm = 0x605C68
  588402:      	jmp	0x591a45 <.text+0x190a45>
  588407:      	movl	$0x605c3c, %eax         # imm = 0x605C3C
  58840c:      	jmp	0x591a45 <.text+0x190a45>
  588411:      	movl	$0x605c24, %eax         # imm = 0x605C24
  588416:      	jmp	0x591a45 <.text+0x190a45>
  58841b:      	movl	$0x605c0c, %eax         # imm = 0x605C0C
  588420:      	jmp	0x591a45 <.text+0x190a45>
  588425:      	movl	$0x605bec, %eax         # imm = 0x605BEC
  58842a:      	jmp	0x591a45 <.text+0x190a45>
  58842f:      	movl	$0x605bd0, %eax         # imm = 0x605BD0
  588434:      	jmp	0x591a45 <.text+0x190a45>
  588439:      	movl	$0x605bb0, %eax         # imm = 0x605BB0
  58843e:      	jmp	0x591a45 <.text+0x190a45>
  588443:      	movl	$0x605b90, %eax         # imm = 0x605B90
  588448:      	jmp	0x591a45 <.text+0x190a45>
  58844d:      	movl	$0x605b6c, %eax         # imm = 0x605B6C
  588452:      	jmp	0x591a45 <.text+0x190a45>
  588457:      	movl	$0x8004d000, %ecx       # imm = 0x8004D000
  58845c:      	cmpl	%ecx, %eax
  58845e:      	jg	0x588515 <.text+0x187515>
  588464:      	je	0x58850b <.text+0x18750b>
  58846a:      	addl	$0x7ffbbfdc, %eax       # imm = 0x7FFBBFDC
  58846f:      	cmpl	$0xd, %eax
  588472:      	ja	0x591a16 <.text+0x190a16>
  588478:      	jmpl	*0x592511(,%eax,4)
  58847f:      	movl	$0x605b50, %eax         # imm = 0x605B50
  588484:      	jmp	0x591a45 <.text+0x190a45>
  588489:      	movl	$0x605b28, %eax         # imm = 0x605B28
  58848e:      	jmp	0x591a45 <.text+0x190a45>
  588493:      	movl	$0x605b08, %eax         # imm = 0x605B08
  588498:      	jmp	0x591a45 <.text+0x190a45>
  58849d:      	movl	$0x605aec, %eax         # imm = 0x605AEC
  5884a2:      	jmp	0x591a45 <.text+0x190a45>
  5884a7:      	movl	$0x605acc, %eax         # imm = 0x605ACC
  5884ac:      	jmp	0x591a45 <.text+0x190a45>
  5884b1:      	movl	$0x605aa4, %eax         # imm = 0x605AA4
  5884b6:      	jmp	0x591a45 <.text+0x190a45>
  5884bb:      	movl	$0x605a7c, %eax         # imm = 0x605A7C
  5884c0:      	jmp	0x591a45 <.text+0x190a45>
  5884c5:      	movl	$0x605a54, %eax         # imm = 0x605A54
  5884ca:      	jmp	0x591a45 <.text+0x190a45>
  5884cf:      	movl	$0x605a2c, %eax         # imm = 0x605A2C
  5884d4:      	jmp	0x591a45 <.text+0x190a45>
  5884d9:      	movl	$0x605a08, %eax         # imm = 0x605A08
  5884de:      	jmp	0x591a45 <.text+0x190a45>
  5884e3:      	movl	$0x6059e0, %eax         # imm = 0x6059E0
  5884e8:      	jmp	0x591a45 <.text+0x190a45>
  5884ed:      	movl	$0x6059bc, %eax         # imm = 0x6059BC
  5884f2:      	jmp	0x591a45 <.text+0x190a45>
  5884f7:      	movl	$0x605994, %eax         # imm = 0x605994
  5884fc:      	jmp	0x591a45 <.text+0x190a45>
  588501:      	movl	$0x60596c, %eax         # imm = 0x60596C
  588506:      	jmp	0x591a45 <.text+0x190a45>
  58850b:      	movl	$0x60595c, %eax         # imm = 0x60595C
  588510:      	jmp	0x591a45 <.text+0x190a45>
  588515:      	movl	$0x8004d080, %ecx       # imm = 0x8004D080
  58851a:      	cmpl	%ecx, %eax
  58851c:      	jg	0x5886e1 <.text+0x1876e1>
  588522:      	je	0x5886d7 <.text+0x1876d7>
  588528:      	addl	$0x7ffb2fff, %eax       # imm = 0x7FFB2FFF
  58852d:      	cmpl	$0x2a, %eax
  588530:      	ja	0x591a16 <.text+0x190a16>
  588536:      	jmpl	*0x592549(,%eax,4)
  58853d:      	movl	$0x605950, %eax         # imm = 0x605950
  588542:      	jmp	0x591a45 <.text+0x190a45>
  588547:      	movl	$0x60593c, %eax         # imm = 0x60593C
  58854c:      	jmp	0x591a45 <.text+0x190a45>
  588551:      	movl	$0x605928, %eax         # imm = 0x605928
  588556:      	jmp	0x591a45 <.text+0x190a45>
  58855b:      	movl	$0x605910, %eax         # imm = 0x605910
  588560:      	jmp	0x591a45 <.text+0x190a45>
  588565:      	movl	$0x6058f8, %eax         # imm = 0x6058F8
  58856a:      	jmp	0x591a45 <.text+0x190a45>
  58856f:      	movl	$0x6058e0, %eax         # imm = 0x6058E0
  588574:      	jmp	0x591a45 <.text+0x190a45>
  588579:      	movl	$0x6058c8, %eax         # imm = 0x6058C8
  58857e:      	jmp	0x591a45 <.text+0x190a45>
  588583:      	movl	$0x6058b0, %eax         # imm = 0x6058B0
  588588:      	jmp	0x591a45 <.text+0x190a45>
  58858d:      	movl	$0x605898, %eax         # imm = 0x605898
  588592:      	jmp	0x591a45 <.text+0x190a45>
  588597:      	movl	$0x605888, %eax         # imm = 0x605888
  58859c:      	jmp	0x591a45 <.text+0x190a45>
  5885a1:      	movl	$0x605878, %eax         # imm = 0x605878
  5885a6:      	jmp	0x591a45 <.text+0x190a45>
  5885ab:      	movl	$0x605864, %eax         # imm = 0x605864
  5885b0:      	jmp	0x591a45 <.text+0x190a45>
  5885b5:      	movl	$0x605850, %eax         # imm = 0x605850
  5885ba:      	jmp	0x591a45 <.text+0x190a45>
  5885bf:      	movl	$0x60583c, %eax         # imm = 0x60583C
  5885c4:      	jmp	0x591a45 <.text+0x190a45>
  5885c9:      	movl	$0x605824, %eax         # imm = 0x605824
  5885ce:      	jmp	0x591a45 <.text+0x190a45>
  5885d3:      	movl	$0x605810, %eax         # imm = 0x605810
  5885d8:      	jmp	0x591a45 <.text+0x190a45>
  5885dd:      	movl	$0x6057f8, %eax         # imm = 0x6057F8
  5885e2:      	jmp	0x591a45 <.text+0x190a45>
  5885e7:      	movl	$0x6057e4, %eax         # imm = 0x6057E4
  5885ec:      	jmp	0x591a45 <.text+0x190a45>
  5885f1:      	movl	$0x6057d4, %eax         # imm = 0x6057D4
  5885f6:      	jmp	0x591a45 <.text+0x190a45>
  5885fb:      	movl	$0x6057c0, %eax         # imm = 0x6057C0
  588600:      	jmp	0x591a45 <.text+0x190a45>
  588605:      	movl	$0x6057a8, %eax         # imm = 0x6057A8
  58860a:      	jmp	0x591a45 <.text+0x190a45>
  58860f:      	movl	$0x605790, %eax         # imm = 0x605790
  588614:      	jmp	0x591a45 <.text+0x190a45>
  588619:      	movl	$0x605780, %eax         # imm = 0x605780
  58861e:      	jmp	0x591a45 <.text+0x190a45>
  588623:      	movl	$0x60576c, %eax         # imm = 0x60576C
  588628:      	jmp	0x591a45 <.text+0x190a45>
  58862d:      	movl	$0x605750, %eax         # imm = 0x605750
  588632:      	jmp	0x591a45 <.text+0x190a45>
  588637:      	movl	$0x605740, %eax         # imm = 0x605740
  58863c:      	jmp	0x591a45 <.text+0x190a45>
  588641:      	movl	$0x605730, %eax         # imm = 0x605730
  588646:      	jmp	0x591a45 <.text+0x190a45>
  58864b:      	movl	$0x605718, %eax         # imm = 0x605718
  588650:      	jmp	0x591a45 <.text+0x190a45>
  588655:      	movl	$0x605700, %eax         # imm = 0x605700
  58865a:      	jmp	0x591a45 <.text+0x190a45>
  58865f:      	movl	$0x6056e4, %eax         # imm = 0x6056E4
  588664:      	jmp	0x591a45 <.text+0x190a45>
  588669:      	movl	$0x6056cc, %eax         # imm = 0x6056CC
  58866e:      	jmp	0x591a45 <.text+0x190a45>
  588673:      	movl	$0x6056b0, %eax         # imm = 0x6056B0
  588678:      	jmp	0x591a45 <.text+0x190a45>
  58867d:      	movl	$0x605694, %eax         # imm = 0x605694
  588682:      	jmp	0x591a45 <.text+0x190a45>
  588687:      	movl	$0x60567c, %eax         # imm = 0x60567C
  58868c:      	jmp	0x591a45 <.text+0x190a45>
  588691:      	movl	$0x605660, %eax         # imm = 0x605660
  588696:      	jmp	0x591a45 <.text+0x190a45>
  58869b:      	movl	$0x60564c, %eax         # imm = 0x60564C
  5886a0:      	jmp	0x591a45 <.text+0x190a45>
  5886a5:      	movl	$0x605630, %eax         # imm = 0x605630
  5886aa:      	jmp	0x591a45 <.text+0x190a45>
  5886af:      	movl	$0x60560c, %eax         # imm = 0x60560C
  5886b4:      	jmp	0x591a45 <.text+0x190a45>
  5886b9:      	movl	$0x6055f4, %eax         # imm = 0x6055F4
  5886be:      	jmp	0x591a45 <.text+0x190a45>
  5886c3:      	movl	$0x6055d0, %eax         # imm = 0x6055D0
  5886c8:      	jmp	0x591a45 <.text+0x190a45>
  5886cd:      	movl	$0x6055b0, %eax         # imm = 0x6055B0
  5886d2:      	jmp	0x591a45 <.text+0x190a45>
  5886d7:      	movl	$0x605598, %eax         # imm = 0x605598
  5886dc:      	jmp	0x591a45 <.text+0x190a45>
  5886e1:      	movl	$0x80070462, %ecx       # imm = 0x80070462
  5886e6:      	cmpl	%ecx, %eax
  5886e8:      	jg	0x588b9b <.text+0x187b9b>
  5886ee:      	je	0x58d1f1 <.text+0x18c1f1>
  5886f4:      	movl	$0x8007009d, %ecx       # imm = 0x8007009D
  5886f9:      	cmpl	%ecx, %eax
  5886fb:      	jg	0x5889cc <.text+0x1879cc>
  588701:      	je	0x58caab <.text+0x18baab>
  588707:      	addl	$-0x60, %ecx
  58870a:      	cmpl	%ecx, %eax
  58870c:      	jg	0x5889ad <.text+0x1879ad>
  588712:      	je	0x58c7a0 <.text+0x18b7a0>
  588718:      	movl	$0x8007000b, %ecx       # imm = 0x8007000B
  58871d:      	cmpl	%ecx, %eax
  58871f:      	jg	0x58898e <.text+0x18798e>
  588725:      	je	0x58c611 <.text+0x18b611>
  58872b:      	movl	$0x8004e027, %ecx       # imm = 0x8004E027
  588730:      	cmpl	%ecx, %eax
  588732:      	jg	0x5888ad <.text+0x1878ad>
  588738:      	je	0x5888a3 <.text+0x1878a3>
  58873e:      	addl	$-0x21, %ecx
  588741:      	cmpl	%ecx, %eax
  588743:      	jg	0x5887fe <.text+0x1877fe>
  588749:      	je	0x5887f4 <.text+0x1877f4>
  58874f:      	movl	$0x8004d085, %ecx       # imm = 0x8004D085
  588754:      	cmpl	%ecx, %eax
  588756:      	jg	0x5887ac <.text+0x1877ac>
  588758:      	je	0x5887a2 <.text+0x1877a2>
  58875a:      	cmpl	$0x8004d081, %eax       # imm = 0x8004D081
  58875f:      	je	0x588798 <.text+0x187798>
  588761:      	cmpl	$0x8004d082, %eax       # imm = 0x8004D082
  588766:      	je	0x58878e <.text+0x18778e>
  588768:      	cmpl	$0x8004d083, %eax       # imm = 0x8004D083
  58876d:      	je	0x588784 <.text+0x187784>
  58876f:      	cmpl	$0x8004d084, %eax       # imm = 0x8004D084
  588774:      	jne	0x591a16 <.text+0x190a16>
  58877a:      	movl	$0x605584, %eax         # imm = 0x605584
  58877f:      	jmp	0x591a45 <.text+0x190a45>
  588784:      	movl	$0x605568, %eax         # imm = 0x605568
  588789:      	jmp	0x591a45 <.text+0x190a45>
  58878e:      	movl	$0x60554c, %eax         # imm = 0x60554C
  588793:      	jmp	0x591a45 <.text+0x190a45>
  588798:      	movl	$0x605538, %eax         # imm = 0x605538
  58879d:      	jmp	0x591a45 <.text+0x190a45>
  5887a2:      	movl	$0x605520, %eax         # imm = 0x605520
  5887a7:      	jmp	0x591a45 <.text+0x190a45>
  5887ac:      	cmpl	$0x8004e000, %eax       # imm = 0x8004E000
  5887b1:      	je	0x5887ea <.text+0x1877ea>
  5887b3:      	cmpl	$0x8004e002, %eax       # imm = 0x8004E002
  5887b8:      	je	0x5887e0 <.text+0x1877e0>
  5887ba:      	cmpl	$0x8004e003, %eax       # imm = 0x8004E003
  5887bf:      	je	0x5887d6 <.text+0x1877d6>
  5887c1:      	cmpl	$0x8004e004, %eax       # imm = 0x8004E004
  5887c6:      	jne	0x591a16 <.text+0x190a16>
  5887cc:      	movl	$0x60550c, %eax         # imm = 0x60550C
  5887d1:      	jmp	0x591a45 <.text+0x190a45>
  5887d6:      	movl	$0x6054f8, %eax         # imm = 0x6054F8
  5887db:      	jmp	0x591a45 <.text+0x190a45>
  5887e0:      	movl	$0x6054e4, %eax         # imm = 0x6054E4
  5887e5:      	jmp	0x591a45 <.text+0x190a45>
  5887ea:      	movl	$0x6054d4, %eax         # imm = 0x6054D4
  5887ef:      	jmp	0x591a45 <.text+0x190a45>
  5887f4:      	movl	$0x6054bc, %eax         # imm = 0x6054BC
  5887f9:      	jmp	0x591a45 <.text+0x190a45>
  5887fe:      	movl	$0x8004e022, %ecx       # imm = 0x8004E022
  588803:      	cmpl	%ecx, %eax
  588805:      	jg	0x58885b <.text+0x18785b>
  588807:      	je	0x588851 <.text+0x187851>
  588809:      	cmpl	$0x8004e007, %eax       # imm = 0x8004E007
  58880e:      	je	0x588847 <.text+0x187847>
  588810:      	cmpl	$0x8004e00c, %eax       # imm = 0x8004E00C
  588815:      	je	0x58883d <.text+0x18783d>
  588817:      	cmpl	$0x8004e00f, %eax       # imm = 0x8004E00F
  58881c:      	je	0x588833 <.text+0x187833>
  58881e:      	cmpl	$0x8004e021, %eax       # imm = 0x8004E021
  588823:      	jne	0x591a16 <.text+0x190a16>
  588829:      	movl	$0x6054a4, %eax         # imm = 0x6054A4
  58882e:      	jmp	0x591a45 <.text+0x190a45>
  588833:      	movl	$0x605488, %eax         # imm = 0x605488
  588838:      	jmp	0x591a45 <.text+0x190a45>
  58883d:      	movl	$0x605470, %eax         # imm = 0x605470
  588842:      	jmp	0x591a45 <.text+0x190a45>
  588847:      	movl	$0x60545c, %eax         # imm = 0x60545C
  58884c:      	jmp	0x591a45 <.text+0x190a45>
  588851:      	movl	$0x605438, %eax         # imm = 0x605438
  588856:      	jmp	0x591a45 <.text+0x190a45>
  58885b:      	cmpl	$0x8004e023, %eax       # imm = 0x8004E023
  588860:      	je	0x588899 <.text+0x187899>
  588862:      	cmpl	$0x8004e024, %eax       # imm = 0x8004E024
  588867:      	je	0x58888f <.text+0x18788f>
  588869:      	cmpl	$0x8004e025, %eax       # imm = 0x8004E025
  58886e:      	je	0x588885 <.text+0x187885>
  588870:      	cmpl	$0x8004e026, %eax       # imm = 0x8004E026
  588875:      	jne	0x591a16 <.text+0x190a16>
  58887b:      	movl	$0x605428, %eax         # imm = 0x605428
  588880:      	jmp	0x591a45 <.text+0x190a45>
  588885:      	movl	$0x60540c, %eax         # imm = 0x60540C
  58888a:      	jmp	0x591a45 <.text+0x190a45>
  58888f:      	movl	$0x6053ec, %eax         # imm = 0x6053EC
  588894:      	jmp	0x591a45 <.text+0x190a45>
  588899:      	movl	$0x6053c8, %eax         # imm = 0x6053C8
  58889e:      	jmp	0x591a45 <.text+0x190a45>
  5888a3:      	movl	$0x6053b0, %eax         # imm = 0x6053B0
  5888a8:      	jmp	0x591a45 <.text+0x190a45>
  5888ad:      	movl	$0x80070002, %ecx       # imm = 0x80070002
  5888b2:      	cmpl	%ecx, %eax
  5888b4:      	jg	0x588965 <.text+0x187965>
  5888ba:      	je	0x58c5b7 <.text+0x18b5b7>
  5888c0:      	movl	$0x8004e02c, %ecx       # imm = 0x8004E02C
  5888c5:      	cmpl	%ecx, %eax
  5888c7:      	jg	0x58891d <.text+0x18791d>
  5888c9:      	je	0x588913 <.text+0x187913>
  5888cb:      	cmpl	$0x8004e028, %eax       # imm = 0x8004E028
  5888d0:      	je	0x588909 <.text+0x187909>
  5888d2:      	cmpl	$0x8004e029, %eax       # imm = 0x8004E029
  5888d7:      	je	0x5888ff <.text+0x1878ff>
  5888d9:      	cmpl	$0x8004e02a, %eax       # imm = 0x8004E02A
  5888de:      	je	0x5888f5 <.text+0x1878f5>
  5888e0:      	cmpl	$0x8004e02b, %eax       # imm = 0x8004E02B
  5888e5:      	jne	0x591a16 <.text+0x190a16>
  5888eb:      	movl	$0x6053a0, %eax         # imm = 0x6053A0
  5888f0:      	jmp	0x591a45 <.text+0x190a45>
  5888f5:      	movl	$0x605390, %eax         # imm = 0x605390
  5888fa:      	jmp	0x591a45 <.text+0x190a45>
  5888ff:      	movl	$0x605378, %eax         # imm = 0x605378
  588904:      	jmp	0x591a45 <.text+0x190a45>
  588909:      	movl	$0x60535c, %eax         # imm = 0x60535C
  58890e:      	jmp	0x591a45 <.text+0x190a45>
  588913:      	movl	$0x60534c, %eax         # imm = 0x60534C
  588918:      	jmp	0x591a45 <.text+0x190a45>
  58891d:      	cmpl	$0x8004e02d, %eax       # imm = 0x8004E02D
  588922:      	je	0x58895b <.text+0x18795b>
  588924:      	cmpl	$0x8004e02e, %eax       # imm = 0x8004E02E
  588929:      	je	0x588951 <.text+0x187951>
  58892b:      	cmpl	$0x8004e02f, %eax       # imm = 0x8004E02F
  588930:      	je	0x588947 <.text+0x187947>
  588932:      	cmpl	$0x80070001, %eax       # imm = 0x80070001
  588937:      	jne	0x591a16 <.text+0x190a16>
  58893d:      	movl	$0x605334, %eax         # imm = 0x605334
  588942:      	jmp	0x591a45 <.text+0x190a45>
  588947:      	movl	$0x605324, %eax         # imm = 0x605324
  58894c:      	jmp	0x591a45 <.text+0x190a45>
  588951:      	movl	$0x60530c, %eax         # imm = 0x60530C
  588956:      	jmp	0x591a45 <.text+0x190a45>
  58895b:      	movl	$0x6052f8, %eax         # imm = 0x6052F8
  588960:      	jmp	0x591a45 <.text+0x190a45>
  588965:      	addl	$0x7ff8fffd, %eax       # imm = 0x7FF8FFFD
  58896a:      	cmpl	$0x7, %eax
  58896d:      	ja	0x591a16 <.text+0x190a16>
  588973:      	jmpl	*0x5925f5(,%eax,4)
  58897a:      	movl	$0x6052ec, %eax         # imm = 0x6052EC
  58897f:      	jmp	0x591a45 <.text+0x190a45>
  588984:      	movl	$0x6052dc, %eax         # imm = 0x6052DC
  588989:      	jmp	0x591a45 <.text+0x190a45>
  58898e:      	addl	$0x7ff8fff4, %eax       # imm = 0x7FF8FFF4
  588993:      	cmpl	$0x30, %eax
  588996:      	ja	0x591a16 <.text+0x190a16>
  58899c:      	jmpl	*0x592615(,%eax,4)
  5889a3:      	movl	$0x6052cc, %eax         # imm = 0x6052CC
  5889a8:      	jmp	0x591a45 <.text+0x190a45>
  5889ad:      	addl	$0x7ff8ffc2, %eax       # imm = 0x7FF8FFC2
  5889b2:      	cmpl	$0x5e, %eax
  5889b5:      	ja	0x591a16 <.text+0x190a16>
  5889bb:      	jmpl	*0x5926d9(,%eax,4)
  5889c2:      	movl	$0x6052bc, %eax         # imm = 0x6052BC
  5889c7:      	jmp	0x591a45 <.text+0x190a45>
  5889cc:      	movl	$0x800700f0, %ecx       # imm = 0x800700F0
  5889d1:      	cmpl	%ecx, %eax
  5889d3:      	jg	0x5889f7 <.text+0x1879f7>
  5889d5:      	je	0x58ccc3 <.text+0x18bcc3>
  5889db:      	addl	$0x7ff8ff62, %eax       # imm = 0x7FF8FF62
  5889e0:      	cmpl	$0x4c, %eax
  5889e3:      	ja	0x591a16 <.text+0x190a16>
  5889e9:      	movzbl	0x592909(%eax), %eax
  5889f0:      	jmpl	*0x592855(,%eax,4)
  5889f7:      	movl	$0x8007041d, %ecx       # imm = 0x8007041D
  5889fc:      	cmpl	%ecx, %eax
  5889fe:      	jg	0x588b86 <.text+0x187b86>
  588a04:      	je	0x58cfdf <.text+0x18bfdf>
  588a0a:      	addl	$-0x38, %ecx
  588a0d:      	cmpl	%ecx, %eax
  588a0f:      	jg	0x588b6a <.text+0x187b6a>
  588a15:      	je	0x58cebc <.text+0x18bebc>
  588a1b:      	movl	$0x8007012b, %ecx       # imm = 0x8007012B
  588a20:      	cmpl	%ecx, %eax
  588a22:      	jg	0x588ad3 <.text+0x187ad3>
  588a28:      	je	0x58cdbf <.text+0x18bdbf>
  588a2e:      	addl	$-0x18, %ecx
  588a31:      	cmpl	%ecx, %eax
  588a33:      	jg	0x588a87 <.text+0x187a87>
  588a35:      	je	0x58cd7c <.text+0x18bd7c>
  588a3b:      	cmpl	$0x800700fe, %eax       # imm = 0x800700FE
  588a40:      	je	0x58cccd <.text+0x18bccd>
  588a46:      	cmpl	$0x800700ff, %eax       # imm = 0x800700FF
  588a4b:      	je	0x58cd40 <.text+0x18bd40>
  588a51:      	cmpl	$0x80070102, %eax       # imm = 0x80070102
  588a56:      	je	0x58cd36 <.text+0x18bd36>
  588a5c:      	cmpl	$0x80070103, %eax       # imm = 0x80070103
  588a61:      	je	0x58cd2c <.text+0x18bd2c>
  588a67:      	cmpl	$0x8007010a, %eax       # imm = 0x8007010A
  588a6c:      	je	0x58cd22 <.text+0x18bd22>
  588a72:      	cmpl	$0x8007010b, %eax       # imm = 0x8007010B
  588a77:      	jne	0x591a16 <.text+0x190a16>
  588a7d:      	movl	$0x6052ac, %eax         # imm = 0x6052AC
  588a82:      	jmp	0x591a45 <.text+0x190a45>
  588a87:      	cmpl	$0x80070114, %eax       # imm = 0x80070114
  588a8c:      	je	0x58cd72 <.text+0x18bd72>
  588a92:      	cmpl	$0x80070115, %eax       # imm = 0x80070115
  588a97:      	je	0x58cd68 <.text+0x18bd68>
  588a9d:      	cmpl	$0x80070116, %eax       # imm = 0x80070116
  588aa2:      	je	0x58cd5e <.text+0x18bd5e>
  588aa8:      	cmpl	$0x8007011a, %eax       # imm = 0x8007011A
  588aad:      	je	0x58cd86 <.text+0x18bd86>
  588ab3:      	cmpl	$0x80070120, %eax       # imm = 0x80070120
  588ab8:      	je	0x58cdc9 <.text+0x18bdc9>
  588abe:      	cmpl	$0x8007012a, %eax       # imm = 0x8007012A
  588ac3:      	jne	0x591a16 <.text+0x190a16>
  588ac9:      	movl	$0x605294, %eax         # imm = 0x605294
  588ace:      	jmp	0x591a45 <.text+0x190a45>
  588ad3:      	movl	$0x80070216, %ecx       # imm = 0x80070216
  588ad8:      	cmpl	%ecx, %eax
  588ada:      	jg	0x588b29 <.text+0x187b29>
  588adc:      	je	0x58ce1f <.text+0x18be1f>
  588ae2:      	cmpl	$0x8007012c, %eax       # imm = 0x8007012C
  588ae7:      	je	0x58cdb5 <.text+0x18bdb5>
  588aed:      	cmpl	$0x8007012d, %eax       # imm = 0x8007012D
  588af2:      	je	0x58cdd3 <.text+0x18bdd3>
  588af8:      	cmpl	$0x8007012e, %eax       # imm = 0x8007012E
  588afd:      	je	0x58ce15 <.text+0x18be15>
  588b03:      	cmpl	$0x8007012f, %eax       # imm = 0x8007012F
  588b08:      	je	0x58ce0b <.text+0x18be0b>
  588b0e:      	cmpl	$0x8007013d, %eax       # imm = 0x8007013D
  588b13:      	je	0x58ce01 <.text+0x18be01>
  588b19:      	cmpl	$0x800701e7, %eax       # imm = 0x800701E7
  588b1e:      	je	0x58cdf7 <.text+0x18bdf7>
  588b24:      	jmp	0x591a16 <.text+0x190a16>
  588b29:      	cmpl	$0x80070217, %eax       # imm = 0x80070217
  588b2e:      	je	0x58ce7f <.text+0x18be7f>
  588b34:      	cmpl	$0x80070218, %eax       # imm = 0x80070218
  588b39:      	je	0x58ce75 <.text+0x18be75>
  588b3f:      	cmpl	$0x800703e2, %eax       # imm = 0x800703E2
  588b44:      	je	0x58ce6b <.text+0x18be6b>
  588b4a:      	cmpl	$0x800703e3, %eax       # imm = 0x800703E3
  588b4f:      	je	0x58ce61 <.text+0x18be61>
  588b55:      	cmpl	$0x800703e4, %eax       # imm = 0x800703E4
  588b5a:      	jne	0x591a16 <.text+0x190a16>
  588b60:      	movl	$0x605280, %eax         # imm = 0x605280
  588b65:      	jmp	0x591a45 <.text+0x190a45>
  588b6a:      	addl	$0x7ff8fc1a, %eax       # imm = 0x7FF8FC1A
  588b6f:      	cmpl	$0x36, %eax
  588b72:      	ja	0x591a16 <.text+0x190a16>
  588b78:      	movzbl	0x5929c5(%eax), %eax
  588b7f:      	jmpl	*0x592959(,%eax,4)
  588b86:      	addl	$0x7ff8fbe2, %eax       # imm = 0x7FF8FBE2
  588b8b:      	cmpl	$0x43, %eax
  588b8e:      	ja	0x591a16 <.text+0x190a16>
  588b94:      	jmpl	*0x5929fd(,%eax,4)
  588b9b:      	addl	$0x7ff8fb9d, %eax       # imm = 0x7FF8FB9D
  588ba0:      	cmpl	$0x1f6, %eax            # imm = 0x1F6
  588ba5:      	ja	0x591a16 <.text+0x190a16>
  588bab:      	jmpl	*0x592b0d(,%eax,4)
  588bb2:      	movl	$0x800706a4, %ecx       # imm = 0x800706A4
  588bb7:      	cmpl	%ecx, %eax
  588bb9:      	jg	0x588bd6 <.text+0x187bd6>
  588bbb:      	je	0x58dcc6 <.text+0x18ccc6>
  588bc1:      	addl	$0x7ff8f9a5, %eax       # imm = 0x7FF8F9A5
  588bc6:      	cmpl	$0x11, %eax
  588bc9:      	ja	0x591a16 <.text+0x190a16>
  588bcf:      	jmpl	*0x5932e9(,%eax,4)
  588bd6:      	movl	$0x800708ca, %ecx       # imm = 0x800708CA
  588bdb:      	cmpl	%ecx, %eax
  588bdd:      	jg	0x588c03 <.text+0x187c03>
  588bdf:      	je	0x58e62f <.text+0x18d62f>
  588be5:      	addl	$0x7ff8f95b, %eax       # imm = 0x7FF8F95B
  588bea:      	cmpl	$0x1f5, %eax            # imm = 0x1F5
  588bef:      	ja	0x591a16 <.text+0x190a16>
  588bf5:      	movzbl	0x593615(%eax), %eax
  588bfc:      	jmpl	*0x593331(,%eax,4)
  588c03:      	movl	$0x8007215d, %ecx       # imm = 0x8007215D
  588c08:      	cmpl	%ecx, %eax
  588c0a:      	jg	0x5890d6 <.text+0x1880d6>
  588c10:      	je	0x59005b <.text+0x18f05b>
  588c16:      	movl	$0x8007201a, %ecx       # imm = 0x8007201A
  588c1b:      	cmpl	%ecx, %eax
  588c1d:      	jg	0x5890bf <.text+0x1880bf>
  588c23:      	je	0x58f525 <.text+0x18e525>
  588c29:      	movl	$0x800713bb, %ecx       # imm = 0x800713BB
  588c2e:      	cmpl	%ecx, %eax
  588c30:      	jg	0x588eb7 <.text+0x187eb7>
  588c36:      	je	0x58ede6 <.text+0x18dde6>
  588c3c:      	movl	$0x800710e9, %ecx       # imm = 0x800710E9
  588c41:      	cmpl	%ecx, %eax
  588c43:      	jg	0x588da1 <.text+0x187da1>
  588c49:      	je	0x58ea36 <.text+0x18da36>
  588c4f:      	addl	$-0x78, %ecx
  588c52:      	cmpl	%ecx, %eax
  588c54:      	jg	0x588d85 <.text+0x187d85>
  588c5a:      	je	0x58e8bc <.text+0x18d8bc>
  588c60:      	movl	$0x80070bc6, %ecx       # imm = 0x80070BC6
  588c65:      	cmpl	%ecx, %eax
  588c67:      	jg	0x588cfb <.text+0x187cfb>
  588c6d:      	je	0x58e7ae <.text+0x18d7ae>
  588c73:      	addl	$-0x9, %ecx
  588c76:      	cmpl	%ecx, %eax
  588c78:      	jg	0x588ce6 <.text+0x187ce6>
  588c7a:      	je	0x58e73f <.text+0x18d73f>
  588c80:      	movl	$0x80070bb9, %ecx       # imm = 0x80070BB9
  588c85:      	cmpl	%ecx, %eax
  588c87:      	jg	0x588cc0 <.text+0x187cc0>
  588c89:      	je	0x58e706 <.text+0x18d706>
  588c8f:      	cmpl	$0x80070961, %eax       # imm = 0x80070961
  588c94:      	je	0x58e6fc <.text+0x18d6fc>
  588c9a:      	cmpl	$0x80070962, %eax       # imm = 0x80070962
  588c9f:      	je	0x58e6f2 <.text+0x18d6f2>
  588ca5:      	cmpl	$0x80070964, %eax       # imm = 0x80070964
  588caa:      	je	0x58e6e8 <.text+0x18d6e8>
  588cb0:      	cmpl	$0x80070bb8, %eax       # imm = 0x80070BB8
  588cb5:      	je	0x58e6de <.text+0x18d6de>
  588cbb:      	jmp	0x591a16 <.text+0x190a16>
  588cc0:      	cmpl	$0x80070bba, %eax       # imm = 0x80070BBA
  588cc5:      	je	0x58e735 <.text+0x18d735>
  588ccb:      	cmpl	$0x80070bbb, %eax       # imm = 0x80070BBB
  588cd0:      	je	0x58e72b <.text+0x18d72b>
  588cd6:      	cmpl	$0x80070bbc, %eax       # imm = 0x80070BBC
  588cdb:      	je	0x58e721 <.text+0x18d721>
  588ce1:      	jmp	0x591a16 <.text+0x190a16>
  588ce6:      	addl	$0x7ff8f442, %eax       # imm = 0x7FF8F442
  588ceb:      	cmpl	$0x7, %eax
  588cee:      	ja	0x591a16 <.text+0x190a16>
  588cf4:      	jmpl	*0x59380d(,%eax,4)
  588cfb:      	movl	$0x80071068, %ecx       # imm = 0x80071068
  588d00:      	cmpl	%ecx, %eax
  588d02:      	jg	0x588d70 <.text+0x187d70>
  588d04:      	je	0x58e84d <.text+0x18d84d>
  588d0a:      	movl	$0x80070fa4, %ecx       # imm = 0x80070FA4
  588d0f:      	cmpl	%ecx, %eax
  588d11:      	jg	0x588d4a <.text+0x187d4a>
  588d13:      	je	0x58e812 <.text+0x18d812>
  588d19:      	cmpl	$0x80070fa0, %eax       # imm = 0x80070FA0
  588d1e:      	je	0x58e808 <.text+0x18d808>
  588d24:      	cmpl	$0x80070fa1, %eax       # imm = 0x80070FA1
  588d29:      	je	0x58e7fe <.text+0x18d7fe>
  588d2f:      	cmpl	$0x80070fa2, %eax       # imm = 0x80070FA2
  588d34:      	je	0x58e7f4 <.text+0x18d7f4>
  588d3a:      	cmpl	$0x80070fa3, %eax       # imm = 0x80070FA3
  588d3f:      	je	0x58e7ea <.text+0x18d7ea>
  588d45:      	jmp	0x591a16 <.text+0x190a16>
  588d4a:      	cmpl	$0x80070fa5, %eax       # imm = 0x80070FA5
  588d4f:      	je	0x58e843 <.text+0x18d843>
  588d55:      	cmpl	$0x80070fa6, %eax       # imm = 0x80070FA6
  588d5a:      	je	0x58e839 <.text+0x18d839>
  588d60:      	cmpl	$0x80071004, %eax       # imm = 0x80071004
  588d65:      	je	0x58e82f <.text+0x18d82f>
  588d6b:      	jmp	0x591a16 <.text+0x190a16>
  588d70:      	addl	$0x7ff8ef97, %eax       # imm = 0x7FF8EF97
  588d75:      	cmpl	$0x7, %eax
  588d78:      	ja	0x591a16 <.text+0x190a16>
  588d7e:      	jmpl	*0x59382d(,%eax,4)
  588d85:      	addl	$0x7ff8ef8e, %eax       # imm = 0x7FF8EF8E
  588d8a:      	cmpl	$0x76, %eax
  588d8d:      	ja	0x591a16 <.text+0x190a16>
  588d93:      	movzbl	0x5938d9(%eax), %eax
  588d9a:      	jmpl	*0x59384d(,%eax,4)
  588da1:      	movl	$0x80071126, %ecx       # imm = 0x80071126
  588da6:      	cmpl	%ecx, %eax
  588da8:      	jg	0x588dcc <.text+0x187dcc>
  588daa:      	je	0x58eafb <.text+0x18dafb>
  588db0:      	addl	$0x7ff8ef16, %eax       # imm = 0x7FF8EF16
  588db5:      	cmpl	$0x16, %eax
  588db8:      	ja	0x591a16 <.text+0x190a16>
  588dbe:      	movzbl	0x59398d(%eax), %eax
  588dc5:      	jmpl	*0x593951(,%eax,4)
  588dcc:      	movl	$0x8007139f, %ecx       # imm = 0x8007139F
  588dd1:      	cmpl	%ecx, %eax
  588dd3:      	jg	0x588ea2 <.text+0x187ea2>
  588dd9:      	je	0x58ec91 <.text+0x18dc91>
  588ddf:      	addl	$-0xe, %ecx
  588de2:      	cmpl	%ecx, %eax
  588de4:      	jg	0x588e8d <.text+0x187e8d>
  588dea:      	je	0x58ebf0 <.text+0x18dbf0>
  588df0:      	movl	$0x8007138a, %ecx       # imm = 0x8007138A
  588df5:      	cmpl	%ecx, %eax
  588df7:      	jg	0x588e46 <.text+0x187e46>
  588df9:      	je	0x58eb90 <.text+0x18db90>
  588dff:      	cmpl	$0x80071127, %eax       # imm = 0x80071127
  588e04:      	je	0x58eb86 <.text+0x18db86>
  588e0a:      	cmpl	$0x80071128, %eax       # imm = 0x80071128
  588e0f:      	je	0x58eb7c <.text+0x18db7c>
  588e15:      	cmpl	$0x80071129, %eax       # imm = 0x80071129
  588e1a:      	je	0x58eb72 <.text+0x18db72>
  588e20:      	cmpl	$0x8007112a, %eax       # imm = 0x8007112A
  588e25:      	je	0x58eb68 <.text+0x18db68>
  588e2b:      	cmpl	$0x80071194, %eax       # imm = 0x80071194
  588e30:      	je	0x58eb5e <.text+0x18db5e>
  588e36:      	cmpl	$0x80071389, %eax       # imm = 0x80071389
  588e3b:      	je	0x58eb54 <.text+0x18db54>
  588e41:      	jmp	0x591a16 <.text+0x190a16>
  588e46:      	cmpl	$0x8007138b, %eax       # imm = 0x8007138B
  588e4b:      	je	0x58ebe6 <.text+0x18dbe6>
  588e51:      	cmpl	$0x8007138c, %eax       # imm = 0x8007138C
  588e56:      	je	0x58ebdc <.text+0x18dbdc>
  588e5c:      	cmpl	$0x8007138d, %eax       # imm = 0x8007138D
  588e61:      	je	0x58ebd2 <.text+0x18dbd2>
  588e67:      	cmpl	$0x8007138e, %eax       # imm = 0x8007138E
  588e6c:      	je	0x58ebc8 <.text+0x18dbc8>
  588e72:      	cmpl	$0x8007138f, %eax       # imm = 0x8007138F
  588e77:      	je	0x58ebbe <.text+0x18dbbe>
  588e7d:      	cmpl	$0x80071390, %eax       # imm = 0x80071390
  588e82:      	je	0x58ebb4 <.text+0x18dbb4>
  588e88:      	jmp	0x591a16 <.text+0x190a16>
  588e8d:      	addl	$0x7ff8ec6e, %eax       # imm = 0x7FF8EC6E
  588e92:      	cmpl	$0xc, %eax
  588e95:      	ja	0x591a16 <.text+0x190a16>
  588e9b:      	jmpl	*0x5939a5(,%eax,4)
  588ea2:      	addl	$0x7ff8ec60, %eax       # imm = 0x7FF8EC60
  588ea7:      	cmpl	$0x1a, %eax
  588eaa:      	ja	0x591a16 <.text+0x190a16>
  588eb0:      	jmpl	*0x5939d9(,%eax,4)
  588eb7:      	movl	$0x80071702, %ecx       # imm = 0x80071702
  588ebc:      	cmpl	%ecx, %eax
  588ebe:      	jg	0x588edb <.text+0x187edb>
  588ec0:      	je	0x58ef62 <.text+0x18df62>
  588ec6:      	addl	$0x7ff8ec44, %eax       # imm = 0x7FF8EC44
  588ecb:      	cmpl	$0x25, %eax
  588ece:      	ja	0x591a16 <.text+0x190a16>
  588ed4:      	jmpl	*0x593a45(,%eax,4)
  588edb:      	movl	$0x80071770, %ecx       # imm = 0x80071770
  588ee0:      	cmpl	%ecx, %eax
  588ee2:      	jg	0x588eff <.text+0x187eff>
  588ee4:      	je	0x58eff4 <.text+0x18dff4>
  588eea:      	addl	$0x7ff8e8fd, %eax       # imm = 0x7FF8E8FD
  588eef:      	cmpl	$0x9, %eax
  588ef2:      	ja	0x591a16 <.text+0x190a16>
  588ef8:      	jmpl	*0x593add(,%eax,4)
  588eff:      	movl	$0x800717e6, %ecx       # imm = 0x800717E6
  588f04:      	cmpl	%ecx, %eax
  588f06:      	jg	0x588f23 <.text+0x187f23>
  588f08:      	je	0x58f0c6 <.text+0x18e0c6>
  588f0e:      	addl	$0x7ff8e88f, %eax       # imm = 0x7FF8E88F
  588f13:      	cmpl	$0xf, %eax
  588f16:      	ja	0x591a16 <.text+0x190a16>
  588f1c:      	jmpl	*0x593b05(,%eax,4)
  588f23:      	movl	$0x80071b90, %ecx       # imm = 0x80071B90
  588f28:      	cmpl	%ecx, %eax
  588f2a:      	jg	0x588ff6 <.text+0x187ff6>
  588f30:      	je	0x58f344 <.text+0x18e344>
  588f36:      	addl	$-0x22, %ecx
  588f39:      	cmpl	%ecx, %eax
  588f3b:      	jg	0x588fda <.text+0x187fda>
  588f41:      	je	0x58f205 <.text+0x18e205>
  588f47:      	movl	$0x80071b61, %ecx       # imm = 0x80071B61
  588f4c:      	cmpl	%ecx, %eax
  588f4e:      	jg	0x588fc5 <.text+0x187fc5>
  588f50:      	je	0x58f196 <.text+0x18e196>
  588f56:      	addl	$-0x5, %ecx
  588f59:      	cmpl	%ecx, %eax
  588f5b:      	jg	0x588f94 <.text+0x187f94>
  588f5d:      	je	0x58f150 <.text+0x18e150>
  588f63:      	cmpl	$0x80071838, %eax       # imm = 0x80071838
  588f68:      	je	0x58f146 <.text+0x18e146>
  588f6e:      	cmpl	$0x80071b59, %eax       # imm = 0x80071B59
  588f73:      	je	0x58f13c <.text+0x18e13c>
  588f79:      	cmpl	$0x80071b5a, %eax       # imm = 0x80071B5A
  588f7e:      	je	0x58f132 <.text+0x18e132>
  588f84:      	cmpl	$0x80071b5b, %eax       # imm = 0x80071B5B
  588f89:      	je	0x58f128 <.text+0x18e128>
  588f8f:      	jmp	0x591a16 <.text+0x190a16>
  588f94:      	cmpl	$0x80071b5d, %eax       # imm = 0x80071B5D
  588f99:      	je	0x58f18c <.text+0x18e18c>
  588f9f:      	cmpl	$0x80071b5e, %eax       # imm = 0x80071B5E
  588fa4:      	je	0x58f182 <.text+0x18e182>
  588faa:      	cmpl	$0x80071b5f, %eax       # imm = 0x80071B5F
  588faf:      	je	0x58f178 <.text+0x18e178>
  588fb5:      	cmpl	$0x80071b60, %eax       # imm = 0x80071B60
  588fba:      	je	0x58f16e <.text+0x18e16e>
  588fc0:      	jmp	0x591a16 <.text+0x190a16>
  588fc5:      	addl	$0x7ff8e49e, %eax       # imm = 0x7FF8E49E
  588fca:      	cmpl	$0x7, %eax
  588fcd:      	ja	0x591a16 <.text+0x190a16>
  588fd3:      	jmpl	*0x593b45(,%eax,4)
  588fda:      	addl	$0x7ff8e491, %eax       # imm = 0x7FF8E491
  588fdf:      	cmpl	$0x20, %eax
  588fe2:      	ja	0x591a16 <.text+0x190a16>
  588fe8:      	movzbl	0x593bb1(%eax), %eax
  588fef:      	jmpl	*0x593b65(,%eax,4)
  588ff6:      	movl	$0x80071f51, %ecx       # imm = 0x80071F51
  588ffb:      	cmpl	%ecx, %eax
  588ffd:      	jg	0x5890aa <.text+0x1880aa>
  589003:      	je	0x58f434 <.text+0x18e434>
  589009:      	addl	$-0x9, %ecx
  58900c:      	cmpl	%ecx, %eax
  58900e:      	jg	0x589095 <.text+0x188095>
  589014:      	je	0x58f39c <.text+0x18e39c>
  58901a:      	movl	$0x80071f43, %ecx       # imm = 0x80071F43
  58901f:      	cmpl	%ecx, %eax
  589021:      	jg	0x58905f <.text+0x18805f>
  589023:      	je	0x58f373 <.text+0x18e373>
  589029:      	cmpl	$0x80071b91, %eax       # imm = 0x80071B91
  58902e:      	je	0x58f33a <.text+0x18e33a>
  589034:      	cmpl	$0x80071b92, %eax       # imm = 0x80071B92
  589039:      	je	0x58f330 <.text+0x18e330>
  58903f:      	cmpl	$0x80071f41, %eax       # imm = 0x80071F41
  589044:      	je	0x58f326 <.text+0x18e326>
  58904a:      	cmpl	$0x80071f42, %eax       # imm = 0x80071F42
  58904f:      	jne	0x591a16 <.text+0x190a16>
  589055:      	movl	$0x605264, %eax         # imm = 0x605264
  58905a:      	jmp	0x591a45 <.text+0x190a45>
  58905f:      	cmpl	$0x80071f44, %eax       # imm = 0x80071F44
  589064:      	je	0x58f369 <.text+0x18e369>
  58906a:      	cmpl	$0x80071f45, %eax       # imm = 0x80071F45
  58906f:      	je	0x58f35f <.text+0x18e35f>
  589075:      	cmpl	$0x80071f46, %eax       # imm = 0x80071F46
  58907a:      	je	0x58f37d <.text+0x18e37d>
  589080:      	cmpl	$0x80071f47, %eax       # imm = 0x80071F47
  589085:      	jne	0x591a16 <.text+0x190a16>
  58908b:      	movl	$0x605248, %eax         # imm = 0x605248
  589090:      	jmp	0x591a45 <.text+0x190a45>
  589095:      	addl	$0x7ff8e0b7, %eax       # imm = 0x7FF8E0B7
  58909a:      	cmpl	$0x7, %eax
  58909d:      	ja	0x591a16 <.text+0x190a16>
  5890a3:      	jmpl	*0x593bd5(,%eax,4)
  5890aa:      	addl	$0x7ff8dff8, %eax       # imm = 0x7FF8DFF8
  5890af:      	cmpl	$0x11, %eax
  5890b2:      	ja	0x591a16 <.text+0x190a16>
  5890b8:      	jmpl	*0x593bf5(,%eax,4)
  5890bf:      	addl	$0x7ff8dfe5, %eax       # imm = 0x7FF8DFE5
  5890c4:      	cmpl	$0x141, %eax            # imm = 0x141
  5890c9:      	ja	0x591a16 <.text+0x190a16>
  5890cf:      	jmpl	*0x593c3d(,%eax,4)
  5890d6:      	movl	$0x80072328, %ecx       # imm = 0x80072328
  5890db:      	cmpl	%ecx, %eax
  5890dd:      	jg	0x5890fa <.text+0x1880fa>
  5890df:      	je	0x5902bd <.text+0x18f2bd>
  5890e5:      	addl	$0x7ff8dea2, %eax       # imm = 0x7FF8DEA2
  5890ea:      	cmpl	$0x3b, %eax
  5890ed:      	ja	0x591a16 <.text+0x190a16>
  5890f3:      	jmpl	*0x594145(,%eax,4)
  5890fa:      	movl	$0x8007251c, %ecx       # imm = 0x8007251C
  5890ff:      	cmpl	%ecx, %eax
  589101:      	jg	0x58911e <.text+0x18811e>
  589103:      	je	0x590371 <.text+0x18f371>
  589109:      	addl	$0x7ff8dcd7, %eax       # imm = 0x7FF8DCD7
  58910e:      	cmpl	$0x11, %eax
  589111:      	ja	0x591a16 <.text+0x190a16>
  589117:      	jmpl	*0x594235(,%eax,4)
  58911e:      	movl	$0x80073620, %ecx       # imm = 0x80073620
  589123:      	cmpl	%ecx, %eax
  589125:      	jg	0x5894d7 <.text+0x1884d7>
  58912b:      	je	0x590e16 <.text+0x18fe16>
  589131:      	movl	$0x8007276c, %ecx       # imm = 0x8007276C
  589136:      	cmpl	%ecx, %eax
  589138:      	jg	0x58928a <.text+0x18828a>
  58913e:      	je	0x5908bd <.text+0x18f8bd>
  589144:      	movl	$0x800725f6, %ecx       # imm = 0x800725F6
  589149:      	cmpl	%ecx, %eax
  58914b:      	jg	0x589171 <.text+0x188171>
  58914d:      	je	0x590603 <.text+0x18f603>
  589153:      	addl	$0x7ff8dae3, %eax       # imm = 0x7FF8DAE3
  589158:      	cmpl	$0xd8, %eax
  58915d:      	ja	0x591a16 <.text+0x190a16>
  589163:      	movzbl	0x594375(%eax), %eax
  58916a:      	jmpl	*0x59427d(,%eax,4)
  589171:      	movl	$0x8007273b, %ecx       # imm = 0x8007273B
  589176:      	cmpl	%ecx, %eax
  589178:      	jg	0x58926e <.text+0x18826e>
  58917e:      	je	0x5906fd <.text+0x18f6fd>
  589184:      	addl	$-0x2b, %ecx
  589187:      	cmpl	%ecx, %eax
  589189:      	jg	0x589252 <.text+0x188252>
  58918f:      	je	0x590667 <.text+0x18f667>
  589195:      	movl	$0x8007267a, %ecx       # imm = 0x8007267A
  58919a:      	cmpl	%ecx, %eax
  58919c:      	jg	0x5891fb <.text+0x1881fb>
  58919e:      	je	0x590649 <.text+0x18f649>
  5891a4:      	cmpl	$0x800725f7, %eax       # imm = 0x800725F7
  5891a9:      	je	0x59060d <.text+0x18f60d>
  5891af:      	cmpl	$0x80072616, %eax       # imm = 0x80072616
  5891b4:      	je	0x590617 <.text+0x18f617>
  5891ba:      	cmpl	$0x80072617, %eax       # imm = 0x80072617
  5891bf:      	je	0x590621 <.text+0x18f621>
  5891c5:      	cmpl	$0x80072618, %eax       # imm = 0x80072618
  5891ca:      	je	0x59062b <.text+0x18f62b>
  5891d0:      	cmpl	$0x80072619, %eax       # imm = 0x80072619
  5891d5:      	je	0x590635 <.text+0x18f635>
  5891db:      	cmpl	$0x80072648, %eax       # imm = 0x80072648
  5891e0:      	je	0x59063f <.text+0x18f63f>
  5891e6:      	cmpl	$0x80072649, %eax       # imm = 0x80072649
  5891eb:      	jne	0x591a16 <.text+0x190a16>
  5891f1:      	movl	$0x60522c, %eax         # imm = 0x60522C
  5891f6:      	jmp	0x591a45 <.text+0x190a45>
  5891fb:      	cmpl	$0x8007267b, %eax       # imm = 0x8007267B
  589200:      	je	0x590653 <.text+0x18f653>
  589206:      	cmpl	$0x8007267c, %eax       # imm = 0x8007267C
  58920b:      	je	0x59065d <.text+0x18f65d>
  589211:      	cmpl	$0x800726ac, %eax       # imm = 0x800726AC
  589216:      	je	0x590833 <.text+0x18f833>
  58921c:      	cmpl	$0x800726ad, %eax       # imm = 0x800726AD
  589221:      	je	0x59083d <.text+0x18f83d>
  589227:      	cmpl	$0x800726ae, %eax       # imm = 0x800726AE
  58922c:      	je	0x590847 <.text+0x18f847>
  589232:      	cmpl	$0x800726af, %eax       # imm = 0x800726AF
  589237:      	je	0x590851 <.text+0x18f851>
  58923d:      	cmpl	$0x800726b0, %eax       # imm = 0x800726B0
  589242:      	jne	0x591a16 <.text+0x190a16>
  589248:      	movl	$0x60520c, %eax         # imm = 0x60520C
  58924d:      	jmp	0x591a45 <.text+0x190a45>
  589252:      	addl	$0x7ff8d8ec, %eax       # imm = 0x7FF8D8EC
  589257:      	cmpl	$0x26, %eax
  58925a:      	ja	0x591a16 <.text+0x190a16>
  589260:      	movzbl	0x59448d(%eax), %eax
  589267:      	jmpl	*0x594451(,%eax,4)
  58926e:      	addl	$0x7ff8d8c4, %eax       # imm = 0x7FF8D8C4
  589273:      	cmpl	$0x2f, %eax
  589276:      	ja	0x591a16 <.text+0x190a16>
  58927c:      	movzbl	0x59452d(%eax), %eax
  589283:      	jmpl	*0x5944b5(,%eax,4)
  58928a:      	movl	$0x800732d9, %ecx       # imm = 0x800732D9
  58928f:      	cmpl	%ecx, %eax
  589291:      	jg	0x5893cc <.text+0x1883cc>
  589297:      	je	0x590b8b <.text+0x18fb8b>
  58929d:      	movl	$0x80072b0a, %ecx       # imm = 0x80072B0A
  5892a2:      	cmpl	%ecx, %eax
  5892a4:      	jg	0x589393 <.text+0x188393>
  5892aa:      	je	0x590a1c <.text+0x18fa1c>
  5892b0:      	addl	$-0xf, %ecx
  5892b3:      	cmpl	%ecx, %eax
  5892b5:      	jg	0x58937e <.text+0x18837e>
  5892bb:      	je	0x59095e <.text+0x18f95e>
  5892c1:      	movl	$0x8007277b, %ecx       # imm = 0x8007277B
  5892c6:      	cmpl	%ecx, %eax
  5892c8:      	jg	0x589327 <.text+0x188327>
  5892ca:      	je	0x590903 <.text+0x18f903>
  5892d0:      	cmpl	$0x8007276d, %eax       # imm = 0x8007276D
  5892d5:      	je	0x5908c7 <.text+0x18f8c7>
  5892db:      	cmpl	$0x80072775, %eax       # imm = 0x80072775
  5892e0:      	je	0x5908d1 <.text+0x18f8d1>
  5892e6:      	cmpl	$0x80072776, %eax       # imm = 0x80072776
  5892eb:      	je	0x5908db <.text+0x18f8db>
  5892f1:      	cmpl	$0x80072777, %eax       # imm = 0x80072777
  5892f6:      	je	0x5908e5 <.text+0x18f8e5>
  5892fc:      	cmpl	$0x80072778, %eax       # imm = 0x80072778
  589301:      	je	0x5908ef <.text+0x18f8ef>
  589307:      	cmpl	$0x80072779, %eax       # imm = 0x80072779
  58930c:      	je	0x5908f9 <.text+0x18f8f9>
  589312:      	cmpl	$0x8007277a, %eax       # imm = 0x8007277A
  589317:      	jne	0x591a16 <.text+0x190a16>
  58931d:      	movl	$0x6051f4, %eax         # imm = 0x6051F4
  589322:      	jmp	0x591a45 <.text+0x190a45>
  589327:      	cmpl	$0x8007277c, %eax       # imm = 0x8007277C
  58932c:      	je	0x59090d <.text+0x18f90d>
  589332:      	cmpl	$0x8007277d, %eax       # imm = 0x8007277D
  589337:      	je	0x590917 <.text+0x18f917>
  58933d:      	cmpl	$0x8007277e, %eax       # imm = 0x8007277E
  589342:      	je	0x590921 <.text+0x18f921>
  589348:      	cmpl	$0x8007277f, %eax       # imm = 0x8007277F
  58934d:      	je	0x59092b <.text+0x18f92b>
  589353:      	cmpl	$0x80072780, %eax       # imm = 0x80072780
  589358:      	je	0x590935 <.text+0x18f935>
  58935e:      	cmpl	$0x80072af9, %eax       # imm = 0x80072AF9
  589363:      	je	0x590954 <.text+0x18f954>
  589369:      	cmpl	$0x80072afa, %eax       # imm = 0x80072AFA
  58936e:      	jne	0x591a16 <.text+0x190a16>
  589374:      	movl	$0x6051e4, %eax         # imm = 0x6051E4
  589379:      	jmp	0x591a45 <.text+0x190a45>
  58937e:      	addl	$0x7ff8d504, %eax       # imm = 0x7FF8D504
  589383:      	cmpl	$0xd, %eax
  589386:      	ja	0x591a16 <.text+0x190a16>
  58938c:      	jmpl	*0x59455d(,%eax,4)
  589393:      	movl	$0x800732c8, %ecx       # imm = 0x800732C8
  589398:      	cmpl	%ecx, %eax
  58939a:      	jg	0x5893b7 <.text+0x1883b7>
  58939c:      	je	0x590aa8 <.text+0x18faa8>
  5893a2:      	addl	$0x7ff8d4f5, %eax       # imm = 0x7FF8D4F5
  5893a7:      	cmpl	$0xc, %eax
  5893aa:      	ja	0x591a16 <.text+0x190a16>
  5893b0:      	jmpl	*0x594595(,%eax,4)
  5893b7:      	addl	$0x7ff8cd37, %eax       # imm = 0x7FF8CD37
  5893bc:      	cmpl	$0xf, %eax
  5893bf:      	ja	0x591a16 <.text+0x190a16>
  5893c5:      	jmpl	*0x5945c9(,%eax,4)
  5893cc:      	movl	$0x80073602, %ecx       # imm = 0x80073602
  5893d1:      	cmpl	%ecx, %eax
  5893d3:      	jg	0x5894c2 <.text+0x1884c2>
  5893d9:      	je	0x590cc2 <.text+0x18fcc2>
  5893df:      	addl	$-0x11, %ecx
  5893e2:      	cmpl	%ecx, %eax
  5893e4:      	jg	0x5894ad <.text+0x1884ad>
  5893ea:      	je	0x590c2c <.text+0x18fc2c>
  5893f0:      	movl	$0x800735e9, %ecx       # imm = 0x800735E9
  5893f5:      	cmpl	%ecx, %eax
  5893f7:      	jg	0x589456 <.text+0x188456>
  5893f9:      	je	0x590be6 <.text+0x18fbe6>
  5893ff:      	cmpl	$0x800732da, %eax       # imm = 0x800732DA
  589404:      	je	0x590b95 <.text+0x18fb95>
  58940a:      	cmpl	$0x800732db, %eax       # imm = 0x800732DB
  58940f:      	je	0x590b9f <.text+0x18fb9f>
  589415:      	cmpl	$0x800732dc, %eax       # imm = 0x800732DC
  58941a:      	je	0x590ba9 <.text+0x18fba9>
  589420:      	cmpl	$0x800732dd, %eax       # imm = 0x800732DD
  589425:      	je	0x590bb3 <.text+0x18fbb3>
  58942b:      	cmpl	$0x800732de, %eax       # imm = 0x800732DE
  589430:      	je	0x590bbd <.text+0x18fbbd>
  589436:      	cmpl	$0x800732df, %eax       # imm = 0x800732DF
  58943b:      	je	0x590bc7 <.text+0x18fbc7>
  589441:      	cmpl	$0x800735e8, %eax       # imm = 0x800735E8
  589446:      	jne	0x591a16 <.text+0x190a16>
  58944c:      	movl	$0x6051c0, %eax         # imm = 0x6051C0
  589451:      	jmp	0x591a45 <.text+0x190a45>
  589456:      	cmpl	$0x800735ea, %eax       # imm = 0x800735EA
  58945b:      	je	0x590bf0 <.text+0x18fbf0>
  589461:      	cmpl	$0x800735eb, %eax       # imm = 0x800735EB
  589466:      	je	0x590bfa <.text+0x18fbfa>
  58946c:      	cmpl	$0x800735ec, %eax       # imm = 0x800735EC
  589471:      	je	0x590c04 <.text+0x18fc04>
  589477:      	cmpl	$0x800735ed, %eax       # imm = 0x800735ED
  58947c:      	je	0x590c0e <.text+0x18fc0e>
  589482:      	cmpl	$0x800735ee, %eax       # imm = 0x800735EE
  589487:      	je	0x590c18 <.text+0x18fc18>
  58948d:      	cmpl	$0x800735ef, %eax       # imm = 0x800735EF
  589492:      	je	0x590c22 <.text+0x18fc22>
  589498:      	cmpl	$0x800735f0, %eax       # imm = 0x800735F0
  58949d:      	jne	0x591a16 <.text+0x190a16>
  5894a3:      	movl	$0x6051a4, %eax         # imm = 0x6051A4
  5894a8:      	jmp	0x591a45 <.text+0x190a45>
  5894ad:      	addl	$0x7ff8ca0e, %eax       # imm = 0x7FF8CA0E
  5894b2:      	cmpl	$0xf, %eax
  5894b5:      	ja	0x591a16 <.text+0x190a16>
  5894bb:      	jmpl	*0x594609(,%eax,4)
  5894c2:      	addl	$0x7ff8c9fd, %eax       # imm = 0x7FF8C9FD
  5894c7:      	cmpl	$0x1c, %eax
  5894ca:      	ja	0x591a16 <.text+0x190a16>
  5894d0:      	jmpl	*0x594649(,%eax,4)
  5894d7:      	movl	$0x80073649, %ecx       # imm = 0x80073649
  5894dc:      	cmpl	%ecx, %eax
  5894de:      	jg	0x5894fb <.text+0x1884fb>
  5894e0:      	je	0x590f24 <.text+0x18ff24>
  5894e6:      	addl	$0x7ff8c9df, %eax       # imm = 0x7FF8C9DF
  5894eb:      	cmpl	$0x1a, %eax
  5894ee:      	ja	0x591a16 <.text+0x190a16>
  5894f4:      	jmpl	*0x5946bd(,%eax,4)
  5894fb:      	movl	$0x80080001, %ecx       # imm = 0x80080001
  589500:      	cmpl	%ecx, %eax
  589502:      	jg	0x589525 <.text+0x188525>
  589504:      	je	0x58951b <.text+0x18851b>
  589506:      	addl	$0x7ff8c950, %eax       # imm = 0x7FF8C950
  58950b:      	cmpl	$0x50, %eax
  58950e:      	ja	0x591a16 <.text+0x190a16>
  589514:      	jmpl	*0x594729(,%eax,4)
  58951b:      	movl	$0x605188, %eax         # imm = 0x605188
  589520:      	jmp	0x591a45 <.text+0x190a45>
  589525:      	movl	$0x80090001, %ecx       # imm = 0x80090001
  58952a:      	cmpl	%ecx, %eax
  58952c:      	jg	0x5895b7 <.text+0x1885b7>
  589532:      	je	0x5895ad <.text+0x1885ad>
  589534:      	addl	$0x7ff7fffe, %eax       # imm = 0x7FF7FFFE
  589539:      	cmpl	$0xf, %eax
  58953c:      	ja	0x591a16 <.text+0x190a16>
  589542:      	jmpl	*0x59486d(,%eax,4)
  589549:      	movl	$0x605178, %eax         # imm = 0x605178
  58954e:      	jmp	0x591a45 <.text+0x190a45>
  589553:      	movl	$0x605160, %eax         # imm = 0x605160
  589558:      	jmp	0x591a45 <.text+0x190a45>
  58955d:      	movl	$0x605150, %eax         # imm = 0x605150
  589562:      	jmp	0x591a45 <.text+0x190a45>
  589567:      	movl	$0x605134, %eax         # imm = 0x605134
  58956c:      	jmp	0x591a45 <.text+0x190a45>
  589571:      	movl	$0x60511c, %eax         # imm = 0x60511C
  589576:      	jmp	0x591a45 <.text+0x190a45>
  58957b:      	movl	$0x605108, %eax         # imm = 0x605108
  589580:      	jmp	0x591a45 <.text+0x190a45>
  589585:      	movl	$0x6050f0, %eax         # imm = 0x6050F0
  58958a:      	jmp	0x591a45 <.text+0x190a45>
  58958f:      	movl	$0x6050dc, %eax         # imm = 0x6050DC
  589594:      	jmp	0x591a45 <.text+0x190a45>
  589599:      	movl	$0x6050c8, %eax         # imm = 0x6050C8
  58959e:      	jmp	0x591a45 <.text+0x190a45>
  5895a3:      	movl	$0x6050b4, %eax         # imm = 0x6050B4
  5895a8:      	jmp	0x591a45 <.text+0x190a45>
  5895ad:      	movl	$0x6050a8, %eax         # imm = 0x6050A8
  5895b2:      	jmp	0x591a45 <.text+0x190a45>
  5895b7:      	movl	$0x80090300, %ecx       # imm = 0x80090300
  5895bc:      	cmpl	%ecx, %eax
  5895be:      	jg	0x589751 <.text+0x188751>
  5895c4:      	je	0x589747 <.text+0x188747>
  5895ca:      	addl	$0x7ff6fffe, %eax       # imm = 0x7FF6FFFE
  5895cf:      	cmpl	$0x23, %eax
  5895d2:      	ja	0x591a16 <.text+0x190a16>
  5895d8:      	jmpl	*0x5948ad(,%eax,4)
  5895df:      	movl	$0x605098, %eax         # imm = 0x605098
  5895e4:      	jmp	0x591a45 <.text+0x190a45>
  5895e9:      	movl	$0x60508c, %eax         # imm = 0x60508C
  5895ee:      	jmp	0x591a45 <.text+0x190a45>
  5895f3:      	movl	$0x605080, %eax         # imm = 0x605080
  5895f8:      	jmp	0x591a45 <.text+0x190a45>
  5895fd:      	movl	$0x605070, %eax         # imm = 0x605070
  589602:      	jmp	0x591a45 <.text+0x190a45>
  589607:      	movl	$0x60505c, %eax         # imm = 0x60505C
  58960c:      	jmp	0x591a45 <.text+0x190a45>
  589611:      	movl	$0x605050, %eax         # imm = 0x605050
  589616:      	jmp	0x591a45 <.text+0x190a45>
  58961b:      	movl	$0x605040, %eax         # imm = 0x605040
  589620:      	jmp	0x591a45 <.text+0x190a45>
  589625:      	movl	$0x605030, %eax         # imm = 0x605030
  58962a:      	jmp	0x591a45 <.text+0x190a45>
  58962f:      	movl	$0x605020, %eax         # imm = 0x605020
  589634:      	jmp	0x591a45 <.text+0x190a45>
  589639:      	movl	$0x60500c, %eax         # imm = 0x60500C
  58963e:      	jmp	0x591a45 <.text+0x190a45>
  589643:      	movl	$0x604ff8, %eax         # imm = 0x604FF8
  589648:      	jmp	0x591a45 <.text+0x190a45>
  58964d:      	movl	$0x604fec, %eax         # imm = 0x604FEC
  589652:      	jmp	0x591a45 <.text+0x190a45>
  589657:      	movl	$0x604fdc, %eax         # imm = 0x604FDC
  58965c:      	jmp	0x591a45 <.text+0x190a45>
  589661:      	movl	$0x604fd0, %eax         # imm = 0x604FD0
  589666:      	jmp	0x591a45 <.text+0x190a45>
  58966b:      	movl	$0x604fc4, %eax         # imm = 0x604FC4
  589670:      	jmp	0x591a45 <.text+0x190a45>
  589675:      	movl	$0x604fb4, %eax         # imm = 0x604FB4
  58967a:      	jmp	0x591a45 <.text+0x190a45>
  58967f:      	movl	$0x604fa0, %eax         # imm = 0x604FA0
  589684:      	jmp	0x591a45 <.text+0x190a45>
  589689:      	movl	$0x604f8c, %eax         # imm = 0x604F8C
  58968e:      	jmp	0x591a45 <.text+0x190a45>
  589693:      	movl	$0x604f78, %eax         # imm = 0x604F78
  589698:      	jmp	0x591a45 <.text+0x190a45>
  58969d:      	movl	$0x604f64, %eax         # imm = 0x604F64
  5896a2:      	jmp	0x591a45 <.text+0x190a45>
  5896a7:      	movl	$0x604f54, %eax         # imm = 0x604F54
  5896ac:      	jmp	0x591a45 <.text+0x190a45>
  5896b1:      	movl	$0x604f3c, %eax         # imm = 0x604F3C
  5896b6:      	jmp	0x591a45 <.text+0x190a45>
  5896bb:      	movl	$0x604f24, %eax         # imm = 0x604F24
  5896c0:      	jmp	0x591a45 <.text+0x190a45>
  5896c5:      	movl	$0x604f10, %eax         # imm = 0x604F10
  5896ca:      	jmp	0x591a45 <.text+0x190a45>
  5896cf:      	movl	$0x604ef8, %eax         # imm = 0x604EF8
  5896d4:      	jmp	0x591a45 <.text+0x190a45>
  5896d9:      	movl	$0x604ee0, %eax         # imm = 0x604EE0
  5896de:      	jmp	0x591a45 <.text+0x190a45>
  5896e3:      	movl	$0x604ec8, %eax         # imm = 0x604EC8
  5896e8:      	jmp	0x591a45 <.text+0x190a45>
  5896ed:      	movl	$0x604eb0, %eax         # imm = 0x604EB0
  5896f2:      	jmp	0x591a45 <.text+0x190a45>
  5896f7:      	movl	$0x604e98, %eax         # imm = 0x604E98
  5896fc:      	jmp	0x591a45 <.text+0x190a45>
  589701:      	movl	$0x604e80, %eax         # imm = 0x604E80
  589706:      	jmp	0x591a45 <.text+0x190a45>
  58970b:      	movl	$0x604e74, %eax         # imm = 0x604E74
  589710:      	jmp	0x591a45 <.text+0x190a45>
  589715:      	movl	$0x604e68, %eax         # imm = 0x604E68
  58971a:      	jmp	0x591a45 <.text+0x190a45>
  58971f:      	movl	$0x604e54, %eax         # imm = 0x604E54
  589724:      	jmp	0x591a45 <.text+0x190a45>
  589729:      	movl	$0x604e34, %eax         # imm = 0x604E34
  58972e:      	jmp	0x591a45 <.text+0x190a45>
  589733:      	movl	$0x604e1c, %eax         # imm = 0x604E1C
  589738:      	jmp	0x591a45 <.text+0x190a45>
  58973d:      	movl	$0x604e08, %eax         # imm = 0x604E08
  589742:      	jmp	0x591a45 <.text+0x190a45>
  589747:      	movl	$0x604dec, %eax         # imm = 0x604DEC
  58974c:      	jmp	0x591a45 <.text+0x190a45>
  589751:      	movl	$0x80091001, %ecx       # imm = 0x80091001
  589756:      	cmpl	%ecx, %eax
  589758:      	jg	0x5899ce <.text+0x1889ce>
  58975e:      	je	0x5899c4 <.text+0x1889c4>
  589764:      	addl	$0x7ff6fcff, %eax       # imm = 0x7FF6FCFF
  589769:      	cmpl	$0x54, %eax
  58976c:      	ja	0x591a16 <.text+0x190a16>
  589772:      	movzbl	0x594a29(%eax), %eax
  589779:      	jmpl	*0x59493d(,%eax,4)
  589780:      	movl	$0x604dd4, %eax         # imm = 0x604DD4
  589785:      	jmp	0x591a45 <.text+0x190a45>
  58978a:      	movl	$0x604db8, %eax         # imm = 0x604DB8
  58978f:      	jmp	0x591a45 <.text+0x190a45>
  589794:      	movl	$0x604da0, %eax         # imm = 0x604DA0
  589799:      	jmp	0x591a45 <.text+0x190a45>
  58979e:      	movl	$0x604d88, %eax         # imm = 0x604D88
  5897a3:      	jmp	0x591a45 <.text+0x190a45>
  5897a8:      	movl	$0x604d70, %eax         # imm = 0x604D70
  5897ad:      	jmp	0x591a45 <.text+0x190a45>
  5897b2:      	movl	$0x604d60, %eax         # imm = 0x604D60
  5897b7:      	jmp	0x591a45 <.text+0x190a45>
  5897bc:      	movl	$0x604d48, %eax         # imm = 0x604D48
  5897c1:      	jmp	0x591a45 <.text+0x190a45>
  5897c6:      	movl	$0x604d34, %eax         # imm = 0x604D34
  5897cb:      	jmp	0x591a45 <.text+0x190a45>
  5897d0:      	movl	$0x604d20, %eax         # imm = 0x604D20
  5897d5:      	jmp	0x591a45 <.text+0x190a45>
  5897da:      	movl	$0x604d08, %eax         # imm = 0x604D08
  5897df:      	jmp	0x591a45 <.text+0x190a45>
  5897e4:      	movl	$0x604cf0, %eax         # imm = 0x604CF0
  5897e9:      	jmp	0x591a45 <.text+0x190a45>
  5897ee:      	movl	$0x604cdc, %eax         # imm = 0x604CDC
  5897f3:      	jmp	0x591a45 <.text+0x190a45>
  5897f8:      	movl	$0x604cc0, %eax         # imm = 0x604CC0
  5897fd:      	jmp	0x591a45 <.text+0x190a45>
  589802:      	movl	$0x604ca8, %eax         # imm = 0x604CA8
  589807:      	jmp	0x591a45 <.text+0x190a45>
  58980c:      	movl	$0x604c90, %eax         # imm = 0x604C90
  589811:      	jmp	0x591a45 <.text+0x190a45>
  589816:      	movl	$0x604c78, %eax         # imm = 0x604C78
  58981b:      	jmp	0x591a45 <.text+0x190a45>
  589820:      	movl	$0x604c54, %eax         # imm = 0x604C54
  589825:      	jmp	0x591a45 <.text+0x190a45>
  58982a:      	movl	$0x604c44, %eax         # imm = 0x604C44
  58982f:      	jmp	0x591a45 <.text+0x190a45>
  589834:      	movl	$0x604c2c, %eax         # imm = 0x604C2C
  589839:      	jmp	0x591a45 <.text+0x190a45>
  58983e:      	movl	$0x604c10, %eax         # imm = 0x604C10
  589843:      	jmp	0x591a45 <.text+0x190a45>
  589848:      	movl	$0x604bf0, %eax         # imm = 0x604BF0
  58984d:      	jmp	0x591a45 <.text+0x190a45>
  589852:      	movl	$0x604bd8, %eax         # imm = 0x604BD8
  589857:      	jmp	0x591a45 <.text+0x190a45>
  58985c:      	movl	$0x604bc0, %eax         # imm = 0x604BC0
  589861:      	jmp	0x591a45 <.text+0x190a45>
  589866:      	movl	$0x604bb0, %eax         # imm = 0x604BB0
  58986b:      	jmp	0x591a45 <.text+0x190a45>
  589870:      	movl	$0x604b98, %eax         # imm = 0x604B98
  589875:      	jmp	0x591a45 <.text+0x190a45>
  58987a:      	movl	$0x604b80, %eax         # imm = 0x604B80
  58987f:      	jmp	0x591a45 <.text+0x190a45>
  589884:      	movl	$0x604b6c, %eax         # imm = 0x604B6C
  589889:      	jmp	0x591a45 <.text+0x190a45>
  58988e:      	movl	$0x604b58, %eax         # imm = 0x604B58
  589893:      	jmp	0x591a45 <.text+0x190a45>
  589898:      	movl	$0x604b40, %eax         # imm = 0x604B40
  58989d:      	jmp	0x591a45 <.text+0x190a45>
  5898a2:      	movl	$0x604b28, %eax         # imm = 0x604B28
  5898a7:      	jmp	0x591a45 <.text+0x190a45>
  5898ac:      	movl	$0x604b0c, %eax         # imm = 0x604B0C
  5898b1:      	jmp	0x591a45 <.text+0x190a45>
  5898b6:      	movl	$0x604af0, %eax         # imm = 0x604AF0
  5898bb:      	jmp	0x591a45 <.text+0x190a45>
  5898c0:      	movl	$0x604acc, %eax         # imm = 0x604ACC
  5898c5:      	jmp	0x591a45 <.text+0x190a45>
  5898ca:      	movl	$0x604ab8, %eax         # imm = 0x604AB8
  5898cf:      	jmp	0x591a45 <.text+0x190a45>
  5898d4:      	movl	$0x604aa0, %eax         # imm = 0x604AA0
  5898d9:      	jmp	0x591a45 <.text+0x190a45>
  5898de:      	movl	$0x604a80, %eax         # imm = 0x604A80
  5898e3:      	jmp	0x591a45 <.text+0x190a45>
  5898e8:      	movl	$0x604a64, %eax         # imm = 0x604A64
  5898ed:      	jmp	0x591a45 <.text+0x190a45>
  5898f2:      	movl	$0x604a44, %eax         # imm = 0x604A44
  5898f7:      	jmp	0x591a45 <.text+0x190a45>
  5898fc:      	movl	$0x604a30, %eax         # imm = 0x604A30
  589901:      	jmp	0x591a45 <.text+0x190a45>
  589906:      	movl	$0x604a0c, %eax         # imm = 0x604A0C
  58990b:      	jmp	0x591a45 <.text+0x190a45>
  589910:      	movl	$0x6049f0, %eax         # imm = 0x6049F0
  589915:      	jmp	0x591a45 <.text+0x190a45>
  58991a:      	movl	$0x6049dc, %eax         # imm = 0x6049DC
  58991f:      	jmp	0x591a45 <.text+0x190a45>
  589924:      	movl	$0x6049c0, %eax         # imm = 0x6049C0
  589929:      	jmp	0x591a45 <.text+0x190a45>
  58992e:      	movl	$0x6049a0, %eax         # imm = 0x6049A0
  589933:      	jmp	0x591a45 <.text+0x190a45>
  589938:      	movl	$0x604984, %eax         # imm = 0x604984
  58993d:      	jmp	0x591a45 <.text+0x190a45>
  589942:      	movl	$0x604968, %eax         # imm = 0x604968
  589947:      	jmp	0x591a45 <.text+0x190a45>
  58994c:      	movl	$0x60494c, %eax         # imm = 0x60494C
  589951:      	jmp	0x591a45 <.text+0x190a45>
  589956:      	movl	$0x604934, %eax         # imm = 0x604934
  58995b:      	jmp	0x591a45 <.text+0x190a45>
  589960:      	movl	$0x604918, %eax         # imm = 0x604918
  589965:      	jmp	0x591a45 <.text+0x190a45>
  58996a:      	movl	$0x6048fc, %eax         # imm = 0x6048FC
  58996f:      	jmp	0x591a45 <.text+0x190a45>
  589974:      	movl	$0x6048e8, %eax         # imm = 0x6048E8
  589979:      	jmp	0x591a45 <.text+0x190a45>
  58997e:      	movl	$0x6048d0, %eax         # imm = 0x6048D0
  589983:      	jmp	0x591a45 <.text+0x190a45>
  589988:      	movl	$0x6048bc, %eax         # imm = 0x6048BC
  58998d:      	jmp	0x591a45 <.text+0x190a45>
  589992:      	movl	$0x60489c, %eax         # imm = 0x60489C
  589997:      	jmp	0x591a45 <.text+0x190a45>
  58999c:      	movl	$0x604880, %eax         # imm = 0x604880
  5899a1:      	jmp	0x591a45 <.text+0x190a45>
  5899a6:      	movl	$0x604864, %eax         # imm = 0x604864
  5899ab:      	jmp	0x591a45 <.text+0x190a45>
  5899b0:      	movl	$0x604848, %eax         # imm = 0x604848
  5899b5:      	jmp	0x591a45 <.text+0x190a45>
  5899ba:      	movl	$0x604828, %eax         # imm = 0x604828
  5899bf:      	jmp	0x591a45 <.text+0x190a45>
  5899c4:      	movl	$0x604814, %eax         # imm = 0x604814
  5899c9:      	jmp	0x591a45 <.text+0x190a45>
  5899ce:      	movl	$0x80092001, %ecx       # imm = 0x80092001
  5899d3:      	cmpl	%ecx, %eax
  5899d5:      	jg	0x589aa0 <.text+0x188aa0>
  5899db:      	je	0x589a96 <.text+0x188a96>
  5899e1:      	addl	$0x7ff6effe, %eax       # imm = 0x7FF6EFFE
  5899e6:      	cmpl	$0xf, %eax
  5899e9:      	ja	0x591a16 <.text+0x190a16>
  5899ef:      	jmpl	*0x594a81(,%eax,4)
  5899f6:      	movl	$0x6047fc, %eax         # imm = 0x6047FC
  5899fb:      	jmp	0x591a45 <.text+0x190a45>
  589a00:      	movl	$0x6047e8, %eax         # imm = 0x6047E8
  589a05:      	jmp	0x591a45 <.text+0x190a45>
  589a0a:      	movl	$0x6047cc, %eax         # imm = 0x6047CC
  589a0f:      	jmp	0x591a45 <.text+0x190a45>
  589a14:      	movl	$0x6047b0, %eax         # imm = 0x6047B0
  589a19:      	jmp	0x591a45 <.text+0x190a45>
  589a1e:      	movl	$0x604794, %eax         # imm = 0x604794
  589a23:      	jmp	0x591a45 <.text+0x190a45>
  589a28:      	movl	$0x604780, %eax         # imm = 0x604780
  589a2d:      	jmp	0x591a45 <.text+0x190a45>
  589a32:      	movl	$0x604768, %eax         # imm = 0x604768
  589a37:      	jmp	0x591a45 <.text+0x190a45>
  589a3c:      	movl	$0x60474c, %eax         # imm = 0x60474C
  589a41:      	jmp	0x591a45 <.text+0x190a45>
  589a46:      	movl	$0x604734, %eax         # imm = 0x604734
  589a4b:      	jmp	0x591a45 <.text+0x190a45>
  589a50:      	movl	$0x604718, %eax         # imm = 0x604718
  589a55:      	jmp	0x591a45 <.text+0x190a45>
  589a5a:      	movl	$0x604700, %eax         # imm = 0x604700
  589a5f:      	jmp	0x591a45 <.text+0x190a45>
  589a64:      	movl	$0x6046e4, %eax         # imm = 0x6046E4
  589a69:      	jmp	0x591a45 <.text+0x190a45>
  589a6e:      	movl	$0x6046c8, %eax         # imm = 0x6046C8
  589a73:      	jmp	0x591a45 <.text+0x190a45>
  589a78:      	movl	$0x6046ac, %eax         # imm = 0x6046AC
  589a7d:      	jmp	0x591a45 <.text+0x190a45>
  589a82:      	movl	$0x60468c, %eax         # imm = 0x60468C
  589a87:      	jmp	0x591a45 <.text+0x190a45>
  589a8c:      	movl	$0x604668, %eax         # imm = 0x604668
  589a91:      	jmp	0x591a45 <.text+0x190a45>
  589a96:      	movl	$0x604658, %eax         # imm = 0x604658
  589a9b:      	jmp	0x591a45 <.text+0x190a45>
  589aa0:      	addl	$0x7ff6dffe, %eax       # imm = 0x7FF6DFFE
  589aa5:      	cmpl	$0xa, %eax
  589aa8:      	ja	0x591a16 <.text+0x190a16>
  589aae:      	jmpl	*0x594ac1(,%eax,4)
  589ab5:      	movl	$0x604644, %eax         # imm = 0x604644
  589aba:      	jmp	0x591a45 <.text+0x190a45>
  589abf:      	movl	$0x604630, %eax         # imm = 0x604630
  589ac4:      	jmp	0x591a45 <.text+0x190a45>
  589ac9:      	movl	$0x60461c, %eax         # imm = 0x60461C
  589ace:      	jmp	0x591a45 <.text+0x190a45>
  589ad3:      	movl	$0x60460c, %eax         # imm = 0x60460C
  589ad8:      	jmp	0x591a45 <.text+0x190a45>
  589add:      	movl	$0x6045f8, %eax         # imm = 0x6045F8
  589ae2:      	jmp	0x591a45 <.text+0x190a45>
  589ae7:      	movl	$0x6045e4, %eax         # imm = 0x6045E4
  589aec:      	jmp	0x591a45 <.text+0x190a45>
  589af1:      	movl	$0x6045cc, %eax         # imm = 0x6045CC
  589af6:      	jmp	0x591a45 <.text+0x190a45>
  589afb:      	movl	$0x6045b8, %eax         # imm = 0x6045B8
  589b00:      	jmp	0x591a45 <.text+0x190a45>
  589b05:      	movl	$0x60459c, %eax         # imm = 0x60459C
  589b0a:      	jmp	0x591a45 <.text+0x190a45>
  589b0f:      	movl	$0x604584, %eax         # imm = 0x604584
  589b14:      	jmp	0x591a45 <.text+0x190a45>
  589b19:      	movl	$0x60456c, %eax         # imm = 0x60456C
  589b1e:      	jmp	0x591a45 <.text+0x190a45>
  589b23:      	movl	$0x60455c, %eax         # imm = 0x60455C
  589b28:      	jmp	0x591a45 <.text+0x190a45>
  589b2d:      	movl	$0x80093000, %ecx       # imm = 0x80093000
  589b32:      	cmpl	%ecx, %eax
  589b34:      	jg	0x589c2e <.text+0x188c2e>
  589b3a:      	je	0x589c24 <.text+0x188c24>
  589b40:      	addl	$0x7ff6dff2, %eax       # imm = 0x7FF6DFF2
  589b45:      	cmpl	$0x1e, %eax
  589b48:      	ja	0x591a16 <.text+0x190a16>
  589b4e:      	movzbl	0x594b41(%eax), %eax
  589b55:      	jmpl	*0x594aed(,%eax,4)
  589b5c:      	movl	$0x604548, %eax         # imm = 0x604548
  589b61:      	jmp	0x591a45 <.text+0x190a45>
  589b66:      	movl	$0x604530, %eax         # imm = 0x604530
  589b6b:      	jmp	0x591a45 <.text+0x190a45>
  589b70:      	movl	$0x604520, %eax         # imm = 0x604520
  589b75:      	jmp	0x591a45 <.text+0x190a45>
  589b7a:      	movl	$0x604504, %eax         # imm = 0x604504
  589b7f:      	jmp	0x591a45 <.text+0x190a45>
  589b84:      	movl	$0x6044e8, %eax         # imm = 0x6044E8
  589b89:      	jmp	0x591a45 <.text+0x190a45>
  589b8e:      	movl	$0x6044cc, %eax         # imm = 0x6044CC
  589b93:      	jmp	0x591a45 <.text+0x190a45>
  589b98:      	movl	$0x6044a8, %eax         # imm = 0x6044A8
  589b9d:      	jmp	0x591a45 <.text+0x190a45>
  589ba2:      	movl	$0x604488, %eax         # imm = 0x604488
  589ba7:      	jmp	0x591a45 <.text+0x190a45>
  589bac:      	movl	$0x604464, %eax         # imm = 0x604464
  589bb1:      	jmp	0x591a45 <.text+0x190a45>
  589bb6:      	movl	$0x604448, %eax         # imm = 0x604448
  589bbb:      	jmp	0x591a45 <.text+0x190a45>
  589bc0:      	movl	$0x60442c, %eax         # imm = 0x60442C
  589bc5:      	jmp	0x591a45 <.text+0x190a45>
  589bca:      	movl	$0x604414, %eax         # imm = 0x604414
  589bcf:      	jmp	0x591a45 <.text+0x190a45>
  589bd4:      	movl	$0x604400, %eax         # imm = 0x604400
  589bd9:      	jmp	0x591a45 <.text+0x190a45>
  589bde:      	movl	$0x6043e4, %eax         # imm = 0x6043E4
  589be3:      	jmp	0x591a45 <.text+0x190a45>
  589be8:      	movl	$0x6043c8, %eax         # imm = 0x6043C8
  589bed:      	jmp	0x591a45 <.text+0x190a45>
  589bf2:      	movl	$0x6043a8, %eax         # imm = 0x6043A8
  589bf7:      	jmp	0x591a45 <.text+0x190a45>
  589bfc:      	movl	$0x604388, %eax         # imm = 0x604388
  589c01:      	jmp	0x591a45 <.text+0x190a45>
  589c06:      	movl	$0x604374, %eax         # imm = 0x604374
  589c0b:      	jmp	0x591a45 <.text+0x190a45>
  589c10:      	movl	$0x604358, %eax         # imm = 0x604358
  589c15:      	jmp	0x591a45 <.text+0x190a45>
  589c1a:      	movl	$0x60433c, %eax         # imm = 0x60433C
  589c1f:      	jmp	0x591a45 <.text+0x190a45>
  589c24:      	movl	$0x604328, %eax         # imm = 0x604328
  589c29:      	jmp	0x591a45 <.text+0x190a45>
  589c2e:      	movl	$0x80093100, %ecx       # imm = 0x80093100
  589c33:      	cmpl	%ecx, %eax
  589c35:      	jg	0x589e2c <.text+0x188e2c>
  589c3b:      	je	0x589e22 <.text+0x188e22>
  589c41:      	addl	$0x7ff6cfff, %eax       # imm = 0x7FF6CFFF
  589c46:      	cmpl	$0x2d, %eax
  589c49:      	ja	0x591a16 <.text+0x190a16>
  589c4f:      	jmpl	*0x594b61(,%eax,4)
  589c56:      	movl	$0x604318, %eax         # imm = 0x604318
  589c5b:      	jmp	0x591a45 <.text+0x190a45>
  589c60:      	movl	$0x604300, %eax         # imm = 0x604300
  589c65:      	jmp	0x591a45 <.text+0x190a45>
  589c6a:      	movl	$0x6042f0, %eax         # imm = 0x6042F0
  589c6f:      	jmp	0x591a45 <.text+0x190a45>
  589c74:      	movl	$0x6042e0, %eax         # imm = 0x6042E0
  589c79:      	jmp	0x591a45 <.text+0x190a45>
  589c7e:      	movl	$0x6042d0, %eax         # imm = 0x6042D0
  589c83:      	jmp	0x591a45 <.text+0x190a45>
  589c88:      	movl	$0x6042c4, %eax         # imm = 0x6042C4
  589c8d:      	jmp	0x591a45 <.text+0x190a45>
  589c92:      	movl	$0x6042b4, %eax         # imm = 0x6042B4
  589c97:      	jmp	0x591a45 <.text+0x190a45>
  589c9c:      	movl	$0x6042a4, %eax         # imm = 0x6042A4
  589ca1:      	jmp	0x591a45 <.text+0x190a45>
  589ca6:      	movl	$0x604290, %eax         # imm = 0x604290
  589cab:      	jmp	0x591a45 <.text+0x190a45>
  589cb0:      	movl	$0x604284, %eax         # imm = 0x604284
  589cb5:      	jmp	0x591a45 <.text+0x190a45>
  589cba:      	movl	$0x604278, %eax         # imm = 0x604278
  589cbf:      	jmp	0x591a45 <.text+0x190a45>
  589cc4:      	movl	$0x604268, %eax         # imm = 0x604268
  589cc9:      	jmp	0x591a45 <.text+0x190a45>
  589cce:      	movl	$0x604248, %eax         # imm = 0x604248
  589cd3:      	jmp	0x591a45 <.text+0x190a45>
  589cd8:      	movl	$0x604238, %eax         # imm = 0x604238
  589cdd:      	jmp	0x591a45 <.text+0x190a45>
  589ce2:      	movl	$0x604228, %eax         # imm = 0x604228
  589ce7:      	jmp	0x591a45 <.text+0x190a45>
  589cec:      	movl	$0x604218, %eax         # imm = 0x604218
  589cf1:      	jmp	0x591a45 <.text+0x190a45>
  589cf6:      	movl	$0x604200, %eax         # imm = 0x604200
  589cfb:      	jmp	0x591a45 <.text+0x190a45>
  589d00:      	movl	$0x6041f0, %eax         # imm = 0x6041F0
  589d05:      	jmp	0x591a45 <.text+0x190a45>
  589d0a:      	movl	$0x6041d0, %eax         # imm = 0x6041D0
  589d0f:      	jmp	0x591a45 <.text+0x190a45>
  589d14:      	movl	$0x6041c0, %eax         # imm = 0x6041C0
  589d19:      	jmp	0x591a45 <.text+0x190a45>
  589d1e:      	movl	$0x6041b0, %eax         # imm = 0x6041B0
  589d23:      	jmp	0x591a45 <.text+0x190a45>
  589d28:      	movl	$0x60419c, %eax         # imm = 0x60419C
  589d2d:      	jmp	0x591a45 <.text+0x190a45>
  589d32:      	movl	$0x604184, %eax         # imm = 0x604184
  589d37:      	jmp	0x591a45 <.text+0x190a45>
  589d3c:      	movl	$0x604168, %eax         # imm = 0x604168
  589d41:      	jmp	0x591a45 <.text+0x190a45>
  589d46:      	movl	$0x604154, %eax         # imm = 0x604154
  589d4b:      	jmp	0x591a45 <.text+0x190a45>
  589d50:      	movl	$0x60413c, %eax         # imm = 0x60413C
  589d55:      	jmp	0x591a45 <.text+0x190a45>
  589d5a:      	movl	$0x604120, %eax         # imm = 0x604120
  589d5f:      	jmp	0x591a45 <.text+0x190a45>
  589d64:      	movl	$0x604104, %eax         # imm = 0x604104
  589d69:      	jmp	0x591a45 <.text+0x190a45>
  589d6e:      	movl	$0x6040f0, %eax         # imm = 0x6040F0
  589d73:      	jmp	0x591a45 <.text+0x190a45>
  589d78:      	movl	$0x6040d8, %eax         # imm = 0x6040D8
  589d7d:      	jmp	0x591a45 <.text+0x190a45>
  589d82:      	movl	$0x6040c0, %eax         # imm = 0x6040C0
  589d87:      	jmp	0x591a45 <.text+0x190a45>
  589d8c:      	movl	$0x6040a4, %eax         # imm = 0x6040A4
  589d91:      	jmp	0x591a45 <.text+0x190a45>
  589d96:      	movl	$0x604090, %eax         # imm = 0x604090
  589d9b:      	jmp	0x591a45 <.text+0x190a45>
  589da0:      	movl	$0x604074, %eax         # imm = 0x604074
  589da5:      	jmp	0x591a45 <.text+0x190a45>
  589daa:      	movl	$0x604054, %eax         # imm = 0x604054
  589daf:      	jmp	0x591a45 <.text+0x190a45>
  589db4:      	movl	$0x604034, %eax         # imm = 0x604034
  589db9:      	jmp	0x591a45 <.text+0x190a45>
  589dbe:      	movl	$0x604014, %eax         # imm = 0x604014
  589dc3:      	jmp	0x591a45 <.text+0x190a45>
  589dc8:      	movl	$0x603ff8, %eax         # imm = 0x603FF8
  589dcd:      	jmp	0x591a45 <.text+0x190a45>
  589dd2:      	movl	$0x603fe0, %eax         # imm = 0x603FE0
  589dd7:      	jmp	0x591a45 <.text+0x190a45>
  589ddc:      	movl	$0x603fc8, %eax         # imm = 0x603FC8
  589de1:      	jmp	0x591a45 <.text+0x190a45>
  589de6:      	movl	$0x603fb0, %eax         # imm = 0x603FB0
  589deb:      	jmp	0x591a45 <.text+0x190a45>
  589df0:      	movl	$0x603f94, %eax         # imm = 0x603F94
  589df5:      	jmp	0x591a45 <.text+0x190a45>
  589dfa:      	movl	$0x603f7c, %eax         # imm = 0x603F7C
  589dff:      	jmp	0x591a45 <.text+0x190a45>
  589e04:      	movl	$0x603f68, %eax         # imm = 0x603F68
  589e09:      	jmp	0x591a45 <.text+0x190a45>
  589e0e:      	movl	$0x603f50, %eax         # imm = 0x603F50
  589e13:      	jmp	0x591a45 <.text+0x190a45>
  589e18:      	movl	$0x603f34, %eax         # imm = 0x603F34
  589e1d:      	jmp	0x591a45 <.text+0x190a45>
  589e22:      	movl	$0x603f20, %eax         # imm = 0x603F20
  589e27:      	jmp	0x591a45 <.text+0x190a45>
  589e2c:      	movl	$0x80093133, %ecx       # imm = 0x80093133
  589e31:      	cmpl	%ecx, %eax
  589e33:      	jg	0x589eea <.text+0x188eea>
  589e39:      	je	0x589ee0 <.text+0x188ee0>
  589e3f:      	addl	$0x7ff6ceff, %eax       # imm = 0x7FF6CEFF
  589e44:      	cmpl	$0xd, %eax
  589e47:      	ja	0x591a16 <.text+0x190a16>
  589e4d:      	jmpl	*0x594c19(,%eax,4)
  589e54:      	movl	$0x603f08, %eax         # imm = 0x603F08
  589e59:      	jmp	0x591a45 <.text+0x190a45>
  589e5e:      	movl	$0x603ef4, %eax         # imm = 0x603EF4
  589e63:      	jmp	0x591a45 <.text+0x190a45>
  589e68:      	movl	$0x603edc, %eax         # imm = 0x603EDC
  589e6d:      	jmp	0x591a45 <.text+0x190a45>
  589e72:      	movl	$0x603ec8, %eax         # imm = 0x603EC8
  589e77:      	jmp	0x591a45 <.text+0x190a45>
  589e7c:      	movl	$0x603eb0, %eax         # imm = 0x603EB0
  589e81:      	jmp	0x591a45 <.text+0x190a45>
  589e86:      	movl	$0x603e9c, %eax         # imm = 0x603E9C
  589e8b:      	jmp	0x591a45 <.text+0x190a45>
  589e90:      	movl	$0x603e84, %eax         # imm = 0x603E84
  589e95:      	jmp	0x591a45 <.text+0x190a45>
  589e9a:      	movl	$0x603e70, %eax         # imm = 0x603E70
  589e9f:      	jmp	0x591a45 <.text+0x190a45>
  589ea4:      	movl	$0x603e58, %eax         # imm = 0x603E58
  589ea9:      	jmp	0x591a45 <.text+0x190a45>
  589eae:      	movl	$0x603e40, %eax         # imm = 0x603E40
  589eb3:      	jmp	0x591a45 <.text+0x190a45>
  589eb8:      	movl	$0x603e2c, %eax         # imm = 0x603E2C
  589ebd:      	jmp	0x591a45 <.text+0x190a45>
  589ec2:      	movl	$0x603e18, %eax         # imm = 0x603E18
  589ec7:      	jmp	0x591a45 <.text+0x190a45>
  589ecc:      	movl	$0x603e04, %eax         # imm = 0x603E04
  589ed1:      	jmp	0x591a45 <.text+0x190a45>
  589ed6:      	movl	$0x603df0, %eax         # imm = 0x603DF0
  589edb:      	jmp	0x591a45 <.text+0x190a45>
  589ee0:      	movl	$0x603dd8, %eax         # imm = 0x603DD8
  589ee5:      	jmp	0x591a45 <.text+0x190a45>
  589eea:      	movl	$0x6b1, %ecx            # imm = 0x6B1
  589eef:      	cmpl	%ecx, %eax
  589ef1:      	jg	0x58df50 <.text+0x18cf50>
  589ef7:      	je	0x58df46 <.text+0x18cf46>
  589efd:      	movl	$0x8ac70105, %ecx       # imm = 0x8AC70105
  589f02:      	cmpl	%ecx, %eax
  589f04:      	jg	0x58c341 <.text+0x18b341>
  589f0a:      	je	0x58c337 <.text+0x18b337>
  589f10:      	movl	$0x8011080e, %ecx       # imm = 0x8011080E
  589f15:      	cmpl	%ecx, %eax
  589f17:      	jg	0x58aff9 <.text+0x189ff9>
  589f1d:      	je	0x58afef <.text+0x189fef>
  589f23:      	movl	$0x800f022e, %ecx       # imm = 0x800F022E
  589f28:      	cmpl	%ecx, %eax
  589f2a:      	jg	0x58a8c1 <.text+0x1898c1>
  589f30:      	je	0x58a8b7 <.text+0x1898b7>
  589f36:      	movl	$0x800b0006, %ecx       # imm = 0x800B0006
  589f3b:      	cmpl	%ecx, %eax
  589f3d:      	jg	0x58a43b <.text+0x18943b>
  589f43:      	je	0x58a431 <.text+0x189431>
  589f49:      	movl	$0x80095001, %ecx       # imm = 0x80095001
  589f4e:      	cmpl	%ecx, %eax
  589f50:      	jg	0x58a1a9 <.text+0x1891a9>
  589f56:      	je	0x58a19f <.text+0x18919f>
  589f5c:      	movl	$0x80094012, %ecx       # imm = 0x80094012
  589f61:      	cmpl	%ecx, %eax
  589f63:      	jg	0x58a0b9 <.text+0x1890b9>
  589f69:      	je	0x58a0af <.text+0x1890af>
  589f6f:      	addl	$-0xa, %ecx
  589f72:      	cmpl	%ecx, %eax
  589f74:      	jg	0x58a040 <.text+0x189040>
  589f7a:      	je	0x58a036 <.text+0x189036>
  589f80:      	movl	$0x80094003, %ecx       # imm = 0x80094003
  589f85:      	cmpl	%ecx, %eax
  589f87:      	jg	0x589fee <.text+0x188fee>
  589f89:      	je	0x589fe4 <.text+0x188fe4>
  589f8b:      	cmpl	$0x80093134, %eax       # imm = 0x80093134
  589f90:      	je	0x589fda <.text+0x188fda>
  589f92:      	cmpl	$0x80093201, %eax       # imm = 0x80093201
  589f97:      	je	0x589fd0 <.text+0x188fd0>
  589f99:      	cmpl	$0x80093202, %eax       # imm = 0x80093202
  589f9e:      	je	0x589fc6 <.text+0x188fc6>
  589fa0:      	cmpl	$0x80094001, %eax       # imm = 0x80094001
  589fa5:      	je	0x589fbc <.text+0x188fbc>
  589fa7:      	cmpl	$0x80094002, %eax       # imm = 0x80094002
  589fac:      	jne	0x591a16 <.text+0x190a16>
  589fb2:      	movl	$0x603dc0, %eax         # imm = 0x603DC0
  589fb7:      	jmp	0x591a45 <.text+0x190a45>
  589fbc:      	movl	$0x603da0, %eax         # imm = 0x603DA0
  589fc1:      	jmp	0x591a45 <.text+0x190a45>
  589fc6:      	movl	$0x603d8c, %eax         # imm = 0x603D8C
  589fcb:      	jmp	0x591a45 <.text+0x190a45>
  589fd0:      	movl	$0x603d74, %eax         # imm = 0x603D74
  589fd5:      	jmp	0x591a45 <.text+0x190a45>
  589fda:      	movl	$0x603d60, %eax         # imm = 0x603D60
  589fdf:      	jmp	0x591a45 <.text+0x190a45>
  589fe4:      	movl	$0x603d44, %eax         # imm = 0x603D44
  589fe9:      	jmp	0x591a45 <.text+0x190a45>
  589fee:      	cmpl	$0x80094004, %eax       # imm = 0x80094004
  589ff3:      	je	0x58a02c <.text+0x18902c>
  589ff5:      	cmpl	$0x80094005, %eax       # imm = 0x80094005
  589ffa:      	je	0x58a022 <.text+0x189022>
  589ffc:      	cmpl	$0x80094006, %eax       # imm = 0x80094006
  58a001:      	je	0x58a018 <.text+0x189018>
  58a003:      	cmpl	$0x80094007, %eax       # imm = 0x80094007
  58a008:      	jne	0x591a16 <.text+0x190a16>
  58a00e:      	movl	$0x603d28, %eax         # imm = 0x603D28
  58a013:      	jmp	0x591a45 <.text+0x190a45>
  58a018:      	movl	$0x603d0c, %eax         # imm = 0x603D0C
  58a01d:      	jmp	0x591a45 <.text+0x190a45>
  58a022:      	movl	$0x603ce8, %eax         # imm = 0x603CE8
  58a027:      	jmp	0x591a45 <.text+0x190a45>
  58a02c:      	movl	$0x603ccc, %eax         # imm = 0x603CCC
  58a031:      	jmp	0x591a45 <.text+0x190a45>
  58a036:      	movl	$0x603cb4, %eax         # imm = 0x603CB4
  58a03b:      	jmp	0x591a45 <.text+0x190a45>
  58a040:      	addl	$0x7ff6bff7, %eax       # imm = 0x7FF6BFF7
  58a045:      	cmpl	$0x8, %eax
  58a048:      	ja	0x591a16 <.text+0x190a16>
  58a04e:      	jmpl	*0x594c51(,%eax,4)
  58a055:      	movl	$0x603c98, %eax         # imm = 0x603C98
  58a05a:      	jmp	0x591a45 <.text+0x190a45>
  58a05f:      	movl	$0x603c70, %eax         # imm = 0x603C70
  58a064:      	jmp	0x591a45 <.text+0x190a45>
  58a069:      	movl	$0x603c58, %eax         # imm = 0x603C58
  58a06e:      	jmp	0x591a45 <.text+0x190a45>
  58a073:      	movl	$0x603c34, %eax         # imm = 0x603C34
  58a078:      	jmp	0x591a45 <.text+0x190a45>
  58a07d:      	movl	$0x603c14, %eax         # imm = 0x603C14
  58a082:      	jmp	0x591a45 <.text+0x190a45>
  58a087:      	movl	$0x603bec, %eax         # imm = 0x603BEC
  58a08c:      	jmp	0x591a45 <.text+0x190a45>
  58a091:      	movl	$0x603bd0, %eax         # imm = 0x603BD0
  58a096:      	jmp	0x591a45 <.text+0x190a45>
  58a09b:      	movl	$0x603bb4, %eax         # imm = 0x603BB4
  58a0a0:      	jmp	0x591a45 <.text+0x190a45>
  58a0a5:      	movl	$0x603b9c, %eax         # imm = 0x603B9C
  58a0aa:      	jmp	0x591a45 <.text+0x190a45>
  58a0af:      	movl	$0x603b80, %eax         # imm = 0x603B80
  58a0b4:      	jmp	0x591a45 <.text+0x190a45>
  58a0b9:      	movl	$0x80095000, %ecx       # imm = 0x80095000
  58a0be:      	cmpl	%ecx, %eax
  58a0c0:      	jg	0x591a16 <.text+0x190a16>
  58a0c6:      	je	0x58a195 <.text+0x189195>
  58a0cc:      	addl	$0x7ff6b800, %eax       # imm = 0x7FF6B800
  58a0d1:      	cmpl	$0x11, %eax
  58a0d4:      	ja	0x591a16 <.text+0x190a16>
  58a0da:      	jmpl	*0x594c75(,%eax,4)
  58a0e1:      	movl	$0x603b60, %eax         # imm = 0x603B60
  58a0e6:      	jmp	0x591a45 <.text+0x190a45>
  58a0eb:      	movl	$0x603b48, %eax         # imm = 0x603B48
  58a0f0:      	jmp	0x591a45 <.text+0x190a45>
  58a0f5:      	movl	$0x603b2c, %eax         # imm = 0x603B2C
  58a0fa:      	jmp	0x591a45 <.text+0x190a45>
  58a0ff:      	movl	$0x603b08, %eax         # imm = 0x603B08
  58a104:      	jmp	0x591a45 <.text+0x190a45>
  58a109:      	movl	$0x603ae8, %eax         # imm = 0x603AE8
  58a10e:      	jmp	0x591a45 <.text+0x190a45>
  58a113:      	movl	$0x603acc, %eax         # imm = 0x603ACC
  58a118:      	jmp	0x591a45 <.text+0x190a45>
  58a11d:      	movl	$0x603aac, %eax         # imm = 0x603AAC
  58a122:      	jmp	0x591a45 <.text+0x190a45>
  58a127:      	movl	$0x603a8c, %eax         # imm = 0x603A8C
  58a12c:      	jmp	0x591a45 <.text+0x190a45>
  58a131:      	movl	$0x603a68, %eax         # imm = 0x603A68
  58a136:      	jmp	0x591a45 <.text+0x190a45>
  58a13b:      	movl	$0x603a44, %eax         # imm = 0x603A44
  58a140:      	jmp	0x591a45 <.text+0x190a45>
  58a145:      	movl	$0x603a28, %eax         # imm = 0x603A28
  58a14a:      	jmp	0x591a45 <.text+0x190a45>
  58a14f:      	movl	$0x603a08, %eax         # imm = 0x603A08
  58a154:      	jmp	0x591a45 <.text+0x190a45>
  58a159:      	movl	$0x6039e4, %eax         # imm = 0x6039E4
  58a15e:      	jmp	0x591a45 <.text+0x190a45>
  58a163:      	movl	$0x6039c4, %eax         # imm = 0x6039C4
  58a168:      	jmp	0x591a45 <.text+0x190a45>
  58a16d:      	movl	$0x603998, %eax         # imm = 0x603998
  58a172:      	jmp	0x591a45 <.text+0x190a45>
  58a177:      	movl	$0x603978, %eax         # imm = 0x603978
  58a17c:      	jmp	0x591a45 <.text+0x190a45>
  58a181:      	movl	$0x603954, %eax         # imm = 0x603954
  58a186:      	jmp	0x591a45 <.text+0x190a45>
  58a18b:      	movl	$0x60393c, %eax         # imm = 0x60393C
  58a190:      	jmp	0x591a45 <.text+0x190a45>
  58a195:      	movl	$0x60391c, %eax         # imm = 0x60391C
  58a19a:      	jmp	0x591a45 <.text+0x190a45>
  58a19f:      	movl	$0x6038fc, %eax         # imm = 0x6038FC
  58a1a4:      	jmp	0x591a45 <.text+0x190a45>
  58a1a9:      	movl	$0x80097008, %ecx       # imm = 0x80097008
  58a1ae:      	cmpl	%ecx, %eax
  58a1b0:      	jg	0x58a32b <.text+0x18932b>
  58a1b6:      	je	0x58a321 <.text+0x189321>
  58a1bc:      	movl	$0x80096010, %ecx       # imm = 0x80096010
  58a1c1:      	cmpl	%ecx, %eax
  58a1c3:      	jg	0x58a27c <.text+0x18927c>
  58a1c9:      	je	0x58a272 <.text+0x189272>
  58a1cf:      	addl	$-0xf, %ecx
  58a1d2:      	cmpl	%ecx, %eax
  58a1d4:      	jg	0x58a22a <.text+0x18922a>
  58a1d6:      	je	0x58a220 <.text+0x189220>
  58a1d8:      	cmpl	$0x80095002, %eax       # imm = 0x80095002
  58a1dd:      	je	0x58a216 <.text+0x189216>
  58a1df:      	cmpl	$0x80095003, %eax       # imm = 0x80095003
  58a1e4:      	je	0x58a20c <.text+0x18920c>
  58a1e6:      	cmpl	$0x80095004, %eax       # imm = 0x80095004
  58a1eb:      	je	0x58a202 <.text+0x189202>
  58a1ed:      	cmpl	$0x80095005, %eax       # imm = 0x80095005
  58a1f2:      	jne	0x591a16 <.text+0x190a16>
  58a1f8:      	movl	$0x6038d8, %eax         # imm = 0x6038D8
  58a1fd:      	jmp	0x591a45 <.text+0x190a45>
  58a202:      	movl	$0x6038b4, %eax         # imm = 0x6038B4
  58a207:      	jmp	0x591a45 <.text+0x190a45>
  58a20c:      	movl	$0x60388c, %eax         # imm = 0x60388C
  58a211:      	jmp	0x591a45 <.text+0x190a45>
  58a216:      	movl	$0x603864, %eax         # imm = 0x603864
  58a21b:      	jmp	0x591a45 <.text+0x190a45>
  58a220:      	movl	$0x60384c, %eax         # imm = 0x60384C
  58a225:      	jmp	0x591a45 <.text+0x190a45>
  58a22a:      	cmpl	$0x80096002, %eax       # imm = 0x80096002
  58a22f:      	je	0x58a268 <.text+0x189268>
  58a231:      	cmpl	$0x80096003, %eax       # imm = 0x80096003
  58a236:      	je	0x58a25e <.text+0x18925e>
  58a238:      	cmpl	$0x80096004, %eax       # imm = 0x80096004
  58a23d:      	je	0x58a254 <.text+0x189254>
  58a23f:      	cmpl	$0x80096005, %eax       # imm = 0x80096005
  58a244:      	jne	0x591a16 <.text+0x190a16>
  58a24a:      	movl	$0x603838, %eax         # imm = 0x603838
  58a24f:      	jmp	0x591a45 <.text+0x190a45>
  58a254:      	movl	$0x603820, %eax         # imm = 0x603820
  58a259:      	jmp	0x591a45 <.text+0x190a45>
  58a25e:      	movl	$0x603808, %eax         # imm = 0x603808
  58a263:      	jmp	0x591a45 <.text+0x190a45>
  58a268:      	movl	$0x6037f0, %eax         # imm = 0x6037F0
  58a26d:      	jmp	0x591a45 <.text+0x190a45>
  58a272:      	movl	$0x6037dc, %eax         # imm = 0x6037DC
  58a277:      	jmp	0x591a45 <.text+0x190a45>
  58a27c:      	movl	$0x80097003, %ecx       # imm = 0x80097003
  58a281:      	cmpl	%ecx, %eax
  58a283:      	jg	0x58a2d9 <.text+0x1892d9>
  58a285:      	je	0x58a2cf <.text+0x1892cf>
  58a287:      	cmpl	$0x80096019, %eax       # imm = 0x80096019
  58a28c:      	je	0x58a2c5 <.text+0x1892c5>
  58a28e:      	cmpl	$0x8009601e, %eax       # imm = 0x8009601E
  58a293:      	je	0x58a2bb <.text+0x1892bb>
  58a295:      	cmpl	$0x80097001, %eax       # imm = 0x80097001
  58a29a:      	je	0x58a2b1 <.text+0x1892b1>
  58a29c:      	cmpl	$0x80097002, %eax       # imm = 0x80097002
  58a2a1:      	jne	0x591a16 <.text+0x190a16>
  58a2a7:      	movl	$0x6037c0, %eax         # imm = 0x6037C0
  58a2ac:      	jmp	0x591a45 <.text+0x190a45>
  58a2b1:      	movl	$0x6037a4, %eax         # imm = 0x6037A4
  58a2b6:      	jmp	0x591a45 <.text+0x190a45>
  58a2bb:      	movl	$0x603788, %eax         # imm = 0x603788
  58a2c0:      	jmp	0x591a45 <.text+0x190a45>
  58a2c5:      	movl	$0x60376c, %eax         # imm = 0x60376C
  58a2ca:      	jmp	0x591a45 <.text+0x190a45>
  58a2cf:      	movl	$0x603754, %eax         # imm = 0x603754
  58a2d4:      	jmp	0x591a45 <.text+0x190a45>
  58a2d9:      	cmpl	$0x80097004, %eax       # imm = 0x80097004
  58a2de:      	je	0x58a317 <.text+0x189317>
  58a2e0:      	cmpl	$0x80097005, %eax       # imm = 0x80097005
  58a2e5:      	je	0x58a30d <.text+0x18930d>
  58a2e7:      	cmpl	$0x80097006, %eax       # imm = 0x80097006
  58a2ec:      	je	0x58a303 <.text+0x189303>
  58a2ee:      	cmpl	$0x80097007, %eax       # imm = 0x80097007
  58a2f3:      	jne	0x591a16 <.text+0x190a16>
  58a2f9:      	movl	$0x603738, %eax         # imm = 0x603738
  58a2fe:      	jmp	0x591a45 <.text+0x190a45>
  58a303:      	movl	$0x60371c, %eax         # imm = 0x60371C
  58a308:      	jmp	0x591a45 <.text+0x190a45>
  58a30d:      	movl	$0x603700, %eax         # imm = 0x603700
  58a312:      	jmp	0x591a45 <.text+0x190a45>
  58a317:      	movl	$0x6036e4, %eax         # imm = 0x6036E4
  58a31c:      	jmp	0x591a45 <.text+0x190a45>
  58a321:      	movl	$0x6036bc, %eax         # imm = 0x6036BC
  58a326:      	jmp	0x591a45 <.text+0x190a45>
  58a32b:      	movl	$0x800b0001, %ecx       # imm = 0x800B0001
  58a330:      	cmpl	%ecx, %eax
  58a332:      	jg	0x58a3e9 <.text+0x1893e9>
  58a338:      	je	0x58a3df <.text+0x1893df>
  58a33e:      	addl	$0x7ff68ff7, %eax       # imm = 0x7FF68FF7
  58a343:      	cmpl	$0xf, %eax
  58a346:      	ja	0x591a16 <.text+0x190a16>
  58a34c:      	jmpl	*0x594cbd(,%eax,4)
  58a353:      	movl	$0x6036a0, %eax         # imm = 0x6036A0
  58a358:      	jmp	0x591a45 <.text+0x190a45>
  58a35d:      	movl	$0x603684, %eax         # imm = 0x603684
  58a362:      	jmp	0x591a45 <.text+0x190a45>
  58a367:      	movl	$0x60366c, %eax         # imm = 0x60366C
  58a36c:      	jmp	0x591a45 <.text+0x190a45>
  58a371:      	movl	$0x603650, %eax         # imm = 0x603650
  58a376:      	jmp	0x591a45 <.text+0x190a45>
  58a37b:      	movl	$0x603634, %eax         # imm = 0x603634
  58a380:      	jmp	0x591a45 <.text+0x190a45>
  58a385:      	movl	$0x603618, %eax         # imm = 0x603618
  58a38a:      	jmp	0x591a45 <.text+0x190a45>
  58a38f:      	movl	$0x6035f8, %eax         # imm = 0x6035F8
  58a394:      	jmp	0x591a45 <.text+0x190a45>
  58a399:      	movl	$0x6035e0, %eax         # imm = 0x6035E0
  58a39e:      	jmp	0x591a45 <.text+0x190a45>
  58a3a3:      	movl	$0x6035d0, %eax         # imm = 0x6035D0
  58a3a8:      	jmp	0x591a45 <.text+0x190a45>
  58a3ad:      	movl	$0x6035bc, %eax         # imm = 0x6035BC
  58a3b2:      	jmp	0x591a45 <.text+0x190a45>
  58a3b7:      	movl	$0x6035a4, %eax         # imm = 0x6035A4
  58a3bc:      	jmp	0x591a45 <.text+0x190a45>
  58a3c1:      	movl	$0x603588, %eax         # imm = 0x603588
  58a3c6:      	jmp	0x591a45 <.text+0x190a45>
  58a3cb:      	movl	$0x603570, %eax         # imm = 0x603570
  58a3d0:      	jmp	0x591a45 <.text+0x190a45>
  58a3d5:      	movl	$0x603558, %eax         # imm = 0x603558
  58a3da:      	jmp	0x591a45 <.text+0x190a45>
  58a3df:      	movl	$0x60353c, %eax         # imm = 0x60353C
  58a3e4:      	jmp	0x591a45 <.text+0x190a45>
  58a3e9:      	cmpl	$0x800b0002, %eax       # imm = 0x800B0002
  58a3ee:      	je	0x58a427 <.text+0x189427>
  58a3f0:      	cmpl	$0x800b0003, %eax       # imm = 0x800B0003
  58a3f5:      	je	0x58a41d <.text+0x18941d>
  58a3f7:      	cmpl	$0x800b0004, %eax       # imm = 0x800B0004
  58a3fc:      	je	0x58a413 <.text+0x189413>
  58a3fe:      	cmpl	$0x800b0005, %eax       # imm = 0x800B0005
  58a403:      	jne	0x591a16 <.text+0x190a16>
  58a409:      	movl	$0x60352c, %eax         # imm = 0x60352C
  58a40e:      	jmp	0x591a45 <.text+0x190a45>
  58a413:      	movl	$0x603510, %eax         # imm = 0x603510
  58a418:      	jmp	0x591a45 <.text+0x190a45>
  58a41d:      	movl	$0x6034f0, %eax         # imm = 0x6034F0
  58a422:      	jmp	0x591a45 <.text+0x190a45>
  58a427:      	movl	$0x6034d8, %eax         # imm = 0x6034D8
  58a42c:      	jmp	0x591a45 <.text+0x190a45>
  58a431:      	movl	$0x6034c8, %eax         # imm = 0x6034C8
  58a436:      	jmp	0x591a45 <.text+0x190a45>
  58a43b:      	movl	$0x800f0206, %ecx       # imm = 0x800F0206
  58a440:      	cmpl	%ecx, %eax
  58a442:      	jg	0x58a71c <.text+0x18971c>
  58a448:      	je	0x58a712 <.text+0x189712>
  58a44e:      	movl	$0x800b010f, %ecx       # imm = 0x800B010F
  58a453:      	cmpl	%ecx, %eax
  58a455:      	jg	0x58a5ab <.text+0x1895ab>
  58a45b:      	je	0x58a5a1 <.text+0x1895a1>
  58a461:      	addl	$-0xa, %ecx
  58a464:      	cmpl	%ecx, %eax
  58a466:      	jg	0x58a532 <.text+0x189532>
  58a46c:      	je	0x58a528 <.text+0x189528>
  58a472:      	movl	$0x800b0100, %ecx       # imm = 0x800B0100
  58a477:      	cmpl	%ecx, %eax
  58a479:      	jg	0x58a4e0 <.text+0x1894e0>
  58a47b:      	je	0x58a4d6 <.text+0x1894d6>
  58a47d:      	cmpl	$0x800b0007, %eax       # imm = 0x800B0007
  58a482:      	je	0x58a4cc <.text+0x1894cc>
  58a484:      	cmpl	$0x800b0008, %eax       # imm = 0x800B0008
  58a489:      	je	0x58a4c2 <.text+0x1894c2>
  58a48b:      	cmpl	$0x800b0009, %eax       # imm = 0x800B0009
  58a490:      	je	0x58a4b8 <.text+0x1894b8>
  58a492:      	cmpl	$0x800b000a, %eax       # imm = 0x800B000A
  58a497:      	je	0x58a4ae <.text+0x1894ae>
  58a499:      	cmpl	$0x800b000b, %eax       # imm = 0x800B000B
  58a49e:      	jne	0x591a16 <.text+0x190a16>
  58a4a4:      	movl	$0x6034b0, %eax         # imm = 0x6034B0
  58a4a9:      	jmp	0x591a45 <.text+0x190a45>
  58a4ae:      	movl	$0x603494, %eax         # imm = 0x603494
  58a4b3:      	jmp	0x591a45 <.text+0x190a45>
  58a4b8:      	movl	$0x60347c, %eax         # imm = 0x60347C
  58a4bd:      	jmp	0x591a45 <.text+0x190a45>
  58a4c2:      	movl	$0x60346c, %eax         # imm = 0x60346C
  58a4c7:      	jmp	0x591a45 <.text+0x190a45>
  58a4cc:      	movl	$0x603454, %eax         # imm = 0x603454
  58a4d1:      	jmp	0x591a45 <.text+0x190a45>
  58a4d6:      	movl	$0x603440, %eax         # imm = 0x603440
  58a4db:      	jmp	0x591a45 <.text+0x190a45>
  58a4e0:      	cmpl	$0x800b0101, %eax       # imm = 0x800B0101
  58a4e5:      	je	0x58a51e <.text+0x18951e>
  58a4e7:      	cmpl	$0x800b0102, %eax       # imm = 0x800B0102
  58a4ec:      	je	0x58a514 <.text+0x189514>
  58a4ee:      	cmpl	$0x800b0103, %eax       # imm = 0x800B0103
  58a4f3:      	je	0x58a50a <.text+0x18950a>
  58a4f5:      	cmpl	$0x800b0104, %eax       # imm = 0x800B0104
  58a4fa:      	jne	0x591a16 <.text+0x190a16>
  58a500:      	movl	$0x60342c, %eax         # imm = 0x60342C
  58a505:      	jmp	0x591a45 <.text+0x190a45>
  58a50a:      	movl	$0x603420, %eax         # imm = 0x603420
  58a50f:      	jmp	0x591a45 <.text+0x190a45>
  58a514:      	movl	$0x603400, %eax         # imm = 0x603400
  58a519:      	jmp	0x591a45 <.text+0x190a45>
  58a51e:      	movl	$0x6033f0, %eax         # imm = 0x6033F0
  58a523:      	jmp	0x591a45 <.text+0x190a45>
  58a528:      	movl	$0x6033e0, %eax         # imm = 0x6033E0
  58a52d:      	jmp	0x591a45 <.text+0x190a45>
  58a532:      	addl	$0x7ff4fefa, %eax       # imm = 0x7FF4FEFA
  58a537:      	cmpl	$0x8, %eax
  58a53a:      	ja	0x591a16 <.text+0x190a16>
  58a540:      	jmpl	*0x594cfd(,%eax,4)
  58a547:      	movl	$0x6033d0, %eax         # imm = 0x6033D0
  58a54c:      	jmp	0x591a45 <.text+0x190a45>
  58a551:      	movl	$0x6033b8, %eax         # imm = 0x6033B8
  58a556:      	jmp	0x591a45 <.text+0x190a45>
  58a55b:      	movl	$0x6033a4, %eax         # imm = 0x6033A4
  58a560:      	jmp	0x591a45 <.text+0x190a45>
  58a565:      	movl	$0x60338c, %eax         # imm = 0x60338C
  58a56a:      	jmp	0x591a45 <.text+0x190a45>
  58a56f:      	movl	$0x60337c, %eax         # imm = 0x60337C
  58a574:      	jmp	0x591a45 <.text+0x190a45>
  58a579:      	movl	$0x60336c, %eax         # imm = 0x60336C
  58a57e:      	jmp	0x591a45 <.text+0x190a45>
  58a583:      	movl	$0x60335c, %eax         # imm = 0x60335C
  58a588:      	jmp	0x591a45 <.text+0x190a45>
  58a58d:      	movl	$0x603340, %eax         # imm = 0x603340
  58a592:      	jmp	0x591a45 <.text+0x190a45>
  58a597:      	movl	$0x603324, %eax         # imm = 0x603324
  58a59c:      	jmp	0x591a45 <.text+0x190a45>
  58a5a1:      	movl	$0x603310, %eax         # imm = 0x603310
  58a5a6:      	jmp	0x591a45 <.text+0x190a45>
  58a5ab:      	movl	$0x800f0100, %ecx       # imm = 0x800F0100
  58a5b0:      	cmpl	%ecx, %eax
  58a5b2:      	jg	0x58a66d <.text+0x18966d>
  58a5b8:      	je	0x58a663 <.text+0x189663>
  58a5be:      	movl	$0x800b0114, %ecx       # imm = 0x800B0114
  58a5c3:      	cmpl	%ecx, %eax
  58a5c5:      	jg	0x58a61b <.text+0x18961b>
  58a5c7:      	je	0x58a611 <.text+0x189611>
  58a5c9:      	cmpl	$0x800b0110, %eax       # imm = 0x800B0110
  58a5ce:      	je	0x58a607 <.text+0x189607>
  58a5d0:      	cmpl	$0x800b0111, %eax       # imm = 0x800B0111
  58a5d5:      	je	0x58a5fd <.text+0x1895fd>
  58a5d7:      	cmpl	$0x800b0112, %eax       # imm = 0x800B0112
  58a5dc:      	je	0x58a5f3 <.text+0x1895f3>
  58a5de:      	cmpl	$0x800b0113, %eax       # imm = 0x800B0113
  58a5e3:      	jne	0x591a16 <.text+0x190a16>
  58a5e9:      	movl	$0x6032f8, %eax         # imm = 0x6032F8
  58a5ee:      	jmp	0x591a45 <.text+0x190a45>
  58a5f3:      	movl	$0x6032e4, %eax         # imm = 0x6032E4
  58a5f8:      	jmp	0x591a45 <.text+0x190a45>
  58a5fd:      	movl	$0x6032c8, %eax         # imm = 0x6032C8
  58a602:      	jmp	0x591a45 <.text+0x190a45>
  58a607:      	movl	$0x6032b4, %eax         # imm = 0x6032B4
  58a60c:      	jmp	0x591a45 <.text+0x190a45>
  58a611:      	movl	$0x6032a0, %eax         # imm = 0x6032A0
  58a616:      	jmp	0x591a45 <.text+0x190a45>
  58a61b:      	cmpl	$0x800f0000, %eax       # imm = 0x800F0000
  58a620:      	je	0x58a659 <.text+0x189659>
  58a622:      	cmpl	$0x800f0001, %eax       # imm = 0x800F0001
  58a627:      	je	0x58a64f <.text+0x18964f>
  58a629:      	cmpl	$0x800f0002, %eax       # imm = 0x800F0002
  58a62e:      	je	0x58a645 <.text+0x189645>
  58a630:      	cmpl	$0x800f0003, %eax       # imm = 0x800F0003
  58a635:      	jne	0x591a16 <.text+0x190a16>
  58a63b:      	movl	$0x603288, %eax         # imm = 0x603288
  58a640:      	jmp	0x591a45 <.text+0x190a45>
  58a645:      	movl	$0x603268, %eax         # imm = 0x603268
  58a64a:      	jmp	0x591a45 <.text+0x190a45>
  58a64f:      	movl	$0x603248, %eax         # imm = 0x603248
  58a654:      	jmp	0x591a45 <.text+0x190a45>
  58a659:      	movl	$0x603228, %eax         # imm = 0x603228
  58a65e:      	jmp	0x591a45 <.text+0x190a45>
  58a663:      	movl	$0x603210, %eax         # imm = 0x603210
  58a668:      	jmp	0x591a45 <.text+0x190a45>
  58a66d:      	movl	$0x800f0201, %ecx       # imm = 0x800F0201
  58a672:      	cmpl	%ecx, %eax
  58a674:      	jg	0x58a6ca <.text+0x1896ca>
  58a676:      	je	0x58a6c0 <.text+0x1896c0>
  58a678:      	cmpl	$0x800f0101, %eax       # imm = 0x800F0101
  58a67d:      	je	0x58a6b6 <.text+0x1896b6>
  58a67f:      	cmpl	$0x800f0102, %eax       # imm = 0x800F0102
  58a684:      	je	0x58a6ac <.text+0x1896ac>
  58a686:      	cmpl	$0x800f0103, %eax       # imm = 0x800F0103
  58a68b:      	je	0x58a6a2 <.text+0x1896a2>
  58a68d:      	cmpl	$0x800f0200, %eax       # imm = 0x800F0200
  58a692:      	jne	0x591a16 <.text+0x190a16>
  58a698:      	movl	$0x6031f4, %eax         # imm = 0x6031F4
  58a69d:      	jmp	0x591a45 <.text+0x190a45>
  58a6a2:      	movl	$0x6031e0, %eax         # imm = 0x6031E0
  58a6a7:      	jmp	0x591a45 <.text+0x190a45>
  58a6ac:      	movl	$0x6031c8, %eax         # imm = 0x6031C8
  58a6b1:      	jmp	0x591a45 <.text+0x190a45>
  58a6b6:      	movl	$0x6031ac, %eax         # imm = 0x6031AC
  58a6bb:      	jmp	0x591a45 <.text+0x190a45>
  58a6c0:      	movl	$0x603194, %eax         # imm = 0x603194
  58a6c5:      	jmp	0x591a45 <.text+0x190a45>
  58a6ca:      	cmpl	$0x800f0202, %eax       # imm = 0x800F0202
  58a6cf:      	je	0x58a708 <.text+0x189708>
  58a6d1:      	cmpl	$0x800f0203, %eax       # imm = 0x800F0203
  58a6d6:      	je	0x58a6fe <.text+0x1896fe>
  58a6d8:      	cmpl	$0x800f0204, %eax       # imm = 0x800F0204
  58a6dd:      	je	0x58a6f4 <.text+0x1896f4>
  58a6df:      	cmpl	$0x800f0205, %eax       # imm = 0x800F0205
  58a6e4:      	jne	0x591a16 <.text+0x190a16>
  58a6ea:      	movl	$0x603174, %eax         # imm = 0x603174
  58a6ef:      	jmp	0x591a45 <.text+0x190a45>
  58a6f4:      	movl	$0x603158, %eax         # imm = 0x603158
  58a6f9:      	jmp	0x591a45 <.text+0x190a45>
  58a6fe:      	movl	$0x60313c, %eax         # imm = 0x60313C
  58a703:      	jmp	0x591a45 <.text+0x190a45>
  58a708:      	movl	$0x603124, %eax         # imm = 0x603124
  58a70d:      	jmp	0x591a45 <.text+0x190a45>
  58a712:      	movl	$0x60310c, %eax         # imm = 0x60310C
  58a717:      	jmp	0x591a45 <.text+0x190a45>
  58a71c:      	addl	$0x7ff0fdf9, %eax       # imm = 0x7FF0FDF9
  58a721:      	cmpl	$0x26, %eax
  58a724:      	ja	0x591a16 <.text+0x190a16>
  58a72a:      	jmpl	*0x594d21(,%eax,4)
  58a731:      	movl	$0x6030ec, %eax         # imm = 0x6030EC
  58a736:      	jmp	0x591a45 <.text+0x190a45>
  58a73b:      	movl	$0x6030cc, %eax         # imm = 0x6030CC
  58a740:      	jmp	0x591a45 <.text+0x190a45>
  58a745:      	movl	$0x6030ac, %eax         # imm = 0x6030AC
  58a74a:      	jmp	0x591a45 <.text+0x190a45>
  58a74f:      	movl	$0x60309c, %eax         # imm = 0x60309C
  58a754:      	jmp	0x591a45 <.text+0x190a45>
  58a759:      	movl	$0x603084, %eax         # imm = 0x603084
  58a75e:      	jmp	0x591a45 <.text+0x190a45>
  58a763:      	movl	$0x603064, %eax         # imm = 0x603064
  58a768:      	jmp	0x591a45 <.text+0x190a45>
  58a76d:      	movl	$0x603044, %eax         # imm = 0x603044
  58a772:      	jmp	0x591a45 <.text+0x190a45>
  58a777:      	movl	$0x60302c, %eax         # imm = 0x60302C
  58a77c:      	jmp	0x591a45 <.text+0x190a45>
  58a781:      	movl	$0x603014, %eax         # imm = 0x603014
  58a786:      	jmp	0x591a45 <.text+0x190a45>
  58a78b:      	movl	$0x602ff8, %eax         # imm = 0x602FF8
  58a790:      	jmp	0x591a45 <.text+0x190a45>
  58a795:      	movl	$0x602fdc, %eax         # imm = 0x602FDC
  58a79a:      	jmp	0x591a45 <.text+0x190a45>
  58a79f:      	movl	$0x602fc0, %eax         # imm = 0x602FC0
  58a7a4:      	jmp	0x591a45 <.text+0x190a45>
  58a7a9:      	movl	$0x602fa4, %eax         # imm = 0x602FA4
  58a7ae:      	jmp	0x591a45 <.text+0x190a45>
  58a7b3:      	movl	$0x602f90, %eax         # imm = 0x602F90
  58a7b8:      	jmp	0x591a45 <.text+0x190a45>
  58a7bd:      	movl	$0x602f70, %eax         # imm = 0x602F70
  58a7c2:      	jmp	0x591a45 <.text+0x190a45>
  58a7c7:      	movl	$0x602f54, %eax         # imm = 0x602F54
  58a7cc:      	jmp	0x591a45 <.text+0x190a45>
  58a7d1:      	movl	$0x602f34, %eax         # imm = 0x602F34
  58a7d6:      	jmp	0x591a45 <.text+0x190a45>
  58a7db:      	movl	$0x602f14, %eax         # imm = 0x602F14
  58a7e0:      	jmp	0x591a45 <.text+0x190a45>
  58a7e5:      	movl	$0x602ef4, %eax         # imm = 0x602EF4
  58a7ea:      	jmp	0x591a45 <.text+0x190a45>
  58a7ef:      	movl	$0x602ed0, %eax         # imm = 0x602ED0
  58a7f4:      	jmp	0x591a45 <.text+0x190a45>
  58a7f9:      	movl	$0x602eb0, %eax         # imm = 0x602EB0
  58a7fe:      	jmp	0x591a45 <.text+0x190a45>
  58a803:      	movl	$0x602e8c, %eax         # imm = 0x602E8C
  58a808:      	jmp	0x591a45 <.text+0x190a45>
  58a80d:      	movl	$0x602e68, %eax         # imm = 0x602E68
  58a812:      	jmp	0x591a45 <.text+0x190a45>
  58a817:      	movl	$0x602e48, %eax         # imm = 0x602E48
  58a81c:      	jmp	0x591a45 <.text+0x190a45>
  58a821:      	movl	$0x602e24, %eax         # imm = 0x602E24
  58a826:      	jmp	0x591a45 <.text+0x190a45>
  58a82b:      	movl	$0x602e08, %eax         # imm = 0x602E08
  58a830:      	jmp	0x591a45 <.text+0x190a45>
  58a835:      	movl	$0x602dec, %eax         # imm = 0x602DEC
  58a83a:      	jmp	0x591a45 <.text+0x190a45>
  58a83f:      	movl	$0x602dd0, %eax         # imm = 0x602DD0
  58a844:      	jmp	0x591a45 <.text+0x190a45>
  58a849:      	movl	$0x602db0, %eax         # imm = 0x602DB0
  58a84e:      	jmp	0x591a45 <.text+0x190a45>
  58a853:      	movl	$0x602d8c, %eax         # imm = 0x602D8C
  58a858:      	jmp	0x591a45 <.text+0x190a45>
  58a85d:      	movl	$0x602d68, %eax         # imm = 0x602D68
  58a862:      	jmp	0x591a45 <.text+0x190a45>
  58a867:      	movl	$0x602d44, %eax         # imm = 0x602D44
  58a86c:      	jmp	0x591a45 <.text+0x190a45>
  58a871:      	movl	$0x602d28, %eax         # imm = 0x602D28
  58a876:      	jmp	0x591a45 <.text+0x190a45>
  58a87b:      	movl	$0x602d0c, %eax         # imm = 0x602D0C
  58a880:      	jmp	0x591a45 <.text+0x190a45>
  58a885:      	movl	$0x602cf4, %eax         # imm = 0x602CF4
  58a88a:      	jmp	0x591a45 <.text+0x190a45>
  58a88f:      	movl	$0x602cd4, %eax         # imm = 0x602CD4
  58a894:      	jmp	0x591a45 <.text+0x190a45>
  58a899:      	movl	$0x602cbc, %eax         # imm = 0x602CBC
  58a89e:      	jmp	0x591a45 <.text+0x190a45>
  58a8a3:      	movl	$0x602c9c, %eax         # imm = 0x602C9C
  58a8a8:      	jmp	0x591a45 <.text+0x190a45>
  58a8ad:      	movl	$0x602c7c, %eax         # imm = 0x602C7C
  58a8b2:      	jmp	0x591a45 <.text+0x190a45>
  58a8b7:      	movl	$0x602c60, %eax         # imm = 0x602C60
  58a8bc:      	jmp	0x591a45 <.text+0x190a45>
  58a8c1:      	movl	$0x800f1000, %ecx       # imm = 0x800F1000
  58a8c6:      	cmpl	%ecx, %eax
  58a8c8:      	jg	0x58a953 <.text+0x189953>
  58a8ce:      	je	0x58a949 <.text+0x189949>
  58a8d0:      	addl	$0x7ff0fdd1, %eax       # imm = 0x7FF0FDD1
  58a8d5:      	cmpl	$0x9, %eax
  58a8d8:      	ja	0x591a16 <.text+0x190a16>
  58a8de:      	jmpl	*0x594dbd(,%eax,4)
  58a8e5:      	movl	$0x602c40, %eax         # imm = 0x602C40
  58a8ea:      	jmp	0x591a45 <.text+0x190a45>
  58a8ef:      	movl	$0x602c1c, %eax         # imm = 0x602C1C
  58a8f4:      	jmp	0x591a45 <.text+0x190a45>
  58a8f9:      	movl	$0x602c04, %eax         # imm = 0x602C04
  58a8fe:      	jmp	0x591a45 <.text+0x190a45>
  58a903:      	movl	$0x602be8, %eax         # imm = 0x602BE8
  58a908:      	jmp	0x591a45 <.text+0x190a45>
  58a90d:      	movl	$0x602bd0, %eax         # imm = 0x602BD0
  58a912:      	jmp	0x591a45 <.text+0x190a45>
  58a917:      	movl	$0x602bb4, %eax         # imm = 0x602BB4
  58a91c:      	jmp	0x591a45 <.text+0x190a45>
  58a921:      	movl	$0x602ba0, %eax         # imm = 0x602BA0
  58a926:      	jmp	0x591a45 <.text+0x190a45>
  58a92b:      	movl	$0x602b7c, %eax         # imm = 0x602B7C
  58a930:      	jmp	0x591a45 <.text+0x190a45>
  58a935:      	movl	$0x602b5c, %eax         # imm = 0x602B5C
  58a93a:      	jmp	0x591a45 <.text+0x190a45>
  58a93f:      	movl	$0x602b44, %eax         # imm = 0x602B44
  58a944:      	jmp	0x591a45 <.text+0x190a45>
  58a949:      	movl	$0x602b28, %eax         # imm = 0x602B28
  58a94e:      	jmp	0x591a45 <.text+0x190a45>
  58a953:      	movl	$0x80110401, %ecx       # imm = 0x80110401
  58a958:      	cmpl	%ecx, %eax
  58a95a:      	jg	0x58abda <.text+0x189bda>
  58a960:      	je	0x58abd0 <.text+0x189bd0>
  58a966:      	addl	$0x7fefffff, %eax       # imm = 0x7FEFFFFF
  58a96b:      	cmpl	$0x6e, %eax
  58a96e:      	ja	0x591a16 <.text+0x190a16>
  58a974:      	movzbl	0x594ed5(%eax), %eax
  58a97b:      	jmpl	*0x594de5(,%eax,4)
  58a982:      	movl	$0x602b10, %eax         # imm = 0x602B10
  58a987:      	jmp	0x591a45 <.text+0x190a45>
  58a98c:      	movl	$0x602afc, %eax         # imm = 0x602AFC
  58a991:      	jmp	0x591a45 <.text+0x190a45>
  58a996:      	movl	$0x602ae4, %eax         # imm = 0x602AE4
  58a99b:      	jmp	0x591a45 <.text+0x190a45>
  58a9a0:      	movl	$0x602ac8, %eax         # imm = 0x602AC8
  58a9a5:      	jmp	0x591a45 <.text+0x190a45>
  58a9aa:      	movl	$0x602ab0, %eax         # imm = 0x602AB0
  58a9af:      	jmp	0x591a45 <.text+0x190a45>
  58a9b4:      	movl	$0x602a9c, %eax         # imm = 0x602A9C
  58a9b9:      	jmp	0x591a45 <.text+0x190a45>
  58a9be:      	movl	$0x602a84, %eax         # imm = 0x602A84
  58a9c3:      	jmp	0x591a45 <.text+0x190a45>
  58a9c8:      	movl	$0x602a68, %eax         # imm = 0x602A68
  58a9cd:      	jmp	0x591a45 <.text+0x190a45>
  58a9d2:      	movl	$0x602a50, %eax         # imm = 0x602A50
  58a9d7:      	jmp	0x591a45 <.text+0x190a45>
  58a9dc:      	movl	$0x602a40, %eax         # imm = 0x602A40
  58a9e1:      	jmp	0x591a45 <.text+0x190a45>
  58a9e6:      	movl	$0x602a24, %eax         # imm = 0x602A24
  58a9eb:      	jmp	0x591a45 <.text+0x190a45>
  58a9f0:      	movl	$0x602a0c, %eax         # imm = 0x602A0C
  58a9f5:      	jmp	0x591a45 <.text+0x190a45>
  58a9fa:      	movl	$0x6029f4, %eax         # imm = 0x6029F4
  58a9ff:      	jmp	0x591a45 <.text+0x190a45>
  58aa04:      	movl	$0x6029dc, %eax         # imm = 0x6029DC
  58aa09:      	jmp	0x591a45 <.text+0x190a45>
  58aa0e:      	movl	$0x6029c4, %eax         # imm = 0x6029C4
  58aa13:      	jmp	0x591a45 <.text+0x190a45>
  58aa18:      	movl	$0x6029b0, %eax         # imm = 0x6029B0
  58aa1d:      	jmp	0x591a45 <.text+0x190a45>
  58aa22:      	movl	$0x602998, %eax         # imm = 0x602998
  58aa27:      	jmp	0x591a45 <.text+0x190a45>
  58aa2c:      	movl	$0x60297c, %eax         # imm = 0x60297C
  58aa31:      	jmp	0x591a45 <.text+0x190a45>
  58aa36:      	movl	$0x602968, %eax         # imm = 0x602968
  58aa3b:      	jmp	0x591a45 <.text+0x190a45>
  58aa40:      	movl	$0x602950, %eax         # imm = 0x602950
  58aa45:      	jmp	0x591a45 <.text+0x190a45>
  58aa4a:      	movl	$0x60293c, %eax         # imm = 0x60293C
  58aa4f:      	jmp	0x591a45 <.text+0x190a45>
  58aa54:      	movl	$0x602924, %eax         # imm = 0x602924
  58aa59:      	jmp	0x591a45 <.text+0x190a45>
  58aa5e:      	movl	$0x602908, %eax         # imm = 0x602908
  58aa63:      	jmp	0x591a45 <.text+0x190a45>
  58aa68:      	movl	$0x6028f4, %eax         # imm = 0x6028F4
  58aa6d:      	jmp	0x591a45 <.text+0x190a45>
  58aa72:      	movl	$0x6028dc, %eax         # imm = 0x6028DC
  58aa77:      	jmp	0x591a45 <.text+0x190a45>
  58aa7c:      	movl	$0x6028c0, %eax         # imm = 0x6028C0
  58aa81:      	jmp	0x591a45 <.text+0x190a45>
  58aa86:      	movl	$0x6028a4, %eax         # imm = 0x6028A4
  58aa8b:      	jmp	0x591a45 <.text+0x190a45>
  58aa90:      	movl	$0x602888, %eax         # imm = 0x602888
  58aa95:      	jmp	0x591a45 <.text+0x190a45>
  58aa9a:      	movl	$0x602874, %eax         # imm = 0x602874
  58aa9f:      	jmp	0x591a45 <.text+0x190a45>
  58aaa4:      	movl	$0x60285c, %eax         # imm = 0x60285C
  58aaa9:      	jmp	0x591a45 <.text+0x190a45>
  58aaae:      	movl	$0x602848, %eax         # imm = 0x602848
  58aab3:      	jmp	0x591a45 <.text+0x190a45>
  58aab8:      	movl	$0x60282c, %eax         # imm = 0x60282C
  58aabd:      	jmp	0x591a45 <.text+0x190a45>
  58aac2:      	movl	$0x602814, %eax         # imm = 0x602814
  58aac7:      	jmp	0x591a45 <.text+0x190a45>
  58aacc:      	movl	$0x6027f8, %eax         # imm = 0x6027F8
  58aad1:      	jmp	0x591a45 <.text+0x190a45>
  58aad6:      	movl	$0x6027e0, %eax         # imm = 0x6027E0
  58aadb:      	jmp	0x591a45 <.text+0x190a45>
  58aae0:      	movl	$0x6027c8, %eax         # imm = 0x6027C8
  58aae5:      	jmp	0x591a45 <.text+0x190a45>
  58aaea:      	movl	$0x6027b8, %eax         # imm = 0x6027B8
  58aaef:      	jmp	0x591a45 <.text+0x190a45>
  58aaf4:      	movl	$0x6027a8, %eax         # imm = 0x6027A8
  58aaf9:      	jmp	0x591a45 <.text+0x190a45>
  58aafe:      	movl	$0x602794, %eax         # imm = 0x602794
  58ab03:      	jmp	0x591a45 <.text+0x190a45>
  58ab08:      	movl	$0x60277c, %eax         # imm = 0x60277C
  58ab0d:      	jmp	0x591a45 <.text+0x190a45>
  58ab12:      	movl	$0x602768, %eax         # imm = 0x602768
  58ab17:      	jmp	0x591a45 <.text+0x190a45>
  58ab1c:      	movl	$0x602754, %eax         # imm = 0x602754
  58ab21:      	jmp	0x591a45 <.text+0x190a45>
  58ab26:      	movl	$0x60273c, %eax         # imm = 0x60273C
  58ab2b:      	jmp	0x591a45 <.text+0x190a45>
  58ab30:      	movl	$0x602720, %eax         # imm = 0x602720
  58ab35:      	jmp	0x591a45 <.text+0x190a45>
  58ab3a:      	movl	$0x602700, %eax         # imm = 0x602700
  58ab3f:      	jmp	0x591a45 <.text+0x190a45>
  58ab44:      	movl	$0x6026e0, %eax         # imm = 0x6026E0
  58ab49:      	jmp	0x591a45 <.text+0x190a45>
  58ab4e:      	movl	$0x6026c8, %eax         # imm = 0x6026C8
  58ab53:      	jmp	0x591a45 <.text+0x190a45>
  58ab58:      	movl	$0x6026ac, %eax         # imm = 0x6026AC
  58ab5d:      	jmp	0x591a45 <.text+0x190a45>
  58ab62:      	movl	$0x602690, %eax         # imm = 0x602690
  58ab67:      	jmp	0x591a45 <.text+0x190a45>
  58ab6c:      	movl	$0x602678, %eax         # imm = 0x602678
  58ab71:      	jmp	0x591a45 <.text+0x190a45>
  58ab76:      	movl	$0x602664, %eax         # imm = 0x602664
  58ab7b:      	jmp	0x591a45 <.text+0x190a45>
  58ab80:      	movl	$0x60264c, %eax         # imm = 0x60264C
  58ab85:      	jmp	0x591a45 <.text+0x190a45>
  58ab8a:      	movl	$0x602630, %eax         # imm = 0x602630
  58ab8f:      	jmp	0x591a45 <.text+0x190a45>
  58ab94:      	movl	$0x60261c, %eax         # imm = 0x60261C
  58ab99:      	jmp	0x591a45 <.text+0x190a45>
  58ab9e:      	movl	$0x602608, %eax         # imm = 0x602608
  58aba3:      	jmp	0x591a45 <.text+0x190a45>
  58aba8:      	movl	$0x6025fc, %eax         # imm = 0x6025FC
  58abad:      	jmp	0x591a45 <.text+0x190a45>
  58abb2:      	movl	$0x6025e0, %eax         # imm = 0x6025E0
  58abb7:      	jmp	0x591a45 <.text+0x190a45>
  58abbc:      	movl	$0x6025c4, %eax         # imm = 0x6025C4
  58abc1:      	jmp	0x591a45 <.text+0x190a45>
  58abc6:      	movl	$0x6025a4, %eax         # imm = 0x6025A4
  58abcb:      	jmp	0x591a45 <.text+0x190a45>
  58abd0:      	movl	$0x60258c, %eax         # imm = 0x60258C
  58abd5:      	jmp	0x591a45 <.text+0x190a45>
  58abda:      	movl	$0x80110600, %ecx       # imm = 0x80110600
  58abdf:      	cmpl	%ecx, %eax
  58abe1:      	jg	0x58af17 <.text+0x189f17>
  58abe7:      	je	0x58af0d <.text+0x189f0d>
  58abed:      	addl	$0x7feefbfe, %eax       # imm = 0x7FEEFBFE
  58abf2:      	cmpl	$0x84, %eax
  58abf7:      	ja	0x591a16 <.text+0x190a16>
  58abfd:      	movzbl	0x59507d(%eax), %eax
  58ac04:      	jmpl	*0x594f45(,%eax,4)
  58ac0b:      	movl	$0x602570, %eax         # imm = 0x602570
  58ac10:      	jmp	0x591a45 <.text+0x190a45>
  58ac15:      	movl	$0x602558, %eax         # imm = 0x602558
  58ac1a:      	jmp	0x591a45 <.text+0x190a45>
  58ac1f:      	movl	$0x60253c, %eax         # imm = 0x60253C
  58ac24:      	jmp	0x591a45 <.text+0x190a45>
  58ac29:      	movl	$0x60251c, %eax         # imm = 0x60251C
  58ac2e:      	jmp	0x591a45 <.text+0x190a45>
  58ac33:      	movl	$0x6024fc, %eax         # imm = 0x6024FC
  58ac38:      	jmp	0x591a45 <.text+0x190a45>
  58ac3d:      	movl	$0x6024e0, %eax         # imm = 0x6024E0
  58ac42:      	jmp	0x591a45 <.text+0x190a45>
  58ac47:      	movl	$0x6024cc, %eax         # imm = 0x6024CC
  58ac4c:      	jmp	0x591a45 <.text+0x190a45>
  58ac51:      	movl	$0x6024ac, %eax         # imm = 0x6024AC
  58ac56:      	jmp	0x591a45 <.text+0x190a45>
  58ac5b:      	movl	$0x602494, %eax         # imm = 0x602494
  58ac60:      	jmp	0x591a45 <.text+0x190a45>
  58ac65:      	movl	$0x60247c, %eax         # imm = 0x60247C
  58ac6a:      	jmp	0x591a45 <.text+0x190a45>
  58ac6f:      	movl	$0x602468, %eax         # imm = 0x602468
  58ac74:      	jmp	0x591a45 <.text+0x190a45>
  58ac79:      	movl	$0x60244c, %eax         # imm = 0x60244C
  58ac7e:      	jmp	0x591a45 <.text+0x190a45>
  58ac83:      	movl	$0x602430, %eax         # imm = 0x602430
  58ac88:      	jmp	0x591a45 <.text+0x190a45>
  58ac8d:      	movl	$0x602410, %eax         # imm = 0x602410
  58ac92:      	jmp	0x591a45 <.text+0x190a45>
  58ac97:      	movl	$0x6023f0, %eax         # imm = 0x6023F0
  58ac9c:      	jmp	0x591a45 <.text+0x190a45>
  58aca1:      	movl	$0x6023d0, %eax         # imm = 0x6023D0
  58aca6:      	jmp	0x591a45 <.text+0x190a45>
  58acab:      	movl	$0x6023b0, %eax         # imm = 0x6023B0
  58acb0:      	jmp	0x591a45 <.text+0x190a45>
  58acb5:      	movl	$0x602394, %eax         # imm = 0x602394
  58acba:      	jmp	0x591a45 <.text+0x190a45>
  58acbf:      	movl	$0x602374, %eax         # imm = 0x602374
  58acc4:      	jmp	0x591a45 <.text+0x190a45>
  58acc9:      	movl	$0x602358, %eax         # imm = 0x602358
  58acce:      	jmp	0x591a45 <.text+0x190a45>
  58acd3:      	movl	$0x60233c, %eax         # imm = 0x60233C
  58acd8:      	jmp	0x591a45 <.text+0x190a45>
  58acdd:      	movl	$0x602320, %eax         # imm = 0x602320
  58ace2:      	jmp	0x591a45 <.text+0x190a45>
  58ace7:      	movl	$0x602304, %eax         # imm = 0x602304
  58acec:      	jmp	0x591a45 <.text+0x190a45>
  58acf1:      	movl	$0x6022e8, %eax         # imm = 0x6022E8
  58acf6:      	jmp	0x591a45 <.text+0x190a45>
  58acfb:      	movl	$0x6022c4, %eax         # imm = 0x6022C4
  58ad00:      	jmp	0x591a45 <.text+0x190a45>
  58ad05:      	movl	$0x6022a4, %eax         # imm = 0x6022A4
  58ad0a:      	jmp	0x591a45 <.text+0x190a45>
  58ad0f:      	movl	$0x602284, %eax         # imm = 0x602284
  58ad14:      	jmp	0x591a45 <.text+0x190a45>
  58ad19:      	movl	$0x602260, %eax         # imm = 0x602260
  58ad1e:      	jmp	0x591a45 <.text+0x190a45>
  58ad23:      	movl	$0x602244, %eax         # imm = 0x602244
  58ad28:      	jmp	0x591a45 <.text+0x190a45>
  58ad2d:      	movl	$0x602220, %eax         # imm = 0x602220
  58ad32:      	jmp	0x591a45 <.text+0x190a45>
  58ad37:      	movl	$0x602204, %eax         # imm = 0x602204
  58ad3c:      	jmp	0x591a45 <.text+0x190a45>
  58ad41:      	movl	$0x6021e8, %eax         # imm = 0x6021E8
  58ad46:      	jmp	0x591a45 <.text+0x190a45>
  58ad4b:      	movl	$0x6021d4, %eax         # imm = 0x6021D4
  58ad50:      	jmp	0x591a45 <.text+0x190a45>
  58ad55:      	movl	$0x6021b8, %eax         # imm = 0x6021B8
  58ad5a:      	jmp	0x591a45 <.text+0x190a45>
  58ad5f:      	movl	$0x602198, %eax         # imm = 0x602198
  58ad64:      	jmp	0x591a45 <.text+0x190a45>
  58ad69:      	movl	$0x602180, %eax         # imm = 0x602180
  58ad6e:      	jmp	0x591a45 <.text+0x190a45>
  58ad73:      	movl	$0x602168, %eax         # imm = 0x602168
  58ad78:      	jmp	0x591a45 <.text+0x190a45>
  58ad7d:      	movl	$0x602148, %eax         # imm = 0x602148
  58ad82:      	jmp	0x591a45 <.text+0x190a45>
  58ad87:      	movl	$0x602128, %eax         # imm = 0x602128
  58ad8c:      	jmp	0x591a45 <.text+0x190a45>
  58ad91:      	movl	$0x602108, %eax         # imm = 0x602108
  58ad96:      	jmp	0x591a45 <.text+0x190a45>
  58ad9b:      	movl	$0x6020e8, %eax         # imm = 0x6020E8
  58ada0:      	jmp	0x591a45 <.text+0x190a45>
  58ada5:      	movl	$0x6020d0, %eax         # imm = 0x6020D0
  58adaa:      	jmp	0x591a45 <.text+0x190a45>
  58adaf:      	movl	$0x6020b4, %eax         # imm = 0x6020B4
  58adb4:      	jmp	0x591a45 <.text+0x190a45>
  58adb9:      	movl	$0x602098, %eax         # imm = 0x602098
  58adbe:      	jmp	0x591a45 <.text+0x190a45>
  58adc3:      	movl	$0x602078, %eax         # imm = 0x602078
  58adc8:      	jmp	0x591a45 <.text+0x190a45>
  58adcd:      	movl	$0x60205c, %eax         # imm = 0x60205C
  58add2:      	jmp	0x591a45 <.text+0x190a45>
  58add7:      	movl	$0x60203c, %eax         # imm = 0x60203C
  58addc:      	jmp	0x591a45 <.text+0x190a45>
  58ade1:      	movl	$0x60201c, %eax         # imm = 0x60201C
  58ade6:      	jmp	0x591a45 <.text+0x190a45>
  58adeb:      	movl	$0x601ffc, %eax         # imm = 0x601FFC
  58adf0:      	jmp	0x591a45 <.text+0x190a45>
  58adf5:      	movl	$0x601fd4, %eax         # imm = 0x601FD4
  58adfa:      	jmp	0x591a45 <.text+0x190a45>
  58adff:      	movl	$0x601fac, %eax         # imm = 0x601FAC
  58ae04:      	jmp	0x591a45 <.text+0x190a45>
  58ae09:      	movl	$0x601f88, %eax         # imm = 0x601F88
  58ae0e:      	jmp	0x591a45 <.text+0x190a45>
  58ae13:      	movl	$0x601f68, %eax         # imm = 0x601F68
  58ae18:      	jmp	0x591a45 <.text+0x190a45>
  58ae1d:      	movl	$0x601f44, %eax         # imm = 0x601F44
  58ae22:      	jmp	0x591a45 <.text+0x190a45>
  58ae27:      	movl	$0x601f1c, %eax         # imm = 0x601F1C
  58ae2c:      	jmp	0x591a45 <.text+0x190a45>
  58ae31:      	movl	$0x601ef0, %eax         # imm = 0x601EF0
  58ae36:      	jmp	0x591a45 <.text+0x190a45>
  58ae3b:      	movl	$0x601ec8, %eax         # imm = 0x601EC8
  58ae40:      	jmp	0x591a45 <.text+0x190a45>
  58ae45:      	movl	$0x601ea8, %eax         # imm = 0x601EA8
  58ae4a:      	jmp	0x591a45 <.text+0x190a45>
  58ae4f:      	movl	$0x601e88, %eax         # imm = 0x601E88
  58ae54:      	jmp	0x591a45 <.text+0x190a45>
  58ae59:      	movl	$0x601e60, %eax         # imm = 0x601E60
  58ae5e:      	jmp	0x591a45 <.text+0x190a45>
  58ae63:      	movl	$0x601e38, %eax         # imm = 0x601E38
  58ae68:      	jmp	0x591a45 <.text+0x190a45>
  58ae6d:      	movl	$0x601e18, %eax         # imm = 0x601E18
  58ae72:      	jmp	0x591a45 <.text+0x190a45>
  58ae77:      	movl	$0x601dec, %eax         # imm = 0x601DEC
  58ae7c:      	jmp	0x591a45 <.text+0x190a45>
  58ae81:      	movl	$0x601dbc, %eax         # imm = 0x601DBC
  58ae86:      	jmp	0x591a45 <.text+0x190a45>
  58ae8b:      	movl	$0x601d94, %eax         # imm = 0x601D94
  58ae90:      	jmp	0x591a45 <.text+0x190a45>
  58ae95:      	movl	$0x601d70, %eax         # imm = 0x601D70
  58ae9a:      	jmp	0x591a45 <.text+0x190a45>
  58ae9f:      	movl	$0x601d50, %eax         # imm = 0x601D50
  58aea4:      	jmp	0x591a45 <.text+0x190a45>
  58aea9:      	movl	$0x601d34, %eax         # imm = 0x601D34
  58aeae:      	jmp	0x591a45 <.text+0x190a45>
  58aeb3:      	movl	$0x601d18, %eax         # imm = 0x601D18
  58aeb8:      	jmp	0x591a45 <.text+0x190a45>
  58aebd:      	movl	$0x601cf8, %eax         # imm = 0x601CF8
  58aec2:      	jmp	0x591a45 <.text+0x190a45>
  58aec7:      	movl	$0x601cd4, %eax         # imm = 0x601CD4
  58aecc:      	jmp	0x591a45 <.text+0x190a45>
  58aed1:      	movl	$0x601cb4, %eax         # imm = 0x601CB4
  58aed6:      	jmp	0x591a45 <.text+0x190a45>
  58aedb:      	movl	$0x601c94, %eax         # imm = 0x601C94
  58aee0:      	jmp	0x591a45 <.text+0x190a45>
  58aee5:      	movl	$0x601c70, %eax         # imm = 0x601C70
  58aeea:      	jmp	0x591a45 <.text+0x190a45>
  58aeef:      	movl	$0x601c50, %eax         # imm = 0x601C50
  58aef4:      	jmp	0x591a45 <.text+0x190a45>
  58aef9:      	movl	$0x601c24, %eax         # imm = 0x601C24
  58aefe:      	jmp	0x591a45 <.text+0x190a45>
  58af03:      	movl	$0x601c08, %eax         # imm = 0x601C08
  58af08:      	jmp	0x591a45 <.text+0x190a45>
  58af0d:      	movl	$0x601be8, %eax         # imm = 0x601BE8
  58af12:      	jmp	0x591a45 <.text+0x190a45>
  58af17:      	movl	$0x80110701, %ecx       # imm = 0x80110701
  58af1c:      	cmpl	%ecx, %eax
  58af1e:      	jg	0x58af96 <.text+0x189f96>
  58af20:      	je	0x58af8c <.text+0x189f8c>
  58af22:      	cmpl	$0x80110601, %eax       # imm = 0x80110601
  58af27:      	je	0x58af82 <.text+0x189f82>
  58af29:      	cmpl	$0x80110602, %eax       # imm = 0x80110602
  58af2e:      	je	0x58af78 <.text+0x189f78>
  58af30:      	cmpl	$0x80110603, %eax       # imm = 0x80110603
  58af35:      	je	0x58af6e <.text+0x189f6e>
  58af37:      	cmpl	$0x80110604, %eax       # imm = 0x80110604
  58af3c:      	je	0x58af64 <.text+0x189f64>
  58af3e:      	cmpl	$0x80110605, %eax       # imm = 0x80110605
  58af43:      	je	0x58af5a <.text+0x189f5a>
  58af45:      	cmpl	$0x80110606, %eax       # imm = 0x80110606
  58af4a:      	jne	0x591a16 <.text+0x190a16>
  58af50:      	movl	$0x601bcc, %eax         # imm = 0x601BCC
  58af55:      	jmp	0x591a45 <.text+0x190a45>
  58af5a:      	movl	$0x601bb4, %eax         # imm = 0x601BB4
  58af5f:      	jmp	0x591a45 <.text+0x190a45>
  58af64:      	movl	$0x601ba0, %eax         # imm = 0x601BA0
  58af69:      	jmp	0x591a45 <.text+0x190a45>
  58af6e:      	movl	$0x601b84, %eax         # imm = 0x601B84
  58af73:      	jmp	0x591a45 <.text+0x190a45>
  58af78:      	movl	$0x601b5c, %eax         # imm = 0x601B5C
  58af7d:      	jmp	0x591a45 <.text+0x190a45>
  58af82:      	movl	$0x601b3c, %eax         # imm = 0x601B3C
  58af87:      	jmp	0x591a45 <.text+0x190a45>
  58af8c:      	movl	$0x601b20, %eax         # imm = 0x601B20
  58af91:      	jmp	0x591a45 <.text+0x190a45>
  58af96:      	cmpl	$0x80110808, %eax       # imm = 0x80110808
  58af9b:      	je	0x58afe5 <.text+0x189fe5>
  58af9d:      	cmpl	$0x80110809, %eax       # imm = 0x80110809
  58afa2:      	je	0x58afdb <.text+0x189fdb>
  58afa4:      	cmpl	$0x8011080a, %eax       # imm = 0x8011080A
  58afa9:      	je	0x58afd1 <.text+0x189fd1>
  58afab:      	cmpl	$0x8011080b, %eax       # imm = 0x8011080B
  58afb0:      	je	0x58afc7 <.text+0x189fc7>
  58afb2:      	cmpl	$0x8011080d, %eax       # imm = 0x8011080D
  58afb7:      	jne	0x591a16 <.text+0x190a16>
  58afbd:      	movl	$0x601af0, %eax         # imm = 0x601AF0
  58afc2:      	jmp	0x591a45 <.text+0x190a45>
  58afc7:      	movl	$0x601ad0, %eax         # imm = 0x601AD0
  58afcc:      	jmp	0x591a45 <.text+0x190a45>
  58afd1:      	movl	$0x601ab4, %eax         # imm = 0x601AB4
  58afd6:      	jmp	0x591a45 <.text+0x190a45>
  58afdb:      	movl	$0x601a90, %eax         # imm = 0x601A90
  58afe0:      	jmp	0x591a45 <.text+0x190a45>
  58afe5:      	movl	$0x601a6c, %eax         # imm = 0x601A6C
  58afea:      	jmp	0x591a45 <.text+0x190a45>
  58afef:      	movl	$0x601a54, %eax         # imm = 0x601A54
  58aff4:      	jmp	0x591a45 <.text+0x190a45>
  58aff9:      	movl	$0x88760005, %ecx       # imm = 0x88760005
  58affe:      	cmpl	%ecx, %eax
  58b000:      	jg	0x58b0f3 <.text+0x18a0f3>
  58b006:      	je	0x58b0e9 <.text+0x18a0e9>
  58b00c:      	addl	$0x7feef7f1, %eax       # imm = 0x7FEEF7F1
  58b011:      	cmpl	$0x14, %eax
  58b014:      	ja	0x591a16 <.text+0x190a16>
  58b01a:      	jmpl	*0x595105(,%eax,4)
  58b021:      	movl	$0x601a30, %eax         # imm = 0x601A30
  58b026:      	jmp	0x591a45 <.text+0x190a45>
  58b02b:      	movl	$0x601a0c, %eax         # imm = 0x601A0C
  58b030:      	jmp	0x591a45 <.text+0x190a45>
  58b035:      	movl	$0x6019e8, %eax         # imm = 0x6019E8
  58b03a:      	jmp	0x591a45 <.text+0x190a45>
  58b03f:      	movl	$0x6019bc, %eax         # imm = 0x6019BC
  58b044:      	jmp	0x591a45 <.text+0x190a45>
  58b049:      	movl	$0x601998, %eax         # imm = 0x601998
  58b04e:      	jmp	0x591a45 <.text+0x190a45>
  58b053:      	movl	$0x601978, %eax         # imm = 0x601978
  58b058:      	jmp	0x591a45 <.text+0x190a45>
  58b05d:      	movl	$0x601950, %eax         # imm = 0x601950
  58b062:      	jmp	0x591a45 <.text+0x190a45>
  58b067:      	movl	$0x601924, %eax         # imm = 0x601924
  58b06c:      	jmp	0x591a45 <.text+0x190a45>
  58b071:      	movl	$0x601900, %eax         # imm = 0x601900
  58b076:      	jmp	0x591a45 <.text+0x190a45>
  58b07b:      	movl	$0x6018e0, %eax         # imm = 0x6018E0
  58b080:      	jmp	0x591a45 <.text+0x190a45>
  58b085:      	movl	$0x6018ac, %eax         # imm = 0x6018AC
  58b08a:      	jmp	0x591a45 <.text+0x190a45>
  58b08f:      	movl	$0x601870, %eax         # imm = 0x601870
  58b094:      	jmp	0x591a45 <.text+0x190a45>
  58b099:      	movl	$0x601854, %eax         # imm = 0x601854
  58b09e:      	jmp	0x591a45 <.text+0x190a45>
  58b0a3:      	movl	$0x601838, %eax         # imm = 0x601838
  58b0a8:      	jmp	0x591a45 <.text+0x190a45>
  58b0ad:      	movl	$0x601818, %eax         # imm = 0x601818
  58b0b2:      	jmp	0x591a45 <.text+0x190a45>
  58b0b7:      	movl	$0x6017ec, %eax         # imm = 0x6017EC
  58b0bc:      	jmp	0x591a45 <.text+0x190a45>
  58b0c1:      	movl	$0x6017c8, %eax         # imm = 0x6017C8
  58b0c6:      	jmp	0x591a45 <.text+0x190a45>
  58b0cb:      	movl	$0x6017a8, %eax         # imm = 0x6017A8
  58b0d0:      	jmp	0x591a45 <.text+0x190a45>
  58b0d5:      	movl	$0x601790, %eax         # imm = 0x601790
  58b0da:      	jmp	0x591a45 <.text+0x190a45>
  58b0df:      	movl	$0x60176c, %eax         # imm = 0x60176C
  58b0e4:      	jmp	0x591a45 <.text+0x190a45>
  58b0e9:      	movl	$0x601750, %eax         # imm = 0x601750
  58b0ee:      	jmp	0x591a45 <.text+0x190a45>
  58b0f3:      	movl	$0x8876038f, %ecx       # imm = 0x8876038F
  58b0f8:      	cmpl	%ecx, %eax
  58b0fa:      	jg	0x58b95a <.text+0x18a95a>
  58b100:      	je	0x58b950 <.text+0x18a950>
  58b106:      	movl	$0x8876023d, %ecx       # imm = 0x8876023D
  58b10b:      	cmpl	%ecx, %eax
  58b10d:      	jg	0x58b644 <.text+0x18a644>
  58b113:      	je	0x58b63a <.text+0x18a63a>
  58b119:      	movl	$0x8876014f, %ecx       # imm = 0x8876014F
  58b11e:      	cmpl	%ecx, %eax
  58b120:      	jg	0x58b3f9 <.text+0x18a3f9>
  58b126:      	je	0x58b3ef <.text+0x18a3ef>
  58b12c:      	addl	$-0x7d, %ecx
  58b12f:      	cmpl	%ecx, %eax
  58b131:      	jg	0x58b29b <.text+0x18a29b>
  58b137:      	je	0x58b291 <.text+0x18a291>
  58b13d:      	movl	$0x88760082, %ecx       # imm = 0x88760082
  58b142:      	cmpl	%ecx, %eax
  58b144:      	jg	0x58b1fd <.text+0x18a1fd>
  58b14a:      	je	0x58b1f3 <.text+0x18a1f3>
  58b150:      	addl	$-0x28, %ecx
  58b153:      	cmpl	%ecx, %eax
  58b155:      	jg	0x58b1ab <.text+0x18a1ab>
  58b157:      	je	0x58b1a1 <.text+0x18a1a1>
  58b159:      	cmpl	$0x8876000a, %eax       # imm = 0x8876000A
  58b15e:      	je	0x58b197 <.text+0x18a197>
  58b160:      	cmpl	$0x88760014, %eax       # imm = 0x88760014
  58b165:      	je	0x58b18d <.text+0x18a18d>
  58b167:      	cmpl	$0x88760028, %eax       # imm = 0x88760028
  58b16c:      	je	0x58b183 <.text+0x18a183>
  58b16e:      	cmpl	$0x88760037, %eax       # imm = 0x88760037
  58b173:      	jne	0x591a16 <.text+0x190a16>
  58b179:      	movl	$0x601740, %eax         # imm = 0x601740
  58b17e:      	jmp	0x591a45 <.text+0x190a45>
  58b183:      	movl	$0x601728, %eax         # imm = 0x601728
  58b188:      	jmp	0x591a45 <.text+0x190a45>
  58b18d:      	movl	$0x60170c, %eax         # imm = 0x60170C
  58b192:      	jmp	0x591a45 <.text+0x190a45>
  58b197:      	movl	$0x6016f0, %eax         # imm = 0x6016F0
  58b19c:      	jmp	0x591a45 <.text+0x190a45>
  58b1a1:      	movl	$0x6016dc, %eax         # imm = 0x6016DC
  58b1a6:      	jmp	0x591a45 <.text+0x190a45>
  58b1ab:      	cmpl	$0x8876005f, %eax       # imm = 0x8876005F
  58b1b0:      	je	0x58b1e9 <.text+0x18a1e9>
  58b1b2:      	cmpl	$0x88760064, %eax       # imm = 0x88760064
  58b1b7:      	je	0x58b1df <.text+0x18a1df>
  58b1b9:      	cmpl	$0x8876006e, %eax       # imm = 0x8876006E
  58b1be:      	je	0x58b1d5 <.text+0x18a1d5>
  58b1c0:      	cmpl	$0x88760078, %eax       # imm = 0x88760078
  58b1c5:      	jne	0x591a16 <.text+0x190a16>
  58b1cb:      	movl	$0x6016c8, %eax         # imm = 0x6016C8
  58b1d0:      	jmp	0x591a45 <.text+0x190a45>
  58b1d5:      	movl	$0x6016b0, %eax         # imm = 0x6016B0
  58b1da:      	jmp	0x591a45 <.text+0x190a45>
  58b1df:      	movl	$0x60169c, %eax         # imm = 0x60169C
  58b1e4:      	jmp	0x591a45 <.text+0x190a45>
  58b1e9:      	movl	$0x601680, %eax         # imm = 0x601680
  58b1ee:      	jmp	0x591a45 <.text+0x190a45>
  58b1f3:      	movl	$0x60166c, %eax         # imm = 0x60166C
  58b1f8:      	jmp	0x591a45 <.text+0x190a45>
  58b1fd:      	movl	$0x887600b4, %ecx       # imm = 0x887600B4
  58b202:      	cmpl	%ecx, %eax
  58b204:      	jg	0x58b25a <.text+0x18a25a>
  58b206:      	je	0x58b250 <.text+0x18a250>
  58b208:      	cmpl	$0x88760091, %eax       # imm = 0x88760091
  58b20d:      	je	0x58b246 <.text+0x18a246>
  58b20f:      	cmpl	$0x88760096, %eax       # imm = 0x88760096
  58b214:      	je	0x58b23c <.text+0x18a23c>
  58b216:      	cmpl	$0x887600a0, %eax       # imm = 0x887600A0
  58b21b:      	je	0x58b232 <.text+0x18a232>
  58b21d:      	cmpl	$0x887600aa, %eax       # imm = 0x887600AA
  58b222:      	jne	0x591a16 <.text+0x190a16>
  58b228:      	movl	$0x601660, %eax         # imm = 0x601660
  58b22d:      	jmp	0x591a45 <.text+0x190a45>
  58b232:      	movl	$0x601648, %eax         # imm = 0x601648
  58b237:      	jmp	0x591a45 <.text+0x190a45>
  58b23c:      	movl	$0x601634, %eax         # imm = 0x601634
  58b241:      	jmp	0x591a45 <.text+0x190a45>
  58b246:      	movl	$0x601618, %eax         # imm = 0x601618
  58b24b:      	jmp	0x591a45 <.text+0x190a45>
  58b250:      	movl	$0x601608, %eax         # imm = 0x601608
  58b255:      	jmp	0x591a45 <.text+0x190a45>
  58b25a:      	cmpl	$0x887600b5, %eax       # imm = 0x887600B5
  58b25f:      	je	0x58b287 <.text+0x18a287>
  58b261:      	cmpl	$0x887600b6, %eax       # imm = 0x887600B6
  58b266:      	je	0x58b27d <.text+0x18a27d>
  58b268:      	cmpl	$0x887600cd, %eax       # imm = 0x887600CD
  58b26d:      	jne	0x591a16 <.text+0x190a16>
  58b273:      	movl	$0x6015f4, %eax         # imm = 0x6015F4
  58b278:      	jmp	0x591a45 <.text+0x190a45>
  58b27d:      	movl	$0x6015e0, %eax         # imm = 0x6015E0
  58b282:      	jmp	0x591a45 <.text+0x190a45>
  58b287:      	movl	$0x6015c8, %eax         # imm = 0x6015C8
  58b28c:      	jmp	0x591a45 <.text+0x190a45>
  58b291:      	movl	$0x6015b4, %eax         # imm = 0x6015B4
  58b296:      	jmp	0x591a45 <.text+0x190a45>
  58b29b:      	movl	$0x88760104, %ecx       # imm = 0x88760104
  58b2a0:      	cmpl	%ecx, %eax
  58b2a2:      	jg	0x58b35b <.text+0x18a35b>
  58b2a8:      	je	0x58b351 <.text+0x18a351>
  58b2ae:      	addl	$-0x23, %ecx
  58b2b1:      	cmpl	%ecx, %eax
  58b2b3:      	jg	0x58b309 <.text+0x18a309>
  58b2b5:      	je	0x58b2ff <.text+0x18a2ff>
  58b2b7:      	cmpl	$0x887600d4, %eax       # imm = 0x887600D4
  58b2bc:      	je	0x58b2f5 <.text+0x18a2f5>
  58b2be:      	cmpl	$0x887600d7, %eax       # imm = 0x887600D7
  58b2c3:      	je	0x58b2eb <.text+0x18a2eb>
  58b2c5:      	cmpl	$0x887600dc, %eax       # imm = 0x887600DC
  58b2ca:      	je	0x58b2e1 <.text+0x18a2e1>
  58b2cc:      	cmpl	$0x887600de, %eax       # imm = 0x887600DE
  58b2d1:      	jne	0x591a16 <.text+0x190a16>
  58b2d7:      	movl	$0x601598, %eax         # imm = 0x601598
  58b2dc:      	jmp	0x591a45 <.text+0x190a45>
  58b2e1:      	movl	$0x601584, %eax         # imm = 0x601584
  58b2e6:      	jmp	0x591a45 <.text+0x190a45>
  58b2eb:      	movl	$0x601570, %eax         # imm = 0x601570
  58b2f0:      	jmp	0x591a45 <.text+0x190a45>
  58b2f5:      	movl	$0x601554, %eax         # imm = 0x601554
  58b2fa:      	jmp	0x591a45 <.text+0x190a45>
  58b2ff:      	movl	$0x60153c, %eax         # imm = 0x60153C
  58b304:      	jmp	0x591a45 <.text+0x190a45>
  58b309:      	cmpl	$0x887600e6, %eax       # imm = 0x887600E6
  58b30e:      	je	0x58b347 <.text+0x18a347>
  58b310:      	cmpl	$0x887600f0, %eax       # imm = 0x887600F0
  58b315:      	je	0x58b33d <.text+0x18a33d>
  58b317:      	cmpl	$0x887600fa, %eax       # imm = 0x887600FA
  58b31c:      	je	0x58b333 <.text+0x18a333>
  58b31e:      	cmpl	$0x887600ff, %eax       # imm = 0x887600FF
  58b323:      	jne	0x591a16 <.text+0x190a16>
  58b329:      	movl	$0x60152c, %eax         # imm = 0x60152C
  58b32e:      	jmp	0x591a45 <.text+0x190a45>
  58b333:      	movl	$0x601518, %eax         # imm = 0x601518
  58b338:      	jmp	0x591a45 <.text+0x190a45>
  58b33d:      	movl	$0x60150c, %eax         # imm = 0x60150C
  58b342:      	jmp	0x591a45 <.text+0x190a45>
  58b347:      	movl	$0x6014fc, %eax         # imm = 0x6014FC
  58b34c:      	jmp	0x591a45 <.text+0x190a45>
  58b351:      	movl	$0x6014e8, %eax         # imm = 0x6014E8
  58b356:      	jmp	0x591a45 <.text+0x190a45>
  58b35b:      	movl	$0x8876013c, %ecx       # imm = 0x8876013C
  58b360:      	cmpl	%ecx, %eax
  58b362:      	jg	0x58b3b8 <.text+0x18a3b8>
  58b364:      	je	0x58b3ae <.text+0x18a3ae>
  58b366:      	cmpl	$0x8876010e, %eax       # imm = 0x8876010E
  58b36b:      	je	0x58b3a4 <.text+0x18a3a4>
  58b36d:      	cmpl	$0x88760118, %eax       # imm = 0x88760118
  58b372:      	je	0x58b39a <.text+0x18a39a>
  58b374:      	cmpl	$0x88760122, %eax       # imm = 0x88760122
  58b379:      	je	0x58b390 <.text+0x18a390>
  58b37b:      	cmpl	$0x88760136, %eax       # imm = 0x88760136
  58b380:      	jne	0x591a16 <.text+0x190a16>
  58b386:      	movl	$0x6014d4, %eax         # imm = 0x6014D4
  58b38b:      	jmp	0x591a45 <.text+0x190a45>
  58b390:      	movl	$0x6014c0, %eax         # imm = 0x6014C0
  58b395:      	jmp	0x591a45 <.text+0x190a45>
  58b39a:      	movl	$0x6014ac, %eax         # imm = 0x6014AC
  58b39f:      	jmp	0x591a45 <.text+0x190a45>
  58b3a4:      	movl	$0x601494, %eax         # imm = 0x601494
  58b3a9:      	jmp	0x591a45 <.text+0x190a45>
  58b3ae:      	movl	$0x601480, %eax         # imm = 0x601480
  58b3b3:      	jmp	0x591a45 <.text+0x190a45>
  58b3b8:      	cmpl	$0x8876013d, %eax       # imm = 0x8876013D
  58b3bd:      	je	0x58b3e5 <.text+0x18a3e5>
  58b3bf:      	cmpl	$0x88760140, %eax       # imm = 0x88760140
  58b3c4:      	je	0x58b3db <.text+0x18a3db>
  58b3c6:      	cmpl	$0x8876014a, %eax       # imm = 0x8876014A
  58b3cb:      	jne	0x591a16 <.text+0x190a16>
  58b3d1:      	movl	$0x60146c, %eax         # imm = 0x60146C
  58b3d6:      	jmp	0x591a45 <.text+0x190a45>
  58b3db:      	movl	$0x601458, %eax         # imm = 0x601458
  58b3e0:      	jmp	0x591a45 <.text+0x190a45>
  58b3e5:      	movl	$0x601440, %eax         # imm = 0x601440
  58b3ea:      	jmp	0x591a45 <.text+0x190a45>
  58b3ef:      	movl	$0x601430, %eax         # imm = 0x601430
  58b3f4:      	jmp	0x591a45 <.text+0x190a45>
  58b3f9:      	movl	$0x887601fe, %ecx       # imm = 0x887601FE
  58b3fe:      	cmpl	%ecx, %eax
  58b400:      	jg	0x58b56a <.text+0x18a56a>
  58b406:      	je	0x58b560 <.text+0x18a560>
  58b40c:      	addl	$-0x5a, %ecx
  58b40f:      	cmpl	%ecx, %eax
  58b411:      	jg	0x58b4cc <.text+0x18a4cc>
  58b417:      	je	0x58b4c2 <.text+0x18a4c2>
  58b41d:      	movl	$0x8876017e, %ecx       # imm = 0x8876017E
  58b422:      	cmpl	%ecx, %eax
  58b424:      	jg	0x58b47a <.text+0x18a47a>
  58b426:      	je	0x58b470 <.text+0x18a470>
  58b428:      	cmpl	$0x88760154, %eax       # imm = 0x88760154
  58b42d:      	je	0x58b466 <.text+0x18a466>
  58b42f:      	cmpl	$0x8876015e, %eax       # imm = 0x8876015E
  58b434:      	je	0x58b45c <.text+0x18a45c>
  58b436:      	cmpl	$0x88760168, %eax       # imm = 0x88760168
  58b43b:      	je	0x58b452 <.text+0x18a452>
  58b43d:      	cmpl	$0x8876017c, %eax       # imm = 0x8876017C
  58b442:      	jne	0x591a16 <.text+0x190a16>
  58b448:      	movl	$0x601418, %eax         # imm = 0x601418
  58b44d:      	jmp	0x591a45 <.text+0x190a45>
  58b452:      	movl	$0x601408, %eax         # imm = 0x601408
  58b457:      	jmp	0x591a45 <.text+0x190a45>
  58b45c:      	movl	$0x6013f4, %eax         # imm = 0x6013F4
  58b461:      	jmp	0x591a45 <.text+0x190a45>
  58b466:      	movl	$0x6013e0, %eax         # imm = 0x6013E0
  58b46b:      	jmp	0x591a45 <.text+0x190a45>
  58b470:      	movl	$0x6013c8, %eax         # imm = 0x6013C8
  58b475:      	jmp	0x591a45 <.text+0x190a45>
  58b47a:      	cmpl	$0x88760180, %eax       # imm = 0x88760180
  58b47f:      	je	0x58b4b8 <.text+0x18a4b8>
  58b481:      	cmpl	$0x88760183, %eax       # imm = 0x88760183
  58b486:      	je	0x58b4ae <.text+0x18a4ae>
  58b488:      	cmpl	$0x88760190, %eax       # imm = 0x88760190
  58b48d:      	je	0x58b4a4 <.text+0x18a4a4>
  58b48f:      	cmpl	$0x8876019a, %eax       # imm = 0x8876019A
  58b494:      	jne	0x591a16 <.text+0x190a16>
  58b49a:      	movl	$0x6013a8, %eax         # imm = 0x6013A8
  58b49f:      	jmp	0x591a45 <.text+0x190a45>
  58b4a4:      	movl	$0x601390, %eax         # imm = 0x601390
  58b4a9:      	jmp	0x591a45 <.text+0x190a45>
  58b4ae:      	movl	$0x60137c, %eax         # imm = 0x60137C
  58b4b3:      	jmp	0x591a45 <.text+0x190a45>
  58b4b8:      	movl	$0x601358, %eax         # imm = 0x601358
  58b4bd:      	jmp	0x591a45 <.text+0x190a45>
  58b4c2:      	movl	$0x601338, %eax         # imm = 0x601338
  58b4c7:      	jmp	0x591a45 <.text+0x190a45>
  58b4cc:      	movl	$0x887601cc, %ecx       # imm = 0x887601CC
  58b4d1:      	cmpl	%ecx, %eax
  58b4d3:      	jg	0x58b529 <.text+0x18a529>
  58b4d5:      	je	0x58b51f <.text+0x18a51f>
  58b4d7:      	cmpl	$0x887601ae, %eax       # imm = 0x887601AE
  58b4dc:      	je	0x58b515 <.text+0x18a515>
  58b4de:      	cmpl	$0x887601b3, %eax       # imm = 0x887601B3
  58b4e3:      	je	0x58b50b <.text+0x18a50b>
  58b4e5:      	cmpl	$0x887601b8, %eax       # imm = 0x887601B8
  58b4ea:      	je	0x58b501 <.text+0x18a501>
  58b4ec:      	cmpl	$0x887601c2, %eax       # imm = 0x887601C2
  58b4f1:      	jne	0x591a16 <.text+0x190a16>
  58b4f7:      	movl	$0x601324, %eax         # imm = 0x601324
  58b4fc:      	jmp	0x591a45 <.text+0x190a45>
  58b501:      	movl	$0x60130c, %eax         # imm = 0x60130C
  58b506:      	jmp	0x591a45 <.text+0x190a45>
  58b50b:      	movl	$0x6012f4, %eax         # imm = 0x6012F4
  58b510:      	jmp	0x591a45 <.text+0x190a45>
  58b515:      	movl	$0x6012e0, %eax         # imm = 0x6012E0
  58b51a:      	jmp	0x591a45 <.text+0x190a45>
  58b51f:      	movl	$0x6012c4, %eax         # imm = 0x6012C4
  58b524:      	jmp	0x591a45 <.text+0x190a45>
  58b529:      	cmpl	$0x887601d6, %eax       # imm = 0x887601D6
  58b52e:      	je	0x58b556 <.text+0x18a556>
  58b530:      	cmpl	$0x887601e0, %eax       # imm = 0x887601E0
  58b535:      	je	0x58b54c <.text+0x18a54c>
  58b537:      	cmpl	$0x887601ea, %eax       # imm = 0x887601EA
  58b53c:      	jne	0x591a16 <.text+0x190a16>
  58b542:      	movl	$0x6012b0, %eax         # imm = 0x6012B0
  58b547:      	jmp	0x591a45 <.text+0x190a45>
  58b54c:      	movl	$0x60129c, %eax         # imm = 0x60129C
  58b551:      	jmp	0x591a45 <.text+0x190a45>
  58b556:      	movl	$0x601288, %eax         # imm = 0x601288
  58b55b:      	jmp	0x591a45 <.text+0x190a45>
  58b560:      	movl	$0x601270, %eax         # imm = 0x601270
  58b565:      	jmp	0x591a45 <.text+0x190a45>
  58b56a:      	addl	$0x7789fdf8, %eax       # imm = 0x7789FDF8
  58b56f:      	cmpl	$0x34, %eax
  58b572:      	ja	0x591a16 <.text+0x190a16>
  58b578:      	movzbl	0x5951a5(%eax), %eax
  58b57f:      	jmpl	*0x595159(,%eax,4)
  58b586:      	movl	$0x601258, %eax         # imm = 0x601258
  58b58b:      	jmp	0x591a45 <.text+0x190a45>
  58b590:      	movl	$0x601244, %eax         # imm = 0x601244
  58b595:      	jmp	0x591a45 <.text+0x190a45>
  58b59a:      	movl	$0x601224, %eax         # imm = 0x601224
  58b59f:      	jmp	0x591a45 <.text+0x190a45>
  58b5a4:      	movl	$0x60120c, %eax         # imm = 0x60120C
  58b5a9:      	jmp	0x591a45 <.text+0x190a45>
  58b5ae:      	movl	$0x6011ec, %eax         # imm = 0x6011EC
  58b5b3:      	jmp	0x591a45 <.text+0x190a45>
  58b5b8:      	movl	$0x6011dc, %eax         # imm = 0x6011DC
  58b5bd:      	jmp	0x591a45 <.text+0x190a45>
  58b5c2:      	movl	$0x6011c0, %eax         # imm = 0x6011C0
  58b5c7:      	jmp	0x591a45 <.text+0x190a45>
  58b5cc:      	movl	$0x6011a0, %eax         # imm = 0x6011A0
  58b5d1:      	jmp	0x591a45 <.text+0x190a45>
  58b5d6:      	movl	$0x601188, %eax         # imm = 0x601188
  58b5db:      	jmp	0x591a45 <.text+0x190a45>
  58b5e0:      	movl	$0x601164, %eax         # imm = 0x601164
  58b5e5:      	jmp	0x591a45 <.text+0x190a45>
  58b5ea:      	movl	$0x601150, %eax         # imm = 0x601150
  58b5ef:      	jmp	0x591a45 <.text+0x190a45>
  58b5f4:      	movl	$0x601138, %eax         # imm = 0x601138
  58b5f9:      	jmp	0x591a45 <.text+0x190a45>
  58b5fe:      	movl	$0x60111c, %eax         # imm = 0x60111C
  58b603:      	jmp	0x591a45 <.text+0x190a45>
  58b608:      	movl	$0x601104, %eax         # imm = 0x601104
  58b60d:      	jmp	0x591a45 <.text+0x190a45>
  58b612:      	movl	$0x6010f4, %eax         # imm = 0x6010F4
  58b617:      	jmp	0x591a45 <.text+0x190a45>
  58b61c:      	movl	$0x6010dc, %eax         # imm = 0x6010DC
  58b621:      	jmp	0x591a45 <.text+0x190a45>
  58b626:      	movl	$0x6010c4, %eax         # imm = 0x6010C4
  58b62b:      	jmp	0x591a45 <.text+0x190a45>
  58b630:      	movl	$0x6010ac, %eax         # imm = 0x6010AC
  58b635:      	jmp	0x591a45 <.text+0x190a45>
  58b63a:      	movl	$0x601098, %eax         # imm = 0x601098
  58b63f:      	jmp	0x591a45 <.text+0x190a45>
  58b644:      	addl	$0x7789fdc2, %eax       # imm = 0x7789FDC2
  58b649:      	cmpl	$0x150, %eax            # imm = 0x150
  58b64e:      	ja	0x591a16 <.text+0x190a16>
  58b654:      	movzbl	0x59530d(%eax), %eax
  58b65b:      	jmpl	*0x5951dd(,%eax,4)
  58b662:      	movl	$0x601080, %eax         # imm = 0x601080
  58b667:      	jmp	0x591a45 <.text+0x190a45>
  58b66c:      	movl	$0x601070, %eax         # imm = 0x601070
  58b671:      	jmp	0x591a45 <.text+0x190a45>
  58b676:      	movl	$0x60105c, %eax         # imm = 0x60105C
  58b67b:      	jmp	0x591a45 <.text+0x190a45>
  58b680:      	movl	$0x601044, %eax         # imm = 0x601044
  58b685:      	jmp	0x591a45 <.text+0x190a45>
  58b68a:      	movl	$0x601030, %eax         # imm = 0x601030
  58b68f:      	jmp	0x591a45 <.text+0x190a45>
  58b694:      	movl	$0x601018, %eax         # imm = 0x601018
  58b699:      	jmp	0x591a45 <.text+0x190a45>
  58b69e:      	movl	$0x600ffc, %eax         # imm = 0x600FFC
  58b6a3:      	jmp	0x591a45 <.text+0x190a45>
  58b6a8:      	movl	$0x600fdc, %eax         # imm = 0x600FDC
  58b6ad:      	jmp	0x591a45 <.text+0x190a45>
  58b6b2:      	movl	$0x600fc8, %eax         # imm = 0x600FC8
  58b6b7:      	jmp	0x591a45 <.text+0x190a45>
  58b6bc:      	movl	$0x600fb4, %eax         # imm = 0x600FB4
  58b6c1:      	jmp	0x591a45 <.text+0x190a45>
  58b6c6:      	movl	$0x600fa4, %eax         # imm = 0x600FA4
  58b6cb:      	jmp	0x591a45 <.text+0x190a45>
  58b6d0:      	movl	$0x600f90, %eax         # imm = 0x600F90
  58b6d5:      	jmp	0x591a45 <.text+0x190a45>
  58b6da:      	movl	$0x600f84, %eax         # imm = 0x600F84
  58b6df:      	jmp	0x591a45 <.text+0x190a45>
  58b6e4:      	movl	$0x600f74, %eax         # imm = 0x600F74
  58b6e9:      	jmp	0x591a45 <.text+0x190a45>
  58b6ee:      	movl	$0x600f5c, %eax         # imm = 0x600F5C
  58b6f3:      	jmp	0x591a45 <.text+0x190a45>
  58b6f8:      	movl	$0x600f48, %eax         # imm = 0x600F48
  58b6fd:      	jmp	0x591a45 <.text+0x190a45>
  58b702:      	movl	$0x600f30, %eax         # imm = 0x600F30
  58b707:      	jmp	0x591a45 <.text+0x190a45>
  58b70c:      	movl	$0x600f1c, %eax         # imm = 0x600F1C
  58b711:      	jmp	0x591a45 <.text+0x190a45>
  58b716:      	movl	$0x600f00, %eax         # imm = 0x600F00
  58b71b:      	jmp	0x591a45 <.text+0x190a45>
  58b720:      	movl	$0x600eec, %eax         # imm = 0x600EEC
  58b725:      	jmp	0x591a45 <.text+0x190a45>
  58b72a:      	movl	$0x600edc, %eax         # imm = 0x600EDC
  58b72f:      	jmp	0x591a45 <.text+0x190a45>
  58b734:      	movl	$0x600ec8, %eax         # imm = 0x600EC8
  58b739:      	jmp	0x591a45 <.text+0x190a45>
  58b73e:      	movl	$0x600eac, %eax         # imm = 0x600EAC
  58b743:      	jmp	0x591a45 <.text+0x190a45>
  58b748:      	movl	$0x600e94, %eax         # imm = 0x600E94
  58b74d:      	jmp	0x591a45 <.text+0x190a45>
  58b752:      	movl	$0x600e7c, %eax         # imm = 0x600E7C
  58b757:      	jmp	0x591a45 <.text+0x190a45>
  58b75c:      	movl	$0x600e68, %eax         # imm = 0x600E68
  58b761:      	jmp	0x591a45 <.text+0x190a45>
  58b766:      	movl	$0x600e50, %eax         # imm = 0x600E50
  58b76b:      	jmp	0x591a45 <.text+0x190a45>
  58b770:      	movl	$0x600e3c, %eax         # imm = 0x600E3C
  58b775:      	jmp	0x591a45 <.text+0x190a45>
  58b77a:      	movl	$0x600e2c, %eax         # imm = 0x600E2C
  58b77f:      	jmp	0x591a45 <.text+0x190a45>
  58b784:      	movl	$0x600e1c, %eax         # imm = 0x600E1C
  58b789:      	jmp	0x591a45 <.text+0x190a45>
  58b78e:      	movl	$0x600e08, %eax         # imm = 0x600E08
  58b793:      	jmp	0x591a45 <.text+0x190a45>
  58b798:      	movl	$0x600df8, %eax         # imm = 0x600DF8
  58b79d:      	jmp	0x591a45 <.text+0x190a45>
  58b7a2:      	movl	$0x600de0, %eax         # imm = 0x600DE0
  58b7a7:      	jmp	0x591a45 <.text+0x190a45>
  58b7ac:      	movl	$0x600dc8, %eax         # imm = 0x600DC8
  58b7b1:      	jmp	0x591a45 <.text+0x190a45>
  58b7b6:      	movl	$0x600dac, %eax         # imm = 0x600DAC
  58b7bb:      	jmp	0x591a45 <.text+0x190a45>
  58b7c0:      	movl	$0x600d94, %eax         # imm = 0x600D94
  58b7c5:      	jmp	0x591a45 <.text+0x190a45>
  58b7ca:      	movl	$0x600d74, %eax         # imm = 0x600D74
  58b7cf:      	jmp	0x591a45 <.text+0x190a45>
  58b7d4:      	movl	$0x600d60, %eax         # imm = 0x600D60
  58b7d9:      	jmp	0x591a45 <.text+0x190a45>
  58b7de:      	movl	$0x600d4c, %eax         # imm = 0x600D4C
  58b7e3:      	jmp	0x591a45 <.text+0x190a45>
  58b7e8:      	movl	$0x600d38, %eax         # imm = 0x600D38
  58b7ed:      	jmp	0x591a45 <.text+0x190a45>
  58b7f2:      	movl	$0x600d1c, %eax         # imm = 0x600D1C
  58b7f7:      	jmp	0x591a45 <.text+0x190a45>
  58b7fc:      	movl	$0x600d08, %eax         # imm = 0x600D08
  58b801:      	jmp	0x591a45 <.text+0x190a45>
  58b806:      	movl	$0x600cf4, %eax         # imm = 0x600CF4
  58b80b:      	jmp	0x591a45 <.text+0x190a45>
  58b810:      	movl	$0x600cdc, %eax         # imm = 0x600CDC
  58b815:      	jmp	0x591a45 <.text+0x190a45>
  58b81a:      	movl	$0x600cc4, %eax         # imm = 0x600CC4
  58b81f:      	jmp	0x591a45 <.text+0x190a45>
  58b824:      	movl	$0x600ca8, %eax         # imm = 0x600CA8
  58b829:      	jmp	0x591a45 <.text+0x190a45>
  58b82e:      	movl	$0x600c90, %eax         # imm = 0x600C90
  58b833:      	jmp	0x591a45 <.text+0x190a45>
  58b838:      	movl	$0x600c78, %eax         # imm = 0x600C78
  58b83d:      	jmp	0x591a45 <.text+0x190a45>
  58b842:      	movl	$0x600c60, %eax         # imm = 0x600C60
  58b847:      	jmp	0x591a45 <.text+0x190a45>
  58b84c:      	movl	$0x600c44, %eax         # imm = 0x600C44
  58b851:      	jmp	0x591a45 <.text+0x190a45>
  58b856:      	movl	$0x600c28, %eax         # imm = 0x600C28
  58b85b:      	jmp	0x591a45 <.text+0x190a45>
  58b860:      	movl	$0x600c04, %eax         # imm = 0x600C04
  58b865:      	jmp	0x591a45 <.text+0x190a45>
  58b86a:      	movl	$0x600bf0, %eax         # imm = 0x600BF0
  58b86f:      	jmp	0x591a45 <.text+0x190a45>
  58b874:      	movl	$0x600bd8, %eax         # imm = 0x600BD8
  58b879:      	jmp	0x591a45 <.text+0x190a45>
  58b87e:      	movl	$0x600bc0, %eax         # imm = 0x600BC0
  58b883:      	jmp	0x591a45 <.text+0x190a45>
  58b888:      	movl	$0x600ba8, %eax         # imm = 0x600BA8
  58b88d:      	jmp	0x591a45 <.text+0x190a45>
  58b892:      	movl	$0x600b8c, %eax         # imm = 0x600B8C
  58b897:      	jmp	0x591a45 <.text+0x190a45>
  58b89c:      	movl	$0x600b74, %eax         # imm = 0x600B74
  58b8a1:      	jmp	0x591a45 <.text+0x190a45>
  58b8a6:      	movl	$0x600b5c, %eax         # imm = 0x600B5C
  58b8ab:      	jmp	0x591a45 <.text+0x190a45>
  58b8b0:      	movl	$0x600b44, %eax         # imm = 0x600B44
  58b8b5:      	jmp	0x591a45 <.text+0x190a45>
  58b8ba:      	movl	$0x600b24, %eax         # imm = 0x600B24
  58b8bf:      	jmp	0x591a45 <.text+0x190a45>
  58b8c4:      	movl	$0x600b0c, %eax         # imm = 0x600B0C
  58b8c9:      	jmp	0x591a45 <.text+0x190a45>
  58b8ce:      	movl	$0x600af4, %eax         # imm = 0x600AF4
  58b8d3:      	jmp	0x591a45 <.text+0x190a45>
  58b8d8:      	movl	$0x600adc, %eax         # imm = 0x600ADC
  58b8dd:      	jmp	0x591a45 <.text+0x190a45>
  58b8e2:      	movl	$0x600ac8, %eax         # imm = 0x600AC8
  58b8e7:      	jmp	0x591a45 <.text+0x190a45>
  58b8ec:      	movl	$0x600ab4, %eax         # imm = 0x600AB4
  58b8f1:      	jmp	0x591a45 <.text+0x190a45>
  58b8f6:      	movl	$0x600aa0, %eax         # imm = 0x600AA0
  58b8fb:      	jmp	0x591a45 <.text+0x190a45>
  58b900:      	movl	$0x600a8c, %eax         # imm = 0x600A8C
  58b905:      	jmp	0x591a45 <.text+0x190a45>
  58b90a:      	movl	$0x600a78, %eax         # imm = 0x600A78
  58b90f:      	jmp	0x591a45 <.text+0x190a45>
  58b914:      	movl	$0x600a60, %eax         # imm = 0x600A60
  58b919:      	jmp	0x591a45 <.text+0x190a45>
  58b91e:      	movl	$0x600a44, %eax         # imm = 0x600A44
  58b923:      	jmp	0x591a45 <.text+0x190a45>
  58b928:      	movl	$0x600a2c, %eax         # imm = 0x600A2C
  58b92d:      	jmp	0x591a45 <.text+0x190a45>
  58b932:      	movl	$0x600a14, %eax         # imm = 0x600A14
  58b937:      	jmp	0x591a45 <.text+0x190a45>
  58b93c:      	movl	$0x6009fc, %eax         # imm = 0x6009FC
  58b941:      	jmp	0x591a45 <.text+0x190a45>
  58b946:      	movl	$0x6009e0, %eax         # imm = 0x6009E0
  58b94b:      	jmp	0x591a45 <.text+0x190a45>
  58b950:      	movl	$0x6009cc, %eax         # imm = 0x6009CC
  58b955:      	jmp	0x591a45 <.text+0x190a45>
  58b95a:      	movl	$0x887c0001, %ecx       # imm = 0x887C0001
  58b95f:      	cmpl	%ecx, %eax
  58b961:      	jg	0x58beb3 <.text+0x18aeb3>
  58b967:      	je	0x58bea9 <.text+0x18aea9>
  58b96d:      	movl	$0x88760b58, %ecx       # imm = 0x88760B58
  58b972:      	cmpl	%ecx, %eax
  58b974:      	jg	0x58bbe4 <.text+0x18abe4>
  58b97a:      	je	0x58bbda <.text+0x18abda>
  58b980:      	movl	$0x88760866, %ecx       # imm = 0x88760866
  58b985:      	cmpl	%ecx, %eax
  58b987:      	jg	0x58bac2 <.text+0x18aac2>
  58b98d:      	je	0x58bab8 <.text+0x18aab8>
  58b993:      	addl	$-0x4b, %ecx
  58b996:      	cmpl	%ecx, %eax
  58b998:      	jg	0x58ba53 <.text+0x18aa53>
  58b99e:      	je	0x58ba49 <.text+0x18aa49>
  58b9a4:      	movl	$0x88760394, %ecx       # imm = 0x88760394
  58b9a9:      	cmpl	%ecx, %eax
  58b9ab:      	jg	0x58ba01 <.text+0x18aa01>
  58b9ad:      	je	0x58b9f7 <.text+0x18a9f7>
  58b9af:      	cmpl	$0x88760390, %eax       # imm = 0x88760390
  58b9b4:      	je	0x58b9ed <.text+0x18a9ed>
  58b9b6:      	cmpl	$0x88760391, %eax       # imm = 0x88760391
  58b9bb:      	je	0x58b9e3 <.text+0x18a9e3>
  58b9bd:      	cmpl	$0x88760392, %eax       # imm = 0x88760392
  58b9c2:      	je	0x58b9d9 <.text+0x18a9d9>
  58b9c4:      	cmpl	$0x88760393, %eax       # imm = 0x88760393
  58b9c9:      	jne	0x591a16 <.text+0x190a16>
  58b9cf:      	movl	$0x6009b4, %eax         # imm = 0x6009B4
  58b9d4:      	jmp	0x591a45 <.text+0x190a45>
  58b9d9:      	movl	$0x600998, %eax         # imm = 0x600998
  58b9de:      	jmp	0x591a45 <.text+0x190a45>
  58b9e3:      	movl	$0x600980, %eax         # imm = 0x600980
  58b9e8:      	jmp	0x591a45 <.text+0x190a45>
  58b9ed:      	movl	$0x60096c, %eax         # imm = 0x60096C
  58b9f2:      	jmp	0x591a45 <.text+0x190a45>
  58b9f7:      	movl	$0x600958, %eax         # imm = 0x600958
  58b9fc:      	jmp	0x591a45 <.text+0x190a45>
  58ba01:      	cmpl	$0x88760395, %eax       # imm = 0x88760395
  58ba06:      	je	0x58ba3f <.text+0x18aa3f>
  58ba08:      	cmpl	$0x88760818, %eax       # imm = 0x88760818
  58ba0d:      	je	0x58ba35 <.text+0x18aa35>
  58ba0f:      	cmpl	$0x88760819, %eax       # imm = 0x88760819
  58ba14:      	je	0x58ba2b <.text+0x18aa2b>
  58ba16:      	cmpl	$0x8876081a, %eax       # imm = 0x8876081A
  58ba1b:      	jne	0x591a16 <.text+0x190a16>
  58ba21:      	movl	$0x60093c, %eax         # imm = 0x60093C
  58ba26:      	jmp	0x591a45 <.text+0x190a45>
  58ba2b:      	movl	$0x600918, %eax         # imm = 0x600918
  58ba30:      	jmp	0x591a45 <.text+0x190a45>
  58ba35:      	movl	$0x6008fc, %eax         # imm = 0x6008FC
  58ba3a:      	jmp	0x591a45 <.text+0x190a45>
  58ba3f:      	movl	$0x6008e4, %eax         # imm = 0x6008E4
  58ba44:      	jmp	0x591a45 <.text+0x190a45>
  58ba49:      	movl	$0x6008c0, %eax         # imm = 0x6008C0
  58ba4e:      	jmp	0x591a45 <.text+0x190a45>
  58ba53:      	addl	$0x7789f7e4, %eax       # imm = 0x7789F7E4
  58ba58:      	cmpl	$0xb, %eax
  58ba5b:      	ja	0x591a16 <.text+0x190a16>
  58ba61:      	jmpl	*0x595461(,%eax,4)
  58ba68:      	movl	$0x6008a4, %eax         # imm = 0x6008A4
  58ba6d:      	jmp	0x591a45 <.text+0x190a45>
  58ba72:      	movl	$0x600888, %eax         # imm = 0x600888
  58ba77:      	jmp	0x591a45 <.text+0x190a45>
  58ba7c:      	movl	$0x600868, %eax         # imm = 0x600868
  58ba81:      	jmp	0x591a45 <.text+0x190a45>
  58ba86:      	movl	$0x600848, %eax         # imm = 0x600848
  58ba8b:      	jmp	0x591a45 <.text+0x190a45>
  58ba90:      	movl	$0x600828, %eax         # imm = 0x600828
  58ba95:      	jmp	0x591a45 <.text+0x190a45>
  58ba9a:      	movl	$0x600808, %eax         # imm = 0x600808
  58ba9f:      	jmp	0x591a45 <.text+0x190a45>
  58baa4:      	movl	$0x6007e4, %eax         # imm = 0x6007E4
  58baa9:      	jmp	0x591a45 <.text+0x190a45>
  58baae:      	movl	$0x6007c8, %eax         # imm = 0x6007C8
  58bab3:      	jmp	0x591a45 <.text+0x190a45>
  58bab8:      	movl	$0x6007b8, %eax         # imm = 0x6007B8
  58babd:      	jmp	0x591a45 <.text+0x190a45>
  58bac2:      	movl	$0x8876087b, %ecx       # imm = 0x8876087B
  58bac7:      	cmpl	%ecx, %eax
  58bac9:      	jg	0x58bb46 <.text+0x18ab46>
  58bacb:      	je	0x58bb3c <.text+0x18ab3c>
  58bacd:      	addl	$0x7789f799, %eax       # imm = 0x7789F799
  58bad2:      	cmpl	$0xd, %eax
  58bad5:      	ja	0x591a16 <.text+0x190a16>
  58badb:      	jmpl	*0x595491(,%eax,4)
  58bae2:      	movl	$0x6007a8, %eax         # imm = 0x6007A8
  58bae7:      	jmp	0x591a45 <.text+0x190a45>
  58baec:      	movl	$0x600794, %eax         # imm = 0x600794
  58baf1:      	jmp	0x591a45 <.text+0x190a45>
  58baf6:      	movl	$0x60077c, %eax         # imm = 0x60077C
  58bafb:      	jmp	0x591a45 <.text+0x190a45>
  58bb00:      	movl	$0x600768, %eax         # imm = 0x600768
  58bb05:      	jmp	0x591a45 <.text+0x190a45>
  58bb0a:      	movl	$0x600750, %eax         # imm = 0x600750
  58bb0f:      	jmp	0x591a45 <.text+0x190a45>
  58bb14:      	movl	$0x60073c, %eax         # imm = 0x60073C
  58bb19:      	jmp	0x591a45 <.text+0x190a45>
  58bb1e:      	movl	$0x600720, %eax         # imm = 0x600720
  58bb23:      	jmp	0x591a45 <.text+0x190a45>
  58bb28:      	movl	$0x600708, %eax         # imm = 0x600708
  58bb2d:      	jmp	0x591a45 <.text+0x190a45>
  58bb32:      	movl	$0x6006f4, %eax         # imm = 0x6006F4
  58bb37:      	jmp	0x591a45 <.text+0x190a45>
  58bb3c:      	movl	$0x6006d8, %eax         # imm = 0x6006D8
  58bb41:      	jmp	0x591a45 <.text+0x190a45>
  58bb46:      	movl	$0x88760b54, %ecx       # imm = 0x88760B54
  58bb4b:      	cmpl	%ecx, %eax
  58bb4d:      	jg	0x58bba3 <.text+0x18aba3>
  58bb4f:      	je	0x58bb99 <.text+0x18ab99>
  58bb51:      	cmpl	$0x8876087c, %eax       # imm = 0x8876087C
  58bb56:      	je	0x58bb8f <.text+0x18ab8f>
  58bb58:      	cmpl	$0x8876087d, %eax       # imm = 0x8876087D
  58bb5d:      	je	0x58bb85 <.text+0x18ab85>
  58bb5f:      	cmpl	$0x8876087e, %eax       # imm = 0x8876087E
  58bb64:      	je	0x58bb7b <.text+0x18ab7b>
  58bb66:      	cmpl	$0x88760884, %eax       # imm = 0x88760884
  58bb6b:      	jne	0x591a16 <.text+0x190a16>
  58bb71:      	movl	$0x6006b4, %eax         # imm = 0x6006B4
  58bb76:      	jmp	0x591a45 <.text+0x190a45>
  58bb7b:      	movl	$0x600698, %eax         # imm = 0x600698
  58bb80:      	jmp	0x591a45 <.text+0x190a45>
  58bb85:      	movl	$0x60067c, %eax         # imm = 0x60067C
  58bb8a:      	jmp	0x591a45 <.text+0x190a45>
  58bb8f:      	movl	$0x60065c, %eax         # imm = 0x60065C
  58bb94:      	jmp	0x591a45 <.text+0x190a45>
  58bb99:      	movl	$0x60063c, %eax         # imm = 0x60063C
  58bb9e:      	jmp	0x591a45 <.text+0x190a45>
  58bba3:      	cmpl	$0x88760b55, %eax       # imm = 0x88760B55
  58bba8:      	je	0x58bbd0 <.text+0x18abd0>
  58bbaa:      	cmpl	$0x88760b56, %eax       # imm = 0x88760B56
  58bbaf:      	je	0x58bbc6 <.text+0x18abc6>
  58bbb1:      	cmpl	$0x88760b57, %eax       # imm = 0x88760B57
  58bbb6:      	jne	0x591a16 <.text+0x190a16>
  58bbbc:      	movl	$0x60061c, %eax         # imm = 0x60061C
  58bbc1:      	jmp	0x591a45 <.text+0x190a45>
  58bbc6:      	movl	$0x600604, %eax         # imm = 0x600604
  58bbcb:      	jmp	0x591a45 <.text+0x190a45>
  58bbd0:      	movl	$0x6005f0, %eax         # imm = 0x6005F0
  58bbd5:      	jmp	0x591a45 <.text+0x190a45>
  58bbda:      	movl	$0x6005d4, %eax         # imm = 0x6005D4
  58bbdf:      	jmp	0x591a45 <.text+0x190a45>
  58bbe4:      	movl	$0x887800dc, %ecx       # imm = 0x887800DC
  58bbe9:      	cmpl	%ecx, %eax
  58bbeb:      	jg	0x58bd55 <.text+0x18ad55>
  58bbf1:      	je	0x58bd4b <.text+0x18ad4b>
  58bbf7:      	addl	$-0x64, %ecx
  58bbfa:      	cmpl	%ecx, %eax
  58bbfc:      	jg	0x58bcb7 <.text+0x18acb7>
  58bc02:      	je	0x58bcad <.text+0x18acad>
  58bc08:      	movl	$0x8878000a, %ecx       # imm = 0x8878000A
  58bc0d:      	cmpl	%ecx, %eax
  58bc0f:      	jg	0x58bc65 <.text+0x18ac65>
  58bc11:      	je	0x58bc5b <.text+0x18ac5b>
  58bc13:      	cmpl	$0x88760b59, %eax       # imm = 0x88760B59
  58bc18:      	je	0x58bc51 <.text+0x18ac51>
  58bc1a:      	cmpl	$0x88760b5a, %eax       # imm = 0x88760B5A
  58bc1f:      	je	0x58bc47 <.text+0x18ac47>
  58bc21:      	cmpl	$0x88760b5b, %eax       # imm = 0x88760B5B
  58bc26:      	je	0x58bc3d <.text+0x18ac3d>
  58bc28:      	cmpl	$0x88760b5c, %eax       # imm = 0x88760B5C
  58bc2d:      	jne	0x591a16 <.text+0x190a16>
  58bc33:      	movl	$0x6005b4, %eax         # imm = 0x6005B4
  58bc38:      	jmp	0x591a45 <.text+0x190a45>
  58bc3d:      	movl	$0x600594, %eax         # imm = 0x600594
  58bc42:      	jmp	0x591a45 <.text+0x190a45>
  58bc47:      	movl	$0x600578, %eax         # imm = 0x600578
  58bc4c:      	jmp	0x591a45 <.text+0x190a45>
  58bc51:      	movl	$0x600564, %eax         # imm = 0x600564
  58bc56:      	jmp	0x591a45 <.text+0x190a45>
  58bc5b:      	movl	$0x600554, %eax         # imm = 0x600554
  58bc60:      	jmp	0x591a45 <.text+0x190a45>
  58bc65:      	cmpl	$0x8878001e, %eax       # imm = 0x8878001E
  58bc6a:      	je	0x58bca3 <.text+0x18aca3>
  58bc6c:      	cmpl	$0x88780032, %eax       # imm = 0x88780032
  58bc71:      	je	0x58bc99 <.text+0x18ac99>
  58bc73:      	cmpl	$0x88780046, %eax       # imm = 0x88780046
  58bc78:      	je	0x58bc8f <.text+0x18ac8f>
  58bc7a:      	cmpl	$0x88780064, %eax       # imm = 0x88780064
  58bc7f:      	jne	0x591a16 <.text+0x190a16>
  58bc85:      	movl	$0x600544, %eax         # imm = 0x600544
  58bc8a:      	jmp	0x591a45 <.text+0x190a45>
  58bc8f:      	movl	$0x60052c, %eax         # imm = 0x60052C
  58bc94:      	jmp	0x591a45 <.text+0x190a45>
  58bc99:      	movl	$0x600518, %eax         # imm = 0x600518
  58bc9e:      	jmp	0x591a45 <.text+0x190a45>
  58bca3:      	movl	$0x600500, %eax         # imm = 0x600500
  58bca8:      	jmp	0x591a45 <.text+0x190a45>
  58bcad:      	movl	$0x6004f0, %eax         # imm = 0x6004F0
  58bcb2:      	jmp	0x591a45 <.text+0x190a45>
  58bcb7:      	movl	$0x887800b4, %ecx       # imm = 0x887800B4
  58bcbc:      	cmpl	%ecx, %eax
  58bcbe:      	jg	0x58bd14 <.text+0x18ad14>
  58bcc0:      	je	0x58bd0a <.text+0x18ad0a>
  58bcc2:      	cmpl	$0x88780082, %eax       # imm = 0x88780082
  58bcc7:      	je	0x58bd00 <.text+0x18ad00>
  58bcc9:      	cmpl	$0x88780096, %eax       # imm = 0x88780096
  58bcce:      	je	0x58bcf6 <.text+0x18acf6>
  58bcd0:      	cmpl	$0x887800a0, %eax       # imm = 0x887800A0
  58bcd5:      	je	0x58bcec <.text+0x18acec>
  58bcd7:      	cmpl	$0x887800aa, %eax       # imm = 0x887800AA
  58bcdc:      	jne	0x591a16 <.text+0x190a16>
  58bce2:      	movl	$0x6004dc, %eax         # imm = 0x6004DC
  58bce7:      	jmp	0x591a45 <.text+0x190a45>
  58bcec:      	movl	$0x6004c4, %eax         # imm = 0x6004C4
  58bcf1:      	jmp	0x591a45 <.text+0x190a45>
  58bcf6:      	movl	$0x6004b0, %eax         # imm = 0x6004B0
  58bcfb:      	jmp	0x591a45 <.text+0x190a45>
  58bd00:      	movl	$0x600494, %eax         # imm = 0x600494
  58bd05:      	jmp	0x591a45 <.text+0x190a45>
  58bd0a:      	movl	$0x60047c, %eax         # imm = 0x60047C
  58bd0f:      	jmp	0x591a45 <.text+0x190a45>
  58bd14:      	cmpl	$0x887800be, %eax       # imm = 0x887800BE
  58bd19:      	je	0x58bd41 <.text+0x18ad41>
  58bd1b:      	cmpl	$0x887800c8, %eax       # imm = 0x887800C8
  58bd20:      	je	0x58bd37 <.text+0x18ad37>
  58bd22:      	cmpl	$0x887800d2, %eax       # imm = 0x887800D2
  58bd27:      	jne	0x591a16 <.text+0x190a16>
  58bd2d:      	movl	$0x600464, %eax         # imm = 0x600464
  58bd32:      	jmp	0x591a45 <.text+0x190a45>
  58bd37:      	movl	$0x600454, %eax         # imm = 0x600454
  58bd3c:      	jmp	0x591a45 <.text+0x190a45>
  58bd41:      	movl	$0x600440, %eax         # imm = 0x600440
  58bd46:      	jmp	0x591a45 <.text+0x190a45>
  58bd4b:      	movl	$0x60042c, %eax         # imm = 0x60042C
  58bd50:      	jmp	0x591a45 <.text+0x190a45>
  58bd55:      	movl	$0x887a0007, %ecx       # imm = 0x887A0007
  58bd5a:      	cmpl	%ecx, %eax
  58bd5c:      	jg	0x58be15 <.text+0x18ae15>
  58bd62:      	je	0x58be0b <.text+0x18ae0b>
  58bd68:      	addl	$-0x5, %ecx
  58bd6b:      	cmpl	%ecx, %eax
  58bd6d:      	jg	0x58bdc3 <.text+0x18adc3>
  58bd6f:      	je	0x58bdb9 <.text+0x18adb9>
  58bd71:      	cmpl	$0x88781161, %eax       # imm = 0x88781161
  58bd76:      	je	0x58bdaf <.text+0x18adaf>
  58bd78:      	cmpl	$0x88790001, %eax       # imm = 0x88790001
  58bd7d:      	je	0x58bda5 <.text+0x18ada5>
  58bd7f:      	cmpl	$0x88790002, %eax       # imm = 0x88790002
  58bd84:      	je	0x58bd9b <.text+0x18ad9b>
  58bd86:      	cmpl	$0x887a0001, %eax       # imm = 0x887A0001
  58bd8b:      	jne	0x591a16 <.text+0x190a16>
  58bd91:      	movl	$0x600414, %eax         # imm = 0x600414
  58bd96:      	jmp	0x591a45 <.text+0x190a45>
  58bd9b:      	movl	$0x6003f8, %eax         # imm = 0x6003F8
  58bda0:      	jmp	0x591a45 <.text+0x190a45>
  58bda5:      	movl	$0x6003cc, %eax         # imm = 0x6003CC
  58bdaa:      	jmp	0x591a45 <.text+0x190a45>
  58bdaf:      	movl	$0x6003b4, %eax         # imm = 0x6003B4
  58bdb4:      	jmp	0x591a45 <.text+0x190a45>
  58bdb9:      	movl	$0x60039c, %eax         # imm = 0x60039C
  58bdbe:      	jmp	0x591a45 <.text+0x190a45>
  58bdc3:      	cmpl	$0x887a0003, %eax       # imm = 0x887A0003
  58bdc8:      	je	0x58be01 <.text+0x18ae01>
  58bdca:      	cmpl	$0x887a0004, %eax       # imm = 0x887A0004
  58bdcf:      	je	0x58bdf7 <.text+0x18adf7>
  58bdd1:      	cmpl	$0x887a0005, %eax       # imm = 0x887A0005
  58bdd6:      	je	0x58bded <.text+0x18aded>
  58bdd8:      	cmpl	$0x887a0006, %eax       # imm = 0x887A0006
  58bddd:      	jne	0x591a16 <.text+0x190a16>
  58bde3:      	movl	$0x600384, %eax         # imm = 0x600384
  58bde8:      	jmp	0x591a45 <.text+0x190a45>
  58bded:      	movl	$0x600368, %eax         # imm = 0x600368
  58bdf2:      	jmp	0x591a45 <.text+0x190a45>
  58bdf7:      	movl	$0x600350, %eax         # imm = 0x600350
  58bdfc:      	jmp	0x591a45 <.text+0x190a45>
  58be01:      	movl	$0x600338, %eax         # imm = 0x600338
  58be06:      	jmp	0x591a45 <.text+0x190a45>
  58be0b:      	movl	$0x600320, %eax         # imm = 0x600320
  58be10:      	jmp	0x591a45 <.text+0x190a45>
  58be15:      	movl	$0x887a0021, %ecx       # imm = 0x887A0021
  58be1a:      	cmpl	%ecx, %eax
  58be1c:      	jg	0x58be72 <.text+0x18ae72>
  58be1e:      	je	0x58be68 <.text+0x18ae68>
  58be20:      	cmpl	$0x887a000a, %eax       # imm = 0x887A000A
  58be25:      	je	0x58be5e <.text+0x18ae5e>
  58be27:      	cmpl	$0x887a000b, %eax       # imm = 0x887A000B
  58be2c:      	je	0x58be54 <.text+0x18ae54>
  58be2e:      	cmpl	$0x887a000c, %eax       # imm = 0x887A000C
  58be33:      	je	0x58be4a <.text+0x18ae4a>
  58be35:      	cmpl	$0x887a0020, %eax       # imm = 0x887A0020
  58be3a:      	jne	0x591a16 <.text+0x190a16>
  58be40:      	movl	$0x6002fc, %eax         # imm = 0x6002FC
  58be45:      	jmp	0x591a45 <.text+0x190a45>
  58be4a:      	movl	$0x6002d4, %eax         # imm = 0x6002D4
  58be4f:      	jmp	0x591a45 <.text+0x190a45>
  58be54:      	movl	$0x6002ac, %eax         # imm = 0x6002AC
  58be59:      	jmp	0x591a45 <.text+0x190a45>
  58be5e:      	movl	$0x60028c, %eax         # imm = 0x60028C
  58be63:      	jmp	0x591a45 <.text+0x190a45>
  58be68:      	movl	$0x600274, %eax         # imm = 0x600274
  58be6d:      	jmp	0x591a45 <.text+0x190a45>
  58be72:      	cmpl	$0x887a0022, %eax       # imm = 0x887A0022
  58be77:      	je	0x58be9f <.text+0x18ae9f>
  58be79:      	cmpl	$0x887a0023, %eax       # imm = 0x887A0023
  58be7e:      	je	0x58be95 <.text+0x18ae95>
  58be80:      	cmpl	$0x887a0024, %eax       # imm = 0x887A0024
  58be85:      	jne	0x591a16 <.text+0x190a16>
  58be8b:      	movl	$0x600254, %eax         # imm = 0x600254
  58be90:      	jmp	0x591a45 <.text+0x190a45>
  58be95:      	movl	$0x60022c, %eax         # imm = 0x60022C
  58be9a:      	jmp	0x591a45 <.text+0x190a45>
  58be9f:      	movl	$0x600208, %eax         # imm = 0x600208
  58bea4:      	jmp	0x591a45 <.text+0x190a45>
  58bea9:      	movl	$0x6001dc, %eax         # imm = 0x6001DC
  58beae:      	jmp	0x591a45 <.text+0x190a45>
  58beb3:      	movl	$0x88990017, %ecx       # imm = 0x88990017
  58beb8:      	cmpl	%ecx, %eax
  58beba:      	jg	0x58c10a <.text+0x18b10a>
  58bec0:      	je	0x58c100 <.text+0x18b100>
  58bec6:      	addl	$-0x14, %ecx
  58bec9:      	cmpl	%ecx, %eax
  58becb:      	jg	0x58c037 <.text+0x18b037>
  58bed1:      	je	0x58c02d <.text+0x18b02d>
  58bed7:      	movl	$0x88985000, %ecx       # imm = 0x88985000
  58bedc:      	cmpl	%ecx, %eax
  58bede:      	jg	0x58bf99 <.text+0x18af99>
  58bee4:      	je	0x58bf8f <.text+0x18af8f>
  58beea:      	movl	$0x88960002, %ecx       # imm = 0x88960002
  58beef:      	cmpl	%ecx, %eax
  58bef1:      	jg	0x58bf47 <.text+0x18af47>
  58bef3:      	je	0x58bf3d <.text+0x18af3d>
  58bef5:      	cmpl	$0x887c0002, %eax       # imm = 0x887C0002
  58befa:      	je	0x58bf33 <.text+0x18af33>
  58befc:      	cmpl	$0x887c0003, %eax       # imm = 0x887C0003
  58bf01:      	je	0x58bf29 <.text+0x18af29>
  58bf03:      	cmpl	$0x887c0004, %eax       # imm = 0x887C0004
  58bf08:      	je	0x58bf1f <.text+0x18af1f>
  58bf0a:      	cmpl	$0x88960001, %eax       # imm = 0x88960001
  58bf0f:      	jne	0x591a16 <.text+0x190a16>
  58bf15:      	movl	$0x6001c4, %eax         # imm = 0x6001C4
  58bf1a:      	jmp	0x591a45 <.text+0x190a45>
  58bf1f:      	movl	$0x600188, %eax         # imm = 0x600188
  58bf24:      	jmp	0x591a45 <.text+0x190a45>
  58bf29:      	movl	$0x60015c, %eax         # imm = 0x60015C
  58bf2e:      	jmp	0x591a45 <.text+0x190a45>
  58bf33:      	movl	$0x600140, %eax         # imm = 0x600140
  58bf38:      	jmp	0x591a45 <.text+0x190a45>
  58bf3d:      	movl	$0x600124, %eax         # imm = 0x600124
  58bf42:      	jmp	0x591a45 <.text+0x190a45>
  58bf47:      	cmpl	$0x88960003, %eax       # imm = 0x88960003
  58bf4c:      	je	0x58bf85 <.text+0x18af85>
  58bf4e:      	cmpl	$0x88960004, %eax       # imm = 0x88960004
  58bf53:      	je	0x58bf7b <.text+0x18af7b>
  58bf55:      	cmpl	$0x88970001, %eax       # imm = 0x88970001
  58bf5a:      	je	0x58bf71 <.text+0x18af71>
  58bf5c:      	cmpl	$0x88982f80, %eax       # imm = 0x88982F80
  58bf61:      	jne	0x591a16 <.text+0x190a16>
  58bf67:      	movl	$0x600104, %eax         # imm = 0x600104
  58bf6c:      	jmp	0x591a45 <.text+0x190a45>
  58bf71:      	movl	$0x6000e8, %eax         # imm = 0x6000E8
  58bf76:      	jmp	0x591a45 <.text+0x190a45>
  58bf7b:      	movl	$0x6000c8, %eax         # imm = 0x6000C8
  58bf80:      	jmp	0x591a45 <.text+0x190a45>
  58bf85:      	movl	$0x6000a8, %eax         # imm = 0x6000A8
  58bf8a:      	jmp	0x591a45 <.text+0x190a45>
  58bf8f:      	movl	$0x600094, %eax         # imm = 0x600094
  58bf94:      	jmp	0x591a45 <.text+0x190a45>
  58bf99:      	movl	$0x88985005, %ecx       # imm = 0x88985005
  58bf9e:      	cmpl	%ecx, %eax
  58bfa0:      	jg	0x58bff6 <.text+0x18aff6>
  58bfa2:      	je	0x58bfec <.text+0x18afec>
  58bfa4:      	cmpl	$0x88985001, %eax       # imm = 0x88985001
  58bfa9:      	je	0x58bfe2 <.text+0x18afe2>
  58bfab:      	cmpl	$0x88985002, %eax       # imm = 0x88985002
  58bfb0:      	je	0x58bfd8 <.text+0x18afd8>
  58bfb2:      	cmpl	$0x88985003, %eax       # imm = 0x88985003
  58bfb7:      	je	0x58bfce <.text+0x18afce>
  58bfb9:      	cmpl	$0x88985004, %eax       # imm = 0x88985004
  58bfbe:      	jne	0x591a16 <.text+0x190a16>
  58bfc4:      	movl	$0x600080, %eax         # imm = 0x600080
  58bfc9:      	jmp	0x591a45 <.text+0x190a45>
  58bfce:      	movl	$0x600068, %eax         # imm = 0x600068
  58bfd3:      	jmp	0x591a45 <.text+0x190a45>
  58bfd8:      	movl	$0x600058, %eax         # imm = 0x600058
  58bfdd:      	jmp	0x591a45 <.text+0x190a45>
  58bfe2:      	movl	$0x600044, %eax         # imm = 0x600044
  58bfe7:      	jmp	0x591a45 <.text+0x190a45>
  58bfec:      	movl	$0x600024, %eax         # imm = 0x600024
  58bff1:      	jmp	0x591a45 <.text+0x190a45>
  58bff6:      	cmpl	$0x88985006, %eax       # imm = 0x88985006
  58bffb:      	je	0x58c023 <.text+0x18b023>
  58bffd:      	cmpl	$0x88990001, %eax       # imm = 0x88990001
  58c002:      	je	0x58c019 <.text+0x18b019>
  58c004:      	cmpl	$0x88990002, %eax       # imm = 0x88990002
  58c009:      	jne	0x591a16 <.text+0x190a16>
  58c00f:      	movl	$0x60000c, %eax         # imm = 0x60000C
  58c014:      	jmp	0x591a45 <.text+0x190a45>
  58c019:      	movl	$0x5ffff8, %eax         # imm = 0x5FFFF8
  58c01e:      	jmp	0x591a45 <.text+0x190a45>
  58c023:      	movl	$0x5fffdc, %eax         # imm = 0x5FFFDC
  58c028:      	jmp	0x591a45 <.text+0x190a45>
  58c02d:      	movl	$0x5fffbc, %eax         # imm = 0x5FFFBC
  58c032:      	jmp	0x591a45 <.text+0x190a45>
  58c037:      	addl	$0x7766fffc, %eax       # imm = 0x7766FFFC
  58c03c:      	cmpl	$0x12, %eax
  58c03f:      	ja	0x591a16 <.text+0x190a16>
  58c045:      	jmpl	*0x5954c9(,%eax,4)
  58c04c:      	movl	$0x5fffa4, %eax         # imm = 0x5FFFA4
  58c051:      	jmp	0x591a45 <.text+0x190a45>
  58c056:      	movl	$0x5fff88, %eax         # imm = 0x5FFF88
  58c05b:      	jmp	0x591a45 <.text+0x190a45>
  58c060:      	movl	$0x5fff68, %eax         # imm = 0x5FFF68
  58c065:      	jmp	0x591a45 <.text+0x190a45>
  58c06a:      	movl	$0x5fff54, %eax         # imm = 0x5FFF54
  58c06f:      	jmp	0x591a45 <.text+0x190a45>
  58c074:      	movl	$0x5fff3c, %eax         # imm = 0x5FFF3C
  58c079:      	jmp	0x591a45 <.text+0x190a45>
  58c07e:      	movl	$0x5fff18, %eax         # imm = 0x5FFF18
  58c083:      	jmp	0x591a45 <.text+0x190a45>
  58c088:      	movl	$0x5fff04, %eax         # imm = 0x5FFF04
  58c08d:      	jmp	0x591a45 <.text+0x190a45>
  58c092:      	movl	$0x5ffee8, %eax         # imm = 0x5FFEE8
  58c097:      	jmp	0x591a45 <.text+0x190a45>
  58c09c:      	movl	$0x5ffed0, %eax         # imm = 0x5FFED0
  58c0a1:      	jmp	0x591a45 <.text+0x190a45>
  58c0a6:      	movl	$0x5ffeb0, %eax         # imm = 0x5FFEB0
  58c0ab:      	jmp	0x591a45 <.text+0x190a45>
  58c0b0:      	movl	$0x5ffe90, %eax         # imm = 0x5FFE90
  58c0b5:      	jmp	0x591a45 <.text+0x190a45>
  58c0ba:      	movl	$0x5ffe6c, %eax         # imm = 0x5FFE6C
  58c0bf:      	jmp	0x591a45 <.text+0x190a45>
  58c0c4:      	movl	$0x5ffe50, %eax         # imm = 0x5FFE50
  58c0c9:      	jmp	0x591a45 <.text+0x190a45>
  58c0ce:      	movl	$0x5ffe3c, %eax         # imm = 0x5FFE3C
  58c0d3:      	jmp	0x591a45 <.text+0x190a45>
  58c0d8:      	movl	$0x5ffe24, %eax         # imm = 0x5FFE24
  58c0dd:      	jmp	0x591a45 <.text+0x190a45>
  58c0e2:      	movl	$0x5ffe08, %eax         # imm = 0x5FFE08
  58c0e7:      	jmp	0x591a45 <.text+0x190a45>
  58c0ec:      	movl	$0x5ffde4, %eax         # imm = 0x5FFDE4
  58c0f1:      	jmp	0x591a45 <.text+0x190a45>
  58c0f6:      	movl	$0x5ffdc8, %eax         # imm = 0x5FFDC8
  58c0fb:      	jmp	0x591a45 <.text+0x190a45>
  58c100:      	movl	$0x5ffd9c, %eax         # imm = 0x5FFD9C
  58c105:      	jmp	0x591a45 <.text+0x190a45>
  58c10a:      	movl	$0x8ac7000e, %ecx       # imm = 0x8AC7000E
  58c10f:      	cmpl	%ecx, %eax
  58c111:      	jg	0x58c24c <.text+0x18b24c>
  58c117:      	je	0x58c242 <.text+0x18b242>
  58c11d:      	addl	$-0x9, %ecx
  58c120:      	cmpl	%ecx, %eax
  58c122:      	jg	0x58c1dd <.text+0x18b1dd>
  58c128:      	je	0x58c1d3 <.text+0x18b1d3>
  58c12e:      	movl	$0x8899001c, %ecx       # imm = 0x8899001C
  58c133:      	cmpl	%ecx, %eax
  58c135:      	jg	0x58c18b <.text+0x18b18b>
  58c137:      	je	0x58c181 <.text+0x18b181>
  58c139:      	cmpl	$0x88990018, %eax       # imm = 0x88990018
  58c13e:      	je	0x58c177 <.text+0x18b177>
  58c140:      	cmpl	$0x88990019, %eax       # imm = 0x88990019
  58c145:      	je	0x58c16d <.text+0x18b16d>
  58c147:      	cmpl	$0x8899001a, %eax       # imm = 0x8899001A
  58c14c:      	je	0x58c163 <.text+0x18b163>
  58c14e:      	cmpl	$0x8899001b, %eax       # imm = 0x8899001B
  58c153:      	jne	0x591a16 <.text+0x190a16>
  58c159:      	movl	$0x5ffd78, %eax         # imm = 0x5FFD78
  58c15e:      	jmp	0x591a45 <.text+0x190a45>
  58c163:      	movl	$0x5ffd54, %eax         # imm = 0x5FFD54
  58c168:      	jmp	0x591a45 <.text+0x190a45>
  58c16d:      	movl	$0x5ffd40, %eax         # imm = 0x5FFD40
  58c172:      	jmp	0x591a45 <.text+0x190a45>
  58c177:      	movl	$0x5ffd20, %eax         # imm = 0x5FFD20
  58c17c:      	jmp	0x591a45 <.text+0x190a45>
  58c181:      	movl	$0x5ffcfc, %eax         # imm = 0x5FFCFC
  58c186:      	jmp	0x591a45 <.text+0x190a45>
  58c18b:      	cmpl	$0x8ac70001, %eax       # imm = 0x8AC70001
  58c190:      	je	0x58c1c9 <.text+0x18b1c9>
  58c192:      	cmpl	$0x8ac70002, %eax       # imm = 0x8AC70002
  58c197:      	je	0x58c1bf <.text+0x18b1bf>
  58c199:      	cmpl	$0x8ac70003, %eax       # imm = 0x8AC70003
  58c19e:      	je	0x58c1b5 <.text+0x18b1b5>
  58c1a0:      	cmpl	$0x8ac70004, %eax       # imm = 0x8AC70004
  58c1a5:      	jne	0x591a16 <.text+0x190a16>
  58c1ab:      	movl	$0x5ffcd8, %eax         # imm = 0x5FFCD8
  58c1b0:      	jmp	0x591a45 <.text+0x190a45>
  58c1b5:      	movl	$0x5ffcc0, %eax         # imm = 0x5FFCC0
  58c1ba:      	jmp	0x591a45 <.text+0x190a45>
  58c1bf:      	movl	$0x5ffca4, %eax         # imm = 0x5FFCA4
  58c1c4:      	jmp	0x591a45 <.text+0x190a45>
  58c1c9:      	movl	$0x5ffc84, %eax         # imm = 0x5FFC84
  58c1ce:      	jmp	0x591a45 <.text+0x190a45>
  58c1d3:      	movl	$0x5ffc60, %eax         # imm = 0x5FFC60
  58c1d8:      	jmp	0x591a45 <.text+0x190a45>
  58c1dd:      	addl	$0x7538fffa, %eax       # imm = 0x7538FFFA
  58c1e2:      	cmpl	$0x7, %eax
  58c1e5:      	ja	0x591a16 <.text+0x190a16>
  58c1eb:      	jmpl	*0x595515(,%eax,4)
  58c1f2:      	movl	$0x5ffc44, %eax         # imm = 0x5FFC44
  58c1f7:      	jmp	0x591a45 <.text+0x190a45>
  58c1fc:      	movl	$0x5ffc28, %eax         # imm = 0x5FFC28
  58c201:      	jmp	0x591a45 <.text+0x190a45>
  58c206:      	movl	$0x5ffc00, %eax         # imm = 0x5FFC00
  58c20b:      	jmp	0x591a45 <.text+0x190a45>
  58c210:      	movl	$0x5ffbe0, %eax         # imm = 0x5FFBE0
  58c215:      	jmp	0x591a45 <.text+0x190a45>
  58c21a:      	movl	$0x5ffbbc, %eax         # imm = 0x5FFBBC
  58c21f:      	jmp	0x591a45 <.text+0x190a45>
  58c224:      	movl	$0x5ffb9c, %eax         # imm = 0x5FFB9C
  58c229:      	jmp	0x591a45 <.text+0x190a45>
  58c22e:      	movl	$0x5ffb7c, %eax         # imm = 0x5FFB7C
  58c233:      	jmp	0x591a45 <.text+0x190a45>
  58c238:      	movl	$0x5ffb5c, %eax         # imm = 0x5FFB5C
  58c23d:      	jmp	0x591a45 <.text+0x190a45>
  58c242:      	movl	$0x5ffb3c, %eax         # imm = 0x5FFB3C
  58c247:      	jmp	0x591a45 <.text+0x190a45>
  58c24c:      	movl	$0x8ac70101, %ecx       # imm = 0x8AC70101
  58c251:      	cmpl	%ecx, %eax
  58c253:      	jg	0x58c300 <.text+0x18b300>
  58c259:      	je	0x58c2f6 <.text+0x18b2f6>
  58c25f:      	addl	$0x7538fff1, %eax       # imm = 0x7538FFF1
  58c264:      	cmpl	$0xc, %eax
  58c267:      	ja	0x591a16 <.text+0x190a16>
  58c26d:      	jmpl	*0x595535(,%eax,4)
  58c274:      	movl	$0x5ffb14, %eax         # imm = 0x5FFB14
  58c279:      	jmp	0x591a45 <.text+0x190a45>
  58c27e:      	movl	$0x5ffafc, %eax         # imm = 0x5FFAFC
  58c283:      	jmp	0x591a45 <.text+0x190a45>
  58c288:      	movl	$0x5ffae0, %eax         # imm = 0x5FFAE0
  58c28d:      	jmp	0x591a45 <.text+0x190a45>
  58c292:      	movl	$0x5ffac8, %eax         # imm = 0x5FFAC8
  58c297:      	jmp	0x591a45 <.text+0x190a45>
  58c29c:      	movl	$0x5ffab0, %eax         # imm = 0x5FFAB0
  58c2a1:      	jmp	0x591a45 <.text+0x190a45>
  58c2a6:      	movl	$0x5ffa90, %eax         # imm = 0x5FFA90
  58c2ab:      	jmp	0x591a45 <.text+0x190a45>
  58c2b0:      	movl	$0x5ffa68, %eax         # imm = 0x5FFA68
  58c2b5:      	jmp	0x591a45 <.text+0x190a45>
  58c2ba:      	movl	$0x5ffa44, %eax         # imm = 0x5FFA44
  58c2bf:      	jmp	0x591a45 <.text+0x190a45>
  58c2c4:      	movl	$0x5ffa2c, %eax         # imm = 0x5FFA2C
  58c2c9:      	jmp	0x591a45 <.text+0x190a45>
  58c2ce:      	movl	$0x5ffa0c, %eax         # imm = 0x5FFA0C
  58c2d3:      	jmp	0x591a45 <.text+0x190a45>
  58c2d8:      	movl	$0x5ff9e8, %eax         # imm = 0x5FF9E8
  58c2dd:      	jmp	0x591a45 <.text+0x190a45>
  58c2e2:      	movl	$0x5ff9c4, %eax         # imm = 0x5FF9C4
  58c2e7:      	jmp	0x591a45 <.text+0x190a45>
  58c2ec:      	movl	$0x5ff9a4, %eax         # imm = 0x5FF9A4
  58c2f1:      	jmp	0x591a45 <.text+0x190a45>
  58c2f6:      	movl	$0x5ff984, %eax         # imm = 0x5FF984
  58c2fb:      	jmp	0x591a45 <.text+0x190a45>
  58c300:      	cmpl	$0x8ac70102, %eax       # imm = 0x8AC70102
  58c305:      	je	0x58c32d <.text+0x18b32d>
  58c307:      	cmpl	$0x8ac70103, %eax       # imm = 0x8AC70103
  58c30c:      	je	0x58c323 <.text+0x18b323>
  58c30e:      	cmpl	$0x8ac70104, %eax       # imm = 0x8AC70104
  58c313:      	jne	0x591a16 <.text+0x190a16>
  58c319:      	movl	$0x5ff960, %eax         # imm = 0x5FF960
  58c31e:      	jmp	0x591a45 <.text+0x190a45>
  58c323:      	movl	$0x5ff938, %eax         # imm = 0x5FF938
  58c328:      	jmp	0x591a45 <.text+0x190a45>
  58c32d:      	movl	$0x5ff914, %eax         # imm = 0x5FF914
  58c332:      	jmp	0x591a45 <.text+0x190a45>
  58c337:      	movl	$0x5ff8ec, %eax         # imm = 0x5FF8EC
  58c33c:      	jmp	0x591a45 <.text+0x190a45>
  58c341:      	movl	$0x47e, %ecx            # imm = 0x47E
  58c346:      	cmpl	%ecx, %eax
  58c348:      	jg	0x58d291 <.text+0x18c291>
  58c34e:      	je	0x58d287 <.text+0x18c287>
  58c354:      	movl	$0xa7, %ecx
  58c359:      	cmpl	%ecx, %eax
  58c35b:      	jg	0x58cafb <.text+0x18bafb>
  58c361:      	je	0x58caf1 <.text+0x18baf1>
  58c367:      	cmpl	$0x3f, %eax
  58c36a:      	jg	0x58c7be <.text+0x18b7be>
  58c370:      	je	0x58c7b4 <.text+0x18b7b4>
  58c376:      	cmpl	$0xb, %eax
  58c379:      	jg	0x58c61b <.text+0x18b61b>
  58c37f:      	je	0x58c611 <.text+0x18b611>
  58c385:      	movl	$0xc00ce017, %ecx       # imm = 0xC00CE017
  58c38a:      	cmpl	%ecx, %eax
  58c38c:      	jg	0x58c4e9 <.text+0x18b4e9>
  58c392:      	je	0x58c4df <.text+0x18b4df>
  58c398:      	addl	$-0x11, %ecx
  58c39b:      	cmpl	%ecx, %eax
  58c39d:      	jg	0x58c469 <.text+0x18b469>
  58c3a3:      	je	0x58c45f <.text+0x18b45f>
  58c3a9:      	movl	$0xc0090002, %ecx       # imm = 0xC0090002
  58c3ae:      	cmpl	%ecx, %eax
  58c3b0:      	jg	0x58c417 <.text+0x18b417>
  58c3b2:      	je	0x58c40d <.text+0x18b40d>
  58c3b4:      	cmpl	$0x8ac70106, %eax       # imm = 0x8AC70106
  58c3b9:      	je	0x58c403 <.text+0x18b403>
  58c3bb:      	cmpl	$0x8ac70107, %eax       # imm = 0x8AC70107
  58c3c0:      	je	0x58c3f9 <.text+0x18b3f9>
  58c3c2:      	cmpl	$0x8ac70108, %eax       # imm = 0x8AC70108
  58c3c7:      	je	0x58c3ef <.text+0x18b3ef>
  58c3c9:      	cmpl	$0x8ac70109, %eax       # imm = 0x8AC70109
  58c3ce:      	je	0x58c3e5 <.text+0x18b3e5>
  58c3d0:      	cmpl	$0xc0090001, %eax       # imm = 0xC0090001
  58c3d5:      	jne	0x591a16 <.text+0x190a16>
  58c3db:      	movl	$0x5ff8d4, %eax         # imm = 0x5FF8D4
  58c3e0:      	jmp	0x591a45 <.text+0x190a45>
  58c3e5:      	movl	$0x5ff8ac, %eax         # imm = 0x5FF8AC
  58c3ea:      	jmp	0x591a45 <.text+0x190a45>
  58c3ef:      	movl	$0x5ff880, %eax         # imm = 0x5FF880
  58c3f4:      	jmp	0x591a45 <.text+0x190a45>
  58c3f9:      	movl	$0x5ff85c, %eax         # imm = 0x5FF85C
  58c3fe:      	jmp	0x591a45 <.text+0x190a45>
  58c403:      	movl	$0x5ff834, %eax         # imm = 0x5FF834
  58c408:      	jmp	0x591a45 <.text+0x190a45>
  58c40d:      	movl	$0x5ff81c, %eax         # imm = 0x5FF81C
  58c412:      	jmp	0x591a45 <.text+0x190a45>
  58c417:      	cmpl	$0xc00ce002, %eax       # imm = 0xC00CE002
  58c41c:      	je	0x58c455 <.text+0x18b455>
  58c41e:      	cmpl	$0xc00ce003, %eax       # imm = 0xC00CE003
  58c423:      	je	0x58c44b <.text+0x18b44b>
  58c425:      	cmpl	$0xc00ce004, %eax       # imm = 0xC00CE004
  58c42a:      	je	0x58c441 <.text+0x18b441>
  58c42c:      	cmpl	$0xc00ce005, %eax       # imm = 0xC00CE005
  58c431:      	jne	0x591a16 <.text+0x190a16>
  58c437:      	movl	$0x5ff808, %eax         # imm = 0x5FF808
  58c43c:      	jmp	0x591a45 <.text+0x190a45>
  58c441:      	movl	$0x5ff7f0, %eax         # imm = 0x5FF7F0
  58c446:      	jmp	0x591a45 <.text+0x190a45>
  58c44b:      	movl	$0x5ff7d4, %eax         # imm = 0x5FF7D4
  58c450:      	jmp	0x591a45 <.text+0x190a45>
  58c455:      	movl	$0x5ff7bc, %eax         # imm = 0x5FF7BC
  58c45a:      	jmp	0x591a45 <.text+0x190a45>
  58c45f:      	movl	$0x5ff7a4, %eax         # imm = 0x5FF7A4
  58c464:      	jmp	0x591a45 <.text+0x190a45>
  58c469:      	addl	$0x3ff31ff9, %eax       # imm = 0x3FF31FF9
  58c46e:      	cmpl	$0xf, %eax
  58c471:      	ja	0x591a16 <.text+0x190a16>
  58c477:      	movzbl	0x595591(%eax), %eax
  58c47e:      	jmpl	*0x595569(,%eax,4)
  58c485:      	movl	$0x5ff790, %eax         # imm = 0x5FF790
  58c48a:      	jmp	0x591a45 <.text+0x190a45>
  58c48f:      	movl	$0x5ff778, %eax         # imm = 0x5FF778
  58c494:      	jmp	0x591a45 <.text+0x190a45>
  58c499:      	movl	$0x5ff75c, %eax         # imm = 0x5FF75C
  58c49e:      	jmp	0x591a45 <.text+0x190a45>
  58c4a3:      	movl	$0x5ff744, %eax         # imm = 0x5FF744
  58c4a8:      	jmp	0x591a45 <.text+0x190a45>
  58c4ad:      	movl	$0x5ff728, %eax         # imm = 0x5FF728
  58c4b2:      	jmp	0x591a45 <.text+0x190a45>
  58c4b7:      	movl	$0x5ff710, %eax         # imm = 0x5FF710
  58c4bc:      	jmp	0x591a45 <.text+0x190a45>
  58c4c1:      	movl	$0x5ff6fc, %eax         # imm = 0x5FF6FC
  58c4c6:      	jmp	0x591a45 <.text+0x190a45>
  58c4cb:      	movl	$0x5ff6e0, %eax         # imm = 0x5FF6E0
  58c4d0:      	jmp	0x591a45 <.text+0x190a45>
  58c4d5:      	movl	$0x5ff6cc, %eax         # imm = 0x5FF6CC
  58c4da:      	jmp	0x591a45 <.text+0x190a45>
  58c4df:      	movl	$0x5ff6b8, %eax         # imm = 0x5FF6B8
  58c4e4:      	jmp	0x591a45 <.text+0x190a45>
  58c4e9:      	cmpl	$0x1, %eax
  58c4ec:      	jg	0x58c5a4 <.text+0x18b5a4>
  58c4f2:      	je	0x58c59a <.text+0x18b59a>
  58c4f8:      	movl	$0xc00ce020, %ecx       # imm = 0xC00CE020
  58c4fd:      	cmpl	%ecx, %eax
  58c4ff:      	jg	0x58c555 <.text+0x18b555>
  58c501:      	je	0x58c54b <.text+0x18b54b>
  58c503:      	cmpl	$0xc00ce018, %eax       # imm = 0xC00CE018
  58c508:      	je	0x58c541 <.text+0x18b541>
  58c50a:      	cmpl	$0xc00ce019, %eax       # imm = 0xC00CE019
  58c50f:      	je	0x58c537 <.text+0x18b537>
  58c511:      	cmpl	$0xc00ce01c, %eax       # imm = 0xC00CE01C
  58c516:      	je	0x58c52d <.text+0x18b52d>
  58c518:      	cmpl	$0xc00ce01e, %eax       # imm = 0xC00CE01E
  58c51d:      	jne	0x591a16 <.text+0x190a16>
  58c523:      	movl	$0x5ff6a8, %eax         # imm = 0x5FF6A8
  58c528:      	jmp	0x591a45 <.text+0x190a45>
  58c52d:      	movl	$0x5ff690, %eax         # imm = 0x5FF690
  58c532:      	jmp	0x591a45 <.text+0x190a45>
  58c537:      	movl	$0x5ff678, %eax         # imm = 0x5FF678
  58c53c:      	jmp	0x591a45 <.text+0x190a45>
  58c541:      	movl	$0x5ff664, %eax         # imm = 0x5FF664
  58c546:      	jmp	0x591a45 <.text+0x190a45>
  58c54b:      	movl	$0x5ff644, %eax         # imm = 0x5FF644
  58c550:      	jmp	0x591a45 <.text+0x190a45>
  58c555:      	cmpl	$0xc00ce026, %eax       # imm = 0xC00CE026
  58c55a:      	je	0x58c590 <.text+0x18b590>
  58c55c:      	cmpl	$0xc00ce223, %eax       # imm = 0xC00CE223
  58c561:      	je	0x58c586 <.text+0x18b586>
  58c563:      	cmpl	$0xc00ce224, %eax       # imm = 0xC00CE224
  58c568:      	je	0x58c57c <.text+0x18b57c>
  58c56a:      	testl	%eax, %eax
  58c56c:      	jne	0x591a16 <.text+0x190a16>
  58c572:      	movl	$0x5ff63c, %eax         # imm = 0x5FF63C
  58c577:      	jmp	0x591a45 <.text+0x190a45>
  58c57c:      	movl	$0x5ff630, %eax         # imm = 0x5FF630
  58c581:      	jmp	0x591a45 <.text+0x190a45>
  58c586:      	movl	$0x5ff624, %eax         # imm = 0x5FF624
  58c58b:      	jmp	0x591a45 <.text+0x190a45>
  58c590:      	movl	$0x5ff610, %eax         # imm = 0x5FF610
  58c595:      	jmp	0x591a45 <.text+0x190a45>
  58c59a:      	movl	$0x5ff608, %eax         # imm = 0x5FF608
  58c59f:      	jmp	0x591a45 <.text+0x190a45>
  58c5a4:      	addl	$-0x2, %eax
  58c5a7:      	cmpl	$0x8, %eax
  58c5aa:      	ja	0x591a16 <.text+0x190a16>
  58c5b0:      	jmpl	*0x5955a1(,%eax,4)
  58c5b7:      	movl	$0x5ff5f0, %eax         # imm = 0x5FF5F0
  58c5bc:      	jmp	0x591a45 <.text+0x190a45>
  58c5c1:      	movl	$0x5ff5d8, %eax         # imm = 0x5FF5D8
  58c5c6:      	jmp	0x591a45 <.text+0x190a45>
  58c5cb:      	movl	$0x5ff5bc, %eax         # imm = 0x5FF5BC
  58c5d0:      	jmp	0x591a45 <.text+0x190a45>
  58c5d5:      	movl	$0x5ff5a8, %eax         # imm = 0x5FF5A8
  58c5da:      	jmp	0x591a45 <.text+0x190a45>
  58c5df:      	movl	$0x5ff590, %eax         # imm = 0x5FF590
  58c5e4:      	jmp	0x591a45 <.text+0x190a45>
  58c5e9:      	movl	$0x5ff57c, %eax         # imm = 0x5FF57C
  58c5ee:      	jmp	0x591a45 <.text+0x190a45>
  58c5f3:      	movl	$0x5ff564, %eax         # imm = 0x5FF564
  58c5f8:      	jmp	0x591a45 <.text+0x190a45>
  58c5fd:      	movl	$0x5ff550, %eax         # imm = 0x5FF550
  58c602:      	jmp	0x591a45 <.text+0x190a45>
  58c607:      	movl	$0x5ff538, %eax         # imm = 0x5FF538
  58c60c:      	jmp	0x591a45 <.text+0x190a45>
  58c611:      	movl	$0x5ff524, %eax         # imm = 0x5FF524
  58c616:      	jmp	0x591a45 <.text+0x190a45>
  58c61b:      	addl	$-0xc, %eax
  58c61e:      	cmpl	$0x32, %eax
  58c621:      	ja	0x591a16 <.text+0x190a16>
  58c627:      	jmpl	*0x5955c5(,%eax,4)
  58c62e:      	movl	$0x5ff50c, %eax         # imm = 0x5FF50C
  58c633:      	jmp	0x591a45 <.text+0x190a45>
  58c638:      	movl	$0x5ff4f8, %eax         # imm = 0x5FF4F8
  58c63d:      	jmp	0x591a45 <.text+0x190a45>
  58c642:      	movl	$0x5ff4e4, %eax         # imm = 0x5FF4E4
  58c647:      	jmp	0x591a45 <.text+0x190a45>
  58c64c:      	movl	$0x5ff4d0, %eax         # imm = 0x5FF4D0
  58c651:      	jmp	0x591a45 <.text+0x190a45>
  58c656:      	movl	$0x5ff4b8, %eax         # imm = 0x5FF4B8
  58c65b:      	jmp	0x591a45 <.text+0x190a45>
  58c660:      	movl	$0x5ff4a0, %eax         # imm = 0x5FF4A0
  58c665:      	jmp	0x591a45 <.text+0x190a45>
  58c66a:      	movl	$0x5ff48c, %eax         # imm = 0x5FF48C
  58c66f:      	jmp	0x591a45 <.text+0x190a45>
  58c674:      	movl	$0x5ff478, %eax         # imm = 0x5FF478
  58c679:      	jmp	0x591a45 <.text+0x190a45>
  58c67e:      	movl	$0x5ff468, %eax         # imm = 0x5FF468
  58c683:      	jmp	0x591a45 <.text+0x190a45>
  58c688:      	movl	$0x5ff458, %eax         # imm = 0x5FF458
  58c68d:      	jmp	0x591a45 <.text+0x190a45>
  58c692:      	movl	$0x5ff444, %eax         # imm = 0x5FF444
  58c697:      	jmp	0x591a45 <.text+0x190a45>
  58c69c:      	movl	$0x5ff438, %eax         # imm = 0x5FF438
  58c6a1:      	jmp	0x591a45 <.text+0x190a45>
  58c6a6:      	movl	$0x5ff424, %eax         # imm = 0x5FF424
  58c6ab:      	jmp	0x591a45 <.text+0x190a45>
  58c6b0:      	movl	$0x5ff418, %eax         # imm = 0x5FF418
  58c6b5:      	jmp	0x591a45 <.text+0x190a45>
  58c6ba:      	movl	$0x5ff404, %eax         # imm = 0x5FF404
  58c6bf:      	jmp	0x591a45 <.text+0x190a45>
  58c6c4:      	movl	$0x5ff3ec, %eax         # imm = 0x5FF3EC
  58c6c9:      	jmp	0x591a45 <.text+0x190a45>
  58c6ce:      	movl	$0x5ff3d8, %eax         # imm = 0x5FF3D8
  58c6d3:      	jmp	0x591a45 <.text+0x190a45>
  58c6d8:      	movl	$0x5ff3c4, %eax         # imm = 0x5FF3C4
  58c6dd:      	jmp	0x591a45 <.text+0x190a45>
  58c6e2:      	movl	$0x5ff3b0, %eax         # imm = 0x5FF3B0
  58c6e7:      	jmp	0x591a45 <.text+0x190a45>
  58c6ec:      	movl	$0x5ff39c, %eax         # imm = 0x5FF39C
  58c6f1:      	jmp	0x591a45 <.text+0x190a45>
  58c6f6:      	movl	$0x5ff384, %eax         # imm = 0x5FF384
  58c6fb:      	jmp	0x591a45 <.text+0x190a45>
  58c700:      	movl	$0x5ff36c, %eax         # imm = 0x5FF36C
  58c705:      	jmp	0x591a45 <.text+0x190a45>
  58c70a:      	movl	$0x5ff358, %eax         # imm = 0x5FF358
  58c70f:      	jmp	0x591a45 <.text+0x190a45>
  58c714:      	movl	$0x5ff338, %eax         # imm = 0x5FF338
  58c719:      	jmp	0x591a45 <.text+0x190a45>
  58c71e:      	movl	$0x5ff324, %eax         # imm = 0x5FF324
  58c723:      	jmp	0x591a45 <.text+0x190a45>
  58c728:      	movl	$0x5ff30c, %eax         # imm = 0x5FF30C
  58c72d:      	jmp	0x591a45 <.text+0x190a45>
  58c732:      	movl	$0x5ff2f8, %eax         # imm = 0x5FF2F8
  58c737:      	jmp	0x591a45 <.text+0x190a45>
  58c73c:      	movl	$0x5ff2e4, %eax         # imm = 0x5FF2E4
  58c741:      	jmp	0x591a45 <.text+0x190a45>
  58c746:      	movl	$0x5ff2d4, %eax         # imm = 0x5FF2D4
  58c74b:      	jmp	0x591a45 <.text+0x190a45>
  58c750:      	movl	$0x5ff2c0, %eax         # imm = 0x5FF2C0
  58c755:      	jmp	0x591a45 <.text+0x190a45>
  58c75a:      	movl	$0x5ff2ac, %eax         # imm = 0x5FF2AC
  58c75f:      	jmp	0x591a45 <.text+0x190a45>
  58c764:      	movl	$0x5ff298, %eax         # imm = 0x5FF298
  58c769:      	jmp	0x591a45 <.text+0x190a45>
  58c76e:      	movl	$0x5ff284, %eax         # imm = 0x5FF284
  58c773:      	jmp	0x591a45 <.text+0x190a45>
  58c778:      	movl	$0x5ff270, %eax         # imm = 0x5FF270
  58c77d:      	jmp	0x591a45 <.text+0x190a45>
  58c782:      	movl	$0x5ff25c, %eax         # imm = 0x5FF25C
  58c787:      	jmp	0x591a45 <.text+0x190a45>
  58c78c:      	movl	$0x5ff248, %eax         # imm = 0x5FF248
  58c791:      	jmp	0x591a45 <.text+0x190a45>
  58c796:      	movl	$0x5ff234, %eax         # imm = 0x5FF234
  58c79b:      	jmp	0x591a45 <.text+0x190a45>
  58c7a0:      	movl	$0x5ff220, %eax         # imm = 0x5FF220
  58c7a5:      	jmp	0x591a45 <.text+0x190a45>
  58c7aa:      	movl	$0x5ff208, %eax         # imm = 0x5FF208
  58c7af:      	jmp	0x591a45 <.text+0x190a45>
  58c7b4:      	movl	$0x5ff1f0, %eax         # imm = 0x5FF1F0
  58c7b9:      	jmp	0x591a45 <.text+0x190a45>
  58c7be:      	addl	$-0x40, %eax
  58c7c1:      	cmpl	$0x64, %eax
  58c7c4:      	ja	0x591a16 <.text+0x190a16>
  58c7ca:      	jmpl	*0x595691(,%eax,4)
  58c7d1:      	movl	$0x5ff1d8, %eax         # imm = 0x5FF1D8
  58c7d6:      	jmp	0x591a45 <.text+0x190a45>
  58c7db:      	movl	$0x5ff1bc, %eax         # imm = 0x5FF1BC
  58c7e0:      	jmp	0x591a45 <.text+0x190a45>
  58c7e5:      	movl	$0x5ff1a8, %eax         # imm = 0x5FF1A8
  58c7ea:      	jmp	0x591a45 <.text+0x190a45>
  58c7ef:      	movl	$0x5ff194, %eax         # imm = 0x5FF194
  58c7f4:      	jmp	0x591a45 <.text+0x190a45>
  58c7f9:      	movl	$0x5ff17c, %eax         # imm = 0x5FF17C
  58c7fe:      	jmp	0x591a45 <.text+0x190a45>
  58c803:      	movl	$0x5ff168, %eax         # imm = 0x5FF168
  58c808:      	jmp	0x591a45 <.text+0x190a45>
  58c80d:      	movl	$0x5ff150, %eax         # imm = 0x5FF150
  58c812:      	jmp	0x591a45 <.text+0x190a45>
  58c817:      	movl	$0x5ff13c, %eax         # imm = 0x5FF13C
  58c81c:      	jmp	0x591a45 <.text+0x190a45>
  58c821:      	movl	$0x5ff128, %eax         # imm = 0x5FF128
  58c826:      	jmp	0x591a45 <.text+0x190a45>
  58c82b:      	movl	$0x5ff114, %eax         # imm = 0x5FF114
  58c830:      	jmp	0x591a45 <.text+0x190a45>
  58c835:      	movl	$0x5ff100, %eax         # imm = 0x5FF100
  58c83a:      	jmp	0x591a45 <.text+0x190a45>
  58c83f:      	movl	$0x5ff0f0, %eax         # imm = 0x5FF0F0
  58c844:      	jmp	0x591a45 <.text+0x190a45>
  58c849:      	movl	$0x5ff0d8, %eax         # imm = 0x5FF0D8
  58c84e:      	jmp	0x591a45 <.text+0x190a45>
  58c853:      	movl	$0x5ff0c0, %eax         # imm = 0x5FF0C0
  58c858:      	jmp	0x591a45 <.text+0x190a45>
  58c85d:      	movl	$0x5ff0a8, %eax         # imm = 0x5FF0A8
  58c862:      	jmp	0x591a45 <.text+0x190a45>
  58c867:      	movl	$0x5ff090, %eax         # imm = 0x5FF090
  58c86c:      	jmp	0x591a45 <.text+0x190a45>
  58c871:      	movl	$0x5ff078, %eax         # imm = 0x5FF078
  58c876:      	jmp	0x591a45 <.text+0x190a45>
  58c87b:      	movl	$0x5ff064, %eax         # imm = 0x5FF064
  58c880:      	jmp	0x591a45 <.text+0x190a45>
  58c885:      	movl	$0x5ff048, %eax         # imm = 0x5FF048
  58c88a:      	jmp	0x591a45 <.text+0x190a45>
  58c88f:      	movl	$0x5ff028, %eax         # imm = 0x5FF028
  58c894:      	jmp	0x591a45 <.text+0x190a45>
  58c899:      	movl	$0x5ff014, %eax         # imm = 0x5FF014
  58c89e:      	jmp	0x591a45 <.text+0x190a45>
  58c8a3:      	movl	$0x5feff8, %eax         # imm = 0x5FEFF8
  58c8a8:      	jmp	0x591a45 <.text+0x190a45>
  58c8ad:      	movl	$0x5fefd8, %eax         # imm = 0x5FEFD8
  58c8b2:      	jmp	0x591a45 <.text+0x190a45>
  58c8b7:      	movl	$0x5fefc0, %eax         # imm = 0x5FEFC0
  58c8bc:      	jmp	0x591a45 <.text+0x190a45>
  58c8c1:      	movl	$0x5fefa8, %eax         # imm = 0x5FEFA8
  58c8c6:      	jmp	0x591a45 <.text+0x190a45>
  58c8cb:      	movl	$0x5fef94, %eax         # imm = 0x5FEF94
  58c8d0:      	jmp	0x591a45 <.text+0x190a45>
  58c8d5:      	movl	$0x5fef80, %eax         # imm = 0x5FEF80
  58c8da:      	jmp	0x591a45 <.text+0x190a45>
  58c8df:      	movl	$0x5fef6c, %eax         # imm = 0x5FEF6C
  58c8e4:      	jmp	0x591a45 <.text+0x190a45>
  58c8e9:      	movl	$0x5fef58, %eax         # imm = 0x5FEF58
  58c8ee:      	jmp	0x591a45 <.text+0x190a45>
  58c8f3:      	movl	$0x5fef40, %eax         # imm = 0x5FEF40
  58c8f8:      	jmp	0x591a45 <.text+0x190a45>
  58c8fd:      	movl	$0x5fef30, %eax         # imm = 0x5FEF30
  58c902:      	jmp	0x591a45 <.text+0x190a45>
  58c907:      	movl	$0x5fef10, %eax         # imm = 0x5FEF10
  58c90c:      	jmp	0x591a45 <.text+0x190a45>
  58c911:      	movl	$0x5feef4, %eax         # imm = 0x5FEEF4
  58c916:      	jmp	0x591a45 <.text+0x190a45>
  58c91b:      	movl	$0x5feedc, %eax         # imm = 0x5FEEDC
  58c920:      	jmp	0x591a45 <.text+0x190a45>
  58c925:      	movl	$0x5feec0, %eax         # imm = 0x5FEEC0
  58c92a:      	jmp	0x591a45 <.text+0x190a45>
  58c92f:      	movl	$0x5feea8, %eax         # imm = 0x5FEEA8
  58c934:      	jmp	0x591a45 <.text+0x190a45>
  58c939:      	movl	$0x5fee8c, %eax         # imm = 0x5FEE8C
  58c93e:      	jmp	0x591a45 <.text+0x190a45>
  58c943:      	movl	$0x5fee78, %eax         # imm = 0x5FEE78
  58c948:      	jmp	0x591a45 <.text+0x190a45>
  58c94d:      	movl	$0x5fee5c, %eax         # imm = 0x5FEE5C
  58c952:      	jmp	0x591a45 <.text+0x190a45>
  58c957:      	movl	$0x5fee48, %eax         # imm = 0x5FEE48
  58c95c:      	jmp	0x591a45 <.text+0x190a45>
  58c961:      	movl	$0x5fee34, %eax         # imm = 0x5FEE34
  58c966:      	jmp	0x591a45 <.text+0x190a45>
  58c96b:      	movl	$0x5fee1c, %eax         # imm = 0x5FEE1C
  58c970:      	jmp	0x591a45 <.text+0x190a45>
  58c975:      	movl	$0x5fee08, %eax         # imm = 0x5FEE08
  58c97a:      	jmp	0x591a45 <.text+0x190a45>
  58c97f:      	movl	$0x5fedf0, %eax         # imm = 0x5FEDF0
  58c984:      	jmp	0x591a45 <.text+0x190a45>
  58c989:      	movl	$0x5fedd8, %eax         # imm = 0x5FEDD8
  58c98e:      	jmp	0x591a45 <.text+0x190a45>
  58c993:      	movl	$0x5fedbc, %eax         # imm = 0x5FEDBC
  58c998:      	jmp	0x591a45 <.text+0x190a45>
  58c99d:      	movl	$0x5feda0, %eax         # imm = 0x5FEDA0
  58c9a2:      	jmp	0x591a45 <.text+0x190a45>
  58c9a7:      	movl	$0x5fed8c, %eax         # imm = 0x5FED8C
  58c9ac:      	jmp	0x591a45 <.text+0x190a45>
  58c9b1:      	movl	$0x5fed74, %eax         # imm = 0x5FED74
  58c9b6:      	jmp	0x591a45 <.text+0x190a45>
  58c9bb:      	movl	$0x5fed5c, %eax         # imm = 0x5FED5C
  58c9c0:      	jmp	0x591a45 <.text+0x190a45>
  58c9c5:      	movl	$0x5fed4c, %eax         # imm = 0x5FED4C
  58c9ca:      	jmp	0x591a45 <.text+0x190a45>
  58c9cf:      	movl	$0x5fed38, %eax         # imm = 0x5FED38
  58c9d4:      	jmp	0x591a45 <.text+0x190a45>
  58c9d9:      	movl	$0x5fed24, %eax         # imm = 0x5FED24
  58c9de:      	jmp	0x591a45 <.text+0x190a45>
  58c9e3:      	movl	$0x5fed10, %eax         # imm = 0x5FED10
  58c9e8:      	jmp	0x591a45 <.text+0x190a45>
  58c9ed:      	movl	$0x5fecfc, %eax         # imm = 0x5FECFC
  58c9f2:      	jmp	0x591a45 <.text+0x190a45>
  58c9f7:      	movl	$0x5fece4, %eax         # imm = 0x5FECE4
  58c9fc:      	jmp	0x591a45 <.text+0x190a45>
  58ca01:      	movl	$0x5fecd0, %eax         # imm = 0x5FECD0
  58ca06:      	jmp	0x591a45 <.text+0x190a45>
  58ca0b:      	movl	$0x5fecbc, %eax         # imm = 0x5FECBC
  58ca10:      	jmp	0x591a45 <.text+0x190a45>
  58ca15:      	movl	$0x5feca8, %eax         # imm = 0x5FECA8
  58ca1a:      	jmp	0x591a45 <.text+0x190a45>
  58ca1f:      	movl	$0x5fec94, %eax         # imm = 0x5FEC94
  58ca24:      	jmp	0x591a45 <.text+0x190a45>
  58ca29:      	movl	$0x5fec80, %eax         # imm = 0x5FEC80
  58ca2e:      	jmp	0x591a45 <.text+0x190a45>
  58ca33:      	movl	$0x5fec6c, %eax         # imm = 0x5FEC6C
  58ca38:      	jmp	0x591a45 <.text+0x190a45>
  58ca3d:      	movl	$0x5fec58, %eax         # imm = 0x5FEC58
  58ca42:      	jmp	0x591a45 <.text+0x190a45>
  58ca47:      	movl	$0x5fec44, %eax         # imm = 0x5FEC44
  58ca4c:      	jmp	0x591a45 <.text+0x190a45>
  58ca51:      	movl	$0x5fec34, %eax         # imm = 0x5FEC34
  58ca56:      	jmp	0x591a45 <.text+0x190a45>
  58ca5b:      	movl	$0x5fec1c, %eax         # imm = 0x5FEC1C
  58ca60:      	jmp	0x591a45 <.text+0x190a45>
  58ca65:      	movl	$0x5fec08, %eax         # imm = 0x5FEC08
  58ca6a:      	jmp	0x591a45 <.text+0x190a45>
  58ca6f:      	movl	$0x5febec, %eax         # imm = 0x5FEBEC
  58ca74:      	jmp	0x591a45 <.text+0x190a45>
  58ca79:      	movl	$0x5febd0, %eax         # imm = 0x5FEBD0
  58ca7e:      	jmp	0x591a45 <.text+0x190a45>
  58ca83:      	movl	$0x5febb4, %eax         # imm = 0x5FEBB4
  58ca88:      	jmp	0x591a45 <.text+0x190a45>
  58ca8d:      	movl	$0x5feb9c, %eax         # imm = 0x5FEB9C
  58ca92:      	jmp	0x591a45 <.text+0x190a45>
  58ca97:      	movl	$0x5feb88, %eax         # imm = 0x5FEB88
  58ca9c:      	jmp	0x591a45 <.text+0x190a45>
  58caa1:      	movl	$0x5feb70, %eax         # imm = 0x5FEB70
  58caa6:      	jmp	0x591a45 <.text+0x190a45>
  58caab:      	movl	$0x5feb60, %eax         # imm = 0x5FEB60
  58cab0:      	jmp	0x591a45 <.text+0x190a45>
  58cab5:      	movl	$0x5feb4c, %eax         # imm = 0x5FEB4C
  58caba:      	jmp	0x591a45 <.text+0x190a45>
  58cabf:      	movl	$0x5feb34, %eax         # imm = 0x5FEB34
  58cac4:      	jmp	0x591a45 <.text+0x190a45>
  58cac9:      	movl	$0x5feb20, %eax         # imm = 0x5FEB20
  58cace:      	jmp	0x591a45 <.text+0x190a45>
  58cad3:      	movl	$0x5feb0c, %eax         # imm = 0x5FEB0C
  58cad8:      	jmp	0x591a45 <.text+0x190a45>
  58cadd:      	movl	$0x5feaf4, %eax         # imm = 0x5FEAF4
  58cae2:      	jmp	0x591a45 <.text+0x190a45>
  58cae7:      	movl	$0x5feadc, %eax         # imm = 0x5FEADC
  58caec:      	jmp	0x591a45 <.text+0x190a45>
  58caf1:      	movl	$0x5feac8, %eax         # imm = 0x5FEAC8
  58caf6:      	jmp	0x591a45 <.text+0x190a45>
  58cafb:      	movl	$0x3f4, %ecx            # imm = 0x3F4
  58cb00:      	cmpl	%ecx, %eax
  58cb02:      	jg	0x58cf49 <.text+0x18bf49>
  58cb08:      	je	0x58cf3f <.text+0x18bf3f>
  58cb0e:      	movl	$0xfe, %ecx
  58cb13:      	cmpl	%ecx, %eax
  58cb15:      	jg	0x58ccd7 <.text+0x18bcd7>
  58cb1b:      	je	0x58cccd <.text+0x18bccd>
  58cb21:      	addl	$0xffffff56, %eax       # imm = 0xFFFFFF56
  58cb26:      	cmpl	$0x46, %eax
  58cb29:      	ja	0x591a16 <.text+0x190a16>
  58cb2f:      	movzbl	0x5958c9(%eax), %eax
  58cb36:      	jmpl	*0x595825(,%eax,4)
  58cb3d:      	movl	$0x5feabc, %eax         # imm = 0x5FEABC
  58cb42:      	jmp	0x591a45 <.text+0x190a45>
  58cb47:      	movl	$0x5feaa4, %eax         # imm = 0x5FEAA4
  58cb4c:      	jmp	0x591a45 <.text+0x190a45>
  58cb51:      	movl	$0x5fea80, %eax         # imm = 0x5FEA80
  58cb56:      	jmp	0x591a45 <.text+0x190a45>
  58cb5b:      	movl	$0x5fea60, %eax         # imm = 0x5FEA60
  58cb60:      	jmp	0x591a45 <.text+0x190a45>
  58cb65:      	movl	$0x5fea48, %eax         # imm = 0x5FEA48
  58cb6a:      	jmp	0x591a45 <.text+0x190a45>
  58cb6f:      	movl	$0x5fea30, %eax         # imm = 0x5FEA30
  58cb74:      	jmp	0x591a45 <.text+0x190a45>
  58cb79:      	movl	$0x5fea14, %eax         # imm = 0x5FEA14
  58cb7e:      	jmp	0x591a45 <.text+0x190a45>
  58cb83:      	movl	$0x5fea00, %eax         # imm = 0x5FEA00
  58cb88:      	jmp	0x591a45 <.text+0x190a45>
  58cb8d:      	movl	$0x5fe9e0, %eax         # imm = 0x5FE9E0
  58cb92:      	jmp	0x591a45 <.text+0x190a45>
  58cb97:      	movl	$0x5fe9c8, %eax         # imm = 0x5FE9C8
  58cb9c:      	jmp	0x591a45 <.text+0x190a45>
  58cba1:      	movl	$0x5fe9ac, %eax         # imm = 0x5FE9AC
  58cba6:      	jmp	0x591a45 <.text+0x190a45>
  58cbab:      	movl	$0x5fe990, %eax         # imm = 0x5FE990
  58cbb0:      	jmp	0x591a45 <.text+0x190a45>
  58cbb5:      	movl	$0x5fe974, %eax         # imm = 0x5FE974
  58cbba:      	jmp	0x591a45 <.text+0x190a45>
  58cbbf:      	movl	$0x5fe95c, %eax         # imm = 0x5FE95C
  58cbc4:      	jmp	0x591a45 <.text+0x190a45>
  58cbc9:      	movl	$0x5fe93c, %eax         # imm = 0x5FE93C
  58cbce:      	jmp	0x591a45 <.text+0x190a45>
  58cbd3:      	movl	$0x5fe920, %eax         # imm = 0x5FE920
  58cbd8:      	jmp	0x591a45 <.text+0x190a45>
  58cbdd:      	movl	$0x5fe900, %eax         # imm = 0x5FE900
  58cbe2:      	jmp	0x591a45 <.text+0x190a45>
  58cbe7:      	movl	$0x5fe8e8, %eax         # imm = 0x5FE8E8
  58cbec:      	jmp	0x591a45 <.text+0x190a45>
  58cbf1:      	movl	$0x5fe8d0, %eax         # imm = 0x5FE8D0
  58cbf6:      	jmp	0x591a45 <.text+0x190a45>
  58cbfb:      	movl	$0x5fe8b0, %eax         # imm = 0x5FE8B0
  58cc00:      	jmp	0x591a45 <.text+0x190a45>
  58cc05:      	movl	$0x5fe890, %eax         # imm = 0x5FE890
  58cc0a:      	jmp	0x591a45 <.text+0x190a45>
  58cc0f:      	movl	$0x5fe870, %eax         # imm = 0x5FE870
  58cc14:      	jmp	0x591a45 <.text+0x190a45>
  58cc19:      	movl	$0x5fe850, %eax         # imm = 0x5FE850
  58cc1e:      	jmp	0x591a45 <.text+0x190a45>
  58cc23:      	movl	$0x5fe838, %eax         # imm = 0x5FE838
  58cc28:      	jmp	0x591a45 <.text+0x190a45>
  58cc2d:      	movl	$0x5fe820, %eax         # imm = 0x5FE820
  58cc32:      	jmp	0x591a45 <.text+0x190a45>
  58cc37:      	movl	$0x5fe804, %eax         # imm = 0x5FE804
  58cc3c:      	jmp	0x591a45 <.text+0x190a45>
  58cc41:      	movl	$0x5fe7e8, %eax         # imm = 0x5FE7E8
  58cc46:      	jmp	0x591a45 <.text+0x190a45>
  58cc4b:      	movl	$0x5fe7c8, %eax         # imm = 0x5FE7C8
  58cc50:      	jmp	0x591a45 <.text+0x190a45>
  58cc55:      	movl	$0x5fe7ac, %eax         # imm = 0x5FE7AC
  58cc5a:      	jmp	0x591a45 <.text+0x190a45>
  58cc5f:      	movl	$0x5fe794, %eax         # imm = 0x5FE794
  58cc64:      	jmp	0x591a45 <.text+0x190a45>
  58cc69:      	movl	$0x5fe784, %eax         # imm = 0x5FE784
  58cc6e:      	jmp	0x591a45 <.text+0x190a45>
  58cc73:      	movl	$0x5fe76c, %eax         # imm = 0x5FE76C
  58cc78:      	jmp	0x591a45 <.text+0x190a45>
  58cc7d:      	movl	$0x5fe750, %eax         # imm = 0x5FE750
  58cc82:      	jmp	0x591a45 <.text+0x190a45>
  58cc87:      	movl	$0x5fe730, %eax         # imm = 0x5FE730
  58cc8c:      	jmp	0x591a45 <.text+0x190a45>
  58cc91:      	movl	$0x5fe720, %eax         # imm = 0x5FE720
  58cc96:      	jmp	0x591a45 <.text+0x190a45>
  58cc9b:      	movl	$0x5fe710, %eax         # imm = 0x5FE710
  58cca0:      	jmp	0x591a45 <.text+0x190a45>
  58cca5:      	movl	$0x5fe700, %eax         # imm = 0x5FE700
  58ccaa:      	jmp	0x591a45 <.text+0x190a45>
  58ccaf:      	movl	$0x5fe6e4, %eax         # imm = 0x5FE6E4
  58ccb4:      	jmp	0x591a45 <.text+0x190a45>
  58ccb9:      	movl	$0x5fe6d4, %eax         # imm = 0x5FE6D4
  58ccbe:      	jmp	0x591a45 <.text+0x190a45>
  58ccc3:      	movl	$0x5fe6bc, %eax         # imm = 0x5FE6BC
  58ccc8:      	jmp	0x591a45 <.text+0x190a45>
  58cccd:      	movl	$0x5fe6a4, %eax         # imm = 0x5FE6A4
  58ccd2:      	jmp	0x591a45 <.text+0x190a45>
  58ccd7:      	movl	$0x216, %ecx            # imm = 0x216
  58ccdc:      	cmpl	%ecx, %eax
  58ccde:      	jg	0x58ce29 <.text+0x18be29>
  58cce4:      	je	0x58ce1f <.text+0x18be1f>
  58ccea:      	movl	$0x11a, %ecx            # imm = 0x11A
  58ccef:      	cmpl	%ecx, %eax
  58ccf1:      	jg	0x58cd90 <.text+0x18bd90>
  58ccf7:      	je	0x58cd86 <.text+0x18bd86>
  58ccfd:      	addl	$-0xf, %ecx
  58cd00:      	cmpl	%ecx, %eax
  58cd02:      	jg	0x58cd4a <.text+0x18bd4a>
  58cd04:      	je	0x588a7d <.text+0x187a7d>
  58cd0a:      	subl	$0xff, %eax
  58cd0f:      	je	0x58cd40 <.text+0x18bd40>
  58cd11:      	subl	$0x3, %eax
  58cd14:      	je	0x58cd36 <.text+0x18bd36>
  58cd16:      	decl	%eax
  58cd17:      	je	0x58cd2c <.text+0x18bd2c>
  58cd19:      	subl	$0x7, %eax
  58cd1c:      	jne	0x591a16 <.text+0x190a16>
  58cd22:      	movl	$0x5fe690, %eax         # imm = 0x5FE690
  58cd27:      	jmp	0x591a45 <.text+0x190a45>
  58cd2c:      	movl	$0x5fe67c, %eax         # imm = 0x5FE67C
  58cd31:      	jmp	0x591a45 <.text+0x190a45>
  58cd36:      	movl	$0x5fe66c, %eax         # imm = 0x5FE66C
  58cd3b:      	jmp	0x591a45 <.text+0x190a45>
  58cd40:      	movl	$0x5fe650, %eax         # imm = 0x5FE650
  58cd45:      	jmp	0x591a45 <.text+0x190a45>
  58cd4a:      	subl	$0x113, %eax            # imm = 0x113
  58cd4f:      	je	0x58cd7c <.text+0x18bd7c>
  58cd51:      	decl	%eax
  58cd52:      	je	0x58cd72 <.text+0x18bd72>
  58cd54:      	decl	%eax
  58cd55:      	je	0x58cd68 <.text+0x18bd68>
  58cd57:      	decl	%eax
  58cd58:      	jne	0x591a16 <.text+0x190a16>
  58cd5e:      	movl	$0x5fe638, %eax         # imm = 0x5FE638
  58cd63:      	jmp	0x591a45 <.text+0x190a45>
  58cd68:      	movl	$0x5fe624, %eax         # imm = 0x5FE624
  58cd6d:      	jmp	0x591a45 <.text+0x190a45>
  58cd72:      	movl	$0x5fe60c, %eax         # imm = 0x5FE60C
  58cd77:      	jmp	0x591a45 <.text+0x190a45>
  58cd7c:      	movl	$0x5fe5f8, %eax         # imm = 0x5FE5F8
  58cd81:      	jmp	0x591a45 <.text+0x190a45>
  58cd86:      	movl	$0x5fe5e0, %eax         # imm = 0x5FE5E0
  58cd8b:      	jmp	0x591a45 <.text+0x190a45>
  58cd90:      	movl	$0x12d, %ecx            # imm = 0x12D
  58cd95:      	cmpl	%ecx, %eax
  58cd97:      	jg	0x58cddd <.text+0x18bddd>
  58cd99:      	je	0x58cdd3 <.text+0x18bdd3>
  58cd9b:      	subl	$0x120, %eax            # imm = 0x120
  58cda0:      	je	0x58cdc9 <.text+0x18bdc9>
  58cda2:      	subl	$0xa, %eax
  58cda5:      	je	0x588ac9 <.text+0x187ac9>
  58cdab:      	decl	%eax
  58cdac:      	je	0x58cdbf <.text+0x18bdbf>
  58cdae:      	decl	%eax
  58cdaf:      	jne	0x591a16 <.text+0x190a16>
  58cdb5:      	movl	$0x5fe5c4, %eax         # imm = 0x5FE5C4
  58cdba:      	jmp	0x591a45 <.text+0x190a45>
  58cdbf:      	movl	$0x5fe5b0, %eax         # imm = 0x5FE5B0
  58cdc4:      	jmp	0x591a45 <.text+0x190a45>
  58cdc9:      	movl	$0x5fe5a0, %eax         # imm = 0x5FE5A0
  58cdce:      	jmp	0x591a45 <.text+0x190a45>
  58cdd3:      	movl	$0x5fe580, %eax         # imm = 0x5FE580
  58cdd8:      	jmp	0x591a45 <.text+0x190a45>
  58cddd:      	subl	$0x12e, %eax            # imm = 0x12E
  58cde2:      	je	0x58ce15 <.text+0x18be15>
  58cde4:      	decl	%eax
  58cde5:      	je	0x58ce0b <.text+0x18be0b>
  58cde7:      	subl	$0xe, %eax
  58cdea:      	je	0x58ce01 <.text+0x18be01>
  58cdec:      	subl	$0xaa, %eax
  58cdf1:      	jne	0x591a16 <.text+0x190a16>
  58cdf7:      	movl	$0x5fe568, %eax         # imm = 0x5FE568
  58cdfc:      	jmp	0x591a45 <.text+0x190a45>
  58ce01:      	movl	$0x5fe550, %eax         # imm = 0x5FE550
  58ce06:      	jmp	0x591a45 <.text+0x190a45>
  58ce0b:      	movl	$0x5fe538, %eax         # imm = 0x5FE538
  58ce10:      	jmp	0x591a45 <.text+0x190a45>
  58ce15:      	movl	$0x5fe51c, %eax         # imm = 0x5FE51C
  58ce1a:      	jmp	0x591a45 <.text+0x190a45>
  58ce1f:      	movl	$0x5fe500, %eax         # imm = 0x5FE500
  58ce24:      	jmp	0x591a45 <.text+0x190a45>
  58ce29:      	movl	$0x3ea, %ecx            # imm = 0x3EA
  58ce2e:      	cmpl	%ecx, %eax
  58ce30:      	jg	0x58ced0 <.text+0x18bed0>
  58ce36:      	je	0x58cec6 <.text+0x18bec6>
  58ce3c:      	addl	$-0x6, %ecx
  58ce3f:      	cmpl	%ecx, %eax
  58ce41:      	jg	0x58ce89 <.text+0x18be89>
  58ce43:      	je	0x588b60 <.text+0x187b60>
  58ce49:      	subl	$0x217, %eax            # imm = 0x217
  58ce4e:      	je	0x58ce7f <.text+0x18be7f>
  58ce50:      	decl	%eax
  58ce51:      	je	0x58ce75 <.text+0x18be75>
  58ce53:      	subl	$0x1ca, %eax            # imm = 0x1CA
  58ce58:      	je	0x58ce6b <.text+0x18be6b>
  58ce5a:      	decl	%eax
  58ce5b:      	jne	0x591a16 <.text+0x190a16>
  58ce61:      	movl	$0x5fe4e8, %eax         # imm = 0x5FE4E8
  58ce66:      	jmp	0x591a45 <.text+0x190a45>
  58ce6b:      	movl	$0x5fe4d0, %eax         # imm = 0x5FE4D0
  58ce70:      	jmp	0x591a45 <.text+0x190a45>
  58ce75:      	movl	$0x5fe4b8, %eax         # imm = 0x5FE4B8
  58ce7a:      	jmp	0x591a45 <.text+0x190a45>
  58ce7f:      	movl	$0x5fe4a0, %eax         # imm = 0x5FE4A0
  58ce84:      	jmp	0x591a45 <.text+0x190a45>
  58ce89:      	subl	$0x3e5, %eax            # imm = 0x3E5
  58ce8e:      	je	0x58cebc <.text+0x18bebc>
  58ce90:      	decl	%eax
  58ce91:      	je	0x58ceb2 <.text+0x18beb2>
  58ce93:      	decl	%eax
  58ce94:      	je	0x58cea8 <.text+0x18bea8>
  58ce96:      	decl	%eax
  58ce97:      	decl	%eax
  58ce98:      	jne	0x591a16 <.text+0x190a16>
  58ce9e:      	movl	$0x5fe488, %eax         # imm = 0x5FE488
  58cea3:      	jmp	0x591a45 <.text+0x190a45>
  58cea8:      	movl	$0x5fe478, %eax         # imm = 0x5FE478
  58cead:      	jmp	0x591a45 <.text+0x190a45>
  58ceb2:      	movl	$0x5fe468, %eax         # imm = 0x5FE468
  58ceb7:      	jmp	0x591a45 <.text+0x190a45>
  58cebc:      	movl	$0x5fe454, %eax         # imm = 0x5FE454
  58cec1:      	jmp	0x591a45 <.text+0x190a45>
  58cec6:      	movl	$0x5fe43c, %eax         # imm = 0x5FE43C
  58cecb:      	jmp	0x591a45 <.text+0x190a45>
  58ced0:      	addl	$0xfffffc15, %eax       # imm = 0xFFFFFC15
  58ced5:      	cmpl	$0x8, %eax
  58ced8:      	ja	0x591a16 <.text+0x190a16>
  58cede:      	jmpl	*0x595911(,%eax,4)
  58cee5:      	movl	$0x5fe424, %eax         # imm = 0x5FE424
  58ceea:      	jmp	0x591a45 <.text+0x190a45>
  58ceef:      	movl	$0x5fe410, %eax         # imm = 0x5FE410
  58cef4:      	jmp	0x591a45 <.text+0x190a45>
  58cef9:      	movl	$0x5fe3f4, %eax         # imm = 0x5FE3F4
  58cefe:      	jmp	0x591a45 <.text+0x190a45>
  58cf03:      	movl	$0x5fe3e0, %eax         # imm = 0x5FE3E0
  58cf08:      	jmp	0x591a45 <.text+0x190a45>
  58cf0d:      	movl	$0x5fe3c8, %eax         # imm = 0x5FE3C8
  58cf12:      	jmp	0x591a45 <.text+0x190a45>
  58cf17:      	movl	$0x5fe3b8, %eax         # imm = 0x5FE3B8
  58cf1c:      	jmp	0x591a45 <.text+0x190a45>
  58cf21:      	movl	$0x5fe3ac, %eax         # imm = 0x5FE3AC
  58cf26:      	jmp	0x591a45 <.text+0x190a45>
  58cf2b:      	movl	$0x5fe39c, %eax         # imm = 0x5FE39C
  58cf30:      	jmp	0x591a45 <.text+0x190a45>
  58cf35:      	movl	$0x5fe38c, %eax         # imm = 0x5FE38C
  58cf3a:      	jmp	0x591a45 <.text+0x190a45>
  58cf3f:      	movl	$0x5fe37c, %eax         # imm = 0x5FE37C
  58cf44:      	jmp	0x591a45 <.text+0x190a45>
  58cf49:      	addl	$0xfffffc0b, %eax       # imm = 0xFFFFFC0B
  58cf4e:      	cmpl	$0x81, %eax
  58cf53:      	ja	0x591a16 <.text+0x190a16>
  58cf59:      	movzbl	0x595a79(%eax), %eax
  58cf60:      	jmpl	*0x595935(,%eax,4)
  58cf67:      	movl	$0x5fe36c, %eax         # imm = 0x5FE36C
  58cf6c:      	jmp	0x591a45 <.text+0x190a45>
  58cf71:      	movl	$0x5fe350, %eax         # imm = 0x5FE350
  58cf76:      	jmp	0x591a45 <.text+0x190a45>
  58cf7b:      	movl	$0x5fe338, %eax         # imm = 0x5FE338
  58cf80:      	jmp	0x591a45 <.text+0x190a45>
  58cf85:      	movl	$0x5fe31c, %eax         # imm = 0x5FE31C
  58cf8a:      	jmp	0x591a45 <.text+0x190a45>
  58cf8f:      	movl	$0x5fe304, %eax         # imm = 0x5FE304
  58cf94:      	jmp	0x591a45 <.text+0x190a45>
  58cf99:      	movl	$0x5fe2f0, %eax         # imm = 0x5FE2F0
  58cf9e:      	jmp	0x591a45 <.text+0x190a45>
  58cfa3:      	movl	$0x5fe2dc, %eax         # imm = 0x5FE2DC
  58cfa8:      	jmp	0x591a45 <.text+0x190a45>
  58cfad:      	movl	$0x5fe2c4, %eax         # imm = 0x5FE2C4
  58cfb2:      	jmp	0x591a45 <.text+0x190a45>
  58cfb7:      	movl	$0x5fe2a4, %eax         # imm = 0x5FE2A4
  58cfbc:      	jmp	0x591a45 <.text+0x190a45>
  58cfc1:      	movl	$0x5fe28c, %eax         # imm = 0x5FE28C
  58cfc6:      	jmp	0x591a45 <.text+0x190a45>
  58cfcb:      	movl	$0x5fe268, %eax         # imm = 0x5FE268
  58cfd0:      	jmp	0x591a45 <.text+0x190a45>
  58cfd5:      	movl	$0x5fe248, %eax         # imm = 0x5FE248
  58cfda:      	jmp	0x591a45 <.text+0x190a45>
  58cfdf:      	movl	$0x5fe228, %eax         # imm = 0x5FE228
  58cfe4:      	jmp	0x591a45 <.text+0x190a45>
  58cfe9:      	movl	$0x5fe210, %eax         # imm = 0x5FE210
  58cfee:      	jmp	0x591a45 <.text+0x190a45>
  58cff3:      	movl	$0x5fe1f0, %eax         # imm = 0x5FE1F0
  58cff8:      	jmp	0x591a45 <.text+0x190a45>
  58cffd:      	movl	$0x5fe1d0, %eax         # imm = 0x5FE1D0
  58d002:      	jmp	0x591a45 <.text+0x190a45>
  58d007:      	movl	$0x5fe1b0, %eax         # imm = 0x5FE1B0
  58d00c:      	jmp	0x591a45 <.text+0x190a45>
  58d011:      	movl	$0x5fe198, %eax         # imm = 0x5FE198
  58d016:      	jmp	0x591a45 <.text+0x190a45>
  58d01b:      	movl	$0x5fe17c, %eax         # imm = 0x5FE17C
  58d020:      	jmp	0x591a45 <.text+0x190a45>
  58d025:      	movl	$0x5fe15c, %eax         # imm = 0x5FE15C
  58d02a:      	jmp	0x591a45 <.text+0x190a45>
  58d02f:      	movl	$0x5fe138, %eax         # imm = 0x5FE138
  58d034:      	jmp	0x591a45 <.text+0x190a45>
  58d039:      	movl	$0x5fe11c, %eax         # imm = 0x5FE11C
  58d03e:      	jmp	0x591a45 <.text+0x190a45>
  58d043:      	movl	$0x5fe0f4, %eax         # imm = 0x5FE0F4
  58d048:      	jmp	0x591a45 <.text+0x190a45>
  58d04d:      	movl	$0x5fe0d8, %eax         # imm = 0x5FE0D8
  58d052:      	jmp	0x591a45 <.text+0x190a45>
  58d057:      	movl	$0x5fe0b8, %eax         # imm = 0x5FE0B8
  58d05c:      	jmp	0x591a45 <.text+0x190a45>
  58d061:      	movl	$0x5fe098, %eax         # imm = 0x5FE098
  58d066:      	jmp	0x591a45 <.text+0x190a45>
  58d06b:      	movl	$0x5fe080, %eax         # imm = 0x5FE080
  58d070:      	jmp	0x591a45 <.text+0x190a45>
  58d075:      	movl	$0x5fe060, %eax         # imm = 0x5FE060
  58d07a:      	jmp	0x591a45 <.text+0x190a45>
  58d07f:      	movl	$0x5fe044, %eax         # imm = 0x5FE044
  58d084:      	jmp	0x591a45 <.text+0x190a45>
  58d089:      	movl	$0x5fe028, %eax         # imm = 0x5FE028
  58d08e:      	jmp	0x591a45 <.text+0x190a45>
  58d093:      	movl	$0x5fe00c, %eax         # imm = 0x5FE00C
  58d098:      	jmp	0x591a45 <.text+0x190a45>
  58d09d:      	movl	$0x5fdfec, %eax         # imm = 0x5FDFEC
  58d0a2:      	jmp	0x591a45 <.text+0x190a45>
  58d0a7:      	movl	$0x5fdfd4, %eax         # imm = 0x5FDFD4
  58d0ac:      	jmp	0x591a45 <.text+0x190a45>
  58d0b1:      	movl	$0x5fdfb8, %eax         # imm = 0x5FDFB8
  58d0b6:      	jmp	0x591a45 <.text+0x190a45>
  58d0bb:      	movl	$0x5fdf94, %eax         # imm = 0x5FDF94
  58d0c0:      	jmp	0x591a45 <.text+0x190a45>
  58d0c5:      	movl	$0x5fdf78, %eax         # imm = 0x5FDF78
  58d0ca:      	jmp	0x591a45 <.text+0x190a45>
  58d0cf:      	movl	$0x5fdf5c, %eax         # imm = 0x5FDF5C
  58d0d4:      	jmp	0x591a45 <.text+0x190a45>
  58d0d9:      	movl	$0x5fdf3c, %eax         # imm = 0x5FDF3C
  58d0de:      	jmp	0x591a45 <.text+0x190a45>
  58d0e3:      	movl	$0x5fdf1c, %eax         # imm = 0x5FDF1C
  58d0e8:      	jmp	0x591a45 <.text+0x190a45>
  58d0ed:      	movl	$0x5fdef8, %eax         # imm = 0x5FDEF8
  58d0f2:      	jmp	0x591a45 <.text+0x190a45>
  58d0f7:      	movl	$0x5fded4, %eax         # imm = 0x5FDED4
  58d0fc:      	jmp	0x591a45 <.text+0x190a45>
  58d101:      	movl	$0x5fdeb8, %eax         # imm = 0x5FDEB8
  58d106:      	jmp	0x591a45 <.text+0x190a45>
  58d10b:      	movl	$0x5fde9c, %eax         # imm = 0x5FDE9C
  58d110:      	jmp	0x591a45 <.text+0x190a45>
  58d115:      	movl	$0x5fde88, %eax         # imm = 0x5FDE88
  58d11a:      	jmp	0x591a45 <.text+0x190a45>
  58d11f:      	movl	$0x5fde70, %eax         # imm = 0x5FDE70
  58d124:      	jmp	0x591a45 <.text+0x190a45>
  58d129:      	movl	$0x5fde54, %eax         # imm = 0x5FDE54
  58d12e:      	jmp	0x591a45 <.text+0x190a45>
  58d133:      	movl	$0x5fde3c, %eax         # imm = 0x5FDE3C
  58d138:      	jmp	0x591a45 <.text+0x190a45>
  58d13d:      	movl	$0x5fde24, %eax         # imm = 0x5FDE24
  58d142:      	jmp	0x591a45 <.text+0x190a45>
  58d147:      	movl	$0x5fde0c, %eax         # imm = 0x5FDE0C
  58d14c:      	jmp	0x591a45 <.text+0x190a45>
  58d151:      	movl	$0x5fddf0, %eax         # imm = 0x5FDDF0
  58d156:      	jmp	0x591a45 <.text+0x190a45>
  58d15b:      	movl	$0x5fddd0, %eax         # imm = 0x5FDDD0
  58d160:      	jmp	0x591a45 <.text+0x190a45>
  58d165:      	movl	$0x5fddb4, %eax         # imm = 0x5FDDB4
  58d16a:      	jmp	0x591a45 <.text+0x190a45>
  58d16f:      	movl	$0x5fdd94, %eax         # imm = 0x5FDD94
  58d174:      	jmp	0x591a45 <.text+0x190a45>
  58d179:      	movl	$0x5fdd80, %eax         # imm = 0x5FDD80
  58d17e:      	jmp	0x591a45 <.text+0x190a45>
  58d183:      	movl	$0x5fdd70, %eax         # imm = 0x5FDD70
  58d188:      	jmp	0x591a45 <.text+0x190a45>
  58d18d:      	movl	$0x5fdd58, %eax         # imm = 0x5FDD58
  58d192:      	jmp	0x591a45 <.text+0x190a45>
  58d197:      	movl	$0x5fdd38, %eax         # imm = 0x5FDD38
  58d19c:      	jmp	0x591a45 <.text+0x190a45>
  58d1a1:      	movl	$0x5fdd20, %eax         # imm = 0x5FDD20
  58d1a6:      	jmp	0x591a45 <.text+0x190a45>
  58d1ab:      	movl	$0x5fdd04, %eax         # imm = 0x5FDD04
  58d1b0:      	jmp	0x591a45 <.text+0x190a45>
  58d1b5:      	movl	$0x5fdce4, %eax         # imm = 0x5FDCE4
  58d1ba:      	jmp	0x591a45 <.text+0x190a45>
  58d1bf:      	movl	$0x5fdcd4, %eax         # imm = 0x5FDCD4
  58d1c4:      	jmp	0x591a45 <.text+0x190a45>
  58d1c9:      	movl	$0x5fdcbc, %eax         # imm = 0x5FDCBC
  58d1ce:      	jmp	0x591a45 <.text+0x190a45>
  58d1d3:      	movl	$0x5fdcac, %eax         # imm = 0x5FDCAC
  58d1d8:      	jmp	0x591a45 <.text+0x190a45>
  58d1dd:      	movl	$0x5fdc98, %eax         # imm = 0x5FDC98
  58d1e2:      	jmp	0x591a45 <.text+0x190a45>
  58d1e7:      	movl	$0x5fdc80, %eax         # imm = 0x5FDC80
  58d1ec:      	jmp	0x591a45 <.text+0x190a45>
  58d1f1:      	movl	$0x5fdc60, %eax         # imm = 0x5FDC60
  58d1f6:      	jmp	0x591a45 <.text+0x190a45>
  58d1fb:      	movl	$0x5fdc44, %eax         # imm = 0x5FDC44
  58d200:      	jmp	0x591a45 <.text+0x190a45>
  58d205:      	movl	$0x5fdc28, %eax         # imm = 0x5FDC28
  58d20a:      	jmp	0x591a45 <.text+0x190a45>
  58d20f:      	movl	$0x5fdc0c, %eax         # imm = 0x5FDC0C
  58d214:      	jmp	0x591a45 <.text+0x190a45>
  58d219:      	movl	$0x5fdbec, %eax         # imm = 0x5FDBEC
  58d21e:      	jmp	0x591a45 <.text+0x190a45>
  58d223:      	movl	$0x5fdbd0, %eax         # imm = 0x5FDBD0
  58d228:      	jmp	0x591a45 <.text+0x190a45>
  58d22d:      	movl	$0x5fdbb8, %eax         # imm = 0x5FDBB8
  58d232:      	jmp	0x591a45 <.text+0x190a45>
  58d237:      	movl	$0x5fdba4, %eax         # imm = 0x5FDBA4
  58d23c:      	jmp	0x591a45 <.text+0x190a45>
  58d241:      	movl	$0x5fdb84, %eax         # imm = 0x5FDB84
  58d246:      	jmp	0x591a45 <.text+0x190a45>
  58d24b:      	movl	$0x5fdb6c, %eax         # imm = 0x5FDB6C
  58d250:      	jmp	0x591a45 <.text+0x190a45>
  58d255:      	movl	$0x5fdb54, %eax         # imm = 0x5FDB54
  58d25a:      	jmp	0x591a45 <.text+0x190a45>
  58d25f:      	movl	$0x5fdb34, %eax         # imm = 0x5FDB34
  58d264:      	jmp	0x591a45 <.text+0x190a45>
  58d269:      	movl	$0x5fdb14, %eax         # imm = 0x5FDB14
  58d26e:      	jmp	0x591a45 <.text+0x190a45>
  58d273:      	movl	$0x5fdafc, %eax         # imm = 0x5FDAFC
  58d278:      	jmp	0x591a45 <.text+0x190a45>
  58d27d:      	movl	$0x5fdae0, %eax         # imm = 0x5FDAE0
  58d282:      	jmp	0x591a45 <.text+0x190a45>
  58d287:      	movl	$0x5fdac8, %eax         # imm = 0x5FDAC8
  58d28c:      	jmp	0x591a45 <.text+0x190a45>
  58d291:      	addl	$0xfffffb81, %eax       # imm = 0xFFFFFB81
  58d296:      	cmpl	$0x231, %eax            # imm = 0x231
  58d29b:      	ja	0x591a16 <.text+0x190a16>
  58d2a1:      	jmpl	*0x595afd(,%eax,4)
  58d2a8:      	movl	$0x5fdab4, %eax         # imm = 0x5FDAB4
  58d2ad:      	jmp	0x591a45 <.text+0x190a45>
  58d2b2:      	movl	$0x5fda98, %eax         # imm = 0x5FDA98
  58d2b7:      	jmp	0x591a45 <.text+0x190a45>
  58d2bc:      	movl	$0x5fda88, %eax         # imm = 0x5FDA88
  58d2c1:      	jmp	0x591a45 <.text+0x190a45>
  58d2c6:      	movl	$0x5fda74, %eax         # imm = 0x5FDA74
  58d2cb:      	jmp	0x591a45 <.text+0x190a45>
  58d2d0:      	movl	$0x5fda5c, %eax         # imm = 0x5FDA5C
  58d2d5:      	jmp	0x591a45 <.text+0x190a45>
  58d2da:      	movl	$0x5fda4c, %eax         # imm = 0x5FDA4C
  58d2df:      	jmp	0x591a45 <.text+0x190a45>
  58d2e4:      	movl	$0x5fda38, %eax         # imm = 0x5FDA38
  58d2e9:      	jmp	0x591a45 <.text+0x190a45>
  58d2ee:      	movl	$0x5fda1c, %eax         # imm = 0x5FDA1C
  58d2f3:      	jmp	0x591a45 <.text+0x190a45>
  58d2f8:      	movl	$0x5fda04, %eax         # imm = 0x5FDA04
  58d2fd:      	jmp	0x591a45 <.text+0x190a45>
  58d302:      	movl	$0x5fd9e8, %eax         # imm = 0x5FD9E8
  58d307:      	jmp	0x591a45 <.text+0x190a45>
  58d30c:      	movl	$0x5fd9c8, %eax         # imm = 0x5FD9C8
  58d311:      	jmp	0x591a45 <.text+0x190a45>
  58d316:      	movl	$0x5fd9a8, %eax         # imm = 0x5FD9A8
  58d31b:      	jmp	0x591a45 <.text+0x190a45>
  58d320:      	movl	$0x5fd98c, %eax         # imm = 0x5FD98C
  58d325:      	jmp	0x591a45 <.text+0x190a45>
  58d32a:      	movl	$0x5fd964, %eax         # imm = 0x5FD964
  58d32f:      	jmp	0x591a45 <.text+0x190a45>
  58d334:      	movl	$0x5fd944, %eax         # imm = 0x5FD944
  58d339:      	jmp	0x591a45 <.text+0x190a45>
  58d33e:      	movl	$0x5fd92c, %eax         # imm = 0x5FD92C
  58d343:      	jmp	0x591a45 <.text+0x190a45>
  58d348:      	movl	$0x5fd910, %eax         # imm = 0x5FD910
  58d34d:      	jmp	0x591a45 <.text+0x190a45>
  58d352:      	movl	$0x5fd900, %eax         # imm = 0x5FD900
  58d357:      	jmp	0x591a45 <.text+0x190a45>
  58d35c:      	movl	$0x5fd8f0, %eax         # imm = 0x5FD8F0
  58d361:      	jmp	0x591a45 <.text+0x190a45>
  58d366:      	movl	$0x5fd8dc, %eax         # imm = 0x5FD8DC
  58d36b:      	jmp	0x591a45 <.text+0x190a45>
  58d370:      	movl	$0x5fd8c4, %eax         # imm = 0x5FD8C4
  58d375:      	jmp	0x591a45 <.text+0x190a45>
  58d37a:      	movl	$0x5fd8a8, %eax         # imm = 0x5FD8A8
  58d37f:      	jmp	0x591a45 <.text+0x190a45>
  58d384:      	movl	$0x5fd894, %eax         # imm = 0x5FD894
  58d389:      	jmp	0x591a45 <.text+0x190a45>
  58d38e:      	movl	$0x5fd874, %eax         # imm = 0x5FD874
  58d393:      	jmp	0x591a45 <.text+0x190a45>
  58d398:      	movl	$0x5fd850, %eax         # imm = 0x5FD850
  58d39d:      	jmp	0x591a45 <.text+0x190a45>
  58d3a2:      	movl	$0x5fd82c, %eax         # imm = 0x5FD82C
  58d3a7:      	jmp	0x591a45 <.text+0x190a45>
  58d3ac:      	movl	$0x5fd808, %eax         # imm = 0x5FD808
  58d3b1:      	jmp	0x591a45 <.text+0x190a45>
  58d3b6:      	movl	$0x5fd7ec, %eax         # imm = 0x5FD7EC
  58d3bb:      	jmp	0x591a45 <.text+0x190a45>
  58d3c0:      	movl	$0x5fd7d0, %eax         # imm = 0x5FD7D0
  58d3c5:      	jmp	0x591a45 <.text+0x190a45>
  58d3ca:      	movl	$0x5fd7bc, %eax         # imm = 0x5FD7BC
  58d3cf:      	jmp	0x591a45 <.text+0x190a45>
  58d3d4:      	movl	$0x5fd7a0, %eax         # imm = 0x5FD7A0
  58d3d9:      	jmp	0x591a45 <.text+0x190a45>
  58d3de:      	movl	$0x5fd780, %eax         # imm = 0x5FD780
  58d3e3:      	jmp	0x591a45 <.text+0x190a45>
  58d3e8:      	movl	$0x5fd764, %eax         # imm = 0x5FD764
  58d3ed:      	jmp	0x591a45 <.text+0x190a45>
  58d3f2:      	movl	$0x5fd750, %eax         # imm = 0x5FD750
  58d3f7:      	jmp	0x591a45 <.text+0x190a45>
  58d3fc:      	movl	$0x5fd734, %eax         # imm = 0x5FD734
  58d401:      	jmp	0x591a45 <.text+0x190a45>
  58d406:      	movl	$0x5fd720, %eax         # imm = 0x5FD720
  58d40b:      	jmp	0x591a45 <.text+0x190a45>
  58d410:      	movl	$0x5fd70c, %eax         # imm = 0x5FD70C
  58d415:      	jmp	0x591a45 <.text+0x190a45>
  58d41a:      	movl	$0x5fd6f4, %eax         # imm = 0x5FD6F4
  58d41f:      	jmp	0x591a45 <.text+0x190a45>
  58d424:      	movl	$0x5fd6dc, %eax         # imm = 0x5FD6DC
  58d429:      	jmp	0x591a45 <.text+0x190a45>
  58d42e:      	movl	$0x5fd6c0, %eax         # imm = 0x5FD6C0
  58d433:      	jmp	0x591a45 <.text+0x190a45>
  58d438:      	movl	$0x5fd6a8, %eax         # imm = 0x5FD6A8
  58d43d:      	jmp	0x591a45 <.text+0x190a45>
  58d442:      	movl	$0x5fd68c, %eax         # imm = 0x5FD68C
  58d447:      	jmp	0x591a45 <.text+0x190a45>
  58d44c:      	movl	$0x5fd670, %eax         # imm = 0x5FD670
  58d451:      	jmp	0x591a45 <.text+0x190a45>
  58d456:      	movl	$0x5fd658, %eax         # imm = 0x5FD658
  58d45b:      	jmp	0x591a45 <.text+0x190a45>
  58d460:      	movl	$0x5fd640, %eax         # imm = 0x5FD640
  58d465:      	jmp	0x591a45 <.text+0x190a45>
  58d46a:      	movl	$0x5fd624, %eax         # imm = 0x5FD624
  58d46f:      	jmp	0x591a45 <.text+0x190a45>
  58d474:      	movl	$0x5fd608, %eax         # imm = 0x5FD608
  58d479:      	jmp	0x591a45 <.text+0x190a45>
  58d47e:      	movl	$0x5fd5ec, %eax         # imm = 0x5FD5EC
  58d483:      	jmp	0x591a45 <.text+0x190a45>
  58d488:      	movl	$0x5fd5c8, %eax         # imm = 0x5FD5C8
  58d48d:      	jmp	0x591a45 <.text+0x190a45>
  58d492:      	movl	$0x5fd5a4, %eax         # imm = 0x5FD5A4
  58d497:      	jmp	0x591a45 <.text+0x190a45>
  58d49c:      	movl	$0x5fd58c, %eax         # imm = 0x5FD58C
  58d4a1:      	jmp	0x591a45 <.text+0x190a45>
  58d4a6:      	movl	$0x5fd578, %eax         # imm = 0x5FD578
  58d4ab:      	jmp	0x591a45 <.text+0x190a45>
  58d4b0:      	movl	$0x5fd568, %eax         # imm = 0x5FD568
  58d4b5:      	jmp	0x591a45 <.text+0x190a45>
  58d4ba:      	movl	$0x5fd550, %eax         # imm = 0x5FD550
  58d4bf:      	jmp	0x591a45 <.text+0x190a45>
  58d4c4:      	movl	$0x5fd534, %eax         # imm = 0x5FD534
  58d4c9:      	jmp	0x591a45 <.text+0x190a45>
  58d4ce:      	movl	$0x5fd518, %eax         # imm = 0x5FD518
  58d4d3:      	jmp	0x591a45 <.text+0x190a45>
  58d4d8:      	movl	$0x5fd4f4, %eax         # imm = 0x5FD4F4
  58d4dd:      	jmp	0x591a45 <.text+0x190a45>
  58d4e2:      	movl	$0x5fd4d4, %eax         # imm = 0x5FD4D4
  58d4e7:      	jmp	0x591a45 <.text+0x190a45>
  58d4ec:      	movl	$0x5fd4b8, %eax         # imm = 0x5FD4B8
  58d4f1:      	jmp	0x591a45 <.text+0x190a45>
  58d4f6:      	movl	$0x5fd4a0, %eax         # imm = 0x5FD4A0
  58d4fb:      	jmp	0x591a45 <.text+0x190a45>
  58d500:      	movl	$0x5fd484, %eax         # imm = 0x5FD484
  58d505:      	jmp	0x591a45 <.text+0x190a45>
  58d50a:      	movl	$0x5fd46c, %eax         # imm = 0x5FD46C
  58d50f:      	jmp	0x591a45 <.text+0x190a45>
  58d514:      	movl	$0x5fd450, %eax         # imm = 0x5FD450
  58d519:      	jmp	0x591a45 <.text+0x190a45>
  58d51e:      	movl	$0x5fd438, %eax         # imm = 0x5FD438
  58d523:      	jmp	0x591a45 <.text+0x190a45>
  58d528:      	movl	$0x5fd420, %eax         # imm = 0x5FD420
  58d52d:      	jmp	0x591a45 <.text+0x190a45>
  58d532:      	movl	$0x5fd404, %eax         # imm = 0x5FD404
  58d537:      	jmp	0x591a45 <.text+0x190a45>
  58d53c:      	movl	$0x5fd3f8, %eax         # imm = 0x5FD3F8
  58d541:      	jmp	0x591a45 <.text+0x190a45>
  58d546:      	movl	$0x5fd3d8, %eax         # imm = 0x5FD3D8
  58d54b:      	jmp	0x591a45 <.text+0x190a45>
  58d550:      	movl	$0x5fd3b8, %eax         # imm = 0x5FD3B8
  58d555:      	jmp	0x591a45 <.text+0x190a45>
  58d55a:      	movl	$0x5fd398, %eax         # imm = 0x5FD398
  58d55f:      	jmp	0x591a45 <.text+0x190a45>
  58d564:      	movl	$0x5fd380, %eax         # imm = 0x5FD380
  58d569:      	jmp	0x591a45 <.text+0x190a45>
  58d56e:      	movl	$0x5fd364, %eax         # imm = 0x5FD364
  58d573:      	jmp	0x591a45 <.text+0x190a45>
  58d578:      	movl	$0x5fd34c, %eax         # imm = 0x5FD34C
  58d57d:      	jmp	0x591a45 <.text+0x190a45>
  58d582:      	movl	$0x5fd334, %eax         # imm = 0x5FD334
  58d587:      	jmp	0x591a45 <.text+0x190a45>
  58d58c:      	movl	$0x5fd320, %eax         # imm = 0x5FD320
  58d591:      	jmp	0x591a45 <.text+0x190a45>
  58d596:      	movl	$0x5fd310, %eax         # imm = 0x5FD310
  58d59b:      	jmp	0x591a45 <.text+0x190a45>
  58d5a0:      	movl	$0x5fd2f4, %eax         # imm = 0x5FD2F4
  58d5a5:      	jmp	0x591a45 <.text+0x190a45>
  58d5aa:      	movl	$0x5fd2dc, %eax         # imm = 0x5FD2DC
  58d5af:      	jmp	0x591a45 <.text+0x190a45>
  58d5b4:      	movl	$0x5fd2c8, %eax         # imm = 0x5FD2C8
  58d5b9:      	jmp	0x591a45 <.text+0x190a45>
  58d5be:      	movl	$0x5fd2a8, %eax         # imm = 0x5FD2A8
  58d5c3:      	jmp	0x591a45 <.text+0x190a45>
  58d5c8:      	movl	$0x5fd290, %eax         # imm = 0x5FD290
  58d5cd:      	jmp	0x591a45 <.text+0x190a45>
  58d5d2:      	movl	$0x5fd278, %eax         # imm = 0x5FD278
  58d5d7:      	jmp	0x591a45 <.text+0x190a45>
  58d5dc:      	movl	$0x5fd25c, %eax         # imm = 0x5FD25C
  58d5e1:      	jmp	0x591a45 <.text+0x190a45>
  58d5e6:      	movl	$0x5fd23c, %eax         # imm = 0x5FD23C
  58d5eb:      	jmp	0x591a45 <.text+0x190a45>
  58d5f0:      	movl	$0x5fd224, %eax         # imm = 0x5FD224
  58d5f5:      	jmp	0x591a45 <.text+0x190a45>
  58d5fa:      	movl	$0x5fd20c, %eax         # imm = 0x5FD20C
  58d5ff:      	jmp	0x591a45 <.text+0x190a45>
  58d604:      	movl	$0x5fd1f4, %eax         # imm = 0x5FD1F4
  58d609:      	jmp	0x591a45 <.text+0x190a45>
  58d60e:      	movl	$0x5fd1e0, %eax         # imm = 0x5FD1E0
  58d613:      	jmp	0x591a45 <.text+0x190a45>
  58d618:      	movl	$0x5fd1c4, %eax         # imm = 0x5FD1C4
  58d61d:      	jmp	0x591a45 <.text+0x190a45>
  58d622:      	movl	$0x5fd1a4, %eax         # imm = 0x5FD1A4
  58d627:      	jmp	0x591a45 <.text+0x190a45>
  58d62c:      	movl	$0x5fd184, %eax         # imm = 0x5FD184
  58d631:      	jmp	0x591a45 <.text+0x190a45>
  58d636:      	movl	$0x5fd16c, %eax         # imm = 0x5FD16C
  58d63b:      	jmp	0x591a45 <.text+0x190a45>
  58d640:      	movl	$0x5fd150, %eax         # imm = 0x5FD150
  58d645:      	jmp	0x591a45 <.text+0x190a45>
  58d64a:      	movl	$0x5fd138, %eax         # imm = 0x5FD138
  58d64f:      	jmp	0x591a45 <.text+0x190a45>
  58d654:      	movl	$0x5fd11c, %eax         # imm = 0x5FD11C
  58d659:      	jmp	0x591a45 <.text+0x190a45>
  58d65e:      	movl	$0x5fd100, %eax         # imm = 0x5FD100
  58d663:      	jmp	0x591a45 <.text+0x190a45>
  58d668:      	movl	$0x5fd0ec, %eax         # imm = 0x5FD0EC
  58d66d:      	jmp	0x591a45 <.text+0x190a45>
  58d672:      	movl	$0x5fd0d8, %eax         # imm = 0x5FD0D8
  58d677:      	jmp	0x591a45 <.text+0x190a45>
  58d67c:      	movl	$0x5fd0c4, %eax         # imm = 0x5FD0C4
  58d681:      	jmp	0x591a45 <.text+0x190a45>
  58d686:      	movl	$0x5fd0b0, %eax         # imm = 0x5FD0B0
  58d68b:      	jmp	0x591a45 <.text+0x190a45>
  58d690:      	movl	$0x5fd098, %eax         # imm = 0x5FD098
  58d695:      	jmp	0x591a45 <.text+0x190a45>
  58d69a:      	movl	$0x5fd07c, %eax         # imm = 0x5FD07C
  58d69f:      	jmp	0x591a45 <.text+0x190a45>
  58d6a4:      	movl	$0x5fd068, %eax         # imm = 0x5FD068
  58d6a9:      	jmp	0x591a45 <.text+0x190a45>
  58d6ae:      	movl	$0x5fd050, %eax         # imm = 0x5FD050
  58d6b3:      	jmp	0x591a45 <.text+0x190a45>
  58d6b8:      	movl	$0x5fd034, %eax         # imm = 0x5FD034
  58d6bd:      	jmp	0x591a45 <.text+0x190a45>
  58d6c2:      	movl	$0x5fd018, %eax         # imm = 0x5FD018
  58d6c7:      	jmp	0x591a45 <.text+0x190a45>
  58d6cc:      	movl	$0x5fd004, %eax         # imm = 0x5FD004
  58d6d1:      	jmp	0x591a45 <.text+0x190a45>
  58d6d6:      	movl	$0x5fcfe8, %eax         # imm = 0x5FCFE8
  58d6db:      	jmp	0x591a45 <.text+0x190a45>
  58d6e0:      	movl	$0x5fcfcc, %eax         # imm = 0x5FCFCC
  58d6e5:      	jmp	0x591a45 <.text+0x190a45>
  58d6ea:      	movl	$0x5fcfb0, %eax         # imm = 0x5FCFB0
  58d6ef:      	jmp	0x591a45 <.text+0x190a45>
  58d6f4:      	movl	$0x5fcf98, %eax         # imm = 0x5FCF98
  58d6f9:      	jmp	0x591a45 <.text+0x190a45>
  58d6fe:      	movl	$0x5fcf80, %eax         # imm = 0x5FCF80
  58d703:      	jmp	0x591a45 <.text+0x190a45>
  58d708:      	movl	$0x5fcf6c, %eax         # imm = 0x5FCF6C
  58d70d:      	jmp	0x591a45 <.text+0x190a45>
  58d712:      	movl	$0x5fcf4c, %eax         # imm = 0x5FCF4C
  58d717:      	jmp	0x591a45 <.text+0x190a45>
  58d71c:      	movl	$0x5fcf34, %eax         # imm = 0x5FCF34
  58d721:      	jmp	0x591a45 <.text+0x190a45>
  58d726:      	movl	$0x5fcf18, %eax         # imm = 0x5FCF18
  58d72b:      	jmp	0x591a45 <.text+0x190a45>
  58d730:      	movl	$0x5fcf04, %eax         # imm = 0x5FCF04
  58d735:      	jmp	0x591a45 <.text+0x190a45>
  58d73a:      	movl	$0x5fcef0, %eax         # imm = 0x5FCEF0
  58d73f:      	jmp	0x591a45 <.text+0x190a45>
  58d744:      	movl	$0x5fced0, %eax         # imm = 0x5FCED0
  58d749:      	jmp	0x591a45 <.text+0x190a45>
  58d74e:      	movl	$0x5fceb4, %eax         # imm = 0x5FCEB4
  58d753:      	jmp	0x591a45 <.text+0x190a45>
  58d758:      	movl	$0x5fce9c, %eax         # imm = 0x5FCE9C
  58d75d:      	jmp	0x591a45 <.text+0x190a45>
  58d762:      	movl	$0x5fce80, %eax         # imm = 0x5FCE80
  58d767:      	jmp	0x591a45 <.text+0x190a45>
  58d76c:      	movl	$0x5fce64, %eax         # imm = 0x5FCE64
  58d771:      	jmp	0x591a45 <.text+0x190a45>
  58d776:      	movl	$0x5fce44, %eax         # imm = 0x5FCE44
  58d77b:      	jmp	0x591a45 <.text+0x190a45>
  58d780:      	movl	$0x5fce24, %eax         # imm = 0x5FCE24
  58d785:      	jmp	0x591a45 <.text+0x190a45>
  58d78a:      	movl	$0x5fce04, %eax         # imm = 0x5FCE04
  58d78f:      	jmp	0x591a45 <.text+0x190a45>
  58d794:      	movl	$0x5fcde8, %eax         # imm = 0x5FCDE8
  58d799:      	jmp	0x591a45 <.text+0x190a45>
  58d79e:      	movl	$0x5fcdcc, %eax         # imm = 0x5FCDCC
  58d7a3:      	jmp	0x591a45 <.text+0x190a45>
  58d7a8:      	movl	$0x5fcdb4, %eax         # imm = 0x5FCDB4
  58d7ad:      	jmp	0x591a45 <.text+0x190a45>
  58d7b2:      	movl	$0x5fcd98, %eax         # imm = 0x5FCD98
  58d7b7:      	jmp	0x591a45 <.text+0x190a45>
  58d7bc:      	movl	$0x5fcd78, %eax         # imm = 0x5FCD78
  58d7c1:      	jmp	0x591a45 <.text+0x190a45>
  58d7c6:      	movl	$0x5fcd5c, %eax         # imm = 0x5FCD5C
  58d7cb:      	jmp	0x591a45 <.text+0x190a45>
  58d7d0:      	movl	$0x5fcd40, %eax         # imm = 0x5FCD40
  58d7d5:      	jmp	0x591a45 <.text+0x190a45>
  58d7da:      	movl	$0x5fcd24, %eax         # imm = 0x5FCD24
  58d7df:      	jmp	0x591a45 <.text+0x190a45>
  58d7e4:      	movl	$0x5fcd0c, %eax         # imm = 0x5FCD0C
  58d7e9:      	jmp	0x591a45 <.text+0x190a45>
  58d7ee:      	movl	$0x5fccf8, %eax         # imm = 0x5FCCF8
  58d7f3:      	jmp	0x591a45 <.text+0x190a45>
  58d7f8:      	movl	$0x5fccdc, %eax         # imm = 0x5FCCDC
  58d7fd:      	jmp	0x591a45 <.text+0x190a45>
  58d802:      	movl	$0x5fccbc, %eax         # imm = 0x5FCCBC
  58d807:      	jmp	0x591a45 <.text+0x190a45>
  58d80c:      	movl	$0x5fcca4, %eax         # imm = 0x5FCCA4
  58d811:      	jmp	0x591a45 <.text+0x190a45>
  58d816:      	movl	$0x5fcc88, %eax         # imm = 0x5FCC88
  58d81b:      	jmp	0x591a45 <.text+0x190a45>
  58d820:      	movl	$0x5fcc6c, %eax         # imm = 0x5FCC6C
  58d825:      	jmp	0x591a45 <.text+0x190a45>
  58d82a:      	movl	$0x5fcc54, %eax         # imm = 0x5FCC54
  58d82f:      	jmp	0x591a45 <.text+0x190a45>
  58d834:      	movl	$0x5fcc38, %eax         # imm = 0x5FCC38
  58d839:      	jmp	0x591a45 <.text+0x190a45>
  58d83e:      	movl	$0x5fcc20, %eax         # imm = 0x5FCC20
  58d843:      	jmp	0x591a45 <.text+0x190a45>
  58d848:      	movl	$0x5fcc00, %eax         # imm = 0x5FCC00
  58d84d:      	jmp	0x591a45 <.text+0x190a45>
  58d852:      	movl	$0x5fcbe0, %eax         # imm = 0x5FCBE0
  58d857:      	jmp	0x591a45 <.text+0x190a45>
  58d85c:      	movl	$0x5fcbc4, %eax         # imm = 0x5FCBC4
  58d861:      	jmp	0x591a45 <.text+0x190a45>
  58d866:      	movl	$0x5fcba8, %eax         # imm = 0x5FCBA8
  58d86b:      	jmp	0x591a45 <.text+0x190a45>
  58d870:      	movl	$0x5fcb8c, %eax         # imm = 0x5FCB8C
  58d875:      	jmp	0x591a45 <.text+0x190a45>
  58d87a:      	movl	$0x5fcb70, %eax         # imm = 0x5FCB70
  58d87f:      	jmp	0x591a45 <.text+0x190a45>
  58d884:      	movl	$0x5fcb58, %eax         # imm = 0x5FCB58
  58d889:      	jmp	0x591a45 <.text+0x190a45>
  58d88e:      	movl	$0x5fcb44, %eax         # imm = 0x5FCB44
  58d893:      	jmp	0x591a45 <.text+0x190a45>
  58d898:      	movl	$0x5fcb30, %eax         # imm = 0x5FCB30
  58d89d:      	jmp	0x591a45 <.text+0x190a45>
  58d8a2:      	movl	$0x5fcb14, %eax         # imm = 0x5FCB14
  58d8a7:      	jmp	0x591a45 <.text+0x190a45>
  58d8ac:      	movl	$0x5fcaf8, %eax         # imm = 0x5FCAF8
  58d8b1:      	jmp	0x591a45 <.text+0x190a45>
  58d8b6:      	movl	$0x5fcae4, %eax         # imm = 0x5FCAE4
  58d8bb:      	jmp	0x591a45 <.text+0x190a45>
  58d8c0:      	movl	$0x5fcac8, %eax         # imm = 0x5FCAC8
  58d8c5:      	jmp	0x591a45 <.text+0x190a45>
  58d8ca:      	movl	$0x5fcab0, %eax         # imm = 0x5FCAB0
  58d8cf:      	jmp	0x591a45 <.text+0x190a45>
  58d8d4:      	movl	$0x5fca9c, %eax         # imm = 0x5FCA9C
  58d8d9:      	jmp	0x591a45 <.text+0x190a45>
  58d8de:      	movl	$0x5fca84, %eax         # imm = 0x5FCA84
  58d8e3:      	jmp	0x591a45 <.text+0x190a45>
  58d8e8:      	movl	$0x5fca6c, %eax         # imm = 0x5FCA6C
  58d8ed:      	jmp	0x591a45 <.text+0x190a45>
  58d8f2:      	movl	$0x5fca54, %eax         # imm = 0x5FCA54
  58d8f7:      	jmp	0x591a45 <.text+0x190a45>
  58d8fc:      	movl	$0x5fca3c, %eax         # imm = 0x5FCA3C
  58d901:      	jmp	0x591a45 <.text+0x190a45>
  58d906:      	movl	$0x5fca20, %eax         # imm = 0x5FCA20
  58d90b:      	jmp	0x591a45 <.text+0x190a45>
  58d910:      	movl	$0x5fca00, %eax         # imm = 0x5FCA00
  58d915:      	jmp	0x591a45 <.text+0x190a45>
  58d91a:      	movl	$0x5fc9dc, %eax         # imm = 0x5FC9DC
  58d91f:      	jmp	0x591a45 <.text+0x190a45>
  58d924:      	movl	$0x5fc9c4, %eax         # imm = 0x5FC9C4
  58d929:      	jmp	0x591a45 <.text+0x190a45>
  58d92e:      	movl	$0x5fc9ac, %eax         # imm = 0x5FC9AC
  58d933:      	jmp	0x591a45 <.text+0x190a45>
  58d938:      	movl	$0x5fc998, %eax         # imm = 0x5FC998
  58d93d:      	jmp	0x591a45 <.text+0x190a45>
  58d942:      	movl	$0x5fc974, %eax         # imm = 0x5FC974
  58d947:      	jmp	0x591a45 <.text+0x190a45>
  58d94c:      	movl	$0x5fc95c, %eax         # imm = 0x5FC95C
  58d951:      	jmp	0x591a45 <.text+0x190a45>
  58d956:      	movl	$0x5fc948, %eax         # imm = 0x5FC948
  58d95b:      	jmp	0x591a45 <.text+0x190a45>
  58d960:      	movl	$0x5fc934, %eax         # imm = 0x5FC934
  58d965:      	jmp	0x591a45 <.text+0x190a45>
  58d96a:      	movl	$0x5fc918, %eax         # imm = 0x5FC918
  58d96f:      	jmp	0x591a45 <.text+0x190a45>
  58d974:      	movl	$0x5fc8f8, %eax         # imm = 0x5FC8F8
  58d979:      	jmp	0x591a45 <.text+0x190a45>
  58d97e:      	movl	$0x5fc8e0, %eax         # imm = 0x5FC8E0
  58d983:      	jmp	0x591a45 <.text+0x190a45>
  58d988:      	movl	$0x5fc8c4, %eax         # imm = 0x5FC8C4
  58d98d:      	jmp	0x591a45 <.text+0x190a45>
  58d992:      	movl	$0x5fc8b4, %eax         # imm = 0x5FC8B4
  58d997:      	jmp	0x591a45 <.text+0x190a45>
  58d99c:      	movl	$0x5fc898, %eax         # imm = 0x5FC898
  58d9a1:      	jmp	0x591a45 <.text+0x190a45>
  58d9a6:      	movl	$0x5fc87c, %eax         # imm = 0x5FC87C
  58d9ab:      	jmp	0x591a45 <.text+0x190a45>
  58d9b0:      	movl	$0x5fc860, %eax         # imm = 0x5FC860
  58d9b5:      	jmp	0x591a45 <.text+0x190a45>
  58d9ba:      	movl	$0x5fc844, %eax         # imm = 0x5FC844
  58d9bf:      	jmp	0x591a45 <.text+0x190a45>
  58d9c4:      	movl	$0x5fc828, %eax         # imm = 0x5FC828
  58d9c9:      	jmp	0x591a45 <.text+0x190a45>
  58d9ce:      	movl	$0x5fc80c, %eax         # imm = 0x5FC80C
  58d9d3:      	jmp	0x591a45 <.text+0x190a45>
  58d9d8:      	movl	$0x5fc7f4, %eax         # imm = 0x5FC7F4
  58d9dd:      	jmp	0x591a45 <.text+0x190a45>
  58d9e2:      	movl	$0x5fc7d8, %eax         # imm = 0x5FC7D8
  58d9e7:      	jmp	0x591a45 <.text+0x190a45>
  58d9ec:      	movl	$0x5fc7b8, %eax         # imm = 0x5FC7B8
  58d9f1:      	jmp	0x591a45 <.text+0x190a45>
  58d9f6:      	movl	$0x5fc798, %eax         # imm = 0x5FC798
  58d9fb:      	jmp	0x591a45 <.text+0x190a45>
  58da00:      	movl	$0x5fc77c, %eax         # imm = 0x5FC77C
  58da05:      	jmp	0x591a45 <.text+0x190a45>
  58da0a:      	movl	$0x5fc760, %eax         # imm = 0x5FC760
  58da0f:      	jmp	0x591a45 <.text+0x190a45>
  58da14:      	movl	$0x5fc748, %eax         # imm = 0x5FC748
  58da19:      	jmp	0x591a45 <.text+0x190a45>
  58da1e:      	movl	$0x5fc734, %eax         # imm = 0x5FC734
  58da23:      	jmp	0x591a45 <.text+0x190a45>
  58da28:      	movl	$0x5fc718, %eax         # imm = 0x5FC718
  58da2d:      	jmp	0x591a45 <.text+0x190a45>
  58da32:      	movl	$0x5fc6fc, %eax         # imm = 0x5FC6FC
  58da37:      	jmp	0x591a45 <.text+0x190a45>
  58da3c:      	movl	$0x5fc6e0, %eax         # imm = 0x5FC6E0
  58da41:      	jmp	0x591a45 <.text+0x190a45>
  58da46:      	movl	$0x5fc6c0, %eax         # imm = 0x5FC6C0
  58da4b:      	jmp	0x591a45 <.text+0x190a45>
  58da50:      	movl	$0x5fc6a4, %eax         # imm = 0x5FC6A4
  58da55:      	jmp	0x591a45 <.text+0x190a45>
  58da5a:      	movl	$0x5fc688, %eax         # imm = 0x5FC688
  58da5f:      	jmp	0x591a45 <.text+0x190a45>
  58da64:      	movl	$0x5fc670, %eax         # imm = 0x5FC670
  58da69:      	jmp	0x591a45 <.text+0x190a45>
  58da6e:      	movl	$0x5fc654, %eax         # imm = 0x5FC654
  58da73:      	jmp	0x591a45 <.text+0x190a45>
  58da78:      	movl	$0x5fc634, %eax         # imm = 0x5FC634
  58da7d:      	jmp	0x591a45 <.text+0x190a45>
  58da82:      	movl	$0x5fc618, %eax         # imm = 0x5FC618
  58da87:      	jmp	0x591a45 <.text+0x190a45>
  58da8c:      	movl	$0x5fc5fc, %eax         # imm = 0x5FC5FC
  58da91:      	jmp	0x591a45 <.text+0x190a45>
  58da96:      	movl	$0x5fc5e8, %eax         # imm = 0x5FC5E8
  58da9b:      	jmp	0x591a45 <.text+0x190a45>
  58daa0:      	movl	$0x5fc5cc, %eax         # imm = 0x5FC5CC
  58daa5:      	jmp	0x591a45 <.text+0x190a45>
  58daaa:      	movl	$0x5fc5b0, %eax         # imm = 0x5FC5B0
  58daaf:      	jmp	0x591a45 <.text+0x190a45>
  58dab4:      	movl	$0x5fc598, %eax         # imm = 0x5FC598
  58dab9:      	jmp	0x591a45 <.text+0x190a45>
  58dabe:      	movl	$0x5fc580, %eax         # imm = 0x5FC580
  58dac3:      	jmp	0x591a45 <.text+0x190a45>
  58dac8:      	movl	$0x5fc568, %eax         # imm = 0x5FC568
  58dacd:      	jmp	0x591a45 <.text+0x190a45>
  58dad2:      	movl	$0x5fc54c, %eax         # imm = 0x5FC54C
  58dad7:      	jmp	0x591a45 <.text+0x190a45>
  58dadc:      	movl	$0x5fc530, %eax         # imm = 0x5FC530
  58dae1:      	jmp	0x591a45 <.text+0x190a45>
  58dae6:      	movl	$0x5fc514, %eax         # imm = 0x5FC514
  58daeb:      	jmp	0x591a45 <.text+0x190a45>
  58daf0:      	movl	$0x5fc4f8, %eax         # imm = 0x5FC4F8
  58daf5:      	jmp	0x591a45 <.text+0x190a45>
  58dafa:      	movl	$0x5fc4d0, %eax         # imm = 0x5FC4D0
  58daff:      	jmp	0x591a45 <.text+0x190a45>
  58db04:      	movl	$0x5fc4b8, %eax         # imm = 0x5FC4B8
  58db09:      	jmp	0x591a45 <.text+0x190a45>
  58db0e:      	movl	$0x5fc4a0, %eax         # imm = 0x5FC4A0
  58db13:      	jmp	0x591a45 <.text+0x190a45>
  58db18:      	movl	$0x5fc484, %eax         # imm = 0x5FC484
  58db1d:      	jmp	0x591a45 <.text+0x190a45>
  58db22:      	movl	$0x5fc46c, %eax         # imm = 0x5FC46C
  58db27:      	jmp	0x591a45 <.text+0x190a45>
  58db2c:      	movl	$0x5fc450, %eax         # imm = 0x5FC450
  58db31:      	jmp	0x591a45 <.text+0x190a45>
  58db36:      	movl	$0x5fc430, %eax         # imm = 0x5FC430
  58db3b:      	jmp	0x591a45 <.text+0x190a45>
  58db40:      	movl	$0x5fc418, %eax         # imm = 0x5FC418
  58db45:      	jmp	0x591a45 <.text+0x190a45>
  58db4a:      	movl	$0x5fc3fc, %eax         # imm = 0x5FC3FC
  58db4f:      	jmp	0x591a45 <.text+0x190a45>
  58db54:      	movl	$0x5fc3e4, %eax         # imm = 0x5FC3E4
  58db59:      	jmp	0x591a45 <.text+0x190a45>
  58db5e:      	movl	$0x5fc3c8, %eax         # imm = 0x5FC3C8
  58db63:      	jmp	0x591a45 <.text+0x190a45>
  58db68:      	movl	$0x5fc3ac, %eax         # imm = 0x5FC3AC
  58db6d:      	jmp	0x591a45 <.text+0x190a45>
  58db72:      	movl	$0x5fc398, %eax         # imm = 0x5FC398
  58db77:      	jmp	0x591a45 <.text+0x190a45>
  58db7c:      	movl	$0x5fc378, %eax         # imm = 0x5FC378
  58db81:      	jmp	0x591a45 <.text+0x190a45>
  58db86:      	movl	$0x5fc358, %eax         # imm = 0x5FC358
  58db8b:      	jmp	0x591a45 <.text+0x190a45>
  58db90:      	movl	$0x5fc33c, %eax         # imm = 0x5FC33C
  58db95:      	jmp	0x591a45 <.text+0x190a45>
  58db9a:      	movl	$0x5fc31c, %eax         # imm = 0x5FC31C
  58db9f:      	jmp	0x591a45 <.text+0x190a45>
  58dba4:      	movl	$0x5fc2fc, %eax         # imm = 0x5FC2FC
  58dba9:      	jmp	0x591a45 <.text+0x190a45>
  58dbae:      	movl	$0x5fc2e4, %eax         # imm = 0x5FC2E4
  58dbb3:      	jmp	0x591a45 <.text+0x190a45>
  58dbb8:      	movl	$0x5fc2cc, %eax         # imm = 0x5FC2CC
  58dbbd:      	jmp	0x591a45 <.text+0x190a45>
  58dbc2:      	movl	$0x5fc2b4, %eax         # imm = 0x5FC2B4
  58dbc7:      	jmp	0x591a45 <.text+0x190a45>
  58dbcc:      	movl	$0x5fc298, %eax         # imm = 0x5FC298
  58dbd1:      	jmp	0x591a45 <.text+0x190a45>
  58dbd6:      	movl	$0x5fc278, %eax         # imm = 0x5FC278
  58dbdb:      	jmp	0x591a45 <.text+0x190a45>
  58dbe0:      	movl	$0x5fc25c, %eax         # imm = 0x5FC25C
  58dbe5:      	jmp	0x591a45 <.text+0x190a45>
  58dbea:      	movl	$0x5fc230, %eax         # imm = 0x5FC230
  58dbef:      	jmp	0x591a45 <.text+0x190a45>
  58dbf4:      	movl	$0x5fc220, %eax         # imm = 0x5FC220
  58dbf9:      	jmp	0x591a45 <.text+0x190a45>
  58dbfe:      	movl	$0x5fc200, %eax         # imm = 0x5FC200
  58dc03:      	jmp	0x591a45 <.text+0x190a45>
  58dc08:      	movl	$0x5fc1e4, %eax         # imm = 0x5FC1E4
  58dc0d:      	jmp	0x591a45 <.text+0x190a45>
  58dc12:      	movl	$0x5fc1c8, %eax         # imm = 0x5FC1C8
  58dc17:      	jmp	0x591a45 <.text+0x190a45>
  58dc1c:      	movl	$0x5fc1b4, %eax         # imm = 0x5FC1B4
  58dc21:      	jmp	0x591a45 <.text+0x190a45>
  58dc26:      	movl	$0x5fc198, %eax         # imm = 0x5FC198
  58dc2b:      	jmp	0x591a45 <.text+0x190a45>
  58dc30:      	movl	$0x5fc180, %eax         # imm = 0x5FC180
  58dc35:      	jmp	0x591a45 <.text+0x190a45>
  58dc3a:      	movl	$0x5fc168, %eax         # imm = 0x5FC168
  58dc3f:      	jmp	0x591a45 <.text+0x190a45>
  58dc44:      	movl	$0x5fc150, %eax         # imm = 0x5FC150
  58dc49:      	jmp	0x591a45 <.text+0x190a45>
  58dc4e:      	movl	$0x5fc138, %eax         # imm = 0x5FC138
  58dc53:      	jmp	0x591a45 <.text+0x190a45>
  58dc58:      	movl	$0x5fc120, %eax         # imm = 0x5FC120
  58dc5d:      	jmp	0x591a45 <.text+0x190a45>
  58dc62:      	movl	$0x5fc108, %eax         # imm = 0x5FC108
  58dc67:      	jmp	0x591a45 <.text+0x190a45>
  58dc6c:      	movl	$0x5fc0f0, %eax         # imm = 0x5FC0F0
  58dc71:      	jmp	0x591a45 <.text+0x190a45>
  58dc76:      	movl	$0x5fc0d4, %eax         # imm = 0x5FC0D4
  58dc7b:      	jmp	0x591a45 <.text+0x190a45>
  58dc80:      	movl	$0x5fc0bc, %eax         # imm = 0x5FC0BC
  58dc85:      	jmp	0x591a45 <.text+0x190a45>
  58dc8a:      	movl	$0x5fc0a8, %eax         # imm = 0x5FC0A8
  58dc8f:      	jmp	0x591a45 <.text+0x190a45>
  58dc94:      	movl	$0x5fc08c, %eax         # imm = 0x5FC08C
  58dc99:      	jmp	0x591a45 <.text+0x190a45>
  58dc9e:      	movl	$0x5fc070, %eax         # imm = 0x5FC070
  58dca3:      	jmp	0x591a45 <.text+0x190a45>
  58dca8:      	movl	$0x5fc058, %eax         # imm = 0x5FC058
  58dcad:      	jmp	0x591a45 <.text+0x190a45>
  58dcb2:      	movl	$0x5fc044, %eax         # imm = 0x5FC044
  58dcb7:      	jmp	0x591a45 <.text+0x190a45>
  58dcbc:      	movl	$0x5fc02c, %eax         # imm = 0x5FC02C
  58dcc1:      	jmp	0x591a45 <.text+0x190a45>
  58dcc6:      	movl	$0x5fc00c, %eax         # imm = 0x5FC00C
  58dccb:      	jmp	0x591a45 <.text+0x190a45>
  58dcd0:      	movl	$0x5fbff0, %eax         # imm = 0x5FBFF0
  58dcd5:      	jmp	0x591a45 <.text+0x190a45>
  58dcda:      	movl	$0x5fbfd8, %eax         # imm = 0x5FBFD8
  58dcdf:      	jmp	0x591a45 <.text+0x190a45>
  58dce4:      	movl	$0x5fbfbc, %eax         # imm = 0x5FBFBC
  58dce9:      	jmp	0x591a45 <.text+0x190a45>
  58dcee:      	movl	$0x5fbfa0, %eax         # imm = 0x5FBFA0
  58dcf3:      	jmp	0x591a45 <.text+0x190a45>
  58dcf8:      	movl	$0x5fbf84, %eax         # imm = 0x5FBF84
  58dcfd:      	jmp	0x591a45 <.text+0x190a45>
  58dd02:      	movl	$0x5fbf64, %eax         # imm = 0x5FBF64
  58dd07:      	jmp	0x591a45 <.text+0x190a45>
  58dd0c:      	movl	$0x5fbf4c, %eax         # imm = 0x5FBF4C
  58dd11:      	jmp	0x591a45 <.text+0x190a45>
  58dd16:      	movl	$0x5fbf34, %eax         # imm = 0x5FBF34
  58dd1b:      	jmp	0x591a45 <.text+0x190a45>
  58dd20:      	movl	$0x5fbf1c, %eax         # imm = 0x5FBF1C
  58dd25:      	jmp	0x591a45 <.text+0x190a45>
  58dd2a:      	movl	$0x5fbf04, %eax         # imm = 0x5FBF04
  58dd2f:      	jmp	0x591a45 <.text+0x190a45>
  58dd34:      	movl	$0x5fbee8, %eax         # imm = 0x5FBEE8
  58dd39:      	jmp	0x591a45 <.text+0x190a45>
  58dd3e:      	movl	$0x5fbec8, %eax         # imm = 0x5FBEC8
  58dd43:      	jmp	0x591a45 <.text+0x190a45>
  58dd48:      	movl	$0x5fbeac, %eax         # imm = 0x5FBEAC
  58dd4d:      	jmp	0x591a45 <.text+0x190a45>
  58dd52:      	movl	$0x5fbe94, %eax         # imm = 0x5FBE94
  58dd57:      	jmp	0x591a45 <.text+0x190a45>
  58dd5c:      	movl	$0x5fbe78, %eax         # imm = 0x5FBE78
  58dd61:      	jmp	0x591a45 <.text+0x190a45>
  58dd66:      	movl	$0x5fbe60, %eax         # imm = 0x5FBE60
  58dd6b:      	jmp	0x591a45 <.text+0x190a45>
  58dd70:      	movl	$0x5fbe44, %eax         # imm = 0x5FBE44
  58dd75:      	jmp	0x591a45 <.text+0x190a45>
  58dd7a:      	movl	$0x5fbe20, %eax         # imm = 0x5FBE20
  58dd7f:      	jmp	0x591a45 <.text+0x190a45>
  58dd84:      	movl	$0x5fbe10, %eax         # imm = 0x5FBE10
  58dd89:      	jmp	0x591a45 <.text+0x190a45>
  58dd8e:      	movl	$0x5fbdf8, %eax         # imm = 0x5FBDF8
  58dd93:      	jmp	0x591a45 <.text+0x190a45>
  58dd98:      	movl	$0x5fbde0, %eax         # imm = 0x5FBDE0
  58dd9d:      	jmp	0x591a45 <.text+0x190a45>
  58dda2:      	movl	$0x5fbdcc, %eax         # imm = 0x5FBDCC
  58dda7:      	jmp	0x591a45 <.text+0x190a45>
  58ddac:      	movl	$0x5fbdac, %eax         # imm = 0x5FBDAC
  58ddb1:      	jmp	0x591a45 <.text+0x190a45>
  58ddb6:      	movl	$0x5fbd90, %eax         # imm = 0x5FBD90
  58ddbb:      	jmp	0x591a45 <.text+0x190a45>
  58ddc0:      	movl	$0x5fbd78, %eax         # imm = 0x5FBD78
  58ddc5:      	jmp	0x591a45 <.text+0x190a45>
  58ddca:      	movl	$0x5fbd60, %eax         # imm = 0x5FBD60
  58ddcf:      	jmp	0x591a45 <.text+0x190a45>
  58ddd4:      	movl	$0x5fbd3c, %eax         # imm = 0x5FBD3C
  58ddd9:      	jmp	0x591a45 <.text+0x190a45>
  58ddde:      	movl	$0x5fbd20, %eax         # imm = 0x5FBD20
  58dde3:      	jmp	0x591a45 <.text+0x190a45>
  58dde8:      	movl	$0x5fbd08, %eax         # imm = 0x5FBD08
  58dded:      	jmp	0x591a45 <.text+0x190a45>
  58ddf2:      	movl	$0x5fbce0, %eax         # imm = 0x5FBCE0
  58ddf7:      	jmp	0x591a45 <.text+0x190a45>
  58ddfc:      	movl	$0x5fbcb8, %eax         # imm = 0x5FBCB8
  58de01:      	jmp	0x591a45 <.text+0x190a45>
  58de06:      	movl	$0x5fbca0, %eax         # imm = 0x5FBCA0
  58de0b:      	jmp	0x591a45 <.text+0x190a45>
  58de10:      	movl	$0x5fbc80, %eax         # imm = 0x5FBC80
  58de15:      	jmp	0x591a45 <.text+0x190a45>
  58de1a:      	movl	$0x5fbc5c, %eax         # imm = 0x5FBC5C
  58de1f:      	jmp	0x591a45 <.text+0x190a45>
  58de24:      	movl	$0x5fbc3c, %eax         # imm = 0x5FBC3C
  58de29:      	jmp	0x591a45 <.text+0x190a45>
  58de2e:      	movl	$0x5fbc1c, %eax         # imm = 0x5FBC1C
  58de33:      	jmp	0x591a45 <.text+0x190a45>
  58de38:      	movl	$0x5fbbfc, %eax         # imm = 0x5FBBFC
  58de3d:      	jmp	0x591a45 <.text+0x190a45>
  58de42:      	movl	$0x5fbbd8, %eax         # imm = 0x5FBBD8
  58de47:      	jmp	0x591a45 <.text+0x190a45>
  58de4c:      	movl	$0x5fbbb8, %eax         # imm = 0x5FBBB8
  58de51:      	jmp	0x591a45 <.text+0x190a45>
  58de56:      	movl	$0x5fbb9c, %eax         # imm = 0x5FBB9C
  58de5b:      	jmp	0x591a45 <.text+0x190a45>
  58de60:      	movl	$0x5fbb80, %eax         # imm = 0x5FBB80
  58de65:      	jmp	0x591a45 <.text+0x190a45>
  58de6a:      	movl	$0x5fbb5c, %eax         # imm = 0x5FBB5C
  58de6f:      	jmp	0x591a45 <.text+0x190a45>
  58de74:      	movl	$0x5fbb3c, %eax         # imm = 0x5FBB3C
  58de79:      	jmp	0x591a45 <.text+0x190a45>
  58de7e:      	movl	$0x5fbb1c, %eax         # imm = 0x5FBB1C
  58de83:      	jmp	0x591a45 <.text+0x190a45>
  58de88:      	movl	$0x5fbb00, %eax         # imm = 0x5FBB00
  58de8d:      	jmp	0x591a45 <.text+0x190a45>
  58de92:      	movl	$0x5fbae8, %eax         # imm = 0x5FBAE8
  58de97:      	jmp	0x591a45 <.text+0x190a45>
  58de9c:      	movl	$0x5fbad4, %eax         # imm = 0x5FBAD4
  58dea1:      	jmp	0x591a45 <.text+0x190a45>
  58dea6:      	movl	$0x5fbabc, %eax         # imm = 0x5FBABC
  58deab:      	jmp	0x591a45 <.text+0x190a45>
  58deb0:      	movl	$0x5fbaa4, %eax         # imm = 0x5FBAA4
  58deb5:      	jmp	0x591a45 <.text+0x190a45>
  58deba:      	movl	$0x5fba90, %eax         # imm = 0x5FBA90
  58debf:      	jmp	0x591a45 <.text+0x190a45>
  58dec4:      	movl	$0x5fba70, %eax         # imm = 0x5FBA70
  58dec9:      	jmp	0x591a45 <.text+0x190a45>
  58dece:      	movl	$0x5fba4c, %eax         # imm = 0x5FBA4C
  58ded3:      	jmp	0x591a45 <.text+0x190a45>
  58ded8:      	movl	$0x5fba34, %eax         # imm = 0x5FBA34
  58dedd:      	jmp	0x591a45 <.text+0x190a45>
  58dee2:      	movl	$0x5fba14, %eax         # imm = 0x5FBA14
  58dee7:      	jmp	0x591a45 <.text+0x190a45>
  58deec:      	movl	$0x5fb9f8, %eax         # imm = 0x5FB9F8
  58def1:      	jmp	0x591a45 <.text+0x190a45>
  58def6:      	movl	$0x5fb9d8, %eax         # imm = 0x5FB9D8
  58defb:      	jmp	0x591a45 <.text+0x190a45>
  58df00:      	movl	$0x5fb9c0, %eax         # imm = 0x5FB9C0
  58df05:      	jmp	0x591a45 <.text+0x190a45>
  58df0a:      	movl	$0x5fb9a4, %eax         # imm = 0x5FB9A4
  58df0f:      	jmp	0x591a45 <.text+0x190a45>
  58df14:      	movl	$0x5fb984, %eax         # imm = 0x5FB984
  58df19:      	jmp	0x591a45 <.text+0x190a45>
  58df1e:      	movl	$0x5fb964, %eax         # imm = 0x5FB964
  58df23:      	jmp	0x591a45 <.text+0x190a45>
  58df28:      	movl	$0x5fb944, %eax         # imm = 0x5FB944
  58df2d:      	jmp	0x591a45 <.text+0x190a45>
  58df32:      	movl	$0x5fb924, %eax         # imm = 0x5FB924
  58df37:      	jmp	0x591a45 <.text+0x190a45>
  58df3c:      	movl	$0x5fb900, %eax         # imm = 0x5FB900
  58df41:      	jmp	0x591a45 <.text+0x190a45>
  58df46:      	movl	$0x5fb8e8, %eax         # imm = 0x5FB8E8
  58df4b:      	jmp	0x591a45 <.text+0x190a45>
  58df50:      	movl	$0x8ca, %ecx            # imm = 0x8CA
  58df55:      	cmpl	%ecx, %eax
  58df57:      	jg	0x58e639 <.text+0x18d639>
  58df5d:      	je	0x58e62f <.text+0x18d62f>
  58df63:      	addl	$0xfffff94e, %eax       # imm = 0xFFFFF94E
  58df68:      	cmpl	$0x1e8, %eax            # imm = 0x1E8
  58df6d:      	ja	0x591a16 <.text+0x190a16>
  58df73:      	movzbl	0x596675(%eax), %eax
  58df7a:      	jmpl	*0x5963c5(,%eax,4)
  58df81:      	movl	$0x5fb8c8, %eax         # imm = 0x5FB8C8
  58df86:      	jmp	0x591a45 <.text+0x190a45>
  58df8b:      	movl	$0x5fb8b4, %eax         # imm = 0x5FB8B4
  58df90:      	jmp	0x591a45 <.text+0x190a45>
  58df95:      	movl	$0x5fb89c, %eax         # imm = 0x5FB89C
  58df9a:      	jmp	0x591a45 <.text+0x190a45>
  58df9f:      	movl	$0x5fb888, %eax         # imm = 0x5FB888
  58dfa4:      	jmp	0x591a45 <.text+0x190a45>
  58dfa9:      	movl	$0x5fb874, %eax         # imm = 0x5FB874
  58dfae:      	jmp	0x591a45 <.text+0x190a45>
  58dfb3:      	movl	$0x5fb860, %eax         # imm = 0x5FB860
  58dfb8:      	jmp	0x591a45 <.text+0x190a45>
  58dfbd:      	movl	$0x5fb844, %eax         # imm = 0x5FB844
  58dfc2:      	jmp	0x591a45 <.text+0x190a45>
  58dfc7:      	movl	$0x5fb82c, %eax         # imm = 0x5FB82C
  58dfcc:      	jmp	0x591a45 <.text+0x190a45>
  58dfd1:      	movl	$0x5fb810, %eax         # imm = 0x5FB810
  58dfd6:      	jmp	0x591a45 <.text+0x190a45>
  58dfdb:      	movl	$0x5fb7f8, %eax         # imm = 0x5FB7F8
  58dfe0:      	jmp	0x591a45 <.text+0x190a45>
  58dfe5:      	movl	$0x5fb7d8, %eax         # imm = 0x5FB7D8
  58dfea:      	jmp	0x591a45 <.text+0x190a45>
  58dfef:      	movl	$0x5fb7c0, %eax         # imm = 0x5FB7C0
  58dff4:      	jmp	0x591a45 <.text+0x190a45>
  58dff9:      	movl	$0x5fb7ac, %eax         # imm = 0x5FB7AC
  58dffe:      	jmp	0x591a45 <.text+0x190a45>
  58e003:      	movl	$0x5fb794, %eax         # imm = 0x5FB794
  58e008:      	jmp	0x591a45 <.text+0x190a45>
  58e00d:      	movl	$0x5fb77c, %eax         # imm = 0x5FB77C
  58e012:      	jmp	0x591a45 <.text+0x190a45>
  58e017:      	movl	$0x5fb760, %eax         # imm = 0x5FB760
  58e01c:      	jmp	0x591a45 <.text+0x190a45>
  58e021:      	movl	$0x5fb748, %eax         # imm = 0x5FB748
  58e026:      	jmp	0x591a45 <.text+0x190a45>
  58e02b:      	movl	$0x5fb734, %eax         # imm = 0x5FB734
  58e030:      	jmp	0x591a45 <.text+0x190a45>
  58e035:      	movl	$0x5fb720, %eax         # imm = 0x5FB720
  58e03a:      	jmp	0x591a45 <.text+0x190a45>
  58e03f:      	movl	$0x5fb70c, %eax         # imm = 0x5FB70C
  58e044:      	jmp	0x591a45 <.text+0x190a45>
  58e049:      	movl	$0x5fb6f0, %eax         # imm = 0x5FB6F0
  58e04e:      	jmp	0x591a45 <.text+0x190a45>
  58e053:      	movl	$0x5fb6d0, %eax         # imm = 0x5FB6D0
  58e058:      	jmp	0x591a45 <.text+0x190a45>
  58e05d:      	movl	$0x5fb6b8, %eax         # imm = 0x5FB6B8
  58e062:      	jmp	0x591a45 <.text+0x190a45>
  58e067:      	movl	$0x5fb69c, %eax         # imm = 0x5FB69C
  58e06c:      	jmp	0x591a45 <.text+0x190a45>
  58e071:      	movl	$0x5fb680, %eax         # imm = 0x5FB680
  58e076:      	jmp	0x591a45 <.text+0x190a45>
  58e07b:      	movl	$0x5fb664, %eax         # imm = 0x5FB664
  58e080:      	jmp	0x591a45 <.text+0x190a45>
  58e085:      	movl	$0x5fb64c, %eax         # imm = 0x5FB64C
  58e08a:      	jmp	0x591a45 <.text+0x190a45>
  58e08f:      	movl	$0x5fb634, %eax         # imm = 0x5FB634
  58e094:      	jmp	0x591a45 <.text+0x190a45>
  58e099:      	movl	$0x5fb618, %eax         # imm = 0x5FB618
  58e09e:      	jmp	0x591a45 <.text+0x190a45>
  58e0a3:      	movl	$0x5fb5fc, %eax         # imm = 0x5FB5FC
  58e0a8:      	jmp	0x591a45 <.text+0x190a45>
  58e0ad:      	movl	$0x5fb5e0, %eax         # imm = 0x5FB5E0
  58e0b2:      	jmp	0x591a45 <.text+0x190a45>
  58e0b7:      	movl	$0x5fb5c4, %eax         # imm = 0x5FB5C4
  58e0bc:      	jmp	0x591a45 <.text+0x190a45>
  58e0c1:      	movl	$0x5fb5a8, %eax         # imm = 0x5FB5A8
  58e0c6:      	jmp	0x591a45 <.text+0x190a45>
  58e0cb:      	movl	$0x5fb58c, %eax         # imm = 0x5FB58C
  58e0d0:      	jmp	0x591a45 <.text+0x190a45>
  58e0d5:      	movl	$0x5fb578, %eax         # imm = 0x5FB578
  58e0da:      	jmp	0x591a45 <.text+0x190a45>
  58e0df:      	movl	$0x5fb560, %eax         # imm = 0x5FB560
  58e0e4:      	jmp	0x591a45 <.text+0x190a45>
  58e0e9:      	movl	$0x5fb548, %eax         # imm = 0x5FB548
  58e0ee:      	jmp	0x591a45 <.text+0x190a45>
  58e0f3:      	movl	$0x5fb530, %eax         # imm = 0x5FB530
  58e0f8:      	jmp	0x591a45 <.text+0x190a45>
  58e0fd:      	movl	$0x5fb518, %eax         # imm = 0x5FB518
  58e102:      	jmp	0x591a45 <.text+0x190a45>
  58e107:      	movl	$0x5fb4fc, %eax         # imm = 0x5FB4FC
  58e10c:      	jmp	0x591a45 <.text+0x190a45>
  58e111:      	movl	$0x5fb4e4, %eax         # imm = 0x5FB4E4
  58e116:      	jmp	0x591a45 <.text+0x190a45>
  58e11b:      	movl	$0x5fb4c4, %eax         # imm = 0x5FB4C4
  58e120:      	jmp	0x591a45 <.text+0x190a45>
  58e125:      	movl	$0x5fb4a8, %eax         # imm = 0x5FB4A8
  58e12a:      	jmp	0x591a45 <.text+0x190a45>
  58e12f:      	movl	$0x5fb48c, %eax         # imm = 0x5FB48C
  58e134:      	jmp	0x591a45 <.text+0x190a45>
  58e139:      	movl	$0x5fb474, %eax         # imm = 0x5FB474
  58e13e:      	jmp	0x591a45 <.text+0x190a45>
  58e143:      	movl	$0x5fb454, %eax         # imm = 0x5FB454
  58e148:      	jmp	0x591a45 <.text+0x190a45>
  58e14d:      	movl	$0x5fb43c, %eax         # imm = 0x5FB43C
  58e152:      	jmp	0x591a45 <.text+0x190a45>
  58e157:      	movl	$0x5fb424, %eax         # imm = 0x5FB424
  58e15c:      	jmp	0x591a45 <.text+0x190a45>
  58e161:      	movl	$0x5fb408, %eax         # imm = 0x5FB408
  58e166:      	jmp	0x591a45 <.text+0x190a45>
  58e16b:      	movl	$0x5fb3f0, %eax         # imm = 0x5FB3F0
  58e170:      	jmp	0x591a45 <.text+0x190a45>
  58e175:      	movl	$0x5fb3dc, %eax         # imm = 0x5FB3DC
  58e17a:      	jmp	0x591a45 <.text+0x190a45>
  58e17f:      	movl	$0x5fb3c8, %eax         # imm = 0x5FB3C8
  58e184:      	jmp	0x591a45 <.text+0x190a45>
  58e189:      	movl	$0x5fb3b4, %eax         # imm = 0x5FB3B4
  58e18e:      	jmp	0x591a45 <.text+0x190a45>
  58e193:      	movl	$0x5fb3a0, %eax         # imm = 0x5FB3A0
  58e198:      	jmp	0x591a45 <.text+0x190a45>
  58e19d:      	movl	$0x5fb38c, %eax         # imm = 0x5FB38C
  58e1a2:      	jmp	0x591a45 <.text+0x190a45>
  58e1a7:      	movl	$0x5fb374, %eax         # imm = 0x5FB374
  58e1ac:      	jmp	0x591a45 <.text+0x190a45>
  58e1b1:      	movl	$0x5fb354, %eax         # imm = 0x5FB354
  58e1b6:      	jmp	0x591a45 <.text+0x190a45>
  58e1bb:      	movl	$0x5fb334, %eax         # imm = 0x5FB334
  58e1c0:      	jmp	0x591a45 <.text+0x190a45>
  58e1c5:      	movl	$0x5fb318, %eax         # imm = 0x5FB318
  58e1ca:      	jmp	0x591a45 <.text+0x190a45>
  58e1cf:      	movl	$0x5fb2fc, %eax         # imm = 0x5FB2FC
  58e1d4:      	jmp	0x591a45 <.text+0x190a45>
  58e1d9:      	movl	$0x5fb2e0, %eax         # imm = 0x5FB2E0
  58e1de:      	jmp	0x591a45 <.text+0x190a45>
  58e1e3:      	movl	$0x5fb2c0, %eax         # imm = 0x5FB2C0
  58e1e8:      	jmp	0x591a45 <.text+0x190a45>
  58e1ed:      	movl	$0x5fb2a8, %eax         # imm = 0x5FB2A8
  58e1f2:      	jmp	0x591a45 <.text+0x190a45>
  58e1f7:      	movl	$0x5fb288, %eax         # imm = 0x5FB288
  58e1fc:      	jmp	0x591a45 <.text+0x190a45>
  58e201:      	movl	$0x5fb26c, %eax         # imm = 0x5FB26C
  58e206:      	jmp	0x591a45 <.text+0x190a45>
  58e20b:      	movl	$0x5fb258, %eax         # imm = 0x5FB258
  58e210:      	jmp	0x591a45 <.text+0x190a45>
  58e215:      	movl	$0x5fb23c, %eax         # imm = 0x5FB23C
  58e21a:      	jmp	0x591a45 <.text+0x190a45>
  58e21f:      	movl	$0x5fb220, %eax         # imm = 0x5FB220
  58e224:      	jmp	0x591a45 <.text+0x190a45>
  58e229:      	movl	$0x5fb204, %eax         # imm = 0x5FB204
  58e22e:      	jmp	0x591a45 <.text+0x190a45>
  58e233:      	movl	$0x5fb1e8, %eax         # imm = 0x5FB1E8
  58e238:      	jmp	0x591a45 <.text+0x190a45>
  58e23d:      	movl	$0x5fb1c8, %eax         # imm = 0x5FB1C8
  58e242:      	jmp	0x591a45 <.text+0x190a45>
  58e247:      	movl	$0x5fb1a4, %eax         # imm = 0x5FB1A4
  58e24c:      	jmp	0x591a45 <.text+0x190a45>
  58e251:      	movl	$0x5fb190, %eax         # imm = 0x5FB190
  58e256:      	jmp	0x591a45 <.text+0x190a45>
  58e25b:      	movl	$0x5fb178, %eax         # imm = 0x5FB178
  58e260:      	jmp	0x591a45 <.text+0x190a45>
  58e265:      	movl	$0x5fb15c, %eax         # imm = 0x5FB15C
  58e26a:      	jmp	0x591a45 <.text+0x190a45>
  58e26f:      	movl	$0x5fb144, %eax         # imm = 0x5FB144
  58e274:      	jmp	0x591a45 <.text+0x190a45>
  58e279:      	movl	$0x5fb120, %eax         # imm = 0x5FB120
  58e27e:      	jmp	0x591a45 <.text+0x190a45>
  58e283:      	movl	$0x5fb0f8, %eax         # imm = 0x5FB0F8
  58e288:      	jmp	0x591a45 <.text+0x190a45>
  58e28d:      	movl	$0x5fb0e4, %eax         # imm = 0x5FB0E4
  58e292:      	jmp	0x591a45 <.text+0x190a45>
  58e297:      	movl	$0x5fb0c4, %eax         # imm = 0x5FB0C4
  58e29c:      	jmp	0x591a45 <.text+0x190a45>
  58e2a1:      	movl	$0x5fb0a4, %eax         # imm = 0x5FB0A4
  58e2a6:      	jmp	0x591a45 <.text+0x190a45>
  58e2ab:      	movl	$0x5fb084, %eax         # imm = 0x5FB084
  58e2b0:      	jmp	0x591a45 <.text+0x190a45>
  58e2b5:      	movl	$0x5fb06c, %eax         # imm = 0x5FB06C
  58e2ba:      	jmp	0x591a45 <.text+0x190a45>
  58e2bf:      	movl	$0x5fb050, %eax         # imm = 0x5FB050
  58e2c4:      	jmp	0x591a45 <.text+0x190a45>
  58e2c9:      	movl	$0x5fb030, %eax         # imm = 0x5FB030
  58e2ce:      	jmp	0x591a45 <.text+0x190a45>
  58e2d3:      	movl	$0x5fb010, %eax         # imm = 0x5FB010
  58e2d8:      	jmp	0x591a45 <.text+0x190a45>
  58e2dd:      	movl	$0x5faff8, %eax         # imm = 0x5FAFF8
  58e2e2:      	jmp	0x591a45 <.text+0x190a45>
  58e2e7:      	movl	$0x5fafdc, %eax         # imm = 0x5FAFDC
  58e2ec:      	jmp	0x591a45 <.text+0x190a45>
  58e2f1:      	movl	$0x5fafc4, %eax         # imm = 0x5FAFC4
  58e2f6:      	jmp	0x591a45 <.text+0x190a45>
  58e2fb:      	movl	$0x5faf9c, %eax         # imm = 0x5FAF9C
  58e300:      	jmp	0x591a45 <.text+0x190a45>
  58e305:      	movl	$0x5faf74, %eax         # imm = 0x5FAF74
  58e30a:      	jmp	0x591a45 <.text+0x190a45>
  58e30f:      	movl	$0x5faf50, %eax         # imm = 0x5FAF50
  58e314:      	jmp	0x591a45 <.text+0x190a45>
  58e319:      	movl	$0x5faf30, %eax         # imm = 0x5FAF30
  58e31e:      	jmp	0x591a45 <.text+0x190a45>
  58e323:      	movl	$0x5faf10, %eax         # imm = 0x5FAF10
  58e328:      	jmp	0x591a45 <.text+0x190a45>
  58e32d:      	movl	$0x5faef0, %eax         # imm = 0x5FAEF0
  58e332:      	jmp	0x591a45 <.text+0x190a45>
  58e337:      	movl	$0x5faed0, %eax         # imm = 0x5FAED0
  58e33c:      	jmp	0x591a45 <.text+0x190a45>
  58e341:      	movl	$0x5faeb0, %eax         # imm = 0x5FAEB0
  58e346:      	jmp	0x591a45 <.text+0x190a45>
  58e34b:      	movl	$0x5fae90, %eax         # imm = 0x5FAE90
  58e350:      	jmp	0x591a45 <.text+0x190a45>
  58e355:      	movl	$0x5fae78, %eax         # imm = 0x5FAE78
  58e35a:      	jmp	0x591a45 <.text+0x190a45>
  58e35f:      	movl	$0x5fae64, %eax         # imm = 0x5FAE64
  58e364:      	jmp	0x591a45 <.text+0x190a45>
  58e369:      	movl	$0x5fae4c, %eax         # imm = 0x5FAE4C
  58e36e:      	jmp	0x591a45 <.text+0x190a45>
  58e373:      	movl	$0x5fae30, %eax         # imm = 0x5FAE30
  58e378:      	jmp	0x591a45 <.text+0x190a45>
  58e37d:      	movl	$0x5fae1c, %eax         # imm = 0x5FAE1C
  58e382:      	jmp	0x591a45 <.text+0x190a45>
  58e387:      	movl	$0x5fadfc, %eax         # imm = 0x5FADFC
  58e38c:      	jmp	0x591a45 <.text+0x190a45>
  58e391:      	movl	$0x5fade8, %eax         # imm = 0x5FADE8
  58e396:      	jmp	0x591a45 <.text+0x190a45>
  58e39b:      	movl	$0x5fadd4, %eax         # imm = 0x5FADD4
  58e3a0:      	jmp	0x591a45 <.text+0x190a45>
  58e3a5:      	movl	$0x5fadbc, %eax         # imm = 0x5FADBC
  58e3aa:      	jmp	0x591a45 <.text+0x190a45>
  58e3af:      	movl	$0x5fada8, %eax         # imm = 0x5FADA8
  58e3b4:      	jmp	0x591a45 <.text+0x190a45>
  58e3b9:      	movl	$0x5fad94, %eax         # imm = 0x5FAD94
  58e3be:      	jmp	0x591a45 <.text+0x190a45>
  58e3c3:      	movl	$0x5fad7c, %eax         # imm = 0x5FAD7C
  58e3c8:      	jmp	0x591a45 <.text+0x190a45>
  58e3cd:      	movl	$0x5fad64, %eax         # imm = 0x5FAD64
  58e3d2:      	jmp	0x591a45 <.text+0x190a45>
  58e3d7:      	movl	$0x5fad48, %eax         # imm = 0x5FAD48
  58e3dc:      	jmp	0x591a45 <.text+0x190a45>
  58e3e1:      	movl	$0x5fad2c, %eax         # imm = 0x5FAD2C
  58e3e6:      	jmp	0x591a45 <.text+0x190a45>
  58e3eb:      	movl	$0x5fad14, %eax         # imm = 0x5FAD14
  58e3f0:      	jmp	0x591a45 <.text+0x190a45>
  58e3f5:      	movl	$0x5facf8, %eax         # imm = 0x5FACF8
  58e3fa:      	jmp	0x591a45 <.text+0x190a45>
  58e3ff:      	movl	$0x5facd8, %eax         # imm = 0x5FACD8
  58e404:      	jmp	0x591a45 <.text+0x190a45>
  58e409:      	movl	$0x5facc4, %eax         # imm = 0x5FACC4
  58e40e:      	jmp	0x591a45 <.text+0x190a45>
  58e413:      	movl	$0x5facac, %eax         # imm = 0x5FACAC
  58e418:      	jmp	0x591a45 <.text+0x190a45>
  58e41d:      	movl	$0x5fac98, %eax         # imm = 0x5FAC98
  58e422:      	jmp	0x591a45 <.text+0x190a45>
  58e427:      	movl	$0x5fac80, %eax         # imm = 0x5FAC80
  58e42c:      	jmp	0x591a45 <.text+0x190a45>
  58e431:      	movl	$0x5fac68, %eax         # imm = 0x5FAC68
  58e436:      	jmp	0x591a45 <.text+0x190a45>
  58e43b:      	movl	$0x5fac50, %eax         # imm = 0x5FAC50
  58e440:      	jmp	0x591a45 <.text+0x190a45>
  58e445:      	movl	$0x5fac38, %eax         # imm = 0x5FAC38
  58e44a:      	jmp	0x591a45 <.text+0x190a45>
  58e44f:      	movl	$0x5fac1c, %eax         # imm = 0x5FAC1C
  58e454:      	jmp	0x591a45 <.text+0x190a45>
  58e459:      	movl	$0x5fac00, %eax         # imm = 0x5FAC00
  58e45e:      	jmp	0x591a45 <.text+0x190a45>
  58e463:      	movl	$0x5fabdc, %eax         # imm = 0x5FABDC
  58e468:      	jmp	0x591a45 <.text+0x190a45>
  58e46d:      	movl	$0x5fabc0, %eax         # imm = 0x5FABC0
  58e472:      	jmp	0x591a45 <.text+0x190a45>
  58e477:      	movl	$0x5fabb0, %eax         # imm = 0x5FABB0
  58e47c:      	jmp	0x591a45 <.text+0x190a45>
  58e481:      	movl	$0x5faba0, %eax         # imm = 0x5FABA0
  58e486:      	jmp	0x591a45 <.text+0x190a45>
  58e48b:      	movl	$0x5fab90, %eax         # imm = 0x5FAB90
  58e490:      	jmp	0x591a45 <.text+0x190a45>
  58e495:      	movl	$0x5fab78, %eax         # imm = 0x5FAB78
  58e49a:      	jmp	0x591a45 <.text+0x190a45>
  58e49f:      	movl	$0x5fab5c, %eax         # imm = 0x5FAB5C
  58e4a4:      	jmp	0x591a45 <.text+0x190a45>
  58e4a9:      	movl	$0x5fab40, %eax         # imm = 0x5FAB40
  58e4ae:      	jmp	0x591a45 <.text+0x190a45>
  58e4b3:      	movl	$0x5fab2c, %eax         # imm = 0x5FAB2C
  58e4b8:      	jmp	0x591a45 <.text+0x190a45>
  58e4bd:      	movl	$0x5fab10, %eax         # imm = 0x5FAB10
  58e4c2:      	jmp	0x591a45 <.text+0x190a45>
  58e4c7:      	movl	$0x5faafc, %eax         # imm = 0x5FAAFC
  58e4cc:      	jmp	0x591a45 <.text+0x190a45>
  58e4d1:      	movl	$0x5faae8, %eax         # imm = 0x5FAAE8
  58e4d6:      	jmp	0x591a45 <.text+0x190a45>
  58e4db:      	movl	$0x5faad0, %eax         # imm = 0x5FAAD0
  58e4e0:      	jmp	0x591a45 <.text+0x190a45>
  58e4e5:      	movl	$0x5faab4, %eax         # imm = 0x5FAAB4
  58e4ea:      	jmp	0x591a45 <.text+0x190a45>
  58e4ef:      	movl	$0x5faa98, %eax         # imm = 0x5FAA98
  58e4f4:      	jmp	0x591a45 <.text+0x190a45>
  58e4f9:      	movl	$0x5faa84, %eax         # imm = 0x5FAA84
  58e4fe:      	jmp	0x591a45 <.text+0x190a45>
  58e503:      	movl	$0x5faa68, %eax         # imm = 0x5FAA68
  58e508:      	jmp	0x591a45 <.text+0x190a45>
  58e50d:      	movl	$0x5faa48, %eax         # imm = 0x5FAA48
  58e512:      	jmp	0x591a45 <.text+0x190a45>
  58e517:      	movl	$0x5faa28, %eax         # imm = 0x5FAA28
  58e51c:      	jmp	0x591a45 <.text+0x190a45>
  58e521:      	movl	$0x5faa08, %eax         # imm = 0x5FAA08
  58e526:      	jmp	0x591a45 <.text+0x190a45>
  58e52b:      	movl	$0x5fa9f4, %eax         # imm = 0x5FA9F4
  58e530:      	jmp	0x591a45 <.text+0x190a45>
  58e535:      	movl	$0x5fa9dc, %eax         # imm = 0x5FA9DC
  58e53a:      	jmp	0x591a45 <.text+0x190a45>
  58e53f:      	movl	$0x5fa9c8, %eax         # imm = 0x5FA9C8
  58e544:      	jmp	0x591a45 <.text+0x190a45>
  58e549:      	movl	$0x5fa9b0, %eax         # imm = 0x5FA9B0
  58e54e:      	jmp	0x591a45 <.text+0x190a45>
  58e553:      	movl	$0x5fa99c, %eax         # imm = 0x5FA99C
  58e558:      	jmp	0x591a45 <.text+0x190a45>
  58e55d:      	movl	$0x5fa970, %eax         # imm = 0x5FA970
  58e562:      	jmp	0x591a45 <.text+0x190a45>
  58e567:      	movl	$0x5fa958, %eax         # imm = 0x5FA958
  58e56c:      	jmp	0x591a45 <.text+0x190a45>
  58e571:      	movl	$0x5fa93c, %eax         # imm = 0x5FA93C
  58e576:      	jmp	0x591a45 <.text+0x190a45>
  58e57b:      	movl	$0x5fa924, %eax         # imm = 0x5FA924
  58e580:      	jmp	0x591a45 <.text+0x190a45>
  58e585:      	movl	$0x5fa908, %eax         # imm = 0x5FA908
  58e58a:      	jmp	0x591a45 <.text+0x190a45>
  58e58f:      	movl	$0x5fa8f0, %eax         # imm = 0x5FA8F0
  58e594:      	jmp	0x591a45 <.text+0x190a45>
  58e599:      	movl	$0x5fa8d4, %eax         # imm = 0x5FA8D4
  58e59e:      	jmp	0x591a45 <.text+0x190a45>
  58e5a3:      	movl	$0x5fa8b8, %eax         # imm = 0x5FA8B8
  58e5a8:      	jmp	0x591a45 <.text+0x190a45>
  58e5ad:      	movl	$0x5fa898, %eax         # imm = 0x5FA898
  58e5b2:      	jmp	0x591a45 <.text+0x190a45>
  58e5b7:      	movl	$0x5fa884, %eax         # imm = 0x5FA884
  58e5bc:      	jmp	0x591a45 <.text+0x190a45>
  58e5c1:      	movl	$0x5fa868, %eax         # imm = 0x5FA868
  58e5c6:      	jmp	0x591a45 <.text+0x190a45>
  58e5cb:      	movl	$0x5fa84c, %eax         # imm = 0x5FA84C
  58e5d0:      	jmp	0x591a45 <.text+0x190a45>
  58e5d5:      	movl	$0x5fa82c, %eax         # imm = 0x5FA82C
  58e5da:      	jmp	0x591a45 <.text+0x190a45>
  58e5df:      	movl	$0x5fa814, %eax         # imm = 0x5FA814
  58e5e4:      	jmp	0x591a45 <.text+0x190a45>
  58e5e9:      	movl	$0x5fa7fc, %eax         # imm = 0x5FA7FC
  58e5ee:      	jmp	0x591a45 <.text+0x190a45>
  58e5f3:      	movl	$0x5fa7e0, %eax         # imm = 0x5FA7E0
  58e5f8:      	jmp	0x591a45 <.text+0x190a45>
  58e5fd:      	movl	$0x5fa7c8, %eax         # imm = 0x5FA7C8
  58e602:      	jmp	0x591a45 <.text+0x190a45>
  58e607:      	movl	$0x5fa7ac, %eax         # imm = 0x5FA7AC
  58e60c:      	jmp	0x591a45 <.text+0x190a45>
  58e611:      	movl	$0x5fa794, %eax         # imm = 0x5FA794
  58e616:      	jmp	0x591a45 <.text+0x190a45>
  58e61b:      	movl	$0x5fa77c, %eax         # imm = 0x5FA77C
  58e620:      	jmp	0x591a45 <.text+0x190a45>
  58e625:      	movl	$0x5fa754, %eax         # imm = 0x5FA754
  58e62a:      	jmp	0x591a45 <.text+0x190a45>
  58e62f:      	movl	$0x5fa740, %eax         # imm = 0x5FA740
  58e634:      	jmp	0x591a45 <.text+0x190a45>
  58e639:      	movl	$0x2158, %ecx           # imm = 0x2158
  58e63e:      	cmpl	%ecx, %eax
  58e640:      	jg	0x59000b <.text+0x18f00b>
  58e646:      	je	0x590001 <.text+0x18f001>
  58e64c:      	movl	$0x2017, %ecx           # imm = 0x2017
  58e651:      	cmpl	%ecx, %eax
  58e653:      	jg	0x58f4fa <.text+0x18e4fa>
  58e659:      	je	0x58f4f0 <.text+0x18e4f0>
  58e65f:      	movl	$0x13ba, %ecx           # imm = 0x13BA
  58e664:      	cmpl	%ecx, %eax
  58e666:      	jg	0x58edbe <.text+0x18ddbe>
  58e66c:      	je	0x58edb4 <.text+0x18ddb4>
  58e672:      	movl	$0x10e9, %ecx           # imm = 0x10E9
  58e677:      	cmpl	%ecx, %eax
  58e679:      	jg	0x58ea40 <.text+0x18da40>
  58e67f:      	je	0x58ea36 <.text+0x18da36>
  58e685:      	addl	$-0x78, %ecx
  58e688:      	cmpl	%ecx, %eax
  58e68a:      	jg	0x58e8c6 <.text+0x18d8c6>
  58e690:      	je	0x58e8bc <.text+0x18d8bc>
  58e696:      	movl	$0xbc6, %ecx            # imm = 0xBC6
  58e69b:      	cmpl	%ecx, %eax
  58e69d:      	jg	0x58e7b8 <.text+0x18d7b8>
  58e6a3:      	je	0x58e7ae <.text+0x18d7ae>
  58e6a9:      	addl	$-0x9, %ecx
  58e6ac:      	cmpl	%ecx, %eax
  58e6ae:      	jg	0x58e749 <.text+0x18d749>
  58e6b4:      	je	0x58e73f <.text+0x18d73f>
  58e6ba:      	movl	$0xbb9, %ecx            # imm = 0xBB9
  58e6bf:      	cmpl	%ecx, %eax
  58e6c1:      	jg	0x58e710 <.text+0x18d710>
  58e6c3:      	je	0x58e706 <.text+0x18d706>
  58e6c5:      	subl	$0x961, %eax            # imm = 0x961
  58e6ca:      	je	0x58e6fc <.text+0x18d6fc>
  58e6cc:      	decl	%eax
  58e6cd:      	je	0x58e6f2 <.text+0x18d6f2>
  58e6cf:      	decl	%eax
  58e6d0:      	decl	%eax
  58e6d1:      	je	0x58e6e8 <.text+0x18d6e8>
  58e6d3:      	subl	$0x254, %eax            # imm = 0x254
  58e6d8:      	jne	0x591a16 <.text+0x190a16>
  58e6de:      	movl	$0x5fa724, %eax         # imm = 0x5FA724
  58e6e3:      	jmp	0x591a45 <.text+0x190a45>
  58e6e8:      	movl	$0x5fa710, %eax         # imm = 0x5FA710
  58e6ed:      	jmp	0x591a45 <.text+0x190a45>
  58e6f2:      	movl	$0x5fa6f4, %eax         # imm = 0x5FA6F4
  58e6f7:      	jmp	0x591a45 <.text+0x190a45>
  58e6fc:      	movl	$0x5fa6e0, %eax         # imm = 0x5FA6E0
  58e701:      	jmp	0x591a45 <.text+0x190a45>
  58e706:      	movl	$0x5fa6c4, %eax         # imm = 0x5FA6C4
  58e70b:      	jmp	0x591a45 <.text+0x190a45>
  58e710:      	subl	$0xbba, %eax            # imm = 0xBBA
  58e715:      	je	0x58e735 <.text+0x18d735>
  58e717:      	decl	%eax
  58e718:      	je	0x58e72b <.text+0x18d72b>
  58e71a:      	decl	%eax
  58e71b:      	jne	0x591a16 <.text+0x190a16>
  58e721:      	movl	$0x5fa6b0, %eax         # imm = 0x5FA6B0
  58e726:      	jmp	0x591a45 <.text+0x190a45>
  58e72b:      	movl	$0x5fa698, %eax         # imm = 0x5FA698
  58e730:      	jmp	0x591a45 <.text+0x190a45>
  58e735:      	movl	$0x5fa67c, %eax         # imm = 0x5FA67C
  58e73a:      	jmp	0x591a45 <.text+0x190a45>
  58e73f:      	movl	$0x5fa654, %eax         # imm = 0x5FA654
  58e744:      	jmp	0x591a45 <.text+0x190a45>
  58e749:      	addl	$0xfffff442, %eax       # imm = 0xFFFFF442
  58e74e:      	cmpl	$0x7, %eax
  58e751:      	ja	0x591a16 <.text+0x190a16>
  58e757:      	jmpl	*0x596861(,%eax,4)
  58e75e:      	movl	$0x5fa62c, %eax         # imm = 0x5FA62C
  58e763:      	jmp	0x591a45 <.text+0x190a45>
  58e768:      	movl	$0x5fa610, %eax         # imm = 0x5FA610
  58e76d:      	jmp	0x591a45 <.text+0x190a45>
  58e772:      	movl	$0x5fa5f4, %eax         # imm = 0x5FA5F4
  58e777:      	jmp	0x591a45 <.text+0x190a45>
  58e77c:      	movl	$0x5fa5d4, %eax         # imm = 0x5FA5D4
  58e781:      	jmp	0x591a45 <.text+0x190a45>
  58e786:      	movl	$0x5fa5b4, %eax         # imm = 0x5FA5B4
  58e78b:      	jmp	0x591a45 <.text+0x190a45>
  58e790:      	movl	$0x5fa594, %eax         # imm = 0x5FA594
  58e795:      	jmp	0x591a45 <.text+0x190a45>
  58e79a:      	movl	$0x5fa57c, %eax         # imm = 0x5FA57C
  58e79f:      	jmp	0x591a45 <.text+0x190a45>
  58e7a4:      	movl	$0x5fa560, %eax         # imm = 0x5FA560
  58e7a9:      	jmp	0x591a45 <.text+0x190a45>
  58e7ae:      	movl	$0x5fa540, %eax         # imm = 0x5FA540
  58e7b3:      	jmp	0x591a45 <.text+0x190a45>
  58e7b8:      	movl	$0x1068, %ecx           # imm = 0x1068
  58e7bd:      	cmpl	%ecx, %eax
  58e7bf:      	jg	0x58e857 <.text+0x18d857>
  58e7c5:      	je	0x58e84d <.text+0x18d84d>
  58e7cb:      	movl	$0xfa4, %ecx            # imm = 0xFA4
  58e7d0:      	cmpl	%ecx, %eax
  58e7d2:      	jg	0x58e81c <.text+0x18d81c>
  58e7d4:      	je	0x58e812 <.text+0x18d812>
  58e7d6:      	subl	$0xfa0, %eax            # imm = 0xFA0
  58e7db:      	je	0x58e808 <.text+0x18d808>
  58e7dd:      	decl	%eax
  58e7de:      	je	0x58e7fe <.text+0x18d7fe>
  58e7e0:      	decl	%eax
  58e7e1:      	je	0x58e7f4 <.text+0x18d7f4>
  58e7e3:      	decl	%eax
  58e7e4:      	jne	0x591a16 <.text+0x190a16>
  58e7ea:      	movl	$0x5fa52c, %eax         # imm = 0x5FA52C
  58e7ef:      	jmp	0x591a45 <.text+0x190a45>
  58e7f4:      	movl	$0x5fa518, %eax         # imm = 0x5FA518
  58e7f9:      	jmp	0x591a45 <.text+0x190a45>
  58e7fe:      	movl	$0x5fa4f8, %eax         # imm = 0x5FA4F8
  58e803:      	jmp	0x591a45 <.text+0x190a45>
  58e808:      	movl	$0x5fa4e4, %eax         # imm = 0x5FA4E4
  58e80d:      	jmp	0x591a45 <.text+0x190a45>
  58e812:      	movl	$0x5fa4d0, %eax         # imm = 0x5FA4D0
  58e817:      	jmp	0x591a45 <.text+0x190a45>
  58e81c:      	subl	$0xfa5, %eax            # imm = 0xFA5
  58e821:      	je	0x58e843 <.text+0x18d843>
  58e823:      	decl	%eax
  58e824:      	je	0x58e839 <.text+0x18d839>
  58e826:      	subl	$0x5e, %eax
  58e829:      	jne	0x591a16 <.text+0x190a16>
  58e82f:      	movl	$0x5fa4b4, %eax         # imm = 0x5FA4B4
  58e834:      	jmp	0x591a45 <.text+0x190a45>
  58e839:      	movl	$0x5fa49c, %eax         # imm = 0x5FA49C
  58e83e:      	jmp	0x591a45 <.text+0x190a45>
  58e843:      	movl	$0x5fa484, %eax         # imm = 0x5FA484
  58e848:      	jmp	0x591a45 <.text+0x190a45>
  58e84d:      	movl	$0x5fa468, %eax         # imm = 0x5FA468
  58e852:      	jmp	0x591a45 <.text+0x190a45>
  58e857:      	addl	$0xffffef97, %eax       # imm = 0xFFFFEF97
  58e85c:      	cmpl	$0x7, %eax
  58e85f:      	ja	0x591a16 <.text+0x190a16>
  58e865:      	jmpl	*0x596881(,%eax,4)
  58e86c:      	movl	$0x5fa448, %eax         # imm = 0x5FA448
  58e871:      	jmp	0x591a45 <.text+0x190a45>
  58e876:      	movl	$0x5fa42c, %eax         # imm = 0x5FA42C
  58e87b:      	jmp	0x591a45 <.text+0x190a45>
  58e880:      	movl	$0x5fa418, %eax         # imm = 0x5FA418
  58e885:      	jmp	0x591a45 <.text+0x190a45>
  58e88a:      	movl	$0x5fa400, %eax         # imm = 0x5FA400
  58e88f:      	jmp	0x591a45 <.text+0x190a45>
  58e894:      	movl	$0x5fa3dc, %eax         # imm = 0x5FA3DC
  58e899:      	jmp	0x591a45 <.text+0x190a45>
  58e89e:      	movl	$0x5fa3c0, %eax         # imm = 0x5FA3C0
  58e8a3:      	jmp	0x591a45 <.text+0x190a45>
  58e8a8:      	movl	$0x5fa3a4, %eax         # imm = 0x5FA3A4
  58e8ad:      	jmp	0x591a45 <.text+0x190a45>
  58e8b2:      	movl	$0x5fa384, %eax         # imm = 0x5FA384
  58e8b7:      	jmp	0x591a45 <.text+0x190a45>
  58e8bc:      	movl	$0x5fa370, %eax         # imm = 0x5FA370
  58e8c1:      	jmp	0x591a45 <.text+0x190a45>
  58e8c6:      	addl	$0xffffef8e, %eax       # imm = 0xFFFFEF8E
  58e8cb:      	cmpl	$0x76, %eax
  58e8ce:      	ja	0x591a16 <.text+0x190a16>
  58e8d4:      	movzbl	0x59692d(%eax), %eax
  58e8db:      	jmpl	*0x5968a1(,%eax,4)
  58e8e2:      	movl	$0x5fa358, %eax         # imm = 0x5FA358
  58e8e7:      	jmp	0x591a45 <.text+0x190a45>
  58e8ec:      	movl	$0x5fa33c, %eax         # imm = 0x5FA33C
  58e8f1:      	jmp	0x591a45 <.text+0x190a45>
  58e8f6:      	movl	$0x5fa320, %eax         # imm = 0x5FA320
  58e8fb:      	jmp	0x591a45 <.text+0x190a45>
  58e900:      	movl	$0x5fa30c, %eax         # imm = 0x5FA30C
  58e905:      	jmp	0x591a45 <.text+0x190a45>
  58e90a:      	movl	$0x5fa2f4, %eax         # imm = 0x5FA2F4
  58e90f:      	jmp	0x591a45 <.text+0x190a45>
  58e914:      	movl	$0x5fa2e0, %eax         # imm = 0x5FA2E0
  58e919:      	jmp	0x591a45 <.text+0x190a45>
  58e91e:      	movl	$0x5fa2c8, %eax         # imm = 0x5FA2C8
  58e923:      	jmp	0x591a45 <.text+0x190a45>
  58e928:      	movl	$0x5fa2ac, %eax         # imm = 0x5FA2AC
  58e92d:      	jmp	0x591a45 <.text+0x190a45>
  58e932:      	movl	$0x5fa290, %eax         # imm = 0x5FA290
  58e937:      	jmp	0x591a45 <.text+0x190a45>
  58e93c:      	movl	$0x5fa27c, %eax         # imm = 0x5FA27C
  58e941:      	jmp	0x591a45 <.text+0x190a45>
  58e946:      	movl	$0x5fa264, %eax         # imm = 0x5FA264
  58e94b:      	jmp	0x591a45 <.text+0x190a45>
  58e950:      	movl	$0x5fa258, %eax         # imm = 0x5FA258
  58e955:      	jmp	0x591a45 <.text+0x190a45>
  58e95a:      	movl	$0x5fa248, %eax         # imm = 0x5FA248
  58e95f:      	jmp	0x591a45 <.text+0x190a45>
  58e964:      	movl	$0x5fa230, %eax         # imm = 0x5FA230
  58e969:      	jmp	0x591a45 <.text+0x190a45>
  58e96e:      	movl	$0x5fa218, %eax         # imm = 0x5FA218
  58e973:      	jmp	0x591a45 <.text+0x190a45>
  58e978:      	movl	$0x5fa200, %eax         # imm = 0x5FA200
  58e97d:      	jmp	0x591a45 <.text+0x190a45>
  58e982:      	movl	$0x5fa1e8, %eax         # imm = 0x5FA1E8
  58e987:      	jmp	0x591a45 <.text+0x190a45>
  58e98c:      	movl	$0x5fa1d0, %eax         # imm = 0x5FA1D0
  58e991:      	jmp	0x591a45 <.text+0x190a45>
  58e996:      	movl	$0x5fa1b8, %eax         # imm = 0x5FA1B8
  58e99b:      	jmp	0x591a45 <.text+0x190a45>
  58e9a0:      	movl	$0x5fa1a4, %eax         # imm = 0x5FA1A4
  58e9a5:      	jmp	0x591a45 <.text+0x190a45>
  58e9aa:      	movl	$0x5fa188, %eax         # imm = 0x5FA188
  58e9af:      	jmp	0x591a45 <.text+0x190a45>
  58e9b4:      	movl	$0x5fa16c, %eax         # imm = 0x5FA16C
  58e9b9:      	jmp	0x591a45 <.text+0x190a45>
  58e9be:      	movl	$0x5fa154, %eax         # imm = 0x5FA154
  58e9c3:      	jmp	0x591a45 <.text+0x190a45>
  58e9c8:      	movl	$0x5fa138, %eax         # imm = 0x5FA138
  58e9cd:      	jmp	0x591a45 <.text+0x190a45>
  58e9d2:      	movl	$0x5fa11c, %eax         # imm = 0x5FA11C
  58e9d7:      	jmp	0x591a45 <.text+0x190a45>
  58e9dc:      	movl	$0x5fa104, %eax         # imm = 0x5FA104
  58e9e1:      	jmp	0x591a45 <.text+0x190a45>
  58e9e6:      	movl	$0x5fa0e8, %eax         # imm = 0x5FA0E8
  58e9eb:      	jmp	0x591a45 <.text+0x190a45>
  58e9f0:      	movl	$0x5fa0d4, %eax         # imm = 0x5FA0D4
  58e9f5:      	jmp	0x591a45 <.text+0x190a45>
  58e9fa:      	movl	$0x5fa0b8, %eax         # imm = 0x5FA0B8
  58e9ff:      	jmp	0x591a45 <.text+0x190a45>
  58ea04:      	movl	$0x5fa09c, %eax         # imm = 0x5FA09C
  58ea09:      	jmp	0x591a45 <.text+0x190a45>
  58ea0e:      	movl	$0x5fa07c, %eax         # imm = 0x5FA07C
  58ea13:      	jmp	0x591a45 <.text+0x190a45>
  58ea18:      	movl	$0x5fa05c, %eax         # imm = 0x5FA05C
  58ea1d:      	jmp	0x591a45 <.text+0x190a45>
  58ea22:      	movl	$0x5fa038, %eax         # imm = 0x5FA038
  58ea27:      	jmp	0x591a45 <.text+0x190a45>
  58ea2c:      	movl	$0x5fa020, %eax         # imm = 0x5FA020
  58ea31:      	jmp	0x591a45 <.text+0x190a45>
  58ea36:      	movl	$0x5fa004, %eax         # imm = 0x5FA004
  58ea3b:      	jmp	0x591a45 <.text+0x190a45>
  58ea40:      	movl	$0x1126, %ecx           # imm = 0x1126
  58ea45:      	cmpl	%ecx, %eax
  58ea47:      	jg	0x58eb05 <.text+0x18db05>
  58ea4d:      	je	0x58eafb <.text+0x18dafb>
  58ea53:      	addl	$0xffffef16, %eax       # imm = 0xFFFFEF16
  58ea58:      	cmpl	$0x16, %eax
  58ea5b:      	ja	0x591a16 <.text+0x190a16>
  58ea61:      	movzbl	0x5969e1(%eax), %eax
  58ea68:      	jmpl	*0x5969a5(,%eax,4)
  58ea6f:      	movl	$0x5f9fe0, %eax         # imm = 0x5F9FE0
  58ea74:      	jmp	0x591a45 <.text+0x190a45>
  58ea79:      	movl	$0x5f9fc8, %eax         # imm = 0x5F9FC8
  58ea7e:      	jmp	0x591a45 <.text+0x190a45>
  58ea83:      	movl	$0x5f9fac, %eax         # imm = 0x5F9FAC
  58ea88:      	jmp	0x591a45 <.text+0x190a45>
  58ea8d:      	movl	$0x5f9f8c, %eax         # imm = 0x5F9F8C
  58ea92:      	jmp	0x591a45 <.text+0x190a45>
  58ea97:      	movl	$0x5f9f74, %eax         # imm = 0x5F9F74
  58ea9c:      	jmp	0x591a45 <.text+0x190a45>
  58eaa1:      	movl	$0x5f9f58, %eax         # imm = 0x5F9F58
  58eaa6:      	jmp	0x591a45 <.text+0x190a45>
  58eaab:      	movl	$0x5f9f38, %eax         # imm = 0x5F9F38
  58eab0:      	jmp	0x591a45 <.text+0x190a45>
  58eab5:      	movl	$0x5f9f24, %eax         # imm = 0x5F9F24
  58eaba:      	jmp	0x591a45 <.text+0x190a45>
  58eabf:      	movl	$0x5f9f04, %eax         # imm = 0x5F9F04
  58eac4:      	jmp	0x591a45 <.text+0x190a45>
  58eac9:      	movl	$0x5f9ee0, %eax         # imm = 0x5F9EE0
  58eace:      	jmp	0x591a45 <.text+0x190a45>
  58ead3:      	movl	$0x5f9ec0, %eax         # imm = 0x5F9EC0
  58ead8:      	jmp	0x591a45 <.text+0x190a45>
  58eadd:      	movl	$0x5f9ea8, %eax         # imm = 0x5F9EA8
  58eae2:      	jmp	0x591a45 <.text+0x190a45>
  58eae7:      	movl	$0x5f9e8c, %eax         # imm = 0x5F9E8C
  58eaec:      	jmp	0x591a45 <.text+0x190a45>
  58eaf1:      	movl	$0x5f9e68, %eax         # imm = 0x5F9E68
  58eaf6:      	jmp	0x591a45 <.text+0x190a45>
  58eafb:      	movl	$0x5f9e4c, %eax         # imm = 0x5F9E4C
  58eb00:      	jmp	0x591a45 <.text+0x190a45>
  58eb05:      	movl	$0x139f, %ecx           # imm = 0x139F
  58eb0a:      	cmpl	%ecx, %eax
  58eb0c:      	jg	0x58ec9b <.text+0x18dc9b>
  58eb12:      	je	0x58ec91 <.text+0x18dc91>
  58eb18:      	addl	$-0xe, %ecx
  58eb1b:      	cmpl	%ecx, %eax
  58eb1d:      	jg	0x58ebfa <.text+0x18dbfa>
  58eb23:      	je	0x58ebf0 <.text+0x18dbf0>
  58eb29:      	movl	$0x138a, %ecx           # imm = 0x138A
  58eb2e:      	cmpl	%ecx, %eax
  58eb30:      	jg	0x58eb9a <.text+0x18db9a>
  58eb32:      	je	0x58eb90 <.text+0x18db90>
  58eb34:      	subl	$0x1127, %eax           # imm = 0x1127
  58eb39:      	je	0x58eb86 <.text+0x18db86>
  58eb3b:      	decl	%eax
  58eb3c:      	je	0x58eb7c <.text+0x18db7c>
  58eb3e:      	decl	%eax
  58eb3f:      	je	0x58eb72 <.text+0x18db72>
  58eb41:      	decl	%eax
  58eb42:      	je	0x58eb68 <.text+0x18db68>
  58eb44:      	subl	$0x6a, %eax
  58eb47:      	je	0x58eb5e <.text+0x18db5e>
  58eb49:      	subl	$0x1f5, %eax            # imm = 0x1F5
  58eb4e:      	jne	0x591a16 <.text+0x190a16>
  58eb54:      	movl	$0x5f9e2c, %eax         # imm = 0x5F9E2C
  58eb59:      	jmp	0x591a45 <.text+0x190a45>
  58eb5e:      	movl	$0x5f9e0c, %eax         # imm = 0x5F9E0C
  58eb63:      	jmp	0x591a45 <.text+0x190a45>
  58eb68:      	movl	$0x5f9df0, %eax         # imm = 0x5F9DF0
  58eb6d:      	jmp	0x591a45 <.text+0x190a45>
  58eb72:      	movl	$0x5f9dd4, %eax         # imm = 0x5F9DD4
  58eb77:      	jmp	0x591a45 <.text+0x190a45>
  58eb7c:      	movl	$0x5f9db8, %eax         # imm = 0x5F9DB8
  58eb81:      	jmp	0x591a45 <.text+0x190a45>
  58eb86:      	movl	$0x5f9d94, %eax         # imm = 0x5F9D94
  58eb8b:      	jmp	0x591a45 <.text+0x190a45>
  58eb90:      	movl	$0x5f9d78, %eax         # imm = 0x5F9D78
  58eb95:      	jmp	0x591a45 <.text+0x190a45>
  58eb9a:      	subl	$0x138b, %eax           # imm = 0x138B
  58eb9f:      	je	0x58ebe6 <.text+0x18dbe6>
  58eba1:      	decl	%eax
  58eba2:      	je	0x58ebdc <.text+0x18dbdc>
  58eba4:      	decl	%eax
  58eba5:      	je	0x58ebd2 <.text+0x18dbd2>
  58eba7:      	decl	%eax
  58eba8:      	je	0x58ebc8 <.text+0x18dbc8>
  58ebaa:      	decl	%eax
  58ebab:      	je	0x58ebbe <.text+0x18dbbe>
  58ebad:      	decl	%eax
  58ebae:      	jne	0x591a16 <.text+0x190a16>
  58ebb4:      	movl	$0x5f9d60, %eax         # imm = 0x5F9D60
  58ebb9:      	jmp	0x591a45 <.text+0x190a45>
  58ebbe:      	movl	$0x5f9d44, %eax         # imm = 0x5F9D44
  58ebc3:      	jmp	0x591a45 <.text+0x190a45>
  58ebc8:      	movl	$0x5f9d24, %eax         # imm = 0x5F9D24
  58ebcd:      	jmp	0x591a45 <.text+0x190a45>
  58ebd2:      	movl	$0x5f9d04, %eax         # imm = 0x5F9D04
  58ebd7:      	jmp	0x591a45 <.text+0x190a45>
  58ebdc:      	movl	$0x5f9ce8, %eax         # imm = 0x5F9CE8
  58ebe1:      	jmp	0x591a45 <.text+0x190a45>
  58ebe6:      	movl	$0x5f9cc8, %eax         # imm = 0x5F9CC8
  58ebeb:      	jmp	0x591a45 <.text+0x190a45>
  58ebf0:      	movl	$0x5f9ca8, %eax         # imm = 0x5F9CA8
  58ebf5:      	jmp	0x591a45 <.text+0x190a45>
  58ebfa:      	addl	$0xffffec6e, %eax       # imm = 0xFFFFEC6E
  58ebff:      	cmpl	$0xc, %eax
  58ec02:      	ja	0x591a16 <.text+0x190a16>
  58ec08:      	jmpl	*0x5969f9(,%eax,4)
  58ec0f:      	movl	$0x5f9c8c, %eax         # imm = 0x5F9C8C
  58ec14:      	jmp	0x591a45 <.text+0x190a45>
  58ec19:      	movl	$0x5f9c74, %eax         # imm = 0x5F9C74
  58ec1e:      	jmp	0x591a45 <.text+0x190a45>
  58ec23:      	movl	$0x5f9c58, %eax         # imm = 0x5F9C58
  58ec28:      	jmp	0x591a45 <.text+0x190a45>
  58ec2d:      	movl	$0x5f9c40, %eax         # imm = 0x5F9C40
  58ec32:      	jmp	0x591a45 <.text+0x190a45>
  58ec37:      	movl	$0x5f9c28, %eax         # imm = 0x5F9C28
  58ec3c:      	jmp	0x591a45 <.text+0x190a45>
  58ec41:      	movl	$0x5f9c04, %eax         # imm = 0x5F9C04
  58ec46:      	jmp	0x591a45 <.text+0x190a45>
  58ec4b:      	movl	$0x5f9be4, %eax         # imm = 0x5F9BE4
  58ec50:      	jmp	0x591a45 <.text+0x190a45>
  58ec55:      	movl	$0x5f9bc8, %eax         # imm = 0x5F9BC8
  58ec5a:      	jmp	0x591a45 <.text+0x190a45>
  58ec5f:      	movl	$0x5f9bac, %eax         # imm = 0x5F9BAC
  58ec64:      	jmp	0x591a45 <.text+0x190a45>
  58ec69:      	movl	$0x5f9b94, %eax         # imm = 0x5F9B94
  58ec6e:      	jmp	0x591a45 <.text+0x190a45>
  58ec73:      	movl	$0x5f9b7c, %eax         # imm = 0x5F9B7C
  58ec78:      	jmp	0x591a45 <.text+0x190a45>
  58ec7d:      	movl	$0x5f9b60, %eax         # imm = 0x5F9B60
  58ec82:      	jmp	0x591a45 <.text+0x190a45>
  58ec87:      	movl	$0x5f9b44, %eax         # imm = 0x5F9B44
  58ec8c:      	jmp	0x591a45 <.text+0x190a45>
  58ec91:      	movl	$0x5f9b30, %eax         # imm = 0x5F9B30
  58ec96:      	jmp	0x591a45 <.text+0x190a45>
  58ec9b:      	addl	$0xffffec60, %eax       # imm = 0xFFFFEC60
  58eca0:      	cmpl	$0x19, %eax
  58eca3:      	ja	0x591a16 <.text+0x190a16>
  58eca9:      	jmpl	*0x596a2d(,%eax,4)
  58ecb0:      	movl	$0x5f9b0c, %eax         # imm = 0x5F9B0C
  58ecb5:      	jmp	0x591a45 <.text+0x190a45>
  58ecba:      	movl	$0x5f9af4, %eax         # imm = 0x5F9AF4
  58ecbf:      	jmp	0x591a45 <.text+0x190a45>
  58ecc4:      	movl	$0x5f9ae0, %eax         # imm = 0x5F9AE0
  58ecc9:      	jmp	0x591a45 <.text+0x190a45>
  58ecce:      	movl	$0x5f9abc, %eax         # imm = 0x5F9ABC
  58ecd3:      	jmp	0x591a45 <.text+0x190a45>
  58ecd8:      	movl	$0x5f9aa0, %eax         # imm = 0x5F9AA0
  58ecdd:      	jmp	0x591a45 <.text+0x190a45>
  58ece2:      	movl	$0x5f9a84, %eax         # imm = 0x5F9A84
  58ece7:      	jmp	0x591a45 <.text+0x190a45>
  58ecec:      	movl	$0x5f9a5c, %eax         # imm = 0x5F9A5C
  58ecf1:      	jmp	0x591a45 <.text+0x190a45>
  58ecf6:      	movl	$0x5f9a38, %eax         # imm = 0x5F9A38
  58ecfb:      	jmp	0x591a45 <.text+0x190a45>
  58ed00:      	movl	$0x5f9a14, %eax         # imm = 0x5F9A14
  58ed05:      	jmp	0x591a45 <.text+0x190a45>
  58ed0a:      	movl	$0x5f99f0, %eax         # imm = 0x5F99F0
  58ed0f:      	jmp	0x591a45 <.text+0x190a45>
  58ed14:      	movl	$0x5f99d4, %eax         # imm = 0x5F99D4
  58ed19:      	jmp	0x591a45 <.text+0x190a45>
  58ed1e:      	movl	$0x5f99b8, %eax         # imm = 0x5F99B8
  58ed23:      	jmp	0x591a45 <.text+0x190a45>
  58ed28:      	movl	$0x5f999c, %eax         # imm = 0x5F999C
  58ed2d:      	jmp	0x591a45 <.text+0x190a45>
  58ed32:      	movl	$0x5f997c, %eax         # imm = 0x5F997C
  58ed37:      	jmp	0x591a45 <.text+0x190a45>
  58ed3c:      	movl	$0x5f9964, %eax         # imm = 0x5F9964
  58ed41:      	jmp	0x591a45 <.text+0x190a45>
  58ed46:      	movl	$0x5f9948, %eax         # imm = 0x5F9948
  58ed4b:      	jmp	0x591a45 <.text+0x190a45>
  58ed50:      	movl	$0x5f992c, %eax         # imm = 0x5F992C
  58ed55:      	jmp	0x591a45 <.text+0x190a45>
  58ed5a:      	movl	$0x5f990c, %eax         # imm = 0x5F990C
  58ed5f:      	jmp	0x591a45 <.text+0x190a45>
  58ed64:      	movl	$0x5f98ec, %eax         # imm = 0x5F98EC
  58ed69:      	jmp	0x591a45 <.text+0x190a45>
  58ed6e:      	movl	$0x5f98c8, %eax         # imm = 0x5F98C8
  58ed73:      	jmp	0x591a45 <.text+0x190a45>
  58ed78:      	movl	$0x5f98a8, %eax         # imm = 0x5F98A8
  58ed7d:      	jmp	0x591a45 <.text+0x190a45>
  58ed82:      	movl	$0x5f9888, %eax         # imm = 0x5F9888
  58ed87:      	jmp	0x591a45 <.text+0x190a45>
  58ed8c:      	movl	$0x5f9864, %eax         # imm = 0x5F9864
  58ed91:      	jmp	0x591a45 <.text+0x190a45>
  58ed96:      	movl	$0x5f983c, %eax         # imm = 0x5F983C
  58ed9b:      	jmp	0x591a45 <.text+0x190a45>
  58eda0:      	movl	$0x5f981c, %eax         # imm = 0x5F981C
  58eda5:      	jmp	0x591a45 <.text+0x190a45>
  58edaa:      	movl	$0x5f97f4, %eax         # imm = 0x5F97F4
  58edaf:      	jmp	0x591a45 <.text+0x190a45>
  58edb4:      	movl	$0x5f97dc, %eax         # imm = 0x5F97DC
  58edb9:      	jmp	0x591a45 <.text+0x190a45>
  58edbe:      	movl	$0x1702, %ecx           # imm = 0x1702
  58edc3:      	cmpl	%ecx, %eax
  58edc5:      	jg	0x58ef6c <.text+0x18df6c>
  58edcb:      	je	0x58ef62 <.text+0x18df62>
  58edd1:      	addl	$0xffffec45, %eax       # imm = 0xFFFFEC45
  58edd6:      	cmpl	$0x26, %eax
  58edd9:      	ja	0x591a16 <.text+0x190a16>
  58eddf:      	jmpl	*0x596a95(,%eax,4)
  58ede6:      	movl	$0x5f97bc, %eax         # imm = 0x5F97BC
  58edeb:      	jmp	0x591a45 <.text+0x190a45>
  58edf0:      	movl	$0x5f979c, %eax         # imm = 0x5F979C
  58edf5:      	jmp	0x591a45 <.text+0x190a45>
  58edfa:      	movl	$0x5f9778, %eax         # imm = 0x5F9778
  58edff:      	jmp	0x591a45 <.text+0x190a45>
  58ee04:      	movl	$0x5f9758, %eax         # imm = 0x5F9758
  58ee09:      	jmp	0x591a45 <.text+0x190a45>
  58ee0e:      	movl	$0x5f9740, %eax         # imm = 0x5F9740
  58ee13:      	jmp	0x591a45 <.text+0x190a45>
  58ee18:      	movl	$0x5f9724, %eax         # imm = 0x5F9724
  58ee1d:      	jmp	0x591a45 <.text+0x190a45>
  58ee22:      	movl	$0x5f9704, %eax         # imm = 0x5F9704
  58ee27:      	jmp	0x591a45 <.text+0x190a45>
  58ee2c:      	movl	$0x5f96e0, %eax         # imm = 0x5F96E0
  58ee31:      	jmp	0x591a45 <.text+0x190a45>
  58ee36:      	movl	$0x5f96bc, %eax         # imm = 0x5F96BC
  58ee3b:      	jmp	0x591a45 <.text+0x190a45>
  58ee40:      	movl	$0x5f969c, %eax         # imm = 0x5F969C
  58ee45:      	jmp	0x591a45 <.text+0x190a45>
  58ee4a:      	movl	$0x5f967c, %eax         # imm = 0x5F967C
  58ee4f:      	jmp	0x591a45 <.text+0x190a45>
  58ee54:      	movl	$0x5f9654, %eax         # imm = 0x5F9654
  58ee59:      	jmp	0x591a45 <.text+0x190a45>
  58ee5e:      	movl	$0x5f962c, %eax         # imm = 0x5F962C
  58ee63:      	jmp	0x591a45 <.text+0x190a45>
  58ee68:      	movl	$0x5f9608, %eax         # imm = 0x5F9608
  58ee6d:      	jmp	0x591a45 <.text+0x190a45>
  58ee72:      	movl	$0x5f95e4, %eax         # imm = 0x5F95E4
  58ee77:      	jmp	0x591a45 <.text+0x190a45>
  58ee7c:      	movl	$0x5f95bc, %eax         # imm = 0x5F95BC
  58ee81:      	jmp	0x591a45 <.text+0x190a45>
  58ee86:      	movl	$0x5f9598, %eax         # imm = 0x5F9598
  58ee8b:      	jmp	0x591a45 <.text+0x190a45>
  58ee90:      	movl	$0x5f9578, %eax         # imm = 0x5F9578
  58ee95:      	jmp	0x591a45 <.text+0x190a45>
  58ee9a:      	movl	$0x5f955c, %eax         # imm = 0x5F955C
  58ee9f:      	jmp	0x591a45 <.text+0x190a45>
  58eea4:      	movl	$0x5f953c, %eax         # imm = 0x5F953C
  58eea9:      	jmp	0x591a45 <.text+0x190a45>
  58eeae:      	movl	$0x5f951c, %eax         # imm = 0x5F951C
  58eeb3:      	jmp	0x591a45 <.text+0x190a45>
  58eeb8:      	movl	$0x5f94f8, %eax         # imm = 0x5F94F8
  58eebd:      	jmp	0x591a45 <.text+0x190a45>
  58eec2:      	movl	$0x5f94dc, %eax         # imm = 0x5F94DC
  58eec7:      	jmp	0x591a45 <.text+0x190a45>
  58eecc:      	movl	$0x5f94b8, %eax         # imm = 0x5F94B8
  58eed1:      	jmp	0x591a45 <.text+0x190a45>
  58eed6:      	movl	$0x5f948c, %eax         # imm = 0x5F948C
  58eedb:      	jmp	0x591a45 <.text+0x190a45>
  58eee0:      	movl	$0x5f9468, %eax         # imm = 0x5F9468
  58eee5:      	jmp	0x591a45 <.text+0x190a45>
  58eeea:      	movl	$0x5f9440, %eax         # imm = 0x5F9440
  58eeef:      	jmp	0x591a45 <.text+0x190a45>
  58eef4:      	movl	$0x5f941c, %eax         # imm = 0x5F941C
  58eef9:      	jmp	0x591a45 <.text+0x190a45>
  58eefe:      	movl	$0x5f93fc, %eax         # imm = 0x5F93FC
  58ef03:      	jmp	0x591a45 <.text+0x190a45>
  58ef08:      	movl	$0x5f93d0, %eax         # imm = 0x5F93D0
  58ef0d:      	jmp	0x591a45 <.text+0x190a45>
  58ef12:      	movl	$0x5f93ac, %eax         # imm = 0x5F93AC
  58ef17:      	jmp	0x591a45 <.text+0x190a45>
  58ef1c:      	movl	$0x5f9388, %eax         # imm = 0x5F9388
  58ef21:      	jmp	0x591a45 <.text+0x190a45>
  58ef26:      	movl	$0x5f936c, %eax         # imm = 0x5F936C
  58ef2b:      	jmp	0x591a45 <.text+0x190a45>
  58ef30:      	movl	$0x5f934c, %eax         # imm = 0x5F934C
  58ef35:      	jmp	0x591a45 <.text+0x190a45>
  58ef3a:      	movl	$0x5f9330, %eax         # imm = 0x5F9330
  58ef3f:      	jmp	0x591a45 <.text+0x190a45>
  58ef44:      	movl	$0x5f9310, %eax         # imm = 0x5F9310
  58ef49:      	jmp	0x591a45 <.text+0x190a45>
  58ef4e:      	movl	$0x5f92e8, %eax         # imm = 0x5F92E8
  58ef53:      	jmp	0x591a45 <.text+0x190a45>
  58ef58:      	movl	$0x5f92c0, %eax         # imm = 0x5F92C0
  58ef5d:      	jmp	0x591a45 <.text+0x190a45>
  58ef62:      	movl	$0x5f9298, %eax         # imm = 0x5F9298
  58ef67:      	jmp	0x591a45 <.text+0x190a45>
  58ef6c:      	movl	$0x1770, %ecx           # imm = 0x1770
  58ef71:      	cmpl	%ecx, %eax
  58ef73:      	jg	0x58effe <.text+0x18dffe>
  58ef79:      	je	0x58eff4 <.text+0x18dff4>
  58ef7b:      	addl	$0xffffe8fd, %eax       # imm = 0xFFFFE8FD
  58ef80:      	cmpl	$0x9, %eax
  58ef83:      	ja	0x591a16 <.text+0x190a16>
  58ef89:      	jmpl	*0x596b31(,%eax,4)
  58ef90:      	movl	$0x5f9274, %eax         # imm = 0x5F9274
  58ef95:      	jmp	0x591a45 <.text+0x190a45>
  58ef9a:      	movl	$0x5f9254, %eax         # imm = 0x5F9254
  58ef9f:      	jmp	0x591a45 <.text+0x190a45>
  58efa4:      	movl	$0x5f9230, %eax         # imm = 0x5F9230
  58efa9:      	jmp	0x591a45 <.text+0x190a45>
  58efae:      	movl	$0x5f9208, %eax         # imm = 0x5F9208
  58efb3:      	jmp	0x591a45 <.text+0x190a45>
  58efb8:      	movl	$0x5f91dc, %eax         # imm = 0x5F91DC
  58efbd:      	jmp	0x591a45 <.text+0x190a45>
  58efc2:      	movl	$0x5f91b8, %eax         # imm = 0x5F91B8
  58efc7:      	jmp	0x591a45 <.text+0x190a45>
  58efcc:      	movl	$0x5f9194, %eax         # imm = 0x5F9194
  58efd1:      	jmp	0x591a45 <.text+0x190a45>
  58efd6:      	movl	$0x5f9174, %eax         # imm = 0x5F9174
  58efdb:      	jmp	0x591a45 <.text+0x190a45>
  58efe0:      	movl	$0x5f9154, %eax         # imm = 0x5F9154
  58efe5:      	jmp	0x591a45 <.text+0x190a45>
  58efea:      	movl	$0x5f9128, %eax         # imm = 0x5F9128
  58efef:      	jmp	0x591a45 <.text+0x190a45>
  58eff4:      	movl	$0x5f9110, %eax         # imm = 0x5F9110
  58eff9:      	jmp	0x591a45 <.text+0x190a45>
  58effe:      	movl	$0x17e6, %ecx           # imm = 0x17E6
  58f003:      	cmpl	%ecx, %eax
  58f005:      	jg	0x58f0d0 <.text+0x18e0d0>
  58f00b:      	je	0x58f0c6 <.text+0x18e0c6>
  58f011:      	addl	$0xffffe88f, %eax       # imm = 0xFFFFE88F
  58f016:      	cmpl	$0xf, %eax
  58f019:      	ja	0x591a16 <.text+0x190a16>
  58f01f:      	jmpl	*0x596b59(,%eax,4)
  58f026:      	movl	$0x5f90f8, %eax         # imm = 0x5F90F8
  58f02b:      	jmp	0x591a45 <.text+0x190a45>
  58f030:      	movl	$0x5f90e0, %eax         # imm = 0x5F90E0
  58f035:      	jmp	0x591a45 <.text+0x190a45>
  58f03a:      	movl	$0x5f90c4, %eax         # imm = 0x5F90C4
  58f03f:      	jmp	0x591a45 <.text+0x190a45>
  58f044:      	movl	$0x5f90b4, %eax         # imm = 0x5F90B4
  58f049:      	jmp	0x591a45 <.text+0x190a45>
  58f04e:      	movl	$0x5f90a4, %eax         # imm = 0x5F90A4
  58f053:      	jmp	0x591a45 <.text+0x190a45>
  58f058:      	movl	$0x5f9090, %eax         # imm = 0x5F9090
  58f05d:      	jmp	0x591a45 <.text+0x190a45>
  58f062:      	movl	$0x5f9074, %eax         # imm = 0x5F9074
  58f067:      	jmp	0x591a45 <.text+0x190a45>
  58f06c:      	movl	$0x5f905c, %eax         # imm = 0x5F905C
  58f071:      	jmp	0x591a45 <.text+0x190a45>
  58f076:      	movl	$0x5f9044, %eax         # imm = 0x5F9044
  58f07b:      	jmp	0x591a45 <.text+0x190a45>
  58f080:      	movl	$0x5f9028, %eax         # imm = 0x5F9028
  58f085:      	jmp	0x591a45 <.text+0x190a45>
  58f08a:      	movl	$0x5f9008, %eax         # imm = 0x5F9008
  58f08f:      	jmp	0x591a45 <.text+0x190a45>
  58f094:      	movl	$0x5f8fec, %eax         # imm = 0x5F8FEC
  58f099:      	jmp	0x591a45 <.text+0x190a45>
  58f09e:      	movl	$0x5f8fd0, %eax         # imm = 0x5F8FD0
  58f0a3:      	jmp	0x591a45 <.text+0x190a45>
  58f0a8:      	movl	$0x5f8fb0, %eax         # imm = 0x5F8FB0
  58f0ad:      	jmp	0x591a45 <.text+0x190a45>
  58f0b2:      	movl	$0x5f8f9c, %eax         # imm = 0x5F8F9C
  58f0b7:      	jmp	0x591a45 <.text+0x190a45>
  58f0bc:      	movl	$0x5f8f7c, %eax         # imm = 0x5F8F7C
  58f0c1:      	jmp	0x591a45 <.text+0x190a45>
  58f0c6:      	movl	$0x5f8f5c, %eax         # imm = 0x5F8F5C
  58f0cb:      	jmp	0x591a45 <.text+0x190a45>
  58f0d0:      	movl	$0x1b8f, %ecx           # imm = 0x1B8F
  58f0d5:      	cmpl	%ecx, %eax
  58f0d7:      	jg	0x58f2df <.text+0x18e2df>
  58f0dd:      	je	0x58f2d5 <.text+0x18e2d5>
  58f0e3:      	addl	$-0x21, %ecx
  58f0e6:      	cmpl	%ecx, %eax
  58f0e8:      	jg	0x58f20f <.text+0x18e20f>
  58f0ee:      	je	0x58f205 <.text+0x18e205>
  58f0f4:      	movl	$0x1b61, %ecx           # imm = 0x1B61
  58f0f9:      	cmpl	%ecx, %eax
  58f0fb:      	jg	0x58f1a0 <.text+0x18e1a0>
  58f101:      	je	0x58f196 <.text+0x18e196>
  58f107:      	addl	$-0x5, %ecx
  58f10a:      	cmpl	%ecx, %eax
  58f10c:      	jg	0x58f15a <.text+0x18e15a>
  58f10e:      	je	0x58f150 <.text+0x18e150>
  58f110:      	subl	$0x1838, %eax           # imm = 0x1838
  58f115:      	je	0x58f146 <.text+0x18e146>
  58f117:      	subl	$0x321, %eax            # imm = 0x321
  58f11c:      	je	0x58f13c <.text+0x18e13c>
  58f11e:      	decl	%eax
  58f11f:      	je	0x58f132 <.text+0x18e132>
  58f121:      	decl	%eax
  58f122:      	jne	0x591a16 <.text+0x190a16>
  58f128:      	movl	$0x5f8f44, %eax         # imm = 0x5F8F44
  58f12d:      	jmp	0x591a45 <.text+0x190a45>
  58f132:      	movl	$0x5f8f2c, %eax         # imm = 0x5F8F2C
  58f137:      	jmp	0x591a45 <.text+0x190a45>
  58f13c:      	movl	$0x5f8f08, %eax         # imm = 0x5F8F08
  58f141:      	jmp	0x591a45 <.text+0x190a45>
  58f146:      	movl	$0x5f8ee8, %eax         # imm = 0x5F8EE8
  58f14b:      	jmp	0x591a45 <.text+0x190a45>
  58f150:      	movl	$0x5f8ed0, %eax         # imm = 0x5F8ED0
  58f155:      	jmp	0x591a45 <.text+0x190a45>
  58f15a:      	subl	$0x1b5d, %eax           # imm = 0x1B5D
  58f15f:      	je	0x58f18c <.text+0x18e18c>
  58f161:      	decl	%eax
  58f162:      	je	0x58f182 <.text+0x18e182>
  58f164:      	decl	%eax
  58f165:      	je	0x58f178 <.text+0x18e178>
  58f167:      	decl	%eax
  58f168:      	jne	0x591a16 <.text+0x190a16>
  58f16e:      	movl	$0x5f8ebc, %eax         # imm = 0x5F8EBC
  58f173:      	jmp	0x591a45 <.text+0x190a45>
  58f178:      	movl	$0x5f8ea4, %eax         # imm = 0x5F8EA4
  58f17d:      	jmp	0x591a45 <.text+0x190a45>
  58f182:      	movl	$0x5f8e80, %eax         # imm = 0x5F8E80
  58f187:      	jmp	0x591a45 <.text+0x190a45>
  58f18c:      	movl	$0x5f8e58, %eax         # imm = 0x5F8E58
  58f191:      	jmp	0x591a45 <.text+0x190a45>
  58f196:      	movl	$0x5f8e38, %eax         # imm = 0x5F8E38
  58f19b:      	jmp	0x591a45 <.text+0x190a45>
  58f1a0:      	addl	$0xffffe49e, %eax       # imm = 0xFFFFE49E
  58f1a5:      	cmpl	$0x7, %eax
  58f1a8:      	ja	0x591a16 <.text+0x190a16>
  58f1ae:      	jmpl	*0x596b99(,%eax,4)
  58f1b5:      	movl	$0x5f8e1c, %eax         # imm = 0x5F8E1C
  58f1ba:      	jmp	0x591a45 <.text+0x190a45>
  58f1bf:      	movl	$0x5f8dfc, %eax         # imm = 0x5F8DFC
  58f1c4:      	jmp	0x591a45 <.text+0x190a45>
  58f1c9:      	movl	$0x5f8dd8, %eax         # imm = 0x5F8DD8
  58f1ce:      	jmp	0x591a45 <.text+0x190a45>
  58f1d3:      	movl	$0x5f8db4, %eax         # imm = 0x5F8DB4
  58f1d8:      	jmp	0x591a45 <.text+0x190a45>
  58f1dd:      	movl	$0x5f8d8c, %eax         # imm = 0x5F8D8C
  58f1e2:      	jmp	0x591a45 <.text+0x190a45>
  58f1e7:      	movl	$0x5f8d6c, %eax         # imm = 0x5F8D6C
  58f1ec:      	jmp	0x591a45 <.text+0x190a45>
  58f1f1:      	movl	$0x5f8d4c, %eax         # imm = 0x5F8D4C
  58f1f6:      	jmp	0x591a45 <.text+0x190a45>
  58f1fb:      	movl	$0x5f8d38, %eax         # imm = 0x5F8D38
  58f200:      	jmp	0x591a45 <.text+0x190a45>
  58f205:      	movl	$0x5f8d18, %eax         # imm = 0x5F8D18
  58f20a:      	jmp	0x591a45 <.text+0x190a45>
  58f20f:      	addl	$0xffffe491, %eax       # imm = 0xFFFFE491
  58f214:      	cmpl	$0x1f, %eax
  58f217:      	ja	0x591a16 <.text+0x190a16>
  58f21d:      	movzbl	0x596c01(%eax), %eax
  58f224:      	jmpl	*0x596bb9(,%eax,4)
  58f22b:      	movl	$0x5f8cf4, %eax         # imm = 0x5F8CF4
  58f230:      	jmp	0x591a45 <.text+0x190a45>
  58f235:      	movl	$0x5f8cd8, %eax         # imm = 0x5F8CD8
  58f23a:      	jmp	0x591a45 <.text+0x190a45>
  58f23f:      	movl	$0x5f8cbc, %eax         # imm = 0x5F8CBC
  58f244:      	jmp	0x591a45 <.text+0x190a45>
  58f249:      	movl	$0x5f8ca0, %eax         # imm = 0x5F8CA0
  58f24e:      	jmp	0x591a45 <.text+0x190a45>
  58f253:      	movl	$0x5f8c84, %eax         # imm = 0x5F8C84
  58f258:      	jmp	0x591a45 <.text+0x190a45>
  58f25d:      	movl	$0x5f8c6c, %eax         # imm = 0x5F8C6C
  58f262:      	jmp	0x591a45 <.text+0x190a45>
  58f267:      	movl	$0x5f8c4c, %eax         # imm = 0x5F8C4C
  58f26c:      	jmp	0x591a45 <.text+0x190a45>
  58f271:      	movl	$0x5f8c2c, %eax         # imm = 0x5F8C2C
  58f276:      	jmp	0x591a45 <.text+0x190a45>
  58f27b:      	movl	$0x5f8c10, %eax         # imm = 0x5F8C10
  58f280:      	jmp	0x591a45 <.text+0x190a45>
  58f285:      	movl	$0x5f8bf8, %eax         # imm = 0x5F8BF8
  58f28a:      	jmp	0x591a45 <.text+0x190a45>
  58f28f:      	movl	$0x5f8bd4, %eax         # imm = 0x5F8BD4
  58f294:      	jmp	0x591a45 <.text+0x190a45>
  58f299:      	movl	$0x5f8bbc, %eax         # imm = 0x5F8BBC
  58f29e:      	jmp	0x591a45 <.text+0x190a45>
  58f2a3:      	movl	$0x5f8ba0, %eax         # imm = 0x5F8BA0
  58f2a8:      	jmp	0x591a45 <.text+0x190a45>
  58f2ad:      	movl	$0x5f8b84, %eax         # imm = 0x5F8B84
  58f2b2:      	jmp	0x591a45 <.text+0x190a45>
  58f2b7:      	movl	$0x5f8b64, %eax         # imm = 0x5F8B64
  58f2bc:      	jmp	0x591a45 <.text+0x190a45>
  58f2c1:      	movl	$0x5f8b40, %eax         # imm = 0x5F8B40
  58f2c6:      	jmp	0x591a45 <.text+0x190a45>
  58f2cb:      	movl	$0x5f8b20, %eax         # imm = 0x5F8B20
  58f2d0:      	jmp	0x591a45 <.text+0x190a45>
  58f2d5:      	movl	$0x5f8afc, %eax         # imm = 0x5F8AFC
  58f2da:      	jmp	0x591a45 <.text+0x190a45>
  58f2df:      	movl	$0x1f4f, %ecx           # imm = 0x1F4F
  58f2e4:      	cmpl	%ecx, %eax
  58f2e6:      	jg	0x58f3ec <.text+0x18e3ec>
  58f2ec:      	je	0x58f3e2 <.text+0x18e3e2>
  58f2f2:      	addl	$-0x9, %ecx
  58f2f5:      	cmpl	%ecx, %eax
  58f2f7:      	jg	0x58f387 <.text+0x18e387>
  58f2fd:      	je	0x58f37d <.text+0x18e37d>
  58f2ff:      	movl	$0x1f42, %ecx           # imm = 0x1F42
  58f304:      	cmpl	%ecx, %eax
  58f306:      	jg	0x58f34e <.text+0x18e34e>
  58f308:      	je	0x589055 <.text+0x188055>
  58f30e:      	subl	$0x1b90, %eax           # imm = 0x1B90
  58f313:      	je	0x58f344 <.text+0x18e344>
  58f315:      	decl	%eax
  58f316:      	je	0x58f33a <.text+0x18e33a>
  58f318:      	decl	%eax
  58f319:      	je	0x58f330 <.text+0x18e330>
  58f31b:      	subl	$0x3af, %eax            # imm = 0x3AF
  58f320:      	jne	0x591a16 <.text+0x190a16>
  58f326:      	movl	$0x5f8adc, %eax         # imm = 0x5F8ADC
  58f32b:      	jmp	0x591a45 <.text+0x190a45>
  58f330:      	movl	$0x5f8ab4, %eax         # imm = 0x5F8AB4
  58f335:      	jmp	0x591a45 <.text+0x190a45>
  58f33a:      	movl	$0x5f8a94, %eax         # imm = 0x5F8A94
  58f33f:      	jmp	0x591a45 <.text+0x190a45>
  58f344:      	movl	$0x5f8a78, %eax         # imm = 0x5F8A78
  58f349:      	jmp	0x591a45 <.text+0x190a45>
  58f34e:      	subl	$0x1f43, %eax           # imm = 0x1F43
  58f353:      	je	0x58f373 <.text+0x18e373>
  58f355:      	decl	%eax
  58f356:      	je	0x58f369 <.text+0x18e369>
  58f358:      	decl	%eax
  58f359:      	jne	0x591a16 <.text+0x190a16>
  58f35f:      	movl	$0x5f8a64, %eax         # imm = 0x5F8A64
  58f364:      	jmp	0x591a45 <.text+0x190a45>
  58f369:      	movl	$0x5f8a4c, %eax         # imm = 0x5F8A4C
  58f36e:      	jmp	0x591a45 <.text+0x190a45>
  58f373:      	movl	$0x5f8a30, %eax         # imm = 0x5F8A30
  58f378:      	jmp	0x591a45 <.text+0x190a45>
  58f37d:      	movl	$0x5f8a18, %eax         # imm = 0x5F8A18
  58f382:      	jmp	0x591a45 <.text+0x190a45>
  58f387:      	addl	$0xffffe0b9, %eax       # imm = 0xFFFFE0B9
  58f38c:      	cmpl	$0x7, %eax
  58f38f:      	ja	0x591a16 <.text+0x190a16>
  58f395:      	jmpl	*0x596c21(,%eax,4)
  58f39c:      	movl	$0x5f8a00, %eax         # imm = 0x5F8A00
  58f3a1:      	jmp	0x591a45 <.text+0x190a45>
  58f3a6:      	movl	$0x5f89dc, %eax         # imm = 0x5F89DC
  58f3ab:      	jmp	0x591a45 <.text+0x190a45>
  58f3b0:      	movl	$0x5f89bc, %eax         # imm = 0x5F89BC
  58f3b5:      	jmp	0x591a45 <.text+0x190a45>
  58f3ba:      	movl	$0x5f899c, %eax         # imm = 0x5F899C
  58f3bf:      	jmp	0x591a45 <.text+0x190a45>
  58f3c4:      	movl	$0x5f897c, %eax         # imm = 0x5F897C
  58f3c9:      	jmp	0x591a45 <.text+0x190a45>
  58f3ce:      	movl	$0x5f8964, %eax         # imm = 0x5F8964
  58f3d3:      	jmp	0x591a45 <.text+0x190a45>
  58f3d8:      	movl	$0x5f8944, %eax         # imm = 0x5F8944
  58f3dd:      	jmp	0x591a45 <.text+0x190a45>
  58f3e2:      	movl	$0x5f892c, %eax         # imm = 0x5F892C
  58f3e7:      	jmp	0x591a45 <.text+0x190a45>
  58f3ec:      	movl	$0x200e, %ecx           # imm = 0x200E
  58f3f1:      	cmpl	%ecx, %eax
  58f3f3:      	jg	0x58f48b <.text+0x18e48b>
  58f3f9:      	je	0x58f481 <.text+0x18e481>
  58f3ff:      	addl	$-0x4, %ecx
  58f402:      	cmpl	%ecx, %eax
  58f404:      	jg	0x58f452 <.text+0x18e452>
  58f406:      	je	0x58f448 <.text+0x18e448>
  58f408:      	subl	$0x1f50, %eax           # imm = 0x1F50
  58f40d:      	je	0x58f43e <.text+0x18e43e>
  58f40f:      	decl	%eax
  58f410:      	je	0x58f434 <.text+0x18e434>
  58f412:      	subl	$0xb7, %eax
  58f417:      	je	0x58f42a <.text+0x18e42a>
  58f419:      	decl	%eax
  58f41a:      	jne	0x591a16 <.text+0x190a16>
  58f420:      	movl	$0x5f8904, %eax         # imm = 0x5F8904
  58f425:      	jmp	0x591a45 <.text+0x190a45>
  58f42a:      	movl	$0x5f88ec, %eax         # imm = 0x5F88EC
  58f42f:      	jmp	0x591a45 <.text+0x190a45>
  58f434:      	movl	$0x5f88c8, %eax         # imm = 0x5F88C8
  58f439:      	jmp	0x591a45 <.text+0x190a45>
  58f43e:      	movl	$0x5f88b0, %eax         # imm = 0x5F88B0
  58f443:      	jmp	0x591a45 <.text+0x190a45>
  58f448:      	movl	$0x5f8890, %eax         # imm = 0x5F8890
  58f44d:      	jmp	0x591a45 <.text+0x190a45>
  58f452:      	subl	$0x200b, %eax           # imm = 0x200B
  58f457:      	je	0x58f477 <.text+0x18e477>
  58f459:      	decl	%eax
  58f45a:      	je	0x58f46d <.text+0x18e46d>
  58f45c:      	decl	%eax
  58f45d:      	jne	0x591a16 <.text+0x190a16>
  58f463:      	movl	$0x5f886c, %eax         # imm = 0x5F886C
  58f468:      	jmp	0x591a45 <.text+0x190a45>
  58f46d:      	movl	$0x5f8848, %eax         # imm = 0x5F8848
  58f472:      	jmp	0x591a45 <.text+0x190a45>
  58f477:      	movl	$0x5f8824, %eax         # imm = 0x5F8824
  58f47c:      	jmp	0x591a45 <.text+0x190a45>
  58f481:      	movl	$0x5f8814, %eax         # imm = 0x5F8814
  58f486:      	jmp	0x591a45 <.text+0x190a45>
  58f48b:      	addl	$0xffffdff1, %eax       # imm = 0xFFFFDFF1
  58f490:      	cmpl	$0x7, %eax
  58f493:      	ja	0x591a16 <.text+0x190a16>
  58f499:      	jmpl	*0x596c41(,%eax,4)
  58f4a0:      	movl	$0x5f87fc, %eax         # imm = 0x5F87FC
  58f4a5:      	jmp	0x591a45 <.text+0x190a45>
  58f4aa:      	movl	$0x5f87e0, %eax         # imm = 0x5F87E0
  58f4af:      	jmp	0x591a45 <.text+0x190a45>
  58f4b4:      	movl	$0x5f87c8, %eax         # imm = 0x5F87C8
  58f4b9:      	jmp	0x591a45 <.text+0x190a45>
  58f4be:      	movl	$0x5f87a8, %eax         # imm = 0x5F87A8
  58f4c3:      	jmp	0x591a45 <.text+0x190a45>
  58f4c8:      	movl	$0x5f878c, %eax         # imm = 0x5F878C
  58f4cd:      	jmp	0x591a45 <.text+0x190a45>
  58f4d2:      	movl	$0x5f876c, %eax         # imm = 0x5F876C
  58f4d7:      	jmp	0x591a45 <.text+0x190a45>
  58f4dc:      	movl	$0x5f8750, %eax         # imm = 0x5F8750
  58f4e1:      	jmp	0x591a45 <.text+0x190a45>
  58f4e6:      	movl	$0x5f8738, %eax         # imm = 0x5F8738
  58f4eb:      	jmp	0x591a45 <.text+0x190a45>
  58f4f0:      	movl	$0x5f871c, %eax         # imm = 0x5F871C
  58f4f5:      	jmp	0x591a45 <.text+0x190a45>
  58f4fa:      	addl	$0xffffdfe8, %eax       # imm = 0xFFFFDFE8
  58f4ff:      	cmpl	$0x13f, %eax            # imm = 0x13F
  58f504:      	ja	0x591a16 <.text+0x190a16>
  58f50a:      	jmpl	*0x596c61(,%eax,4)
  58f511:      	movl	$0x5f86fc, %eax         # imm = 0x5F86FC
  58f516:      	jmp	0x591a45 <.text+0x190a45>
  58f51b:      	movl	$0x5f86e0, %eax         # imm = 0x5F86E0
  58f520:      	jmp	0x591a45 <.text+0x190a45>
  58f525:      	movl	$0x5f86cc, %eax         # imm = 0x5F86CC
  58f52a:      	jmp	0x591a45 <.text+0x190a45>
  58f52f:      	movl	$0x5f86ac, %eax         # imm = 0x5F86AC
  58f534:      	jmp	0x591a45 <.text+0x190a45>
  58f539:      	movl	$0x5f8694, %eax         # imm = 0x5F8694
  58f53e:      	jmp	0x591a45 <.text+0x190a45>
  58f543:      	movl	$0x5f867c, %eax         # imm = 0x5F867C
  58f548:      	jmp	0x591a45 <.text+0x190a45>
  58f54d:      	movl	$0x5f8660, %eax         # imm = 0x5F8660
  58f552:      	jmp	0x591a45 <.text+0x190a45>
  58f557:      	movl	$0x5f8644, %eax         # imm = 0x5F8644
  58f55c:      	jmp	0x591a45 <.text+0x190a45>
  58f561:      	movl	$0x5f862c, %eax         # imm = 0x5F862C
  58f566:      	jmp	0x591a45 <.text+0x190a45>
  58f56b:      	movl	$0x5f8610, %eax         # imm = 0x5F8610
  58f570:      	jmp	0x591a45 <.text+0x190a45>
  58f575:      	movl	$0x5f85f4, %eax         # imm = 0x5F85F4
  58f57a:      	jmp	0x591a45 <.text+0x190a45>
  58f57f:      	movl	$0x5f85d4, %eax         # imm = 0x5F85D4
  58f584:      	jmp	0x591a45 <.text+0x190a45>
  58f589:      	movl	$0x5f85bc, %eax         # imm = 0x5F85BC
  58f58e:      	jmp	0x591a45 <.text+0x190a45>
  58f593:      	movl	$0x5f85a4, %eax         # imm = 0x5F85A4
  58f598:      	jmp	0x591a45 <.text+0x190a45>
  58f59d:      	movl	$0x5f8580, %eax         # imm = 0x5F8580
  58f5a2:      	jmp	0x591a45 <.text+0x190a45>
  58f5a7:      	movl	$0x5f8560, %eax         # imm = 0x5F8560
  58f5ac:      	jmp	0x591a45 <.text+0x190a45>
  58f5b1:      	movl	$0x5f8544, %eax         # imm = 0x5F8544
  58f5b6:      	jmp	0x591a45 <.text+0x190a45>
  58f5bb:      	movl	$0x5f852c, %eax         # imm = 0x5F852C
  58f5c0:      	jmp	0x591a45 <.text+0x190a45>
  58f5c5:      	movl	$0x5f8518, %eax         # imm = 0x5F8518
  58f5ca:      	jmp	0x591a45 <.text+0x190a45>
  58f5cf:      	movl	$0x5f84f4, %eax         # imm = 0x5F84F4
  58f5d4:      	jmp	0x591a45 <.text+0x190a45>
  58f5d9:      	movl	$0x5f84d0, %eax         # imm = 0x5F84D0
  58f5de:      	jmp	0x591a45 <.text+0x190a45>
  58f5e3:      	movl	$0x5f84b0, %eax         # imm = 0x5F84B0
  58f5e8:      	jmp	0x591a45 <.text+0x190a45>
  58f5ed:      	movl	$0x5f8490, %eax         # imm = 0x5F8490
  58f5f2:      	jmp	0x591a45 <.text+0x190a45>
  58f5f7:      	movl	$0x5f8478, %eax         # imm = 0x5F8478
  58f5fc:      	jmp	0x591a45 <.text+0x190a45>
  58f601:      	movl	$0x5f8460, %eax         # imm = 0x5F8460
  58f606:      	jmp	0x591a45 <.text+0x190a45>
  58f60b:      	movl	$0x5f8444, %eax         # imm = 0x5F8444
  58f610:      	jmp	0x591a45 <.text+0x190a45>
  58f615:      	movl	$0x5f8430, %eax         # imm = 0x5F8430
  58f61a:      	jmp	0x591a45 <.text+0x190a45>
  58f61f:      	movl	$0x5f8410, %eax         # imm = 0x5F8410
  58f624:      	jmp	0x591a45 <.text+0x190a45>
  58f629:      	movl	$0x5f83f0, %eax         # imm = 0x5F83F0
  58f62e:      	jmp	0x591a45 <.text+0x190a45>
  58f633:      	movl	$0x5f83d8, %eax         # imm = 0x5F83D8
  58f638:      	jmp	0x591a45 <.text+0x190a45>
  58f63d:      	movl	$0x5f83bc, %eax         # imm = 0x5F83BC
  58f642:      	jmp	0x591a45 <.text+0x190a45>
  58f647:      	movl	$0x5f8398, %eax         # imm = 0x5F8398
  58f64c:      	jmp	0x591a45 <.text+0x190a45>
  58f651:      	movl	$0x5f8378, %eax         # imm = 0x5F8378
  58f656:      	jmp	0x591a45 <.text+0x190a45>
  58f65b:      	movl	$0x5f8360, %eax         # imm = 0x5F8360
  58f660:      	jmp	0x591a45 <.text+0x190a45>
  58f665:      	movl	$0x5f8348, %eax         # imm = 0x5F8348
  58f66a:      	jmp	0x591a45 <.text+0x190a45>
  58f66f:      	movl	$0x5f8330, %eax         # imm = 0x5F8330
  58f674:      	jmp	0x591a45 <.text+0x190a45>
  58f679:      	movl	$0x5f8318, %eax         # imm = 0x5F8318
  58f67e:      	jmp	0x591a45 <.text+0x190a45>
  58f683:      	movl	$0x5f8300, %eax         # imm = 0x5F8300
  58f688:      	jmp	0x591a45 <.text+0x190a45>
  58f68d:      	movl	$0x5f82e8, %eax         # imm = 0x5F82E8
  58f692:      	jmp	0x591a45 <.text+0x190a45>
  58f697:      	movl	$0x5f82d0, %eax         # imm = 0x5F82D0
  58f69c:      	jmp	0x591a45 <.text+0x190a45>
  58f6a1:      	movl	$0x5f82b0, %eax         # imm = 0x5F82B0
  58f6a6:      	jmp	0x591a45 <.text+0x190a45>
  58f6ab:      	movl	$0x5f8294, %eax         # imm = 0x5F8294
  58f6b0:      	jmp	0x591a45 <.text+0x190a45>
  58f6b5:      	movl	$0x5f827c, %eax         # imm = 0x5F827C
  58f6ba:      	jmp	0x591a45 <.text+0x190a45>
  58f6bf:      	movl	$0x5f8258, %eax         # imm = 0x5F8258
  58f6c4:      	jmp	0x591a45 <.text+0x190a45>
  58f6c9:      	movl	$0x5f823c, %eax         # imm = 0x5F823C
  58f6ce:      	jmp	0x591a45 <.text+0x190a45>
  58f6d3:      	movl	$0x5f821c, %eax         # imm = 0x5F821C
  58f6d8:      	jmp	0x591a45 <.text+0x190a45>
  58f6dd:      	movl	$0x5f81fc, %eax         # imm = 0x5F81FC
  58f6e2:      	jmp	0x591a45 <.text+0x190a45>
  58f6e7:      	movl	$0x5f81dc, %eax         # imm = 0x5F81DC
  58f6ec:      	jmp	0x591a45 <.text+0x190a45>
  58f6f1:      	movl	$0x5f81bc, %eax         # imm = 0x5F81BC
  58f6f6:      	jmp	0x591a45 <.text+0x190a45>
  58f6fb:      	movl	$0x5f8198, %eax         # imm = 0x5F8198
  58f700:      	jmp	0x591a45 <.text+0x190a45>
  58f705:      	movl	$0x5f8174, %eax         # imm = 0x5F8174
  58f70a:      	jmp	0x591a45 <.text+0x190a45>
  58f70f:      	movl	$0x5f8150, %eax         # imm = 0x5F8150
  58f714:      	jmp	0x591a45 <.text+0x190a45>
  58f719:      	movl	$0x5f8130, %eax         # imm = 0x5F8130
  58f71e:      	jmp	0x591a45 <.text+0x190a45>
  58f723:      	movl	$0x5f8114, %eax         # imm = 0x5F8114
  58f728:      	jmp	0x591a45 <.text+0x190a45>
  58f72d:      	movl	$0x5f80f4, %eax         # imm = 0x5F80F4
  58f732:      	jmp	0x591a45 <.text+0x190a45>
  58f737:      	movl	$0x5f80dc, %eax         # imm = 0x5F80DC
  58f73c:      	jmp	0x591a45 <.text+0x190a45>
  58f741:      	movl	$0x5f80c0, %eax         # imm = 0x5F80C0
  58f746:      	jmp	0x591a45 <.text+0x190a45>
  58f74b:      	movl	$0x5f80a4, %eax         # imm = 0x5F80A4
  58f750:      	jmp	0x591a45 <.text+0x190a45>
  58f755:      	movl	$0x5f8084, %eax         # imm = 0x5F8084
  58f75a:      	jmp	0x591a45 <.text+0x190a45>
  58f75f:      	movl	$0x5f8064, %eax         # imm = 0x5F8064
  58f764:      	jmp	0x591a45 <.text+0x190a45>
  58f769:      	movl	$0x5f8044, %eax         # imm = 0x5F8044
  58f76e:      	jmp	0x591a45 <.text+0x190a45>
  58f773:      	movl	$0x5f8028, %eax         # imm = 0x5F8028
  58f778:      	jmp	0x591a45 <.text+0x190a45>
  58f77d:      	movl	$0x5f8008, %eax         # imm = 0x5F8008
  58f782:      	jmp	0x591a45 <.text+0x190a45>
  58f787:      	movl	$0x5f7fe4, %eax         # imm = 0x5F7FE4
  58f78c:      	jmp	0x591a45 <.text+0x190a45>
  58f791:      	movl	$0x5f7fc8, %eax         # imm = 0x5F7FC8
  58f796:      	jmp	0x591a45 <.text+0x190a45>
  58f79b:      	movl	$0x5f7fa8, %eax         # imm = 0x5F7FA8
  58f7a0:      	jmp	0x591a45 <.text+0x190a45>
  58f7a5:      	movl	$0x5f7f88, %eax         # imm = 0x5F7F88
  58f7aa:      	jmp	0x591a45 <.text+0x190a45>
  58f7af:      	movl	$0x5f7f64, %eax         # imm = 0x5F7F64
  58f7b4:      	jmp	0x591a45 <.text+0x190a45>
  58f7b9:      	movl	$0x5f7f44, %eax         # imm = 0x5F7F44
  58f7be:      	jmp	0x591a45 <.text+0x190a45>
  58f7c3:      	movl	$0x5f7f2c, %eax         # imm = 0x5F7F2C
  58f7c8:      	jmp	0x591a45 <.text+0x190a45>
  58f7cd:      	movl	$0x5f7f10, %eax         # imm = 0x5F7F10
  58f7d2:      	jmp	0x591a45 <.text+0x190a45>
  58f7d7:      	movl	$0x5f7ef4, %eax         # imm = 0x5F7EF4
  58f7dc:      	jmp	0x591a45 <.text+0x190a45>
  58f7e1:      	movl	$0x5f7ed8, %eax         # imm = 0x5F7ED8
  58f7e6:      	jmp	0x591a45 <.text+0x190a45>
  58f7eb:      	movl	$0x5f7eb4, %eax         # imm = 0x5F7EB4
  58f7f0:      	jmp	0x591a45 <.text+0x190a45>
  58f7f5:      	movl	$0x5f7e9c, %eax         # imm = 0x5F7E9C
  58f7fa:      	jmp	0x591a45 <.text+0x190a45>
  58f7ff:      	movl	$0x5f7e84, %eax         # imm = 0x5F7E84
  58f804:      	jmp	0x591a45 <.text+0x190a45>
  58f809:      	movl	$0x5f7e64, %eax         # imm = 0x5F7E64
  58f80e:      	jmp	0x591a45 <.text+0x190a45>
  58f813:      	movl	$0x5f7e48, %eax         # imm = 0x5F7E48
  58f818:      	jmp	0x591a45 <.text+0x190a45>
  58f81d:      	movl	$0x5f7e28, %eax         # imm = 0x5F7E28
  58f822:      	jmp	0x591a45 <.text+0x190a45>
  58f827:      	movl	$0x5f7e0c, %eax         # imm = 0x5F7E0C
  58f82c:      	jmp	0x591a45 <.text+0x190a45>
  58f831:      	movl	$0x5f7df4, %eax         # imm = 0x5F7DF4
  58f836:      	jmp	0x591a45 <.text+0x190a45>
  58f83b:      	movl	$0x5f7dd4, %eax         # imm = 0x5F7DD4
  58f840:      	jmp	0x591a45 <.text+0x190a45>
  58f845:      	movl	$0x5f7dbc, %eax         # imm = 0x5F7DBC
  58f84a:      	jmp	0x591a45 <.text+0x190a45>
  58f84f:      	movl	$0x5f7d9c, %eax         # imm = 0x5F7D9C
  58f854:      	jmp	0x591a45 <.text+0x190a45>
  58f859:      	movl	$0x5f7d84, %eax         # imm = 0x5F7D84
  58f85e:      	jmp	0x591a45 <.text+0x190a45>
  58f863:      	movl	$0x5f7d64, %eax         # imm = 0x5F7D64
  58f868:      	jmp	0x591a45 <.text+0x190a45>
  58f86d:      	movl	$0x5f7d48, %eax         # imm = 0x5F7D48
  58f872:      	jmp	0x591a45 <.text+0x190a45>
  58f877:      	movl	$0x5f7d28, %eax         # imm = 0x5F7D28
  58f87c:      	jmp	0x591a45 <.text+0x190a45>
  58f881:      	movl	$0x5f7d08, %eax         # imm = 0x5F7D08
  58f886:      	jmp	0x591a45 <.text+0x190a45>
  58f88b:      	movl	$0x5f7cf0, %eax         # imm = 0x5F7CF0
  58f890:      	jmp	0x591a45 <.text+0x190a45>
  58f895:      	movl	$0x5f7cd0, %eax         # imm = 0x5F7CD0
  58f89a:      	jmp	0x591a45 <.text+0x190a45>
  58f89f:      	movl	$0x5f7cb4, %eax         # imm = 0x5F7CB4
  58f8a4:      	jmp	0x591a45 <.text+0x190a45>
  58f8a9:      	movl	$0x5f7c98, %eax         # imm = 0x5F7C98
  58f8ae:      	jmp	0x591a45 <.text+0x190a45>
  58f8b3:      	movl	$0x5f7c80, %eax         # imm = 0x5F7C80
  58f8b8:      	jmp	0x591a45 <.text+0x190a45>
  58f8bd:      	movl	$0x5f7c64, %eax         # imm = 0x5F7C64
  58f8c2:      	jmp	0x591a45 <.text+0x190a45>
  58f8c7:      	movl	$0x5f7c48, %eax         # imm = 0x5F7C48
  58f8cc:      	jmp	0x591a45 <.text+0x190a45>
  58f8d1:      	movl	$0x5f7c2c, %eax         # imm = 0x5F7C2C
  58f8d6:      	jmp	0x591a45 <.text+0x190a45>
  58f8db:      	movl	$0x5f7c08, %eax         # imm = 0x5F7C08
  58f8e0:      	jmp	0x591a45 <.text+0x190a45>
  58f8e5:      	movl	$0x5f7bec, %eax         # imm = 0x5F7BEC
  58f8ea:      	jmp	0x591a45 <.text+0x190a45>
  58f8ef:      	movl	$0x5f7bcc, %eax         # imm = 0x5F7BCC
  58f8f4:      	jmp	0x591a45 <.text+0x190a45>
  58f8f9:      	movl	$0x5f7bac, %eax         # imm = 0x5F7BAC
  58f8fe:      	jmp	0x591a45 <.text+0x190a45>
  58f903:      	movl	$0x5f7b94, %eax         # imm = 0x5F7B94
  58f908:      	jmp	0x591a45 <.text+0x190a45>
  58f90d:      	movl	$0x5f7b78, %eax         # imm = 0x5F7B78
  58f912:      	jmp	0x591a45 <.text+0x190a45>
  58f917:      	movl	$0x5f7b5c, %eax         # imm = 0x5F7B5C
  58f91c:      	jmp	0x591a45 <.text+0x190a45>
  58f921:      	movl	$0x5f7b40, %eax         # imm = 0x5F7B40
  58f926:      	jmp	0x591a45 <.text+0x190a45>
  58f92b:      	movl	$0x5f7b28, %eax         # imm = 0x5F7B28
  58f930:      	jmp	0x591a45 <.text+0x190a45>
  58f935:      	movl	$0x5f7b0c, %eax         # imm = 0x5F7B0C
  58f93a:      	jmp	0x591a45 <.text+0x190a45>
  58f93f:      	movl	$0x5f7af0, %eax         # imm = 0x5F7AF0
  58f944:      	jmp	0x591a45 <.text+0x190a45>
  58f949:      	movl	$0x5f7ad0, %eax         # imm = 0x5F7AD0
  58f94e:      	jmp	0x591a45 <.text+0x190a45>
  58f953:      	movl	$0x5f7ab4, %eax         # imm = 0x5F7AB4
  58f958:      	jmp	0x591a45 <.text+0x190a45>
  58f95d:      	movl	$0x5f7a94, %eax         # imm = 0x5F7A94
  58f962:      	jmp	0x591a45 <.text+0x190a45>
  58f967:      	movl	$0x5f7a78, %eax         # imm = 0x5F7A78
  58f96c:      	jmp	0x591a45 <.text+0x190a45>
  58f971:      	movl	$0x5f7a58, %eax         # imm = 0x5F7A58
  58f976:      	jmp	0x591a45 <.text+0x190a45>
  58f97b:      	movl	$0x5f7a38, %eax         # imm = 0x5F7A38
  58f980:      	jmp	0x591a45 <.text+0x190a45>
  58f985:      	movl	$0x5f7a18, %eax         # imm = 0x5F7A18
  58f98a:      	jmp	0x591a45 <.text+0x190a45>
  58f98f:      	movl	$0x5f79fc, %eax         # imm = 0x5F79FC
  58f994:      	jmp	0x591a45 <.text+0x190a45>
  58f999:      	movl	$0x5f79d8, %eax         # imm = 0x5F79D8
  58f99e:      	jmp	0x591a45 <.text+0x190a45>
  58f9a3:      	movl	$0x5f79b4, %eax         # imm = 0x5F79B4
  58f9a8:      	jmp	0x591a45 <.text+0x190a45>
  58f9ad:      	movl	$0x5f7990, %eax         # imm = 0x5F7990
  58f9b2:      	jmp	0x591a45 <.text+0x190a45>
  58f9b7:      	movl	$0x5f797c, %eax         # imm = 0x5F797C
  58f9bc:      	jmp	0x591a45 <.text+0x190a45>
  58f9c1:      	movl	$0x5f7968, %eax         # imm = 0x5F7968
  58f9c6:      	jmp	0x591a45 <.text+0x190a45>
  58f9cb:      	movl	$0x5f7950, %eax         # imm = 0x5F7950
  58f9d0:      	jmp	0x591a45 <.text+0x190a45>
  58f9d5:      	movl	$0x5f7934, %eax         # imm = 0x5F7934
  58f9da:      	jmp	0x591a45 <.text+0x190a45>
  58f9df:      	movl	$0x5f7914, %eax         # imm = 0x5F7914
  58f9e4:      	jmp	0x591a45 <.text+0x190a45>
  58f9e9:      	movl	$0x5f78f8, %eax         # imm = 0x5F78F8
  58f9ee:      	jmp	0x591a45 <.text+0x190a45>
  58f9f3:      	movl	$0x5f78dc, %eax         # imm = 0x5F78DC
  58f9f8:      	jmp	0x591a45 <.text+0x190a45>
  58f9fd:      	movl	$0x5f78bc, %eax         # imm = 0x5F78BC
  58fa02:      	jmp	0x591a45 <.text+0x190a45>
  58fa07:      	movl	$0x5f78a0, %eax         # imm = 0x5F78A0
  58fa0c:      	jmp	0x591a45 <.text+0x190a45>
  58fa11:      	movl	$0x5f7880, %eax         # imm = 0x5F7880
  58fa16:      	jmp	0x591a45 <.text+0x190a45>
  58fa1b:      	movl	$0x5f7860, %eax         # imm = 0x5F7860
  58fa20:      	jmp	0x591a45 <.text+0x190a45>
  58fa25:      	movl	$0x5f7844, %eax         # imm = 0x5F7844
  58fa2a:      	jmp	0x591a45 <.text+0x190a45>
  58fa2f:      	movl	$0x5f7824, %eax         # imm = 0x5F7824
  58fa34:      	jmp	0x591a45 <.text+0x190a45>
  58fa39:      	movl	$0x5f7808, %eax         # imm = 0x5F7808
  58fa3e:      	jmp	0x591a45 <.text+0x190a45>
  58fa43:      	movl	$0x5f77e8, %eax         # imm = 0x5F77E8
  58fa48:      	jmp	0x591a45 <.text+0x190a45>
  58fa4d:      	movl	$0x5f77cc, %eax         # imm = 0x5F77CC
  58fa52:      	jmp	0x591a45 <.text+0x190a45>
  58fa57:      	movl	$0x5f77b0, %eax         # imm = 0x5F77B0
  58fa5c:      	jmp	0x591a45 <.text+0x190a45>
  58fa61:      	movl	$0x5f7794, %eax         # imm = 0x5F7794
  58fa66:      	jmp	0x591a45 <.text+0x190a45>
  58fa6b:      	movl	$0x5f7774, %eax         # imm = 0x5F7774
  58fa70:      	jmp	0x591a45 <.text+0x190a45>
  58fa75:      	movl	$0x5f7750, %eax         # imm = 0x5F7750
  58fa7a:      	jmp	0x591a45 <.text+0x190a45>
  58fa7f:      	movl	$0x5f7738, %eax         # imm = 0x5F7738
  58fa84:      	jmp	0x591a45 <.text+0x190a45>
  58fa89:      	movl	$0x5f771c, %eax         # imm = 0x5F771C
  58fa8e:      	jmp	0x591a45 <.text+0x190a45>
  58fa93:      	movl	$0x5f76fc, %eax         # imm = 0x5F76FC
  58fa98:      	jmp	0x591a45 <.text+0x190a45>
  58fa9d:      	movl	$0x5f76e4, %eax         # imm = 0x5F76E4
  58faa2:      	jmp	0x591a45 <.text+0x190a45>
  58faa7:      	movl	$0x5f76c8, %eax         # imm = 0x5F76C8
  58faac:      	jmp	0x591a45 <.text+0x190a45>
  58fab1:      	movl	$0x5f76a8, %eax         # imm = 0x5F76A8
  58fab6:      	jmp	0x591a45 <.text+0x190a45>
  58fabb:      	movl	$0x5f7684, %eax         # imm = 0x5F7684
  58fac0:      	jmp	0x591a45 <.text+0x190a45>
  58fac5:      	movl	$0x5f7668, %eax         # imm = 0x5F7668
  58faca:      	jmp	0x591a45 <.text+0x190a45>
  58facf:      	movl	$0x5f7650, %eax         # imm = 0x5F7650
  58fad4:      	jmp	0x591a45 <.text+0x190a45>
  58fad9:      	movl	$0x5f7630, %eax         # imm = 0x5F7630
  58fade:      	jmp	0x591a45 <.text+0x190a45>
  58fae3:      	movl	$0x5f7614, %eax         # imm = 0x5F7614
  58fae8:      	jmp	0x591a45 <.text+0x190a45>
  58faed:      	movl	$0x5f75fc, %eax         # imm = 0x5F75FC
  58faf2:      	jmp	0x591a45 <.text+0x190a45>
  58faf7:      	movl	$0x5f75e0, %eax         # imm = 0x5F75E0
  58fafc:      	jmp	0x591a45 <.text+0x190a45>
  58fb01:      	movl	$0x5f75c0, %eax         # imm = 0x5F75C0
  58fb06:      	jmp	0x591a45 <.text+0x190a45>
  58fb0b:      	movl	$0x5f75a0, %eax         # imm = 0x5F75A0
  58fb10:      	jmp	0x591a45 <.text+0x190a45>
  58fb15:      	movl	$0x5f757c, %eax         # imm = 0x5F757C
  58fb1a:      	jmp	0x591a45 <.text+0x190a45>
  58fb1f:      	movl	$0x5f7560, %eax         # imm = 0x5F7560
  58fb24:      	jmp	0x591a45 <.text+0x190a45>
  58fb29:      	movl	$0x5f7540, %eax         # imm = 0x5F7540
  58fb2e:      	jmp	0x591a45 <.text+0x190a45>
  58fb33:      	movl	$0x5f7520, %eax         # imm = 0x5F7520
  58fb38:      	jmp	0x591a45 <.text+0x190a45>
  58fb3d:      	movl	$0x5f7508, %eax         # imm = 0x5F7508
  58fb42:      	jmp	0x591a45 <.text+0x190a45>
  58fb47:      	movl	$0x5f74e8, %eax         # imm = 0x5F74E8
  58fb4c:      	jmp	0x591a45 <.text+0x190a45>
  58fb51:      	movl	$0x5f74cc, %eax         # imm = 0x5F74CC
  58fb56:      	jmp	0x591a45 <.text+0x190a45>
  58fb5b:      	movl	$0x5f74ac, %eax         # imm = 0x5F74AC
  58fb60:      	jmp	0x591a45 <.text+0x190a45>
  58fb65:      	movl	$0x5f748c, %eax         # imm = 0x5F748C
  58fb6a:      	jmp	0x591a45 <.text+0x190a45>
  58fb6f:      	movl	$0x5f746c, %eax         # imm = 0x5F746C
  58fb74:      	jmp	0x591a45 <.text+0x190a45>
  58fb79:      	movl	$0x5f7448, %eax         # imm = 0x5F7448
  58fb7e:      	jmp	0x591a45 <.text+0x190a45>
  58fb83:      	movl	$0x5f7424, %eax         # imm = 0x5F7424
  58fb88:      	jmp	0x591a45 <.text+0x190a45>
  58fb8d:      	movl	$0x5f7408, %eax         # imm = 0x5F7408
  58fb92:      	jmp	0x591a45 <.text+0x190a45>
  58fb97:      	movl	$0x5f73e0, %eax         # imm = 0x5F73E0
  58fb9c:      	jmp	0x591a45 <.text+0x190a45>
  58fba1:      	movl	$0x5f73c0, %eax         # imm = 0x5F73C0
  58fba6:      	jmp	0x591a45 <.text+0x190a45>
  58fbab:      	movl	$0x5f739c, %eax         # imm = 0x5F739C
  58fbb0:      	jmp	0x591a45 <.text+0x190a45>
  58fbb5:      	movl	$0x5f7374, %eax         # imm = 0x5F7374
  58fbba:      	jmp	0x591a45 <.text+0x190a45>
  58fbbf:      	movl	$0x5f7358, %eax         # imm = 0x5F7358
  58fbc4:      	jmp	0x591a45 <.text+0x190a45>
  58fbc9:      	movl	$0x5f7340, %eax         # imm = 0x5F7340
  58fbce:      	jmp	0x591a45 <.text+0x190a45>
  58fbd3:      	movl	$0x5f731c, %eax         # imm = 0x5F731C
  58fbd8:      	jmp	0x591a45 <.text+0x190a45>
  58fbdd:      	movl	$0x5f72fc, %eax         # imm = 0x5F72FC
  58fbe2:      	jmp	0x591a45 <.text+0x190a45>
  58fbe7:      	movl	$0x5f72dc, %eax         # imm = 0x5F72DC
  58fbec:      	jmp	0x591a45 <.text+0x190a45>
  58fbf1:      	movl	$0x5f72b8, %eax         # imm = 0x5F72B8
  58fbf6:      	jmp	0x591a45 <.text+0x190a45>
  58fbfb:      	movl	$0x5f72a0, %eax         # imm = 0x5F72A0
  58fc00:      	jmp	0x591a45 <.text+0x190a45>
  58fc05:      	movl	$0x5f7280, %eax         # imm = 0x5F7280
  58fc0a:      	jmp	0x591a45 <.text+0x190a45>
  58fc0f:      	movl	$0x5f726c, %eax         # imm = 0x5F726C
  58fc14:      	jmp	0x591a45 <.text+0x190a45>
  58fc19:      	movl	$0x5f7258, %eax         # imm = 0x5F7258
  58fc1e:      	jmp	0x591a45 <.text+0x190a45>
  58fc23:      	movl	$0x5f7244, %eax         # imm = 0x5F7244
  58fc28:      	jmp	0x591a45 <.text+0x190a45>
  58fc2d:      	movl	$0x5f722c, %eax         # imm = 0x5F722C
  58fc32:      	jmp	0x591a45 <.text+0x190a45>
  58fc37:      	movl	$0x5f7210, %eax         # imm = 0x5F7210
  58fc3c:      	jmp	0x591a45 <.text+0x190a45>
  58fc41:      	movl	$0x5f71f0, %eax         # imm = 0x5F71F0
  58fc46:      	jmp	0x591a45 <.text+0x190a45>
  58fc4b:      	movl	$0x5f71d0, %eax         # imm = 0x5F71D0
  58fc50:      	jmp	0x591a45 <.text+0x190a45>
  58fc55:      	movl	$0x5f71b0, %eax         # imm = 0x5F71B0
  58fc5a:      	jmp	0x591a45 <.text+0x190a45>
  58fc5f:      	movl	$0x5f7198, %eax         # imm = 0x5F7198
  58fc64:      	jmp	0x591a45 <.text+0x190a45>
  58fc69:      	movl	$0x5f717c, %eax         # imm = 0x5F717C
  58fc6e:      	jmp	0x591a45 <.text+0x190a45>
  58fc73:      	movl	$0x5f715c, %eax         # imm = 0x5F715C
  58fc78:      	jmp	0x591a45 <.text+0x190a45>
  58fc7d:      	movl	$0x5f7140, %eax         # imm = 0x5F7140
  58fc82:      	jmp	0x591a45 <.text+0x190a45>
  58fc87:      	movl	$0x5f7120, %eax         # imm = 0x5F7120
  58fc8c:      	jmp	0x591a45 <.text+0x190a45>
  58fc91:      	movl	$0x5f7108, %eax         # imm = 0x5F7108
  58fc96:      	jmp	0x591a45 <.text+0x190a45>
  58fc9b:      	movl	$0x5f70f0, %eax         # imm = 0x5F70F0
  58fca0:      	jmp	0x591a45 <.text+0x190a45>
  58fca5:      	movl	$0x5f70d4, %eax         # imm = 0x5F70D4
  58fcaa:      	jmp	0x591a45 <.text+0x190a45>
  58fcaf:      	movl	$0x5f70b8, %eax         # imm = 0x5F70B8
  58fcb4:      	jmp	0x591a45 <.text+0x190a45>
  58fcb9:      	movl	$0x5f709c, %eax         # imm = 0x5F709C
  58fcbe:      	jmp	0x591a45 <.text+0x190a45>
  58fcc3:      	movl	$0x5f707c, %eax         # imm = 0x5F707C
  58fcc8:      	jmp	0x591a45 <.text+0x190a45>
  58fccd:      	movl	$0x5f7060, %eax         # imm = 0x5F7060
  58fcd2:      	jmp	0x591a45 <.text+0x190a45>
  58fcd7:      	movl	$0x5f7044, %eax         # imm = 0x5F7044
  58fcdc:      	jmp	0x591a45 <.text+0x190a45>
  58fce1:      	movl	$0x5f7024, %eax         # imm = 0x5F7024
  58fce6:      	jmp	0x591a45 <.text+0x190a45>
  58fceb:      	movl	$0x5f7008, %eax         # imm = 0x5F7008
  58fcf0:      	jmp	0x591a45 <.text+0x190a45>
  58fcf5:      	movl	$0x5f6ff0, %eax         # imm = 0x5F6FF0
  58fcfa:      	jmp	0x591a45 <.text+0x190a45>
  58fcff:      	movl	$0x5f6fd4, %eax         # imm = 0x5F6FD4
  58fd04:      	jmp	0x591a45 <.text+0x190a45>
  58fd09:      	movl	$0x5f6fbc, %eax         # imm = 0x5F6FBC
  58fd0e:      	jmp	0x591a45 <.text+0x190a45>
  58fd13:      	movl	$0x5f6f94, %eax         # imm = 0x5F6F94
  58fd18:      	jmp	0x591a45 <.text+0x190a45>
  58fd1d:      	movl	$0x5f6f6c, %eax         # imm = 0x5F6F6C
  58fd22:      	jmp	0x591a45 <.text+0x190a45>
  58fd27:      	movl	$0x5f6f48, %eax         # imm = 0x5F6F48
  58fd2c:      	jmp	0x591a45 <.text+0x190a45>
  58fd31:      	movl	$0x5f6f24, %eax         # imm = 0x5F6F24
  58fd36:      	jmp	0x591a45 <.text+0x190a45>
  58fd3b:      	movl	$0x5f6f0c, %eax         # imm = 0x5F6F0C
  58fd40:      	jmp	0x591a45 <.text+0x190a45>
  58fd45:      	movl	$0x5f6eec, %eax         # imm = 0x5F6EEC
  58fd4a:      	jmp	0x591a45 <.text+0x190a45>
  58fd4f:      	movl	$0x5f6ecc, %eax         # imm = 0x5F6ECC
  58fd54:      	jmp	0x591a45 <.text+0x190a45>
  58fd59:      	movl	$0x5f6eac, %eax         # imm = 0x5F6EAC
  58fd5e:      	jmp	0x591a45 <.text+0x190a45>
  58fd63:      	movl	$0x5f6e8c, %eax         # imm = 0x5F6E8C
  58fd68:      	jmp	0x591a45 <.text+0x190a45>
  58fd6d:      	movl	$0x5f6e6c, %eax         # imm = 0x5F6E6C
  58fd72:      	jmp	0x591a45 <.text+0x190a45>
  58fd77:      	movl	$0x5f6e40, %eax         # imm = 0x5F6E40
  58fd7c:      	jmp	0x591a45 <.text+0x190a45>
  58fd81:      	movl	$0x5f6e20, %eax         # imm = 0x5F6E20
  58fd86:      	jmp	0x591a45 <.text+0x190a45>
  58fd8b:      	movl	$0x5f6e04, %eax         # imm = 0x5F6E04
  58fd90:      	jmp	0x591a45 <.text+0x190a45>
  58fd95:      	movl	$0x5f6de8, %eax         # imm = 0x5F6DE8
  58fd9a:      	jmp	0x591a45 <.text+0x190a45>
  58fd9f:      	movl	$0x5f6dc8, %eax         # imm = 0x5F6DC8
  58fda4:      	jmp	0x591a45 <.text+0x190a45>
  58fda9:      	movl	$0x5f6dac, %eax         # imm = 0x5F6DAC
  58fdae:      	jmp	0x591a45 <.text+0x190a45>
  58fdb3:      	movl	$0x5f6d8c, %eax         # imm = 0x5F6D8C
  58fdb8:      	jmp	0x591a45 <.text+0x190a45>
  58fdbd:      	movl	$0x5f6d74, %eax         # imm = 0x5F6D74
  58fdc2:      	jmp	0x591a45 <.text+0x190a45>
  58fdc7:      	movl	$0x5f6d50, %eax         # imm = 0x5F6D50
  58fdcc:      	jmp	0x591a45 <.text+0x190a45>
  58fdd1:      	movl	$0x5f6d34, %eax         # imm = 0x5F6D34
  58fdd6:      	jmp	0x591a45 <.text+0x190a45>
  58fddb:      	movl	$0x5f6d18, %eax         # imm = 0x5F6D18
  58fde0:      	jmp	0x591a45 <.text+0x190a45>
  58fde5:      	movl	$0x5f6cf8, %eax         # imm = 0x5F6CF8
  58fdea:      	jmp	0x591a45 <.text+0x190a45>
  58fdef:      	movl	$0x5f6ce0, %eax         # imm = 0x5F6CE0
  58fdf4:      	jmp	0x591a45 <.text+0x190a45>
  58fdf9:      	movl	$0x5f6cc4, %eax         # imm = 0x5F6CC4
  58fdfe:      	jmp	0x591a45 <.text+0x190a45>
  58fe03:      	movl	$0x5f6ca0, %eax         # imm = 0x5F6CA0
  58fe08:      	jmp	0x591a45 <.text+0x190a45>
  58fe0d:      	movl	$0x5f6c84, %eax         # imm = 0x5F6C84
  58fe12:      	jmp	0x591a45 <.text+0x190a45>
  58fe17:      	movl	$0x5f6c60, %eax         # imm = 0x5F6C60
  58fe1c:      	jmp	0x591a45 <.text+0x190a45>
  58fe21:      	movl	$0x5f6c44, %eax         # imm = 0x5F6C44
  58fe26:      	jmp	0x591a45 <.text+0x190a45>
  58fe2b:      	movl	$0x5f6c20, %eax         # imm = 0x5F6C20
  58fe30:      	jmp	0x591a45 <.text+0x190a45>
  58fe35:      	movl	$0x5f6bfc, %eax         # imm = 0x5F6BFC
  58fe3a:      	jmp	0x591a45 <.text+0x190a45>
  58fe3f:      	movl	$0x5f6bd8, %eax         # imm = 0x5F6BD8
  58fe44:      	jmp	0x591a45 <.text+0x190a45>
  58fe49:      	movl	$0x5f6bb0, %eax         # imm = 0x5F6BB0
  58fe4e:      	jmp	0x591a45 <.text+0x190a45>
  58fe53:      	movl	$0x5f6b84, %eax         # imm = 0x5F6B84
  58fe58:      	jmp	0x591a45 <.text+0x190a45>
  58fe5d:      	movl	$0x5f6b64, %eax         # imm = 0x5F6B64
  58fe62:      	jmp	0x591a45 <.text+0x190a45>
  58fe67:      	movl	$0x5f6b40, %eax         # imm = 0x5F6B40
  58fe6c:      	jmp	0x591a45 <.text+0x190a45>
  58fe71:      	movl	$0x5f6b20, %eax         # imm = 0x5F6B20
  58fe76:      	jmp	0x591a45 <.text+0x190a45>
  58fe7b:      	movl	$0x5f6af4, %eax         # imm = 0x5F6AF4
  58fe80:      	jmp	0x591a45 <.text+0x190a45>
  58fe85:      	movl	$0x5f6ad0, %eax         # imm = 0x5F6AD0
  58fe8a:      	jmp	0x591a45 <.text+0x190a45>
  58fe8f:      	movl	$0x5f6aac, %eax         # imm = 0x5F6AAC
  58fe94:      	jmp	0x591a45 <.text+0x190a45>
  58fe99:      	movl	$0x5f6a8c, %eax         # imm = 0x5F6A8C
  58fe9e:      	jmp	0x591a45 <.text+0x190a45>
  58fea3:      	movl	$0x5f6a68, %eax         # imm = 0x5F6A68
  58fea8:      	jmp	0x591a45 <.text+0x190a45>
  58fead:      	movl	$0x5f6a40, %eax         # imm = 0x5F6A40
  58feb2:      	jmp	0x591a45 <.text+0x190a45>
  58feb7:      	movl	$0x5f6a0c, %eax         # imm = 0x5F6A0C
  58febc:      	jmp	0x591a45 <.text+0x190a45>
  58fec1:      	movl	$0x5f69f0, %eax         # imm = 0x5F69F0
  58fec6:      	jmp	0x591a45 <.text+0x190a45>
  58fecb:      	movl	$0x5f69cc, %eax         # imm = 0x5F69CC
  58fed0:      	jmp	0x591a45 <.text+0x190a45>
  58fed5:      	movl	$0x5f69a8, %eax         # imm = 0x5F69A8
  58feda:      	jmp	0x591a45 <.text+0x190a45>
  58fedf:      	movl	$0x5f6984, %eax         # imm = 0x5F6984
  58fee4:      	jmp	0x591a45 <.text+0x190a45>
  58fee9:      	movl	$0x5f6964, %eax         # imm = 0x5F6964
  58feee:      	jmp	0x591a45 <.text+0x190a45>
  58fef3:      	movl	$0x5f6940, %eax         # imm = 0x5F6940
  58fef8:      	jmp	0x591a45 <.text+0x190a45>
  58fefd:      	movl	$0x5f691c, %eax         # imm = 0x5F691C
  58ff02:      	jmp	0x591a45 <.text+0x190a45>
  58ff07:      	movl	$0x5f68f8, %eax         # imm = 0x5F68F8
  58ff0c:      	jmp	0x591a45 <.text+0x190a45>
  58ff11:      	movl	$0x5f68cc, %eax         # imm = 0x5F68CC
  58ff16:      	jmp	0x591a45 <.text+0x190a45>
  58ff1b:      	movl	$0x5f68b0, %eax         # imm = 0x5F68B0
  58ff20:      	jmp	0x591a45 <.text+0x190a45>
  58ff25:      	movl	$0x5f6884, %eax         # imm = 0x5F6884
  58ff2a:      	jmp	0x591a45 <.text+0x190a45>
  58ff2f:      	movl	$0x5f6858, %eax         # imm = 0x5F6858
  58ff34:      	jmp	0x591a45 <.text+0x190a45>
  58ff39:      	movl	$0x5f6830, %eax         # imm = 0x5F6830
  58ff3e:      	jmp	0x591a45 <.text+0x190a45>
  58ff43:      	movl	$0x5f6804, %eax         # imm = 0x5F6804
  58ff48:      	jmp	0x591a45 <.text+0x190a45>
  58ff4d:      	movl	$0x5f67d8, %eax         # imm = 0x5F67D8
  58ff52:      	jmp	0x591a45 <.text+0x190a45>
  58ff57:      	movl	$0x5f67a8, %eax         # imm = 0x5F67A8
  58ff5c:      	jmp	0x591a45 <.text+0x190a45>
  58ff61:      	movl	$0x5f6774, %eax         # imm = 0x5F6774
  58ff66:      	jmp	0x591a45 <.text+0x190a45>
  58ff6b:      	movl	$0x5f6754, %eax         # imm = 0x5F6754
  58ff70:      	jmp	0x591a45 <.text+0x190a45>
  58ff75:      	movl	$0x5f672c, %eax         # imm = 0x5F672C
  58ff7a:      	jmp	0x591a45 <.text+0x190a45>
  58ff7f:      	movl	$0x5f6710, %eax         # imm = 0x5F6710
  58ff84:      	jmp	0x591a45 <.text+0x190a45>
  58ff89:      	movl	$0x5f66f4, %eax         # imm = 0x5F66F4
  58ff8e:      	jmp	0x591a45 <.text+0x190a45>
  58ff93:      	movl	$0x5f66d4, %eax         # imm = 0x5F66D4
  58ff98:      	jmp	0x591a45 <.text+0x190a45>
  58ff9d:      	movl	$0x5f66b8, %eax         # imm = 0x5F66B8
  58ffa2:      	jmp	0x591a45 <.text+0x190a45>
  58ffa7:      	movl	$0x5f66a0, %eax         # imm = 0x5F66A0
  58ffac:      	jmp	0x591a45 <.text+0x190a45>
  58ffb1:      	movl	$0x5f667c, %eax         # imm = 0x5F667C
  58ffb6:      	jmp	0x591a45 <.text+0x190a45>
  58ffbb:      	movl	$0x5f6658, %eax         # imm = 0x5F6658
  58ffc0:      	jmp	0x591a45 <.text+0x190a45>
  58ffc5:      	movl	$0x5f6634, %eax         # imm = 0x5F6634
  58ffca:      	jmp	0x591a45 <.text+0x190a45>
  58ffcf:      	movl	$0x5f6620, %eax         # imm = 0x5F6620
  58ffd4:      	jmp	0x591a45 <.text+0x190a45>
  58ffd9:      	movl	$0x5f6608, %eax         # imm = 0x5F6608
  58ffde:      	jmp	0x591a45 <.text+0x190a45>
  58ffe3:      	movl	$0x5f65e0, %eax         # imm = 0x5F65E0
  58ffe8:      	jmp	0x591a45 <.text+0x190a45>
  58ffed:      	movl	$0x5f65bc, %eax         # imm = 0x5F65BC
  58fff2:      	jmp	0x591a45 <.text+0x190a45>
  58fff7:      	movl	$0x5f6590, %eax         # imm = 0x5F6590
  58fffc:      	jmp	0x591a45 <.text+0x190a45>
  590001:      	movl	$0x5f6564, %eax         # imm = 0x5F6564
  590006:      	jmp	0x591a45 <.text+0x190a45>
  59000b:      	movl	$0x2328, %ecx           # imm = 0x2328
  590010:      	cmpl	%ecx, %eax
  590012:      	jg	0x5902c7 <.text+0x18f2c7>
  590018:      	je	0x5902bd <.text+0x18f2bd>
  59001e:      	addl	$0xffffdea7, %eax       # imm = 0xFFFFDEA7
  590023:      	cmpl	$0x40, %eax
  590026:      	ja	0x591a16 <.text+0x190a16>
  59002c:      	jmpl	*0x597161(,%eax,4)
  590033:      	movl	$0x5f653c, %eax         # imm = 0x5F653C
  590038:      	jmp	0x591a45 <.text+0x190a45>
  59003d:      	movl	$0x5f6518, %eax         # imm = 0x5F6518
  590042:      	jmp	0x591a45 <.text+0x190a45>
  590047:      	movl	$0x5f64f4, %eax         # imm = 0x5F64F4
  59004c:      	jmp	0x591a45 <.text+0x190a45>
  590051:      	movl	$0x5f64c8, %eax         # imm = 0x5F64C8
  590056:      	jmp	0x591a45 <.text+0x190a45>
  59005b:      	movl	$0x5f64b0, %eax         # imm = 0x5F64B0
  590060:      	jmp	0x591a45 <.text+0x190a45>
  590065:      	movl	$0x5f6490, %eax         # imm = 0x5F6490
  59006a:      	jmp	0x591a45 <.text+0x190a45>
  59006f:      	movl	$0x5f6470, %eax         # imm = 0x5F6470
  590074:      	jmp	0x591a45 <.text+0x190a45>
  590079:      	movl	$0x5f6448, %eax         # imm = 0x5F6448
  59007e:      	jmp	0x591a45 <.text+0x190a45>
  590083:      	movl	$0x5f6428, %eax         # imm = 0x5F6428
  590088:      	jmp	0x591a45 <.text+0x190a45>
  59008d:      	movl	$0x5f640c, %eax         # imm = 0x5F640C
  590092:      	jmp	0x591a45 <.text+0x190a45>
  590097:      	movl	$0x5f63f4, %eax         # imm = 0x5F63F4
  59009c:      	jmp	0x591a45 <.text+0x190a45>
  5900a1:      	movl	$0x5f63d0, %eax         # imm = 0x5F63D0
  5900a6:      	jmp	0x591a45 <.text+0x190a45>
  5900ab:      	movl	$0x5f63ac, %eax         # imm = 0x5F63AC
  5900b0:      	jmp	0x591a45 <.text+0x190a45>
  5900b5:      	movl	$0x5f6394, %eax         # imm = 0x5F6394
  5900ba:      	jmp	0x591a45 <.text+0x190a45>
  5900bf:      	movl	$0x5f6374, %eax         # imm = 0x5F6374
  5900c4:      	jmp	0x591a45 <.text+0x190a45>
  5900c9:      	movl	$0x5f634c, %eax         # imm = 0x5F634C
  5900ce:      	jmp	0x591a45 <.text+0x190a45>
  5900d3:      	movl	$0x5f6324, %eax         # imm = 0x5F6324
  5900d8:      	jmp	0x591a45 <.text+0x190a45>
  5900dd:      	movl	$0x5f6304, %eax         # imm = 0x5F6304
  5900e2:      	jmp	0x591a45 <.text+0x190a45>
  5900e7:      	movl	$0x5f62dc, %eax         # imm = 0x5F62DC
  5900ec:      	jmp	0x591a45 <.text+0x190a45>
  5900f1:      	movl	$0x5f62b8, %eax         # imm = 0x5F62B8
  5900f6:      	jmp	0x591a45 <.text+0x190a45>
  5900fb:      	movl	$0x5f6290, %eax         # imm = 0x5F6290
  590100:      	jmp	0x591a45 <.text+0x190a45>
  590105:      	movl	$0x5f6270, %eax         # imm = 0x5F6270
  59010a:      	jmp	0x591a45 <.text+0x190a45>
  59010f:      	movl	$0x5f6248, %eax         # imm = 0x5F6248
  590114:      	jmp	0x591a45 <.text+0x190a45>
  590119:      	movl	$0x5f6220, %eax         # imm = 0x5F6220
  59011e:      	jmp	0x591a45 <.text+0x190a45>
  590123:      	movl	$0x5f6200, %eax         # imm = 0x5F6200
  590128:      	jmp	0x591a45 <.text+0x190a45>
  59012d:      	movl	$0x5f61dc, %eax         # imm = 0x5F61DC
  590132:      	jmp	0x591a45 <.text+0x190a45>
  590137:      	movl	$0x5f61b8, %eax         # imm = 0x5F61B8
  59013c:      	jmp	0x591a45 <.text+0x190a45>
  590141:      	movl	$0x5f6194, %eax         # imm = 0x5F6194
  590146:      	jmp	0x591a45 <.text+0x190a45>
  59014b:      	movl	$0x5f6174, %eax         # imm = 0x5F6174
  590150:      	jmp	0x591a45 <.text+0x190a45>
  590155:      	movl	$0x5f6154, %eax         # imm = 0x5F6154
  59015a:      	jmp	0x591a45 <.text+0x190a45>
  59015f:      	movl	$0x5f6134, %eax         # imm = 0x5F6134
  590164:      	jmp	0x591a45 <.text+0x190a45>
  590169:      	movl	$0x5f6118, %eax         # imm = 0x5F6118
  59016e:      	jmp	0x591a45 <.text+0x190a45>
  590173:      	movl	$0x5f60ec, %eax         # imm = 0x5F60EC
  590178:      	jmp	0x591a45 <.text+0x190a45>
  59017d:      	movl	$0x5f60c8, %eax         # imm = 0x5F60C8
  590182:      	jmp	0x591a45 <.text+0x190a45>
  590187:      	movl	$0x5f60ac, %eax         # imm = 0x5F60AC
  59018c:      	jmp	0x591a45 <.text+0x190a45>
  590191:      	movl	$0x5f6084, %eax         # imm = 0x5F6084
  590196:      	jmp	0x591a45 <.text+0x190a45>
  59019b:      	movl	$0x5f6064, %eax         # imm = 0x5F6064
  5901a0:      	jmp	0x591a45 <.text+0x190a45>
  5901a5:      	movl	$0x5f6040, %eax         # imm = 0x5F6040
  5901aa:      	jmp	0x591a45 <.text+0x190a45>
  5901af:      	movl	$0x5f6028, %eax         # imm = 0x5F6028
  5901b4:      	jmp	0x591a45 <.text+0x190a45>
  5901b9:      	movl	$0x5f600c, %eax         # imm = 0x5F600C
  5901be:      	jmp	0x591a45 <.text+0x190a45>
  5901c3:      	movl	$0x5f5fec, %eax         # imm = 0x5F5FEC
  5901c8:      	jmp	0x591a45 <.text+0x190a45>
  5901cd:      	movl	$0x5f5fc4, %eax         # imm = 0x5F5FC4
  5901d2:      	jmp	0x591a45 <.text+0x190a45>
  5901d7:      	movl	$0x5f5f94, %eax         # imm = 0x5F5F94
  5901dc:      	jmp	0x591a45 <.text+0x190a45>
  5901e1:      	movl	$0x5f5f6c, %eax         # imm = 0x5F5F6C
  5901e6:      	jmp	0x591a45 <.text+0x190a45>
  5901eb:      	movl	$0x5f5f44, %eax         # imm = 0x5F5F44
  5901f0:      	jmp	0x591a45 <.text+0x190a45>
  5901f5:      	movl	$0x5f5f20, %eax         # imm = 0x5F5F20
  5901fa:      	jmp	0x591a45 <.text+0x190a45>
  5901ff:      	movl	$0x5f5efc, %eax         # imm = 0x5F5EFC
  590204:      	jmp	0x591a45 <.text+0x190a45>
  590209:      	movl	$0x5f5ed4, %eax         # imm = 0x5F5ED4
  59020e:      	jmp	0x591a45 <.text+0x190a45>
  590213:      	movl	$0x5f5eac, %eax         # imm = 0x5F5EAC
  590218:      	jmp	0x591a45 <.text+0x190a45>
  59021d:      	movl	$0x5f5e84, %eax         # imm = 0x5F5E84
  590222:      	jmp	0x591a45 <.text+0x190a45>
  590227:      	movl	$0x5f5e64, %eax         # imm = 0x5F5E64
  59022c:      	jmp	0x591a45 <.text+0x190a45>
  590231:      	movl	$0x5f5e4c, %eax         # imm = 0x5F5E4C
  590236:      	jmp	0x591a45 <.text+0x190a45>
  59023b:      	movl	$0x5f5e20, %eax         # imm = 0x5F5E20
  590240:      	jmp	0x591a45 <.text+0x190a45>
  590245:      	movl	$0x5f5dfc, %eax         # imm = 0x5F5DFC
  59024a:      	jmp	0x591a45 <.text+0x190a45>
  59024f:      	movl	$0x5f5ddc, %eax         # imm = 0x5F5DDC
  590254:      	jmp	0x591a45 <.text+0x190a45>
  590259:      	movl	$0x5f5db8, %eax         # imm = 0x5F5DB8
  59025e:      	jmp	0x591a45 <.text+0x190a45>
  590263:      	movl	$0x5f5d98, %eax         # imm = 0x5F5D98
  590268:      	jmp	0x591a45 <.text+0x190a45>
  59026d:      	movl	$0x5f5d78, %eax         # imm = 0x5F5D78
  590272:      	jmp	0x591a45 <.text+0x190a45>
  590277:      	movl	$0x5f5d40, %eax         # imm = 0x5F5D40
  59027c:      	jmp	0x591a45 <.text+0x190a45>
  590281:      	movl	$0x5f5d28, %eax         # imm = 0x5F5D28
  590286:      	jmp	0x591a45 <.text+0x190a45>
  59028b:      	movl	$0x5f5d10, %eax         # imm = 0x5F5D10
  590290:      	jmp	0x591a45 <.text+0x190a45>
  590295:      	movl	$0x5f5cf4, %eax         # imm = 0x5F5CF4
  59029a:      	jmp	0x591a45 <.text+0x190a45>
  59029f:      	movl	$0x5f5cd4, %eax         # imm = 0x5F5CD4
  5902a4:      	jmp	0x591a45 <.text+0x190a45>
  5902a9:      	movl	$0x5f5cbc, %eax         # imm = 0x5F5CBC
  5902ae:      	jmp	0x591a45 <.text+0x190a45>
  5902b3:      	movl	$0x5f5c98, %eax         # imm = 0x5F5C98
  5902b8:      	jmp	0x591a45 <.text+0x190a45>
  5902bd:      	movl	$0x5f5c78, %eax         # imm = 0x5F5C78
  5902c2:      	jmp	0x591a45 <.text+0x190a45>
  5902c7:      	movl	$0x251c, %ecx           # imm = 0x251C
  5902cc:      	cmpl	%ecx, %eax
  5902ce:      	jg	0x59037b <.text+0x18f37b>
  5902d4:      	je	0x590371 <.text+0x18f371>
  5902da:      	addl	$0xffffdcd7, %eax       # imm = 0xFFFFDCD7
  5902df:      	cmpl	$0x11, %eax
  5902e2:      	ja	0x591a16 <.text+0x190a16>
  5902e8:      	jmpl	*0x597265(,%eax,4)
  5902ef:      	movl	$0x5f5c58, %eax         # imm = 0x5F5C58
  5902f4:      	jmp	0x591a45 <.text+0x190a45>
  5902f9:      	movl	$0x5f5c38, %eax         # imm = 0x5F5C38
  5902fe:      	jmp	0x591a45 <.text+0x190a45>
  590303:      	movl	$0x5f5c1c, %eax         # imm = 0x5F5C1C
  590308:      	jmp	0x591a45 <.text+0x190a45>
  59030d:      	movl	$0x5f5bfc, %eax         # imm = 0x5F5BFC
  590312:      	jmp	0x591a45 <.text+0x190a45>
  590317:      	movl	$0x5f5be4, %eax         # imm = 0x5F5BE4
  59031c:      	jmp	0x591a45 <.text+0x190a45>
  590321:      	movl	$0x5f5bc8, %eax         # imm = 0x5F5BC8
  590326:      	jmp	0x591a45 <.text+0x190a45>
  59032b:      	movl	$0x5f5bb0, %eax         # imm = 0x5F5BB0
  590330:      	jmp	0x591a45 <.text+0x190a45>
  590335:      	movl	$0x5f5b98, %eax         # imm = 0x5F5B98
  59033a:      	jmp	0x591a45 <.text+0x190a45>
  59033f:      	movl	$0x5f5b80, %eax         # imm = 0x5F5B80
  590344:      	jmp	0x591a45 <.text+0x190a45>
  590349:      	movl	$0x5f5b68, %eax         # imm = 0x5F5B68
  59034e:      	jmp	0x591a45 <.text+0x190a45>
  590353:      	movl	$0x5f5b50, %eax         # imm = 0x5F5B50
  590358:      	jmp	0x591a45 <.text+0x190a45>
  59035d:      	movl	$0x5f5b38, %eax         # imm = 0x5F5B38
  590362:      	jmp	0x591a45 <.text+0x190a45>
  590367:      	movl	$0x5f5b20, %eax         # imm = 0x5F5B20
  59036c:      	jmp	0x591a45 <.text+0x190a45>
  590371:      	movl	$0x5f5b04, %eax         # imm = 0x5F5B04
  590376:      	jmp	0x591a45 <.text+0x190a45>
  59037b:      	movl	$0x361b, %ecx           # imm = 0x361B
  590380:      	cmpl	%ecx, %eax
  590382:      	jg	0x590dc6 <.text+0x18fdc6>
  590388:      	je	0x590dbc <.text+0x18fdbc>
  59038e:      	movl	$0x2757, %ecx           # imm = 0x2757
  590393:      	cmpl	%ecx, %eax
  590395:      	jg	0x590865 <.text+0x18f865>
  59039b:      	je	0x59085b <.text+0x18f85b>
  5903a1:      	addl	$0xffffdae3, %eax       # imm = 0xFFFFDAE3
  5903a6:      	cmpl	$0x239, %eax            # imm = 0x239
  5903ab:      	ja	0x591a16 <.text+0x190a16>
  5903b1:      	movzbl	0x597491(%eax), %eax
  5903b8:      	jmpl	*0x5972ad(,%eax,4)
  5903bf:      	movl	$0x5f5af0, %eax         # imm = 0x5F5AF0
  5903c4:      	jmp	0x591a45 <.text+0x190a45>
  5903c9:      	movl	$0x5f5ad8, %eax         # imm = 0x5F5AD8
  5903ce:      	jmp	0x591a45 <.text+0x190a45>
  5903d3:      	movl	$0x5f5ac4, %eax         # imm = 0x5F5AC4
  5903d8:      	jmp	0x591a45 <.text+0x190a45>
  5903dd:      	movl	$0x5f5ab4, %eax         # imm = 0x5F5AB4
  5903e2:      	jmp	0x591a45 <.text+0x190a45>
  5903e7:      	movl	$0x5f5a98, %eax         # imm = 0x5F5A98
  5903ec:      	jmp	0x591a45 <.text+0x190a45>
  5903f1:      	movl	$0x5f5a7c, %eax         # imm = 0x5F5A7C
  5903f6:      	jmp	0x591a45 <.text+0x190a45>
  5903fb:      	movl	$0x5f5a64, %eax         # imm = 0x5F5A64
  590400:      	jmp	0x591a45 <.text+0x190a45>
  590405:      	movl	$0x5f5a44, %eax         # imm = 0x5F5A44
  59040a:      	jmp	0x591a45 <.text+0x190a45>
  59040f:      	movl	$0x5f5a28, %eax         # imm = 0x5F5A28
  590414:      	jmp	0x591a45 <.text+0x190a45>
  590419:      	movl	$0x5f5a0c, %eax         # imm = 0x5F5A0C
  59041e:      	jmp	0x591a45 <.text+0x190a45>
  590423:      	movl	$0x5f59f4, %eax         # imm = 0x5F59F4
  590428:      	jmp	0x591a45 <.text+0x190a45>
  59042d:      	movl	$0x5f59dc, %eax         # imm = 0x5F59DC
  590432:      	jmp	0x591a45 <.text+0x190a45>
  590437:      	movl	$0x5f59cc, %eax         # imm = 0x5F59CC
  59043c:      	jmp	0x591a45 <.text+0x190a45>
  590441:      	movl	$0x5f59b4, %eax         # imm = 0x5F59B4
  590446:      	jmp	0x591a45 <.text+0x190a45>
  59044b:      	movl	$0x5f5998, %eax         # imm = 0x5F5998
  590450:      	jmp	0x591a45 <.text+0x190a45>
  590455:      	movl	$0x5f5984, %eax         # imm = 0x5F5984
  59045a:      	jmp	0x591a45 <.text+0x190a45>
  59045f:      	movl	$0x5f5964, %eax         # imm = 0x5F5964
  590464:      	jmp	0x591a45 <.text+0x190a45>
  590469:      	movl	$0x5f594c, %eax         # imm = 0x5F594C
  59046e:      	jmp	0x591a45 <.text+0x190a45>
  590473:      	movl	$0x5f5928, %eax         # imm = 0x5F5928
  590478:      	jmp	0x591a45 <.text+0x190a45>
  59047d:      	movl	$0x5f5904, %eax         # imm = 0x5F5904
  590482:      	jmp	0x591a45 <.text+0x190a45>
  590487:      	movl	$0x5f58e0, %eax         # imm = 0x5F58E0
  59048c:      	jmp	0x591a45 <.text+0x190a45>
  590491:      	movl	$0x5f58bc, %eax         # imm = 0x5F58BC
  590496:      	jmp	0x591a45 <.text+0x190a45>
  59049b:      	movl	$0x5f58a4, %eax         # imm = 0x5F58A4
  5904a0:      	jmp	0x591a45 <.text+0x190a45>
  5904a5:      	movl	$0x5f5884, %eax         # imm = 0x5F5884
  5904aa:      	jmp	0x591a45 <.text+0x190a45>
  5904af:      	movl	$0x5f5864, %eax         # imm = 0x5F5864
  5904b4:      	jmp	0x591a45 <.text+0x190a45>
  5904b9:      	movl	$0x5f5840, %eax         # imm = 0x5F5840
  5904be:      	jmp	0x591a45 <.text+0x190a45>
  5904c3:      	movl	$0x5f5824, %eax         # imm = 0x5F5824
  5904c8:      	jmp	0x591a45 <.text+0x190a45>
  5904cd:      	movl	$0x5f57fc, %eax         # imm = 0x5F57FC
  5904d2:      	jmp	0x591a45 <.text+0x190a45>
  5904d7:      	movl	$0x5f57dc, %eax         # imm = 0x5F57DC
  5904dc:      	jmp	0x591a45 <.text+0x190a45>
  5904e1:      	movl	$0x5f57b8, %eax         # imm = 0x5F57B8
  5904e6:      	jmp	0x591a45 <.text+0x190a45>
  5904eb:      	movl	$0x5f579c, %eax         # imm = 0x5F579C
  5904f0:      	jmp	0x591a45 <.text+0x190a45>
  5904f5:      	movl	$0x5f5780, %eax         # imm = 0x5F5780
  5904fa:      	jmp	0x591a45 <.text+0x190a45>
  5904ff:      	movl	$0x5f5760, %eax         # imm = 0x5F5760
  590504:      	jmp	0x591a45 <.text+0x190a45>
  590509:      	movl	$0x5f5740, %eax         # imm = 0x5F5740
  59050e:      	jmp	0x591a45 <.text+0x190a45>
  590513:      	movl	$0x5f5728, %eax         # imm = 0x5F5728
  590518:      	jmp	0x591a45 <.text+0x190a45>
  59051d:      	movl	$0x5f5704, %eax         # imm = 0x5F5704
  590522:      	jmp	0x591a45 <.text+0x190a45>
  590527:      	movl	$0x5f56e4, %eax         # imm = 0x5F56E4
  59052c:      	jmp	0x591a45 <.text+0x190a45>
  590531:      	movl	$0x5f56c4, %eax         # imm = 0x5F56C4
  590536:      	jmp	0x591a45 <.text+0x190a45>
  59053b:      	movl	$0x5f56a4, %eax         # imm = 0x5F56A4
  590540:      	jmp	0x591a45 <.text+0x190a45>
  590545:      	movl	$0x5f5688, %eax         # imm = 0x5F5688
  59054a:      	jmp	0x591a45 <.text+0x190a45>
  59054f:      	movl	$0x5f5670, %eax         # imm = 0x5F5670
  590554:      	jmp	0x591a45 <.text+0x190a45>
  590559:      	movl	$0x5f5650, %eax         # imm = 0x5F5650
  59055e:      	jmp	0x591a45 <.text+0x190a45>
  590563:      	movl	$0x5f5638, %eax         # imm = 0x5F5638
  590568:      	jmp	0x591a45 <.text+0x190a45>
  59056d:      	movl	$0x5f5618, %eax         # imm = 0x5F5618
  590572:      	jmp	0x591a45 <.text+0x190a45>
  590577:      	movl	$0x5f55f8, %eax         # imm = 0x5F55F8
  59057c:      	jmp	0x591a45 <.text+0x190a45>
  590581:      	movl	$0x5f55dc, %eax         # imm = 0x5F55DC
  590586:      	jmp	0x591a45 <.text+0x190a45>
  59058b:      	movl	$0x5f55c0, %eax         # imm = 0x5F55C0
  590590:      	jmp	0x591a45 <.text+0x190a45>
  590595:      	movl	$0x5f55a8, %eax         # imm = 0x5F55A8
  59059a:      	jmp	0x591a45 <.text+0x190a45>
  59059f:      	movl	$0x5f5590, %eax         # imm = 0x5F5590
  5905a4:      	jmp	0x591a45 <.text+0x190a45>
  5905a9:      	movl	$0x5f5574, %eax         # imm = 0x5F5574
  5905ae:      	jmp	0x591a45 <.text+0x190a45>
  5905b3:      	movl	$0x5f5550, %eax         # imm = 0x5F5550
  5905b8:      	jmp	0x591a45 <.text+0x190a45>
  5905bd:      	movl	$0x5f5530, %eax         # imm = 0x5F5530
  5905c2:      	jmp	0x591a45 <.text+0x190a45>
  5905c7:      	movl	$0x5f5514, %eax         # imm = 0x5F5514
  5905cc:      	jmp	0x591a45 <.text+0x190a45>
  5905d1:      	movl	$0x5f54f4, %eax         # imm = 0x5F54F4
  5905d6:      	jmp	0x591a45 <.text+0x190a45>
  5905db:      	movl	$0x5f54d4, %eax         # imm = 0x5F54D4
  5905e0:      	jmp	0x591a45 <.text+0x190a45>
  5905e5:      	movl	$0x5f54b4, %eax         # imm = 0x5F54B4
  5905ea:      	jmp	0x591a45 <.text+0x190a45>
  5905ef:      	movl	$0x5f5494, %eax         # imm = 0x5F5494
  5905f4:      	jmp	0x591a45 <.text+0x190a45>
  5905f9:      	movl	$0x5f5478, %eax         # imm = 0x5F5478
  5905fe:      	jmp	0x591a45 <.text+0x190a45>
  590603:      	movl	$0x5f5454, %eax         # imm = 0x5F5454
  590608:      	jmp	0x591a45 <.text+0x190a45>
  59060d:      	movl	$0x5f5430, %eax         # imm = 0x5F5430
  590612:      	jmp	0x591a45 <.text+0x190a45>
  590617:      	movl	$0x5f5414, %eax         # imm = 0x5F5414
  59061c:      	jmp	0x591a45 <.text+0x190a45>
  590621:      	movl	$0x5f53fc, %eax         # imm = 0x5F53FC
  590626:      	jmp	0x591a45 <.text+0x190a45>
  59062b:      	movl	$0x5f53ec, %eax         # imm = 0x5F53EC
  590630:      	jmp	0x591a45 <.text+0x190a45>
  590635:      	movl	$0x5f53d0, %eax         # imm = 0x5F53D0
  59063a:      	jmp	0x591a45 <.text+0x190a45>
  59063f:      	movl	$0x5f53b8, %eax         # imm = 0x5F53B8
  590644:      	jmp	0x591a45 <.text+0x190a45>
  590649:      	movl	$0x5f53a0, %eax         # imm = 0x5F53A0
  59064e:      	jmp	0x591a45 <.text+0x190a45>
  590653:      	movl	$0x5f538c, %eax         # imm = 0x5F538C
  590658:      	jmp	0x591a45 <.text+0x190a45>
  59065d:      	movl	$0x5f5370, %eax         # imm = 0x5F5370
  590662:      	jmp	0x591a45 <.text+0x190a45>
  590667:      	movl	$0x5f5364, %eax         # imm = 0x5F5364
  59066c:      	jmp	0x591a45 <.text+0x190a45>
  590671:      	movl	$0x5f5358, %eax         # imm = 0x5F5358
  590676:      	jmp	0x591a45 <.text+0x190a45>
  59067b:      	movl	$0x5f534c, %eax         # imm = 0x5F534C
  590680:      	jmp	0x591a45 <.text+0x190a45>
  590685:      	movl	$0x5f5340, %eax         # imm = 0x5F5340
  59068a:      	jmp	0x591a45 <.text+0x190a45>
  59068f:      	movl	$0x5f5334, %eax         # imm = 0x5F5334
  590694:      	jmp	0x591a45 <.text+0x190a45>
  590699:      	movl	$0x5f5328, %eax         # imm = 0x5F5328
  59069e:      	jmp	0x591a45 <.text+0x190a45>
  5906a3:      	movl	$0x5f531c, %eax         # imm = 0x5F531C
  5906a8:      	jmp	0x591a45 <.text+0x190a45>
  5906ad:      	movl	$0x5f530c, %eax         # imm = 0x5F530C
  5906b2:      	jmp	0x591a45 <.text+0x190a45>
  5906b7:      	movl	$0x5f52fc, %eax         # imm = 0x5F52FC
  5906bc:      	jmp	0x591a45 <.text+0x190a45>
  5906c1:      	movl	$0x5f52f0, %eax         # imm = 0x5F52F0
  5906c6:      	jmp	0x591a45 <.text+0x190a45>
  5906cb:      	movl	$0x5f52e4, %eax         # imm = 0x5F52E4
  5906d0:      	jmp	0x591a45 <.text+0x190a45>
  5906d5:      	movl	$0x5f52d4, %eax         # imm = 0x5F52D4
  5906da:      	jmp	0x591a45 <.text+0x190a45>
  5906df:      	movl	$0x5f52c8, %eax         # imm = 0x5F52C8
  5906e4:      	jmp	0x591a45 <.text+0x190a45>
  5906e9:      	movl	$0x5f52b8, %eax         # imm = 0x5F52B8
  5906ee:      	jmp	0x591a45 <.text+0x190a45>
  5906f3:      	movl	$0x5f52a8, %eax         # imm = 0x5F52A8
  5906f8:      	jmp	0x591a45 <.text+0x190a45>
  5906fd:      	movl	$0x5f5294, %eax         # imm = 0x5F5294
  590702:      	jmp	0x591a45 <.text+0x190a45>
  590707:      	movl	$0x5f5280, %eax         # imm = 0x5F5280
  59070c:      	jmp	0x591a45 <.text+0x190a45>
  590711:      	movl	$0x5f5270, %eax         # imm = 0x5F5270
  590716:      	jmp	0x591a45 <.text+0x190a45>
  59071b:      	movl	$0x5f5260, %eax         # imm = 0x5F5260
  590720:      	jmp	0x591a45 <.text+0x190a45>
  590725:      	movl	$0x5f5250, %eax         # imm = 0x5F5250
  59072a:      	jmp	0x591a45 <.text+0x190a45>
  59072f:      	movl	$0x5f5240, %eax         # imm = 0x5F5240
  590734:      	jmp	0x591a45 <.text+0x190a45>
  590739:      	movl	$0x5f522c, %eax         # imm = 0x5F522C
  59073e:      	jmp	0x591a45 <.text+0x190a45>
  590743:      	movl	$0x5f5220, %eax         # imm = 0x5F5220
  590748:      	jmp	0x591a45 <.text+0x190a45>
  59074d:      	movl	$0x5f5210, %eax         # imm = 0x5F5210
  590752:      	jmp	0x591a45 <.text+0x190a45>
  590757:      	movl	$0x5f5200, %eax         # imm = 0x5F5200
  59075c:      	jmp	0x591a45 <.text+0x190a45>
  590761:      	movl	$0x5f51f0, %eax         # imm = 0x5F51F0
  590766:      	jmp	0x591a45 <.text+0x190a45>
  59076b:      	movl	$0x5f51e0, %eax         # imm = 0x5F51E0
  590770:      	jmp	0x591a45 <.text+0x190a45>
  590775:      	movl	$0x5f51d4, %eax         # imm = 0x5F51D4
  59077a:      	jmp	0x591a45 <.text+0x190a45>
  59077f:      	movl	$0x5f51c8, %eax         # imm = 0x5F51C8
  590784:      	jmp	0x591a45 <.text+0x190a45>
  590789:      	movl	$0x5f51bc, %eax         # imm = 0x5F51BC
  59078e:      	jmp	0x591a45 <.text+0x190a45>
  590793:      	movl	$0x5f51ac, %eax         # imm = 0x5F51AC
  590798:      	jmp	0x591a45 <.text+0x190a45>
  59079d:      	movl	$0x5f519c, %eax         # imm = 0x5F519C
  5907a2:      	jmp	0x591a45 <.text+0x190a45>
  5907a7:      	movl	$0x5f518c, %eax         # imm = 0x5F518C
  5907ac:      	jmp	0x591a45 <.text+0x190a45>
  5907b1:      	movl	$0x5f517c, %eax         # imm = 0x5F517C
  5907b6:      	jmp	0x591a45 <.text+0x190a45>
  5907bb:      	movl	$0x5f5170, %eax         # imm = 0x5F5170
  5907c0:      	jmp	0x591a45 <.text+0x190a45>
  5907c5:      	movl	$0x5f5160, %eax         # imm = 0x5F5160
  5907ca:      	jmp	0x591a45 <.text+0x190a45>
  5907cf:      	movl	$0x5f5150, %eax         # imm = 0x5F5150
  5907d4:      	jmp	0x591a45 <.text+0x190a45>
  5907d9:      	movl	$0x5f5140, %eax         # imm = 0x5F5140
  5907de:      	jmp	0x591a45 <.text+0x190a45>
  5907e3:      	movl	$0x5f5130, %eax         # imm = 0x5F5130
  5907e8:      	jmp	0x591a45 <.text+0x190a45>
  5907ed:      	movl	$0x5f5124, %eax         # imm = 0x5F5124
  5907f2:      	jmp	0x591a45 <.text+0x190a45>
  5907f7:      	movl	$0x5f5118, %eax         # imm = 0x5F5118
  5907fc:      	jmp	0x591a45 <.text+0x190a45>
  590801:      	movl	$0x5f510c, %eax         # imm = 0x5F510C
  590806:      	jmp	0x591a45 <.text+0x190a45>
  59080b:      	movl	$0x5f5100, %eax         # imm = 0x5F5100
  590810:      	jmp	0x591a45 <.text+0x190a45>
  590815:      	movl	$0x5f50dc, %eax         # imm = 0x5F50DC
  59081a:      	jmp	0x591a45 <.text+0x190a45>
  59081f:      	movl	$0x5f50b8, %eax         # imm = 0x5F50B8
  590824:      	jmp	0x591a45 <.text+0x190a45>
  590829:      	movl	$0x5f509c, %eax         # imm = 0x5F509C
  59082e:      	jmp	0x591a45 <.text+0x190a45>
  590833:      	movl	$0x5f5088, %eax         # imm = 0x5F5088
  590838:      	jmp	0x591a45 <.text+0x190a45>
  59083d:      	movl	$0x5f506c, %eax         # imm = 0x5F506C
  590842:      	jmp	0x591a45 <.text+0x190a45>
  590847:      	movl	$0x5f5050, %eax         # imm = 0x5F5050
  59084c:      	jmp	0x591a45 <.text+0x190a45>
  590851:      	movl	$0x5f5034, %eax         # imm = 0x5F5034
  590856:      	jmp	0x591a45 <.text+0x190a45>
  59085b:      	movl	$0x5f5028, %eax         # imm = 0x5F5028
  590860:      	jmp	0x591a45 <.text+0x190a45>
  590865:      	movl	$0x32d5, %ecx           # imm = 0x32D5
  59086a:      	cmpl	%ecx, %eax
  59086c:      	jg	0x590b49 <.text+0x18fb49>
  590872:      	je	0x590b3f <.text+0x18fb3f>
  590878:      	movl	$0x2b07, %ecx           # imm = 0x2B07
  59087d:      	cmpl	%ecx, %eax
  59087f:      	jg	0x5909e0 <.text+0x18f9e0>
  590885:      	je	0x5909d6 <.text+0x18f9d6>
  59088b:      	movl	$0x2780, %ecx           # imm = 0x2780
  590890:      	cmpl	%ecx, %eax
  590892:      	jg	0x59093f <.text+0x18f93f>
  590898:      	je	0x590935 <.text+0x18f935>
  59089e:      	addl	$0xffffd895, %eax       # imm = 0xFFFFD895
  5908a3:      	cmpl	$0x14, %eax
  5908a6:      	ja	0x591a16 <.text+0x190a16>
  5908ac:      	jmpl	*0x5976cd(,%eax,4)
  5908b3:      	movl	$0x5f5018, %eax         # imm = 0x5F5018
  5908b8:      	jmp	0x591a45 <.text+0x190a45>
  5908bd:      	movl	$0x5f5004, %eax         # imm = 0x5F5004
  5908c2:      	jmp	0x591a45 <.text+0x190a45>
  5908c7:      	movl	$0x5f4ff0, %eax         # imm = 0x5F4FF0
  5908cc:      	jmp	0x591a45 <.text+0x190a45>
  5908d1:      	movl	$0x5f4fe4, %eax         # imm = 0x5F4FE4
  5908d6:      	jmp	0x591a45 <.text+0x190a45>
  5908db:      	movl	$0x5f4fd8, %eax         # imm = 0x5F4FD8
  5908e0:      	jmp	0x591a45 <.text+0x190a45>
  5908e5:      	movl	$0x5f4fc8, %eax         # imm = 0x5F4FC8
  5908ea:      	jmp	0x591a45 <.text+0x190a45>
  5908ef:      	movl	$0x5f4fb0, %eax         # imm = 0x5F4FB0
  5908f4:      	jmp	0x591a45 <.text+0x190a45>
  5908f9:      	movl	$0x5f4f9c, %eax         # imm = 0x5F4F9C
  5908fe:      	jmp	0x591a45 <.text+0x190a45>
  590903:      	movl	$0x5f4f88, %eax         # imm = 0x5F4F88
  590908:      	jmp	0x591a45 <.text+0x190a45>
  59090d:      	movl	$0x5f4f70, %eax         # imm = 0x5F4F70
  590912:      	jmp	0x591a45 <.text+0x190a45>
  590917:      	movl	$0x5f4f5c, %eax         # imm = 0x5F4F5C
  59091c:      	jmp	0x591a45 <.text+0x190a45>
  590921:      	movl	$0x5f4f4c, %eax         # imm = 0x5F4F4C
  590926:      	jmp	0x591a45 <.text+0x190a45>
  59092b:      	movl	$0x5f4f3c, %eax         # imm = 0x5F4F3C
  590930:      	jmp	0x591a45 <.text+0x190a45>
  590935:      	movl	$0x5f4f30, %eax         # imm = 0x5F4F30
  59093a:      	jmp	0x591a45 <.text+0x190a45>
  59093f:      	addl	$0xffffd507, %eax       # imm = 0xFFFFD507
  590944:      	cmpl	$0xd, %eax
  590947:      	ja	0x591a16 <.text+0x190a16>
  59094d:      	jmpl	*0x597721(,%eax,4)
  590954:      	movl	$0x5f4f1c, %eax         # imm = 0x5F4F1C
  590959:      	jmp	0x591a45 <.text+0x190a45>
  59095e:      	movl	$0x5f4f0c, %eax         # imm = 0x5F4F0C
  590963:      	jmp	0x591a45 <.text+0x190a45>
  590968:      	movl	$0x5f4f00, %eax         # imm = 0x5F4F00
  59096d:      	jmp	0x591a45 <.text+0x190a45>
  590972:      	movl	$0x5f4eec, %eax         # imm = 0x5F4EEC
  590977:      	jmp	0x591a45 <.text+0x190a45>
  59097c:      	movl	$0x5f4edc, %eax         # imm = 0x5F4EDC
  590981:      	jmp	0x591a45 <.text+0x190a45>
  590986:      	movl	$0x5f4ec8, %eax         # imm = 0x5F4EC8
  59098b:      	jmp	0x591a45 <.text+0x190a45>
  590990:      	movl	$0x5f4eb0, %eax         # imm = 0x5F4EB0
  590995:      	jmp	0x591a45 <.text+0x190a45>
  59099a:      	movl	$0x5f4e94, %eax         # imm = 0x5F4E94
  59099f:      	jmp	0x591a45 <.text+0x190a45>
  5909a4:      	movl	$0x5f4e78, %eax         # imm = 0x5F4E78
  5909a9:      	jmp	0x591a45 <.text+0x190a45>
  5909ae:      	movl	$0x5f4e60, %eax         # imm = 0x5F4E60
  5909b3:      	jmp	0x591a45 <.text+0x190a45>
  5909b8:      	movl	$0x5f4e4c, %eax         # imm = 0x5F4E4C
  5909bd:      	jmp	0x591a45 <.text+0x190a45>
  5909c2:      	movl	$0x5f4e38, %eax         # imm = 0x5F4E38
  5909c7:      	jmp	0x591a45 <.text+0x190a45>
  5909cc:      	movl	$0x5f4e1c, %eax         # imm = 0x5F4E1C
  5909d1:      	jmp	0x591a45 <.text+0x190a45>
  5909d6:      	movl	$0x5f4e04, %eax         # imm = 0x5F4E04
  5909db:      	jmp	0x591a45 <.text+0x190a45>
  5909e0:      	movl	$0x32c8, %ecx           # imm = 0x32C8
  5909e5:      	cmpl	%ecx, %eax
  5909e7:      	jg	0x590ab2 <.text+0x18fab2>
  5909ed:      	je	0x590aa8 <.text+0x18faa8>
  5909f3:      	addl	$0xffffd4f8, %eax       # imm = 0xFFFFD4F8
  5909f8:      	cmpl	$0xf, %eax
  5909fb:      	ja	0x591a16 <.text+0x190a16>
  590a01:      	jmpl	*0x597759(,%eax,4)
  590a08:      	movl	$0x5f4dec, %eax         # imm = 0x5F4DEC
  590a0d:      	jmp	0x591a45 <.text+0x190a45>
  590a12:      	movl	$0x5f4dd8, %eax         # imm = 0x5F4DD8
  590a17:      	jmp	0x591a45 <.text+0x190a45>
  590a1c:      	movl	$0x5f4dc0, %eax         # imm = 0x5F4DC0
  590a21:      	jmp	0x591a45 <.text+0x190a45>
  590a26:      	movl	$0x5f4da8, %eax         # imm = 0x5F4DA8
  590a2b:      	jmp	0x591a45 <.text+0x190a45>
  590a30:      	movl	$0x5f4d94, %eax         # imm = 0x5F4D94
  590a35:      	jmp	0x591a45 <.text+0x190a45>
  590a3a:      	movl	$0x5f4d7c, %eax         # imm = 0x5F4D7C
  590a3f:      	jmp	0x591a45 <.text+0x190a45>
  590a44:      	movl	$0x5f4d68, %eax         # imm = 0x5F4D68
  590a49:      	jmp	0x591a45 <.text+0x190a45>
  590a4e:      	movl	$0x5f4d54, %eax         # imm = 0x5F4D54
  590a53:      	jmp	0x591a45 <.text+0x190a45>
  590a58:      	movl	$0x5f4d3c, %eax         # imm = 0x5F4D3C
  590a5d:      	jmp	0x591a45 <.text+0x190a45>
  590a62:      	movl	$0x5f4d28, %eax         # imm = 0x5F4D28
  590a67:      	jmp	0x591a45 <.text+0x190a45>
  590a6c:      	movl	$0x5f4d14, %eax         # imm = 0x5F4D14
  590a71:      	jmp	0x591a45 <.text+0x190a45>
  590a76:      	movl	$0x5f4d00, %eax         # imm = 0x5F4D00
  590a7b:      	jmp	0x591a45 <.text+0x190a45>
  590a80:      	movl	$0x5f4ce8, %eax         # imm = 0x5F4CE8
  590a85:      	jmp	0x591a45 <.text+0x190a45>
  590a8a:      	movl	$0x5f4cd4, %eax         # imm = 0x5F4CD4
  590a8f:      	jmp	0x591a45 <.text+0x190a45>
  590a94:      	movl	$0x5f4cbc, %eax         # imm = 0x5F4CBC
  590a99:      	jmp	0x591a45 <.text+0x190a45>
  590a9e:      	movl	$0x5f4ca4, %eax         # imm = 0x5F4CA4
  590aa3:      	jmp	0x591a45 <.text+0x190a45>
  590aa8:      	movl	$0x5f4c84, %eax         # imm = 0x5F4C84
  590aad:      	jmp	0x591a45 <.text+0x190a45>
  590ab2:      	addl	$0xffffcd37, %eax       # imm = 0xFFFFCD37
  590ab7:      	cmpl	$0xb, %eax
  590aba:      	ja	0x591a16 <.text+0x190a16>
  590ac0:      	jmpl	*0x597799(,%eax,4)
  590ac7:      	movl	$0x5f4c64, %eax         # imm = 0x5F4C64
  590acc:      	jmp	0x591a45 <.text+0x190a45>
  590ad1:      	movl	$0x5f4c44, %eax         # imm = 0x5F4C44
  590ad6:      	jmp	0x591a45 <.text+0x190a45>
  590adb:      	movl	$0x5f4c24, %eax         # imm = 0x5F4C24
  590ae0:      	jmp	0x591a45 <.text+0x190a45>
  590ae5:      	movl	$0x5f4c04, %eax         # imm = 0x5F4C04
  590aea:      	jmp	0x591a45 <.text+0x190a45>
  590aef:      	movl	$0x5f4be4, %eax         # imm = 0x5F4BE4
  590af4:      	jmp	0x591a45 <.text+0x190a45>
  590af9:      	movl	$0x5f4bc4, %eax         # imm = 0x5F4BC4
  590afe:      	jmp	0x591a45 <.text+0x190a45>
  590b03:      	movl	$0x5f4ba4, %eax         # imm = 0x5F4BA4
  590b08:      	jmp	0x591a45 <.text+0x190a45>
  590b0d:      	movl	$0x5f4b80, %eax         # imm = 0x5F4B80
  590b12:      	jmp	0x591a45 <.text+0x190a45>
  590b17:      	movl	$0x5f4b58, %eax         # imm = 0x5F4B58
  590b1c:      	jmp	0x591a45 <.text+0x190a45>
  590b21:      	movl	$0x5f4b3c, %eax         # imm = 0x5F4B3C
  590b26:      	jmp	0x591a45 <.text+0x190a45>
  590b2b:      	movl	$0x5f4b1c, %eax         # imm = 0x5F4B1C
  590b30:      	jmp	0x591a45 <.text+0x190a45>
  590b35:      	movl	$0x5f4b00, %eax         # imm = 0x5F4B00
  590b3a:      	jmp	0x591a45 <.text+0x190a45>
  590b3f:      	movl	$0x5f4ad8, %eax         # imm = 0x5F4AD8
  590b44:      	jmp	0x591a45 <.text+0x190a45>
  590b49:      	movl	$0x35e8, %ecx           # imm = 0x35E8
  590b4e:      	cmpl	%ecx, %eax
  590b50:      	jg	0x590bd1 <.text+0x18fbd1>
  590b52:      	je	0x58944c <.text+0x18844c>
  590b58:      	addl	$0xffffcd2a, %eax       # imm = 0xFFFFCD2A
  590b5d:      	cmpl	$0x9, %eax
  590b60:      	ja	0x591a16 <.text+0x190a16>
  590b66:      	jmpl	*0x5977c9(,%eax,4)
  590b6d:      	movl	$0x5f4ab0, %eax         # imm = 0x5F4AB0
  590b72:      	jmp	0x591a45 <.text+0x190a45>
  590b77:      	movl	$0x5f4a88, %eax         # imm = 0x5F4A88
  590b7c:      	jmp	0x591a45 <.text+0x190a45>
  590b81:      	movl	$0x5f4a64, %eax         # imm = 0x5F4A64
  590b86:      	jmp	0x591a45 <.text+0x190a45>
  590b8b:      	movl	$0x5f4a40, %eax         # imm = 0x5F4A40
  590b90:      	jmp	0x591a45 <.text+0x190a45>
  590b95:      	movl	$0x5f4a18, %eax         # imm = 0x5F4A18
  590b9a:      	jmp	0x591a45 <.text+0x190a45>
  590b9f:      	movl	$0x5f49e8, %eax         # imm = 0x5F49E8
  590ba4:      	jmp	0x591a45 <.text+0x190a45>
  590ba9:      	movl	$0x5f49bc, %eax         # imm = 0x5F49BC
  590bae:      	jmp	0x591a45 <.text+0x190a45>
  590bb3:      	movl	$0x5f4994, %eax         # imm = 0x5F4994
  590bb8:      	jmp	0x591a45 <.text+0x190a45>
  590bbd:      	movl	$0x5f496c, %eax         # imm = 0x5F496C
  590bc2:      	jmp	0x591a45 <.text+0x190a45>
  590bc7:      	movl	$0x5f4944, %eax         # imm = 0x5F4944
  590bcc:      	jmp	0x591a45 <.text+0x190a45>
  590bd1:      	addl	$0xffffca17, %eax       # imm = 0xFFFFCA17
  590bd6:      	cmpl	$0x31, %eax
  590bd9:      	ja	0x591a16 <.text+0x190a16>
  590bdf:      	jmpl	*0x5977f1(,%eax,4)
  590be6:      	movl	$0x5f4928, %eax         # imm = 0x5F4928
  590beb:      	jmp	0x591a45 <.text+0x190a45>
  590bf0:      	movl	$0x5f490c, %eax         # imm = 0x5F490C
  590bf5:      	jmp	0x591a45 <.text+0x190a45>
  590bfa:      	movl	$0x5f48e8, %eax         # imm = 0x5F48E8
  590bff:      	jmp	0x591a45 <.text+0x190a45>
  590c04:      	movl	$0x5f48bc, %eax         # imm = 0x5F48BC
  590c09:      	jmp	0x591a45 <.text+0x190a45>
  590c0e:      	movl	$0x5f48a0, %eax         # imm = 0x5F48A0
  590c13:      	jmp	0x591a45 <.text+0x190a45>
  590c18:      	movl	$0x5f4888, %eax         # imm = 0x5F4888
  590c1d:      	jmp	0x591a45 <.text+0x190a45>
  590c22:      	movl	$0x5f486c, %eax         # imm = 0x5F486C
  590c27:      	jmp	0x591a45 <.text+0x190a45>
  590c2c:      	movl	$0x5f484c, %eax         # imm = 0x5F484C
  590c31:      	jmp	0x591a45 <.text+0x190a45>
  590c36:      	movl	$0x5f482c, %eax         # imm = 0x5F482C
  590c3b:      	jmp	0x591a45 <.text+0x190a45>
  590c40:      	movl	$0x5f480c, %eax         # imm = 0x5F480C
  590c45:      	jmp	0x591a45 <.text+0x190a45>
  590c4a:      	movl	$0x5f47e8, %eax         # imm = 0x5F47E8
  590c4f:      	jmp	0x591a45 <.text+0x190a45>
  590c54:      	movl	$0x5f47c4, %eax         # imm = 0x5F47C4
  590c59:      	jmp	0x591a45 <.text+0x190a45>
  590c5e:      	movl	$0x5f47a4, %eax         # imm = 0x5F47A4
  590c63:      	jmp	0x591a45 <.text+0x190a45>
  590c68:      	movl	$0x5f4784, %eax         # imm = 0x5F4784
  590c6d:      	jmp	0x591a45 <.text+0x190a45>
  590c72:      	movl	$0x5f476c, %eax         # imm = 0x5F476C
  590c77:      	jmp	0x591a45 <.text+0x190a45>
  590c7c:      	movl	$0x5f4750, %eax         # imm = 0x5F4750
  590c81:      	jmp	0x591a45 <.text+0x190a45>
  590c86:      	movl	$0x5f472c, %eax         # imm = 0x5F472C
  590c8b:      	jmp	0x591a45 <.text+0x190a45>
  590c90:      	movl	$0x5f4708, %eax         # imm = 0x5F4708
  590c95:      	jmp	0x591a45 <.text+0x190a45>
  590c9a:      	movl	$0x5f46e8, %eax         # imm = 0x5F46E8
  590c9f:      	jmp	0x591a45 <.text+0x190a45>
  590ca4:      	movl	$0x5f46d0, %eax         # imm = 0x5F46D0
  590ca9:      	jmp	0x591a45 <.text+0x190a45>
  590cae:      	movl	$0x5f46b0, %eax         # imm = 0x5F46B0
  590cb3:      	jmp	0x591a45 <.text+0x190a45>
  590cb8:      	movl	$0x5f4694, %eax         # imm = 0x5F4694
  590cbd:      	jmp	0x591a45 <.text+0x190a45>
  590cc2:      	movl	$0x5f4670, %eax         # imm = 0x5F4670
  590cc7:      	jmp	0x591a45 <.text+0x190a45>
  590ccc:      	movl	$0x5f4650, %eax         # imm = 0x5F4650
  590cd1:      	jmp	0x591a45 <.text+0x190a45>
  590cd6:      	movl	$0x5f4630, %eax         # imm = 0x5F4630
  590cdb:      	jmp	0x591a45 <.text+0x190a45>
  590ce0:      	movl	$0x5f4614, %eax         # imm = 0x5F4614
  590ce5:      	jmp	0x591a45 <.text+0x190a45>
  590cea:      	movl	$0x5f45f4, %eax         # imm = 0x5F45F4
  590cef:      	jmp	0x591a45 <.text+0x190a45>
  590cf4:      	movl	$0x5f45d0, %eax         # imm = 0x5F45D0
  590cf9:      	jmp	0x591a45 <.text+0x190a45>
  590cfe:      	movl	$0x5f45ac, %eax         # imm = 0x5F45AC
  590d03:      	jmp	0x591a45 <.text+0x190a45>
  590d08:      	movl	$0x5f458c, %eax         # imm = 0x5F458C
  590d0d:      	jmp	0x591a45 <.text+0x190a45>
  590d12:      	movl	$0x5f456c, %eax         # imm = 0x5F456C
  590d17:      	jmp	0x591a45 <.text+0x190a45>
  590d1c:      	movl	$0x5f4548, %eax         # imm = 0x5F4548
  590d21:      	jmp	0x591a45 <.text+0x190a45>
  590d26:      	movl	$0x5f4520, %eax         # imm = 0x5F4520
  590d2b:      	jmp	0x591a45 <.text+0x190a45>
  590d30:      	movl	$0x5f44fc, %eax         # imm = 0x5F44FC
  590d35:      	jmp	0x591a45 <.text+0x190a45>
  590d3a:      	movl	$0x5f44dc, %eax         # imm = 0x5F44DC
  590d3f:      	jmp	0x591a45 <.text+0x190a45>
  590d44:      	movl	$0x5f44b8, %eax         # imm = 0x5F44B8
  590d49:      	jmp	0x591a45 <.text+0x190a45>
  590d4e:      	movl	$0x5f4494, %eax         # imm = 0x5F4494
  590d53:      	jmp	0x591a45 <.text+0x190a45>
  590d58:      	movl	$0x5f4470, %eax         # imm = 0x5F4470
  590d5d:      	jmp	0x591a45 <.text+0x190a45>
  590d62:      	movl	$0x5f444c, %eax         # imm = 0x5F444C
  590d67:      	jmp	0x591a45 <.text+0x190a45>
  590d6c:      	movl	$0x5f442c, %eax         # imm = 0x5F442C
  590d71:      	jmp	0x591a45 <.text+0x190a45>
  590d76:      	movl	$0x5f440c, %eax         # imm = 0x5F440C
  590d7b:      	jmp	0x591a45 <.text+0x190a45>
  590d80:      	movl	$0x5f43e8, %eax         # imm = 0x5F43E8
  590d85:      	jmp	0x591a45 <.text+0x190a45>
  590d8a:      	movl	$0x5f43c8, %eax         # imm = 0x5F43C8
  590d8f:      	jmp	0x591a45 <.text+0x190a45>
  590d94:      	movl	$0x5f43a8, %eax         # imm = 0x5F43A8
  590d99:      	jmp	0x591a45 <.text+0x190a45>
  590d9e:      	movl	$0x5f4388, %eax         # imm = 0x5F4388
  590da3:      	jmp	0x591a45 <.text+0x190a45>
  590da8:      	movl	$0x5f4368, %eax         # imm = 0x5F4368
  590dad:      	jmp	0x591a45 <.text+0x190a45>
  590db2:      	movl	$0x5f4348, %eax         # imm = 0x5F4348
  590db7:      	jmp	0x591a45 <.text+0x190a45>
  590dbc:      	movl	$0x5f432c, %eax         # imm = 0x5F432C
  590dc1:      	jmp	0x591a45 <.text+0x190a45>
  590dc6:      	movl	$0x3649, %ecx           # imm = 0x3649
  590dcb:      	cmpl	%ecx, %eax
  590dcd:      	jg	0x590f2e <.text+0x18ff2e>
  590dd3:      	je	0x590f24 <.text+0x18ff24>
  590dd9:      	addl	$0xffffc9e4, %eax       # imm = 0xFFFFC9E4
  590dde:      	cmpl	$0x1f, %eax
  590de1:      	ja	0x591a16 <.text+0x190a16>
  590de7:      	jmpl	*0x5978b9(,%eax,4)
  590dee:      	movl	$0x5f4310, %eax         # imm = 0x5F4310
  590df3:      	jmp	0x591a45 <.text+0x190a45>
  590df8:      	movl	$0x5f42f4, %eax         # imm = 0x5F42F4
  590dfd:      	jmp	0x591a45 <.text+0x190a45>
  590e02:      	movl	$0x5f42d4, %eax         # imm = 0x5F42D4
  590e07:      	jmp	0x591a45 <.text+0x190a45>
  590e0c:      	movl	$0x5f42b8, %eax         # imm = 0x5F42B8
  590e11:      	jmp	0x591a45 <.text+0x190a45>
  590e16:      	movl	$0x5f4298, %eax         # imm = 0x5F4298
  590e1b:      	jmp	0x591a45 <.text+0x190a45>
  590e20:      	movl	$0x5f427c, %eax         # imm = 0x5F427C
  590e25:      	jmp	0x591a45 <.text+0x190a45>
  590e2a:      	movl	$0x5f425c, %eax         # imm = 0x5F425C
  590e2f:      	jmp	0x591a45 <.text+0x190a45>
  590e34:      	movl	$0x5f423c, %eax         # imm = 0x5F423C
  590e39:      	jmp	0x591a45 <.text+0x190a45>
  590e3e:      	movl	$0x5f4214, %eax         # imm = 0x5F4214
  590e43:      	jmp	0x591a45 <.text+0x190a45>
  590e48:      	movl	$0x5f41f4, %eax         # imm = 0x5F41F4
  590e4d:      	jmp	0x591a45 <.text+0x190a45>
  590e52:      	movl	$0x5f41d8, %eax         # imm = 0x5F41D8
  590e57:      	jmp	0x591a45 <.text+0x190a45>
  590e5c:      	movl	$0x5f41b4, %eax         # imm = 0x5F41B4
  590e61:      	jmp	0x591a45 <.text+0x190a45>
  590e66:      	movl	$0x5f4198, %eax         # imm = 0x5F4198
  590e6b:      	jmp	0x591a45 <.text+0x190a45>
  590e70:      	movl	$0x5f4178, %eax         # imm = 0x5F4178
  590e75:      	jmp	0x591a45 <.text+0x190a45>
  590e7a:      	movl	$0x5f4160, %eax         # imm = 0x5F4160
  590e7f:      	jmp	0x591a45 <.text+0x190a45>
  590e84:      	movl	$0x5f4148, %eax         # imm = 0x5F4148
  590e89:      	jmp	0x591a45 <.text+0x190a45>
  590e8e:      	movl	$0x5f4128, %eax         # imm = 0x5F4128
  590e93:      	jmp	0x591a45 <.text+0x190a45>
  590e98:      	movl	$0x5f4108, %eax         # imm = 0x5F4108
  590e9d:      	jmp	0x591a45 <.text+0x190a45>
  590ea2:      	movl	$0x5f40e8, %eax         # imm = 0x5F40E8
  590ea7:      	jmp	0x591a45 <.text+0x190a45>
  590eac:      	movl	$0x5f40c4, %eax         # imm = 0x5F40C4
  590eb1:      	jmp	0x591a45 <.text+0x190a45>
  590eb6:      	movl	$0x5f40a0, %eax         # imm = 0x5F40A0
  590ebb:      	jmp	0x591a45 <.text+0x190a45>
  590ec0:      	movl	$0x5f407c, %eax         # imm = 0x5F407C
  590ec5:      	jmp	0x591a45 <.text+0x190a45>
  590eca:      	movl	$0x5f4058, %eax         # imm = 0x5F4058
  590ecf:      	jmp	0x591a45 <.text+0x190a45>
  590ed4:      	movl	$0x5f403c, %eax         # imm = 0x5F403C
  590ed9:      	jmp	0x591a45 <.text+0x190a45>
  590ede:      	movl	$0x5f4020, %eax         # imm = 0x5F4020
  590ee3:      	jmp	0x591a45 <.text+0x190a45>
  590ee8:      	movl	$0x5f4004, %eax         # imm = 0x5F4004
  590eed:      	jmp	0x591a45 <.text+0x190a45>
  590ef2:      	movl	$0x5f3fe4, %eax         # imm = 0x5F3FE4
  590ef7:      	jmp	0x591a45 <.text+0x190a45>
  590efc:      	movl	$0x5f3fb0, %eax         # imm = 0x5F3FB0
  590f01:      	jmp	0x591a45 <.text+0x190a45>
  590f06:      	movl	$0x5f3f8c, %eax         # imm = 0x5F3F8C
  590f0b:      	jmp	0x591a45 <.text+0x190a45>
  590f10:      	movl	$0x5f3f70, %eax         # imm = 0x5F3F70
  590f15:      	jmp	0x591a45 <.text+0x190a45>
  590f1a:      	movl	$0x5f3f48, %eax         # imm = 0x5F3F48
  590f1f:      	jmp	0x591a45 <.text+0x190a45>
  590f24:      	movl	$0x5f3f28, %eax         # imm = 0x5F3F28
  590f29:      	jmp	0x591a45 <.text+0x190a45>
  590f2e:      	movl	$0x30200, %ecx          # imm = 0x30200
  590f33:      	cmpl	%ecx, %eax
  590f35:      	jg	0x59128a <.text+0x19028a>
  590f3b:      	je	0x591280 <.text+0x190280>
  590f41:      	addl	$0xffffc950, %eax       # imm = 0xFFFFC950
  590f46:      	cmpl	$0x50, %eax
  590f49:      	ja	0x591a16 <.text+0x190a16>
  590f4f:      	jmpl	*0x597939(,%eax,4)
  590f56:      	movl	$0x5f3f0c, %eax         # imm = 0x5F3F0C
  590f5b:      	jmp	0x591a45 <.text+0x190a45>
  590f60:      	movl	$0x5f3ef0, %eax         # imm = 0x5F3EF0
  590f65:      	jmp	0x591a45 <.text+0x190a45>
  590f6a:      	movl	$0x5f3ecc, %eax         # imm = 0x5F3ECC
  590f6f:      	jmp	0x591a45 <.text+0x190a45>
  590f74:      	movl	$0x5f3eac, %eax         # imm = 0x5F3EAC
  590f79:      	jmp	0x591a45 <.text+0x190a45>
  590f7e:      	movl	$0x5f3e8c, %eax         # imm = 0x5F3E8C
  590f83:      	jmp	0x591a45 <.text+0x190a45>
  590f88:      	movl	$0x5f3e6c, %eax         # imm = 0x5F3E6C
  590f8d:      	jmp	0x591a45 <.text+0x190a45>
  590f92:      	movl	$0x5f3e44, %eax         # imm = 0x5F3E44
  590f97:      	jmp	0x591a45 <.text+0x190a45>
  590f9c:      	movl	$0x5f3e2c, %eax         # imm = 0x5F3E2C
  590fa1:      	jmp	0x591a45 <.text+0x190a45>
  590fa6:      	movl	$0x5f3e10, %eax         # imm = 0x5F3E10
  590fab:      	jmp	0x591a45 <.text+0x190a45>
  590fb0:      	movl	$0x5f3df0, %eax         # imm = 0x5F3DF0
  590fb5:      	jmp	0x591a45 <.text+0x190a45>
  590fba:      	movl	$0x5f3dcc, %eax         # imm = 0x5F3DCC
  590fbf:      	jmp	0x591a45 <.text+0x190a45>
  590fc4:      	movl	$0x5f3da4, %eax         # imm = 0x5F3DA4
  590fc9:      	jmp	0x591a45 <.text+0x190a45>
  590fce:      	movl	$0x5f3d80, %eax         # imm = 0x5F3D80
  590fd3:      	jmp	0x591a45 <.text+0x190a45>
  590fd8:      	movl	$0x5f3d64, %eax         # imm = 0x5F3D64
  590fdd:      	jmp	0x591a45 <.text+0x190a45>
  590fe2:      	movl	$0x5f3d40, %eax         # imm = 0x5F3D40
  590fe7:      	jmp	0x591a45 <.text+0x190a45>
  590fec:      	movl	$0x5f3d0c, %eax         # imm = 0x5F3D0C
  590ff1:      	jmp	0x591a45 <.text+0x190a45>
  590ff6:      	movl	$0x5f3cd8, %eax         # imm = 0x5F3CD8
  590ffb:      	jmp	0x591a45 <.text+0x190a45>
  591000:      	movl	$0x5f3ca8, %eax         # imm = 0x5F3CA8
  591005:      	jmp	0x591a45 <.text+0x190a45>
  59100a:      	movl	$0x5f3c70, %eax         # imm = 0x5F3C70
  59100f:      	jmp	0x591a45 <.text+0x190a45>
  591014:      	movl	$0x5f3c38, %eax         # imm = 0x5F3C38
  591019:      	jmp	0x591a45 <.text+0x190a45>
  59101e:      	movl	$0x5f3bfc, %eax         # imm = 0x5F3BFC
  591023:      	jmp	0x591a45 <.text+0x190a45>
  591028:      	movl	$0x5f3bdc, %eax         # imm = 0x5F3BDC
  59102d:      	jmp	0x591a45 <.text+0x190a45>
  591032:      	movl	$0x5f3bb4, %eax         # imm = 0x5F3BB4
  591037:      	jmp	0x591a45 <.text+0x190a45>
  59103c:      	movl	$0x5f3b98, %eax         # imm = 0x5F3B98
  591041:      	jmp	0x591a45 <.text+0x190a45>
  591046:      	movl	$0x5f3b80, %eax         # imm = 0x5F3B80
  59104b:      	jmp	0x591a45 <.text+0x190a45>
  591050:      	movl	$0x5f3b64, %eax         # imm = 0x5F3B64
  591055:      	jmp	0x591a45 <.text+0x190a45>
  59105a:      	movl	$0x5f3b48, %eax         # imm = 0x5F3B48
  59105f:      	jmp	0x591a45 <.text+0x190a45>
  591064:      	movl	$0x5f3b24, %eax         # imm = 0x5F3B24
  591069:      	jmp	0x591a45 <.text+0x190a45>
  59106e:      	movl	$0x5f3b04, %eax         # imm = 0x5F3B04
  591073:      	jmp	0x591a45 <.text+0x190a45>
  591078:      	movl	$0x5f3ae4, %eax         # imm = 0x5F3AE4
  59107d:      	jmp	0x591a45 <.text+0x190a45>
  591082:      	movl	$0x5f3ac4, %eax         # imm = 0x5F3AC4
  591087:      	jmp	0x591a45 <.text+0x190a45>
  59108c:      	movl	$0x5f3aa4, %eax         # imm = 0x5F3AA4
  591091:      	jmp	0x591a45 <.text+0x190a45>
  591096:      	movl	$0x5f3a80, %eax         # imm = 0x5F3A80
  59109b:      	jmp	0x591a45 <.text+0x190a45>
  5910a0:      	movl	$0x5f3a64, %eax         # imm = 0x5F3A64
  5910a5:      	jmp	0x591a45 <.text+0x190a45>
  5910aa:      	movl	$0x5f3a44, %eax         # imm = 0x5F3A44
  5910af:      	jmp	0x591a45 <.text+0x190a45>
  5910b4:      	movl	$0x5f3a24, %eax         # imm = 0x5F3A24
  5910b9:      	jmp	0x591a45 <.text+0x190a45>
  5910be:      	movl	$0x5f3a08, %eax         # imm = 0x5F3A08
  5910c3:      	jmp	0x591a45 <.text+0x190a45>
  5910c8:      	movl	$0x5f39e4, %eax         # imm = 0x5F39E4
  5910cd:      	jmp	0x591a45 <.text+0x190a45>
  5910d2:      	movl	$0x5f39c4, %eax         # imm = 0x5F39C4
  5910d7:      	jmp	0x591a45 <.text+0x190a45>
  5910dc:      	movl	$0x5f39a0, %eax         # imm = 0x5F39A0
  5910e1:      	jmp	0x591a45 <.text+0x190a45>
  5910e6:      	movl	$0x5f3980, %eax         # imm = 0x5F3980
  5910eb:      	jmp	0x591a45 <.text+0x190a45>
  5910f0:      	movl	$0x5f3960, %eax         # imm = 0x5F3960
  5910f5:      	jmp	0x591a45 <.text+0x190a45>
  5910fa:      	movl	$0x5f3938, %eax         # imm = 0x5F3938
  5910ff:      	jmp	0x591a45 <.text+0x190a45>
  591104:      	movl	$0x5f3914, %eax         # imm = 0x5F3914
  591109:      	jmp	0x591a45 <.text+0x190a45>
  59110e:      	movl	$0x5f38f4, %eax         # imm = 0x5F38F4
  591113:      	jmp	0x591a45 <.text+0x190a45>
  591118:      	movl	$0x5f38d0, %eax         # imm = 0x5F38D0
  59111d:      	jmp	0x591a45 <.text+0x190a45>
  591122:      	movl	$0x5f38b0, %eax         # imm = 0x5F38B0
  591127:      	jmp	0x591a45 <.text+0x190a45>
  59112c:      	movl	$0x5f3890, %eax         # imm = 0x5F3890
  591131:      	jmp	0x591a45 <.text+0x190a45>
  591136:      	movl	$0x5f386c, %eax         # imm = 0x5F386C
  59113b:      	jmp	0x591a45 <.text+0x190a45>
  591140:      	movl	$0x5f384c, %eax         # imm = 0x5F384C
  591145:      	jmp	0x591a45 <.text+0x190a45>
  59114a:      	movl	$0x5f3820, %eax         # imm = 0x5F3820
  59114f:      	jmp	0x591a45 <.text+0x190a45>
  591154:      	movl	$0x5f37fc, %eax         # imm = 0x5F37FC
  591159:      	jmp	0x591a45 <.text+0x190a45>
  59115e:      	movl	$0x5f37e0, %eax         # imm = 0x5F37E0
  591163:      	jmp	0x591a45 <.text+0x190a45>
  591168:      	movl	$0x5f37bc, %eax         # imm = 0x5F37BC
  59116d:      	jmp	0x591a45 <.text+0x190a45>
  591172:      	movl	$0x5f379c, %eax         # imm = 0x5F379C
  591177:      	jmp	0x591a45 <.text+0x190a45>
  59117c:      	movl	$0x5f3778, %eax         # imm = 0x5F3778
  591181:      	jmp	0x591a45 <.text+0x190a45>
  591186:      	movl	$0x5f375c, %eax         # imm = 0x5F375C
  59118b:      	jmp	0x591a45 <.text+0x190a45>
  591190:      	movl	$0x5f3740, %eax         # imm = 0x5F3740
  591195:      	jmp	0x591a45 <.text+0x190a45>
  59119a:      	movl	$0x5f3720, %eax         # imm = 0x5F3720
  59119f:      	jmp	0x591a45 <.text+0x190a45>
  5911a4:      	movl	$0x5f36fc, %eax         # imm = 0x5F36FC
  5911a9:      	jmp	0x591a45 <.text+0x190a45>
  5911ae:      	movl	$0x5f36d8, %eax         # imm = 0x5F36D8
  5911b3:      	jmp	0x591a45 <.text+0x190a45>
  5911b8:      	movl	$0x5f36b8, %eax         # imm = 0x5F36B8
  5911bd:      	jmp	0x591a45 <.text+0x190a45>
  5911c2:      	movl	$0x5f3698, %eax         # imm = 0x5F3698
  5911c7:      	jmp	0x591a45 <.text+0x190a45>
  5911cc:      	movl	$0x5f3678, %eax         # imm = 0x5F3678
  5911d1:      	jmp	0x591a45 <.text+0x190a45>
  5911d6:      	movl	$0x5f3658, %eax         # imm = 0x5F3658
  5911db:      	jmp	0x591a45 <.text+0x190a45>
  5911e0:      	movl	$0x5f3638, %eax         # imm = 0x5F3638
  5911e5:      	jmp	0x591a45 <.text+0x190a45>
  5911ea:      	movl	$0x5f3614, %eax         # imm = 0x5F3614
  5911ef:      	jmp	0x591a45 <.text+0x190a45>
  5911f4:      	movl	$0x5f35f4, %eax         # imm = 0x5F35F4
  5911f9:      	jmp	0x591a45 <.text+0x190a45>
  5911fe:      	movl	$0x5f35d4, %eax         # imm = 0x5F35D4
  591203:      	jmp	0x591a45 <.text+0x190a45>
  591208:      	movl	$0x5f35b8, %eax         # imm = 0x5F35B8
  59120d:      	jmp	0x591a45 <.text+0x190a45>
  591212:      	movl	$0x5f3594, %eax         # imm = 0x5F3594
  591217:      	jmp	0x591a45 <.text+0x190a45>
  59121c:      	movl	$0x5f356c, %eax         # imm = 0x5F356C
  591221:      	jmp	0x591a45 <.text+0x190a45>
  591226:      	movl	$0x5f354c, %eax         # imm = 0x5F354C
  59122b:      	jmp	0x591a45 <.text+0x190a45>
  591230:      	movl	$0x5f352c, %eax         # imm = 0x5F352C
  591235:      	jmp	0x591a45 <.text+0x190a45>
  59123a:      	movl	$0x5f3504, %eax         # imm = 0x5F3504
  59123f:      	jmp	0x591a45 <.text+0x190a45>
  591244:      	movl	$0x5f34d8, %eax         # imm = 0x5F34D8
  591249:      	jmp	0x591a45 <.text+0x190a45>
  59124e:      	movl	$0x5f34b0, %eax         # imm = 0x5F34B0
  591253:      	jmp	0x591a45 <.text+0x190a45>
  591258:      	movl	$0x5f348c, %eax         # imm = 0x5F348C
  59125d:      	jmp	0x591a45 <.text+0x190a45>
  591262:      	movl	$0x5f3460, %eax         # imm = 0x5F3460
  591267:      	jmp	0x591a45 <.text+0x190a45>
  59126c:      	movl	$0x5f3430, %eax         # imm = 0x5F3430
  591271:      	jmp	0x591a45 <.text+0x190a45>
  591276:      	movl	$0x5f33fc, %eax         # imm = 0x5F33FC
  59127b:      	jmp	0x591a45 <.text+0x190a45>
  591280:      	movl	$0x5f33ec, %eax         # imm = 0x5F33EC
  591285:      	jmp	0x591a45 <.text+0x190a45>
  59128a:      	movl	$0x40245, %ecx          # imm = 0x40245
  59128f:      	cmpl	%ecx, %eax
  591291:      	jg	0x591692 <.text+0x190692>
  591297:      	je	0x591688 <.text+0x190688>
  59129d:      	movl	$0x4014f, %ecx          # imm = 0x4014F
  5912a2:      	cmpl	%ecx, %eax
  5912a4:      	jg	0x59149b <.text+0x19049b>
  5912aa:      	je	0x591491 <.text+0x190491>
  5912b0:      	movl	$0x40009, %ecx          # imm = 0x40009
  5912b5:      	cmpl	%ecx, %eax
  5912b7:      	jg	0x5913aa <.text+0x1903aa>
  5912bd:      	je	0x5913a0 <.text+0x1903a0>
  5912c3:      	addl	$-0x8, %ecx
  5912c6:      	cmpl	%ecx, %eax
  5912c8:      	jg	0x59133d <.text+0x19033d>
  5912ca:      	je	0x591333 <.text+0x190333>
  5912cc:      	subl	$0x30201, %eax          # imm = 0x30201
  5912d1:      	je	0x591329 <.text+0x190329>
  5912d3:      	decl	%eax
  5912d4:      	je	0x59131f <.text+0x19031f>
  5912d6:      	decl	%eax
  5912d7:      	je	0x591315 <.text+0x190315>
  5912d9:      	decl	%eax
  5912da:      	je	0x59130b <.text+0x19030b>
  5912dc:      	decl	%eax
  5912dd:      	je	0x591301 <.text+0x190301>
  5912df:      	decl	%eax
  5912e0:      	je	0x5912f7 <.text+0x1902f7>
  5912e2:      	subl	$0xfdfa, %eax           # imm = 0xFDFA
  5912e7:      	jne	0x591a16 <.text+0x190a16>
  5912ed:      	movl	$0x5f33e0, %eax         # imm = 0x5F33E0
  5912f2:      	jmp	0x591a45 <.text+0x190a45>
  5912f7:      	movl	$0x5f33c8, %eax         # imm = 0x5F33C8
  5912fc:      	jmp	0x591a45 <.text+0x190a45>
  591301:      	movl	$0x5f33ac, %eax         # imm = 0x5F33AC
  591306:      	jmp	0x591a45 <.text+0x190a45>
  59130b:      	movl	$0x5f3398, %eax         # imm = 0x5F3398
  591310:      	jmp	0x591a45 <.text+0x190a45>
  591315:      	movl	$0x5f3384, %eax         # imm = 0x5F3384
  59131a:      	jmp	0x591a45 <.text+0x190a45>
  59131f:      	movl	$0x5f3374, %eax         # imm = 0x5F3374
  591324:      	jmp	0x591a45 <.text+0x190a45>
  591329:      	movl	$0x5f3368, %eax         # imm = 0x5F3368
  59132e:      	jmp	0x591a45 <.text+0x190a45>
  591333:      	movl	$0x5f3358, %eax         # imm = 0x5F3358
  591338:      	jmp	0x591a45 <.text+0x190a45>
  59133d:      	subl	$0x40002, %eax          # imm = 0x40002
  591342:      	je	0x591396 <.text+0x190396>
  591344:      	decl	%eax
  591345:      	je	0x59138c <.text+0x19038c>
  591347:      	decl	%eax
  591348:      	je	0x591382 <.text+0x190382>
  59134a:      	decl	%eax
  59134b:      	je	0x591378 <.text+0x190378>
  59134d:      	decl	%eax
  59134e:      	je	0x59136e <.text+0x19036e>
  591350:      	decl	%eax
  591351:      	je	0x591364 <.text+0x190364>
  591353:      	decl	%eax
  591354:      	jne	0x591a16 <.text+0x190a16>
  59135a:      	movl	$0x5f333c, %eax         # imm = 0x5F333C
  59135f:      	jmp	0x591a45 <.text+0x190a45>
  591364:      	movl	$0x5f332c, %eax         # imm = 0x5F332C
  591369:      	jmp	0x591a45 <.text+0x190a45>
  59136e:      	movl	$0x5f3310, %eax         # imm = 0x5F3310
  591373:      	jmp	0x591a45 <.text+0x190a45>
  591378:      	movl	$0x5f32fc, %eax         # imm = 0x5F32FC
  59137d:      	jmp	0x591a45 <.text+0x190a45>
  591382:      	movl	$0x5f32ec, %eax         # imm = 0x5F32EC
  591387:      	jmp	0x591a45 <.text+0x190a45>
  59138c:      	movl	$0x5f32d8, %eax         # imm = 0x5F32D8
  591391:      	jmp	0x591a45 <.text+0x190a45>
  591396:      	movl	$0x5f32c0, %eax         # imm = 0x5F32C0
  59139b:      	jmp	0x591a45 <.text+0x190a45>
  5913a0:      	movl	$0x5f32a8, %eax         # imm = 0x5F32A8
  5913a5:      	jmp	0x591a45 <.text+0x190a45>
  5913aa:      	movl	$0x4010f, %ecx          # imm = 0x4010F
  5913af:      	cmpl	%ecx, %eax
  5913b1:      	jg	0x591428 <.text+0x190428>
  5913b3:      	je	0x59141e <.text+0x19041e>
  5913b5:      	subl	$0x40010, %eax          # imm = 0x40010
  5913ba:      	je	0x591414 <.text+0x190414>
  5913bc:      	subl	$0x7, %eax
  5913bf:      	je	0x59140a <.text+0x19040a>
  5913c1:      	subl	$0xe8, %eax
  5913c6:      	je	0x591400 <.text+0x190400>
  5913c8:      	decl	%eax
  5913c9:      	je	0x5913f6 <.text+0x1903f6>
  5913cb:      	decl	%eax
  5913cc:      	je	0x5913ec <.text+0x1903ec>
  5913ce:      	decl	%eax
  5913cf:      	je	0x5913e2 <.text+0x1903e2>
  5913d1:      	decl	%eax
  5913d2:      	jne	0x591a16 <.text+0x190a16>
  5913d8:      	movl	$0x5f3294, %eax         # imm = 0x5F3294
  5913dd:      	jmp	0x591a45 <.text+0x190a45>
  5913e2:      	movl	$0x5f3274, %eax         # imm = 0x5F3274
  5913e7:      	jmp	0x591a45 <.text+0x190a45>
  5913ec:      	movl	$0x5f3260, %eax         # imm = 0x5F3260
  5913f1:      	jmp	0x591a45 <.text+0x190a45>
  5913f6:      	movl	$0x5f324c, %eax         # imm = 0x5F324C
  5913fb:      	jmp	0x591a45 <.text+0x190a45>
  591400:      	movl	$0x5f3240, %eax         # imm = 0x5F3240
  591405:      	jmp	0x591a45 <.text+0x190a45>
  59140a:      	movl	$0x5f3224, %eax         # imm = 0x5F3224
  59140f:      	jmp	0x591a45 <.text+0x190a45>
  591414:      	movl	$0x5f320c, %eax         # imm = 0x5F320C
  591419:      	jmp	0x591a45 <.text+0x190a45>
  59141e:      	movl	$0x5f31fc, %eax         # imm = 0x5F31FC
  591423:      	jmp	0x591a45 <.text+0x190a45>
  591428:      	subl	$0x40110, %eax          # imm = 0x40110
  59142d:      	je	0x591487 <.text+0x190487>
  59142f:      	subl	$0xf, %eax
  591432:      	je	0x59147d <.text+0x19047d>
  591434:      	decl	%eax
  591435:      	je	0x591473 <.text+0x190473>
  591437:      	subl	$0xf, %eax
  59143a:      	je	0x591469 <.text+0x190469>
  59143c:      	decl	%eax
  59143d:      	je	0x59145f <.text+0x19045f>
  59143f:      	subl	$0xf, %eax
  591442:      	je	0x591455 <.text+0x190455>
  591444:      	decl	%eax
  591445:      	jne	0x591a16 <.text+0x190a16>
  59144b:      	movl	$0x5f31ec, %eax         # imm = 0x5F31EC
  591450:      	jmp	0x591a45 <.text+0x190a45>
  591455:      	movl	$0x5f31e0, %eax         # imm = 0x5F31E0
  59145a:      	jmp	0x591a45 <.text+0x190a45>
  59145f:      	movl	$0x5f31d0, %eax         # imm = 0x5F31D0
  591464:      	jmp	0x591a45 <.text+0x190a45>
  591469:      	movl	$0x5f31c0, %eax         # imm = 0x5F31C0
  59146e:      	jmp	0x591a45 <.text+0x190a45>
  591473:      	movl	$0x5f31b0, %eax         # imm = 0x5F31B0
  591478:      	jmp	0x591a45 <.text+0x190a45>
  59147d:      	movl	$0x5f319c, %eax         # imm = 0x5F319C
  591482:      	jmp	0x591a45 <.text+0x190a45>
  591487:      	movl	$0x5f3184, %eax         # imm = 0x5F3184
  59148c:      	jmp	0x591a45 <.text+0x190a45>
  591491:      	movl	$0x5f3178, %eax         # imm = 0x5F3178
  591496:      	jmp	0x591a45 <.text+0x190a45>
  59149b:      	movl	$0x401bf, %ecx          # imm = 0x401BF
  5914a0:      	cmpl	%ecx, %eax
  5914a2:      	jg	0x59159d <.text+0x19059d>
  5914a8:      	je	0x591593 <.text+0x190593>
  5914ae:      	addl	$-0x3e, %ecx
  5914b1:      	cmpl	%ecx, %eax
  5914b3:      	jg	0x59152a <.text+0x19052a>
  5914b5:      	je	0x591520 <.text+0x190520>
  5914b7:      	subl	$0x40150, %eax          # imm = 0x40150
  5914bc:      	je	0x591516 <.text+0x190516>
  5914be:      	subl	$0xf, %eax
  5914c1:      	je	0x59150c <.text+0x19050c>
  5914c3:      	subl	$0x11, %eax
  5914c6:      	je	0x591502 <.text+0x190502>
  5914c8:      	decl	%eax
  5914c9:      	je	0x5914f8 <.text+0x1904f8>
  5914cb:      	decl	%eax
  5914cc:      	je	0x5914ee <.text+0x1904ee>
  5914ce:      	subl	$0xd, %eax
  5914d1:      	je	0x5914e4 <.text+0x1904e4>
  5914d3:      	decl	%eax
  5914d4:      	jne	0x591a16 <.text+0x190a16>
  5914da:      	movl	$0x5f3168, %eax         # imm = 0x5F3168
  5914df:      	jmp	0x591a45 <.text+0x190a45>
  5914e4:      	movl	$0x5f3158, %eax         # imm = 0x5F3158
  5914e9:      	jmp	0x591a45 <.text+0x190a45>
  5914ee:      	movl	$0x5f3138, %eax         # imm = 0x5F3138
  5914f3:      	jmp	0x591a45 <.text+0x190a45>
  5914f8:      	movl	$0x5f3124, %eax         # imm = 0x5F3124
  5914fd:      	jmp	0x591a45 <.text+0x190a45>
  591502:      	movl	$0x5f3114, %eax         # imm = 0x5F3114
  591507:      	jmp	0x591a45 <.text+0x190a45>
  59150c:      	movl	$0x5f3104, %eax         # imm = 0x5F3104
  591511:      	jmp	0x591a45 <.text+0x190a45>
  591516:      	movl	$0x5f30f4, %eax         # imm = 0x5F30F4
  59151b:      	jmp	0x591a45 <.text+0x190a45>
  591520:      	movl	$0x5f30d8, %eax         # imm = 0x5F30D8
  591525:      	jmp	0x591a45 <.text+0x190a45>
  59152a:      	subl	$0x40182, %eax          # imm = 0x40182
  59152f:      	je	0x591589 <.text+0x190589>
  591531:      	subl	$0xd, %eax
  591534:      	je	0x59157f <.text+0x19057f>
  591536:      	decl	%eax
  591537:      	je	0x591575 <.text+0x190575>
  591539:      	subl	$0xf, %eax
  59153c:      	je	0x59156b <.text+0x19056b>
  59153e:      	decl	%eax
  59153f:      	je	0x591561 <.text+0x190561>
  591541:      	subl	$0xf, %eax
  591544:      	je	0x591557 <.text+0x190557>
  591546:      	decl	%eax
  591547:      	jne	0x591a16 <.text+0x190a16>
  59154d:      	movl	$0x5f30c8, %eax         # imm = 0x5F30C8
  591552:      	jmp	0x591a45 <.text+0x190a45>
  591557:      	movl	$0x5f30b8, %eax         # imm = 0x5F30B8
  59155c:      	jmp	0x591a45 <.text+0x190a45>
  591561:      	movl	$0x5f30a8, %eax         # imm = 0x5F30A8
  591566:      	jmp	0x591a45 <.text+0x190a45>
  59156b:      	movl	$0x5f3094, %eax         # imm = 0x5F3094
  591570:      	jmp	0x591a45 <.text+0x190a45>
  591575:      	movl	$0x5f3080, %eax         # imm = 0x5F3080
  59157a:      	jmp	0x591a45 <.text+0x190a45>
  59157f:      	movl	$0x5f3070, %eax         # imm = 0x5F3070
  591584:      	jmp	0x591a45 <.text+0x190a45>
  591589:      	movl	$0x5f3058, %eax         # imm = 0x5F3058
  59158e:      	jmp	0x591a45 <.text+0x190a45>
  591593:      	movl	$0x5f304c, %eax         # imm = 0x5F304C
  591598:      	jmp	0x591a45 <.text+0x190a45>
  59159d:      	movl	$0x401e5, %ecx          # imm = 0x401E5
  5915a2:      	cmpl	%ecx, %eax
  5915a4:      	jg	0x59161b <.text+0x19061b>
  5915a6:      	je	0x591611 <.text+0x190611>
  5915a8:      	subl	$0x401c0, %eax          # imm = 0x401C0
  5915ad:      	je	0x591607 <.text+0x190607>
  5915af:      	subl	$0xf, %eax
  5915b2:      	je	0x5915fd <.text+0x1905fd>
  5915b4:      	decl	%eax
  5915b5:      	je	0x5915f3 <.text+0x1905f3>
  5915b7:      	subl	$0xf, %eax
  5915ba:      	je	0x5915e9 <.text+0x1905e9>
  5915bc:      	decl	%eax
  5915bd:      	je	0x5915df <.text+0x1905df>
  5915bf:      	decl	%eax
  5915c0:      	decl	%eax
  5915c1:      	je	0x5915d5 <.text+0x1905d5>
  5915c3:      	decl	%eax
  5915c4:      	decl	%eax
  5915c5:      	jne	0x591a16 <.text+0x190a16>
  5915cb:      	movl	$0x5f3044, %eax         # imm = 0x5F3044
  5915d0:      	jmp	0x591a45 <.text+0x190a45>
  5915d5:      	movl	$0x5f302c, %eax         # imm = 0x5F302C
  5915da:      	jmp	0x591a45 <.text+0x190a45>
  5915df:      	movl	$0x5f3020, %eax         # imm = 0x5F3020
  5915e4:      	jmp	0x591a45 <.text+0x190a45>
  5915e9:      	movl	$0x5f3010, %eax         # imm = 0x5F3010
  5915ee:      	jmp	0x591a45 <.text+0x190a45>
  5915f3:      	movl	$0x5f3000, %eax         # imm = 0x5F3000
  5915f8:      	jmp	0x591a45 <.text+0x190a45>
  5915fd:      	movl	$0x5f2fec, %eax         # imm = 0x5F2FEC
  591602:      	jmp	0x591a45 <.text+0x190a45>
  591607:      	movl	$0x5f2fd8, %eax         # imm = 0x5F2FD8
  59160c:      	jmp	0x591a45 <.text+0x190a45>
  591611:      	movl	$0x5f2fcc, %eax         # imm = 0x5F2FCC
  591616:      	jmp	0x591a45 <.text+0x190a45>
  59161b:      	subl	$0x401e6, %eax          # imm = 0x401E6
  591620:      	je	0x59167e <.text+0x19067e>
  591622:      	decl	%eax
  591623:      	je	0x591674 <.text+0x190674>
  591625:      	subl	$0x8, %eax
  591628:      	je	0x59166a <.text+0x19066a>
  59162a:      	subl	$0x13, %eax
  59162d:      	je	0x591660 <.text+0x190660>
  59162f:      	subl	$0x2b, %eax
  591632:      	je	0x591656 <.text+0x190656>
  591634:      	subl	$0xa, %eax
  591637:      	je	0x59164c <.text+0x19064c>
  591639:      	subl	$0xb, %eax
  59163c:      	jne	0x591a16 <.text+0x190a16>
  591642:      	movl	$0x5f2fb4, %eax         # imm = 0x5F2FB4
  591647:      	jmp	0x591a45 <.text+0x190a45>
  59164c:      	movl	$0x5f2f98, %eax         # imm = 0x5F2F98
  591651:      	jmp	0x591a45 <.text+0x190a45>
  591656:      	movl	$0x5f2f80, %eax         # imm = 0x5F2F80
  59165b:      	jmp	0x591a45 <.text+0x190a45>
  591660:      	movl	$0x5f2f68, %eax         # imm = 0x5F2F68
  591665:      	jmp	0x591a45 <.text+0x190a45>
  59166a:      	movl	$0x5f2f5c, %eax         # imm = 0x5F2F5C
  59166f:      	jmp	0x591a45 <.text+0x190a45>
  591674:      	movl	$0x5f2f3c, %eax         # imm = 0x5F2F3C
  591679:      	jmp	0x591a45 <.text+0x190a45>
  59167e:      	movl	$0x5f2f34, %eax         # imm = 0x5F2F34
  591683:      	jmp	0x591a45 <.text+0x190a45>
  591688:      	movl	$0x5f2f1c, %eax         # imm = 0x5F2F1C
  59168d:      	jmp	0x591a45 <.text+0x190a45>
  591692:      	movl	$0x4d007, %ecx          # imm = 0x4D007
  591697:      	cmpl	%ecx, %eax
  591699:      	jg	0x591892 <.text+0x190892>
  59169f:      	je	0x591888 <.text+0x190888>
  5916a5:      	movl	$0x41300, %ecx          # imm = 0x41300
  5916aa:      	cmpl	%ecx, %eax
  5916ac:      	jg	0x5917ad <.text+0x1907ad>
  5916b2:      	je	0x5917a3 <.text+0x1907a3>
  5916b8:      	movl	$0x40263, %ecx          # imm = 0x40263
  5916bd:      	cmpl	%ecx, %eax
  5916bf:      	jg	0x591739 <.text+0x190739>
  5916c1:      	je	0x59172f <.text+0x19072f>
  5916c3:      	subl	$0x40246, %eax          # imm = 0x40246
  5916c8:      	je	0x591725 <.text+0x190725>
  5916ca:      	subl	$0xa, %eax
  5916cd:      	je	0x59171b <.text+0x19071b>
  5916cf:      	subl	$0x4, %eax
  5916d2:      	je	0x591711 <.text+0x190711>
  5916d4:      	subl	$0x3, %eax
  5916d7:      	je	0x591707 <.text+0x190707>
  5916d9:      	decl	%eax
  5916da:      	je	0x5916fd <.text+0x1906fd>
  5916dc:      	decl	%eax
  5916dd:      	decl	%eax
  5916de:      	je	0x5916f3 <.text+0x1906f3>
  5916e0:      	subl	$0x6, %eax
  5916e3:      	jne	0x591a16 <.text+0x190a16>
  5916e9:      	movl	$0x5f2f0c, %eax         # imm = 0x5F2F0C
  5916ee:      	jmp	0x591a45 <.text+0x190a45>
  5916f3:      	movl	$0x5f2f00, %eax         # imm = 0x5F2F00
  5916f8:      	jmp	0x591a45 <.text+0x190a45>
  5916fd:      	movl	$0x5f2ee4, %eax         # imm = 0x5F2EE4
  591702:      	jmp	0x591a45 <.text+0x190a45>
  591707:      	movl	$0x5f2ec8, %eax         # imm = 0x5F2EC8
  59170c:      	jmp	0x591a45 <.text+0x190a45>
  591711:      	movl	$0x5f2eac, %eax         # imm = 0x5F2EAC
  591716:      	jmp	0x591a45 <.text+0x190a45>
  59171b:      	movl	$0x5f2e90, %eax         # imm = 0x5F2E90
  591720:      	jmp	0x591a45 <.text+0x190a45>
  591725:      	movl	$0x5f2e74, %eax         # imm = 0x5F2E74
  59172a:      	jmp	0x591a45 <.text+0x190a45>
  59172f:      	movl	$0x5f2e64, %eax         # imm = 0x5F2E64
  591734:      	jmp	0x591a45 <.text+0x190a45>
  591739:      	subl	$0x40267, %eax          # imm = 0x40267
  59173e:      	je	0x591799 <.text+0x190799>
  591740:      	decl	%eax
  591741:      	je	0x59178f <.text+0x19078f>
  591743:      	subl	$0x8, %eax
  591746:      	je	0x591785 <.text+0x190785>
  591748:      	subl	$0xe, %eax
  59174b:      	je	0x59177b <.text+0x19077b>
  59174d:      	decl	%eax
  59174e:      	decl	%eax
  59174f:      	je	0x591771 <.text+0x190771>
  591751:      	subl	$0xc, %eax
  591754:      	je	0x591767 <.text+0x190767>
  591756:      	decl	%eax
  591757:      	jne	0x591a16 <.text+0x190a16>
  59175d:      	movl	$0x5f2e4c, %eax         # imm = 0x5F2E4C
  591762:      	jmp	0x591a45 <.text+0x190a45>
  591767:      	movl	$0x5f2e20, %eax         # imm = 0x5F2E20
  59176c:      	jmp	0x591a45 <.text+0x190a45>
  591771:      	movl	$0x5f2e00, %eax         # imm = 0x5F2E00
  591776:      	jmp	0x591a45 <.text+0x190a45>
  59177b:      	movl	$0x5f2dec, %eax         # imm = 0x5F2DEC
  591780:      	jmp	0x591a45 <.text+0x190a45>
  591785:      	movl	$0x5f2dd8, %eax         # imm = 0x5F2DD8
  59178a:      	jmp	0x591a45 <.text+0x190a45>
  59178f:      	movl	$0x5f2dc8, %eax         # imm = 0x5F2DC8
  591794:      	jmp	0x591a45 <.text+0x190a45>
  591799:      	movl	$0x5f2db4, %eax         # imm = 0x5F2DB4
  59179e:      	jmp	0x591a45 <.text+0x190a45>
  5917a3:      	movl	$0x5f2da0, %eax         # imm = 0x5F2DA0
  5917a8:      	jmp	0x591a45 <.text+0x190a45>
  5917ad:      	movl	$0x41308, %ecx          # imm = 0x41308
  5917b2:      	cmpl	%ecx, %eax
  5917b4:      	jg	0x591825 <.text+0x190825>
  5917b6:      	je	0x59181b <.text+0x19081b>
  5917b8:      	subl	$0x41301, %eax          # imm = 0x41301
  5917bd:      	je	0x591811 <.text+0x190811>
  5917bf:      	decl	%eax
  5917c0:      	je	0x591807 <.text+0x190807>
  5917c2:      	decl	%eax
  5917c3:      	je	0x5917fd <.text+0x1907fd>
  5917c5:      	decl	%eax
  5917c6:      	je	0x5917f3 <.text+0x1907f3>
  5917c8:      	decl	%eax
  5917c9:      	je	0x5917e9 <.text+0x1907e9>
  5917cb:      	decl	%eax
  5917cc:      	je	0x5917df <.text+0x1907df>
  5917ce:      	decl	%eax
  5917cf:      	jne	0x591a16 <.text+0x190a16>
  5917d5:      	movl	$0x5f2d80, %eax         # imm = 0x5F2D80
  5917da:      	jmp	0x591a45 <.text+0x190a45>
  5917df:      	movl	$0x5f2d68, %eax         # imm = 0x5F2D68
  5917e4:      	jmp	0x591a45 <.text+0x190a45>
  5917e9:      	movl	$0x5f2d4c, %eax         # imm = 0x5F2D4C
  5917ee:      	jmp	0x591a45 <.text+0x190a45>
  5917f3:      	movl	$0x5f2d30, %eax         # imm = 0x5F2D30
  5917f8:      	jmp	0x591a45 <.text+0x190a45>
  5917fd:      	movl	$0x5f2d14, %eax         # imm = 0x5F2D14
  591802:      	jmp	0x591a45 <.text+0x190a45>
  591807:      	movl	$0x5f2cfc, %eax         # imm = 0x5F2CFC
  59180c:      	jmp	0x591a45 <.text+0x190a45>
  591811:      	movl	$0x5f2ce4, %eax         # imm = 0x5F2CE4
  591816:      	jmp	0x591a45 <.text+0x190a45>
  59181b:      	movl	$0x5f2ccc, %eax         # imm = 0x5F2CCC
  591820:      	jmp	0x591a45 <.text+0x190a45>
  591825:      	subl	$0x4d000, %eax          # imm = 0x4D000
  59182a:      	je	0x59187e <.text+0x19087e>
  59182c:      	decl	%eax
  59182d:      	je	0x591874 <.text+0x190874>
  59182f:      	decl	%eax
  591830:      	je	0x59186a <.text+0x19086a>
  591832:      	decl	%eax
  591833:      	je	0x591860 <.text+0x190860>
  591835:      	decl	%eax
  591836:      	je	0x591856 <.text+0x190856>
  591838:      	decl	%eax
  591839:      	je	0x59184c <.text+0x19084c>
  59183b:      	decl	%eax
  59183c:      	jne	0x591a16 <.text+0x190a16>
  591842:      	movl	$0x5f2cb0, %eax         # imm = 0x5F2CB0
  591847:      	jmp	0x591a45 <.text+0x190a45>
  59184c:      	movl	$0x5f2c94, %eax         # imm = 0x5F2C94
  591851:      	jmp	0x591a45 <.text+0x190a45>
  591856:      	movl	$0x5f2c84, %eax         # imm = 0x5F2C84
  59185b:      	jmp	0x591a45 <.text+0x190a45>
  591860:      	movl	$0x5f2c70, %eax         # imm = 0x5F2C70
  591865:      	jmp	0x591a45 <.text+0x190a45>
  59186a:      	movl	$0x5f2c60, %eax         # imm = 0x5F2C60
  59186f:      	jmp	0x591a45 <.text+0x190a45>
  591874:      	movl	$0x5f2c50, %eax         # imm = 0x5F2C50
  591879:      	jmp	0x591a45 <.text+0x190a45>
  59187e:      	movl	$0x5f2c40, %eax         # imm = 0x5F2C40
  591883:      	jmp	0x591a45 <.text+0x190a45>
  591888:      	movl	$0x5f2c2c, %eax         # imm = 0x5F2C2C
  59188d:      	jmp	0x591a45 <.text+0x190a45>
  591892:      	movl	$0x90323, %ecx          # imm = 0x90323
  591897:      	cmpl	%ecx, %eax
  591899:      	jg	0x591999 <.text+0x190999>
  59189f:      	je	0x59198f <.text+0x19098f>
  5918a5:      	movl	$0x80013, %ecx          # imm = 0x80013
  5918aa:      	cmpl	%ecx, %eax
  5918ac:      	jg	0x591929 <.text+0x190929>
  5918ae:      	je	0x59191f <.text+0x19091f>
  5918b0:      	subl	$0x4d008, %eax          # imm = 0x4D008
  5918b5:      	je	0x591915 <.text+0x190915>
  5918b7:      	decl	%eax
  5918b8:      	je	0x59190b <.text+0x19090b>
  5918ba:      	decl	%eax
  5918bb:      	je	0x591901 <.text+0x190901>
  5918bd:      	subl	$0x6, %eax
  5918c0:      	je	0x5918f7 <.text+0x1908f7>
  5918c2:      	subl	$0xff0, %eax            # imm = 0xFF0
  5918c7:      	je	0x5918ed <.text+0x1908ed>
  5918c9:      	subl	$0x2f, %eax
  5918cc:      	je	0x5918e3 <.text+0x1908e3>
  5918ce:      	subl	$0x31fe3, %eax          # imm = 0x31FE3
  5918d3:      	jne	0x591a16 <.text+0x190a16>
  5918d9:      	movl	$0x5f2c14, %eax         # imm = 0x5F2C14
  5918de:      	jmp	0x591a45 <.text+0x190a45>
  5918e3:      	movl	$0x5f2c04, %eax         # imm = 0x5F2C04
  5918e8:      	jmp	0x591a45 <.text+0x190a45>
  5918ed:      	movl	$0x5f2bf4, %eax         # imm = 0x5F2BF4
  5918f2:      	jmp	0x591a45 <.text+0x190a45>
  5918f7:      	movl	$0x5f2be8, %eax         # imm = 0x5F2BE8
  5918fc:      	jmp	0x591a45 <.text+0x190a45>
  591901:      	movl	$0x5f2bd4, %eax         # imm = 0x5F2BD4
  591906:      	jmp	0x591a45 <.text+0x190a45>
  59190b:      	movl	$0x5f2bc0, %eax         # imm = 0x5F2BC0
  591910:      	jmp	0x591a45 <.text+0x190a45>
  591915:      	movl	$0x5f2bb0, %eax         # imm = 0x5F2BB0
  59191a:      	jmp	0x591a45 <.text+0x190a45>
  59191f:      	movl	$0x5f2b94, %eax         # imm = 0x5F2B94
  591924:      	jmp	0x591a45 <.text+0x190a45>
  591929:      	subl	$0x90312, %eax          # imm = 0x90312
  59192e:      	je	0x591985 <.text+0x190985>
  591930:      	decl	%eax
  591931:      	je	0x59197b <.text+0x19097b>
  591933:      	decl	%eax
  591934:      	je	0x591971 <.text+0x190971>
  591936:      	decl	%eax
  591937:      	je	0x591967 <.text+0x190967>
  591939:      	decl	%eax
  59193a:      	decl	%eax
  59193b:      	je	0x59195d <.text+0x19095d>
  59193d:      	subl	$0x9, %eax
  591940:      	je	0x591953 <.text+0x190953>
  591942:      	decl	%eax
  591943:      	jne	0x591a16 <.text+0x190a16>
  591949:      	movl	$0x5f2b80, %eax         # imm = 0x5F2B80
  59194e:      	jmp	0x591a45 <.text+0x190a45>
  591953:      	movl	$0x5f2b60, %eax         # imm = 0x5F2B60
  591958:      	jmp	0x591a45 <.text+0x190a45>
  59195d:      	movl	$0x5f2b48, %eax         # imm = 0x5F2B48
  591962:      	jmp	0x591a45 <.text+0x190a45>
  591967:      	movl	$0x5f2b34, %eax         # imm = 0x5F2B34
  59196c:      	jmp	0x591a45 <.text+0x190a45>
  591971:      	movl	$0x5f2b18, %eax         # imm = 0x5F2B18
  591976:      	jmp	0x591a45 <.text+0x190a45>
  59197b:      	movl	$0x5f2b00, %eax         # imm = 0x5F2B00
  591980:      	jmp	0x591a45 <.text+0x190a45>
  591985:      	movl	$0x5f2ae8, %eax         # imm = 0x5F2AE8
  59198a:      	jmp	0x591a45 <.text+0x190a45>
  59198f:      	movl	$0x5f2ad0, %eax         # imm = 0x5F2AD0
  591994:      	jmp	0x591a45 <.text+0x190a45>
  591999:      	movl	$0x87a0001, %ecx        # imm = 0x87A0001
  59199e:      	cmpl	%ecx, %eax
  5919a0:      	jg	0x5919ff <.text+0x1909ff>
  5919a2:      	je	0x5919f8 <.text+0x1909f8>
  5919a4:      	subl	$0x91012, %eax          # imm = 0x91012
  5919a9:      	je	0x5919f1 <.text+0x1909f1>
  5919ab:      	subl	$0x86cf85d, %eax        # imm = 0x86CF85D
  5919b0:      	je	0x5919ea <.text+0x1909ea>
  5919b2:      	subl	$0x6, %eax
  5919b5:      	je	0x5919e3 <.text+0x1909e3>
  5919b7:      	decl	%eax
  5919b8:      	je	0x5919dc <.text+0x1909dc>
  5919ba:      	decl	%eax
  5919bb:      	je	0x5919d5 <.text+0x1909d5>
  5919bd:      	decl	%eax
  5919be:      	je	0x5919ce <.text+0x1909ce>
  5919c0:      	subl	$0x1f792, %eax          # imm = 0x1F792
  5919c5:      	jne	0x591a16 <.text+0x190a16>
  5919c7:      	movl	$0x5f2ab8, %eax         # imm = 0x5F2AB8
  5919cc:      	jmp	0x591a45 <.text+0x190a45>
  5919ce:      	movl	$0x5f2aa4, %eax         # imm = 0x5F2AA4
  5919d3:      	jmp	0x591a45 <.text+0x190a45>
  5919d5:      	movl	$0x5f2a8c, %eax         # imm = 0x5F2A8C
  5919da:      	jmp	0x591a45 <.text+0x190a45>
  5919dc:      	movl	$0x5f2a70, %eax         # imm = 0x5F2A70
  5919e1:      	jmp	0x591a45 <.text+0x190a45>
  5919e3:      	movl	$0x5f2a60, %eax         # imm = 0x5F2A60
  5919e8:      	jmp	0x591a45 <.text+0x190a45>
  5919ea:      	movl	$0x5f2a50, %eax         # imm = 0x5F2A50
  5919ef:      	jmp	0x591a45 <.text+0x190a45>
  5919f1:      	movl	$0x5f2a30, %eax         # imm = 0x5F2A30
  5919f6:      	jmp	0x591a45 <.text+0x190a45>
  5919f8:      	movl	$0x5f2a18, %eax         # imm = 0x5F2A18
  5919fd:      	jmp	0x591a45 <.text+0x190a45>
  5919ff:      	subl	$0x87a0002, %eax        # imm = 0x87A0002
  591a04:      	je	0x591a40 <.text+0x190a40>
  591a06:      	decl	%eax
  591a07:      	decl	%eax
  591a08:      	je	0x591a39 <.text+0x190a39>
  591a0a:      	decl	%eax
  591a0b:      	je	0x591a32 <.text+0x190a32>
  591a0d:      	decl	%eax
  591a0e:      	je	0x591a2b <.text+0x190a2b>
  591a10:      	decl	%eax
  591a11:      	je	0x591a24 <.text+0x190a24>
  591a13:      	decl	%eax
  591a14:      	je	0x591a1d <.text+0x190a1d>
  591a16:      	movl	$0x5f052c, %eax         # imm = 0x5F052C
  591a1b:      	jmp	0x591a45 <.text+0x190a45>
  591a1d:      	movl	$0x5f29f4, %eax         # imm = 0x5F29F4
  591a22:      	jmp	0x591a45 <.text+0x190a45>
  591a24:      	movl	$0x5f29d8, %eax         # imm = 0x5F29D8
  591a29:      	jmp	0x591a45 <.text+0x190a45>
  591a2b:      	movl	$0x5f29ac, %eax         # imm = 0x5F29AC
  591a30:      	jmp	0x591a45 <.text+0x190a45>
  591a32:      	movl	$0x5f298c, %eax         # imm = 0x5F298C
  591a37:      	jmp	0x591a45 <.text+0x190a45>
  591a39:      	movl	$0x5f2970, %eax         # imm = 0x5F2970
  591a3e:      	jmp	0x591a45 <.text+0x190a45>
  591a40:      	movl	$0x5f295c, %eax         # imm = 0x5F295C
  591a45:      	popl	%ebp
  591a46:      	retl	$0x4
  591a49:      	insl	%dx, %es:(%edi)
  591a4a:      	popl	%eax
  591a4c:      	addb	%dh, 0x64(%edi)
  591a4f:      	popl	%eax
  591a50:      	addb	%al, -0x74ffa79c(%ecx)
  591a56:      	popl	%eax
  591a58:      	addb	%dl, -0x60ffa79c(%ebp)
  591a5e:      	popl	%eax
  591a60:      	addb	%ch, -0x4cffa79c(%ecx)
  591a66:      	popl	%eax
  591a68:      	addb	%bh, -0x19ffa79c(%ebp)
  591a6e:      	popl	%eax
  591a70:      	addb	%dh, %al
  591a72:      	popl	%eax
  591a74:      	addb	%bh, %dl
  591a76:      	popl	%eax
  591a78:      	addb	%al, 0x650e0058(,%eiz,2)
  591a7f:      	popl	%eax
  591a80:      	addb	%bl, (%eax)
  591a82:      	popl	%eax
  591a84:      	addb	%ah, (%edx)
  591a86:      	popl	%eax
  591a88:      	addb	%ch, 0x65360058(,%eiz,2)
  591a8f:      	popl	%eax
  591a90:      	addb	%al, 0x65(%eax)
  591a93:      	popl	%eax
  591a94:      	addb	%cl, 0x65(%edx)
  591a97:      	popl	%eax
  591a98:      	addb	%dl, 0x58(%ebp,%eiz,2)
  591a9c:      	addb	%bl, 0x65(%esi)
  591a9f:      	popl	%eax
  591aa0:      	addb	%ch, 0x65(%eax)
  591aa3:      	popl	%eax
  591aa4:      	addb	%dh, 0x65(%edx)
  591aa7:      	popl	%eax
  591aa8:      	addb	%bh, 0x58(%ebp,%eiz,2)
  591aac:      	addb	%al, -0x6fffa79b(%esi)
  591ab2:      	popl	%eax
  591ab4:      	addb	%bl, -0x5bffa79b(%edx)
  591aba:      	popl	%eax
  591abc:      	addb	%dh, -0x44ffa79a(%ecx)
  591ac2:      	popw	%ax
  591ac4:      	addb	%al, %ch
  591ac6:      	popw	%ax
  591ac8:      	addb	%cl, %bh
  591aca:      	popw	%ax
  591acc:      	addb	%bl, %cl
  591ace:      	popw	%ax
  591ad0:      	addb	%ah, %bl
  591ad2:      	popw	%ax
  591ad4:      	addb	%ch, %ch
  591ad6:      	popw	%ax
  591ad8:      	addb	%dh, %bh
  591ada:      	popw	%ax
  591adc:      	addb	%al, (%ecx)
  591ade:      	addr16		popl	%eax
  591ae0:      	addb	%bh, %bl
  591ae2:      	addr16		popl	%eax
  591ae4:      	addb	%al, 0xf005868
  591aea:      	pushl	$0x68190058             # imm = 0x68190058
  591aef:      	popl	%eax
  591af0:      	addb	%ah, (%ebx)
  591af2:      	pushl	$0x682d0058             # imm = 0x682D0058
  591af7:      	popl	%eax
  591af8:      	addb	%dh, (%edi)
  591afa:      	pushl	$0x68410058             # imm = 0x68410058
  591aff:      	popl	%eax
  591b00:      	addb	%cl, 0x68(%ebx)
  591b03:      	popl	%eax
  591b04:      	addb	%al, -0x6effa798(%edi)
  591b0a:      	pushl	$0x689b0058             # imm = 0x689B0058
  591b0f:      	popl	%eax
  591b10:      	addb	%ah, -0x50ffa798(%ebp)
  591b16:      	pushl	$0x68b90058             # imm = 0x68B90058
  591b1b:      	popl	%eax
  591b1c:      	addb	%al, %bl
  591b1e:      	pushl	$0x68cd0058             # imm = 0x68CD0058
  591b23:      	popl	%eax
  591b24:      	addb	%dl, %bh
  591b26:      	pushl	$0x68e10058             # imm = 0x68E10058
  591b2b:      	popl	%eax
  591b2c:      	addb	%ch, %bl
  591b2e:      	pushl	$0x68f50058             # imm = 0x68F50058
  591b33:      	popl	%eax
  591b34:      	addb	%bh, %bh
  591b36:      	pushl	$0x69090058             # imm = 0x69090058
  591b3b:      	popl	%eax
  591b3c:      	addb	%dl, (%ebx)
  591b3e:      	imull	$0x58691d, (%eax), %ebx # imm = 0x58691D
  591b45:      	daa
  591b46:      	imull	$0x586931, (%eax), %ebx # imm = 0x586931
  591b4d:      	cmpl	0x58(%ecx), %ebp
  591b50:      	addb	%al, 0x69(%ebp)
  591b53:      	popl	%eax
  591b54:      	addb	%cl, 0x69(%edi)
  591b57:      	popl	%eax
  591b58:      	addb	%bl, 0x69(%ecx)
  591b5b:      	popl	%eax
  591b5c:      	addb	%ah, 0x69(%ebx)
  591b5f:      	popl	%eax
  591b60:      	addb	%ch, 0x69(%ebp)
  591b63:      	popl	%eax
  591b64:      	addb	%dh, 0x69(%edi)
  591b67:      	popl	%eax
  591b68:      	addb	%al, -0x74ffa797(%ecx)
  591b6e:      	imull	$0x586995, (%eax), %ebx # imm = 0x586995
  591b75:      	lahf
  591b76:      	imull	$0x5869a9, (%eax), %ebx # imm = 0x5869A9
  591b7d:      	movb	$0x69, %bl
  591b7f:      	popl	%eax
  591b80:      	addb	%bh, -0x38ffa797(%ebp)
  591b86:      	imull	$0x5869d1, (%eax), %ebx # imm = 0x5869D1
  591b8d:      	fldt	0x58(%ecx)
  591b90:      	addb	%ah, %ch
  591b92:      	imull	$0x5869ef, (%eax), %ebx # imm = 0x5869EF
  591b99:      	stc
  591b9a:      	imull	$0x586a03, (%eax), %ebx # imm = 0x586A03
  591ba1:      	orl	$0x1700586a, %eax       # imm = 0x1700586A
  591ba6:      	pushl	$0x58
  591ba8:      	addb	%ah, (%ecx)
  591baa:      	pushl	$0x58
  591bac:      	addb	%ch, (%ebx)
  591bae:      	pushl	$0x58
  591bb0:      	addb	%dh, 0x3f00586a
  591bb6:      	pushl	$0x58
  591bb8:      	addb	%dl, (%esi)
  591bba:      	sbbb	(%ecx), %bl
  591bbd:      	decl	%ecx
  591bbe:      	pushl	$0x58
  591bc0:      	addb	%dl, 0x6a(%ebx)
  591bc3:      	popl	%eax
  591bc4:      	addb	%cl, 0x1600586a(%edi)
  591bca:      	sbbb	(%ecx), %bl
  591bcd:      	cltd
  591bce:      	pushl	$0x58
  591bd0:      	addb	%ah, -0x52ffa796(%ebx)
  591bd6:      	pushl	$0x58
  591bd8:      	addb	%dh, -0x3effa796(%edi)
  591bde:      	pushl	$0x58
  591be0:      	addb	%cl, %bl
  591be2:      	pushl	$0x58
  591be4:      	addb	%dl, %ch
  591be6:      	pushl	$0x58
  591be8:      	addb	%bl, %bh
  591bea:      	pushl	$0x58
  591bec:      	addb	%ch, %cl
  591bee:      	pushl	$0x58
  591bf0:      	addb	%dh, %bl
  591bf2:      	pushl	$0x58
  591bf4:      	addb	%bh, %ch
  591bf6:      	pushl	$0x58
  591bf8:      	addb	%al, (%edi)
  591bfa:      	imull	$0x11, (%eax), %ebx
  591bfe:      	imull	$0x1b, (%eax), %ebx
  591c02:      	imull	$0x25, (%eax), %ebx
  591c06:      	imull	$0x2f, (%eax), %ebx
  591c0a:      	imull	$0x39, (%eax), %ebx
  591c0e:      	imull	$0x20, (%eax), %ebx
  591c12:      	outsl	(%esi), %dx
  591c13:      	popl	%eax
  591c14:      	addb	%ch, (%edx)
  591c16:      	outsl	(%esi), %dx
  591c17:      	popl	%eax
  591c18:      	addb	%dh, (%edi,%ebp,2)
  591c1b:      	popl	%eax
  591c1c:      	addb	%bh, (%esi)
  591c1e:      	outsl	(%esi), %dx
  591c1f:      	popl	%eax
  591c20:      	addb	%cl, 0x6f(%eax)
  591c23:      	popl	%eax
  591c24:      	addb	%dl, 0x6f(%edx)
  591c27:      	popl	%eax
  591c28:      	addb	%bl, 0x58(%edi,%ebp,2)
  591c2c:      	addb	%ah, 0x6f(%esi)
  591c2f:      	popl	%eax
  591c30:      	addb	%dh, 0x6f(%eax)
  591c33:      	popl	%eax
  591c34:      	addb	%al, 0x71(%ecx)
  591c37:      	popl	%eax
  591c38:      	addb	%cl, 0x71(%ebx)
  591c3b:      	popl	%eax
  591c3c:      	addb	%dl, 0x71(%ebp)
  591c3f:      	popl	%eax
  591c40:      	addb	%bl, 0x71(%edi)
  591c43:      	popl	%eax
  591c44:      	addb	%ch, 0x71(%ecx)
  591c47:      	popl	%eax
  591c48:      	addb	%dh, 0x71(%ebx)
  591c4b:      	popl	%eax
  591c4c:      	addb	%bh, 0x71(%ebp)
  591c4f:      	popl	%eax
  591c50:      	addb	%al, -0x6effa78f(%edi)
  591c56:      	jno	0x591cb0 <.text+0x190cb0>
  591c58:      	addb	%bl, -0x5affa78f(%ebx)
  591c5e:      	jno	0x591cb8 <.text+0x190cb8>
  591c60:      	addb	%cl, %dh
  591c62:      	jno	0x591cbc <.text+0x190cbc>
  591c64:      	addb	%bl, %al
  591c66:      	jno	0x591cc0 <.text+0x190cc0>
  591c68:      	addb	%ah, %dl
  591c6a:      	jno	0x591cc4 <.text+0x190cc4>
  591c6c:      	addb	%ch, %ah
  591c6e:      	jno	0x591cc8 <.text+0x190cc8>
  591c70:      	addb	%dh, %dh
  591c72:      	jno	0x591ccc <.text+0x190ccc>
  591c74:      	addb	%al, (%eax)
  591c76:      	jb	0x591cd0 <.text+0x190cd0>
  591c78:      	addb	%cl, (%edx)
  591c7a:      	jb	0x591cd4 <.text+0x190cd4>
  591c7c:      	addb	%dl, (%edx,%esi,2)
  591c7f:      	popl	%eax
  591c80:      	addb	%al, 0x72(%esi)
  591c83:      	popl	%eax
  591c84:      	addb	%dl, 0x72(%eax)
  591c87:      	popl	%eax
  591c88:      	addb	%ah, 0x58(%edx,%esi,2)
  591c8c:      	addb	%ch, 0x72(%esi)
  591c8f:      	popl	%eax
  591c90:      	addb	%bl, 0x72(%edx)
  591c93:      	popl	%eax
  591c94:      	addb	%bh, 0x72(%eax)
  591c97:      	popl	%eax
  591c98:      	addb	%cl, 0x72960058(%edx,%esi,2)
  591c9f:      	popl	%eax
  591ca0:      	addb	%al, -0x5fffa78e(%edx)
  591ca6:      	jb	0x591d00 <.text+0x190d00>
  591ca8:      	addb	%ch, -0x4bffa78e(%edx)
  591cae:      	jb	0x591d08 <.text+0x190d08>
  591cb0:      	addb	%bh, -0x37ffa78e(%esi)
  591cb6:      	jb	0x591d10 <.text+0x190d10>
  591cb8:      	addb	%dl, %dl
  591cba:      	jb	0x591d14 <.text+0x190d14>
  591cbc:      	addb	%bl, %ah
  591cbe:      	jb	0x591d18 <.text+0x190d18>
  591cc0:      	addb	%dh, %al
  591cc2:      	jb	0x591d1c <.text+0x190d1c>
  591cc4:      	addb	%bh, %dl
  591cc6:      	jb	0x591d20 <.text+0x190d20>
  591cc8:      	addb	%al, (%ebx,%esi,2)
  591ccb:      	popl	%eax
  591ccc:      	addb	%cl, (%esi)
  591cce:      	jae	0x591d28 <.text+0x190d28>
  591cd0:      	addb	%bl, (%eax)
  591cd2:      	jae	0x591d2c <.text+0x190d2c>
  591cd4:      	addb	%dh, 0x75(%eax)
  591cd7:      	popl	%eax
  591cd8:      	addb	%ah, %dh
  591cda:      	jb	0x591d34 <.text+0x190d34>
  591cdc:      	addb	%ah, (%edx)
  591cde:      	jae	0x591d38 <.text+0x190d38>
  591ce0:      	addb	%ch, (%ebx,%esi,2)
  591ce3:      	popl	%eax
  591ce4:      	addb	%dh, (%esi)
  591ce6:      	jae	0x591d40 <.text+0x190d40>
  591ce8:      	addb	%cl, 0x73(%edx)
  591ceb:      	popl	%eax
  591cec:      	addb	%dl, 0x58(%ebx,%esi,2)
  591cf0:      	addb	%bl, 0x73(%esi)
  591cf3:      	popl	%eax
  591cf4:      	addb	%ch, 0x73(%eax)
  591cf7:      	popl	%eax
  591cf8:      	addb	%dh, 0x73(%edx)
  591cfb:      	popl	%eax
  591cfc:      	addb	%bh, 0x58(%ebx,%esi,2)
  591d00:      	addb	%al, -0x6fffa78d(%esi)
  591d06:      	jae	0x591d60 <.text+0x190d60>
  591d08:      	addb	%bl, -0x5bffa78d(%edx)
  591d0e:      	jae	0x591d68 <.text+0x190d68>
  591d10:      	addb	%al, 0x73(%eax)
  591d13:      	popl	%eax
  591d14:      	addb	%ch, -0x47ffa78d(%esi)
  591d1a:      	jae	0x591d74 <.text+0x190d74>
  591d1c:      	addb	%al, %dl
  591d1e:      	jae	0x591d78 <.text+0x190d78>
  591d20:      	addb	%dl, %dh
  591d22:      	jae	0x591d7c <.text+0x190d7c>
  591d24:      	addb	%cl, %ah
  591d26:      	jae	0x591d80 <.text+0x190d80>
  591d28:      	addb	%ah, %al
  591d2a:      	jae	0x591d84 <.text+0x190d84>
  591d2c:      	addb	%ch, %dl
  591d2e:      	jae	0x591d88 <.text+0x190d88>
  591d30:      	addb	%dh, %ah
  591d32:      	jae	0x591d8c <.text+0x190d8c>
  591d34:      	addb	%bh, %dh
  591d36:      	jae	0x591d90 <.text+0x190d90>
  591d38:      	addb	%cl, (%eax)
  591d3a:      	je	0x591d94 <.text+0x190d94>
  591d3c:      	addb	%dl, (%edx)
  591d3e:      	je	0x591d98 <.text+0x190d98>
  591d40:      	addb	%bl, (%esp,%esi,2)
  591d43:      	popl	%eax
  591d44:      	addb	%ah, (%esi)
  591d46:      	je	0x591da0 <.text+0x190da0>
  591d48:      	addb	%bh, (%edx)
  591d4a:      	je	0x591da4 <.text+0x190da4>
  591d4c:      	addb	%al, 0x58(%esp,%esi,2)
  591d50:      	addb	%cl, 0x74(%esi)
  591d53:      	popl	%eax
  591d54:      	addb	%bl, 0x74(%eax)
  591d57:      	popl	%eax
  591d58:      	addb	%ah, 0x74(%edx)
  591d5b:      	popl	%eax
  591d5c:      	addb	%ch, 0x58(%esp,%esi,2)
  591d60:      	addb	%dh, (%eax)
  591d62:      	je	0x591dbc <.text+0x190dbc>
  591d64:      	addb	%dh, 0x74(%esi)
  591d67:      	popl	%eax
  591d68:      	addb	%cl, -0x6bffa78c(%edx)
  591d6e:      	je	0x591dc8 <.text+0x190dc8>
  591d70:      	addb	%bl, -0x57ffa78c(%esi)
  591d76:      	je	0x591dd0 <.text+0x190dd0>
  591d78:      	addb	%al, -0x4dffa78c(%eax)
  591d7e:      	je	0x591dd8 <.text+0x190dd8>
  591d80:      	addb	%al, %dh
  591d82:      	je	0x591ddc <.text+0x190ddc>
  591d84:      	addb	%dl, %al
  591d86:      	je	0x591de0 <.text+0x190de0>
  591d88:      	addb	%bl, %dl
  591d8a:      	je	0x591de4 <.text+0x190de4>
  591d8c:      	addb	%ah, %ah
  591d8e:      	je	0x591de8 <.text+0x190de8>
  591d90:      	addb	%ch, %dh
  591d92:      	je	0x591dec <.text+0x190dec>
  591d94:      	addb	%bh, %al
  591d96:      	je	0x591df0 <.text+0x190df0>
  591d98:      	addb	%al, (%edx)
  591d9a:      	jne	0x591df4 <.text+0x190df4>
  591d9c:      	addb	%cl, 0x75160058(,%esi,2)
  591da3:      	popl	%eax
  591da4:      	addb	%ah, (%eax)
  591da6:      	jne	0x591e00 <.text+0x190e00>
  591da8:      	addb	%ch, (%edx)
  591daa:      	jne	0x591e04 <.text+0x190e04>
  591dac:      	addb	%dh, 0x753e0058(,%esi,2)
  591db3:      	popl	%eax
  591db4:      	addb	%cl, 0x75(%eax)
  591db7:      	popl	%eax
  591db8:      	addb	%bh, 0x75520058(%esp,%esi,2)
  591dbf:      	popl	%eax
  591dc0:      	addb	%bl, 0x58(%ebp,%esi,2)
  591dc4:      	addb	%ah, 0x75(%esi)
  591dc7:      	popl	%eax
  591dc8:      	addb	%dl, (%esi)
  591dca:      	sbbb	(%ecx), %bl
  591dcd:      	addb	%al, (%ecx)
  591dcf:      	addb	(%ebx), %al
  591dd1:      	pushl	%edx
  591dd2:      	pushl	%edx
  591dd3:      	pushl	%edx
  591dd4:      	pushl	%edx
  591dd5:      	pushl	%edx
  591dd6:      	pushl	%edx
  591dd7:      	pushl	%edx
  591dd8:      	pushl	%edx
  591dd9:      	pushl	%edx
  591dda:      	pushl	%edx
  591ddb:      	pushl	%edx
  591ddc:      	pushl	%edx
  591ddd:      	addb	$0x5, %al
  591ddf:      	pushl	%es
  591de0:      	popl	%es
  591de1:      	pushl	%edx
  591de2:      	pushl	%edx
  591de3:      	pushl	%edx
  591de4:      	pushl	%edx
  591de5:      	pushl	%edx
  591de6:      	pushl	%edx
  591de7:      	pushl	%edx
  591de8:      	pushl	%edx
  591de9:      	pushl	%edx
  591dea:      	pushl	%edx
  591deb:      	pushl	%edx
  591dec:      	pushl	%edx
  591ded:      	orb	%cl, (%ecx)
  591def:      	pushl	%edx
  591df0:      	pushl	%edx
  591df1:      	pushl	%edx
  591df2:      	pushl	%edx
  591df3:      	pushl	%edx
  591df4:      	pushl	%edx
  591df5:      	pushl	%edx
  591df6:      	pushl	%edx
  591df7:      	pushl	%edx
  591df8:      	pushl	%edx
  591df9:      	pushl	%edx
  591dfa:      	pushl	%edx
  591dfb:      	pushl	%edx
  591dfc:      	pushl	%edx
  591dfd:      	orb	(%ebx), %cl
  591dff:      	pushl	%edx
  591e00:      	pushl	%edx
  591e01:      	pushl	%edx
  591e02:      	pushl	%edx
  591e03:      	pushl	%edx
  591e04:      	pushl	%edx
  591e05:      	pushl	%edx
  591e06:      	pushl	%edx
  591e07:      	pushl	%edx
  591e08:      	pushl	%edx
  591e09:      	pushl	%edx
  591e0a:      	pushl	%edx
  591e0b:      	pushl	%edx
  591e0c:      	pushl	%edx
  591e0d:      	orb	$0xd, %al
  591e0f:      	pushl	%edx
  591e10:      	pushl	%edx
  591e11:      	pushl	%edx
  591e12:      	pushl	%edx
  591e13:      	pushl	%edx
  591e14:      	pushl	%edx
  591e15:      	pushl	%edx
  591e16:      	pushl	%edx
  591e17:      	pushl	%edx
  591e18:      	pushl	%edx
  591e19:      	pushl	%edx
  591e1a:      	pushl	%edx
  591e1b:      	pushl	%edx
  591e1c:      	pushl	%edx
  591e1d:      	pushl	%cs
  591e1e:      	movups	(%ecx), %xmm2
  591e21:      	adcb	(%ebx), %dl
  591e23:      	adcb	$0x15, %al
  591e25:      	pushl	%edx
  591e26:      	pushl	%edx
  591e27:      	pushl	%edx
  591e28:      	pushl	%edx
  591e29:      	pushl	%edx
  591e2a:      	pushl	%edx
  591e2b:      	pushl	%edx
  591e2c:      	pushl	%edx
  591e2d:      	pushl	%ss
  591e2e:      	popl	%ss
  591e2f:      	sbbb	%dl, 0x52(%edx)
  591e32:      	sbbl	%ebx, (%edx)
  591e34:      	sbbl	0x21201f1e(,%ebx), %ebx
  591e3b:      	andb	(%ebx), %ah
  591e3d:      	andb	$0x25, %al
  591e3f:      	pushl	%edx
  591e40:      	pushl	%edx
  591e41:      	pushl	%edx
  591e42:      	pushl	%edx
  591e43:      	pushl	%edx
  591e44:      	pushl	%edx
  591e45:      	pushl	%edx
  591e46:      	pushl	%edx
  591e47:      	pushl	%edx
  591e48:      	pushl	%edx
  591e49:      	pushl	%edx
  591e4a:      	pushl	%edx
  591e4b:      	pushl	%edx
  591e4c:      	pushl	%edx
  591e4d:      	daa
  591e4f:      	subb	%dl, 0x52(%edx)
  591e52:      	pushl	%edx
  591e53:      	pushl	%edx
  591e54:      	pushl	%edx
  591e55:      	pushl	%edx
  591e56:      	pushl	%edx
  591e57:      	pushl	%edx
  591e58:      	pushl	%edx
  591e59:      	pushl	%edx
  591e5a:      	pushl	%edx
  591e5b:      	pushl	%edx
  591e5c:      	pushl	%edx
  591e5d:      	subl	%ebp, (%edx)
  591e5f:      	pushl	%edx
  591e60:      	pushl	%edx
  591e61:      	pushl	%edx
  591e62:      	pushl	%edx
  591e63:      	pushl	%edx
  591e64:      	pushl	%edx
  591e65:      	pushl	%edx
  591e66:      	pushl	%edx
  591e67:      	pushl	%edx
  591e68:      	pushl	%edx
  591e69:      	pushl	%edx
  591e6a:      	pushl	%edx
  591e6b:      	pushl	%edx
  591e6c:      	pushl	%edx
  591e6d:      	subl	0x52525252(,%ebp), %ebp
  591e74:      	pushl	%edx
  591e75:      	pushl	%edx
  591e76:      	pushl	%edx
  591e77:      	pushl	%edx
  591e78:      	pushl	%edx
  591e79:      	pushl	%edx
  591e7a:      	pushl	%edx
  591e7b:      	pushl	%edx
  591e7c:      	pushl	%edx
  591e7d:      	das
  591e7f:      	pushl	%edx
  591e80:      	pushl	%edx
  591e81:      	pushl	%edx
  591e82:      	pushl	%edx
  591e83:      	pushl	%edx
  591e84:      	pushl	%edx
  591e85:      	pushl	%edx
  591e86:      	pushl	%edx
  591e87:      	pushl	%edx
  591e88:      	pushl	%edx
  591e89:      	pushl	%edx
  591e8a:      	pushl	%edx
  591e8b:      	pushl	%edx
  591e8c:      	pushl	%edx
  591e8d:      	xorb	%dh, (%ecx)
  591e8f:      	xorb	(%ebx), %dh
  591e91:      	xorb	$0x35, %al
  591e93:      	aaa
  591e95:      	pushl	%edx
  591e96:      	pushl	%edx
  591e97:      	pushl	%edx
  591e98:      	pushl	%edx
  591e99:      	pushl	%edx
  591e9a:      	pushl	%edx
  591e9b:      	pushl	%edx
  591e9c:      	pushl	%edx
  591e9d:      	cmpb	%bh, (%ecx)
  591e9f:      	cmpb	(%ebx), %bh
  591ea1:      	cmpb	$0x3d, %al
  591ea3:      	pushl	%edx
  591ea4:      	pushl	%edx
  591ea5:      	pushl	%edx
  591ea6:      	pushl	%edx
  591ea7:      	pushl	%edx
  591ea8:      	pushl	%edx
  591ea9:      	pushl	%edx
  591eaa:      	pushl	%edx
  591eab:      	pushl	%edx
  591eac:      	pushl	%edx
  591ead:      	aas
  591eaf:      	incl	%eax
  591eb0:      	incl	%ecx
  591eb1:      	incl	%edx
  591eb2:      	incl	%ebx
  591eb3:      	incl	%esp
  591eb4:      	incl	%ebp
  591eb5:      	incl	%esi
  591eb6:      	incl	%edi
  591eb7:      	decl	%eax
  591eb8:      	decl	%ecx
  591eb9:      	decl	%edx
  591eba:      	decl	%ebx
  591ebb:      	decl	%esp
  591ebc:      	decl	%ebp
  591ebd:      	decl	%esi
  591ebe:      	decl	%edi
  591ebf:      	pushl	%eax
  591ec0:      	pushl	%ecx
  591ec1:      	movb	$0x75, %ch
  591ec3:      	popl	%eax
  591ec4:      	addb	%bh, -0x36ffa78b(%edi)
  591eca:      	jne	0x591f24 <.text+0x190f24>
  591ecc:      	addb	%dl, %bl
  591ece:      	jne	0x591f28 <.text+0x190f28>
  591ed0:      	addb	%bl, %ch
  591ed2:      	jne	0x591f2c <.text+0x190f2c>
  591ed4:      	addb	%ah, %bh
  591ed6:      	jne	0x591f30 <.text+0x190f30>
  591ed8:      	addb	%dh, %cl
  591eda:      	jne	0x591f34 <.text+0x190f34>
  591edc:      	addb	%bh, %bl
  591ede:      	jne	0x591f38 <.text+0x190f38>
  591ee0:      	addb	%al, 0xf005876
  591ee6:      	jbe	0x591f40 <.text+0x190f40>
  591ee8:      	addb	%bl, (%ecx)
  591eea:      	jbe	0x591f44 <.text+0x190f44>
  591eec:      	addb	%ah, (%ebx)
  591eee:      	jbe	0x591f48 <.text+0x190f48>
  591ef0:      	addb	%ch, 0x37005876
  591ef6:      	jbe	0x591f50 <.text+0x190f50>
  591ef8:      	addb	%al, 0x76(%ecx)
  591efb:      	popl	%eax
  591efc:      	addb	%cl, 0x76(%ebx)
  591eff:      	popl	%eax
  591f00:      	addb	%dl, 0x76(%ebp)
  591f03:      	popl	%eax
  591f04:      	addb	%bl, 0x76(%edi)
  591f07:      	popl	%eax
  591f08:      	addb	%ch, 0x76(%ecx)
  591f0b:      	popl	%eax
  591f0c:      	addb	%dh, 0x76(%ebx)
  591f0f:      	popl	%eax
  591f10:      	addb	%bh, 0x76(%ebp)
  591f13:      	popl	%eax
  591f14:      	addb	%al, -0x6effa78a(%edi)
  591f1a:      	jbe	0x591f74 <.text+0x190f74>
  591f1c:      	addb	%bl, -0x1effa78a(%ebx)
  591f22:      	jbe	0x591f7c <.text+0x190f7c>
  591f24:      	addb	%ch, %bl
  591f26:      	jbe	0x591f80 <.text+0x190f80>
  591f28:      	addb	%dh, %ch
  591f2a:      	jbe	0x591f84 <.text+0x190f84>
  591f2c:      	addb	%bh, %bh
  591f2e:      	jbe	0x591f88 <.text+0x190f88>
  591f30:      	addb	%cl, (%ecx)
  591f32:      	ja	0x591f8c <.text+0x190f8c>
  591f34:      	addb	%dl, (%ebx)
  591f36:      	ja	0x591f90 <.text+0x190f90>
  591f38:      	addb	%bl, 0x27005877
  591f3e:      	ja	0x591f98 <.text+0x190f98>
  591f40:      	addb	%dh, (%ecx)
  591f42:      	ja	0x591f9c <.text+0x190f9c>
  591f44:      	addb	%bh, (%ebx)
  591f46:      	ja	0x591fa0 <.text+0x190fa0>
  591f48:      	addb	%al, 0x77(%ebp)
  591f4b:      	popl	%eax
  591f4c:      	addb	%cl, 0x77(%edi)
  591f4f:      	popl	%eax
  591f50:      	addb	%bl, 0x77(%ecx)
  591f53:      	popl	%eax
  591f54:      	addb	%ah, 0x77(%ebx)
  591f57:      	popl	%eax
  591f58:      	addb	%ch, 0x77(%ebp)
  591f5b:      	popl	%eax
  591f5c:      	addb	%dh, 0x77(%edi)
  591f5f:      	popl	%eax
  591f60:      	addb	%al, -0x74ffa789(%ecx)
  591f66:      	ja	0x591fc0 <.text+0x190fc0>
  591f68:      	addb	%dl, -0x60ffa789(%ebp)
  591f6e:      	ja	0x591fc8 <.text+0x190fc8>
  591f70:      	addb	%ch, -0x4cffa789(%ecx)
  591f76:      	ja	0x591fd0 <.text+0x190fd0>
  591f78:      	addb	%bh, -0x38ffa789(%ebp)
  591f7e:      	ja	0x591fd8 <.text+0x190fd8>
  591f80:      	addb	%dl, %cl
  591f82:      	ja	0x591fdc <.text+0x190fdc>
  591f84:      	addb	%bl, %bl
  591f86:      	ja	0x591fe0 <.text+0x190fe0>
  591f88:      	addb	%ah, %ch
  591f8a:      	ja	0x591fe4 <.text+0x190fe4>
  591f8c:      	addb	%ch, %bh
  591f8e:      	ja	0x591fe8 <.text+0x190fe8>
  591f90:      	addb	%bh, %cl
  591f92:      	ja	0x591fec <.text+0x190fec>
  591f94:      	addb	%al, (%ebx)
  591f96:      	js	0x591ff0 <.text+0x190ff0>
  591f98:      	addb	%cl, 0x17005878
  591f9e:      	js	0x591ff8 <.text+0x190ff8>
  591fa0:      	addb	%ah, (%ecx)
  591fa2:      	js	0x591ffc <.text+0x190ffc>
  591fa4:      	addb	%ch, (%ebx)
  591fa6:      	js	0x592000 <.text+0x191000>
  591fa8:      	addb	%dh, 0x3f005878
  591fae:      	js	0x592008 <.text+0x191008>
  591fb0:      	addb	%cl, 0x78(%ecx)
  591fb3:      	popl	%eax
  591fb4:      	addb	%dl, 0x78(%ebx)
  591fb7:      	popl	%eax
  591fb8:      	addb	%bl, 0x78(%ebp)
  591fbb:      	popl	%eax
  591fbc:      	addb	%ah, 0x78(%edi)
  591fbf:      	popl	%eax
  591fc0:      	addb	%dh, 0x78(%ecx)
  591fc3:      	popl	%eax
  591fc4:      	addb	%bh, 0x78(%ebx)
  591fc7:      	popl	%eax
  591fc8:      	addb	%al, -0x70ffa788(%ebp)
  591fce:      	js	0x592028 <.text+0x191028>
  591fd0:      	addb	%bl, -0x5cffa788(%ecx)
  591fd6:      	js	0x592030 <.text+0x191030>
  591fd8:      	addb	%ch, -0x48ffa788(%ebp)
  591fde:      	js	0x592038 <.text+0x191038>
  591fe0:      	addb	%al, %cl
  591fe2:      	js	0x59203c <.text+0x19103c>
  591fe4:      	addb	%cl, %bl
  591fe6:      	js	0x592040 <.text+0x191040>
  591fe8:      	addb	%dl, %ch
  591fea:      	js	0x592044 <.text+0x191044>
  591fec:      	addb	%bl, %bh
  591fee:      	js	0x592048 <.text+0x191048>
  591ff0:      	addb	%ch, %cl
  591ff2:      	js	0x59204c <.text+0x19104c>
  591ff4:      	addb	%dh, %bl
  591ff6:      	js	0x592050 <.text+0x191050>
  591ff8:      	addb	%bh, %ch
  591ffa:      	js	0x592054 <.text+0x191054>
  591ffc:      	addb	%al, (%edi)
  591ffe:      	jns	0x592058 <.text+0x191058>
  592000:      	addb	%dl, (%ecx)
  592002:      	jns	0x59205c <.text+0x19105c>
  592004:      	addb	%bl, (%ebx)
  592006:      	jns	0x592060 <.text+0x191060>
  592008:      	addb	%ah, 0x2f005879
  59200e:      	jns	0x592068 <.text+0x191068>
  592010:      	addb	%bh, (%ecx)
  592012:      	jns	0x59206c <.text+0x19106c>
  592014:      	addb	%al, 0x79(%ebx)
  592017:      	popl	%eax
  592018:      	addb	%cl, 0x79(%ebp)
  59201b:      	popl	%eax
  59201c:      	addb	%dl, 0x79(%edi)
  59201f:      	popl	%eax
  592020:      	addb	%ah, 0x79(%ecx)
  592023:      	popl	%eax
  592024:      	addb	%ch, 0x79(%ebx)
  592027:      	popl	%eax
  592028:      	addb	%dh, 0x79(%ebp)
  59202b:      	popl	%eax
  59202c:      	addb	%bh, 0x79(%edi)
  59202f:      	popl	%eax
  592030:      	addb	%cl, -0x6cffa787(%ecx)
  592036:      	jns	0x592090 <.text+0x191090>
  592038:      	addb	%bl, -0x58ffa787(%ebp)
  59203e:      	jns	0x592098 <.text+0x191098>
  592040:      	addb	%dh, -0x44ffa787(%ecx)
  592046:      	jns	0x5920a0 <.text+0x1910a0>
  592048:      	addb	%al, %ch
  59204a:      	jns	0x5920a4 <.text+0x1910a4>
  59204c:      	addb	%cl, %bh
  59204e:      	jns	0x5920a8 <.text+0x1910a8>
  592050:      	addb	%bl, %cl
  592052:      	jns	0x5920ac <.text+0x1910ac>
  592054:      	addb	%ah, %bl
  592056:      	jns	0x5920b0 <.text+0x1910b0>
  592058:      	addb	%ch, %ch
  59205a:      	jns	0x5920b4 <.text+0x1910b4>
  59205c:      	addb	%dh, %bh
  59205e:      	jns	0x5920b8 <.text+0x1910b8>
  592060:      	addb	%al, (%ecx)
  592062:      	jp	0x5920bc <.text+0x1910bc>
  592064:      	addb	%cl, (%ebx)
  592066:      	jp	0x5920c0 <.text+0x1910c0>
  592068:      	addb	%dl, 0x1f00587a
  59206e:      	jp	0x5920c8 <.text+0x1910c8>
  592070:      	addb	%ch, (%ecx)
  592072:      	jp	0x5920cc <.text+0x1910cc>
  592074:      	addb	%dh, (%ebx)
  592076:      	jp	0x5920d0 <.text+0x1910d0>
  592078:      	addb	%bh, 0x4700587a
  59207e:      	jp	0x5920d8 <.text+0x1910d8>
  592080:      	addb	%dl, 0x7a(%ecx)
  592083:      	popl	%eax
  592084:      	addb	%bl, 0x7a(%ebx)
  592087:      	popl	%eax
  592088:      	addb	%ah, 0x7a(%ebp)
  59208b:      	popl	%eax
  59208c:      	addb	%ch, 0x7a(%edi)
  59208f:      	popl	%eax
  592090:      	addb	%bh, 0x7a(%ecx)
  592093:      	popl	%eax
  592094:      	addb	%al, -0x72ffa786(%ebx)
  59209a:      	jp	0x5920f4 <.text+0x1910f4>
  59209c:      	addb	%dl, -0x5effa786(%edi)
  5920a2:      	jp	0x5920fc <.text+0x1910fc>
  5920a4:      	addb	%ch, -0x4affa786(%ebx)
  5920aa:      	jp	0x592104 <.text+0x191104>
  5920ac:      	addb	%bh, -0x36ffa786(%edi)
  5920b2:      	jp	0x59210c <.text+0x19110c>
  5920b4:      	addb	%dl, %bl
  5920b6:      	jp	0x592110 <.text+0x191110>
  5920b8:      	addb	%bl, %ch
  5920ba:      	jp	0x592114 <.text+0x191114>
  5920bc:      	addb	%ah, %bh
  5920be:      	jp	0x592118 <.text+0x191118>
  5920c0:      	addb	%ah, -0x50ffa78a(%ebp)
  5920c6:      	jbe	0x592120 <.text+0x191120>
  5920c8:      	addb	%bh, -0x3cffa78a(%ecx)
  5920ce:      	jbe	0x592128 <.text+0x191128>
  5920d0:      	addb	%cl, %ch
  5920d2:      	jbe	0x59212c <.text+0x19112c>
  5920d4:      	addb	%dl, %bh
  5920d6:      	jbe	0x592130 <.text+0x191130>
  5920d8:      	addb	%dl, (%esi)
  5920da:      	sbbb	(%ecx), %bl
  5920dd:      	addb	%al, (%ecx)
  5920df:      	addb	(%ebx), %al
  5920e1:      	addb	$0x5, %al
  5920e3:      	pushl	%es
  5920e4:      	popl	%es
  5920e5:      	orb	%cl, (%ecx)
  5920e7:      	orb	(%ebx), %cl
  5920e9:      	orb	$0xd, %al
  5920eb:      	pushl	%cs
  5920ec:      	movups	(%ecx), %xmm2
  5920ef:      	adcb	(%ebx), %dl
  5920f1:      	adcb	$0x15, %al
  5920f3:      	pushl	%ss
  5920f4:      	popl	%ss
  5920f5:      	sbbb	%bl, (%ecx)
  5920f7:      	sbbb	(%ebx), %bl
  5920f9:      	sbbb	$0x1d, %al
  5920fb:      	pushl	%ds
  5920fc:      	popl	%ds
  5920fd:      	andb	%ah, (%ecx)
  5920ff:      	andb	(%ebx), %ah
  592101:      	andb	$0x25, %al
  592103:      	daa
  592105:      	subb	%ch, (%ecx)
  592107:      	subb	(%ebx), %ch
  592109:      	subb	$0x2d, %al
  59210b:      	das
  59210d:      	xorb	%dh, (%ecx)
  59210f:      	xorb	(%ebx), %dh
  592111:      	xorb	$0x35, %al
  592113:      	aaa
  592115:      	cmpb	%bh, (%ecx)
  592117:      	cmpb	(%ebx), %bh
  592119:      	cmpb	$0x3d, %al
  59211b:      	aas
  59211d:      	incl	%eax
  59211e:      	incl	%ecx
  59211f:      	incl	%edx
  592120:      	xchgb	%al, 0x44(%ebx)
  592123:      	incl	%ebp
  592124:      	incl	%esi
  592125:      	xchgb	%al, 0x48478686(%esi)
  59212b:      	xchgb	%cl, 0x4a(%ecx)
  59212e:      	xchgb	%al, -0x79b2b3b5(%esi)
  592134:      	xchgb	%al, -0x7979797a(%esi)
  59213a:      	decl	%esi
  59213b:      	decl	%edi
  59213c:      	pushl	%eax
  59213d:      	xchgb	%dl, 0x52(%ecx)
  592140:      	xchgb	%al, 0x55548653(%esi)
  592146:      	pushl	%esi
  592147:      	pushl	%edi
  592148:      	popl	%eax
  592149:      	xchgb	%bl, 0x5a(%ecx)
  59214c:      	xchgb	%bl, 0x5c(%ebx)
  59214f:      	popl	%ebp
  592150:      	xchgb	%al, -0x797979a2(%esi)
  592156:      	xchgb	%al, 0x605f8686(%esi)
  59215c:      	popal
  59215d:      	bound	%esp, 0x64(%ebx)
  592160:      	addr16		pushw	$0x6a69         # imm = 0x6A69
  592166:      	imull	$0x6f, 0x6e6d866c(%esi), %eax
  59216d:      	jo	0x5921e0 <.text+0x1911e0>
  59216f:      	jb	0x5921e4 <.text+0x1911e4>
  592171:      	je	0x5921e8 <.text+0x1911e8>
  592173:      	jbe	0x5921ec <.text+0x1911ec>
  592175:      	xchgb	%al, 0x7b7a7978(%esi)
  59217b:      	jl	0x5921fa <.text+0x1911fa>
  59217d:      	jle	0x5921fe <.text+0x1911fe>
  59217f:      	xchgb	%al, -0x7979797a(%esi)
  592185:      	xchgb	%al, -0x7979797a(%esi)
  59218b:      	xchgb	%al, -0x7979797a(%esi)
  592191:      	xchgb	%al, -0x7979797a(%esi)
  592197:      	xchgb	%al, -0x7979797a(%esi)
  59219d:      	xchgb	%al, -0x7979797a(%esi)
  5921a3:      	xchgb	%al, -0x7979797a(%esi)
  5921a9:      	xchgb	%al, -0x7979797a(%esi)
  5921af:      	xchgb	%al, -0x7979797a(%esi)
  5921b5:      	xchgb	%al, -0x7979797a(%esi)
  5921bb:      	xchgb	%al, -0x7979797a(%esi)
  5921c1:      	xchgb	%al, -0x7979797a(%esi)
  5921c7:      	xchgb	%al, -0x7979797a(%esi)
  5921cd:      	xchgb	%al, -0x7979797a(%esi)
  5921d3:      	xchgb	%al, -0x7979797a(%esi)
  5921d9:      	xchgb	%al, -0x7979797a(%esi)
  5921df:      	xchgb	%al, -0x7979797a(%esi)
  5921e5:      	xchgb	%al, -0x7e7f797a(%esi)
  5921eb:      	addb	$-0x77, -0x747a7c(%ebx)
  5921f2:      	jnp	0x59224c <.text+0x19124c>
  5921f4:      	addb	%ah, 0x7b(%ecx)
  5921f7:      	popl	%eax
  5921f8:      	addb	%ch, 0x7b(%ebx)
  5921fb:      	popl	%eax
  5921fc:      	addb	%dh, 0x7b(%ebp)
  5921ff:      	popl	%eax
  592200:      	addb	%bh, 0x7b(%edi)
  592203:      	popl	%eax
  592204:      	addb	%dl, -0x62ffa785(%ebx)
  59220a:      	jnp	0x592264 <.text+0x191264>
  59220c:      	addb	%ah, -0x4effa785(%edi)
  592212:      	jnp	0x59226c <.text+0x19126c>
  592214:      	addb	%bh, -0x3affa785(%ebx)
  59221a:      	jnp	0x592274 <.text+0x191274>
  59221c:      	addb	%cl, %bh
  59221e:      	jnp	0x592278 <.text+0x191278>
  592220:      	addb	%dl, (%esi)
  592222:      	sbbb	(%ecx), %bl
  592225:      	addb	%cl, (%esp,%ecx)
  592228:      	orb	$0xc, %al
  59222a:      	orb	$0xc, %al
  59222c:      	orb	$0xc, %al
  59222e:      	orb	$0xc, %al
  592230:      	orb	$0xc, %al
  592232:      	addl	%eax, (%edx)
  592234:      	addl	0x9080706(,%eax), %eax
  59223b:      	orb	(%ebx), %cl
  59223d:      	popl	%es
  59223e:      	jl	0x592298 <.text+0x191298>
  592240:      	addb	%dl, (%ecx)
  592242:      	jl	0x59229c <.text+0x19129c>
  592244:      	addb	%bl, (%ebx)
  592246:      	jl	0x5922a0 <.text+0x1912a0>
  592248:      	addb	%ah, 0x2f00587c
  59224e:      	jl	0x5922a8 <.text+0x1912a8>
  592250:      	addb	%bh, (%ecx)
  592252:      	jl	0x5922ac <.text+0x1912ac>
  592254:      	addb	%al, 0x7c(%ebx)
  592257:      	popl	%eax
  592258:      	addb	%cl, 0x7c(%ebp)
  59225b:      	popl	%eax
  59225c:      	addb	%dl, 0x7c(%edi)
  59225f:      	popl	%eax
  592260:      	addb	%ah, 0x7c(%ecx)
  592263:      	popl	%eax
  592264:      	addb	%dl, 0x7c9e0058(%esp,%edi,2)
  59226b:      	popl	%eax
  59226c:      	addb	%ch, -0x4dffa784(%eax)
  592272:      	jl	0x5922cc <.text+0x1912cc>
  592274:      	addb	%bh, 0x7cc60058(%esp,%edi,2)
  59227b:      	popl	%eax
  59227c:      	addb	%dl, %al
  59227e:      	jl	0x5922d8 <.text+0x1912d8>
  592280:      	addb	%bl, %dl
  592282:      	jl	0x5922dc <.text+0x1912dc>
  592284:      	addb	%ah, %ah
  592286:      	jl	0x5922e0 <.text+0x1912e0>
  592288:      	addb	%ch, %dh
  59228a:      	jl	0x5922e4 <.text+0x1912e4>
  59228c:      	addb	%bh, %al
  59228e:      	jl	0x5922e8 <.text+0x1912e8>
  592290:      	addb	%al, (%edx)
  592292:      	jge	0x5922ec <.text+0x1912ec>
  592294:      	addb	%cl, 0x7d160058(,%edi,2)
  59229b:      	popl	%eax
  59229c:      	addb	%ah, (%eax)
  59229e:      	jge	0x5922f8 <.text+0x1912f8>
  5922a0:      	addb	%ch, (%edx)
  5922a2:      	jge	0x5922fc <.text+0x1912fc>
  5922a4:      	addb	%dh, 0x7d3e0058(,%edi,2)
  5922ab:      	popl	%eax
  5922ac:      	addb	%cl, 0x7d(%eax)
  5922af:      	popl	%eax
  5922b0:      	addb	%dl, 0x7d(%edx)
  5922b3:      	popl	%eax
  5922b4:      	addb	%bl, 0x58(%ebp,%edi,2)
  5922b8:      	addb	%ah, 0x7d(%esi)
  5922bb:      	popl	%eax
  5922bc:      	addb	%dh, 0x7d(%eax)
  5922bf:      	popl	%eax
  5922c0:      	addb	%bh, 0x7d(%edx)
  5922c3:      	popl	%eax
  5922c4:      	addb	%ah, -0x52ffa783(%ebx)
  5922ca:      	jge	0x592324 <.text+0x191324>
  5922cc:      	addb	%dh, -0x3effa783(%edi)
  5922d2:      	jge	0x59232c <.text+0x19132c>
  5922d4:      	addb	%cl, %bl
  5922d6:      	jge	0x592330 <.text+0x191330>
  5922d8:      	addb	%dl, %ch
  5922da:      	jge	0x592334 <.text+0x191334>
  5922dc:      	addb	%bl, %bh
  5922de:      	jge	0x592338 <.text+0x191338>
  5922e0:      	addb	%ch, %cl
  5922e2:      	jge	0x59233c <.text+0x19133c>
  5922e4:      	addb	%dh, %bl
  5922e6:      	jge	0x592340 <.text+0x191340>
  5922e8:      	addb	%bh, %ch
  5922ea:      	jge	0x592344 <.text+0x191344>
  5922ec:      	addb	%al, (%edi)
  5922ee:      	jle	0x592348 <.text+0x191348>
  5922f0:      	addb	%dl, (%ecx)
  5922f2:      	jle	0x59234c <.text+0x19134c>
  5922f4:      	addb	%bl, (%ebx)
  5922f6:      	jle	0x592350 <.text+0x191350>
  5922f8:      	addb	%ah, 0x2f00587e
  5922fe:      	jle	0x592358 <.text+0x191358>
  592300:      	addb	%bh, (%ecx)
  592302:      	jle	0x59235c <.text+0x19135c>
  592304:      	addb	%al, 0x7e(%ebx)
  592307:      	popl	%eax
  592308:      	addb	%cl, 0x7e(%ebp)
  59230b:      	popl	%eax
  59230c:      	addb	%dl, 0x7e(%edi)
  59230f:      	popl	%eax
  592310:      	addb	%ah, 0x7e(%ecx)
  592313:      	popl	%eax
  592314:      	addb	%ch, 0x7e(%ebx)
  592317:      	popl	%eax
  592318:      	addb	%dh, 0x7e(%ebp)
  59231b:      	popl	%eax
  59231c:      	addb	%bh, 0x7e(%edi)
  59231f:      	popl	%eax
  592320:      	addb	%cl, -0x6cffa782(%ecx)
  592326:      	jle	0x592380 <.text+0x191380>
  592328:      	addb	%bl, -0x58ffa782(%ebp)
  59232e:      	jle	0x592388 <.text+0x191388>
  592330:      	addb	%dh, -0x44ffa782(%ecx)
  592336:      	jle	0x592390 <.text+0x191390>
  592338:      	addb	%al, %ch
  59233a:      	jle	0x592394 <.text+0x191394>
  59233c:      	addb	%cl, %bh
  59233e:      	jle	0x592398 <.text+0x191398>
  592340:      	addb	%bl, %cl
  592342:      	jle	0x59239c <.text+0x19139c>
  592344:      	addb	%ah, %bl
  592346:      	jle	0x5923a0 <.text+0x1913a0>
  592348:      	addb	%ch, %ch
  59234a:      	jle	0x5923a4 <.text+0x1913a4>
  59234c:      	addb	%dh, %bh
  59234e:      	jle	0x5923a8 <.text+0x1913a8>
  592350:      	addb	%al, (%ecx)
  592352:      	jg	0x5923ac <.text+0x1913ac>
  592354:      	addb	%cl, (%ebx)
  592356:      	jg	0x5923b0 <.text+0x1913b0>
  592358:      	addb	%dl, 0x1f00587f
  59235e:      	jg	0x5923b8 <.text+0x1913b8>
  592360:      	addb	%ch, (%ecx)
  592362:      	jg	0x5923bc <.text+0x1913bc>
  592364:      	addb	%dh, (%ebx)
  592366:      	jg	0x5923c0 <.text+0x1913c0>
  592368:      	addb	%bh, 0x4700587f
  59236e:      	jg	0x5923c8 <.text+0x1913c8>
  592370:      	addb	%dl, 0x7f(%ecx)
  592373:      	popl	%eax
  592374:      	addb	%bl, 0x7f(%ebx)
  592377:      	popl	%eax
  592378:      	addb	%ah, 0x7f(%ebp)
  59237b:      	popl	%eax
  59237c:      	addb	%dl, (%esi)
  59237e:      	sbbb	(%ecx), %bl
  592381:      	pushl	%ss
  592382:      	sbbb	(%ecx), %bl
  592385:      	pushl	%ss
  592386:      	sbbb	(%ecx), %bl
  592389:      	pushl	%ss
  59238a:      	sbbb	(%ecx), %bl
  59238d:      	pushl	%ss
  59238e:      	sbbb	(%ecx), %bl
  592391:      	pushl	%ss
  592392:      	sbbb	(%ecx), %bl
  592395:      	outsl	(%esi), %dx
  592396:      	jg	0x5923f0 <.text+0x1913f0>
  592398:      	addb	%bh, 0x7f(%ecx)
  59239b:      	popl	%eax
  59239c:      	addb	%al, -0x40ffa781(%ebx)
  5923a2:      	jg	0x5923fc <.text+0x1913fc>
  5923a4:      	addb	%cl, %cl
  5923a6:      	jg	0x592400 <.text+0x191400>
  5923a8:      	addb	%dl, %bl
  5923aa:      	jg	0x592404 <.text+0x191404>
  5923ac:      	addb	%bl, %ch
  5923ae:      	jg	0x592408 <.text+0x191408>
  5923b0:      	addb	%ah, %bh
  5923b2:      	jg	0x59240c <.text+0x19140c>
  5923b4:      	addb	%dh, %cl
  5923b6:      	jg	0x592410 <.text+0x191410>
  5923b8:      	addb	%bh, %bl
  5923ba:      	jg	0x592414 <.text+0x191414>
  5923bc:      	addb	%al, 0xf005880
  5923c2:      	sbbb	$0x19, (%eax)
  5923c6:      	sbbb	$0x16, (%eax)
  5923ca:      	sbbb	(%ecx), %bl
  5923cd:      	andl	-0x7fd2ffa8(%eax), %eax
  5923d3:      	popl	%eax
  5923d4:      	addb	%dh, (%edi)
  5923d6:      	sbbb	$0x41, (%eax)
  5923da:      	sbbb	$0x4b, (%eax)
  5923de:      	sbbb	$0x55, (%eax)
  5923e2:      	sbbb	$0x5f, (%eax)
  5923e6:      	sbbb	$0x69, (%eax)
  5923ea:      	sbbb	$0x73, (%eax)
  5923ee:      	sbbb	$0x7d, (%eax)
  5923f2:      	sbbb	$-0x79, (%eax)
  5923f6:      	sbbb	$-0x6f, (%eax)
  5923fa:      	sbbb	$-0x65, (%eax)
  5923fe:      	sbbb	$-0x5b, (%eax)
  592402:      	sbbb	$-0x51, (%eax)
  592406:      	sbbb	$-0x47, (%eax)
  59240a:      	sbbb	$-0x3d, (%eax)
  59240e:      	sbbb	$-0x33, (%eax)
  592412:      	sbbb	$-0x29, (%eax)
  592416:      	sbbb	$-0x1f, (%eax)
  59241a:      	sbbb	$-0x15, (%eax)
  59241e:      	sbbb	$-0xb, (%eax)
  592422:      	sbbb	$-0x1, (%eax)
  592426:      	sbbb	$0x9, (%eax)
  59242a:      	sbbl	$0x588113, (%eax)       # imm = 0x588113
  592431:      	sbbl	$0x27005881, %eax       # imm = 0x27005881
  592436:      	sbbl	$0x588131, (%eax)       # imm = 0x588131
  59243d:      	pushl	%ss
  59243e:      	sbbb	(%ecx), %bl
  592441:      	pushl	%ss
  592442:      	sbbb	(%ecx), %bl
  592445:      	pushl	%ss
  592446:      	sbbb	(%ecx), %bl
  592449:      	pushl	%ss
  59244a:      	sbbb	(%ecx), %bl
  59244d:      	pushl	%ss
  59244e:      	sbbb	(%ecx), %bl
  592451:      	cmpl	-0x7ebaffa8(%ecx), %eax
  592457:      	popl	%eax
  592458:      	addb	%cl, -0x7f(%edi)
  59245b:      	popl	%eax
  59245c:      	addb	%bl, -0x7f(%ecx)
  59245f:      	popl	%eax
  592460:      	addb	%ah, -0x7f(%ebx)
  592463:      	popl	%eax
  592464:      	addb	%ch, -0x7f(%ebp)
  592467:      	popl	%eax
  592468:      	addb	%dh, -0x7f(%edi)
  59246b:      	popl	%eax
  59246c:      	addb	%al, -0x74ffa77f(%ecx)
  592472:      	sbbl	$0x588195, (%eax)       # imm = 0x588195
  592479:      	lahf
  59247a:      	sbbl	$0x5881db, (%eax)       # imm = 0x5881DB
  592481:      	inl	$0x81, %eax
  592483:      	popl	%eax
  592484:      	addb	%ch, %bh
  592486:      	sbbl	$0x5881f9, (%eax)       # imm = 0x5881F9
  59248d:      	addl	-0x7df2ffa8(%edx), %eax
  592493:      	popl	%eax
  592494:      	addb	%dl, (%edi)
  592496:      	sbbb	$0x21, (%eax)
  59249a:      	sbbb	$0x2b, (%eax)
  59249e:      	sbbb	$0x35, (%eax)
  5924a2:      	sbbb	$0x3f, (%eax)
  5924a6:      	sbbb	$0x49, (%eax)
  5924aa:      	sbbb	$0x34, (%eax)
  5924ae:      	sbbl	$0x3e, (%eax)
  5924b2:      	sbbl	$0x48, (%eax)
  5924b6:      	sbbl	$0x52, (%eax)
  5924ba:      	sbbl	$0x5c, (%eax)
  5924be:      	sbbl	$0x66, (%eax)
  5924c2:      	sbbl	$0x70, (%eax)
  5924c6:      	sbbl	$0x7a, (%eax)
  5924ca:      	sbbl	$-0x5d, (%eax)
  5924ce:      	sbbl	$-0x53, (%eax)
  5924d2:      	sbbl	$-0x49, (%eax)
  5924d6:      	sbbl	$-0x3f, (%eax)
  5924da:      	sbbl	$-0x35, (%eax)
  5924de:      	sbbl	$-0x2b, (%eax)
  5924e2:      	sbbl	$-0x21, (%eax)
  5924e6:      	sbbl	$-0x17, (%eax)
  5924ea:      	sbbl	$-0xd, (%eax)
  5924ee:      	sbbl	$-0x3, (%eax)
  5924f2:      	sbbl	$0x7, (%eax)
  5924f6:      	testb	%bl, (%eax)
  5924f9:      	adcl	%eax, 0x58841b00(%eax,%ebx,2)
  592500:      	addb	%ah, 0x2f005884
  592506:      	testb	%bl, (%eax)
  592509:      	cmpl	%eax, 0x58844300(%eax,%ebx,2)
  592510:      	addb	%bh, -0x7c(%edi)
  592513:      	popl	%eax
  592514:      	addb	%cl, -0x6cffa77c(%ecx)
  59251a:      	testb	%bl, (%eax)
  59251d:      	popfl
  59251e:      	testb	%bl, (%eax)
  592521:      	cmpsl	%es:(%edi), (%esi)
  592522:      	testb	%bl, (%eax)
  592525:      	movb	$-0x7c, %cl
  592527:      	popl	%eax
  592528:      	addb	%bh, -0x3affa77c(%ebx)
  59252e:      	testb	%bl, (%eax)
  592531:      	iretl
  592532:      	testb	%bl, (%eax)
  592535:      	flds	0x5884e300(%eax,%ebx,2)
  59253c:      	addb	%ch, %ch
  59253e:      	testb	%bl, (%eax)
  592541:      	testl	$0x58854700, 0x58850100(%eax,%ebx,2) # imm = 0x58854700
  59254c:      	addb	%dl, -0x7b(%ecx)
  59254f:      	popl	%eax
  592550:      	addb	%bl, -0x7b(%ebx)
  592553:      	popl	%eax
  592554:      	addb	%ah, -0x7b(%ebp)
  592557:      	popl	%eax
  592558:      	addb	%ch, -0x7b(%edi)
  59255b:      	popl	%eax
  59255c:      	addb	%bh, -0x7b(%ecx)
  59255f:      	popl	%eax
  592560:      	addb	%al, -0x72ffa77b(%ebx)
  592566:      	testl	%ebx, (%eax)
  592569:      	xchgl	%edi, %eax
  59256a:      	testl	%ebx, (%eax)
  59256d:      	movl	0xab005885, %eax
  592572:      	testl	%ebx, (%eax)
  592575:      	movb	$-0x7b, %ch
  592577:      	popl	%eax
  592578:      	addb	%bh, -0x36ffa77b(%edi)
  59257e:      	testl	%ebx, (%eax)
  592581:      	roll	%cl, -0x7a22ffa8(%ebp)
  592587:      	popl	%eax
  592588:      	addb	%ah, %bh
  59258a:      	testl	%ebx, (%eax)
  59258d:      	<unknown>
  59258e:      	testl	%ebx, (%eax)
  592591:      	sti
  592592:      	testl	%ebx, (%eax)
  592595:      	addl	$0xf005886, %eax        # imm = 0xF005886
  59259a:      	xchgb	%bl, (%eax)
  59259d:      	sbbl	%eax, -0x79dcffa8(%esi)
  5925a3:      	popl	%eax
  5925a4:      	addb	%ch, 0x37005886
  5925aa:      	xchgb	%bl, (%eax)
  5925ad:      	incl	%ecx
  5925ae:      	xchgb	%bl, (%eax)
  5925b1:      	decl	%ebx
  5925b2:      	xchgb	%bl, (%eax)
  5925b5:      	pushl	%ebp
  5925b6:      	xchgb	%bl, (%eax)
  5925b9:      	popl	%edi
  5925ba:      	xchgb	%bl, (%eax)
  5925bd:      	imull	$0x867d0058, -0x798cffa8(%esi), %eax # imm = 0x867D0058
  5925c7:      	popl	%eax
  5925c8:      	addb	%al, -0x6effa77a(%edi)
  5925ce:      	xchgb	%bl, (%eax)
  5925d1:      	wait
  5925d2:      	xchgb	%bl, (%eax)
  5925d5:      	movsl	(%esi), %es:(%edi)
  5925d6:      	xchgb	%bl, (%eax)
  5925d9:      	scasl	%es:(%edi), %eax
  5925da:      	xchgb	%bl, (%eax)
  5925dd:      	movl	$0xc3005886, %ecx       # imm = 0xC3005886
  5925e2:      	xchgb	%bl, (%eax)
  5925e5:      	int	$0x86
  5925e7:      	popl	%eax
  5925e8:      	addb	%dl, (%esi)
  5925ea:      	sbbb	(%ecx), %bl
  5925ed:      	pushl	%ss
  5925ee:      	sbbb	(%ecx), %bl
  5925f1:      	cmpl	$0xc1005885, %eax       # imm = 0xC1005885
  5925f6:      	ldsl	(%eax), %ebx
  5925f9:      	lretl
  5925fa:      	ldsl	(%eax), %ebx
  5925fd:      	testb	%cl, -0x7685ffa8(%ecx)
  592603:      	popl	%eax
  592604:      	addb	%ch, %cl
  592606:      	ldsl	(%eax), %ebx
  592609:      	rep		ldsl	(%eax), %ebx
  59260d:      	std
  59260e:      	ldsl	(%eax), %ebx
  592611:      	popl	%es
  592612:      	<unknown>
  592615:      	<unknown>
  592619:      	cmpb	%al, %dh
  59261b:      	popl	%eax
  59261c:      	addb	%ah, 0x4c005889(%ebx)
  592622:      	<unknown>
  592625:      	pushl	%esi
  592626:      	<unknown>
  592629:      	pushal
  59262a:      	<unknown>
  59262d:      	pushl	$-0x3a
  59262f:      	popl	%eax
  592630:      	addb	%dh, 0x58(%esi,%eax,8)
  592634:      	addb	%bh, -0x3a(%esi)
  592637:      	popl	%eax
  592638:      	addb	%cl, -0x6dffa73a(%eax)
  59263e:      	<unknown>
  592641:      	pushfl
  592642:      	<unknown>
  592645:      	cmpsb	%es:(%edi), (%esi)
  592646:      	<unknown>
  592649:      	movb	$-0x3a, %al
  59264b:      	popl	%eax
  59264c:      	addb	%bh, -0x3bffa73a(%edx)
  592652:      	<unknown>
  592655:      	into
  592656:      	<unknown>
  592659:      	fadd	%st(6), %st
  59265b:      	popl	%eax
  59265c:      	addb	%ah, %dl
  59265e:      	<unknown>
  592661:      	inb	%dx, %al
  592662:      	<unknown>
  592665:      	testb	$0x58, %dh
  592668:      	addb	%al, (%eax)
  59266a:      	<unknown>
  59266d:      	orb	%bh, %al
  59266f:      	popl	%eax
  592670:      	addb	%dl, (%esi)
  592672:      	sbbb	(%ecx), %bl
  592675:      	adcb	$-0x39, %al
  592677:      	popl	%eax
  592678:      	addb	%dl, (%esi)
  59267a:      	sbbb	(%ecx), %bl
  59267d:      	pushl	%ds
  59267e:      	<unknown>
  592681:      	subb	%al, %bh
  592683:      	popl	%eax
  592684:      	addb	%dl, (%esi)
  592686:      	sbbb	(%ecx), %bl
  592689:      	pushl	%ss
  59268a:      	sbbb	(%ecx), %bl
  59268d:      	pushl	%ss
  59268e:      	sbbb	(%ecx), %bl
  592691:      	pushl	%ss
  592692:      	sbbb	(%ecx), %bl
  592695:      	pushl	%ss
  592696:      	sbbb	(%ecx), %bl
  592699:      	pushl	%ss
  59269a:      	sbbb	(%ecx), %bl
  59269d:      	pushl	%ss
  59269e:      	sbbb	(%ecx), %bl
  5926a1:      	pushl	%ss
  5926a2:      	sbbb	(%ecx), %bl
  5926a5:      	pushl	%ss
  5926a6:      	sbbb	(%ecx), %bl
  5926a9:      	pushl	%ss
  5926aa:      	sbbb	(%ecx), %bl
  5926ad:      	xorb	%bh, %al
  5926af:      	popl	%eax
  5926b0:      	addb	%bh, (%edi,%eax,8)
  5926b3:      	popl	%eax
  5926b4:      	addb	%al, -0x39(%esi)
  5926b7:      	popl	%eax
  5926b8:      	addb	%dl, -0x39(%eax)
  5926bb:      	popl	%eax
  5926bc:      	addb	%bl, -0x39(%edx)
  5926bf:      	popl	%eax
  5926c0:      	addb	%ah, 0x58(%edi,%eax,8)
  5926c4:      	addb	%ch, -0x39(%esi)
  5926c7:      	popl	%eax
  5926c8:      	addb	%bh, -0x39(%eax)
  5926cb:      	popl	%eax
  5926cc:      	addb	%al, -0x73ffa739(%edx)
  5926d2:      	<unknown>
  5926d5:      	xchgl	%esi, %eax
  5926d6:      	<unknown>
  5926d9:      	stosb	%al, %es:(%edi)
  5926da:      	<unknown>
  5926dd:      	movb	$-0x39, %ah
  5926df:      	popl	%eax
  5926e0:      	addb	%dl, %cl
  5926e2:      	<unknown>
  5926e5:      	fcmovnb	%st(7), %st
  5926e7:      	popl	%eax
  5926e8:      	addb	%ah, %ch
  5926ea:      	<unknown>
  5926ed:      	outl	%eax, %dx
  5926ee:      	<unknown>
  5926f1:      	stc
  5926f2:      	<unknown>
  5926f5:      	addl	%eax, %ecx
  5926f7:      	popl	%eax
  5926f8:      	addb	%cl, 0x170058c8
  5926fe:      	enter	$0x58, $0x21
  592702:      	enter	$0x58, $0x16
  592706:      	sbbb	(%ecx), %bl
  592709:      	pushl	%ss
  59270a:      	sbbb	(%ecx), %bl
  59270d:      	pushl	%ss
  59270e:      	sbbb	(%ecx), %bl
  592711:      	pushl	%ss
  592712:      	sbbb	(%ecx), %bl
  592715:      	pushl	%ss
  592716:      	sbbb	(%ecx), %bl
  592719:      	pushl	%ss
  59271a:      	sbbb	(%ecx), %bl
  59271d:      	pushl	%ss
  59271e:      	sbbb	(%ecx), %bl
  592721:      	subl	%eax, %ecx
  592723:      	popl	%eax
  592724:      	addb	%dl, (%esi)
  592726:      	sbbb	(%ecx), %bl
  592729:      	xorl	$0x3f0058c8, %eax       # imm = 0x3F0058C8
  59272e:      	enter	$0x58, $0x49
  592732:      	enter	$0x58, $0x53
  592736:      	enter	$0x58, $0x5d
  59273a:      	enter	$0x58, $-0x3e
  59273e:      	movl	%ebx, (%eax)
  592741:      	jno	0x59270b <.text+0x19170b>
  592743:      	popl	%eax
  592744:      	addb	%bh, -0x38(%ebx)
  592747:      	popl	%eax
  592748:      	addb	%dl, (%esi)
  59274a:      	sbbb	(%ecx), %bl
  59274d:      	pushl	%ss
  59274e:      	sbbb	(%ecx), %bl
  592751:      	pushl	%ss
  592752:      	sbbb	(%ecx), %bl
  592755:      	pushl	%ss
  592756:      	sbbb	(%ecx), %bl
  592759:      	pushl	%ss
  59275a:      	sbbb	(%ecx), %bl
  59275d:      	pushl	%ss
  59275e:      	sbbb	(%ecx), %bl
  592761:      	pushl	%ss
  592762:      	sbbb	(%ecx), %bl
  592765:      	pushl	%ss
  592766:      	sbbb	(%ecx), %bl
  592769:      	pushl	%ss
  59276a:      	sbbb	(%ecx), %bl
  59276d:      	pushl	%ss
  59276e:      	sbbb	(%ecx), %bl
  592771:      	testl	%ecx, %eax
  592773:      	popl	%eax
  592774:      	addb	%cl, -0x66ffa738(%edi)
  59277a:      	enter	$0x58, $-0x5d
  59277e:      	enter	$0x58, $-0x53
  592782:      	enter	$0x58, $-0x49
  592786:      	enter	$0x58, $-0x3f
  59278a:      	enter	$0x58, $-0x35
  59278e:      	enter	$0x58, $-0x2b
  592792:      	enter	$0x58, $-0x21
  592796:      	enter	$0x58, $-0x17
  59279a:      	enter	$0x58, $-0xd
  59279e:      	enter	$0x58, $-0x3
  5927a2:      	enter	$0x58, $0x7
  5927a6:      	leave
  5927a7:      	popl	%eax
  5927a8:      	addb	%dl, (%ecx)
  5927aa:      	leave
  5927ab:      	popl	%eax
  5927ac:      	addb	%dl, (%esi)
  5927ae:      	sbbb	(%ecx), %bl
  5927b1:      	pushl	%ss
  5927b2:      	sbbb	(%ecx), %bl
  5927b5:      	sbbl	%ecx, %ecx
  5927b7:      	popl	%eax
  5927b8:      	addb	%ah, 0x2f0058c9
  5927be:      	leave
  5927bf:      	popl	%eax
  5927c0:      	addb	%bh, (%ecx)
  5927c2:      	leave
  5927c3:      	popl	%eax
  5927c4:      	addb	%al, -0x37(%ebx)
  5927c7:      	popl	%eax
  5927c8:      	addb	%cl, -0x37(%ebp)
  5927cb:      	popl	%eax
  5927cc:      	addb	%dl, -0x37(%edi)
  5927cf:      	popl	%eax
  5927d0:      	addb	%ah, -0x37(%ecx)
  5927d3:      	popl	%eax
  5927d4:      	addb	%ch, -0x37(%ebx)
  5927d7:      	popl	%eax
  5927d8:      	addb	%dh, -0x37(%ebp)
  5927db:      	popl	%eax
  5927dc:      	addb	%bh, -0x37(%edi)
  5927df:      	popl	%eax
  5927e0:      	addb	%cl, -0x6cffa737(%ecx)
  5927e6:      	leave
  5927e7:      	popl	%eax
  5927e8:      	addb	%bl, -0x58ffa737(%ebp)
  5927ee:      	leave
  5927ef:      	popl	%eax
  5927f0:      	addb	%dh, -0x44ffa737(%ecx)
  5927f6:      	leave
  5927f7:      	popl	%eax
  5927f8:      	addb	%al, %ch
  5927fa:      	leave
  5927fb:      	popl	%eax
  5927fc:      	addb	%cl, %bh
  5927fe:      	leave
  5927ff:      	popl	%eax
  592800:      	addb	%bl, %cl
  592802:      	leave
  592803:      	popl	%eax
  592804:      	addb	%ah, %bl
  592806:      	leave
  592807:      	popl	%eax
  592808:      	addb	%ch, %ch
  59280a:      	leave
  59280b:      	popl	%eax
  59280c:      	addb	%dh, %bh
  59280e:      	leave
  59280f:      	popl	%eax
  592810:      	addb	%al, (%ecx)
  592812:      	lretl	$0x58
  592815:      	orl	%edx, %ecx
  592817:      	popl	%eax
  592818:      	addb	%dl, 0x1f0058ca
  59281e:      	lretl	$0x58
  592821:      	subl	%ecx, %edx
  592823:      	popl	%eax
  592824:      	addb	%dh, (%ebx)
  592826:      	lretl	$0x58
  592829:      	cmpl	$0x470058ca, %eax       # imm = 0x470058CA
  59282e:      	lretl	$0x58
  592831:      	pushl	%ecx
  592832:      	lretl	$0x58
  592835:      	popl	%ebx
  592836:      	lretl	$0x58
  592839:      	lretl	$0x58
  59283d:      	outsl	(%esi), %dx
  59283e:      	lretl	$0x58
  592841:      	jns	0x59280d <.text+0x19180d>
  592843:      	popl	%eax
  592844:      	addb	%al, -0x72ffa736(%ebx)
  59284a:      	lretl	$0x58
  59284d:      	xchgl	%edi, %eax
  59284e:      	lretl	$0x58
  592851:      	movl	0xb50058ca, %eax
  592856:      	lretl	$0x58
  592859:      	movl	$0xc90058ca, %edi       # imm = 0xC90058CA
  59285e:      	lretl	$0x58
  592861:      	rorl	%cl, %edx
  592863:      	popl	%eax
  592864:      	addb	%bl, %ch
  592866:      	lretl	$0x58
  592869:      	outl	%eax, $0xca
  59286b:      	popl	%eax
  59286c:      	addb	%dh, %cl
  59286e:      	lretl	$0x58
  592871:      	cmpl	$0x470058cb, %eax       # imm = 0x470058CB
  592876:      	lretl
  592877:      	popl	%eax
  592878:      	addb	%dl, -0x35(%ecx)
  59287b:      	popl	%eax
  59287c:      	addb	%bl, -0x35(%ebx)
  59287f:      	popl	%eax
  592880:      	addb	%ah, -0x35(%ebp)
  592883:      	popl	%eax
  592884:      	addb	%ch, -0x35(%edi)
  592887:      	popl	%eax
  592888:      	addb	%bh, -0x35(%ecx)
  59288b:      	popl	%eax
  59288c:      	addb	%al, -0x72ffa735(%ebx)
  592892:      	lretl
  592893:      	popl	%eax
  592894:      	addb	%dl, -0x5effa735(%edi)
  59289a:      	lretl
  59289b:      	popl	%eax
  59289c:      	addb	%ch, -0x4affa735(%ebx)
  5928a2:      	lretl
  5928a3:      	popl	%eax
  5928a4:      	addb	%bh, -0x36ffa735(%edi)
  5928aa:      	lretl
  5928ab:      	popl	%eax
  5928ac:      	addb	%dl, %bl
  5928ae:      	lretl
  5928af:      	popl	%eax
  5928b0:      	addb	%bl, %ch
  5928b2:      	lretl
  5928b3:      	popl	%eax
  5928b4:      	addb	%ah, %bh
  5928b6:      	lretl
  5928b7:      	popl	%eax
  5928b8:      	addb	%dh, %cl
  5928ba:      	lretl
  5928bb:      	popl	%eax
  5928bc:      	addb	%bh, %bl
  5928be:      	lretl
  5928bf:      	popl	%eax
  5928c0:      	addb	%bl, (%ecx)
  5928c2:      	int3
  5928c3:      	popl	%eax
  5928c4:      	addb	%ah, (%ebx)
  5928c6:      	int3
  5928c7:      	popl	%eax
  5928c8:      	addb	%ch, 0x370058cc
  5928ce:      	int3
  5928cf:      	popl	%eax
  5928d0:      	addb	%al, -0x34(%ecx)
  5928d3:      	popl	%eax
  5928d4:      	addb	%cl, -0x34(%ebx)
  5928d7:      	popl	%eax
  5928d8:      	addb	%dl, -0x34(%ebp)
  5928db:      	popl	%eax
  5928dc:      	addb	%bl, -0x34(%edi)
  5928df:      	popl	%eax
  5928e0:      	addb	%ch, -0x34(%ecx)
  5928e3:      	popl	%eax
  5928e4:      	addb	%dh, -0x34(%ebx)
  5928e7:      	popl	%eax
  5928e8:      	addb	%bh, -0x34(%ebp)
  5928eb:      	popl	%eax
  5928ec:      	addb	%al, -0x6effa734(%edi)
  5928f2:      	int3
  5928f3:      	popl	%eax
  5928f4:      	addb	%bl, -0x5affa734(%ebx)
  5928fa:      	int3
  5928fb:      	popl	%eax
  5928fc:      	addb	%ch, -0x46ffa734(%edi)
  592902:      	int3
  592903:      	popl	%eax
  592904:      	addb	%dl, (%esi)
  592906:      	sbbb	(%ecx), %bl
  592909:      	addb	%al, (%ecx)
  59290b:      	addb	(%ebx), %al
  59290d:      	addb	$0x2c, %al
  59290f:      	addl	$0x2c062c2c, %eax       # imm = 0x2C062C2C
  592914:      	subb	$0x7, %al
  592916:      	subb	$0x2c, %al
  592918:      	orb	%cl, (%ecx)
  59291a:      	subb	$0x2c, %al
  59291c:      	subb	$0x2c, %al
  59291e:      	subb	$0xa, %al
  592920:      	subb	$0xb, %al
  592922:      	orb	$0x2c, %al
  592924:      	subb	$0xd, %al
  592926:      	pushl	%cs
  592927:      	movups	(%ecx), %xmm2
  59292a:      	adcb	(%ebx), %dl
  59292c:      	adcb	$0x15, %al
  59292e:      	pushl	%ss
  59292f:      	popl	%ss
  592930:      	sbbb	%bl, (%ecx)
  592932:      	sbbb	(%esp,%ebp), %ch
  592935:      	sbbl	(%esp,%ebp), %ebx
  592938:      	sbbl	$0x21201f1e, %eax       # imm = 0x21201F1E
  59293d:      	andb	(%ebx,%eiz), %ch
  592940:      	subb	$0x24, %al
  592942:      	andl	$0x2c2c2c26, %eax       # imm = 0x2C2C2C26
  592947:      	subb	$0x2c, %al
  592949:      	subb	$0x2c, %al
  59294b:      	subb	$0x2c, %al
  59294d:      	subb	$0x2c, %al
  59294f:      	subb	$0x2c, %al
  592951:      	daa
  592952:      	subb	%ch, (%ecx)
  592954:      	subb	(%ebx), %ch
  592956:      	leal	(%ecx), %ecx
  592959:      	movb	$-0x32, %dl
  59295b:      	popl	%eax
  59295c:      	addb	%ch, -0x61ffa732(%eax)
  592962:      	into
  592963:      	popl	%eax
  592964:      	addb	%al, %dh
  592966:      	into
  592967:      	popl	%eax
  592968:      	addb	%ah, %ch
  59296a:      	into
  59296b:      	popl	%eax
  59296c:      	addb	%ch, %bh
  59296e:      	into
  59296f:      	popl	%eax
  592970:      	addb	%bh, %cl
  592972:      	into
  592973:      	popl	%eax
  592974:      	addb	%al, (%ebx)
  592976:      	iretl
  592977:      	popl	%eax
  592978:      	addb	%cl, 0x170058cf
  59297e:      	iretl
  59297f:      	popl	%eax
  592980:      	addb	%ah, (%ecx)
  592982:      	iretl
  592983:      	popl	%eax
  592984:      	addb	%ch, (%ebx)
  592986:      	iretl
  592987:      	popl	%eax
  592988:      	addb	%dh, 0x3f0058cf
  59298e:      	iretl
  59298f:      	popl	%eax
  592990:      	addb	%ah, -0x31(%edi)
  592993:      	popl	%eax
  592994:      	addb	%dh, -0x31(%ecx)
  592997:      	popl	%eax
  592998:      	addb	%bh, -0x31(%ebx)
  59299b:      	popl	%eax
  59299c:      	addb	%al, -0x70ffa731(%ebp)
  5929a2:      	iretl
  5929a3:      	popl	%eax
  5929a4:      	addb	%bl, -0x5cffa731(%ecx)
  5929aa:      	iretl
  5929ab:      	popl	%eax
  5929ac:      	addb	%ch, -0x48ffa731(%ebp)
  5929b2:      	iretl
  5929b3:      	popl	%eax
  5929b4:      	addb	%al, %cl
  5929b6:      	iretl
  5929b7:      	popl	%eax
  5929b8:      	addb	%cl, %bl
  5929ba:      	iretl
  5929bb:      	popl	%eax
  5929bc:      	addb	%dl, %ch
  5929be:      	iretl
  5929bf:      	popl	%eax
  5929c0:      	addb	%dl, (%esi)
  5929c2:      	sbbb	(%ecx), %bl
  5929c5:      	addb	%al, (%ecx)
  5929c7:      	sbbb	(%edx), %al
  5929c9:      	addl	0x9080706(,%eax), %eax
  5929d0:      	orb	(%ebx), %cl
  5929d2:      	orb	$0xd, %al
  5929d4:      	pushl	%cs
  5929d5:      	movups	(%ecx), %xmm2
  5929d8:      	adcb	(%ebx), %dl
  5929da:      	adcb	$0x15, %al
  5929dc:      	pushl	%ss
  5929dd:      	popl	%ss
  5929de:      	sbbb	(%edx), %bl
  5929e0:      	sbbb	(%edx), %bl
  5929e2:      	sbbb	(%edx), %bl
  5929e4:      	sbbb	(%edx), %bl
  5929e6:      	sbbb	(%edx), %bl
  5929e8:      	sbbb	(%edx), %bl
  5929ea:      	sbbb	(%edx), %bl
  5929ec:      	sbbb	(%edx), %bl
  5929ee:      	sbbb	(%edx), %bl
  5929f0:      	sbbb	(%edx), %bl
  5929f2:      	sbbb	(%edx), %bl
  5929f4:      	sbbb	(%edx), %bl
  5929f6:      	sbbb	(%edx), %bl
  5929f8:      	sbbb	(%edx), %bl
  5929fa:      	sbbb	%bl, (%ecx)
  5929fc:      	nop
  5929fd:      	jmp	0xf35982d1
  592a02:      	iretl
  592a03:      	popl	%eax
  592a04:      	addb	%bh, %ch
  592a06:      	iretl
  592a07:      	popl	%eax
  592a08:      	addb	%al, (%edi)
  592a0a:      	rcrb	(%eax)
  592a0d:      	adcl	%edx, %eax
  592a0f:      	popl	%eax
  592a10:      	addb	%bl, (%ebx)
  592a12:      	rcrb	(%eax)
  592a15:      	andl	$0x2f0058d0, %eax       # imm = 0x2F0058D0
  592a1a:      	rcrb	(%eax)
  592a1d:      	cmpl	%edx, %eax
  592a1f:      	popl	%eax
  592a20:      	addb	%al, -0x30(%ebx)
  592a23:      	popl	%eax
  592a24:      	addb	%cl, -0x30(%ebp)
  592a27:      	popl	%eax
  592a28:      	addb	%dl, -0x30(%edi)
  592a2b:      	popl	%eax
  592a2c:      	addb	%ah, -0x30(%ecx)
  592a2f:      	popl	%eax
  592a30:      	addb	%ch, -0x30(%ebx)
  592a33:      	popl	%eax
  592a34:      	addb	%dh, -0x30(%ebp)
  592a37:      	popl	%eax
  592a38:      	addb	%bh, -0x30(%edi)
  592a3b:      	popl	%eax
  592a3c:      	addb	%cl, -0x6cffa730(%ecx)
  592a42:      	rcrb	(%eax)
  592a45:      	popfl
  592a46:      	rcrb	(%eax)
  592a49:      	cmpsl	%es:(%edi), (%esi)
  592a4a:      	rcrb	(%eax)
  592a4d:      	movb	$-0x30, %cl
  592a4f:      	popl	%eax
  592a50:      	addb	%bh, -0x3affa730(%ebx)
  592a56:      	rcrb	(%eax)
  592a59:      	iretl
  592a5a:      	rcrb	(%eax)
  592a5d:      	fnop
  592a5f:      	popl	%eax
  592a60:      	addb	%ah, %bl
  592a62:      	rcrb	(%eax)
  592a65:      	inl	%dx, %eax
  592a66:      	rcrb	(%eax)
  592a69:      	notl	%eax
  592a6b:      	popl	%eax
  592a6c:      	addb	%al, (%ecx)
  592a6e:      	rcrl	(%eax)
  592a71:      	orl	%ecx, %edx
  592a73:      	popl	%eax
  592a74:      	addb	%bh, -0x2e(%ebp)
  592a77:      	popl	%eax
  592a78:      	addb	%dl, (%esi)
  592a7a:      	sbbb	(%ecx), %bl
  592a7d:      	pushl	%ss
  592a7e:      	sbbb	(%ecx), %bl
  592a81:      	pushl	%ss
  592a82:      	sbbb	(%ecx), %bl
  592a85:      	pushl	%ss
  592a86:      	sbbb	(%ecx), %bl
  592a89:      	pushl	%ss
  592a8a:      	sbbb	(%ecx), %bl
  592a8d:      	pushl	%ss
  592a8e:      	sbbb	(%ecx), %bl
  592a91:      	pushl	%ss
  592a92:      	sbbb	(%ecx), %bl
  592a95:      	pushl	%ss
  592a96:      	sbbb	(%ecx), %bl
  592a99:      	pushl	%ss
  592a9a:      	sbbb	(%ecx), %bl
  592a9d:      	pushl	%ss
  592a9e:      	sbbb	(%ecx), %bl
  592aa1:      	pushl	%ss
  592aa2:      	sbbb	(%ecx), %bl
  592aa5:      	pushl	%ss
  592aa6:      	sbbb	(%ecx), %bl
  592aa9:      	pushl	%ss
  592aaa:      	sbbb	(%ecx), %bl
  592aad:      	pushl	%ss
  592aae:      	sbbb	(%ecx), %bl
  592ab1:      	pushl	%ss
  592ab2:      	sbbb	(%ecx), %bl
  592ab5:      	adcl	$0x1f0058d1, %eax       # imm = 0x1F0058D1
  592aba:      	rcrl	(%eax)
  592abd:      	subl	%edx, %ecx
  592abf:      	popl	%eax
  592ac0:      	addb	%dh, (%ebx)
  592ac2:      	rcrl	(%eax)
  592ac5:      	cmpl	$0x470058d1, %eax       # imm = 0x470058D1
  592aca:      	rcrl	(%eax)
  592acd:      	pushl	%ecx
  592ace:      	rcrl	(%eax)
  592ad1:      	popl	%ebx
  592ad2:      	rcrl	(%eax)
  592ad5:      	rcrl	%gs:(%eax)
  592ad9:      	outsl	(%esi), %dx
  592ada:      	rcrl	(%eax)
  592add:      	jns	0x592ab0 <.text+0x191ab0>
  592adf:      	popl	%eax
  592ae0:      	addb	%al, -0x72ffa72f(%ebx)
  592ae6:      	rcrl	(%eax)
  592ae9:      	xchgl	%edi, %eax
  592aea:      	rcrl	(%eax)
  592aed:      	movl	0xab0058d1, %eax
  592af2:      	rcrl	(%eax)
  592af5:      	movb	$-0x2f, %ch
  592af7:      	popl	%eax
  592af8:      	addb	%bh, -0x36ffa72f(%edi)
  592afe:      	rcrl	(%eax)
  592b01:      	rcll	%cl, %ecx
  592b03:      	popl	%eax
  592b04:      	addb	%bl, %ch
  592b06:      	rcrl	(%eax)
  592b09:      	outl	%eax, $0xd1
  592b0b:      	popl	%eax
  592b0c:      	addb	%bh, %bl
  592b0e:      	rcrl	(%eax)
  592b11:      	addl	$0xf0058d2, %eax        # imm = 0xF0058D2
  592b16:      	rcrb	%cl, (%eax)
  592b19:      	sbbl	%edx, %edx
  592b1b:      	popl	%eax
  592b1c:      	addb	%ah, (%ebx)
  592b1e:      	rcrb	%cl, (%eax)
  592b21:      	subl	$0x370058d2, %eax       # imm = 0x370058D2
  592b26:      	rcrb	%cl, (%eax)
  592b29:      	incl	%ecx
  592b2a:      	rcrb	%cl, (%eax)
  592b2d:      	decl	%ebx
  592b2e:      	rcrb	%cl, (%eax)
  592b31:      	pushl	%ebp
  592b32:      	rcrb	%cl, (%eax)
  592b35:      	pushl	%ss
  592b36:      	sbbb	(%ecx), %bl
  592b39:      	pushl	%ss
  592b3a:      	sbbb	(%ecx), %bl
  592b3d:      	pushl	%ss
  592b3e:      	sbbb	(%ecx), %bl
  592b41:      	pushl	%ss
  592b42:      	sbbb	(%ecx), %bl
  592b45:      	pushl	%ss
  592b46:      	sbbb	(%ecx), %bl
  592b49:      	pushl	%ss
  592b4a:      	sbbb	(%ecx), %bl
  592b4d:      	pushl	%ss
  592b4e:      	sbbb	(%ecx), %bl
  592b51:      	popl	%edi
  592b52:      	rcrb	%cl, (%eax)
  592b55:      	imull	$0xd2730058, %edx, %edx # imm = 0xD2730058
  592b5b:      	popl	%eax
  592b5c:      	addb	%dl, (%esi)
  592b5e:      	sbbb	(%ecx), %bl
  592b61:      	pushl	%ss
  592b62:      	sbbb	(%ecx), %bl
  592b65:      	pushl	%ss
  592b66:      	sbbb	(%ecx), %bl
  592b69:      	pushl	%ss
  592b6a:      	sbbb	(%ecx), %bl
  592b6d:      	pushl	%ss
  592b6e:      	sbbb	(%ecx), %bl
  592b71:      	pushl	%ss
  592b72:      	sbbb	(%ecx), %bl
  592b75:      	pushl	%ss
  592b76:      	sbbb	(%ecx), %bl
  592b79:      	xchgl	%edx, %edx
  592b7b:      	popl	%eax
  592b7c:      	addb	%ch, -0x4dffa72e(%eax)
  592b82:      	rcrb	%cl, (%eax)
  592b85:      	movl	$0xc60058d2, %esp       # imm = 0xC60058D2
  592b8a:      	rcrb	%cl, (%eax)
  592b8d:      	rclb	%dl
  592b8f:      	popl	%eax
  592b90:      	addb	%bl, %dl
  592b92:      	rcrb	%cl, (%eax)
  592b95:      	inb	$0xd2, %al
  592b97:      	popl	%eax
  592b98:      	addb	%ch, %dh
  592b9a:      	rcrb	%cl, (%eax)
  592b9d:      	clc
  592b9e:      	rcrb	%cl, (%eax)
  592ba1:      	addb	%bl, %dl
  592ba3:      	popl	%eax
  592ba4:      	addb	%cl, (%ebx,%edx,8)
  592ba7:      	popl	%eax
  592ba8:      	addb	%dl, (%esi)
  592baa:      	rcrl	%cl, (%eax)
  592bad:      	andb	%dl, %bl
  592baf:      	popl	%eax
  592bb0:      	addb	%ch, (%edx)
  592bb2:      	rcrl	%cl, (%eax)
  592bb5:      	xorb	$-0x2d, %al
  592bb7:      	popl	%eax
  592bb8:      	addb	%bh, (%esi)
  592bba:      	rcrl	%cl, (%eax)
  592bbd:      	decl	%eax
  592bbe:      	rcrl	%cl, (%eax)
  592bc1:      	pushl	%edx
  592bc2:      	rcrl	%cl, (%eax)
  592bc5:      	popl	%esp
  592bc6:      	rcrl	%cl, (%eax)
  592bc9:      	rcrw	%cl, (%eax)
  592bcd:      	jo	0x592ba2 <.text+0x191ba2>
  592bcf:      	popl	%eax
  592bd0:      	addb	%bh, -0x2d(%edx)
  592bd3:      	popl	%eax
  592bd4:      	addb	%al, 0x1a160058(%ebx,%edx,8)
  592bdb:      	popl	%ecx
  592bdc:      	addb	%cl, -0x67ffa72d(%esi)
  592be2:      	rcrl	%cl, (%eax)
  592be5:      	movb	%al, 0xac0058d3
  592bea:      	rcrl	%cl, (%eax)
  592bed:      	movb	$-0x2d, %dh
  592bef:      	popl	%eax
  592bf0:      	addb	%al, %al
  592bf2:      	rcrl	%cl, (%eax)
  592bf5:      	decl	%eax
  592bf6:      	fstpl	(%eax)
  592bf9:      	pushl	%ss
  592bfa:      	sbbb	(%ecx), %bl
  592bfd:      	pushl	%ss
  592bfe:      	sbbb	(%ecx), %bl
  592c01:      	pushl	%ss
  592c02:      	sbbb	(%ecx), %bl
  592c05:      	pushl	%ss
  592c06:      	sbbb	(%ecx), %bl
  592c09:      	pushl	%ss
  592c0a:      	sbbb	(%ecx), %bl
  592c0d:      	pushl	%ss
  592c0e:      	sbbb	(%ecx), %bl
  592c11:      	pushl	%ss
  592c12:      	sbbb	(%ecx), %bl
  592c15:      	pushl	%ss
  592c16:      	sbbb	(%ecx), %bl
  592c19:      	pushl	%ss
  592c1a:      	sbbb	(%ecx), %bl
  592c1d:      	pushl	%ss
  592c1e:      	sbbb	(%ecx), %bl
  592c21:      	pushl	%ss
  592c22:      	sbbb	(%ecx), %bl
  592c25:      	pushl	%ss
  592c26:      	sbbb	(%ecx), %bl
  592c29:      	pushl	%ss
  592c2a:      	sbbb	(%ecx), %bl
  592c2d:      	pushl	%ss
  592c2e:      	sbbb	(%ecx), %bl
  592c31:      	pushl	%ss
  592c32:      	sbbb	(%ecx), %bl
  592c35:      	pushl	%ss
  592c36:      	sbbb	(%ecx), %bl
  592c39:      	pushl	%ss
  592c3a:      	sbbb	(%ecx), %bl
  592c3d:      	pushl	%ss
  592c3e:      	sbbb	(%ecx), %bl
  592c41:      	lretl	$0x58d3                 # imm = 0x58D3
  592c44:      	addb	%dl, %ah
  592c46:      	rcrl	%cl, (%eax)
  592c49:      	<unknown>
  592c4b:      	popl	%eax
  592c4c:      	addb	%ch, %al
  592c4e:      	rcrl	%cl, (%eax)
  592c51:      	repne		rcrl	%cl, (%eax)
  592c55:      	cld
  592c56:      	rcrl	%cl, (%eax)
  592c59:      	pushl	%es
  592c5a:      	aam	$0x58
  592c5c:      	addb	%dl, (%eax)
  592c5e:      	aam	$0x58
  592c60:      	addb	%bl, (%edx)
  592c62:      	aam	$0x58
  592c64:      	addb	%ah, (%esp,%edx,8)
  592c67:      	popl	%eax
  592c68:      	addb	%ch, (%esi)
  592c6a:      	aam	$0x58
  592c6c:      	addb	%bh, (%eax)
  592c6e:      	aam	$0x58
  592c70:      	addb	%al, -0x2c(%edx)
  592c73:      	popl	%eax
  592c74:      	addb	%cl, 0x58(%esp,%edx,8)
  592c78:      	addb	%dl, -0x2c(%esi)
  592c7b:      	popl	%eax
  592c7c:      	addb	%ah, -0x2c(%eax)
  592c7f:      	popl	%eax
  592c80:      	addb	%ch, -0x2c(%edx)
  592c83:      	popl	%eax
  592c84:      	addb	%dh, 0x58(%esp,%edx,8)
  592c88:      	addb	%bh, -0x2c(%esi)
  592c8b:      	popl	%eax
  592c8c:      	addb	%cl, -0x6dffa72c(%eax)
  592c92:      	aam	$0x58
  592c94:      	addb	%bl, -0x2b59ffa8(%esp,%edx,8)
  592c9b:      	popl	%eax
  592c9c:      	addb	%dh, -0x45ffa72c(%eax)
  592ca2:      	aam	$0x58
  592ca4:      	addb	%al, %ah
  592ca6:      	aam	$0x58
  592ca8:      	addb	%cl, %dh
  592caa:      	aam	$0x58
  592cac:      	addb	%bl, %al
  592cae:      	aam	$0x58
  592cb0:      	addb	%ah, %dl
  592cb2:      	aam	$0x58
  592cb4:      	addb	%ch, %ah
  592cb6:      	aam	$0x58
  592cb8:      	addb	%dh, %dh
  592cba:      	aam	$0x58
  592cbc:      	addb	%al, (%eax)
  592cbe:      	aad	$0x58
  592cc0:      	addb	%cl, (%edx)
  592cc2:      	aad	$0x58
  592cc4:      	addb	%dl, -0x2ae1ffa8(,%edx,8)
  592ccb:      	popl	%eax
  592ccc:      	addb	%ch, (%eax)
  592cce:      	aad	$0x58
  592cd0:      	addb	%dh, (%edx)
  592cd2:      	aad	$0x58
  592cd4:      	addb	%bh, -0x2ab9ffa8(,%edx,8)
  592cdb:      	popl	%eax
  592cdc:      	addb	%dl, -0x2b(%eax)
  592cdf:      	popl	%eax
  592ce0:      	addb	%bl, -0x2b(%edx)
  592ce3:      	popl	%eax
  592ce4:      	addb	%ah, 0x58(%ebp,%edx,8)
  592ce8:      	addb	%ch, -0x2b(%esi)
  592ceb:      	popl	%eax
  592cec:      	addb	%bh, -0x2b(%eax)
  592cef:      	popl	%eax
  592cf0:      	addb	%al, -0x73ffa72b(%edx)
  592cf6:      	aad	$0x58
  592cf8:      	addb	%dl, -0x5fffa72b(%esi)
  592cfe:      	aad	$0x58
  592d00:      	addb	%ch, -0x4bffa72b(%edx)
  592d06:      	aad	$0x58
  592d08:      	addb	%bh, 0x520058d5(%esi)
  592d0e:      	fstpl	(%eax)
  592d11:      	popl	%esp
  592d12:      	fstpl	(%eax)
  592d15:      	fstpl	(%eax)
  592d19:      	jo	0x592cf8 <.text+0x191cf8>
  592d1b:      	popl	%eax
  592d1c:      	addb	%bh, -0x23(%edx)
  592d1f:      	popl	%eax
  592d20:      	addb	%al, -0x2271ffa8(%ebp,%ebx,8)
  592d27:      	popl	%eax
  592d28:      	addb	%bl, -0x5dffa723(%eax)
  592d2e:      	fstpl	(%eax)
  592d31:      	lodsb	(%esi), %al
  592d32:      	fstpl	(%eax)
  592d35:      	movb	$-0x23, %dh
  592d37:      	popl	%eax
  592d38:      	addb	%al, %al
  592d3a:      	fstpl	(%eax)
  592d3d:      	lretl	$0x58dd                 # imm = 0x58DD
  592d40:      	addb	%dl, %ah
  592d42:      	fstpl	(%eax)
  592d45:      	<unknown>
  592d47:      	popl	%eax
  592d48:      	addb	%dl, (%esi)
  592d4a:      	sbbb	(%ecx), %bl
  592d4d:      	pushl	%ss
  592d4e:      	sbbb	(%ecx), %bl
  592d51:      	pushl	%ss
  592d52:      	sbbb	(%ecx), %bl
  592d55:      	pushl	%ss
  592d56:      	sbbb	(%ecx), %bl
  592d59:      	pushl	%ss
  592d5a:      	sbbb	(%ecx), %bl
  592d5d:      	calll	0x1659863f
  592d62:      	sbbb	(%ecx), %bl
  592d65:      	repne		fstpl	(%eax)
  592d69:      	cld
  592d6a:      	fstpl	(%eax)
  592d6d:      	pushl	%es
  592d6e:      	ficomps	(%eax)
  592d71:      	adcb	%bl, %dh
  592d73:      	popl	%eax
  592d74:      	addb	%dl, (%esi)
  592d76:      	sbbb	(%ecx), %bl
  592d79:      	pushl	%ss
  592d7a:      	sbbb	(%ecx), %bl
  592d7d:      	pushl	%ss
  592d7e:      	sbbb	(%ecx), %bl
  592d81:      	pushl	%ss
  592d82:      	sbbb	(%ecx), %bl
  592d85:      	pushl	%ss
  592d86:      	sbbb	(%ecx), %bl
  592d89:      	pushl	%ss
  592d8a:      	sbbb	(%ecx), %bl
  592d8d:      	pushl	%ss
  592d8e:      	sbbb	(%ecx), %bl
  592d91:      	pushl	%ss
  592d92:      	sbbb	(%ecx), %bl
  592d95:      	pushl	%ss
  592d96:      	sbbb	(%ecx), %bl
  592d99:      	pushl	%ss
  592d9a:      	sbbb	(%ecx), %bl
  592d9d:      	pushl	%ss
  592d9e:      	sbbb	(%ecx), %bl
  592da1:      	pushl	%ss
  592da2:      	sbbb	(%ecx), %bl
  592da5:      	pushl	%ss
  592da6:      	sbbb	(%ecx), %bl
  592da9:      	pushl	%ss
  592daa:      	sbbb	(%ecx), %bl
  592dad:      	pushl	%ss
  592dae:      	sbbb	(%ecx), %bl
  592db1:      	pushl	%ss
  592db2:      	sbbb	(%ecx), %bl
  592db5:      	pushl	%ss
  592db6:      	sbbb	(%ecx), %bl
  592db9:      	pushl	%ss
  592dba:      	sbbb	(%ecx), %bl
  592dbd:      	pushl	%ss
  592dbe:      	sbbb	(%ecx), %bl
  592dc1:      	pushl	%ss
  592dc2:      	sbbb	(%ecx), %bl
  592dc5:      	pushl	%ss
  592dc6:      	sbbb	(%ecx), %bl
  592dc9:      	pushl	%ss
  592dca:      	sbbb	(%ecx), %bl
  592dcd:      	pushl	%ss
  592dce:      	sbbb	(%ecx), %bl
  592dd1:      	enter	$0x58d5, $0x0           # imm = 0x58D5
  592dd5:      	rclb	%cl, %ch
  592dd7:      	popl	%eax
  592dd8:      	addb	%bl, %ah
  592dda:      	aad	$0x58
  592ddc:      	addb	%ah, %dh
  592dde:      	aad	$0x58
  592de0:      	addb	%dh, %al
  592de2:      	aad	$0x58
  592de4:      	addb	%bh, %dl
  592de6:      	aad	$0x58
  592de8:      	addb	%al, (%esi,%edx,8)
  592deb:      	popl	%eax
  592dec:      	addb	%cl, (%esi)
  592dee:      	salc
  592def:      	popl	%eax
  592df0:      	addb	%bl, (%eax)
  592df2:      	salc
  592df3:      	popl	%eax
  592df4:      	addb	%ah, (%edx)
  592df6:      	salc
  592df7:      	popl	%eax
  592df8:      	addb	%ch, (%esi,%edx,8)
  592dfb:      	popl	%eax
  592dfc:      	addb	%dh, (%esi)
  592dfe:      	salc
  592dff:      	popl	%eax
  592e00:      	addb	%al, -0x2a(%eax)
  592e03:      	popl	%eax
  592e04:      	addb	%cl, -0x2a(%edx)
  592e07:      	popl	%eax
  592e08:      	addb	%dl, 0x58(%esi,%edx,8)
  592e0c:      	addb	%bl, -0x2a(%esi)
  592e0f:      	popl	%eax
  592e10:      	addb	%ch, -0x2a(%eax)
  592e13:      	popl	%eax
  592e14:      	addb	%dh, -0x2a(%edx)
  592e17:      	popl	%eax
  592e18:      	addb	%bh, 0x58(%esi,%edx,8)
  592e1c:      	addb	%al, -0x6fffa72a(%esi)
  592e22:      	salc
  592e23:      	popl	%eax
  592e24:      	addb	%bl, -0x5bffa72a(%edx)
  592e2a:      	salc
  592e2b:      	popl	%eax
  592e2c:      	addb	%ch, -0x47ffa72a(%esi)
  592e32:      	salc
  592e33:      	popl	%eax
  592e34:      	addb	%al, %dl
  592e36:      	salc
  592e37:      	popl	%eax
  592e38:      	addb	%cl, %ah
  592e3a:      	salc
  592e3b:      	popl	%eax
  592e3c:      	addb	%dl, %dh
  592e3e:      	salc
  592e3f:      	popl	%eax
  592e40:      	addb	%ah, %al
  592e42:      	salc
  592e43:      	popl	%eax
  592e44:      	addb	%ch, %dl
  592e46:      	salc
  592e47:      	popl	%eax
  592e48:      	addb	%dh, %ah
  592e4a:      	salc
  592e4b:      	popl	%eax
  592e4c:      	addb	%bh, %dh
  592e4e:      	salc
  592e4f:      	popl	%eax
  592e50:      	addb	%cl, (%eax)
  592e52:      	xlatb
  592e53:      	popl	%eax
  592e54:      	addb	%dl, (%edx)
  592e56:      	xlatb
  592e57:      	popl	%eax
  592e58:      	addb	%bl, (%edi,%edx,8)
  592e5b:      	popl	%eax
  592e5c:      	addb	%ah, (%esi)
  592e5e:      	xlatb
  592e5f:      	popl	%eax
  592e60:      	addb	%dh, (%eax)
  592e62:      	xlatb
  592e63:      	popl	%eax
  592e64:      	addb	%bh, (%edx)
  592e66:      	xlatb
  592e67:      	popl	%eax
  592e68:      	addb	%al, 0x58(%edi,%edx,8)
  592e6c:      	addb	%dl, (%esi)
  592e6e:      	sbbb	(%ecx), %bl
  592e71:      	decl	%esi
  592e72:      	xlatb
  592e73:      	popl	%eax
  592e74:      	addb	%bl, -0x29(%eax)
  592e77:      	popl	%eax
  592e78:      	addb	%ah, -0x29(%edx)
  592e7b:      	popl	%eax
  592e7c:      	addb	%ch, 0x58(%edi,%edx,8)
  592e80:      	addb	%dh, -0x29(%esi)
  592e83:      	popl	%eax
  592e84:      	addb	%al, -0x75ffa729(%eax)
  592e8a:      	xlatb
  592e8b:      	popl	%eax
  592e8c:      	addb	%dl, -0x2861ffa8(%edi,%edx,8)
  592e93:      	popl	%eax
  592e94:      	addb	%ch, -0x4dffa729(%eax)
  592e9a:      	xlatb
  592e9b:      	popl	%eax
  592e9c:      	addb	%bh, -0x2839ffa8(%edi,%edx,8)
  592ea3:      	popl	%eax
  592ea4:      	addb	%dl, %al
  592ea6:      	xlatb
  592ea7:      	popl	%eax
  592ea8:      	addb	%bl, %dl
  592eaa:      	xlatb
  592eab:      	popl	%eax
  592eac:      	addb	%ah, %ah
  592eae:      	xlatb
  592eaf:      	popl	%eax
  592eb0:      	addb	%ch, %dh
  592eb2:      	xlatb
  592eb3:      	popl	%eax
  592eb4:      	addb	%bh, %al
  592eb6:      	xlatb
  592eb7:      	popl	%eax
  592eb8:      	addb	%al, (%edx)
  592eba:      	fcomps	(%eax)
  592ebd:      	orb	$-0x28, %al
  592ebf:      	popl	%eax
  592ec0:      	addb	%dl, (%esi)
  592ec2:      	fcomps	(%eax)
  592ec5:      	andb	%bl, %al
  592ec7:      	popl	%eax
  592ec8:      	addb	%ch, (%edx)
  592eca:      	fcomps	(%eax)
  592ecd:      	xorb	$-0x28, %al
  592ecf:      	popl	%eax
  592ed0:      	addb	%bh, (%esi)
  592ed2:      	fcomps	(%eax)
  592ed5:      	decl	%eax
  592ed6:      	fcomps	(%eax)
  592ed9:      	pushl	%edx
  592eda:      	fcomps	(%eax)
  592edd:      	popl	%esp
  592ede:      	fcomps	(%eax)
  592ee1:      	fcomps	(%eax)
  592ee5:      	jo	0x592ebf <.text+0x191ebf>
  592ee7:      	popl	%eax
  592ee8:      	addb	%bh, -0x28(%edx)
  592eeb:      	popl	%eax
  592eec:      	addb	%al, -0x2771ffa8(%eax,%ebx,8)
  592ef3:      	popl	%eax
  592ef4:      	addb	%bl, -0x5dffa728(%eax)
  592efa:      	fcomps	(%eax)
  592efd:      	lodsb	(%esi), %al
  592efe:      	fcomps	(%eax)
  592f01:      	movb	$-0x28, %dh
  592f03:      	popl	%eax
  592f04:      	addb	%al, %al
  592f06:      	fcomps	(%eax)
  592f09:      	lretl	$0x58d8                 # imm = 0x58D8
  592f0c:      	addb	%dl, %ah
  592f0e:      	fcomps	(%eax)
  592f11:      	<unknown>
  592f13:      	popl	%eax
  592f14:      	addb	%ch, %al
  592f16:      	fcomps	(%eax)
  592f19:      	repne		fcomps	(%eax)
  592f1d:      	cld
  592f1e:      	fcomps	(%eax)
  592f21:      	pushl	%es
  592f22:      	fstps	(%eax)
  592f25:      	adcb	%bl, %cl
  592f27:      	popl	%eax
  592f28:      	addb	%bl, (%edx)
  592f2a:      	fstps	(%eax)
  592f2d:      	andb	$-0x27, %al
  592f2f:      	popl	%eax
  592f30:      	addb	%ch, (%esi)
  592f32:      	fstps	(%eax)
  592f35:      	cmpb	%bl, %cl
  592f37:      	popl	%eax
  592f38:      	addb	%al, -0x27(%edx)
  592f3b:      	popl	%eax
  592f3c:      	addb	%cl, 0x58(%ecx,%ebx,8)
  592f40:      	addb	%dl, -0x27(%esi)
  592f43:      	popl	%eax
  592f44:      	addb	%ah, -0x27(%eax)
  592f47:      	popl	%eax
  592f48:      	addb	%ch, -0x27(%edx)
  592f4b:      	popl	%eax
  592f4c:      	addb	%dh, 0x58(%ecx,%ebx,8)
  592f50:      	addb	%bh, -0x27(%esi)
  592f53:      	popl	%eax
  592f54:      	addb	%cl, -0x6dffa727(%eax)
  592f5a:      	fstps	(%eax)
  592f5d:      	sbbb	%dh, %bl
  592f5f:      	popl	%eax
  592f60:      	addb	%bl, -0x2659ffa8(%ecx,%ebx,8)
  592f67:      	popl	%eax
  592f68:      	addb	%dh, -0x45ffa727(%eax)
  592f6e:      	fstps	(%eax)
  592f71:      	<unknown>
  592f74:      	addb	%cl, %dh
  592f76:      	fstps	(%eax)
  592f79:      	fcomp	%st(1)
  592f7b:      	popl	%eax
  592f7c:      	addb	%ah, %dl
  592f7e:      	fstps	(%eax)
  592f81:      	inb	%dx, %al
  592f82:      	fstps	(%eax)
  592f85:      	negb	%cl
  592f87:      	popl	%eax
  592f88:      	addb	%al, (%eax)
  592f8a:      	ficompl	(%eax)
  592f8d:      	orb	%dl, %bl
  592f8f:      	popl	%eax
  592f90:      	addb	%dl, (%edx,%ebx,8)
  592f93:      	popl	%eax
  592f94:      	addb	%bl, (%esi)
  592f96:      	ficompl	(%eax)
  592f99:      	subb	%bl, %dl
  592f9b:      	popl	%eax
  592f9c:      	addb	%dh, (%edx)
  592f9e:      	ficompl	(%eax)
  592fa1:      	cmpb	$-0x26, %al
  592fa3:      	popl	%eax
  592fa4:      	addb	%al, -0x26(%esi)
  592fa7:      	popl	%eax
  592fa8:      	addb	%dl, -0x26(%eax)
  592fab:      	popl	%eax
  592fac:      	addb	%bl, -0x26(%edx)
  592faf:      	popl	%eax
  592fb0:      	addb	%ah, 0x58(%edx,%ebx,8)
  592fb4:      	addb	%ch, -0x26(%esi)
  592fb7:      	popl	%eax
  592fb8:      	addb	%bh, -0x26(%eax)
  592fbb:      	popl	%eax
  592fbc:      	addb	%al, -0x73ffa726(%edx)
  592fc2:      	ficompl	(%eax)
  592fc5:      	xchgl	%esi, %eax
  592fc6:      	ficompl	(%eax)
  592fc9:      	movb	0xaa0058da, %al
  592fce:      	ficompl	(%eax)
  592fd1:      	movb	$-0x26, %ah
  592fd3:      	popl	%eax
  592fd4:      	addb	%bh, -0x37ffa726(%esi)
  592fda:      	ficompl	(%eax)
  592fdd:      	rcrb	%cl, %dl
  592fdf:      	popl	%eax
  592fe0:      	addb	%bl, %ah
  592fe2:      	ficompl	(%eax)
  592fe5:      	outb	%al, $0xda
  592fe7:      	popl	%eax
  592fe8:      	addb	%dh, %al
  592fea:      	ficompl	(%eax)
  592fed:      	cli
  592fee:      	ficompl	(%eax)
  592ff1:      	addb	$-0x25, %al
  592ff3:      	popl	%eax
  592ff4:      	addb	%cl, (%esi)
  592ff6:      	fistpl	(%eax)
  592ff9:      	sbbb	%bl, %bl
  592ffb:      	popl	%eax
  592ffc:      	addb	%ah, (%edx)
  592ffe:      	fistpl	(%eax)
  593001:      	subb	$-0x25, %al
  593003:      	popl	%eax
  593004:      	addb	%dh, (%esi)
  593006:      	fistpl	(%eax)
  593009:      	incl	%eax
  59300a:      	fistpl	(%eax)
  59300d:      	decl	%edx
  59300e:      	fistpl	(%eax)
  593011:      	pushl	%esp
  593012:      	fistpl	(%eax)
  593015:      	popl	%esi
  593016:      	fistpl	(%eax)
  593019:      	pushl	$0x720058db             # imm = 0x720058DB
  59301e:      	fistpl	(%eax)
  593021:      	jl	0x592ffe <.text+0x191ffe>
  593023:      	popl	%eax
  593024:      	addb	%al, -0x6fffa725(%esi)
  59302a:      	fistpl	(%eax)
  59302d:      	lcalll	$0x58db, $0xa40058db    # imm = 0x58DB
                                                # imm = 0xA40058DB
  593034:      	addb	%ch, -0x47ffa725(%esi)
  59303a:      	fistpl	(%eax)
  59303d:      	retl	$0x58db                 # imm = 0x58DB
  593040:      	addb	%cl, %ah
  593042:      	fistpl	(%eax)
  593045:      	salc
  593046:      	fistpl	(%eax)
  593049:      	loopne	0x593026 <.text+0x192026>
  59304b:      	popl	%eax
  59304c:      	addb	%ch, %dl
  59304e:      	fistpl	(%eax)
  593051:      	hlt
  593052:      	fistpl	(%eax)
  593055:      	<unknown>
  593057:      	popl	%eax
  593058:      	addb	%dl, (%esi)
  59305a:      	sbbb	(%ecx), %bl
  59305d:      	pushl	%ss
  59305e:      	sbbb	(%ecx), %bl
  593061:      	pushl	%ss
  593062:      	sbbb	(%ecx), %bl
  593065:      	pushl	%ss
  593066:      	sbbb	(%ecx), %bl
  593069:      	pushl	%ss
  59306a:      	sbbb	(%ecx), %bl
  59306d:      	pushl	%ss
  59306e:      	sbbb	(%ecx), %bl
  593071:      	pushl	%ss
  593072:      	sbbb	(%ecx), %bl
  593075:      	pushl	%ss
  593076:      	sbbb	(%ecx), %bl
  593079:      	pushl	%ss
  59307a:      	sbbb	(%ecx), %bl
  59307d:      	pushl	%ss
  59307e:      	sbbb	(%ecx), %bl
  593081:      	pushl	%ss
  593082:      	sbbb	(%ecx), %bl
  593085:      	pushl	%ss
  593086:      	sbbb	(%ecx), %bl
  593089:      	pushl	%ss
  59308a:      	sbbb	(%ecx), %bl
  59308d:      	pushl	%ss
  59308e:      	sbbb	(%ecx), %bl
  593091:      	pushl	%ss
  593092:      	sbbb	(%ecx), %bl
  593095:      	pushl	%ss
  593096:      	sbbb	(%ecx), %bl
  593099:      	pushl	%ss
  59309a:      	sbbb	(%ecx), %bl
  59309d:      	pushl	%ss
  59309e:      	sbbb	(%ecx), %bl
  5930a1:      	pushl	%ss
  5930a2:      	sbbb	(%ecx), %bl
  5930a5:      	pushl	%ss
  5930a6:      	sbbb	(%ecx), %bl
  5930a9:      	pushl	%ss
  5930aa:      	sbbb	(%ecx), %bl
  5930ad:      	pushl	%ss
  5930ae:      	sbbb	(%ecx), %bl
  5930b1:      	pushl	%ss
  5930b2:      	sbbb	(%ecx), %bl
  5930b5:      	pushl	%ss
  5930b6:      	sbbb	(%ecx), %bl
  5930b9:      	pushl	%ss
  5930ba:      	sbbb	(%ecx), %bl
  5930bd:      	pushl	%ss
  5930be:      	sbbb	(%ecx), %bl
  5930c1:      	pushl	%ss
  5930c2:      	sbbb	(%ecx), %bl
  5930c5:      	pushl	%ss
  5930c6:      	sbbb	(%ecx), %bl
  5930c9:      	pushl	%ss
  5930ca:      	sbbb	(%ecx), %bl
  5930cd:      	pushl	%ss
  5930ce:      	sbbb	(%ecx), %bl
  5930d1:      	pushl	%ss
  5930d2:      	sbbb	(%ecx), %bl
  5930d5:      	pushl	%ss
  5930d6:      	sbbb	(%ecx), %bl
  5930d9:      	pushl	%ss
  5930da:      	sbbb	(%ecx), %bl
  5930dd:      	pushl	%ss
  5930de:      	sbbb	(%ecx), %bl
  5930e1:      	pushl	%ss
  5930e2:      	sbbb	(%ecx), %bl
  5930e5:      	pushl	%ss
  5930e6:      	sbbb	(%ecx), %bl
  5930e9:      	pushl	%ss
  5930ea:      	sbbb	(%ecx), %bl
  5930ed:      	pushl	%ss
  5930ee:      	sbbb	(%ecx), %bl
  5930f1:      	orb	%bl, %ah
  5930f3:      	popl	%eax
  5930f4:      	addb	%dl, (%edx)
  5930f6:      	fcompl	(%eax)
  5930f9:      	sbbb	$-0x24, %al
  5930fb:      	popl	%eax
  5930fc:      	addb	%ah, (%esi)
  5930fe:      	fcompl	(%eax)
  593101:      	pushl	%ss
  593102:      	sbbb	(%ecx), %bl
  593105:      	pushl	%ss
  593106:      	sbbb	(%ecx), %bl
  593109:      	pushl	%ss
  59310a:      	sbbb	(%ecx), %bl
  59310d:      	pushl	%ss
  59310e:      	sbbb	(%ecx), %bl
  593111:      	pushl	%ss
  593112:      	sbbb	(%ecx), %bl
  593115:      	pushl	%ss
  593116:      	sbbb	(%ecx), %bl
  593119:      	pushl	%ss
  59311a:      	sbbb	(%ecx), %bl
  59311d:      	pushl	%ss
  59311e:      	sbbb	(%ecx), %bl
  593121:      	pushl	%ss
  593122:      	sbbb	(%ecx), %bl
  593125:      	pushl	%ss
  593126:      	sbbb	(%ecx), %bl
  593129:      	pushl	%ss
  59312a:      	sbbb	(%ecx), %bl
  59312d:      	pushl	%ss
  59312e:      	sbbb	(%ecx), %bl
  593131:      	pushl	%ss
  593132:      	sbbb	(%ecx), %bl
  593135:      	pushl	%ss
  593136:      	sbbb	(%ecx), %bl
  593139:      	pushl	%ss
  59313a:      	sbbb	(%ecx), %bl
  59313d:      	pushl	%ss
  59313e:      	sbbb	(%ecx), %bl
  593141:      	pushl	%ss
  593142:      	sbbb	(%ecx), %bl
  593145:      	pushl	%ss
  593146:      	sbbb	(%ecx), %bl
  593149:      	pushl	%ss
  59314a:      	sbbb	(%ecx), %bl
  59314d:      	pushl	%ss
  59314e:      	sbbb	(%ecx), %bl
  593151:      	pushl	%ss
  593152:      	sbbb	(%ecx), %bl
  593155:      	pushl	%ss
  593156:      	sbbb	(%ecx), %bl
  593159:      	pushl	%ss
  59315a:      	sbbb	(%ecx), %bl
  59315d:      	pushl	%ss
  59315e:      	sbbb	(%ecx), %bl
  593161:      	pushl	%ss
  593162:      	sbbb	(%ecx), %bl
  593165:      	pushl	%ss
  593166:      	sbbb	(%ecx), %bl
  593169:      	pushl	%ss
  59316a:      	sbbb	(%ecx), %bl
  59316d:      	pushl	%ss
  59316e:      	sbbb	(%ecx), %bl
  593171:      	pushl	%ss
  593172:      	sbbb	(%ecx), %bl
  593175:      	pushl	%ss
  593176:      	sbbb	(%ecx), %bl
  593179:      	pushl	%ss
  59317a:      	sbbb	(%ecx), %bl
  59317d:      	pushl	%ss
  59317e:      	sbbb	(%ecx), %bl
  593181:      	pushl	%ss
  593182:      	sbbb	(%ecx), %bl
  593185:      	pushl	%ss
  593186:      	sbbb	(%ecx), %bl
  593189:      	pushl	%ss
  59318a:      	sbbb	(%ecx), %bl
  59318d:      	pushl	%ss
  59318e:      	sbbb	(%ecx), %bl
  593191:      	pushl	%ss
  593192:      	sbbb	(%ecx), %bl
  593195:      	pushl	%ss
  593196:      	sbbb	(%ecx), %bl
  593199:      	pushl	%ss
  59319a:      	sbbb	(%ecx), %bl
  59319d:      	pushl	%ss
  59319e:      	sbbb	(%ecx), %bl
  5931a1:      	pushl	%ss
  5931a2:      	sbbb	(%ecx), %bl
  5931a5:      	pushl	%ss
  5931a6:      	sbbb	(%ecx), %bl
  5931a9:      	pushl	%ss
  5931aa:      	sbbb	(%ecx), %bl
  5931ad:      	pushl	%ss
  5931ae:      	sbbb	(%ecx), %bl
  5931b1:      	pushl	%ss
  5931b2:      	sbbb	(%ecx), %bl
  5931b5:      	pushl	%ss
  5931b6:      	sbbb	(%ecx), %bl
  5931b9:      	pushl	%ss
  5931ba:      	sbbb	(%ecx), %bl
  5931bd:      	pushl	%ss
  5931be:      	sbbb	(%ecx), %bl
  5931c1:      	pushl	%ss
  5931c2:      	sbbb	(%ecx), %bl
  5931c5:      	pushl	%ss
  5931c6:      	sbbb	(%ecx), %bl
  5931c9:      	pushl	%ss
  5931ca:      	sbbb	(%ecx), %bl
  5931cd:      	pushl	%ss
  5931ce:      	sbbb	(%ecx), %bl
  5931d1:      	pushl	%ss
  5931d2:      	sbbb	(%ecx), %bl
  5931d5:      	pushl	%ss
  5931d6:      	sbbb	(%ecx), %bl
  5931d9:      	pushl	%ss
  5931da:      	sbbb	(%ecx), %bl
  5931dd:      	pushl	%ss
  5931de:      	sbbb	(%ecx), %bl
  5931e1:      	pushl	%ss
  5931e2:      	sbbb	(%ecx), %bl
  5931e5:      	pushl	%ss
  5931e6:      	sbbb	(%ecx), %bl
  5931e9:      	pushl	%ss
  5931ea:      	sbbb	(%ecx), %bl
  5931ed:      	pushl	%ss
  5931ee:      	sbbb	(%ecx), %bl
  5931f1:      	pushl	%ss
  5931f2:      	sbbb	(%ecx), %bl
  5931f5:      	pushl	%ss
  5931f6:      	sbbb	(%ecx), %bl
  5931f9:      	pushl	%ss
  5931fa:      	sbbb	(%ecx), %bl
  5931fd:      	pushl	%ss
  5931fe:      	sbbb	(%ecx), %bl
  593201:      	pushl	%ss
  593202:      	sbbb	(%ecx), %bl
  593205:      	pushl	%ss
  593206:      	sbbb	(%ecx), %bl
  593209:      	pushl	%ss
  59320a:      	sbbb	(%ecx), %bl
  59320d:      	pushl	%ss
  59320e:      	sbbb	(%ecx), %bl
  593211:      	pushl	%ss
  593212:      	sbbb	(%ecx), %bl
  593215:      	pushl	%ss
  593216:      	sbbb	(%ecx), %bl
  593219:      	pushl	%ss
  59321a:      	sbbb	(%ecx), %bl
  59321d:      	pushl	%ss
  59321e:      	sbbb	(%ecx), %bl
  593221:      	pushl	%ss
  593222:      	sbbb	(%ecx), %bl
  593225:      	pushl	%ss
  593226:      	sbbb	(%ecx), %bl
  593229:      	pushl	%ss
  59322a:      	sbbb	(%ecx), %bl
  59322d:      	pushl	%ss
  59322e:      	sbbb	(%ecx), %bl
  593231:      	pushl	%ss
  593232:      	sbbb	(%ecx), %bl
  593235:      	pushl	%ss
  593236:      	sbbb	(%ecx), %bl
  593239:      	pushl	%ss
  59323a:      	sbbb	(%ecx), %bl
  59323d:      	pushl	%ss
  59323e:      	sbbb	(%ecx), %bl
  593241:      	pushl	%ss
  593242:      	sbbb	(%ecx), %bl
  593245:      	pushl	%ss
  593246:      	sbbb	(%ecx), %bl
  593249:      	pushl	%ss
  59324a:      	sbbb	(%ecx), %bl
  59324d:      	pushl	%ss
  59324e:      	sbbb	(%ecx), %bl
  593251:      	pushl	%ss
  593252:      	sbbb	(%ecx), %bl
  593255:      	pushl	%ss
  593256:      	sbbb	(%ecx), %bl
  593259:      	pushl	%ss
  59325a:      	sbbb	(%ecx), %bl
  59325d:      	pushl	%ss
  59325e:      	sbbb	(%ecx), %bl
  593261:      	pushl	%ss
  593262:      	sbbb	(%ecx), %bl
  593265:      	pushl	%ss
  593266:      	sbbb	(%ecx), %bl
  593269:      	pushl	%ss
  59326a:      	sbbb	(%ecx), %bl
  59326d:      	pushl	%ss
  59326e:      	sbbb	(%ecx), %bl
  593271:      	pushl	%ss
  593272:      	sbbb	(%ecx), %bl
  593275:      	pushl	%ss
  593276:      	sbbb	(%ecx), %bl
  593279:      	pushl	%ss
  59327a:      	sbbb	(%ecx), %bl
  59327d:      	pushl	%ss
  59327e:      	sbbb	(%ecx), %bl
  593281:      	pushl	%ss
  593282:      	sbbb	(%ecx), %bl
  593285:      	andb	$-0x22, %al
  593287:      	popl	%eax
  593288:      	addb	%dh, (%eax)
  59328a:      	fcompl	(%eax)
  59328d:      	cmpb	%ah, %bl
  59328f:      	popl	%eax
  593290:      	addb	%al, 0x58(%esp,%ebx,8)
  593294:      	addb	%cl, -0x24(%esi)
  593297:      	popl	%eax
  593298:      	addb	%bl, -0x24(%eax)
  59329b:      	popl	%eax
  59329c:      	addb	%ah, -0x24(%edx)
  59329f:      	popl	%eax
  5932a0:      	addb	%ch, 0x58(%esp,%ebx,8)
  5932a4:      	addb	%dh, -0x24(%esi)
  5932a7:      	popl	%eax
  5932a8:      	addb	%al, -0x75ffa724(%eax)
  5932ae:      	fcompl	(%eax)
  5932b1:      	xchgl	%esp, %eax
  5932b2:      	fcompl	(%eax)
  5932b5:      	ficomps	%cs:(%eax)
  5932b9:      	sahf
  5932ba:      	fcompl	(%eax)
  5932bd:      	testb	$-0x24, %al
  5932bf:      	popl	%eax
  5932c0:      	addb	%dh, -0x43ffa724(%edx)
  5932c6:      	fcompl	(%eax)
  5932c9:      	cmpb	%bl, %dh
  5932cb:      	popl	%eax
  5932cc:      	addb	%al, -0x22(%edx)
  5932cf:      	popl	%eax
  5932d0:      	addb	%cl, 0x58(%esi,%ebx,8)
  5932d4:      	addb	%dl, -0x22(%esi)
  5932d7:      	popl	%eax
  5932d8:      	addb	%ah, -0x22(%eax)
  5932db:      	popl	%eax
  5932dc:      	addb	%ch, -0x22(%edx)
  5932df:      	popl	%eax
  5932e0:      	addb	%dh, 0x58(%esi,%ebx,8)
  5932e4:      	addb	%bh, -0x22(%esi)
  5932e7:      	popl	%eax
  5932e8:      	addb	%dl, -0x63ffa722(%edx)
  5932ee:      	ficomps	(%eax)
  5932f1:      	cmpsb	%es:(%edi), (%esi)
  5932f2:      	ficomps	(%eax)
  5932f5:      	movb	$-0x22, %al
  5932f7:      	popl	%eax
  5932f8:      	addb	%bh, -0x3bffa722(%edx)
  5932fe:      	ficomps	(%eax)
  593301:      	into
  593302:      	ficomps	(%eax)
  593305:      	fcomp	%st(6)
  593307:      	popl	%eax
  593308:      	addb	%ah, %dl
  59330a:      	ficomps	(%eax)
  59330d:      	inb	%dx, %al
  59330e:      	ficomps	(%eax)
  593311:      	negb	%dh
  593313:      	popl	%eax
  593314:      	addb	%al, (%eax)
  593316:      	fistps	(%eax)
  593319:      	orb	%bh, %bl
  59331b:      	popl	%eax
  59331c:      	addb	%dl, (%edi,%ebx,8)
  59331f:      	popl	%eax
  593320:      	addb	%bl, (%esi)
  593322:      	fistps	(%eax)
  593325:      	subb	%bl, %bh
  593327:      	popl	%eax
  593328:      	addb	%dh, (%edx)
  59332a:      	fistps	(%eax)
  59332d:      	cmpb	$-0x21, %al
  59332f:      	popl	%eax
  593330:      	addb	%dl, %al
  593332:      	fcompl	(%eax)
  593335:      	fcmovu	%st(4), %st
  593337:      	popl	%eax
  593338:      	addb	%ah, %ah
  59333a:      	fcompl	(%eax)
  59333d:      	outb	%al, %dx
  59333e:      	fcompl	(%eax)
  593341:      	clc
  593342:      	fcompl	(%eax)
  593345:      	addb	%ch, %bl
  593347:      	popl	%eax
  593348:      	addb	%cl, -0x22e9ffa8(,%ebx,8)
  59334f:      	popl	%eax
  593350:      	addb	%ah, (%eax)
  593352:      	fstpl	(%eax)
  593355:      	subb	%ch, %bl
  593357:      	popl	%eax
  593358:      	addb	%dh, -0x22c1ffa8(,%ebx,8)
  59335f:      	popl	%eax
  593360:      	addb	%al, -0x21(%esi)
  593363:      	popl	%eax
  593364:      	addb	%al, -0x74ffa721(%ecx)
  59336a:      	fistps	(%eax)
  59336d:      	xchgl	%ebp, %eax
  59336e:      	fistps	(%eax)
  593371:      	lahf
  593372:      	fistps	(%eax)
  593375:      	testl	$0xb30058df, %eax       # imm = 0xB30058DF
  59337a:      	fistps	(%eax)
  59337d:      	movl	$0xc70058df, %ebp       # imm = 0xC70058DF
  593382:      	fistps	(%eax)
  593385:      	rcrl	%edi
  593387:      	popl	%eax
  593388:      	addb	%bl, %bl
  59338a:      	fistps	(%eax)
  59338d:      	inl	$0xdf, %eax
  59338f:      	popl	%eax
  593390:      	addb	%ch, %bh
  593392:      	fistps	(%eax)
  593395:      	stc
  593396:      	fistps	(%eax)
  593399:      	addl	%eax, %esp
  59339b:      	popl	%eax
  59339c:      	addb	%cl, 0x170058e0
  5933a2:      	loopne	0x5933fc <.text+0x1923fc>
  5933a4:      	addb	%ah, (%ecx)
  5933a6:      	loopne	0x593400 <.text+0x192400>
  5933a8:      	addb	%ch, (%ebx)
  5933aa:      	loopne	0x593404 <.text+0x192404>
  5933ac:      	addb	%dh, 0x3f0058e0
  5933b2:      	loopne	0x59340c <.text+0x19240c>
  5933b4:      	addb	%cl, -0x20(%ecx)
  5933b7:      	popl	%eax
  5933b8:      	addb	%dl, -0x20(%ebx)
  5933bb:      	popl	%eax
  5933bc:      	addb	%bl, -0x20(%ebp)
  5933bf:      	popl	%eax
  5933c0:      	addb	%ah, -0x20(%edi)
  5933c3:      	popl	%eax
  5933c4:      	addb	%dh, -0x20(%ecx)
  5933c7:      	popl	%eax
  5933c8:      	addb	%bh, -0x20(%ebx)
  5933cb:      	popl	%eax
  5933cc:      	addb	%al, -0x70ffa720(%ebp)
  5933d2:      	loopne	0x59342c <.text+0x19242c>
  5933d4:      	addb	%bl, -0x5cffa720(%ecx)
  5933da:      	loopne	0x593434 <.text+0x192434>
  5933dc:      	addb	%ch, -0x48ffa720(%ebp)
  5933e2:      	loopne	0x59343c <.text+0x19243c>
  5933e4:      	addb	%al, %cl
  5933e6:      	loopne	0x593440 <.text+0x192440>
  5933e8:      	addb	%cl, %bl
  5933ea:      	loopne	0x593444 <.text+0x192444>
  5933ec:      	addb	%dl, %ch
  5933ee:      	loopne	0x593448 <.text+0x192448>
  5933f0:      	addb	%bl, %bh
  5933f2:      	loopne	0x59344c <.text+0x19244c>
  5933f4:      	addb	%ch, %cl
  5933f6:      	loopne	0x593450 <.text+0x192450>
  5933f8:      	addb	%dh, %bl
  5933fa:      	loopne	0x593454 <.text+0x192454>
  5933fc:      	addb	%bh, %ch
  5933fe:      	loopne	0x593458 <.text+0x192458>
  593400:      	addb	%al, (%edi)
  593402:      	loope	0x59345c <.text+0x19245c>
  593404:      	addb	%dl, (%ecx)
  593406:      	loope	0x593460 <.text+0x192460>
  593408:      	addb	%bl, (%ebx)
  59340a:      	loope	0x593464 <.text+0x192464>
  59340c:      	addb	%ah, 0x2f0058e1
  593412:      	loope	0x59346c <.text+0x19246c>
  593414:      	addb	%bh, (%ecx)
  593416:      	loope	0x593470 <.text+0x192470>
  593418:      	addb	%al, -0x1f(%ebx)
  59341b:      	popl	%eax
  59341c:      	addb	%cl, -0x1f(%ebp)
  59341f:      	popl	%eax
  593420:      	addb	%dl, -0x1f(%edi)
  593423:      	popl	%eax
  593424:      	addb	%ah, -0x1f(%ecx)
  593427:      	popl	%eax
  593428:      	addb	%ch, -0x1f(%ebx)
  59342b:      	popl	%eax
  59342c:      	addb	%dh, -0x1f(%ebp)
  59342f:      	popl	%eax
  593430:      	addb	%bh, -0x1f(%edi)
  593433:      	popl	%eax
  593434:      	addb	%cl, -0x6cffa71f(%ecx)
  59343a:      	loope	0x593494 <.text+0x192494>
  59343c:      	addb	%bl, -0x58ffa71f(%ebp)
  593442:      	loope	0x59349c <.text+0x19249c>
  593444:      	addb	%dh, -0x44ffa71f(%ecx)
  59344a:      	loope	0x5934a4 <.text+0x1924a4>
  59344c:      	addb	%al, %ch
  59344e:      	loope	0x5934a8 <.text+0x1924a8>
  593450:      	addb	%cl, %bh
  593452:      	loope	0x5934ac <.text+0x1924ac>
  593454:      	addb	%bl, %cl
  593456:      	loope	0x5934b0 <.text+0x1924b0>
  593458:      	addb	%ah, %bl
  59345a:      	loope	0x5934b4 <.text+0x1924b4>
  59345c:      	addb	%ch, %ch
  59345e:      	loope	0x5934b8 <.text+0x1924b8>
  593460:      	addb	%dh, %bh
  593462:      	loope	0x5934bc <.text+0x1924bc>
  593464:      	addb	%al, (%ecx)
  593466:      	loop	0x5934c0 <.text+0x1924c0>
  593468:      	addb	%cl, (%ebx)
  59346a:      	loop	0x5934c4 <.text+0x1924c4>
  59346c:      	addb	%dl, 0x1f0058e2
  593472:      	loop	0x5934cc <.text+0x1924cc>
  593474:      	addb	%ch, (%ecx)
  593476:      	loop	0x5934d0 <.text+0x1924d0>
  593478:      	addb	%dh, (%ebx)
  59347a:      	loop	0x5934d4 <.text+0x1924d4>
  59347c:      	addb	%bh, 0x470058e2
  593482:      	loop	0x5934dc <.text+0x1924dc>
  593484:      	addb	%dl, -0x1e(%ecx)
  593487:      	popl	%eax
  593488:      	addb	%bl, -0x1e(%ebx)
  59348b:      	popl	%eax
  59348c:      	addb	%ah, -0x1e(%ebp)
  59348f:      	popl	%eax
  593490:      	addb	%ch, -0x1e(%edi)
  593493:      	popl	%eax
  593494:      	addb	%bh, -0x1e(%ecx)
  593497:      	popl	%eax
  593498:      	addb	%al, -0x72ffa71e(%ebx)
  59349e:      	loop	0x5934f8 <.text+0x1924f8>
  5934a0:      	addb	%dl, -0x5effa71e(%edi)
  5934a6:      	loop	0x593500 <.text+0x192500>
  5934a8:      	addb	%ch, -0x4affa71e(%ebx)
  5934ae:      	loop	0x593508 <.text+0x192508>
  5934b0:      	addb	%bh, -0x36ffa71e(%edi)
  5934b6:      	loop	0x593510 <.text+0x192510>
  5934b8:      	addb	%dl, %bl
  5934ba:      	loop	0x593514 <.text+0x192514>
  5934bc:      	addb	%bl, %ch
  5934be:      	loop	0x593518 <.text+0x192518>
  5934c0:      	addb	%ah, %bh
  5934c2:      	loop	0x59351c <.text+0x19251c>
  5934c4:      	addb	%dh, %cl
  5934c6:      	loop	0x593520 <.text+0x192520>
  5934c8:      	addb	%bh, %bl
  5934ca:      	loop	0x593524 <.text+0x192524>
  5934cc:      	addb	%al, 0xf0058e3
  5934d2:      	jecxz	0x59352c <.text+0x19252c>
  5934d4:      	addb	%bl, (%ecx)
  5934d6:      	jecxz	0x593530 <.text+0x192530>
  5934d8:      	addb	%ah, (%ebx)
  5934da:      	jecxz	0x593534 <.text+0x192534>
  5934dc:      	addb	%ch, 0x370058e3
  5934e2:      	jecxz	0x59353c <.text+0x19253c>
  5934e4:      	addb	%al, -0x1d(%ecx)
  5934e7:      	popl	%eax
  5934e8:      	addb	%cl, -0x1d(%ebx)
  5934eb:      	popl	%eax
  5934ec:      	addb	%dl, -0x1d(%ebp)
  5934ef:      	popl	%eax
  5934f0:      	addb	%bl, -0x1d(%edi)
  5934f3:      	popl	%eax
  5934f4:      	addb	%ch, -0x1d(%ecx)
  5934f7:      	popl	%eax
  5934f8:      	addb	%dh, -0x1d(%ebx)
  5934fb:      	popl	%eax
  5934fc:      	addb	%bh, -0x1d(%ebp)
  5934ff:      	popl	%eax
  593500:      	addb	%al, -0x6effa71d(%edi)
  593506:      	jecxz	0x593560 <.text+0x192560>
  593508:      	addb	%bl, -0x5affa71d(%ebx)
  59350e:      	jecxz	0x593568 <.text+0x192568>
  593510:      	addb	%ch, -0x46ffa71d(%edi)
  593516:      	jecxz	0x593570 <.text+0x192570>
  593518:      	addb	%al, %bl
  59351a:      	jecxz	0x593574 <.text+0x192574>
  59351c:      	addb	%cl, %ch
  59351e:      	jecxz	0x593578 <.text+0x192578>
  593520:      	addb	%dl, %bh
  593522:      	jecxz	0x59357c <.text+0x19257c>
  593524:      	addb	%ah, %cl
  593526:      	jecxz	0x593580 <.text+0x192580>
  593528:      	addb	%ch, %bl
  59352a:      	jecxz	0x593584 <.text+0x192584>
  59352c:      	addb	%dh, %ch
  59352e:      	jecxz	0x593588 <.text+0x192588>
  593530:      	addb	%bh, %bh
  593532:      	jecxz	0x59358c <.text+0x19258c>
  593534:      	addb	%cl, (%ecx)
  593536:      	inb	$0x58, %al
  593538:      	addb	%dl, (%ebx)
  59353a:      	inb	$0x58, %al
  59353c:      	addb	%bl, 0x270058e4
  593542:      	inb	$0x58, %al
  593544:      	addb	%dh, (%ecx)
  593546:      	inb	$0x58, %al
  593548:      	addb	%bh, (%ebx)
  59354a:      	inb	$0x58, %al
  59354c:      	addb	%al, -0x1c(%ebp)
  59354f:      	popl	%eax
  593550:      	addb	%cl, -0x1c(%edi)
  593553:      	popl	%eax
  593554:      	addb	%bl, -0x1c(%ecx)
  593557:      	popl	%eax
  593558:      	addb	%ah, -0x1c(%ebx)
  59355b:      	popl	%eax
  59355c:      	addb	%ch, -0x1c(%ebp)
  59355f:      	popl	%eax
  593560:      	addb	%dh, -0x1c(%edi)
  593563:      	popl	%eax
  593564:      	addb	%al, -0x74ffa71c(%ecx)
  59356a:      	inb	$0x58, %al
  59356c:      	addb	%dl, -0x60ffa71c(%ebp)
  593572:      	inb	$0x58, %al
  593574:      	addb	%ch, -0x4cffa71c(%ecx)
  59357a:      	inb	$0x58, %al
  59357c:      	addb	%bh, -0x38ffa71c(%ebp)
  593582:      	inb	$0x58, %al
  593584:      	addb	%dl, %cl
  593586:      	inb	$0x58, %al
  593588:      	addb	%bl, %bl
  59358a:      	inb	$0x58, %al
  59358c:      	addb	%ah, %ch
  59358e:      	inb	$0x58, %al
  593590:      	addb	%al, %cl
  593592:      	inl	$0x58, %eax
  593594:      	addb	%cl, %bl
  593596:      	inl	$0x58, %eax
  593598:      	addb	%dl, %ch
  59359a:      	inl	$0x58, %eax
  59359c:      	addb	%bl, %bh
  59359e:      	inl	$0x58, %eax
  5935a0:      	addb	%ch, %cl
  5935a2:      	inl	$0x58, %eax
  5935a4:      	addb	%dh, %bl
  5935a6:      	inl	$0x58, %eax
  5935a8:      	addb	%bh, %ch
  5935aa:      	inl	$0x58, %eax
  5935ac:      	addb	%al, (%edi)
  5935ae:      	outb	%al, $0x58
  5935b0:      	addb	%dl, (%ecx)
  5935b2:      	outb	%al, $0x58
  5935b4:      	addb	%bl, (%ebx)
  5935b6:      	outb	%al, $0x58
  5935b8:      	addb	%ch, %bh
  5935ba:      	inb	$0x58, %al
  5935bc:      	addb	%bh, %cl
  5935be:      	inb	$0x58, %al
  5935c0:      	addb	%al, (%ebx)
  5935c2:      	inl	$0x58, %eax
  5935c4:      	addb	%cl, 0x170058e5
  5935ca:      	inl	$0x58, %eax
  5935cc:      	addb	%ah, (%ecx)
  5935ce:      	inl	$0x58, %eax
  5935d0:      	addb	%ch, (%ebx)
  5935d2:      	inl	$0x58, %eax
  5935d4:      	addb	%dh, 0x3f0058e5
  5935da:      	inl	$0x58, %eax
  5935dc:      	addb	%cl, -0x1b(%ecx)
  5935df:      	popl	%eax
  5935e0:      	addb	%dl, -0x1b(%ebx)
  5935e3:      	popl	%eax
  5935e4:      	addb	%bl, -0x1b(%ebp)
  5935e7:      	popl	%eax
  5935e8:      	addb	%ah, -0x1b(%edi)
  5935eb:      	popl	%eax
  5935ec:      	addb	%dh, -0x1b(%ecx)
  5935ef:      	popl	%eax
  5935f0:      	addb	%bh, -0x1b(%ebx)
  5935f3:      	popl	%eax
  5935f4:      	addb	%al, -0x70ffa71b(%ebp)
  5935fa:      	inl	$0x58, %eax
  5935fc:      	addb	%bl, -0x5cffa71b(%ecx)
  593602:      	inl	$0x58, %eax
  593604:      	addb	%ch, 0x250058e5(%ebp)
  59360a:      	outb	%al, $0x58
  59360c:      	addb	%dh, 0x160058e5(%edi)
  593612:      	sbbb	(%ecx), %bl
  593615:      	addb	%al, (%ecx)
  593617:      	addb	(%ebx), %al
  593619:      	addb	$0x5, %al
  59361b:      	pushl	%es
  59361c:      	popl	%es
  59361d:      	orb	%cl, (%ecx)
  59361f:      	orb	(%ebx), %cl
  593621:      	orb	$0xd, %al
  593623:      	pushl	%cs
  593624:      	movups	(%ecx), %xmm2
  593627:      	adcb	(%ebx), %dl
  593629:      	adcb	$0x15, %al
  59362b:      	pushl	%ss
  59362c:      	popl	%ss
  59362d:      	sbbb	%bl, (%ecx)
  59362f:      	sbbb	(%ebx), %bl
  593631:      	movl	$0x1e1db81c, %eax       # imm = 0x1E1DB81C
  593636:      	popl	%ds
  593637:      	andb	%ah, (%ecx)
  593639:      	andb	0x26252423(%eax), %bh
  59363f:      	daa
  593640:      	subb	%ch, (%ecx)
  593642:      	subb	(%ebx), %ch
  593644:      	subb	$0x2d, %al
  593646:      	das
  593648:      	xorb	%dh, (%ecx)
  59364a:      	xorb	(%ebx), %dh
  59364c:      	xorb	$0x35, %al
  59364e:      	aaa
  593650:      	cmpb	%bh, (%ecx)
  593652:      	cmpb	(%ebx), %bh
  593654:      	cmpb	$0x3d, %al
  593656:      	aas
  593658:      	incl	%eax
  593659:      	incl	%ecx
  59365a:      	incl	%edx
  59365b:      	incl	%ebx
  59365c:      	incl	%esp
  59365d:      	incl	%ebp
  59365e:      	incl	%esi
  59365f:      	incl	%edi
  593660:      	movl	$0x4b4a4948, %eax       # imm = 0x4B4A4948
  593665:      	decl	%esp
  593666:      	decl	%ebp
  593667:      	decl	%esi
  593668:      	decl	%edi
  593669:      	pushl	%eax
  59366a:      	pushl	%ecx
  59366b:      	pushl	%edx
  59366c:      	pushl	%ebx
  59366d:      	pushl	%esp
  59366e:      	pushl	%ebp
  59366f:      	pushl	%esi
  593670:      	pushl	%edi
  593671:      	popl	%eax
  593672:      	popl	%ecx
  593673:      	popl	%edx
  593674:      	popl	%ebx
  593675:      	popl	%esp
  593676:      	popl	%ebp
  593677:      	popl	%esi
  593678:      	popl	%edi
  593679:      	pushal
  59367a:      	popal
  59367b:      	bound	%esp, 0x64(%ebx)
  59367e:      	addr16		pushw	$0x6a69         # imm = 0x6A69
  593684:      	imull	$0x6f, 0x6e(%ebp,%ebp,2), %ebp
  593689:      	jo	0x5936fc <.text+0x1926fc>
  59368b:      	jb	0x593700 <.text+0x192700>
  59368d:      	je	0x593704 <.text+0x192704>
  59368f:      	jbe	0x593708 <.text+0x192708>
  593691:      	js	0x59370c <.text+0x19270c>
  593693:      	jp	0x593710 <.text+0x192710>
  593695:      	jl	0x593714 <.text+0x192714>
  593697:      	jle	0x593718 <.text+0x192718>
  593699:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59369e:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936a3:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936a8:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936ad:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936b2:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936b7:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936bc:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936c1:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936c6:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936cb:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936d0:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936d5:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5936da:      	addb	$-0x7a, -0x7a7b7c7e(%ecx)
  5936e1:      	xchgl	%ecx, -0x73747577(%eax)
  5936e7:      	leal	-0x6d6e6f71(%esi), %ecx
  5936ed:      	xchgl	%ebx, %eax
  5936ee:      	xchgl	%esp, %eax
  5936ef:      	xchgl	%ebp, %eax
  5936f0:      	xchgl	%esi, %eax
  5936f1:      	xchgl	%edi, %eax
  5936f2:      	cwtl
  5936f3:      	cltd
  5936f4:      	lcalll	$-0x5f61, $0x9e9d9c9b   # imm = 0xA09F
                                                # imm = 0x9E9D9C9B
  5936fb:      	movl	0xb8b8b8b8, %eax
  593700:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593705:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59370a:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59370f:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593714:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593719:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59371e:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593723:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593728:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59372d:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593732:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593737:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59373c:      	movl	$0xa2b8b8b8, %eax       # imm = 0xA2B8B8B8
  593741:      	movl	%eax, 0xa7a6a5a4
  593746:      	movl	$0xa8b8b8b8, %eax       # imm = 0xA8B8B8B8
  59374b:      	testl	$0xadacabaa, %eax       # imm = 0xADACABAA
  593750:      	scasb	%es:(%edi), %al
  593751:      	scasl	%es:(%edi), %eax
  593752:      	movb	$-0x4f, %al
  593754:      	movb	$-0x4d, %dl
  593756:      	movb	$-0x48, %ah
  593758:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59375d:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593762:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593767:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59376c:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593771:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593776:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59377b:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593780:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593785:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59378a:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59378f:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593794:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593799:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  59379e:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937a3:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937a8:      	movl	$0xb5b8b8b8, %eax       # imm = 0xB5B8B8B8
  5937ad:      	movb	$-0x48, %dh
  5937af:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937b4:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937b9:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937be:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937c3:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937c8:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937cd:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937d2:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937d7:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937dc:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937e1:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937e6:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937eb:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937f0:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937f5:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937fa:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  5937ff:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593804:      	movl	$0xb8b8b8b8, %eax       # imm = 0xB8B8B8B8
  593809:      	movl	$0x5eff8bb7, %eax       # imm = 0x5EFF8BB7
  59380e:      	outl	%eax, $0x58
  593810:      	addb	%ch, -0x19(%eax)
  593813:      	popl	%eax
  593814:      	addb	%dh, -0x19(%edx)
  593817:      	popl	%eax
  593818:      	addb	%bh, 0x58(%edi,%eiz,8)
  59381c:      	addb	%al, -0x6fffa719(%esi)
  593822:      	outl	%eax, $0x58
  593824:      	addb	%bl, -0x5bffa719(%edx)
  59382a:      	outl	%eax, $0x58
  59382c:      	addb	%ch, 0x58(%eax,%ebp,8)
  593830:      	addb	%dh, -0x18(%esi)
  593833:      	popl	%eax
  593834:      	addb	%al, -0x75ffa718(%eax)
  59383a:      	calll	0xe8ed3897
  59383f:      	popl	%eax
  593840:      	addb	%bl, -0x57ffa718(%esi)
  593846:      	calll	0xe90b38a3
  59384b:      	popl	%eax
  59384c:      	addb	%ah, %dl
  59384e:      	calll	0xe94538ab
  593853:      	popl	%eax
  593854:      	addb	%dh, %dh
  593856:      	calll	0xe95938b3
  59385b:      	popl	%eax
  59385c:      	addb	%cl, (%edx)
  59385e:      	jmp	0xe96d38bb
  593863:      	popl	%eax
  593864:      	addb	%bl, (%esi)
  593866:      	jmp	0xe98138c3
  59386b:      	popl	%eax
  59386c:      	addb	%dh, (%edx)
  59386e:      	jmp	0xe99538cb
  593873:      	popl	%eax
  593874:      	addb	%al, -0x17(%esi)
  593877:      	popl	%eax
  593878:      	addb	%dl, -0x17(%eax)
  59387b:      	popl	%eax
  59387c:      	addb	%bl, -0x17(%edx)
  59387f:      	popl	%eax
  593880:      	addb	%ah, 0x58(%ecx,%ebp,8)
  593884:      	addb	%ch, -0x17(%esi)
  593887:      	popl	%eax
  593888:      	addb	%bh, -0x17(%eax)
  59388b:      	popl	%eax
  59388c:      	addb	%al, -0x73ffa717(%edx)
  593892:      	jmp	0xe9ef38ef
  593897:      	popl	%eax
  593898:      	addb	%ah, -0x55ffa717(%eax)
  59389e:      	jmp	0xea0d38fb
  5938a3:      	popl	%eax
  5938a4:      	addb	%bh, -0x37ffa717(%esi)
  5938aa:      	jmp	0xea2b3907
  5938af:      	popl	%eax
  5938b0:      	addb	%bl, %ah
  5938b2:      	jmp	0xea3f390f
  5938b7:      	popl	%eax
  5938b8:      	addb	%dh, %al
  5938ba:      	jmp	0xea533917
  5938bf:      	popl	%eax
  5938c0:      	addb	%al, (%edx,%ebp,8)
  5938c3:      	popl	%eax
  5938c4:      	addb	%cl, (%esi)
  5938c6:      	ljmpl	$0x58, $0xea180058      # imm = 0xEA180058
  5938cd:      	andb	%dl, %ch
  5938cf:      	popl	%eax
  5938d0:      	addb	%ch, (%edx,%ebp,8)
  5938d3:      	popl	%eax
  5938d4:      	addb	%dl, (%esi)
  5938d6:      	sbbb	(%ecx), %bl
  5938d9:      	addb	%al, (%ecx)
  5938db:      	addb	(%ebx), %al
  5938dd:      	addb	$0x22, %al
  5938df:      	andb	(%edx), %ah
  5938e1:      	andb	(%edx), %ah
  5938e3:      	andb	(%edx), %ah
  5938e5:      	andb	(%edx), %ah
  5938e7:      	andb	(%edx), %ah
  5938e9:      	andb	(%edx), %ah
  5938eb:      	andb	(%edx), %ah
  5938ed:      	andb	(%edx), %ah
  5938ef:      	andb	(%edx), %ah
  5938f1:      	andb	(%edx), %ah
  5938f3:      	andb	(%edx), %ah
  5938f5:      	andb	(%edx), %ah
  5938f7:      	andb	(%edx), %ah
  5938f9:      	andb	(%edx), %ah
  5938fb:      	andb	(%edx), %ah
  5938fd:      	andb	(%edx), %ah
  5938ff:      	andb	(%edx), %ah
  593901:      	andb	(%edx), %ah
  593903:      	andb	(%edx), %ah
  593905:      	andb	(%edx), %ah
  593907:      	andb	(%edx), %ah
  593909:      	andb	(%edx), %ah
  59390b:      	andb	(%edx), %ah
  59390d:      	andb	(%edx), %ah
  59390f:      	andb	(%edx), %ah
  593911:      	andb	(%edx), %ah
  593913:      	andb	(%edx), %ah
  593915:      	andb	(%edx), %ah
  593917:      	andb	(%edx), %ah
  593919:      	andb	(%edx), %ah
  59391b:      	andb	(%edx), %ah
  59391d:      	andb	(%edx), %ah
  59391f:      	andb	(%edx), %ah
  593921:      	andb	(%edx), %ah
  593923:      	andb	(%edx), %ah
  593925:      	andb	(%edx), %ah
  593927:      	andb	(%edx), %ah
  593929:      	andb	(%edx), %ah
  59392b:      	andb	(%edx), %ah
  59392d:      	andb	(%edx), %ah
  59392f:      	andb	(%edx), %ah
  593931:      	andb	(%edx), %ah
  593933:      	addl	$0x9080706, %eax        # imm = 0x9080706
  593938:      	orb	(%ebx), %cl
  59393a:      	orb	$0xd, %al
  59393c:      	pushl	%cs
  59393d:      	movups	(%ecx), %xmm2
  593940:      	adcb	(%ebx), %dl
  593942:      	adcb	$0x15, %al
  593944:      	pushl	%ss
  593945:      	popl	%ss
  593946:      	sbbb	%bl, (%ecx)
  593948:      	sbbb	(%ebx), %bl
  59394a:      	sbbb	$0x1d, %al
  59394c:      	pushl	%ds
  59394d:      	popl	%ds
  59394e:      	andb	%ah, (%ecx)
  593950:      	nop
  593951:      	outsl	(%esi), %dx
  593952:      	ljmpl	$0x58, $0xea790058      # imm = 0xEA790058
  593959:      	subl	$0x58, %edx
  59395c:      	addb	%cl, -0x68ffa716(%ebp)
  593962:      	ljmpl	$0x58, $0xeaa10058      # imm = 0xEAA10058
  593969:      	stosl	%eax, %es:(%edi)
  59396a:      	ljmpl	$0x58, $0xead30058      # imm = 0xEAD30058
  593971:      	fucomp	%st(2)
  593973:      	popl	%eax
  593974:      	addb	%ah, %bh
  593976:      	ljmpl	$0x58, $0xeaf10058      # imm = 0xEAF10058
  59397d:      	movb	$-0x16, %ch
  59397f:      	popl	%eax
  593980:      	addb	%bh, -0x36ffa716(%edi)
  593986:      	ljmpl	$0x59, $0x1a160058      # imm = 0x1A160058
  59398d:      	addb	%al, (%ecx)
  59398f:      	addb	(%ebx), %al
  593991:      	addb	$0x5, %al
  593993:      	pushl	%es
  593994:      	popl	%es
  593995:      	orb	%cl, (%ecx)
  593997:      	orb	(%esi), %cl
  593999:      	pushl	%cs
  59399a:      	pushl	%cs
  59399b:      	pushl	%cs
  59399c:      	pushl	%cs
  59399d:      	pushl	%cs
  59399e:      	pushl	%cs
  59399f:      	pushl	%cs
  5939a0:      	pushl	%cs
  5939a1:      	orl	0x58ec0f90(,%ecx), %ecx
  5939a8:      	addb	%bl, (%ecx)
  5939aa:      	inb	%dx, %al
  5939ab:      	popl	%eax
  5939ac:      	addb	%ah, (%ebx)
  5939ae:      	inb	%dx, %al
  5939af:      	popl	%eax
  5939b0:      	addb	%ch, 0x370058ec
  5939b6:      	inb	%dx, %al
  5939b7:      	popl	%eax
  5939b8:      	addb	%al, -0x14(%ecx)
  5939bb:      	popl	%eax
  5939bc:      	addb	%cl, -0x14(%ebx)
  5939bf:      	popl	%eax
  5939c0:      	addb	%dl, -0x14(%ebp)
  5939c3:      	popl	%eax
  5939c4:      	addb	%bl, -0x14(%edi)
  5939c7:      	popl	%eax
  5939c8:      	addb	%ch, -0x14(%ecx)
  5939cb:      	popl	%eax
  5939cc:      	addb	%dh, -0x14(%ebx)
  5939cf:      	popl	%eax
  5939d0:      	addb	%bh, -0x14(%ebp)
  5939d3:      	popl	%eax
  5939d4:      	addb	%al, -0x4fffa714(%edi)
  5939da:      	inb	%dx, %al
  5939db:      	popl	%eax
  5939dc:      	addb	%bh, -0x3bffa714(%edx)
  5939e2:      	inb	%dx, %al
  5939e3:      	popl	%eax
  5939e4:      	addb	%cl, %dh
  5939e6:      	inb	%dx, %al
  5939e7:      	popl	%eax
  5939e8:      	addb	%bl, %al
  5939ea:      	inb	%dx, %al
  5939eb:      	popl	%eax
  5939ec:      	addb	%ah, %dl
  5939ee:      	inb	%dx, %al
  5939ef:      	popl	%eax
  5939f0:      	addb	%ch, %ah
  5939f2:      	inb	%dx, %al
  5939f3:      	popl	%eax
  5939f4:      	addb	%dh, %dh
  5939f6:      	inb	%dx, %al
  5939f7:      	popl	%eax
  5939f8:      	addb	%al, (%eax)
  5939fa:      	inl	%dx, %eax
  5939fb:      	popl	%eax
  5939fc:      	addb	%cl, (%edx)
  5939fe:      	inl	%dx, %eax
  5939ff:      	popl	%eax
  593a00:      	addb	%dl, -0x12e1ffa8(,%ebp,8)
  593a07:      	popl	%eax
  593a08:      	addb	%ch, (%eax)
  593a0a:      	inl	%dx, %eax
  593a0b:      	popl	%eax
  593a0c:      	addb	%dh, (%edx)
  593a0e:      	inl	%dx, %eax
  593a0f:      	popl	%eax
  593a10:      	addb	%bh, -0x12b9ffa8(,%ebp,8)
  593a17:      	popl	%eax
  593a18:      	addb	%dl, -0x13(%eax)
  593a1b:      	popl	%eax
  593a1c:      	addb	%bl, -0x13(%edx)
  593a1f:      	popl	%eax
  593a20:      	addb	%ah, 0x58(%ebp,%ebp,8)
  593a24:      	addb	%ch, -0x13(%esi)
  593a27:      	popl	%eax
  593a28:      	addb	%bh, -0x13(%eax)
  593a2b:      	popl	%eax
  593a2c:      	addb	%al, -0x73ffa713(%edx)
  593a32:      	inl	%dx, %eax
  593a33:      	popl	%eax
  593a34:      	addb	%dl, -0x5fffa713(%esi)
  593a3a:      	inl	%dx, %eax
  593a3b:      	popl	%eax
  593a3c:      	addb	%ch, -0x4bffa713(%edx)
  593a42:      	inl	%dx, %eax
  593a43:      	popl	%eax
  593a44:      	addb	%dh, %al
  593a46:      	inl	%dx, %eax
  593a47:      	popl	%eax
  593a48:      	addb	%bh, %dl
  593a4a:      	inl	%dx, %eax
  593a4b:      	popl	%eax
  593a4c:      	addb	%al, (%esi,%ebp,8)
  593a4f:      	popl	%eax
  593a50:      	addb	%dl, (%esi)
  593a52:      	sbbb	(%ecx), %bl
  593a55:      	pushl	%cs
  593a56:      	outb	%al, %dx
  593a57:      	popl	%eax
  593a58:      	addb	%bl, (%eax)
  593a5a:      	outb	%al, %dx
  593a5b:      	popl	%eax
  593a5c:      	addb	%ah, (%edx)
  593a5e:      	outb	%al, %dx
  593a5f:      	popl	%eax
  593a60:      	addb	%ch, (%esi,%ebp,8)
  593a63:      	popl	%eax
  593a64:      	addb	%dh, (%esi)
  593a66:      	outb	%al, %dx
  593a67:      	popl	%eax
  593a68:      	addb	%al, -0x12(%eax)
  593a6b:      	popl	%eax
  593a6c:      	addb	%cl, -0x12(%edx)
  593a6f:      	popl	%eax
  593a70:      	addb	%dl, 0x58(%esi,%ebp,8)
  593a74:      	addb	%bl, -0x12(%esi)
  593a77:      	popl	%eax
  593a78:      	addb	%ch, -0x12(%eax)
  593a7b:      	popl	%eax
  593a7c:      	addb	%dh, -0x12(%edx)
  593a7f:      	popl	%eax
  593a80:      	addb	%bh, 0x58(%esi,%ebp,8)
  593a84:      	addb	%al, -0x6fffa712(%esi)
  593a8a:      	outb	%al, %dx
  593a8b:      	popl	%eax
  593a8c:      	addb	%bl, -0x5bffa712(%edx)
  593a92:      	outb	%al, %dx
  593a93:      	popl	%eax
  593a94:      	addb	%ch, -0x47ffa712(%esi)
  593a9a:      	outb	%al, %dx
  593a9b:      	popl	%eax
  593a9c:      	addb	%al, %dl
  593a9e:      	outb	%al, %dx
  593a9f:      	popl	%eax
  593aa0:      	addb	%cl, %ah
  593aa2:      	outb	%al, %dx
  593aa3:      	popl	%eax
  593aa4:      	addb	%dl, %dh
  593aa6:      	outb	%al, %dx
  593aa7:      	popl	%eax
  593aa8:      	addb	%ah, %al
  593aaa:      	outb	%al, %dx
  593aab:      	popl	%eax
  593aac:      	addb	%ch, %dl
  593aae:      	outb	%al, %dx
  593aaf:      	popl	%eax
  593ab0:      	addb	%dh, %ah
  593ab2:      	outb	%al, %dx
  593ab3:      	popl	%eax
  593ab4:      	addb	%bh, %dh
  593ab6:      	outb	%al, %dx
  593ab7:      	popl	%eax
  593ab8:      	addb	%cl, (%eax)
  593aba:      	outl	%eax, %dx
  593abb:      	popl	%eax
  593abc:      	addb	%dl, (%edx)
  593abe:      	outl	%eax, %dx
  593abf:      	popl	%eax
  593ac0:      	addb	%bl, (%edi,%ebp,8)
  593ac3:      	popl	%eax
  593ac4:      	addb	%ah, (%esi)
  593ac6:      	outl	%eax, %dx
  593ac7:      	popl	%eax
  593ac8:      	addb	%dh, (%eax)
  593aca:      	outl	%eax, %dx
  593acb:      	popl	%eax
  593acc:      	addb	%bh, (%edx)
  593ace:      	outl	%eax, %dx
  593acf:      	popl	%eax
  593ad0:      	addb	%al, 0x58(%edi,%ebp,8)
  593ad4:      	addb	%cl, -0x11(%esi)
  593ad7:      	popl	%eax
  593ad8:      	addb	%bl, -0x11(%eax)
  593adb:      	popl	%eax
  593adc:      	addb	%dl, -0x65ffa711(%eax)
  593ae2:      	outl	%eax, %dx
  593ae3:      	popl	%eax
  593ae4:      	addb	%ah, -0x1051ffa8(%edi,%ebp,8)
  593aeb:      	popl	%eax
  593aec:      	addb	%bh, -0x3dffa711(%eax)
  593af2:      	outl	%eax, %dx
  593af3:      	popl	%eax
  593af4:      	addb	%cl, %ah
  593af6:      	outl	%eax, %dx
  593af7:      	popl	%eax
  593af8:      	addb	%dl, %dh
  593afa:      	outl	%eax, %dx
  593afb:      	popl	%eax
  593afc:      	addb	%ah, %al
  593afe:      	outl	%eax, %dx
  593aff:      	popl	%eax
  593b00:      	addb	%ch, %dl
  593b02:      	outl	%eax, %dx
  593b03:      	popl	%eax
  593b04:      	addb	%ah, (%esi)
  593b06:      	lock
  593b07:      	popl	%eax
  593b08:      	addb	%dh, (%eax)
  593b0a:      	lock
  593b0b:      	popl	%eax
  593b0c:      	addb	%bh, (%edx)
  593b0e:      	lock
  593b0f:      	popl	%eax
  593b10:      	addb	%al, 0x58(%eax,%esi,8)
  593b14:      	addb	%cl, -0x10(%esi)
  593b17:      	popl	%eax
  593b18:      	addb	%bl, -0x10(%eax)
  593b1b:      	popl	%eax
  593b1c:      	addb	%ah, -0x10(%edx)
  593b1f:      	popl	%eax
  593b20:      	addb	%ch, 0x58(%eax,%esi,8)
  593b24:      	addb	%dh, -0x10(%esi)
  593b27:      	popl	%eax
  593b28:      	addb	%al, -0x75ffa710(%eax)
  593b2e:      	lock
  593b2f:      	popl	%eax
  593b30:      	addb	%dl, -0xf61ffa8(%eax,%esi,8)
  593b37:      	popl	%eax
  593b38:      	addb	%ch, -0x4dffa710(%eax)
  593b3e:      	lock
  593b3f:      	popl	%eax
  593b40:      	addb	%bh, -0xe4affa8(%eax,%esi,8)
  593b47:      	popl	%eax
  593b48:      	addb	%bh, -0x36ffa70f(%edi)
  593b4e:      	<unknown>
  593b4f:      	popl	%eax
  593b50:      	addb	%dl, %bl
  593b52:      	<unknown>
  593b53:      	popl	%eax
  593b54:      	addb	%bl, %ch
  593b56:      	<unknown>
  593b57:      	popl	%eax
  593b58:      	addb	%ah, %bh
  593b5a:      	<unknown>
  593b5b:      	popl	%eax
  593b5c:      	addb	%dh, %cl
  593b5e:      	<unknown>
  593b5f:      	popl	%eax
  593b60:      	addb	%bh, %bl
  593b62:      	<unknown>
  593b63:      	popl	%eax
  593b64:      	addb	%ch, (%ebx)
  593b66:      	repne		popl	%eax
  593b68:      	addb	%dh, 0x3f0058f2
  593b6e:      	repne		popl	%eax
  593b70:      	addb	%cl, -0xe(%ecx)
  593b73:      	popl	%eax
  593b74:      	addb	%dl, -0xe(%ebx)
  593b77:      	popl	%eax
  593b78:      	addb	%bl, -0xe(%ebp)
  593b7b:      	popl	%eax
  593b7c:      	addb	%ah, -0xe(%edi)
  593b7f:      	popl	%eax
  593b80:      	addb	%dh, -0xe(%ecx)
  593b83:      	popl	%eax
  593b84:      	addb	%bh, -0xe(%ebx)
  593b87:      	popl	%eax
  593b88:      	addb	%al, -0x70ffa70e(%ebp)
  593b8e:      	repne		popl	%eax
  593b90:      	addb	%bl, -0x5cffa70e(%ecx)
  593b96:      	repne		popl	%eax
  593b98:      	addb	%ch, -0x48ffa70e(%ebp)
  593b9e:      	repne		popl	%eax
  593ba0:      	addb	%al, %cl
  593ba2:      	repne		popl	%eax
  593ba4:      	addb	%cl, %bl
  593ba6:      	repne		popl	%eax
  593ba8:      	addb	%dl, %ch
  593baa:      	repne		popl	%eax
  593bac:      	addb	%dl, (%esi)
  593bae:      	sbbb	(%ecx), %bl
  593bb1:      	addb	%al, (%ecx)
  593bb3:      	addb	(%edx), %dl
  593bb5:      	adcb	(%edx), %dl
  593bb7:      	adcb	(%edx), %dl
  593bb9:      	adcb	(%edx), %dl
  593bbb:      	adcb	(%edx), %dl
  593bbd:      	addl	(%edx), %edx
  593bbf:      	addb	$0x5, %al
  593bc1:      	adcb	(%esi), %al
  593bc3:      	popl	%es
  593bc4:      	orb	%dl, (%edx)
  593bc6:      	orl	%ecx, (%edx)
  593bc8:      	adcb	(%edx), %dl
  593bca:      	adcb	(%ebx), %cl
  593bcc:      	orb	$0xd, %al
  593bce:      	pushl	%cs
  593bcf:      	movups	(%ecx), %xmm2
  593bd2:      	leal	(%ecx), %ecx
  593bd5:      	cmpsb	%es:(%edi), (%esi)
  593bd6:      	rep		popl	%eax
  593bd8:      	addb	%dh, -0x45ffa70d(%eax)
  593bde:      	rep		popl	%eax
  593be0:      	addb	%al, %ah
  593be2:      	rep		popl	%eax
  593be4:      	addb	%cl, %dh
  593be6:      	rep		popl	%eax
  593be8:      	addb	%bl, %al
  593bea:      	rep		popl	%eax
  593bec:      	addb	%ah, %dl
  593bee:      	rep		popl	%eax
  593bf0:      	addb	%bh, (%esi)
  593bf2:      	hlt
  593bf3:      	popl	%eax
  593bf4:      	addb	%ch, (%edx)
  593bf6:      	hlt
  593bf7:      	popl	%eax
  593bf8:      	addb	%ah, (%eax)
  593bfa:      	hlt
  593bfb:      	popl	%eax
  593bfc:      	addb	%cl, -0xc(%eax)
  593bff:      	popl	%eax
  593c00:      	addb	%dh, -0xc(%edi)
  593c03:      	popl	%eax
  593c04:      	addb	%ch, -0xc(%ebp)
  593c07:      	popl	%eax
  593c08:      	addb	%ah, -0xc(%ebx)
  593c0b:      	popl	%eax
  593c0c:      	addb	%al, -0x5fffa70c(%ecx)
  593c12:      	hlt
  593c13:      	popl	%eax
  593c14:      	addb	%ch, -0x4bffa70c(%edx)
  593c1a:      	hlt
  593c1b:      	popl	%eax
  593c1c:      	addb	%bh, -0x37ffa70c(%esi)
  593c22:      	hlt
  593c23:      	popl	%eax
  593c24:      	addb	%dl, %dl
  593c26:      	hlt
  593c27:      	popl	%eax
  593c28:      	addb	%bl, %ah
  593c2a:      	hlt
  593c2b:      	popl	%eax
  593c2c:      	addb	%ah, %dh
  593c2e:      	hlt
  593c2f:      	popl	%eax
  593c30:      	addb	%dh, %al
  593c32:      	hlt
  593c33:      	popl	%eax
  593c34:      	addb	%dl, (%ecx)
  593c36:      	cmc
  593c37:      	popl	%eax
  593c38:      	addb	%bl, (%ebx)
  593c3a:      	cmc
  593c3b:      	popl	%eax
  593c3c:      	addb	%ch, (%edi)
  593c3e:      	cmc
  593c3f:      	popl	%eax
  593c40:      	addb	%bh, (%ecx)
  593c42:      	cmc
  593c43:      	popl	%eax
  593c44:      	addb	%al, -0xb(%ebx)
  593c47:      	popl	%eax
  593c48:      	addb	%cl, -0xb(%ebp)
  593c4b:      	popl	%eax
  593c4c:      	addb	%dl, (%esi)
  593c4e:      	sbbb	(%ecx), %bl
  593c51:      	pushl	%edi
  593c52:      	cmc
  593c53:      	popl	%eax
  593c54:      	addb	%ah, -0xb(%ecx)
  593c57:      	popl	%eax
  593c58:      	addb	%ch, -0xb(%ebx)
  593c5b:      	popl	%eax
  593c5c:      	addb	%dh, -0xb(%ebp)
  593c5f:      	popl	%eax
  593c60:      	addb	%bh, -0xb(%edi)
  593c63:      	popl	%eax
  593c64:      	addb	%cl, -0x6cffa70b(%ecx)
  593c6a:      	cmc
  593c6b:      	popl	%eax
  593c6c:      	addb	%bl, -0x58ffa70b(%ebp)
  593c72:      	cmc
  593c73:      	popl	%eax
  593c74:      	addb	%dh, -0x44ffa70b(%ecx)
  593c7a:      	cmc
  593c7b:      	popl	%eax
  593c7c:      	addb	%al, %ch
  593c7e:      	cmc
  593c7f:      	popl	%eax
  593c80:      	addb	%cl, %bh
  593c82:      	cmc
  593c83:      	popl	%eax
  593c84:      	addb	%bl, %cl
  593c86:      	cmc
  593c87:      	popl	%eax
  593c88:      	addb	%ah, %bl
  593c8a:      	cmc
  593c8b:      	popl	%eax
  593c8c:      	addb	%ch, %ch
  593c8e:      	cmc
  593c8f:      	popl	%eax
  593c90:      	addb	%dh, %bh
  593c92:      	cmc
  593c93:      	popl	%eax
  593c94:      	addb	%al, (%ecx)
  593c96:      	negb	(%eax)
  593c99:      	orl	%esi, %esi
  593c9b:      	popl	%eax
  593c9c:      	addb	%dl, 0x1f0058f6
  593ca2:      	negb	(%eax)
  593ca5:      	subl	%esi, %esi
  593ca7:      	popl	%eax
  593ca8:      	addb	%dh, (%ebx)
  593caa:      	negb	(%eax)
  593cad:      	cmpl	$0x470058f6, %eax       # imm = 0x470058F6
  593cb2:      	negb	(%eax)
  593cb5:      	pushl	%ecx
  593cb6:      	negb	(%eax)
  593cb9:      	popl	%ebx
  593cba:      	negb	(%eax)
  593cbd:      	negb	%gs:(%eax)
  593cc1:      	outsl	(%esi), %dx
  593cc2:      	negb	(%eax)
  593cc5:      	jns	0x593cbd <.text+0x192cbd>
  593cc7:      	popl	%eax
  593cc8:      	addb	%al, -0x72ffa70a(%ebx)
  593cce:      	negb	(%eax)
  593cd1:      	xchgl	%edi, %eax
  593cd2:      	negb	(%eax)
  593cd5:      	movl	0xab0058f6, %eax
  593cda:      	negb	(%eax)
  593cdd:      	movb	$-0xa, %ch
  593cdf:      	popl	%eax
  593ce0:      	addb	%bh, -0x60ffa70a(%edi)
  593ce6:      	std
  593ce7:      	popl	%eax
  593ce8:      	addb	%ch, 0x160058fd(%ecx)
  593cee:      	sbbb	(%ecx), %bl
  593cf1:      	pushl	%ss
  593cf2:      	sbbb	(%ecx), %bl
  593cf5:      	pushl	%ss
  593cf6:      	sbbb	(%ecx), %bl
  593cf9:      	pushl	%ss
  593cfa:      	sbbb	(%ecx), %bl
  593cfd:      	pushl	%ss
  593cfe:      	sbbb	(%ecx), %bl
  593d01:      	pushl	%ss
  593d02:      	sbbb	(%ecx), %bl
  593d05:      	pushl	%ss
  593d06:      	sbbb	(%ecx), %bl
  593d09:      	pushl	%ss
  593d0a:      	sbbb	(%ecx), %bl
  593d0d:      	pushl	%ss
  593d0e:      	sbbb	(%ecx), %bl
  593d11:      	pushl	%ss
  593d12:      	sbbb	(%ecx), %bl
  593d15:      	pushl	%ss
  593d16:      	sbbb	(%ecx), %bl
  593d19:      	pushl	%ss
  593d1a:      	sbbb	(%ecx), %bl
  593d1d:      	pushl	%ss
  593d1e:      	sbbb	(%ecx), %bl
  593d21:      	pushl	%ss
  593d22:      	sbbb	(%ecx), %bl
  593d25:      	pushl	%ss
  593d26:      	sbbb	(%ecx), %bl
  593d29:      	pushl	%ss
  593d2a:      	sbbb	(%ecx), %bl
  593d2d:      	pushl	%ss
  593d2e:      	sbbb	(%ecx), %bl
  593d31:      	pushl	%ss
  593d32:      	sbbb	(%ecx), %bl
  593d35:      	pushl	%ss
  593d36:      	sbbb	(%ecx), %bl
  593d39:      	pushl	%ss
  593d3a:      	sbbb	(%ecx), %bl
  593d3d:      	pushl	%ss
  593d3e:      	sbbb	(%ecx), %bl
  593d41:      	pushl	%ss
  593d42:      	sbbb	(%ecx), %bl
  593d45:      	pushl	%ss
  593d46:      	sbbb	(%ecx), %bl
  593d49:      	pushl	%ss
  593d4a:      	sbbb	(%ecx), %bl
  593d4d:      	pushl	%ss
  593d4e:      	sbbb	(%ecx), %bl
  593d51:      	pushl	%ss
  593d52:      	sbbb	(%ecx), %bl
  593d55:      	pushl	%ss
  593d56:      	sbbb	(%ecx), %bl
  593d59:      	pushl	%ss
  593d5a:      	sbbb	(%ecx), %bl
  593d5d:      	pushl	%ss
  593d5e:      	sbbb	(%ecx), %bl
  593d61:      	pushl	%ss
  593d62:      	sbbb	(%ecx), %bl
  593d65:      	pushl	%ss
  593d66:      	sbbb	(%ecx), %bl
  593d69:      	pushl	%ss
  593d6a:      	sbbb	(%ecx), %bl
  593d6d:      	pushl	%ss
  593d6e:      	sbbb	(%ecx), %bl
  593d71:      	pushl	%ss
  593d72:      	sbbb	(%ecx), %bl
  593d75:      	pushl	%ss
  593d76:      	sbbb	(%ecx), %bl
  593d79:      	pushl	%ss
  593d7a:      	sbbb	(%ecx), %bl
  593d7d:      	pushl	%ss
  593d7e:      	sbbb	(%ecx), %bl
  593d81:      	pushl	%ss
  593d82:      	sbbb	(%ecx), %bl
  593d85:      	leave
  593d86:      	negb	(%eax)
  593d89:      	<unknown>
  593d8b:      	popl	%eax
  593d8c:      	addb	%bl, %ch
  593d8e:      	negb	(%eax)
  593d91:      	outl	%eax, $0xf6
  593d93:      	popl	%eax
  593d94:      	addb	%dh, %cl
  593d96:      	negb	(%eax)
  593d99:      	sti
  593d9a:      	negb	(%eax)
  593d9d:      	addl	$0xf0058f7, %eax        # imm = 0xF0058F7
  593da2:      	negl	(%eax)
  593da5:      	sbbl	%esi, %edi
  593da7:      	popl	%eax
  593da8:      	addb	%ah, (%ebx)
  593daa:      	negl	(%eax)
  593dad:      	subl	$0x370058f7, %eax       # imm = 0x370058F7
  593db2:      	negl	(%eax)
  593db5:      	incl	%ecx
  593db6:      	negl	(%eax)
  593db9:      	decl	%ebx
  593dba:      	negl	(%eax)
  593dbd:      	pushl	%ebp
  593dbe:      	negl	(%eax)
  593dc1:      	popl	%edi
  593dc2:      	negl	(%eax)
  593dc5:      	imull	$0xf7730058, %edi, %esi # imm = 0xF7730058
  593dcb:      	popl	%eax
  593dcc:      	addb	%dl, (%esi)
  593dce:      	sbbb	(%ecx), %bl
  593dd1:      	jge	0x593dca <.text+0x192dca>
  593dd3:      	popl	%eax
  593dd4:      	addb	%al, -0x6effa709(%edi)
  593dda:      	negl	(%eax)
  593ddd:      	wait
  593dde:      	negl	(%eax)
  593de1:      	movsl	(%esi), %es:(%edi)
  593de2:      	negl	(%eax)
  593de5:      	scasl	%es:(%edi), %eax
  593de6:      	negl	(%eax)
  593de9:      	movl	$0xc30058f7, %ecx       # imm = 0xC30058F7
  593dee:      	negl	(%eax)
  593df1:      	int	$0xf7
  593df3:      	popl	%eax
  593df4:      	addb	%dl, %bh
  593df6:      	negl	(%eax)
  593df9:      	loope	0x593df2 <.text+0x192df2>
  593dfb:      	popl	%eax
  593dfc:      	addb	%ch, %bl
  593dfe:      	negl	(%eax)
  593e01:      	cmc
  593e02:      	negl	(%eax)
  593e05:      	pushl	%edi
  593e07:      	popl	%eax
  593e08:      	addb	%cl, (%ecx)
  593e0a:      	clc
  593e0b:      	popl	%eax
  593e0c:      	addb	%dl, (%ebx)
  593e0e:      	clc
  593e0f:      	popl	%eax
  593e10:      	addb	%bl, 0x270058f8
  593e16:      	clc
  593e17:      	popl	%eax
  593e18:      	addb	%dh, (%ecx)
  593e1a:      	clc
  593e1b:      	popl	%eax
  593e1c:      	addb	%dh, 0x3b0058fd(%ebx)
  593e22:      	clc
  593e23:      	popl	%eax
  593e24:      	addb	%al, -0x8(%ebp)
  593e27:      	popl	%eax
  593e28:      	addb	%cl, -0x8(%edi)
  593e2b:      	popl	%eax
  593e2c:      	addb	%bl, -0x8(%ecx)
  593e2f:      	popl	%eax
  593e30:      	addb	%ah, -0x8(%ebx)
  593e33:      	popl	%eax
  593e34:      	addb	%ch, -0x8(%ebp)
  593e37:      	popl	%eax
  593e38:      	addb	%dh, -0x8(%edi)
  593e3b:      	popl	%eax
  593e3c:      	addb	%al, -0x74ffa708(%ecx)
  593e42:      	clc
  593e43:      	popl	%eax
  593e44:      	addb	%dl, -0x60ffa708(%ebp)
  593e4a:      	clc
  593e4b:      	popl	%eax
  593e4c:      	addb	%ch, -0x4cffa708(%ecx)
  593e52:      	clc
  593e53:      	popl	%eax
  593e54:      	addb	%bh, -0x38ffa708(%ebp)
  593e5a:      	clc
  593e5b:      	popl	%eax
  593e5c:      	addb	%dl, %cl
  593e5e:      	clc
  593e5f:      	popl	%eax
  593e60:      	addb	%bl, %bl
  593e62:      	clc
  593e63:      	popl	%eax
  593e64:      	addb	%ah, %ch
  593e66:      	clc
  593e67:      	popl	%eax
  593e68:      	addb	%ch, %bh
  593e6a:      	clc
  593e6b:      	popl	%eax
  593e6c:      	addb	%bh, %cl
  593e6e:      	clc
  593e6f:      	popl	%eax
  593e70:      	addb	%al, (%ebx)
  593e72:      	stc
  593e73:      	popl	%eax
  593e74:      	addb	%cl, 0x170058f9
  593e7a:      	stc
  593e7b:      	popl	%eax
  593e7c:      	addb	%ah, (%ecx)
  593e7e:      	stc
  593e7f:      	popl	%eax
  593e80:      	addb	%ch, (%ebx)
  593e82:      	stc
  593e83:      	popl	%eax
  593e84:      	addb	%dh, 0x3f0058f9
  593e8a:      	stc
  593e8b:      	popl	%eax
  593e8c:      	addb	%cl, -0x7(%ecx)
  593e8f:      	popl	%eax
  593e90:      	addb	%dl, -0x7(%ebx)
  593e93:      	popl	%eax
  593e94:      	addb	%bl, -0x7(%ebp)
  593e97:      	popl	%eax
  593e98:      	addb	%ah, -0x7(%edi)
  593e9b:      	popl	%eax
  593e9c:      	addb	%dh, -0x7(%ecx)
  593e9f:      	popl	%eax
  593ea0:      	addb	%bh, -0x7(%ebx)
  593ea3:      	popl	%eax
  593ea4:      	addb	%al, -0x70ffa707(%ebp)
  593eaa:      	stc
  593eab:      	popl	%eax
  593eac:      	addb	%bl, -0x5cffa707(%ecx)
  593eb2:      	stc
  593eb3:      	popl	%eax
  593eb4:      	addb	%ch, -0x48ffa707(%ebp)
  593eba:      	stc
  593ebb:      	popl	%eax
  593ebc:      	addb	%al, %cl
  593ebe:      	stc
  593ebf:      	popl	%eax
  593ec0:      	addb	%cl, %bl
  593ec2:      	stc
  593ec3:      	popl	%eax
  593ec4:      	addb	%dl, %ch
  593ec6:      	stc
  593ec7:      	popl	%eax
  593ec8:      	addb	%bl, %bh
  593eca:      	stc
  593ecb:      	popl	%eax
  593ecc:      	addb	%ch, %cl
  593ece:      	stc
  593ecf:      	popl	%eax
  593ed0:      	addb	%dh, %bl
  593ed2:      	stc
  593ed3:      	popl	%eax
  593ed4:      	addb	%bh, %ch
  593ed6:      	stc
  593ed7:      	popl	%eax
  593ed8:      	addb	%al, (%edi)
  593eda:      	cli
  593edb:      	popl	%eax
  593edc:      	addb	%dl, (%ecx)
  593ede:      	cli
  593edf:      	popl	%eax
  593ee0:      	addb	%bl, (%ebx)
  593ee2:      	cli
  593ee3:      	popl	%eax
  593ee4:      	addb	%ah, 0x2f0058fa
  593eea:      	cli
  593eeb:      	popl	%eax
  593eec:      	addb	%bh, (%ecx)
  593eee:      	cli
  593eef:      	popl	%eax
  593ef0:      	addb	%al, -0x6(%ebx)
  593ef3:      	popl	%eax
  593ef4:      	addb	%cl, -0x6(%ebp)
  593ef7:      	popl	%eax
  593ef8:      	addb	%dl, -0x6(%edi)
  593efb:      	popl	%eax
  593efc:      	addb	%ah, -0x6(%ecx)
  593eff:      	popl	%eax
  593f00:      	addb	%ch, -0x6(%ebx)
  593f03:      	popl	%eax
  593f04:      	addb	%dh, -0x6(%ebp)
  593f07:      	popl	%eax
  593f08:      	addb	%bh, -0x6(%edi)
  593f0b:      	popl	%eax
  593f0c:      	addb	%cl, -0x6cffa706(%ecx)
  593f12:      	cli
  593f13:      	popl	%eax
  593f14:      	addb	%bl, -0x58ffa706(%ebp)
  593f1a:      	cli
  593f1b:      	popl	%eax
  593f1c:      	addb	%dh, -0x44ffa706(%ecx)
  593f22:      	cli
  593f23:      	popl	%eax
  593f24:      	addb	%al, %ch
  593f26:      	cli
  593f27:      	popl	%eax
  593f28:      	addb	%cl, %bh
  593f2a:      	cli
  593f2b:      	popl	%eax
  593f2c:      	addb	%bl, %cl
  593f2e:      	cli
  593f2f:      	popl	%eax
  593f30:      	addb	%ah, %bl
  593f32:      	cli
  593f33:      	popl	%eax
  593f34:      	addb	%ch, %ch
  593f36:      	cli
  593f37:      	popl	%eax
  593f38:      	addb	%dh, %bh
  593f3a:      	cli
  593f3b:      	popl	%eax
  593f3c:      	addb	%al, (%ecx)
  593f3e:      	sti
  593f3f:      	popl	%eax
  593f40:      	addb	%cl, (%ebx)
  593f42:      	sti
  593f43:      	popl	%eax
  593f44:      	addb	%dl, 0x1f0058fb
  593f4a:      	sti
  593f4b:      	popl	%eax
  593f4c:      	addb	%ch, (%ecx)
  593f4e:      	sti
  593f4f:      	popl	%eax
  593f50:      	addb	%dh, (%ebx)
  593f52:      	sti
  593f53:      	popl	%eax
  593f54:      	addb	%bh, 0x470058fb
  593f5a:      	sti
  593f5b:      	popl	%eax
  593f5c:      	addb	%dl, -0x5(%ecx)
  593f5f:      	popl	%eax
  593f60:      	addb	%bl, -0x5(%ebx)
  593f63:      	popl	%eax
  593f64:      	addb	%ah, -0x5(%ebp)
  593f67:      	popl	%eax
  593f68:      	addb	%ch, -0x5(%edi)
  593f6b:      	popl	%eax
  593f6c:      	addb	%bh, -0x5(%ecx)
  593f6f:      	popl	%eax
  593f70:      	addb	%al, -0x72ffa705(%ebx)
  593f76:      	sti
  593f77:      	popl	%eax
  593f78:      	addb	%dl, -0x5effa705(%edi)
  593f7e:      	sti
  593f7f:      	popl	%eax
  593f80:      	addb	%ch, -0x4affa705(%ebx)
  593f86:      	sti
  593f87:      	popl	%eax
  593f88:      	addb	%bh, -0x36ffa705(%edi)
  593f8e:      	sti
  593f8f:      	popl	%eax
  593f90:      	addb	%dl, %bl
  593f92:      	sti
  593f93:      	popl	%eax
  593f94:      	addb	%bl, %ch
  593f96:      	sti
  593f97:      	popl	%eax
  593f98:      	addb	%ah, %bh
  593f9a:      	sti
  593f9b:      	popl	%eax
  593f9c:      	addb	%dh, %cl
  593f9e:      	sti
  593f9f:      	popl	%eax
  593fa0:      	addb	%bh, %bl
  593fa2:      	sti
  593fa3:      	popl	%eax
  593fa4:      	addb	%al, 0xf0058fc
  593faa:      	cld
  593fab:      	popl	%eax
  593fac:      	addb	%bl, (%ecx)
  593fae:      	cld
  593faf:      	popl	%eax
  593fb0:      	addb	%ah, (%ebx)
  593fb2:      	cld
  593fb3:      	popl	%eax
  593fb4:      	addb	%ch, 0x370058fc
  593fba:      	cld
  593fbb:      	popl	%eax
  593fbc:      	addb	%al, -0x4(%ecx)
  593fbf:      	popl	%eax
  593fc0:      	addb	%cl, -0x4(%ebx)
  593fc3:      	popl	%eax
  593fc4:      	addb	%dl, -0x4(%ebp)
  593fc7:      	popl	%eax
  593fc8:      	addb	%bl, -0x4(%edi)
  593fcb:      	popl	%eax
  593fcc:      	addb	%ch, -0x4(%ecx)
  593fcf:      	popl	%eax
  593fd0:      	addb	%dh, -0x4(%ebx)
  593fd3:      	popl	%eax
  593fd4:      	addb	%bh, -0x4(%ebp)
  593fd7:      	popl	%eax
  593fd8:      	addb	%al, -0x6effa704(%edi)
  593fde:      	cld
  593fdf:      	popl	%eax
  593fe0:      	addb	%bl, -0x5affa704(%ebx)
  593fe6:      	cld
  593fe7:      	popl	%eax
  593fe8:      	addb	%ch, -0x46ffa704(%edi)
  593fee:      	cld
  593fef:      	popl	%eax
  593ff0:      	addb	%al, %bl
  593ff2:      	cld
  593ff3:      	popl	%eax
  593ff4:      	addb	%cl, %ch
  593ff6:      	cld
  593ff7:      	popl	%eax
  593ff8:      	addb	%dl, %bh
  593ffa:      	cld
  593ffb:      	popl	%eax
  593ffc:      	addb	%ah, %cl
  593ffe:      	cld
  593fff:      	popl	%eax
  594000:      	addb	%ch, %bl
  594002:      	cld
  594003:      	popl	%eax
  594004:      	addb	%dh, %ch
  594006:      	cld
  594007:      	popl	%eax
  594008:      	addb	%bh, %bh
  59400a:      	cld
  59400b:      	popl	%eax
  59400c:      	addb	%cl, (%ecx)
  59400e:      	std
  59400f:      	popl	%eax
  594010:      	addb	%dl, (%ebx)
  594012:      	std
  594013:      	popl	%eax
  594014:      	addb	%bl, 0x270058fd
  59401a:      	std
  59401b:      	popl	%eax
  59401c:      	addb	%dh, (%ecx)
  59401e:      	std
  59401f:      	popl	%eax
  594020:      	addb	%bh, (%ebx)
  594022:      	std
  594023:      	popl	%eax
  594024:      	addb	%al, -0x3(%ebp)
  594027:      	popl	%eax
  594028:      	addb	%cl, -0x3(%edi)
  59402b:      	popl	%eax
  59402c:      	addb	%bl, -0x3(%ecx)
  59402f:      	popl	%eax
  594030:      	addb	%ah, -0x3(%ebx)
  594033:      	popl	%eax
  594034:      	addb	%ch, -0x3(%ebp)
  594037:      	popl	%eax
  594038:      	addb	%dh, -0x3(%edi)
  59403b:      	popl	%eax
  59403c:      	addb	%al, -0x74ffa703(%ecx)
  594042:      	std
  594043:      	popl	%eax
  594044:      	addb	%dl, -0x42ffa703(%ebp)
  59404a:      	std
  59404b:      	popl	%eax
  59404c:      	addb	%al, %bh
  59404e:      	std
  59404f:      	popl	%eax
  594050:      	addb	%dl, %cl
  594052:      	std
  594053:      	popl	%eax
  594054:      	addb	%bl, %bl
  594056:      	std
  594057:      	popl	%eax
  594058:      	addb	%ah, %ch
  59405a:      	std
  59405b:      	popl	%eax
  59405c:      	addb	%ch, %bh
  59405e:      	std
  59405f:      	popl	%eax
  594060:      	addb	%bh, %cl
  594062:      	std
  594063:      	popl	%eax
  594064:      	addb	%al, (%ebx)
  594066:      	<unknown>
  594069:      	orl	$0x170058fe, %eax       # imm = 0x170058FE
  59406e:      	<unknown>
  594071:      	andl	%edi, %esi
  594073:      	popl	%eax
  594074:      	addb	%ch, (%ebx)
  594076:      	<unknown>
  594079:      	xorl	$0x3f0058fe, %eax       # imm = 0x3F0058FE
  59407e:      	<unknown>
  594081:      	decl	%ecx
  594082:      	<unknown>
  594085:      	pushl	%ebx
  594086:      	<unknown>
  594089:      	popl	%ebp
  59408a:      	<unknown>
  59408d:      	<unknown>
  594091:      	jno	0x594091 <.text+0x193091>
  594093:      	popl	%eax
  594094:      	addb	%bh, -0x2(%ebx)
  594097:      	popl	%eax
  594098:      	addb	%al, -0x70ffa702(%ebp)
  59409e:      	<unknown>
  5940a1:      	cltd
  5940a2:      	<unknown>
  5940a5:      	movl	%eax, 0xad0058fe
  5940aa:      	<unknown>
  5940ad:      	movb	$-0x2, %bh
  5940af:      	popl	%eax
  5940b0:      	addb	%al, %cl
  5940b2:      	<unknown>
  5940b5:      	lretl
  5940b6:      	<unknown>
  5940b9:      	aad	$-0x2
  5940bb:      	popl	%eax
  5940bc:      	addb	%bl, %bh
  5940be:      	<unknown>
  5940c1:      	jmp	0xf35999c4
  5940c6:      	<unknown>
  5940c9:      	std
  5940ca:      	<unknown>
  5940cd:      	popl	%es
  5940ce:      	lcalll	*(%eax)
  5940d1:      	adcl	%edi, %edi
  5940d3:      	popl	%eax
  5940d4:      	addb	%bl, (%ebx)
  5940d6:      	lcalll	*(%eax)
  5940d9:      	andl	$0x2f0058ff, %eax       # imm = 0x2F0058FF
  5940de:      	lcalll	*(%eax)
  5940e1:      	cmpl	%edi, %edi
  5940e3:      	popl	%eax
  5940e4:      	addb	%al, -0x1(%ebx)
  5940e7:      	popl	%eax
  5940e8:      	addb	%cl, -0x1(%ebp)
  5940eb:      	popl	%eax
  5940ec:      	addb	%dl, -0x1(%edi)
  5940ef:      	popl	%eax
  5940f0:      	addb	%ah, -0x1(%ecx)
  5940f3:      	popl	%eax
  5940f4:      	addb	%ch, -0x1(%ebx)
  5940f7:      	popl	%eax
  5940f8:      	addb	%dh, -0x1(%ebp)
  5940fb:      	popl	%eax
  5940fc:      	addb	%bh, -0x1(%edi)
  5940ff:      	popl	%eax
  594100:      	addb	%cl, -0x6cffa701(%ecx)
  594106:      	lcalll	*(%eax)
  594109:      	popfl
  59410a:      	lcalll	*(%eax)
  59410d:      	cmpsl	%es:(%edi), (%esi)
  59410e:      	lcalll	*(%eax)
  594111:      	movb	$-0x1, %cl
  594113:      	popl	%eax
  594114:      	addb	%bh, -0x3affa701(%ebx)
  59411a:      	lcalll	*(%eax)
  59411d:      	iretl
  59411e:      	lcalll	*(%eax)
  594121:      	fcos
  594123:      	popl	%eax
  594124:      	addb	%ah, %bl
  594126:      	lcalll	*(%eax)
  594129:      	inl	%dx, %eax
  59412a:      	lcalll	*(%eax)
  59412d:      	idivl	%edi
  59412f:      	popl	%eax
  594130:      	addb	%al, (%ecx)
  594132:      	addb	%bl, (%ecx)
  594135:      	xorl	(%eax), %eax
  594137:      	popl	%ecx
  594138:      	addb	%bh, 0x47005900
  59413e:      	addb	%bl, (%ecx)
  594141:      	pushl	%ecx
  594142:      	addb	%bl, (%ecx)
  594145:      	addb	%bl, %gs:(%ecx)
  594149:      	outsl	(%esi), %dx
  59414a:      	addb	%bl, (%ecx)
  59414d:      	jns	0x59414f <.text+0x19314f>
  59414f:      	popl	%ecx
  594150:      	addb	%al, -0x72ffa700(%ebx)
  594156:      	addb	%bl, (%ecx)
  594159:      	xchgl	%edi, %eax
  59415a:      	addb	%bl, (%ecx)
  59415d:      	movl	0xab005900, %eax
  594162:      	addb	%bl, (%ecx)
  594165:      	movb	$0x0, %ch
  594167:      	popl	%ecx
  594168:      	addb	%bh, -0x36ffa700(%edi)
  59416e:      	addb	%bl, (%ecx)
  594171:      	roll	%cl, (%eax)
  594173:      	popl	%ecx
  594174:      	addb	%bl, %ch
  594176:      	addb	%bl, (%ecx)
  594179:      	outl	%eax, $0x0
  59417b:      	popl	%ecx
  59417c:      	addb	%dh, %cl
  59417e:      	addb	%bl, (%ecx)
  594181:      	sti
  594182:      	addb	%bl, (%ecx)
  594185:      	addl	$0xf005901, %eax        # imm = 0xF005901
  59418a:      	addl	%ebx, (%ecx)
  59418d:      	sbbl	%eax, (%ecx)
  59418f:      	popl	%ecx
  594190:      	addb	%ah, (%ebx)
  594192:      	addl	%ebx, (%ecx)
  594195:      	subl	$0x37005901, %eax       # imm = 0x37005901
  59419a:      	addl	%ebx, (%ecx)
  59419d:      	incl	%ecx
  59419e:      	addl	%ebx, (%ecx)
  5941a1:      	decl	%ebx
  5941a2:      	addl	%ebx, (%ecx)
  5941a5:      	pushl	%ebp
  5941a6:      	addl	%ebx, (%ecx)
  5941a9:      	popl	%edi
  5941aa:      	addl	%ebx, (%ecx)
  5941ad:      	imull	$0x1730059, (%ecx), %eax # imm = 0x1730059
  5941b3:      	popl	%ecx
  5941b4:      	addb	%bh, 0x1(%ebp)
  5941b7:      	popl	%ecx
  5941b8:      	addb	%al, -0x6effa6ff(%edi)
  5941be:      	addl	%ebx, (%ecx)
  5941c1:      	wait
  5941c2:      	addl	%ebx, (%ecx)
  5941c5:      	movsl	(%esi), %es:(%edi)
  5941c6:      	addl	%ebx, (%ecx)
  5941c9:      	scasl	%es:(%edi), %eax
  5941ca:      	addl	%ebx, (%ecx)
  5941cd:      	movl	$0xc3005901, %ecx       # imm = 0xC3005901
  5941d2:      	addl	%ebx, (%ecx)
  5941d5:      	int	$0x1
  5941d7:      	popl	%ecx
  5941d8:      	addb	%dl, %bh
  5941da:      	addl	%ebx, (%ecx)
  5941dd:      	loope	0x5941e0 <.text+0x1931e0>
  5941df:      	popl	%ecx
  5941e0:      	addb	%ch, %bl
  5941e2:      	addl	%ebx, (%ecx)
  5941e5:      	cmc
  5941e6:      	addl	%ebx, (%ecx)
  5941e9:      	incl	(%ecx)
  5941eb:      	popl	%ecx
  5941ec:      	addb	%cl, (%ecx)
  5941ee:      	addb	(%ecx), %bl
  5941f1:      	adcl	(%edx), %eax
  5941f3:      	popl	%ecx
  5941f4:      	addb	%bl, 0x27005902
  5941fa:      	addb	(%ecx), %bl
  5941fd:      	xorl	%eax, (%edx)
  5941ff:      	popl	%ecx
  594200:      	addb	%bh, (%ebx)
  594202:      	addb	(%ecx), %bl
  594205:      	incl	%ebp
  594206:      	addb	(%ecx), %bl
  594209:      	decl	%edi
  59420a:      	addb	(%ecx), %bl
  59420d:      	popl	%ecx
  59420e:      	addb	(%ecx), %bl
  594211:      	arpl	%ax, (%edx)
  594213:      	popl	%ecx
  594214:      	addb	%ch, 0x2(%ebp)
  594217:      	popl	%ecx
  594218:      	addb	%dh, 0x2(%edi)
  59421b:      	popl	%ecx
  59421c:      	addb	%al, -0x74ffa6fe(%ecx)
  594222:      	addb	(%ecx), %bl
  594225:      	xchgl	%ebp, %eax
  594226:      	addb	(%ecx), %bl
  594229:      	lahf
  59422a:      	addb	(%ecx), %bl
  59422d:      	testl	$0xb3005902, %eax       # imm = 0xB3005902
  594232:      	addb	(%ecx), %bl
  594235:      	outl	%eax, %dx
  594236:      	addb	(%ecx), %bl
  594239:      	stc
  59423a:      	addb	(%ecx), %bl
  59423d:      	addl	(%ebx), %eax
  59423f:      	popl	%ecx
  594240:      	addb	%cl, 0x17005903
  594246:      	addl	(%ecx), %ebx
  594249:      	andl	%eax, (%ebx)
  59424b:      	popl	%ecx
  59424c:      	addb	%ch, (%ebx)
  59424e:      	addl	(%ecx), %ebx
  594251:      	xorl	$0x3f005903, %eax       # imm = 0x3F005903
  594256:      	addl	(%ecx), %ebx
  594259:      	decl	%ecx
  59425a:      	addl	(%ecx), %ebx
  59425d:      	pushl	%ss
  59425e:      	sbbb	(%ecx), %bl
  594261:      	pushl	%ss
  594262:      	sbbb	(%ecx), %bl
  594265:      	pushl	%ss
  594266:      	sbbb	(%ecx), %bl
  594269:      	pushl	%ss
  59426a:      	sbbb	(%ecx), %bl
  59426d:      	pushl	%ss
  59426e:      	sbbb	(%ecx), %bl
  594271:      	pushl	%ebx
  594272:      	addl	(%ecx), %ebx
  594275:      	popl	%ebp
  594276:      	addl	(%ecx), %ebx
  594279:      	addl	(%bx,%di), %ebx
  59427d:      	movl	$0xc9005903, %edi       # imm = 0xC9005903
  594282:      	addl	(%ecx), %ebx
  594285:      	roll	%cl, (%ebx)
  594287:      	popl	%ecx
  594288:      	addb	%bl, %ch
  59428a:      	addl	(%ecx), %ebx
  59428d:      	outl	%eax, $0x3
  59428f:      	popl	%ecx
  594290:      	addb	%dh, %cl
  594292:      	addl	(%ecx), %ebx
  594295:      	sti
  594296:      	addl	(%ecx), %ebx
  594299:      	addl	$0xf005904, %eax        # imm = 0xF005904
  59429e:      	addb	$0x59, %al
  5942a0:      	addb	%bl, (%ecx)
  5942a2:      	addb	$0x59, %al
  5942a4:      	addb	%ah, (%ebx)
  5942a6:      	addb	$0x59, %al
  5942a8:      	addb	%ch, 0x37005904
  5942ae:      	addb	$0x59, %al
  5942b0:      	addb	%al, 0x4(%ecx)
  5942b3:      	popl	%ecx
  5942b4:      	addb	%cl, 0x4(%ebx)
  5942b7:      	popl	%ecx
  5942b8:      	addb	%dl, 0x4(%ebp)
  5942bb:      	popl	%ecx
  5942bc:      	addb	%bl, 0x4(%edi)
  5942bf:      	popl	%ecx
  5942c0:      	addb	%ch, 0x4(%ecx)
  5942c3:      	popl	%ecx
  5942c4:      	addb	%dh, 0x4(%ebx)
  5942c7:      	popl	%ecx
  5942c8:      	addb	%bh, 0x4(%ebp)
  5942cb:      	popl	%ecx
  5942cc:      	addb	%al, -0x6effa6fc(%edi)
  5942d2:      	addb	$0x59, %al
  5942d4:      	addb	%bl, -0x5affa6fc(%ebx)
  5942da:      	addb	$0x59, %al
  5942dc:      	addb	%ch, -0x46ffa6fc(%edi)
  5942e2:      	addb	$0x59, %al
  5942e4:      	addb	%al, %bl
  5942e6:      	addb	$0x59, %al
  5942e8:      	addb	%cl, %ch
  5942ea:      	addb	$0x59, %al
  5942ec:      	addb	%dl, %bh
  5942ee:      	addb	$0x59, %al
  5942f0:      	addb	%ah, %cl
  5942f2:      	addb	$0x59, %al
  5942f4:      	addb	%ch, %bl
  5942f6:      	addb	$0x59, %al
  5942f8:      	addb	%dh, %ch
  5942fa:      	addb	$0x59, %al
  5942fc:      	addb	%bh, %bh
  5942fe:      	addb	$0x59, %al
  594300:      	addb	%cl, (%ecx)
  594302:      	addl	$0x8150059, %eax        # imm = 0x8150059
  594307:      	popl	%ecx
  594308:      	addb	%bl, (%edi)
  59430a:      	orb	%bl, (%ecx)
  59430d:      	subl	%ecx, (%eax)
  59430f:      	popl	%ecx
  594310:      	addb	%dl, (%ebx)
  594312:      	addl	$0x51d0059, %eax        # imm = 0x51D0059
  594317:      	popl	%ecx
  594318:      	addb	%ah, (%edi)
  59431a:      	addl	$0x5310059, %eax        # imm = 0x5310059
  59431f:      	popl	%ecx
  594320:      	addb	%bh, (%ebx)
  594322:      	addl	$0x5450059, %eax        # imm = 0x5450059
  594327:      	popl	%ecx
  594328:      	addb	%cl, 0x5(%edi)
  59432b:      	popl	%ecx
  59432c:      	addb	%bl, 0x5(%ecx)
  59432f:      	popl	%ecx
  594330:      	addb	%ah, 0x5(%ebx)
  594333:      	popl	%ecx
  594334:      	addb	%ch, 0x5(%ebp)
  594337:      	popl	%ecx
  594338:      	addb	%dh, 0x5(%edi)
  59433b:      	popl	%ecx
  59433c:      	addb	%al, -0x74ffa6fb(%ecx)
  594342:      	addl	$0x5950059, %eax        # imm = 0x5950059
  594347:      	popl	%ecx
  594348:      	addb	%bl, -0x56ffa6fb(%edi)
  59434e:      	addl	$0x5b30059, %eax        # imm = 0x5B30059
  594353:      	popl	%ecx
  594354:      	addb	%bh, -0x38ffa6fb(%ebp)
  59435a:      	addl	$0x5d10059, %eax        # imm = 0x5D10059
  59435f:      	popl	%ecx
  594360:      	addb	%bl, %bl
  594362:      	addl	$0x5e50059, %eax        # imm = 0x5E50059
  594367:      	popl	%ecx
  594368:      	addb	%ch, %bh
  59436a:      	addl	$0x5f90059, %eax        # imm = 0x5F90059
  59436f:      	popl	%ecx
  594370:      	addb	%dl, (%esi)
  594372:      	sbbb	(%ecx), %bl
  594375:      	addb	%al, (%ecx)
  594377:      	addb	(%ebx), %al
  594379:      	addb	$0x3d, %al
  59437b:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594380:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594385:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59438a:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59438f:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594394:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594399:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59439e:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943a3:      	cmpl	$0x6053d3d, %eax        # imm = 0x6053D3D
  5943a8:      	popl	%es
  5943a9:      	orb	%cl, (%ecx)
  5943ab:      	orb	(%ebx), %cl
  5943ad:      	orb	$0xd, %al
  5943af:      	pushl	%cs
  5943b0:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943b5:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943ba:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943bf:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943c4:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943c9:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943ce:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943d3:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943d8:      	movups	(%ecx), %xmm2
  5943db:      	adcb	(%ebx), %dl
  5943dd:      	adcb	$0x15, %al
  5943df:      	pushl	%ss
  5943e0:      	popl	%ss
  5943e1:      	sbbb	%bl, (%ecx)
  5943e3:      	sbbb	(%ebx), %bl
  5943e5:      	sbbb	$0x1d, %al
  5943e7:      	pushl	%ds
  5943e8:      	popl	%ds
  5943e9:      	andb	%ah, (%ecx)
  5943eb:      	andb	(%ebx), %ah
  5943ed:      	andb	$0x3d, %al
  5943ef:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943f4:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943f9:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  5943fe:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594403:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594408:      	cmpl	$0x2726253d, %eax       # imm = 0x2726253D
  59440d:      	subb	%ch, (%ecx)
  59440f:      	subb	0x3d3d3d3d, %bh
  594415:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59441a:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59441f:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594424:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594429:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  59442e:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594433:      	cmpl	$0x3d3d3d3d, %eax       # imm = 0x3D3D3D3D
  594438:      	cmpl	$0x2b3d3d3d, %eax       # imm = 0x2B3D3D3D
  59443d:      	subb	$0x2d, %al
  59443f:      	das
  594441:      	xorb	%dh, (%ecx)
  594443:      	xorb	(%ebx), %dh
  594445:      	xorb	$0x35, %al
  594447:      	aaa
  594449:      	cmpb	%bh, (%ecx)
  59444b:      	cmpb	(%ebx), %bh
  59444d:      	cmpb	$-0x73, %al
  59444f:      	decl	%ecx
  594450:      	addb	%dh, 0x6(%ecx)
  594453:      	popl	%ecx
  594454:      	addb	%bh, 0x6(%ebx)
  594457:      	popl	%ecx
  594458:      	addb	%al, -0x70ffa6fa(%ebp)
  59445e:      	pushl	%es
  59445f:      	popl	%ecx
  594460:      	addb	%bl, -0x5cffa6fa(%ecx)
  594466:      	pushl	%es
  594467:      	popl	%ecx
  594468:      	addb	%ch, -0x48ffa6fa(%ebp)
  59446e:      	pushl	%es
  59446f:      	popl	%ecx
  594470:      	addb	%al, %cl
  594472:      	pushl	%es
  594473:      	popl	%ecx
  594474:      	addb	%cl, %bl
  594476:      	pushl	%es
  594477:      	popl	%ecx
  594478:      	addb	%dl, %ch
  59447a:      	pushl	%es
  59447b:      	popl	%ecx
  59447c:      	addb	%bl, %bh
  59447e:      	pushl	%es
  59447f:      	popl	%ecx
  594480:      	addb	%ch, %cl
  594482:      	pushl	%es
  594483:      	popl	%ecx
  594484:      	addb	%dh, %bl
  594486:      	pushl	%es
  594487:      	popl	%ecx
  594488:      	addb	%dl, (%esi)
  59448a:      	sbbb	(%ecx), %bl
  59448d:      	addb	%cl, (%esi)
  59448f:      	pushl	%cs
  594490:      	pushl	%cs
  594491:      	pushl	%cs
  594492:      	addl	%ecx, (%esi)
  594494:      	pushl	%cs
  594495:      	pushl	%cs
  594496:      	addb	(%ebx), %al
  594498:      	pushl	%cs
  594499:      	pushl	%cs
  59449a:      	pushl	%cs
  59449b:      	pushl	%cs
  59449c:      	pushl	%cs
  59449d:      	pushl	%cs
  59449e:      	pushl	%cs
  59449f:      	addb	$0xe, %al
  5944a1:      	addl	$0xe0e0e0e, %eax        # imm = 0xE0E0E0E
  5944a6:      	pushl	%cs
  5944a7:      	pushl	%cs
  5944a8:      	pushl	%cs
  5944a9:      	pushl	%cs
  5944aa:      	pushl	%cs
  5944ab:      	pushl	%cs
  5944ac:      	pushl	%es
  5944ad:      	popl	%es
  5944ae:      	orb	%cl, (%ecx)
  5944b0:      	orb	(%ebx), %cl
  5944b2:      	orb	$0xd, %al
  5944b4:      	nop
  5944b5:      	popl	%es
  5944b6:      	popl	%es
  5944b7:      	popl	%ecx
  5944b8:      	addb	%dl, (%ecx)
  5944ba:      	popl	%es
  5944bb:      	popl	%ecx
  5944bc:      	addb	%bl, (%ebx)
  5944be:      	popl	%es
  5944bf:      	popl	%ecx
  5944c0:      	addb	%ah, 0x2f005907
  5944c6:      	popl	%es
  5944c7:      	popl	%ecx
  5944c8:      	addb	%bh, (%ecx)
  5944ca:      	popl	%es
  5944cb:      	popl	%ecx
  5944cc:      	addb	%al, 0x7(%ebx)
  5944cf:      	popl	%ecx
  5944d0:      	addb	%cl, 0x7(%ebp)
  5944d3:      	popl	%ecx
  5944d4:      	addb	%dl, 0x7(%edi)
  5944d7:      	popl	%ecx
  5944d8:      	addb	%ah, 0x7(%ecx)
  5944db:      	popl	%ecx
  5944dc:      	addb	%ch, 0x7(%ebx)
  5944df:      	popl	%ecx
  5944e0:      	addb	%dh, 0x7(%ebp)
  5944e3:      	popl	%ecx
  5944e4:      	addb	%bh, 0x7(%edi)
  5944e7:      	popl	%ecx
  5944e8:      	addb	%cl, -0x6cffa6f9(%ecx)
  5944ee:      	popl	%es
  5944ef:      	popl	%ecx
  5944f0:      	addb	%bl, -0x58ffa6f9(%ebp)
  5944f6:      	popl	%es
  5944f7:      	popl	%ecx
  5944f8:      	addb	%dh, -0x44ffa6f9(%ecx)
  5944fe:      	popl	%es
  5944ff:      	popl	%ecx
  594500:      	addb	%al, %ch
  594502:      	popl	%es
  594503:      	popl	%ecx
  594504:      	addb	%cl, %bh
  594506:      	popl	%es
  594507:      	popl	%ecx
  594508:      	addb	%bl, %cl
  59450a:      	popl	%es
  59450b:      	popl	%ecx
  59450c:      	addb	%ah, %bl
  59450e:      	popl	%es
  59450f:      	popl	%ecx
  594510:      	addb	%ch, %ch
  594512:      	popl	%es
  594513:      	popl	%ecx
  594514:      	addb	%dh, %bh
  594516:      	popl	%es
  594517:      	popl	%ecx
  594518:      	addb	%al, (%ecx)
  59451a:      	orb	%bl, (%ecx)
  59451d:      	orl	(%eax), %ecx
  59451f:      	popl	%ecx
  594520:      	addb	%bl, 0x8(%ebx)
  594523:      	popl	%ecx
  594524:      	addb	%dh, 0x16005908(%ebx)
  59452a:      	sbbb	(%ecx), %bl
  59452d:      	addb	%al, (%ecx)
  59452f:      	addb	(%ebx), %al
  594531:      	addb	$0x5, %al
  594533:      	pushl	%es
  594534:      	popl	%es
  594535:      	orb	%cl, (%ecx)
  594537:      	orb	(%ebx), %cl
  594539:      	orb	$0xd, %al
  59453b:      	pushl	%cs
  59453c:      	movups	(%ecx), %xmm2
  59453f:      	adcb	(%ebx), %dl
  594541:      	adcb	$0x15, %al
  594543:      	pushl	%ss
  594544:      	popl	%ss
  594545:      	sbbb	%bl, (%ecx)
  594547:      	sbbb	(%ebx), %bl
  594549:      	sbbl	$0x1d1d1d1d, %eax       # imm = 0x1D1D1D1D
  59454e:      	sbbl	$0x1d1d1d1d, %eax       # imm = 0x1D1D1D1D
  594553:      	sbbl	$0x1d1d1d1d, %eax       # imm = 0x1D1D1D1D
  594558:      	sbbl	$0x1c1d1d1d, %eax       # imm = 0x1C1D1D1D
  59455d:      	pushl	$0x72005909             # imm = 0x72005909
  594562:      	orl	%ebx, (%ecx)
  594565:      	jl	0x594570 <.text+0x193570>
  594567:      	popl	%ecx
  594568:      	addb	%al, -0x6fffa6f7(%esi)
  59456e:      	orl	%ebx, (%ecx)
  594571:      	lcalll	$0x5909, $0xa4005909    # imm = 0x5909
                                                # imm = 0xA4005909
  594578:      	addb	%ch, -0x47ffa6f7(%esi)
  59457e:      	orl	%ebx, (%ecx)
  594581:      	retl	$0x5909                 # imm = 0x5909
  594584:      	addb	%cl, %ah
  594586:      	orl	%ebx, (%ecx)
  594589:      	salc
  59458a:      	orl	%ebx, (%ecx)
  59458d:      	orb	%cl, (%edx)
  59458f:      	popl	%ecx
  594590:      	addb	%dl, (%edx)
  594592:      	orb	(%ecx), %bl
  594595:      	orb	%es:(%ecx), %bl
  594599:      	xorb	%cl, (%edx)
  59459b:      	popl	%ecx
  59459c:      	addb	%bh, (%edx)
  59459e:      	orb	(%ecx), %bl
  5945a1:      	incl	%esp
  5945a2:      	orb	(%ecx), %bl
  5945a5:      	decl	%esi
  5945a6:      	orb	(%ecx), %bl
  5945a9:      	popl	%eax
  5945aa:      	orb	(%ecx), %bl
  5945ad:      	bound	%ecx, (%edx)
  5945af:      	popl	%ecx
  5945b0:      	addb	%ch, 0x59(%edx,%ecx)
  5945b4:      	addb	%dh, 0xa(%esi)
  5945b7:      	popl	%ecx
  5945b8:      	addb	%al, -0x75ffa6f6(%eax)
  5945be:      	orb	(%ecx), %bl
  5945c1:      	xchgl	%esp, %eax
  5945c2:      	orb	(%ecx), %bl
  5945c5:      	sahf
  5945c6:      	orb	(%ecx), %bl
  5945c9:      	<unknown>
  5945cb:      	popl	%ecx
  5945cc:      	addb	%dl, %cl
  5945ce:      	orb	(%ecx), %bl
  5945d1:      	fisttpl	(%edx)
  5945d3:      	popl	%ecx
  5945d4:      	addb	%ah, %ch
  5945d6:      	orb	(%ecx), %bl
  5945d9:      	outl	%eax, %dx
  5945da:      	orb	(%ecx), %bl
  5945dd:      	stc
  5945de:      	orb	(%ecx), %bl
  5945e1:      	addl	(%ebx), %ecx
  5945e3:      	popl	%ecx
  5945e4:      	addb	%cl, 0x1700590b
  5945ea:      	orl	(%ecx), %ebx
  5945ed:      	andl	%ecx, (%ebx)
  5945ef:      	popl	%ecx
  5945f0:      	addb	%ch, (%ebx)
  5945f2:      	orl	(%ecx), %ebx
  5945f5:      	xorl	$0x3f00590b, %eax       # imm = 0x3F00590B
  5945fa:      	orl	(%ecx), %ebx
  5945fd:      	insl	%dx, %es:(%edi)
  5945fe:      	orl	(%ecx), %ebx
  594601:      	ja	0x59460e <.text+0x19360e>
  594603:      	popl	%ecx
  594604:      	addb	%al, 0x3600590b(%ecx)
  59460a:      	orb	$0x59, %al
  59460c:      	addb	%al, 0xc(%eax)
  59460f:      	popl	%ecx
  594610:      	addb	%cl, 0xc(%edx)
  594613:      	popl	%ecx
  594614:      	addb	%dl, 0x59(%esp,%ecx)
  594618:      	addb	%bl, 0xc(%esi)
  59461b:      	popl	%ecx
  59461c:      	addb	%ch, 0xc(%eax)
  59461f:      	popl	%ecx
  594620:      	addb	%dh, 0xc(%edx)
  594623:      	popl	%ecx
  594624:      	addb	%bh, 0x59(%esp,%ecx)
  594628:      	addb	%al, -0x6fffa6f4(%esi)
  59462e:      	orb	$0x59, %al
  594630:      	addb	%bl, 0x1600590c(%edx)
  594636:      	sbbb	(%ecx), %bl
  594639:      	movsb	(%esi), %es:(%edi)
  59463a:      	orb	$0x59, %al
  59463c:      	addb	%dl, (%esi)
  59463e:      	sbbb	(%ecx), %bl
  594641:      	scasb	%es:(%edi), %al
  594642:      	orb	$0x59, %al
  594644:      	addb	%bh, -0x33ffa6f4(%eax)
  59464a:      	orb	$0x59, %al
  59464c:      	addb	%dl, %dh
  59464e:      	orb	$0x59, %al
  594650:      	addb	%ah, %al
  594652:      	orb	$0x59, %al
  594654:      	addb	%ch, %dl
  594656:      	orb	$0x59, %al
  594658:      	addb	%dh, %ah
  59465a:      	orb	$0x59, %al
  59465c:      	addb	%bh, %dh
  59465e:      	orb	$0x59, %al
  594660:      	addb	%cl, (%eax)
  594662:      	orl	$0xd120059, %eax        # imm = 0xD120059
  594667:      	popl	%ecx
  594668:      	addb	%bl, 0xd260059(,%ecx)
  59466f:      	popl	%ecx
  594670:      	addb	%dh, (%eax)
  594672:      	orl	$0xd3a0059, %eax        # imm = 0xD3A0059
  594677:      	popl	%ecx
  594678:      	addb	%al, 0x59(%ebp,%ecx)
  59467c:      	addb	%cl, 0xd(%esi)
  59467f:      	popl	%ecx
  594680:      	addb	%bl, 0xd(%eax)
  594683:      	popl	%ecx
  594684:      	addb	%ah, 0xd(%edx)
  594687:      	popl	%ecx
  594688:      	addb	%ch, 0x59(%ebp,%ecx)
  59468c:      	addb	%dh, 0xd(%esi)
  59468f:      	popl	%ecx
  594690:      	addb	%al, -0x75ffa6f3(%eax)
  594696:      	orl	$0xd940059, %eax        # imm = 0xD940059
  59469b:      	popl	%ecx
  59469c:      	addb	%bl, -0x57ffa6f3(%esi)
  5946a2:      	orl	$0xdb20059, %eax        # imm = 0xDB20059
  5946a7:      	popl	%ecx
  5946a8:      	addb	%bh, 0xdee0059(%ebp,%ecx)
  5946af:      	popl	%ecx
  5946b0:      	addb	%bh, %al
  5946b2:      	orl	$0xe020059, %eax        # imm = 0xE020059
  5946b7:      	popl	%ecx
  5946b8:      	addb	%cl, (%esi,%ecx)
  5946bb:      	popl	%ecx
  5946bc:      	addb	%ah, (%eax)
  5946be:      	pushl	%cs
  5946bf:      	popl	%ecx
  5946c0:      	addb	%ch, (%edx)
  5946c2:      	pushl	%cs
  5946c3:      	popl	%ecx
  5946c4:      	addb	%dh, (%esi,%ecx)
  5946c7:      	popl	%ecx
  5946c8:      	addb	%bh, (%esi)
  5946ca:      	pushl	%cs
  5946cb:      	popl	%ecx
  5946cc:      	addb	%cl, 0xe(%eax)
  5946cf:      	popl	%ecx
  5946d0:      	addb	%dl, 0xe(%edx)
  5946d3:      	popl	%ecx
  5946d4:      	addb	%bl, 0x59(%esi,%ecx)
  5946d8:      	addb	%ah, 0xe(%esi)
  5946db:      	popl	%ecx
  5946dc:      	addb	%dh, 0xe(%eax)
  5946df:      	popl	%ecx
  5946e0:      	addb	%bh, 0xe(%edx)
  5946e3:      	popl	%ecx
  5946e4:      	addb	%al, 0xe8e0059(%esi,%ecx)
  5946eb:      	popl	%ecx
  5946ec:      	addb	%bl, -0x5dffa6f2(%eax)
  5946f2:      	pushl	%cs
  5946f3:      	popl	%ecx
  5946f4:      	addb	%ch, 0xeb60059(%esi,%ecx)
  5946fb:      	popl	%ecx
  5946fc:      	addb	%al, %al
  5946fe:      	pushl	%cs
  5946ff:      	popl	%ecx
  594700:      	addb	%cl, %dl
  594702:      	pushl	%cs
  594703:      	popl	%ecx
  594704:      	addb	%dl, %ah
  594706:      	pushl	%cs
  594707:      	popl	%ecx
  594708:      	addb	%bl, %dh
  59470a:      	pushl	%cs
  59470b:      	popl	%ecx
  59470c:      	addb	%ch, %al
  59470e:      	pushl	%cs
  59470f:      	popl	%ecx
  594710:      	addb	%dh, %dl
  594712:      	pushl	%cs
  594713:      	popl	%ecx
  594714:      	addb	%bh, %ah
  594716:      	pushl	%cs
  594717:      	popl	%ecx
  594718:      	addb	%dl, (%esi)
  59471a:      	sbbb	(%ecx), %bl
  59471d:      	pushl	%es
  59471e:      	mulps	(%eax), %xmm0
  594721:      	adcb	%cl, (%edi)
  594723:      	popl	%ecx
  594724:      	addb	%bl, (%edx)
  594726:      	mulps	(%eax), %xmm0
  594729:      	pushl	%esi
  59472a:      	mulps	(%eax), %xmm0
  59472d:      	pushal
  59472e:      	mulps	(%eax), %xmm0
  594731:      	pushl	$0xf
  594733:      	popl	%ecx
  594734:      	addb	%dh, 0x59(%edi,%ecx)
  594738:      	addb	%bh, 0xf(%esi)
  59473b:      	popl	%ecx
  59473c:      	addb	%cl, -0x6dffa6f1(%eax)
  594742:      	mulps	(%eax), %xmm0
  594745:      	pushfl
  594746:      	mulps	(%eax), %xmm0
  594749:      	cmpsb	%es:(%edi), (%esi)
  59474a:      	mulps	(%eax), %xmm0
  59474d:      	movb	$0xf, %al
  59474f:      	popl	%ecx
  594750:      	addb	%bh, -0x3bffa6f1(%edx)
  594756:      	mulps	(%eax), %xmm0
  594759:      	into
  59475a:      	mulps	(%eax), %xmm0
  59475d:      	fmuls	(%edi)
  59475f:      	popl	%ecx
  594760:      	addb	%ah, %dl
  594762:      	mulps	(%eax), %xmm0
  594765:      	inb	%dx, %al
  594766:      	mulps	(%eax), %xmm0
  594769:      	<unknown>
  59476b:      	popl	%ecx
  59476c:      	addb	%al, (%eax)
  59476e:      	adcb	%bl, (%ecx)
  594771:      	orb	(%eax), %dl
  594773:      	popl	%ecx
  594774:      	addb	%dl, (%eax,%edx)
  594777:      	popl	%ecx
  594778:      	addb	%bl, (%esi)
  59477a:      	adcb	%bl, (%ecx)
  59477d:      	subb	%dl, (%eax)
  59477f:      	popl	%ecx
  594780:      	addb	%dh, (%edx)
  594782:      	adcb	%bl, (%ecx)
  594785:      	cmpb	$0x10, %al
  594787:      	popl	%ecx
  594788:      	addb	%al, 0x10(%esi)
  59478b:      	popl	%ecx
  59478c:      	addb	%dl, 0x10(%eax)
  59478f:      	popl	%ecx
  594790:      	addb	%bl, 0x10(%edx)
  594793:      	popl	%ecx
  594794:      	addb	%ah, 0x59(%eax,%edx)
  594798:      	addb	%ch, 0x10(%esi)
  59479b:      	popl	%ecx
  59479c:      	addb	%bh, 0x10(%eax)
  59479f:      	popl	%ecx
  5947a0:      	addb	%al, -0x73ffa6f0(%edx)
  5947a6:      	adcb	%bl, (%ecx)
  5947a9:      	xchgl	%esi, %eax
  5947aa:      	adcb	%bl, (%ecx)
  5947ad:      	movb	0xaa005910, %al
  5947b2:      	adcb	%bl, (%ecx)
  5947b5:      	movb	$0x10, %ah
  5947b7:      	popl	%ecx
  5947b8:      	addb	%bh, -0x37ffa6f0(%esi)
  5947be:      	adcb	%bl, (%ecx)
  5947c1:      	rclb	%cl, (%eax)
  5947c3:      	popl	%ecx
  5947c4:      	addb	%bl, %ah
  5947c6:      	adcb	%bl, (%ecx)
  5947c9:      	outb	%al, $0x10
  5947cb:      	popl	%ecx
  5947cc:      	addb	%dh, %al
  5947ce:      	adcb	%bl, (%ecx)
  5947d1:      	cli
  5947d2:      	adcb	%bl, (%ecx)
  5947d5:      	addb	$0x11, %al
  5947d7:      	popl	%ecx
  5947d8:      	addb	%cl, (%esi)
  5947da:      	adcl	%ebx, (%ecx)
  5947dd:      	sbbb	%dl, (%ecx)
  5947df:      	popl	%ecx
  5947e0:      	addb	%ah, (%edx)
  5947e2:      	adcl	%ebx, (%ecx)
  5947e5:      	subb	$0x11, %al
  5947e7:      	popl	%ecx
  5947e8:      	addb	%dh, (%esi)
  5947ea:      	adcl	%ebx, (%ecx)
  5947ed:      	incl	%eax
  5947ee:      	adcl	%ebx, (%ecx)
  5947f1:      	decl	%edx
  5947f2:      	adcl	%ebx, (%ecx)
  5947f5:      	pushl	%esp
  5947f6:      	adcl	%ebx, (%ecx)
  5947f9:      	popl	%esi
  5947fa:      	adcl	%ebx, (%ecx)
  5947fd:      	pushl	$0x72005911             # imm = 0x72005911
  594802:      	adcl	%ebx, (%ecx)
  594805:      	jl	0x594818 <.text+0x193818>
  594807:      	popl	%ecx
  594808:      	addb	%al, -0x6fffa6ef(%esi)
  59480e:      	adcl	%ebx, (%ecx)
  594811:      	lcalll	$0x5911, $0xa4005911    # imm = 0x5911
                                                # imm = 0xA4005911
  594818:      	addb	%ch, -0x47ffa6ef(%esi)
  59481e:      	adcl	%ebx, (%ecx)
  594821:      	retl	$0x5911                 # imm = 0x5911
  594824:      	addb	%cl, %ah
  594826:      	adcl	%ebx, (%ecx)
  594829:      	salc
  59482a:      	adcl	%ebx, (%ecx)
  59482d:      	loopne	0x594840 <.text+0x193840>
  59482f:      	popl	%ecx
  594830:      	addb	%ch, %dl
  594832:      	adcl	%ebx, (%ecx)
  594835:      	hlt
  594836:      	adcl	%ebx, (%ecx)
  594839:      	<unknown>
  59483b:      	popl	%ecx
  59483c:      	addb	%cl, (%eax)
  59483e:      	adcb	(%ecx), %bl
  594841:      	adcb	(%edx), %dl
  594843:      	popl	%ecx
  594844:      	addb	%bl, (%edx,%edx)
  594847:      	popl	%ecx
  594848:      	addb	%ah, (%esi)
  59484a:      	adcb	(%ecx), %bl
  59484d:      	xorb	%dl, (%edx)
  59484f:      	popl	%ecx
  594850:      	addb	%bh, (%edx)
  594852:      	adcb	(%ecx), %bl
  594855:      	incl	%esp
  594856:      	adcb	(%ecx), %bl
  594859:      	decl	%esi
  59485a:      	adcb	(%ecx), %bl
  59485d:      	popl	%eax
  59485e:      	adcb	(%ecx), %bl
  594861:      	bound	%edx, (%edx)
  594863:      	popl	%ecx
  594864:      	addb	%ch, 0x59(%edx,%edx)
  594868:      	addb	%dh, 0x12(%esi)
  59486b:      	popl	%ecx
  59486c:      	addb	%cl, -0x6b(%ecx)
  59486f:      	popl	%eax
  594870:      	addb	%dl, -0x6b(%ebx)
  594873:      	popl	%eax
  594874:      	addb	%bl, -0x6b(%ebp)
  594877:      	popl	%eax
  594878:      	addb	%ah, -0x6b(%edi)
  59487b:      	popl	%eax
  59487c:      	addb	%dh, -0x6b(%ecx)
  59487f:      	popl	%eax
  594880:      	addb	%bh, -0x6b(%ebx)
  594883:      	popl	%eax
  594884:      	addb	%al, -0x70ffa76b(%ebp)
  59488a:      	xchgl	%ebp, %eax
  59488b:      	popl	%eax
  59488c:      	addb	%dl, (%esi)
  59488e:      	sbbb	(%ecx), %bl
  594891:      	pushl	%ss
  594892:      	sbbb	(%ecx), %bl
  594895:      	pushl	%ss
  594896:      	sbbb	(%ecx), %bl
  594899:      	pushl	%ss
  59489a:      	sbbb	(%ecx), %bl
  59489d:      	pushl	%ss
  59489e:      	sbbb	(%ecx), %bl
  5948a1:      	pushl	%ss
  5948a2:      	sbbb	(%ecx), %bl
  5948a5:      	cltd
  5948a6:      	xchgl	%ebp, %eax
  5948a7:      	popl	%eax
  5948a8:      	addb	%ah, -0x20ffa76b(%ebx)
  5948ae:      	xchgl	%ebp, %eax
  5948af:      	popl	%eax
  5948b0:      	addb	%ch, %cl
  5948b2:      	xchgl	%ebp, %eax
  5948b3:      	popl	%eax
  5948b4:      	addb	%dh, %bl
  5948b6:      	xchgl	%ebp, %eax
  5948b7:      	popl	%eax
  5948b8:      	addb	%bh, %ch
  5948ba:      	xchgl	%ebp, %eax
  5948bb:      	popl	%eax
  5948bc:      	addb	%al, (%edi)
  5948be:      	xchgl	%esi, %eax
  5948bf:      	popl	%eax
  5948c0:      	addb	%dl, (%ecx)
  5948c2:      	xchgl	%esi, %eax
  5948c3:      	popl	%eax
  5948c4:      	addb	%bl, (%ebx)
  5948c6:      	xchgl	%esi, %eax
  5948c7:      	popl	%eax
  5948c8:      	addb	%ah, 0x2f005896
  5948ce:      	xchgl	%esi, %eax
  5948cf:      	popl	%eax
  5948d0:      	addb	%bh, (%ecx)
  5948d2:      	xchgl	%esi, %eax
  5948d3:      	popl	%eax
  5948d4:      	addb	%al, -0x6a(%ebx)
  5948d7:      	popl	%eax
  5948d8:      	addb	%cl, -0x6a(%ebp)
  5948db:      	popl	%eax
  5948dc:      	addb	%dl, -0x6a(%edi)
  5948df:      	popl	%eax
  5948e0:      	addb	%ah, -0x6a(%ecx)
  5948e3:      	popl	%eax
  5948e4:      	addb	%ch, -0x6a(%ebx)
  5948e7:      	popl	%eax
  5948e8:      	addb	%dh, -0x6a(%ebp)
  5948eb:      	popl	%eax
  5948ec:      	addb	%bh, -0x6a(%edi)
  5948ef:      	popl	%eax
  5948f0:      	addb	%cl, -0x6cffa76a(%ecx)
  5948f6:      	xchgl	%esi, %eax
  5948f7:      	popl	%eax
  5948f8:      	addb	%bl, -0x58ffa76a(%ebp)
  5948fe:      	xchgl	%esi, %eax
  5948ff:      	popl	%eax
  594900:      	addb	%dh, -0x44ffa76a(%ecx)
  594906:      	xchgl	%esi, %eax
  594907:      	popl	%eax
  594908:      	addb	%al, %ch
  59490a:      	xchgl	%esi, %eax
  59490b:      	popl	%eax
  59490c:      	addb	%cl, %bh
  59490e:      	xchgl	%esi, %eax
  59490f:      	popl	%eax
  594910:      	addb	%bl, %cl
  594912:      	xchgl	%esi, %eax
  594913:      	popl	%eax
  594914:      	addb	%ah, %bl
  594916:      	xchgl	%esi, %eax
  594917:      	popl	%eax
  594918:      	addb	%ch, %ch
  59491a:      	xchgl	%esi, %eax
  59491b:      	popl	%eax
  59491c:      	addb	%dh, %bh
  59491e:      	xchgl	%esi, %eax
  59491f:      	popl	%eax
  594920:      	addb	%al, (%ecx)
  594922:      	xchgl	%edi, %eax
  594923:      	popl	%eax
  594924:      	addb	%cl, (%ebx)
  594926:      	xchgl	%edi, %eax
  594927:      	popl	%eax
  594928:      	addb	%dl, 0x1f005897
  59492e:      	xchgl	%edi, %eax
  59492f:      	popl	%eax
  594930:      	addb	%ch, (%ecx)
  594932:      	xchgl	%edi, %eax
  594933:      	popl	%eax
  594934:      	addb	%dh, (%ebx)
  594936:      	xchgl	%edi, %eax
  594937:      	popl	%eax
  594938:      	addb	%bh, -0x7fffa769
  59493e:      	xchgl	%edi, %eax
  59493f:      	popl	%eax
  594940:      	addb	%cl, -0x6bffa769(%edx)
  594946:      	xchgl	%edi, %eax
  594947:      	popl	%eax
  594948:      	addb	%bl, -0x57ffa769(%esi)
  59494e:      	xchgl	%edi, %eax
  59494f:      	popl	%eax
  594950:      	addb	%dh, -0x43ffa769(%edx)
  594956:      	xchgl	%edi, %eax
  594957:      	popl	%eax
  594958:      	addb	%al, %dh
  59495a:      	xchgl	%edi, %eax
  59495b:      	popl	%eax
  59495c:      	addb	%dl, %al
  59495e:      	xchgl	%edi, %eax
  59495f:      	popl	%eax
  594960:      	addb	%bl, %dl
  594962:      	xchgl	%edi, %eax
  594963:      	popl	%eax
  594964:      	addb	%ah, %ah
  594966:      	xchgl	%edi, %eax
  594967:      	popl	%eax
  594968:      	addb	%ch, %dh
  59496a:      	xchgl	%edi, %eax
  59496b:      	popl	%eax
  59496c:      	addb	%bh, %al
  59496e:      	xchgl	%edi, %eax
  59496f:      	popl	%eax
  594970:      	addb	%al, (%edx)
  594972:      	cwtl
  594973:      	popl	%eax
  594974:      	addb	%cl, (%eax,%ebx,4)
  594977:      	popl	%eax
  594978:      	addb	%dl, (%esi)
  59497a:      	cwtl
  59497b:      	popl	%eax
  59497c:      	addb	%ah, (%eax)
  59497e:      	cwtl
  59497f:      	popl	%eax
  594980:      	addb	%ch, (%edx)
  594982:      	cwtl
  594983:      	popl	%eax
  594984:      	addb	%dh, (%eax,%ebx,4)
  594987:      	popl	%eax
  594988:      	addb	%bh, (%esi)
  59498a:      	cwtl
  59498b:      	popl	%eax
  59498c:      	addb	%cl, -0x68(%eax)
  59498f:      	popl	%eax
  594990:      	addb	%dl, -0x68(%edx)
  594993:      	popl	%eax
  594994:      	addb	%bl, 0x58(%eax,%ebx,4)
  594998:      	addb	%ah, -0x68(%esi)
  59499b:      	popl	%eax
  59499c:      	addb	%dh, -0x68(%eax)
  59499f:      	popl	%eax
  5949a0:      	addb	%bh, -0x68(%edx)
  5949a3:      	popl	%eax
  5949a4:      	addb	%al, -0x6771ffa8(%eax,%ebx,4)
  5949ab:      	popl	%eax
  5949ac:      	addb	%bl, -0x5dffa768(%eax)
  5949b2:      	cwtl
  5949b3:      	popl	%eax
  5949b4:      	addb	%ch, -0x6749ffa8(%eax,%ebx,4)
  5949bb:      	popl	%eax
  5949bc:      	addb	%al, %al
  5949be:      	cwtl
  5949bf:      	popl	%eax
  5949c0:      	addb	%cl, %dl
  5949c2:      	cwtl
  5949c3:      	popl	%eax
  5949c4:      	addb	%dl, %ah
  5949c6:      	cwtl
  5949c7:      	popl	%eax
  5949c8:      	addb	%bl, %dh
  5949ca:      	cwtl
  5949cb:      	popl	%eax
  5949cc:      	addb	%ch, %al
  5949ce:      	cwtl
  5949cf:      	popl	%eax
  5949d0:      	addb	%dh, %dl
  5949d2:      	cwtl
  5949d3:      	popl	%eax
  5949d4:      	addb	%bh, %ah
  5949d6:      	cwtl
  5949d7:      	popl	%eax
  5949d8:      	addb	%al, (%esi)
  5949da:      	cltd
  5949db:      	popl	%eax
  5949dc:      	addb	%dl, (%eax)
  5949de:      	cltd
  5949df:      	popl	%eax
  5949e0:      	addb	%bl, (%edx)
  5949e2:      	cltd
  5949e3:      	popl	%eax
  5949e4:      	addb	%ah, (%ecx,%ebx,4)
  5949e7:      	popl	%eax
  5949e8:      	addb	%ch, (%esi)
  5949ea:      	cltd
  5949eb:      	popl	%eax
  5949ec:      	addb	%bh, (%eax)
  5949ee:      	cltd
  5949ef:      	popl	%eax
  5949f0:      	addb	%al, -0x67(%edx)
  5949f3:      	popl	%eax
  5949f4:      	addb	%cl, 0x58(%ecx,%ebx,4)
  5949f8:      	addb	%dl, -0x67(%esi)
  5949fb:      	popl	%eax
  5949fc:      	addb	%ah, -0x67(%eax)
  5949ff:      	popl	%eax
  594a00:      	addb	%ch, -0x67(%edx)
  594a03:      	popl	%eax
  594a04:      	addb	%dh, 0x58(%ecx,%ebx,4)
  594a08:      	addb	%bh, -0x67(%esi)
  594a0b:      	popl	%eax
  594a0c:      	addb	%cl, -0x6dffa767(%eax)
  594a12:      	cltd
  594a13:      	popl	%eax
  594a14:      	addb	%bl, -0x6659ffa8(%ecx,%ebx,4)
  594a1b:      	popl	%eax
  594a1c:      	addb	%dh, -0x45ffa767(%eax)
  594a22:      	cltd
  594a23:      	popl	%eax
  594a24:      	addb	%dl, (%esi)
  594a26:      	sbbb	(%ecx), %bl
  594a29:      	addb	%al, (%ecx)
  594a2b:      	addb	(%ebx), %al
  594a2d:      	addb	$0x5, %al
  594a2f:      	pushl	%es
  594a30:      	popl	%es
  594a31:      	orb	%cl, (%ecx)
  594a33:      	orb	(%ebx), %cl
  594a35:      	orb	$0xd, %al
  594a37:      	pushl	%cs
  594a38:      	movups	(%edx), %xmm7
  594a3b:      	cmpb	(%edx), %bh
  594a3d:      	cmpb	(%ecx), %dl
  594a3f:      	adcb	(%ebx), %dl
  594a41:      	cmpb	(%edx), %bh
  594a43:      	cmpb	(%edx), %bh
  594a45:      	cmpb	(%edx), %bh
  594a47:      	cmpb	0x18173a16(,%edx), %dl
  594a4e:      	sbbl	%ebx, (%edx)
  594a50:      	sbbl	(%edx,%edi), %ebx
  594a53:      	cmpb	(%edx), %bh
  594a55:      	cmpb	(%edx), %bh
  594a57:      	cmpb	0x21201f1e, %bl
  594a5d:      	andb	(%ebx), %ah
  594a5f:      	andb	$0x25, %al
  594a61:      	daa
  594a63:      	subb	%ch, (%ecx)
  594a65:      	subb	(%ebx), %ch
  594a67:      	subb	$0x2d, %al
  594a69:      	das
  594a6b:      	xorb	%bh, (%edx)
  594a6d:      	xorl	%esi, (%edx)
  594a6f:      	xorl	(%edx,%edi), %esi
  594a72:      	cmpb	(%edx), %bh
  594a74:      	cmpb	(%edx), %bh
  594a76:      	cmpb	(%edx), %bh
  594a78:      	cmpb	0x39383736, %dh
  594a7e:      	leal	(%ecx), %ecx
  594a81:      	negb	-0x65ffffa8(%ecx)
  594a87:      	popl	%eax
  594a88:      	addb	%cl, (%edx)
  594a8a:      	lcalll	$0x58, $0x9a140058      # imm = 0x9A140058
  594a91:      	pushl	%ds
  594a92:      	lcalll	$0x58, $0x9a280058      # imm = 0x9A280058
  594a99:      	xorb	-0x65c3ffa8(%edx), %bl
  594a9f:      	popl	%eax
  594aa0:      	addb	%al, -0x66(%esi)
  594aa3:      	popl	%eax
  594aa4:      	addb	%dl, -0x66(%eax)
  594aa7:      	popl	%eax
  594aa8:      	addb	%bl, -0x66(%edx)
  594aab:      	popl	%eax
  594aac:      	addb	%ah, 0x58(%edx,%ebx,4)
  594ab0:      	addb	%ch, -0x66(%esi)
  594ab3:      	popl	%eax
  594ab4:      	addb	%bh, -0x66(%eax)
  594ab7:      	popl	%eax
  594ab8:      	addb	%al, -0x73ffa766(%edx)
  594abe:      	lcalll	$0x58, $0x9ab50058      # imm = 0x9AB50058
  594ac5:      	movl	$0xc900589a, %edi       # imm = 0xC900589A
  594aca:      	lcalll	$0x58, $0x9ad30058      # imm = 0x9AD30058
  594ad1:      	fstpl	-0x6518ffa8(%edx)
  594ad7:      	popl	%eax
  594ad8:      	addb	%dh, %cl
  594ada:      	lcalll	$0x58, $0x9afb0058      # imm = 0x9AFB0058
  594ae1:      	addl	$0xf00589b, %eax        # imm = 0xF00589B
  594ae6:      	wait
  594ae7:      	popl	%eax
  594ae8:      	addb	%bl, (%ecx)
  594aea:      	wait
  594aeb:      	popl	%eax
  594aec:      	addb	%bl, 0x58(%ebx,%ebx,4)
  594af0:      	addb	%ah, -0x65(%esi)
  594af3:      	popl	%eax
  594af4:      	addb	%dh, -0x65(%eax)
  594af7:      	popl	%eax
  594af8:      	addb	%bh, -0x65(%edx)
  594afb:      	popl	%eax
  594afc:      	addb	%al, -0x6471ffa8(%ebx,%ebx,4)
  594b03:      	popl	%eax
  594b04:      	addb	%bl, -0x5dffa765(%eax)
  594b0a:      	wait
  594b0b:      	popl	%eax
  594b0c:      	addb	%ch, -0x6449ffa8(%ebx,%ebx,4)
  594b13:      	popl	%eax
  594b14:      	addb	%al, %al
  594b16:      	wait
  594b17:      	popl	%eax
  594b18:      	addb	%cl, %dl
  594b1a:      	wait
  594b1b:      	popl	%eax
  594b1c:      	addb	%dl, %ah
  594b1e:      	wait
  594b1f:      	popl	%eax
  594b20:      	addb	%bl, %dh
  594b22:      	wait
  594b23:      	popl	%eax
  594b24:      	addb	%ch, %al
  594b26:      	wait
  594b27:      	popl	%eax
  594b28:      	addb	%dh, %dl
  594b2a:      	wait
  594b2b:      	popl	%eax
  594b2c:      	addb	%bh, %ah
  594b2e:      	wait
  594b2f:      	popl	%eax
  594b30:      	addb	%al, (%esi)
  594b32:      	pushfl
  594b33:      	popl	%eax
  594b34:      	addb	%dl, (%eax)
  594b36:      	pushfl
  594b37:      	popl	%eax
  594b38:      	addb	%bl, (%edx)
  594b3a:      	pushfl
  594b3b:      	popl	%eax
  594b3c:      	addb	%dl, (%esi)
  594b3e:      	sbbb	(%ecx), %bl
  594b41:      	addb	%al, (%ecx)
  594b43:      	addb	(%ebx), %al
  594b45:      	addb	$0x5, %al
  594b47:      	pushl	%es
  594b48:      	adcb	$0x14, %al
  594b4a:      	adcb	$0x14, %al
  594b4c:      	adcb	$0x14, %al
  594b4e:      	adcb	$0x14, %al
  594b50:      	adcb	$0x14, %al
  594b52:      	adcb	$0x7, %al
  594b54:      	orb	%cl, (%ecx)
  594b56:      	orb	(%ebx), %cl
  594b58:      	orb	$0xd, %al
  594b5a:      	pushl	%cs
  594b5b:      	movups	(%ecx), %xmm2
  594b5e:      	adcb	(%ebx), %dl
  594b60:      	nop
  594b61:      	pushl	%esi
  594b62:      	pushfl
  594b63:      	popl	%eax
  594b64:      	addb	%ah, -0x64(%eax)
  594b67:      	popl	%eax
  594b68:      	addb	%ch, -0x64(%edx)
  594b6b:      	popl	%eax
  594b6c:      	addb	%dh, 0x58(%esp,%ebx,4)
  594b70:      	addb	%bh, -0x64(%esi)
  594b73:      	popl	%eax
  594b74:      	addb	%cl, -0x6dffa764(%eax)
  594b7a:      	pushfl
  594b7b:      	popl	%eax
  594b7c:      	addb	%bl, -0x6359ffa8(%esp,%ebx,4)
  594b83:      	popl	%eax
  594b84:      	addb	%dh, -0x45ffa764(%eax)
  594b8a:      	pushfl
  594b8b:      	popl	%eax
  594b8c:      	addb	%al, %ah
  594b8e:      	pushfl
  594b8f:      	popl	%eax
  594b90:      	addb	%cl, %dh
  594b92:      	pushfl
  594b93:      	popl	%eax
  594b94:      	addb	%bl, %al
  594b96:      	pushfl
  594b97:      	popl	%eax
  594b98:      	addb	%ah, %dl
  594b9a:      	pushfl
  594b9b:      	popl	%eax
  594b9c:      	addb	%ch, %ah
  594b9e:      	pushfl
  594b9f:      	popl	%eax
  594ba0:      	addb	%dh, %dh
  594ba2:      	pushfl
  594ba3:      	popl	%eax
  594ba4:      	addb	%al, (%eax)
  594ba6:      	popfl
  594ba7:      	popl	%eax
  594ba8:      	addb	%cl, (%edx)
  594baa:      	popfl
  594bab:      	popl	%eax
  594bac:      	addb	%dl, -0x62e1ffa8(,%ebx,4)
  594bb3:      	popl	%eax
  594bb4:      	addb	%ch, (%eax)
  594bb6:      	popfl
  594bb7:      	popl	%eax
  594bb8:      	addb	%dh, (%edx)
  594bba:      	popfl
  594bbb:      	popl	%eax
  594bbc:      	addb	%bh, -0x62b9ffa8(,%ebx,4)
  594bc3:      	popl	%eax
  594bc4:      	addb	%dl, -0x63(%eax)
  594bc7:      	popl	%eax
  594bc8:      	addb	%bl, -0x63(%edx)
  594bcb:      	popl	%eax
  594bcc:      	addb	%ah, 0x58(%ebp,%ebx,4)
  594bd0:      	addb	%ch, -0x63(%esi)
  594bd3:      	popl	%eax
  594bd4:      	addb	%bh, -0x63(%eax)
  594bd7:      	popl	%eax
  594bd8:      	addb	%al, -0x73ffa763(%edx)
  594bde:      	popfl
  594bdf:      	popl	%eax
  594be0:      	addb	%dl, -0x5fffa763(%esi)
  594be6:      	popfl
  594be7:      	popl	%eax
  594be8:      	addb	%ch, -0x4bffa763(%edx)
  594bee:      	popfl
  594bef:      	popl	%eax
  594bf0:      	addb	%bh, -0x37ffa763(%esi)
  594bf6:      	popfl
  594bf7:      	popl	%eax
  594bf8:      	addb	%dl, %dl
  594bfa:      	popfl
  594bfb:      	popl	%eax
  594bfc:      	addb	%bl, %ah
  594bfe:      	popfl
  594bff:      	popl	%eax
  594c00:      	addb	%ah, %dh
  594c02:      	popfl
  594c03:      	popl	%eax
  594c04:      	addb	%dh, %al
  594c06:      	popfl
  594c07:      	popl	%eax
  594c08:      	addb	%bh, %dl
  594c0a:      	popfl
  594c0b:      	popl	%eax
  594c0c:      	addb	%al, (%esi,%ebx,4)
  594c0f:      	popl	%eax
  594c10:      	addb	%cl, (%esi)
  594c12:      	sahf
  594c13:      	popl	%eax
  594c14:      	addb	%bl, (%eax)
  594c16:      	sahf
  594c17:      	popl	%eax
  594c18:      	addb	%dl, 0x58(%esi,%ebx,4)
  594c1c:      	addb	%bl, -0x62(%esi)
  594c1f:      	popl	%eax
  594c20:      	addb	%ch, -0x62(%eax)
  594c23:      	popl	%eax
  594c24:      	addb	%dh, -0x62(%edx)
  594c27:      	popl	%eax
  594c28:      	addb	%bh, 0x58(%esi,%ebx,4)
  594c2c:      	addb	%al, -0x6fffa762(%esi)
  594c32:      	sahf
  594c33:      	popl	%eax
  594c34:      	addb	%bl, -0x5bffa762(%edx)
  594c3a:      	sahf
  594c3b:      	popl	%eax
  594c3c:      	addb	%ch, -0x47ffa762(%esi)
  594c42:      	sahf
  594c43:      	popl	%eax
  594c44:      	addb	%al, %dl
  594c46:      	sahf
  594c47:      	popl	%eax
  594c48:      	addb	%cl, %ah
  594c4a:      	sahf
  594c4b:      	popl	%eax
  594c4c:      	addb	%dl, %dh
  594c4e:      	sahf
  594c4f:      	popl	%eax
  594c50:      	addb	%dl, -0x60(%ebp)
  594c53:      	popl	%eax
  594c54:      	addb	%bl, -0x60(%edi)
  594c57:      	popl	%eax
  594c58:      	addb	%ch, -0x60(%ecx)
  594c5b:      	popl	%eax
  594c5c:      	addb	%dh, -0x60(%ebx)
  594c5f:      	popl	%eax
  594c60:      	addb	%bh, -0x60(%ebp)
  594c63:      	popl	%eax
  594c64:      	addb	%al, -0x6effa760(%edi)
  594c6a:      	movb	0xa09b0058, %al
  594c6f:      	popl	%eax
  594c70:      	addb	%ah, -0x1effa760(%ebp)
  594c76:      	movb	0xa0eb0058, %al
  594c7b:      	popl	%eax
  594c7c:      	addb	%dh, %ch
  594c7e:      	movb	0xa0ff0058, %al
  594c83:      	popl	%eax
  594c84:      	addb	%cl, (%ecx)
  594c86:      	movl	0xa1130058, %eax
  594c8b:      	popl	%eax
  594c8c:      	addb	%bl, 0x270058a1
  594c92:      	movl	0xa1310058, %eax
  594c97:      	popl	%eax
  594c98:      	addb	%bh, (%ebx)
  594c9a:      	movl	0xa1450058, %eax
  594c9f:      	popl	%eax
  594ca0:      	addb	%cl, -0x5f(%edi)
  594ca3:      	popl	%eax
  594ca4:      	addb	%bl, -0x5f(%ecx)
  594ca7:      	popl	%eax
  594ca8:      	addb	%ah, -0x5f(%ebx)
  594cab:      	popl	%eax
  594cac:      	addb	%ch, -0x5f(%ebp)
  594caf:      	popl	%eax
  594cb0:      	addb	%dh, -0x5f(%edi)
  594cb3:      	popl	%eax
  594cb4:      	addb	%al, -0x74ffa75f(%ecx)
  594cba:      	movl	0xa3530058, %eax
  594cbf:      	popl	%eax
  594cc0:      	addb	%bl, -0x5d(%ebp)
  594cc3:      	popl	%eax
  594cc4:      	addb	%ah, -0x5d(%edi)
  594cc7:      	popl	%eax
  594cc8:      	addb	%dh, -0x5d(%ecx)
  594ccb:      	popl	%eax
  594ccc:      	addb	%bh, -0x5d(%ebx)
  594ccf:      	popl	%eax
  594cd0:      	addb	%dl, (%esi)
  594cd2:      	sbbb	(%ecx), %bl
  594cd5:      	pushl	%ss
  594cd6:      	sbbb	(%ecx), %bl
  594cd9:      	testl	%esp, -0x5c70ffa8(%ebx)
  594cdf:      	popl	%eax
  594ce0:      	addb	%bl, -0x5cffa75d(%ecx)
  594ce6:      	movl	%eax, 0xa3ad0058
  594ceb:      	popl	%eax
  594cec:      	addb	%dh, -0x3effa75d(%edi)
  594cf2:      	movl	%eax, 0xa3cb0058
  594cf7:      	popl	%eax
  594cf8:      	addb	%dl, %ch
  594cfa:      	movl	%eax, 0xa5470058
  594cff:      	popl	%eax
  594d00:      	addb	%dl, -0x5b(%ecx)
  594d03:      	popl	%eax
  594d04:      	addb	%bl, -0x5b(%ebx)
  594d07:      	popl	%eax
  594d08:      	addb	%ah, -0x5b(%ebp)
  594d0b:      	popl	%eax
  594d0c:      	addb	%ch, -0x5b(%edi)
  594d0f:      	popl	%eax
  594d10:      	addb	%bh, -0x5b(%ecx)
  594d13:      	popl	%eax
  594d14:      	addb	%al, -0x72ffa75b(%ebx)
  594d1a:      	movsl	(%esi), %es:(%edi)
  594d1b:      	popl	%eax
  594d1c:      	addb	%dl, 0x310058a5(%edi)
  594d22:      	cmpsl	%es:(%edi), (%esi)
  594d23:      	popl	%eax
  594d24:      	addb	%bh, (%ebx)
  594d26:      	cmpsl	%es:(%edi), (%esi)
  594d27:      	popl	%eax
  594d28:      	addb	%al, -0x59(%ebp)
  594d2b:      	popl	%eax
  594d2c:      	addb	%cl, -0x59(%edi)
  594d2f:      	popl	%eax
  594d30:      	addb	%bl, -0x59(%ecx)
  594d33:      	popl	%eax
  594d34:      	addb	%ah, -0x59(%ebx)
  594d37:      	popl	%eax
  594d38:      	addb	%ch, -0x59(%ebp)
  594d3b:      	popl	%eax
  594d3c:      	addb	%dh, -0x59(%edi)
  594d3f:      	popl	%eax
  594d40:      	addb	%al, -0x74ffa759(%ecx)
  594d46:      	cmpsl	%es:(%edi), (%esi)
  594d47:      	popl	%eax
  594d48:      	addb	%dl, -0x60ffa759(%ebp)
  594d4e:      	cmpsl	%es:(%edi), (%esi)
  594d4f:      	popl	%eax
  594d50:      	addb	%ch, -0x4cffa759(%ecx)
  594d56:      	cmpsl	%es:(%edi), (%esi)
  594d57:      	popl	%eax
  594d58:      	addb	%bh, -0x38ffa759(%ebp)
  594d5e:      	cmpsl	%es:(%edi), (%esi)
  594d5f:      	popl	%eax
  594d60:      	addb	%dl, %cl
  594d62:      	cmpsl	%es:(%edi), (%esi)
  594d63:      	popl	%eax
  594d64:      	addb	%bl, %bl
  594d66:      	cmpsl	%es:(%edi), (%esi)
  594d67:      	popl	%eax
  594d68:      	addb	%ah, %ch
  594d6a:      	cmpsl	%es:(%edi), (%esi)
  594d6b:      	popl	%eax
  594d6c:      	addb	%ch, %bh
  594d6e:      	cmpsl	%es:(%edi), (%esi)
  594d6f:      	popl	%eax
  594d70:      	addb	%bh, %cl
  594d72:      	cmpsl	%es:(%edi), (%esi)
  594d73:      	popl	%eax
  594d74:      	addb	%al, (%ebx)
  594d76:      	testb	$0x58, %al
  594d78:      	addb	%cl, 0x170058a8
  594d7e:      	testb	$0x58, %al
  594d80:      	addb	%ah, (%ecx)
  594d82:      	testb	$0x58, %al
  594d84:      	addb	%ch, (%ebx)
  594d86:      	testb	$0x58, %al
  594d88:      	addb	%dh, 0x3f0058a8
  594d8e:      	testb	$0x58, %al
  594d90:      	addb	%cl, -0x58(%ecx)
  594d93:      	popl	%eax
  594d94:      	addb	%dl, -0x58(%ebx)
  594d97:      	popl	%eax
  594d98:      	addb	%bl, -0x58(%ebp)
  594d9b:      	popl	%eax
  594d9c:      	addb	%ah, -0x58(%edi)
  594d9f:      	popl	%eax
  594da0:      	addb	%dh, -0x58(%ecx)
  594da3:      	popl	%eax
  594da4:      	addb	%bh, -0x58(%ebx)
  594da7:      	popl	%eax
  594da8:      	addb	%al, -0x70ffa758(%ebp)
  594dae:      	testb	$0x58, %al
  594db0:      	addb	%bl, -0x5cffa758(%ecx)
  594db6:      	testb	$0x58, %al
  594db8:      	addb	%ch, -0x1affa758(%ebp)
  594dbe:      	testb	$0x58, %al
  594dc0:      	addb	%ch, %bh
  594dc2:      	testb	$0x58, %al
  594dc4:      	addb	%bh, %cl
  594dc6:      	testb	$0x58, %al
  594dc8:      	addb	%al, (%ebx)
  594dca:      	testl	$0xa90d0058, %eax       # imm = 0xA90D0058
  594dcf:      	popl	%eax
  594dd0:      	addb	%dl, (%edi)
  594dd2:      	testl	$0xa9210058, %eax       # imm = 0xA9210058
  594dd7:      	popl	%eax
  594dd8:      	addb	%ch, (%ebx)
  594dda:      	testl	$0xa9350058, %eax       # imm = 0xA9350058
  594ddf:      	popl	%eax
  594de0:      	addb	%bh, (%edi)
  594de2:      	testl	$0xa9820058, %eax       # imm = 0xA9820058
  594de7:      	popl	%eax
  594de8:      	addb	%cl, -0x5669ffa8(%ecx,%ebp,4)
  594def:      	popl	%eax
  594df0:      	addb	%ah, -0x55ffa757(%eax)
  594df6:      	testl	$0xa9b40058, %eax       # imm = 0xA9B40058
  594dfb:      	popl	%eax
  594dfc:      	addb	%bh, -0x37ffa757(%esi)
  594e02:      	testl	$0xa9d20058, %eax       # imm = 0xA9D20058
  594e07:      	popl	%eax
  594e08:      	addb	%bl, %ah
  594e0a:      	testl	$0xa9e60058, %eax       # imm = 0xA9E60058
  594e0f:      	popl	%eax
  594e10:      	addb	%dh, %al
  594e12:      	testl	$0xa9fa0058, %eax       # imm = 0xA9FA0058
  594e17:      	popl	%eax
  594e18:      	addb	%al, (%edx,%ebp,4)
  594e1b:      	popl	%eax
  594e1c:      	addb	%cl, (%esi)
  594e1e:      	stosb	%al, %es:(%edi)
  594e1f:      	popl	%eax
  594e20:      	addb	%bl, (%eax)
  594e22:      	stosb	%al, %es:(%edi)
  594e23:      	popl	%eax
  594e24:      	addb	%ah, (%edx)
  594e26:      	stosb	%al, %es:(%edi)
  594e27:      	popl	%eax
  594e28:      	addb	%ch, (%edx,%ebp,4)
  594e2b:      	popl	%eax
  594e2c:      	addb	%dh, (%esi)
  594e2e:      	stosb	%al, %es:(%edi)
  594e2f:      	popl	%eax
  594e30:      	addb	%al, -0x56(%eax)
  594e33:      	popl	%eax
  594e34:      	addb	%cl, -0x56(%edx)
  594e37:      	popl	%eax
  594e38:      	addb	%dl, 0x58(%edx,%ebp,4)
  594e3c:      	addb	%bl, -0x56(%esi)
  594e3f:      	popl	%eax
  594e40:      	addb	%ch, -0x56(%eax)
  594e43:      	popl	%eax
  594e44:      	addb	%dh, -0x56(%edx)
  594e47:      	popl	%eax
  594e48:      	addb	%bh, 0x58(%edx,%ebp,4)
  594e4c:      	addb	%al, -0x6fffa756(%esi)
  594e52:      	stosb	%al, %es:(%edi)
  594e53:      	popl	%eax
  594e54:      	addb	%bl, -0x5bffa756(%edx)
  594e5a:      	stosb	%al, %es:(%edi)
  594e5b:      	popl	%eax
  594e5c:      	addb	%ch, -0x47ffa756(%esi)
  594e62:      	stosb	%al, %es:(%edi)
  594e63:      	popl	%eax
  594e64:      	addb	%al, %dl
  594e66:      	stosb	%al, %es:(%edi)
  594e67:      	popl	%eax
  594e68:      	addb	%cl, %ah
  594e6a:      	stosb	%al, %es:(%edi)
  594e6b:      	popl	%eax
  594e6c:      	addb	%dl, %dh
  594e6e:      	stosb	%al, %es:(%edi)
  594e6f:      	popl	%eax
  594e70:      	addb	%ah, %al
  594e72:      	stosb	%al, %es:(%edi)
  594e73:      	popl	%eax
  594e74:      	addb	%ch, %dl
  594e76:      	stosb	%al, %es:(%edi)
  594e77:      	popl	%eax
  594e78:      	addb	%dh, %ah
  594e7a:      	stosb	%al, %es:(%edi)
  594e7b:      	popl	%eax
  594e7c:      	addb	%bh, %dh
  594e7e:      	stosb	%al, %es:(%edi)
  594e7f:      	popl	%eax
  594e80:      	addb	%cl, (%eax)
  594e82:      	stosl	%eax, %es:(%edi)
  594e83:      	popl	%eax
  594e84:      	addb	%dl, (%edx)
  594e86:      	stosl	%eax, %es:(%edi)
  594e87:      	popl	%eax
  594e88:      	addb	%bl, (%ebx,%ebp,4)
  594e8b:      	popl	%eax
  594e8c:      	addb	%ah, (%esi)
  594e8e:      	stosl	%eax, %es:(%edi)
  594e8f:      	popl	%eax
  594e90:      	addb	%dh, (%eax)
  594e92:      	stosl	%eax, %es:(%edi)
  594e93:      	popl	%eax
  594e94:      	addb	%bh, (%edx)
  594e96:      	stosl	%eax, %es:(%edi)
  594e97:      	popl	%eax
  594e98:      	addb	%al, 0x58(%ebx,%ebp,4)
  594e9c:      	addb	%cl, -0x55(%esi)
  594e9f:      	popl	%eax
  594ea0:      	addb	%bh, -0x54a7ffa8(%ebx,%ebp,4)
  594ea7:      	popl	%eax
  594ea8:      	addb	%ah, -0x55(%edx)
  594eab:      	popl	%eax
  594eac:      	addb	%ch, 0x58(%ebx,%ebp,4)
  594eb0:      	addb	%dh, -0x55(%esi)
  594eb3:      	popl	%eax
  594eb4:      	addb	%al, -0x75ffa755(%eax)
  594eba:      	stosl	%eax, %es:(%edi)
  594ebb:      	popl	%eax
  594ebc:      	addb	%dl, -0x5461ffa8(%ebx,%ebp,4)
  594ec3:      	popl	%eax
  594ec4:      	addb	%ch, -0x4dffa755(%eax)
  594eca:      	stosl	%eax, %es:(%edi)
  594ecb:      	popl	%eax
  594ecc:      	addb	%al, %dh
  594ece:      	stosl	%eax, %es:(%edi)
  594ecf:      	popl	%eax
  594ed0:      	addb	%dl, (%esi)
  594ed2:      	sbbb	(%ecx), %bl
  594ed5:      	addb	%al, (%ecx)
  594ed7:      	addb	(%ebx), %al
  594ed9:      	addb	$0x5, %al
  594edb:      	pushl	%es
  594edc:      	popl	%es
  594edd:      	orb	%cl, (%ecx)
  594edf:      	orb	(%ebx), %cl
  594ee1:      	orb	$0xd, %al
  594ee3:      	pushl	%cs
  594ee4:      	movups	(%ecx), %xmm2
  594ee7:      	adcb	(%ebx), %dl
  594ee9:      	adcb	$0x15, %al
  594eeb:      	pushl	%ss
  594eec:      	popl	%ss
  594eed:      	sbbb	%bl, (%ecx)
  594eef:      	sbbb	(%ebx), %bl
  594ef1:      	sbbb	$0x1d, %al
  594ef3:      	pushl	%ds
  594ef4:      	popl	%ds
  594ef5:      	andb	%ah, (%ecx)
  594ef7:      	andb	(%ebx), %ah
  594ef9:      	andb	$0x25, %al
  594efb:      	daa
  594efd:      	subb	%ch, (%ecx)
  594eff:      	subb	(%ebx), %ch
  594f01:      	subb	$0x2d, %al
  594f03:      	das
  594f05:      	cmpl	(%ebx), %edi
  594f07:      	cmpl	(%ebx), %edi
  594f09:      	cmpl	(%ebx), %edi
  594f0b:      	cmpl	(%ebx), %edi
  594f0d:      	cmpl	(%ebx), %edi
  594f0f:      	cmpl	(%ebx), %edi
  594f11:      	cmpl	(%ebx), %edi
  594f13:      	cmpl	(%ebx), %edi
  594f15:      	cmpl	(%ebx), %edi
  594f17:      	cmpl	(%ebx), %edi
  594f19:      	cmpl	(%ebx), %edi
  594f1b:      	cmpl	(%ebx), %edi
  594f1d:      	cmpl	(%ebx), %edi
  594f1f:      	cmpl	(%ebx), %edi
  594f21:      	cmpl	(%ebx), %edi
  594f23:      	cmpl	(%ebx), %edi
  594f25:      	cmpl	(%ebx), %edi
  594f27:      	cmpl	(%ebx), %edi
  594f29:      	cmpl	(%ebx), %edi
  594f2b:      	cmpl	(%ebx), %edi
  594f2d:      	cmpl	(%ebx), %edi
  594f2f:      	cmpl	(%ebx), %edi
  594f31:      	cmpl	(%ebx), %edi
  594f33:      	cmpl	(%ebx), %edi
  594f35:      	cmpl	(%ebx), %edi
  594f37:      	cmpl	(%ebx), %edi
  594f39:      	xorb	%dh, (%ecx)
  594f3b:      	xorb	(%ebx), %dh
  594f3d:      	xorb	$0x35, %al
  594f3f:      	aaa
  594f41:      	cmpb	%bh, (%ecx)
  594f43:      	cmpb	0x58ac0b(%eax), %dl
  594f49:      	adcl	$0x1f0058ac, %eax       # imm = 0x1F0058AC
  594f4e:      	lodsb	(%esi), %al
  594f4f:      	popl	%eax
  594f50:      	addb	%ch, (%ecx)
  594f52:      	lodsb	(%esi), %al
  594f53:      	popl	%eax
  594f54:      	addb	%dh, (%ebx)
  594f56:      	lodsb	(%esi), %al
  594f57:      	popl	%eax
  594f58:      	addb	%bh, 0x470058ac
  594f5e:      	lodsb	(%esi), %al
  594f5f:      	popl	%eax
  594f60:      	addb	%dl, -0x54(%ecx)
  594f63:      	popl	%eax
  594f64:      	addb	%bl, -0x54(%ebx)
  594f67:      	popl	%eax
  594f68:      	addb	%ah, -0x54(%ebp)
  594f6b:      	popl	%eax
  594f6c:      	addb	%ch, -0x54(%edi)
  594f6f:      	popl	%eax
  594f70:      	addb	%bh, -0x54(%ecx)
  594f73:      	popl	%eax
  594f74:      	addb	%al, -0x72ffa754(%ebx)
  594f7a:      	lodsb	(%esi), %al
  594f7b:      	popl	%eax
  594f7c:      	addb	%dl, -0x5effa754(%edi)
  594f82:      	lodsb	(%esi), %al
  594f83:      	popl	%eax
  594f84:      	addb	%ch, -0x4affa754(%ebx)
  594f8a:      	lodsb	(%esi), %al
  594f8b:      	popl	%eax
  594f8c:      	addb	%bh, -0x36ffa754(%edi)
  594f92:      	lodsb	(%esi), %al
  594f93:      	popl	%eax
  594f94:      	addb	%dl, %bl
  594f96:      	lodsb	(%esi), %al
  594f97:      	popl	%eax
  594f98:      	addb	%bl, %ch
  594f9a:      	lodsb	(%esi), %al
  594f9b:      	popl	%eax
  594f9c:      	addb	%ah, %bh
  594f9e:      	lodsb	(%esi), %al
  594f9f:      	popl	%eax
  594fa0:      	addb	%dh, %cl
  594fa2:      	lodsb	(%esi), %al
  594fa3:      	popl	%eax
  594fa4:      	addb	%bh, %bl
  594fa6:      	lodsb	(%esi), %al
  594fa7:      	popl	%eax
  594fa8:      	addb	%al, 0xf0058ad
  594fae:      	lodsl	(%esi), %eax
  594faf:      	popl	%eax
  594fb0:      	addb	%bl, (%ecx)
  594fb2:      	lodsl	(%esi), %eax
  594fb3:      	popl	%eax
  594fb4:      	addb	%ah, (%ebx)
  594fb6:      	lodsl	(%esi), %eax
  594fb7:      	popl	%eax
  594fb8:      	addb	%ch, 0x370058ad
  594fbe:      	lodsl	(%esi), %eax
  594fbf:      	popl	%eax
  594fc0:      	addb	%al, -0x53(%ecx)
  594fc3:      	popl	%eax
  594fc4:      	addb	%cl, -0x53(%ebx)
  594fc7:      	popl	%eax
  594fc8:      	addb	%dl, -0x53(%ebp)
  594fcb:      	popl	%eax
  594fcc:      	addb	%bl, -0x53(%edi)
  594fcf:      	popl	%eax
  594fd0:      	addb	%ch, -0x53(%ecx)
  594fd3:      	popl	%eax
  594fd4:      	addb	%dh, -0x53(%ebx)
  594fd7:      	popl	%eax
  594fd8:      	addb	%bh, -0x53(%ebp)
  594fdb:      	popl	%eax
  594fdc:      	addb	%al, -0x6effa753(%edi)
  594fe2:      	lodsl	(%esi), %eax
  594fe3:      	popl	%eax
  594fe4:      	addb	%bl, -0x5affa753(%ebx)
  594fea:      	lodsl	(%esi), %eax
  594feb:      	popl	%eax
  594fec:      	addb	%ch, -0x46ffa753(%edi)
  594ff2:      	lodsl	(%esi), %eax
  594ff3:      	popl	%eax
  594ff4:      	addb	%al, %bl
  594ff6:      	lodsl	(%esi), %eax
  594ff7:      	popl	%eax
  594ff8:      	addb	%cl, %ch
  594ffa:      	lodsl	(%esi), %eax
  594ffb:      	popl	%eax
  594ffc:      	addb	%dl, %bh
  594ffe:      	lodsl	(%esi), %eax
  594fff:      	popl	%eax
  595000:      	addb	%ah, %cl
  595002:      	lodsl	(%esi), %eax
  595003:      	popl	%eax
  595004:      	addb	%ch, %bl
  595006:      	lodsl	(%esi), %eax
  595007:      	popl	%eax
  595008:      	addb	%dh, %ch
  59500a:      	lodsl	(%esi), %eax
  59500b:      	popl	%eax
  59500c:      	addb	%bh, %bh
  59500e:      	lodsl	(%esi), %eax
  59500f:      	popl	%eax
  595010:      	addb	%cl, (%ecx)
  595012:      	scasb	%es:(%edi), %al
  595013:      	popl	%eax
  595014:      	addb	%dl, (%ebx)
  595016:      	scasb	%es:(%edi), %al
  595017:      	popl	%eax
  595018:      	addb	%bl, 0x270058ae
  59501e:      	scasb	%es:(%edi), %al
  59501f:      	popl	%eax
  595020:      	addb	%dh, (%ecx)
  595022:      	scasb	%es:(%edi), %al
  595023:      	popl	%eax
  595024:      	addb	%bh, (%ebx)
  595026:      	scasb	%es:(%edi), %al
  595027:      	popl	%eax
  595028:      	addb	%al, -0x52(%ebp)
  59502b:      	popl	%eax
  59502c:      	addb	%cl, -0x52(%edi)
  59502f:      	popl	%eax
  595030:      	addb	%bl, -0x52(%ecx)
  595033:      	popl	%eax
  595034:      	addb	%ah, -0x52(%ebx)
  595037:      	popl	%eax
  595038:      	addb	%ch, -0x52(%ebp)
  59503b:      	popl	%eax
  59503c:      	addb	%dh, -0x52(%edi)
  59503f:      	popl	%eax
  595040:      	addb	%al, -0x74ffa752(%ecx)
  595046:      	scasb	%es:(%edi), %al
  595047:      	popl	%eax
  595048:      	addb	%dl, -0x60ffa752(%ebp)
  59504e:      	scasb	%es:(%edi), %al
  59504f:      	popl	%eax
  595050:      	addb	%ch, -0x4cffa752(%ecx)
  595056:      	scasb	%es:(%edi), %al
  595057:      	popl	%eax
  595058:      	addb	%bh, -0x38ffa752(%ebp)
  59505e:      	scasb	%es:(%edi), %al
  59505f:      	popl	%eax
  595060:      	addb	%dl, %cl
  595062:      	scasb	%es:(%edi), %al
  595063:      	popl	%eax
  595064:      	addb	%bl, %bl
  595066:      	scasb	%es:(%edi), %al
  595067:      	popl	%eax
  595068:      	addb	%ah, %ch
  59506a:      	scasb	%es:(%edi), %al
  59506b:      	popl	%eax
  59506c:      	addb	%ch, %bh
  59506e:      	scasb	%es:(%edi), %al
  59506f:      	popl	%eax
  595070:      	addb	%bh, %cl
  595072:      	scasb	%es:(%edi), %al
  595073:      	popl	%eax
  595074:      	addb	%al, (%ebx)
  595076:      	scasl	%es:(%edi), %eax
  595077:      	popl	%eax
  595078:      	addb	%dl, (%esi)
  59507a:      	sbbb	(%ecx), %bl
  59507d:      	addb	%al, (%ecx)
  59507f:      	addb	0x4d(%ebp), %cl
  595082:      	addl	0x9080706(,%eax), %eax
  595089:      	decl	%ebp
  59508a:      	orb	(%ebx), %cl
  59508c:      	orb	$0xd, %al
  59508e:      	pushl	%cs
  59508f:      	cmovgel	0x4d(%ebp), %ecx
  595093:      	adcb	%dl, (%ecx)
  595095:      	adcb	(%ebx), %dl
  595097:      	decl	%ebp
  595098:      	adcb	$0x15, %al
  59509a:      	pushl	%ss
  59509b:      	decl	%ebp
  59509c:      	decl	%ebp
  59509d:      	decl	%ebp
  59509e:      	popl	%ss
  59509f:      	sbbb	%bl, (%ecx)
  5950a1:      	sbbb	(%ebx), %bl
  5950a3:      	sbbb	$0x1d, %al
  5950a5:      	pushl	%ds
  5950a6:      	popl	%ds
  5950a7:      	andb	%ah, (%ecx)
  5950a9:      	andb	0x23(%ebp), %cl
  5950ac:      	decl	%ebp
  5950ad:      	decl	%ebp
  5950ae:      	andb	$0x25, %al
  5950b0:      	daa
  5950b2:      	subb	%ch, (%ecx)
  5950b4:      	subb	0x2b(%ebp), %cl
  5950b7:      	subb	$0x4d, %al
  5950b9:      	subl	$0x4d4d4d2e, %eax       # imm = 0x4D4D4D2E
  5950be:      	decl	%ebp
  5950bf:      	decl	%ebp
  5950c0:      	decl	%ebp
  5950c1:      	das
  5950c2:      	xorb	%dh, (%ecx)
  5950c4:      	xorb	(%ebx), %dh
  5950c6:      	xorb	$0x35, %al
  5950c8:      	aaa
  5950ca:      	cmpb	%bh, (%ecx)
  5950cc:      	cmpb	0x4d(%ebp), %cl
  5950cf:      	decl	%ebp
  5950d0:      	decl	%ebp
  5950d1:      	decl	%ebp
  5950d2:      	cmpl	0x41403f3e(,%edi), %edi
  5950d9:      	decl	%ebp
  5950da:      	decl	%ebp
  5950db:      	decl	%ebp
  5950dc:      	decl	%ebp
  5950dd:      	decl	%ebp
  5950de:      	decl	%ebp
  5950df:      	decl	%ebp
  5950e0:      	decl	%ebp
  5950e1:      	decl	%ebp
  5950e2:      	decl	%ebp
  5950e3:      	decl	%ebp
  5950e4:      	decl	%ebp
  5950e5:      	decl	%ebp
  5950e6:      	decl	%ebp
  5950e7:      	decl	%ebp
  5950e8:      	decl	%ebp
  5950e9:      	decl	%ebp
  5950ea:      	decl	%ebp
  5950eb:      	decl	%ebp
  5950ec:      	decl	%ebp
  5950ed:      	incl	%edx
  5950ee:      	incl	%ebx
  5950ef:      	incl	%esp
  5950f0:      	incl	%ebp
  5950f1:      	decl	%ebp
  5950f2:      	decl	%ebp
  5950f3:      	decl	%ebp
  5950f4:      	decl	%ebp
  5950f5:      	decl	%ebp
  5950f6:      	decl	%ebp
  5950f7:      	decl	%ebp
  5950f8:      	decl	%ebp
  5950f9:      	decl	%ebp
  5950fa:      	decl	%ebp
  5950fb:      	incl	%esi
  5950fc:      	incl	%edi
  5950fd:      	decl	%eax
  5950fe:      	decl	%ecx
  5950ff:      	decl	%edx
  595100:      	decl	%ebx
  595101:      	decl	%esp
  595102:      	leal	(%ecx), %ecx
  595105:      	andl	%esi, 0x1a160058(%eax)
  59510b:      	popl	%ecx
  59510c:      	addb	%ch, (%ebx)
  59510e:      	movb	$0x58, %al
  595110:      	addb	%dh, 0x3f0058b0
  595116:      	movb	$0x58, %al
  595118:      	addb	%cl, -0x50(%ecx)
  59511b:      	popl	%eax
  59511c:      	addb	%dl, -0x50(%ebx)
  59511f:      	popl	%eax
  595120:      	addb	%bl, -0x50(%ebp)
  595123:      	popl	%eax
  595124:      	addb	%ah, -0x50(%edi)
  595127:      	popl	%eax
  595128:      	addb	%dh, -0x50(%ecx)
  59512b:      	popl	%eax
  59512c:      	addb	%bh, -0x50(%ebx)
  59512f:      	popl	%eax
  595130:      	addb	%al, -0x70ffa750(%ebp)
  595136:      	movb	$0x58, %al
  595138:      	addb	%bl, -0x5cffa750(%ecx)
  59513e:      	movb	$0x58, %al
  595140:      	addb	%ch, -0x48ffa750(%ebp)
  595146:      	movb	$0x58, %al
  595148:      	addb	%al, %cl
  59514a:      	movb	$0x58, %al
  59514c:      	addb	%cl, %bl
  59514e:      	movb	$0x58, %al
  595150:      	addb	%dl, %ch
  595152:      	movb	$0x58, %al
  595154:      	addb	%bl, %bh
  595156:      	movb	$0x58, %al
  595158:      	addb	%al, -0x6fffa74b(%esi)
  59515e:      	movb	$0x58, %ch
  595160:      	addb	%bl, -0x5bffa74b(%edx)
  595166:      	movb	$0x58, %ch
  595168:      	addb	%ch, -0x47ffa74b(%esi)
  59516e:      	movb	$0x58, %ch
  595170:      	addb	%al, %dl
  595172:      	movb	$0x58, %ch
  595174:      	addb	%cl, %ah
  595176:      	movb	$0x58, %ch
  595178:      	addb	%dl, %dh
  59517a:      	movb	$0x58, %ch
  59517c:      	addb	%ah, %al
  59517e:      	movb	$0x58, %ch
  595180:      	addb	%ch, %dl
  595182:      	movb	$0x58, %ch
  595184:      	addb	%dh, %ah
  595186:      	movb	$0x58, %ch
  595188:      	addb	%bh, %dh
  59518a:      	movb	$0x58, %ch
  59518c:      	addb	%cl, (%eax)
  59518e:      	movb	$0x58, %dh
  595190:      	addb	%dl, (%edx)
  595192:      	movb	$0x58, %dh
  595194:      	addb	%bl, (%esi,%esi,4)
  595197:      	popl	%eax
  595198:      	addb	%ah, (%esi)
  59519a:      	movb	$0x58, %dh
  59519c:      	addb	%dh, (%eax)
  59519e:      	movb	$0x58, %dh
  5951a0:      	addb	%dl, (%esi)
  5951a2:      	sbbb	(%ecx), %bl
  5951a5:      	addb	%al, (%ecx)
  5951a7:      	adcb	(%edx), %dl
  5951a9:      	adcb	(%edx), %dl
  5951ab:      	adcb	(%edx), %dl
  5951ad:      	adcb	(%edx), %dl
  5951af:      	adcb	(%edx), %dl
  5951b1:      	adcb	(%edx), %dl
  5951b3:      	adcb	(%edx), %dl
  5951b5:      	adcb	(%edx), %al
  5951b7:      	adcb	(%edx), %dl
  5951b9:      	addl	(%edx), %edx
  5951bb:      	addb	$0x12, %al
  5951bd:      	adcb	(%edx), %dl
  5951bf:      	adcb	(%edx), %dl
  5951c1:      	adcb	(%edx), %dl
  5951c3:      	adcb	(%edx), %dl
  5951c5:      	adcb	(%edx), %dl
  5951c7:      	adcb	(%edx), %dl
  5951c9:      	adcb	(%edx), %dl
  5951cb:      	adcb	(%edx), %dl
  5951cd:      	addl	$0x9080706, %eax        # imm = 0x9080706
  5951d2:      	orb	(%ebx), %cl
  5951d4:      	orb	$0xd, %al
  5951d6:      	pushl	%cs
  5951d7:      	movups	(%ecx), %xmm2
  5951da:      	leal	(%ecx), %ecx
  5951dd:      	bound	%esi, -0x4993ffa8(%esi)
  5951e3:      	popl	%eax
  5951e4:      	addb	%dh, -0x4a(%esi)
  5951e7:      	popl	%eax
  5951e8:      	addb	%al, -0x75ffa74a(%eax)
  5951ee:      	movb	$0x58, %dh
  5951f0:      	addb	%dl, -0x4961ffa8(%esi,%esi,4)
  5951f7:      	popl	%eax
  5951f8:      	addb	%ch, -0x4dffa74a(%eax)
  5951fe:      	movb	$0x58, %dh
  595200:      	addb	%bh, -0x4939ffa8(%esi,%esi,4)
  595207:      	popl	%eax
  595208:      	addb	%dl, %al
  59520a:      	movb	$0x58, %dh
  59520c:      	addb	%bl, %dl
  59520e:      	movb	$0x58, %dh
  595210:      	addb	%ah, %ah
  595212:      	movb	$0x58, %dh
  595214:      	addb	%ch, %dh
  595216:      	movb	$0x58, %dh
  595218:      	addb	%bh, %al
  59521a:      	movb	$0x58, %dh
  59521c:      	addb	%al, (%edx)
  59521e:      	movb	$0x58, %bh
  595220:      	addb	%cl, (%edi,%esi,4)
  595223:      	popl	%eax
  595224:      	addb	%dl, (%esi)
  595226:      	movb	$0x58, %bh
  595228:      	addb	%ah, (%eax)
  59522a:      	movb	$0x58, %bh
  59522c:      	addb	%ch, (%edx)
  59522e:      	movb	$0x58, %bh
  595230:      	addb	%dh, (%edi,%esi,4)
  595233:      	popl	%eax
  595234:      	addb	%bh, (%esi)
  595236:      	movb	$0x58, %bh
  595238:      	addb	%cl, -0x49(%eax)
  59523b:      	popl	%eax
  59523c:      	addb	%dl, -0x49(%edx)
  59523f:      	popl	%eax
  595240:      	addb	%bl, 0x58(%edi,%esi,4)
  595244:      	addb	%ah, -0x49(%esi)
  595247:      	popl	%eax
  595248:      	addb	%dh, -0x49(%eax)
  59524b:      	popl	%eax
  59524c:      	addb	%bh, -0x49(%edx)
  59524f:      	popl	%eax
  595250:      	addb	%al, -0x4871ffa8(%edi,%esi,4)
  595257:      	popl	%eax
  595258:      	addb	%bl, -0x5dffa749(%eax)
  59525e:      	movb	$0x58, %bh
  595260:      	addb	%ch, -0x4849ffa8(%edi,%esi,4)
  595267:      	popl	%eax
  595268:      	addb	%al, %al
  59526a:      	movb	$0x58, %bh
  59526c:      	addb	%cl, %dl
  59526e:      	movb	$0x58, %bh
  595270:      	addb	%dl, %ah
  595272:      	movb	$0x58, %bh
  595274:      	addb	%bl, %dh
  595276:      	movb	$0x58, %bh
  595278:      	addb	%ch, %al
  59527a:      	movb	$0x58, %bh
  59527c:      	addb	%dh, %dl
  59527e:      	movb	$0x58, %bh
  595280:      	addb	%bh, %ah
  595282:      	movb	$0x58, %bh
  595284:      	addb	%al, (%esi)
  595286:      	movl	$0xb8100058, %eax       # imm = 0xB8100058
  59528b:      	popl	%eax
  59528c:      	addb	%bl, (%edx)
  59528e:      	movl	$0xb8240058, %eax       # imm = 0xB8240058
  595293:      	popl	%eax
  595294:      	addb	%ch, (%esi)
  595296:      	movl	$0xb8380058, %eax       # imm = 0xB8380058
  59529b:      	popl	%eax
  59529c:      	addb	%al, -0x48(%edx)
  59529f:      	popl	%eax
  5952a0:      	addb	%cl, 0x58(%eax,%edi,4)
  5952a4:      	addb	%dl, -0x48(%esi)
  5952a7:      	popl	%eax
  5952a8:      	addb	%ah, -0x48(%eax)
  5952ab:      	popl	%eax
  5952ac:      	addb	%ch, -0x48(%edx)
  5952af:      	popl	%eax
  5952b0:      	addb	%dh, 0x58(%eax,%edi,4)
  5952b4:      	addb	%bh, -0x48(%esi)
  5952b7:      	popl	%eax
  5952b8:      	addb	%cl, -0x6dffa748(%eax)
  5952be:      	movl	$0xb89c0058, %eax       # imm = 0xB89C0058
  5952c3:      	popl	%eax
  5952c4:      	addb	%ah, -0x4fffa748(%esi)
  5952ca:      	movl	$0xb8ba0058, %eax       # imm = 0xB8BA0058
  5952cf:      	popl	%eax
  5952d0:      	addb	%al, %ah
  5952d2:      	movl	$0xb8ce0058, %eax       # imm = 0xB8CE0058
  5952d7:      	popl	%eax
  5952d8:      	addb	%bl, %al
  5952da:      	movl	$0xb8e20058, %eax       # imm = 0xB8E20058
  5952df:      	popl	%eax
  5952e0:      	addb	%ch, %ah
  5952e2:      	movl	$0xb8f60058, %eax       # imm = 0xB8F60058
  5952e7:      	popl	%eax
  5952e8:      	addb	%al, (%eax)
  5952ea:      	movl	$0xb90a0058, %ecx       # imm = 0xB90A0058
  5952ef:      	popl	%eax
  5952f0:      	addb	%dl, (%ecx,%edi,4)
  5952f3:      	popl	%eax
  5952f4:      	addb	%bl, (%esi)
  5952f6:      	movl	$0xb9280058, %ecx       # imm = 0xB9280058
  5952fb:      	popl	%eax
  5952fc:      	addb	%dh, (%edx)
  5952fe:      	movl	$0xb93c0058, %ecx       # imm = 0xB93C0058
  595303:      	popl	%eax
  595304:      	addb	%al, -0x47(%esi)
  595307:      	popl	%eax
  595308:      	addb	%dl, (%esi)
  59530a:      	sbbb	(%ecx), %bl
  59530d:      	addb	%al, (%ecx)
  59530f:      	addb	(%ebx), %al
  595311:      	addb	$0x5, %al
  595313:      	pushl	%es
  595314:      	popl	%es
  595315:      	orb	%cl, (%ecx)
  595317:      	orb	(%ebx), %cl
  595319:      	orb	$0xd, %al
  59531b:      	pushl	%cs
  59531c:      	movups	(%ecx), %xmm2
  59531f:      	adcb	0x4b(%ebx), %cl
  595322:      	decl	%ebx
  595323:      	decl	%ebx
  595324:      	decl	%ebx
  595325:      	decl	%ebx
  595326:      	decl	%ebx
  595327:      	adcl	0x4b4b4b16(,%edx), %edx
  59532e:      	decl	%ebx
  59532f:      	decl	%ebx
  595330:      	decl	%ebx
  595331:      	decl	%ebx
  595332:      	decl	%ebx
  595333:      	decl	%ebx
  595334:      	decl	%ebx
  595335:      	decl	%ebx
  595336:      	decl	%ebx
  595337:      	decl	%ebx
  595338:      	decl	%ebx
  595339:      	decl	%ebx
  59533a:      	decl	%ebx
  59533b:      	popl	%ss
  59533c:      	decl	%ebx
  59533d:      	decl	%ebx
  59533e:      	decl	%ebx
  59533f:      	decl	%ebx
  595340:      	decl	%ebx
  595341:      	decl	%ebx
  595342:      	decl	%ebx
  595343:      	decl	%ebx
  595344:      	decl	%ebx
  595345:      	sbbb	%cl, 0x4b(%ebx)
  595348:      	decl	%ebx
  595349:      	decl	%ebx
  59534a:      	decl	%ebx
  59534b:      	decl	%ebx
  59534c:      	decl	%ebx
  59534d:      	decl	%ebx
  59534e:      	decl	%ebx
  59534f:      	sbbl	%ecx, 0x4b(%ebx)
  595352:      	decl	%ebx
  595353:      	decl	%ebx
  595354:      	decl	%ebx
  595355:      	decl	%ebx
  595356:      	decl	%ebx
  595357:      	decl	%ebx
  595358:      	decl	%ebx
  595359:      	decl	%ebx
  59535a:      	decl	%ebx
  59535b:      	decl	%ebx
  59535c:      	decl	%ebx
  59535d:      	decl	%ebx
  59535e:      	decl	%ebx
  59535f:      	decl	%ebx
  595360:      	decl	%ebx
  595361:      	decl	%ebx
  595362:      	decl	%ebx
  595363:      	sbbb	0x4b(%ebx), %cl
  595366:      	decl	%ebx
  595367:      	decl	%ebx
  595368:      	decl	%ebx
  595369:      	decl	%ebx
  59536a:      	decl	%ebx
  59536b:      	decl	%ebx
  59536c:      	decl	%ebx
  59536d:      	decl	%ebx
  59536e:      	decl	%ebx
  59536f:      	decl	%ebx
  595370:      	decl	%ebx
  595371:      	decl	%ebx
  595372:      	decl	%ebx
  595373:      	decl	%ebx
  595374:      	decl	%ebx
  595375:      	decl	%ebx
  595376:      	decl	%ebx
  595377:      	sbbl	0x4b(%ebx), %ecx
  59537a:      	decl	%ebx
  59537b:      	decl	%ebx
  59537c:      	decl	%ebx
  59537d:      	decl	%ebx
  59537e:      	decl	%ebx
  59537f:      	decl	%ebx
  595380:      	decl	%ebx
  595381:      	sbbb	$0x1d, %al
  595383:      	pushl	%ds
  595384:      	popl	%ds
  595385:      	andb	%ah, (%ecx)
  595387:      	andb	(%ebx), %ah
  595389:      	decl	%ebx
  59538a:      	andb	$0x4b, %al
  59538c:      	decl	%ebx
  59538d:      	decl	%ebx
  59538e:      	decl	%ebx
  59538f:      	decl	%ebx
  595390:      	decl	%ebx
  595391:      	decl	%ebx
  595392:      	decl	%ebx
  595393:      	decl	%ebx
  595394:      	decl	%ebx
  595395:      	decl	%ebx
  595396:      	decl	%ebx
  595397:      	decl	%ebx
  595398:      	decl	%ebx
  595399:      	decl	%ebx
  59539a:      	decl	%ebx
  59539b:      	decl	%ebx
  59539c:      	decl	%ebx
  59539d:      	decl	%ebx
  59539e:      	decl	%ebx
  59539f:      	decl	%ebx
  5953a0:      	decl	%ebx
  5953a1:      	decl	%ebx
  5953a2:      	decl	%ebx
  5953a3:      	decl	%ebx
  5953a4:      	decl	%ebx
  5953a5:      	decl	%ebx
  5953a6:      	decl	%ebx
  5953a7:      	decl	%ebx
  5953a8:      	decl	%ebx
  5953a9:      	decl	%ebx
  5953aa:      	decl	%ebx
  5953ab:      	decl	%ebx
  5953ac:      	decl	%ebx
  5953ad:      	decl	%ebx
  5953ae:      	decl	%ebx
  5953af:      	decl	%ebx
  5953b0:      	decl	%ebx
  5953b1:      	decl	%ebx
  5953b2:      	decl	%ebx
  5953b3:      	decl	%ebx
  5953b4:      	decl	%ebx
  5953b5:      	decl	%ebx
  5953b6:      	decl	%ebx
  5953b7:      	decl	%ebx
  5953b8:      	decl	%ebx
  5953b9:      	decl	%ebx
  5953ba:      	decl	%ebx
  5953bb:      	decl	%ebx
  5953bc:      	decl	%ebx
  5953bd:      	decl	%ebx
  5953be:      	decl	%ebx
  5953bf:      	decl	%ebx
  5953c0:      	decl	%ebx
  5953c1:      	decl	%ebx
  5953c2:      	decl	%ebx
  5953c3:      	decl	%ebx
  5953c4:      	decl	%ebx
  5953c5:      	decl	%ebx
  5953c6:      	decl	%ebx
  5953c7:      	decl	%ebx
  5953c8:      	decl	%ebx
  5953c9:      	decl	%ebx
  5953ca:      	decl	%ebx
  5953cb:      	decl	%ebx
  5953cc:      	decl	%ebx
  5953cd:      	decl	%ebx
  5953ce:      	decl	%ebx
  5953cf:      	decl	%ebx
  5953d0:      	decl	%ebx
  5953d1:      	decl	%ebx
  5953d2:      	decl	%ebx
  5953d3:      	decl	%ebx
  5953d4:      	decl	%ebx
  5953d5:      	decl	%ebx
  5953d6:      	decl	%ebx
  5953d7:      	decl	%ebx
  5953d8:      	decl	%ebx
  5953d9:      	decl	%ebx
  5953da:      	decl	%ebx
  5953db:      	decl	%ebx
  5953dc:      	decl	%ebx
  5953dd:      	decl	%ebx
  5953de:      	decl	%ebx
  5953df:      	decl	%ebx
  5953e0:      	decl	%ebx
  5953e1:      	decl	%ebx
  5953e2:      	decl	%ebx
  5953e3:      	decl	%ebx
  5953e4:      	decl	%ebx
  5953e5:      	decl	%ebx
  5953e6:      	decl	%ebx
  5953e7:      	decl	%ebx
  5953e8:      	decl	%ebx
  5953e9:      	decl	%ebx
  5953ea:      	decl	%ebx
  5953eb:      	decl	%ebx
  5953ec:      	decl	%ebx
  5953ed:      	decl	%ebx
  5953ee:      	decl	%ebx
  5953ef:      	decl	%ebx
  5953f0:      	decl	%ebx
  5953f1:      	decl	%ebx
  5953f2:      	decl	%ebx
  5953f3:      	decl	%ebx
  5953f4:      	decl	%ebx
  5953f5:      	decl	%ebx
  5953f6:      	decl	%ebx
  5953f7:      	decl	%ebx
  5953f8:      	decl	%ebx
  5953f9:      	decl	%ebx
  5953fa:      	decl	%ebx
  5953fb:      	decl	%ebx
  5953fc:      	decl	%ebx
  5953fd:      	decl	%ebx
  5953fe:      	decl	%ebx
  5953ff:      	decl	%ebx
  595400:      	decl	%ebx
  595401:      	decl	%ebx
  595402:      	decl	%ebx
  595403:      	decl	%ebx
  595404:      	decl	%ebx
  595405:      	decl	%ebx
  595406:      	decl	%ebx
  595407:      	decl	%ebx
  595408:      	decl	%ebx
  595409:      	decl	%ebx
  59540a:      	decl	%ebx
  59540b:      	decl	%ebx
  59540c:      	decl	%ebx
  59540d:      	decl	%ebx
  59540e:      	decl	%ebx
  59540f:      	decl	%ebx
  595410:      	decl	%ebx
  595411:      	decl	%ebx
  595412:      	decl	%ebx
  595413:      	decl	%ebx
  595414:      	decl	%ebx
  595415:      	decl	%ebx
  595416:      	decl	%ebx
  595417:      	decl	%ebx
  595418:      	decl	%ebx
  595419:      	decl	%ebx
  59541a:      	decl	%ebx
  59541b:      	decl	%ebx
  59541c:      	decl	%ebx
  59541d:      	decl	%ebx
  59541e:      	decl	%ebx
  59541f:      	decl	%ebx
  595420:      	decl	%ebx
  595421:      	andl	$0x29282726, %eax       # imm = 0x29282726
  595426:      	subb	(%ebx), %ch
  595428:      	subb	$0x2d, %al
  59542a:      	das
  59542c:      	xorb	%dh, (%ecx)
  59542e:      	xorb	(%ebx), %dh
  595430:      	xorb	$0x35, %al
  595432:      	aaa
  595434:      	cmpb	%bh, (%ecx)
  595436:      	cmpb	(%ebx), %bh
  595438:      	cmpb	$0x3d, %al
  59543a:      	aas
  59543c:      	decl	%ebx
  59543d:      	decl	%ebx
  59543e:      	decl	%ebx
  59543f:      	decl	%ebx
  595440:      	decl	%ebx
  595441:      	decl	%ebx
  595442:      	decl	%ebx
  595443:      	decl	%ebx
  595444:      	decl	%ebx
  595445:      	decl	%ebx
  595446:      	decl	%ebx
  595447:      	decl	%ebx
  595448:      	decl	%ebx
  595449:      	decl	%ebx
  59544a:      	decl	%ebx
  59544b:      	decl	%ebx
  59544c:      	decl	%ebx
  59544d:      	decl	%ebx
  59544e:      	decl	%ebx
  59544f:      	decl	%ebx
  595450:      	decl	%ebx
  595451:      	decl	%ebx
  595452:      	decl	%ebx
  595453:      	incl	%eax
  595454:      	incl	%ecx
  595455:      	incl	%edx
  595456:      	incl	%ebx
  595457:      	incl	%esp
  595458:      	incl	%ebp
  595459:      	incl	%esi
  59545a:      	incl	%edi
  59545b:      	decl	%eax
  59545c:      	decl	%ecx
  59545d:      	decl	%edx
  59545e:      	leal	(%ecx), %ecx
  595461:      	pushl	$0x720058ba             # imm = 0x720058BA
  595466:      	movl	$0xba7c0058, %edx       # imm = 0xBA7C0058
  59546b:      	popl	%eax
  59546c:      	addb	%al, 0x160058ba(%esi)
  595472:      	sbbb	(%ecx), %bl
  595475:      	nop
  595476:      	movl	$0xba9a0058, %edx       # imm = 0xBA9A0058
  59547b:      	popl	%eax
  59547c:      	addb	%dl, (%esi)
  59547e:      	sbbb	(%ecx), %bl
  595481:      	pushl	%ss
  595482:      	sbbb	(%ecx), %bl
  595485:      	pushl	%ss
  595486:      	sbbb	(%ecx), %bl
  595489:      	movsb	(%esi), %es:(%edi)
  59548a:      	movl	$0xbaae0058, %edx       # imm = 0xBAAE0058
  59548f:      	popl	%eax
  595490:      	addb	%ah, %dl
  595492:      	movl	$0xbaec0058, %edx       # imm = 0xBAEC0058
  595497:      	popl	%eax
  595498:      	addb	%dh, %dh
  59549a:      	movl	$0xbb000058, %edx       # imm = 0xBB000058
  59549f:      	popl	%eax
  5954a0:      	addb	%cl, (%edx)
  5954a2:      	movl	$0xbb140058, %ebx       # imm = 0xBB140058
  5954a7:      	popl	%eax
  5954a8:      	addb	%bl, (%esi)
  5954aa:      	movl	$0x1a160058, %ebx       # imm = 0x1A160058
  5954af:      	popl	%ecx
  5954b0:      	addb	%dl, (%esi)
  5954b2:      	sbbb	(%ecx), %bl
  5954b5:      	subb	%bh, 0x1a160058(%ebx)
  5954bb:      	popl	%ecx
  5954bc:      	addb	%dl, (%esi)
  5954be:      	sbbb	(%ecx), %bl
  5954c1:      	pushl	%ss
  5954c2:      	sbbb	(%ecx), %bl
  5954c5:      	xorb	-0x3fb3ffa8(%ebx), %bh
  5954cb:      	popl	%eax
  5954cc:      	addb	%dl, -0x40(%esi)
  5954cf:      	popl	%eax
  5954d0:      	addb	%ah, -0x40(%eax)
  5954d3:      	popl	%eax
  5954d4:      	addb	%ch, -0x40(%edx)
  5954d7:      	popl	%eax
  5954d8:      	addb	%dh, 0x58(%eax,%eax,8)
  5954dc:      	addb	%bh, -0x40(%esi)
  5954df:      	popl	%eax
  5954e0:      	addb	%cl, -0x6dffa740(%eax)
  5954e6:      	rcrb	$0x9c, (%eax)
  5954ea:      	rcrb	$0xa6, (%eax)
  5954ee:      	rcrb	$0xb0, (%eax)
  5954f2:      	rcrb	$0xba, (%eax)
  5954f6:      	rcrb	$0xc4, (%eax)
  5954fa:      	rcrb	$0xce, (%eax)
  5954fe:      	rcrb	$0xd8, (%eax)
  595502:      	rcrb	$0xe2, (%eax)
  595506:      	rcrb	$0xec, (%eax)
  59550a:      	rcrb	$0x16, (%eax)
  59550e:      	sbbb	(%ecx), %bl
  595511:      	testb	$0x58, %al
  595514:      	addb	%dh, %dl
  595516:      	rcrl	$0xfc, (%eax)
  59551a:      	rcrl	$0x6, (%eax)
  59551e:      	retl	$0x58
  595521:      	adcb	%al, %dl
  595523:      	popl	%eax
  595524:      	addb	%bl, (%edx)
  595526:      	retl	$0x58
  595529:      	andb	$-0x3e, %al
  59552b:      	popl	%eax
  59552c:      	addb	%ch, (%esi)
  59552e:      	retl	$0x58
  595531:      	cmpb	%al, %dl
  595533:      	popl	%eax
  595534:      	addb	%dh, 0x58(%edx,%eax,8)
  595538:      	addb	%bh, -0x3e(%esi)
  59553b:      	popl	%eax
  59553c:      	addb	%cl, -0x6dffa73e(%eax)
  595542:      	retl	$0x58
  595545:      	pushfl
  595546:      	retl	$0x58
  595549:      	cmpsb	%es:(%edi), (%esi)
  59554a:      	retl	$0x58
  59554d:      	movb	$-0x3e, %al
  59554f:      	popl	%eax
  595550:      	addb	%bh, -0x3bffa73e(%edx)
  595556:      	retl	$0x58
  595559:      	into
  59555a:      	retl	$0x58
  59555d:      	fadd	%st(2), %st
  59555f:      	popl	%eax
  595560:      	addb	%ah, %dl
  595562:      	retl	$0x58
  595565:      	inb	%dx, %al
  595566:      	retl	$0x58
  595569:      	testl	%eax, %esp
  59556b:      	popl	%eax
  59556c:      	addb	%cl, -0x66ffa73c(%edi)
  595572:      	lesl	(%eax), %ebx
  595575:      	movl	%eax, 0xad0058c4
  59557a:      	lesl	(%eax), %ebx
  59557d:      	movb	$-0x3c, %bh
  59557f:      	popl	%eax
  595580:      	addb	%al, %cl
  595582:      	lesl	(%eax), %ebx
  595585:      	lretl
  595586:      	lesl	(%eax), %ebx
  595589:      	aad	$-0x3c
  59558b:      	popl	%eax
  59558c:      	addb	%dl, (%esi)
  59558e:      	sbbb	(%ecx), %bl
  595591:      	addb	%cl, (%ecx)
  595593:      	orl	%ecx, (%ecx)
  595595:      	orl	%ecx, (%ecx)
  595597:      	addl	%eax, (%edx)
  595599:      	orl	%ecx, (%ecx)
  59559b:      	addl	-0x48f7f8fa(,%eax), %eax
  5955a2:      	ldsl	(%eax), %ebx
  5955a5:      	roll	$0x58, %ebp
  5955a8:      	addb	%cl, %bl
  5955aa:      	ldsl	(%eax), %ebx
  5955ad:      	aad	$-0x3b
  5955af:      	popl	%eax
  5955b0:      	addb	%bl, %bh
  5955b2:      	ldsl	(%eax), %ebx
  5955b5:      	jmp	0xf359ae7f
  5955ba:      	ldsl	(%eax), %ebx
  5955bd:      	std
  5955be:      	ldsl	(%eax), %ebx
  5955c1:      	popl	%es
  5955c2:      	<unknown>
  5955c5:      	<unknown>
  5955c9:      	cmpb	%al, %dh
  5955cb:      	popl	%eax
  5955cc:      	addb	%al, -0x3a(%edx)
  5955cf:      	popl	%eax
  5955d0:      	addb	%cl, 0x58(%esi,%eax,8)
  5955d4:      	addb	%dl, -0x3a(%esi)
  5955d7:      	popl	%eax
  5955d8:      	addb	%ah, -0x3a(%eax)
  5955db:      	popl	%eax
  5955dc:      	addb	%ch, -0x3a(%edx)
  5955df:      	popl	%eax
  5955e0:      	addb	%dh, 0x58(%esi,%eax,8)
  5955e4:      	addb	%bh, -0x3a(%esi)
  5955e7:      	popl	%eax
  5955e8:      	addb	%cl, -0x6dffa73a(%eax)
  5955ee:      	<unknown>
  5955f1:      	pushfl
  5955f2:      	<unknown>
  5955f5:      	cmpsb	%es:(%edi), (%esi)
  5955f6:      	<unknown>
  5955f9:      	movb	$-0x3a, %al
  5955fb:      	popl	%eax
  5955fc:      	addb	%bh, -0x3bffa73a(%edx)
  595602:      	<unknown>
  595605:      	into
  595606:      	<unknown>
  595609:      	fadd	%st(6), %st
  59560b:      	popl	%eax
  59560c:      	addb	%ah, %dl
  59560e:      	<unknown>
  595611:      	inb	%dx, %al
  595612:      	<unknown>
  595615:      	testb	$0x58, %dh
  595618:      	addb	%al, (%eax)
  59561a:      	<unknown>
  59561d:      	orb	%bh, %al
  59561f:      	popl	%eax
  595620:      	addb	%dl, (%esi)
  595622:      	sbbb	(%ecx), %bl
  595625:      	adcb	$-0x39, %al
  595627:      	popl	%eax
  595628:      	addb	%dl, (%esi)
  59562a:      	sbbb	(%ecx), %bl
  59562d:      	pushl	%ds
  59562e:      	<unknown>
  595631:      	subb	%al, %bh
  595633:      	popl	%eax
  595634:      	addb	%dl, (%esi)
  595636:      	sbbb	(%ecx), %bl
  595639:      	pushl	%ss
  59563a:      	sbbb	(%ecx), %bl
  59563d:      	pushl	%ss
  59563e:      	sbbb	(%ecx), %bl
  595641:      	pushl	%ss
  595642:      	sbbb	(%ecx), %bl
  595645:      	pushl	%ss
  595646:      	sbbb	(%ecx), %bl
  595649:      	pushl	%ss
  59564a:      	sbbb	(%ecx), %bl
  59564d:      	pushl	%ss
  59564e:      	sbbb	(%ecx), %bl
  595651:      	pushl	%ss
  595652:      	sbbb	(%ecx), %bl
  595655:      	pushl	%ss
  595656:      	sbbb	(%ecx), %bl
  595659:      	pushl	%ss
  59565a:      	sbbb	(%ecx), %bl
  59565d:      	xorb	%bh, %al
  59565f:      	popl	%eax
  595660:      	addb	%bh, (%edi,%eax,8)
  595663:      	popl	%eax
  595664:      	addb	%al, -0x39(%esi)
  595667:      	popl	%eax
  595668:      	addb	%dl, -0x39(%eax)
  59566b:      	popl	%eax
  59566c:      	addb	%bl, -0x39(%edx)
  59566f:      	popl	%eax
  595670:      	addb	%ah, 0x58(%edi,%eax,8)
  595674:      	addb	%ch, -0x39(%esi)
  595677:      	popl	%eax
  595678:      	addb	%bh, -0x39(%eax)
  59567b:      	popl	%eax
  59567c:      	addb	%al, -0x73ffa739(%edx)
  595682:      	<unknown>
  595685:      	xchgl	%esi, %eax
  595686:      	<unknown>
  595689:      	movb	0xaa0058c7, %al
  59568e:      	<unknown>
  595691:      	roll	%edi
  595693:      	popl	%eax
  595694:      	addb	%bl, %bl
  595696:      	<unknown>
  595699:      	inl	$0xc7, %eax
  59569b:      	popl	%eax
  59569c:      	addb	%ch, %bh
  59569e:      	<unknown>
  5956a1:      	stc
  5956a2:      	<unknown>
  5956a5:      	addl	%eax, %ecx
  5956a7:      	popl	%eax
  5956a8:      	addb	%cl, 0x170058c8
  5956ae:      	enter	$0x58, $0x21
  5956b2:      	enter	$0x58, $0x16
  5956b6:      	sbbb	(%ecx), %bl
  5956b9:      	pushl	%ss
  5956ba:      	sbbb	(%ecx), %bl
  5956bd:      	pushl	%ss
  5956be:      	sbbb	(%ecx), %bl
  5956c1:      	pushl	%ss
  5956c2:      	sbbb	(%ecx), %bl
  5956c5:      	pushl	%ss
  5956c6:      	sbbb	(%ecx), %bl
  5956c9:      	pushl	%ss
  5956ca:      	sbbb	(%ecx), %bl
  5956cd:      	pushl	%ss
  5956ce:      	sbbb	(%ecx), %bl
  5956d1:      	subl	%eax, %ecx
  5956d3:      	popl	%eax
  5956d4:      	addb	%dl, (%esi)
  5956d6:      	sbbb	(%ecx), %bl
  5956d9:      	xorl	$0x3f0058c8, %eax       # imm = 0x3F0058C8
  5956de:      	enter	$0x58, $0x49
  5956e2:      	enter	$0x58, $0x53
  5956e6:      	enter	$0x58, $0x5d
  5956ea:      	enter	$0x58, $0x67
  5956ee:      	enter	$0x58, $0x71
  5956f2:      	enter	$0x58, $0x7b
  5956f6:      	enter	$0x58, $0x16
  5956fa:      	sbbb	(%ecx), %bl
  5956fd:      	pushl	%ss
  5956fe:      	sbbb	(%ecx), %bl
  595701:      	pushl	%ss
  595702:      	sbbb	(%ecx), %bl
  595705:      	pushl	%ss
  595706:      	sbbb	(%ecx), %bl
  595709:      	pushl	%ss
  59570a:      	sbbb	(%ecx), %bl
  59570d:      	pushl	%ss
  59570e:      	sbbb	(%ecx), %bl
  595711:      	pushl	%ss
  595712:      	sbbb	(%ecx), %bl
  595715:      	pushl	%ss
  595716:      	sbbb	(%ecx), %bl
  595719:      	pushl	%ss
  59571a:      	sbbb	(%ecx), %bl
  59571d:      	pushl	%ss
  59571e:      	sbbb	(%ecx), %bl
  595721:      	testl	%ecx, %eax
  595723:      	popl	%eax
  595724:      	addb	%cl, -0x66ffa738(%edi)
  59572a:      	enter	$0x58, $-0x5d
  59572e:      	enter	$0x58, $-0x53
  595732:      	enter	$0x58, $-0x49
  595736:      	enter	$0x58, $-0x3f
  59573a:      	enter	$0x58, $-0x35
  59573e:      	enter	$0x58, $-0x2b
  595742:      	enter	$0x58, $-0x21
  595746:      	enter	$0x58, $-0x17
  59574a:      	enter	$0x58, $-0xd
  59574e:      	enter	$0x58, $-0x3
  595752:      	enter	$0x58, $0x7
  595756:      	leave
  595757:      	popl	%eax
  595758:      	addb	%dl, (%ecx)
  59575a:      	leave
  59575b:      	popl	%eax
  59575c:      	addb	%dl, (%esi)
  59575e:      	sbbb	(%ecx), %bl
  595761:      	pushl	%ss
  595762:      	sbbb	(%ecx), %bl
  595765:      	sbbl	%ecx, %ecx
  595767:      	popl	%eax
  595768:      	addb	%ah, 0x2f0058c9
  59576e:      	leave
  59576f:      	popl	%eax
  595770:      	addb	%bh, (%ecx)
  595772:      	leave
  595773:      	popl	%eax
  595774:      	addb	%al, -0x37(%ebx)
  595777:      	popl	%eax
  595778:      	addb	%cl, -0x37(%ebp)
  59577b:      	popl	%eax
  59577c:      	addb	%dl, -0x37(%edi)
  59577f:      	popl	%eax
  595780:      	addb	%ah, -0x37(%ecx)
  595783:      	popl	%eax
  595784:      	addb	%ch, -0x37(%ebx)
  595787:      	popl	%eax
  595788:      	addb	%dh, -0x37(%ebp)
  59578b:      	popl	%eax
  59578c:      	addb	%bh, -0x37(%edi)
  59578f:      	popl	%eax
  595790:      	addb	%cl, -0x6cffa737(%ecx)
  595796:      	leave
  595797:      	popl	%eax
  595798:      	addb	%bl, -0x58ffa737(%ebp)
  59579e:      	leave
  59579f:      	popl	%eax
  5957a0:      	addb	%dh, -0x44ffa737(%ecx)
  5957a6:      	leave
  5957a7:      	popl	%eax
  5957a8:      	addb	%al, %ch
  5957aa:      	leave
  5957ab:      	popl	%eax
  5957ac:      	addb	%cl, %bh
  5957ae:      	leave
  5957af:      	popl	%eax
  5957b0:      	addb	%bl, %cl
  5957b2:      	leave
  5957b3:      	popl	%eax
  5957b4:      	addb	%ah, %bl
  5957b6:      	leave
  5957b7:      	popl	%eax
  5957b8:      	addb	%ch, %ch
  5957ba:      	leave
  5957bb:      	popl	%eax
  5957bc:      	addb	%dh, %bh
  5957be:      	leave
  5957bf:      	popl	%eax
  5957c0:      	addb	%al, (%ecx)
  5957c2:      	lretl	$0x58
  5957c5:      	orl	%edx, %ecx
  5957c7:      	popl	%eax
  5957c8:      	addb	%dl, 0x1f0058ca
  5957ce:      	lretl	$0x58
  5957d1:      	subl	%ecx, %edx
  5957d3:      	popl	%eax
  5957d4:      	addb	%dh, (%ebx)
  5957d6:      	lretl	$0x58
  5957d9:      	cmpl	$0x470058ca, %eax       # imm = 0x470058CA
  5957de:      	lretl	$0x58
  5957e1:      	pushl	%ecx
  5957e2:      	lretl	$0x58
  5957e5:      	popl	%ebx
  5957e6:      	lretl	$0x58
  5957e9:      	lretl	$0x58
  5957ed:      	outsl	(%esi), %dx
  5957ee:      	lretl	$0x58
  5957f1:      	jns	0x5957bd <.text+0x1947bd>
  5957f3:      	popl	%eax
  5957f4:      	addb	%al, -0x72ffa736(%ebx)
  5957fa:      	lretl	$0x58
  5957fd:      	xchgl	%edi, %eax
  5957fe:      	lretl	$0x58
  595801:      	movl	0xab0058ca, %eax
  595806:      	lretl	$0x58
  595809:      	movb	$-0x36, %ch
  59580b:      	popl	%eax
  59580c:      	addb	%bh, -0x36ffa736(%edi)
  595812:      	lretl	$0x58
  595815:      	rorl	%cl, %edx
  595817:      	popl	%eax
  595818:      	addb	%bl, %ch
  59581a:      	lretl	$0x58
  59581d:      	pushl	%ss
  59581e:      	sbbb	(%ecx), %bl
  595821:      	outl	%eax, $0xca
  595823:      	popl	%eax
  595824:      	addb	%bh, 0x470058cb
  59582a:      	lretl
  59582b:      	popl	%eax
  59582c:      	addb	%dl, -0x35(%ecx)
  59582f:      	popl	%eax
  595830:      	addb	%bl, -0x35(%ebx)
  595833:      	popl	%eax
  595834:      	addb	%ah, -0x35(%ebp)
  595837:      	popl	%eax
  595838:      	addb	%ch, -0x35(%edi)
  59583b:      	popl	%eax
  59583c:      	addb	%bh, -0x35(%ecx)
  59583f:      	popl	%eax
  595840:      	addb	%al, -0x72ffa735(%ebx)
  595846:      	lretl
  595847:      	popl	%eax
  595848:      	addb	%dl, -0x5effa735(%edi)
  59584e:      	lretl
  59584f:      	popl	%eax
  595850:      	addb	%ch, -0x4affa735(%ebx)
  595856:      	lretl
  595857:      	popl	%eax
  595858:      	addb	%bh, -0x36ffa735(%edi)
  59585e:      	lretl
  59585f:      	popl	%eax
  595860:      	addb	%dl, %bl
  595862:      	lretl
  595863:      	popl	%eax
  595864:      	addb	%bl, %ch
  595866:      	lretl
  595867:      	popl	%eax
  595868:      	addb	%ah, %bh
  59586a:      	lretl
  59586b:      	popl	%eax
  59586c:      	addb	%dh, %cl
  59586e:      	lretl
  59586f:      	popl	%eax
  595870:      	addb	%bh, %bl
  595872:      	lretl
  595873:      	popl	%eax
  595874:      	addb	%al, 0xf0058cc
  59587a:      	int3
  59587b:      	popl	%eax
  59587c:      	addb	%bl, (%ecx)
  59587e:      	int3
  59587f:      	popl	%eax
  595880:      	addb	%ah, (%ebx)
  595882:      	int3
  595883:      	popl	%eax
  595884:      	addb	%ch, 0x370058cc
  59588a:      	int3
  59588b:      	popl	%eax
  59588c:      	addb	%al, -0x34(%ecx)
  59588f:      	popl	%eax
  595890:      	addb	%cl, -0x34(%ebx)
  595893:      	popl	%eax
  595894:      	addb	%dl, -0x34(%ebp)
  595897:      	popl	%eax
  595898:      	addb	%bl, -0x34(%edi)
  59589b:      	popl	%eax
  59589c:      	addb	%ch, -0x34(%ecx)
  59589f:      	popl	%eax
  5958a0:      	addb	%dh, -0x34(%ebx)
  5958a3:      	popl	%eax
  5958a4:      	addb	%bh, -0x34(%ebp)
  5958a7:      	popl	%eax
  5958a8:      	addb	%al, -0x6effa734(%edi)
  5958ae:      	int3
  5958af:      	popl	%eax
  5958b0:      	addb	%bl, -0x5affa734(%ebx)
  5958b6:      	int3
  5958b7:      	popl	%eax
  5958b8:      	addb	%ch, -0x46ffa734(%edi)
  5958be:      	int3
  5958bf:      	popl	%eax
  5958c0:      	addb	%al, %bl
  5958c2:      	int3
  5958c3:      	popl	%eax
  5958c4:      	addb	%dl, (%esi)
  5958c6:      	sbbb	(%ecx), %bl
  5958c9:      	addb	%ch, (%eax)
  5958cb:      	subb	%al, (%ecx)
  5958cd:      	addb	(%eax), %ch
  5958cf:      	subb	%ch, (%eax)
  5958d1:      	subb	%ch, (%eax)
  5958d3:      	addl	(%eax), %ebp
  5958d5:      	addb	$0x5, %al
  5958d7:      	subb	%ch, (%eax)
  5958d9:      	pushl	%es
  5958da:      	popl	%es
  5958db:      	orb	%cl, (%ecx)
  5958dd:      	orb	(%ebx), %cl
  5958df:      	orb	$0xd, %al
  5958e1:      	pushl	%cs
  5958e2:      	movups	(%ecx), %xmm2
  5958e5:      	adcb	(%ebx), %dl
  5958e7:      	adcb	$0x15, %al
  5958e9:      	pushl	%ss
  5958ea:      	popl	%ss
  5958eb:      	subb	%bl, (%eax)
  5958ed:      	sbbl	%ebx, (%edx)
  5958ef:      	sbbl	0x1f281e28(,%ebx), %ebx
  5958f6:      	andb	%ah, (%ecx)
  5958f8:      	subb	%ch, (%eax)
  5958fa:      	subb	%ch, (%eax)
  5958fc:      	subb	%ch, (%eax)
  5958fe:      	subb	%ch, (%eax)
  595900:      	subb	%ch, (%eax)
  595902:      	subb	%ch, (%eax)
  595904:      	subb	%ah, (%edx)
  595906:      	andl	0x28282826(,%eiz), %esp
  59590d:      	subb	%ch, (%eax)
  59590f:      	daa
  595910:      	nop
  595911:      	inl	$0xce, %eax
  595913:      	popl	%eax
  595914:      	addb	%ch, %bh
  595916:      	into
  595917:      	popl	%eax
  595918:      	addb	%bh, %cl
  59591a:      	into
  59591b:      	popl	%eax
  59591c:      	addb	%al, (%ebx)
  59591e:      	iretl
  59591f:      	popl	%eax
  595920:      	addb	%cl, 0x170058cf
  595926:      	iretl
  595927:      	popl	%eax
  595928:      	addb	%ah, (%ecx)
  59592a:      	iretl
  59592b:      	popl	%eax
  59592c:      	addb	%ch, (%ebx)
  59592e:      	iretl
  59592f:      	popl	%eax
  595930:      	addb	%dh, 0x670058cf
  595936:      	iretl
  595937:      	popl	%eax
  595938:      	addb	%dh, -0x31(%ecx)
  59593b:      	popl	%eax
  59593c:      	addb	%bh, -0x31(%ebx)
  59593f:      	popl	%eax
  595940:      	addb	%al, -0x70ffa731(%ebp)
  595946:      	iretl
  595947:      	popl	%eax
  595948:      	addb	%bl, -0x5cffa731(%ecx)
  59594e:      	iretl
  59594f:      	popl	%eax
  595950:      	addb	%ch, -0x48ffa731(%ebp)
  595956:      	iretl
  595957:      	popl	%eax
  595958:      	addb	%al, %cl
  59595a:      	iretl
  59595b:      	popl	%eax
  59595c:      	addb	%cl, %bl
  59595e:      	iretl
  59595f:      	popl	%eax
  595960:      	addb	%dl, %ch
  595962:      	iretl
  595963:      	popl	%eax
  595964:      	addb	%bl, %bh
  595966:      	iretl
  595967:      	popl	%eax
  595968:      	addb	%ch, %cl
  59596a:      	iretl
  59596b:      	popl	%eax
  59596c:      	addb	%dh, %bl
  59596e:      	iretl
  59596f:      	popl	%eax
  595970:      	addb	%bh, %ch
  595972:      	iretl
  595973:      	popl	%eax
  595974:      	addb	%al, (%edi)
  595976:      	rcrb	(%eax)
  595979:      	adcl	%edx, %eax
  59597b:      	popl	%eax
  59597c:      	addb	%bl, (%ebx)
  59597e:      	rcrb	(%eax)
  595981:      	andl	$0x2f0058d0, %eax       # imm = 0x2F0058D0
  595986:      	rcrb	(%eax)
  595989:      	cmpl	%edx, %eax
  59598b:      	popl	%eax
  59598c:      	addb	%al, -0x30(%ebx)
  59598f:      	popl	%eax
  595990:      	addb	%cl, -0x30(%ebp)
  595993:      	popl	%eax
  595994:      	addb	%dl, -0x30(%edi)
  595997:      	popl	%eax
  595998:      	addb	%ah, -0x30(%ecx)
  59599b:      	popl	%eax
  59599c:      	addb	%ch, -0x30(%ebx)
  59599f:      	popl	%eax
  5959a0:      	addb	%dh, -0x30(%ebp)
  5959a3:      	popl	%eax
  5959a4:      	addb	%bh, -0x30(%edi)
  5959a7:      	popl	%eax
  5959a8:      	addb	%cl, -0x6cffa730(%ecx)
  5959ae:      	rcrb	(%eax)
  5959b1:      	popfl
  5959b2:      	rcrb	(%eax)
  5959b5:      	cmpsl	%es:(%edi), (%esi)
  5959b6:      	rcrb	(%eax)
  5959b9:      	movb	$-0x30, %cl
  5959bb:      	popl	%eax
  5959bc:      	addb	%bh, -0x3affa730(%ebx)
  5959c2:      	rcrb	(%eax)
  5959c5:      	iretl
  5959c6:      	rcrb	(%eax)
  5959c9:      	fnop
  5959cb:      	popl	%eax
  5959cc:      	addb	%ah, %bl
  5959ce:      	rcrb	(%eax)
  5959d1:      	inl	%dx, %eax
  5959d2:      	rcrb	(%eax)
  5959d5:      	notl	%eax
  5959d7:      	popl	%eax
  5959d8:      	addb	%al, (%ecx)
  5959da:      	rcrl	(%eax)
  5959dd:      	orl	%ecx, %edx
  5959df:      	popl	%eax
  5959e0:      	addb	%bh, -0x2e(%ebp)
  5959e3:      	popl	%eax
  5959e4:      	addb	%dl, 0x1f0058d1
  5959ea:      	rcrl	(%eax)
  5959ed:      	subl	%edx, %ecx
  5959ef:      	popl	%eax
  5959f0:      	addb	%dh, (%ebx)
  5959f2:      	rcrl	(%eax)
  5959f5:      	cmpl	$0x470058d1, %eax       # imm = 0x470058D1
  5959fa:      	rcrl	(%eax)
  5959fd:      	pushl	%ecx
  5959fe:      	rcrl	(%eax)
  595a01:      	popl	%ebx
  595a02:      	rcrl	(%eax)
  595a05:      	rcrl	%gs:(%eax)
  595a09:      	outsl	(%esi), %dx
  595a0a:      	rcrl	(%eax)
  595a0d:      	jns	0x5959e0 <.text+0x1949e0>
  595a0f:      	popl	%eax
  595a10:      	addb	%al, -0x72ffa72f(%ebx)
  595a16:      	rcrl	(%eax)
  595a19:      	xchgl	%edi, %eax
  595a1a:      	rcrl	(%eax)
  595a1d:      	movl	0xab0058d1, %eax
  595a22:      	rcrl	(%eax)
  595a25:      	movb	$-0x2f, %ch
  595a27:      	popl	%eax
  595a28:      	addb	%bh, -0x36ffa72f(%edi)
  595a2e:      	rcrl	(%eax)
  595a31:      	rcll	%cl, %ecx
  595a33:      	popl	%eax
  595a34:      	addb	%bl, %ch
  595a36:      	rcrl	(%eax)
  595a39:      	outl	%eax, $0xd1
  595a3b:      	popl	%eax
  595a3c:      	addb	%dh, %cl
  595a3e:      	rcrl	(%eax)
  595a41:      	sti
  595a42:      	rcrl	(%eax)
  595a45:      	addl	$0xf0058d2, %eax        # imm = 0xF0058D2
  595a4a:      	rcrb	%cl, (%eax)
  595a4d:      	sbbl	%edx, %edx
  595a4f:      	popl	%eax
  595a50:      	addb	%ah, (%ebx)
  595a52:      	rcrb	%cl, (%eax)
  595a55:      	subl	$0x370058d2, %eax       # imm = 0x370058D2
  595a5a:      	rcrb	%cl, (%eax)
  595a5d:      	incl	%ecx
  595a5e:      	rcrb	%cl, (%eax)
  595a61:      	decl	%ebx
  595a62:      	rcrb	%cl, (%eax)
  595a65:      	pushl	%ebp
  595a66:      	rcrb	%cl, (%eax)
  595a69:      	popl	%edi
  595a6a:      	rcrb	%cl, (%eax)
  595a6d:      	imull	$0xd2730058, %edx, %edx # imm = 0xD2730058
  595a73:      	popl	%eax
  595a74:      	addb	%dl, (%esi)
  595a76:      	sbbb	(%ecx), %bl
  595a79:      	addb	%al, (%ecx)
  595a7b:      	addb	(%ebx), %al
  595a7d:      	addb	$0x5, %al
  595a7f:      	pushl	%es
  595a80:      	popl	%es
  595a81:      	orb	%cl, (%ecx)
  595a83:      	pushl	%eax
  595a84:      	pushl	%eax
  595a85:      	pushl	%eax
  595a86:      	pushl	%eax
  595a87:      	pushl	%eax
  595a88:      	pushl	%eax
  595a89:      	pushl	%eax
  595a8a:      	pushl	%eax
  595a8b:      	pushl	%eax
  595a8c:      	pushl	%eax
  595a8d:      	pushl	%eax
  595a8e:      	pushl	%eax
  595a8f:      	pushl	%eax
  595a90:      	pushl	%eax
  595a91:      	pushl	%eax
  595a92:      	pushl	%eax
  595a93:      	pushl	%eax
  595a94:      	pushl	%eax
  595a95:      	pushl	%eax
  595a96:      	pushl	%eax
  595a97:      	pushl	%eax
  595a98:      	pushl	%eax
  595a99:      	pushl	%eax
  595a9a:      	pushl	%eax
  595a9b:      	pushl	%eax
  595a9c:      	pushl	%eax
  595a9d:      	pushl	%eax
  595a9e:      	pushl	%eax
  595a9f:      	orb	(%ebx), %cl
  595aa1:      	orb	$0xd, %al
  595aa3:      	pushl	%cs
  595aa4:      	movups	(%ecx), %xmm2
  595aa7:      	adcb	(%ebx), %dl
  595aa9:      	adcb	$0x15, %al
  595aab:      	pushl	%ss
  595aac:      	popl	%ss
  595aad:      	sbbb	%bl, (%ecx)
  595aaf:      	sbbb	(%ebx), %bl
  595ab1:      	sbbb	$0x1d, %al
  595ab3:      	pushl	%ds
  595ab4:      	popl	%ds
  595ab5:      	andb	%ah, (%ecx)
  595ab7:      	andb	(%ebx), %ah
  595ab9:      	andb	$0x25, %al
  595abb:      	daa
  595abd:      	subb	%ch, (%ecx)
  595abf:      	subb	(%ebx), %ch
  595ac1:      	pushl	%eax
  595ac2:      	pushl	%eax
  595ac3:      	pushl	%eax
  595ac4:      	pushl	%eax
  595ac5:      	pushl	%eax
  595ac6:      	pushl	%eax
  595ac7:      	pushl	%eax
  595ac8:      	pushl	%eax
  595ac9:      	pushl	%eax
  595aca:      	pushl	%eax
  595acb:      	pushl	%eax
  595acc:      	pushl	%eax
  595acd:      	pushl	%eax
  595ace:      	pushl	%eax
  595acf:      	pushl	%eax
  595ad0:      	subb	$0x2d, %al
  595ad2:      	das
  595ad4:      	xorb	%dh, (%ecx)
  595ad6:      	xorb	(%ebx), %dh
  595ad8:      	xorb	$0x35, %al
  595ada:      	aaa
  595adc:      	cmpb	%bh, (%ecx)
  595ade:      	cmpb	(%ebx), %bh
  595ae0:      	cmpb	$0x3d, %al
  595ae2:      	aas
  595ae4:      	incl	%eax
  595ae5:      	incl	%ecx
  595ae6:      	incl	%edx
  595ae7:      	incl	%ebx
  595ae8:      	incl	%esp
  595ae9:      	incl	%ebp
  595aea:      	incl	%esi
  595aeb:      	incl	%edi
  595aec:      	decl	%eax
  595aed:      	decl	%ecx
  595aee:      	decl	%edx
  595aef:      	decl	%ebx
  595af0:      	decl	%esp
  595af1:      	pushl	%eax
  595af2:      	pushl	%eax
  595af3:      	pushl	%eax
  595af4:      	pushl	%eax
  595af5:      	pushl	%eax
  595af6:      	pushl	%eax
  595af7:      	pushl	%eax
  595af8:      	decl	%ebp
  595af9:      	decl	%esi
  595afa:      	decl	%edi
  595afb:      	movl	%edi, %edi
  595afd:      	testb	$-0x2e, %al
  595aff:      	popl	%eax
  595b00:      	addb	%dh, -0x43ffa72e(%edx)
  595b06:      	rcrb	%cl, (%eax)
  595b09:      	<unknown>
  595b0b:      	popl	%eax
  595b0c:      	addb	%dl, %al
  595b0e:      	rcrb	%cl, (%eax)
  595b11:      	fcmovbe	%st(2), %st
  595b13:      	popl	%eax
  595b14:      	addb	%ah, %ah
  595b16:      	rcrb	%cl, (%eax)
  595b19:      	outb	%al, %dx
  595b1a:      	rcrb	%cl, (%eax)
  595b1d:      	clc
  595b1e:      	rcrb	%cl, (%eax)
  595b21:      	addb	%bl, %dl
  595b23:      	popl	%eax
  595b24:      	addb	%cl, (%ebx,%edx,8)
  595b27:      	popl	%eax
  595b28:      	addb	%dl, (%esi)
  595b2a:      	rcrl	%cl, (%eax)
  595b2d:      	andb	%dl, %bl
  595b2f:      	popl	%eax
  595b30:      	addb	%ch, (%edx)
  595b32:      	rcrl	%cl, (%eax)
  595b35:      	xorb	$-0x2d, %al
  595b37:      	popl	%eax
  595b38:      	addb	%bh, (%esi)
  595b3a:      	rcrl	%cl, (%eax)
  595b3d:      	decl	%eax
  595b3e:      	rcrl	%cl, (%eax)
  595b41:      	pushl	%edx
  595b42:      	rcrl	%cl, (%eax)
  595b45:      	popl	%esp
  595b46:      	rcrl	%cl, (%eax)
  595b49:      	rcrw	%cl, (%eax)
  595b4d:      	jo	0x595b22 <.text+0x194b22>
  595b4f:      	popl	%eax
  595b50:      	addb	%bh, -0x2d(%edx)
  595b53:      	popl	%eax
  595b54:      	addb	%al, 0x1a160058(%ebx,%edx,8)
  595b5b:      	popl	%ecx
  595b5c:      	addb	%cl, -0x67ffa72d(%esi)
  595b62:      	rcrl	%cl, (%eax)
  595b65:      	movb	%al, 0xac0058d3
  595b6a:      	rcrl	%cl, (%eax)
  595b6d:      	movb	$-0x2d, %dh
  595b6f:      	popl	%eax
  595b70:      	addb	%al, %al
  595b72:      	rcrl	%cl, (%eax)
  595b75:      	decl	%eax
  595b76:      	fstpl	(%eax)
  595b79:      	pushl	%ss
  595b7a:      	sbbb	(%ecx), %bl
  595b7d:      	pushl	%ss
  595b7e:      	sbbb	(%ecx), %bl
  595b81:      	pushl	%ss
  595b82:      	sbbb	(%ecx), %bl
  595b85:      	pushl	%ss
  595b86:      	sbbb	(%ecx), %bl
  595b89:      	pushl	%ss
  595b8a:      	sbbb	(%ecx), %bl
  595b8d:      	pushl	%ss
  595b8e:      	sbbb	(%ecx), %bl
  595b91:      	pushl	%ss
  595b92:      	sbbb	(%ecx), %bl
  595b95:      	pushl	%ss
  595b96:      	sbbb	(%ecx), %bl
  595b99:      	pushl	%ss
  595b9a:      	sbbb	(%ecx), %bl
  595b9d:      	pushl	%ss
  595b9e:      	sbbb	(%ecx), %bl
  595ba1:      	pushl	%ss
  595ba2:      	sbbb	(%ecx), %bl
  595ba5:      	pushl	%ss
  595ba6:      	sbbb	(%ecx), %bl
  595ba9:      	pushl	%ss
  595baa:      	sbbb	(%ecx), %bl
  595bad:      	pushl	%ss
  595bae:      	sbbb	(%ecx), %bl
  595bb1:      	pushl	%ss
  595bb2:      	sbbb	(%ecx), %bl
  595bb5:      	pushl	%ss
  595bb6:      	sbbb	(%ecx), %bl
  595bb9:      	pushl	%ss
  595bba:      	sbbb	(%ecx), %bl
  595bbd:      	pushl	%ss
  595bbe:      	sbbb	(%ecx), %bl
  595bc1:      	lretl	$0x58d3                 # imm = 0x58D3
  595bc4:      	addb	%dl, %ah
  595bc6:      	rcrl	%cl, (%eax)
  595bc9:      	<unknown>
  595bcb:      	popl	%eax
  595bcc:      	addb	%ch, %al
  595bce:      	rcrl	%cl, (%eax)
  595bd1:      	repne		rcrl	%cl, (%eax)
  595bd5:      	cld
  595bd6:      	rcrl	%cl, (%eax)
  595bd9:      	pushl	%es
  595bda:      	aam	$0x58
  595bdc:      	addb	%dl, (%eax)
  595bde:      	aam	$0x58
  595be0:      	addb	%bl, (%edx)
  595be2:      	aam	$0x58
  595be4:      	addb	%ah, (%esp,%edx,8)
  595be7:      	popl	%eax
  595be8:      	addb	%ch, (%esi)
  595bea:      	aam	$0x58
  595bec:      	addb	%bh, (%eax)
  595bee:      	aam	$0x58
  595bf0:      	addb	%al, -0x2c(%edx)
  595bf3:      	popl	%eax
  595bf4:      	addb	%cl, 0x58(%esp,%edx,8)
  595bf8:      	addb	%dl, -0x2c(%esi)
  595bfb:      	popl	%eax
  595bfc:      	addb	%ah, -0x2c(%eax)
  595bff:      	popl	%eax
  595c00:      	addb	%ch, -0x2c(%edx)
  595c03:      	popl	%eax
  595c04:      	addb	%dh, 0x58(%esp,%edx,8)
  595c08:      	addb	%bh, -0x2c(%esi)
  595c0b:      	popl	%eax
  595c0c:      	addb	%cl, -0x6dffa72c(%eax)
  595c12:      	aam	$0x58
  595c14:      	addb	%bl, -0x2b59ffa8(%esp,%edx,8)
  595c1b:      	popl	%eax
  595c1c:      	addb	%dh, -0x45ffa72c(%eax)
  595c22:      	aam	$0x58
  595c24:      	addb	%al, %ah
  595c26:      	aam	$0x58
  595c28:      	addb	%cl, %dh
  595c2a:      	aam	$0x58
  595c2c:      	addb	%bl, %al
  595c2e:      	aam	$0x58
  595c30:      	addb	%ah, %dl
  595c32:      	aam	$0x58
  595c34:      	addb	%ch, %ah
  595c36:      	aam	$0x58
  595c38:      	addb	%dh, %dh
  595c3a:      	aam	$0x58
  595c3c:      	addb	%al, (%eax)
  595c3e:      	aad	$0x58
  595c40:      	addb	%cl, (%edx)
  595c42:      	aad	$0x58
  595c44:      	addb	%dl, -0x2ae1ffa8(,%edx,8)
  595c4b:      	popl	%eax
  595c4c:      	addb	%ch, (%eax)
  595c4e:      	aad	$0x58
  595c50:      	addb	%dh, (%edx)
  595c52:      	aad	$0x58
  595c54:      	addb	%bh, -0x2ab9ffa8(,%edx,8)
  595c5b:      	popl	%eax
  595c5c:      	addb	%dl, -0x2b(%eax)
  595c5f:      	popl	%eax
  595c60:      	addb	%bl, -0x2b(%edx)
  595c63:      	popl	%eax
  595c64:      	addb	%ah, 0x58(%ebp,%edx,8)
  595c68:      	addb	%ch, -0x2b(%esi)
  595c6b:      	popl	%eax
  595c6c:      	addb	%bh, -0x2b(%eax)
  595c6f:      	popl	%eax
  595c70:      	addb	%al, -0x73ffa72b(%edx)
  595c76:      	aad	$0x58
  595c78:      	addb	%dl, -0x5fffa72b(%esi)
  595c7e:      	aad	$0x58
  595c80:      	addb	%ch, -0x4bffa72b(%edx)
  595c86:      	aad	$0x58
  595c88:      	addb	%bh, 0x520058d5(%esi)
  595c8e:      	fstpl	(%eax)
  595c91:      	popl	%esp
  595c92:      	fstpl	(%eax)
  595c95:      	fstpl	(%eax)
  595c99:      	jo	0x595c78 <.text+0x194c78>
  595c9b:      	popl	%eax
  595c9c:      	addb	%bh, -0x23(%edx)
  595c9f:      	popl	%eax
  595ca0:      	addb	%al, -0x2271ffa8(%ebp,%ebx,8)
  595ca7:      	popl	%eax
  595ca8:      	addb	%bl, -0x5dffa723(%eax)
  595cae:      	fstpl	(%eax)
  595cb1:      	lodsb	(%esi), %al
  595cb2:      	fstpl	(%eax)
  595cb5:      	movb	$-0x23, %dh
  595cb7:      	popl	%eax
  595cb8:      	addb	%al, %al
  595cba:      	fstpl	(%eax)
  595cbd:      	lretl	$0x58dd                 # imm = 0x58DD
  595cc0:      	addb	%dl, %ah
  595cc2:      	fstpl	(%eax)
  595cc5:      	<unknown>
  595cc7:      	popl	%eax
  595cc8:      	addb	%dl, (%esi)
  595cca:      	sbbb	(%ecx), %bl
  595ccd:      	pushl	%ss
  595cce:      	sbbb	(%ecx), %bl
  595cd1:      	pushl	%ss
  595cd2:      	sbbb	(%ecx), %bl
  595cd5:      	pushl	%ss
  595cd6:      	sbbb	(%ecx), %bl
  595cd9:      	pushl	%ss
  595cda:      	sbbb	(%ecx), %bl
  595cdd:      	calll	0x1659b5bf
  595ce2:      	sbbb	(%ecx), %bl
  595ce5:      	repne		fstpl	(%eax)
  595ce9:      	cld
  595cea:      	fstpl	(%eax)
  595ced:      	pushl	%es
  595cee:      	ficomps	(%eax)
  595cf1:      	adcb	%bl, %dh
  595cf3:      	popl	%eax
  595cf4:      	addb	%dl, (%esi)
  595cf6:      	sbbb	(%ecx), %bl
  595cf9:      	pushl	%ss
  595cfa:      	sbbb	(%ecx), %bl
  595cfd:      	pushl	%ss
  595cfe:      	sbbb	(%ecx), %bl
  595d01:      	pushl	%ss
  595d02:      	sbbb	(%ecx), %bl
  595d05:      	pushl	%ss
  595d06:      	sbbb	(%ecx), %bl
  595d09:      	pushl	%ss
  595d0a:      	sbbb	(%ecx), %bl
  595d0d:      	pushl	%ss
  595d0e:      	sbbb	(%ecx), %bl
  595d11:      	pushl	%ss
  595d12:      	sbbb	(%ecx), %bl
  595d15:      	pushl	%ss
  595d16:      	sbbb	(%ecx), %bl
  595d19:      	pushl	%ss
  595d1a:      	sbbb	(%ecx), %bl
  595d1d:      	pushl	%ss
  595d1e:      	sbbb	(%ecx), %bl
  595d21:      	pushl	%ss
  595d22:      	sbbb	(%ecx), %bl
  595d25:      	pushl	%ss
  595d26:      	sbbb	(%ecx), %bl
  595d29:      	pushl	%ss
  595d2a:      	sbbb	(%ecx), %bl
  595d2d:      	pushl	%ss
  595d2e:      	sbbb	(%ecx), %bl
  595d31:      	pushl	%ss
  595d32:      	sbbb	(%ecx), %bl
  595d35:      	pushl	%ss
  595d36:      	sbbb	(%ecx), %bl
  595d39:      	pushl	%ss
  595d3a:      	sbbb	(%ecx), %bl
  595d3d:      	pushl	%ss
  595d3e:      	sbbb	(%ecx), %bl
  595d41:      	pushl	%ss
  595d42:      	sbbb	(%ecx), %bl
  595d45:      	pushl	%ss
  595d46:      	sbbb	(%ecx), %bl
  595d49:      	pushl	%ss
  595d4a:      	sbbb	(%ecx), %bl
  595d4d:      	pushl	%ss
  595d4e:      	sbbb	(%ecx), %bl
  595d51:      	enter	$0x58d5, $0x0           # imm = 0x58D5
  595d55:      	rclb	%cl, %ch
  595d57:      	popl	%eax
  595d58:      	addb	%bl, %ah
  595d5a:      	aad	$0x58
  595d5c:      	addb	%ah, %dh
  595d5e:      	aad	$0x58
  595d60:      	addb	%dh, %al
  595d62:      	aad	$0x58
  595d64:      	addb	%bh, %dl
  595d66:      	aad	$0x58
  595d68:      	addb	%al, (%esi,%edx,8)
  595d6b:      	popl	%eax
  595d6c:      	addb	%cl, (%esi)
  595d6e:      	salc
  595d6f:      	popl	%eax
  595d70:      	addb	%bl, (%eax)
  595d72:      	salc
  595d73:      	popl	%eax
  595d74:      	addb	%ah, (%edx)
  595d76:      	salc
  595d77:      	popl	%eax
  595d78:      	addb	%ch, (%esi,%edx,8)
  595d7b:      	popl	%eax
  595d7c:      	addb	%dh, (%esi)
  595d7e:      	salc
  595d7f:      	popl	%eax
  595d80:      	addb	%al, -0x2a(%eax)
  595d83:      	popl	%eax
  595d84:      	addb	%cl, -0x2a(%edx)
  595d87:      	popl	%eax
  595d88:      	addb	%dl, 0x58(%esi,%edx,8)
  595d8c:      	addb	%bl, -0x2a(%esi)
  595d8f:      	popl	%eax
  595d90:      	addb	%ch, -0x2a(%eax)
  595d93:      	popl	%eax
  595d94:      	addb	%dh, -0x2a(%edx)
  595d97:      	popl	%eax
  595d98:      	addb	%bh, 0x58(%esi,%edx,8)
  595d9c:      	addb	%al, -0x6fffa72a(%esi)
  595da2:      	salc
  595da3:      	popl	%eax
  595da4:      	addb	%bl, -0x5bffa72a(%edx)
  595daa:      	salc
  595dab:      	popl	%eax
  595dac:      	addb	%ch, -0x47ffa72a(%esi)
  595db2:      	salc
  595db3:      	popl	%eax
  595db4:      	addb	%al, %dl
  595db6:      	salc
  595db7:      	popl	%eax
  595db8:      	addb	%cl, %ah
  595dba:      	salc
  595dbb:      	popl	%eax
  595dbc:      	addb	%dl, %dh
  595dbe:      	salc
  595dbf:      	popl	%eax
  595dc0:      	addb	%ah, %al
  595dc2:      	salc
  595dc3:      	popl	%eax
  595dc4:      	addb	%ch, %dl
  595dc6:      	salc
  595dc7:      	popl	%eax
  595dc8:      	addb	%dh, %ah
  595dca:      	salc
  595dcb:      	popl	%eax
  595dcc:      	addb	%bh, %dh
  595dce:      	salc
  595dcf:      	popl	%eax
  595dd0:      	addb	%cl, (%eax)
  595dd2:      	xlatb
  595dd3:      	popl	%eax
  595dd4:      	addb	%dl, (%edx)
  595dd6:      	xlatb
  595dd7:      	popl	%eax
  595dd8:      	addb	%bl, (%edi,%edx,8)
  595ddb:      	popl	%eax
  595ddc:      	addb	%ah, (%esi)
  595dde:      	xlatb
  595ddf:      	popl	%eax
  595de0:      	addb	%dh, (%eax)
  595de2:      	xlatb
  595de3:      	popl	%eax
  595de4:      	addb	%bh, (%edx)
  595de6:      	xlatb
  595de7:      	popl	%eax
  595de8:      	addb	%al, 0x58(%edi,%edx,8)
  595dec:      	addb	%dl, (%esi)
  595dee:      	sbbb	(%ecx), %bl
  595df1:      	decl	%esi
  595df2:      	xlatb
  595df3:      	popl	%eax
  595df4:      	addb	%bl, -0x29(%eax)
  595df7:      	popl	%eax
  595df8:      	addb	%ah, -0x29(%edx)
  595dfb:      	popl	%eax
  595dfc:      	addb	%ch, 0x58(%edi,%edx,8)
  595e00:      	addb	%dh, -0x29(%esi)
  595e03:      	popl	%eax
  595e04:      	addb	%al, -0x75ffa729(%eax)
  595e0a:      	xlatb
  595e0b:      	popl	%eax
  595e0c:      	addb	%dl, -0x2861ffa8(%edi,%edx,8)
  595e13:      	popl	%eax
  595e14:      	addb	%ch, -0x4dffa729(%eax)
  595e1a:      	xlatb
  595e1b:      	popl	%eax
  595e1c:      	addb	%bh, -0x2839ffa8(%edi,%edx,8)
  595e23:      	popl	%eax
  595e24:      	addb	%dl, %al
  595e26:      	xlatb
  595e27:      	popl	%eax
  595e28:      	addb	%bl, %dl
  595e2a:      	xlatb
  595e2b:      	popl	%eax
  595e2c:      	addb	%ah, %ah
  595e2e:      	xlatb
  595e2f:      	popl	%eax
  595e30:      	addb	%ch, %dh
  595e32:      	xlatb
  595e33:      	popl	%eax
  595e34:      	addb	%bh, %al
  595e36:      	xlatb
  595e37:      	popl	%eax
  595e38:      	addb	%al, (%edx)
  595e3a:      	fcomps	(%eax)
  595e3d:      	orb	$-0x28, %al
  595e3f:      	popl	%eax
  595e40:      	addb	%dl, (%esi)
  595e42:      	fcomps	(%eax)
  595e45:      	andb	%bl, %al
  595e47:      	popl	%eax
  595e48:      	addb	%ch, (%edx)
  595e4a:      	fcomps	(%eax)
  595e4d:      	xorb	$-0x28, %al
  595e4f:      	popl	%eax
  595e50:      	addb	%bh, (%esi)
  595e52:      	fcomps	(%eax)
  595e55:      	decl	%eax
  595e56:      	fcomps	(%eax)
  595e59:      	pushl	%edx
  595e5a:      	fcomps	(%eax)
  595e5d:      	popl	%esp
  595e5e:      	fcomps	(%eax)
  595e61:      	fcomps	(%eax)
  595e65:      	jo	0x595e3f <.text+0x194e3f>
  595e67:      	popl	%eax
  595e68:      	addb	%bh, -0x28(%edx)
  595e6b:      	popl	%eax
  595e6c:      	addb	%al, -0x2771ffa8(%eax,%ebx,8)
  595e73:      	popl	%eax
  595e74:      	addb	%bl, -0x5dffa728(%eax)
  595e7a:      	fcomps	(%eax)
  595e7d:      	lodsb	(%esi), %al
  595e7e:      	fcomps	(%eax)
  595e81:      	movb	$-0x28, %dh
  595e83:      	popl	%eax
  595e84:      	addb	%al, %al
  595e86:      	fcomps	(%eax)
  595e89:      	lretl	$0x58d8                 # imm = 0x58D8
  595e8c:      	addb	%dl, %ah
  595e8e:      	fcomps	(%eax)
  595e91:      	<unknown>
  595e93:      	popl	%eax
  595e94:      	addb	%ch, %al
  595e96:      	fcomps	(%eax)
  595e99:      	repne		fcomps	(%eax)
  595e9d:      	cld
  595e9e:      	fcomps	(%eax)
  595ea1:      	pushl	%es
  595ea2:      	fstps	(%eax)
  595ea5:      	adcb	%bl, %cl
  595ea7:      	popl	%eax
  595ea8:      	addb	%bl, (%edx)
  595eaa:      	fstps	(%eax)
  595ead:      	andb	$-0x27, %al
  595eaf:      	popl	%eax
  595eb0:      	addb	%ch, (%esi)
  595eb2:      	fstps	(%eax)
  595eb5:      	cmpb	%bl, %cl
  595eb7:      	popl	%eax
  595eb8:      	addb	%al, -0x27(%edx)
  595ebb:      	popl	%eax
  595ebc:      	addb	%cl, 0x58(%ecx,%ebx,8)
  595ec0:      	addb	%dl, -0x27(%esi)
  595ec3:      	popl	%eax
  595ec4:      	addb	%ah, -0x27(%eax)
  595ec7:      	popl	%eax
  595ec8:      	addb	%ch, -0x27(%edx)
  595ecb:      	popl	%eax
  595ecc:      	addb	%dh, 0x58(%ecx,%ebx,8)
  595ed0:      	addb	%bh, -0x27(%esi)
  595ed3:      	popl	%eax
  595ed4:      	addb	%cl, -0x6dffa727(%eax)
  595eda:      	fstps	(%eax)
  595edd:      	sbbb	%dh, %bl
  595edf:      	popl	%eax
  595ee0:      	addb	%bl, -0x2659ffa8(%ecx,%ebx,8)
  595ee7:      	popl	%eax
  595ee8:      	addb	%dh, -0x45ffa727(%eax)
  595eee:      	fstps	(%eax)
  595ef1:      	<unknown>
  595ef4:      	addb	%cl, %dh
  595ef6:      	fstps	(%eax)
  595ef9:      	fcomp	%st(1)
  595efb:      	popl	%eax
  595efc:      	addb	%ah, %dl
  595efe:      	fstps	(%eax)
  595f01:      	inb	%dx, %al
  595f02:      	fstps	(%eax)
  595f05:      	negb	%cl
  595f07:      	popl	%eax
  595f08:      	addb	%al, (%eax)
  595f0a:      	ficompl	(%eax)
  595f0d:      	orb	%dl, %bl
  595f0f:      	popl	%eax
  595f10:      	addb	%dl, (%edx,%ebx,8)
  595f13:      	popl	%eax
  595f14:      	addb	%bl, (%esi)
  595f16:      	ficompl	(%eax)
  595f19:      	subb	%bl, %dl
  595f1b:      	popl	%eax
  595f1c:      	addb	%dh, (%edx)
  595f1e:      	ficompl	(%eax)
  595f21:      	cmpb	$-0x26, %al
  595f23:      	popl	%eax
  595f24:      	addb	%al, -0x26(%esi)
  595f27:      	popl	%eax
  595f28:      	addb	%dl, -0x26(%eax)
  595f2b:      	popl	%eax
  595f2c:      	addb	%bl, -0x26(%edx)
  595f2f:      	popl	%eax
  595f30:      	addb	%ah, 0x58(%edx,%ebx,8)
  595f34:      	addb	%ch, -0x26(%esi)
  595f37:      	popl	%eax
  595f38:      	addb	%bh, -0x26(%eax)
  595f3b:      	popl	%eax
  595f3c:      	addb	%al, -0x73ffa726(%edx)
  595f42:      	ficompl	(%eax)
  595f45:      	xchgl	%esi, %eax
  595f46:      	ficompl	(%eax)
  595f49:      	movb	0xaa0058da, %al
  595f4e:      	ficompl	(%eax)
  595f51:      	movb	$-0x26, %ah
  595f53:      	popl	%eax
  595f54:      	addb	%bh, -0x37ffa726(%esi)
  595f5a:      	ficompl	(%eax)
  595f5d:      	rcrb	%cl, %dl
  595f5f:      	popl	%eax
  595f60:      	addb	%bl, %ah
  595f62:      	ficompl	(%eax)
  595f65:      	outb	%al, $0xda
  595f67:      	popl	%eax
  595f68:      	addb	%dh, %al
  595f6a:      	ficompl	(%eax)
  595f6d:      	cli
  595f6e:      	ficompl	(%eax)
  595f71:      	addb	$-0x25, %al
  595f73:      	popl	%eax
  595f74:      	addb	%cl, (%esi)
  595f76:      	fistpl	(%eax)
  595f79:      	sbbb	%bl, %bl
  595f7b:      	popl	%eax
  595f7c:      	addb	%ah, (%edx)
  595f7e:      	fistpl	(%eax)
  595f81:      	subb	$-0x25, %al
  595f83:      	popl	%eax
  595f84:      	addb	%dh, (%esi)
  595f86:      	fistpl	(%eax)
  595f89:      	incl	%eax
  595f8a:      	fistpl	(%eax)
  595f8d:      	decl	%edx
  595f8e:      	fistpl	(%eax)
  595f91:      	pushl	%esp
  595f92:      	fistpl	(%eax)
  595f95:      	popl	%esi
  595f96:      	fistpl	(%eax)
  595f99:      	pushl	$0x720058db             # imm = 0x720058DB
  595f9e:      	fistpl	(%eax)
  595fa1:      	jl	0x595f7e <.text+0x194f7e>
  595fa3:      	popl	%eax
  595fa4:      	addb	%al, -0x6fffa725(%esi)
  595faa:      	fistpl	(%eax)
  595fad:      	lcalll	$0x58db, $0xa40058db    # imm = 0x58DB
                                                # imm = 0xA40058DB
  595fb4:      	addb	%ch, -0x47ffa725(%esi)
  595fba:      	fistpl	(%eax)
  595fbd:      	retl	$0x58db                 # imm = 0x58DB
  595fc0:      	addb	%cl, %ah
  595fc2:      	fistpl	(%eax)
  595fc5:      	salc
  595fc6:      	fistpl	(%eax)
  595fc9:      	loopne	0x595fa6 <.text+0x194fa6>
  595fcb:      	popl	%eax
  595fcc:      	addb	%ch, %dl
  595fce:      	fistpl	(%eax)
  595fd1:      	hlt
  595fd2:      	fistpl	(%eax)
  595fd5:      	<unknown>
  595fd7:      	popl	%eax
  595fd8:      	addb	%dl, (%esi)
  595fda:      	sbbb	(%ecx), %bl
  595fdd:      	pushl	%ss
  595fde:      	sbbb	(%ecx), %bl
  595fe1:      	pushl	%ss
  595fe2:      	sbbb	(%ecx), %bl
  595fe5:      	pushl	%ss
  595fe6:      	sbbb	(%ecx), %bl
  595fe9:      	pushl	%ss
  595fea:      	sbbb	(%ecx), %bl
  595fed:      	pushl	%ss
  595fee:      	sbbb	(%ecx), %bl
  595ff1:      	pushl	%ss
  595ff2:      	sbbb	(%ecx), %bl
  595ff5:      	pushl	%ss
  595ff6:      	sbbb	(%ecx), %bl
  595ff9:      	pushl	%ss
  595ffa:      	sbbb	(%ecx), %bl
  595ffd:      	pushl	%ss
  595ffe:      	sbbb	(%ecx), %bl
  596001:      	pushl	%ss
  596002:      	sbbb	(%ecx), %bl
  596005:      	pushl	%ss
  596006:      	sbbb	(%ecx), %bl
  596009:      	pushl	%ss
  59600a:      	sbbb	(%ecx), %bl
  59600d:      	pushl	%ss
  59600e:      	sbbb	(%ecx), %bl
  596011:      	pushl	%ss
  596012:      	sbbb	(%ecx), %bl
  596015:      	pushl	%ss
  596016:      	sbbb	(%ecx), %bl
  596019:      	pushl	%ss
  59601a:      	sbbb	(%ecx), %bl
  59601d:      	pushl	%ss
  59601e:      	sbbb	(%ecx), %bl
  596021:      	pushl	%ss
  596022:      	sbbb	(%ecx), %bl
  596025:      	pushl	%ss
  596026:      	sbbb	(%ecx), %bl
  596029:      	pushl	%ss
  59602a:      	sbbb	(%ecx), %bl
  59602d:      	pushl	%ss
  59602e:      	sbbb	(%ecx), %bl
  596031:      	pushl	%ss
  596032:      	sbbb	(%ecx), %bl
  596035:      	pushl	%ss
  596036:      	sbbb	(%ecx), %bl
  596039:      	pushl	%ss
  59603a:      	sbbb	(%ecx), %bl
  59603d:      	pushl	%ss
  59603e:      	sbbb	(%ecx), %bl
  596041:      	pushl	%ss
  596042:      	sbbb	(%ecx), %bl
  596045:      	pushl	%ss
  596046:      	sbbb	(%ecx), %bl
  596049:      	pushl	%ss
  59604a:      	sbbb	(%ecx), %bl
  59604d:      	pushl	%ss
  59604e:      	sbbb	(%ecx), %bl
  596051:      	pushl	%ss
  596052:      	sbbb	(%ecx), %bl
  596055:      	pushl	%ss
  596056:      	sbbb	(%ecx), %bl
  596059:      	pushl	%ss
  59605a:      	sbbb	(%ecx), %bl
  59605d:      	pushl	%ss
  59605e:      	sbbb	(%ecx), %bl
  596061:      	pushl	%ss
  596062:      	sbbb	(%ecx), %bl
  596065:      	pushl	%ss
  596066:      	sbbb	(%ecx), %bl
  596069:      	pushl	%ss
  59606a:      	sbbb	(%ecx), %bl
  59606d:      	pushl	%ss
  59606e:      	sbbb	(%ecx), %bl
  596071:      	orb	%bl, %ah
  596073:      	popl	%eax
  596074:      	addb	%dl, (%edx)
  596076:      	fcompl	(%eax)
  596079:      	sbbb	$-0x24, %al
  59607b:      	popl	%eax
  59607c:      	addb	%ah, (%esi)
  59607e:      	fcompl	(%eax)
  596081:      	pushl	%ss
  596082:      	sbbb	(%ecx), %bl
  596085:      	pushl	%ss
  596086:      	sbbb	(%ecx), %bl
  596089:      	pushl	%ss
  59608a:      	sbbb	(%ecx), %bl
  59608d:      	pushl	%ss
  59608e:      	sbbb	(%ecx), %bl
  596091:      	pushl	%ss
  596092:      	sbbb	(%ecx), %bl
  596095:      	pushl	%ss
  596096:      	sbbb	(%ecx), %bl
  596099:      	pushl	%ss
  59609a:      	sbbb	(%ecx), %bl
  59609d:      	pushl	%ss
  59609e:      	sbbb	(%ecx), %bl
  5960a1:      	pushl	%ss
  5960a2:      	sbbb	(%ecx), %bl
  5960a5:      	pushl	%ss
  5960a6:      	sbbb	(%ecx), %bl
  5960a9:      	pushl	%ss
  5960aa:      	sbbb	(%ecx), %bl
  5960ad:      	pushl	%ss
  5960ae:      	sbbb	(%ecx), %bl
  5960b1:      	pushl	%ss
  5960b2:      	sbbb	(%ecx), %bl
  5960b5:      	pushl	%ss
  5960b6:      	sbbb	(%ecx), %bl
  5960b9:      	pushl	%ss
  5960ba:      	sbbb	(%ecx), %bl
  5960bd:      	pushl	%ss
  5960be:      	sbbb	(%ecx), %bl
  5960c1:      	pushl	%ss
  5960c2:      	sbbb	(%ecx), %bl
  5960c5:      	pushl	%ss
  5960c6:      	sbbb	(%ecx), %bl
  5960c9:      	pushl	%ss
  5960ca:      	sbbb	(%ecx), %bl
  5960cd:      	pushl	%ss
  5960ce:      	sbbb	(%ecx), %bl
  5960d1:      	pushl	%ss
  5960d2:      	sbbb	(%ecx), %bl
  5960d5:      	pushl	%ss
  5960d6:      	sbbb	(%ecx), %bl
  5960d9:      	pushl	%ss
  5960da:      	sbbb	(%ecx), %bl
  5960dd:      	pushl	%ss
  5960de:      	sbbb	(%ecx), %bl
  5960e1:      	pushl	%ss
  5960e2:      	sbbb	(%ecx), %bl
  5960e5:      	pushl	%ss
  5960e6:      	sbbb	(%ecx), %bl
  5960e9:      	pushl	%ss
  5960ea:      	sbbb	(%ecx), %bl
  5960ed:      	pushl	%ss
  5960ee:      	sbbb	(%ecx), %bl
  5960f1:      	pushl	%ss
  5960f2:      	sbbb	(%ecx), %bl
  5960f5:      	pushl	%ss
  5960f6:      	sbbb	(%ecx), %bl
  5960f9:      	pushl	%ss
  5960fa:      	sbbb	(%ecx), %bl
  5960fd:      	pushl	%ss
  5960fe:      	sbbb	(%ecx), %bl
  596101:      	pushl	%ss
  596102:      	sbbb	(%ecx), %bl
  596105:      	pushl	%ss
  596106:      	sbbb	(%ecx), %bl
  596109:      	pushl	%ss
  59610a:      	sbbb	(%ecx), %bl
  59610d:      	pushl	%ss
  59610e:      	sbbb	(%ecx), %bl
  596111:      	pushl	%ss
  596112:      	sbbb	(%ecx), %bl
  596115:      	pushl	%ss
  596116:      	sbbb	(%ecx), %bl
  596119:      	pushl	%ss
  59611a:      	sbbb	(%ecx), %bl
  59611d:      	pushl	%ss
  59611e:      	sbbb	(%ecx), %bl
  596121:      	pushl	%ss
  596122:      	sbbb	(%ecx), %bl
  596125:      	pushl	%ss
  596126:      	sbbb	(%ecx), %bl
  596129:      	pushl	%ss
  59612a:      	sbbb	(%ecx), %bl
  59612d:      	pushl	%ss
  59612e:      	sbbb	(%ecx), %bl
  596131:      	pushl	%ss
  596132:      	sbbb	(%ecx), %bl
  596135:      	pushl	%ss
  596136:      	sbbb	(%ecx), %bl
  596139:      	pushl	%ss
  59613a:      	sbbb	(%ecx), %bl
  59613d:      	pushl	%ss
  59613e:      	sbbb	(%ecx), %bl
  596141:      	pushl	%ss
  596142:      	sbbb	(%ecx), %bl
  596145:      	pushl	%ss
  596146:      	sbbb	(%ecx), %bl
  596149:      	pushl	%ss
  59614a:      	sbbb	(%ecx), %bl
  59614d:      	pushl	%ss
  59614e:      	sbbb	(%ecx), %bl
  596151:      	pushl	%ss
  596152:      	sbbb	(%ecx), %bl
  596155:      	pushl	%ss
  596156:      	sbbb	(%ecx), %bl
  596159:      	pushl	%ss
  59615a:      	sbbb	(%ecx), %bl
  59615d:      	pushl	%ss
  59615e:      	sbbb	(%ecx), %bl
  596161:      	pushl	%ss
  596162:      	sbbb	(%ecx), %bl
  596165:      	pushl	%ss
  596166:      	sbbb	(%ecx), %bl
  596169:      	pushl	%ss
  59616a:      	sbbb	(%ecx), %bl
  59616d:      	pushl	%ss
  59616e:      	sbbb	(%ecx), %bl
  596171:      	pushl	%ss
  596172:      	sbbb	(%ecx), %bl
  596175:      	pushl	%ss
  596176:      	sbbb	(%ecx), %bl
  596179:      	pushl	%ss
  59617a:      	sbbb	(%ecx), %bl
  59617d:      	pushl	%ss
  59617e:      	sbbb	(%ecx), %bl
  596181:      	pushl	%ss
  596182:      	sbbb	(%ecx), %bl
  596185:      	pushl	%ss
  596186:      	sbbb	(%ecx), %bl
  596189:      	pushl	%ss
  59618a:      	sbbb	(%ecx), %bl
  59618d:      	pushl	%ss
  59618e:      	sbbb	(%ecx), %bl
  596191:      	pushl	%ss
  596192:      	sbbb	(%ecx), %bl
  596195:      	pushl	%ss
  596196:      	sbbb	(%ecx), %bl
  596199:      	pushl	%ss
  59619a:      	sbbb	(%ecx), %bl
  59619d:      	pushl	%ss
  59619e:      	sbbb	(%ecx), %bl
  5961a1:      	pushl	%ss
  5961a2:      	sbbb	(%ecx), %bl
  5961a5:      	pushl	%ss
  5961a6:      	sbbb	(%ecx), %bl
  5961a9:      	pushl	%ss
  5961aa:      	sbbb	(%ecx), %bl
  5961ad:      	pushl	%ss
  5961ae:      	sbbb	(%ecx), %bl
  5961b1:      	pushl	%ss
  5961b2:      	sbbb	(%ecx), %bl
  5961b5:      	pushl	%ss
  5961b6:      	sbbb	(%ecx), %bl
  5961b9:      	pushl	%ss
  5961ba:      	sbbb	(%ecx), %bl
  5961bd:      	pushl	%ss
  5961be:      	sbbb	(%ecx), %bl
  5961c1:      	pushl	%ss
  5961c2:      	sbbb	(%ecx), %bl
  5961c5:      	pushl	%ss
  5961c6:      	sbbb	(%ecx), %bl
  5961c9:      	pushl	%ss
  5961ca:      	sbbb	(%ecx), %bl
  5961cd:      	pushl	%ss
  5961ce:      	sbbb	(%ecx), %bl
  5961d1:      	pushl	%ss
  5961d2:      	sbbb	(%ecx), %bl
  5961d5:      	pushl	%ss
  5961d6:      	sbbb	(%ecx), %bl
  5961d9:      	pushl	%ss
  5961da:      	sbbb	(%ecx), %bl
  5961dd:      	pushl	%ss
  5961de:      	sbbb	(%ecx), %bl
  5961e1:      	pushl	%ss
  5961e2:      	sbbb	(%ecx), %bl
  5961e5:      	pushl	%ss
  5961e6:      	sbbb	(%ecx), %bl
  5961e9:      	pushl	%ss
  5961ea:      	sbbb	(%ecx), %bl
  5961ed:      	pushl	%ss
  5961ee:      	sbbb	(%ecx), %bl
  5961f1:      	pushl	%ss
  5961f2:      	sbbb	(%ecx), %bl
  5961f5:      	pushl	%ss
  5961f6:      	sbbb	(%ecx), %bl
  5961f9:      	pushl	%ss
  5961fa:      	sbbb	(%ecx), %bl
  5961fd:      	pushl	%ss
  5961fe:      	sbbb	(%ecx), %bl
  596201:      	pushl	%ss
  596202:      	sbbb	(%ecx), %bl
  596205:      	andb	$-0x22, %al
  596207:      	popl	%eax
  596208:      	addb	%dh, (%eax)
  59620a:      	fcompl	(%eax)
  59620d:      	cmpb	%ah, %bl
  59620f:      	popl	%eax
  596210:      	addb	%al, 0x58(%esp,%ebx,8)
  596214:      	addb	%cl, -0x24(%esi)
  596217:      	popl	%eax
  596218:      	addb	%bl, -0x24(%eax)
  59621b:      	popl	%eax
  59621c:      	addb	%ah, -0x24(%edx)
  59621f:      	popl	%eax
  596220:      	addb	%ch, 0x58(%esp,%ebx,8)
  596224:      	addb	%dh, -0x24(%esi)
  596227:      	popl	%eax
  596228:      	addb	%al, -0x75ffa724(%eax)
  59622e:      	fcompl	(%eax)
  596231:      	xchgl	%esp, %eax
  596232:      	fcompl	(%eax)
  596235:      	ficomps	%cs:(%eax)
  596239:      	sahf
  59623a:      	fcompl	(%eax)
  59623d:      	testb	$-0x24, %al
  59623f:      	popl	%eax
  596240:      	addb	%dh, -0x43ffa724(%edx)
  596246:      	fcompl	(%eax)
  596249:      	cmpb	%bl, %dh
  59624b:      	popl	%eax
  59624c:      	addb	%al, -0x22(%edx)
  59624f:      	popl	%eax
  596250:      	addb	%cl, 0x58(%esi,%ebx,8)
  596254:      	addb	%dl, -0x22(%esi)
  596257:      	popl	%eax
  596258:      	addb	%ah, -0x22(%eax)
  59625b:      	popl	%eax
  59625c:      	addb	%ch, -0x22(%edx)
  59625f:      	popl	%eax
  596260:      	addb	%dh, 0x58(%esi,%ebx,8)
  596264:      	addb	%bh, -0x22(%esi)
  596267:      	popl	%eax
  596268:      	addb	%cl, -0x6dffa722(%eax)
  59626e:      	ficomps	(%eax)
  596271:      	pushfl
  596272:      	ficomps	(%eax)
  596275:      	cmpsb	%es:(%edi), (%esi)
  596276:      	ficomps	(%eax)
  596279:      	movb	$-0x22, %al
  59627b:      	popl	%eax
  59627c:      	addb	%bh, -0x3bffa722(%edx)
  596282:      	ficomps	(%eax)
  596285:      	into
  596286:      	ficomps	(%eax)
  596289:      	fcomp	%st(6)
  59628b:      	popl	%eax
  59628c:      	addb	%ah, %dl
  59628e:      	ficomps	(%eax)
  596291:      	inb	%dx, %al
  596292:      	ficomps	(%eax)
  596295:      	negb	%dh
  596297:      	popl	%eax
  596298:      	addb	%al, (%eax)
  59629a:      	fistps	(%eax)
  59629d:      	orb	%bh, %bl
  59629f:      	popl	%eax
  5962a0:      	addb	%dl, (%edi,%ebx,8)
  5962a3:      	popl	%eax
  5962a4:      	addb	%bl, (%esi)
  5962a6:      	fistps	(%eax)
  5962a9:      	subb	%bl, %bh
  5962ab:      	popl	%eax
  5962ac:      	addb	%dh, (%edx)
  5962ae:      	fistps	(%eax)
  5962b1:      	cmpb	$-0x21, %al
  5962b3:      	popl	%eax
  5962b4:      	addb	%dl, (%esi)
  5962b6:      	sbbb	(%ecx), %bl
  5962b9:      	pushl	%ss
  5962ba:      	sbbb	(%ecx), %bl
  5962bd:      	pushl	%ss
  5962be:      	sbbb	(%ecx), %bl
  5962c1:      	pushl	%ss
  5962c2:      	sbbb	(%ecx), %bl
  5962c5:      	pushl	%ss
  5962c6:      	sbbb	(%ecx), %bl
  5962c9:      	pushl	%ss
  5962ca:      	sbbb	(%ecx), %bl
  5962cd:      	pushl	%ss
  5962ce:      	sbbb	(%ecx), %bl
  5962d1:      	pushl	%ss
  5962d2:      	sbbb	(%ecx), %bl
  5962d5:      	pushl	%ss
  5962d6:      	sbbb	(%ecx), %bl
  5962d9:      	pushl	%ss
  5962da:      	sbbb	(%ecx), %bl
  5962dd:      	pushl	%ss
  5962de:      	sbbb	(%ecx), %bl
  5962e1:      	pushl	%ss
  5962e2:      	sbbb	(%ecx), %bl
  5962e5:      	pushl	%ss
  5962e6:      	sbbb	(%ecx), %bl
  5962e9:      	pushl	%ss
  5962ea:      	sbbb	(%ecx), %bl
  5962ed:      	pushl	%ss
  5962ee:      	sbbb	(%ecx), %bl
  5962f1:      	pushl	%ss
  5962f2:      	sbbb	(%ecx), %bl
  5962f5:      	pushl	%ss
  5962f6:      	sbbb	(%ecx), %bl
  5962f9:      	pushl	%ss
  5962fa:      	sbbb	(%ecx), %bl
  5962fd:      	pushl	%ss
  5962fe:      	sbbb	(%ecx), %bl
  596301:      	pushl	%ss
  596302:      	sbbb	(%ecx), %bl
  596305:      	pushl	%ss
  596306:      	sbbb	(%ecx), %bl
  596309:      	pushl	%ss
  59630a:      	sbbb	(%ecx), %bl
  59630d:      	pushl	%ss
  59630e:      	sbbb	(%ecx), %bl
  596311:      	pushl	%ss
  596312:      	sbbb	(%ecx), %bl
  596315:      	pushl	%ss
  596316:      	sbbb	(%ecx), %bl
  596319:      	pushl	%ss
  59631a:      	sbbb	(%ecx), %bl
  59631d:      	pushl	%ss
  59631e:      	sbbb	(%ecx), %bl
  596321:      	pushl	%ss
  596322:      	sbbb	(%ecx), %bl
  596325:      	pushl	%ss
  596326:      	sbbb	(%ecx), %bl
  596329:      	pushl	%ss
  59632a:      	sbbb	(%ecx), %bl
  59632d:      	pushl	%ss
  59632e:      	sbbb	(%ecx), %bl
  596331:      	pushl	%ss
  596332:      	sbbb	(%ecx), %bl
  596335:      	pushl	%ss
  596336:      	sbbb	(%ecx), %bl
  596339:      	pushl	%ss
  59633a:      	sbbb	(%ecx), %bl
  59633d:      	pushl	%ss
  59633e:      	sbbb	(%ecx), %bl
  596341:      	pushl	%ss
  596342:      	sbbb	(%ecx), %bl
  596345:      	pushl	%ss
  596346:      	sbbb	(%ecx), %bl
  596349:      	pushl	%ss
  59634a:      	sbbb	(%ecx), %bl
  59634d:      	pushl	%ss
  59634e:      	sbbb	(%ecx), %bl
  596351:      	pushl	%ss
  596352:      	sbbb	(%ecx), %bl
  596355:      	pushl	%ss
  596356:      	sbbb	(%ecx), %bl
  596359:      	pushl	%ss
  59635a:      	sbbb	(%ecx), %bl
  59635d:      	pushl	%ss
  59635e:      	sbbb	(%ecx), %bl
  596361:      	pushl	%ss
  596362:      	sbbb	(%ecx), %bl
  596365:      	pushl	%ss
  596366:      	sbbb	(%ecx), %bl
  596369:      	pushl	%ss
  59636a:      	sbbb	(%ecx), %bl
  59636d:      	pushl	%ss
  59636e:      	sbbb	(%ecx), %bl
  596371:      	pushl	%ss
  596372:      	sbbb	(%ecx), %bl
  596375:      	pushl	%ss
  596376:      	sbbb	(%ecx), %bl
  596379:      	pushl	%ss
  59637a:      	sbbb	(%ecx), %bl
  59637d:      	pushl	%ss
  59637e:      	sbbb	(%ecx), %bl
  596381:      	pushl	%ss
  596382:      	sbbb	(%ecx), %bl
  596385:      	pushl	%ss
  596386:      	sbbb	(%ecx), %bl
  596389:      	pushl	%ss
  59638a:      	sbbb	(%ecx), %bl
  59638d:      	pushl	%ss
  59638e:      	sbbb	(%ecx), %bl
  596391:      	<unknown>
  596393:      	popl	%eax
  596394:      	addb	%dl, %al
  596396:      	fcompl	(%eax)
  596399:      	fcmovu	%st(4), %st
  59639b:      	popl	%eax
  59639c:      	addb	%ah, %ah
  59639e:      	fcompl	(%eax)
  5963a1:      	outb	%al, %dx
  5963a2:      	fcompl	(%eax)
  5963a5:      	clc
  5963a6:      	fcompl	(%eax)
  5963a9:      	addb	%ch, %bl
  5963ab:      	popl	%eax
  5963ac:      	addb	%cl, -0x22e9ffa8(,%ebx,8)
  5963b3:      	popl	%eax
  5963b4:      	addb	%ah, (%eax)
  5963b6:      	fstpl	(%eax)
  5963b9:      	subb	%ch, %bl
  5963bb:      	popl	%eax
  5963bc:      	addb	%dh, -0x22c1ffa8(,%ebx,8)
  5963c3:      	popl	%eax
  5963c4:      	addb	%al, -0x74ffa721(%ecx)
  5963ca:      	fistps	(%eax)
  5963cd:      	xchgl	%ebp, %eax
  5963ce:      	fistps	(%eax)
  5963d1:      	lahf
  5963d2:      	fistps	(%eax)
  5963d5:      	testl	$0xb30058df, %eax       # imm = 0xB30058DF
  5963da:      	fistps	(%eax)
  5963dd:      	movl	$0xc70058df, %ebp       # imm = 0xC70058DF
  5963e2:      	fistps	(%eax)
  5963e5:      	rcrl	%edi
  5963e7:      	popl	%eax
  5963e8:      	addb	%bl, %bl
  5963ea:      	fistps	(%eax)
  5963ed:      	inl	$0xdf, %eax
  5963ef:      	popl	%eax
  5963f0:      	addb	%ch, %bh
  5963f2:      	fistps	(%eax)
  5963f5:      	stc
  5963f6:      	fistps	(%eax)
  5963f9:      	addl	%eax, %esp
  5963fb:      	popl	%eax
  5963fc:      	addb	%cl, 0x170058e0
  596402:      	loopne	0x59645c <.text+0x19545c>
  596404:      	addb	%ah, (%ecx)
  596406:      	loopne	0x596460 <.text+0x195460>
  596408:      	addb	%ch, (%ebx)
  59640a:      	loopne	0x596464 <.text+0x195464>
  59640c:      	addb	%dh, 0x3f0058e0
  596412:      	loopne	0x59646c <.text+0x19546c>
  596414:      	addb	%cl, -0x20(%ecx)
  596417:      	popl	%eax
  596418:      	addb	%dl, -0x20(%ebx)
  59641b:      	popl	%eax
  59641c:      	addb	%bl, -0x20(%ebp)
  59641f:      	popl	%eax
  596420:      	addb	%ah, -0x20(%edi)
  596423:      	popl	%eax
  596424:      	addb	%dh, -0x20(%ecx)
  596427:      	popl	%eax
  596428:      	addb	%bh, -0x20(%ebx)
  59642b:      	popl	%eax
  59642c:      	addb	%al, -0x70ffa720(%ebp)
  596432:      	loopne	0x59648c <.text+0x19548c>
  596434:      	addb	%bl, -0x5cffa720(%ecx)
  59643a:      	loopne	0x596494 <.text+0x195494>
  59643c:      	addb	%ch, -0x48ffa720(%ebp)
  596442:      	loopne	0x59649c <.text+0x19549c>
  596444:      	addb	%al, %cl
  596446:      	loopne	0x5964a0 <.text+0x1954a0>
  596448:      	addb	%cl, %bl
  59644a:      	loopne	0x5964a4 <.text+0x1954a4>
  59644c:      	addb	%dl, %ch
  59644e:      	loopne	0x5964a8 <.text+0x1954a8>
  596450:      	addb	%bl, %bh
  596452:      	loopne	0x5964ac <.text+0x1954ac>
  596454:      	addb	%ch, %cl
  596456:      	loopne	0x5964b0 <.text+0x1954b0>
  596458:      	addb	%dh, %bl
  59645a:      	loopne	0x5964b4 <.text+0x1954b4>
  59645c:      	addb	%bh, %ch
  59645e:      	loopne	0x5964b8 <.text+0x1954b8>
  596460:      	addb	%al, (%edi)
  596462:      	loope	0x5964bc <.text+0x1954bc>
  596464:      	addb	%dl, (%ecx)
  596466:      	loope	0x5964c0 <.text+0x1954c0>
  596468:      	addb	%bl, (%ebx)
  59646a:      	loope	0x5964c4 <.text+0x1954c4>
  59646c:      	addb	%ah, 0x2f0058e1
  596472:      	loope	0x5964cc <.text+0x1954cc>
  596474:      	addb	%bh, (%ecx)
  596476:      	loope	0x5964d0 <.text+0x1954d0>
  596478:      	addb	%al, -0x1f(%ebx)
  59647b:      	popl	%eax
  59647c:      	addb	%cl, -0x1f(%ebp)
  59647f:      	popl	%eax
  596480:      	addb	%dl, -0x1f(%edi)
  596483:      	popl	%eax
  596484:      	addb	%ah, -0x1f(%ecx)
  596487:      	popl	%eax
  596488:      	addb	%ch, -0x1f(%ebx)
  59648b:      	popl	%eax
  59648c:      	addb	%dh, -0x1f(%ebp)
  59648f:      	popl	%eax
  596490:      	addb	%bh, -0x1f(%edi)
  596493:      	popl	%eax
  596494:      	addb	%cl, -0x6cffa71f(%ecx)
  59649a:      	loope	0x5964f4 <.text+0x1954f4>
  59649c:      	addb	%bl, -0x58ffa71f(%ebp)
  5964a2:      	loope	0x5964fc <.text+0x1954fc>
  5964a4:      	addb	%dh, -0x44ffa71f(%ecx)
  5964aa:      	loope	0x596504 <.text+0x195504>
  5964ac:      	addb	%al, %ch
  5964ae:      	loope	0x596508 <.text+0x195508>
  5964b0:      	addb	%cl, %bh
  5964b2:      	loope	0x59650c <.text+0x19550c>
  5964b4:      	addb	%bl, %cl
  5964b6:      	loope	0x596510 <.text+0x195510>
  5964b8:      	addb	%ah, %bl
  5964ba:      	loope	0x596514 <.text+0x195514>
  5964bc:      	addb	%ch, %ch
  5964be:      	loope	0x596518 <.text+0x195518>
  5964c0:      	addb	%dh, %bh
  5964c2:      	loope	0x59651c <.text+0x19551c>
  5964c4:      	addb	%al, (%ecx)
  5964c6:      	loop	0x596520 <.text+0x195520>
  5964c8:      	addb	%cl, (%ebx)
  5964ca:      	loop	0x596524 <.text+0x195524>
  5964cc:      	addb	%dl, 0x1f0058e2
  5964d2:      	loop	0x59652c <.text+0x19552c>
  5964d4:      	addb	%ch, (%ecx)
  5964d6:      	loop	0x596530 <.text+0x195530>
  5964d8:      	addb	%dh, (%ebx)
  5964da:      	loop	0x596534 <.text+0x195534>
  5964dc:      	addb	%bh, 0x470058e2
  5964e2:      	loop	0x59653c <.text+0x19553c>
  5964e4:      	addb	%dl, -0x1e(%ecx)
  5964e7:      	popl	%eax
  5964e8:      	addb	%bl, -0x1e(%ebx)
  5964eb:      	popl	%eax
  5964ec:      	addb	%ah, -0x1e(%ebp)
  5964ef:      	popl	%eax
  5964f0:      	addb	%ch, -0x1e(%edi)
  5964f3:      	popl	%eax
  5964f4:      	addb	%bh, -0x1e(%ecx)
  5964f7:      	popl	%eax
  5964f8:      	addb	%al, -0x72ffa71e(%ebx)
  5964fe:      	loop	0x596558 <.text+0x195558>
  596500:      	addb	%dl, -0x5effa71e(%edi)
  596506:      	loop	0x596560 <.text+0x195560>
  596508:      	addb	%ch, -0x4affa71e(%ebx)
  59650e:      	loop	0x596568 <.text+0x195568>
  596510:      	addb	%bh, -0x36ffa71e(%edi)
  596516:      	loop	0x596570 <.text+0x195570>
  596518:      	addb	%dl, %bl
  59651a:      	loop	0x596574 <.text+0x195574>
  59651c:      	addb	%bl, %ch
  59651e:      	loop	0x596578 <.text+0x195578>
  596520:      	addb	%ah, %bh
  596522:      	loop	0x59657c <.text+0x19557c>
  596524:      	addb	%dh, %cl
  596526:      	loop	0x596580 <.text+0x195580>
  596528:      	addb	%bh, %bl
  59652a:      	loop	0x596584 <.text+0x195584>
  59652c:      	addb	%al, 0xf0058e3
  596532:      	jecxz	0x59658c <.text+0x19558c>
  596534:      	addb	%bl, (%ecx)
  596536:      	jecxz	0x596590 <.text+0x195590>
  596538:      	addb	%ah, (%ebx)
  59653a:      	jecxz	0x596594 <.text+0x195594>
  59653c:      	addb	%ch, 0x370058e3
  596542:      	jecxz	0x59659c <.text+0x19559c>
  596544:      	addb	%al, -0x1d(%ecx)
  596547:      	popl	%eax
  596548:      	addb	%cl, -0x1d(%ebx)
  59654b:      	popl	%eax
  59654c:      	addb	%dl, -0x1d(%ebp)
  59654f:      	popl	%eax
  596550:      	addb	%bl, -0x1d(%edi)
  596553:      	popl	%eax
  596554:      	addb	%ch, -0x1d(%ecx)
  596557:      	popl	%eax
  596558:      	addb	%dh, -0x1d(%ebx)
  59655b:      	popl	%eax
  59655c:      	addb	%bh, -0x1d(%ebp)
  59655f:      	popl	%eax
  596560:      	addb	%al, -0x6effa71d(%edi)
  596566:      	jecxz	0x5965c0 <.text+0x1955c0>
  596568:      	addb	%bl, -0x5affa71d(%ebx)
  59656e:      	jecxz	0x5965c8 <.text+0x1955c8>
  596570:      	addb	%ch, -0x46ffa71d(%edi)
  596576:      	jecxz	0x5965d0 <.text+0x1955d0>
  596578:      	addb	%al, %bl
  59657a:      	jecxz	0x5965d4 <.text+0x1955d4>
  59657c:      	addb	%cl, %ch
  59657e:      	jecxz	0x5965d8 <.text+0x1955d8>
  596580:      	addb	%dl, %bh
  596582:      	jecxz	0x5965dc <.text+0x1955dc>
  596584:      	addb	%ah, %cl
  596586:      	jecxz	0x5965e0 <.text+0x1955e0>
  596588:      	addb	%ch, %bl
  59658a:      	jecxz	0x5965e4 <.text+0x1955e4>
  59658c:      	addb	%dh, %ch
  59658e:      	jecxz	0x5965e8 <.text+0x1955e8>
  596590:      	addb	%bh, %bh
  596592:      	jecxz	0x5965ec <.text+0x1955ec>
  596594:      	addb	%cl, (%ecx)
  596596:      	inb	$0x58, %al
  596598:      	addb	%dl, (%ebx)
  59659a:      	inb	$0x58, %al
  59659c:      	addb	%bl, 0x270058e4
  5965a2:      	inb	$0x58, %al
  5965a4:      	addb	%dh, (%ecx)
  5965a6:      	inb	$0x58, %al
  5965a8:      	addb	%bh, (%ebx)
  5965aa:      	inb	$0x58, %al
  5965ac:      	addb	%al, -0x1c(%ebp)
  5965af:      	popl	%eax
  5965b0:      	addb	%cl, -0x1c(%edi)
  5965b3:      	popl	%eax
  5965b4:      	addb	%bl, -0x1c(%ecx)
  5965b7:      	popl	%eax
  5965b8:      	addb	%ah, -0x1c(%ebx)
  5965bb:      	popl	%eax
  5965bc:      	addb	%ch, -0x1c(%ebp)
  5965bf:      	popl	%eax
  5965c0:      	addb	%dh, -0x1c(%edi)
  5965c3:      	popl	%eax
  5965c4:      	addb	%al, -0x74ffa71c(%ecx)
  5965ca:      	inb	$0x58, %al
  5965cc:      	addb	%dl, -0x60ffa71c(%ebp)
  5965d2:      	inb	$0x58, %al
  5965d4:      	addb	%ch, -0x4cffa71c(%ecx)
  5965da:      	inb	$0x58, %al
  5965dc:      	addb	%bh, -0x38ffa71c(%ebp)
  5965e2:      	inb	$0x58, %al
  5965e4:      	addb	%dl, %cl
  5965e6:      	inb	$0x58, %al
  5965e8:      	addb	%bl, %bl
  5965ea:      	inb	$0x58, %al
  5965ec:      	addb	%ah, %ch
  5965ee:      	inb	$0x58, %al
  5965f0:      	addb	%al, %cl
  5965f2:      	inl	$0x58, %eax
  5965f4:      	addb	%cl, %bl
  5965f6:      	inl	$0x58, %eax
  5965f8:      	addb	%dl, %ch
  5965fa:      	inl	$0x58, %eax
  5965fc:      	addb	%bl, %bh
  5965fe:      	inl	$0x58, %eax
  596600:      	addb	%ch, %cl
  596602:      	inl	$0x58, %eax
  596604:      	addb	%dh, %bl
  596606:      	inl	$0x58, %eax
  596608:      	addb	%bh, %ch
  59660a:      	inl	$0x58, %eax
  59660c:      	addb	%al, (%edi)
  59660e:      	outb	%al, $0x58
  596610:      	addb	%dl, (%ecx)
  596612:      	outb	%al, $0x58
  596614:      	addb	%bl, (%ebx)
  596616:      	outb	%al, $0x58
  596618:      	addb	%ch, %bh
  59661a:      	inb	$0x58, %al
  59661c:      	addb	%bh, %cl
  59661e:      	inb	$0x58, %al
  596620:      	addb	%al, (%ebx)
  596622:      	inl	$0x58, %eax
  596624:      	addb	%cl, 0x170058e5
  59662a:      	inl	$0x58, %eax
  59662c:      	addb	%ah, (%ecx)
  59662e:      	inl	$0x58, %eax
  596630:      	addb	%ch, (%ebx)
  596632:      	inl	$0x58, %eax
  596634:      	addb	%dh, 0x3f0058e5
  59663a:      	inl	$0x58, %eax
  59663c:      	addb	%cl, -0x1b(%ecx)
  59663f:      	popl	%eax
  596640:      	addb	%dl, -0x1b(%ebx)
  596643:      	popl	%eax
  596644:      	addb	%bl, -0x1b(%ebp)
  596647:      	popl	%eax
  596648:      	addb	%ah, -0x1b(%edi)
  59664b:      	popl	%eax
  59664c:      	addb	%dh, -0x1b(%ecx)
  59664f:      	popl	%eax
  596650:      	addb	%bh, -0x1b(%ebx)
  596653:      	popl	%eax
  596654:      	addb	%al, -0x70ffa71b(%ebp)
  59665a:      	inl	$0x58, %eax
  59665c:      	addb	%bl, -0x5cffa71b(%ecx)
  596662:      	inl	$0x58, %eax
  596664:      	addb	%ch, 0x250058e5(%ebp)
  59666a:      	outb	%al, $0x58
  59666c:      	addb	%dh, 0x160058e5(%edi)
  596672:      	sbbb	(%ecx), %bl
  596675:      	addb	%al, (%ecx)
  596677:      	addb	(%ebx), %al
  596679:      	addb	$0x5, %al
  59667b:      	pushl	%es
  59667c:      	popl	%es
  59667d:      	orb	%cl, (%ecx)
  59667f:      	orb	(%ebx), %cl
  596681:      	orb	$0xd, %al
  596683:      	pushl	%cs
  596684:      	stosl	%eax, %es:(%edi)
  596685:      	btsl	%edx, (%eax)
  596688:      	adcl	%edx, (%edx)
  59668a:      	adcl	0x181716ab(,%edx), %edx
  596691:      	sbbl	%ebx, (%edx)
  596693:      	sbbl	0x21201f1e(,%ebx), %ebx
  59669a:      	andb	(%ebx), %ah
  59669c:      	andb	$0x25, %al
  59669e:      	daa
  5966a0:      	subb	%ch, (%ecx)
  5966a2:      	subb	(%ebx), %ch
  5966a4:      	subb	$0x2d, %al
  5966a6:      	das
  5966a8:      	xorb	%dh, (%ecx)
  5966aa:      	xorb	(%ebx), %dh
  5966ac:      	xorb	$0x35, %al
  5966ae:      	aaa
  5966b0:      	cmpb	%bh, (%ecx)
  5966b2:      	cmpb	0x3e3d3c3b(%ebx), %ch
  5966b8:      	aas
  5966b9:      	incl	%eax
  5966ba:      	incl	%ecx
  5966bb:      	incl	%edx
  5966bc:      	incl	%ebx
  5966bd:      	incl	%esp
  5966be:      	incl	%ebp
  5966bf:      	incl	%esi
  5966c0:      	incl	%edi
  5966c1:      	decl	%eax
  5966c2:      	decl	%ecx
  5966c3:      	decl	%edx
  5966c4:      	decl	%ebx
  5966c5:      	decl	%esp
  5966c6:      	decl	%ebp
  5966c7:      	decl	%esi
  5966c8:      	decl	%edi
  5966c9:      	pushl	%eax
  5966ca:      	pushl	%ecx
  5966cb:      	pushl	%edx
  5966cc:      	pushl	%ebx
  5966cd:      	pushl	%esp
  5966ce:      	pushl	%ebp
  5966cf:      	pushl	%esi
  5966d0:      	pushl	%edi
  5966d1:      	popl	%eax
  5966d2:      	popl	%ecx
  5966d3:      	popl	%edx
  5966d4:      	popl	%ebx
  5966d5:      	popl	%esp
  5966d6:      	popl	%ebp
  5966d7:      	popl	%esi
  5966d8:      	popl	%edi
  5966d9:      	pushal
  5966da:      	popal
  5966db:      	bound	%esp, 0x64(%ebx)
  5966de:      	addr16		pushw	$0x6a69         # imm = 0x6A69
  5966e4:      	imull	$0x6f, 0x6e(%ebp,%ebp,2), %ebp
  5966e9:      	jo	0x59675c <.text+0x19575c>
  5966eb:      	jb	0x596698 <.text+0x195698>
  5966ed:      	stosl	%eax, %es:(%edi)
  5966ee:      	stosl	%eax, %es:(%edi)
  5966ef:      	stosl	%eax, %es:(%edi)
  5966f0:      	stosl	%eax, %es:(%edi)
  5966f1:      	stosl	%eax, %es:(%edi)
  5966f2:      	stosl	%eax, %es:(%edi)
  5966f3:      	stosl	%eax, %es:(%edi)
  5966f4:      	stosl	%eax, %es:(%edi)
  5966f5:      	stosl	%eax, %es:(%edi)
  5966f6:      	stosl	%eax, %es:(%edi)
  5966f7:      	stosl	%eax, %es:(%edi)
  5966f8:      	stosl	%eax, %es:(%edi)
  5966f9:      	stosl	%eax, %es:(%edi)
  5966fa:      	stosl	%eax, %es:(%edi)
  5966fb:      	stosl	%eax, %es:(%edi)
  5966fc:      	stosl	%eax, %es:(%edi)
  5966fd:      	stosl	%eax, %es:(%edi)
  5966fe:      	stosl	%eax, %es:(%edi)
  5966ff:      	stosl	%eax, %es:(%edi)
  596700:      	stosl	%eax, %es:(%edi)
  596701:      	stosl	%eax, %es:(%edi)
  596702:      	stosl	%eax, %es:(%edi)
  596703:      	stosl	%eax, %es:(%edi)
  596704:      	stosl	%eax, %es:(%edi)
  596705:      	stosl	%eax, %es:(%edi)
  596706:      	stosl	%eax, %es:(%edi)
  596707:      	stosl	%eax, %es:(%edi)
  596708:      	stosl	%eax, %es:(%edi)
  596709:      	stosl	%eax, %es:(%edi)
  59670a:      	stosl	%eax, %es:(%edi)
  59670b:      	stosl	%eax, %es:(%edi)
  59670c:      	stosl	%eax, %es:(%edi)
  59670d:      	stosl	%eax, %es:(%edi)
  59670e:      	stosl	%eax, %es:(%edi)
  59670f:      	stosl	%eax, %es:(%edi)
  596710:      	stosl	%eax, %es:(%edi)
  596711:      	stosl	%eax, %es:(%edi)
  596712:      	stosl	%eax, %es:(%edi)
  596713:      	stosl	%eax, %es:(%edi)
  596714:      	stosl	%eax, %es:(%edi)
  596715:      	stosl	%eax, %es:(%edi)
  596716:      	stosl	%eax, %es:(%edi)
  596717:      	stosl	%eax, %es:(%edi)
  596718:      	stosl	%eax, %es:(%edi)
  596719:      	stosl	%eax, %es:(%edi)
  59671a:      	stosl	%eax, %es:(%edi)
  59671b:      	stosl	%eax, %es:(%edi)
  59671c:      	stosl	%eax, %es:(%edi)
  59671d:      	stosl	%eax, %es:(%edi)
  59671e:      	stosl	%eax, %es:(%edi)
  59671f:      	stosl	%eax, %es:(%edi)
  596720:      	stosl	%eax, %es:(%edi)
  596721:      	stosl	%eax, %es:(%edi)
  596722:      	stosl	%eax, %es:(%edi)
  596723:      	stosl	%eax, %es:(%edi)
  596724:      	stosl	%eax, %es:(%edi)
  596725:      	stosl	%eax, %es:(%edi)
  596726:      	stosl	%eax, %es:(%edi)
  596727:      	stosl	%eax, %es:(%edi)
  596728:      	stosl	%eax, %es:(%edi)
  596729:      	stosl	%eax, %es:(%edi)
  59672a:      	stosl	%eax, %es:(%edi)
  59672b:      	stosl	%eax, %es:(%edi)
  59672c:      	stosl	%eax, %es:(%edi)
  59672d:      	jae	0x5967a3 <.text+0x1957a3>
  59672f:      	jne	0x5967a7 <.text+0x1957a7>
  596731:      	ja	0x5967ab <.text+0x1957ab>
  596733:      	jns	0x5967af <.text+0x1957af>
  596735:      	jnp	0x5967b3 <.text+0x1957b3>
  596737:      	jge	0x5967b7 <.text+0x1957b7>
  596739:      	jg	0x5966bb <.text+0x1956bb>
  59673b:      	addl	$0x8a898887, -0x797a7b7d(%edx) # imm = 0x8A898887
  596745:      	movl	-0x6e6f7072(%ebp,%ecx,4), %ecx
  59674c:      	xchgl	%edx, %eax
  59674d:      	xchgl	%ebx, %eax
  59674e:      	xchgl	%esp, %eax
  59674f:      	stosl	%eax, %es:(%edi)
  596750:      	stosl	%eax, %es:(%edi)
  596751:      	stosl	%eax, %es:(%edi)
  596752:      	stosl	%eax, %es:(%edi)
  596753:      	stosl	%eax, %es:(%edi)
  596754:      	stosl	%eax, %es:(%edi)
  596755:      	stosl	%eax, %es:(%edi)
  596756:      	stosl	%eax, %es:(%edi)
  596757:      	stosl	%eax, %es:(%edi)
  596758:      	stosl	%eax, %es:(%edi)
  596759:      	stosl	%eax, %es:(%edi)
  59675a:      	stosl	%eax, %es:(%edi)
  59675b:      	stosl	%eax, %es:(%edi)
  59675c:      	stosl	%eax, %es:(%edi)
  59675d:      	stosl	%eax, %es:(%edi)
  59675e:      	stosl	%eax, %es:(%edi)
  59675f:      	stosl	%eax, %es:(%edi)
  596760:      	stosl	%eax, %es:(%edi)
  596761:      	stosl	%eax, %es:(%edi)
  596762:      	stosl	%eax, %es:(%edi)
  596763:      	stosl	%eax, %es:(%edi)
  596764:      	stosl	%eax, %es:(%edi)
  596765:      	stosl	%eax, %es:(%edi)
  596766:      	stosl	%eax, %es:(%edi)
  596767:      	stosl	%eax, %es:(%edi)
  596768:      	stosl	%eax, %es:(%edi)
  596769:      	stosl	%eax, %es:(%edi)
  59676a:      	stosl	%eax, %es:(%edi)
  59676b:      	stosl	%eax, %es:(%edi)
  59676c:      	stosl	%eax, %es:(%edi)
  59676d:      	stosl	%eax, %es:(%edi)
  59676e:      	stosl	%eax, %es:(%edi)
  59676f:      	stosl	%eax, %es:(%edi)
  596770:      	stosl	%eax, %es:(%edi)
  596771:      	stosl	%eax, %es:(%edi)
  596772:      	stosl	%eax, %es:(%edi)
  596773:      	stosl	%eax, %es:(%edi)
  596774:      	stosl	%eax, %es:(%edi)
  596775:      	stosl	%eax, %es:(%edi)
  596776:      	stosl	%eax, %es:(%edi)
  596777:      	stosl	%eax, %es:(%edi)
  596778:      	stosl	%eax, %es:(%edi)
  596779:      	stosl	%eax, %es:(%edi)
  59677a:      	stosl	%eax, %es:(%edi)
  59677b:      	stosl	%eax, %es:(%edi)
  59677c:      	stosl	%eax, %es:(%edi)
  59677d:      	stosl	%eax, %es:(%edi)
  59677e:      	stosl	%eax, %es:(%edi)
  59677f:      	stosl	%eax, %es:(%edi)
  596780:      	stosl	%eax, %es:(%edi)
  596781:      	stosl	%eax, %es:(%edi)
  596782:      	stosl	%eax, %es:(%edi)
  596783:      	stosl	%eax, %es:(%edi)
  596784:      	stosl	%eax, %es:(%edi)
  596785:      	stosl	%eax, %es:(%edi)
  596786:      	stosl	%eax, %es:(%edi)
  596787:      	stosl	%eax, %es:(%edi)
  596788:      	stosl	%eax, %es:(%edi)
  596789:      	stosl	%eax, %es:(%edi)
  59678a:      	stosl	%eax, %es:(%edi)
  59678b:      	stosl	%eax, %es:(%edi)
  59678c:      	stosl	%eax, %es:(%edi)
  59678d:      	stosl	%eax, %es:(%edi)
  59678e:      	stosl	%eax, %es:(%edi)
  59678f:      	stosl	%eax, %es:(%edi)
  596790:      	stosl	%eax, %es:(%edi)
  596791:      	stosl	%eax, %es:(%edi)
  596792:      	stosl	%eax, %es:(%edi)
  596793:      	xchgl	%ebp, %eax
  596794:      	xchgl	%esi, %eax
  596795:      	xchgl	%edi, %eax
  596796:      	cwtl
  596797:      	cltd
  596798:      	lcalll	$-0x6365, $0xabababab   # imm = 0x9C9B
                                                # imm = 0xABABABAB
  59679f:      	popfl
  5967a0:      	sahf
  5967a1:      	lahf
  5967a2:      	movb	0xa4a3a2a1, %al
  5967a7:      	movsl	(%esi), %es:(%edi)
  5967a8:      	cmpsb	%es:(%edi), (%esi)
  5967a9:      	cmpsl	%es:(%edi), (%esi)
  5967aa:      	stosl	%eax, %es:(%edi)
  5967ab:      	stosl	%eax, %es:(%edi)
  5967ac:      	stosl	%eax, %es:(%edi)
  5967ad:      	stosl	%eax, %es:(%edi)
  5967ae:      	stosl	%eax, %es:(%edi)
  5967af:      	stosl	%eax, %es:(%edi)
  5967b0:      	stosl	%eax, %es:(%edi)
  5967b1:      	stosl	%eax, %es:(%edi)
  5967b2:      	stosl	%eax, %es:(%edi)
  5967b3:      	stosl	%eax, %es:(%edi)
  5967b4:      	stosl	%eax, %es:(%edi)
  5967b5:      	stosl	%eax, %es:(%edi)
  5967b6:      	stosl	%eax, %es:(%edi)
  5967b7:      	stosl	%eax, %es:(%edi)
  5967b8:      	stosl	%eax, %es:(%edi)
  5967b9:      	stosl	%eax, %es:(%edi)
  5967ba:      	stosl	%eax, %es:(%edi)
  5967bb:      	stosl	%eax, %es:(%edi)
  5967bc:      	stosl	%eax, %es:(%edi)
  5967bd:      	stosl	%eax, %es:(%edi)
  5967be:      	stosl	%eax, %es:(%edi)
  5967bf:      	stosl	%eax, %es:(%edi)
  5967c0:      	stosl	%eax, %es:(%edi)
  5967c1:      	stosl	%eax, %es:(%edi)
  5967c2:      	stosl	%eax, %es:(%edi)
  5967c3:      	stosl	%eax, %es:(%edi)
  5967c4:      	stosl	%eax, %es:(%edi)
  5967c5:      	stosl	%eax, %es:(%edi)
  5967c6:      	stosl	%eax, %es:(%edi)
  5967c7:      	stosl	%eax, %es:(%edi)
  5967c8:      	stosl	%eax, %es:(%edi)
  5967c9:      	stosl	%eax, %es:(%edi)
  5967ca:      	stosl	%eax, %es:(%edi)
  5967cb:      	stosl	%eax, %es:(%edi)
  5967cc:      	stosl	%eax, %es:(%edi)
  5967cd:      	stosl	%eax, %es:(%edi)
  5967ce:      	stosl	%eax, %es:(%edi)
  5967cf:      	stosl	%eax, %es:(%edi)
  5967d0:      	stosl	%eax, %es:(%edi)
  5967d1:      	stosl	%eax, %es:(%edi)
  5967d2:      	stosl	%eax, %es:(%edi)
  5967d3:      	stosl	%eax, %es:(%edi)
  5967d4:      	stosl	%eax, %es:(%edi)
  5967d5:      	stosl	%eax, %es:(%edi)
  5967d6:      	stosl	%eax, %es:(%edi)
  5967d7:      	stosl	%eax, %es:(%edi)
  5967d8:      	stosl	%eax, %es:(%edi)
  5967d9:      	stosl	%eax, %es:(%edi)
  5967da:      	stosl	%eax, %es:(%edi)
  5967db:      	stosl	%eax, %es:(%edi)
  5967dc:      	stosl	%eax, %es:(%edi)
  5967dd:      	stosl	%eax, %es:(%edi)
  5967de:      	stosl	%eax, %es:(%edi)
  5967df:      	stosl	%eax, %es:(%edi)
  5967e0:      	stosl	%eax, %es:(%edi)
  5967e1:      	stosl	%eax, %es:(%edi)
  5967e2:      	stosl	%eax, %es:(%edi)
  5967e3:      	stosl	%eax, %es:(%edi)
  5967e4:      	stosl	%eax, %es:(%edi)
  5967e5:      	stosl	%eax, %es:(%edi)
  5967e6:      	stosl	%eax, %es:(%edi)
  5967e7:      	stosl	%eax, %es:(%edi)
  5967e8:      	stosl	%eax, %es:(%edi)
  5967e9:      	stosl	%eax, %es:(%edi)
  5967ea:      	stosl	%eax, %es:(%edi)
  5967eb:      	stosl	%eax, %es:(%edi)
  5967ec:      	stosl	%eax, %es:(%edi)
  5967ed:      	stosl	%eax, %es:(%edi)
  5967ee:      	stosl	%eax, %es:(%edi)
  5967ef:      	stosl	%eax, %es:(%edi)
  5967f0:      	stosl	%eax, %es:(%edi)
  5967f1:      	stosl	%eax, %es:(%edi)
  5967f2:      	stosl	%eax, %es:(%edi)
  5967f3:      	stosl	%eax, %es:(%edi)
  5967f4:      	stosl	%eax, %es:(%edi)
  5967f5:      	stosl	%eax, %es:(%edi)
  5967f6:      	stosl	%eax, %es:(%edi)
  5967f7:      	stosl	%eax, %es:(%edi)
  5967f8:      	stosl	%eax, %es:(%edi)
  5967f9:      	stosl	%eax, %es:(%edi)
  5967fa:      	stosl	%eax, %es:(%edi)
  5967fb:      	stosl	%eax, %es:(%edi)
  5967fc:      	stosl	%eax, %es:(%edi)
  5967fd:      	stosl	%eax, %es:(%edi)
  5967fe:      	stosl	%eax, %es:(%edi)
  5967ff:      	testb	$-0x57, %al
  596801:      	stosl	%eax, %es:(%edi)
  596802:      	stosl	%eax, %es:(%edi)
  596803:      	stosl	%eax, %es:(%edi)
  596804:      	stosl	%eax, %es:(%edi)
  596805:      	stosl	%eax, %es:(%edi)
  596806:      	stosl	%eax, %es:(%edi)
  596807:      	stosl	%eax, %es:(%edi)
  596808:      	stosl	%eax, %es:(%edi)
  596809:      	stosl	%eax, %es:(%edi)
  59680a:      	stosl	%eax, %es:(%edi)
  59680b:      	stosl	%eax, %es:(%edi)
  59680c:      	stosl	%eax, %es:(%edi)
  59680d:      	stosl	%eax, %es:(%edi)
  59680e:      	stosl	%eax, %es:(%edi)
  59680f:      	stosl	%eax, %es:(%edi)
  596810:      	stosl	%eax, %es:(%edi)
  596811:      	stosl	%eax, %es:(%edi)
  596812:      	stosl	%eax, %es:(%edi)
  596813:      	stosl	%eax, %es:(%edi)
  596814:      	stosl	%eax, %es:(%edi)
  596815:      	stosl	%eax, %es:(%edi)
  596816:      	stosl	%eax, %es:(%edi)
  596817:      	stosl	%eax, %es:(%edi)
  596818:      	stosl	%eax, %es:(%edi)
  596819:      	stosl	%eax, %es:(%edi)
  59681a:      	stosl	%eax, %es:(%edi)
  59681b:      	stosl	%eax, %es:(%edi)
  59681c:      	stosl	%eax, %es:(%edi)
  59681d:      	stosl	%eax, %es:(%edi)
  59681e:      	stosl	%eax, %es:(%edi)
  59681f:      	stosl	%eax, %es:(%edi)
  596820:      	stosl	%eax, %es:(%edi)
  596821:      	stosl	%eax, %es:(%edi)
  596822:      	stosl	%eax, %es:(%edi)
  596823:      	stosl	%eax, %es:(%edi)
  596824:      	stosl	%eax, %es:(%edi)
  596825:      	stosl	%eax, %es:(%edi)
  596826:      	stosl	%eax, %es:(%edi)
  596827:      	stosl	%eax, %es:(%edi)
  596828:      	stosl	%eax, %es:(%edi)
  596829:      	stosl	%eax, %es:(%edi)
  59682a:      	stosl	%eax, %es:(%edi)
  59682b:      	stosl	%eax, %es:(%edi)
  59682c:      	stosl	%eax, %es:(%edi)
  59682d:      	stosl	%eax, %es:(%edi)
  59682e:      	stosl	%eax, %es:(%edi)
  59682f:      	stosl	%eax, %es:(%edi)
  596830:      	stosl	%eax, %es:(%edi)
  596831:      	stosl	%eax, %es:(%edi)
  596832:      	stosl	%eax, %es:(%edi)
  596833:      	stosl	%eax, %es:(%edi)
  596834:      	stosl	%eax, %es:(%edi)
  596835:      	stosl	%eax, %es:(%edi)
  596836:      	stosl	%eax, %es:(%edi)
  596837:      	stosl	%eax, %es:(%edi)
  596838:      	stosl	%eax, %es:(%edi)
  596839:      	stosl	%eax, %es:(%edi)
  59683a:      	stosl	%eax, %es:(%edi)
  59683b:      	stosl	%eax, %es:(%edi)
  59683c:      	stosl	%eax, %es:(%edi)
  59683d:      	stosl	%eax, %es:(%edi)
  59683e:      	stosl	%eax, %es:(%edi)
  59683f:      	stosl	%eax, %es:(%edi)
  596840:      	stosl	%eax, %es:(%edi)
  596841:      	stosl	%eax, %es:(%edi)
  596842:      	stosl	%eax, %es:(%edi)
  596843:      	stosl	%eax, %es:(%edi)
  596844:      	stosl	%eax, %es:(%edi)
  596845:      	stosl	%eax, %es:(%edi)
  596846:      	stosl	%eax, %es:(%edi)
  596847:      	stosl	%eax, %es:(%edi)
  596848:      	stosl	%eax, %es:(%edi)
  596849:      	stosl	%eax, %es:(%edi)
  59684a:      	stosl	%eax, %es:(%edi)
  59684b:      	stosl	%eax, %es:(%edi)
  59684c:      	stosl	%eax, %es:(%edi)
  59684d:      	stosl	%eax, %es:(%edi)
  59684e:      	stosl	%eax, %es:(%edi)
  59684f:      	stosl	%eax, %es:(%edi)
  596850:      	stosl	%eax, %es:(%edi)
  596851:      	stosl	%eax, %es:(%edi)
  596852:      	stosl	%eax, %es:(%edi)
  596853:      	stosl	%eax, %es:(%edi)
  596854:      	stosl	%eax, %es:(%edi)
  596855:      	stosl	%eax, %es:(%edi)
  596856:      	stosl	%eax, %es:(%edi)
  596857:      	stosl	%eax, %es:(%edi)
  596858:      	stosl	%eax, %es:(%edi)
  596859:      	stosl	%eax, %es:(%edi)
  59685a:      	stosl	%eax, %es:(%edi)
  59685b:      	stosl	%eax, %es:(%edi)
  59685c:      	stosl	%eax, %es:(%edi)
  59685d:      	stosb	%al, %es:(%edi)
  59685e:      	leal	(%ecx), %ecx
  596861:      	popl	%esi
  596862:      	outl	%eax, $0x58
  596864:      	addb	%ch, -0x19(%eax)
  596867:      	popl	%eax
  596868:      	addb	%dh, -0x19(%edx)
  59686b:      	popl	%eax
  59686c:      	addb	%bh, 0x58(%edi,%eiz,8)
  596870:      	addb	%al, -0x6fffa719(%esi)
  596876:      	outl	%eax, $0x58
  596878:      	addb	%bl, -0x5bffa719(%edx)
  59687e:      	outl	%eax, $0x58
  596880:      	addb	%ch, 0x58(%eax,%ebp,8)
  596884:      	addb	%dh, -0x18(%esi)
  596887:      	popl	%eax
  596888:      	addb	%al, -0x75ffa718(%eax)
  59688e:      	calll	0xe8ed68eb
  596893:      	popl	%eax
  596894:      	addb	%bl, -0x57ffa718(%esi)
  59689a:      	calll	0xe90b68f7
  59689f:      	popl	%eax
  5968a0:      	addb	%ah, %dl
  5968a2:      	calll	0xe94568ff
  5968a7:      	popl	%eax
  5968a8:      	addb	%dh, %dh
  5968aa:      	calll	0xe9596907
  5968af:      	popl	%eax
  5968b0:      	addb	%cl, (%edx)
  5968b2:      	jmp	0xe96d690f
  5968b7:      	popl	%eax
  5968b8:      	addb	%bl, (%esi)
  5968ba:      	jmp	0xe9816917
  5968bf:      	popl	%eax
  5968c0:      	addb	%dh, (%edx)
  5968c2:      	jmp	0xe995691f
  5968c7:      	popl	%eax
  5968c8:      	addb	%al, -0x17(%esi)
  5968cb:      	popl	%eax
  5968cc:      	addb	%dl, -0x17(%eax)
  5968cf:      	popl	%eax
  5968d0:      	addb	%bl, -0x17(%edx)
  5968d3:      	popl	%eax
  5968d4:      	addb	%ah, 0x58(%ecx,%ebp,8)
  5968d8:      	addb	%ch, -0x17(%esi)
  5968db:      	popl	%eax
  5968dc:      	addb	%bh, -0x17(%eax)
  5968df:      	popl	%eax
  5968e0:      	addb	%al, -0x73ffa717(%edx)
  5968e6:      	jmp	0xe9ef6943
  5968eb:      	popl	%eax
  5968ec:      	addb	%ah, -0x55ffa717(%eax)
  5968f2:      	jmp	0xea0d694f
  5968f7:      	popl	%eax
  5968f8:      	addb	%bh, -0x37ffa717(%esi)
  5968fe:      	jmp	0xea2b695b
  596903:      	popl	%eax
  596904:      	addb	%bl, %ah
  596906:      	jmp	0xea3f6963
  59690b:      	popl	%eax
  59690c:      	addb	%dh, %al
  59690e:      	jmp	0xea53696b
  596913:      	popl	%eax
  596914:      	addb	%al, (%edx,%ebp,8)
  596917:      	popl	%eax
  596918:      	addb	%cl, (%esi)
  59691a:      	ljmpl	$0x58, $0xea180058      # imm = 0xEA180058
  596921:      	andb	%dl, %ch
  596923:      	popl	%eax
  596924:      	addb	%ch, (%edx,%ebp,8)
  596927:      	popl	%eax
  596928:      	addb	%dl, (%esi)
  59692a:      	sbbb	(%ecx), %bl
  59692d:      	addb	%al, (%ecx)
  59692f:      	addb	(%ebx), %al
  596931:      	addb	$0x22, %al
  596933:      	andb	(%edx), %ah
  596935:      	andb	(%edx), %ah
  596937:      	andb	(%edx), %ah
  596939:      	andb	(%edx), %ah
  59693b:      	andb	(%edx), %ah
  59693d:      	andb	(%edx), %ah
  59693f:      	andb	(%edx), %ah
  596941:      	andb	(%edx), %ah
  596943:      	andb	(%edx), %ah
  596945:      	andb	(%edx), %ah
  596947:      	andb	(%edx), %ah
  596949:      	andb	(%edx), %ah
  59694b:      	andb	(%edx), %ah
  59694d:      	andb	(%edx), %ah
  59694f:      	andb	(%edx), %ah
  596951:      	andb	(%edx), %ah
  596953:      	andb	(%edx), %ah
  596955:      	andb	(%edx), %ah
  596957:      	andb	(%edx), %ah
  596959:      	andb	(%edx), %ah
  59695b:      	andb	(%edx), %ah
  59695d:      	andb	(%edx), %ah
  59695f:      	andb	(%edx), %ah
  596961:      	andb	(%edx), %ah
  596963:      	andb	(%edx), %ah
  596965:      	andb	(%edx), %ah
  596967:      	andb	(%edx), %ah
  596969:      	andb	(%edx), %ah
  59696b:      	andb	(%edx), %ah
  59696d:      	andb	(%edx), %ah
  59696f:      	andb	(%edx), %ah
  596971:      	andb	(%edx), %ah
  596973:      	andb	(%edx), %ah
  596975:      	andb	(%edx), %ah
  596977:      	andb	(%edx), %ah
  596979:      	andb	(%edx), %ah
  59697b:      	andb	(%edx), %ah
  59697d:      	andb	(%edx), %ah
  59697f:      	andb	(%edx), %ah
  596981:      	andb	(%edx), %ah
  596983:      	andb	(%edx), %ah
  596985:      	andb	(%edx), %ah
  596987:      	addl	$0x9080706, %eax        # imm = 0x9080706
  59698c:      	orb	(%ebx), %cl
  59698e:      	orb	$0xd, %al
  596990:      	pushl	%cs
  596991:      	movups	(%ecx), %xmm2
  596994:      	adcb	(%ebx), %dl
  596996:      	adcb	$0x15, %al
  596998:      	pushl	%ss
  596999:      	popl	%ss
  59699a:      	sbbb	%bl, (%ecx)
  59699c:      	sbbb	(%ebx), %bl
  59699e:      	sbbb	$0x1d, %al
  5969a0:      	pushl	%ds
  5969a1:      	popl	%ds
  5969a2:      	andb	%ah, (%ecx)
  5969a4:      	nop
  5969a5:      	outsl	(%esi), %dx
  5969a6:      	ljmpl	$0x58, $0xea790058      # imm = 0xEA790058
  5969ad:      	subl	$0x58, %edx
  5969b0:      	addb	%cl, -0x68ffa716(%ebp)
  5969b6:      	ljmpl	$0x58, $0xeaa10058      # imm = 0xEAA10058
  5969bd:      	stosl	%eax, %es:(%edi)
  5969be:      	ljmpl	$0x58, $0xead30058      # imm = 0xEAD30058
  5969c5:      	fucomp	%st(2)
  5969c7:      	popl	%eax
  5969c8:      	addb	%ah, %bh
  5969ca:      	ljmpl	$0x58, $0xeaf10058      # imm = 0xEAF10058
  5969d1:      	movb	$-0x16, %ch
  5969d3:      	popl	%eax
  5969d4:      	addb	%bh, -0x36ffa716(%edi)
  5969da:      	ljmpl	$0x59, $0x1a160058      # imm = 0x1A160058
  5969e1:      	addb	%al, (%ecx)
  5969e3:      	addb	(%ebx), %al
  5969e5:      	addb	$0x5, %al
  5969e7:      	pushl	%es
  5969e8:      	popl	%es
  5969e9:      	orb	%cl, (%ecx)
  5969eb:      	orb	(%esi), %cl
  5969ed:      	pushl	%cs
  5969ee:      	pushl	%cs
  5969ef:      	pushl	%cs
  5969f0:      	pushl	%cs
  5969f1:      	pushl	%cs
  5969f2:      	pushl	%cs
  5969f3:      	pushl	%cs
  5969f4:      	pushl	%cs
  5969f5:      	orl	0x58ec0f90(,%ecx), %ecx
  5969fc:      	addb	%bl, (%ecx)
  5969fe:      	inb	%dx, %al
  5969ff:      	popl	%eax
  596a00:      	addb	%ah, (%ebx)
  596a02:      	inb	%dx, %al
  596a03:      	popl	%eax
  596a04:      	addb	%ch, 0x370058ec
  596a0a:      	inb	%dx, %al
  596a0b:      	popl	%eax
  596a0c:      	addb	%al, -0x14(%ecx)
  596a0f:      	popl	%eax
  596a10:      	addb	%cl, -0x14(%ebx)
  596a13:      	popl	%eax
  596a14:      	addb	%dl, -0x14(%ebp)
  596a17:      	popl	%eax
  596a18:      	addb	%bl, -0x14(%edi)
  596a1b:      	popl	%eax
  596a1c:      	addb	%ch, -0x14(%ecx)
  596a1f:      	popl	%eax
  596a20:      	addb	%dh, -0x14(%ebx)
  596a23:      	popl	%eax
  596a24:      	addb	%bh, -0x14(%ebp)
  596a27:      	popl	%eax
  596a28:      	addb	%al, -0x4fffa714(%edi)
  596a2e:      	inb	%dx, %al
  596a2f:      	popl	%eax
  596a30:      	addb	%bh, -0x3bffa714(%edx)
  596a36:      	inb	%dx, %al
  596a37:      	popl	%eax
  596a38:      	addb	%cl, %dh
  596a3a:      	inb	%dx, %al
  596a3b:      	popl	%eax
  596a3c:      	addb	%bl, %al
  596a3e:      	inb	%dx, %al
  596a3f:      	popl	%eax
  596a40:      	addb	%ah, %dl
  596a42:      	inb	%dx, %al
  596a43:      	popl	%eax
  596a44:      	addb	%ch, %ah
  596a46:      	inb	%dx, %al
  596a47:      	popl	%eax
  596a48:      	addb	%dh, %dh
  596a4a:      	inb	%dx, %al
  596a4b:      	popl	%eax
  596a4c:      	addb	%al, (%eax)
  596a4e:      	inl	%dx, %eax
  596a4f:      	popl	%eax
  596a50:      	addb	%cl, (%edx)
  596a52:      	inl	%dx, %eax
  596a53:      	popl	%eax
  596a54:      	addb	%dl, -0x12e1ffa8(,%ebp,8)
  596a5b:      	popl	%eax
  596a5c:      	addb	%ch, (%eax)
  596a5e:      	inl	%dx, %eax
  596a5f:      	popl	%eax
  596a60:      	addb	%dh, (%edx)
  596a62:      	inl	%dx, %eax
  596a63:      	popl	%eax
  596a64:      	addb	%bh, -0x12b9ffa8(,%ebp,8)
  596a6b:      	popl	%eax
  596a6c:      	addb	%dl, -0x13(%eax)
  596a6f:      	popl	%eax
  596a70:      	addb	%bl, -0x13(%edx)
  596a73:      	popl	%eax
  596a74:      	addb	%ah, 0x58(%ebp,%ebp,8)
  596a78:      	addb	%ch, -0x13(%esi)
  596a7b:      	popl	%eax
  596a7c:      	addb	%bh, -0x13(%eax)
  596a7f:      	popl	%eax
  596a80:      	addb	%al, -0x73ffa713(%edx)
  596a86:      	inl	%dx, %eax
  596a87:      	popl	%eax
  596a88:      	addb	%dl, -0x5fffa713(%esi)
  596a8e:      	inl	%dx, %eax
  596a8f:      	popl	%eax
  596a90:      	addb	%ch, -0x19ffa713(%edx)
  596a96:      	inl	%dx, %eax
  596a97:      	popl	%eax
  596a98:      	addb	%dh, %al
  596a9a:      	inl	%dx, %eax
  596a9b:      	popl	%eax
  596a9c:      	addb	%bh, %dl
  596a9e:      	inl	%dx, %eax
  596a9f:      	popl	%eax
  596aa0:      	addb	%al, (%esi,%ebp,8)
  596aa3:      	popl	%eax
  596aa4:      	addb	%dl, (%esi)
  596aa6:      	sbbb	(%ecx), %bl
  596aa9:      	pushl	%cs
  596aaa:      	outb	%al, %dx
  596aab:      	popl	%eax
  596aac:      	addb	%bl, (%eax)
  596aae:      	outb	%al, %dx
  596aaf:      	popl	%eax
  596ab0:      	addb	%ah, (%edx)
  596ab2:      	outb	%al, %dx
  596ab3:      	popl	%eax
  596ab4:      	addb	%ch, (%esi,%ebp,8)
  596ab7:      	popl	%eax
  596ab8:      	addb	%dh, (%esi)
  596aba:      	outb	%al, %dx
  596abb:      	popl	%eax
  596abc:      	addb	%al, -0x12(%eax)
  596abf:      	popl	%eax
  596ac0:      	addb	%cl, -0x12(%edx)
  596ac3:      	popl	%eax
  596ac4:      	addb	%dl, 0x58(%esi,%ebp,8)
  596ac8:      	addb	%bl, -0x12(%esi)
  596acb:      	popl	%eax
  596acc:      	addb	%ch, -0x12(%eax)
  596acf:      	popl	%eax
  596ad0:      	addb	%dh, -0x12(%edx)
  596ad3:      	popl	%eax
  596ad4:      	addb	%bh, 0x58(%esi,%ebp,8)
  596ad8:      	addb	%al, -0x6fffa712(%esi)
  596ade:      	outb	%al, %dx
  596adf:      	popl	%eax
  596ae0:      	addb	%bl, -0x5bffa712(%edx)
  596ae6:      	outb	%al, %dx
  596ae7:      	popl	%eax
  596ae8:      	addb	%ch, -0x47ffa712(%esi)
  596aee:      	outb	%al, %dx
  596aef:      	popl	%eax
  596af0:      	addb	%al, %dl
  596af2:      	outb	%al, %dx
  596af3:      	popl	%eax
  596af4:      	addb	%cl, %ah
  596af6:      	outb	%al, %dx
  596af7:      	popl	%eax
  596af8:      	addb	%dl, %dh
  596afa:      	outb	%al, %dx
  596afb:      	popl	%eax
  596afc:      	addb	%ah, %al
  596afe:      	outb	%al, %dx
  596aff:      	popl	%eax
  596b00:      	addb	%ch, %dl
  596b02:      	outb	%al, %dx
  596b03:      	popl	%eax
  596b04:      	addb	%dh, %ah
  596b06:      	outb	%al, %dx
  596b07:      	popl	%eax
  596b08:      	addb	%bh, %dh
  596b0a:      	outb	%al, %dx
  596b0b:      	popl	%eax
  596b0c:      	addb	%cl, (%eax)
  596b0e:      	outl	%eax, %dx
  596b0f:      	popl	%eax
  596b10:      	addb	%dl, (%edx)
  596b12:      	outl	%eax, %dx
  596b13:      	popl	%eax
  596b14:      	addb	%bl, (%edi,%ebp,8)
  596b17:      	popl	%eax
  596b18:      	addb	%ah, (%esi)
  596b1a:      	outl	%eax, %dx
  596b1b:      	popl	%eax
  596b1c:      	addb	%dh, (%eax)
  596b1e:      	outl	%eax, %dx
  596b1f:      	popl	%eax
  596b20:      	addb	%bh, (%edx)
  596b22:      	outl	%eax, %dx
  596b23:      	popl	%eax
  596b24:      	addb	%al, 0x58(%edi,%ebp,8)
  596b28:      	addb	%cl, -0x11(%esi)
  596b2b:      	popl	%eax
  596b2c:      	addb	%bl, -0x11(%eax)
  596b2f:      	popl	%eax
  596b30:      	addb	%dl, -0x65ffa711(%eax)
  596b36:      	outl	%eax, %dx
  596b37:      	popl	%eax
  596b38:      	addb	%ah, -0x1051ffa8(%edi,%ebp,8)
  596b3f:      	popl	%eax
  596b40:      	addb	%bh, -0x3dffa711(%eax)
  596b46:      	outl	%eax, %dx
  596b47:      	popl	%eax
  596b48:      	addb	%cl, %ah
  596b4a:      	outl	%eax, %dx
  596b4b:      	popl	%eax
  596b4c:      	addb	%dl, %dh
  596b4e:      	outl	%eax, %dx
  596b4f:      	popl	%eax
  596b50:      	addb	%ah, %al
  596b52:      	outl	%eax, %dx
  596b53:      	popl	%eax
  596b54:      	addb	%ch, %dl
  596b56:      	outl	%eax, %dx
  596b57:      	popl	%eax
  596b58:      	addb	%ah, (%esi)
  596b5a:      	lock
  596b5b:      	popl	%eax
  596b5c:      	addb	%dh, (%eax)
  596b5e:      	lock
  596b5f:      	popl	%eax
  596b60:      	addb	%bh, (%edx)
  596b62:      	lock
  596b63:      	popl	%eax
  596b64:      	addb	%al, 0x58(%eax,%esi,8)
  596b68:      	addb	%cl, -0x10(%esi)
  596b6b:      	popl	%eax
  596b6c:      	addb	%bl, -0x10(%eax)
  596b6f:      	popl	%eax
  596b70:      	addb	%ah, -0x10(%edx)
  596b73:      	popl	%eax
  596b74:      	addb	%ch, 0x58(%eax,%esi,8)
  596b78:      	addb	%dh, -0x10(%esi)
  596b7b:      	popl	%eax
  596b7c:      	addb	%al, -0x75ffa710(%eax)
  596b82:      	lock
  596b83:      	popl	%eax
  596b84:      	addb	%dl, -0xf61ffa8(%eax,%esi,8)
  596b8b:      	popl	%eax
  596b8c:      	addb	%ch, -0x4dffa710(%eax)
  596b92:      	lock
  596b93:      	popl	%eax
  596b94:      	addb	%bh, -0xe4affa8(%eax,%esi,8)
  596b9b:      	popl	%eax
  596b9c:      	addb	%bh, -0x36ffa70f(%edi)
  596ba2:      	<unknown>
  596ba3:      	popl	%eax
  596ba4:      	addb	%dl, %bl
  596ba6:      	<unknown>
  596ba7:      	popl	%eax
  596ba8:      	addb	%bl, %ch
  596baa:      	<unknown>
  596bab:      	popl	%eax
  596bac:      	addb	%ah, %bh
  596bae:      	<unknown>
  596baf:      	popl	%eax
  596bb0:      	addb	%dh, %cl
  596bb2:      	<unknown>
  596bb3:      	popl	%eax
  596bb4:      	addb	%bh, %bl
  596bb6:      	<unknown>
  596bb7:      	popl	%eax
  596bb8:      	addb	%ch, (%ebx)
  596bba:      	repne		popl	%eax
  596bbc:      	addb	%dh, 0x3f0058f2
  596bc2:      	repne		popl	%eax
  596bc4:      	addb	%cl, -0xe(%ecx)
  596bc7:      	popl	%eax
  596bc8:      	addb	%dl, -0xe(%ebx)
  596bcb:      	popl	%eax
  596bcc:      	addb	%bl, -0xe(%ebp)
  596bcf:      	popl	%eax
  596bd0:      	addb	%ah, -0xe(%edi)
  596bd3:      	popl	%eax
  596bd4:      	addb	%dh, -0xe(%ecx)
  596bd7:      	popl	%eax
  596bd8:      	addb	%bh, -0xe(%ebx)
  596bdb:      	popl	%eax
  596bdc:      	addb	%al, -0x70ffa70e(%ebp)
  596be2:      	repne		popl	%eax
  596be4:      	addb	%bl, -0x5cffa70e(%ecx)
  596bea:      	repne		popl	%eax
  596bec:      	addb	%ch, -0x48ffa70e(%ebp)
  596bf2:      	repne		popl	%eax
  596bf4:      	addb	%al, %cl
  596bf6:      	repne		popl	%eax
  596bf8:      	addb	%cl, %bl
  596bfa:      	repne		popl	%eax
  596bfc:      	addb	%dl, (%esi)
  596bfe:      	sbbb	(%ecx), %bl
  596c01:      	addb	%al, (%ecx)
  596c03:      	addb	(%ecx), %dl
  596c05:      	adcl	%edx, (%ecx)
  596c07:      	adcl	%edx, (%ecx)
  596c09:      	adcl	%edx, (%ecx)
  596c0b:      	adcl	%edx, (%ecx)
  596c0d:      	addl	(%ecx), %edx
  596c0f:      	addb	$0x5, %al
  596c11:      	adcl	%eax, (%esi)
  596c13:      	popl	%es
  596c14:      	orb	%dl, (%ecx)
  596c16:      	orl	%ecx, (%edx)
  596c18:      	adcl	%edx, (%ecx)
  596c1a:      	adcl	%ecx, (%ebx)
  596c1c:      	orb	$0xd, %al
  596c1e:      	pushl	%cs
  596c1f:      	movups	-0x63ffa770(%ebx), %xmm1
  596c26:      	rep		popl	%eax
  596c28:      	addb	%ah, -0x4fffa70d(%esi)
  596c2e:      	rep		popl	%eax
  596c30:      	addb	%bh, -0x3bffa70d(%edx)
  596c36:      	rep		popl	%eax
  596c38:      	addb	%cl, %dh
  596c3a:      	rep		popl	%eax
  596c3c:      	addb	%bl, %al
  596c3e:      	rep		popl	%eax
  596c40:      	addb	%ah, -0x55ffa70c(%eax)
  596c46:      	hlt
  596c47:      	popl	%eax
  596c48:      	addb	%dh, -0xb41ffa8(%esp,%esi,8)
  596c4f:      	popl	%eax
  596c50:      	addb	%cl, %al
  596c52:      	hlt
  596c53:      	popl	%eax
  596c54:      	addb	%dl, %dl
  596c56:      	hlt
  596c57:      	popl	%eax
  596c58:      	addb	%bl, %ah
  596c5a:      	hlt
  596c5b:      	popl	%eax
  596c5c:      	addb	%ah, %dh
  596c5e:      	hlt
  596c5f:      	popl	%eax
  596c60:      	addb	%dl, (%ecx)
  596c62:      	cmc
  596c63:      	popl	%eax
  596c64:      	addb	%bl, (%ebx)
  596c66:      	cmc
  596c67:      	popl	%eax
  596c68:      	addb	%ah, 0x2f0058f5
  596c6e:      	cmc
  596c6f:      	popl	%eax
  596c70:      	addb	%bh, (%ecx)
  596c72:      	cmc
  596c73:      	popl	%eax
  596c74:      	addb	%al, -0xb(%ebx)
  596c77:      	popl	%eax
  596c78:      	addb	%cl, -0xb(%ebp)
  596c7b:      	popl	%eax
  596c7c:      	addb	%dl, (%esi)
  596c7e:      	sbbb	(%ecx), %bl
  596c81:      	pushl	%edi
  596c82:      	cmc
  596c83:      	popl	%eax
  596c84:      	addb	%ah, -0xb(%ecx)
  596c87:      	popl	%eax
  596c88:      	addb	%ch, -0xb(%ebx)
  596c8b:      	popl	%eax
  596c8c:      	addb	%dh, -0xb(%ebp)
  596c8f:      	popl	%eax
  596c90:      	addb	%bh, -0xb(%edi)
  596c93:      	popl	%eax
  596c94:      	addb	%cl, -0x6cffa70b(%ecx)
  596c9a:      	cmc
  596c9b:      	popl	%eax
  596c9c:      	addb	%bl, -0x58ffa70b(%ebp)
  596ca2:      	cmc
  596ca3:      	popl	%eax
  596ca4:      	addb	%dh, -0x44ffa70b(%ecx)
  596caa:      	cmc
  596cab:      	popl	%eax
  596cac:      	addb	%al, %ch
  596cae:      	cmc
  596caf:      	popl	%eax
  596cb0:      	addb	%cl, %bh
  596cb2:      	cmc
  596cb3:      	popl	%eax
  596cb4:      	addb	%bl, %cl
  596cb6:      	cmc
  596cb7:      	popl	%eax
  596cb8:      	addb	%ah, %bl
  596cba:      	cmc
  596cbb:      	popl	%eax
  596cbc:      	addb	%ch, %ch
  596cbe:      	cmc
  596cbf:      	popl	%eax
  596cc0:      	addb	%dh, %bh
  596cc2:      	cmc
  596cc3:      	popl	%eax
  596cc4:      	addb	%al, (%ecx)
  596cc6:      	negb	(%eax)
  596cc9:      	orl	%esi, %esi
  596ccb:      	popl	%eax
  596ccc:      	addb	%dl, 0x1f0058f6
  596cd2:      	negb	(%eax)
  596cd5:      	subl	%esi, %esi
  596cd7:      	popl	%eax
  596cd8:      	addb	%dh, (%ebx)
  596cda:      	negb	(%eax)
  596cdd:      	cmpl	$0x470058f6, %eax       # imm = 0x470058F6
  596ce2:      	negb	(%eax)
  596ce5:      	pushl	%ecx
  596ce6:      	negb	(%eax)
  596ce9:      	popl	%ebx
  596cea:      	negb	(%eax)
  596ced:      	negb	%gs:(%eax)
  596cf1:      	outsl	(%esi), %dx
  596cf2:      	negb	(%eax)
  596cf5:      	jns	0x596ced <.text+0x195ced>
  596cf7:      	popl	%eax
  596cf8:      	addb	%al, -0x72ffa70a(%ebx)
  596cfe:      	negb	(%eax)
  596d01:      	xchgl	%edi, %eax
  596d02:      	negb	(%eax)
  596d05:      	movl	0xab0058f6, %eax
  596d0a:      	negb	(%eax)
  596d0d:      	movb	$-0xa, %ch
  596d0f:      	popl	%eax
  596d10:      	addb	%bh, -0x60ffa70a(%edi)
  596d16:      	std
  596d17:      	popl	%eax
  596d18:      	addb	%ch, 0x160058fd(%ecx)
  596d1e:      	sbbb	(%ecx), %bl
  596d21:      	pushl	%ss
  596d22:      	sbbb	(%ecx), %bl
  596d25:      	pushl	%ss
  596d26:      	sbbb	(%ecx), %bl
  596d29:      	pushl	%ss
  596d2a:      	sbbb	(%ecx), %bl
  596d2d:      	pushl	%ss
  596d2e:      	sbbb	(%ecx), %bl
  596d31:      	pushl	%ss
  596d32:      	sbbb	(%ecx), %bl
  596d35:      	pushl	%ss
  596d36:      	sbbb	(%ecx), %bl
  596d39:      	pushl	%ss
  596d3a:      	sbbb	(%ecx), %bl
  596d3d:      	pushl	%ss
  596d3e:      	sbbb	(%ecx), %bl
  596d41:      	pushl	%ss
  596d42:      	sbbb	(%ecx), %bl
  596d45:      	pushl	%ss
  596d46:      	sbbb	(%ecx), %bl
  596d49:      	pushl	%ss
  596d4a:      	sbbb	(%ecx), %bl
  596d4d:      	pushl	%ss
  596d4e:      	sbbb	(%ecx), %bl
  596d51:      	pushl	%ss
  596d52:      	sbbb	(%ecx), %bl
  596d55:      	pushl	%ss
  596d56:      	sbbb	(%ecx), %bl
  596d59:      	pushl	%ss
  596d5a:      	sbbb	(%ecx), %bl
  596d5d:      	pushl	%ss
  596d5e:      	sbbb	(%ecx), %bl
  596d61:      	pushl	%ss
  596d62:      	sbbb	(%ecx), %bl
  596d65:      	pushl	%ss
  596d66:      	sbbb	(%ecx), %bl
  596d69:      	pushl	%ss
  596d6a:      	sbbb	(%ecx), %bl
  596d6d:      	pushl	%ss
  596d6e:      	sbbb	(%ecx), %bl
  596d71:      	pushl	%ss
  596d72:      	sbbb	(%ecx), %bl
  596d75:      	pushl	%ss
  596d76:      	sbbb	(%ecx), %bl
  596d79:      	pushl	%ss
  596d7a:      	sbbb	(%ecx), %bl
  596d7d:      	pushl	%ss
  596d7e:      	sbbb	(%ecx), %bl
  596d81:      	pushl	%ss
  596d82:      	sbbb	(%ecx), %bl
  596d85:      	pushl	%ss
  596d86:      	sbbb	(%ecx), %bl
  596d89:      	pushl	%ss
  596d8a:      	sbbb	(%ecx), %bl
  596d8d:      	pushl	%ss
  596d8e:      	sbbb	(%ecx), %bl
  596d91:      	pushl	%ss
  596d92:      	sbbb	(%ecx), %bl
  596d95:      	pushl	%ss
  596d96:      	sbbb	(%ecx), %bl
  596d99:      	pushl	%ss
  596d9a:      	sbbb	(%ecx), %bl
  596d9d:      	pushl	%ss
  596d9e:      	sbbb	(%ecx), %bl
  596da1:      	pushl	%ss
  596da2:      	sbbb	(%ecx), %bl
  596da5:      	pushl	%ss
  596da6:      	sbbb	(%ecx), %bl
  596da9:      	pushl	%ss
  596daa:      	sbbb	(%ecx), %bl
  596dad:      	pushl	%ss
  596dae:      	sbbb	(%ecx), %bl
  596db1:      	pushl	%ss
  596db2:      	sbbb	(%ecx), %bl
  596db5:      	leave
  596db6:      	negb	(%eax)
  596db9:      	<unknown>
  596dbb:      	popl	%eax
  596dbc:      	addb	%bl, %ch
  596dbe:      	negb	(%eax)
  596dc1:      	outl	%eax, $0xf6
  596dc3:      	popl	%eax
  596dc4:      	addb	%dh, %cl
  596dc6:      	negb	(%eax)
  596dc9:      	sti
  596dca:      	negb	(%eax)
  596dcd:      	addl	$0xf0058f7, %eax        # imm = 0xF0058F7
  596dd2:      	negl	(%eax)
  596dd5:      	sbbl	%esi, %edi
  596dd7:      	popl	%eax
  596dd8:      	addb	%ah, (%ebx)
  596dda:      	negl	(%eax)
  596ddd:      	subl	$0x370058f7, %eax       # imm = 0x370058F7
  596de2:      	negl	(%eax)
  596de5:      	incl	%ecx
  596de6:      	negl	(%eax)
  596de9:      	decl	%ebx
  596dea:      	negl	(%eax)
  596ded:      	pushl	%ebp
  596dee:      	negl	(%eax)
  596df1:      	popl	%edi
  596df2:      	negl	(%eax)
  596df5:      	imull	$0xf7730058, %edi, %esi # imm = 0xF7730058
  596dfb:      	popl	%eax
  596dfc:      	addb	%dl, (%esi)
  596dfe:      	sbbb	(%ecx), %bl
  596e01:      	jge	0x596dfa <.text+0x195dfa>
  596e03:      	popl	%eax
  596e04:      	addb	%al, -0x6effa709(%edi)
  596e0a:      	negl	(%eax)
  596e0d:      	wait
  596e0e:      	negl	(%eax)
  596e11:      	movsl	(%esi), %es:(%edi)
  596e12:      	negl	(%eax)
  596e15:      	scasl	%es:(%edi), %eax
  596e16:      	negl	(%eax)
  596e19:      	movl	$0xc30058f7, %ecx       # imm = 0xC30058F7
  596e1e:      	negl	(%eax)
  596e21:      	int	$0xf7
  596e23:      	popl	%eax
  596e24:      	addb	%dl, %bh
  596e26:      	negl	(%eax)
  596e29:      	loope	0x596e22 <.text+0x195e22>
  596e2b:      	popl	%eax
  596e2c:      	addb	%ch, %bl
  596e2e:      	negl	(%eax)
  596e31:      	cmc
  596e32:      	negl	(%eax)
  596e35:      	pushl	%edi
  596e37:      	popl	%eax
  596e38:      	addb	%cl, (%ecx)
  596e3a:      	clc
  596e3b:      	popl	%eax
  596e3c:      	addb	%dl, (%ebx)
  596e3e:      	clc
  596e3f:      	popl	%eax
  596e40:      	addb	%bl, 0x270058f8
  596e46:      	clc
  596e47:      	popl	%eax
  596e48:      	addb	%dh, (%ecx)
  596e4a:      	clc
  596e4b:      	popl	%eax
  596e4c:      	addb	%dh, 0x3b0058fd(%ebx)
  596e52:      	clc
  596e53:      	popl	%eax
  596e54:      	addb	%al, -0x8(%ebp)
  596e57:      	popl	%eax
  596e58:      	addb	%cl, -0x8(%edi)
  596e5b:      	popl	%eax
  596e5c:      	addb	%bl, -0x8(%ecx)
  596e5f:      	popl	%eax
  596e60:      	addb	%ah, -0x8(%ebx)
  596e63:      	popl	%eax
  596e64:      	addb	%ch, -0x8(%ebp)
  596e67:      	popl	%eax
  596e68:      	addb	%dh, -0x8(%edi)
  596e6b:      	popl	%eax
  596e6c:      	addb	%al, -0x74ffa708(%ecx)
  596e72:      	clc
  596e73:      	popl	%eax
  596e74:      	addb	%dl, -0x60ffa708(%ebp)
  596e7a:      	clc
  596e7b:      	popl	%eax
  596e7c:      	addb	%ch, -0x4cffa708(%ecx)
  596e82:      	clc
  596e83:      	popl	%eax
  596e84:      	addb	%bh, -0x38ffa708(%ebp)
  596e8a:      	clc
  596e8b:      	popl	%eax
  596e8c:      	addb	%dl, %cl
  596e8e:      	clc
  596e8f:      	popl	%eax
  596e90:      	addb	%bl, %bl
  596e92:      	clc
  596e93:      	popl	%eax
  596e94:      	addb	%ah, %ch
  596e96:      	clc
  596e97:      	popl	%eax
  596e98:      	addb	%ch, %bh
  596e9a:      	clc
  596e9b:      	popl	%eax
  596e9c:      	addb	%bh, %cl
  596e9e:      	clc
  596e9f:      	popl	%eax
  596ea0:      	addb	%al, (%ebx)
  596ea2:      	stc
  596ea3:      	popl	%eax
  596ea4:      	addb	%cl, 0x170058f9
  596eaa:      	stc
  596eab:      	popl	%eax
  596eac:      	addb	%ah, (%ecx)
  596eae:      	stc
  596eaf:      	popl	%eax
  596eb0:      	addb	%ch, (%ebx)
  596eb2:      	stc
  596eb3:      	popl	%eax
  596eb4:      	addb	%dh, 0x3f0058f9
  596eba:      	stc
  596ebb:      	popl	%eax
  596ebc:      	addb	%cl, -0x7(%ecx)
  596ebf:      	popl	%eax
  596ec0:      	addb	%dl, -0x7(%ebx)
  596ec3:      	popl	%eax
  596ec4:      	addb	%bl, -0x7(%ebp)
  596ec7:      	popl	%eax
  596ec8:      	addb	%ah, -0x7(%edi)
  596ecb:      	popl	%eax
  596ecc:      	addb	%dh, -0x7(%ecx)
  596ecf:      	popl	%eax
  596ed0:      	addb	%bh, -0x7(%ebx)
  596ed3:      	popl	%eax
  596ed4:      	addb	%al, -0x70ffa707(%ebp)
  596eda:      	stc
  596edb:      	popl	%eax
  596edc:      	addb	%bl, -0x5cffa707(%ecx)
  596ee2:      	stc
  596ee3:      	popl	%eax
  596ee4:      	addb	%ch, -0x48ffa707(%ebp)
  596eea:      	stc
  596eeb:      	popl	%eax
  596eec:      	addb	%al, %cl
  596eee:      	stc
  596eef:      	popl	%eax
  596ef0:      	addb	%cl, %bl
  596ef2:      	stc
  596ef3:      	popl	%eax
  596ef4:      	addb	%dl, %ch
  596ef6:      	stc
  596ef7:      	popl	%eax
  596ef8:      	addb	%bl, %bh
  596efa:      	stc
  596efb:      	popl	%eax
  596efc:      	addb	%ch, %cl
  596efe:      	stc
  596eff:      	popl	%eax
  596f00:      	addb	%dh, %bl
  596f02:      	stc
  596f03:      	popl	%eax
  596f04:      	addb	%bh, %ch
  596f06:      	stc
  596f07:      	popl	%eax
  596f08:      	addb	%al, (%edi)
  596f0a:      	cli
  596f0b:      	popl	%eax
  596f0c:      	addb	%dl, (%ecx)
  596f0e:      	cli
  596f0f:      	popl	%eax
  596f10:      	addb	%bl, (%ebx)
  596f12:      	cli
  596f13:      	popl	%eax
  596f14:      	addb	%ah, 0x2f0058fa
  596f1a:      	cli
  596f1b:      	popl	%eax
  596f1c:      	addb	%bh, (%ecx)
  596f1e:      	cli
  596f1f:      	popl	%eax
  596f20:      	addb	%al, -0x6(%ebx)
  596f23:      	popl	%eax
  596f24:      	addb	%cl, -0x6(%ebp)
  596f27:      	popl	%eax
  596f28:      	addb	%dl, -0x6(%edi)
  596f2b:      	popl	%eax
  596f2c:      	addb	%ah, -0x6(%ecx)
  596f2f:      	popl	%eax
  596f30:      	addb	%ch, -0x6(%ebx)
  596f33:      	popl	%eax
  596f34:      	addb	%dh, -0x6(%ebp)
  596f37:      	popl	%eax
  596f38:      	addb	%bh, -0x6(%edi)
  596f3b:      	popl	%eax
  596f3c:      	addb	%cl, -0x6cffa706(%ecx)
  596f42:      	cli
  596f43:      	popl	%eax
  596f44:      	addb	%bl, -0x58ffa706(%ebp)
  596f4a:      	cli
  596f4b:      	popl	%eax
  596f4c:      	addb	%dh, -0x44ffa706(%ecx)
  596f52:      	cli
  596f53:      	popl	%eax
  596f54:      	addb	%al, %ch
  596f56:      	cli
  596f57:      	popl	%eax
  596f58:      	addb	%cl, %bh
  596f5a:      	cli
  596f5b:      	popl	%eax
  596f5c:      	addb	%bl, %cl
  596f5e:      	cli
  596f5f:      	popl	%eax
  596f60:      	addb	%ah, %bl
  596f62:      	cli
  596f63:      	popl	%eax
  596f64:      	addb	%ch, %ch
  596f66:      	cli
  596f67:      	popl	%eax
  596f68:      	addb	%dh, %bh
  596f6a:      	cli
  596f6b:      	popl	%eax
  596f6c:      	addb	%al, (%ecx)
  596f6e:      	sti
  596f6f:      	popl	%eax
  596f70:      	addb	%cl, (%ebx)
  596f72:      	sti
  596f73:      	popl	%eax
  596f74:      	addb	%dl, 0x1f0058fb
  596f7a:      	sti
  596f7b:      	popl	%eax
  596f7c:      	addb	%ch, (%ecx)
  596f7e:      	sti
  596f7f:      	popl	%eax
  596f80:      	addb	%dh, (%ebx)
  596f82:      	sti
  596f83:      	popl	%eax
  596f84:      	addb	%bh, 0x470058fb
  596f8a:      	sti
  596f8b:      	popl	%eax
  596f8c:      	addb	%dl, -0x5(%ecx)
  596f8f:      	popl	%eax
  596f90:      	addb	%bl, -0x5(%ebx)
  596f93:      	popl	%eax
  596f94:      	addb	%ah, -0x5(%ebp)
  596f97:      	popl	%eax
  596f98:      	addb	%ch, -0x5(%edi)
  596f9b:      	popl	%eax
  596f9c:      	addb	%bh, -0x5(%ecx)
  596f9f:      	popl	%eax
  596fa0:      	addb	%al, -0x72ffa705(%ebx)
  596fa6:      	sti
  596fa7:      	popl	%eax
  596fa8:      	addb	%dl, -0x5effa705(%edi)
  596fae:      	sti
  596faf:      	popl	%eax
  596fb0:      	addb	%ch, -0x4affa705(%ebx)
  596fb6:      	sti
  596fb7:      	popl	%eax
  596fb8:      	addb	%bh, -0x36ffa705(%edi)
  596fbe:      	sti
  596fbf:      	popl	%eax
  596fc0:      	addb	%dl, %bl
  596fc2:      	sti
  596fc3:      	popl	%eax
  596fc4:      	addb	%bl, %ch
  596fc6:      	sti
  596fc7:      	popl	%eax
  596fc8:      	addb	%ah, %bh
  596fca:      	sti
  596fcb:      	popl	%eax
  596fcc:      	addb	%dh, %cl
  596fce:      	sti
  596fcf:      	popl	%eax
  596fd0:      	addb	%bh, %bl
  596fd2:      	sti
  596fd3:      	popl	%eax
  596fd4:      	addb	%al, 0xf0058fc
  596fda:      	cld
  596fdb:      	popl	%eax
  596fdc:      	addb	%bl, (%ecx)
  596fde:      	cld
  596fdf:      	popl	%eax
  596fe0:      	addb	%ah, (%ebx)
  596fe2:      	cld
  596fe3:      	popl	%eax
  596fe4:      	addb	%ch, 0x370058fc
  596fea:      	cld
  596feb:      	popl	%eax
  596fec:      	addb	%al, -0x4(%ecx)
  596fef:      	popl	%eax
  596ff0:      	addb	%cl, -0x4(%ebx)
  596ff3:      	popl	%eax
  596ff4:      	addb	%dl, -0x4(%ebp)
  596ff7:      	popl	%eax
  596ff8:      	addb	%bl, -0x4(%edi)
  596ffb:      	popl	%eax
  596ffc:      	addb	%ch, -0x4(%ecx)
  596fff:      	popl	%eax
  597000:      	addb	%dh, -0x4(%ebx)
  597003:      	popl	%eax
  597004:      	addb	%bh, -0x4(%ebp)
  597007:      	popl	%eax
  597008:      	addb	%al, -0x6effa704(%edi)
  59700e:      	cld
  59700f:      	popl	%eax
  597010:      	addb	%bl, -0x5affa704(%ebx)
  597016:      	cld
  597017:      	popl	%eax
  597018:      	addb	%ch, -0x46ffa704(%edi)
  59701e:      	cld
  59701f:      	popl	%eax
  597020:      	addb	%al, %bl
  597022:      	cld
  597023:      	popl	%eax
  597024:      	addb	%cl, %ch
  597026:      	cld
  597027:      	popl	%eax
  597028:      	addb	%dl, %bh
  59702a:      	cld
  59702b:      	popl	%eax
  59702c:      	addb	%ah, %cl
  59702e:      	cld
  59702f:      	popl	%eax
  597030:      	addb	%ch, %bl
  597032:      	cld
  597033:      	popl	%eax
  597034:      	addb	%dh, %ch
  597036:      	cld
  597037:      	popl	%eax
  597038:      	addb	%bh, %bh
  59703a:      	cld
  59703b:      	popl	%eax
  59703c:      	addb	%cl, (%ecx)
  59703e:      	std
  59703f:      	popl	%eax
  597040:      	addb	%dl, (%ebx)
  597042:      	std
  597043:      	popl	%eax
  597044:      	addb	%bl, 0x270058fd
  59704a:      	std
  59704b:      	popl	%eax
  59704c:      	addb	%dh, (%ecx)
  59704e:      	std
  59704f:      	popl	%eax
  597050:      	addb	%bh, (%ebx)
  597052:      	std
  597053:      	popl	%eax
  597054:      	addb	%al, -0x3(%ebp)
  597057:      	popl	%eax
  597058:      	addb	%cl, -0x3(%edi)
  59705b:      	popl	%eax
  59705c:      	addb	%bl, -0x3(%ecx)
  59705f:      	popl	%eax
  597060:      	addb	%ah, -0x3(%ebx)
  597063:      	popl	%eax
  597064:      	addb	%ch, -0x3(%ebp)
  597067:      	popl	%eax
  597068:      	addb	%dh, -0x3(%edi)
  59706b:      	popl	%eax
  59706c:      	addb	%al, -0x74ffa703(%ecx)
  597072:      	std
  597073:      	popl	%eax
  597074:      	addb	%dl, -0x42ffa703(%ebp)
  59707a:      	std
  59707b:      	popl	%eax
  59707c:      	addb	%al, %bh
  59707e:      	std
  59707f:      	popl	%eax
  597080:      	addb	%dl, %cl
  597082:      	std
  597083:      	popl	%eax
  597084:      	addb	%bl, %bl
  597086:      	std
  597087:      	popl	%eax
  597088:      	addb	%ah, %ch
  59708a:      	std
  59708b:      	popl	%eax
  59708c:      	addb	%ch, %bh
  59708e:      	std
  59708f:      	popl	%eax
  597090:      	addb	%bh, %cl
  597092:      	std
  597093:      	popl	%eax
  597094:      	addb	%al, (%ebx)
  597096:      	<unknown>
  597099:      	orl	$0x170058fe, %eax       # imm = 0x170058FE
  59709e:      	<unknown>
  5970a1:      	andl	%edi, %esi
  5970a3:      	popl	%eax
  5970a4:      	addb	%ch, (%ebx)
  5970a6:      	<unknown>
  5970a9:      	xorl	$0x3f0058fe, %eax       # imm = 0x3F0058FE
  5970ae:      	<unknown>
  5970b1:      	decl	%ecx
  5970b2:      	<unknown>
  5970b5:      	pushl	%ebx
  5970b6:      	<unknown>
  5970b9:      	popl	%ebp
  5970ba:      	<unknown>
  5970bd:      	<unknown>
  5970c1:      	jno	0x5970c1 <.text+0x1960c1>
  5970c3:      	popl	%eax
  5970c4:      	addb	%bh, -0x2(%ebx)
  5970c7:      	popl	%eax
  5970c8:      	addb	%al, -0x70ffa702(%ebp)
  5970ce:      	<unknown>
  5970d1:      	cltd
  5970d2:      	<unknown>
  5970d5:      	movl	%eax, 0xad0058fe
  5970da:      	<unknown>
  5970dd:      	movb	$-0x2, %bh
  5970df:      	popl	%eax
  5970e0:      	addb	%al, %cl
  5970e2:      	<unknown>
  5970e5:      	lretl
  5970e6:      	<unknown>
  5970e9:      	aad	$-0x2
  5970eb:      	popl	%eax
  5970ec:      	addb	%bl, %bh
  5970ee:      	<unknown>
  5970f1:      	jmp	0xf359c9f4
  5970f6:      	<unknown>
  5970f9:      	std
  5970fa:      	<unknown>
  5970fd:      	popl	%es
  5970fe:      	lcalll	*(%eax)
  597101:      	adcl	%edi, %edi
  597103:      	popl	%eax
  597104:      	addb	%bl, (%ebx)
  597106:      	lcalll	*(%eax)
  597109:      	andl	$0x2f0058ff, %eax       # imm = 0x2F0058FF
  59710e:      	lcalll	*(%eax)
  597111:      	cmpl	%edi, %edi
  597113:      	popl	%eax
  597114:      	addb	%al, -0x1(%ebx)
  597117:      	popl	%eax
  597118:      	addb	%cl, -0x1(%ebp)
  59711b:      	popl	%eax
  59711c:      	addb	%dl, -0x1(%edi)
  59711f:      	popl	%eax
  597120:      	addb	%ah, -0x1(%ecx)
  597123:      	popl	%eax
  597124:      	addb	%ch, -0x1(%ebx)
  597127:      	popl	%eax
  597128:      	addb	%dh, -0x1(%ebp)
  59712b:      	popl	%eax
  59712c:      	addb	%bh, -0x1(%edi)
  59712f:      	popl	%eax
  597130:      	addb	%cl, -0x6cffa701(%ecx)
  597136:      	lcalll	*(%eax)
  597139:      	popfl
  59713a:      	lcalll	*(%eax)
  59713d:      	cmpsl	%es:(%edi), (%esi)
  59713e:      	lcalll	*(%eax)
  597141:      	movb	$-0x1, %cl
  597143:      	popl	%eax
  597144:      	addb	%bh, -0x3affa701(%ebx)
  59714a:      	lcalll	*(%eax)
  59714d:      	iretl
  59714e:      	lcalll	*(%eax)
  597151:      	fcos
  597153:      	popl	%eax
  597154:      	addb	%ah, %bl
  597156:      	lcalll	*(%eax)
  597159:      	inl	%dx, %eax
  59715a:      	lcalll	*(%eax)
  59715d:      	idivl	%edi
  59715f:      	popl	%eax
  597160:      	addb	%dh, (%ebx)
  597162:      	addb	%bl, (%ecx)
  597165:      	cmpl	$0x47005900, %eax       # imm = 0x47005900
  59716a:      	addb	%bl, (%ecx)
  59716d:      	pushl	%ecx
  59716e:      	addb	%bl, (%ecx)
  597171:      	popl	%ebx
  597172:      	addb	%bl, (%ecx)
  597175:      	addb	%bl, %gs:(%ecx)
  597179:      	outsl	(%esi), %dx
  59717a:      	addb	%bl, (%ecx)
  59717d:      	jns	0x59717f <.text+0x19617f>
  59717f:      	popl	%ecx
  597180:      	addb	%al, -0x72ffa700(%ebx)
  597186:      	addb	%bl, (%ecx)
  597189:      	xchgl	%edi, %eax
  59718a:      	addb	%bl, (%ecx)
  59718d:      	movl	0xab005900, %eax
  597192:      	addb	%bl, (%ecx)
  597195:      	movb	$0x0, %ch
  597197:      	popl	%ecx
  597198:      	addb	%bh, -0x36ffa700(%edi)
  59719e:      	addb	%bl, (%ecx)
  5971a1:      	roll	%cl, (%eax)
  5971a3:      	popl	%ecx
  5971a4:      	addb	%bl, %ch
  5971a6:      	addb	%bl, (%ecx)
  5971a9:      	outl	%eax, $0x0
  5971ab:      	popl	%ecx
  5971ac:      	addb	%dh, %cl
  5971ae:      	addb	%bl, (%ecx)
  5971b1:      	sti
  5971b2:      	addb	%bl, (%ecx)
  5971b5:      	addl	$0xf005901, %eax        # imm = 0xF005901
  5971ba:      	addl	%ebx, (%ecx)
  5971bd:      	sbbl	%eax, (%ecx)
  5971bf:      	popl	%ecx
  5971c0:      	addb	%ah, (%ebx)
  5971c2:      	addl	%ebx, (%ecx)
  5971c5:      	subl	$0x37005901, %eax       # imm = 0x37005901
  5971ca:      	addl	%ebx, (%ecx)
  5971cd:      	incl	%ecx
  5971ce:      	addl	%ebx, (%ecx)
  5971d1:      	decl	%ebx
  5971d2:      	addl	%ebx, (%ecx)
  5971d5:      	pushl	%ebp
  5971d6:      	addl	%ebx, (%ecx)
  5971d9:      	popl	%edi
  5971da:      	addl	%ebx, (%ecx)
  5971dd:      	imull	$0x1730059, (%ecx), %eax # imm = 0x1730059
  5971e3:      	popl	%ecx
  5971e4:      	addb	%bh, 0x1(%ebp)
  5971e7:      	popl	%ecx
  5971e8:      	addb	%al, -0x6effa6ff(%edi)
  5971ee:      	addl	%ebx, (%ecx)
  5971f1:      	wait
  5971f2:      	addl	%ebx, (%ecx)
  5971f5:      	movsl	(%esi), %es:(%edi)
  5971f6:      	addl	%ebx, (%ecx)
  5971f9:      	scasl	%es:(%edi), %eax
  5971fa:      	addl	%ebx, (%ecx)
  5971fd:      	movl	$0xc3005901, %ecx       # imm = 0xC3005901
  597202:      	addl	%ebx, (%ecx)
  597205:      	int	$0x1
  597207:      	popl	%ecx
  597208:      	addb	%dl, %bh
  59720a:      	addl	%ebx, (%ecx)
  59720d:      	loope	0x597210 <.text+0x196210>
  59720f:      	popl	%ecx
  597210:      	addb	%ch, %bl
  597212:      	addl	%ebx, (%ecx)
  597215:      	cmc
  597216:      	addl	%ebx, (%ecx)
  597219:      	incl	(%ecx)
  59721b:      	popl	%ecx
  59721c:      	addb	%cl, (%ecx)
  59721e:      	addb	(%ecx), %bl
  597221:      	adcl	(%edx), %eax
  597223:      	popl	%ecx
  597224:      	addb	%bl, 0x27005902
  59722a:      	addb	(%ecx), %bl
  59722d:      	xorl	%eax, (%edx)
  59722f:      	popl	%ecx
  597230:      	addb	%bh, (%ebx)
  597232:      	addb	(%ecx), %bl
  597235:      	incl	%ebp
  597236:      	addb	(%ecx), %bl
  597239:      	decl	%edi
  59723a:      	addb	(%ecx), %bl
  59723d:      	popl	%ecx
  59723e:      	addb	(%ecx), %bl
  597241:      	arpl	%ax, (%edx)
  597243:      	popl	%ecx
  597244:      	addb	%ch, 0x2(%ebp)
  597247:      	popl	%ecx
  597248:      	addb	%dh, 0x2(%edi)
  59724b:      	popl	%ecx
  59724c:      	addb	%al, -0x74ffa6fe(%ecx)
  597252:      	addb	(%ecx), %bl
  597255:      	xchgl	%ebp, %eax
  597256:      	addb	(%ecx), %bl
  597259:      	lahf
  59725a:      	addb	(%ecx), %bl
  59725d:      	testl	$0xb3005902, %eax       # imm = 0xB3005902
  597262:      	addb	(%ecx), %bl
  597265:      	outl	%eax, %dx
  597266:      	addb	(%ecx), %bl
  597269:      	stc
  59726a:      	addb	(%ecx), %bl
  59726d:      	addl	(%ebx), %eax
  59726f:      	popl	%ecx
  597270:      	addb	%cl, 0x17005903
  597276:      	addl	(%ecx), %ebx
  597279:      	andl	%eax, (%ebx)
  59727b:      	popl	%ecx
  59727c:      	addb	%ch, (%ebx)
  59727e:      	addl	(%ecx), %ebx
  597281:      	xorl	$0x3f005903, %eax       # imm = 0x3F005903
  597286:      	addl	(%ecx), %ebx
  597289:      	decl	%ecx
  59728a:      	addl	(%ecx), %ebx
  59728d:      	pushl	%ss
  59728e:      	sbbb	(%ecx), %bl
  597291:      	pushl	%ss
  597292:      	sbbb	(%ecx), %bl
  597295:      	pushl	%ss
  597296:      	sbbb	(%ecx), %bl
  597299:      	pushl	%ss
  59729a:      	sbbb	(%ecx), %bl
  59729d:      	pushl	%ss
  59729e:      	sbbb	(%ecx), %bl
  5972a1:      	pushl	%ebx
  5972a2:      	addl	(%ecx), %ebx
  5972a5:      	popl	%ebp
  5972a6:      	addl	(%ecx), %ebx
  5972a9:      	addl	(%bx,%di), %ebx
  5972ad:      	movl	$0xc9005903, %edi       # imm = 0xC9005903
  5972b2:      	addl	(%ecx), %ebx
  5972b5:      	roll	%cl, (%ebx)
  5972b7:      	popl	%ecx
  5972b8:      	addb	%bl, %ch
  5972ba:      	addl	(%ecx), %ebx
  5972bd:      	outl	%eax, $0x3
  5972bf:      	popl	%ecx
  5972c0:      	addb	%dh, %cl
  5972c2:      	addl	(%ecx), %ebx
  5972c5:      	sti
  5972c6:      	addl	(%ecx), %ebx
  5972c9:      	addl	$0xf005904, %eax        # imm = 0xF005904
  5972ce:      	addb	$0x59, %al
  5972d0:      	addb	%bl, (%ecx)
  5972d2:      	addb	$0x59, %al
  5972d4:      	addb	%ah, (%ebx)
  5972d6:      	addb	$0x59, %al
  5972d8:      	addb	%ch, 0x37005904
  5972de:      	addb	$0x59, %al
  5972e0:      	addb	%al, 0x4(%ecx)
  5972e3:      	popl	%ecx
  5972e4:      	addb	%cl, 0x4(%ebx)
  5972e7:      	popl	%ecx
  5972e8:      	addb	%dl, 0x4(%ebp)
  5972eb:      	popl	%ecx
  5972ec:      	addb	%bl, 0x4(%edi)
  5972ef:      	popl	%ecx
  5972f0:      	addb	%ch, 0x4(%ecx)
  5972f3:      	popl	%ecx
  5972f4:      	addb	%dh, 0x4(%ebx)
  5972f7:      	popl	%ecx
  5972f8:      	addb	%bh, 0x4(%ebp)
  5972fb:      	popl	%ecx
  5972fc:      	addb	%al, -0x6effa6fc(%edi)
  597302:      	addb	$0x59, %al
  597304:      	addb	%bl, -0x5affa6fc(%ebx)
  59730a:      	addb	$0x59, %al
  59730c:      	addb	%ch, -0x46ffa6fc(%edi)
  597312:      	addb	$0x59, %al
  597314:      	addb	%al, %bl
  597316:      	addb	$0x59, %al
  597318:      	addb	%cl, %ch
  59731a:      	addb	$0x59, %al
  59731c:      	addb	%dl, %bh
  59731e:      	addb	$0x59, %al
  597320:      	addb	%ah, %cl
  597322:      	addb	$0x59, %al
  597324:      	addb	%ch, %bl
  597326:      	addb	$0x59, %al
  597328:      	addb	%dh, %ch
  59732a:      	addb	$0x59, %al
  59732c:      	addb	%bh, %bh
  59732e:      	addb	$0x59, %al
  597330:      	addb	%cl, (%ecx)
  597332:      	addl	$0x8150059, %eax        # imm = 0x8150059
  597337:      	popl	%ecx
  597338:      	addb	%bl, (%edi)
  59733a:      	orb	%bl, (%ecx)
  59733d:      	subl	%ecx, (%eax)
  59733f:      	popl	%ecx
  597340:      	addb	%dl, (%ebx)
  597342:      	addl	$0x51d0059, %eax        # imm = 0x51D0059
  597347:      	popl	%ecx
  597348:      	addb	%ah, (%edi)
  59734a:      	addl	$0x5310059, %eax        # imm = 0x5310059
  59734f:      	popl	%ecx
  597350:      	addb	%bh, (%ebx)
  597352:      	addl	$0x5450059, %eax        # imm = 0x5450059
  597357:      	popl	%ecx
  597358:      	addb	%cl, 0x5(%edi)
  59735b:      	popl	%ecx
  59735c:      	addb	%bl, 0x5(%ecx)
  59735f:      	popl	%ecx
  597360:      	addb	%ah, 0x5(%ebx)
  597363:      	popl	%ecx
  597364:      	addb	%ch, 0x5(%ebp)
  597367:      	popl	%ecx
  597368:      	addb	%dh, 0x5(%edi)
  59736b:      	popl	%ecx
  59736c:      	addb	%al, -0x74ffa6fb(%ecx)
  597372:      	addl	$0x5950059, %eax        # imm = 0x5950059
  597377:      	popl	%ecx
  597378:      	addb	%bl, -0x56ffa6fb(%edi)
  59737e:      	addl	$0x5b30059, %eax        # imm = 0x5B30059
  597383:      	popl	%ecx
  597384:      	addb	%bh, -0x38ffa6fb(%ebp)
  59738a:      	addl	$0x5d10059, %eax        # imm = 0x5D10059
  59738f:      	popl	%ecx
  597390:      	addb	%bl, %bl
  597392:      	addl	$0x5e50059, %eax        # imm = 0x5E50059
  597397:      	popl	%ecx
  597398:      	addb	%ch, %bh
  59739a:      	addl	$0x5f90059, %eax        # imm = 0x5F90059
  59739f:      	popl	%ecx
  5973a0:      	addb	%al, (%ebx)
  5973a2:      	pushl	%es
  5973a3:      	popl	%ecx
  5973a4:      	addb	%cl, 0x17005906
  5973aa:      	pushl	%es
  5973ab:      	popl	%ecx
  5973ac:      	addb	%ah, (%ecx)
  5973ae:      	pushl	%es
  5973af:      	popl	%ecx
  5973b0:      	addb	%ch, (%ebx)
  5973b2:      	pushl	%es
  5973b3:      	popl	%ecx
  5973b4:      	addb	%dh, 0x3f005906
  5973ba:      	pushl	%es
  5973bb:      	popl	%ecx
  5973bc:      	addb	%dh, %cl
  5973be:      	xchgl	%ecx, %eax
  5973bf:      	popl	%eax
  5973c0:      	addb	%cl, 0x6(%ecx)
  5973c3:      	popl	%ecx
  5973c4:      	addb	%dl, 0x6(%ebx)
  5973c7:      	popl	%ecx
  5973c8:      	addb	%bl, 0x6(%ebp)
  5973cb:      	popl	%ecx
  5973cc:      	addb	%dh, (%ebx)
  5973ce:      	orb	%bl, (%ecx)
  5973d1:      	cmpl	$0x47005908, %eax       # imm = 0x47005908
  5973d6:      	orb	%bl, (%ecx)
  5973d9:      	pushl	%ecx
  5973da:      	orb	%bl, (%ecx)
  5973dd:      	decl	%eax
  5973de:      	xchgl	%edx, %eax
  5973df:      	popl	%eax
  5973e0:      	addb	%ah, 0x6(%edi)
  5973e3:      	popl	%ecx
  5973e4:      	addb	%dh, 0x6(%ecx)
  5973e7:      	popl	%ecx
  5973e8:      	addb	%bh, 0x6(%ebx)
  5973eb:      	popl	%ecx
  5973ec:      	addb	%al, -0x70ffa6fa(%ebp)
  5973f2:      	pushl	%es
  5973f3:      	popl	%ecx
  5973f4:      	addb	%bl, -0x5cffa6fa(%ecx)
  5973fa:      	pushl	%es
  5973fb:      	popl	%ecx
  5973fc:      	addb	%ch, -0x48ffa6fa(%ebp)
  597402:      	pushl	%es
  597403:      	popl	%ecx
  597404:      	addb	%al, %cl
  597406:      	pushl	%es
  597407:      	popl	%ecx
  597408:      	addb	%cl, %bl
  59740a:      	pushl	%es
  59740b:      	popl	%ecx
  59740c:      	addb	%dl, %ch
  59740e:      	pushl	%es
  59740f:      	popl	%ecx
  597410:      	addb	%bl, %bh
  597412:      	pushl	%es
  597413:      	popl	%ecx
  597414:      	addb	%ch, %cl
  597416:      	pushl	%es
  597417:      	popl	%ecx
  597418:      	addb	%dh, %bl
  59741a:      	pushl	%es
  59741b:      	popl	%ecx
  59741c:      	addb	%bh, %ch
  59741e:      	pushl	%es
  59741f:      	popl	%ecx
  597420:      	addb	%al, (%edi)
  597422:      	popl	%es
  597423:      	popl	%ecx
  597424:      	addb	%dl, (%ecx)
  597426:      	popl	%es
  597427:      	popl	%ecx
  597428:      	addb	%bl, (%ebx)
  59742a:      	popl	%es
  59742b:      	popl	%ecx
  59742c:      	addb	%ah, 0x2f005907
  597432:      	popl	%es
  597433:      	popl	%ecx
  597434:      	addb	%bh, (%ecx)
  597436:      	popl	%es
  597437:      	popl	%ecx
  597438:      	addb	%al, 0x7(%ebx)
  59743b:      	popl	%ecx
  59743c:      	addb	%cl, 0x7(%ebp)
  59743f:      	popl	%ecx
  597440:      	addb	%dl, 0x7(%edi)
  597443:      	popl	%ecx
  597444:      	addb	%ah, 0x7(%ecx)
  597447:      	popl	%ecx
  597448:      	addb	%ch, 0x7(%ebx)
  59744b:      	popl	%ecx
  59744c:      	addb	%dh, 0x7(%ebp)
  59744f:      	popl	%ecx
  597450:      	addb	%bh, 0x7(%edi)
  597453:      	popl	%ecx
  597454:      	addb	%cl, -0x6cffa6f9(%ecx)
  59745a:      	popl	%es
  59745b:      	popl	%ecx
  59745c:      	addb	%bl, -0x58ffa6f9(%ebp)
  597462:      	popl	%es
  597463:      	popl	%ecx
  597464:      	addb	%dh, -0x44ffa6f9(%ecx)
  59746a:      	popl	%es
  59746b:      	popl	%ecx
  59746c:      	addb	%al, %ch
  59746e:      	popl	%es
  59746f:      	popl	%ecx
  597470:      	addb	%cl, %bh
  597472:      	popl	%es
  597473:      	popl	%ecx
  597474:      	addb	%bl, %cl
  597476:      	popl	%es
  597477:      	popl	%ecx
  597478:      	addb	%ah, %bl
  59747a:      	popl	%es
  59747b:      	popl	%ecx
  59747c:      	addb	%ch, %ch
  59747e:      	popl	%es
  59747f:      	popl	%ecx
  597480:      	addb	%dh, %bh
  597482:      	popl	%es
  597483:      	popl	%ecx
  597484:      	addb	%al, (%ecx)
  597486:      	orb	%bl, (%ecx)
  597489:      	orl	(%eax), %ecx
  59748b:      	popl	%ecx
  59748c:      	addb	%dl, (%esi)
  59748e:      	sbbb	(%ecx), %bl
  597491:      	addb	%al, (%ecx)
  597493:      	addb	(%ebx), %al
  597495:      	addb	$0x78, %al
  597497:      	js	0x597511 <.text+0x196511>
  597499:      	js	0x597513 <.text+0x196513>
  59749b:      	js	0x597515 <.text+0x196515>
  59749d:      	js	0x597517 <.text+0x196517>
  59749f:      	js	0x597519 <.text+0x196519>
  5974a1:      	js	0x59751b <.text+0x19651b>
  5974a3:      	js	0x59751d <.text+0x19651d>
  5974a5:      	js	0x59751f <.text+0x19651f>
  5974a7:      	js	0x597521 <.text+0x196521>
  5974a9:      	js	0x597523 <.text+0x196523>
  5974ab:      	js	0x597525 <.text+0x196525>
  5974ad:      	js	0x597527 <.text+0x196527>
  5974af:      	js	0x597529 <.text+0x196529>
  5974b1:      	js	0x59752b <.text+0x19652b>
  5974b3:      	js	0x59752d <.text+0x19652d>
  5974b5:      	js	0x59752f <.text+0x19652f>
  5974b7:      	js	0x597531 <.text+0x196531>
  5974b9:      	js	0x597533 <.text+0x196533>
  5974bb:      	js	0x597535 <.text+0x196535>
  5974bd:      	js	0x597537 <.text+0x196537>
  5974bf:      	js	0x597539 <.text+0x196539>
  5974c1:      	js	0x5974c8 <.text+0x1964c8>
  5974c3:      	pushl	%es
  5974c4:      	popl	%es
  5974c5:      	orb	%cl, (%ecx)
  5974c7:      	orb	(%ebx), %cl
  5974c9:      	orb	$0xd, %al
  5974cb:      	pushl	%cs
  5974cc:      	js	0x597546 <.text+0x196546>
  5974ce:      	js	0x597548 <.text+0x196548>
  5974d0:      	js	0x59754a <.text+0x19654a>
  5974d2:      	js	0x59754c <.text+0x19654c>
  5974d4:      	js	0x59754e <.text+0x19654e>
  5974d6:      	js	0x597550 <.text+0x196550>
  5974d8:      	js	0x597552 <.text+0x196552>
  5974da:      	js	0x597554 <.text+0x196554>
  5974dc:      	js	0x597556 <.text+0x196556>
  5974de:      	js	0x597558 <.text+0x196558>
  5974e0:      	js	0x59755a <.text+0x19655a>
  5974e2:      	js	0x59755c <.text+0x19655c>
  5974e4:      	js	0x59755e <.text+0x19655e>
  5974e6:      	js	0x597560 <.text+0x196560>
  5974e8:      	js	0x597562 <.text+0x196562>
  5974ea:      	js	0x597564 <.text+0x196564>
  5974ec:      	js	0x597566 <.text+0x196566>
  5974ee:      	js	0x597568 <.text+0x196568>
  5974f0:      	js	0x59756a <.text+0x19656a>
  5974f2:      	js	0x59756c <.text+0x19656c>
  5974f4:      	movups	(%ecx), %xmm2
  5974f7:      	adcb	(%ebx), %dl
  5974f9:      	adcb	$0x15, %al
  5974fb:      	pushl	%ss
  5974fc:      	popl	%ss
  5974fd:      	sbbb	%bl, (%ecx)
  5974ff:      	sbbb	(%ebx), %bl
  597501:      	sbbb	$0x1d, %al
  597503:      	pushl	%ds
  597504:      	popl	%ds
  597505:      	andb	%ah, (%ecx)
  597507:      	andb	(%ebx), %ah
  597509:      	andb	$0x78, %al
  59750b:      	js	0x597585 <.text+0x196585>
  59750d:      	js	0x597587 <.text+0x196587>
  59750f:      	js	0x597589 <.text+0x196589>
  597511:      	js	0x59758b <.text+0x19658b>
  597513:      	js	0x59758d <.text+0x19658d>
  597515:      	js	0x59758f <.text+0x19658f>
  597517:      	js	0x597591 <.text+0x196591>
  597519:      	js	0x597593 <.text+0x196593>
  59751b:      	js	0x597595 <.text+0x196595>
  59751d:      	js	0x597597 <.text+0x196597>
  59751f:      	js	0x597599 <.text+0x196599>
  597521:      	js	0x59759b <.text+0x19659b>
  597523:      	js	0x59759d <.text+0x19659d>
  597525:      	js	0x59754c <.text+0x19654c>
  597527:      	daa
  597529:      	subb	%ch, (%ecx)
  59752b:      	subb	0x78(%eax), %bh
  59752e:      	js	0x5975a8 <.text+0x1965a8>
  597530:      	js	0x5975aa <.text+0x1965aa>
  597532:      	js	0x5975ac <.text+0x1965ac>
  597534:      	js	0x5975ae <.text+0x1965ae>
  597536:      	js	0x5975b0 <.text+0x1965b0>
  597538:      	js	0x5975b2 <.text+0x1965b2>
  59753a:      	js	0x5975b4 <.text+0x1965b4>
  59753c:      	js	0x5975b6 <.text+0x1965b6>
  59753e:      	js	0x5975b8 <.text+0x1965b8>
  597540:      	js	0x5975ba <.text+0x1965ba>
  597542:      	js	0x5975bc <.text+0x1965bc>
  597544:      	js	0x5975be <.text+0x1965be>
  597546:      	js	0x5975c0 <.text+0x1965c0>
  597548:      	js	0x5975c2 <.text+0x1965c2>
  59754a:      	js	0x5975c4 <.text+0x1965c4>
  59754c:      	js	0x5975c6 <.text+0x1965c6>
  59754e:      	js	0x5975c8 <.text+0x1965c8>
  597550:      	js	0x5975ca <.text+0x1965ca>
  597552:      	js	0x5975cc <.text+0x1965cc>
  597554:      	js	0x5975ce <.text+0x1965ce>
  597556:      	js	0x5975d0 <.text+0x1965d0>
  597558:      	subl	0x31302f2e(,%ebp), %ebp
  59755f:      	xorb	(%ebx), %dh
  597561:      	xorb	$0x35, %al
  597563:      	aaa
  597565:      	cmpb	%bh, (%ecx)
  597567:      	cmpb	(%ebx), %bh
  597569:      	cmpb	$0x3d, %al
  59756b:      	js	0x5975e6 <.text+0x1965e6>
  59756e:      	js	0x5975e8 <.text+0x1965e8>
  597570:      	js	0x5975ea <.text+0x1965ea>
  597572:      	js	0x5975ec <.text+0x1965ec>
  597574:      	js	0x5975ee <.text+0x1965ee>
  597576:      	js	0x5975f0 <.text+0x1965f0>
  597578:      	js	0x5975f2 <.text+0x1965f2>
  59757a:      	js	0x5975f4 <.text+0x1965f4>
  59757c:      	js	0x5975f6 <.text+0x1965f6>
  59757e:      	js	0x5975f8 <.text+0x1965f8>
  597580:      	js	0x5975fa <.text+0x1965fa>
  597582:      	js	0x5975fc <.text+0x1965fc>
  597584:      	js	0x5975fe <.text+0x1965fe>
  597586:      	js	0x597600 <.text+0x196600>
  597588:      	js	0x597602 <.text+0x196602>
  59758a:      	aas
  59758b:      	incl	%eax
  59758c:      	incl	%ecx
  59758d:      	incl	%edx
  59758e:      	js	0x597608 <.text+0x196608>
  597590:      	js	0x59760a <.text+0x19660a>
  597592:      	js	0x59760c <.text+0x19660c>
  597594:      	js	0x59760e <.text+0x19660e>
  597596:      	js	0x597610 <.text+0x196610>
  597598:      	js	0x597612 <.text+0x196612>
  59759a:      	js	0x597614 <.text+0x196614>
  59759c:      	js	0x597616 <.text+0x196616>
  59759e:      	js	0x597618 <.text+0x196618>
  5975a0:      	js	0x59761a <.text+0x19661a>
  5975a2:      	js	0x59761c <.text+0x19661c>
  5975a4:      	js	0x59761e <.text+0x19661e>
  5975a6:      	js	0x597620 <.text+0x196620>
  5975a8:      	js	0x597622 <.text+0x196622>
  5975aa:      	js	0x597624 <.text+0x196624>
  5975ac:      	js	0x597626 <.text+0x196626>
  5975ae:      	js	0x597628 <.text+0x196628>
  5975b0:      	js	0x59762a <.text+0x19662a>
  5975b2:      	js	0x59762c <.text+0x19662c>
  5975b4:      	js	0x59762e <.text+0x19662e>
  5975b6:      	js	0x597630 <.text+0x196630>
  5975b8:      	js	0x597632 <.text+0x196632>
  5975ba:      	js	0x597634 <.text+0x196634>
  5975bc:      	incl	%ebx
  5975bd:      	incl	%esp
  5975be:      	js	0x597638 <.text+0x196638>
  5975c0:      	js	0x59763a <.text+0x19663a>
  5975c2:      	js	0x59763c <.text+0x19663c>
  5975c4:      	js	0x59763e <.text+0x19663e>
  5975c6:      	js	0x597640 <.text+0x196640>
  5975c8:      	js	0x597642 <.text+0x196642>
  5975ca:      	js	0x597644 <.text+0x196644>
  5975cc:      	js	0x597646 <.text+0x196646>
  5975ce:      	js	0x597648 <.text+0x196648>
  5975d0:      	js	0x59764a <.text+0x19664a>
  5975d2:      	js	0x59764c <.text+0x19664c>
  5975d4:      	js	0x59764e <.text+0x19664e>
  5975d6:      	js	0x597650 <.text+0x196650>
  5975d8:      	js	0x597652 <.text+0x196652>
  5975da:      	js	0x597654 <.text+0x196654>
  5975dc:      	js	0x597656 <.text+0x196656>
  5975de:      	js	0x597658 <.text+0x196658>
  5975e0:      	js	0x59765a <.text+0x19665a>
  5975e2:      	js	0x59765c <.text+0x19665c>
  5975e4:      	js	0x59765e <.text+0x19665e>
  5975e6:      	js	0x597660 <.text+0x196660>
  5975e8:      	js	0x597662 <.text+0x196662>
  5975ea:      	js	0x597664 <.text+0x196664>
  5975ec:      	js	0x597666 <.text+0x196666>
  5975ee:      	incl	%ebp
  5975ef:      	incl	%esi
  5975f0:      	incl	%edi
  5975f1:      	js	0x59766b <.text+0x19666b>
  5975f3:      	js	0x59766d <.text+0x19666d>
  5975f5:      	js	0x59766f <.text+0x19666f>
  5975f7:      	js	0x597671 <.text+0x196671>
  5975f9:      	js	0x597673 <.text+0x196673>
  5975fb:      	js	0x597675 <.text+0x196675>
  5975fd:      	js	0x597677 <.text+0x196677>
  5975ff:      	js	0x597679 <.text+0x196679>
  597601:      	js	0x59767b <.text+0x19667b>
  597603:      	js	0x59767d <.text+0x19667d>
  597605:      	js	0x59767f <.text+0x19667f>
  597607:      	js	0x597681 <.text+0x196681>
  597609:      	js	0x597683 <.text+0x196683>
  59760b:      	js	0x597685 <.text+0x196685>
  59760d:      	js	0x597687 <.text+0x196687>
  59760f:      	js	0x597689 <.text+0x196689>
  597611:      	js	0x59768b <.text+0x19668b>
  597613:      	js	0x59768d <.text+0x19668d>
  597615:      	js	0x59768f <.text+0x19668f>
  597617:      	js	0x597691 <.text+0x196691>
  597619:      	js	0x597693 <.text+0x196693>
  59761b:      	js	0x597695 <.text+0x196695>
  59761d:      	js	0x597697 <.text+0x196697>
  59761f:      	js	0x597669 <.text+0x196669>
  597621:      	decl	%ecx
  597622:      	decl	%edx
  597623:      	decl	%ebx
  597624:      	decl	%esp
  597625:      	js	0x59769f <.text+0x19669f>
  597627:      	js	0x5976a1 <.text+0x1966a1>
  597629:      	js	0x5976a3 <.text+0x1966a3>
  59762b:      	js	0x5976a5 <.text+0x1966a5>
  59762d:      	js	0x5976a7 <.text+0x1966a7>
  59762f:      	js	0x5976a9 <.text+0x1966a9>
  597631:      	js	0x5976ab <.text+0x1966ab>
  597633:      	js	0x5976ad <.text+0x1966ad>
  597635:      	js	0x5976af <.text+0x1966af>
  597637:      	js	0x5976b1 <.text+0x1966b1>
  597639:      	js	0x5976b3 <.text+0x1966b3>
  59763b:      	js	0x5976b5 <.text+0x1966b5>
  59763d:      	js	0x5976b7 <.text+0x1966b7>
  59763f:      	js	0x5976b9 <.text+0x1966b9>
  597641:      	js	0x5976bb <.text+0x1966bb>
  597643:      	js	0x5976bd <.text+0x1966bd>
  597645:      	js	0x5976bf <.text+0x1966bf>
  597647:      	js	0x5976c1 <.text+0x1966c1>
  597649:      	js	0x5976c3 <.text+0x1966c3>
  59764b:      	js	0x5976c5 <.text+0x1966c5>
  59764d:      	js	0x5976c7 <.text+0x1966c7>
  59764f:      	js	0x5976c9 <.text+0x1966c9>
  597651:      	js	0x5976cb <.text+0x1966cb>
  597653:      	js	0x5976cd <.text+0x1966cd>
  597655:      	js	0x5976cf <.text+0x1966cf>
  597657:      	js	0x5976d1 <.text+0x1966d1>
  597659:      	js	0x5976d3 <.text+0x1966d3>
  59765b:      	js	0x5976d5 <.text+0x1966d5>
  59765d:      	js	0x5976d7 <.text+0x1966d7>
  59765f:      	js	0x5976d9 <.text+0x1966d9>
  597661:      	js	0x5976db <.text+0x1966db>
  597663:      	js	0x5976dd <.text+0x1966dd>
  597665:      	js	0x5976df <.text+0x1966df>
  597667:      	js	0x5976e1 <.text+0x1966e1>
  597669:      	js	0x5976e3 <.text+0x1966e3>
  59766b:      	js	0x5976e5 <.text+0x1966e5>
  59766d:      	js	0x5976e7 <.text+0x1966e7>
  59766f:      	js	0x5976e9 <.text+0x1966e9>
  597671:      	js	0x5976eb <.text+0x1966eb>
  597673:      	js	0x5976ed <.text+0x1966ed>
  597675:      	js	0x5976ef <.text+0x1966ef>
  597677:      	js	0x5976f1 <.text+0x1966f1>
  597679:      	js	0x5976f3 <.text+0x1966f3>
  59767b:      	js	0x5976f5 <.text+0x1966f5>
  59767d:      	js	0x5976f7 <.text+0x1966f7>
  59767f:      	js	0x5976f9 <.text+0x1966f9>
  597681:      	js	0x5976fb <.text+0x1966fb>
  597683:      	js	0x5976d2 <.text+0x1966d2>
  597685:      	js	0x5976ff <.text+0x1966ff>
  597687:      	js	0x5976d7 <.text+0x1966d7>
  597689:      	js	0x597703 <.text+0x196703>
  59768b:      	js	0x597705 <.text+0x196705>
  59768d:      	decl	%edi
  59768e:      	js	0x597708 <.text+0x196708>
  597690:      	js	0x5976e2 <.text+0x1966e2>
  597692:      	pushl	%ecx
  597693:      	js	0x59770d <.text+0x19670d>
  597695:      	js	0x59770f <.text+0x19670f>
  597697:      	js	0x597711 <.text+0x196711>
  597699:      	js	0x5976ed <.text+0x1966ed>
  59769b:      	js	0x5976f0 <.text+0x1966f0>
  59769d:      	js	0x597717 <.text+0x196717>
  59769f:      	js	0x597719 <.text+0x196719>
  5976a1:      	js	0x59771b <.text+0x19671b>
  5976a3:      	js	0x59771d <.text+0x19671d>
  5976a5:      	js	0x59771f <.text+0x19671f>
  5976a7:      	pushl	%esp
  5976a8:      	pushl	%ebp
  5976a9:      	pushl	%esi
  5976aa:      	pushl	%edi
  5976ab:      	popl	%eax
  5976ac:      	popl	%ecx
  5976ad:      	popl	%edx
  5976ae:      	popl	%ebx
  5976af:      	popl	%esp
  5976b0:      	popl	%ebp
  5976b1:      	popl	%esi
  5976b2:      	popl	%edi
  5976b3:      	pushal
  5976b4:      	popal
  5976b5:      	bound	%esp, 0x64(%ebx)
  5976b8:      	addr16		pushw	$0x6a69         # imm = 0x6A69
  5976be:      	imull	$0x6f, 0x6e(%ebp,%ebp,2), %ebp
  5976c3:      	jo	0x597736 <.text+0x196736>
  5976c5:      	jb	0x59773a <.text+0x19673a>
  5976c7:      	je	0x59773e <.text+0x19673e>
  5976c9:      	jbe	0x597742 <.text+0x196742>
  5976cb:      	movl	%edi, %edi
  5976cd:      	movb	$0x8, %bl
  5976cf:      	popl	%ecx
  5976d0:      	addb	%bh, -0x38ffa6f8(%ebp)
  5976d6:      	orb	%bl, (%ecx)
  5976d9:      	pushl	%ss
  5976da:      	sbbb	(%ecx), %bl
  5976dd:      	pushl	%ss
  5976de:      	sbbb	(%ecx), %bl
  5976e1:      	pushl	%ss
  5976e2:      	sbbb	(%ecx), %bl
  5976e5:      	pushl	%ss
  5976e6:      	sbbb	(%ecx), %bl
  5976e9:      	pushl	%ss
  5976ea:      	sbbb	(%ecx), %bl
  5976ed:      	pushl	%ss
  5976ee:      	sbbb	(%ecx), %bl
  5976f1:      	pushl	%ss
  5976f2:      	sbbb	(%ecx), %bl
  5976f5:      	rorl	(%eax)
  5976f7:      	popl	%ecx
  5976f8:      	addb	%bl, %bl
  5976fa:      	orb	%bl, (%ecx)
  5976fd:      	inl	$0x8, %eax
  5976ff:      	popl	%ecx
  597700:      	addb	%ch, %bh
  597702:      	orb	%bl, (%ecx)
  597705:      	stc
  597706:      	orb	%bl, (%ecx)
  597709:      	sbbl	$0x3005893, %eax        # imm = 0x3005893
  59770e:      	orl	%ebx, (%ecx)
  597711:      	orl	$0x17005909, %eax       # imm = 0x17005909
  597716:      	orl	%ebx, (%ecx)
  597719:      	andl	%ecx, (%ecx)
  59771b:      	popl	%ecx
  59771c:      	addb	%ch, (%ebx)
  59771e:      	orl	%ebx, (%ecx)
  597721:      	pushl	%esp
  597722:      	orl	%ebx, (%ecx)
  597725:      	je	0x5976ba <.text+0x1966ba>
  597727:      	popl	%eax
  597728:      	addb	%bl, 0x9(%esi)
  59772b:      	popl	%ecx
  59772c:      	addb	%ch, 0x9(%eax)
  59772f:      	popl	%ecx
  597730:      	addb	%dh, 0x9(%edx)
  597733:      	popl	%ecx
  597734:      	addb	%bh, 0x59(%ecx,%ecx)
  597738:      	addb	%al, -0x6fffa6f7(%esi)
  59773e:      	orl	%ebx, (%ecx)
  597741:      	lcalll	$0x5909, $0xa4005909    # imm = 0x5909
                                                # imm = 0xA4005909
  597748:      	addb	%ch, -0x47ffa6f7(%esi)
  59774e:      	orl	%ebx, (%ecx)
  597751:      	retl	$0x5909                 # imm = 0x5909
  597754:      	addb	%cl, %ah
  597756:      	orl	%ebx, (%ecx)
  597759:      	orb	%cl, (%edx)
  59775b:      	popl	%ecx
  59775c:      	addb	%dl, (%edx)
  59775e:      	orb	(%ecx), %bl
  597761:      	sbbb	$0xa, %al
  597763:      	popl	%ecx
  597764:      	addb	%ah, (%esi)
  597766:      	orb	(%ecx), %bl
  597769:      	xorb	%cl, (%edx)
  59776b:      	popl	%ecx
  59776c:      	addb	%bh, (%edx)
  59776e:      	orb	(%ecx), %bl
  597771:      	incl	%esp
  597772:      	orb	(%ecx), %bl
  597775:      	decl	%esi
  597776:      	orb	(%ecx), %bl
  597779:      	popl	%eax
  59777a:      	orb	(%ecx), %bl
  59777d:      	bound	%ecx, (%edx)
  59777f:      	popl	%ecx
  597780:      	addb	%ch, 0x59(%edx,%ecx)
  597784:      	addb	%dh, 0xa(%esi)
  597787:      	popl	%ecx
  597788:      	addb	%al, -0x75ffa6f6(%eax)
  59778e:      	orb	(%ecx), %bl
  597791:      	xchgl	%esp, %eax
  597792:      	orb	(%ecx), %bl
  597795:      	sahf
  597796:      	orb	(%ecx), %bl
  597799:      	<unknown>
  59779b:      	popl	%ecx
  59779c:      	addb	%dl, %cl
  59779e:      	orb	(%ecx), %bl
  5977a1:      	fisttpl	(%edx)
  5977a3:      	popl	%ecx
  5977a4:      	addb	%ah, %ch
  5977a6:      	orb	(%ecx), %bl
  5977a9:      	outl	%eax, %dx
  5977aa:      	orb	(%ecx), %bl
  5977ad:      	stc
  5977ae:      	orb	(%ecx), %bl
  5977b1:      	addl	(%ebx), %ecx
  5977b3:      	popl	%ecx
  5977b4:      	addb	%cl, 0x1700590b
  5977ba:      	orl	(%ecx), %ebx
  5977bd:      	andl	%ecx, (%ebx)
  5977bf:      	popl	%ecx
  5977c0:      	addb	%ch, (%ebx)
  5977c2:      	orl	(%ecx), %ebx
  5977c5:      	xorl	$0x6d00590b, %eax       # imm = 0x6D00590B
  5977ca:      	orl	(%ecx), %ebx
  5977cd:      	ja	0x5977da <.text+0x1967da>
  5977cf:      	popl	%ecx
  5977d0:      	addb	%al, -0x74ffa6f5(%ecx)
  5977d6:      	orl	(%ecx), %ebx
  5977d9:      	xchgl	%ebp, %eax
  5977da:      	orl	(%ecx), %ebx
  5977dd:      	lahf
  5977de:      	orl	(%ecx), %ebx
  5977e1:      	testl	$0xb300590b, %eax       # imm = 0xB300590B
  5977e6:      	orl	(%ecx), %ebx
  5977e9:      	movl	$0xc700590b, %ebp       # imm = 0xC700590B
  5977ee:      	orl	(%ecx), %ebx
  5977f1:      	outb	%al, $0xb
  5977f3:      	popl	%ecx
  5977f4:      	addb	%dh, %al
  5977f6:      	orl	(%ecx), %ebx
  5977f9:      	cli
  5977fa:      	orl	(%ecx), %ebx
  5977fd:      	addb	$0xc, %al
  5977ff:      	popl	%ecx
  597800:      	addb	%cl, (%esi)
  597802:      	orb	$0x59, %al
  597804:      	addb	%bl, (%eax)
  597806:      	orb	$0x59, %al
  597808:      	addb	%ah, (%edx)
  59780a:      	orb	$0x59, %al
  59780c:      	addb	%ah, 0x2c005894(%ebx)
  597812:      	orb	$0x59, %al
  597814:      	addb	%dh, (%esi)
  597816:      	orb	$0x59, %al
  597818:      	addb	%al, 0xc(%eax)
  59781b:      	popl	%ecx
  59781c:      	addb	%cl, 0xc(%edx)
  59781f:      	popl	%ecx
  597820:      	addb	%dl, 0x59(%esp,%ecx)
  597824:      	addb	%bl, 0xc(%esi)
  597827:      	popl	%ecx
  597828:      	addb	%ch, 0xc(%eax)
  59782b:      	popl	%ecx
  59782c:      	addb	%dh, 0xc(%edx)
  59782f:      	popl	%ecx
  597830:      	addb	%bh, 0x59(%esp,%ecx)
  597834:      	addb	%al, -0x6fffa6f4(%esi)
  59783a:      	orb	$0x59, %al
  59783c:      	addb	%bl, 0x1600590c(%edx)
  597842:      	sbbb	(%ecx), %bl
  597845:      	movsb	(%esi), %es:(%edi)
  597846:      	orb	$0x59, %al
  597848:      	addb	%dl, (%esi)
  59784a:      	sbbb	(%ecx), %bl
  59784d:      	scasb	%es:(%edi), %al
  59784e:      	orb	$0x59, %al
  597850:      	addb	%bh, -0x3dffa6f4(%eax)
  597856:      	orb	$0x59, %al
  597858:      	addb	%cl, %ah
  59785a:      	orb	$0x59, %al
  59785c:      	addb	%dl, %dh
  59785e:      	orb	$0x59, %al
  597860:      	addb	%ah, %al
  597862:      	orb	$0x59, %al
  597864:      	addb	%ch, %dl
  597866:      	orb	$0x59, %al
  597868:      	addb	%dh, %ah
  59786a:      	orb	$0x59, %al
  59786c:      	addb	%bh, %dh
  59786e:      	orb	$0x59, %al
  597870:      	addb	%cl, (%eax)
  597872:      	orl	$0xd120059, %eax        # imm = 0xD120059
  597877:      	popl	%ecx
  597878:      	addb	%bl, 0xd260059(,%ecx)
  59787f:      	popl	%ecx
  597880:      	addb	%dh, (%eax)
  597882:      	orl	$0xd3a0059, %eax        # imm = 0xD3A0059
  597887:      	popl	%ecx
  597888:      	addb	%al, 0x59(%ebp,%ecx)
  59788c:      	addb	%cl, 0xd(%esi)
  59788f:      	popl	%ecx
  597890:      	addb	%bl, 0xd(%eax)
  597893:      	popl	%ecx
  597894:      	addb	%ah, 0xd(%edx)
  597897:      	popl	%ecx
  597898:      	addb	%ch, 0x59(%ebp,%ecx)
  59789c:      	addb	%dh, 0xd(%esi)
  59789f:      	popl	%ecx
  5978a0:      	addb	%al, -0x75ffa6f3(%eax)
  5978a6:      	orl	$0xd940059, %eax        # imm = 0xD940059
  5978ab:      	popl	%ecx
  5978ac:      	addb	%bl, -0x57ffa6f3(%esi)
  5978b2:      	orl	$0xdb20059, %eax        # imm = 0xDB20059
  5978b7:      	popl	%ecx
  5978b8:      	addb	%ch, %dh
  5978ba:      	orl	$0xdf80059, %eax        # imm = 0xDF80059
  5978bf:      	popl	%ecx
  5978c0:      	addb	%al, (%edx)
  5978c2:      	pushl	%cs
  5978c3:      	popl	%ecx
  5978c4:      	addb	%cl, (%esi,%ecx)
  5978c7:      	popl	%ecx
  5978c8:      	addb	%dl, (%esi)
  5978ca:      	pushl	%cs
  5978cb:      	popl	%ecx
  5978cc:      	addb	%ah, (%eax)
  5978ce:      	pushl	%cs
  5978cf:      	popl	%ecx
  5978d0:      	addb	%ch, (%edx)
  5978d2:      	pushl	%cs
  5978d3:      	popl	%ecx
  5978d4:      	addb	%dh, (%esi,%ecx)
  5978d7:      	popl	%ecx
  5978d8:      	addb	%bh, (%esi)
  5978da:      	pushl	%cs
  5978db:      	popl	%ecx
  5978dc:      	addb	%cl, 0xe(%eax)
  5978df:      	popl	%ecx
  5978e0:      	addb	%dl, 0xe(%edx)
  5978e3:      	popl	%ecx
  5978e4:      	addb	%bl, 0x59(%esi,%ecx)
  5978e8:      	addb	%ah, 0xe(%esi)
  5978eb:      	popl	%ecx
  5978ec:      	addb	%dh, 0xe(%eax)
  5978ef:      	popl	%ecx
  5978f0:      	addb	%bh, 0xe(%edx)
  5978f3:      	popl	%ecx
  5978f4:      	addb	%al, 0xe8e0059(%esi,%ecx)
  5978fb:      	popl	%ecx
  5978fc:      	addb	%bl, -0x5dffa6f2(%eax)
  597902:      	pushl	%cs
  597903:      	popl	%ecx
  597904:      	addb	%ch, 0xeb60059(%esi,%ecx)
  59790b:      	popl	%ecx
  59790c:      	addb	%al, %al
  59790e:      	pushl	%cs
  59790f:      	popl	%ecx
  597910:      	addb	%cl, %dl
  597912:      	pushl	%cs
  597913:      	popl	%ecx
  597914:      	addb	%dl, %ah
  597916:      	pushl	%cs
  597917:      	popl	%ecx
  597918:      	addb	%bl, %dh
  59791a:      	pushl	%cs
  59791b:      	popl	%ecx
  59791c:      	addb	%ch, %al
  59791e:      	pushl	%cs
  59791f:      	popl	%ecx
  597920:      	addb	%dh, %dl
  597922:      	pushl	%cs
  597923:      	popl	%ecx
  597924:      	addb	%bh, %ah
  597926:      	pushl	%cs
  597927:      	popl	%ecx
  597928:      	addb	%dl, (%esi)
  59792a:      	sbbb	(%ecx), %bl
  59792d:      	pushl	%es
  59792e:      	mulps	(%eax), %xmm0
  597931:      	adcb	%cl, (%edi)
  597933:      	popl	%ecx
  597934:      	addb	%bl, (%edx)
  597936:      	mulps	(%eax), %xmm0
  597939:      	pushl	%esi
  59793a:      	mulps	(%eax), %xmm0
  59793d:      	pushal
  59793e:      	mulps	(%eax), %xmm0
  597941:      	pushl	$0xf
  597943:      	popl	%ecx
  597944:      	addb	%dh, 0x59(%edi,%ecx)
  597948:      	addb	%bh, 0xf(%esi)
  59794b:      	popl	%ecx
  59794c:      	addb	%cl, -0x6dffa6f1(%eax)
  597952:      	mulps	(%eax), %xmm0
  597955:      	pushfl
  597956:      	mulps	(%eax), %xmm0
  597959:      	cmpsb	%es:(%edi), (%esi)
  59795a:      	mulps	(%eax), %xmm0
  59795d:      	movb	$0xf, %al
  59795f:      	popl	%ecx
  597960:      	addb	%bh, -0x3bffa6f1(%edx)
  597966:      	mulps	(%eax), %xmm0
  597969:      	into
  59796a:      	mulps	(%eax), %xmm0
  59796d:      	fmuls	(%edi)
  59796f:      	popl	%ecx
  597970:      	addb	%ah, %dl
  597972:      	mulps	(%eax), %xmm0
  597975:      	inb	%dx, %al
  597976:      	mulps	(%eax), %xmm0
  597979:      	<unknown>
  59797b:      	popl	%ecx
  59797c:      	addb	%al, (%eax)
  59797e:      	adcb	%bl, (%ecx)
  597981:      	orb	(%eax), %dl
  597983:      	popl	%ecx
  597984:      	addb	%dl, (%eax,%edx)
  597987:      	popl	%ecx
  597988:      	addb	%bl, (%esi)
  59798a:      	adcb	%bl, (%ecx)
  59798d:      	subb	%dl, (%eax)
  59798f:      	popl	%ecx
  597990:      	addb	%dh, (%edx)
  597992:      	adcb	%bl, (%ecx)
  597995:      	cmpb	$0x10, %al
  597997:      	popl	%ecx
  597998:      	addb	%al, 0x10(%esi)
  59799b:      	popl	%ecx
  59799c:      	addb	%dl, 0x10(%eax)
  59799f:      	popl	%ecx
  5979a0:      	addb	%bl, 0x10(%edx)
  5979a3:      	popl	%ecx
  5979a4:      	addb	%ah, 0x59(%eax,%edx)
  5979a8:      	addb	%ch, 0x10(%esi)
  5979ab:      	popl	%ecx
  5979ac:      	addb	%bh, 0x10(%eax)
  5979af:      	popl	%ecx
  5979b0:      	addb	%al, -0x73ffa6f0(%edx)
  5979b6:      	adcb	%bl, (%ecx)
  5979b9:      	xchgl	%esi, %eax
  5979ba:      	adcb	%bl, (%ecx)
  5979bd:      	movb	0xaa005910, %al
  5979c2:      	adcb	%bl, (%ecx)
  5979c5:      	movb	$0x10, %ah
  5979c7:      	popl	%ecx
  5979c8:      	addb	%bh, -0x37ffa6f0(%esi)
  5979ce:      	adcb	%bl, (%ecx)
  5979d1:      	rclb	%cl, (%eax)
  5979d3:      	popl	%ecx
  5979d4:      	addb	%bl, %ah
  5979d6:      	adcb	%bl, (%ecx)
  5979d9:      	outb	%al, $0x10
  5979db:      	popl	%ecx
  5979dc:      	addb	%dh, %al
  5979de:      	adcb	%bl, (%ecx)
  5979e1:      	cli
  5979e2:      	adcb	%bl, (%ecx)
  5979e5:      	addb	$0x11, %al
  5979e7:      	popl	%ecx
  5979e8:      	addb	%cl, (%esi)
  5979ea:      	adcl	%ebx, (%ecx)
  5979ed:      	sbbb	%dl, (%ecx)
  5979ef:      	popl	%ecx
  5979f0:      	addb	%ah, (%edx)
  5979f2:      	adcl	%ebx, (%ecx)
  5979f5:      	subb	$0x11, %al
  5979f7:      	popl	%ecx
  5979f8:      	addb	%dh, (%esi)
  5979fa:      	adcl	%ebx, (%ecx)
  5979fd:      	incl	%eax
  5979fe:      	adcl	%ebx, (%ecx)
  597a01:      	decl	%edx
  597a02:      	adcl	%ebx, (%ecx)
  597a05:      	pushl	%esp
  597a06:      	adcl	%ebx, (%ecx)
  597a09:      	popl	%esi
  597a0a:      	adcl	%ebx, (%ecx)
  597a0d:      	pushl	$0x72005911             # imm = 0x72005911
  597a12:      	adcl	%ebx, (%ecx)
  597a15:      	jl	0x597a28 <.text+0x196a28>
  597a17:      	popl	%ecx
  597a18:      	addb	%al, -0x6fffa6ef(%esi)
  597a1e:      	adcl	%ebx, (%ecx)
  597a21:      	lcalll	$0x5911, $0xa4005911    # imm = 0x5911
                                                # imm = 0xA4005911
  597a28:      	addb	%ch, -0x47ffa6ef(%esi)
  597a2e:      	adcl	%ebx, (%ecx)
  597a31:      	retl	$0x5911                 # imm = 0x5911
  597a34:      	addb	%cl, %ah
  597a36:      	adcl	%ebx, (%ecx)
  597a39:      	salc
  597a3a:      	adcl	%ebx, (%ecx)
  597a3d:      	loopne	0x597a50 <.text+0x196a50>
  597a3f:      	popl	%ecx
  597a40:      	addb	%ch, %dl
  597a42:      	adcl	%ebx, (%ecx)
  597a45:      	hlt
  597a46:      	adcl	%ebx, (%ecx)
  597a49:      	<unknown>
  597a4b:      	popl	%ecx
  597a4c:      	addb	%cl, (%eax)
  597a4e:      	adcb	(%ecx), %bl
  597a51:      	adcb	(%edx), %dl
  597a53:      	popl	%ecx
  597a54:      	addb	%bl, (%edx,%edx)
  597a57:      	popl	%ecx
  597a58:      	addb	%ah, (%esi)
  597a5a:      	adcb	(%ecx), %bl
  597a5d:      	xorb	%dl, (%edx)
  597a5f:      	popl	%ecx
  597a60:      	addb	%bh, (%edx)
  597a62:      	adcb	(%ecx), %bl
  597a65:      	incl	%esp
  597a66:      	adcb	(%ecx), %bl
  597a69:      	decl	%esi
  597a6a:      	adcb	(%ecx), %bl
  597a6d:      	popl	%eax
  597a6e:      	adcb	(%ecx), %bl
  597a71:      	bound	%edx, (%edx)
  597a73:      	popl	%ecx
  597a74:      	addb	%ch, 0x59(%edx,%edx)
  597a78:      	addb	%dh, 0x12(%esi)
  597a7b:      	popl	%ecx
  597a7c:      	addb	%cl, -0x1374aa01(%ebx)
