
.PHONY: all clean

all:
	@echo C
	gcc -Wall longestCommonPrefix.c -o longestCommonPrefixC && ./longestCommonPrefixC

	@echo CPP
	g++ -Wall longestCommonPrefix.cpp -o longestCommonPrefixCPP && ./longestCommonPrefixCPP

	@echo Haskell
	runghc longestCommonPrefix.hs

clean:
	rm -f *.o *~ longestCommonPrefixC longestCommonPrefixCPP
