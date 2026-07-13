; Entry: 004fd31f
; Name: Terrain128Poly
; Signature: void Terrain128Poly(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004fdbd9
; Reason: Exception while decompiling 004fd31f: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004fd31f --stop-address=0x004fdbd9 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4fd31f:      	pushl	%ebp
  4fd320:      	movl	%esp, %ebp
  4fd322:      	pushl	%ebx
  4fd323:      	pushl	%esi
  4fd324:      	pushl	%edi
  4fd325:      	pushl	%ebp
  4fd326:      	subl	$0x700, %esp            # imm = 0x700
  4fd32c:      	movl	0x14(%ebp), %ebx
  4fd32f:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fd334:      	movl	0xc(%ebp), %esi
  4fd337:      	movl	0x10(%ebp), %eax
  4fd33a:      	fildl	0x4(%ebx)
  4fd33d:      	movl	(%ebx), %ecx
  4fd33f:      	movl	%esi, (%esp)
  4fd342:      	shll	$0x3, %eax
  4fd345:      	leal	0x8(%ebx), %edi
  4fd348:      	fildl	(%ebx)
  4fd34a:      	movl	%ecx, 0x10(%esp)
  4fd34e:      	leal	(%eax,%eax,2), %ecx
  4fd351:      	xorl	%eax, %eax
  4fd353:      	movl	%edi, 0x50(%esp)
  4fd357:      	flds	0x62c808
  4fd35d:      	fsubs	0x14(%esi,%eax)
  4fd361:      	flds	0x4(%esi,%eax)
  4fd365:      	faddl	0x632380
  4fd36b:      	fxch	%st(1)
  4fd36d:      	flds	0xc(%esi,%eax)
  4fd371:      	fmul	%st(3), %st
  4fd373:      	flds	0x10(%esi,%eax)
  4fd377:      	fmul	%st(5), %st
  4fd379:      	fxch	%st(3)
  4fd37b:      	fstpl	0x38(%esp)
  4fd37f:      	fxch	%st(1)
  4fd381:      	fmuls	0x62c810
  4fd387:      	fxch	%st(2)
  4fd389:      	fstps	0x10(%esi,%eax)
  4fd38d:      	fstps	0xc(%esi,%eax)
  4fd391:      	fstps	0x14(%esi,%eax)
  4fd395:      	movl	0x38(%esp), %edi
  4fd399:      	movl	%eax, 0x3e4(%esp,%eax)
  4fd3a0:      	movl	%eax, 0x114(%esp,%eax)
  4fd3a7:      	movl	%edi, 0x400(%esp,%eax)
  4fd3ae:      	addl	$0x18, %eax
  4fd3b1:      	cmpl	%edx, %edi
  4fd3b3:      	jg	0x4fd3b9 <.text+0xfc3b9>
  4fd3b5:      	movl	%eax, %ebx
  4fd3b7:      	movl	%edi, %edx
  4fd3b9:      	cmpl	%ecx, %eax
  4fd3bb:      	jne	0x4fd357 <.text+0xfc357>
  4fd3bd:      	subl	$0x18, %ebx
  4fd3c0:      	leal	-0x18(%eax), %ecx
  4fd3c3:      	fcompp
  4fd3c5:      	movl	$0x0, 0x3e4(%esp,%eax)
  4fd3d0:      	movl	%ecx, 0xfc(%esp)
  4fd3d7:      	movl	0x8(%ebp), %edi
  4fd3da:      	movl	%ebx, 0xcc(%esp)
  4fd3e1:      	movl	%ebx, 0x9c(%esp)
  4fd3e8:      	movl	%ebx, 0xd0(%esp)
  4fd3ef:      	movl	%esi, %ebp
  4fd3f1:      	movl	0x20(%edi), %eax
  4fd3f4:      	movl	(%edi), %ecx
  4fd3f6:      	addl	%edx, %eax
  4fd3f8:      	movl	0x14(%edi), %esi
  4fd3fb:      	movl	0x1c(%edi), %edi
  4fd3fe:      	imull	%ecx
  4fd400:      	addl	%edi, %esi
  4fd402:      	movl	%ecx, 0xc(%esp)
  4fd406:      	addl	%eax, %esi
  4fd408:      	movl	0x400(%esp,%ebx), %edi
  4fd40f:      	movl	%esi, 0x98(%esp)
  4fd416:      	movl	%ebx, 0xa0(%esp)
  4fd41d:      	movl	0xd0(%esp), %ecx
  4fd424:      	movl	0x400(%esp,%ecx), %eax
  4fd42b:      	movl	%edi, 0x4(%esp)
  4fd42f:      	cmpl	%eax, %edi
  4fd431:      	jl	0x4fd55a <.text+0xfc55a>
  4fd437:      	movl	0x3fc(%esp,%ecx), %edx
  4fd43e:      	movl	%ecx, %eax
  4fd440:      	movl	%edx, 0xd0(%esp)
  4fd447:      	cmpl	0x9c(%esp), %edx
  4fd44e:      	je	0x4fdbcd <.text+0xfcbcd>
  4fd454:      	movl	0x400(%esp,%edx), %esi
  4fd45b:      	movl	%edx, %ecx
  4fd45d:      	cmpl	%esi, %edi
  4fd45f:      	jge	0x4fd437 <.text+0xfc437>
  4fd461:      	flds	0x14(%ebp,%edx)
  4fd465:      	fsubs	0x14(%ebp,%eax)
  4fd469:      	flds	0x4(%ebp,%edx)
  4fd46d:      	fsubs	0x4(%ebp,%eax)
  4fd471:      	flds	0x10(%ebp,%edx)
  4fd475:      	fsubs	0x10(%ebp,%eax)
  4fd479:      	fxch	%st(1)
  4fd47b:      	fdivrs	0x62c808
  4fd481:      	flds	0xc(%ebp,%edx)
  4fd485:      	fsubs	0xc(%ebp,%eax)
  4fd489:      	fxch	%st(1)
  4fd48b:      	fmul	%st, %st(2)
  4fd48d:      	flds	0x8(%ebp,%edx)
  4fd491:      	fsubs	0x8(%ebp,%eax)
  4fd495:      	fxch	%st(2)
  4fd497:      	fmul	%st(1), %st
  4fd499:      	flds	(%ebp,%edx)
  4fd49d:      	fsubs	(%ebp,%eax)
  4fd4a1:      	fxch	%st(3)
  4fd4a3:      	fmul	%st(2), %st
  4fd4a5:      	fxch	%st(4)
  4fd4a7:      	fstps	0xec(%esp)
  4fd4ae:      	fstps	0xe8(%esp)
  4fd4b5:      	fmul	%st, %st(3)
  4fd4b7:      	flds	0x4(%ebp,%eax)
  4fd4bb:      	faddl	0x632380
  4fd4c1:      	fxch	%st(2)
  4fd4c3:      	fmulp	%st, %st(1)
  4fd4c5:      	fxch	%st(3)
  4fd4c7:      	fstps	0xf8(%esp)
  4fd4ce:      	fstpl	0x38(%esp)
  4fd4d2:      	fstps	0xf4(%esp)
  4fd4d9:      	fildl	0x38(%esp)
  4fd4dd:      	fxch	%st(1)
  4fd4df:      	fstps	0xf0(%esp)
  4fd4e6:      	fsubs	0x4(%ebp,%eax)
  4fd4ea:      	flds	0xf0(%esp)
  4fd4f1:      	flds	0xf4(%esp)
  4fd4f8:      	fmul	%st(2), %st
  4fd4fa:      	flds	0xe8(%esp)
  4fd501:      	fmul	%st(3), %st
  4fd503:      	flds	0xf8(%esp)
  4fd50a:      	fmul	%st(4), %st
  4fd50c:      	fxch	%st(2)
  4fd50e:      	fadds	0x8(%ebp,%eax)
  4fd512:      	flds	0xec(%esp)
  4fd519:      	fmul	%st(5), %st
  4fd51b:      	fxch	%st(2)
  4fd51d:      	fadds	0xc(%ebp,%eax)
  4fd521:      	fxch	%st(4)
  4fd523:      	fmulp	%st, %st(5)
  4fd525:      	fstps	0xd8(%esp)
  4fd52c:      	fadds	0x10(%ebp,%eax)
  4fd530:      	fxch	%st(3)
  4fd532:      	fadds	(%ebp,%eax)
  4fd536:      	fxch	%st(2)
  4fd538:      	fstps	0xdc(%esp)
  4fd53f:      	fadds	0x14(%ebp,%eax)
  4fd543:      	fxch	%st(2)
  4fd545:      	fstps	0xe0(%esp)
  4fd54c:      	fstps	0xd4(%esp)
  4fd553:      	fstps	0xe4(%esp)
  4fd55a:      	movl	0xa0(%esp), %ecx
  4fd561:      	cmpl	0x400(%esp,%ecx), %edi
  4fd568:      	jl	0x4fd682 <.text+0xfc682>
  4fd56e:      	movl	0xfc(%esp,%ecx), %edx
  4fd575:      	movl	%ecx, %eax
  4fd577:      	movl	%edx, 0xa0(%esp)
  4fd57e:      	movl	%edx, %ecx
  4fd580:      	cmpl	0x400(%esp,%edx), %edi
  4fd587:      	jge	0x4fd56e <.text+0xfc56e>
  4fd589:      	flds	0x14(%ebp,%edx)
  4fd58d:      	fsubs	0x14(%ebp,%eax)
  4fd591:      	flds	0x4(%ebp,%edx)
  4fd595:      	fsubs	0x4(%ebp,%eax)
  4fd599:      	flds	0x10(%ebp,%edx)
  4fd59d:      	fsubs	0x10(%ebp,%eax)
  4fd5a1:      	fxch	%st(1)
  4fd5a3:      	fdivrs	0x62c808
  4fd5a9:      	flds	0xc(%ebp,%edx)
  4fd5ad:      	fsubs	0xc(%ebp,%eax)
  4fd5b1:      	fxch	%st(1)
  4fd5b3:      	fmul	%st, %st(2)
  4fd5b5:      	flds	0x8(%ebp,%edx)
  4fd5b9:      	fsubs	0x8(%ebp,%eax)
  4fd5bd:      	fxch	%st(2)
  4fd5bf:      	fmul	%st(1), %st
  4fd5c1:      	flds	(%ebp,%edx)
  4fd5c5:      	fsubs	(%ebp,%eax)
  4fd5c9:      	fxch	%st(3)
  4fd5cb:      	fmul	%st(2), %st
  4fd5cd:      	fxch	%st(4)
  4fd5cf:      	fstps	0xbc(%esp)
  4fd5d6:      	fstps	0xb8(%esp)
  4fd5dd:      	fmul	%st, %st(3)
  4fd5df:      	flds	0x4(%ebp,%eax)
  4fd5e3:      	faddl	0x632380
  4fd5e9:      	fxch	%st(2)
  4fd5eb:      	fmulp	%st, %st(1)
  4fd5ed:      	fxch	%st(3)
  4fd5ef:      	fstps	0xc8(%esp)
  4fd5f6:      	fstpl	0x38(%esp)
  4fd5fa:      	fstps	0xc4(%esp)
  4fd601:      	fildl	0x38(%esp)
  4fd605:      	fxch	%st(1)
  4fd607:      	fstps	0xc0(%esp)
  4fd60e:      	fsubs	0x4(%ebp,%eax)
  4fd612:      	flds	0xc0(%esp)
  4fd619:      	flds	0xc4(%esp)
  4fd620:      	fmul	%st(2), %st
  4fd622:      	flds	0xb8(%esp)
  4fd629:      	fmul	%st(3), %st
  4fd62b:      	flds	0xc8(%esp)
  4fd632:      	fmul	%st(4), %st
  4fd634:      	fxch	%st(2)
  4fd636:      	fadds	0x8(%ebp,%eax)
  4fd63a:      	flds	0xbc(%esp)
  4fd641:      	fmul	%st(5), %st
  4fd643:      	fxch	%st(2)
  4fd645:      	fadds	0xc(%ebp,%eax)
  4fd649:      	fxch	%st(4)
  4fd64b:      	fmulp	%st, %st(5)
  4fd64d:      	fstps	0xa8(%esp)
  4fd654:      	fadds	0x10(%ebp,%eax)
  4fd658:      	fxch	%st(3)
  4fd65a:      	fadds	(%ebp,%eax)
  4fd65e:      	fxch	%st(2)
  4fd660:      	fstps	0xac(%esp)
  4fd667:      	fadds	0x14(%ebp,%eax)
  4fd66b:      	fxch	%st(2)
  4fd66d:      	fstps	0xb0(%esp)
  4fd674:      	fstps	0xa4(%esp)
  4fd67b:      	fstps	0xb4(%esp)
  4fd682:      	flds	0xd4(%esp)
  4fd689:      	faddl	0x632380
  4fd68f:      	flds	0xa4(%esp)
  4fd696:      	faddl	0x632380
  4fd69c:      	fxch	%st(1)
  4fd69e:      	fstpl	0x48(%esp)
  4fd6a2:      	fstpl	0x40(%esp)
  4fd6a6:      	movl	0x48(%esp), %edx
  4fd6aa:      	movl	0x40(%esp), %ebx
  4fd6ae:      	cmpl	%edx, %ebx
  4fd6b0:      	je	0x4fdad6 <.text+0xfcad6>
  4fd6b6:      	jl	0x4fd795 <.text+0xfc795>
  4fd6bc:      	flds	0xb4(%esp)
  4fd6c3:      	fsubs	0xe4(%esp)
  4fd6ca:      	flds	0xa4(%esp)
  4fd6d1:      	fsubs	0xd4(%esp)
  4fd6d8:      	flds	0xb0(%esp)
  4fd6df:      	fsubs	0xe0(%esp)
  4fd6e6:      	fxch	%st(1)
  4fd6e8:      	fdivrs	0x62c808
  4fd6ee:      	flds	0xac(%esp)
  4fd6f5:      	fsubs	0xdc(%esp)
  4fd6fc:      	fxch	%st(2)
  4fd6fe:      	fmul	%st(1), %st
  4fd700:      	flds	0xa8(%esp)
  4fd707:      	fsubs	0xd8(%esp)
  4fd70e:      	fxch	%st(3)
  4fd710:      	fmul	%st(2), %st
  4fd712:      	fxch	%st(1)
  4fd714:      	fstps	0x1c(%esp)
  4fd718:      	fxch	%st(1)
  4fd71a:      	fmul	%st, %st(2)
  4fd71c:      	fxch	%st(1)
  4fd71e:      	fstps	0x18(%esp)
  4fd722:      	fmulp	%st, %st(2)
  4fd724:      	fildl	0x48(%esp)
  4fd728:      	fxch	%st(1)
  4fd72a:      	fstps	0x20(%esp)
  4fd72e:      	fsubs	0xd4(%esp)
  4fd735:      	fld	%st(1)
  4fd737:      	faddl	0x632380
  4fd73d:      	fxch	%st(2)
  4fd73f:      	fmul	%st(1), %st
  4fd741:      	flds	0x1c(%esp)
  4fd745:      	fxch	%st(3)
  4fd747:      	fstpl	0x68(%esp)
  4fd74b:      	fadds	0xe4(%esp)
  4fd752:      	fxch	%st(2)
  4fd754:      	flds	0x18(%esp)
  4fd758:      	fmul	%st(2), %st
  4fd75a:      	fxch	%st(3)
  4fd75c:      	faddl	0x632380
  4fd762:      	fxch	%st(3)
  4fd764:      	flds	0x20(%esp)
  4fd768:      	fmul	%st(3), %st
  4fd76a:      	fxch	%st(4)
  4fd76c:      	fstpl	0x90(%esp)
  4fd773:      	fadds	0xdc(%esp)
  4fd77a:      	fxch	%st(2)
  4fd77c:      	fmulp	%st, %st(1)
  4fd77e:      	fxch	%st(2)
  4fd780:      	fadds	0xd8(%esp)
  4fd787:      	fxch	%st(2)
  4fd789:      	fadds	0xe0(%esp)
  4fd790:      	jmp	0x4fd873 <.text+0xfc873>
  4fd795:      	movl	%ebx, 0x48(%esp)
  4fd799:      	movl	%edx, %ebx
  4fd79b:      	movl	0x48(%esp), %edx
  4fd79f:      	flds	0xe4(%esp)
  4fd7a6:      	fsubs	0xb4(%esp)
  4fd7ad:      	flds	0xd4(%esp)
  4fd7b4:      	fsubs	0xa4(%esp)
  4fd7bb:      	flds	0xe0(%esp)
  4fd7c2:      	fsubs	0xb0(%esp)
  4fd7c9:      	fxch	%st(1)
  4fd7cb:      	fdivrs	0x62c808
  4fd7d1:      	flds	0xdc(%esp)
  4fd7d8:      	fsubs	0xac(%esp)
  4fd7df:      	fxch	%st(2)
  4fd7e1:      	fmul	%st(1), %st
  4fd7e3:      	flds	0xd8(%esp)
  4fd7ea:      	fsubs	0xa8(%esp)
  4fd7f1:      	fxch	%st(3)
  4fd7f3:      	fmul	%st(2), %st
  4fd7f5:      	fxch	%st(1)
  4fd7f7:      	fstps	0x1c(%esp)
  4fd7fb:      	fxch	%st(1)
  4fd7fd:      	fmul	%st, %st(2)
  4fd7ff:      	fxch	%st(1)
  4fd801:      	fstps	0x18(%esp)
  4fd805:      	fmulp	%st, %st(2)
  4fd807:      	fildl	0x48(%esp)
  4fd80b:      	fxch	%st(1)
  4fd80d:      	fstps	0x20(%esp)
  4fd811:      	fsubs	0xa4(%esp)
  4fd818:      	fld	%st(1)
  4fd81a:      	faddl	0x632380
  4fd820:      	fxch	%st(2)
  4fd822:      	fmul	%st(1), %st
  4fd824:      	flds	0x1c(%esp)
  4fd828:      	fxch	%st(3)
  4fd82a:      	fstpl	0x68(%esp)
  4fd82e:      	fadds	0xb4(%esp)
  4fd835:      	fxch	%st(2)
  4fd837:      	flds	0x18(%esp)
  4fd83b:      	fmul	%st(2), %st
  4fd83d:      	fxch	%st(3)
  4fd83f:      	faddl	0x632380
  4fd845:      	fxch	%st(3)
  4fd847:      	flds	0x20(%esp)
  4fd84b:      	fmul	%st(3), %st
  4fd84d:      	fxch	%st(4)
  4fd84f:      	fstpl	0x90(%esp)
  4fd856:      	fadds	0xac(%esp)
  4fd85d:      	fxch	%st(2)
  4fd85f:      	fmulp	%st, %st(1)
  4fd861:      	fxch	%st(2)
  4fd863:      	fadds	0xa8(%esp)
  4fd86a:      	fxch	%st(2)
  4fd86c:      	fadds	0xb0(%esp)
  4fd873:      	movl	0x68(%esp), %eax
  4fd877:      	movl	0x98(%esp), %edi
  4fd87e:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4fd883:      	subl	%edx, %ebx
  4fd885:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4fd88a:      	addl	%edx, %edi
  4fd88c:      	movl	%eax, 0x68(%esp)
  4fd890:      	flds	0x18(%esp)
  4fd894:      	fmuls	0x62c814
  4fd89a:      	flds	0x1c(%esp)
  4fd89e:      	fmuls	0x62c814
  4fd8a4:      	flds	0x20(%esp)
  4fd8a8:      	fmuls	0x62c814
  4fd8ae:      	fxch	%st(2)
  4fd8b0:      	fstps	0x24(%esp)
  4fd8b4:      	fstps	0x28(%esp)
  4fd8b8:      	fstps	0x2c(%esp)
  4fd8bc:      	fxch	%st(2)
  4fd8be:      	flds	0x62c80c
  4fd8c4:      	fdiv	%st(1), %st
  4fd8c6:      	fld	%st(3)
  4fd8c8:      	fmul	%st(1), %st
  4fd8ca:      	fld	%st(3)
  4fd8cc:      	fmulp	%st, %st(2)
  4fd8ce:      	faddl	0x632380
  4fd8d4:      	fxch	%st(1)
  4fd8d6:      	faddl	0x632380
  4fd8dc:      	fxch	%st(2)
  4fd8de:      	fadds	0x2c(%esp)
  4fd8e2:      	fxch	%st(1)
  4fd8e4:      	fstpl	0x78(%esp)
  4fd8e8:      	fxch	%st(1)
  4fd8ea:      	fstpl	0x70(%esp)
  4fd8ee:      	flds	0x62c80c
  4fd8f4:      	fdiv	%st(1), %st
  4fd8f6:      	decl	%ebx
  4fd8f7:      	jmp	0x4fd9d8 <.text+0xfc9d8>
  4fd8fc:      	flds	0x24(%esp)
  4fd900:      	faddp	%st, %st(3)
  4fd902:      	flds	0x28(%esp)
  4fd906:      	faddp	%st, %st(4)
  4fd908:      	fld	%st(2)
  4fd90a:      	fmul	%st(1), %st
  4fd90c:      	flds	0x2c(%esp)
  4fd910:      	fxch	%st(2)
  4fd912:      	fmul	%st(5), %st
  4fd914:      	fxch	%st(2)
  4fd916:      	faddp	%st, %st(3)
  4fd918:      	faddl	0x632380
  4fd91e:      	fxch	%st(1)
  4fd920:      	faddl	0x632380
  4fd926:      	fld	%st(2)
  4fd928:      	fxch	%st(2)
  4fd92a:      	fstpl	0x80(%esp)
  4fd931:      	fstpl	0x88(%esp)
  4fd938:      	fdivrs	0x62c80c
  4fd93e:      	movl	0x78(%esp), %ebp
  4fd942:      	movl	0x70(%esp), %esi
  4fd946:      	movl	0x88(%esp), %eax
  4fd94d:      	movl	0x80(%esp), %edx
  4fd954:      	subl	%ebp, %eax
  4fd956:      	subl	%esi, %edx
  4fd958:      	sarl	$0x4, %eax
  4fd95b:      	movl	%ebx, 0x8(%esp)
  4fd95f:      	sarl	$0x4, %edx
  4fd962:      	movl	0x90(%esp), %ebx
  4fd969:      	movl	%edx, 0x58(%esp)
  4fd96d:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4fd973:      	movl	%eax, 0x60(%esp)
  4fd977:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4fd97d:      	movl	%ebp, %eax
  4fd97f:      	movl	%esi, %edx
  4fd981:      	sarl	$0x9, %eax
  4fd984:      	movl	0x50(%esp), %ecx
  4fd988:      	sarl	$0x10, %edx
  4fd98b:      	andb	$-0x80, %al
  4fd98d:      	addl	%ecx, %eax
  4fd98f:      	movl	0x68(%esp), %ecx
  4fd993:      	addl	0x60(%esp), %ebp
  4fd997:      	addl	0x58(%esp), %esi
  4fd99b:      	movb	(%eax,%edx), %dl
  4fd99e:      	incl	%edi
  4fd99f:      	movb	%bh, %dh
  4fd9a1:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4fd9a7:      	movb	0xd1e480(%edx), %al
  4fd9ad:      	addl	%ecx, %ebx
  4fd9af:      	movb	%al, -0x1(%edi)
  4fd9b2:      	jge	0x4fd97d <.text+0xfc97d>
  4fd9b4:      	movl	%ebx, 0x90(%esp)
  4fd9bb:      	movl	0x8(%esp), %ebx
  4fd9bf:      	movl	0x80(%esp), %eax
  4fd9c6:      	movl	0x88(%esp), %edx
  4fd9cd:      	movl	%eax, 0x70(%esp)
  4fd9d1:      	movl	%edx, 0x78(%esp)
  4fd9d5:      	subl	$0x10, %ebx
  4fd9d8:      	cmpl	$0x10, %ebx
  4fd9db:      	jge	0x4fd8fc <.text+0xfc8fc>
  4fd9e1:      	movl	0x90(%esp), %eax
  4fd9e8:      	movl	%ebx, %ecx
  4fd9ea:      	decl	%ebx
  4fd9eb:      	movl	0x78(%esp), %ebp
  4fd9ef:      	shll	$0x11, %ebx
  4fd9f2:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4fd9f7:      	movl	0x70(%esp), %esi
  4fd9fb:      	orl	%eax, %ebx
  4fd9fd:      	cmpl	$0x0, %ecx
  4fda00:      	je	0x4fdab4 <.text+0xfcab4>
  4fda06:      	fxch	%st(1)
  4fda08:      	fsubs	0x2c(%esp)
  4fda0c:      	flds	0x20(%esp)
  4fda10:      	fmuls	0x62c810(,%ecx,8)
  4fda17:      	flds	0x18(%esp)
  4fda1b:      	fmuls	0x62c810(,%ecx,8)
  4fda22:      	flds	0x1c(%esp)
  4fda26:      	fmuls	0x62c810(,%ecx,8)
  4fda2d:      	fxch	%st(2)
  4fda2f:      	faddp	%st, %st(3)
  4fda31:      	faddp	%st, %st(4)
  4fda33:      	faddp	%st, %st(4)
  4fda35:      	fdivrs	0x62c80c
  4fda3b:      	fmul	%st, %st(2)
  4fda3d:      	fildl	0x70(%esp)
  4fda41:      	fxch	%st(1)
  4fda43:      	fmul	%st(4), %st
  4fda45:      	fildl	0x78(%esp)
  4fda49:      	fxch	%st(2)
  4fda4b:      	fsubrp	%st, %st(4)
  4fda4d:      	fsubp	%st, %st(1)
  4fda4f:      	fxch	%st(2)
  4fda51:      	fmuls	0x62c814(,%ecx,8)
  4fda58:      	fxch	%st(2)
  4fda5a:      	fmuls	0x62c814(,%ecx,8)
  4fda61:      	fxch	%st(2)
  4fda63:      	faddl	0x632380
  4fda69:      	fxch	%st(2)
  4fda6b:      	faddl	0x632380
  4fda71:      	fxch	%st(2)
  4fda73:      	fstl	0x58(%esp)
  4fda77:      	fxch	%st(2)
  4fda79:      	fstl	0x60(%esp)
  4fda7d:      	movl	%ebp, %eax
  4fda7f:      	movl	%esi, %edx
  4fda81:      	sarl	$0x9, %eax
  4fda84:      	movl	0x50(%esp), %ecx
  4fda88:      	sarl	$0x10, %edx
  4fda8b:      	andb	$-0x80, %al
  4fda8d:      	addl	%ecx, %eax
  4fda8f:      	movl	0x68(%esp), %ecx
  4fda93:      	addl	0x60(%esp), %ebp
  4fda97:      	addl	0x58(%esp), %esi
  4fda9b:      	movb	(%eax,%edx), %dl
  4fda9e:      	incl	%edi
  4fda9f:      	movb	%bh, %dh
  4fdaa1:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4fdaa7:      	movb	0xd1e480(%edx), %al
  4fdaad:      	addl	%ecx, %ebx
  4fdaaf:      	movb	%al, -0x1(%edi)
  4fdab2:      	jge	0x4fda7d <.text+0xfca7d>
  4fdab4:      	sarl	$0x9, %ebp
  4fdab7:      	xorl	%edx, %edx
  4fdab9:      	sarl	$0x10, %esi
  4fdabc:      	movl	0x50(%esp), %eax
  4fdac0:      	andl	$-0x80, %ebp
  4fdac3:      	movb	%bh, %dh
  4fdac5:      	addl	%ebp, %eax
  4fdac7:      	fcompp
  4fdac9:      	movb	(%eax,%esi), %dl
  4fdacc:      	fcompp
  4fdace:      	movb	0xd1e480(%edx), %al
  4fdad4:      	movb	%al, (%edi)
  4fdad6:      	flds	0xb4(%esp)
  4fdadd:      	fadds	0xc8(%esp)
  4fdae4:      	flds	0xa8(%esp)
  4fdaeb:      	fadds	0xc4(%esp)
  4fdaf2:      	flds	0xb0(%esp)
  4fdaf9:      	fadds	0xbc(%esp)
  4fdb00:      	flds	0xac(%esp)
  4fdb07:      	fadds	0xb8(%esp)
  4fdb0e:      	flds	0xa4(%esp)
  4fdb15:      	fadds	0xc0(%esp)
  4fdb1c:      	fxch	%st(3)
  4fdb1e:      	fstps	0xa8(%esp)
  4fdb25:      	fstps	0xac(%esp)
  4fdb2c:      	fstps	0xb0(%esp)
  4fdb33:      	fstps	0xa4(%esp)
  4fdb3a:      	fstps	0xb4(%esp)
  4fdb41:      	flds	0xe4(%esp)
  4fdb48:      	fadds	0xf8(%esp)
  4fdb4f:      	flds	0xd8(%esp)
  4fdb56:      	fadds	0xf4(%esp)
  4fdb5d:      	flds	0xe0(%esp)
  4fdb64:      	fadds	0xec(%esp)
  4fdb6b:      	flds	0xdc(%esp)
  4fdb72:      	fadds	0xe8(%esp)
  4fdb79:      	flds	0xd4(%esp)
  4fdb80:      	fadds	0xf0(%esp)
  4fdb87:      	fxch	%st(3)
  4fdb89:      	fstps	0xd8(%esp)
  4fdb90:      	fstps	0xdc(%esp)
  4fdb97:      	fstps	0xe0(%esp)
  4fdb9e:      	fstps	0xd4(%esp)
  4fdba5:      	fstps	0xe4(%esp)
  4fdbac:      	movl	0x98(%esp), %esi
  4fdbb3:      	movl	0xc(%esp), %eax
  4fdbb7:      	movl	(%esp), %ebp
  4fdbba:      	addl	%eax, %esi
  4fdbbc:      	movl	0x4(%esp), %edi
  4fdbc0:      	movl	%esi, 0x98(%esp)
  4fdbc7:      	incl	%edi
  4fdbc8:      	jmp	0x4fd41d <.text+0xfc41d>
  4fdbcd:      	addl	$0x700, %esp            # imm = 0x700
  4fdbd3:      	popl	%ebp
  4fdbd4:      	popl	%edi
  4fdbd5:      	popl	%esi
  4fdbd6:      	popl	%ebx
  4fdbd7:      	popl	%ebp
  4fdbd8:      	retl
