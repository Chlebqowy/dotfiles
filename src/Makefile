build:
	g++ chlebqowy-workspace-bar-wl.cpp -o ../bin/chlebqowy-workspace-bar-wl
	g++ chlebqowy-info-bar-wl.cpp -o ../bin/chlebqowy-info-bar-wl
install:
	rm -fv ~/.local/bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-info-bar-wl
	install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
	install -D -m 0755 ../bin/chlebqowy-info-bar-wl ~/.local/bin/chlebqowy-info-bar-wl
install-global:
	sudo rm -fv ~/.local/bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-gpu-usage ~/.local/bin/chlebqowy-update-num
	sudo install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
	sudo install -D -m 0755 ../bin/chlebqowy-info-bar-wl ~/.local/bin/chlebqowy-info-bar-wl
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
