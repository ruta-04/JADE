CXXFLAGS += --std=c++17
//GTKFLAGS +=`/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`

all:make
debug: CXXFALGS += -g
debug: default

main: main.o main_window.o dialogs.o store.o product.o java.o donut.o customer.o order.o
		${CXX} ${CXXFLAGS} -o main main.o main_window.o dialogs.o store.o product.o java.o donut.o customer.o order.o `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main.o: main.cpp *.h
		${CXX} ${CXXFLAGS} -c main.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
main_window.o: main_window.cpp *.h
		${CXX} ${CXXFLAGS} -c main_window.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
dialogs.o:dialogs.cpp *.h
		${CXX} ${CXXFLAGS} -c dialogs.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
store.o: store.cpp *.h
		${CXX} ${CXXFLAGS} -c store.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
product.o: product.cpp *.h
		${CXX} ${CXXFLAGS} -c product.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
java.o: java.cpp *.h
		${CXX} ${CXXFLAGS} -c java.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
donut.o: donut.cpp *.h
		${CXX} ${CXXFLAGS} -c donut.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
customer.o: customer.cpp *.h
		${CXX} ${CXXFLAGS} -c customer.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`
oxrder.o: order.o *.h
		${CXX} ${CXXFLAGS} -c order.cpp `/usr/bin/pkg-config gtkmm-3.0 --cflags --libs`


Clean:
		-rm -f *.gch *.o a.out main
