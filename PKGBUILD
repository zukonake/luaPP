# Author: zukonake <zeukmc@gmail.com>

pkgname=luaPP
pkgver=1.0
pkgrel=1
pkgdesc="Simple Lua to C++ library"
arch=('any')
url="https://github.com/zukonake/$pkgname"
license=(GPL)
depends=('lua>=5.2')
source=("$url/releases/download/$pkgver/$pkgname-$pkgver.tar.xz")

build() {
  cd "$srcdir/$pkgname-$pkgver/"
  make
}

package() {
  cd "$srcdir/$pkgname-$pkgver/"
  make install
}
