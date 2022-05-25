all:
	make release
	make run
	make clean
release:
	clang++ *.cpp -std=c++17 -O3 -o bin/checker
run:
	bin/checker data/in.txt
debug:
	clang++ *.cpp -std=c++17 -Wall -Wextra -Werror -g -o bin/checker
sanitized:
	clang++ *.cpp -std=c++17 -fsanitize=address,undefined,leak -o bin/checker
clean:
	rm -r bin/*