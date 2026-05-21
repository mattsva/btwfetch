{
  lib,
  stdenv,
}:

stdenv.mkDerivation rec {
  pname = "btwfetch";
  version = "0.0.4";

  src = ./.;

  makeFlags = [
    "PREFIX=$(out)"
  ];

  installPhase = ''
    make install PREFIX=$out
  '';

  meta = with lib; {
    description = "yet another system fetch tool nobody asked for";
    homepage = "https://github.com/mattsva/btwfetch";
    license = licenses.bsd3;
    platforms = platforms.linux;

    mainProgram = "btwfetch";
  };
}
