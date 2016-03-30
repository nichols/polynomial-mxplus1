CPPFLAGS = -std=c++11 -g -Wall -O3
LDLIBS = 
CXX = g++


f2t_main_print: f2poly.o f2t_sequence.o

f2t_main_print_degrees: f2poly.o f2t_sequence.o

f2t_main_singlecycle: f2poly.o f2t_sequence.o f2t_findcycles.o

f2t_main_allcycles: f2poly.o f2t_sequence.o f2t_findcycles.o

f2xt_main_print: f2poly.o f2xt_sequence.o

f2xt_main_print_degrees: f2poly.o f2xt_sequence.o

f2xt_main_singlecycle: f2poly.o f2xt_sequence.o f2xt_findcycles.o

f2xt_main_allcycles: f2poly.o f2xt_sequence.o f2xt_findcycles.o

f2xt_main_everett: f2poly.o f2xt_sequence.o
