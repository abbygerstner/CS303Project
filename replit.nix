{ pkgs }: {
	deps = [
    pkgs.qt4
		pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}