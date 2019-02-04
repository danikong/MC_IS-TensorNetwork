gen_files = test_ten test_file

class_dir = class/

h_files = tensor randomGen network statMod
cpp_files := $(h_files)

dir := ./$(class_dir)
h_all := $(join $(addsuffix $(class_dir), $(dir $(h_files))), $(h_files:=.h))
cpp_all := $(join $(addsuffix $(class_dir), $(dir $(cpp_files))), $(cpp_files:=.cpp))

main: main.cpp $(h_all) $(cpp_all)
	make -f Makefile.main

# test_ten: test_ten.cpp $(h_all) $(cpp_all)
# 	make -f Makefile.test_ten

tentf: tentf.cpp $(h_all) $(cpp_all)
	make -f Makefile.tentf

nettf: nettf.cpp $(h_all) $(cpp_all)
	make -f Makefile.nettf

# test_net: test_net.cpp $(h_all) $(cpp_all)
# 	make -f Makefile.test_net

empty: empty.cpp $(h_all) $(cpp_all)
	make -f Makefile.empty


clear:
	rm *.o $(gen_files) ./class/*.o *.out ./*.o
