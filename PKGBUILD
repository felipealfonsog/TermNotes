pkgname=term-notes
pkgver=1.0.0
pkgrel=1
pkgdesc="Terminal-based note-taking application"
arch=('x86_64')
url="https://github.com/felipealfonsog/term-notes"
license=('MIT')
depends=('gcc' 'vim' 'nano')

source=("https://github.com/felipealfonsog/term-notes/archive/v$pkgver.tar.gz")

build() {
  cd "$srcdir/term-notes-$pkgver"
  make
}

package() {
  cd "$srcdir/term-notes-$pkgver"
  install -Dm755 term_notes "$pkgdir/usr/bin/term_notes"
}

sha256sums=('0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef')
