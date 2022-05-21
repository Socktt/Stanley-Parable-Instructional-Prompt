# nasm and qemu
sudo dnf install nasm -y
sudo dnf install qemu -y
sudo dnf install qemu-kvm -y

# GCC cross compiler for i386 systems (might take quite some time, prepare food)

sudo dnf update
sudo dnf install gcc gcc-c++ make -y
sudo dnf install bison -y
sudo dnf install flex -y
sudo dnf install gmp-devel -y
sudo dnf install libmpc-devel -y
sudo dnf install mpfr-devel -y
sudo dnf install texinfo -y

export PREFIX="/usr/local/i386elfgcc"
export TARGET=i386-elf
export PATH="$PREFIX/bin:$PATH"

mkdir /tmp/src
cd /tmp/src
curl -O http://ftp.gnu.org/gnu/binutils/binutils-2.35.1.tar.gz
tar xf binutils-2.35.1.tar.gz
mkdir binutils-build
cd binutils-build
../binutils-2.35.1/configure --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror --prefix=$PREFIX 2>&1 | tee configure.log
sudo make -j 2 all install 2>&1 | tee make.log

cd /tmp/src
curl -O https://ftp.gnu.org/gnu/gcc/gcc-10.2.0/gcc-10.2.0.tar.gz
tar xf gcc-10.2.0.tar.gz
mkdir gcc-build
cd gcc-build
echo Configure: . . . . . . .
../gcc-10.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --disable-libssp --enable-language=c++ --without-headers
echo MAKE ALL-GCC:
sudo make -j 2 all-gcc
echo MAKE ALL-TARGET-LIBGCC:
sudo make -j 2 all-target-libgcc
echo MAKE INSTALL-GCC:
sudo make -j 2 install-gcc
echo MAKE INSTALL-TARGET-LIBGCC:
sudo make -j 2 install-target-libgcc
echo HERE U GO MAYBE:
ls /usr/local/i386elfgcc/bin
export PATH=$PATH:/usr/local/i386elfgcc/bin
