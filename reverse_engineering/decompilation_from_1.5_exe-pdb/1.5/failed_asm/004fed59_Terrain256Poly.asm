; Entry: 004fed59
; Name: Terrain256Poly
; Signature: void Terrain256Poly(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004ff666
; Reason: Exception while decompiling 004fed59: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004fed59 --stop-address=0x004ff666 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4fed59:      	pushl	%ebp
  4fed5a:      	movl	%esp, %ebp
  4fed5c:      	movl	0x14(%ebp), %ecx
  4fed5f:      	movzwl	(%ecx), %eax
  4fed62:      	pushl	%ebx
  4fed63:      	movl	$0x100, %edx            # imm = 0x100
  4fed68:      	pushl	%esi
  4fed69:      	pushl	%edi
  4fed6a:      	cmpw	%dx, %ax
  4fed6d:      	je	0x4fedaf <.text+0xfddaf>
  4fed6f:      	pushl	%ecx
  4fed70:      	pushl	0x10(%ebp)
  4fed73:      	addl	$-0x80, %edx
  4fed76:      	pushl	0xc(%ebp)
  4fed79:      	pushl	0x8(%ebp)
  4fed7c:      	cmpw	%dx, %ax
  4fed7f:      	jne	0x4fed88 <.text+0xfdd88>
  4fed81:      	calll	0x4fd31f <.text+0xfc31f>
  4fed86:      	jmp	0x4feda7 <.text+0xfdda7>
  4fed88:      	cmpw	$0x40, %ax
  4fed8c:      	jne	0x4fed95 <.text+0xfdd95>
  4fed8e:      	calll	0x4fdbd9 <.text+0xfcbd9>
  4fed93:      	jmp	0x4feda7 <.text+0xfdda7>
  4fed95:      	cmpw	$0x20, %ax
  4fed99:      	jne	0x4feda2 <.text+0xfdda2>
  4fed9b:      	calll	0x4fe493 <.text+0xfd493>
  4feda0:      	jmp	0x4feda7 <.text+0xfdda7>
  4feda2:      	calll	0x4f5020 <.text+0xf4020>
  4feda7:      	addl	$0x10, %esp
  4fedaa:      	jmp	0x4ff661 <.text+0xfe661>
  4fedaf:      	pushl	%ebp
  4fedb0:      	subl	$0x700, %esp            # imm = 0x700
  4fedb6:      	movl	0x14(%ebp), %ebx
  4fedb9:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fedbe:      	movl	0xc(%ebp), %esi
  4fedc1:      	movl	0x10(%ebp), %eax
  4fedc4:      	fildl	0x4(%ebx)
  4fedc7:      	movl	(%ebx), %ecx
  4fedc9:      	movl	%esi, (%esp)
  4fedcc:      	shll	$0x3, %eax
  4fedcf:      	leal	0x8(%ebx), %edi
  4fedd2:      	fildl	(%ebx)
  4fedd4:      	movl	%ecx, 0x10(%esp)
  4fedd8:      	leal	(%eax,%eax,2), %ecx
  4feddb:      	xorl	%eax, %eax
  4feddd:      	movl	%edi, 0x50(%esp)
  4fede1:      	flds	0x62c808
  4fede7:      	fsubs	0x14(%esi,%eax)
  4fedeb:      	flds	0x4(%esi,%eax)
  4fedef:      	faddl	0x632380
  4fedf5:      	fxch	%st(1)
  4fedf7:      	flds	0xc(%esi,%eax)
  4fedfb:      	fmul	%st(3), %st
  4fedfd:      	flds	0x10(%esi,%eax)
  4fee01:      	fmul	%st(5), %st
  4fee03:      	fxch	%st(3)
  4fee05:      	fstpl	0x38(%esp)
  4fee09:      	fxch	%st(1)
  4fee0b:      	fmuls	0x62c810
  4fee11:      	fxch	%st(2)
  4fee13:      	fstps	0x10(%esi,%eax)
  4fee17:      	fstps	0xc(%esi,%eax)
  4fee1b:      	fstps	0x14(%esi,%eax)
  4fee1f:      	movl	0x38(%esp), %edi
  4fee23:      	movl	%eax, 0x3e4(%esp,%eax)
  4fee2a:      	movl	%eax, 0x114(%esp,%eax)
  4fee31:      	movl	%edi, 0x400(%esp,%eax)
  4fee38:      	addl	$0x18, %eax
  4fee3b:      	cmpl	%edx, %edi
  4fee3d:      	jg	0x4fee43 <.text+0xfde43>
  4fee3f:      	movl	%eax, %ebx
  4fee41:      	movl	%edi, %edx
  4fee43:      	cmpl	%ecx, %eax
  4fee45:      	jne	0x4fede1 <.text+0xfdde1>
  4fee47:      	subl	$0x18, %ebx
  4fee4a:      	leal	-0x18(%eax), %ecx
  4fee4d:      	fcompp
  4fee4f:      	movl	$0x0, 0x3e4(%esp,%eax)
  4fee5a:      	movl	%ecx, 0xfc(%esp)
  4fee61:      	movl	0x8(%ebp), %edi
  4fee64:      	movl	%ebx, 0xcc(%esp)
  4fee6b:      	movl	%ebx, 0x9c(%esp)
  4fee72:      	movl	%ebx, 0xd0(%esp)
  4fee79:      	movl	%esi, %ebp
  4fee7b:      	movl	0x20(%edi), %eax
  4fee7e:      	movl	(%edi), %ecx
  4fee80:      	addl	%edx, %eax
  4fee82:      	movl	0x14(%edi), %esi
  4fee85:      	movl	0x1c(%edi), %edi
  4fee88:      	imull	%ecx
  4fee8a:      	addl	%edi, %esi
  4fee8c:      	movl	%ecx, 0xc(%esp)
  4fee90:      	addl	%eax, %esi
  4fee92:      	movl	0x400(%esp,%ebx), %edi
  4fee99:      	movl	%esi, 0x98(%esp)
  4feea0:      	movl	%ebx, 0xa0(%esp)
  4feea7:      	movl	0xd0(%esp), %ecx
  4feeae:      	movl	0x400(%esp,%ecx), %eax
  4feeb5:      	movl	%edi, 0x4(%esp)
  4feeb9:      	cmpl	%eax, %edi
  4feebb:      	jl	0x4fefe4 <.text+0xfdfe4>
  4feec1:      	movl	0x3fc(%esp,%ecx), %edx
  4feec8:      	movl	%ecx, %eax
  4feeca:      	movl	%edx, 0xd0(%esp)
  4feed1:      	cmpl	0x9c(%esp), %edx
  4feed8:      	je	0x4ff65a <.text+0xfe65a>
  4feede:      	movl	0x400(%esp,%edx), %esi
  4feee5:      	movl	%edx, %ecx
  4feee7:      	cmpl	%esi, %edi
  4feee9:      	jge	0x4feec1 <.text+0xfdec1>
  4feeeb:      	flds	0x14(%ebp,%edx)
  4feeef:      	fsubs	0x14(%ebp,%eax)
  4feef3:      	flds	0x4(%ebp,%edx)
  4feef7:      	fsubs	0x4(%ebp,%eax)
  4feefb:      	flds	0x10(%ebp,%edx)
  4feeff:      	fsubs	0x10(%ebp,%eax)
  4fef03:      	fxch	%st(1)
  4fef05:      	fdivrs	0x62c808
  4fef0b:      	flds	0xc(%ebp,%edx)
  4fef0f:      	fsubs	0xc(%ebp,%eax)
  4fef13:      	fxch	%st(1)
  4fef15:      	fmul	%st, %st(2)
  4fef17:      	flds	0x8(%ebp,%edx)
  4fef1b:      	fsubs	0x8(%ebp,%eax)
  4fef1f:      	fxch	%st(2)
  4fef21:      	fmul	%st(1), %st
  4fef23:      	flds	(%ebp,%edx)
  4fef27:      	fsubs	(%ebp,%eax)
  4fef2b:      	fxch	%st(3)
  4fef2d:      	fmul	%st(2), %st
  4fef2f:      	fxch	%st(4)
  4fef31:      	fstps	0xec(%esp)
  4fef38:      	fstps	0xe8(%esp)
  4fef3f:      	fmul	%st, %st(3)
  4fef41:      	flds	0x4(%ebp,%eax)
  4fef45:      	faddl	0x632380
  4fef4b:      	fxch	%st(2)
  4fef4d:      	fmulp	%st, %st(1)
  4fef4f:      	fxch	%st(3)
  4fef51:      	fstps	0xf8(%esp)
  4fef58:      	fstpl	0x38(%esp)
  4fef5c:      	fstps	0xf4(%esp)
  4fef63:      	fildl	0x38(%esp)
  4fef67:      	fxch	%st(1)
  4fef69:      	fstps	0xf0(%esp)
  4fef70:      	fsubs	0x4(%ebp,%eax)
  4fef74:      	flds	0xf0(%esp)
  4fef7b:      	flds	0xf4(%esp)
  4fef82:      	fmul	%st(2), %st
  4fef84:      	flds	0xe8(%esp)
  4fef8b:      	fmul	%st(3), %st
  4fef8d:      	flds	0xf8(%esp)
  4fef94:      	fmul	%st(4), %st
  4fef96:      	fxch	%st(2)
  4fef98:      	fadds	0x8(%ebp,%eax)
  4fef9c:      	flds	0xec(%esp)
  4fefa3:      	fmul	%st(5), %st
  4fefa5:      	fxch	%st(2)
  4fefa7:      	fadds	0xc(%ebp,%eax)
  4fefab:      	fxch	%st(4)
  4fefad:      	fmulp	%st, %st(5)
  4fefaf:      	fstps	0xd8(%esp)
  4fefb6:      	fadds	0x10(%ebp,%eax)
  4fefba:      	fxch	%st(3)
  4fefbc:      	fadds	(%ebp,%eax)
  4fefc0:      	fxch	%st(2)
  4fefc2:      	fstps	0xdc(%esp)
  4fefc9:      	fadds	0x14(%ebp,%eax)
  4fefcd:      	fxch	%st(2)
  4fefcf:      	fstps	0xe0(%esp)
  4fefd6:      	fstps	0xd4(%esp)
  4fefdd:      	fstps	0xe4(%esp)
  4fefe4:      	movl	0xa0(%esp), %ecx
  4fefeb:      	cmpl	0x400(%esp,%ecx), %edi
  4feff2:      	jl	0x4ff10c <.text+0xfe10c>
  4feff8:      	movl	0xfc(%esp,%ecx), %edx
  4fefff:      	movl	%ecx, %eax
  4ff001:      	movl	%edx, 0xa0(%esp)
  4ff008:      	movl	%edx, %ecx
  4ff00a:      	cmpl	0x400(%esp,%edx), %edi
  4ff011:      	jge	0x4feff8 <.text+0xfdff8>
  4ff013:      	flds	0x14(%ebp,%edx)
  4ff017:      	fsubs	0x14(%ebp,%eax)
  4ff01b:      	flds	0x4(%ebp,%edx)
  4ff01f:      	fsubs	0x4(%ebp,%eax)
  4ff023:      	flds	0x10(%ebp,%edx)
  4ff027:      	fsubs	0x10(%ebp,%eax)
  4ff02b:      	fxch	%st(1)
  4ff02d:      	fdivrs	0x62c808
  4ff033:      	flds	0xc(%ebp,%edx)
  4ff037:      	fsubs	0xc(%ebp,%eax)
  4ff03b:      	fxch	%st(1)
  4ff03d:      	fmul	%st, %st(2)
  4ff03f:      	flds	0x8(%ebp,%edx)
  4ff043:      	fsubs	0x8(%ebp,%eax)
  4ff047:      	fxch	%st(2)
  4ff049:      	fmul	%st(1), %st
  4ff04b:      	flds	(%ebp,%edx)
  4ff04f:      	fsubs	(%ebp,%eax)
  4ff053:      	fxch	%st(3)
  4ff055:      	fmul	%st(2), %st
  4ff057:      	fxch	%st(4)
  4ff059:      	fstps	0xbc(%esp)
  4ff060:      	fstps	0xb8(%esp)
  4ff067:      	fmul	%st, %st(3)
  4ff069:      	flds	0x4(%ebp,%eax)
  4ff06d:      	faddl	0x632380
  4ff073:      	fxch	%st(2)
  4ff075:      	fmulp	%st, %st(1)
  4ff077:      	fxch	%st(3)
  4ff079:      	fstps	0xc8(%esp)
  4ff080:      	fstpl	0x38(%esp)
  4ff084:      	fstps	0xc4(%esp)
  4ff08b:      	fildl	0x38(%esp)
  4ff08f:      	fxch	%st(1)
  4ff091:      	fstps	0xc0(%esp)
  4ff098:      	fsubs	0x4(%ebp,%eax)
  4ff09c:      	flds	0xc0(%esp)
  4ff0a3:      	flds	0xc4(%esp)
  4ff0aa:      	fmul	%st(2), %st
  4ff0ac:      	flds	0xb8(%esp)
  4ff0b3:      	fmul	%st(3), %st
  4ff0b5:      	flds	0xc8(%esp)
  4ff0bc:      	fmul	%st(4), %st
  4ff0be:      	fxch	%st(2)
  4ff0c0:      	fadds	0x8(%ebp,%eax)
  4ff0c4:      	flds	0xbc(%esp)
  4ff0cb:      	fmul	%st(5), %st
  4ff0cd:      	fxch	%st(2)
  4ff0cf:      	fadds	0xc(%ebp,%eax)
  4ff0d3:      	fxch	%st(4)
  4ff0d5:      	fmulp	%st, %st(5)
  4ff0d7:      	fstps	0xa8(%esp)
  4ff0de:      	fadds	0x10(%ebp,%eax)
  4ff0e2:      	fxch	%st(3)
  4ff0e4:      	fadds	(%ebp,%eax)
  4ff0e8:      	fxch	%st(2)
  4ff0ea:      	fstps	0xac(%esp)
  4ff0f1:      	fadds	0x14(%ebp,%eax)
  4ff0f5:      	fxch	%st(2)
  4ff0f7:      	fstps	0xb0(%esp)
  4ff0fe:      	fstps	0xa4(%esp)
  4ff105:      	fstps	0xb4(%esp)
  4ff10c:      	flds	0xd4(%esp)
  4ff113:      	faddl	0x632380
  4ff119:      	flds	0xa4(%esp)
  4ff120:      	faddl	0x632380
  4ff126:      	fxch	%st(1)
  4ff128:      	fstpl	0x48(%esp)
  4ff12c:      	fstpl	0x40(%esp)
  4ff130:      	movl	0x48(%esp), %edx
  4ff134:      	movl	0x40(%esp), %ebx
  4ff138:      	cmpl	%edx, %ebx
  4ff13a:      	je	0x4ff563 <.text+0xfe563>
  4ff140:      	jl	0x4ff21f <.text+0xfe21f>
  4ff146:      	flds	0xb4(%esp)
  4ff14d:      	fsubs	0xe4(%esp)
  4ff154:      	flds	0xa4(%esp)
  4ff15b:      	fsubs	0xd4(%esp)
  4ff162:      	flds	0xb0(%esp)
  4ff169:      	fsubs	0xe0(%esp)
  4ff170:      	fxch	%st(1)
  4ff172:      	fdivrs	0x62c808
  4ff178:      	flds	0xac(%esp)
  4ff17f:      	fsubs	0xdc(%esp)
  4ff186:      	fxch	%st(2)
  4ff188:      	fmul	%st(1), %st
  4ff18a:      	flds	0xa8(%esp)
  4ff191:      	fsubs	0xd8(%esp)
  4ff198:      	fxch	%st(3)
  4ff19a:      	fmul	%st(2), %st
  4ff19c:      	fxch	%st(1)
  4ff19e:      	fstps	0x1c(%esp)
  4ff1a2:      	fxch	%st(1)
  4ff1a4:      	fmul	%st, %st(2)
  4ff1a6:      	fxch	%st(1)
  4ff1a8:      	fstps	0x18(%esp)
  4ff1ac:      	fmulp	%st, %st(2)
  4ff1ae:      	fildl	0x48(%esp)
  4ff1b2:      	fxch	%st(1)
  4ff1b4:      	fstps	0x20(%esp)
  4ff1b8:      	fsubs	0xd4(%esp)
  4ff1bf:      	fld	%st(1)
  4ff1c1:      	faddl	0x632380
  4ff1c7:      	fxch	%st(2)
  4ff1c9:      	fmul	%st(1), %st
  4ff1cb:      	flds	0x1c(%esp)
  4ff1cf:      	fxch	%st(3)
  4ff1d1:      	fstpl	0x68(%esp)
  4ff1d5:      	fadds	0xe4(%esp)
  4ff1dc:      	fxch	%st(2)
  4ff1de:      	flds	0x18(%esp)
  4ff1e2:      	fmul	%st(2), %st
  4ff1e4:      	fxch	%st(3)
  4ff1e6:      	faddl	0x632380
  4ff1ec:      	fxch	%st(3)
  4ff1ee:      	flds	0x20(%esp)
  4ff1f2:      	fmul	%st(3), %st
  4ff1f4:      	fxch	%st(4)
  4ff1f6:      	fstpl	0x90(%esp)
  4ff1fd:      	fadds	0xdc(%esp)
  4ff204:      	fxch	%st(2)
  4ff206:      	fmulp	%st, %st(1)
  4ff208:      	fxch	%st(2)
  4ff20a:      	fadds	0xd8(%esp)
  4ff211:      	fxch	%st(2)
  4ff213:      	fadds	0xe0(%esp)
  4ff21a:      	jmp	0x4ff2fd <.text+0xfe2fd>
  4ff21f:      	movl	%ebx, 0x48(%esp)
  4ff223:      	movl	%edx, %ebx
  4ff225:      	movl	0x48(%esp), %edx
  4ff229:      	flds	0xe4(%esp)
  4ff230:      	fsubs	0xb4(%esp)
  4ff237:      	flds	0xd4(%esp)
  4ff23e:      	fsubs	0xa4(%esp)
  4ff245:      	flds	0xe0(%esp)
  4ff24c:      	fsubs	0xb0(%esp)
  4ff253:      	fxch	%st(1)
  4ff255:      	fdivrs	0x62c808
  4ff25b:      	flds	0xdc(%esp)
  4ff262:      	fsubs	0xac(%esp)
  4ff269:      	fxch	%st(2)
  4ff26b:      	fmul	%st(1), %st
  4ff26d:      	flds	0xd8(%esp)
  4ff274:      	fsubs	0xa8(%esp)
  4ff27b:      	fxch	%st(3)
  4ff27d:      	fmul	%st(2), %st
  4ff27f:      	fxch	%st(1)
  4ff281:      	fstps	0x1c(%esp)
  4ff285:      	fxch	%st(1)
  4ff287:      	fmul	%st, %st(2)
  4ff289:      	fxch	%st(1)
  4ff28b:      	fstps	0x18(%esp)
  4ff28f:      	fmulp	%st, %st(2)
  4ff291:      	fildl	0x48(%esp)
  4ff295:      	fxch	%st(1)
  4ff297:      	fstps	0x20(%esp)
  4ff29b:      	fsubs	0xa4(%esp)
  4ff2a2:      	fld	%st(1)
  4ff2a4:      	faddl	0x632380
  4ff2aa:      	fxch	%st(2)
  4ff2ac:      	fmul	%st(1), %st
  4ff2ae:      	flds	0x1c(%esp)
  4ff2b2:      	fxch	%st(3)
  4ff2b4:      	fstpl	0x68(%esp)
  4ff2b8:      	fadds	0xb4(%esp)
  4ff2bf:      	fxch	%st(2)
  4ff2c1:      	flds	0x18(%esp)
  4ff2c5:      	fmul	%st(2), %st
  4ff2c7:      	fxch	%st(3)
  4ff2c9:      	faddl	0x632380
  4ff2cf:      	fxch	%st(3)
  4ff2d1:      	flds	0x20(%esp)
  4ff2d5:      	fmul	%st(3), %st
  4ff2d7:      	fxch	%st(4)
  4ff2d9:      	fstpl	0x90(%esp)
  4ff2e0:      	fadds	0xac(%esp)
  4ff2e7:      	fxch	%st(2)
  4ff2e9:      	fmulp	%st, %st(1)
  4ff2eb:      	fxch	%st(2)
  4ff2ed:      	fadds	0xa8(%esp)
  4ff2f4:      	fxch	%st(2)
  4ff2f6:      	fadds	0xb0(%esp)
  4ff2fd:      	movl	0x68(%esp), %eax
  4ff301:      	movl	0x98(%esp), %edi
  4ff308:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4ff30d:      	subl	%edx, %ebx
  4ff30f:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4ff314:      	addl	%edx, %edi
  4ff316:      	movl	%eax, 0x68(%esp)
  4ff31a:      	flds	0x18(%esp)
  4ff31e:      	fmuls	0x62c814
  4ff324:      	flds	0x1c(%esp)
  4ff328:      	fmuls	0x62c814
  4ff32e:      	flds	0x20(%esp)
  4ff332:      	fmuls	0x62c814
  4ff338:      	fxch	%st(2)
  4ff33a:      	fstps	0x24(%esp)
  4ff33e:      	fstps	0x28(%esp)
  4ff342:      	fstps	0x2c(%esp)
  4ff346:      	fxch	%st(2)
  4ff348:      	flds	0x62c80c
  4ff34e:      	fdiv	%st(1), %st
  4ff350:      	fld	%st(3)
  4ff352:      	fmul	%st(1), %st
  4ff354:      	fld	%st(3)
  4ff356:      	fmulp	%st, %st(2)
  4ff358:      	faddl	0x632380
  4ff35e:      	fxch	%st(1)
  4ff360:      	faddl	0x632380
  4ff366:      	fxch	%st(2)
  4ff368:      	fadds	0x2c(%esp)
  4ff36c:      	fxch	%st(1)
  4ff36e:      	fstpl	0x78(%esp)
  4ff372:      	fxch	%st(1)
  4ff374:      	fstpl	0x70(%esp)
  4ff378:      	flds	0x62c80c
  4ff37e:      	fdiv	%st(1), %st
  4ff380:      	decl	%ebx
  4ff381:      	jmp	0x4ff462 <.text+0xfe462>
  4ff386:      	flds	0x24(%esp)
  4ff38a:      	faddp	%st, %st(3)
  4ff38c:      	flds	0x28(%esp)
  4ff390:      	faddp	%st, %st(4)
  4ff392:      	fld	%st(2)
  4ff394:      	fmul	%st(1), %st
  4ff396:      	flds	0x2c(%esp)
  4ff39a:      	fxch	%st(2)
  4ff39c:      	fmul	%st(5), %st
  4ff39e:      	fxch	%st(2)
  4ff3a0:      	faddp	%st, %st(3)
  4ff3a2:      	faddl	0x632380
  4ff3a8:      	fxch	%st(1)
  4ff3aa:      	faddl	0x632380
  4ff3b0:      	fld	%st(2)
  4ff3b2:      	fxch	%st(2)
  4ff3b4:      	fstpl	0x80(%esp)
  4ff3bb:      	fstpl	0x88(%esp)
  4ff3c2:      	fdivrs	0x62c80c
  4ff3c8:      	movl	0x78(%esp), %ebp
  4ff3cc:      	movl	0x70(%esp), %esi
  4ff3d0:      	movl	0x88(%esp), %eax
  4ff3d7:      	movl	0x80(%esp), %edx
  4ff3de:      	subl	%ebp, %eax
  4ff3e0:      	subl	%esi, %edx
  4ff3e2:      	sarl	$0x4, %eax
  4ff3e5:      	movl	%ebx, 0x8(%esp)
  4ff3e9:      	sarl	$0x4, %edx
  4ff3ec:      	movl	0x90(%esp), %ebx
  4ff3f3:      	movl	%edx, 0x58(%esp)
  4ff3f7:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4ff3fd:      	movl	%eax, 0x60(%esp)
  4ff401:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4ff407:      	movl	%ebp, %eax
  4ff409:      	movl	%esi, %edx
  4ff40b:      	sarl	$0x8, %eax
  4ff40e:      	movl	0x50(%esp), %ecx
  4ff412:      	sarl	$0x10, %edx
  4ff415:      	xorb	%al, %al
  4ff417:      	addl	%ecx, %eax
  4ff419:      	movl	0x68(%esp), %ecx
  4ff41d:      	addl	0x60(%esp), %ebp
  4ff421:      	addl	0x58(%esp), %esi
  4ff425:      	movb	(%eax,%edx), %dl
  4ff428:      	incl	%edi
  4ff429:      	movb	%bh, %dh
  4ff42b:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4ff431:      	movb	0xd1e480(%edx), %al
  4ff437:      	addl	%ecx, %ebx
  4ff439:      	movb	%al, -0x1(%edi)
  4ff43c:      	jge	0x4ff407 <.text+0xfe407>
  4ff43e:      	movl	%ebx, 0x90(%esp)
  4ff445:      	movl	0x8(%esp), %ebx
  4ff449:      	movl	0x80(%esp), %eax
  4ff450:      	movl	0x88(%esp), %edx
  4ff457:      	movl	%eax, 0x70(%esp)
  4ff45b:      	movl	%edx, 0x78(%esp)
  4ff45f:      	subl	$0x10, %ebx
  4ff462:      	cmpl	$0x10, %ebx
  4ff465:      	jge	0x4ff386 <.text+0xfe386>
  4ff46b:      	movl	0x90(%esp), %eax
  4ff472:      	movl	%ebx, %ecx
  4ff474:      	decl	%ebx
  4ff475:      	movl	0x78(%esp), %ebp
  4ff479:      	shll	$0x11, %ebx
  4ff47c:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4ff481:      	movl	0x70(%esp), %esi
  4ff485:      	orl	%eax, %ebx
  4ff487:      	cmpl	$0x0, %ecx
  4ff48a:      	je	0x4ff53e <.text+0xfe53e>
  4ff490:      	fxch	%st(1)
  4ff492:      	fsubs	0x2c(%esp)
  4ff496:      	flds	0x20(%esp)
  4ff49a:      	fmuls	0x62c810(,%ecx,8)
  4ff4a1:      	flds	0x18(%esp)
  4ff4a5:      	fmuls	0x62c810(,%ecx,8)
  4ff4ac:      	flds	0x1c(%esp)
  4ff4b0:      	fmuls	0x62c810(,%ecx,8)
  4ff4b7:      	fxch	%st(2)
  4ff4b9:      	faddp	%st, %st(3)
  4ff4bb:      	faddp	%st, %st(4)
  4ff4bd:      	faddp	%st, %st(4)
  4ff4bf:      	fdivrs	0x62c80c
  4ff4c5:      	fmul	%st, %st(2)
  4ff4c7:      	fildl	0x70(%esp)
  4ff4cb:      	fxch	%st(1)
  4ff4cd:      	fmul	%st(4), %st
  4ff4cf:      	fildl	0x78(%esp)
  4ff4d3:      	fxch	%st(2)
  4ff4d5:      	fsubrp	%st, %st(4)
  4ff4d7:      	fsubp	%st, %st(1)
  4ff4d9:      	fxch	%st(2)
  4ff4db:      	fmuls	0x62c814(,%ecx,8)
  4ff4e2:      	fxch	%st(2)
  4ff4e4:      	fmuls	0x62c814(,%ecx,8)
  4ff4eb:      	fxch	%st(2)
  4ff4ed:      	faddl	0x632380
  4ff4f3:      	fxch	%st(2)
  4ff4f5:      	faddl	0x632380
  4ff4fb:      	fxch	%st(2)
  4ff4fd:      	fstl	0x58(%esp)
  4ff501:      	fxch	%st(2)
  4ff503:      	fstl	0x60(%esp)
  4ff507:      	movl	%ebp, %eax
  4ff509:      	movl	%esi, %edx
  4ff50b:      	sarl	$0x8, %eax
  4ff50e:      	movl	0x50(%esp), %ecx
  4ff512:      	sarl	$0x10, %edx
  4ff515:      	xorb	%al, %al
  4ff517:      	addl	%ecx, %eax
  4ff519:      	movl	0x68(%esp), %ecx
  4ff51d:      	addl	0x60(%esp), %ebp
  4ff521:      	addl	0x58(%esp), %esi
  4ff525:      	movb	(%eax,%edx), %dl
  4ff528:      	incl	%edi
  4ff529:      	movb	%bh, %dh
  4ff52b:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4ff531:      	movb	0xd1e480(%edx), %al
  4ff537:      	addl	%ecx, %ebx
  4ff539:      	movb	%al, -0x1(%edi)
  4ff53c:      	jge	0x4ff507 <.text+0xfe507>
  4ff53e:      	sarl	$0x8, %ebp
  4ff541:      	xorl	%edx, %edx
  4ff543:      	sarl	$0x10, %esi
  4ff546:      	movl	0x50(%esp), %eax
  4ff54a:      	andl	$0xffffff00, %ebp       # imm = 0xFFFFFF00
  4ff550:      	movb	%bh, %dh
  4ff552:      	addl	%ebp, %eax
  4ff554:      	fcompp
  4ff556:      	movb	(%eax,%esi), %dl
  4ff559:      	fcompp
  4ff55b:      	movb	0xd1e480(%edx), %al
  4ff561:      	movb	%al, (%edi)
  4ff563:      	flds	0xb4(%esp)
  4ff56a:      	fadds	0xc8(%esp)
  4ff571:      	flds	0xa8(%esp)
  4ff578:      	fadds	0xc4(%esp)
  4ff57f:      	flds	0xb0(%esp)
  4ff586:      	fadds	0xbc(%esp)
  4ff58d:      	flds	0xac(%esp)
  4ff594:      	fadds	0xb8(%esp)
  4ff59b:      	flds	0xa4(%esp)
  4ff5a2:      	fadds	0xc0(%esp)
  4ff5a9:      	fxch	%st(3)
  4ff5ab:      	fstps	0xa8(%esp)
  4ff5b2:      	fstps	0xac(%esp)
  4ff5b9:      	fstps	0xb0(%esp)
  4ff5c0:      	fstps	0xa4(%esp)
  4ff5c7:      	fstps	0xb4(%esp)
  4ff5ce:      	flds	0xe4(%esp)
  4ff5d5:      	fadds	0xf8(%esp)
  4ff5dc:      	flds	0xd8(%esp)
  4ff5e3:      	fadds	0xf4(%esp)
  4ff5ea:      	flds	0xe0(%esp)
  4ff5f1:      	fadds	0xec(%esp)
  4ff5f8:      	flds	0xdc(%esp)
  4ff5ff:      	fadds	0xe8(%esp)
  4ff606:      	flds	0xd4(%esp)
  4ff60d:      	fadds	0xf0(%esp)
  4ff614:      	fxch	%st(3)
  4ff616:      	fstps	0xd8(%esp)
  4ff61d:      	fstps	0xdc(%esp)
  4ff624:      	fstps	0xe0(%esp)
  4ff62b:      	fstps	0xd4(%esp)
  4ff632:      	fstps	0xe4(%esp)
  4ff639:      	movl	0x98(%esp), %esi
  4ff640:      	movl	0xc(%esp), %eax
  4ff644:      	movl	(%esp), %ebp
  4ff647:      	addl	%eax, %esi
  4ff649:      	movl	0x4(%esp), %edi
  4ff64d:      	movl	%esi, 0x98(%esp)
  4ff654:      	incl	%edi
  4ff655:      	jmp	0x4feea7 <.text+0xfdea7>
  4ff65a:      	addl	$0x700, %esp            # imm = 0x700
  4ff660:      	popl	%ebp
  4ff661:      	popl	%edi
  4ff662:      	popl	%esi
  4ff663:      	popl	%ebx
  4ff664:      	popl	%ebp
  4ff665:      	retl
