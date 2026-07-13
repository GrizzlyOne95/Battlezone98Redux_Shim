; Entry: 004fdbd9
; Name: Terrain_64Poly
; Signature: void Terrain_64Poly(_GRAPHIC_BUFFER * param_1, POINT_3D * param_2, long param_3, POLYGON_SKIN param_4)
; Stop: 0x004fe493
; Reason: Exception while decompiling 004fdbd9: process: timeout 
; Command: C:\Program Files\LLVM\bin\llvm-objdump.EXE -d --no-show-raw-insn --start-address=0x004fdbd9 --stop-address=0x004fe493 C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe


C:\Users\istuart\Downloads\bzone15227\extracted\bzone.exe:	file format coff-i386

Disassembly of section .text:

00401000 <.text>:
  4fdbd9:      	pushl	%ebp
  4fdbda:      	movl	%esp, %ebp
  4fdbdc:      	pushl	%ebx
  4fdbdd:      	pushl	%esi
  4fdbde:      	pushl	%edi
  4fdbdf:      	pushl	%ebp
  4fdbe0:      	subl	$0x700, %esp            # imm = 0x700
  4fdbe6:      	movl	0x14(%ebp), %ebx
  4fdbe9:      	movl	$0x186a0, %edx          # imm = 0x186A0
  4fdbee:      	movl	0xc(%ebp), %esi
  4fdbf1:      	movl	0x10(%ebp), %eax
  4fdbf4:      	fildl	0x4(%ebx)
  4fdbf7:      	movl	(%ebx), %ecx
  4fdbf9:      	movl	%esi, (%esp)
  4fdbfc:      	shll	$0x3, %eax
  4fdbff:      	leal	0x8(%ebx), %edi
  4fdc02:      	fildl	(%ebx)
  4fdc04:      	movl	%ecx, 0x10(%esp)
  4fdc08:      	leal	(%eax,%eax,2), %ecx
  4fdc0b:      	xorl	%eax, %eax
  4fdc0d:      	movl	%edi, 0x50(%esp)
  4fdc11:      	flds	0x62c808
  4fdc17:      	fsubs	0x14(%esi,%eax)
  4fdc1b:      	flds	0x4(%esi,%eax)
  4fdc1f:      	faddl	0x632380
  4fdc25:      	fxch	%st(1)
  4fdc27:      	flds	0xc(%esi,%eax)
  4fdc2b:      	fmul	%st(3), %st
  4fdc2d:      	flds	0x10(%esi,%eax)
  4fdc31:      	fmul	%st(5), %st
  4fdc33:      	fxch	%st(3)
  4fdc35:      	fstpl	0x38(%esp)
  4fdc39:      	fxch	%st(1)
  4fdc3b:      	fmuls	0x62c810
  4fdc41:      	fxch	%st(2)
  4fdc43:      	fstps	0x10(%esi,%eax)
  4fdc47:      	fstps	0xc(%esi,%eax)
  4fdc4b:      	fstps	0x14(%esi,%eax)
  4fdc4f:      	movl	0x38(%esp), %edi
  4fdc53:      	movl	%eax, 0x3e4(%esp,%eax)
  4fdc5a:      	movl	%eax, 0x114(%esp,%eax)
  4fdc61:      	movl	%edi, 0x400(%esp,%eax)
  4fdc68:      	addl	$0x18, %eax
  4fdc6b:      	cmpl	%edx, %edi
  4fdc6d:      	jg	0x4fdc73 <.text+0xfcc73>
  4fdc6f:      	movl	%eax, %ebx
  4fdc71:      	movl	%edi, %edx
  4fdc73:      	cmpl	%ecx, %eax
  4fdc75:      	jne	0x4fdc11 <.text+0xfcc11>
  4fdc77:      	subl	$0x18, %ebx
  4fdc7a:      	leal	-0x18(%eax), %ecx
  4fdc7d:      	fcompp
  4fdc7f:      	movl	$0x0, 0x3e4(%esp,%eax)
  4fdc8a:      	movl	%ecx, 0xfc(%esp)
  4fdc91:      	movl	0x8(%ebp), %edi
  4fdc94:      	movl	%ebx, 0xcc(%esp)
  4fdc9b:      	movl	%ebx, 0x9c(%esp)
  4fdca2:      	movl	%ebx, 0xd0(%esp)
  4fdca9:      	movl	%esi, %ebp
  4fdcab:      	movl	0x20(%edi), %eax
  4fdcae:      	movl	(%edi), %ecx
  4fdcb0:      	addl	%edx, %eax
  4fdcb2:      	movl	0x14(%edi), %esi
  4fdcb5:      	movl	0x1c(%edi), %edi
  4fdcb8:      	imull	%ecx
  4fdcba:      	addl	%edi, %esi
  4fdcbc:      	movl	%ecx, 0xc(%esp)
  4fdcc0:      	addl	%eax, %esi
  4fdcc2:      	movl	0x400(%esp,%ebx), %edi
  4fdcc9:      	movl	%esi, 0x98(%esp)
  4fdcd0:      	movl	%ebx, 0xa0(%esp)
  4fdcd7:      	movl	0xd0(%esp), %ecx
  4fdcde:      	movl	0x400(%esp,%ecx), %eax
  4fdce5:      	movl	%edi, 0x4(%esp)
  4fdce9:      	cmpl	%eax, %edi
  4fdceb:      	jl	0x4fde14 <.text+0xfce14>
  4fdcf1:      	movl	0x3fc(%esp,%ecx), %edx
  4fdcf8:      	movl	%ecx, %eax
  4fdcfa:      	movl	%edx, 0xd0(%esp)
  4fdd01:      	cmpl	0x9c(%esp), %edx
  4fdd08:      	je	0x4fe487 <.text+0xfd487>
  4fdd0e:      	movl	0x400(%esp,%edx), %esi
  4fdd15:      	movl	%edx, %ecx
  4fdd17:      	cmpl	%esi, %edi
  4fdd19:      	jge	0x4fdcf1 <.text+0xfccf1>
  4fdd1b:      	flds	0x14(%ebp,%edx)
  4fdd1f:      	fsubs	0x14(%ebp,%eax)
  4fdd23:      	flds	0x4(%ebp,%edx)
  4fdd27:      	fsubs	0x4(%ebp,%eax)
  4fdd2b:      	flds	0x10(%ebp,%edx)
  4fdd2f:      	fsubs	0x10(%ebp,%eax)
  4fdd33:      	fxch	%st(1)
  4fdd35:      	fdivrs	0x62c808
  4fdd3b:      	flds	0xc(%ebp,%edx)
  4fdd3f:      	fsubs	0xc(%ebp,%eax)
  4fdd43:      	fxch	%st(1)
  4fdd45:      	fmul	%st, %st(2)
  4fdd47:      	flds	0x8(%ebp,%edx)
  4fdd4b:      	fsubs	0x8(%ebp,%eax)
  4fdd4f:      	fxch	%st(2)
  4fdd51:      	fmul	%st(1), %st
  4fdd53:      	flds	(%ebp,%edx)
  4fdd57:      	fsubs	(%ebp,%eax)
  4fdd5b:      	fxch	%st(3)
  4fdd5d:      	fmul	%st(2), %st
  4fdd5f:      	fxch	%st(4)
  4fdd61:      	fstps	0xec(%esp)
  4fdd68:      	fstps	0xe8(%esp)
  4fdd6f:      	fmul	%st, %st(3)
  4fdd71:      	flds	0x4(%ebp,%eax)
  4fdd75:      	faddl	0x632380
  4fdd7b:      	fxch	%st(2)
  4fdd7d:      	fmulp	%st, %st(1)
  4fdd7f:      	fxch	%st(3)
  4fdd81:      	fstps	0xf8(%esp)
  4fdd88:      	fstpl	0x38(%esp)
  4fdd8c:      	fstps	0xf4(%esp)
  4fdd93:      	fildl	0x38(%esp)
  4fdd97:      	fxch	%st(1)
  4fdd99:      	fstps	0xf0(%esp)
  4fdda0:      	fsubs	0x4(%ebp,%eax)
  4fdda4:      	flds	0xf0(%esp)
  4fddab:      	flds	0xf4(%esp)
  4fddb2:      	fmul	%st(2), %st
  4fddb4:      	flds	0xe8(%esp)
  4fddbb:      	fmul	%st(3), %st
  4fddbd:      	flds	0xf8(%esp)
  4fddc4:      	fmul	%st(4), %st
  4fddc6:      	fxch	%st(2)
  4fddc8:      	fadds	0x8(%ebp,%eax)
  4fddcc:      	flds	0xec(%esp)
  4fddd3:      	fmul	%st(5), %st
  4fddd5:      	fxch	%st(2)
  4fddd7:      	fadds	0xc(%ebp,%eax)
  4fdddb:      	fxch	%st(4)
  4fdddd:      	fmulp	%st, %st(5)
  4fdddf:      	fstps	0xd8(%esp)
  4fdde6:      	fadds	0x10(%ebp,%eax)
  4fddea:      	fxch	%st(3)
  4fddec:      	fadds	(%ebp,%eax)
  4fddf0:      	fxch	%st(2)
  4fddf2:      	fstps	0xdc(%esp)
  4fddf9:      	fadds	0x14(%ebp,%eax)
  4fddfd:      	fxch	%st(2)
  4fddff:      	fstps	0xe0(%esp)
  4fde06:      	fstps	0xd4(%esp)
  4fde0d:      	fstps	0xe4(%esp)
  4fde14:      	movl	0xa0(%esp), %ecx
  4fde1b:      	cmpl	0x400(%esp,%ecx), %edi
  4fde22:      	jl	0x4fdf3c <.text+0xfcf3c>
  4fde28:      	movl	0xfc(%esp,%ecx), %edx
  4fde2f:      	movl	%ecx, %eax
  4fde31:      	movl	%edx, 0xa0(%esp)
  4fde38:      	movl	%edx, %ecx
  4fde3a:      	cmpl	0x400(%esp,%edx), %edi
  4fde41:      	jge	0x4fde28 <.text+0xfce28>
  4fde43:      	flds	0x14(%ebp,%edx)
  4fde47:      	fsubs	0x14(%ebp,%eax)
  4fde4b:      	flds	0x4(%ebp,%edx)
  4fde4f:      	fsubs	0x4(%ebp,%eax)
  4fde53:      	flds	0x10(%ebp,%edx)
  4fde57:      	fsubs	0x10(%ebp,%eax)
  4fde5b:      	fxch	%st(1)
  4fde5d:      	fdivrs	0x62c808
  4fde63:      	flds	0xc(%ebp,%edx)
  4fde67:      	fsubs	0xc(%ebp,%eax)
  4fde6b:      	fxch	%st(1)
  4fde6d:      	fmul	%st, %st(2)
  4fde6f:      	flds	0x8(%ebp,%edx)
  4fde73:      	fsubs	0x8(%ebp,%eax)
  4fde77:      	fxch	%st(2)
  4fde79:      	fmul	%st(1), %st
  4fde7b:      	flds	(%ebp,%edx)
  4fde7f:      	fsubs	(%ebp,%eax)
  4fde83:      	fxch	%st(3)
  4fde85:      	fmul	%st(2), %st
  4fde87:      	fxch	%st(4)
  4fde89:      	fstps	0xbc(%esp)
  4fde90:      	fstps	0xb8(%esp)
  4fde97:      	fmul	%st, %st(3)
  4fde99:      	flds	0x4(%ebp,%eax)
  4fde9d:      	faddl	0x632380
  4fdea3:      	fxch	%st(2)
  4fdea5:      	fmulp	%st, %st(1)
  4fdea7:      	fxch	%st(3)
  4fdea9:      	fstps	0xc8(%esp)
  4fdeb0:      	fstpl	0x38(%esp)
  4fdeb4:      	fstps	0xc4(%esp)
  4fdebb:      	fildl	0x38(%esp)
  4fdebf:      	fxch	%st(1)
  4fdec1:      	fstps	0xc0(%esp)
  4fdec8:      	fsubs	0x4(%ebp,%eax)
  4fdecc:      	flds	0xc0(%esp)
  4fded3:      	flds	0xc4(%esp)
  4fdeda:      	fmul	%st(2), %st
  4fdedc:      	flds	0xb8(%esp)
  4fdee3:      	fmul	%st(3), %st
  4fdee5:      	flds	0xc8(%esp)
  4fdeec:      	fmul	%st(4), %st
  4fdeee:      	fxch	%st(2)
  4fdef0:      	fadds	0x8(%ebp,%eax)
  4fdef4:      	flds	0xbc(%esp)
  4fdefb:      	fmul	%st(5), %st
  4fdefd:      	fxch	%st(2)
  4fdeff:      	fadds	0xc(%ebp,%eax)
  4fdf03:      	fxch	%st(4)
  4fdf05:      	fmulp	%st, %st(5)
  4fdf07:      	fstps	0xa8(%esp)
  4fdf0e:      	fadds	0x10(%ebp,%eax)
  4fdf12:      	fxch	%st(3)
  4fdf14:      	fadds	(%ebp,%eax)
  4fdf18:      	fxch	%st(2)
  4fdf1a:      	fstps	0xac(%esp)
  4fdf21:      	fadds	0x14(%ebp,%eax)
  4fdf25:      	fxch	%st(2)
  4fdf27:      	fstps	0xb0(%esp)
  4fdf2e:      	fstps	0xa4(%esp)
  4fdf35:      	fstps	0xb4(%esp)
  4fdf3c:      	flds	0xd4(%esp)
  4fdf43:      	faddl	0x632380
  4fdf49:      	flds	0xa4(%esp)
  4fdf50:      	faddl	0x632380
  4fdf56:      	fxch	%st(1)
  4fdf58:      	fstpl	0x48(%esp)
  4fdf5c:      	fstpl	0x40(%esp)
  4fdf60:      	movl	0x48(%esp), %edx
  4fdf64:      	movl	0x40(%esp), %ebx
  4fdf68:      	cmpl	%edx, %ebx
  4fdf6a:      	je	0x4fe390 <.text+0xfd390>
  4fdf70:      	jl	0x4fe04f <.text+0xfd04f>
  4fdf76:      	flds	0xb4(%esp)
  4fdf7d:      	fsubs	0xe4(%esp)
  4fdf84:      	flds	0xa4(%esp)
  4fdf8b:      	fsubs	0xd4(%esp)
  4fdf92:      	flds	0xb0(%esp)
  4fdf99:      	fsubs	0xe0(%esp)
  4fdfa0:      	fxch	%st(1)
  4fdfa2:      	fdivrs	0x62c808
  4fdfa8:      	flds	0xac(%esp)
  4fdfaf:      	fsubs	0xdc(%esp)
  4fdfb6:      	fxch	%st(2)
  4fdfb8:      	fmul	%st(1), %st
  4fdfba:      	flds	0xa8(%esp)
  4fdfc1:      	fsubs	0xd8(%esp)
  4fdfc8:      	fxch	%st(3)
  4fdfca:      	fmul	%st(2), %st
  4fdfcc:      	fxch	%st(1)
  4fdfce:      	fstps	0x1c(%esp)
  4fdfd2:      	fxch	%st(1)
  4fdfd4:      	fmul	%st, %st(2)
  4fdfd6:      	fxch	%st(1)
  4fdfd8:      	fstps	0x18(%esp)
  4fdfdc:      	fmulp	%st, %st(2)
  4fdfde:      	fildl	0x48(%esp)
  4fdfe2:      	fxch	%st(1)
  4fdfe4:      	fstps	0x20(%esp)
  4fdfe8:      	fsubs	0xd4(%esp)
  4fdfef:      	fld	%st(1)
  4fdff1:      	faddl	0x632380
  4fdff7:      	fxch	%st(2)
  4fdff9:      	fmul	%st(1), %st
  4fdffb:      	flds	0x1c(%esp)
  4fdfff:      	fxch	%st(3)
  4fe001:      	fstpl	0x68(%esp)
  4fe005:      	fadds	0xe4(%esp)
  4fe00c:      	fxch	%st(2)
  4fe00e:      	flds	0x18(%esp)
  4fe012:      	fmul	%st(2), %st
  4fe014:      	fxch	%st(3)
  4fe016:      	faddl	0x632380
  4fe01c:      	fxch	%st(3)
  4fe01e:      	flds	0x20(%esp)
  4fe022:      	fmul	%st(3), %st
  4fe024:      	fxch	%st(4)
  4fe026:      	fstpl	0x90(%esp)
  4fe02d:      	fadds	0xdc(%esp)
  4fe034:      	fxch	%st(2)
  4fe036:      	fmulp	%st, %st(1)
  4fe038:      	fxch	%st(2)
  4fe03a:      	fadds	0xd8(%esp)
  4fe041:      	fxch	%st(2)
  4fe043:      	fadds	0xe0(%esp)
  4fe04a:      	jmp	0x4fe12d <.text+0xfd12d>
  4fe04f:      	movl	%ebx, 0x48(%esp)
  4fe053:      	movl	%edx, %ebx
  4fe055:      	movl	0x48(%esp), %edx
  4fe059:      	flds	0xe4(%esp)
  4fe060:      	fsubs	0xb4(%esp)
  4fe067:      	flds	0xd4(%esp)
  4fe06e:      	fsubs	0xa4(%esp)
  4fe075:      	flds	0xe0(%esp)
  4fe07c:      	fsubs	0xb0(%esp)
  4fe083:      	fxch	%st(1)
  4fe085:      	fdivrs	0x62c808
  4fe08b:      	flds	0xdc(%esp)
  4fe092:      	fsubs	0xac(%esp)
  4fe099:      	fxch	%st(2)
  4fe09b:      	fmul	%st(1), %st
  4fe09d:      	flds	0xd8(%esp)
  4fe0a4:      	fsubs	0xa8(%esp)
  4fe0ab:      	fxch	%st(3)
  4fe0ad:      	fmul	%st(2), %st
  4fe0af:      	fxch	%st(1)
  4fe0b1:      	fstps	0x1c(%esp)
  4fe0b5:      	fxch	%st(1)
  4fe0b7:      	fmul	%st, %st(2)
  4fe0b9:      	fxch	%st(1)
  4fe0bb:      	fstps	0x18(%esp)
  4fe0bf:      	fmulp	%st, %st(2)
  4fe0c1:      	fildl	0x48(%esp)
  4fe0c5:      	fxch	%st(1)
  4fe0c7:      	fstps	0x20(%esp)
  4fe0cb:      	fsubs	0xa4(%esp)
  4fe0d2:      	fld	%st(1)
  4fe0d4:      	faddl	0x632380
  4fe0da:      	fxch	%st(2)
  4fe0dc:      	fmul	%st(1), %st
  4fe0de:      	flds	0x1c(%esp)
  4fe0e2:      	fxch	%st(3)
  4fe0e4:      	fstpl	0x68(%esp)
  4fe0e8:      	fadds	0xb4(%esp)
  4fe0ef:      	fxch	%st(2)
  4fe0f1:      	flds	0x18(%esp)
  4fe0f5:      	fmul	%st(2), %st
  4fe0f7:      	fxch	%st(3)
  4fe0f9:      	faddl	0x632380
  4fe0ff:      	fxch	%st(3)
  4fe101:      	flds	0x20(%esp)
  4fe105:      	fmul	%st(3), %st
  4fe107:      	fxch	%st(4)
  4fe109:      	fstpl	0x90(%esp)
  4fe110:      	fadds	0xac(%esp)
  4fe117:      	fxch	%st(2)
  4fe119:      	fmulp	%st, %st(1)
  4fe11b:      	fxch	%st(2)
  4fe11d:      	fadds	0xa8(%esp)
  4fe124:      	fxch	%st(2)
  4fe126:      	fadds	0xb0(%esp)
  4fe12d:      	movl	0x68(%esp), %eax
  4fe131:      	movl	0x98(%esp), %edi
  4fe138:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4fe13d:      	subl	%edx, %ebx
  4fe13f:      	orl	$0xfffe0000, %eax       # imm = 0xFFFE0000
  4fe144:      	addl	%edx, %edi
  4fe146:      	movl	%eax, 0x68(%esp)
  4fe14a:      	flds	0x18(%esp)
  4fe14e:      	fmuls	0x62c814
  4fe154:      	flds	0x1c(%esp)
  4fe158:      	fmuls	0x62c814
  4fe15e:      	flds	0x20(%esp)
  4fe162:      	fmuls	0x62c814
  4fe168:      	fxch	%st(2)
  4fe16a:      	fstps	0x24(%esp)
  4fe16e:      	fstps	0x28(%esp)
  4fe172:      	fstps	0x2c(%esp)
  4fe176:      	fxch	%st(2)
  4fe178:      	flds	0x62c80c
  4fe17e:      	fdiv	%st(1), %st
  4fe180:      	fld	%st(3)
  4fe182:      	fmul	%st(1), %st
  4fe184:      	fld	%st(3)
  4fe186:      	fmulp	%st, %st(2)
  4fe188:      	faddl	0x632380
  4fe18e:      	fxch	%st(1)
  4fe190:      	faddl	0x632380
  4fe196:      	fxch	%st(2)
  4fe198:      	fadds	0x2c(%esp)
  4fe19c:      	fxch	%st(1)
  4fe19e:      	fstpl	0x78(%esp)
  4fe1a2:      	fxch	%st(1)
  4fe1a4:      	fstpl	0x70(%esp)
  4fe1a8:      	flds	0x62c80c
  4fe1ae:      	fdiv	%st(1), %st
  4fe1b0:      	decl	%ebx
  4fe1b1:      	jmp	0x4fe292 <.text+0xfd292>
  4fe1b6:      	flds	0x24(%esp)
  4fe1ba:      	faddp	%st, %st(3)
  4fe1bc:      	flds	0x28(%esp)
  4fe1c0:      	faddp	%st, %st(4)
  4fe1c2:      	fld	%st(2)
  4fe1c4:      	fmul	%st(1), %st
  4fe1c6:      	flds	0x2c(%esp)
  4fe1ca:      	fxch	%st(2)
  4fe1cc:      	fmul	%st(5), %st
  4fe1ce:      	fxch	%st(2)
  4fe1d0:      	faddp	%st, %st(3)
  4fe1d2:      	faddl	0x632380
  4fe1d8:      	fxch	%st(1)
  4fe1da:      	faddl	0x632380
  4fe1e0:      	fld	%st(2)
  4fe1e2:      	fxch	%st(2)
  4fe1e4:      	fstpl	0x80(%esp)
  4fe1eb:      	fstpl	0x88(%esp)
  4fe1f2:      	fdivrs	0x62c80c
  4fe1f8:      	movl	0x78(%esp), %ebp
  4fe1fc:      	movl	0x70(%esp), %esi
  4fe200:      	movl	0x88(%esp), %eax
  4fe207:      	movl	0x80(%esp), %edx
  4fe20e:      	subl	%ebp, %eax
  4fe210:      	subl	%esi, %edx
  4fe212:      	sarl	$0x4, %eax
  4fe215:      	movl	%ebx, 0x8(%esp)
  4fe219:      	sarl	$0x4, %edx
  4fe21c:      	movl	0x90(%esp), %ebx
  4fe223:      	movl	%edx, 0x58(%esp)
  4fe227:      	andl	$0xffff, %ebx           # imm = 0xFFFF
  4fe22d:      	movl	%eax, 0x60(%esp)
  4fe231:      	orl	$0x1e0000, %ebx         # imm = 0x1E0000
  4fe237:      	movl	%ebp, %eax
  4fe239:      	movl	%esi, %edx
  4fe23b:      	sarl	$0xa, %eax
  4fe23e:      	movl	0x50(%esp), %ecx
  4fe242:      	sarl	$0x10, %edx
  4fe245:      	andb	$-0x40, %al
  4fe247:      	addl	%ecx, %eax
  4fe249:      	movl	0x68(%esp), %ecx
  4fe24d:      	addl	0x60(%esp), %ebp
  4fe251:      	addl	0x58(%esp), %esi
  4fe255:      	movb	(%eax,%edx), %dl
  4fe258:      	incl	%edi
  4fe259:      	movb	%bh, %dh
  4fe25b:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4fe261:      	movb	0xd1e480(%edx), %al
  4fe267:      	addl	%ecx, %ebx
  4fe269:      	movb	%al, -0x1(%edi)
  4fe26c:      	jge	0x4fe237 <.text+0xfd237>
  4fe26e:      	movl	%ebx, 0x90(%esp)
  4fe275:      	movl	0x8(%esp), %ebx
  4fe279:      	movl	0x80(%esp), %eax
  4fe280:      	movl	0x88(%esp), %edx
  4fe287:      	movl	%eax, 0x70(%esp)
  4fe28b:      	movl	%edx, 0x78(%esp)
  4fe28f:      	subl	$0x10, %ebx
  4fe292:      	cmpl	$0x10, %ebx
  4fe295:      	jge	0x4fe1b6 <.text+0xfd1b6>
  4fe29b:      	movl	0x90(%esp), %eax
  4fe2a2:      	movl	%ebx, %ecx
  4fe2a4:      	decl	%ebx
  4fe2a5:      	movl	0x78(%esp), %ebp
  4fe2a9:      	shll	$0x11, %ebx
  4fe2ac:      	andl	$0xffff, %eax           # imm = 0xFFFF
  4fe2b1:      	movl	0x70(%esp), %esi
  4fe2b5:      	orl	%eax, %ebx
  4fe2b7:      	cmpl	$0x0, %ecx
  4fe2ba:      	je	0x4fe36e <.text+0xfd36e>
  4fe2c0:      	fxch	%st(1)
  4fe2c2:      	fsubs	0x2c(%esp)
  4fe2c6:      	flds	0x20(%esp)
  4fe2ca:      	fmuls	0x62c810(,%ecx,8)
  4fe2d1:      	flds	0x18(%esp)
  4fe2d5:      	fmuls	0x62c810(,%ecx,8)
  4fe2dc:      	flds	0x1c(%esp)
  4fe2e0:      	fmuls	0x62c810(,%ecx,8)
  4fe2e7:      	fxch	%st(2)
  4fe2e9:      	faddp	%st, %st(3)
  4fe2eb:      	faddp	%st, %st(4)
  4fe2ed:      	faddp	%st, %st(4)
  4fe2ef:      	fdivrs	0x62c80c
  4fe2f5:      	fmul	%st, %st(2)
  4fe2f7:      	fildl	0x70(%esp)
  4fe2fb:      	fxch	%st(1)
  4fe2fd:      	fmul	%st(4), %st
  4fe2ff:      	fildl	0x78(%esp)
  4fe303:      	fxch	%st(2)
  4fe305:      	fsubrp	%st, %st(4)
  4fe307:      	fsubp	%st, %st(1)
  4fe309:      	fxch	%st(2)
  4fe30b:      	fmuls	0x62c814(,%ecx,8)
  4fe312:      	fxch	%st(2)
  4fe314:      	fmuls	0x62c814(,%ecx,8)
  4fe31b:      	fxch	%st(2)
  4fe31d:      	faddl	0x632380
  4fe323:      	fxch	%st(2)
  4fe325:      	faddl	0x632380
  4fe32b:      	fxch	%st(2)
  4fe32d:      	fstl	0x58(%esp)
  4fe331:      	fxch	%st(2)
  4fe333:      	fstl	0x60(%esp)
  4fe337:      	movl	%ebp, %eax
  4fe339:      	movl	%esi, %edx
  4fe33b:      	sarl	$0xa, %eax
  4fe33e:      	movl	0x50(%esp), %ecx
  4fe342:      	sarl	$0x10, %edx
  4fe345:      	andb	$-0x40, %al
  4fe347:      	addl	%ecx, %eax
  4fe349:      	movl	0x68(%esp), %ecx
  4fe34d:      	addl	0x60(%esp), %ebp
  4fe351:      	addl	0x58(%esp), %esi
  4fe355:      	movb	(%eax,%edx), %dl
  4fe358:      	incl	%edi
  4fe359:      	movb	%bh, %dh
  4fe35b:      	andl	$0xfffeffff, %ebx       # imm = 0xFFFEFFFF
  4fe361:      	movb	0xd1e480(%edx), %al
  4fe367:      	addl	%ecx, %ebx
  4fe369:      	movb	%al, -0x1(%edi)
  4fe36c:      	jge	0x4fe337 <.text+0xfd337>
  4fe36e:      	sarl	$0xa, %ebp
  4fe371:      	xorl	%edx, %edx
  4fe373:      	sarl	$0x10, %esi
  4fe376:      	movl	0x50(%esp), %eax
  4fe37a:      	andl	$-0x40, %ebp
  4fe37d:      	movb	%bh, %dh
  4fe37f:      	addl	%ebp, %eax
  4fe381:      	fcompp
  4fe383:      	movb	(%eax,%esi), %dl
  4fe386:      	fcompp
  4fe388:      	movb	0xd1e480(%edx), %al
  4fe38e:      	movb	%al, (%edi)
  4fe390:      	flds	0xb4(%esp)
  4fe397:      	fadds	0xc8(%esp)
  4fe39e:      	flds	0xa8(%esp)
  4fe3a5:      	fadds	0xc4(%esp)
  4fe3ac:      	flds	0xb0(%esp)
  4fe3b3:      	fadds	0xbc(%esp)
  4fe3ba:      	flds	0xac(%esp)
  4fe3c1:      	fadds	0xb8(%esp)
  4fe3c8:      	flds	0xa4(%esp)
  4fe3cf:      	fadds	0xc0(%esp)
  4fe3d6:      	fxch	%st(3)
  4fe3d8:      	fstps	0xa8(%esp)
  4fe3df:      	fstps	0xac(%esp)
  4fe3e6:      	fstps	0xb0(%esp)
  4fe3ed:      	fstps	0xa4(%esp)
  4fe3f4:      	fstps	0xb4(%esp)
  4fe3fb:      	flds	0xe4(%esp)
  4fe402:      	fadds	0xf8(%esp)
  4fe409:      	flds	0xd8(%esp)
  4fe410:      	fadds	0xf4(%esp)
  4fe417:      	flds	0xe0(%esp)
  4fe41e:      	fadds	0xec(%esp)
  4fe425:      	flds	0xdc(%esp)
  4fe42c:      	fadds	0xe8(%esp)
  4fe433:      	flds	0xd4(%esp)
  4fe43a:      	fadds	0xf0(%esp)
  4fe441:      	fxch	%st(3)
  4fe443:      	fstps	0xd8(%esp)
  4fe44a:      	fstps	0xdc(%esp)
  4fe451:      	fstps	0xe0(%esp)
  4fe458:      	fstps	0xd4(%esp)
  4fe45f:      	fstps	0xe4(%esp)
  4fe466:      	movl	0x98(%esp), %esi
  4fe46d:      	movl	0xc(%esp), %eax
  4fe471:      	movl	(%esp), %ebp
  4fe474:      	addl	%eax, %esi
  4fe476:      	movl	0x4(%esp), %edi
  4fe47a:      	movl	%esi, 0x98(%esp)
  4fe481:      	incl	%edi
  4fe482:      	jmp	0x4fdcd7 <.text+0xfccd7>
  4fe487:      	addl	$0x700, %esp            # imm = 0x700
  4fe48d:      	popl	%ebp
  4fe48e:      	popl	%edi
  4fe48f:      	popl	%esi
  4fe490:      	popl	%ebx
  4fe491:      	popl	%ebp
  4fe492:      	retl
