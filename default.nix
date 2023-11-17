{ pkgs ? import<nixpkgs>{} }:

with pkgs;

stdenv.mkDerivation {
  name = "minesweepes";
  src = ./.;
  buildInputs = [ pkgs.ncurses ];
  nativeBuildInputs = [ pkgs.pkg-config ];
  enableParallelBuilding = true;

  installPhase = ''
    mkdir -p $out/bin
    cp bin/minesweepes $out/bin/
  '';
}

