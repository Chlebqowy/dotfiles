build:
	g++ chlebqowy-workspace-bar-wl.cpp -o ../bin/chlebqowy-workspace-bar-wl
	g++ chlebqowy-info-bar-wl.cpp -o ../bin/chlebqowy-info-bar-wl
	g++ chlebqowy-small-bar-wl.cpp -o ../bin/chlebqowy-small-bar-wl
install:
	rm -fv ~/.local/bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-info-bar-wl ~/.local/bin/chlebqowy-small-bar-wl
	install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
	install -D -m 0755 ../bin/chlebqowy-info-bar-wl ~/.local/bin/chlebqowy-info-bar-wl
	install -D -m 0755 ../bin/chlebqowy-small-bar-wl ~/.local/bin/chlebqowy-small-bar-wl
install-global:
	sudo rm -fv /usr/bin/chlebqowy-workspace-bar-wl /usr/bin/chlebqowy-info-bar-wl /usr/bin/chlebqowy-small-bar-wl
	sudo install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl /usr/bin/chlebqowy-workspace-bar-wl
	sudo install -D -m 0755 ../bin/chlebqowy-info-bar-wl /usr/bin/chlebqowy-info-bar-wl
	sudo install -D -m 0755 ../bin/chlebqowy-small-bar-wl /usr/bin/chlebqowy-small-bar-wl
build-infobar:
	g++ chlebqowy-info-bar-wl.cpp -o ../bin/chlebqowy-info-bar-wl
install-infobar:
	rm -v ~/.local/bin/chlebqowy-info-bar-wl
	install -D -m 0755 ../bin/chlebqowy-info-bar-wl ~/.local/bin/chlebqowy-info-bar-wl
build-wsbar:
	g++ chlebqowy-workspace-bar-wl.cpp -o ../bin/chlebqowy-workspace-bar-wl
install-wsbar:
	rm -fv ~/.local/bin/chlebqowy-workspace-bar-wl
	install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
build-smallbar:
	g++ chlebqowy-small-bar-wl.cpp -o ../bin/chlebqowy-small-bar-wl
install-smallbar:
	rm -fv ~/.local/bin/chlebqowy-small-bar-wl
	install -D -m 0755 ../bin/chlebqowy-small-bar-wl ~/.local/bin/chlebqowy-small-bar-wl
