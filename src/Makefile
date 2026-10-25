build:
	g++ chlebqowy-workspace-bar-wl.cpp -o ../bin/chlebqowy-workspace-bar-wl
	g++ chlebqowy-gpu-usage.cpp -o ../bin/chlebqowy-gpu-usage
	g++ chlebqowy-update-num.cpp -o ../bin/chlebqowy-update-num
install:
	rm -v ~/.local/bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-gpu-usage ~/.local/bin/chlebqowy-update-num
	install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
	install -D -m 0755 ../bin/chlebqowy-gpu-usage  ~/.local/bin/chlebqowy-gpu-usage
	install -D -m 0755 ../bin/chlebqowy-update-num ~/.local/bin/chlebqowy-update-num
install-global:
	sudo rm -v ~/.local/bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-gpu-usage ~/.local/bin/chlebqowy-update-num
	sudo install -D -m 0755 ../bin/chlebqowy-workspace-bar-wl ~/.local/bin/chlebqowy-workspace-bar-wl
	sudo install -D -m 0755 ../bin/chlebqowy-gpu-usage  /usr/bin/chlebqowy-gpu-usage
	sudo install -D -m 0755 ../bin/chlebqowy-update-num /usr/bin/chlebqowy-update-num
