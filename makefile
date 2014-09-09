#Change TimeServer.a below to your desired executible filename

#Set all your object files (the object files of all the .cpp files in your project, e.g. main.o my_sub_functions.o )
OBJ = Server.o Main.o Parser.o RequestObject.o FormatterXml.o FormatterString.o FormatterHtml.o FormatterJson.o TimeUtil.o dcftime_client.o

#Set any dependant header files so that if they are edited they cause a complete re-compile (e.g. main.h some_subfunctions.h some_definitions_file.h ), or leave blank
DEPS = Server.h Parser.h RequestObject.h FormatterXml.h FormatterString.h FormatterHtml.h FormatterJson.h TimeUtil.h dcftime_iface.h dcftime_rcp_common.h dcftime_client.h

#Any special libraries you are using in your project (e.g. -lbcm2835 -lrt `pkg-config --libs gtk+-3.0` ), or leave blank
LIBS = -pthread -lboost_system -lboost_serialization

#Set any compiler flags you want to use (e.g. -I/usr/include/somefolder `pkg-config --cflags gtk+-3.0` ), or leave blank
CFLAGS = -std=c++11

#Set the compiler you are using ( gcc for C or g++ for C++ )
CC = g++

#Set the filename extensiton of your C files (e.g. .c or .cpp )
EXTENSION = .cpp

#define a rule that applies to all files ending in the .o suffix, which says that the .o file depends upon the .c version of the file and all the .h files included in the DEPS macro.  Compile each object file
%.o: %$(EXTENSION) $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

#Combine them into the output file
#Set your desired exe output file name here
TimeServer.a: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

#Cleanup
#.PHONY: clean

clean:
	rm -f *.o *~ core *~ 

